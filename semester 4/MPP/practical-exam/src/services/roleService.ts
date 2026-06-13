import { roleRepository } from "@/src/repositories/roleRepository";

class RoleService {
  getRegisterableRoles() {
    return roleRepository.findRegisterable();
  }
}

export const roleService = new RoleService();
