import { NextResponse } from "next/server";
import { articleService } from "@/src/services/articleService";
import { validateArticlePayload } from "@/src/validation/articleValidation";

export const dynamic = "force-dynamic";

export async function GET(request: Request) {
  const viewerId = Number(request.headers.get("x-user-id"));
  return NextResponse.json(
    await articleService.getArticles(Number.isInteger(viewerId) ? viewerId : undefined),
  );
}

export async function POST(request: Request) {
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
    const article = await articleService.createArticle(editorId, {
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

    return NextResponse.json(article, { status: 201 });
  } catch (error) {
    const message =
      error instanceof Error ? error.message : "Article could not be created.";
    return NextResponse.json({ message }, { status: 403 });
  }
}
