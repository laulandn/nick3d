
#define DEBUG_OUT std::cerr
#define ERR_OUT std::cerr
//#define DEBUG_OUT *aNullStream
//#define CONS_OUT std::cout
#define CONS_IN std::cin


#ifdef DEBUG_VERBOSE
#undef DEBUG_VERBOSE
#endif


#ifdef NICK_USE_NICK3D


#include <iostream>


#ifdef NIK_GUILIB
#include "../guilib/AWindow.h"
#endif

#ifdef NIK_NIKDRAWING
//#include "../../niklib/nikdrawing.h"
#endif


#include "AMatrix3D.h"
#include "ARenderer3D.h"
#include "AShape3D.h"
#include "AVertex3D.h"
#include "ALine3D.h"


////////////////////////////////////////////////////////////////////////////////
//  ARenderer3D Class
////////////////////////////////////////////////////////////////////////////////

ARenderer3D::ARenderer3D(AWindow *win)
{
  window=win;
}


void ARenderer3D::init()
{
  window=(AWindow *)NULL;
}


void ARenderer3D::draw(AShape3D *shape)
{
}


////////////////////////////////////////////////////////////////////////////////
//  AWireframeRenderer3D Class
////////////////////////////////////////////////////////////////////////////////

AWireframeRenderer3D::AWireframeRenderer3D(AWindow *win) : ARenderer3D(win)
{
  init();
  window=win;
}


// WARNING: This is a very hacky function...(and we aren't even really using AShape3Ds anymore!
void AWireframeRenderer3D::draw(AShape3D *shape)
{
  ERR_OUT<<"AWireframeRenderer3D::draw not implemented!\n";
  exit(EXIT_SUCCESS);
/*
  if(!window) return;
  unsigned long a, b,c,d;
  unsigned long xdif=0;
  unsigned long ydif=0;
#ifdef NIK_GUILIB
  xdif=window->getWidth()/2;
  ydif=window->getHeight()/2;
#endif
#ifdef NIK_NIKDRAWING
  xdif=ndActualWidth/2;
  ydif=ndActualHeight/2;
#endif
  for(unsigned long i=0;i<shape->numLines;i++)
  {
    a=(unsigned long)shape->vertices[shape->lines[i].start].sx+xdif;
    b=(unsigned long)shape->vertices[shape->lines[i].start].sy+ydif;
    c=(unsigned long)shape->vertices[shape->lines[i].end].sx+xdif;
    d=(unsigned long)shape->vertices[shape->lines[i].end].sy+ydif;
#ifdef NIK_GUILIB
    window->setForeground(shape->lines[i].color);
    window->drawLine(a,b,c,d);
#endif
#ifdef NIK_NIKDRAWING
    nickSetColorLong(shape->lines[i].color);
    nickDrawLine(a,b,c,d);
#endif
  }
  */
}


#endif // NICK_USE_NICK3D

