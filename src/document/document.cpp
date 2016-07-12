#include "document.hpp"

Document::Document(const std::string & filename) : _filename(filename) {}

Document::~Document() {}

std::string Document::filename(void) const {
	return _filename;
}

void Document::append_paragraph(Paragraph * p) {
	Paragraph *last_p(nullptr);

	if (_paragraph.size()) {
		last_p = _paragraph.back();
	}

	if (last_p and p->level() < last_p->level()) {
		last_p->last(true);
	}

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
