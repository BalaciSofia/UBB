import { pool } from "@/src/lib/db";
import { createSeedArticles } from "@/src/lib/createArticles";

let setupPromise: Promise<void> | null = null;

export function ensureDatabaseReady() {
  setupPromise ??= setupDatabase();
  return setupPromise;
}

async function setupDatabase() {
  await pool.query(`
    CREATE TABLE IF NOT EXISTS roles (
      id SERIAL PRIMARY KEY,
      name VARCHAR(30) UNIQUE NOT NULL,
      color VARCHAR(30) NOT NULL
    );

    CREATE TABLE IF NOT EXISTS permissions (
      id SERIAL PRIMARY KEY,
      role_id INTEGER NOT NULL REFERENCES roles(id) ON DELETE CASCADE,
      name VARCHAR(80) NOT NULL,
      UNIQUE(role_id, name)
    );

    CREATE TABLE IF NOT EXISTS users (
      id SERIAL PRIMARY KEY,
      username VARCHAR(80) UNIQUE NOT NULL,
      password VARCHAR(120) NOT NULL,
      role_id INTEGER NOT NULL REFERENCES roles(id)
    );

    CREATE TABLE IF NOT EXISTS articles (
      id VARCHAR(80) PRIMARY KEY,
      title TEXT NOT NULL,
      article_date VARCHAR(80) NOT NULL,
      eyebrow VARCHAR(80) NOT NULL,
      author VARCHAR(120) NOT NULL,
      summary TEXT NOT NULL,
      body JSONB NOT NULL,
      status VARCHAR(30) NOT NULL DEFAULT 'started',
      editor_id INTEGER REFERENCES users(id)
    );

    CREATE TABLE IF NOT EXISTS article_journalists (
      article_id VARCHAR(80) NOT NULL REFERENCES articles(id) ON DELETE CASCADE,
      journalist_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
      PRIMARY KEY (article_id, journalist_id)
    );

    CREATE TABLE IF NOT EXISTS paragraphs (
      id SERIAL PRIMARY KEY,
      article_id VARCHAR(80) NOT NULL REFERENCES articles(id) ON DELETE CASCADE,
      text TEXT NOT NULL,
      position INTEGER NOT NULL,
      UNIQUE(article_id, position)
    );

    CREATE TABLE IF NOT EXISTS images (
      id SERIAL PRIMARY KEY,
      paragraph_id INTEGER NOT NULL REFERENCES paragraphs(id) ON DELETE CASCADE,
      path TEXT NOT NULL
    );
  `);

  await pool.query(`
    ALTER TABLE articles
      ADD COLUMN IF NOT EXISTS status VARCHAR(30) NOT NULL DEFAULT 'started',
      ADD COLUMN IF NOT EXISTS editor_id INTEGER REFERENCES users(id);
  `);

  await pool.query(`
    INSERT INTO roles (name, color)
    VALUES
      ('admin', 'red'),
      ('journalist', 'blue'),
      ('editor', 'yellow'),
      ('user', 'green')
    ON CONFLICT (name) DO UPDATE SET color = EXCLUDED.color;
  `);

  await pool.query(`
    INSERT INTO permissions (role_id, name)
    SELECT id, permission_name
    FROM roles
    CROSS JOIN (
      VALUES
        ('read_articles'),
        ('login'),
        ('register'),
        ('create_article'),
        ('assign_journalists'),
        ('change_article_status')
    ) AS permissions(permission_name)
    ON CONFLICT (role_id, name) DO NOTHING;
  `);

  await pool.query(`
    INSERT INTO users (username, password, role_id)
    SELECT 'admin', 'admin', id
    FROM roles
    WHERE name = 'admin'
    ON CONFLICT (username) DO NOTHING;
  `);

  await pool.query(`
    INSERT INTO users (username, password, role_id)
    SELECT seed.username, seed.password, roles.id
    FROM (
      VALUES
        ('editor', 'editor', 'editor'),
        ('journalist1', 'journalist1', 'journalist'),
        ('journalist2', 'journalist2', 'journalist')
    ) AS seed(username, password, role_name)
    JOIN roles ON roles.name = seed.role_name
    ON CONFLICT (username) DO NOTHING;
  `);

  const articleCount = await pool.query<{ count: string }>(
    "SELECT COUNT(*) FROM articles",
  );

  if (Number(articleCount.rows[0].count) === 0) {
    for (const article of createSeedArticles()) {
      await pool.query(
        `INSERT INTO articles
          (id, title, article_date, eyebrow, author, summary, body)
         VALUES ($1, $2, $3, $4, $5, $6, $7)`,
        [
          article.id,
          article.title,
          article.date,
          article.eyebrow,
          article.author,
          article.summary,
          JSON.stringify(article.body),
        ],
      );
    }
  }

  await seedArticleParagraphsAndJournalists();
}

async function seedArticleParagraphsAndJournalists() {
  const editor = await pool.query<{ id: number }>(
    "SELECT users.id FROM users JOIN roles ON roles.id = users.role_id WHERE roles.name = 'editor' ORDER BY users.id LIMIT 1",
  );
  const journalists = await pool.query<{ id: number }>(
    "SELECT users.id FROM users JOIN roles ON roles.id = users.role_id WHERE roles.name = 'journalist' ORDER BY users.id LIMIT 2",
  );

  if (editor.rows[0]) {
    await pool.query("UPDATE articles SET editor_id = $1 WHERE editor_id IS NULL", [
      editor.rows[0].id,
    ]);
  }

  const articles = await pool.query<{
    id: string;
    body: string[] | string;
  }>("SELECT id, body FROM articles");

  for (const article of articles.rows) {
    for (const journalist of journalists.rows) {
      await pool.query(
        `INSERT INTO article_journalists (article_id, journalist_id)
         VALUES ($1, $2)
         ON CONFLICT DO NOTHING`,
        [article.id, journalist.id],
      );
    }

    const paragraphCount = await pool.query<{ count: string }>(
      "SELECT COUNT(*) FROM paragraphs WHERE article_id = $1",
      [article.id],
    );

    if (Number(paragraphCount.rows[0].count) > 0) {
      continue;
    }

    const body = Array.isArray(article.body)
      ? article.body
      : JSON.parse(article.body);

    for (const [index, text] of body.entries()) {
      await pool.query(
        `INSERT INTO paragraphs (article_id, text, position)
         VALUES ($1, $2, $3)`,
        [article.id, text, index],
      );
    }
  }
}
