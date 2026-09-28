let score = 0;
$(document).ready(function () {
    let game_width = $(".game-area").width();
    let game_height = $(".game-area").height();
    addAnotherImage(game_height, game_width);
    scheduleNextImage(game_height, game_width);
});

function addAnotherImage(h, w) {
    let idx = Math.floor(Math.random() * 5) + 1;
    spawnImage(h, w, idx);
}

function scheduleNextImage(h, w) {
    let delay = 500 + Math.random() * 1000;

    setTimeout(function () {
        if (score < 10) {
            addAnotherImage(h, w);
            scheduleNextImage(h, w);
        }
    }, delay);
}

function spawnImage(h, w, idx) {
    if (idx==3) {time = 3000;}
    else {time = 500 + Math.random() * 1000;}
    let x = Math.random() * (w - 100);
    let y = Math.random() * (h - 100);
    let img = $("<img>");
    img.attr("src", "pics/cat" + idx + ".jpg");
    img.css({
        "left": x+"px",
        "top": y+"px"
    });

    $(".game-area").append(img);
    let t = setTimeout(function () {
        img.remove();
    }, time);

    img.click(function () {
        if(idx == 3) score=score+3;
        else score = score + 1;
        img.remove();
        clearTimeout(t);
        if (score >= 10) {
            $(".score").text("You win! Score: " + score);
        } else {
            $(".score").text("score: " + score);
        }
    });
}
