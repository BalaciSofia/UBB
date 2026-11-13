function showMessage(message) {
    document.getElementById('message').textContent = message;
}

async function sendForm(url, body) {
    const response = await fetch(url, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        },
        body
    });
    const message = await response.json();
    showMessage(message);
    await loadClasses();
    await loadUserBookings();
}

async function bookClass(event, classId) {
    event.preventDefault();
    await sendForm('/add-booking', `classId=${encodeURIComponent(classId)}`);
}

async function cancelBooking(event, bookingId, classId) {
    event.preventDefault();
    await sendForm(
        '/cancel-booking',
        `bookingId=${encodeURIComponent(bookingId)}&classId=${encodeURIComponent(classId)}`
    );
}

async function loadClasses() {
    const response = await fetch('/get-upcomming-classes');
    const data = await response.json();
    const tbody = document.getElementById('upcomming-classes');
    tbody.innerHTML = '';
    let i=0;
    data.classes.forEach(entry => {
                const tr = document.createElement('tr');
                 tr.innerHTML = `
                        <td>${entry.id}</td>
                        <td>${entry.className}</td>
                        <td>${entry.instructorName}</td>
                        <td>${entry.classDate}</td>
                        <td>${entry.maxCapacity}</td>
                        <td>${data.available[i]}</td>
                        <td><form onsubmit="bookClass(event, ${entry.id})">
                        <input type="submit" value="Book">
                        </form></td>
                    `;
                
                tbody.appendChild(tr);
                i++;
            });
}
loadClasses();


async function loadUserBookings() {
    const response = await fetch('/get-user-bookings');
    const data = await response.json();
    const tbody = document.getElementById('user-bookings');
    tbody.innerHTML = '';
    data.forEach(entry => {
                const tr = document.createElement('tr');
                 tr.innerHTML = `
                        <td>${entry.bookingId}</td>
                        <td>${entry.className}</td>
                        <td>${entry.classDate}</td>
                        <td>${entry.bookedAt}</td>
                        <td>${entry.cancelled}</td>
                        <td><form onsubmit="cancelBooking(event, ${entry.bookingId}, ${entry.classId})">
                        <input type="submit" value="Cancel">
                        </form></td>
                    `;
                
                tbody.appendChild(tr);
            });
}
loadUserBookings();

