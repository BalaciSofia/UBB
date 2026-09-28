const AuthService = require('../services/AuthService');

class AuthController {
  constructor() {
    this.authService = new AuthService();
    this.login = this.login.bind(this);
    this.logout = this.logout.bind(this);
  }

  async login(req, res) {
    try {
      const { username, password } = req.body;
      const user = await this.authService.login(username, password);

      req.session.userId = user.userId;
      req.session.role = user.role;

      res.json({
        success: true,
        role: user.role,
        redirect: user.role === 'student' ? '/student' : '/professor',
      });
    } catch (err) {
      res.status(err.status || 400).json({
        success: false,
        message: err.message,
      });
    }
  }

  logout(req, res) {
    req.session.destroy(() => {
      res.json({ success: true, message: 'Logged out' });
    });
  }
}

module.exports = AuthController;
