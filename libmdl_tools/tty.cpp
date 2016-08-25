#include "tools/tty.hpp"

#include <sys/ioctl.h>
#include <unistd.h>

TTY::TTY() {
	struct winsize ws;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	_lines = ws.ws_row;
	_columns = ws.ws_col;
}

unsigned short TTY::lines(void) const {
	return _lines;
}

unsigned short TTY::columns(void) const {
	return _columns;
}
