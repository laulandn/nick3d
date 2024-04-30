#ifndef NICK3D_AMESH3D_H
#define NICK3D_AMESH3D_H


#ifdef NICK_USE_NICK3D


#include "AMatrix3D.h"
#include "AVertex3D.h"
#include "AMeshPart3D.h"
#include "ATexture3D.h"
#include "ATextCoord3D.h"
#include "AFace3D.h"
#include "ACamera3D.h"


class AList_alib;


class ADrawableMesh3D
{
public:
  ADrawableMesh3D();
  //
  unsigned long getNumVerts() { return nverts; }
  void setNumVerts(unsigned long n) { nverts=n; }
  //
  // These are in the format of x y x y etc (I think)
  void setDrawVerts(int *dv) { drawVerts=dv; }
  int *getDrawVerts() { return drawVerts; }
  //
protected:
  //
  void init();
  //
  int *drawVerts;
  unsigned long nverts;
  //
};


class AMesh3D
{
public:
  AMesh3D();
  AMesh3D(unsigned long tnVerts,float *tVerts,unsigned long tnFaces,short *tFaces);
  AMesh3D(unsigned long tnVerts,AVertexF3D **tVerts,unsigned long tnFaces,AFace3D **tFaces);
  AMesh3D(AFace3D *f,AFaceInfo3D *fi,AVertexF3D a,AVertexF3D b,AVertexF3D c,AVertexF3D d);
  virtual ~AMesh3D();
  //
  // An array of pointers to APart3D objects...
  AMeshPart3D **getParts() { return parts; }
  unsigned long getNumParts() { return nparts; }
  //
  // An array of arrays of AVertexF3D objects...
  // These are in the format of x y z x y z etc
  float **getVerts() { return verts; }
  // An array of AVertexI3D objects...
  unsigned long getNumVerts() { return nverts; }
  //
  // An array of AVertexF3D objects...
  AVertexF3D *getVertNormals() { return vertNormals; }
  // An array of AVertexF3D objects...
  AVertexF3D *getFaceNormals() { return faceNormals; }
  //
  // An array of ATextCoord3D objects...
  // These are in the format of u v u v etc
  float *getTextCoords() { return textCoords; }
  unsigned long getNumTextCoords() { return ntextcoords; }
  // An array of pointers to ATexture3D objects...
  ATexture3D **getTextures() { return textures; }
  unsigned long getNumTextures() { return ntextures; }
  //
  // An array of pointers to AFace3D objects...
  // These are in the format a b c a b c etc
  unsigned short *getFaces() { return faces; }
  AFaceInfo3D **getFaceInfos() { return faceInfos; }
  //
  // An array of pointers to AFace3D objects...
  //AFace3D **getFaceTextCoords() { return faceTextCoords; }
  unsigned short *getFaceTextCoords() { return faceTextCoords; }
  unsigned long getNumFaces() { return nfaces; }
  //
  ADrawableMesh3D *getDrawableMesh() { return &drawableMesh; }
  //
  // WARNING WARNING WARNING
  // These are only meant to be used internally
  // when building the object from raw parts!
  void setParts(AMeshPart3D **p) { parts=p; }
  void setNumParts(unsigned long n) { nparts=n; }
  void setFaces(unsigned short *f) { faces=f; }
  void setFaceInfos(AFaceInfo3D **fi) { faceInfos=fi; }
  //void setFaceTextCoords(AFace3D **f) { faceTextCoords=f; }
  void setFaceTextCoords(unsigned short *f) { faceTextCoords=f; }
  void setTextCoords(float *tc) { textCoords=tc; }
  void setNumFaces(unsigned long n) { nfaces=n; }
  //void setNumFaceTextCoords(unsigned long n) { nftcs=n; }
  void setNumFrames(unsigned long n) { numFrames=n; }
  void setNumTextCoords(unsigned long n) { ntextcoords=n; }
  //void addFace(AFace3D *f);
  //
  // For now we use AList_alib...
  // WARNING These are only meant to be used internally when building the object from raw parts!
  void createVertsPerFrame(unsigned long frame,AList_alib *theVerts,unsigned long numVerts);
  void createVertNormals(AList_alib *theVerts,unsigned long numVerts);
  //void createTextCoords(AList_alib *theCoords,unsigned long numtcs);
  void createTextures(AList_alib *theTextures,unsigned long numTextures);
  //
  void buildFTCsFromTCs();
  void allocVertParts(unsigned long tNumFrames,unsigned long whichFrame,unsigned long tNumVerts);
  //
  void setName(char *n) { name=n; }
  char *getName() { return name; }
  //AMatrix3D *getModelToDrawMatrix() { return &modelToDrawMatrix; }
  AVertexF3D *getBMin() { return &bmin; }
  AVertexF3D *getBMax() { return &bmax; }
  float getXWidth() { return xwidth; }
  float getYWidth() { return ywidth; }
  float getZWidth() { return zwidth; }
  bool isStale() { return stale; }
  void setStale(bool t) { stale=t; }
  //
  void unit();
  void scale(float sx,float sy,float sz);
  void translate(float sx,float sy,float sz);
  //
  void scaleAllVerts(float sx,float sy,float sz);
  void translateAllVerts(float sx,float sy,float sz);
  void rotateXAllVerts(float r);
  void rotateYAllVerts(float r);
  void rotateZAllVerts(float r);
  //float normalizeScale();  // returns value it scaled by
  //void normalizeTranslation();
  //
  void transformVertsToDraw();
  void transCamModelToDrawMatrix(ACamera3D *c);
  virtual void calcWidths();
  virtual void calcBoundingBox();
  //
  unsigned long getNumAnimSeq() { return numSeq; }
  void setCurAnimSequence(unsigned long num) { curSeqNum=num;  if(curSeqNum==numSeq)  curSeqNum=0;  }
  unsigned long getCurAnimSequence() { return curSeqNum; }
  unsigned long getNumAnimFrames() { return numFrames; }
  void setCurAnimFrame(unsigned long num) { curFrameNum=num;  if(curFrameNum==numFrames) curFrameNum=0; }
  unsigned long getCurAnimFrame() { return curFrameNum; }
  //
  void setCurTexture(unsigned long num) { curTextNum=num;  if(curTextNum==ntextures) curTextNum=0; }
  unsigned long getCurTexture() { return curTextNum; }
  void setFixTextCoords(bool t) { fixTextCoords=t; }
  //
  virtual void debugDump();
  bool isValid();
  //
protected:
  //
  void init();
  //
  AVertexF3D bmin,bmax;
  float xwidth,ywidth,zwidth;
  //
  bool fixTextCoords;
  unsigned long nparts;
  unsigned long curFrameNum,curSeqNum,curTextNum;
  unsigned long nverts;
  unsigned long nfaces,ntextures,ntextcoords;
  unsigned long numSeq,numFrames;
  //unsigned long nftcs;  // should always equal nfaces
  //
  AMeshPart3D **parts;
  //AList_alib *partList;
  unsigned short *faces;
  AFaceInfo3D **faceInfos;
  //AFace3D **faceTextCoords;  // same as num of faces
  unsigned short *faceTextCoords;
  //AList_alib *faceTextCoordList;
  //
  float **verts;
  //
  AVertexF3D *vertNormals;  // same as num of verts
  AVertexF3D *faceNormals;  // same as num of faces
  float *textCoords;
  ATexture3D **textures;
  //
  ADrawableMesh3D drawableMesh;
  AMatrix3D modelToDrawMatrix;
  char *name;
  bool stale;
};


#endif // NICK_USE_NICK3D


#endif // NICK3D_AMESH3D_H

