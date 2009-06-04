#ifndef __C_RGE_SPRITE_H__
#define __C_RGE_SPRITE_H__

#include "CRgePlane.h"

#include "DOD_Sprite.h"

class CRgeSprite : protected CRgePlane
{
public:
	CRgeSprite();
	virtual ~CRgeSprite();
	
public:
	static void		Init();
	static VALUE	SpriteAllocate(VALUE klass);
	
protected:
	attr_accessor(x)
	attr_accessor(y)
	
private:
	Dod::DOD_Sprite*		m_pSprite;
};

#endif
