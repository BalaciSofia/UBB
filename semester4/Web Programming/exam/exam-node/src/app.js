const express = require('express');
const session = require('express-session');
const path = require('path');
const AuthController = require('./controller/authController');

const app = express();
const authController = new AuthController();


app.use(express.urlencoded({ extended: true }));
app.use(express.json());

app.use(session({
    secret: 'secret',
    resave: false,
    saveUninitialized: false
}));

app.use(express.static(path.join(__dirname, 'public')));

app.post('/login', authController.login);

app.get('/', (req, res) => {
    res.redirect('/login.html');
});
module.exports = app;