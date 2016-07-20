# News

## [No version] No date

### New features

* TBD

### Changed

* [libmdl] Change include directory from `$PREFIX/include` to `$PREFIX/include/mdl`
* [mdl] Implement Title3 for `NcursesDisplayDriver`
* [mdl] Implement Title3 for `HtmlDisplayDriver`
* [mdl] Implement Title3 for `LaTeXDisplayDriver`

## [v1.0.0] 2016-07-15

This program has now reached a sufficiently mature state. It has been reordered
and split into `mdl` and `libmdl`.

### New features

* Add HtmlDisplayDriver
* Add TroffDisplayDriver
* Implement Title3Paragraph (also in MdParser)
* Add manpage (assets/mdl.1.md) and manpage generation

### Changed

* Fix URL reading in MdParser (do not include the last parenthesis)

## [v0.5.1] 2016-07-13

### New features

* Add Paragraph::_last feature (to detect the change of paragraph type)
* New UrlLineElement constructor (for two arguments)

### Changed

* Detection of valid delimtor for LaTeX
* Documentation

## [v0.5.0] 2016-07-12

### New features

* Add a LaTeXDisplayDriver class

## [v0.4.1] 2016-07-02

### New features

* Add a `--version` option to display the version number of the program
* Handle inline code snippets
* Handle bold and italic line elements
* Handle quotations
* Detech italics capability (does not work on all terminal emulators)
* Display URLs in windows (press `u`)

## [v0.4.0] 2016-04-16

### New features

* Scrolling now supports `PgUp`, `PgDn` and `space` keys
* Indented code blocks
* Use `boost::program_options` to handle options

### Changed

* Various bugfixes (overlapping elements)

## [v0.3.0] 2016-04-15

### New features

* Text scrolling in the Ncurses display
* Show position info in the bottom bar
* Parse URL's in Markdown
* Major improvements in documentation

## [v0.2.0] 2016-03-27

### New features

* First draft of the ncurses displayer (no scrolling, no highlighting)
