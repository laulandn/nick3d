#ifndef NICK3D_AMESHPART3D_H
#define NICK3D_AMESHPART3D_H


#ifdef NICK_USE_NICK3D


class AMeshPart3D
{
public:
  AMeshPart3D();
  //
  char *name;
  unsigned long startVert,endVert;
  unsigned long startFace,endFace;
protected:
};


#endif // NICK_USE_NICK3D


#endif // NICK3D_AMESHPART3D_H

