import { NextResponse } from "next/server";
import { articleService } from "@/src/services/articleService";

export const dynamic = "force-dynamic";

export async function GET() {
  return NextResponse.json(await articleService.getArticles());
}
