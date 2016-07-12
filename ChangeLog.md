# Change Log

All notable changes to this project will be documented in this file.
This project adheres to [Semantic Versioning](http://semver.org/).

## [No version] No date

### New features

* TBD

### Changed

* src/document/url_line_element.hpp: add two-arguments constructor
* src/document/url_line_element.cpp: implement two-arguments constructor

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