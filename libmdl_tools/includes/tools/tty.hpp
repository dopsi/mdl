#ifndef LIBMDL_TOOLS_TTY_HPP
#define LIBMDL_TOOLS_TTY_HPP

class TTY {
	private:
		unsigned short _lines;
		unsigned short _columns;
		void get_winsize(void);
		void set_winsize(unsigned short c, unsigned short l);
	public:
		TTY();

		unsigned short lines(void) const;
		unsigned short lines(unsigned short l);
		unsigned short columns(void) const;
		unsigned short columns(unsigned short c);
};

#endif // LIBMDL_TOOLS_TTY_HPP
