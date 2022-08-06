# Flippity (formerly "Flippitydigits")

A very simple game for learning to distinguish numbers and letters
that are forward from those that are backward.  I made this game for a
child.  She thought it was fun, and she improved quickly.

The C++ version of the game can only be run in the source directory
(or another where the original_sounds directory appears).

## Two Implementations

This distribution includes a web-based version of the game in web/ and
a fun but somewhat delicate C++ implementation---delicate because of
dependencies.

You can find a demo of the web version here:

  https://ecashin.github.io/flippitydigits/

... but please note that the CSS for text transforms don't always work
correctly on mobile devices.  On Android Chrome and Android FireFox,
the reversed digits and letters appear as invisible.

## Object of the Game

Your time is printed at the end of the game.  The object is to get the
lowest time you can without hitting escape.

I have noticed that in the C++ version, children sometimes instead try
to get as many crying sounds going as possible at the same time, so I
suppose that's an alternative object of the game.  :)

## Dependencies

### Web Flippity Dependencies

The web version has no external depedencies.  It comes with transpiled
CSS and JavaScript, built from the Stylus and TypeScript sources
respectively.

### C++ Flippity Dependencies

The dependencies I know about are listed below as Ubuntu install
commands.

    sudo apt-get update &&
    sudo apt-get install g++ make &&
    sudo apt-get install --install-suggests liballegro4{,-d{ev,oc}} &&
    sudo apt-get install --install-suggests cimg-{examples,d{ev,oc}} &&
    sudo apt-get install xemacs21-basesupport  # (for sounds)

## Building

### Building and Running Web Flippity

You can copy the files in web/ into a place that a web server will
make available, but if you want to change things, you can re-build the
CSS and JavaScript and run the development HTTP server with,

    cd web
    make srv

Then you can access the game at http://127.0.0.1:8000/

### Building and Running C++ Flippity

See the flippity.cpp file for dependencies listed as Ubuntu packages.
Your system might have different names for the same software.

Compile with `make` or compile and run with,

    make run

## Play

### Universal keys

    SPACE       advance to next trial
    f           respond that the letter/digit is "forward"
    b           respond that the letter/digit is "backward"
    h           request a "help" display of all digits

### C++ version keys

    r           repeat the sound of the letter (letters only)
    ESC         quit early

## Sound Attribution for Web Version

### The "Correct" Sound

Title: A Tone

http://soundbible.com/1815-A-Tone.html

About: A single note to replace your default windows beep. nice calm and enchanting.

Uploaded: 05.08.11 | License: Public Domain | Recorded by His Self

### The "Incorrect" Sound

http://soundbible.com/1127-Computer-Error.html

Title: Computer Error

About: Cool computer error sound effect that you can use to replace you operating system error sound or to note an error.

Uploaded: 10.25.09 | License: Attribution 3.0 | Recorded by Mike Koenig
