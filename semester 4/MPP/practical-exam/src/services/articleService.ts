import { articleRepository } from "@/src/repositories/articleRepository";

class ArticleService {
  async getArticles() {
    return articleRepository.findAll();
  }

  async getArticleById(id: string) {
    return articleRepository.findById(id);
  }
}

export const articleService = new ArticleService();
