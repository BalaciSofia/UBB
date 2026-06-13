export type Article = {
  id: string;
  title: string;
  date: string;
  eyebrow: string;
  author: string;
  summary: string;
  body: string[];
};

export type ArticleSummary = Pick<
  Article,
  "id" | "title" | "date" | "author" | "summary"
>;
