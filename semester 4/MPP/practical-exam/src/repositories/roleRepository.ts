import { pool } from "@/src/lib/db";
import { ensureDatabaseReady } from "@/src/lib/databaseSetup";
import type { Role, RoleName } from "@/src/domain/role";

class RoleRepository {
  async findRegisterable(): Promise<Role[]> {
    await ensureDatabaseReady();

    const result = await pool.query<Role>(
      "SELECT id, name, color FROM roles WHERE name <> 'admin' ORDER BY name",
    );

    return result.rows;
  }

  async isRegisterable(roleName: string): Promise<boolean> {
    const roles = await this.findRegisterable();
    return roles.some((role) => role.name === roleName);
  }
}

export const roleRepository = new RoleRepository();
