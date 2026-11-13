const app = require('./app');

const PORT = process.env.PORT || 5164;

app.listen(PORT, () => {
  console.log(`Grades API server running at http://localhost:${PORT}`);
});
