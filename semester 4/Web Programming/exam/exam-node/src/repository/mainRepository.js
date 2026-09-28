const pool = require('./config');
const User = require('../domain/user');

class MainRepository {
    async authenticate(username, password) {
        const [rows] = await pool.execute(
            'SELECT * FROM users WHERE username = ?',
            [username]
        );
        if (rows.length === 0) {
            return null;
        }
        let a = new User(rows[0])
        if(a.password !== password){
            return null;
        }
        return a;
    }
}

module.exports = MainRepository;