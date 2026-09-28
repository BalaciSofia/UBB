const images = [
    "pics/cat1.jpg",
    "pics/cat2.jpg",
    "pics/cat3.jpg",
    "pics/cat4.jpg",
    "pics/cat5.jpg"
];

let currentIndex = 0;
let isPlaying = false;
let intervalId = null;

const slideImage = document.getElementById("slideImage");
const playPauseBtn = document.getElementById("playPauseBtn");
const repeatCheckbox = document.getElementById("repeatCheckbox");
const timeSelect = document.getElementById("timeSelect");

function showImage(index) {
    slideImage.src = images[index];
}

function nextImage() {
    if (currentIndex < images.length - 1) {
        currentIndex++;
    } else {
        if (repeatCheckbox.checked) {
            currentIndex = 0;
        } else {
            stopSlideshow();
            return;
        }
    }
    showImage(currentIndex);
}

function startSlideshow() {
    if (isPlaying) return;

    isPlaying = true;
    playPauseBtn.textContent = "Pause";

    intervalId = setInterval(nextImage, parseInt(timeSelect.value));
}

function stopSlideshow() {
    isPlaying = false;
    playPauseBtn.textContent = "Play";
    clearInterval(intervalId);
}

playPauseBtn.addEventListener("click", function () {
    if (isPlaying) {
        stopSlideshow();
    } else {
        startSlideshow();
    }
});

timeSelect.addEventListener("change", function () {
    if (isPlaying) {
        clearInterval(intervalId);
        intervalId = setInterval(nextImage, parseInt(timeSelect.value));
    }
});
