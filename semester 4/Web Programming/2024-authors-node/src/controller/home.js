
const MainRepository = require('../repository/repository');
const Document = require('../domain/document');

class HomeController {
    constructor(){
         this.repository = new MainRepository();
        this.getMyCreations = this.getMyCreations.bind(this);
        this.addDocument = this.addDocument.bind(this);
        this.largestNumberOfAuthors = this.largestNumberOfAuthors.bind(this);
        this.deleteMovie = this.deleteMovie.bind(this);
    }

    async getMyCreations(req, res) {
        const authorId = req.session.author.id;
        const creations = await this.repository.getAuthorCreations(authorId);
        return res.json({ creations });
    }

    async addDocument(req, res) {
        const { name, contents } = req.body;
        const document = new Document({ name, contents });
        const authorId = req.session.author.id;
        await this.repository.addDocument(document, authorId);
        return res.redirect('/home.html');    }

    async largestNumberOfAuthors(req, res) {
        const { documents, maxAuthors } = await this.repository.largestNumberOfAuthors();
        return res.json({ documents, maxAuthors });
    }

    async deleteMovie(req, res) {
        const { movieId } = req.body;
        const authorId = req.session.author.id;
        const result = await this.repository.deleteMovie(movieId, authorId);
        if (!result) {
            return res.status(404).json({ message: 'Movie not found or not owned by the author' });
        }
        return res.redirect('/home.html');
    }
}

module.exports = HomeController;