// flippity.ts - flippitydigits

              
// declare var Date;

var Flippity;
(function (Flippity) {
    var last_n         = -1;
    var flip         ;
    var game_start      ;
    var n_remaining = 15;
    var letters = 'abcdefghijklmnopqrstuvwxyz';

    function handlersOff() {
        $('body').off();
        $('.forward').off();
        $('.backward').off();
    }

    function decisionMode() {
        handlersOff();
        $('body').keypress(decisionHandler);
        $('button').removeClass('disabled');
        $('.forward').click(function (e) {
            e.charCode = 'f'.charCodeAt(0);
            return decisionHandler(e);
        });
        $('.backward').click(function (e) {
            e.charCode = 'b'.charCodeAt(0);
            return decisionHandler(e);
        });
        $('button').removeClass('disabled');
    }

    function advanceMode() {
        handlersOff();
        $('button').removeClass('active');
        $('button').addClass('disabled');
        $('body').keypress(nextHandler);
    }

    function loadAudio()       {
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

    function ok_digit(n        )          {
        return (n !== 8 && n !== 0 && n !== last_n);
    }
    function randn(low        , high        )         {
        var spread         = high - low;

        return Math.floor(Math.random() * (spread+1)) + low;
    }
    Flippity.randn = randn;

    function nextOne()         {
        var s, sound;

        if (randn(1, 2) === 1) {
            return nextDigit() + "";
        }
        s = letters[randn(0, letters.length-1)];
        sound = $("#sound-" + s)[0];
        if (!sound) {
          throw "no sound";
        }
        sound.load();
        sound.play();
        if (randn(1, 2) === 2) {
            s = s.toUpperCase();
        }
        return s;
    }
    function nextDigit()         {
        var n         = randn(0, 9);

        while (true) {
            if (ok_digit(n))
                break;
            n = randn(1, 9);
        }
        last_n = n;
        return n;
    }
    function resp(correct         )       {
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
        advanceMode();
    }
    function changePrompt()       {
        var $cont = $('.flip-container');
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
    function nextHandler(e)       {
        console.log(['in nextHandler', e]);
        $('body').focus();
        if (e.charCode == 'n'.charCodeAt(0)) {
            changePrompt();
            decisionMode();
        }
        return false;
    }
    function decisionHandler(e)       {
        console.log(['in decisionHandler', e]);
        if (e.charCode == 'f'.charCodeAt(0)) {
            resp(!flip);
        } else if (e.charCode === 'b'.charCodeAt(0)) {
            resp(flip);
        } else if (e.charCode === 'h'.charCodeAt(0)) {
            $('#hint').show();
        }
        if (n_remaining === 0) {
            var now = new Date();
            var elapsed = now.getTime() - game_start.getTime();
            var txt = '<p>You took ';
            txt += (elapsed / 1000.0).toString();
            txt += ' seconds to win!</p>';
            $('.outcome').html(txt);
            handlersOff();
        }
    }
    function start()       {
        game_start = new Date();
        changePrompt();
        $('#n_remaining').html(n_remaining);
        decisionMode();
    }
    Flippity.start = start;
})(Flippity || (Flippity = {}));
