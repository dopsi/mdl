#ifndef MDL_DOCUMENT_HPP
#define MDL_DOCUMENT_HPP

#include "paragraph.hpp"

#include <vector>

/**
 * @brief A text document
 **/
class Document {
	private:
		std::vector<Paragraph*> _paragraph;
	public:
		Document();
		~Document();
		void append_paragraph(Paragraph * e);
		size_t size(void) const;
		Paragraph* operator[] (const size_t idx) const;
};

#endif // MDL_DOCUMENT_HPP
