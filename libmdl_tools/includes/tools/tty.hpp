#ifndef LIBMDL_TOOLS_TTY_HPP
#define LIBMDL_TOOLS_TTY_HPP

class TTY {
	private:
		unsigned short _lines;
		unsigned short _columns;
	public:
		TTY();

		unsigned short lines(void) const;
		unsigned short columns(void) const;
};

#endif // LIBMDL_TOOLS_TTY_HPP
