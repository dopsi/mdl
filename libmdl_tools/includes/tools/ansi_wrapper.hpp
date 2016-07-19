#ifndef MDL_TOOLS_ANSI_WRAPPER_HPP
#define MDL_TOOLS_ANSI_WRAPPER_HPP

#include <ostream>

class AnsiWrapper {
	public:
		/**
		 * @brief Constructor
		 *
		 * @param stream The stream to be wrapped
		 **/
		AnsiWrapper(std::ostream & stream);

		/**
		 * @brief List of colors
		 **/
		enum class Color {
			Black,
			Red,
			Green,
			Yellow,
			Blue,
			Magenta,
			Cyan,
			White
		};

		/**
		 * @brief Set foreground color
		 *
		 * Set the foreground color.
		 *
		 * @param color New foreground color of the terminal
		 **/
		void fg(const Color & color);

		/**
		 * @brief Set background color
		 *
		 * Set the background color.
		 *
		 * @param color New background color of the terminal
		 **/
		void bg(const Color & color);

		/**
		 * @brief Reverse
		 **/
		void reverse();

		/**
		 * @brief Underline
		 **/
		void underline(bool underline=true);

		/**
		 * @brief Reset
		 **/
		void reset(void);

		/**
		 * @brief Template of a operator
		 *
		 * This operator allows to handle all types that 
		 * have an overloaded operator to std::ostream.
		 * To be able to output any object, it is only 
		 * required to overload the operator to print
		 * it on an std::ostream object.
		 **/
		template<typename T> AnsiWrapper& operator<<(const T& obj);

		/**
		 * @brief Operator to handle std::endl-like functions
		 *
		 * This operator allows to handle std::endl-like functions 
		 **/
		AnsiWrapper& operator<<(std::ostream& (*f)(std::ostream&));

	private:
		/**
		 * @brief Reference to the wrapped stream
		 **/
		std::ostream &_stream;
};

template<typename T> AnsiWrapper& AnsiWrapper::operator<<(const T& obj) {
	_stream << obj;
	return *this;
}

#endif // MDL_TOOLS_ANSI_WRAPPER_HPP
