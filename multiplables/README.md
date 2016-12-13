# Multiplables: Multiplication Tables Drills

## Theory

This program starts out more likely to give you pairs of factors that
have higher values, because usually those are the ones that kids find
harder to memorize.  But you can set the highest factor the program
will use to something your kid is ready for.  (See "Playing" below.)

When the player responds correctly before a certain number of seconds
has elapsed, a nice sound plays, and that factor pair (in both
directions) is removed from the game play.

Responding correctly but slowly allows the factor pair to reappear at
a random later time.

Responding incorrectly causes the factor pair to appear a bit more
frequently.

## Building

Requires boost library, SFML library, and cmake.  What a mess for the
poor user trying to build this!  Sorry.

Maybe this will work:

* Install your favorite SFML library
* Install your favorite boost library
* Edit CMakeLists.txt to update the include directories
* Edit CMakeLists.txt to update the library directories
* Run `cmake .` (Note the space and dot after cmake.)
* Run `make`

## Playing

Run multiplables like this:

    ./multiplables

... or by specifying your time criterion and maximum factor value,
overriding the defaults.  The program will "crash" if you don't
provide a value after these options.  Please fix that and send a pull
request.  `:)`

    ./multiplables --help
    ./multiplables --max 7 --seconds 4

The player is presented with a problem like `0 x 1`, types in the
result and hits enter.  The program provides feedback, including the
number of factor pairs that remain to be defeated by answering
quickly.  The goal is to have zero "remaining" factor pairs.