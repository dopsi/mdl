#ifndef MDL_LINE_ELEMENT_HPP
#define MDL_LINE_ELEMENT_HPP

#include <string>

/**
 * @brief A line element
 *
 * This line element is a sub-element of a Paragraph, not to be followed by a newline.
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
