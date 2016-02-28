#include "md_parser.hpp"
#include "text_line_element.hpp"
#include "text_paragraph.hpp"
#include "title1_paragraph.hpp"
#include "title2_paragraph.hpp"

using namespace std;

namespace {
	bool string_has_only(const std::string & s, const char & c) {
		return (s.find_first_not_of(c) == std::string::npos);
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
	_document = new Document();
	Paragraph *p0(nullptr), *p1(nullptr);
	LineElement *e = nullptr, *last_e = nullptr;
	while (getline(_input_file, line)) {
		if (line.empty()) {
			// end of line, change paragraph
			if (p0) {
				_document->append_paragraph(p0);
			}
			p0 = new TextParagraph();
		} else {
			if (!p0) {
				p0 = new TextParagraph();
			}

			if (string_has_only(line, '=')) {
				// title1 delimiter
				p1 = new Title1Paragraph(p0);
				delete p0;
				p0 = nullptr;
				_document->append_paragraph(p1);
				p1 = nullptr;
			} else if (string_has_only(line, '-')) {
				// title2 delimiter
				p1 = new Title2Paragraph(p0);
				delete p0;
				p0 = nullptr;
				_document->append_paragraph(p1);
				p1 = nullptr;
			} else {
				// other content
				if (last_e && (last_e->content()).back() != ' ' && line.front() != ' ') {
					line = " "+line;
				}
				e = new TextLineElement(line);
				p0->append_line_element(e);
				last_e = e;
				e = nullptr;
			}
		}
	}

	if (p0) {
		_document->append_paragraph(p0);
	}
}
