#ifndef MDP_OLIST1_PARAGRAPH_HPP
#define MDP_OLIST1_PARAGRAPH_HPP

#include "paragraph.hpp"

/**
 * @brief Ordered list paragraph (level 1)
 *
 * Every list element is represented by one instance of OList1Paragraph.
 **/
class OList1Paragraph : public Paragraph {
	public:
		OList1Paragraph() : Paragraph() {}
		OList1Paragraph(Paragraph * p) : Paragraph(p) {}
		virtual Level level(void) const;
};

#endif // MDP_OLIST1_PARAGRAPH_HPP

