// Copyright �2014 Black Sphere Studios
// For conditions of distribution and use, see copyright notice in PlaneShader.h

#ifndef __IMAGE_H__PS__
#define __IMAGE_H__PS__

#include "psTextured.h"
#include "psColored.h"
#include "psSolid.h"

namespace planeshader {
  struct DEF_IMAGE;

  // Represents a renderable image with UV source coordinates
  class PS_DLLEXPORT psImage : public psSolid, public psTextured, public psColored, public psDriverHold
  {
  public:
    psImage(const psImage& copy);
    psImage(psImage&& mov);
    psImage(const DEF_IMAGE& def);
    virtual ~psImage();
    explicit psImage(psTex* tex = 0, const psVec3D& position=VEC3D_ZERO, FNUM rotation=0.0f, const psVec& pivot=VEC_ZERO, FLAG_TYPE flags=0, int zorder=0, psStateblock* stateblock=0, psShader* shader=0, psPass* pass = 0, psInheritable* parent=0, const psVec& scale=VEC_ONE, unsigned int color=0xFFFFFFFF);
    explicit psImage(const char* file, const psVec3D& position=VEC3D_ZERO, FNUM rotation=0.0f, const psVec& pivot=VEC_ZERO, FLAG_TYPE flags=0, int zorder=0, psStateblock* stateblock=0, psShader* shader=0, psPass* pass = 0, psInheritable* parent=0, const psVec& scale=VEC_ONE, unsigned int color=0xFFFFFFFF);
    void AddSource(const psRect& r = RECT_UNITRECT);
    void ClearSources();
    inline psRect GetSource(unsigned int index=0) const { if(index>=_uvs.Size() || index >= _tex.Size()) return RECT_ZERO; return _uvs[index]*_tex[index]->GetDim(); }
    inline const psRect& GetRelativeSource(unsigned int index=0) const { return _uvs[index]; }
    inline const psRect* GetRelativeSources() const { return _uvs; }
    inline void SetRelativeSource(const psRect& uv, unsigned int index=0) { if(index<_rts.Size()) _uvs[index] = uv; }
    inline void SetSource(const psRect& uv, unsigned int index=0) { if(index<_uvs.Size() && index<_tex.Size()) _uvs[index] = uv/_tex[index]->GetDim(); }
    unsigned char NumSources() const { return _uvs.Size(); }
    virtual psTex* const* GetTextures() const { return psTextured::GetTextures(); }
    virtual unsigned char NumTextures() const { return psTextured::NumTextures(); }
    virtual psTex* const* GetRenderTargets() const { return psTextured::GetRenderTargets(); }
    virtual unsigned char NumRT() const { return psTextured::NumRT(); }

    psImage& operator =(const psImage& right);
    psImage& operator =(psImage&& right);

  protected:
    virtual void _render();
    virtual void BSS_FASTCALL _renderbatch(psRenderable** rlist, unsigned int count);
    virtual bool BSS_FASTCALL _batch(psRenderable* r) const;
    void _setuvs(unsigned int size);

    bss_util::cArray<psRect, unsigned char> _uvs;
  };

  struct BSS_COMPILER_DLLEXPORT DEF_IMAGE : DEF_SOLID, DEF_TEXTURED, DEF_COLORED
  {
    inline virtual psImage* BSS_FASTCALL Spawn() const { return new psImage(*this); } //This creates a new instance of whatever class this definition defines
    inline virtual DEF_IMAGE* BSS_FASTCALL Clone() const { return new DEF_IMAGE(*this); }

    std::vector<psRect> sources;
  };
}

#endif