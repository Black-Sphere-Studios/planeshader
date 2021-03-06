// Copyright �2018 Black Sphere Studios
// For conditions of distribution and use, see copyright notice in ps_dec.h

#ifndef __VECTOR_H__PS__
#define __VECTOR_H__PS__

#include "psSolid.h"
#include "psColor.h"
#include "bss-util/DynArray.h"

namespace planeshader {
  // Used by all curve objects to render a curve as a deconstructed quadratic curve
  class PS_DLLEXPORT psQuadraticHull : public psRenderable, public psDriverHold
  {
    struct QuadVertex
    {
      float x, y, z, t;
      float p0[4];
      float p1[4];
      float p2[4];
      uint32_t color;
    };

  public:
    psQuadraticHull();
    ~psQuadraticHull();
    void Clear();
    void AppendQuadraticCurve(psVec p0, psVec p1, psVec p2, float thickness, uint32_t color, char cap);

    static const int CURVEBUFSIZE = 512 * 3;
    static inline psVec FromQuad(QuadVertex& v) { return psVec(v.x, v.y); }
    static void SetVert(float(&v)[4], psVec& x, float thickness);

  protected:
    virtual void _render(const psTransform2D& parent) override;
    bss::DynArray<QuadVertex, uint32_t> _verts;
  };

  class PS_DLLEXPORT psQuadraticCurve : public psQuadraticHull
  {
  public:
    psQuadraticCurve(psVec p0, psVec p1, psVec p2, float thickness = 1.0f, uint32_t color = 0xFFFFFFFF);
    psQuadraticCurve(psVec(&p)[3], float thickness = 1.0f, uint32_t color = 0xFFFFFFFF);
    ~psQuadraticCurve();
    void Set(psVec p0, psVec p1, psVec p2);
    void Set(psVec (&p)[3]);
    inline void SetThickness(float thickness) { _thickness = thickness; }
    inline float GetThickness() const { return _thickness; }
    inline const psVec(&Get() const)[3] { return _p; }
    inline psColor32 GetColor() const { return _color; }
    inline void SetColor(psColor32 color) { _color = color; }

  protected:
    psVec _p[3];
    float _thickness;
    psColor32 _color;
  };

  class PS_DLLEXPORT psCubicCurve : public psQuadraticHull
  {
  public:
    psCubicCurve(psVec p0, psVec p1, psVec p2, psVec p3, float thickness = 1.0f, uint32_t color = 0xFFFFFFFF, float maxerr = 1.0f);
    psCubicCurve(psVec(&p)[4], float thickness = 1.0f, uint32_t color = 0xFFFFFFFF);
    ~psCubicCurve();
    void Set(psVec p0, psVec p1, psVec p2, psVec p3);
    void Set(psVec(&p)[4]);
    inline void SetThickness(float thickness) { _thickness = thickness; }
    inline float GetThickness() const { return _thickness; }
    inline const psVec(&Get() const)[4] { return _p; }
    inline psColor32 GetColor() const { return _color; }
    inline void SetColor(psColor32 color) { _color = color; }

  protected:
    void _addquad(const float(&P0)[2], const float(&P1)[2], const float(&P2)[2]);
    psVec _p[4];
    float _thickness;
    float _maxerr;
    psColor32 _color;
  };

  class PS_DLLEXPORT psRoundRect : public psSolid, public psDriverHold
  {
    struct RRVertex
    {
      float x, y, z, t;
      psRect dimpivot;
      psRect corners;
      float outline;
      uint32_t color;
      uint32_t outlinecolor;
    };

  public:
    psRoundRect(const psRoundRect& copy);
    psRoundRect(psRoundRect&& mov);
    explicit psRoundRect(const psRectRotateZ& rect = psRectRotateZ(0, 0, 0, 0, 0, VEC_ZERO, 0), psFlag flags = 0, int zorder = 0, psStateblock* stateblock = 0, psShader* shader = 0, psLayer* pass = 0, const psVec& scale = VEC_ONE);
    virtual ~psRoundRect();
    inline const psRect& GetCorners() const { return _corners; }
    inline void SetCorners(const psRect& corners) { _corners = corners; }
    inline float GetOutline() const { return _edge; }
    inline void SetOutline(float outline) { _edge = outline; }
    inline psColor32 GetOutlineColor() const { return _outline; }
    inline void SetOutlineColor(psColor32 color) { _outline = color; }
    inline psColor32 GetColor() const { return _color; }
    inline void SetColor(psColor32 color) { _color = color; }

    static const int RRBUFSIZE = 64;
    static void DrawRoundRect(psShader* shader, psStateblock* stateblock, const psRectRotateZ& rect, const psRect& corners, psFlag flags, psColor32 color32, psColor32 outline32, float edge);

    psRoundRect& operator=(const psRoundRect& copy);
    psRoundRect& operator=(psRoundRect&& mov);

  protected:
    virtual void _render(const psTransform2D& parent) override;

    psRect _corners;
    psColor32 _outline;
    psColor32 _color;
    float _edge;
  };

  class PS_DLLEXPORT psRoundTri : public psSolid, public psDriverHold
  {
    struct RRVertex
    {
      float x, y, z, t;
      psRect dimpivot;
      psRect corners;
      float outline;
      uint32_t color;
      uint32_t outlinecolor;
    };

  public:
    psRoundTri(const psRoundTri& copy);
    psRoundTri(psRoundTri&& mov);
    explicit psRoundTri(const psRectRotateZ& rect = psRectRotateZ(0, 0, 0, 0, 0, VEC_ZERO, 0), psFlag flags = 0, int zorder = 0, psStateblock* stateblock = 0, psShader* shader = 0, psLayer* pass = 0, const psVec& scale = VEC_ONE);
    virtual ~psRoundTri();
    inline const psRect& GetCorners() const { return _corners; }
    inline void SetCorners(const psRect& corners) { _corners = corners; }
    inline float GetOutline() const { return _edge; }
    inline void SetOutline(float outline) { _edge = outline; }
    inline psColor32 GetOutlineColor() const { return _outline; }
    inline void SetOutlineColor(psColor32 color) { _outline = color; }
    inline psColor32 GetColor() const { return _color; }
    inline void SetColor(psColor32 color) { _color = color; }

    static const int RTRIBUFSIZE = 64;
    static void DrawRoundTri(psShader* shader, psStateblock* stateblock, const psRectRotateZ& rect, const psRect& corners, psFlag flags, psColor32 color32, psColor32 outline32, float edge);

    psRoundTri& operator=(const psRoundTri& copy);
    psRoundTri& operator=(psRoundTri&& mov);

  protected:
    virtual void _render(const psTransform2D& parent) override;

    psRect _corners;
    psColor32 _outline;
    psColor32 _color;
    float _edge;
  };

  class PS_DLLEXPORT psRenderCircle : public psSolid, public psDriverHold
  {
    struct CircleVertex
    {
      float x, y, z, t;
      psRect dimpivot;
      psRect arcs;
      float outline;
      uint32_t color;
      uint32_t outlinecolor;
    };

  public:
    psRenderCircle(const psRenderCircle& copy);
    psRenderCircle(psRenderCircle&& mov);
    explicit psRenderCircle(float radius = 0, const psVec3D& position = VEC3D_ZERO, psFlag flags = 0, int zorder = 0, psStateblock* stateblock = 0, psShader* shader = 0, psLayer* pass = 0, const psVec& scale = VEC_ONE);
    virtual ~psRenderCircle();
    inline const psRect& GetArcs() const { return _arcs; }
    inline void SetArcs(const psRect& arcs) { _arcs = arcs; }
    inline float GetOutline() const { return _edge; }
    inline void SetOutline(float outline) { _edge = outline; }
    inline psColor32 GetOutlineColor() const { return _outline; }
    inline void SetOutlineColor(psColor32 color) { _outline = color; }
    inline psColor32 GetColor() const { return _color; }
    inline void SetColor(psColor32 color) { _color = color; }

    static const int CIRCLEBUFSIZE = 64;
    static void DrawCircle(psShader* shader, psStateblock* stateblock, const psRectRotateZ& rect, const psRect& arcs, psFlag flags, psColor32 color32, psColor32 outline32, float edge);

    psRenderCircle& operator=(const psRenderCircle& copy);
    psRenderCircle& operator=(psRenderCircle&& mov);

  protected:
    virtual void _render(const psTransform2D& parent) override;

    psRect _arcs;
    psColor32 _outline;
    psColor32 _color;
    float _edge;
  };
}

#endif