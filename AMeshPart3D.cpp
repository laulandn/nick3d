
#define DEBUG_OUT std::cerr
//#define DEBUG_OUT *aNullStream


#ifdef DEBUG_VERBOSE
#undef DEBUG_VERBOSE
#endif


#ifdef NICK_USE_NICK3D


#include <stdio.h>

#include "AMeshPart3D.h"


////////////////////////////////////////////////////////////////////////////////
//  AMeshPart3D Class
////////////////////////////////////////////////////////////////////////////////

AMeshPart3D::AMeshPart3D()
{
  name=NULL;
  startVert=0;  endVert=0;
  startFace=0;  endFace=0;
}


#endif // NICK_USE_NICK3D

