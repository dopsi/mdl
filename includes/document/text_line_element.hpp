#ifndef MDL_TEXT_LINE_ELEMENT_HPP
#define MDL_TEXT_LINE_ELEMENT_HPP

#include "line_element.hpp"

/**
 * @brief A text line element
 **/
class TextLineElement : public LineElement {
	public:
		TextLineElement(const std::string & content);
		~TextLineElement() {}
};

#endif // MDL_TEXT_LINE_ELEMENT_HPP
