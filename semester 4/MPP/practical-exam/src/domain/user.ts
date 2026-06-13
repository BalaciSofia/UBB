import type { Role } from "@/src/domain/role";

export type User = {
  id: number;
  username: string;
  role: Role;
};

export type Journalist = User & {
  role: Role & { name: "journalist" };
};

export type Editor = User & {
  role: Role & { name: "editor" };
};

export type AuthUser = User | Journalist | Editor;
