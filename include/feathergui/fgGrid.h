// Copyright �2017 Black Sphere Studios
// For conditions of distribution and use, see copyright notice in "feathergui.h"

#ifndef __FG_GRID_H__
#define __FG_GRID_H__

#include "fgList.h"
#include "fgTextbox.h"

#ifdef  __cplusplus
extern "C" {
#endif

  enum FGGRID_FLAGS
  {
    FGGRID_AUTOEDIT = (FGLIST_DRAGGABLE << 1),
  };

  enum FGGRID_ACTIONS
  {
    FGGRID_RESIZECOLUMN = FGSCROLLBAR_NUM,
  };

  typedef struct _FG_GRID_ROW {
    fgElement element;
    struct _FG_BOX_ORDERED_ELEMENTS_ order;
#ifdef  __cplusplus
    inline operator fgElement*() { return &element; }
    inline fgElement* operator->() { return operator fgElement*(); }
    FG_DLLEXPORT void InsertItem(fgElement* item, size_t column = (size_t)-1);
    FG_DLLEXPORT void InsertItem(const char* item, size_t column = (size_t)-1);
    FG_DLLEXPORT bool SetItem(fgElement* item, size_t column);
    FG_DLLEXPORT bool SetItem(const char* item, size_t column);
    FG_DLLEXPORT bool RemoveItem(size_t column);
    FG_DLLEXPORT fgElement* GetItem(size_t column);
#endif
  } fgGridRow;

  // Represents a grid of columns (or rows) with labels.
  typedef struct _FG_GRID {
    fgList list;
    fgList header; // The header is where the labels are
    fgTextbox editbox; // Used for autoediting grid controls.
    fgColor rowedgecolor;
    fgColor columnedgecolor;
    fgColor rowevencolor;
#ifdef  __cplusplus
    inline operator fgElement*() { return &list.box.scroll.control.element; }
    inline fgElement* operator->() { return operator fgElement*(); }
    FG_DLLEXPORT fgElement* InsertColumn(const char* name, size_t column = (size_t)-1);
    FG_DLLEXPORT bool SetItem(fgElement* item, size_t column, size_t row);
    FG_DLLEXPORT bool SetItem(const char* item, size_t column, size_t row);
    FG_DLLEXPORT fgGridRow* InsertRow(size_t row = (size_t)-1);
    FG_DLLEXPORT bool RemoveColumn(size_t column);
    FG_DLLEXPORT bool RemoveRow(size_t row);
    FG_DLLEXPORT bool RemoveItem(size_t column, size_t row);
    FG_DLLEXPORT fgElement* GetItem(size_t column, size_t row);
    FG_DLLEXPORT fgGridRow* GetRow(size_t row);
    FG_DLLEXPORT fgElement* GetColumn(size_t column);
#endif
  } fgGrid;

  FG_EXTERN void fgGrid_Init(fgGrid* BSS_RESTRICT self, fgElement* BSS_RESTRICT parent, fgElement* BSS_RESTRICT next, const char* name, fgFlag flags, const fgTransform* transform, unsigned short units);
  FG_EXTERN void fgGrid_Destroy(fgGrid* self);
  FG_EXTERN size_t fgGrid_Message(fgGrid* self, const FG_Msg* msg);

  FG_EXTERN void fgGridRow_Init(fgGridRow* BSS_RESTRICT self, fgElement* BSS_RESTRICT parent, fgElement* BSS_RESTRICT next, const char* name, fgFlag flags, const fgTransform* transform, unsigned short units);
  FG_EXTERN size_t fgGridRow_Message(fgGridRow* self, const FG_Msg* msg);
  FG_EXTERN void fgGridRow_Destroy(fgGridRow* self);

#ifdef  __cplusplus
}
#endif

#endif
