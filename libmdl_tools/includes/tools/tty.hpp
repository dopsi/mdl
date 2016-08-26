#ifndef LIBMDL_TOOLS_TTY_HPP
#define LIBMDL_TOOLS_TTY_HPP

/**
 * @brief TTY handling class
 *
 * This class is intended to allow for an easy handling of the Linux TTY.
 * This class also works for virtual terminals.
 **/
class TTY {
	private:
		unsigned short _lines; /**< @brief Number of lines **/
		unsigned short _columns; /**< @brief Number of columns **/

		/**
		 * @brief Internal helper function to get the TTY size.
		 *
		 * This function is a wrapper around ioctl.
		 **/
		void get_winsize(void);

		/**
		 * @brief Internal helper function to set the TTY size.
		 *
		 * This function is a wrapper around ioctl.
		 **/
		void set_winsize(unsigned short c, unsigned short l);
	public:
		/**
		 * @brief Constructor
		 **/
		TTY();

		/**
		 * @brief Get the number of lines.
		 *
		 * @return The number of lines of the TTY.
		 **/
		unsigned short lines(void) const;

		/**
		 * @brief Set the number of lines of the TTY.
		 *
		 * @param l The new number of lines.
		 *
		 * @return The new number of lines.
		 **/
		unsigned short lines(unsigned short l);

		/**
		 * @brief Get the number of columns.
		 *
		 * @return The number of columns of the TTY.
		 **/
		unsigned short columns(void) const;

		/**
		 * @brief Set the number of columns of the TTY.
		 *
		 * @param l The new number of columns.
		 *
		 * @return The new number of columns.
		 **/
		unsigned short columns(unsigned short c);
};

#endif // LIBMDL_TOOLS_TTY_HPP
