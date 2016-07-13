#ifndef MDL_URL_LINE_ELEMENT_HPP
#define MDL_URL_LINE_ELEMENT_HPP

#include "line_element.hpp"

/**
 * @brief An URL line element
 *
 * The link name will be returned by a call of LineElement::content(),
 * while the link's url will be returned by UrlLineElement::url().
 **/
class UrlLineElement : public LineElement {
	protected:
		std::string _url;
	public:
		/**
		 * @brief Standart constructor
		 *
		 * This constructor takes two arguments, for maximum
		 * compatibility for all parsers.
		 *
		 * @param content Link name
		 * @param url Link url
		 **/
		UrlLineElement(const std::string & content,
				const std::string & url);

		/**
		 * @brief Destructor
		 **/
		~UrlLineElement() {}

		/**
		 * @brief Return the link's url
		 **/
		std::string url(void) const;
};

#endif // MDL_URL_LINE_ELEMENT_HPP
