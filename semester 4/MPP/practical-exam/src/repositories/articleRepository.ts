import { randomUUID } from "crypto";
import { pool } from "@/src/lib/db";
import { ensureDatabaseReady } from "@/src/lib/databaseSetup";
import type {
  Article,
  ArticleContentPayload,
  ArticleComment,
  ArticleEditorPayload,
  ArticleImage,
  ArticleParagraph,
  ArticleStatus,
  ArticleSummary,
} from "@/src/domain/article";
import type { RoleName } from "@/src/domain/role";

type ArticleRow = {
  id: string;
  title: string;
  article_date: string;
  status: ArticleStatus;
  summary: string;
};

type ParagraphRow = {
  id: number;
  text: string;
};

type ImageRow = {
  id: number;
  paragraph_id: number;
  path: string;
};

type CommentRow = {
  id: number;
  paragraph_id: number;
  text: string;
};

type JournalistRow = {
  username: string;
};

async function getParagraphs(articleId: string): Promise<ArticleParagraph[]> {
  const paragraphResult = await pool.query<ParagraphRow>(
    `SELECT id, text
     FROM paragraphs
     WHERE article_id = $1
     ORDER BY position ASC`,
    [articleId],
  );

  if (paragraphResult.rows.length === 0) {
    return [];
  }

  const imageResult = await pool.query<ImageRow>(
    `SELECT images.id, images.paragraph_id, images.path
     FROM images
     JOIN paragraphs ON paragraphs.id = images.paragraph_id
     WHERE paragraphs.article_id = $1
     ORDER BY images.id ASC`,
    [articleId],
  );

  const imagesByParagraph = new Map<number, ArticleImage[]>();
  const commentsByParagraph = new Map<number, ArticleComment[]>();

  for (const image of imageResult.rows) {
    const paragraphImages = imagesByParagraph.get(image.paragraph_id) ?? [];
    paragraphImages.push({ id: image.id, path: image.path });
    imagesByParagraph.set(image.paragraph_id, paragraphImages);
  }

  const commentResult = await pool.query<CommentRow>(
    `SELECT comments.id, comments.paragraph_id, comments.text
     FROM comments
     JOIN paragraphs ON paragraphs.id = comments.paragraph_id
     WHERE paragraphs.article_id = $1
     ORDER BY comments.id ASC`,
    [articleId],
  );

  for (const comment of commentResult.rows) {
    const paragraphComments =
      commentsByParagraph.get(comment.paragraph_id) ?? [];
    paragraphComments.push({ id: comment.id, text: comment.text });
    commentsByParagraph.set(comment.paragraph_id, paragraphComments);
  }

  return paragraphResult.rows.map((paragraph) => ({
    id: paragraph.id,
    text: paragraph.text,
    images: imagesByParagraph.get(paragraph.id) ?? [],
    comments: commentsByParagraph.get(paragraph.id) ?? [],
  }));
}

async function getJournalists(articleId: string): Promise<string[]> {
  const result = await pool.query<JournalistRow>(
    `SELECT users.username
     FROM article_journalists
     JOIN users ON users.id = article_journalists.journalist_id
     WHERE article_journalists.article_id = $1
     ORDER BY users.username ASC`,
    [articleId],
  );

  return result.rows.map((row) => row.username);
}

async function mapArticle(row: ArticleRow): Promise<Article> {
  const paragraphs = await getParagraphs(row.id);

  return {
    id: row.id,
    title: row.title,
    date: row.article_date,
    status: row.status,
    journalists: await getJournalists(row.id),
    summary: row.summary,
    paragraphs,
  };
}

class ArticleRepository {
  async findAll(
    roleName?: RoleName,
    viewerId?: number,
  ): Promise<ArticleSummary[]> {
    await ensureDatabaseReady();

    const result = await pool.query<ArticleRow>(
      `
      SELECT id, title, article_date, status, summary
      FROM articles
      WHERE
        $1 = 'editor'
        OR status = 'finished'
        OR (
          $1 = 'journalist'
          AND EXISTS (
            SELECT 1
            FROM article_journalists
            WHERE article_journalists.article_id = articles.id
              AND article_journalists.journalist_id = $2
          )
        )
      ORDER BY article_date DESC, title ASC
    `,
      [roleName ?? "user", viewerId ?? null],
    );

    return Promise.all(
      result.rows.map(async (row) => ({
        id: row.id,
        title: row.title,
        date: row.article_date,
        status: row.status,
        summary: row.summary,
        journalists: await getJournalists(row.id),
      })),
    );
  }

  async findById(
    id: string,
    roleName?: RoleName,
    viewerId?: number,
  ): Promise<Article | undefined> {
    await ensureDatabaseReady();

    const result = await pool.query<ArticleRow>(
      `SELECT id, title, article_date, status, summary
       FROM articles
       WHERE id = $1
        AND (
          $2 = 'editor'
          OR status = 'finished'
          OR (
            $2 = 'journalist'
            AND EXISTS (
              SELECT 1
              FROM article_journalists
              WHERE article_journalists.article_id = articles.id
                AND article_journalists.journalist_id = $3
            )
          )
        )`,
      [id, roleName ?? "user", viewerId ?? null],
    );

    return result.rows[0] ? mapArticle(result.rows[0]) : undefined;
  }

  async create(
    editorId: number,
    payload: ArticleEditorPayload,
  ): Promise<Article> {
    await ensureDatabaseReady();

    const id = randomUUID();
    const summary = payload.paragraphs[0]?.text.slice(0, 220) ?? "";
    const client = await pool.connect();

    try {
      await client.query("BEGIN");
      await client.query(
        `INSERT INTO articles
          (id, title, article_date, status, eyebrow, author, summary, body, editor_id)
         VALUES ($1, $2, $3, 'started', 'Editor Desk', '', $4, '[]'::jsonb, $5)`,
        [
          id,
          payload.title,
          new Date().toLocaleDateString("en-US", {
            day: "2-digit",
            month: "long",
            year: "numeric",
          }),
          summary,
          editorId,
        ],
      );

      await this.replaceJournalists(id, payload.journalistIds, client);
      await this.replaceParagraphs(id, payload.paragraphs, client);
      await client.query("COMMIT");
    } catch (error) {
      await client.query("ROLLBACK");
      throw error;
    } finally {
      client.release();
    }

    const article = await this.findById(id, "editor", editorId);

    if (!article) {
      throw new Error("Created article could not be loaded.");
    }

    return article;
  }

  async update(
    id: string,
    payload: ArticleEditorPayload,
  ): Promise<Article | undefined> {
    await ensureDatabaseReady();

    const summary = payload.paragraphs[0]?.text.slice(0, 220) ?? "";
    const client = await pool.connect();

    try {
      await client.query("BEGIN");
      const result = await client.query(
        `UPDATE articles
         SET title = $1, summary = $2
         WHERE id = $3`,
        [payload.title, summary, id],
      );

      if (result.rowCount === 0) {
        await client.query("ROLLBACK");
        return undefined;
      }

      await this.replaceJournalists(id, payload.journalistIds, client);
      await this.replaceParagraphs(id, payload.paragraphs, client);
      await client.query("COMMIT");
    } catch (error) {
      await client.query("ROLLBACK");
      throw error;
    } finally {
      client.release();
    }

    return this.findById(id, "editor");
  }

  async updateContent(
    id: string,
    payload: ArticleContentPayload,
  ): Promise<Article | undefined> {
    await ensureDatabaseReady();

    const exists = await pool.query<{ id: string }>(
      "SELECT id FROM articles WHERE id = $1",
      [id],
    );

    if (!exists.rows[0]) {
      return undefined;
    }

    const existingParagraphs = await getParagraphs(id);
    const client = await pool.connect();

    try {
      await client.query("BEGIN");
      await this.replaceParagraphs(
        id,
        payload.paragraphs.map((paragraph, index) => ({
          ...paragraph,
          comments:
            existingParagraphs[index]?.comments.map((comment) => comment.text) ??
            [],
        })),
        client,
      );
      await client.query("COMMIT");
    } catch (error) {
      await client.query("ROLLBACK");
      throw error;
    } finally {
      client.release();
    }

    return this.findById(id, "editor");
  }

  async updateStatus(
    id: string,
    status: ArticleStatus,
  ): Promise<Article | undefined> {
    await ensureDatabaseReady();

    const result = await pool.query(
      "UPDATE articles SET status = $1 WHERE id = $2",
      [status, id],
    );

    if (result.rowCount === 0) {
      return undefined;
    }

    return this.findById(id, "editor");
  }

  async isJournalistAssigned(
    articleId: string,
    journalistId: number,
  ): Promise<boolean> {
    await ensureDatabaseReady();

    const result = await pool.query<{ exists: boolean }>(
      `SELECT EXISTS (
        SELECT 1
        FROM article_journalists
        WHERE article_id = $1 AND journalist_id = $2
      )`,
      [articleId, journalistId],
    );

    return result.rows[0]?.exists ?? false;
  }

  async delete(id: string): Promise<boolean> {
    await ensureDatabaseReady();

    const result = await pool.query("DELETE FROM articles WHERE id = $1", [id]);
    return (result.rowCount ?? 0) > 0;
  }

  private async replaceJournalists(
    articleId: string,
    journalistIds: number[],
    client: Pick<typeof pool, "query">,
  ) {
    await client.query("DELETE FROM article_journalists WHERE article_id = $1", [
      articleId,
    ]);

    for (const journalistId of journalistIds) {
      await client.query(
        `INSERT INTO article_journalists (article_id, journalist_id)
         VALUES ($1, $2)`,
        [articleId, journalistId],
      );
    }
  }

  private async replaceParagraphs(
    articleId: string,
    paragraphs: ArticleEditorPayload["paragraphs"],
    client: Pick<typeof pool, "query">,
  ) {
    await client.query("DELETE FROM paragraphs WHERE article_id = $1", [
      articleId,
    ]);

    for (const [index, paragraph] of paragraphs.entries()) {
      const paragraphResult = await client.query<{ id: number }>(
        `INSERT INTO paragraphs (article_id, text, position)
         VALUES ($1, $2, $3)
         RETURNING id`,
        [articleId, paragraph.text, index],
      );

      for (const imagePath of paragraph.imagePaths) {
        await client.query(
          "INSERT INTO images (paragraph_id, path) VALUES ($1, $2)",
          [paragraphResult.rows[0].id, imagePath],
        );
      }

      for (const comment of paragraph.comments) {
        await client.query(
          "INSERT INTO comments (paragraph_id, text) VALUES ($1, $2)",
          [paragraphResult.rows[0].id, comment],
        );
      }
    }
  }
}

export const articleRepository = new ArticleRepository();
