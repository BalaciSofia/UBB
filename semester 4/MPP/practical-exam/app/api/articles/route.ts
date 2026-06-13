import { NextResponse } from "next/server";
import { articleService } from "@/src/services/articleService";

export async function GET() {
  return NextResponse.json(articleService.getArticles());
}
