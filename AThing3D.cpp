
#define DEBUG_OUT std::cerr
//#define DEBUG_OUT *aNullStream


#ifdef DEBUG_VERBOSE
#undef DEBUG_VERBOSE
#endif


#ifdef NICK_USE_NICK3D


#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "../cpp/alib/anullstream.h"

#include "AThing3D.h"


////////////////////////////////////////////////////////////////////////////////
//  AThing3D Class
////////////////////////////////////////////////////////////////////////////////


AThing3D::AThing3D(AMesh3D *theMesh)
{
  DEBUG_OUT<<"AThing3D::AThing3D()\n";
  init();
  m=theMesh;
  if(!m) { std::cerr<<"No mesh for AThing3D!\n"; exit(EXIT_FAILURE); }
}


AThing3D::~AThing3D()
{
  if(m) delete m;
  m=NULL;
}


void AThing3D::init()
{
  m=NULL;
  nverts=0;
  drawVerts=NULL;
  //
  x=0.0;  y=0.0;  z=0.0;
  rx=0.0;  ry=0.0;  rz=0.0;
}


#endif // NICK_USE_NICK3D

