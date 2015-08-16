// Copyright �2015 Black Sphere Studios
// For conditions of distribution and use, see copyright notice in PlaneShader.h

#ifndef __TEXT_H__PS__
#define __TEXT_H__PS__

#include "psTexFont.h"
#include "psSolid.h"
#include "psColored.h"
#include "bss-util\cStr.h"
#include "bss-util\cArraySort.h"

namespace planeshader {
  struct DEF_TEXT;

  class PS_DLLEXPORT psText : public psSolid, public psColored
  {
  public:
    psText(const psText& copy);
    psText(psText&& mov);
    psText(const DEF_TEXT& def);
    explicit psText(psTexFont* font=0, const char* text = 0, const psVec3D& position = VEC3D_ZERO, FNUM rotation = 0.0f, const psVec& pivot = VEC_ZERO, FLAG_TYPE flags = 0, int zorder = 0, psStateblock* stateblock = 0, psShader* shader = 0, psPass* pass = 0, psInheritable* parent = 0, const psVec& scale = VEC_ONE);
    ~psText();
    // Get/Set the text to be rendered
    inline const int* GetText() const { return _text; }
    inline void SetText(const char* text) { _text = text; _recalcdim(); }
    // Get/Set font used
    inline psTexFont* GetFont() const { return const_cast<psTexFont*>((const psTexFont*)_font); }
    void SetFont(psTexFont* font);
    // Get/Set the dimensions of the textbox - a dimension of 0 will grow to contain the text.
    inline psVec GetSize() const { return _textdim; }
    inline void SetSize(psVec size) { _textdim = size; _recalcdim(); }
    // Get/Set letter spacing
    inline float GetLetterSpacing() const { return _letterspacing; }
    inline void SetLetterSpacing(float spacing) { _letterspacing = spacing; _recalcdim(); }
    // Get/Set draw flags
    inline unsigned short GetDrawFlags() const { return _drawflags; }
    inline void SetDrawFlags(unsigned short flags) { _drawflags = flags; }
    // Get/Set per-character modification function
    inline const psTexFont::DELEGATE& GetFunc() const { return _func; }
    inline void SetFunc(psTexFont::DELEGATE func) { _func = func; }

  protected:
    virtual void _render();
    void _recalcdim();

    cStrT<int> _text;
    bss_util::cAutoRef<psTexFont> _font;
    psVec _textdim;
    float _letterspacing;
    unsigned short _drawflags;
    psTexFont::DELEGATE _func;
  };

  struct BSS_COMPILER_DLLEXPORT DEF_TEXT : DEF_SOLID, DEF_COLORED
  {
    inline DEF_TEXT() : font(0), textdim(VEC_ZERO), letterspacing(0), drawflags(0), func(0,0) {}
    inline virtual psText* BSS_FASTCALL Spawn() const { return new psText(*this); } //LINKER ERRORS IF THIS DOESNT EXIST! - This should never be called (since the class itself is abstract), but we have to have it here to support inherited classes
    inline virtual DEF_TEXT* BSS_FASTCALL Clone() const { return new DEF_TEXT(*this); }

    cStr text;
    psTexFont* font;
    psVec textdim;
    float letterspacing;
    unsigned short drawflags;
    psTexFont::DELEGATE func;
  };
}
#endif