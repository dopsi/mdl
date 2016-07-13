#include "md_parser.hpp"

#include "../document/text_line_element.hpp"
#include "../document/url_line_element.hpp"
#include "../document/code_line_element.hpp"
#include "../document/bold_line_element.hpp"
#include "../document/italic_line_element.hpp"

#include "../document/text_paragraph.hpp"
#include "../document/title1_paragraph.hpp"
#include "../document/title2_paragraph.hpp"
#include "../document/ulist1_paragraph.hpp"
#include "../document/code_paragraph.hpp"
#include "../document/quote_paragraph.hpp"

#include <regex>

using namespace std;

namespace {
	bool string_has_only(const std::string & s, const char & c) {
		return (s.find_first_not_of(c) == std::string::npos);
	}

	template<class T>
	T max(const T & a, const T & b) {
		if (a > b) {
			return a;
		} else {
			return b;
		}
	}

	size_t string_startswith(const std::string & s, const char & c) {
		size_t i(0);
		while (s[i] == c and i < s.length()){
			++i;
		}

		return i;
	}

	bool string_startswith(const std::string & s, const std::string & c) {
		if (s.length() < c.length()) {
			return false;
		}

		size_t i(0);
		while (s[i] == c[i] and i < c.length() ){
			++i;
		}
		
		if (i != c.length()) {
			return false;
		}

		return true;
	}

	std::string string_clear_leading(const std::string & s, const std::string & subset) {
		size_t found = s.find_first_not_of(subset);
		if (found != string::npos) {
			return s.substr(found);
		} else {
			return string("");
		}
	}

};

MdParser::MdParser(const std::string & filename) :
	Parser(filename) {
	parse();
}

MdParser::~MdParser() {
	// dtor
}

void MdParser::parse() {
	std::string line;
	_document = new Document(_filename);
	Paragraph *current_p(nullptr), *temp_p(nullptr);
	LineElement *e = nullptr, *last_e = nullptr;
	size_t sharps(0);
	while (getline(_input_file, line)) {
		if (line.empty()) {
			// end of line, change paragraph
			if (current_p and current_p->size()) {
				_document->append_paragraph(current_p);
				current_p = nullptr;
			}
			current_p = new TextParagraph();
		} else {
			sharps = string_startswith(line, '#');

			if (!current_p) {
				current_p = new TextParagraph();
			}

			if ( (line.substr(0, 4) == "    " or line[0] == '\t') and (!current_p or !current_p->size()) ) {
				// This is a code paragraph
				delete current_p;
				current_p = new CodeParagraph();
				line = string_clear_leading(line, " \t");
				current_p->append_line_element(new CodeLineElement(line));
				_document->append_paragraph(current_p);
				current_p = new TextParagraph();
			} else if (sharps != 0) {
				line = string_clear_leading(line, "\t #");
				switch(sharps) {
					case 1:
						delete current_p;
						current_p = new Title1Paragraph();
						break;
					case 2:
						delete current_p;
						current_p = new Title2Paragraph();
						break;
					default:
						break;
				}
				parse_line(current_p, line);
			} else if (string_startswith(line, ">") and (!current_p or !current_p->size())) {
				delete current_p;
				current_p = new QuoteParagraph();
				if (line.substr(1).find_first_not_of("\t ") == string::npos) {
					parse_line(current_p, " ");
				} else {
					parse_line(current_p, line.substr(2));
				}
				_document->append_paragraph(current_p);
				current_p = new TextParagraph();
			} else if (string_has_only(line, '=')) { // title 1 delimiter
				temp_p = new Title1Paragraph(current_p);
				delete current_p;
				current_p = nullptr;
				_document->append_paragraph(temp_p);
				temp_p = nullptr;
			} else if (string_has_only(line, '-')) { // title 2 delimiter
				temp_p = new Title2Paragraph(current_p);
				delete current_p;
				current_p = nullptr;
				_document->append_paragraph(temp_p);
				temp_p = nullptr;
			} else if (string_startswith(line, "* ") or string_startswith(line, "- ")) { // level 1 list delimiter
				if (current_p and current_p->size()) {
					_document->append_paragraph(current_p);
					current_p=nullptr;
				}
				current_p = new UList1Paragraph();
				parse_line(current_p, line.substr(2));
			} else {
				// other content
				if (current_p->size() && last_e && (last_e->content()).back() != ' ' && line.front() != ' ') {
					line = " "+line;
				}
				last_e = parse_line(current_p, line);
			}
		}
	}

	if (current_p and current_p->size()) {
		_document->append_paragraph(current_p);
	}
}

LineElement* MdParser::parse_line(Paragraph *p, const std::string & line) {
	regex url_regex("\\[.*\\]\\([^)]*\\)"),
	      code_regex("`[^`]*`"),
	      bold_regex("(\\*\\*|__)[^\\*_]+(\\*\\*|__)"),
	      italic_regex("(\\*|_)[^\\*_]+(\\*|_)");
	smatch match;
	string link_name, link_url;
	size_t link_limit(0);
	LineElement *e;

	if (regex_search(line,match,url_regex)) {
		// Found a url
		parse_line(p, match.prefix());

		link_limit = match.str().find_first_of("](");
		link_name = match.str().substr(1, link_limit-1);
		link_url = match.str().substr(link_limit+2, match.str().length()-(link_limit+3));
		
		p->append_line_element(new UrlLineElement(link_name, link_url));
		e = parse_line(p, match.suffix());
	}  else if (regex_search(line, match, code_regex)) {
		// Found a code snippet
		parse_line(p, match.prefix());
		p->append_line_element(
			new CodeLineElement(match.str().substr(1, match.str().length()-2)));
		e = parse_line(p, match.suffix());
	} else if (regex_search(line, match, bold_regex)) {
		// Bold element
		parse_line(p, match.prefix());
		p->append_line_element(
			new BoldLineElement(match.str().substr(2, match.str().length()-4)));
		e = parse_line(p, match.suffix());
	} else if (regex_search(line, match, italic_regex)) {
		// Italic element
		parse_line(p, match.prefix());
		p->append_line_element(
			new ItalicLineElement(match.str().substr(1, match.str().length()-2)));
		e = parse_line(p, match.suffix());
	} else {
		e = new TextLineElement(line);
		p->append_line_element(e);
	}

	return e;
}
