#include "document.hpp"

Document::Document(const std::string & filename) : _filename(filename) {}

Document::~Document() {}

std::string Document::filename(void) const {
	return _filename;
}

void Document::append_paragraph(Paragraph * p) {
	if (p and p->size()) {
		_paragraph.push_back(p);
	}
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
