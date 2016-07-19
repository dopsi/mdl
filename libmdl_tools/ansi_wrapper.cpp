#include "tools/ansi_wrapper.hpp"

#include <sstream>

using namespace std;

AnsiWrapper::AnsiWrapper(ostream &stream) :
	_stream(stream) {
	// TBD
}

void AnsiWrapper::fg(const Color & color) {
	stringstream code;
	code << "3" << static_cast<int>(color);
	_stream << "\033[" << code.str() << "m";
}

void AnsiWrapper::bg(const Color & color) {
	stringstream code;
	code << "4" << static_cast<int>(color);
	_stream << "\033[" << code.str() << "m";
}

void AnsiWrapper::underline(bool underline) {
	if (underline) {
		_stream << "\033[4m";
	} else {
		_stream << "\033[24m";
	}
}

void AnsiWrapper::reverse() {
	_stream << "\033[7m";
}

void AnsiWrapper::reset() {
	_stream << "\033[0m";
}

AnsiWrapper& AnsiWrapper::operator<<(std::ostream& (*f)(std::ostream&)) {
	f(_stream);
	return *this;
}
