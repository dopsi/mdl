#include "paragraph.hpp"

Paragraph::Paragraph() {
}

Paragraph::Paragraph(Paragraph * p) : _elements(p->_elements) {
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
