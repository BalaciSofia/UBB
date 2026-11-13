const app = require('./app');

const PORT = 5164;

app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
});