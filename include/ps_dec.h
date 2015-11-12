// Copyright �2015 Black Sphere Studios
// For conditions of distribution and use, see copyright notice in PlaneShader.h

#ifndef __DEC_H__PS__
#define __DEC_H__PS__

#include "bss-util/bss_defines.h"

#define PS_VERSION_MAJOR 0
#define PS_VERSION_MINOR 7
#define PS_VERSION_REVISION 0

#ifndef PS_STATIC_LIB
#ifdef PlaneShader_EXPORTS
#pragma warning(disable:4251)
#define PS_DLLEXPORT BSS_COMPILER_DLLEXPORT
#else
#define PS_DLLEXPORT BSS_COMPILER_DLLIMPORT
#endif
#else
#define PS_DLLEXPORT
#endif

#ifdef BSS_DEBUG
#define BSS_ENABLE_PROFILER
#endif

#ifdef  __cplusplus
namespace planeshader {
#endif
  typedef float FNUM; //Float typedef (can be changed to double for double precision)
  typedef unsigned int FLAG_TYPE;

  // All possible flags for objects 
  const FLAG_TYPE PSFLAG_NOTVISIBLE = (1 << 0); //Prevents the object and its children from being rendered
  const FLAG_TYPE PSFLAG_FIXED = (1 << 1); //Ignores the camera rotation and xyz position.
  const FLAG_TYPE PSFLAG_ALWAYSRENDER = (1 << 2); //This object will always render itself regardless of any NOTVISIBLE flags anywhere in the parent chain
  const FLAG_TYPE PSFLAG_DONOTCULL = (1 << 3); //Ensures the object is never culled for any reason
  const FLAG_TYPE PSFLAG_USER = (1 << 4); //This is where you should start your own flag settings

#ifdef  __cplusplus
  const FLAG_TYPE PSFLAG_INHERITABLE = PSFLAG_NOTVISIBLE | PSFLAG_FIXED;
  const FLAG_TYPE PSFLAG_BATCHFLAGS = PSFLAG_NOTVISIBLE | PSFLAG_FIXED;
}
#else
  const FLAG_TYPE PSFLAG_INHERITABLE=0x03;
#endif

#endif
