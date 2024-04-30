#ifndef NICK3D_AWORLD3D_H
#define NICK3D_AWORLD3D_H


#ifdef NICK_USE_NICK3D


//#include "AScene3D.h"
//#include "AThing3D.h"


class AScene3D;
class ACamera3D;
class AThing3D;

class AWindow;


class AWorld3D
{
public:
  //
  AWorld3D(AScene3D *theScene);
  virtual ~AWorld3D();
  //
  AScene3D *getScene() { return s; }
  ACamera3D *getCurCamera() { return c; }
  unsigned long getXWidth();
  unsigned long getYWidth();
  unsigned long getZWidth();
  unsigned long getNumThings() { return numThings; }
  AThing3D **getThings() { return things; }
  //
  void setScaling(float sx,float sy);
  void setDimesions(unsigned long w,unsigned long h);
  //
  void prepareForRendering();
  void render(AWindow *win);
  //
  void debugDump();
  //
protected:
  //
  void init();
  //
  AScene3D *s;
  ACamera3D *c;
  unsigned long numThings;
  AThing3D **things;
  //
  float xScale,yScale;
  unsigned long actualWidth,actualHeight;
};


#endif // NICK_USE_NICK3D


#endif // NICK3D_AWORLD3D_H
