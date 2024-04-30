#ifndef NICK3D_ASHAPE3D_H
#define NICK3D_ASHAPE3D_H


#ifdef NICK_USE_NICK3D


#include "../cpp/alib/ageometry_alib.h"


class AVertex3Dlws;
class ALine3D;


class AShape3D : public AGeometric3d_alib
{
public:
  AShape3D();
  AShape3D(unsigned long numVert, unsigned long numLine,AVertex3Dlws *vert, ALine3D *line);
  virtual ~AShape3D();
  void transform(const ATMatrix<ACoord3dType_alib> *mat);
  void project(int distance);
//protected:
  unsigned long numVertices;
  unsigned long numLines;
  AVertex3Dlws *vertices;
  ALine3D *lines;
};


class AShapeExtruded3D : public AShape3D
{
public:
  AShapeExtruded3D(unsigned long numVert,
    unsigned long numLine, AVertex3Dlws *vert, ALine3D *line);
};


#endif // NICK_USE_NICK3D


#endif // NICK3D_ASHAPE3D_H

