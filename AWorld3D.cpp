
#define DEBUG_OUT std::cerr
#define ERR_OUT std::cerr
//#define DEBUG_OUT *aNullStream


#ifdef DEBUG_VERBOSE
#undef DEBUG_VERBOSE
#endif


#ifdef NICK_USE_NICK3D


#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "../cpp/alib/anullstream.h"

#include "../cpp/guilib/AWindow.h"

#include "AWorld3D.h"
#include "ACamera3D.h"
#include "AThing3D.h"
#include "AScene3D.h"


// HACK
void *nikBindThisTexture3D(ATexture3D *tx);
bool nikPrepareMesh3D(AMesh3D *m);
bool nikPrepareScene3D(AScene3D *s);
void nikDrawFace3D(AWindow *win,AMesh3D *m,unsigned short *f,int *dvs,unsigned long fnum);
void nikDrawMesh3D(AWindow *win,AMesh3D *m,float x,float y,float z);
void nikDrawScene3D(AWindow *win,AScene3D *s);


#define makeRGB24(x,y,z) ((z&0xff)+((y&0xff)<<8)+((x&0xff)<<16))


////////////////////////////////////////////////////////////////////////////////
//  AWorld3D Class
////////////////////////////////////////////////////////////////////////////////


AWorld3D::AWorld3D(AScene3D *theScene)
{
  DEBUG_OUT<<"AWorld3D::AWorld3D()\n";
  init();
  s=theScene;
  if(!s) { std::cerr<<"No scene for AWorld3D!\n"; exit(EXIT_FAILURE); }
  c=s->getCamera(0);
  numThings=s->getNumMeshes();
  things=(AThing3D **)calloc(numThings,sizeof(AThing3D *));
  for(unsigned long t=0;t<numThings;t++) {
    things[t]=new AThing3D(s->getMeshes()[t]);
  }
}


AWorld3D::~AWorld3D()
{
  c=NULL;  // but don't delete it, it belongs to s
  if(s) delete s;
  s=NULL;
}


void AWorld3D::init()
{
  c=NULL;
  s=NULL;
  xScale=1.0; yScale=1.0;
  actualWidth=100;  actualHeight=100;  // Arbitrary...
  numThings=0;
  things=NULL;
}


void AWorld3D::debugDump()
{
  c->debugDump();
  s->debugDump();
}


void AWorld3D::setScaling(float sx,float sy)
{
  xScale=sx;  yScale=sy;
}


void AWorld3D::setDimesions(unsigned long w,unsigned long h)
{
  if(!w) { ERR_OUT<<"setDimesions w is zero!\n"; exit(EXIT_FAILURE); }
  if(!h) { ERR_OUT<<"setDimesions h is zero!\n"; exit(EXIT_FAILURE); }
  actualWidth=w; actualHeight=h;
}


unsigned long AWorld3D::getXWidth()
{
  return s->getXWidth();
}


unsigned long AWorld3D::getYWidth()
{
  return s->getYWidth();
}


unsigned long AWorld3D::getZWidth()
{
  return s->getZWidth();
}


void AWorld3D::prepareForRendering()
{
  // Before we resize for the meshes...
  s->calcBoundingBox();
  s->calcWidths();
  // Resizing...
  for(unsigned long t=0;t<s->getNumMeshes();t++) {
    s->resizeToFit(s->getMeshes()[t]);
  }
  // After we resized.
  s->calcBoundingBox();
  s->calcWidths();
  //std::cerr<<"Need to fix AWorld3D::prepareForRendering!\n";
  //exit(EXIT_FAILURE);
  //nickPrepareScene3D(s);
}


void AWorld3D::render(AWindow *win)
{
  DEBUG_OUT<<"AWorld3D::render()...\n";
  unsigned long t=0;
  AMesh3D *theMesh=NULL;
  for(t=0;t<s->getNumMeshes();t++) {
    DEBUG_OUT<<"Working on mesh #"<<t<<"\n";
    theMesh=s->getMeshes()[t];
    theMesh->unit();
    theMesh->translate(-(theMesh->getBMin()->x+theMesh->getBMax()->x)/2,-(theMesh->getBMin()->y+theMesh->getBMax()->y)/2,-(theMesh->getBMin()->z+theMesh->getBMax()->z)/2);
    theMesh->transCamModelToDrawMatrix(c);
    theMesh->scale(xScale,-xScale,16*xScale/actualWidth);
    theMesh->translate(actualWidth/2,actualHeight/2,8);
    theMesh->setStale(true);
    theMesh->transformVertsToDraw();
  }
  nikDrawScene3D(win,s);
}


void *nikBindThisTexture3D(ATexture3D *tx)
{
  DEBUG_OUT<<"nikBindThisTexture3D not implemented!\n";
  return NULL;
}


bool nikPrepareMesh3D(AMesh3D *m)
{
  DEBUG_OUT<<"nikPrepareMesh3D(...)\n";
  for(unsigned int t=0;t<m->getNumTextures();t++) {
    ATexture3D *tx=m->getTextures()[t];
    tx->setBinding(nikBindThisTexture3D(tx));
  }
  return true;
}


bool nikPrepareScene3D(AScene3D *s)
{
  DEBUG_OUT<<"nikPrepareScene3D(...)\n";
  for(unsigned int t=0;t<s->getNumMeshes();t++) {
    nikPrepareMesh3D(s->getMeshes()[t]);
  }
  return true;
}


void nikDrawFace3D(AWindow *win,AMesh3D *m,unsigned short *f,int *dvs,unsigned long fnum)
{
  if(!win) return;
  if(!m) return;
  if(!f) return;
  if(!dvs) return;
  int x1,y1,x2,y2,x3,y3;
  //float z1,z2,z3;
  float c1,c2,c3;
  unsigned int clr=0xffffff;
  float fact=255.0;
  AFaceInfo3D **fis=m->getFaceInfos();
  AFaceInfo3D *fi=NULL;
  if(fis) fi=fis[fnum];
  //c1=(z1+z2)/2;  c2=(z2+z3)/2;  c3=(z3+z1)/2;
  c1=1.0;  c2=1.0;  c3=1.0;
  //
  //z1=dvs[f->a].z;
  //z2=dvs[f->b].z;
  //z3=dvs[f->c].z;
  //
  /*
  x1=dvs[f->a].x;
  //if(x1<0.0) x1=-x1;
  y1=dvs[f->a].y;
  //if(y1<0.0) y1=-y1;
  x2=dvs[f->b].x;
  //if(x2<0.0) x2=-x2;
  y2=dvs[f->b].y;
  //if(y2<0.0) y2=-y2;
  x3=dvs[f->c].x;
  //if(x3<0.0) x3=-x3;
  y3=dvs[f->c].y;
  //if(y3<0.0) y3=-y3;
  */
  x1=dvs[f[fnum*3]*3];
  y1=dvs[f[fnum*3]*3+1];
  x2=dvs[f[fnum*3+1]*3];
  y2=dvs[f[fnum*3+1]*3+1];
  x3=dvs[f[fnum*3+2]*3];
  y3=dvs[f[fnum*3+2]*3+1];
  //
  //debug_msg("drawFace3D: ("); x1 debug_msg(","); y1 debug_msg(") ("); x2 debug_msg(","); y2 debug_msg(") ("); x3 debug_msg(","); y3 debug_msg(")\n");
  //debug_msg("face colors: "); f->fRed debug_msg(","); f->fGreen debug_msg(","); f->fBlue debug_msg("\n");
  //
  //if((z1>0)&&(z2>0)) {
  if(fi) clr=makeRGB24((int)(c1*fact*fi->fRed),(int)(c2*fact*fi->fGreen),(int)(c3*fact*fi->fBlue));
  clr=0;
  win->setForeground(clr);
  win->drawLine(x1,y1,x2,y2);
  //}
  //if((z2>0)&&(z3>0)) {
  win->drawLine(x2,y2,x3,y3);
  //}
  //if((z3>0)&&(z1>0)) {
  win->drawLine(x3,y3,x1,y1);
  //}
}


void nikDrawMesh3D(AWindow *win,AMesh3D *m,float x,float y,float z)
{
  DEBUG_OUT<<"nikDrawMesh3D Mesh has "<<m->getNumFaces()<<" faces...\n";
  //nikLockDisplay();
  //nikSetColorLong(0x404040);
  //nikClearFrameBuffer();
  int *dvs=m->getDrawableMesh()->getDrawVerts();
  for(unsigned long t=0;t<m->getNumFaces();t++) {
    unsigned short *f=m->getFaces();
    //debug_msg("face: "); f->a debug_msg(","); f->b debug_msg(","); f->c debug_msg("\n");
    nikDrawFace3D(win,m,f,dvs,t);
  }
  //nikUnlockDisplay();
  //nikFlipDisplay();
}


void nikDrawScene3D(AWindow *win,AScene3D *s)
{
  unsigned long nshapes=s->getNumMeshes();
  DEBUG_OUT<<"nikDrawScene3D Scene has "<<nshapes<<" meshes...\n";
  //nikLockDisplay();
  //nikSetColorLong(0x404040);
  //nikClearFrameBuffer();
  for(unsigned long t=0;t<nshapes;t++) {
    AMesh3D *m=s->getMeshes()[t];
    nikDrawMesh3D(win,m,0.0,0.0,0.0);
  }
  //nikUnlockDisplay();
  //nikFlipDisplay();
}


#endif // NICK_USE_NICK3D

