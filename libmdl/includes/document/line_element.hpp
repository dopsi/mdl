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
		/** @brief The contents of the LineElement **/
		std::string _content;
	public:
		/**
		 * @brief Constructor
		 *
		 * @param content The LineElement's content
		 **/
		LineElement(const std::string & content);

		/**
		 * @brief Destructor
		 **/
		virtual ~LineElement() {}

		/**
		 * @brief Get the LineElement's content
		 *
		 * @return the LineElement's content (may be an empty string)
		 **/
		virtual std::string content(void) const;
};

#endif // MDL_LINE_ELEMENT_HPP
