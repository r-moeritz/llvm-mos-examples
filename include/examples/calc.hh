#ifndef CALC_HH
#define CALC_HH

#include "types.h"

namespace examples {
  struct Calculator {
    const BYTE BUFFER_SIZE = 0x80;

    Calculator();
    ~Calculator();

    WORD parseFormulae();

  private:
    WORD parseNumber();
    WORD parseProduct();
    WORD parseFactor();
    void readInput();

    ASCIIZ m_pBuf;
  };
}

#endif // #ifndef CALC_HH
