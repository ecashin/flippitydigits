// flippity.ts - flippitydigits

declare var $;

module Flippity {
    var last_n: number = -1;
    var flip: boolean;

    function ok_digit(n: number): boolean {
	return (n !== 8 && n !== 0 && n !== last_n);
    }
    export function randn(low: number, high: number): number {
	var spread: number = high - low;

	return Math.floor(Math.random() * (spread+1)) + low;
    }
    function next_digit(): number {
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
	    // http://soundbible.com/1815-A-Tone.html
	    // Title: A Tone
	    // About: A single note to replace your default windows beep. nice calm and enchanting.
	    // Uploaded: 05.08.11 | License: Public Domain | Recorded by His Self
	    right.load();
	    right.play();
	} else {
	    // http://soundbible.com/1127-Computer-Error.html
	    // Title: Computer Error
	    // About: Cool computer error sound effect that you can use to replace you operating system error sound or to note an error.
	    // Uploaded: 10.25.09 | License: Attribution 3.0 | Recorded by Mike Koenig
	    wrong.load();
	    wrong.play();
	}
    }
    function changeDigit(): void {
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
	$text.html(next_digit());
    }
    function spaceHandler(e): void {
	if (e.charCode == 32) {
	    changeDigit();
	    $('body').off();
	    $('body').keypress(decisionHandler);
	}
    }
    function decisionHandler(e): void {
	if (e.charCode == 102) {
	    resp(!flip);
	    $('body').off();
	    $('body').keypress(spaceHandler);
	} else if (e.charCode === 98) {
	    resp(flip);
	    $('body').off();
	    $('body').keypress(spaceHandler);
	} else if (e.charCode === 104) {
	    $('#hint').show();
	}
    }
    export function start(): void {
	changeDigit();
	$('body').keypress(decisionHandler);
    }
}