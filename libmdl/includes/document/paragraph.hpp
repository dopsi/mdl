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
		/** @brief Indicate if the paragraph is the last of its type **/
		bool _last;
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
			OList1 /** Ordered list **/,
			UList1 /** Unordered list **/,
			UList2 /** Unordered list **/,
			Quote /** Quote paragraph **/,
			Code /** Code paragraph **/
		};

		/**
		 * @brief Get the Paragraph's Paragraph::Level
		 *
		 * @return The level of the Paragraph
		 **/
		virtual Level level(void) const = 0;
		
		/**
		 * @brief Setter for _last
		 **/
		void last(const bool & last);
		
		/**
		 * @brief Getter for _last
		 **/
		bool last(void) const;
};

#endif // MDL_PARAGRAPH_HPP
