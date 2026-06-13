import { NextResponse } from "next/server";
import { roleService } from "@/src/services/roleService";

export const dynamic = "force-dynamic";

export async function GET() {
  return NextResponse.json(await roleService.getRegisterableRoles());
}
