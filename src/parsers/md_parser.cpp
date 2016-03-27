#include "md_parser.hpp"
#include "../document/text_line_element.hpp"
#include "../document/url_line_element.hpp"
#include "../document/text_paragraph.hpp"
#include "../document/title1_paragraph.hpp"
#include "../document/title2_paragraph.hpp"
#include "../document/ulist1_paragraph.hpp"

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
		return s.substr(s.find_first_not_of(subset));
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
	Paragraph *p0(nullptr), *p1(nullptr);
	LineElement *e = nullptr, *last_e = nullptr;
	size_t sharps(0);
	while (getline(_input_file, line)) {
		if (line.empty()) {
			// end of line, change paragraph
			if (p0 and p0->size()) {
				_document->append_paragraph(p0);
				p0 = nullptr;
			}
			p0 = new TextParagraph();
		} else {
			sharps = string_startswith(line, '#');
			if (!p0) {
				p0 = new TextParagraph();
			}

			if (sharps != 0) {
				switch(sharps) {
					case 1:
						delete p0;
						p0 = new Title1Paragraph();
						break;
					case 2:
						delete p0;
						p0 = new Title2Paragraph();
						break;
					default:
						break;
				}
				parse_line(p0, line);
			} else if (string_has_only(line, '=')) { // title 1 delimiter
				p1 = new Title1Paragraph(p0);
				delete p0;
				p0 = nullptr;
				_document->append_paragraph(p1);
				p1 = nullptr;
			} else if (string_has_only(line, '-')) { // title 2 delimiter
				p1 = new Title2Paragraph(p0);
				delete p0;
				p0 = nullptr;
				_document->append_paragraph(p1);
				p1 = nullptr;
			} else if (string_startswith(line, "* ")) { // level 1 list delimiter
				if (p0 and p0->size()) {
					_document->append_paragraph(p0);
					p0=nullptr;
				}
				p0 = new UList1Paragraph();
				parse_line(p0, line.substr(2));
			} else {
				// other content
				if (p0->size() && last_e && (last_e->content()).back() != ' ' && line.front() != ' ') {
					line = " "+line;
				}
				last_e = parse_line(p0, line);
			}
		}
	}

	if (p0 and p0->size()) {
		_document->append_paragraph(p0);
	}
}

LineElement* MdParser::parse_line(Paragraph *p, const std::string & line) {
	string s(string_clear_leading(line, " \t#"));
	regex r("\\[.*\\]\\(.*\\)");
	smatch m;
	LineElement *e;

	while (regex_search(s,m,r)) {
		e = new TextLineElement(m.prefix());
		p->append_line_element(e);
		e = new UrlLineElement(m.str());
		p->append_line_element(e);
		s = m.suffix().str();
	}

	e = new TextLineElement(s);
	p->append_line_element(e);
	return e;
}