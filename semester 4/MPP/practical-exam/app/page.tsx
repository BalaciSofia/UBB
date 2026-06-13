"use client";

import Image from "next/image";
import { useEffect, useState } from "react";
import type { Article, ArticleSummary } from "@/src/domain/article";

export default function Home() {
  const [articles, setArticles] = useState<ArticleSummary[]>([]);
  const [selectedId, setSelectedId] = useState<string | null>(null);
  const [selectedArticle, setSelectedArticle] = useState<Article | null>(null);
  const [isLoadingArticles, setIsLoadingArticles] = useState(true);
  const [isLoadingArticle, setIsLoadingArticle] = useState(false);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    async function loadArticles() {
      try {
        const response = await fetch("/api/articles");

        if (!response.ok) {
          throw new Error("Could not load articles.");
        }

        setArticles(await response.json());
      } catch {
        setError("The newspaper archive could not be loaded.");
      } finally {
        setIsLoadingArticles(false);
      }
    }

    loadArticles();
  }, []);

  async function selectArticle(id: string) {
    setSelectedId(id);
    setSelectedArticle(null);
    setIsLoadingArticle(true);
    setError(null);

    try {
      const response = await fetch(`/api/articles/${id}`);

      if (!response.ok) {
        throw new Error("Could not load article.");
      }

      setSelectedArticle(await response.json());
    } catch {
      setSelectedId(null);
      setError("The selected article could not be loaded.");
    } finally {
      setIsLoadingArticle(false);
    }
  }

  return (
    <main className="newspaper-shell">
      <section className="masthead-panel" aria-label="Selected article">
        {isLoadingArticle ? (
          <div className="brand-stage">
            <p className="kicker">Loading</p>
            <h1>Fetching the article</h1>
          </div>
        ) : selectedArticle ? (
          <article className="article-detail">
            <button
              className="ghost-button"
              onClick={() => {
                setSelectedId(null);
                setSelectedArticle(null);
              }}
            >
              Back to the front page
            </button>
            <p className="eyebrow">{selectedArticle.eyebrow}</p>
            <h1>{selectedArticle.title}</h1>
            <div className="article-meta">
              <span>{selectedArticle.date}</span>
              <span>{selectedArticle.author}</span>
            </div>
            <p className="lead">{selectedArticle.summary}</p>
            {selectedArticle.body.map((paragraph, index) => (
              <p key={index}>{paragraph}</p>
            ))}
          </article>
        ) : (
          <div className="brand-stage">
            <Image
              src="/brain-logo.jpg"
              alt="Teoria Transpiratiei logo"
              width={260}
              height={190}
              priority
              className="logo"
            />
            <p className="kicker">The edition where thoughts work overtime</p>
            <h1>Teoria Transpiratiei</h1>
            <p className="tagline">
              The newspaper where ideas heat up, arguments start to flow, and
              every story arrives with a slightly blue forehead.
            </p>
          </div>
        )}
      </section>

      <aside className="news-menu" aria-label="News list">
        <div className="menu-header">
          <span>Latest articles</span>
          <strong>{articles.length}</strong>
        </div>
        {error ? <p className="menu-message">{error}</p> : null}
        {isLoadingArticles ? (
          <p className="menu-message">Loading articles...</p>
        ) : null}
        <nav>
          {articles.map((article) => (
            <button
              className={`news-item ${
                selectedId === article.id ? "active" : ""
              }`}
              key={article.id}
              onClick={() => selectArticle(article.id)}
            >
              <span>{article.title}</span>
              <time>{article.date}</time>
            </button>
          ))}
        </nav>
      </aside>
    </main>
  );
}
