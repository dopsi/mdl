#ifndef MDL_LINE_ELEMENT_HPP
#define MDL_LINE_ELEMENT_HPP

#include <string>

/**
 * @brief A line element
 **/
class LineElement {
	protected:
		std::string _content;
	public:
		LineElement(const std::string & content);
		virtual ~LineElement() {}
		virtual std::string content(void) const;
};

#endif // MDL_LINE_ELEMENT_HPP
