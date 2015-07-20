// Copyright �2015 Black Sphere Studios
// For conditions of distribution and use, see copyright notice in PlaneShader.h

#include "psSolid.h"

using namespace planeshader;

psSolid::psSolid(const psSolid& copy) : psInheritable(copy), _scale(copy._scale), _dim(copy._dim), _realdim(copy._realdim), _collisionrect(copy._collisionrect), _boundingrect(copy._boundingrect) { _internalflags|=INTERNALFLAG_SOLID; }
psSolid::psSolid(psSolid&& mov) : psInheritable(std::move(mov)), _scale(mov._scale), _dim(mov._dim), _realdim(mov._realdim), _collisionrect(mov._collisionrect), _boundingrect(mov._boundingrect) { _internalflags|=INTERNALFLAG_SOLID; }

psSolid::psSolid(const DEF_SOLID& def, unsigned char internaltype) : psInheritable(def, internaltype), _dim(VEC_ONE), _realdim(VEC_ONE), _scale(VEC_ONE)
{ 
  _internalflags|=INTERNALFLAG_SOLID;
  psSolid::SetScale(def.scale);
  UpdateBoundingRect();
}

psSolid::psSolid(const psVec3D& position, FNUM rotation, const psVec& pivot, FLAG_TYPE flags, int zorder, psStateblock* stateblock, psShader* shader, psPass* pass, psInheritable* parent, const psVec& scale, unsigned char internaltype) :
  psInheritable(position, rotation, pivot, flags, zorder, stateblock, shader, pass, 0, internaltype), _dim(VEC_ONE), _realdim(VEC_ONE), _scale(VEC_ONE)
{
  _internalflags|=INTERNALFLAG_SOLID;
  psSolid::SetScale(scale);
  UpdateBoundingRect();
  SetParent(parent);
}

psSolid::~psSolid() { }

void psSolid::UpdateBoundingRect() 
{
  psVec3D pos;
  GetTotalPosition(pos);
  pos.xy -= _pivot;
  psVec hold(pos.xy); //This only works with nonnegative scales
  hold+=_dim;
  FNUM rot = GetTotalRotation();
  //if(_collisionrect.topleft == pos && _collisionrect.bottomright == hold && _collisionrect.rotation==rot && _collisionrect.pivot==_pivot && _collisionrect.z==pos.z)
  //  return false; //no update needed 
  _collisionrect.topleft=pos.xy;
  /*cVec holdleft(pos);
  cVec hold(pos); // This works for all scales
  hold+=_dim;
  if(holdleft.x>hold.x) rswap(holdleft.x,hold.x);
  if(holdleft.y>hold.y) rswap(holdleft.y,hold.y);
  GetTotalRotation();
  if(_collisionrect.topleft == holdleft && _collisionrect.bottomright == hold && _collisionrect.rotation==rot && _collisionrect.pivot==_pivot)
  return false; //no update needed
  _collisionrect.topleft=holdleft;*/
  _collisionrect.bottomright=hold;
  _collisionrect.rotation=rot;
  _collisionrect.pivot=_pivot;
  _collisionrect.z=pos.z;
  _boundingrect=_collisionrect.BuildAABB();
  //_internalflags&=(~2);
}

void BSS_FASTCALL psSolid::SetPass(psPass* pass) 
{
  UpdateBoundingRect();
  psInheritable::SetPass(pass);
}

void BSS_FASTCALL psSolid::SetDim(const psVec& dim) { _realdim = dim; _setdim(_scale*_realdim); }
void BSS_FASTCALL psSolid::SetScale(const psVec& scale) { _scale = scale; _setdim(_scale*_realdim); }

void BSS_FASTCALL psSolid::_setdim(const psVec& dim)
{
  if(_dim.x!=0 && _dim.y!=0 && dim.x!=0 && dim.y!=0) // If the dimensions are valid
    _pivot*=(dim/_dim); //Adjust center position
  _dim=dim;
}

psSolid& psSolid::operator =(const psSolid& right)
{
  psInheritable::operator =(right);
  _dim=right._dim;
  _scale=right._scale;
  _realdim=right._realdim;
  return *this; 
}
psSolid& psSolid::operator =(psSolid&& right)
{
  psInheritable::operator =(std::move(right));
  _dim=right._dim;
  _scale=right._scale;
  _realdim=right._realdim;
  return *this;
}

void BSS_FASTCALL psSolid::TypeIDRegFunc(bss_util::AniAttribute*)
{ 
  /*switch(p->typeID)
  {
  case SCALE_ANI_TYPEID:
    p->Attach(&AttrDefSmooth<POSITION_ANI_TYPEID>(&_scale, delegate<void, const cVec&>::From<cSolid, &cSolid::SetScale>(this)));
    break;
  case ZORDER_ANI_TYPEID:
    p->Attach(&AttrDefSmooth<POSITION_ANI_TYPEID>(&_zorder, delegate<void, int>::From<cRenderable, &cRenderable::SetZOrder>(this)));
    break;
  default:
    psInheritable::TypeIDRegFunc(p);
  }*/
}