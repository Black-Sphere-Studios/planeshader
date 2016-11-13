// Copyright �2016 Black Sphere Studios
// For conditions of distribution and use, see copyright notice in "feathergui.h"

#ifndef __FG_LAYOUT_H__
#define __FG_LAYOUT_H__

#include "fgSkin.h"

#ifdef  __cplusplus
extern "C" {
#endif

struct __kh_fgIDMap_t;
struct __kh_fgUserStrings_t;
struct _FG_CLASS_LAYOUT;
typedef fgDeclareVector(struct _FG_CLASS_LAYOUT, ClassLayout) fgVectorClassLayout;

typedef struct _FG_CLASS_LAYOUT {
  fgStyleLayout style;
  fgVectorClassLayout children; // Type: fgClassLayout
  struct __kh_fgUserStrings_t* userdata; // Custom userdata from unknown attributes
} fgClassLayout;

typedef struct _FG_LAYOUT {
  fgSkinBase base;
  struct __kh_fgIDMap_t* idmap; // holds map of last instantiated layout
  fgVectorClassLayout layout; // Type: fgClassLayout
} fgLayout;

FG_EXTERN void FG_FASTCALL fgLayout_Init(fgLayout* self);
FG_EXTERN void FG_FASTCALL fgLayout_Destroy(fgLayout* self);
FG_EXTERN FG_UINT FG_FASTCALL fgLayout_AddLayout(fgLayout* self, const char* type, const char* name, fgFlag flags, const fgTransform* transform, short units, int order = 0);
FG_EXTERN char FG_FASTCALL fgLayout_RemoveLayout(fgLayout* self, FG_UINT layout);
FG_EXTERN fgClassLayout* FG_FASTCALL fgLayout_GetLayout(fgLayout* self, FG_UINT layout);
FG_EXTERN int FG_FASTCALL fgLayout_RegisterFunction(fgListener fn, const char* name);
FG_EXTERN void FG_FASTCALL fgLayout_ApplyFunctions(fgElement* root);

FG_EXTERN void FG_FASTCALL fgClassLayout_Init(fgClassLayout* self, const char* type, const char* name, fgFlag flags, const fgTransform* transform, short units, int order = 0);
FG_EXTERN void FG_FASTCALL fgClassLayout_Destroy(fgClassLayout* self);
FG_EXTERN FG_UINT FG_FASTCALL fgClassLayout_AddChild(fgClassLayout* self, const char* type, const char* name, fgFlag flags, const fgTransform* transform, short units, int order = 0);
FG_EXTERN char FG_FASTCALL fgClassLayout_RemoveChild(fgClassLayout* self, FG_UINT child);
FG_EXTERN fgClassLayout* FG_FASTCALL fgClassLayout_GetChild(fgClassLayout* self, FG_UINT child);

FG_EXTERN fgElement* FG_FASTCALL fgLayout_GetID(fgLayout* self, const char* id);
FG_EXTERN void FG_FASTCALL fgLayout_LoadFileUBJSON(fgLayout* self, const char* file);
FG_EXTERN void FG_FASTCALL fgLayout_LoadUBJSON(fgLayout* self, const char* data, FG_UINT length);
FG_EXTERN void FG_FASTCALL fgLayout_SaveFileUBJSON(fgLayout* self, const char* file);
FG_EXTERN bool FG_FASTCALL fgLayout_LoadFileXML(fgLayout* self, const char* file);
FG_EXTERN bool FG_FASTCALL fgLayout_LoadXML(fgLayout* self, const char* data, FG_UINT length);
FG_EXTERN void FG_FASTCALL fgLayout_SaveFileXML(fgLayout* self, const char* file);
FG_EXTERN void FG_FASTCALL fgLayout_SaveElementXML(fgElement* root, const char* file);

FG_EXTERN size_t FG_FASTCALL fgDefaultLayout(fgElement* self, const FG_Msg* msg, AbsVec* dim);
FG_EXTERN size_t FG_FASTCALL fgDistributeLayout(fgElement* self, const FG_Msg* msg, fgFlag axis);
FG_EXTERN size_t FG_FASTCALL fgTileLayout(fgElement* self, const FG_Msg* msg, fgFlag flags, AbsVec* area);

#ifdef  __cplusplus
}
#endif

#endif