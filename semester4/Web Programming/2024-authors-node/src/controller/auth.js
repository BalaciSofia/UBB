
const MainRepository = require('../repository/repository');
class AuthController {
    constructor(){
        this.repository = new MainRepository();
        this.login = this.login.bind(this);
    }

    async login(req, res) {
        const { name, creation } = req.body;
        const author = await this.repository.findAuthorByName(name, creation);
        if (!author) {
            return res.status(401).json({ message: 'Invalid name or creation' });
        }
        req.session.author = author;
        res.redirect('/home.html');    }
}

module.exports = AuthController;