#ifndef NICK3D_ACAMERA3D_H
#define NICK3D_ACAMERA3D_H


#ifdef NICK_USE_NICK3D


#include "AMatrix3D.h"


class ACamera3D
{
public:
  ACamera3D();
  ACamera3D(float sx,float sy,float sz,float sa, float sb, float sc);
  //
  void unit();
  void transform(ACamera3D *m);
  void transform(AMatrix3D *m);
  void transThisMatrix(AMatrix3D *m);
  void scale(float sx, float sy, float sz);
  void translate(float sx, float sy, float sz);
  void translateTo(float sx, float sy, float sz);
  void xRotBy(float theta);
  void yRotBy(float theta);
  void zRotBy(float theta);
  //
  void debugDump();
  //
protected:
  void init();
  //
  AMatrix3D trans;
};


#endif // NICK_USE_NICK3D


#endif // NICK3D_ACAMERA3D_H

