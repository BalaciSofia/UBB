const loginForm = document.getElementById("login-form");
const loginError = document.getElementById("login-error");

loginForm.addEventListener("submit", submitLogin);

async function submitLogin(event) {
    event.preventDefault();
    const username = loginForm.username.value;
    try{
        const response = await fetch("/exam/backend/auth.php", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify({ username})
        });

        const resp = await response.json();
        
        if (!resp.success) {
            loginError.textContent = resp.message || "Invalid username or password.";
            return;
        }

        sessionStorage.setItem("sessions", JSON.stringify(resp.sessions || []));
        sessionStorage.setItem("muscleGroupScores", JSON.stringify(resp.muscleGroupScores || {}));

        window.location.href = resp.redirect;

    } catch (error) {
        loginError.textContent = "An error occurred during login.";
    }
}
