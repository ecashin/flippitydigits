// flippity.ts - flippitydigits

declare var $;
// declare var Date;

var Flippity;
(function (Flippity) {
    var last_n: number = -1;
    var flip: boolean;
    var game_start: Date;
    var n_remaining = 15;
    var letters = 'abcdefghijklmnopqrstuvwxyz';

    function loadAudio(): void {
        var i, $audio;

        function path(letter) {
            var p = "static/media/original_sounds/";
            p += letter + ".wav";

            return p;
        }

        function element(letter) {
            return '<audio id="sound-' + letter + '">';
        }

        for (i = 0; i < letters.length; i ++) {
            $audio = $(element(letters[i])).attr("src", path(letters[i]));
            $audio.attr("preload", "auto").attr("type", "audio/wav");
            $("body").append($audio);
        }
    }
    Flippity.init = function () {
        loadAudio();
        $("#reload").click(function () { location.reload(); });
    }

    function ok_digit(n: number): boolean {
        return (n !== 8 && n !== 0 && n !== last_n);
    }
    function randn(low: number, high: number): number {
        var spread: number = high - low;

        return Math.floor(Math.random() * (spread+1)) + low;
    }
    Flippity.randn = randn;

    function nextOne(): string {
        var s, sound;

        if (randn(1, 2) === 1) {
            return nextDigit() + "";
        }
        s = letters[randn(0, letters.length + 1)];
        sound = $("#sound-" + s)[0];
        sound.load();
        sound.play();
        if (randn(1, 2) === 2) {
            s = s.toUpperCase();
        }
        return s;
    }
    function nextDigit(): number {
        var n: number = randn(0, 9);

        while (true) {
            if (ok_digit(n))
                break;
            n = randn(1, 9);
        }
        last_n = n;
        return n;
    }
    function resp(correct: boolean): void {
        var right = $('#correct_sound')[0];
        var wrong = $('#incorrect_sound')[0];

        if (correct) {
            right.load();
            right.play();
            n_remaining -= 1;
        } else {
            wrong.load();
            wrong.play();
            n_remaining += 1;
        }
        $('#n_remaining').html(n_remaining);
        $('body').off();
        $('body').keypress(spaceHandler);
    }
    function changePrompt(): void {
        var $cont = $('.container');
        var $div = $cont.find('div');
        var $text = $div.find("figure");
        flip = randn(0, 1) == 1;

        $('#hint').hide();
        if (flip) {
            $text.addClass('flipped');
        } else {
            $text.removeClass('flipped');
        }
        $text.html(nextOne());
    }
    function spaceHandler(e): void {
        if (e.charCode == 32) {  // space
            changePrompt();
            $('body').off();
            $('body').keypress(decisionHandler);
        }
    }
    function decisionHandler(e): void {
        if (e.charCode == 102) {  // f
            resp(!flip);
        } else if (e.charCode === 98) {  // b
            resp(flip);
        } else if (e.charCode === 104) {  // h
            $('#hint').show();
        }
        if (n_remaining === 0) {
            var now = new Date();
            var elapsed = now.getTime() - game_start.getTime();
            var txt = '<p>You took ';
            txt += (elapsed / 1000.0).toString();
            txt += ' seconds to win!</p>';
            $('.outcome').html(txt);
            $('body').off();
        }
    }
    function start(): void {
        game_start = new Date();
        changePrompt();
        $('#n_remaining').html(n_remaining);
        $('body').keypress(decisionHandler);
    }
    Flippity.start = start;
})(Flippity || (Flippity = {}));
