/* PlaneShader - Advanced Hybrid 2D Graphics Engine
   Copyright �2018 Black Sphere Studios

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef __DEC_H__PS__
#define __DEC_H__PS__

#define PS_VERSION_MAJOR 0
#define PS_VERSION_MINOR 7
#define PS_VERSION_REVISION 0

#ifndef _WINRESRC_

#include "bss-util/defines.h"

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
  typedef unsigned int psFlag;

  // All possible flags for objects 
  const psFlag PSFLAG_NOTVISIBLE = (1 << 0); //Prevents the object and its children from being rendered
  const psFlag PSFLAG_FIXED = (1 << 1); //Ignores the camera rotation and xyz position.
  const psFlag PSFLAG_ALWAYSRENDER = (1 << 2); //This object will always render itself regardless of any NOTVISIBLE flags anywhere in the parent chain
  const psFlag PSFLAG_DONOTCULL = (1 << 3); //Ensures the object is never culled for any reason
  const psFlag PSFLAG_DONOTBATCH = (1 << 4); // Used to prevent automatic batching of jobs with the same vertex buffer (usually due to incompatible index buffers)
  const psFlag PSFLAG_USER = (1 << 5); //This is where you should start your own flag settings
  const unsigned int BASE_DPI = 96;

#ifdef  __cplusplus
  const psFlag PSFLAG_INHERITABLE = PSFLAG_NOTVISIBLE | PSFLAG_FIXED;
  const psFlag PSFLAG_BATCHFLAGS = PSFLAG_NOTVISIBLE | PSFLAG_FIXED;
}
#else
  const psFlag PSFLAG_INHERITABLE=0x03;
#endif
#endif
#endif
