export type RoleName = "admin" | "journalist" | "editor" | "user";

export type RoleColor = "red" | "blue" | "yellow" | "green";

export type Role = {
  id: number;
  name: RoleName;
  color: RoleColor;
};
