#ifndef MDL_CODE_LINE_ELEMENT_HPP
#define MDL_CODE_LINE_ELEMENT_HPP

#include "line_element.hpp"

/**
 * @brief A code line element
 **/
class CodeLineElement : public LineElement {
	public:
		CodeLineElement(const std::string & content);
		~CodeLineElement() {}
};

#endif // MDL_CODE_LINE_ELEMENT_HPP
