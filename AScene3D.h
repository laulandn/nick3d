#ifndef NICK3D_ASCENE3D_H
#define NICK3D_ASCENE3D_H


#ifdef NICK_USE_NICK3D


#include "AVertex3D.h"
#include "AFace3D.h"
#include "AVertex3D.h"
#include "AMesh3D.h"
#include "ACamera3D.h"
#include "ALight3D.h"


#define ASCENE3D_SKY_RED (0.0F/255.0F)
#define ASCENE3D_SKY_GREEN (166.0F/255.0F)
#define ASCENE3D_SKY_BLUE (227.0F/255.0F)

#define ASCENE3D_GROUND_RED (0.0F/255.0F)
#define ASCENE3D_GROUND_GREEN (166.0F/255.0F)
#define ASCENE3D_GROUND_BLUE (0.0F/255.0F)


class AScene3D
{
public:
  AScene3D();
  virtual ~AScene3D();
  //
  bool addMesh(AMesh3D *theMesh);
  //
  AMesh3D **getMeshes() { return meshes; }
  unsigned long getNumMeshes() { return nmeshes; }
  ALight3D **getLights() { return lights; }
  unsigned long getNumLights() { return nlights; }
  ACamera3D *getCamera(unsigned long n) { if(!cameras) createDefaultCamera(); return cameras[0]; }
  ACamera3D **getCameras() { return cameras; }
  unsigned long getNumCameras() { return ncameras; }
  AMesh3D *getTheGround() { return theGround; }
  AFaceInfo3D *getTheSky() { return &theSky; }
  AVertexF3D *getBMin() { return &bmin; }
  AVertexF3D *getBMax() { return &bmax; }
  float getXWidth() { return xwidth; }
  float getYWidth() { return ywidth; }
  float getZWidth() { return zwidth; }
  char *getName() { return name; }
  //
  //  **** WARNING These functions are temporary and can break the obj state!
  void setMeshes(AMesh3D **m) { meshes=m; }
  void setNumMeshes(unsigned long n) { nmeshes=n; }
  void setLights(ALight3D **l) { lights=l; }
  void setNumLights(unsigned long n) { nlights=n; }
  void setCameras(ACamera3D **c) { cameras=c; }
  void setNumCameras(unsigned long n) { ncameras=n; }
  //
  virtual void resizeToFit(AMesh3D *thing);
  virtual void resizeToFit(ACamera3D *thing);
  virtual void resizeToFit(ALight3D *thing);
  virtual void calcWidths();
  virtual void calcBoundingBox();
  //
  virtual void debugDump();
protected:
  void init();
  //void createGroundMesh(AFace3D *gf);
  void createDefaultCamera();
  //void scaleAllMeshesDown();
  //void scaleAllCamerasDown();
  //void scaleAllLightsDown();

  //
  unsigned long nmeshes,ncameras,nlights;
  AMesh3D **meshes;
  AList_alib *meshList;
  ACamera3D **cameras;
  AList_alib *cameraList;
  ALight3D **lights;
  AList_alib *lightList;
  //
  AVertexF3D bmin,bmax;
  float xwidth,ywidth,zwidth;
  //float theScaleFactor;
  AMesh3D *theGround;  // watch out, may be null
  AFaceInfo3D theSky;  // for the color only
  char *name;
};


#endif // NICK_USE_NICK3D


#endif // NICK3D_ASCENE3D_H

