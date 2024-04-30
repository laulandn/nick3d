
#define DEBUG_OUT std::cerr
//#define DEBUG_OUT *aNullStream


#ifdef DEBUG_VERBOSE
#undef DEBUG_VERBOSE
#endif


#ifdef NICK_USE_NICK3D


#include "ATextCoord3D.h"


////////////////////////////////////////////////////////////////////////////////
//  ATextCoord3D Class
////////////////////////////////////////////////////////////////////////////////

ATextCoord3D::ATextCoord3D()
{
  //DEBUG_<<"ATextCoord3D created!\n";
  u=0.0;  v=0.0;
}


#endif // NICK_USE_NICK3D

