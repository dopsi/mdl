# Change Log

All notable changes to this project will be documented in this file.
This project adheres to [Semantic Versioning](http://semver.org/).

## [No version] No date

### New features

* TBD

### Changed

* libmdl/CMakeLists.txt: fix install directory for includes

## [v1.0.0] 2016-07-15

This update is a major update to 1.0.0

### New features

* mdl/display_drivers/html_display_driver.hpp: new file
* mdl/display_drivers/html_display_driver.cpp: new file
* mdl/display_drivers/troff_display_driver.hpp: new file
* mdl/display_drivers/troff_display_driver.cpp: new file
* mdl/parsers/md_parser.cpp: introduce Title3Paragraph
* libmdl/includes/document/title3_paragraph.hpp: new file
* libmdl/document/title3_paragraph.cpp: new file
* assets/mdl.1.md: create the manpage

### Changed

* whole project: reorder and split between program and library
* src/main.cpp: add HtmlDisplayDriver
* src/parsers/md_parser.cpp: fix URL parsing

## [v0.5.1] 2016-07-13

### New features

* src/document/document.cpp: detect when paragraph type changes
* src/document/paragraph.hpp: add last variable (+setter +getter)
* src/document/paragraph.cpp: implement last variable (+setter +getter)

### Changed

* src/document/url_line_element.hpp: add two-arguments constructor
* src/document/url_line_element.cpp: implement two-arguments constructor
* various files: documentation

## [v0.5.0] 2016-07-12

### New features

* src/display_drivers/latex_display_driver.hpp: new file
* src/display_drivers/latex_display_driver.cpp: new file

## [v0.4.1] 2016-07-02

### New features

* src/parsers/md_parser.cpp (MdParser::parse_line): parse inline code snippets (using regex)
* src/parsers/md_parser.cpp (MdParser::parse): detect quote paragraphs and take in account
empty quoted lines
* src/parsers/md_parser.cpp (MdParser::parse_line): parse bold and italic elements
* src/parsers/md_parser.cpp (MdParser::parse_line): do not clear the line
* src/parsers/md_parser.cpp (namespace::string_clear_leading): fix bug in string::substr usage
* src/documents/paragraph.cpp (class definition): add Paragraph::Level::Quote
* src/display_drivers/ncurses_display_driver.hpp (class definition): add check_capabilities()
* src/display_drivers/ncurses_display_driver.hpp (class definition): add _url_window
* src/display_drivers/ncurses_display_driver.cpp (N[...]::render): render QuoteParagaph
* src/display_drivers/ncurses_display_driver.cpp (N[...]::render): render BoldLineElement
* src/display_drivers/ncurses_display_driver.cpp (N[...]::render): render ItalicLineElement
* src/display_drivers/ncurses_display_driver.cpp (N[...]::render): add check_capabilities()
* CMakeLists.txt (add_executable): add src/document/quote_paragraph.cpp
* CMakeLists.txt (add_executable): add src/document/bold_line_element.cpp
* src/document/quote_paragraph.hpp: new file
* src/document/quote_paragraph.cpp: new file
* src/document/bold_line_element.hpp: new file
* src/document/bold_line_element.cpp: new file
* src/document/italic_line_element.hpp: new file
* src/document/italic_line_element.cpp: new file
* src/document/url_line_element.hpp: add _url member
* src/document/url_line_element.cpp: extract url from link content

### Changed

* src/parsers/md_parser.cpp (MdParser::parse_line): function now recursive
* src/parsers/md_parser.cpp (MdParser::parse_line): do not allow closing parenthesis in URL
* src/parsers/md_parser.cpp (MdParser::parse): also use tab as code prefix
* src/display_drivers/ncurses_display_driver.cpp(N[...]::render): disable unused attributes
for code paragraphs
* src/display_drivers/ncurses_display_driver.cpp(N[...]::render): fix overlapping lines
* src/display_drivers/ncurses_display_driver.cpp(N[...]::render): save and recall attributes
* src/display_drivers/ncurses_display_driver.cpp(N[...]::render): color code and quote boxes
before writing on them
