import { pool } from "@/src/lib/db";
import { ensureDatabaseReady } from "@/src/lib/databaseSetup";
import type { RoleName } from "@/src/domain/role";
import type { AuthUser } from "@/src/domain/user";

type UserRow = {
  id: number;
  username: string;
  role_id: number;
  role_name: RoleName;
  role_color: "red" | "blue" | "yellow" | "green";
};

function mapUser(row: UserRow): AuthUser {
  return {
    id: row.id,
    username: row.username,
    role: {
      id: row.role_id,
      name: row.role_name,
      color: row.role_color,
    },
  };
}

class UserRepository {
  async findByCredentials(
    username: string,
    password: string,
  ): Promise<AuthUser | undefined> {
    await ensureDatabaseReady();

    const result = await pool.query<UserRow>(
      `SELECT users.id, users.username, roles.id AS role_id,
        roles.name AS role_name, roles.color AS role_color
       FROM users
       JOIN roles ON roles.id = users.role_id
       WHERE users.username = $1 AND users.password = $2`,
      [username, password],
    );

    return result.rows[0] ? mapUser(result.rows[0]) : undefined;
  }

  async create(
    username: string,
    password: string,
    roleName: Exclude<RoleName, "admin">,
  ): Promise<AuthUser> {
    await ensureDatabaseReady();

    const result = await pool.query<UserRow>(
      `INSERT INTO users (username, password, role_id)
       SELECT $1, $2, id
       FROM roles
       WHERE name = $3
       RETURNING
        id,
        username,
        role_id,
        (SELECT name FROM roles WHERE id = role_id) AS role_name,
        (SELECT color FROM roles WHERE id = role_id) AS role_color`,
      [username, password, roleName],
    );

    return mapUser(result.rows[0]);
  }
}

export const userRepository = new UserRepository();
