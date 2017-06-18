#ifndef LAYOUTCHARACTER_HEADER_H
#define LAYOUTCHARACTER_HEADER_H
#include <boost/smart_ptr.hpp>
class LayoutCharacters {

	public:

    /**
     * Tabulator column increment.
     */
    static int  TabInc;

    /**
     * Tabulator character.
     */
    static char TAB;

    /**
     * Line feed character.
     */
    static char LF;

    /**
     * Form feed character.
     */
    static char FF;

    /**
     * Carriage return character.
     */
    static char CR;

    /**
     * QS_TODO 为什么不是0x0？<br/>
     * End of input character. Used as a sentinel to denote the character one beyond the last defined character in a
     * source file.
     */
    static char EOI;
};

#endif

