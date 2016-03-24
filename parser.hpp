#ifndef MDL_PARSER_HPP
#define MDL_PARSER_HPP

#include "document.hpp"

#include <string>
#include <fstream>

/**
 * @brief Generic parser interface
 *
 * This parser interface is meant to be specialized, to be able to return
 * a Document pointer for the type of document it parses.
 **/
class Parser {
	protected:
		std::string _filename; /**!< Input file name **/
		std::ifstream _input_file; /**!< Input file stream, re-read on reload **/
		Document * _document; /**!< Pointer to the Document object **/
	public:
		/**
		 * @brief Constructor
		 *
		 * @param filename Filename of the document to parse
		 *
		 * This constructor does open the file in read-only mode. No error checking
		 * is done.
		 **/
		Parser(const std::string & filename);

		/**
		 * @brief Destructor
		 **/
		virtual ~Parser();

		/**
		 * @brief Return the pointer to the document.
		 * @return the pointer to the document, or nullptr if not yet parsed or
		 * if the parse failed.
		 **/
		virtual Document* get_document(void) const;

		/**
		 * @brief The actual parsing function
		 *
		 * This function has to be implemented by each parser. It should only
		 * create a Document object, pointed to by the Parser::_document pointer,
		 * which will be returned using Parser::get_document().
		 **/
		virtual void parse() = 0;
};

#endif // MDL_PARSER_HPP
