#ifndef NICK3D_AVERTEX3D_H
#define NICK3D_AVERTEX3D_H


#ifdef NICK_USE_NICK3D


#include "../cpp/alib/ageometry_alib.h"


class AVertexF3D //: public AGeometric3D_alib
{
public:
  float x, y, z;
};


class AVertexI3D //: public AGeometric3D_alib
{
public:
  int x, y, z;
};


class AVertex3Dlws //: public AGeometric3D_alib
{
public:
  int lx, ly, lz, lt;
  int wx, wy, wz, wt;
  int sx, sy, sz, st;
};


#endif // NICK_USE_NICK3D


#endif // NICK3D_AVERTEX3D_H

