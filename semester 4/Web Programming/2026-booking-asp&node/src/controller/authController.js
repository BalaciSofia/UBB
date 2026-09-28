const MainRepository = require('../repository/mainRepository');

class AuthController {
    constructor(){
        this.repository = new MainRepository();
        this.login = this.login.bind(this);
    }

    async login(req, res) {
        const { username} = req.body;
        const user = await this.repository.authenticate(username);
        if (!user) {
            return res.redirect('/login.html?error=1');
        }
        req.session.user = user;
        res.redirect('/home.html');   
    }
}

module.exports = AuthController;