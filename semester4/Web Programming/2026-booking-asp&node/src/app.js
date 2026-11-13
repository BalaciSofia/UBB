const express = require('express');
const session = require('express-session');
const path = require('path');
const AuthController = require('./controller/authController');
const HomeController =require('./controller/homeController')

const app = express();
const authController = new AuthController();
const homeController = new HomeController();

function requireLogin(req, res, next) {
    if (!req.session.user) {
        return res.status(401).json('Not logged in');
    }
    next();
}

function requireLoginPage(req, res, next) {
    if (!req.session.user) {
        return res.redirect('/login.html');
    }
    next();
}

app.use(express.urlencoded({ extended: true }));
app.use(express.json());

app.use(session({
    secret: 'secret',
    resave: false,
    saveUninitialized: false
}));

app.get('/home.html', requireLoginPage, (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'home.html'));
});

app.use(express.static(path.join(__dirname, 'public')));

app.post('/login', authController.login);
app.get('/get-upcomming-classes', homeController.getClasses);
app.post('/add-booking', requireLogin, homeController.bookClass);
app.get('/get-user-bookings', requireLogin, homeController.getUserBookings);
app.post('/cancel-booking', requireLogin, homeController.cancelBooking);

app.get('/', (req, res) => {
    res.redirect('/login.html');
});
module.exports = app;
