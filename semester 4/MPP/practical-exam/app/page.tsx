"use client";

import Image from "next/image";
import { faker } from "@faker-js/faker";
import { useMemo, useState } from "react";

type Article = {
  id: string;
  title: string;
  date: string;
  eyebrow: string;
  author: string;
  summary: string;
  body: string[];
};

function createArticles(): Article[] {
  faker.seed(13062026);

  return Array.from({ length: 9 }, (_, index) => {
    const topic = faker.helpers.arrayElement([
      "mental heat",
      "urban exhaustion",
      "public anxiety",
      "silent overthinking",
      "office pressure",
      "collective focus",
      "late-night reasoning",
      "intellectual fatigue",
      "nervous ambition",
    ]);
    const place = faker.location.city();
    const expert = faker.person.fullName();
    const title =
      index === 0
        ? "The Brain That Sweats When Ideas Run Too Fast"
        : faker.helpers.arrayElement([
            `Researchers Map the Hidden Climate of ${faker.word.adjective()} Thoughts`,
            `Inside ${place}'s New Debate About ${faker.word.adjective()} Pressure`,
            `Why ${faker.word.adjective()} Ideas Leave a Trace on the Mind`,
            `A Small Theory of ${faker.word.adjective()} Focus Becomes Front Page News`,
            `The Long Afternoon When ${topic} Took Over the City`,
          ]);

    return {
      id: faker.string.uuid(),
      title,
      date: faker.date.recent({ days: 30 }).toLocaleDateString("en-US", {
        day: "2-digit",
        month: "long",
        year: "numeric",
      }),
      eyebrow: faker.helpers.arrayElement([
        "Investigation",
        "Editorial",
        "Field Report",
        "Urban Chronicle",
        "Science of Fatigue",
      ]),
      author: faker.person.fullName(),
      summary: `A new report from ${place} follows how ${topic} shapes ordinary decisions, difficult conversations, and the strange feeling that every idea has its own temperature.`,
      body: [
        `Witnesses describe the phenomenon as subtle at first. Meetings grow quieter, notebooks fill faster, and people begin to notice that concentration has a physical weight. According to ${expert}, the theory is less about sweat itself and more about the moment when thought becomes effort.`,
        `The newspaper's sources say the pattern appears most clearly during long debates, crowded mornings, and decisions that refuse to become simple. In those moments, ${topic} turns from a private sensation into a public mood, visible in pauses, revisions, and careful glances across the room.`,
        `Critics argue that the theory is too theatrical, but supporters believe it gives language to a common experience. They point to students, clerks, editors, and commuters who all describe the same pressure: the mind working hard enough to change the atmosphere around it.`,
        `For now, the evidence remains informal, but the story keeps spreading. Each new account adds another detail to the archive, suggesting that the border between thinking and feeling may be thinner than anyone expected.`,
      ],
    };
  });
}

export default function Home() {
  const articles = useMemo(() => createArticles(), []);
  const [selectedId, setSelectedId] = useState<string | null>(null);
  const selectedArticle =
    articles.find((article) => article.id === selectedId) ?? null;

  return (
    <main className="newspaper-shell">
      <section className="masthead-panel" aria-label="Selected article">
        {selectedArticle ? (
          <article className="article-detail">
            <button className="ghost-button" onClick={() => setSelectedId(null)}>
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
        <nav>
          {articles.map((article) => (
            <button
              className={`news-item ${
                selectedId === article.id ? "active" : ""
              }`}
              key={article.id}
              onClick={() => setSelectedId(article.id)}
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
