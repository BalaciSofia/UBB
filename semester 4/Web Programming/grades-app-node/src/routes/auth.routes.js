const { Router } = require('express');
const AuthController = require('../controllers/AuthController');

const router = Router();
const controller = new AuthController();

router.post('/login', controller.login);
router.post('/logout', controller.logout);

module.exports = router;
