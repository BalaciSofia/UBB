const express = require('express');
const session = require('express-session');
const cors = require('cors');

const authRoutes = require('./routes/auth.routes');
const professorRoutes = require('./routes/professor.routes');
const studentRoutes = require('./routes/student.routes');

const app = express();

app.use(cors({
  origin: ['http://localhost:4200'],
  credentials: true,
}));

app.use(express.json());
app.use(express.urlencoded({ extended: true }));

app.use(session({
  secret: 'grades-app-node-secret',
  resave: false,
  saveUninitialized: false,
  cookie: {
    httpOnly: true,
    sameSite: 'lax',
    secure: false,
  },
}));

app.use('/auth', authRoutes);
app.use('/professor', professorRoutes);
app.use('/student', studentRoutes);

module.exports = app;
