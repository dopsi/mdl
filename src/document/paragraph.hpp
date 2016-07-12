#ifndef MDL_PARAGRAPH_HPP
#define MDL_PARAGRAPH_HPP

#include "line_element.hpp"

#include <vector>

/**
 * @brief Base class for paragraphs
 *
 * Every paragraph is meant to be followed by a newline.
 **/
class Paragraph {
	protected:
		/** @brief List of LineElement in this Paragraph **/
		std::vector<LineElement*> _elements;
	public:
		/**
		 * @brief Constructor
		 **/
		Paragraph();
		
		/**
		 * @brief Conversion constructor
		 *
		 * @param p Pointer to the original paragraph
		 **/
		Paragraph(Paragraph * p);
		
		/**
		 * @brief Destructor
		 **/
		~Paragraph();

		/**
		 * @brief Append a line element
		 *
		 * @param e The pointer to the LineElement to append
		 **/
		virtual void append_line_element(LineElement * e);

		/**
		 * @brief Get the number of LineElement
		 **/
		size_t size(void) const;

		/**
		 * @brief Access a line element
		 *
		 * @param index The index of the requested LineElement
		 * @return A pointer to the LineElement, nullptr 
		 * if the index does not exist.
		 **/
		LineElement * element(size_t index = 0) const;

		/**
		 * @brief Access a line element
		 *
		 * @param index The index of the requested LineElement
		 * @return A pointer to the LineElement, nullptr 
		 * if the index does not exist.
		 **/
		LineElement * operator[] (size_t index) const;

		/**
		 * @brief Level of the paragraph
		 *
		 * This value is returned by Paragraph::level()
		 **/
		enum class Level {
			Text /** This is the default level **/,
			Title1 /** First title **/,
			Title2 /** Second title **/,
			Title3 /** Third title **/,
			Title4 /** Fourth title **/,
			Title5 /** Fifth title **/,
			Title6 /** Sixth title **/,
			UList1 /** Unordered list **/,
			Code /** Code paragraph **/,
			Quote /** Quote paragraph **/
		};

		/**
		 * @brief Get the Paragraph's Paragraph::Level
		 *
		 * @return The level of the Paragraph
		 **/
		virtual Level level(void) const = 0;
};

#endif // MDL_PARAGRAPH_HPP
