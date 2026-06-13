import { NextResponse } from "next/server";
import { authService } from "@/src/services/authService";

export const dynamic = "force-dynamic";

export async function POST(request: Request) {
  const body = await request.json();
  const user = await authService.login(body.username, body.password);

  if (!user) {
    return NextResponse.json(
      { message: "Invalid username or password." },
      { status: 401 },
    );
  }

  return NextResponse.json(user);
}
