import { faker } from "@faker-js/faker";
import type { Article, ArticleSummary } from "@/src/domain/article";

function createArticles(): Article[] {
  faker.seed(13062026);

  return Array.from({ length: 18 }, (_, index) => {
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

class ArticleRepository {
  private readonly articles = createArticles();

  findAll(): ArticleSummary[] {
    return this.articles.map(({ id, title, date, author, summary }) => ({
      id,
      title,
      date,
      author,
      summary,
    }));
  }

  findById(id: string): Article | undefined {
    return this.articles.find((article) => article.id === id);
  }
}

export const articleRepository = new ArticleRepository();
