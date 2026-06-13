"use client";

import Image from "next/image";
import { FormEvent, useEffect, useState } from "react";
import type { Article, ArticleSummary } from "@/src/domain/article";
import type { Role } from "@/src/domain/role";
import type { AuthUser } from "@/src/domain/user";

type AuthMode = "login" | "register";

const defaultCredentials = {
  username: "",
  password: "",
};

export default function Home() {
  const [articles, setArticles] = useState<ArticleSummary[]>([]);
  const [roles, setRoles] = useState<Role[]>([]);
  const [currentUser, setCurrentUser] = useState<AuthUser | null>(null);
  const [authMode, setAuthMode] = useState<AuthMode>("login");
  const [isAuthOpen, setIsAuthOpen] = useState(false);
  const [credentials, setCredentials] = useState(defaultCredentials);
  const [selectedRole, setSelectedRole] = useState("user");
  const [selectedId, setSelectedId] = useState<string | null>(null);
  const [selectedArticle, setSelectedArticle] = useState<Article | null>(null);
  const [isLoadingArticles, setIsLoadingArticles] = useState(true);
  const [isLoadingArticle, setIsLoadingArticle] = useState(false);
  const [isSubmittingAuth, setIsSubmittingAuth] = useState(false);
  const [error, setError] = useState<string | null>(null);
  const [authMessage, setAuthMessage] = useState<string | null>(null);

  useEffect(() => {
    async function loadInitialData() {
      try {
        const [articlesResponse, rolesResponse] = await Promise.all([
          fetch("/api/articles"),
          fetch("/api/roles"),
        ]);

        if (!articlesResponse.ok) {
          throw new Error("Could not load articles.");
        }

        setArticles(await articlesResponse.json());

        if (rolesResponse.ok) {
          const availableRoles: Role[] = await rolesResponse.json();
          setRoles(availableRoles);
          setSelectedRole(availableRoles[0]?.name ?? "user");
        }
      } catch {
        setError("The newspaper archive could not be loaded.");
      } finally {
        setIsLoadingArticles(false);
      }
    }

    loadInitialData();
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

  async function submitAuth(event: FormEvent<HTMLFormElement>) {
    event.preventDefault();
    setIsSubmittingAuth(true);
    setAuthMessage(null);

    const endpoint =
      authMode === "login" ? "/api/auth/login" : "/api/auth/register";
    const payload =
      authMode === "login"
        ? credentials
        : { ...credentials, role: selectedRole };

    try {
      const response = await fetch(endpoint, {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify(payload),
      });
      const body = await response.json();

      if (!response.ok) {
        throw new Error(body.message ?? "Authentication failed.");
      }

      setCurrentUser(body);
      setCredentials(defaultCredentials);
      setAuthMessage(`Logged in as ${body.username}.`);
    } catch (authError) {
      setAuthMessage(
        authError instanceof Error
          ? authError.message
          : "Authentication failed.",
      );
    } finally {
      setIsSubmittingAuth(false);
    }
  }

  return (
    <main
      className={`newspaper-shell role-${
        currentUser?.role.color ?? "neutral"
      }`}
    >
      <section className="masthead-panel" aria-label="Selected article">
        <div className="auth-panel">
          <button
            className="account-button"
            onClick={() => setIsAuthOpen((current) => !current)}
          >
            {currentUser ? "Account" : "Login / Register"}
          </button>
          {isAuthOpen ? (
            <>
              <div className="auth-tabs">
                <button
                  className={authMode === "login" ? "active" : ""}
                  onClick={() => setAuthMode("login")}
                >
                  Login
                </button>
                <button
                  className={authMode === "register" ? "active" : ""}
                  onClick={() => setAuthMode("register")}
                >
                  Register
                </button>
              </div>
              <form onSubmit={submitAuth} className="auth-form">
                <input
                  aria-label="Username"
                  placeholder="Username"
                  value={credentials.username}
                  onChange={(event) =>
                    setCredentials((current) => ({
                      ...current,
                      username: event.target.value,
                    }))
                  }
                />
                <input
                  aria-label="Password"
                  placeholder="Password"
                  type="password"
                  value={credentials.password}
                  onChange={(event) =>
                    setCredentials((current) => ({
                      ...current,
                      password: event.target.value,
                    }))
                  }
                />
                {authMode === "register" ? (
                  <select
                    aria-label="Role"
                    value={selectedRole}
                    onChange={(event) => setSelectedRole(event.target.value)}
                  >
                    {roles.map((role) => (
                      <option key={role.id} value={role.name}>
                        {role.name}
                      </option>
                    ))}
                  </select>
                ) : null}
                <button type="submit" disabled={isSubmittingAuth}>
                  {isSubmittingAuth ? "Please wait" : authMode}
                </button>
              </form>
            </>
          ) : null}
          {currentUser ? (
            <p className={`session-badge ${currentUser.role.color}`}>
              {currentUser.username} · {currentUser.role.name}
            </p>
          ) : null}
          {authMessage ? <p className="auth-message">{authMessage}</p> : null}
        </div>
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
