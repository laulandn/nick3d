
#define DEBUG_OUT std::cerr
//#define DEBUG_OUT *aNullStream


#ifdef DEBUG_VERBOSE
#undef DEBUG_VERBOSE
#endif


#ifdef NICK_USE_NICK3D


#include <stdlib.h>
#include <iostream>

#include "../cpp/alib/abasics.h"
#include "../cpp/alib/anullstream.h"

#include "AMesh3D.h"

// For now we use AList_alib...
#include "../cpp/alib/abasics.h"


////////////////////////////////////////////////////////////////////////////////
//  ADrawableMesh3D Class
////////////////////////////////////////////////////////////////////////////////


ADrawableMesh3D::ADrawableMesh3D()
{
  DEBUG_OUT<<"ADrawableMesh3D::ADrawableMesh3D()\n";
  init();
}


void ADrawableMesh3D::init()
{
  nverts=0;
  drawVerts=NULL;
}


////////////////////////////////////////////////////////////////////////////////
//  AMesh3D Class
////////////////////////////////////////////////////////////////////////////////

AMesh3D::AMesh3D()
{
  DEBUG_OUT<<"AMesh3D::AMesh3D()\n";
  init();
}


AMesh3D::AMesh3D(AFace3D *f,AFaceInfo3D *fi,AVertexF3D a,AVertexF3D b,AVertexF3D c,AVertexF3D d)
{
  DEBUG_OUT<<"AMesh3D::AMesh3D(f,fi,a,b,c,d)\n";
  init();
  allocVertParts(1,0,4);
  verts[0][0*3]=a.x; verts[0][0*3+1]=a.y; verts[0][0*3+2]=a.z;
  verts[0][1*3]=b.x; verts[0][1*3+1]=b.y; verts[0][1*3+2]=b.z;
  verts[0][2*3]=c.x; verts[0][2*3+1]=c.y; verts[0][2*3+2]=c.z;
  verts[0][3*3]=d.x; verts[0][3*3+1]=d.y; verts[0][3*3+2]=d.z;
  DEBUG_OUT<<a.x<<","<<a.y<<","<<a.z<<"\n";
  DEBUG_OUT<<b.x<<","<<b.y<<","<<b.z<<"\n";
  DEBUG_OUT<<c.x<<","<<c.y<<","<<c.z<<"\n";
  DEBUG_OUT<<d.x<<","<<d.y<<","<<d.z<<"\n";
  nfaces=2;
  faces=(unsigned short *)calloc(nfaces*3,sizeof(unsigned short));
  if(!faces) { std::cerr<<"Couldn't get faces!"; exit(EXIT_FAILURE); }
  faces[0]=3; faces[1]=0; faces[2]=1;
  faces[3]=2; faces[4]=1; faces[5]=3;
  faceInfos=(AFaceInfo3D **)calloc(nfaces,sizeof(AFaceInfo3D *));
  if(!faceInfos) { std::cerr<<"Couldn't get faceInfos!"; exit(EXIT_FAILURE); }
  faceInfos[0]=(AFaceInfo3D *)malloc(sizeof(AFaceInfo3D));
  faceInfos[0]->surf=fi->surf; faceInfos[0]->fRed=fi->fRed; faceInfos[0]->fGreen=fi->fGreen; faceInfos[0]->fBlue=fi->fBlue;
  faceInfos[1]=(AFaceInfo3D *)malloc(sizeof(AFaceInfo3D));
  faceInfos[1]->surf=fi->surf; faceInfos[1]->fRed=fi->fRed; faceInfos[1]->fGreen=fi->fGreen; faceInfos[1]->fBlue=fi->fBlue;
  calcWidths();
  isValid();
}


AMesh3D::AMesh3D(unsigned long tnVerts,float *tVerts,unsigned long tnFaces,short *tFaces)
{
  DEBUG_OUT<<"AMesh3D::AMesh3D("<<tnVerts<<",tVerts,"<<tnFaces<<",tFaces)\n";
  init();
  DEBUG_OUT<<"Building faces...\n";
  faces=(unsigned short *)calloc(tnFaces*3,sizeof(unsigned short));
  faceInfos=(AFaceInfo3D **)calloc(tnFaces,sizeof(faceInfos));
  setNumFaces(tnFaces);
  AFaceInfo3D *fi;
  for(unsigned long t=0;t<tnFaces;t++) {
    //DEBUG_OUT<<tFaces[t*3]<<","<<tFaces[t*3+1]<<","<<tFaces[t*3+2]<<"\n";
    faces[t*3]=tFaces[t*3];
    faces[t*3+1]=tFaces[t*3+1];
    faces[t*3+2]=tFaces[t*3+2];
    fi=new AFaceInfo3D;
    faceInfos[t]=fi;
    //DEBUG_OUT<<faces[t]->a<<","<<faces[t]->b<<","<<faces[t]->c<<"\n";
  }
  //
  DEBUG_OUT<<"Building frames/verts...\n";
  setNumFrames(1);
  allocVertParts(numFrames,0,tnVerts);
  nverts=tnVerts;
  float x,y,z;
  for(unsigned long t=0;t<tnVerts;t++) {
    x=tVerts[t*3];
    y=tVerts[t*3+1];
    z=tVerts[t*3+2];
    //DEBUG_OUT<<tVerts[t*3]<<","<<tVerts[t*3+1]<<","<<tVerts[t*3+2]<<"\n";
    //DEBUG_OUT<<x<<","<<y<<","<<z<<"\n";
    verts[0][t*3]=x;
    verts[0][t*3+1]=y;
    verts[0][t*3+2]=z;
    //DEBUG_OUT<<verts[0][t].x<<","<<verts[0][t].y<<","<<verts[0][t].z<<"\n";
  }
  calcWidths();
  isValid();
}


AMesh3D::AMesh3D(unsigned long tnVerts,AVertexF3D **tVerts,unsigned long tnFaces,AFace3D **tFaces)
{
 DEBUG_OUT<<"AMesh3D::AMesh3D("<<tnVerts<<",tVerts,"<<tnFaces<<",tFaces)\n";
  init();
  DEBUG_OUT<<"Building faces...\n";
  faces=(unsigned short *)calloc(tnFaces*3,sizeof(unsigned short));
  faceInfos=(AFaceInfo3D **)calloc(tnFaces,sizeof(faceInfos));
  setNumFaces(tnFaces);
  AFaceInfo3D *fi;
  for(unsigned long t=0;t<tnFaces;t++) {
    //DEBUG_OUT<<tFaces[t*3]<<","<<tFaces[t*3+1]<<","<<tFaces[t*3+2]<<"\n";
    faces[t*3]=tFaces[t]->a;
    faces[t*3+1]=tFaces[t]->b;
    faces[t*3+2]=tFaces[t]->c;
    //f=(AFace3D *)calloc(sizeof(AFace3D),1);
    fi=new AFaceInfo3D();
    faceInfos[t]=fi;
    //DEBUG_OUT<<faces[t]->a<<","<<faces[t]->b<<","<<faces[t]->c<<"\n";
  }
  //
  DEBUG_OUT<<"Building frames/verts...\n";
  setNumFrames(1);
  allocVertParts(numFrames,0,tnVerts);
  nverts=tnVerts;
  float x,y,z;
  for(unsigned long t=0;t<tnVerts;t++) {
    x=tVerts[t]->x;
    y=tVerts[t]->y;
    z=tVerts[t]->z;
    //DEBUG_OUT<<tVerts[t*3]<<","<<tVerts[t*3+1]<<","<<tVerts[t*3+2]<<"\n";
    //DEBUG_OUT<<x<<","<<y<<","<<z<<"\n";
    verts[0][t*3]=x;
    verts[0][t*3+1]=y;
    verts[0][t*3+2]=z;
    //DEBUG_OUT<<verts[0][t].x<<","<<verts[0][t].y<<","<<verts[0][t].z<<"\n";
  }
  calcWidths();
  isValid();
}


AMesh3D::~AMesh3D()
{
  DEBUG_OUT<<"AMesh3D Destroyed.\n";
}


void AMesh3D::init()
{
  bmin.x=0.0;  bmax.x=0.0;  bmin.y=0.0;  bmax.y=0.0;  bmin.z=0.0;  bmax.z=0.0;
  nparts=0;  parts=NULL;  //partList=NULL;
  nfaces=0;  faces=NULL;  faceInfos=NULL;
  ntextcoords=0;  faceTextCoords=NULL;  //faceTextCoordList=NULL;
  //nftcs=0;
  nverts=0;
  ntextures=0;
  curFrameNum=0;  curSeqNum=0;  curTextNum=0;
  numFrames=1;  numSeq=1;
  verts=NULL;
  vertNormals=NULL;  faceNormals=NULL;
  textCoords=NULL; textures=NULL;
  fixTextCoords=false;
  name=NULL;
  modelToDrawMatrix.unit();
  stale=true;
}


// For now we use AList_alib...
// Assumes you'll createVerts once and only once per frame
void AMesh3D::createVertsPerFrame(unsigned long frame,AList_alib *theVerts,unsigned long numVerts)
{
  if(!numVerts) return;
  if(!theVerts) return;
  //DEBUG_OUT<<"createVertsPerFrame("<<frame<<")...\n";
  //DEBUG_OUT<<"numVerts is "<<numVerts<<" numFrames is "<<numFrames<<"\n";
  allocVertParts(numFrames,frame,numVerts);
  unsigned long t=0;
  theVerts->jumpToHead();
  while(!theVerts->atEnd()) {
    AVertexF3D *thing=(AVertexF3D *)theVerts->info();
    //DEBUG_OUT<<"vert: "<<t<<" "<<thing->x<<","<<thing->y<<","<<thing->z<<"\n";
    verts[frame][t*3]=thing->x;
    verts[frame][t*3+1]=thing->y;
    verts[frame][t*3+2]=thing->z;
    theVerts->advance();
    t++;
  }
  nverts=t;
  //DEBUG_OUT<<"Added "<<t<<" verts.\n";
}


// For now we use AList_alib...
// NOTE: These aren't used yet...
void AMesh3D::createVertNormals(AList_alib *theVerts,unsigned long numVerts)
{
  if(!numVerts) return;
  if(!theVerts) return;
  DEBUG_OUT<<"createVertNormals...\n";
  vertNormals=(AVertexF3D *)calloc(numVerts,sizeof(AVertexF3D));
  if(!vertNormals) return;
  unsigned long t=0;
  theVerts->jumpToHead();
  while(!theVerts->atEnd()) {
    AVertexF3D *thing=(AVertexF3D *)theVerts->info();
    //DEBUG_OUT<<"vertNorm: "<<t<<" "<<thing->x<<","<<thing->y<<","<<thing->z<<"\n";
    if(t<nverts) {
      vertNormals[t].x=thing->x;
      vertNormals[t].y=thing->y;
      vertNormals[t].z=thing->z;
      t++;
    }
    //else DEBUG_OUT<<"(skipped)\n";
    theVerts->advance();
  }
  DEBUG_OUT<<"Added "<<t<<" vertnormals.\n";
}


// For now we use AList_alib...
void AMesh3D::createTextures(AList_alib *theTextures,unsigned long numTextures)
{
  if(!numTextures) return;
  if(!theTextures) return;
  DEBUG_OUT<<"createTextures...\n";
  textures=(ATexture3D **)calloc(numTextures,sizeof(ATexture3D *));
  if(!textures) return;
  unsigned long t=0;
  theTextures->jumpToHead();
  while(!theTextures->atEnd()) {
    ATexture3D *thing=(ATexture3D *)theTextures->info();
    //DEBUG_OUT<<"tc: "<<t<<" "<<thing->x<<","<<thing->y<<"\n";
    textures[t]=thing;
    theTextures->advance();
    t++;
  }
  ntextures=t;
  DEBUG_OUT<<"Added "<<t<<" textures.\n";
}


// If we have textCoords, but not faceTextCoords, then synthesize them
// NOTE: This isn't really correct, just a guess for now
void AMesh3D::buildFTCsFromTCs()
{
  DEBUG_OUT<<"buildFTCsFromTCs...\n";
  unsigned long tx,ty,tz;
  //faceTextCoords=(AFace3D **)malloc(sizeof(AFace3D *)*nfaces);
  faceTextCoords=(unsigned short *)malloc(sizeof(unsigned short)*3*nfaces);
  for(unsigned long i=0;i<nfaces;i++) {
    tx=faces[i*3];
    ty=faces[i*3+1];
    tz=faces[i*3+2];
    /*
    tx=faces[i]->a;
    ty=faces[i]->b;
    tz=faces[i]->c;
    */
    //DEBUG_OUT<<"ftc "<<i<<": "<<tx<<","<<ty<<","<<tz<<"\n";
    /*
    faceTextCoords[i]=(AFace3D *)malloc(sizeof(AFace3D));
    faceTextCoords[i]->a=tx;
    faceTextCoords[i]->b=ty;
    faceTextCoords[i]->c=tz;
    */
    faceTextCoords[i*3]=tx;
    faceTextCoords[i*3+1]=ty;
    faceTextCoords[i*3+2]=tz;
  }
}


/*
void AMesh3D::addFace(AFace3D *f)
{
  DEBUG_OUT<<"addFace...\n";
  std::cerr<<"AMesh3D::addFace not implemented yet!\n";
  exit(EXIT_FAILURE);
}
*/


void AMesh3D::calcBoundingBox()
{
  bmin.x=0.0;  bmax.x=0.0;  bmin.y=0.0;  bmax.y=0.0;  bmin.z=0.0;  bmax.z=0.0;
  for(unsigned long t=0;t<nverts;t++) {
    float dudex=verts[curFrameNum][t*3];
    float dudey=verts[curFrameNum][t*3+1];
    float dudez=verts[curFrameNum][t*3+2];
    if(bmin.x>(dudex)) bmin.x=dudex;
    if(bmax.x<(dudex)) bmax.x=dudex;
    if(bmin.y>(dudey)) bmin.y=dudey;
    if(bmax.y<(dudey)) bmax.y=dudey;
    if(bmin.z>(dudez)) bmin.z=dudez;
    if(bmax.z<(dudez)) bmax.z=dudez;
  }
  //debugDump();
}


void AMesh3D::calcWidths()
{
  calcBoundingBox();
  // Not really right, neg values are screwed, or are they?
  xwidth=bmax.x-bmin.x;
  ywidth=bmax.y-bmin.y;
  zwidth=bmax.z-bmin.z;
  //DEBUG_OUT<<"calcWidths: "<<xwidth<<","<<ywidth<<","<<zwidth<<"\n";
}


/*
// Scale model so size is 1.0,1.0,1.0
float AMesh3D::normalizeScale()
{
  calcWidths();
  float xfactor=(float)1.0/(float)xwidth;
  float yfactor=(float)1.0/(float)ywidth;
  float zfactor=(float)1.0/(float)zwidth;
  DEBUG_OUT<<"normalizeScale: "<<xfactor<<","<<yfactor<<","<<zfactor<<"\n";
  float theFactor=xfactor;
  if(yfactor<theFactor) theFactor=yfactor;
  if(zfactor<theFactor) theFactor=zfactor;
  scaleAllVerts(theFactor,theFactor,theFactor);
  calcWidths();
  //debugDump();
  return theFactor;
}
*/


/*
// Center model at 0,0,0
void AMesh3D::normalizeTranslation()
{
  calcWidths();
  float centerx=xwidth/2+bmin.x;
  float centery=ywidth/2+bmin.y;
  float centerz=zwidth/2+bmin.z;
  DEBUG_OUT<<"normalizeTranslation: "<<centerx<<","<<centery<<","<<centerz<<"\n";
  translateAllVerts(-centerx,-centery,-centerz);
  calcWidths();
  //debugDump();
}
*/


void AMesh3D::transformVertsToDraw()
{
  //DEBUG_OUT<<"transformToWorld...\n";
  if(!verts) { std::cerr<<"No verts!\n"; exit(EXIT_FAILURE); }
  if(!verts[curFrameNum]) { std::cerr<<"No verts[curFrameNum]!\n"; exit(EXIT_FAILURE); }
  if(!drawableMesh.getDrawVerts()) { std::cerr<<"No worldVerts!\n"; exit(EXIT_FAILURE); }
  modelToDrawMatrix.transformI(verts[curFrameNum],drawableMesh.getDrawVerts(),nverts);
  stale=false;
}


void AMesh3D::transCamModelToDrawMatrix(ACamera3D *c)
{
  c->transThisMatrix(&modelToDrawMatrix);
}


void AMesh3D::scaleAllVerts(float sx,float sy,float sz)
{
  DEBUG_OUT<<"scaleAllVerts: "<<sx<<","<<sy<<","<<sz<<"\n";
  for(unsigned long i=0;i<numFrames;i++) {
    for(unsigned long t=0;t<nverts;t++) {
      verts[i][t*3]=(float)verts[i][t*3]*sx;
      verts[i][t*3+1]=(float)verts[i][t*3+1]*sy;
      verts[i][t*3+2]=(float)verts[i][t*3+2]*sz;
    }
  }
  calcWidths();
  //debugDump();
}


void AMesh3D::translateAllVerts(float sx,float sy,float sz)
{
  DEBUG_OUT<<"translateAllVerts: "<<sx<<","<<sy<<","<<sz<<"\n";
  for(unsigned long i=0;i<numFrames;i++) {
    for(unsigned long t=0;t<nverts;t++) {
      verts[i][t*3]=verts[i][t*3]+sx;
      verts[i][t*3+1]=verts[i][t*3+1]+sy;
      verts[i][t*3+2]=verts[i][t*3+2]+sz;
    }
  }
  calcWidths();
  //debugDump();
}


void AMesh3D::rotateXAllVerts(float r)
{
  DEBUG_OUT<<"rotateXAllVerts: "<<r<<"\n";
  float tv[3];
  AMatrix3D m;
  m.xRotBy(r);
  for(unsigned long i=0;i<numFrames;i++) {
    for(unsigned long t=0;t<nverts;t++) {
      m.mult(&verts[curFrameNum][t*3],tv);
      verts[curFrameNum][t*3]=tv[0];
      verts[curFrameNum][t*3+1]=tv[1];
      verts[curFrameNum][t*3+2]=tv[2];
    }
  }
  calcWidths();
  //debugDump();
}


void AMesh3D::rotateYAllVerts(float r)
{
  DEBUG_OUT<<"rotateYAllVerts: "<<r<<"\n";
  float tv[3];
  AMatrix3D m;
  m.yRotBy(r);
  for(unsigned long i=0;i<numFrames;i++) {
    for(unsigned long t=0;t<nverts;t++) {
      m.mult(&verts[curFrameNum][t*3],tv);
      verts[curFrameNum][t*3]=tv[0];
      verts[curFrameNum][t*3+1]=tv[1];
      verts[curFrameNum][t*3+2]=tv[2];
    }
  }
  calcWidths();
  //debugDump();
}


void AMesh3D::rotateZAllVerts(float r)
{
  DEBUG_OUT<<"rotateZAllVerts: "<<r<<"\n";
  float tv[3];
  AMatrix3D m;
  m.zRotBy(r);
  for(unsigned long i=0;i<numFrames;i++) {
    for(unsigned long t=0;t<nverts;t++) {
      m.mult(&verts[curFrameNum][t*3],tv);
      verts[curFrameNum][t*3]=tv[0];
      verts[curFrameNum][t*3+1]=tv[1];
      verts[curFrameNum][t*3+2]=tv[2];
    }
  }
  calcWidths();
  //debugDump();
}


void AMesh3D::unit()
{
  modelToDrawMatrix.unit();
}


void AMesh3D::scale(float sx,float sy,float sz)
{
  //DEBUG_OUT<<"scale: "<<sx<<","<<sy<<","<<sz<<"\n";
  modelToDrawMatrix.scale(sx,sy,sz);
}


void AMesh3D::translate(float sx,float sy,float sz)
{
  //DEBUG_OUT<<"translate: "<<sx<<","<<sy<<","<<sz<<"\n";
  modelToDrawMatrix.translate(sx,sy,sz);
}


/*
void AMesh3D::translateTo(float sx,float sy,float sz)
{
  DEBUG_OUT<<"translateTo: "<<sx<<","<<sy<<","<<sz<<"\n";
  modelToDrawMatrix.translateTo(sx,sy,sz);
}
*/


/*
void AMesh3D::rotateBy(float sx,float sy,float sz)
{
  DEBUG_OUT<<"rotateBy: "<<sx<<","<<sy<<","<<sz<<"\n";
  rotateByX(sx);
  rotateByY(sy);
  rotateByZ(sz);
}
*/


/*
void AMesh3D::rotateByX(float r)
{
  modelToDrawMatrix.xRotBy(r);
}
*/


/*
void AMesh3D::rotateByY(float r)
{
  modelToDrawMatrix.yRotBy(r);
}
*/


/*
void AMesh3D::rotateByZ(float r)
{
  modelToDrawMatrix.zRotBy(r);
}
*/


void AMesh3D::debugDump()
{
  DEBUG_OUT<<"***\n";
  DEBUG_OUT<<"AMesh3D: bbox x=("<<bmin.x<<","<<bmax.x<<") y=("<<bmin.y<<","<<bmax.y<<") z=("<<bmin.z<<","<<bmax.z<<")\n";
  float tw=0.0,th=0.0,td=0.0;
  tw=bmax.x-bmin.x;
  th=bmax.y-bmin.y;
  td=bmax.z-bmin.z;
  DEBUG_OUT<<"tw="<<tw<<" th="<<th<<" td="<<td<<"\n";
  DEBUG_OUT<<"getNumParts: "<<getNumParts()<<"\n";
  DEBUG_OUT<<"getNumVerts: "<<getNumVerts()<<"\n";
  DEBUG_OUT<<"getVertNormals: "; if(getVertNormals()) DEBUG_OUT<<"yep\n"; else DEBUG_OUT<<"nope\n";
  DEBUG_OUT<<"getFaceNormals: "; if(getFaceNormals()) DEBUG_OUT<<"yep\n"; else DEBUG_OUT<<"nope\n";
  DEBUG_OUT<<"getNumTextCoords: "<<getNumTextCoords()<<"\n";
  DEBUG_OUT<<"getNumTextures: "<<getNumTextures()<<"\n";
  DEBUG_OUT<<"getNumFaces: "<<getNumFaces()<<"\n";
  DEBUG_OUT<<"getFaceInfos: "; if(getFaceInfos()) DEBUG_OUT<<"yep\n"; else DEBUG_OUT<<"nope\n";
  //DEBUG_OUT<<"getNumFaceTextCoords: "<<getNumFaceTextCoords()<<"\n";
  DEBUG_OUT<<"getFaceTextCoords: "; if(getFaceTextCoords()) DEBUG_OUT<<"yep\n"; else DEBUG_OUT<<"nope\n";
  DEBUG_OUT<<"getNumAnimSeq: "<<getNumAnimSeq()<<"\n";
  DEBUG_OUT<<"getNumAnimFrames: "<<getNumAnimFrames()<<"\n";
  DEBUG_OUT<<"***\n";
  /*
  DEBUG_OUT<<"Has "<<nverts<<" verts.\n";
  for(unsigned long t=0;t<nverts;t++) {
    DEBUG_OUT<<"v: "<<verts[t].x<<","<<verts[t].y<<","<<verts[t].z<<"\n";
  }
  DEBUG_OUT<<"Has "<<nfaces<<" faces.\n";
  for(unsigned long t=0;t<nfaces;t++) {
    DEBUG_OUT<<"f: "<<faces[t]->a<<","<<faces[t]->b<<","<<faces[t]->c<<"\n";
  }
  */
}


bool AMesh3D::isValid()
{
  bool val=true;
  if(!verts) val=false;
  if(nfaces) {
    // TODO: Make sure all are valid triangles, if not, drop them
    // zero out non-existant vert refs
    for(unsigned long t=0;t<nfaces;t++) {
      if(faces[t*3]>nverts) faces[t*3]=0;
      if(faces[t*3+1]>nverts) faces[t*3+1]=0;
      if(faces[t*3+2]>nverts) faces[t*3+2]=0;
      /*
      if(faces[t]->a>nverts) faces[t]->a=0;
      if(faces[t]->b>nverts) faces[t]->b=0;
      if(faces[t]->c>nverts) faces[t]->c=0;
      */
    }
  }
  //if(val==false) errorFlag=true;
  return val;
}


void AMesh3D::allocVertParts(unsigned long tNumFrames,unsigned long whichFrame,unsigned long tNumVerts)
{
  //DEBUG_OUT<<"allocVertParts: "<<tNumFrames<<","<<whichFrame<<","<<tNumVerts<<"\n";
  nverts=tNumVerts;
  numFrames=tNumFrames;
  if(!verts) verts=(float **)calloc(numFrames,sizeof(float *));
  if(!verts) { std::cerr<<"Didn't get verts!\n"; exit(EXIT_FAILURE); }
  if(!verts[whichFrame]) verts[whichFrame]=(float *)calloc(nverts*3,sizeof(float));
  if(!verts[whichFrame]) { std::cerr<<"Didn't get verts["<<whichFrame<<"]!\n"; exit(EXIT_FAILURE); }
  if(!drawableMesh.getDrawVerts()) drawableMesh.setDrawVerts((int *)calloc(nverts*3,sizeof(int)));
  if(!drawableMesh.getDrawVerts()) { std::cerr<<"Didn't get drawVerts!\n"; exit(EXIT_FAILURE); }
}


#endif // NICK_USE_NICK3D

