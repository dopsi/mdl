#ifndef MDL_BOLD_LINE_ELEMENT_HPP
#define MDL_BOLD_LINE_ELEMENT_HPP

#include "line_element.hpp"

/**
 * @brief A bold line element
 **/
class BoldLineElement : public LineElement {
	public:
		BoldLineElement(const std::string & content);
		~BoldLineElement() {}
};

#endif // MDL_BOLD_LINE_ELEMENT_HPP
