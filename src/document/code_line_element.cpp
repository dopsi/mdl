#include "code_line_element.hpp"

CodeLineElement::CodeLineElement(const std::string & content) :
	LineElement(content.substr(1, content.length()-2)) {}
