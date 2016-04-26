// Copyright �2016 Black Sphere Studios
// For conditions of distribution and use, see copyright notice in "feathergui.h"

#ifndef _FG_TOPWINDOW_H__
#define _FG_TOPWINDOW_H__

#include "fgButton.h"

#ifdef  __cplusplus
extern "C" {
#endif

enum FGTOPWINDOW_FLAGS
{
  FGTOPWINDOW_MINIMIZABLE = (1 << 8),
  FGTOPWINDOW_MAXIMIZABLE = (1 << 9),
  FGTOPWINDOW_RESIZABLE = (1 << 10),
  FGTOPWINDOW_NOTITLEBAR = (1 << 11),
  FGTOPWINDOW_NOBORDER = (1 << 12),
};

enum FGTOPWINDOW_ACTIONS
{
  FGTOPWINDOW_CLOSE = 0,
  FGTOPWINDOW_MAXIMIZE,
  FGTOPWINDOW_RESTORE,
  FGTOPWINDOW_MINIMIZE,
  FGTOPWINDOW_UNMINIMIZE,
};

struct _FG_BUTTON;

// A top-level window is an actual window with a titlebar that can be dragged and resized.
typedef struct {
  fgControl control;
  fgText caption;
  fgButton controls[3]; // 0 is the close button, 1 is the maximize/restore button, 2 is the minimize button
  CRect prevrect; // Stores where the window was before being maximized
  AbsVec offset; // offset from the mouse cursor for movement
  char dragged; // 1 if currently being dragged by mouse
#ifdef  __cplusplus
  inline operator fgElement*() { return &control.element; }
  inline fgElement* operator->() { return operator fgElement*(); }
#endif
} fgTopWindow;

FG_EXTERN fgElement* FG_FASTCALL fgTopWindow_Create(const char* caption, fgFlag flags, const fgTransform* transform);
FG_EXTERN void FG_FASTCALL fgTopWindow_Init(fgTopWindow* self, fgFlag flags, const fgTransform* transform);
FG_EXTERN void FG_FASTCALL fgTopWindow_Destroy(fgTopWindow* self);
FG_EXTERN size_t FG_FASTCALL fgTopWindow_Message(fgTopWindow* self, const FG_Msg* msg);

#ifdef  __cplusplus
}
#endif

#endif
