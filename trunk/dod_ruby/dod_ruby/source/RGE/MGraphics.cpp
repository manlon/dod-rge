#include "Rge.h"

#include <DOD_Gx.h>
#include <DOD_SceneManager.h>

VALUE	rb_mGraphics;

/**
 *	@call
 *		Graphics.update						-> nil
 *
 *	@desc
 *		更新游戏画面，前进 1 帧时间。这个方法应该在你游戏中每帧调用。
 */
static VALUE dm_update(VALUE module)
{
	Dod::Dod_GxBeginScene();
	Dod::Dod_GxGetSceneMgr()->Render();
	Dod::Dod_GxEndScene();
	
	return Qnil;
}

/**
 *	@call
 *		Graphics.wait(duration)				-> nil 。
 *
 *	@desc
 *		游戏画面等待duration帧。
 */
static VALUE dm_wait(VALUE module, VALUE duration)
{
	return Qnil;
}

/**
 *	@call
 *		Graphics.fadein(duration)				-> nil 。
 *
 *	@desc
 *		淡入游戏画面，duration为淡入的帧数。
 */
static VALUE dm_fadein(VALUE module, VALUE duration)
{
	return Qnil;
}

/**
 *	@call
 *		Graphics.fadeout(duration)				-> nil 。
 *
 *	@desc
 *		淡出游戏画面，duration为淡出的帧数。
 */
static VALUE dm_fadeout(VALUE module, VALUE duration)
{
	return Qnil;
}

/**
 *	@call
 *		Graphics.freezing?			-> true 或 false 。
 *
 *	@desc
 *		判断窗口是否处于freezing状态下。
 */
static VALUE dm_is_freezing(VALUE module)
{
	return Qnil;
}

/**
 *	@call
 *		Graphics.freeze					-> nil 。
 *
 *	@desc
 *		准备渐变，固定现在的画面。[ENDLINE]
 *		从这之后一直到调用 transition 方法，其间禁止一切画面更换。
 */
static VALUE dm_freeze(VALUE module)
{
	return Qnil;
}

/**
 *	@call
 *		Graphics.transition									-> nil 。
 *		Graphics.transition(duration)						-> nil 。
 *		Graphics.transition(duration, filename)				-> nil 。
 *		Graphics.transition(duration, filename, vague)		-> nil 。
 *
 *	@desc
 *		进行从以 freeze 方法固定的画面到现在画面的渐变。[ENDLINE]
 *		duration 是渐变的帧数。省略时默认为 8。[ENDLINE]
 *		filename 指定渐变图形的文件名（未指定文件名的话通常为画面淡出）。[ENDLINE]
 *		vague 是传送元和传送处边界的模糊度，数值越大越模糊。省略时默认为 40。
 */
static VALUE dm_transition(int argc,VALUE *argv,VALUE module)
{
	return Qnil;
}

/**
 *	@call
 *		Graphics.frame_reset						-> nil 。
 *
 *	@desc
 *		在RGE里无作用，仅为兼容RMXP而已。
 */
static VALUE dm_frame_reset(VALUE self)
{
	return Qnil;
}

/**
 *	@attr
 *
 *	@call
 *		Graphics.frame_rate			-> fixnum 对象。
 *		Graphics.frame_rate=		-> 新设置的fps数值。
 *
 *	@desc
 *		获取或设置RGE的运行帧率。
 */
static VALUE dm_get_frame_rate(VALUE module)
{
	return RUBY_0;
}

static VALUE dm_set_frame_rate(VALUE module, VALUE fps)
{
	return fps;
}

/**
 *	@attr
 *
 *	@call
 *		Graphics.frame_count			-> fixnum 对象。
 *		Graphics.frame_count=			-> nil 。
 *
 *	@desc
 *		获取或设置游戏的运行帧数，即Graphics.update调用的次数。
 */
static VALUE dm_get_frame_count(VALUE self)
{
	return RUBY_0;
}

static VALUE dm_set_frame_count(VALUE self, VALUE frame_count)
{
	return Qnil;
}

void Init_mGraphics()
{
	/**
	 *	@modulename
	 *
	 *		Graphics
	 *
	 *	@desc
	 *		管理RGE图形部分的模块。
	 */
	rb_mGraphics = rb_define_module_under(rb_mRGE, "Graphics");
	
	rb_define_module_function(rb_mGraphics, "update",	(RbFunc)dm_update, 0);

	rb_define_module_function(rb_mGraphics, "wait",		(RbFunc)dm_wait, 1);
	rb_define_module_function(rb_mGraphics, "fadein",	(RbFunc)dm_fadein, 1);
	rb_define_module_function(rb_mGraphics, "fadeout",	(RbFunc)dm_fadeout, 1);

	rb_define_module_function(rb_mGraphics, "freezing?",	(RbFunc)dm_is_freezing, 0);

	rb_define_module_function(rb_mGraphics, "freeze",		(RbFunc)dm_freeze, 0);
	rb_define_module_function(rb_mGraphics, "transition",	(RbFunc)dm_transition, -1);
	rb_define_module_function(rb_mGraphics, "frame_reset",	(RbFunc)dm_frame_reset, 0);

	rb_define_module_function(rb_mGraphics, "frame_rate",	(RbFunc)dm_get_frame_rate, 0);
	rb_define_module_function(rb_mGraphics, "frame_rate=",	(RbFunc)dm_set_frame_rate, 1);
	rb_define_module_function(rb_mGraphics, "frame_count",	(RbFunc)dm_get_frame_count, 0);
	rb_define_module_function(rb_mGraphics, "frame_count=",	(RbFunc)dm_set_frame_count, 1);
}
