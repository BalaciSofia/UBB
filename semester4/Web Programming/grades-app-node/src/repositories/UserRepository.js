const pool = require('../config/database');
const User = require('../domain/User');

class UserRepository {
  async findByUsername(username) {
    const [rows] = await pool.execute(
      'SELECT userId, username, password, role, groupCode, name FROM users WHERE username = ?',
      [username]
    );
    if (rows.length === 0) return null;
    return new User(rows[0]);
  }

  async findById(userId) {
    const [rows] = await pool.execute(
      'SELECT userId, username, password, role, groupCode, name FROM users WHERE userId = ?',
      [userId]
    );
    if (rows.length === 0) return null;
    return new User(rows[0]);
  }

  async findStudentsByGroup(groupCode, limit, offset) {
    const [rows] = await pool.execute(
      'SELECT userId, name FROM users WHERE role = "student" AND groupCode = ? LIMIT ? OFFSET ?',
      [groupCode, limit, offset]
    );
    return rows;
  }

  async countStudentsByGroup(groupCode) {
    const [rows] = await pool.execute(
      'SELECT COUNT(*) AS total FROM users WHERE role = "student" AND groupCode = ?',
      [groupCode]
    );
    return Number(rows[0].total);
  }

  async findDistinctGroups() {
    const [rows] = await pool.execute(
      'SELECT DISTINCT groupCode FROM users WHERE role = "student" AND groupCode IS NOT NULL AND groupCode <> "" ORDER BY groupCode'
    );
    return rows.map(r => r.groupCode);
  }
}

module.exports = UserRepository;
