export type Article = {
  id: string;
  title: string;
  date: string;
  status: ArticleStatus;
  journalists: string[];
  paragraphs: ArticleParagraph[];
  summary: string;
};

export type ArticleStatus = "started" | "pending" | "finished";

export type ArticleImage = {
  id: number;
  path: string;
};

export type ArticleComment = {
  id: number;
  text: string;
};

export type ArticleParagraph = {
  id: number;
  text: string;
  images: ArticleImage[];
  comments: ArticleComment[];
};

export type ArticleEditorPayload = {
  title: string;
  status?: ArticleStatus;
  journalistIds: number[];
  paragraphs: Array<{
    text: string;
    imagePaths: string[];
    comments: string[];
  }>;
};

export type ArticleContentPayload = {
  paragraphs: Array<{
    text: string;
    imagePaths: string[];
  }>;
};

export type LegacySeedArticle = {
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
  "id" | "title" | "date" | "status" | "journalists" | "summary"
>;
