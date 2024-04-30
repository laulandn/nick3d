#ifndef NICK3D_AFACE3D_H
#define NICK3D_AFACE3D_H


#ifdef NICK_USE_NICK3D


class AFace3D
{
public:
  AFace3D();
  //
  unsigned long a,b,c;
};


class AFaceInfo3D
{
public:
  AFaceInfo3D();
  //
  unsigned long surf;
  float fRed,fGreen,fBlue;
  unsigned long textID;
};


#endif // NICK_USE_NICK3D


#endif // NICK3D_AFACE3D_H

