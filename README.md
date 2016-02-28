mdl - a command line Markdown viewer
====================================

Goal
----

Build a functionnaly similar program to 
[visit1985's mdp](http://github.com/visit1985/mdp), at least for the parser,
to display a Markdown file in the way `less(1)` does for text files.

Technical solutions
-------------------

* Use `cmake(1)` as build system.
* Use `ncurses` as display library.
* Use C++ to write the program.
* Write a parser-independent display system (i.e. the parser can easily be
replaced for another one (maybe one day load an external `.so` file to 
parse the results).

C++ coding
----------

* Use std::wstring to store the data
* Use a vector of vectors of line elements (maybe use a typedef such as 
in the following code)

    typedef vector<LineElement*> Paragraph

* Have a vector of *top-level* elements (aka paragraphs, titles, tables, code, 
quotes). Each one of these elements must have the same interface as all 
the others, to enable them to be easily replaced or completed.
* Each top level element must provide at least one displayable element
(aka text portion of a line, with a specific typesetting) to be displayed.

Versionning
-----------

this project follows the semantic versionning guidelines provided at
[semver.org](http://semver.org/) with versions numbered as `major.minor.
revision` :

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

Copyright 2016 Simon Doppler <dopsi.dev@gmail.com>
