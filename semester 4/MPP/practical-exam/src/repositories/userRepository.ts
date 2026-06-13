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
  async findById(id: number): Promise<AuthUser | undefined> {
    await ensureDatabaseReady();

    const result = await pool.query<UserRow>(
      `SELECT users.id, users.username, roles.id AS role_id,
        roles.name AS role_name, roles.color AS role_color
       FROM users
       JOIN roles ON roles.id = users.role_id
       WHERE users.id = $1`,
      [id],
    );

    return result.rows[0] ? mapUser(result.rows[0]) : undefined;
  }

  async findByRole(roleName: RoleName): Promise<AuthUser[]> {
    await ensureDatabaseReady();

    const result = await pool.query<UserRow>(
      `SELECT users.id, users.username, roles.id AS role_id,
        roles.name AS role_name, roles.color AS role_color
       FROM users
       JOIN roles ON roles.id = users.role_id
       WHERE roles.name = $1
       ORDER BY users.username ASC`,
      [roleName],
    );

    return result.rows.map(mapUser);
  }

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

    const result = await pool.query<{ id: number }>(
      `INSERT INTO users (username, password, role_id)
       SELECT $1, $2, id
       FROM roles
       WHERE name = $3
       RETURNING id`,
      [username, password, roleName],
    );

    const user = await this.findById(result.rows[0].id);

    if (!user) {
      throw new Error("Created user could not be loaded.");
    }

    return user;
  }
}

export const userRepository = new UserRepository();
