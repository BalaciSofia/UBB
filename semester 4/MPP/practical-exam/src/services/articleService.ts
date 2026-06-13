import { articleRepository } from "@/src/repositories/articleRepository";
import type {
  ArticleContentPayload,
  ArticleEditorPayload,
  ArticleStatus,
} from "@/src/domain/article";
import { userRepository } from "@/src/repositories/userRepository";

class ArticleService {
  async getArticles(viewerId?: number) {
    const user = await this.getViewer(viewerId);
    return articleRepository.findAll(user?.role.name, user?.id);
  }

  async getArticleById(id: string, viewerId?: number) {
    const user = await this.getViewer(viewerId);
    return articleRepository.findById(id, user?.role.name, user?.id);
  }

  async createArticle(editorId: number, payload: ArticleEditorPayload) {
    await this.assertEditor(editorId);
    return articleRepository.create(editorId, payload);
  }

  async updateArticle(
    userId: number,
    articleId: string,
    payload: ArticleEditorPayload,
  ) {
    const user = await userRepository.findById(userId);

    if (user?.role.name === "editor") {
      return articleRepository.update(articleId, payload);
    }

    if (user?.role.name === "journalist") {
      await this.assertAssignedJournalist(articleId, user.id);
      return articleRepository.updateContent(articleId, {
        paragraphs: payload.paragraphs.map((paragraph) => ({
          text: paragraph.text,
          imagePaths: paragraph.imagePaths,
        })),
      });
    }

    throw new Error("Only editors or assigned journalists can edit articles.");
  }

  async updateArticleContent(
    journalistId: number,
    articleId: string,
    payload: ArticleContentPayload,
  ) {
    const user = await userRepository.findById(journalistId);

    if (user?.role.name !== "journalist") {
      throw new Error("Only journalists can perform this action.");
    }

    await this.assertAssignedJournalist(articleId, journalistId);
    return articleRepository.updateContent(articleId, payload);
  }

  async updateArticleStatus(
    editorId: number,
    articleId: string,
    status: ArticleStatus,
  ) {
    await this.assertEditor(editorId);
    return articleRepository.updateStatus(articleId, status);
  }

  async deleteArticle(editorId: number, articleId: string) {
    await this.assertEditor(editorId);
    return articleRepository.delete(articleId);
  }

  private async assertEditor(userId: number) {
    const user = await userRepository.findById(userId);

    if (user?.role.name !== "editor") {
      throw new Error("Only editors can perform this action.");
    }
  }

  private async getViewer(userId?: number) {
    if (!userId || !Number.isInteger(userId)) {
      return undefined;
    }

    return userRepository.findById(userId);
  }

  private async assertAssignedJournalist(articleId: string, userId: number) {
    const isAssigned = await articleRepository.isJournalistAssigned(
      articleId,
      userId,
    );

    if (!isAssigned) {
      throw new Error("Journalists can only edit assigned articles.");
    }
  }
}

export const articleService = new ArticleService();
