#ifndef NICK3D_ATEXTURE3D_H
#define NICK3D_ATEXTURE3D_H


#ifdef NICK_USE_NICK3D


class ABitmap;


class ATexture3D
{
public:
  ATexture3D(char *fname);
  ATexture3D(unsigned long w,unsigned long h,unsigned long d,unsigned long np);
  ABitmap *getBitmap() { return bm; }
  void *getBinding() { return boundTexture; }  // Actually just an arbitrary whatever you want...
  void setBinding(void *b) { boundTexture=b; }  // Actually just an arbitrary whatever you want...
protected:
  //
  void init();
  //
  ABitmap *bm;
  void *boundTexture;
};


#endif // NICK_USE_NICK3D


#endif // NICK3D_ATEXTURE3D_H

