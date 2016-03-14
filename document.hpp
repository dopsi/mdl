#ifndef MDL_DOCUMENT_HPP
#define MDL_DOCUMENT_HPP

#include "paragraph.hpp"

#include <vector>

/**
 * @brief A text document
 *
 * This class does represent a text document, made of a series of Paragraph
 * elements, easily accessible through operators on the Document element.
 **/
class Document {
	private:
		std::vector<Paragraph*> _paragraph; /**!< @brief List of paragraphs **/
	public:
		/**
		 * @brief Constructor
		 **/
		Document();

		/**
		 * @brief Destructor
		 **/
		~Document();

		/**
		 * @brief Append a newly parsed paragraph to the document
		 *
		 * @param e Pointer the new Paragraph
		 **/
		void append_paragraph(Paragraph * e);

		/**
		 * @brief Get the number of Paragraph elements in the document
		 *
		 * @return The number of paragraph elements in the document.
		 * This does follow the std::vector numbering.
		 **/
		size_t size(void) const;

		/**
		 * @brief Access a given paragraph
		 *
		 * @param idx Index of the Paragraph in the document
		 *
		 * @return The pointer to the Paragraph object, nullptr if not
		 * found.
		 **/
		Paragraph* operator[] (const size_t idx) const;
};

#endif // MDL_DOCUMENT_HPP
