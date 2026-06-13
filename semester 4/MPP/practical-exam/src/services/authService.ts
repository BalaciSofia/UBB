import type { RoleName } from "@/src/domain/role";
import { roleRepository } from "@/src/repositories/roleRepository";
import { userRepository } from "@/src/repositories/userRepository";

class AuthService {
  async login(username: string, password: string) {
    if (!username || !password) {
      throw new Error("Username and password are required.");
    }

    return userRepository.findByCredentials(username, password);
  }

  async register(username: string, password: string, roleName: RoleName) {
    if (!username || !password) {
      throw new Error("Username and password are required.");
    }

    if (!(await roleRepository.isRegisterable(roleName))) {
      throw new Error("Selected role is not available for registration.");
    }

    return userRepository.create(
      username,
      password,
      roleName as Exclude<RoleName, "admin">,
    );
  }
}

export const authService = new AuthService();
