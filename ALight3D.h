#ifndef NICK3D_ALIGHT3D_H
#define NICK3D_ALIGHT3D_H


#ifdef NICK_USE_NICK3D


#include "AMatrix3D.h"
#include "AVertex3D.h"


class ALight3D
{
public:
  ALight3D(float x,float y,float z);
  //
  AVertexF3D *getBMin() { return &bmin; }
  AVertexF3D *getBMax() { return &bmax; }
  //
  void debugDump();
  //
protected:
  //
  void init();
  //
  AMatrix3D trans;
  AVertexF3D bmin,bmax;
  //
};


#endif // NICK_USE_NICK3D


#endif // NICK3D_ALIGHT3D_H

