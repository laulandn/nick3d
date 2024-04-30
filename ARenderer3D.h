#ifndef NICK3D_ARENDERER3D_H
#define NICK3D_ARENDERER3D_H


#ifdef NICK_USE_NICK3D


#include "../cpp/alib/ageometry_alib.h"


class AWindow;
class AShape3D;


class ARenderer3D : public ABaseClass
{
public:
  ARenderer3D(AWindow *win);
  virtual void draw(AShape3D *shape);
protected:
  virtual void init();
  AWindow *window;
};


class AWireframeRenderer3D : public ARenderer3D
{
public:
  AWireframeRenderer3D(AWindow *win);
  virtual void draw(AShape3D* shape);
protected:
};


#endif // NICK_USE_NICK3D


#endif // NICK3D_ARENDERER3D_H

