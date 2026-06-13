import { NextResponse } from "next/server";
import { authService } from "@/src/services/authService";

export const dynamic = "force-dynamic";

export async function POST(request: Request) {
  try {
    const body = await request.json();
    const user = await authService.register(
      body.username,
      body.password,
      body.role,
    );

    return NextResponse.json(user, { status: 201 });
  } catch (error) {
    const message =
      error instanceof Error ? error.message : "Registration failed.";

    return NextResponse.json({ message }, { status: 400 });
  }
}
