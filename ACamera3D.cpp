
#define DEBUG_OUT std::cerr
//#define DEBUG_OUT *aNullStream


#ifdef DEBUG_VERBOSE
#undef DEBUG_VERBOSE
#endif


#ifdef NICK_USE_NICK3D


#include "ACamera3D.h"

#include "../cpp/alib/anullstream.h"


////////////////////////////////////////////////////////////////////////////////
//  ACamera3D Class
////////////////////////////////////////////////////////////////////////////////

ACamera3D::ACamera3D()
{
  DEBUG_OUT<<"ACamera3D created!\n";
  init();
}


ACamera3D::ACamera3D(float nx,float ny,float nz,float sa, float sb, float sc)
{
  DEBUG_OUT<<"ACamera3D created!\n";
  init();
  trans.translateTo(nx,ny,nz);
  // NOTE: Order is important!
  trans.xRotBy(sa);
  trans.yRotBy(sb);
  trans.zRotBy(sc);
}


void ACamera3D::init()
{
  trans.unit();
}


void ACamera3D::unit()
{
  trans.unit();
}


void ACamera3D::transform(ACamera3D *m)
{
  trans.mult(&m->trans);
}


void ACamera3D::transform(AMatrix3D *m)
{
  trans.mult(m);
}


void ACamera3D::transThisMatrix(AMatrix3D *m)
{
  m->mult(&trans);
}


void ACamera3D::scale(float nx, float ny, float nz)
{
  AMatrix3D m;
  m.scale(nx,ny,nz);
  trans.mult(&m);
}


void ACamera3D::translate(float sx, float sy, float sz)
{
  AMatrix3D m;
  m.translate(sx,sy,sz);
  trans.mult(&m);
}


void ACamera3D::translateTo(float sx, float sy, float sz)
{
  AMatrix3D m;
  m.translateTo(sx,sy,sz);
  trans.mult(&m);
}


void ACamera3D::xRotBy(float theta)
{
  AMatrix3D m;
  m.xRotBy(theta);
  trans.mult(&m);
}


void ACamera3D::yRotBy(float theta)
{
  AMatrix3D m;
  m.yRotBy(theta);
  trans.mult(&m);
}


void ACamera3D::zRotBy(float theta)
{
  AMatrix3D m;
  m.zRotBy(theta);
  trans.mult(&m);
}


void ACamera3D::debugDump()
{
  DEBUG_OUT<<"ACamera3D::debugDump() nothing yet...\n";
  //DEBUG_OUT<<"ACamera3D: x=("<<bmin.x<<","<<bmax.x<<") y=("<<bmin.y<<","<<bmax.y<<") z=("<<bmin.z<<","<<bmax.z<<")\n";
  // TODO: more here...
}


#endif // NICK_USE_NICK3D

