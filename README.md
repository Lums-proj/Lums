<div align="center">
<img src="misc/images/logo.png" alt="Lums logo">
<h1>Lums</h1>
</div>

**Lums** is a powerful, easy to use, C++ game library.
The basic idea behind Lums is to provide a framework-based solution, where the developper
can freely interfere with the execution flow.

Lums provides extra facilities, like unit-free angles, gamestate stack, and much more. Thanks to C++11, these
facilities can now be used with ease, using user-defined litterals.

## Introduction

Lums is based around a core. The core is the center of your game, where everything interract and fuse to give
the player a wonderful experience. When we were creating Lums, we focused on keeping the core as simple and
lightweight as possible. If that doesn't fit your needs, you can always add functionalities to it, just by
subclassing it.

The execution flow of your game is granted to the core. You feed it with a starting state, like a main menu, and run
it. That's all! Your gamestate hooks will get called in the right order, at the right moment. Just relax and let
the magic happen.

## Getting started

Lums is bundled with some tools. To create a working Lums project, the lums command line tool can be used.

    lums new MyAwesomeGame
    cd MyAwesomeGame
    lums run

## Documentation

An offline version of the documentation is available in the `doc` folder.  
An online version is also available [here](http://lums-proj.github.io/Lums/).

## Why Lums ?

Because of this.

![A lums](http://raymanpc.com/wiki/script-en/images/f/f6/YellowLum-RR-TheWoodsofLight.jpg)

## License

This software is under the MIT license.  
You may find a copy of the license along with this software.

## Author

**Lums**, previously known as NGL, was created by Nax.

## Contributors

 - spuyet
