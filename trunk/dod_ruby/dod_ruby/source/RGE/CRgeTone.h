#ifndef __C_RGE_TONE_H__
#define __C_RGE_TONE_H__

#include "CRgeColor.h"

class CRgeTone : public CRgeColor
{
public:
	static void		Init();
	static VALUE	ToneAllocate(VALUE klass);
};

#endif
