#ifndef NICK3D_ALINE3D_H
#define NICK3D_ALINE3D_H


#ifdef NICK_USE_NICK3D


#include "../cpp/alib/ageometry_alib.h"


class ALine3D //: public AGeometric3D
{
public:
  unsigned long start, end;  // Huh? Two ints? How could this even work?!?
  unsigned long color;
};


#endif // NICK_USE_NICK3D


#endif // NICK3D_ALINE3D_H

