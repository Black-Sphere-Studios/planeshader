// Copyright �2014 Black Sphere Studios
// For conditions of distribution and use, see copyright notice in PlaneShader.h

#ifndef __FONT_H__PS__
#define __FONT_H__PS__

#include "psTexFont.h"
#include "bss-util/cStr.h"

typedef struct FT_FaceRec_*  FT_Face;
typedef struct FT_LibraryRec_* FT_Library;

namespace planeshader {
  // Represents a font loaded from an actual Opentype/Truetype/etc. font definition. An absolute path can be specified, or it will look for fonts installed in the operating system.
  class PS_DLLEXPORT psFont : public psTexFont
  {
  public:
    // Iterates through the string and preloads all the glyphs that are used. This is useful for common characters that you know will be loaded eventually. Returns the number of characters successfully loaded 
    unsigned short PreloadGlyphs(const char* glyphs);
    unsigned short PreloadGlyphs(const int* glyphs);

    static FT_Library PTRLIB;
    enum FONT_ANTIALIAS : unsigned char {
      FAA_NONE=0, //No antialiasing
      FAA_ANTIALIAS, //default antialiasing
      FAA_LCD, //antialiasing optimized for LCD displays
      FAA_LCD_V, //Same as above except for vertically oriented LCD displays
      FAA_LIGHT, //Antialiasing with a lighter technique
      FAA_SDF //Antialiasing using a Signed Distance Field. Requires using a shader that takes an SDF as input!
    };

    static psFont* Create(const char* file, int psize, float lineheight=0, FONT_ANTIALIAS antialias = FAA_ANTIALIAS);

  protected:
    psFont(const psFont&) = delete;
    psFont(const char* file, int psize, float lineheight=0, FONT_ANTIALIAS antialias = FAA_ANTIALIAS);
    ~psFont();
    virtual psGlyph* _loadglyph(unsigned int codepoint);
    psGlyph* _renderglyph(unsigned int codepoint);
    void _loadfont();
    void _cleanupfont();
    void _adjustantialias(FONT_ANTIALIAS antialiased);
    void _enforceantialias();
    void _stage();

    psFont& operator=(const psFont&) = delete;

    unsigned int _antialiased;
    int _pointsize;
    unsigned char* _buf;
    FT_Face _ft2face;
    psVeciu _curpos;
    unsigned int _nexty;
    unsigned char _curtex;
    cStr _path;
    cStr _hash;
    bss_util::cArray<psTex*, unsigned char> _staging;

    static bss_util::cHash<const char*, psFont*, true> _Fonts; //Hashlist of all fonts, done by file.
  };
}

#endif