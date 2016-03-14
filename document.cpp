#include "document.hpp"

Document::Document() {}

Document::~Document() {}

void Document::append_paragraph(Paragraph * p) {
	_paragraph.push_back(p);
}

size_t Document::size(void) const {
	return _paragraph.size();
}

Paragraph* Document::operator[](size_t index) const {
	if (index < _paragraph.size()) {
		return _paragraph[index];
	} else {
		return nullptr;
	}
}
