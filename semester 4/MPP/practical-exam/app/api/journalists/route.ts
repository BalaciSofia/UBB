import { NextResponse } from "next/server";
import { userService } from "@/src/services/userService";

export const dynamic = "force-dynamic";

export async function GET() {
  return NextResponse.json(await userService.getJournalists());
}
