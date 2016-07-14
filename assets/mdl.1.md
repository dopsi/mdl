# mdl 1

## NAME

__mdl__ - display and convert MarkDown files

## SYNOPSIS

**mdl** [**-d** *DRIVER*] [**-p** *PARSER*] [**-i**] *FILE*

**mdl** --version

**mdl** --help

## DESCRIPTION

**mdl** is a display and conversion program for MarkDown files.

## OPTIONS

**-d**, **--display-driver**=*DRIVER*

Select a display driver, default is *ncurses*.

The available the display drivers are :

### Available drivers

* *ncurses* : a interface based on nCurses, similar to **less(1)**
* *latex* : a LaTeX output
* *html* : a HTML output
* *troff* : a Troff output for **man(1)**
* *plaintext* : a plaintext display

**-p**, **--input-parser**=*PARSER*

Set the parser for the input file. This switch is not yet active since there is 
only one single parser available yet for MarkDown files.

**-i**, **--input-file**=*FILE*

Name of the input file. The option switch can be ommited if the the filename is 
the last argument.

**--version**

Write the program version to standart output.

**--help**

Display a quick help.

## AUTHOR

This software was written by Simon Doppler. The original source code is hosted on
[GitHub](http://github.com/dopsi/mdl).

## COPYRIGHT

Copyright (C) 2016 Simon Doppler

This is free software; see the source for copying conditions. There is NO  warranty;  not
even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
