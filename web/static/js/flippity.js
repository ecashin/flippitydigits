// flippity.ts - flippitydigits

              
// declare var Date;

var Flippity;
(function (Flippity) {
    var lastOne = '.';
    var flip         ;
    var game_start      ;
    var n_remaining = 15;
    var storage;                // set in Flippity.init
    var defaultLetters = 'BCDEFGJKLNPQRSZabcdefghjkmnpqrstyz';
    var defaultDigits = '12345679';
    var onWrong;

    function ensureLoaded(snd) {
        if (snd.readyState !== snd.HAVE_ENOUGH_DATA) {
          snd.load();
        }
    }
    function playFromStart(snd) {
        ensureLoaded(snd);
        snd.pause();
        snd.currentTime = 0;
        snd.play();
    }

    function handlersOff() {
        $('body').off();
        $('.forward').off();
        $('.backward').off();
        $('.next').off();
    }

    function decisionMode() {
        handlersOff();
        $('body').keypress(decisionHandler);
        $('button.next').addClass('disabled');
        $('button.next').removeClass('active');
        $('.forward').click(function (e) {
            e.charCode = 'f'.charCodeAt(0);
            return decisionHandler(e);
        });
        $('.backward').click(function (e) {
            e.charCode = 'b'.charCodeAt(0);
            return decisionHandler(e);
        });
        $('button.decision').removeClass('disabled');
    }

    function advanceMode() {
        handlersOff();
        $('button.decision').removeClass('active');
        $('button.decision').addClass('disabled');
        $('button.next').click(function (e) {
            e.charCode = 'n'.charCodeAt(0);
            return nextHandler(e);
        });
        $('button.next').removeClass('disabled');
        $('button.next').addClass('active');
        $('body').keypress(nextHandler);
    }

    function loadState()       {
        storage = window.localStorage || {};
        storage.letters = storage.letters || defaultLetters;
        storage.digits = storage.digits || defaultDigits;
    }

    function loadAudio()       {
        var i, $audio, loaded = {}, lc;

        function path(letter) {
            var p = "static/media/original_sounds/";
            p += letter + ".wav";

            return p;
        }

        function element(letter) {
            return '<audio id="sound-' + letter + '">';
        }

        for (i = 0; i < storage.letters.length; i ++) {
            lc = storage.letters[i].toLowerCase();
            if (!loaded[lc]) {
                $audio = $(element(lc)).attr("src", path(lc));
                $audio.attr("preload", "auto").attr("type", "audio/wav");
                $("body").append($audio);
                loaded[lc] = true;
            }
        }
    }
    Flippity.init = function () {
        loadState();
        loadAudio();
        $("#reload").click(function () { location.reload(); });
    };

    function randn(low        , high        )         {
        var spread         = high - low;

        return Math.floor(Math.random() * (spread+1)) + low;
    }
    Flippity.randn = randn;

    function nextOne()         {
        var s, sound;

        if (randn(1, 2) === 1) {
            s = nextDigit();
            onWrong = function () { storage.digits += s + s; };
            return s;
        }
        s = nextLetter();
        sound = $("#sound-" + s.toLowerCase())[0];
        if (!sound) {
          throw "no sound";
        }
        playFromStart(sound);
        onWrong = function () { storage.letters += s + s; };
        return s;
    }
    function nextLetter()         {
        var n         = randn(0, storage.letters.length-1);

        while (true) {
            if (storage.letters[n] !== lastOne) {
                break;
            }
            n = randn(0, storage.letters.length-1);
        }
        lastOne = storage.letters[n];
        return lastOne;
    }

    function nextDigit()         {
        var n         = randn(0, storage.digits.length-1);

        while (true) {
            if (storage.digits[n] !== lastOne) {
                break;
            }
            n = randn(0, storage.digits.length-1);
        }
        lastOne = storage.digits[n];
        return lastOne;
    }
    function resp(correct         )       {
        var right = $('#correct_sound')[0];
        var wrong = $('#incorrect_sound')[0];

        if (correct) {
            playFromStart(right);
            n_remaining -= 1;
        } else {
            onWrong();
            console.log(storage.letters);
            console.log(storage.digits);
            playFromStart(wrong);
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
        $('body').focus();
        if (e.charCode == 'n'.charCodeAt(0)) {
            changePrompt();
            decisionMode();
        }
        return false;
    }
    function decisionHandler(e)       {
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
