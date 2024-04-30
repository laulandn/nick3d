#ifndef NICK3D_ATHING3D_H
#define NICK3D_ATHING3D_H


#ifdef NICK_USE_NICK3D


#include "AMesh3D.h"


class AThing3D
{
public:
  //
  AThing3D(AMesh3D *theMesh);
  virtual ~AThing3D();
  //
  AMesh3D *getMesh() { return m; }
  //
  unsigned long getNumVerts() { return nverts; }
  void setNumVerts(unsigned long n) { nverts=n; }
  //
  void setDrawVerts(int *dv) { drawVerts=dv; }
  int *getDrawVerts() { return drawVerts; }
  //
  void setCurAnimFrame(unsigned long num) { m->setCurAnimFrame(num); }
  unsigned long getCurAnimFrame() { return m->getCurAnimFrame(); }
  //
protected:
  //
  void init();
  //
  AMesh3D *m;
  //
  int *drawVerts;
  unsigned long nverts;
  //
  float x,y,z;
  float rx,ry,rz;
  //
};


#endif // NICK_USE_NICK3D


#endif // NICK3D_ATHING3D_H
