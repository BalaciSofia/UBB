import { pool } from "@/src/lib/db";
import { ensureDatabaseReady } from "@/src/lib/databaseSetup";
import type { Article, ArticleSummary } from "@/src/domain/article";

type ArticleRow = {
  id: string;
  title: string;
  article_date: string;
  eyebrow: string;
  author: string;
  summary: string;
  body: string[] | string;
};

function mapArticle(row: ArticleRow): Article {
  return {
    id: row.id,
    title: row.title,
    date: row.article_date,
    eyebrow: row.eyebrow,
    author: row.author,
    summary: row.summary,
    body: Array.isArray(row.body) ? row.body : JSON.parse(row.body),
  };
}

class ArticleRepository {
  async findAll(): Promise<ArticleSummary[]> {
    await ensureDatabaseReady();

    const result = await pool.query<ArticleRow>(`
      SELECT id, title, article_date, eyebrow, author, summary, body
      FROM articles
      ORDER BY article_date DESC, title ASC
    `);

    return result.rows.map(({ id, title, article_date, author, summary }) => ({
      id,
      title,
      date: article_date,
      author,
      summary,
    }));
  }

  async findById(id: string): Promise<Article | undefined> {
    await ensureDatabaseReady();

    const result = await pool.query<ArticleRow>(
      `SELECT id, title, article_date, eyebrow, author, summary, body
       FROM articles
       WHERE id = $1`,
      [id],
    );

    const article = result.rows[0];
    return article ? mapArticle(article) : undefined;
  }
}

export const articleRepository = new ArticleRepository();
