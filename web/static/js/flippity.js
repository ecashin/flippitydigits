// flippity.ts - flippitydigits
var Flippity;
(function (Flippity) {
    var last_n = -1;
    var flip;
    function ok_digit(n) {
        return (n !== 8 && n !== 0 && n !== last_n);
    }
    function randn(low, high) {
        var spread = high - low;
        return Math.floor(Math.random() * (spread + 1)) + low;
    }
    Flippity.randn = randn;
    function next_digit() {
        var n = randn(0, 9);
        while (true) {
            if (ok_digit(n))
                break;
            n = randn(1, 9);
        }
        last_n = n;
        return n;
    }
    function resp(correct) {
        var right = $('#correct_sound')[0];
        var wrong = $('#incorrect_sound')[0];
        if (correct) {
            // http://soundbible.com/1815-A-Tone.html
            // Title: A Tone
            // About: A single note to replace your default windows beep. nice calm and enchanting.
            // Uploaded: 05.08.11 | License: Public Domain | Recorded by His Self
            right.load();
            right.play();
        }
        else {
            // http://soundbible.com/1127-Computer-Error.html
            // Title: Computer Error
            // About: Cool computer error sound effect that you can use to replace you operating system error sound or to note an error.
            // Uploaded: 10.25.09 | License: Attribution 3.0 | Recorded by Mike Koenig
            wrong.load();
            wrong.play();
        }
    }
    function changeDigit() {
        var $cont = $('.container');
        var $div = $cont.find('div');
        var $text = $div.find("figure");
        flip = randn(0, 1) == 1;
        $('#hint').hide();
        if (flip) {
            $text.addClass('flipped');
        }
        else {
            $text.removeClass('flipped');
        }
        $text.html(next_digit());
    }
    function spaceHandler(e) {
        if (e.charCode == 32) {
            changeDigit();
            $('body').off();
            $('body').keypress(decisionHandler);
        }
    }
    function decisionHandler(e) {
        if (e.charCode == 102) {
            resp(!flip);
            $('body').off();
            $('body').keypress(spaceHandler);
        }
        else if (e.charCode === 98) {
            resp(flip);
            $('body').off();
            $('body').keypress(spaceHandler);
        }
        else if (e.charCode === 104) {
            $('#hint').show();
        }
        console.log(e);
    }
    function start() {
        changeDigit();
        $('body').keypress(decisionHandler);
    }
    Flippity.start = start;
})(Flippity || (Flippity = {}));