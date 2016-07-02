#ifndef MDL_URL_LINE_ELEMENT_HPP
#define MDL_URL_LINE_ELEMENT_HPP

#include "line_element.hpp"

/**
 * @brief An URL line element
 **/
class UrlLineElement : public LineElement {
	protected:
		std::string _url;
	public:
		UrlLineElement(const std::string & content);
		~UrlLineElement() {}
		std::string url(void) const;
};

#endif // MDL_URL_LINE_ELEMENT_HPP
