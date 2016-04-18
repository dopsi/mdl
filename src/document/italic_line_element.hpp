#ifndef MDL_ITALIC_LINE_ELEMENT_HPP
#define MDL_ITALIC_LINE_ELEMENT_HPP

#include "line_element.hpp"

/**
 * @brief A bold line element
 **/
class ItalicLineElement : public LineElement {
	public:
		ItalicLineElement(const std::string & content);
		~ItalicLineElement() {}
};

#endif // MDL_ITALIC_LINE_ELEMENT_HPP
