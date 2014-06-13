// Copyright �2014 Black Sphere Studios
// For conditions of distribution and use, see copyright notice in PlaneShader.h

#ifndef __NULLDRIVER_H__PS__
#define __NULLDRIVER_H__PS__

#include "psDriver.h"

namespace planeshader {
  class BSS_COMPILER_DLLEXPORT psNullDriver : public psDriver
  {
  protected:
    inline psNullDriver() : psDriver(VEC_ZERO) {}

  public:
    // Begins a scene
    virtual bool Begin() { return true; }
    // Ends a scene
    virtual char End() { return 0; }
    // Draws a vertex object
    virtual void BSS_FASTCALL Draw(psVertObj* buf, float(&transform)[4][4], FLAG_TYPE flags) { }
    // Draws a rectangle
    virtual void BSS_FASTCALL DrawRect(const psRectRotateZ rect, const psRect& uv, const unsigned int(&vertexcolor)[4], const psTex* const* texes, unsigned char numtex, FLAG_TYPE flags) { }
    virtual void BSS_FASTCALL DrawRectBatchBegin(const psTex* const* texes, unsigned char numtex, unsigned int numrects, FLAG_TYPE flags, const float xform[4][4]) { }
    virtual void BSS_FASTCALL DrawRectBatch(const psRectRotateZ rect, const psRect& uv, const unsigned int(&vertexcolor)[4], FLAG_TYPE flags) { }
    virtual void DrawRectBatchEnd() { }
    // Draws a circle
    virtual void BSS_FASTCALL DrawCircle() { }
    // Draws a polygon
    virtual void BSS_FASTCALL DrawPolygon(const psVec* verts, FNUM Z, int num, unsigned long vertexcolor, FLAG_TYPE flags) { }
    // Draws points (which are always batch rendered)
    virtual void BSS_FASTCALL DrawPointsBegin(const psTex* texture, float size, FLAG_TYPE flags) { }
    virtual void BSS_FASTCALL DrawPoints(psVertex* particles, unsigned int num) { }
    virtual void DrawPointsEnd() { }
    // Draws lines (which are also always batch rendered)
    virtual void BSS_FASTCALL DrawLinesStart(int num, FLAG_TYPE flags) { }
    virtual void BSS_FASTCALL DrawLines(const cLineT<float>& line, float Z1, float Z2, unsigned long vertexcolor, FLAG_TYPE flags) { }
    virtual void DrawLinesEnd() { }
    // Applies a camera (if you need the current camera, look at the pass you belong to, not the driver)
    virtual void BSS_FASTCALL ApplyCamera(const psVec3D& pos, const psVec& pivot, FNUM rotation, const psRectiu& viewport) { }
    virtual void BSS_FASTCALL ApplyCamera3D(float(&m)[4][4], const psRectiu& viewport) { }
    // Draws a fullscreen quad
    virtual void DrawFullScreenQuad() { }
    // Gets/Sets the extent
    virtual const psVec& GetExtent() const { return VEC_ZERO; }
    virtual void BSS_FASTCALL SetExtent(float znear, float zfar) { }
    // Creates a vertex or index buffer
    virtual void* BSS_FASTCALL CreateBuffer(unsigned short bytes, unsigned int usage, const void* initdata=0) { return 0; }
    virtual void* BSS_FASTCALL LockBuffer(void* target, unsigned int flags) { return 0; }
    virtual void BSS_FASTCALL UnlockBuffer(void* target) { }
    // Creates a texture
    virtual void* BSS_FASTCALL CreateTexture(psVeciu dim, FORMATS format, unsigned int usage=USAGE_SHADER_RESOURCE, unsigned char miplevels=0, const void* initdata=0, void** additionalview=0) { return 0; }
    virtual void* BSS_FASTCALL LoadTexture(const char* path, unsigned int usage=USAGE_SHADER_RESOURCE, FORMATS format=FMT_UNKNOWN, unsigned char miplevels=0, void** additionalview=0) { return 0; }
    virtual void* BSS_FASTCALL LoadTextureInMemory(const void* data, size_t datasize, unsigned int usage=USAGE_SHADER_RESOURCE, FORMATS format=FMT_UNKNOWN, unsigned char miplevels=0, void** additionalview=0) { return 0; }
    // Pushes or pops a scissor rect on to the stack
    virtual void BSS_FASTCALL PushScissorRect(const psRectl& rect) { }
    virtual void PopScissorRect() { }
    // Sets the current rendertargets, setting all the rest to null.
    virtual void BSS_FASTCALL SetRenderTargets(const psTex* const* texes, unsigned char num, const psTex* depthstencil=0) { }
    // Sets shader constants
    virtual void BSS_FASTCALL SetShaderConstants(void* constbuf, SHADER_VER shader) { }
    // Sets textures for a given type of shader (in DX9 this is completely ignored)
    virtual void BSS_FASTCALL SetTextures(const psTex* const* texes, unsigned char num, SHADER_VER shader=PIXEL_SHADER_1_1) { }
    // Builds a stateblock from the given set of state changes
    virtual void* BSS_FASTCALL CreateStateblock(const STATEINFO* states) { return 0; }
    // Sets a given stateblock
    virtual void BSS_FASTCALL SetStateblock(void* stateblock) { }
    // Create a vertex layout from several element descriptions
    virtual void* BSS_FASTCALL CreateLayout(void* shader, const ELEMENT_DESC* elements, unsigned char num) { return 0; }
    virtual void BSS_FASTCALL SetLayout(void* layout) { }
    // Frees a created resource of the specified type
    virtual void BSS_FASTCALL FreeResource(void* p, psDriver::RESOURCE_TYPE t) { }
    virtual void BSS_FASTCALL GrabResource(void* p, psDriver::RESOURCE_TYPE t) { }
    virtual void BSS_FASTCALL CopyResource(void* dest, void* src, psDriver::RESOURCE_TYPE t) { }
    virtual void BSS_FASTCALL Resize(psVeciu dim, FORMATS format, bool fullscreen) { }
    // Gets a pointer to the driver implementation
    virtual RealDriver GetRealDriver() { RealDriver r; r.nul=this; r.type=RealDriver::DRIVERTYPE_NULL; return r; }

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