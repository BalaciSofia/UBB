import { articleRepository } from "@/src/repositories/articleRepository";

class ArticleService {
  getArticles() {
    return articleRepository.findAll();
  }

  getArticleById(id: string) {
    return articleRepository.findById(id);
  }
}

export const articleService = new ArticleService();
