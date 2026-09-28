const { Router } = require('express');
const ProfessorController = require('../controllers/ProfessorController');
const { requireAuth } = require('../middleware/auth.middleware');

const router = Router();
const controller = new ProfessorController();

router.use(requireAuth('professor'));

router.get('/get-context', controller.getContext);
router.get('/get-students', controller.getStudents);
router.post('/save-grade', controller.saveGrade);

module.exports = router;
