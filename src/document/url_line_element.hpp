#ifndef MDL_URL_LINE_ELEMENT_HPP
#define MDL_URL_LINE_ELEMENT_HPP

#include "line_element.hpp"

/**
 * @brief An URL line element
 **/
class UrlLineElement : public LineElement {
	public:
		UrlLineElement(const std::string & content);
		~UrlLineElement() {}
};

#endif // MDL_URL_LINE_ELEMENT_HPP
