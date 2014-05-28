// Copyright �2014 Black Sphere Studios
// For conditions of distribution and use, see copyright notice in PlaneShader.h

#ifndef __ANI_H__PS__
#define __ANI_H__PS__

#include "bss-util/cAnimation.h"

namespace planeshader {
  class psAnimation : public bss_util::cAnimation<bss_util::StaticAllocPolicy<char>>, protected bss_util::LLBase<psAnimation>
  {
    typedef bss_util::cAnimation<bss_util::StaticAllocPolicy<char>> T_ANI;
    template<typename T> friend void BSS_FASTCALL bss_util::LLRemove(T*, T*&);
    template<typename T> friend void BSS_FASTCALL bss_util::LLAdd(T*, T*&);

  public:
    static psAnimation* aniroot;
    inline psAnimation(const psAnimation& copy) : T_ANI(copy) { next = prev = 0; }
    inline psAnimation(psAnimation&& mov) : T_ANI(std::move(mov)) { next = prev = 0; }
    inline psAnimation(const T_ANI& copy) : T_ANI(copy) { next = prev = 0; }
    inline psAnimation(T_ANI&& mov) : T_ANI(std::move(mov)) { next = prev = 0; }
    inline ~psAnimation() { if(prev!=0 || aniroot==this) LLRemove(this, aniroot); }
    inline void Start(double timepassed=0.0) { if(prev==0 && aniroot!=this) LLAdd(this, aniroot); T_ANI::Start(timepassed); }
    inline psAnimation& operator +=(const T_ANI& add) { T_ANI::operator+=(add); return *this; }
    inline const psAnimation operator +(const T_ANI& add) const { psAnimation r(*this); r+=add; return r; }
    inline psAnimation& operator=(const T_ANI& right) { T_ANI::operator=(right); return *this; }
    inline psAnimation& operator=(T_ANI&& right) { T_ANI::operator=(right); return *this; }

    static void AniInterpolate(double delta)
    {
      psAnimation* hold = aniroot;
      psAnimation* cur;
      while(cur=hold)
      {
        hold=cur->next;
        if(!cur->Interpolate(delta))
        {
          LLRemove(cur, aniroot);
          cur->prev=cur->next=0;
        }
      }
    }
  };

  class AbstractAni
  {
  protected:
    virtual void BSS_FASTCALL TypeIDRegFunc(bss_util::AniAttribute*)=0;
  };

  enum AniIDList : unsigned char
  {
    POSITION_ANI_TYPEID=0,
    SCALE_ANI_TYPEID,
    ROTATION_ANI_TYPEID,
    COLOR_ANI_TYPEID,
    TEXTURE_ANI_TYPEID,
    SOURCE_ANI_TYPEID,
    PIVOT_ANI_TYPEID,
    ZORDER_ANI_TYPEID,
    EVENT_ANI_TYPEID,
    NUM_ANI_TYPEIDS //If you are adding custom animation IDs, start here.
  };
}




#endif