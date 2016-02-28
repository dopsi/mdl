#include "line_element.hpp"
LineElement::LineElement(const std::string & content) :
	_content(content) {
	// Nothing
}

std::string LineElement::content() const {
	return _content;
}
