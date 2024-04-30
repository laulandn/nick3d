
#define DEBUG_OUT std::cerr
//#define DEBUG_OUT std::cerr
//#define DEBUG_OUT *aNullStream
//#define CONS_OUT std::cout
#define CONS_IN std::cin


#ifdef DEBUG_VERBOSE
#undef DEBUG_VERBOSE
#endif


#ifdef NICK_USE_NICK3D


#include "AMatrix3D.h"
#include "AShape3D.h"
#include "AVertex3D.h"
#include "ALine3D.h"


////////////////////////////////////////////////////////////////////////////////
//  AShape3D Class
////////////////////////////////////////////////////////////////////////////////

AShape3D::AShape3D()
{
  numVertices = 0;
  numLines = 0;
  vertices = 0;
  lines = 0;
}


AShape3D::AShape3D(unsigned long numVert, unsigned long numLine,
  AVertex3Dlws *vert, ALine3D *line)
{
  numVertices = numVert;
  numLines = numLine;
  vertices = vert;
  lines = line;
}


AShape3D::~AShape3D()
{
  if(vertices) delete [] vertices;
  vertices=(AVertex3Dlws *)NULL;
  if(lines) delete [] lines;
  lines=(ALine3D *)NULL;
}


void AShape3D::transform(const ATMatrix<ACoord3dType_alib> *mat)
{
  for (unsigned long v=0; v<numVertices; v++)
  {
    AVertex3Dlws *vptr = &vertices[v];
    // Converts floats to ints here...
    vptr->wx = vptr->lx*mat->getElement(0,0)+vptr->ly*mat->getElement(1,0)+vptr->lz*mat->getElement(2,0)+mat->getElement(3,0);
    vptr->wy = vptr->lx*mat->getElement(0,1)+vptr->ly*mat->getElement(1,1)+vptr->lz*mat->getElement(2,1)+mat->getElement(3,1);
    vptr->wz = vptr->lx*mat->getElement(0,2)+vptr->ly*mat->getElement(1,2)+vptr->lz*mat->getElement(2,2)+mat->getElement(3,2);
  }
}


void AShape3D::project(int distance)
{
  for (unsigned long v=0; v<numVertices; v++)
  {
    AVertex3Dlws *vptr = &vertices[v];

    // BUG: Doesn't work when vptr->wz is 0
    if (vptr->wz)
    {
      vptr->sx = distance * vptr->wx / vptr->wz;
      vptr->sy = distance * vptr->wy / vptr->wz;
    }
  else {
      vptr->sx = 0;
      vptr->sy = 0;
  }
  }
}


////////////////////////////////////////////////////////////////////////////////
//  AShapeExtruded3D Class
////////////////////////////////////////////////////////////////////////////////

AShapeExtruded3D::AShapeExtruded3D(unsigned long numVert, unsigned long numLine, AVertex3Dlws *vert, ALine3D *line)
{
  numVertices = numVert * 2;
  numLines = numLine * 2 + numVert;
  vertices = new AVertex3Dlws[numVertices];
  lines = new ALine3D[numLines];
  unsigned long i;
  for (i=0; i<numVert; i++)
  {
    vertices[i] = vert[i];
    vertices[i+numVert] = vert[i];
    vertices[i+numVert].lz = vert[i].lz + 2;
  }
  for (i=0; i<numLine; i++)
  {
    lines[i] = line[i];
    lines[i+numLine].start = line[i].start + numVert;
    lines[i+numLine].end   = line[i].end   + numVert;
    lines[i+numLine].color   = line[i].color;
  }
  for (i=0; i<numVert; i++)
  {
    lines[numLine*2+i].start = i;
    lines[numLine*2+i].end   = i+numVert;
    lines[numLine*2+i].color=lines[i].color;
  }
}


#endif // NICK_USE_NICK3D

