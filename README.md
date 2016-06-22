# Project M.K.Eva

A cyperpunk dungeoun crawler RPG rogue-like game.

Writen in C++ language, using SDL library.

## Build

Simple compilation with gcc compiler:

    $ make


Compiles with debug flags and using clang compiler:

    $ make debug


Compile with optimization flags and using gcc compiler:

    $ make release

After a *[envirolment setup][CROSS_COMPILING]*, cross-compile generating a windows OS executable:

	$ make [release] OS=windows
	
## Documentation

Generate doxygen files:

    $ make doc

## Clean project

Clean auto generated files:

    $ make clean

## Dependencies

This project depends on `SDL2` libraries to compile and `Doxygen` to generate documentation.

Therefore, please make sure you have the packages *[SDL2][SDL_LINK]* and *[Doxygen][D_LINK]*.

Also, to automatic format C++ files according to the project codying style, the envirolment is set to use clang-format-3.6 package.

## Guidelines

This project guidelines are based on the *[Linux kernel coding style][CODING_STYLE]*.

To automatic format all code:

    $ make format

[CROSS_COMPILING]: http://swarminglogic.com/article/2014_11_crosscompile
[SDL_LINK]: https://wiki.libsdl.org/Installation
[CODING_STYLE]: https://www.kernel.org/doc/Documentation/CodingStyle
[D_LINK]: http://www.stack.nl/~dimitri/doxygen/download.html

