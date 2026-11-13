class User {
  constructor({ userId, username, password, role, groupCode, name }) {
    this.userId = userId;
    this.username = username;
    this.password = password;
    this.role = role;
    this.groupCode = groupCode;
    this.name = name;
  }
}

module.exports = User;
