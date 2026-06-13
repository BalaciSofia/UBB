import { userRepository } from "@/src/repositories/userRepository";

class UserService {
  getJournalists() {
    return userRepository.findByRole("journalist");
  }
}

export const userService = new UserService();
