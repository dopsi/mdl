mdl - a command line Markdown viewer
====================================

Goal
----

Build a functionnaly similar program to 
[visit1985's mdp](http://github.com/visit1985/mdp), at least for the parser,
to display a Markdown file in the way *less(1)* does for text files.

This program should be easy to extend using derivatives of the DisplayDriver
class to have a new frontend and derivatives of the Parser class (see the 
status.md file for more information).

Usage
-----

* `Up`: go up
* `Down`: go down
* `Space`: go down half page
* `PgUp`: go up one page
* `PgDown`: go down one page
* `u`: display URL links
* `q`: quit program

Building
--------

This program depends on :

* C++11
* ncurses
* Doxygen (to generate the documentation)

To build the program, follow these steps :

* create a `build` directory
* run `cmake $source_directory`
* run `make`

This program cannot be installed as of now.

To build the documentation, run `doxygen` in the source directory

Versionning
-----------

this project follows the semantic versionning guidelines provided at
[semver.org](http://semver.org/) with versions numbered as 
`major.minor.revision` :

* `major` is increased after a backwards incompatible api change.
* `minor` is increased after a backwards compatible api change.
* `revision` is increased after a change with no effect on the api.

any version with `major` being 0 *should* not be considered stable nor
should its api.

Versions history can be found in the file ChangeLog.md

Licence
=======

This software and all related documents are licenced under the
MIT licence (see `LICENCE` file for more informations).

Author
======

Copyright 2016 Simon Doppler <dopsi@member.fsf.org>
