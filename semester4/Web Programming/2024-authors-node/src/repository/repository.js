const pool = require('./config');
const Author = require('../domain/author');
const Document = require('../domain/document');
const Movie = require('../domain/movie');
class MainRepository {
    async findAuthorByName(name, creation) {
        const [rows] = await pool.execute(
            'SELECT * FROM authors WHERE name = ?',
            [name]
        );
        if (rows.length === 0) {
            return null;
        }
        let a = new Author(rows[0])
        if(!a.movieList.includes(creation) && !a.documentList.includes(creation)){
            return null;
        }
        return a;
    }

    async getAuthorCreations(authorId) {
        const [rows] = await pool.execute(
            'SELECT * FROM authors where id = ?',
            [authorId]
        );
        let a = new Author(rows[0]);
      const documentIds = a.documentList
    ? a.documentList.split(',').map(id => id.trim()).filter(id => id.length > 0)
    : [];

const movieIds = a.movieList
    ? a.movieList.split(',').map(id => id.trim()).filter(id => id.length > 0)
    : [];
        const result=[];
        const maxLength = Math.max(documentIds.length, movieIds.length);
        for (let i = 0; i < maxLength; i++) {
            if (i < documentIds.length) {
                const document = await this.getDocumentDetails(documentIds[i]);
                result.push({ type: 'document', item: document });
            }
            if (i < movieIds.length) {
                const movie = await this.getMovieDetails(movieIds[i]);
                result.push({ type: 'movie', item: movie });
            }
        }
        return result;
    }
    async getMovieDetails(movieId) {
        const [rows] = await pool.execute(
            'SELECT * FROM movies WHERE id = ?',
            [movieId]
        );
        let m = new Movie(rows[0]);
        return m;
    }

    async getDocumentDetails(documentId) {
        const [rows] = await pool.execute(
            'SELECT * FROM documents WHERE id = ?',
            [documentId]
        );
        let d = new Document(rows[0]);
        return d;
    }

    async addDocument(document,authorId) {
        const [result] = await pool.execute(
            'INSERT INTO documents (name, contents) VALUES (?, ?)',
            [document.name, document.contents]
        );
        const documentId = result.insertId;
        await this.updateAuthorDocumentList(authorId, documentId);
    }

    async updateAuthorDocumentList(authorId, documentId) {
        const [rows] = await pool.execute(
            'SELECT documentList FROM authors WHERE id = ?',
            [authorId]
        );
        let documentList = rows[0].documentList;
        if (documentList) {
            documentList += `,${documentId}`;
        } else {
            documentList = `${documentId}`;
        }
        await pool.execute(
            'UPDATE authors SET documentList = ? WHERE id = ?',
            [documentList, authorId]
        );
    }

    async largestNumberOfAuthors() {
        const [rows] = await pool.execute('SELECT id FROM documents');
        const documentAuthorCount = {};
        for (const row of rows) {
            const documentId = row.id;
            const [authorRows] = await pool.execute(
                'SELECT id FROM authors WHERE FIND_IN_SET(?, documentList)',
                [documentId]
            );
            documentAuthorCount[documentId] = authorRows.length;
        }

        const counts = Object.values(documentAuthorCount);
        if (counts.length === 0) {
            return { documents: [], maxAuthors: 0 };
        }
        const maxAuthors = Math.max(...counts);

        const documentsWithMaxAuthors = Object.keys(documentAuthorCount).filter(
            (id) => documentAuthorCount[id] === maxAuthors
        );
        const result = [];
        for (const id of documentsWithMaxAuthors) {
            const document = await this.getDocumentDetails(id);
            result.push({
                document,
                authorCount: maxAuthors
            });
        }
        return { documents: result, maxAuthors };
    }

  async deleteMovie(movieId, authorId) {
    const [rows] = await pool.execute(
        'SELECT movieList FROM authors WHERE id = ?',
        [authorId]
    );

    let movieList = rows[0].movieList;
    const movieIdString = String(movieId);

    const movieIds = movieList
        .split(',')
        .map(id => id.trim())
        .filter(id => id.length > 0);

    if (!movieIds.includes(movieIdString)) {
        return false;
    }

    const updatedMovieIds = movieIds.filter(id => id !== movieIdString);
    const updatedMovieList = updatedMovieIds.join(',');

    await pool.execute(
        'UPDATE authors SET movieList = ? WHERE id = ?',
        [updatedMovieList, authorId]
    );

    await pool.execute(
        'DELETE FROM movies WHERE id = ?',
        [movieId]
    );

    return true;
}

}

module.exports = MainRepository;
