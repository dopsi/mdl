#include "../includes/document/paragraph.hpp"

Paragraph::Paragraph() : _last(false) {
}

Paragraph::Paragraph(Paragraph * p) : _last(false), _elements(p->_elements) {
}

Paragraph::~Paragraph() {}

void Paragraph::append_line_element(LineElement * e) {
	_elements.push_back(e);
}

size_t Paragraph::size(void) const {
	return _elements.size();
}

LineElement * Paragraph::element(size_t index) const {
	return _elements[index];
}

LineElement * Paragraph::operator[](size_t index) const {
	return element(index);
}

void Paragraph::last(const bool & last) {
	_last = last;
}

bool Paragraph::last(void) const {
	return _last;
}
