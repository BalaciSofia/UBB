const express = require('express');
const session = require('express-session');
const path = require('path');
const AuthController = require('./controller/auth');
const HomeController = require('./controller/home');

const app = express();
const authController = new AuthController();
const homeController = new HomeController();

app.use(express.urlencoded({ extended: true }));
app.use(express.json());

app.use(session({
    secret: 'authors-secret',
    resave: false,
    saveUninitialized: false
}));

app.use(express.static(path.join(__dirname, 'public')));

app.post('/login', authController.login);
app.get('/my-creations', homeController.getMyCreations);
app.post('/add-document', homeController.addDocument);
app.get('/largest-number-of-authors', homeController.largestNumberOfAuthors);
app.post('/delete-movie', homeController.deleteMovie);

app.get('/', (req, res) => {
    res.redirect('/login.html');
});
module.exports = app;