#ifndef __RGE_DECLARE_H__
#define __RGE_DECLARE_H__

extern	VALUE	rb_mRGE;
extern	VALUE	rb_eRGEBaseError;
extern	VALUE	rb_eRGERuntimeError;
extern	VALUE	rb_eRGEAssertError;
extern	VALUE	rb_mInput;
extern	VALUE	rb_mFrame;
extern	VALUE	rb_mGraphics;

extern	VALUE	rb_cBitmap;
extern	VALUE	rb_cColor;
extern	VALUE	rb_cDistortedSprite;
extern	VALUE	rb_cFlash;
extern	VALUE	rb_cFont;
extern	VALUE	rb_cPlane;
extern	VALUE	rb_cRect;
extern	VALUE	rb_cSprite;
extern	VALUE	rb_cTable;
extern	VALUE	rb_cTone;
extern	VALUE	rb_cViewport;
extern	VALUE	rb_cWindow;

void Init_mRGE();
void Init_mInput();
void Init_mGraphics();

#endif
