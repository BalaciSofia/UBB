import { NextResponse } from "next/server";
import { articleService } from "@/src/services/articleService";
import {
  validateArticlePayload,
  validateStatusPayload,
} from "@/src/validation/articleValidation";
import type { ArticleStatus } from "@/src/domain/article";

export const dynamic = "force-dynamic";

type RouteContext = {
  params: {
    id: string;
  };
};

export async function GET(request: Request, { params }: RouteContext) {
  const viewerId = Number(request.headers.get("x-user-id"));
  const article = await articleService.getArticleById(
    params.id,
    Number.isInteger(viewerId) ? viewerId : undefined,
  );

  if (!article) {
    return NextResponse.json({ message: "Article not found" }, { status: 404 });
  }

  return NextResponse.json(article);
}

export async function PUT(request: Request, { params }: RouteContext) {
  const editorId = Number(request.headers.get("x-user-id"));
  const payload = await request.json();
  const errors = validateArticlePayload(payload);

  if (!Number.isInteger(editorId) || editorId <= 0) {
    errors.push("Editor user id is required.");
  }

  if (errors.length > 0) {
    return NextResponse.json({ errors }, { status: 400 });
  }

  try {
    const article = await articleService.updateArticle(editorId, params.id, {
      title: payload.title.trim(),
      journalistIds: payload.journalistIds.map(Number),
      paragraphs: payload.paragraphs.map(
        (paragraph: {
          text: string;
          imagePaths: string[];
          comments: string[];
        }) => ({
          text: paragraph.text.trim(),
          imagePaths: paragraph.imagePaths.map((path) => path.trim()),
          comments: paragraph.comments.map((comment) => comment.trim()),
        }),
      ),
    });

    if (!article) {
      return NextResponse.json({ message: "Article not found" }, { status: 404 });
    }

    return NextResponse.json(article);
  } catch (error) {
    const message =
      error instanceof Error ? error.message : "Article could not be updated.";
    return NextResponse.json({ message }, { status: 403 });
  }
}

export async function PATCH(request: Request, { params }: RouteContext) {
  const editorId = Number(request.headers.get("x-user-id"));
  const payload = await request.json();
  const errors = validateStatusPayload(payload);

  if (!Number.isInteger(editorId) || editorId <= 0) {
    errors.push("Editor user id is required.");
  }

  if (errors.length > 0) {
    return NextResponse.json({ errors }, { status: 400 });
  }

  try {
    const article = await articleService.updateArticleStatus(
      editorId,
      params.id,
      payload.status as ArticleStatus,
    );

    if (!article) {
      return NextResponse.json({ message: "Article not found" }, { status: 404 });
    }

    return NextResponse.json(article);
  } catch (error) {
    const message =
      error instanceof Error
        ? error.message
        : "Article status could not be updated.";
    return NextResponse.json({ message }, { status: 403 });
  }
}

export async function DELETE(request: Request, { params }: RouteContext) {
  const editorId = Number(request.headers.get("x-user-id"));

  if (!Number.isInteger(editorId) || editorId <= 0) {
    return NextResponse.json(
      { message: "Editor user id is required." },
      { status: 400 },
    );
  }

  try {
    const wasDeleted = await articleService.deleteArticle(editorId, params.id);

    if (!wasDeleted) {
      return NextResponse.json({ message: "Article not found" }, { status: 404 });
    }

    return NextResponse.json({ message: "Article deleted." });
  } catch (error) {
    const message =
      error instanceof Error ? error.message : "Article could not be deleted.";
    return NextResponse.json({ message }, { status: 403 });
  }
}
