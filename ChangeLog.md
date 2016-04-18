# Change Log

All notable changes to this project will be documented in this file.
This project adheres to [Semantic Versioning](http://semver.org/).

## [No version] No date

### New features

* src/parsers/md_parser.cpp (MdParser::parse_line): parse inline code snippets (using regex)
* src/parsers/md_parser.cpp (MdParser::parse): detect quote paragraphs
* src/parsers/md_parser.cpp (MdParser::parse_line): parse bold elements
* src/documents/paragraph.cpp (class definition): add Paragraph::Level::Quote
* src/display_drivers/ncurses_display_driver.cpp (N[...]::render): render QuoteParagaph
* src/display_drivers/ncurses_display_driver.cpp (N[...]::render): render BoldLineElement
* CMakeLists.txt (add_executable): add src/document/quote_paragraph.cpp
* CMakeLists.txt (add_executable): add src/document/bold_line_element.cpp
* src/document/quote_paragraph.hpp: new file
* src/document/quote_paragraph.cpp: new file
* src/document/bold_line_element.hpp: new file
* src/document/bold_line_element.cpp: new file

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
