# Flippity Digits

A very simple game for learning to distinguish numbers that are
forward from those that are backward.  I made this game for a child.
She thought it was fun, and she improved quickly.

## Object of the Game

Your time is printed at the end of the game.  The object is to get the
lowest time you can without hitting escape.

I have noticed that children sometimes instead try to get as many
crying sounds going as possible at the same time, so I suppose that's
an alternative object of the game.  :)

## Dependencies

The dependencies I know about are listed below as Ubuntu install
commands.

    sudo apt-get update &&
    sudo apt-get install g++ make &&
    sudo apt-get install --install-suggests liballegro4{,-d{ev,oc}} &&
    sudo apt-get install --install-suggests cimg-{examples,d{ev,oc}} &&
    sudo apt-get install xemacs21-basesupport  # (for sounds)

## Building

See the flippity.cpp file for dependencies listed as Ubuntu packages.
Your system might have different names for the same software.

Compile with `make` or compile and run with,

    make run

## Play

    SPACE	advance to next trial
    f		respond that the number is "forward"
    b		respond that the number is "backward"
    ESC		quit early
