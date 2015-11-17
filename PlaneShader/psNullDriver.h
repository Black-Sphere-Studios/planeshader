// Copyright �2015 Black Sphere Studios
// For conditions of distribution and use, see copyright notice in PlaneShader.h

#ifndef __NULLDRIVER_H__PS__
#define __NULLDRIVER_H__PS__

#include "psDriver.h"

namespace planeshader {
  class BSS_COMPILER_DLLEXPORT psNullDriver : public psDriver, public psDriverHold
  {
  public:
    inline psNullDriver() : psDriver(VEC_ZERO)
    {
      _driver = this;
      psShader* nullshader = psShader::CreateShader(0, 0, 0, 0);

      library.IMAGE0 = nullshader;
      library.IMAGE = nullshader;
      library.IMAGE2 = nullshader;
      library.IMAGE3 = nullshader;
      library.IMAGE4 = nullshader;
      library.IMAGE5 = nullshader;
      library.IMAGE6 = nullshader;
      library.CIRCLE = nullshader;
      library.POLYGON = nullshader;
      library.LINE = nullshader;
      library.PARTICLE = nullshader;
    }
    inline ~psNullDriver()
    {
      library.IMAGE0->Drop();
    }
    // Begins a scene
    virtual bool Begin() { return true; }
    // Ends a scene
    virtual char End() { return 0; }
    // Draws a vertex object
    virtual void BSS_FASTCALL Draw(psVertObj* buf, FLAG_TYPE flags, const float(&transform)[4][4] = identity) { }
    // Draws a rectangle
    virtual void BSS_FASTCALL DrawRect(const psRectRotateZ rect, const psRect* uv, unsigned char numuv, unsigned int color, const psTex* const* texes, unsigned char numtex, FLAG_TYPE flags, const float(&xform)[4][4] = identity) { }
    virtual void BSS_FASTCALL DrawRectBatchBegin(const psTex* const* texes, unsigned char numtex, unsigned char numuv, FLAG_TYPE flags) { }
    virtual void BSS_FASTCALL DrawRectBatch(const psRectRotateZ rect, const psRect* uv, unsigned int color, const float(&xform)[4][4] = identity) { }
    virtual void DrawRectBatchEnd(const float(&xform)[4][4] = identity) { }
    // Draws a polygon
    virtual void BSS_FASTCALL DrawPolygon(const psVec* verts, int num, psVec3D offset, unsigned long vertexcolor, FLAG_TYPE flags, const float(&transform)[4][4] = identity) { }
    virtual void BSS_FASTCALL DrawPolygon(const psVertex* verts, int num, FLAG_TYPE flags, const float(&transform)[4][4] = identity) { }
    // Draws points (which are always batch rendered)
    virtual void BSS_FASTCALL DrawPointsBegin(const psTex* const* texes, unsigned char numtex, float size, FLAG_TYPE flags) { }
    virtual void BSS_FASTCALL DrawPoints(psVertex* particles, unsigned int num) { }
    virtual void DrawPointsEnd() { }
    // Draws lines (which are also always batch rendered)
    virtual void BSS_FASTCALL DrawLinesStart(FLAG_TYPE flags) { }
    virtual void BSS_FASTCALL DrawLines(const psLine& line, float Z1, float Z2, unsigned long vertexcolor, const float(&transform)[4][4] = identity) { }
    virtual void DrawLinesEnd(const float(&transform)[4][4] = identity) { }
    // Applies a camera (if you need the current camera, look at the pass you belong to, not the driver)
    virtual void BSS_FASTCALL PushCamera(const psVec3D& pos, const psVec& pivot, FNUM rotation, const psRectiu& viewport) { }
    virtual void BSS_FASTCALL PushCamera3D(const float(&m)[4][4], const psRectiu& viewport) { }
    virtual void BSS_FASTCALL PopCamera() {}
    // Applies the camera transform (or it's inverse) according to the flags to a point.
    psVec3D BSS_FASTCALL TransformPoint(const psVec3D& point, FLAG_TYPE flags) const { return VEC3D_ZERO; }
    psVec3D BSS_FASTCALL ReversePoint(const psVec3D& point, FLAG_TYPE flags) const { return VEC3D_ZERO; }
    // Draws a fullscreen quad
    virtual void DrawFullScreenQuad() { }
    // Gets/Sets the extent
    virtual const psVec& GetExtent() const { return VEC_ZERO; }
    virtual void BSS_FASTCALL SetExtent(float znear, float zfar) { }
    // Creates a vertex or index buffer
    virtual void* BSS_FASTCALL CreateBuffer(size_t bytes, unsigned int usage, const void* initdata=0) { return (void*)0xFFFFFFFF; }
    virtual void* BSS_FASTCALL LockBuffer(void* target, unsigned int flags) { return 0; }
    virtual void BSS_FASTCALL UnlockBuffer(void* target) { }
    virtual void* BSS_FASTCALL LockTexture(void* target, unsigned int flags, unsigned int& pitch, unsigned char miplevel = 0) { return 0; }
    virtual void BSS_FASTCALL UnlockTexture(void* target, unsigned char miplevel = 0) {}
    // Creates a texture
    virtual void* BSS_FASTCALL CreateTexture(psVeciu dim, FORMATS format, unsigned int usage=USAGE_SHADER_RESOURCE, unsigned char miplevels=0, const void* initdata=0, void** additionalview=0, psTexblock* texblock=0) { return (void*)0xFFFFFFFF; }
    virtual void* BSS_FASTCALL LoadTexture(const char* path, unsigned int usage=USAGE_SHADER_RESOURCE, FORMATS format=FMT_UNKNOWN, void** additionalview=0, unsigned char miplevels=0, FILTERS mipfilter = FILTER_BOX, FILTERS loadfilter = FILTER_NONE, psVeciu dim = VEC_ZERO, psTexblock* texblock=0, bool sRGB = false) { return (void*)0xFFFFFFFF; }
    virtual void* BSS_FASTCALL LoadTextureInMemory(const void* data, size_t datasize, unsigned int usage=USAGE_SHADER_RESOURCE, FORMATS format=FMT_UNKNOWN, void** additionalview=0, unsigned char miplevels=0, FILTERS mipfilter = FILTER_BOX, FILTERS loadfilter = FILTER_NONE, psVeciu dim = VEC_ZERO, psTexblock* texblock=0, bool sRGB = false) { return (void*)0xFFFFFFFF; }
    virtual void BSS_FASTCALL CopyTextureRect(const psRectiu* srcrect, psVeciu destpos, void* src, void* dest, unsigned char miplevel = 0) { }
    // Pushes or pops a scissor rect on to the stack
    virtual void BSS_FASTCALL PushScissorRect(const psRect& rect) { }
    virtual void PopScissorRect() { }
    // Sets the current rendertargets, setting all the rest to null.
    virtual void BSS_FASTCALL SetRenderTargets(const psTex* const* texes, unsigned char num, const psTex* depthstencil=0) { }
    // Sets shader constants
    virtual void BSS_FASTCALL SetShaderConstants(void* constbuf, SHADER_VER shader) { }
    // Sets textures for a given type of shader (in DX9 this is completely ignored)
    virtual void BSS_FASTCALL SetTextures(const psTex* const* texes, unsigned char num, SHADER_VER shader=PIXEL_SHADER_1_1) { }
    // Builds a stateblock from the given set of state changes
    virtual void* BSS_FASTCALL CreateStateblock(const STATEINFO* states, unsigned int count) { return 0; }
    // Builds a texblock from the given set of sampler states
    virtual void* BSS_FASTCALL CreateTexblock(const STATEINFO* states, unsigned int count) { return 0; }
    // Sets a given stateblock
    virtual void BSS_FASTCALL SetStateblock(void* stateblock) { }
    // Create a vertex layout from several element descriptions
    virtual void* BSS_FASTCALL CreateLayout(void* shader, const ELEMENT_DESC* elements, unsigned char num) { return 0; }
    virtual void BSS_FASTCALL SetLayout(void* layout) { }
    // Clears everything to a specified color
    virtual void BSS_FASTCALL Clear(unsigned int color) { }
    // Frees a created resource of the specified type
    virtual TEXTURE_DESC BSS_FASTCALL GetTextureDesc(void* t) { TEXTURE_DESC r ={ }; return r; }
    virtual void BSS_FASTCALL FreeResource(void* p, psDriver::RESOURCE_TYPE t) { }
    virtual void BSS_FASTCALL GrabResource(void* p, psDriver::RESOURCE_TYPE t) { }
    virtual void BSS_FASTCALL CopyResource(void* dest, void* src, psDriver::RESOURCE_TYPE t) { }
    virtual void BSS_FASTCALL Resize(psVeciu dim, FORMATS format, char fullscreen) { }
    virtual psTex* GetBackBuffer() { return 0; }
    // Gets a pointer to the driver implementation
    virtual RealDriver GetRealDriver() { RealDriver r; r.nul=this; r.type=RealDriver::DRIVERTYPE_NULL; return r; }
    // Gets/Sets the effective DPI
    virtual void SetDPI(psVeciu dpi = psVeciu(BASE_DPI)) { }
    virtual psVeciu GetDPI() { return psVeciu(0, 0); }

    // Compile a shader from a string
    virtual void* BSS_FASTCALL CompileShader(const char* source, SHADER_VER profile, const char* entrypoint="") { return 0; }
    // Create an actual shader object from compiled shader source (either precompiled or from CompileShader())
    virtual void* BSS_FASTCALL CreateShader(const void* data, SHADER_VER profile) { return 0; }
    // Sets current shader
    virtual char BSS_FASTCALL SetShader(void* shader, SHADER_VER profile) { return -1; }
    // Returns true if shader version is supported
    virtual bool BSS_FASTCALL ShaderSupported(SHADER_VER profile) { return false; }
  };
}

#endif