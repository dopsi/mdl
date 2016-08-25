#include "tools/tty.hpp"

#include <sys/ioctl.h>
#include <unistd.h>

TTY::TTY() {
	get_winsize();
}

void TTY::get_winsize(void) {
	struct winsize ws;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	_lines = ws.ws_row;
	_columns = ws.ws_col;
}

void TTY::set_winsize(unsigned short c, unsigned short l) {
	struct winsize ws;
	_lines = ws.ws_row = l;
	_columns = ws.ws_col = c;
	ioctl(STDOUT_FILENO, TIOCSWINSZ, &ws);
}

unsigned short TTY::lines(void) const {
	return _lines;
}

unsigned short TTY::columns(void) const {
	return _columns;
}

unsigned short TTY::lines(unsigned short l) {
	set_winsize(l, _columns);
	return _lines;
}

unsigned short TTY::columns(unsigned short c) {
	set_winsize(_lines, c);
	return _columns;
}
