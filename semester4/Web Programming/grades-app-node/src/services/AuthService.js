const UserRepository = require('../repositories/UserRepository');

class AuthService {
  constructor() {
    this.userRepository = new UserRepository();
  }

  async login(username, password) {
    if (!username || !password) {
      const err = new Error('Username and password are required');
      err.status = 400;
      throw err;
    }

    const user = await this.userRepository.findByUsername(username);

    if (!user || user.password !== password) {
      const err = new Error('Invalid login');
      err.status = 401;
      throw err;
    }

    return user;
  }
}

module.exports = AuthService;
