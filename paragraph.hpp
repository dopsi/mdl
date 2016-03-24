#ifndef MDL_PARAGRAPH_HPP
#define MDL_PARAGRAPH_HPP

#include "line_element.hpp"

#include <vector>

/**
 * @brief Base class for paragraphs
 **/
class Paragraph {
	protected:
		std::vector<LineElement*> _elements;
	public:
		Paragraph();
		Paragraph(Paragraph * p);
		~Paragraph();
		virtual void append_line_element(LineElement * e);
		size_t size(void) const;
		LineElement * element(size_t index = 0) const;
		LineElement * operator[] (size_t index) const;
		enum class Level {
			Text,
			Title1,
			Title2,
			Title3,
			Title4,
			Title5,
			Title6,
			UList1
		};
		virtual Level level(void) const = 0;
};

#endif // MDL_PARAGRAPH_HPP
