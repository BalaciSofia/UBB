"use client";

import Image from "next/image";
import { FormEvent, useEffect, useState } from "react";
import type { Article, ArticleSummary } from "@/src/domain/article";
import type { Role } from "@/src/domain/role";
import type { AuthUser } from "@/src/domain/user";

type AuthMode = "login" | "register";
type EditorParagraph = {
  text: string;
  imagePaths: string[];
  comments: string[];
};

const defaultCredentials = {
  username: "",
  password: "",
};

const defaultEditorParagraph: EditorParagraph = {
  text: "",
  imagePaths: [""],
  comments: [""],
};

function authHeaders(user: AuthUser | null): Record<string, string> {
  return user ? { "x-user-id": String(user.id) } : {};
}

export default function Home() {
  const [articles, setArticles] = useState<ArticleSummary[]>([]);
  const [roles, setRoles] = useState<Role[]>([]);
  const [journalists, setJournalists] = useState<AuthUser[]>([]);
  const [currentUser, setCurrentUser] = useState<AuthUser | null>(null);
  const [authMode, setAuthMode] = useState<AuthMode>("login");
  const [isAuthOpen, setIsAuthOpen] = useState(false);
  const [isEditorComposerOpen, setIsEditorComposerOpen] = useState(false);
  const [editingArticleId, setEditingArticleId] = useState<string | null>(null);
  const [credentials, setCredentials] = useState(defaultCredentials);
  const [selectedRole, setSelectedRole] = useState("user");
  const [editorTitle, setEditorTitle] = useState("");
  const [editorStatus, setEditorStatus] = useState("started");
  const [editorJournalistIds, setEditorJournalistIds] = useState<number[]>([]);
  const [editorParagraphs, setEditorParagraphs] = useState<EditorParagraph[]>([
    defaultEditorParagraph,
  ]);
  const [editorMessage, setEditorMessage] = useState<string | null>(null);
  const [articleEditorMessage, setArticleEditorMessage] = useState<
    string | null
  >(null);
  const [selectedId, setSelectedId] = useState<string | null>(null);
  const [selectedArticle, setSelectedArticle] = useState<Article | null>(null);
  const [isLoadingArticles, setIsLoadingArticles] = useState(true);
  const [isLoadingArticle, setIsLoadingArticle] = useState(false);
  const [isSubmittingAuth, setIsSubmittingAuth] = useState(false);
  const [error, setError] = useState<string | null>(null);
  const [authMessage, setAuthMessage] = useState<string | null>(null);
  const isEditor = currentUser?.role.name === "editor";
  const isJournalist = currentUser?.role.name === "journalist";
  const canEditSelectedArticle =
    isEditor ||
    (isJournalist &&
      !!selectedArticle &&
      selectedArticle.journalists.includes(currentUser.username));

  useEffect(() => {
    async function loadInitialData() {
      try {
        const [articlesResponse, rolesResponse, journalistsResponse] =
          await Promise.all([
            fetch("/api/articles"),
            fetch("/api/roles"),
            fetch("/api/journalists"),
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

        if (journalistsResponse.ok) {
          const availableJournalists: AuthUser[] =
            await journalistsResponse.json();
          setJournalists(availableJournalists);
          setEditorJournalistIds(
            availableJournalists.slice(0, 1).map((journalist) => journalist.id),
          );
        }
      } catch {
        setError("The newspaper archive could not be loaded.");
      } finally {
        setIsLoadingArticles(false);
      }
    }

    loadInitialData();
  }, []);

  async function refreshArticles(user = currentUser) {
    const response = await fetch("/api/articles", {
      headers: authHeaders(user),
    });

    if (response.ok) {
      setArticles(await response.json());
    }
  }

  async function selectArticle(id: string) {
    setSelectedId(id);
    setSelectedArticle(null);
    setIsLoadingArticle(true);
    setError(null);

    try {
      const response = await fetch(`/api/articles/${id}`, {
        headers: authHeaders(currentUser),
      });

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
      setIsAuthOpen(false);
      await refreshArticles(body);
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

  function updateEditorParagraph(
    index: number,
    changes: Partial<EditorParagraph>,
  ) {
    setEditorParagraphs((current) =>
      current.map((paragraph, paragraphIndex) =>
        paragraphIndex === index ? { ...paragraph, ...changes } : paragraph,
      ),
    );
  }

  function updateEditorImage(
    paragraphIndex: number,
    imageIndex: number,
    value: string,
  ) {
    setEditorParagraphs((current) =>
      current.map((paragraph, currentParagraphIndex) => {
        if (currentParagraphIndex !== paragraphIndex) {
          return paragraph;
        }

        return {
          ...paragraph,
          imagePaths: paragraph.imagePaths.map((path, currentImageIndex) =>
            currentImageIndex === imageIndex ? value : path,
          ),
        };
      }),
    );
  }

  function updateEditorComment(
    paragraphIndex: number,
    commentIndex: number,
    value: string,
  ) {
    setEditorParagraphs((current) =>
      current.map((paragraph, currentParagraphIndex) => {
        if (currentParagraphIndex !== paragraphIndex) {
          return paragraph;
        }

        return {
          ...paragraph,
          comments: paragraph.comments.map((comment, currentCommentIndex) =>
            currentCommentIndex === commentIndex ? value : comment,
          ),
        };
      }),
    );
  }

  function toggleJournalist(journalistId: number) {
    setEditorJournalistIds((current) => {
      if (current.includes(journalistId)) {
        return current.filter((id) => id !== journalistId);
      }

      return [...current, journalistId].slice(0, 2);
    });
  }

  function resetEditorForm() {
    setEditorTitle("");
    setEditorParagraphs([defaultEditorParagraph]);
    setEditorStatus("started");
    setEditingArticleId(null);
    setArticleEditorMessage(null);
    setEditorMessage(null);
  }

  function openCreateArticle() {
    resetEditorForm();
    setIsEditorComposerOpen(true);
    setSelectedId(null);
    setSelectedArticle(null);
  }

  async function saveEditorArticle(event: FormEvent<HTMLFormElement>) {
    event.preventDefault();
    setEditorMessage(null);

    if (!currentUser || (!isEditor && !isJournalist)) {
      setEditorMessage("You must be logged in with an internal role.");
      return;
    }

    const payload = {
      title: editorTitle,
      journalistIds: editorJournalistIds,
      paragraphs: editorParagraphs.map((paragraph) => ({
        text: paragraph.text,
        imagePaths: paragraph.imagePaths.filter((path) => path.trim()),
        comments: paragraph.comments.filter((comment) => comment.trim()),
      })),
    };

    const endpoint = editingArticleId
      ? `/api/articles/${editingArticleId}`
      : "/api/articles";
    const response = await fetch(endpoint, {
      method: editingArticleId ? "PUT" : "POST",
      headers: {
        "Content-Type": "application/json",
        "x-user-id": String(currentUser.id),
      },
      body: JSON.stringify(payload),
    });
    const body = await response.json();

    if (!response.ok) {
      setEditorMessage(body.errors?.join(" ") ?? body.message);
      return;
    }

    const articleId = editingArticleId ?? body.id;

    if (isEditor) {
      await fetch(`/api/articles/${articleId}`, {
        method: "PATCH",
        headers: {
          "Content-Type": "application/json",
          "x-user-id": String(currentUser.id),
        },
        body: JSON.stringify({ status: editorStatus }),
      });
    }
    await refreshArticles();
    await selectArticle(articleId);
    setIsEditorComposerOpen(false);
    resetEditorForm();
    setEditorMessage(editingArticleId ? "Article updated." : "Article created.");
  }

  function loadSelectedArticleForEditing() {
    if (!selectedArticle || !canEditSelectedArticle) {
      return;
    }

    setEditorTitle(selectedArticle.title);
    setEditorStatus(selectedArticle.status);
    setEditorJournalistIds(
      journalists
        .filter((journalist) =>
          selectedArticle.journalists.includes(journalist.username),
        )
        .map((journalist) => journalist.id)
        .slice(0, 2),
    );
    setEditorParagraphs(
      selectedArticle.paragraphs.map((paragraph) => ({
        text: paragraph.text,
        imagePaths:
          paragraph.images.length > 0
            ? paragraph.images.map((image) => image.path)
            : [""],
        comments:
          paragraph.comments.length > 0
            ? paragraph.comments.map((comment) => comment.text)
            : [""],
      })),
    );
    setEditingArticleId(selectedArticle.id);
    setIsEditorComposerOpen(true);
    setArticleEditorMessage("Loaded in editor form.");
  }

  async function deleteSelectedArticle() {
    if (!currentUser || !selectedArticle) {
      return;
    }

    const response = await fetch(`/api/articles/${selectedArticle.id}`, {
      method: "DELETE",
      headers: {
        "x-user-id": String(currentUser.id),
      },
    });
    const body = await response.json();

    if (!response.ok) {
      setArticleEditorMessage(body.message);
      return;
    }

    setSelectedId(null);
    setSelectedArticle(null);
    setArticleEditorMessage(null);
    await refreshArticles();
  }

  function renderEditorComposer() {
    const isJournalistComposer = isJournalist && !isEditor;

    return (
      <form className="editor-composer" onSubmit={saveEditorArticle}>
        <div className="composer-heading">
          <div>
            <p className="eyebrow">
              {isJournalistComposer ? "Journalist desk" : "Editor desk"}
            </p>
            <h1>
              {editingArticleId
                ? isJournalistComposer
                  ? "Edit assignment"
                  : "Edit article"
                : "Create article"}
            </h1>
          </div>
          <button
            type="button"
            onClick={() => {
              setIsEditorComposerOpen(false);
              resetEditorForm();
            }}
          >
            Close
          </button>
        </div>
        <div className="composer-grid">
          <label>
            Title
            <input
              placeholder="Article title"
              disabled={isJournalistComposer}
              value={editorTitle}
              onChange={(event) => setEditorTitle(event.target.value)}
            />
          </label>
          <label>
            Status
            <select
              disabled={isJournalistComposer}
              value={editorStatus}
              onChange={(event) => setEditorStatus(event.target.value)}
            >
              <option value="started">started</option>
              <option value="pending">pending</option>
              <option value="finished">finished</option>
            </select>
          </label>
        </div>
        <div className="composer-card">
          <strong>Journalists</strong>
          <p>
            {isJournalistComposer
              ? "Assigned team for this article."
              : "Select one or two journalists for this article."}
          </p>
          <div className="journalist-picker">
            {journalists.map((journalist) => (
              <label key={journalist.id}>
                <input
                  type="checkbox"
                  disabled={isJournalistComposer}
                  checked={editorJournalistIds.includes(journalist.id)}
                  onChange={() => toggleJournalist(journalist.id)}
                />
                {journalist.username}
              </label>
            ))}
          </div>
        </div>
        {editorParagraphs.map((paragraph, paragraphIndex) => (
          <div className="composer-card" key={paragraphIndex}>
            <strong>Paragraph {paragraphIndex + 1}</strong>
            <textarea
              placeholder="Paragraph text"
              value={paragraph.text}
              onChange={(event) =>
                updateEditorParagraph(paragraphIndex, {
                  text: event.target.value,
                })
              }
            />
            {paragraph.imagePaths.map((path, imageIndex) => (
              <input
                key={imageIndex}
                placeholder="Image path"
                value={path}
                onChange={(event) =>
                  updateEditorImage(
                    paragraphIndex,
                    imageIndex,
                    event.target.value,
                  )
                }
              />
            ))}
            {paragraph.comments.map((comment, commentIndex) => (
              <div className="readonly-comment" key={commentIndex}>
                <span>Editor comment</span>
                {isJournalistComposer ? (
                  <p>{comment}</p>
                ) : (
                  <input
                    placeholder="Editor comment"
                    value={comment}
                    onChange={(event) =>
                      updateEditorComment(
                        paragraphIndex,
                        commentIndex,
                        event.target.value,
                      )
                    }
                  />
                )}
              </div>
            ))}
            <div className="composer-actions">
              <button
                type="button"
                onClick={() =>
                  updateEditorParagraph(paragraphIndex, {
                    imagePaths: [...paragraph.imagePaths, ""],
                  })
                }
              >
                Add photo
              </button>
              {!isJournalistComposer ? (
                <button
                  type="button"
                  onClick={() =>
                    updateEditorParagraph(paragraphIndex, {
                      comments: [...paragraph.comments, ""],
                    })
                  }
                >
                  Add comment
                </button>
              ) : null}
            </div>
          </div>
        ))}
        <div className="composer-actions">
          <button
            type="button"
            onClick={() =>
              setEditorParagraphs((current) => [
                ...current,
                { text: "", imagePaths: [""], comments: [""] },
              ])
            }
          >
            Add paragraph
          </button>
          <button type="submit">
            {isJournalistComposer
              ? "Save assignment"
              : editingArticleId
                ? "Save article"
                : "Publish draft"}
          </button>
        </div>
        {editorMessage ? <p className="auth-message">{editorMessage}</p> : null}
      </form>
    );
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
          {authMessage && isAuthOpen ? (
            <p className="auth-message">{authMessage}</p>
          ) : null}
        </div>
        {(isEditor || isJournalist) && isEditorComposerOpen ? (
          renderEditorComposer()
        ) : isLoadingArticle ? (
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
            <p className="eyebrow">{selectedArticle.status}</p>
            <h1>{selectedArticle.title}</h1>
            <div className="article-meta">
              <span>{selectedArticle.date}</span>
              <span>
                {selectedArticle.journalists.length > 0
                  ? selectedArticle.journalists.join(", ")
                  : "Editorial team"}
              </span>
            </div>
            <p className="lead">{selectedArticle.summary}</p>
            {canEditSelectedArticle ? (
              <div className="article-editor-actions">
                <strong>
                  {isJournalist ? "Journalist controls" : "Editor controls"}
                </strong>
                <p>
                  {isJournalist
                    ? "Edit the paragraphs and images for this assigned article. Editor comments are visible in the edit form."
                    : "Edit this article in the main workspace, change its status or journalist team, or remove it from the journal."}
                </p>
                <div>
                  <button type="button" onClick={loadSelectedArticleForEditing}>
                    {isJournalist ? "Edit assignment" : "Edit article"}
                  </button>
                  {isEditor ? (
                    <button type="button" onClick={deleteSelectedArticle}>
                      Delete article
                    </button>
                  ) : null}
                </div>
                {articleEditorMessage ? <p>{articleEditorMessage}</p> : null}
              </div>
            ) : null}
            {selectedArticle.paragraphs.map((paragraph) => (
              <section className="paragraph-block" key={paragraph.id}>
                <p>{paragraph.text}</p>
                {paragraph.images.map((image) => (
                  // eslint-disable-next-line @next/next/no-img-element
                  <img src={image.path} alt="" key={image.id} />
                ))}
              </section>
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
        {isEditor ? (
          <button className="menu-add-button" onClick={openCreateArticle}>
            Add article
          </button>
        ) : null}
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
