#include "Rge.h"

VALUE rb_mRGE;
VALUE rb_eRGEBaseError;
VALUE rb_eRGERuntimeError;
VALUE rb_eRGEAssertError;

static bool RgeRenderProc()
{
	return false;
}
static bool RgeGainFocusProc()
{
	/**
	 *	@callback
	 *
	 *	@call
	 *		Frame.activate
	 *
	 *	@desc
	 *		如果脚本中定义了Frame.activate方法，则窗口激活时会自动调用该方法。可用于继续播放声音等处理。
	 */
//	static ID activate = rb_intern("activate");
//	if (rb_respond_to(rb_mFrame, activate)) rb_funcall(rb_mFrame, activate, 0);

	return false;
}
static bool RgeLostFocusProc()
{
	/**
	 *	@callback
	 *
	 *	@call
	 *		Frame.deactivate
	 *
	 *	@desc
	 *		如果脚本中定义了Frame.deactivate方法，则窗口变为无效时会自动调用该方法。可用于暂停声音等处理。
	 */
//	static ID deactivate = rb_intern("deactivate");
//	if (rb_respond_to(rb_mFrame, deactivate)) rb_funcall(rb_mFrame, deactivate, 0);

	return false;
}

static VALUE dm_init_video_engine(VALUE mod)
{
	return Qtrue;
}

static VALUE dm_init_audio_engine(VALUE mod)
{
	return Qtrue;
}

static VALUE dm_init_all(VALUE mod)
{
	return C2RbBool(RTEST(dm_init_video_engine(mod)) && RTEST(dm_init_audio_engine(mod)));
}

static VALUE dm_quit(VALUE mod)
{
	static ID __id_exit = rb_intern("exit");
	rb_funcall(rb_mKernel, __id_exit, 0);

	return Qnil;	/* not reached */
}

void Init_mRGE()
{
	/**
	 *	@modulename
	 *		RGE
	 *
	 *	@desc
	 *		RGE引擎顶层模块，其他所有内部类都定义在该模块下。
	 */
	rb_mRGE = rb_define_module("RGE");

	rb_define_module_function(rb_mRGE, "init", (RbFunc)dm_init_all, 0);
	rb_define_module_function(rb_mRGE, "init_video", (RbFunc)dm_init_video_engine, 0);
	rb_define_module_function(rb_mRGE, "init_audio", (RbFunc)dm_init_audio_engine, 0);
	rb_define_module_function(rb_mRGE, "quit", (RbFunc)dm_quit, 0);

	/**
	 *	@const
	 *		VERSION
	 *	
	 *	@desc
	 *		RGE版本信息值。
	 */
	rb_define_const(rb_mRGE, "VERSION", rb_str_new2(RGE_VERSION));
	
	/**
	 *	@classname
	 *		BaseError
	 *
	 *	@desc
	 *		RGE中处理各种异常信息的基类。
	 */
	rb_eRGEBaseError = rb_define_class_under(rb_mRGE, "BaseError", rb_eStandardError);

	/**
	 *	@classname
	 *		RuntimeError
	 *
	 *	@desc
	 *		RGE中运行时异常类。
	 */
	rb_eRGERuntimeError = rb_define_class_under(rb_mRGE, "RuntimeError", rb_eRGEBaseError);

	/**
	 *	@classname
	 *		AssertError
	 *
	 *	@desc
	 *		RGE中断言异常的类。
	 */
	rb_eRGEAssertError = rb_define_class_under(rb_mRGE, "AssertError", rb_eRGEBaseError);
}
