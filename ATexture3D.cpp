
#define DEBUG_OUT std::cerr
//#define DEBUG_OUT *aNullStream


#ifdef DEBUG_VERBOSE
#undef DEBUG_VERBOSE
#endif


#ifdef NICK_USE_NICK3D


#include <stdlib.h>
#include <iostream>

#include "ATexture3D.h"

#include "../cpp/decodeimg/ASmartImageDecoder.h"

#include "../cpp/decodeimg/AImageDecoder.h"


////////////////////////////////////////////////////////////////////////////////
//  ATexture3D Class
////////////////////////////////////////////////////////////////////////////////

ATexture3D::ATexture3D(char *fname)
{
  DEBUG_OUT<<"ATexture3D::ATexture3D("<<fname<<")...\n";
  init();
  //
  if(!fname) {
    std::cerr<<"no fname!\n";
    //return;
    exit(EXIT_FAILURE);
  }
  AImageDecoder *dec=(AImageDecoder *)ASmartImageDecoder::pickBestImageDecoder(fname);
  if(!dec) {
    std::cerr<<"no dec!\n";
    //return;
    exit(EXIT_FAILURE);
  }
  bm=dec->createNewBitmapObject();
  if(!bm) {
    std::cerr<<"no bm!\n";
    //return;
    exit(EXIT_FAILURE);
  }
  if(!bm->isTwentyFourBitsChunky()) {
    //std::cerr<<"ABitmap::convert() not implemented!\n";
    //exit(EXIT_FAILURE);
    bm->convertBitmap(24,ALIB_BITMAP_CHUNKY,NULL);
    bm->reorderRGBChunky2BGR();
    //boundTexture=nickBindTexture(this);
  }
}


ATexture3D::ATexture3D(unsigned long w,unsigned long h,unsigned long d,unsigned long np)
{
  DEBUG_OUT<<"ATexture3D::ATexture3D("<<w<<","<<h<<","<<d<<","<<np<<")...\n";
  init();
  bm=new ABitmap((unsigned int)w,(unsigned int)h,(unsigned int)d,(unsigned int)np);
  //
  //boundTexture=nickBindTexture(this);
}


void ATexture3D::init()
{
  bm=(ABitmap *)NULL;
  boundTexture=NULL;
}


#endif // NICK_USE_NICK3D

