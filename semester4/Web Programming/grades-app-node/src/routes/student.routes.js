const { Router } = require('express');
const StudentController = require('../controllers/StudentController');
const { requireAuth } = require('../middleware/auth.middleware');

const router = Router();
const controller = new StudentController();

router.use(requireAuth('student'));

router.get('/get-grades', controller.getGrades);

module.exports = router;
