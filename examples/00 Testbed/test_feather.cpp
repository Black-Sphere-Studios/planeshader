// Copyright �2016 Black Sphere Studios

#include "testbed.h"
#include "psTex.h"
#include "psFont.h"
#include "feathergui/fgButton.h"
#include "feathergui/fgResource.h"
#include "feathergui/fgCurve.h"
#include "feathergui/fgWindow.h"
#include "feathergui/fgRadioButton.h"
#include "feathergui/fgProgressbar.h"
#include "feathergui/fgSlider.h"
#include "feathergui/fgList.h"
#include "feathergui/fgSkin.h"
#include "feathergui/fgRoot.h"
#include "feathergui/fgTextbox.h"
#include "feathergui/fgTabControl.h"
#include "feathergui/fgDebug.h"

using namespace bss_util;
using namespace planeshader;

fgElement* fg_progbar;

TESTDEF::RETPAIR test_feather()
{
  BEGINTEST;
  int fps = 0;
  auto timer = cHighPrecisionTimer::OpenProfiler();
  const fgTransform FILL_TRANSFORM = { { 0, 0, 0, 0, 0, 1, 0, 1 }, 0, { 0, 0, 0, 0 } };

  fgSkin skin;
  fgSkin_Init(&skin);
  fgSkin* fgButtonTestSkin = fgSkinBase_AddSkin(&skin.base, "buttontest");
  fgSkin* fgWindowSkin = fgSkinBase_AddSkin(&skin.base, "Window");
  fgSkin* fgButtonSkin = fgSkinBase_AddSkin(&fgWindowSkin->base, "Button");
  fgSkin* fgResourceSkin = fgSkinBase_AddSkin(&fgButtonTestSkin->base, "Resource");
  fgSkin* fgCheckboxSkin = fgSkinBase_AddSkin(&fgWindowSkin->base, "Checkbox");
  fgSkin* fgRadioButtonSkin = fgSkinBase_AddSkin(&fgWindowSkin->base, "RadioButton");
  fgSkin* fgProgressbarSkin = fgSkinBase_AddSkin(&fgWindowSkin->base, "Progressbar");
  fgSkin* fgSliderSkin = fgSkinBase_AddSkin(&fgWindowSkin->base, "Slider");
  fgSkin* fgTextboxSkin = fgSkinBase_AddSkin(&fgWindowSkin->base, "Textbox");
  fgSkin* fgDropdownSkin = fgSkinBase_AddSkin(&fgWindowSkin->base, "Dropdown");
  fgSkin* fgTreeViewSkin = fgSkinBase_AddSkin(&skin.base, "TreeView");
  fgSkin* fgScrollbarSkin = fgSkinBase_AddSkin(&skin.base, "Scrollbar");
  fgSkin* fgTabControlSkin = fgSkinBase_AddSkin(&skin.base, "TabControl");
  fgSkin* fgListSkin = fgSkinBase_AddSkin(&skin.base, "List");
  fgSkin* fgTextSkin = fgSkinBase_AddSkin(&skin.base, "Text");

  auto fnAddRect = [](fgSkin* target, const char* name, const CRect& uv, const fgTransform& transform, unsigned int color, unsigned int edge, float outline, fgFlag flags, int order = 0) -> fgStyleLayout* {
    fgStyleLayout* layout = fgSkin_GetChild(target, fgSkin_AddChild(target, "Resource", name, FGRESOURCE_ROUNDRECT | flags, &transform, order));
    AddStyleMsgArg<FG_SETUV, CRect>(&layout->style, &uv);
    AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(&layout->style, color);
    AddStyleSubMsg<FG_SETCOLOR, ptrdiff_t>(&layout->style, FGSETCOLOR_EDGE, edge);
    AddStyleMsg<FG_SETOUTLINE, float>(&layout->style, outline);
    return layout;
  };
  auto fnAddCircle = [](fgSkin* target, const char* name, const CRect& uv, const fgTransform& transform, unsigned int color, unsigned int edge, float outline, fgFlag flags, int order = 0) -> fgStyleLayout* {
    fgStyleLayout* layout = fgSkin_GetChild(target, fgSkin_AddChild(target, "Resource", name, FGRESOURCE_CIRCLE | flags, &transform, order));
    AddStyleMsgArg<FG_SETUV, CRect>(&layout->style, &uv);
    AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(&layout->style, color);
    AddStyleSubMsg<FG_SETCOLOR, ptrdiff_t>(&layout->style, FGSETCOLOR_EDGE, edge);
    AddStyleMsg<FG_SETOUTLINE, float>(&layout->style, outline);
    return layout;
  };

  // fgResource
  FG_UINT nuetral = fgSkin_AddStyle(fgResourceSkin, "nuetral");
  FG_UINT active = fgSkin_AddStyle(fgResourceSkin, "active");
  FG_UINT hover = fgSkin_AddStyle(fgResourceSkin, "hover");
  AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(fgResourceSkin, nuetral), 0xFFFF00FF);
  AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(fgResourceSkin, hover), 0xFF00FFFF);
  AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(fgResourceSkin, active), 0xFFFFFF00);

  // fgButton
  FG_UINT bnuetral = fgSkin_AddStyle(fgButtonTestSkin, "nuetral");
  FG_UINT bactive = fgSkin_AddStyle(fgButtonTestSkin, "active");
  FG_UINT bhover = fgSkin_AddStyle(fgButtonTestSkin, "hover");
  AddStyleMsg<FG_SETTEXT, void*>(fgSkin_GetStyle(fgButtonTestSkin, bnuetral), "Nuetral");
  AddStyleMsg<FG_SETTEXT, void*>(fgSkin_GetStyle(fgButtonTestSkin, bactive), "Active");
  AddStyleMsg<FG_SETTEXT, void*>(fgSkin_GetStyle(fgButtonTestSkin, bhover), "Hover");

  void* font = fgCreateFont(FGTEXT_SUBPIXEL, "arial.ttf", 14, 96);
  void* smfont = fgCreateFont(FGTEXT_SUBPIXEL, "arial.ttf", 10, 96);
  ((psFont*)font)->SetLineHeight(16);
  ((psFont*)smfont)->SetLineHeight(12);

  FG_Msg msg = { 0 };
  msg.type = FG_SETCOLOR;
  msg.otherint = 0xFFFFFFFF;
  fgStyle_AddStyleMsg(&fgButtonSkin->style, &msg, 0, 0, 0, 0);
  fgStyle_AddStyleMsg(&fgButtonTestSkin->style, &msg, 0, 0, 0, 0);
  fgStyle_AddStyleMsg(&fgCheckboxSkin->style, &msg, 0, 0, 0, 0);
  fgStyle_AddStyleMsg(&fgRadioButtonSkin->style, &msg, 0, 0, 0, 0);
  fgStyle_AddStyleMsg(&fgProgressbarSkin->style, &msg, 0, 0, 0, 0);
  fgStyle_AddStyleMsg(&fgTextboxSkin->style, &msg, 0, 0, 0, 0);
  fgStyle_AddStyleMsg(&fgTextSkin->style, &msg, 0, 0, 0, 0);
  
  msg.type = FG_SETFONT;
  msg.other = font;
  fgStyle_AddStyleMsg(&fgButtonSkin->style, &msg, 0, 0, 0, 0);
  fgStyle_AddStyleMsg(&fgButtonTestSkin->style, &msg, 0, 0, 0, 0);
  fgStyle_AddStyleMsg(&fgCheckboxSkin->style, &msg, 0, 0, 0, 0);
  fgStyle_AddStyleMsg(&fgRadioButtonSkin->style, &msg, 0, 0, 0, 0);
  fgStyle_AddStyleMsg(&fgProgressbarSkin->style, &msg, 0, 0, 0, 0);
  fgStyle_AddStyleMsg(&fgTextboxSkin->style, &msg, 0, 0, 0, 0);
  fgStyle_AddStyleMsg(&fgTextSkin->style, &msg, 0, 0, 0, 0);

  AbsRect buttonpadding = { 5, 5, 5, 5 };
  AddStyleMsgArg<FG_SETPADDING, AbsRect>(&fgButtonSkin->style, &buttonpadding);

  fgSkin* fgbuttonbgskin = fgSkinBase_AddSkin(&fgButtonSkin->base, "#bg");
  bnuetral = fgSkin_AddStyle(fgbuttonbgskin, "nuetral");
  bactive = fgSkin_AddStyle(fgbuttonbgskin, "active");
  bhover = fgSkin_AddStyle(fgbuttonbgskin, "hover");

  AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(fgbuttonbgskin, bnuetral), 0xFF666666);
  AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(fgbuttonbgskin, bactive), 0xFF505050);
  AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(fgbuttonbgskin, bhover), 0xFF7F7F7F);

  fnAddRect(fgButtonSkin, "#bg", CRect { 5, 0, 5, 0, 5, 0, 5, 0 }, FILL_TRANSFORM, 0xFF666666, 0xFFAAAAAA, 1.0f, FGELEMENT_BACKGROUND);

  // fgWindow
  fnAddRect(fgWindowSkin, 0, CRect { 5, 0, 5, 0, 5, 0, 5, 0 }, FILL_TRANSFORM, 0xFF666666, 0xFFAAAAAA, 1.0f, FGELEMENT_BACKGROUND);

  fgSkin* topwindowcaption = fgSkinBase_AddSkin(&fgWindowSkin->base, "Window$text");
  AbsRect margin = { 4, 4, 0, 0 };
  AddStyleMsgArg<FG_SETMARGIN, AbsRect>(&topwindowcaption->style, &margin);

  // fgCheckbox
  fnAddRect(fgCheckboxSkin, "#checkbg", CRect { 3, 0, 3, 0, 3, 0, 3, 0 }, fgTransform { { 5, 0, 0, 0.5, 20, 0, 15, 0.5 }, 0, { 0, 0, 0, 0.5 } }, 0xFFFFFFFF, 0xFF222222, 1.0f, FGELEMENT_BACKGROUND | FGELEMENT_SNAP);
  //fnAddRect(fgCheckboxSkin, 0, CRect { 0, 0, 0, 0, 0, 0, 0, 0 }, fgTransform { { 0, 0, 0, 0, 0, 1, 0, 1 }, 0, { 0, 0, 0, 0 } }, 0x99000000, 0, 0.0f, FGELEMENT_BACKGROUND);
  AddStyleMsgArg<FG_SETPADDING, AbsRect>(&fgCheckboxSkin->style, &AbsRect { 25,0,5,0 });
  fnAddRect(fgCheckboxSkin, "#check", CRect { 2, 0, 2, 0, 2, 0, 2, 0 }, fgTransform { { 8, 0, 0, 0.5, 17, 0, 9, 0.5 }, 0, { 0, 0, 0, 0.5 } }, 0xFF000000, 0, 0, FGELEMENT_BACKGROUND | FGELEMENT_SNAP, 1);
  fgSkin* fgCheckedSkin = fgSkinBase_AddSkin(&fgCheckboxSkin->base, "#check");

  fgSkin* fgCheckboxSkinbg = fgSkinBase_AddSkin(&fgCheckboxSkin->base, "#checkbg");
  bnuetral = fgSkin_AddStyle(fgCheckboxSkinbg, "nuetral");
  bactive = fgSkin_AddStyle(fgCheckboxSkinbg, "active");
  bhover = fgSkin_AddStyle(fgCheckboxSkinbg, "hover");
  FG_UINT bdefault = fgSkin_AddStyle(fgCheckedSkin, "default");
  FG_UINT bchecked = fgSkin_AddStyle(fgCheckedSkin, "checked");
  FG_UINT bindeterminate = fgSkin_AddStyle(fgCheckedSkin, "indeterminate");

  AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(fgCheckboxSkinbg, bnuetral), 0xFFFFFFFF);
  AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(fgCheckboxSkinbg, bactive), 0xFFBBBBBB);
  AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(fgCheckboxSkinbg, bhover), 0xFFDDDDDD);
  AddStyleMsg<FG_SETFLAG, ptrdiff_t, size_t>(fgSkin_GetStyle(fgCheckedSkin, bdefault), FGELEMENT_HIDDEN, 1);
  AddStyleMsg<FG_SETFLAG, ptrdiff_t, size_t>(fgSkin_GetStyle(fgCheckedSkin, bchecked), FGELEMENT_HIDDEN, 0);
  AddStyleMsg<FG_SETFLAG, ptrdiff_t, size_t>(fgSkin_GetStyle(fgCheckedSkin, bindeterminate), FGELEMENT_HIDDEN, 1);

  // fgRadioButton
  fnAddCircle(fgRadioButtonSkin, "#bg", CRect { 0, 0, PI_DOUBLEf, 0, 0, 0, PI_DOUBLEf, 0 }, fgTransform { { 5, 0, 0, 0.5, 20, 0, 15, 0.5 }, 0, { 0, 0, 0, 0.5 } }, 0xFFFFFFFF, 0xFF222222, 1.0f, FGELEMENT_BACKGROUND | FGELEMENT_SNAP);
  AddStyleMsgArg<FG_SETPADDING, AbsRect>(&fgRadioButtonSkin->style, &AbsRect { 25,5,5,5 });
  fnAddCircle(fgRadioButtonSkin, "#check", CRect { 0, 0, PI_DOUBLEf, 0, 0, 0, PI_DOUBLEf, 0 }, fgTransform { { 8, 0, 0, 0.5, 17, 0, 9, 0.5 }, 0, { 0, 0, 0, 0.5 } }, 0xFF000000, 0, 0, FGELEMENT_BACKGROUND | FGELEMENT_SNAP, 1);
  fgSkin* fgRadioSelectedSkin = fgSkinBase_AddSkin(&fgRadioButtonSkin->base, "#check");

  fgSkin* fgRadioButtonSkinbg = fgSkinBase_AddSkin(&fgRadioButtonSkin->base, "#bg");
  bnuetral = fgSkin_AddStyle(fgRadioButtonSkinbg, "nuetral");
  bactive = fgSkin_AddStyle(fgRadioButtonSkinbg, "active");
  bhover = fgSkin_AddStyle(fgRadioButtonSkinbg, "hover");
  bdefault = fgSkin_AddStyle(fgRadioSelectedSkin, "default");
  bchecked = fgSkin_AddStyle(fgRadioSelectedSkin, "checked");

  AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(fgRadioButtonSkinbg, bnuetral), 0xFFFFFFFF);
  AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(fgRadioButtonSkinbg, bactive), 0xFFBBBBBB);
  AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(fgRadioButtonSkinbg, bhover), 0xFFDDDDDD);
  AddStyleMsg<FG_SETFLAG, ptrdiff_t, size_t>(fgSkin_GetStyle(fgRadioSelectedSkin, bdefault), FGELEMENT_HIDDEN, 1);
  AddStyleMsg<FG_SETFLAG, ptrdiff_t, size_t>(fgSkin_GetStyle(fgRadioSelectedSkin, bchecked), FGELEMENT_HIDDEN, 0);

  // fgSlider
  AddStyleMsgArg<FG_SETPADDING, AbsRect>(&fgSliderSkin->style, &AbsRect { 5,0,5,0 });
  {
    fgStyleLayout* layout = fgSkin_GetChild(fgSliderSkin, fgSkin_AddChild(fgSliderSkin, "Curve", 0, FGCURVE_LINE, &fgTransform { { 0, 0, 0, 0.5, 0, 1.0, 1.0, 0.5 }, 0, { 0, 0, 0, 0 } }));
    AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(&layout->style, 0xFFFFFFFF);
  }
  fgSkin* fgSliderDragSkin = fgSkinBase_AddSkin(&fgSliderSkin->base, "Slider$slider");
  fnAddRect(fgSliderDragSkin, 0, CRect { 5, 0, 5, 0, 5, 0, 5, 0 }, fgTransform { { 0, 0, 0, 0, 10, 0, 20, 0 }, 0, { 0, 0, 0, 0 } }, 0xFFFFFFFF, 0xFF666666, 1.0f, FGELEMENT_NOCLIP);

  // fgProgressbar
  AddStyleMsgArg<FG_SETPADDING, AbsRect>(&fgProgressbarSkin->style, &AbsRect { 0,0,0,0 });
  fnAddRect(fgProgressbarSkin, 0, CRect { 6, 0, 6, 0, 6, 0, 6, 0 }, FILL_TRANSFORM, 0, 0xFFDDDDDD, 3.0f, FGELEMENT_BACKGROUND);
  fgSkin* fgProgressSkin = fgSkinBase_AddSkin(&fgProgressbarSkin->base, "Progressbar$bar");
  fnAddRect(fgProgressSkin, 0, CRect { 6, 0, 6, 0, 6, 0, 6, 0 }, FILL_TRANSFORM, 0xFF333333, 0, 3.0f, 0);

  // fgBox
  fgSkin* fgBoxSkin = fgSkinBase_AddSkin(&fgWindowSkin->base, "Box");
  fgBoxSkin->inherit = fgScrollbarSkin;
  fgSkin* fgScrollbarSkinBGx = fgSkinBase_AddSkin(&fgScrollbarSkin->base, "Scrollbar$horzbg");
  fgSkin* fgScrollbarSkinBGy = fgSkinBase_AddSkin(&fgScrollbarSkin->base, "Scrollbar$vertbg");
  fgSkin* fgScrollbarSkinBG = fgSkinBase_AddSkin(&fgScrollbarSkin->base, "Scrollbar$corner");
  AddStyleMsgArg<FG_SETAREA, CRect>(&fgScrollbarSkinBGx->style, &CRect { 0, 0, -20, 1, 0, 1, 0, 1 });
  AddStyleMsgArg<FG_SETAREA, CRect>(&fgScrollbarSkinBGy->style, &CRect { -20, 1, 0, 0, 0, 1, 0, 1 });
  AddStyleMsgArg<FG_SETPADDING, AbsRect>(&fgScrollbarSkinBGx->style, &AbsRect { 20, 0, 20, 0 });
  AddStyleMsgArg<FG_SETPADDING, AbsRect>(&fgScrollbarSkinBGy->style, &AbsRect { 0, 20, 0, 20 });
  fnAddRect(fgScrollbarSkinBGx, 0, CRect { 0, 0, 0, 0, 0, 0, 0, 0 }, FILL_TRANSFORM, 0x66000000, 0, 0.0f, FGELEMENT_BACKGROUND | FGELEMENT_IGNORE);
  fnAddRect(fgScrollbarSkinBGy, 0, CRect { 0, 0, 0, 0, 0, 0, 0, 0 }, FILL_TRANSFORM, 0x66000000, 0, 0.0f, FGELEMENT_BACKGROUND | FGELEMENT_IGNORE);
  fnAddRect(fgScrollbarSkinBG, 0, CRect { 0, 0, 0, 0, 0, 0, 0, 0 }, FILL_TRANSFORM, 0x66000000, 0, 0.0f, FGELEMENT_BACKGROUND | FGELEMENT_IGNORE);
  fgSkin* fgScrollbarSkinBarx = fgSkinBase_AddSkin(&fgScrollbarSkin->base, "Scrollbar$scrollhorz");
  fgSkin* fgScrollbarSkinBary = fgSkinBase_AddSkin(&fgScrollbarSkin->base, "Scrollbar$scrollvert");
  AddStyleMsgArg<FG_SETAREA, CRect>(&fgScrollbarSkinBarx->style, &CRect { 0, 0, 0, 0, 0, 1, 0, 1 });
  AddStyleMsgArg<FG_SETAREA, CRect>(&fgScrollbarSkinBary->style, &CRect { 0, 0, 0, 0, 0, 1, 0, 1 });
  fnAddRect(fgScrollbarSkinBarx, "#scrollbg", CRect { 6, 0, 6, 0, 6, 0, 6, 0 }, FILL_TRANSFORM, 0x660000FF, 0xFF0000FF, 1.0f, FGELEMENT_BACKGROUND | FGELEMENT_IGNORE);
  fnAddRect(fgScrollbarSkinBary, "#scrollbg", CRect { 6, 0, 6, 0, 6, 0, 6, 0 }, FILL_TRANSFORM, 0x660000FF, 0xFF0000FF, 1.0f, FGELEMENT_BACKGROUND | FGELEMENT_IGNORE);
  fgSkin* fgScrollbarSkinLeft = fgSkinBase_AddSkin(&fgScrollbarSkin->base, "Scrollbar$scrollleft");
  fgSkin* fgScrollbarSkinTop = fgSkinBase_AddSkin(&fgScrollbarSkin->base, "Scrollbar$scrolltop");
  fgSkin* fgScrollbarSkinRight = fgSkinBase_AddSkin(&fgScrollbarSkin->base, "Scrollbar$scrollright");
  fgSkin* fgScrollbarSkinBottom = fgSkinBase_AddSkin(&fgScrollbarSkin->base, "Scrollbar$scrollbottom");
  AddStyleMsgArg<FG_SETAREA, CRect>(&fgScrollbarSkinLeft->style, &CRect { 0, 0, 0, 0, 20, 0, 20, 0 });
  AddStyleMsgArg<FG_SETAREA, CRect>(&fgScrollbarSkinTop->style, &CRect { 0, 0, 0, 0, 20, 0, 20, 0 });
  AddStyleMsgArg<FG_SETAREA, CRect>(&fgScrollbarSkinRight->style, &CRect { -20, 1, 0, 0, 0, 1, 20, 0 });
  AddStyleMsgArg<FG_SETAREA, CRect>(&fgScrollbarSkinBottom->style, &CRect { 0, 0, -20, 1, 20, 0, 0, 1 });
  fnAddRect(fgScrollbarSkinLeft, "#scrollbg", CRect { 6, 0, 6, 0, 6, 0, 6, 0 }, FILL_TRANSFORM, 0, 0xFF0000FF, 1.0f, FGELEMENT_BACKGROUND);
  fnAddRect(fgScrollbarSkinTop, "#scrollbg", CRect { 6, 0, 6, 0, 6, 0, 6, 0 }, FILL_TRANSFORM, 0, 0xFF0000FF, 1.0f, FGELEMENT_BACKGROUND);
  fnAddRect(fgScrollbarSkinRight, "#scrollbg", CRect { 6, 0, 6, 0, 6, 0, 6, 0 }, FILL_TRANSFORM, 0, 0xFF0000FF, 1.0f, FGELEMENT_BACKGROUND);
  fnAddRect(fgScrollbarSkinBottom, "#scrollbg", CRect { 6, 0, 6, 0, 6, 0, 6, 0 }, FILL_TRANSFORM, 0, 0xFF0000FF, 1.0f, FGELEMENT_BACKGROUND);

  auto disabledskin = [](fgSkin* parent, const char* name, uint32_t nuetral, uint32_t disabled) {
    fgSkin* s = fgSkinBase_AddSkin(&parent->base, name);
    size_t sdisabled = fgSkin_AddStyle(s, "disabled");
    size_t snuetral = fgSkin_AddStyle(s, "nuetral");
    AddStyleSubMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(s, sdisabled), FGSETCOLOR_EDGE, disabled);
    AddStyleSubMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(s, snuetral), FGSETCOLOR_EDGE, nuetral);
  };

  disabledskin(fgScrollbarSkinLeft, "#scrollbg", 0xFF0000FF, 0xFF999999);
  disabledskin(fgScrollbarSkinTop, "#scrollbg", 0xFF0000FF, 0xFF999999);
  disabledskin(fgScrollbarSkinRight, "#scrollbg", 0xFF0000FF, 0xFF999999);
  disabledskin(fgScrollbarSkinBottom, "#scrollbg", 0xFF0000FF, 0xFF999999);
  disabledskin(fgScrollbarSkinBarx, "#scrollbg", 0xFF0000FF, 0xFF999999);
  disabledskin(fgScrollbarSkinBary, "#scrollbg", 0xFF0000FF, 0xFF999999);

  // fgTextbox
  fgTextboxSkin->inherit = fgScrollbarSkin;
  fnAddRect(fgTextboxSkin, "#textbg", CRect { 3, 0, 3, 0, 3, 0, 3, 0 }, FILL_TRANSFORM, 0x99000000, 0xFFAAAAAA, 1.0f, FGELEMENT_BACKGROUND | FGELEMENT_IGNORE);
  AddStyleMsg<FG_SETLINEHEIGHT, float>(&fgTextboxSkin->style, 16.0f);
  AddStyleSubMsg<FG_SETCOLOR, ptrdiff_t>(&fgTextboxSkin->style, FGSETCOLOR_PLACEHOLDER, 0x88FFFFFF);
  AddStyleSubMsg<FG_SETCOLOR, ptrdiff_t>(&fgTextboxSkin->style, FGSETCOLOR_CURSOR, 0xFFFFFFFF);
  AddStyleSubMsg<FG_SETCOLOR, ptrdiff_t>(&fgTextboxSkin->style, FGSETCOLOR_SELECT, 0xAAAA0000);
  AddStyleMsgArg<FG_SETPADDING, AbsRect>(&fgTextboxSkin->style, &AbsRect { 3, 3, 3, 3 });

  // fgTreeView
  fnAddRect(fgTreeViewSkin, 0, CRect { 3, 0, 3, 0, 3, 0, 3, 0 }, FILL_TRANSFORM, 0x99000000, 0xFFAAAAAA, 1.0f, FGELEMENT_BACKGROUND | FGELEMENT_IGNORE);
  fgSkin* fgTreeViewTextSkin = fgSkinBase_AddSkin(&fgTreeViewSkin->base, "Text");
  AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(&fgTreeViewTextSkin->style, 0xFFFFFFFF);
  AddStyleMsg<FG_SETFONT, void*>(&fgTreeViewTextSkin->style, smfont);
  fgSkin* fgTreeItemSkin = fgSkinBase_AddSkin(&fgTreeViewSkin->base, "TreeItem");
  fnAddRect(fgTreeItemSkin, "#bg", CRect { 2, 0, 2, 0, 2, 0, 2, 0 }, FILL_TRANSFORM, 0x99AA6666, 0xAAFFAAAA, 1.0f, FGELEMENT_BACKGROUND | FGELEMENT_IGNORE);
  AddStyleMsgArg<FG_SETPADDING, AbsRect>(&fgTreeItemSkin->style, &AbsRect { 20, 0, 0, 0 });
  fgSkin* fgTreeItemArrowSkin = fgSkinBase_AddSkin(&fgTreeItemSkin->base, "TreeItem$arrow");
  AddStyleMsgArg<FG_SETTRANSFORM, fgTransform>(&fgTreeItemArrowSkin->style, &fgTransform { { 4, 0, 1, 0, 16, 0, 13, 0 }, 0, { 0, 0, 0, 0 } });
  fnAddRect(fgTreeItemArrowSkin, "#bg", CRect { 3, 0, 3, 0, 3, 0, 3, 0 }, FILL_TRANSFORM, 0, 0xFFDDDDDD, 1.0f, FGELEMENT_BACKGROUND | FGELEMENT_IGNORE);
  fnAddRect(fgTreeItemArrowSkin, "#bgv", CRect { 0, 0, 0, 0, 0, 0, 0, 0 }, fgTransform { { -1, 0.5, 2, 0, 1, 0.5, -2, 1 }, 0, { 0, 0, 0, 0 } }, 0xFFDDDDDD, 0, 0.0f, FGELEMENT_BACKGROUND | FGELEMENT_IGNORE);
  fnAddRect(fgTreeItemArrowSkin, "#bgh", CRect { 0, 0, 0, 0, 0, 0, 0, 0 }, fgTransform { { 2, 0, -1, 0.5, -2, 1, 1, 0.5 }, 0, { 0, 0, 0, 0 } }, 0xFFDDDDDD, 0, 0.0f, FGELEMENT_BACKGROUND | FGELEMENT_IGNORE);

  fgSkin* fgTreeItemArrowSkinbg = fgSkinBase_AddSkin(&fgTreeItemArrowSkin->base, "#bgv");
  size_t shidden = fgSkin_AddStyle(fgTreeItemArrowSkinbg, "hidden");
  size_t svisible = fgSkin_AddStyle(fgTreeItemArrowSkinbg, "visible");
  AddStyleMsg<FG_SETFLAG, ptrdiff_t, size_t>(fgSkin_GetStyle(fgTreeItemArrowSkinbg, shidden), FGELEMENT_HIDDEN, 0);
  AddStyleMsg<FG_SETFLAG, ptrdiff_t, size_t>(fgSkin_GetStyle(fgTreeItemArrowSkinbg, svisible), FGELEMENT_HIDDEN, 1);

  fgSkin* fgTreeItemSkinbg = fgSkinBase_AddSkin(&fgTreeItemSkin->base, "#bg");
  size_t sfocus = fgSkin_AddStyle(fgTreeItemSkinbg, "nuetral+focused");
  bnuetral = fgSkin_AddStyle(fgTreeItemSkinbg, "nuetral");
  AddStyleMsg<FG_SETFLAG, ptrdiff_t, size_t>(fgSkin_GetStyle(fgTreeItemSkinbg, sfocus), FGELEMENT_HIDDEN, 0);
  AddStyleMsg<FG_SETFLAG, ptrdiff_t, size_t>(fgSkin_GetStyle(fgTreeItemSkinbg, bnuetral), FGELEMENT_HIDDEN, 1);

  // fgList
  fnAddRect(fgListSkin, "#listbg", CRect { 3, 0, 3, 0, 3, 0, 3, 0 }, FILL_TRANSFORM, 0x99000000, 0xFFAAAAAA, 1.0f, FGELEMENT_BACKGROUND | FGELEMENT_IGNORE);

  // ListItem
  fgSkin* listitemskin = fgSkinBase_AddSkin(&skin.base, "listitem");
  fnAddRect(listitemskin, "#listbg", CRect { 3, 0, 3, 0, 3, 0, 3, 0 }, FILL_TRANSFORM, 0x99009999, 0xFFAAAAAA, 1.0f, FGELEMENT_BACKGROUND | FGELEMENT_IGNORE);
  fgSkin* listitembgskin = fgSkinBase_AddSkin(&listitemskin->base, "#listbg");

  bhover = fgSkin_AddStyle(listitembgskin, "hover");
  bnuetral = fgSkin_AddStyle(listitembgskin, "nuetral");
  AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(listitembgskin, bnuetral), 0x99009900);
  AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(listitembgskin, bhover), 0x99990099);
  AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(listitembgskin, fgSkin_AddStyle(listitembgskin, "nuetral+selected")), 0x99999900);
  AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(listitembgskin, fgSkin_AddStyle(listitembgskin, "hover+selected")), 0xCC999900);

  // fgDropdown
  fnAddRect(fgDropdownSkin, "#dropdownbg", CRect { 3, 0, 3, 0, 3, 0, 3, 0 }, FILL_TRANSFORM, 0x99000000, 0xFFAAAAAA, 1.0f, FGELEMENT_BACKGROUND | FGELEMENT_IGNORE);
  fgSkin* dropdownboxskin = fgSkinBase_AddSkin(&fgDropdownSkin->base, "fgDropdown$box");
  dropdownboxskin->inherit = fgScrollbarSkin;
  fnAddRect(dropdownboxskin, "#dropdownboxbg", CRect { 3, 0, 3, 0, 3, 0, 3, 0 }, FILL_TRANSFORM, 0x99000000, 0xFFAAAAAA, 1.0f, FGELEMENT_BACKGROUND | FGELEMENT_IGNORE);
  AddStyleSubMsg<FG_SETCOLOR, ptrdiff_t>(&fgDropdownSkin->style, FGSETCOLOR_HOVER, 0x99990099);
  AddStyleSubMsg<FG_SETCOLOR, ptrdiff_t>(&fgDropdownSkin->style, FGSETCOLOR_SELECT, 0xAAAA0000);

  // fgTabControl
  //fnAddRect(fgTabControlSkin, "#tabcontrolbg", CRect { 3, 0, 3, 0, 3, 0, 3, 0 }, FILL_TRANSFORM, 0x99000000, 0xFFAAAAAA, 1.0f, FGELEMENT_BACKGROUND | FGELEMENT_IGNORE);
  //fgSkin* tabcontrolpanelskin = fgSkinBase_AddSkin(&fgTabControlSkin->base, "fgTabControl$panel");
  //fnAddRect(tabcontrolpanelskin, "#tabpanelbg", CRect { 3, 0, 3, 0, 3, 0, 3, 0 }, FILL_TRANSFORM, 0x99000000, 0xFFAAAAAA, 1.0f, FGELEMENT_BACKGROUND | FGELEMENT_IGNORE);
  fgSkin* tabcontroltoggleskin = fgSkinBase_AddSkin(&fgTabControlSkin->base, "fgTabControl$toggle");
  fnAddRect(tabcontroltoggleskin, "#tabtogglebg", CRect { 3, 0, 3, 0, 3, 0, 3, 0 }, FILL_TRANSFORM, 0x99000000, 0xFFAAAAAA, 1.0f, FGELEMENT_BACKGROUND | FGELEMENT_IGNORE);
  AddStyleSubMsg<FG_SETCOLOR, ptrdiff_t>(&tabcontroltoggleskin->style, FGSETCOLOR_MAIN, 0xFFFFFFFF);
  bdefault = fgSkin_AddStyle(tabcontroltoggleskin, "default");
  bchecked = fgSkin_AddStyle(tabcontroltoggleskin, "checked");
  AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(tabcontroltoggleskin, bdefault), 0xBBFFFFFF);
  AddStyleMsg<FG_SETCOLOR, ptrdiff_t>(fgSkin_GetStyle(tabcontroltoggleskin, bchecked), 0xFFFFFFFF);

  // Apply skin and set up layout
  fgVoidMessage(*fgSingleton(), FG_SETSKIN, &skin, 0);

  fgElement* res = fgResource_Create(fgCreateResourceFile(0, "../media/circle.png"), 0, 0xFFFFFFFF, 0, 0, 0, FGELEMENT_EXPAND | FGELEMENT_IGNORE, 0);
  fgElement* button = fgCreate("Button", *fgSingleton(), 0, 0, FGELEMENT_EXPAND, 0);
  fgVoidMessage(button, FG_ADDITEM, res, 0);
  button->SetName("buttontest");
  
  fgElement* topwindow = fgCreate("Window", *fgSingleton(), 0, 0, 0, &fgTransform { { 130, 0, 100, 0, 510, 0, 420, 0 }, 0, { 0, 0, 0, 0 } });
  topwindow->SetText("test window");
  topwindow->SetColor(0xFFFFFFFF, FGSETCOLOR_MAIN);
  topwindow->SetFont(font);
  topwindow->SetPadding(AbsRect { 10,22,10,10 });

  fgTabControl* tabs = (fgTabControl*)fgCreate("TabControl", topwindow, 0, 0, 0, &fgTransform { { 0, 0, 0, 0, 0, 1, 0, 1 }, 0, { 0, 0, 0, 0 } });
  fgElement* tab1 = tabs->AddItem("Tab 1");
  fgElement* tab2 = tabs->AddItem("Long Name Tab");
  fgElement* tab3 = tabs->AddItem("Tab 3");
  fgElement* tab4 = tabs->AddItem("Tab 4");
  tab1->GetSelectedItem()->Action();
  tab3->GetSelectedItem()->SetText("New Tab");

  fgElement* buttontop = fgCreate("Button", tab1, 0, 0, FGELEMENT_EXPAND, &fgTransform { { 10, 0, 10, 0, 0, 0, 0, 0 }, 0, { 0, 0, 0, 0 } });
  buttontop->SetText("Not Pressed");
  fgListener listener = [](fgElement* self, const FG_Msg*) { self->SetText("Pressed!"); };
  buttontop->AddListener(FG_ACTION, listener);

  fgElement* boxholder = fgCreate("Box", tab1, 0, 0, FGBOX_TILEY | FGELEMENT_EXPANDX, &fgTransform { { 10, 0, 160, 0, 150, 0, 240, 0 }, 0, { 0, 0, 0, 0 } });
  fgScrollbar* test = (fgScrollbar*)boxholder;
  boxholder->SetDim(100, -1);
  //boxholder->SetDim(-1, 100);

  fgCreate("Checkbox", boxholder, 0, 0, FGELEMENT_EXPAND, &fgTransform { { 0, 0, 0, 0, 0, 0, 0, 0 }, 0, { 0, 0, 0, 0 } })->SetText("Check Test 1");
  fgCreate("Checkbox", boxholder, 0, 0, FGELEMENT_EXPAND, &fgTransform { { 0, 0, 0, 0, 0, 0, 0, 0 }, 0, { 0, 0, 0, 0 } })->SetText("Check Test 22");
  fgCreate("Checkbox", boxholder, 0, 0, FGELEMENT_EXPAND, &fgTransform { { 0, 0, 0, 0, 0, 0, 0, 0 }, 0, { 0, 0, 0, 0 } })->SetText("Check Test 3");
  fgCreate("Checkbox", boxholder, 0, 0, FGELEMENT_EXPAND, &fgTransform { { 0, 0, 0, 0, 0, 0, 0, 0 }, 0, { 0, 0, 0, 0 } })->SetText("Check Test 4");
  fgCreate("Checkbox", boxholder, 0, 0, FGELEMENT_EXPAND, &fgTransform { { 0, 0, 0, 0, 0, 0, 0, 0 }, 0, { 0, 0, 0, 0 } })->SetText("Check Test 5");
  
  fgCreate("Radiobutton", tab1, 0, 0, FGELEMENT_EXPAND, &fgTransform { { 190, 0, 130, 0, 0, 0, 0, 0 }, 0, { 0, 0, 0, 0 } })->SetText("Radio Test 1");
  fgCreate("Radiobutton", tab1, 0, 0, FGELEMENT_EXPAND, &fgTransform { { 190, 0, 160, 0, 0, 0, 0, 0 }, 0, { 0, 0, 0, 0 } })->SetText("Radio Test 2");
  fgCreate("Radiobutton", tab1, 0, 0, FGELEMENT_EXPAND, &fgTransform { { 190, 0, 190, 0, 0, 0, 0, 0 }, 0, { 0, 0, 0, 0 } })->SetText("Radio Test 3");

  fgElement* slider = fgCreate("Slider", tab1, 0, 0, 0, &fgTransform { { 10, 0, 70, 0, 150, 0, 90, 0 }, 0, { 0, 0, 0, 0 } });
  slider->SetValue(500, 1);
  slider->AddListener(FG_SETVALUE, [](fgElement* self, const FG_Msg*) { fg_progbar->SetValueF(self->GetValueF(0) / self->GetValueF(1), 0); fg_progbar->SetText(cStrF("%i", self->GetValue(0))); });
  fg_progbar = fgProgressbar_Create(0.0, tab1, 0, 0, 0, &fgTransform { { 10, 0, 100, 0, 150, 0, 125, 0 }, 0, { 0, 0, 0, 0 } });

  fgElement* textbox = fgCreate("Textbox", tab2, 0, 0, FGTEXT_WORDWRAP, &fgTransform { { 140, 0, 30, 0, 210, 0, 150, 0 }, 0, { 0, 0, 0, 0 } });
  //textbox->SetText((const char*)8226, FGSETTEXT_MASK);
  textbox->SetText("placeholder", FGSETTEXT_PLACEHOLDER_UTF8);
  
  fgElement* list = fgCreate("List", *fgSingleton(), 0, 0, FGBOX_TILEY|FGELEMENT_EXPANDY| FGLIST_MULTISELECT, &fgTransform { { -350, 1.0, 30, 0, -250, 1.0, 0, 0 }, 0, { 0, 0, 0, 0 } });
  fgCreate("ListItem", list, 0, 0, 0, &fgTransform { { 0, 0, 0, 0, 0, 1.0, 20, 0 }, 0, { 0, 0, 0, 0 } });
  fgCreate("Text", list, 0, 0, 0, &fgTransform { { 0, 0, 0, 0, 0, 1.0, 20, 0 }, 0, { 0, 0, 0, 0 } })->SetText("List 1");
  fgCreate("Text", list, 0, 0, 0, &fgTransform { { 0, 0, 0, 0, 0, 1.0, 20, 0 }, 0, { 0, 0, 0, 0 } })->SetText("List 2");
  fgCreate("Text", list, 0, 0, 0, &fgTransform { { 0, 0, 0, 0, 0, 1.0, 20, 0 }, 0, { 0, 0, 0, 0 } })->SetText("List 3");
  fgCreate("Text", list, 0, 0, 0, &fgTransform { { 0, 0, 0, 0, 0, 1.0, 20, 0 }, 0, { 0, 0, 0, 0 } })->SetText("List 4");
  fgCreate("ListItem", list, 0, 0, 0, &fgTransform { { 0, 0, 0, 0, 0, 1.0, 20, 0 }, 0, { 0, 0, 0, 0 } });
  fgCreate("Text", list, 0, 0, 0, &fgTransform { { 0, 0, 0, 0, 0, 1.0, 20, 0 }, 0, { 0, 0, 0, 0 } })->SetText("List 5");
  
  fgElement* dropdown = fgCreate("Dropdown", tab3, 0, 0, FGBOX_TILEY, &fgTransform { { 10, 0, 260, 0, 150, 0, 290, 0 }, 0, { 0, 0, 0, 0 } });
  fgCreate("Text", dropdown, 0, 0, 0, &fgTransform { { 0, 0, 0, 0, 0, 1.0, 20, 0 }, 0, { 0, 0, 0, 0 } })->SetText("Drop 1");
  fgCreate("Text", dropdown, 0, 0, 0, &fgTransform { { 0, 0, 0, 0, 0, 1.0, 20, 0 }, 0, { 0, 0, 0, 0 } })->SetText("Drop 2");
  fgCreate("Text", dropdown, 0, 0, FGELEMENT_EXPAND, &fgTransform { { 0, 0, 0, 0, 0, 0, 0, 0 }, 0, { 0, 0, 0, 0 } })->SetText("Drop 3");
  fgCreate("Text", dropdown, 0, 0, 0, &fgTransform { { 0, 0, 0, 0, 0, 1.0, 20, 0 }, 0, { 0, 0, 0, 0 } })->SetText("Drop 4");
  dropdown->SetDim(-1, 60);

  fgSingleton()->behaviorhook = &fgRoot_BehaviorListener; // make sure the listener hash is enabled
  cHighPrecisionTimer time;

  /*std::function<size_t(const FG_Msg&)> guicallback = [&](const FG_Msg& evt) -> size_t
  {
    if(evt.type == FG_KEYDOWN || evt.type == FG_KEYUP)
    {
      bool isdown = evt.type == FG_KEYDOWN;
      switch(evt.keycode)
      {
      case FG_KEY_DOWN:
        fgSendSubMsg<FG_ACTION, float, float>(boxholder, FGSCROLLBAR_CHANGE, 0.0, -1.0);
        break;
      case FG_KEY_ESCAPE:
        if(isdown) engine->Quit();
        break;
      case FG_KEY_RETURN:
        if(isdown && !evt.IsAltDown()) gotonext = true;
        break;
      case FG_KEY_F11:
        if(isdown)
        {
          if(fgDebug_Get() != 0 && !(fgDebug_Get()->element.flags&FGELEMENT_HIDDEN))
            fgDebug_Hide();
          else
            fgDebug_Show(200, 200);
        }
      }
    }
    return 0;
  };

  engine->SetPreprocess(guicallback);*/
  
  //engine->GetMonitor()->element.SetFlags(FGWINDOW_RESIZABLE);
  while(!gotonext && engine->Begin())
  {
    engine->GetDriver()->Clear(0xFF000000);
    engine->GetGUI().Render();
    engine->End();
    engine->FlushMessages();
    fgRoot_Update(fgSingleton(), time.Update()*0.001);
    updatefpscount(timer, fps);
  }

  fgElement_Clear(*fgSingleton());
  fgSkin_Destroy(&skin);

  ENDTEST;
}