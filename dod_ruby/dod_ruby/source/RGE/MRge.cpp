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
	 *		����ű��ж�����Frame.activate�������򴰿ڼ���ʱ���Զ����ø÷����������ڼ������������ȴ���
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
	 *		����ű��ж�����Frame.deactivate�������򴰿ڱ�Ϊ��Чʱ���Զ����ø÷�������������ͣ�����ȴ���
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
	 *		RGE���涥��ģ�飬���������ڲ��඼�����ڸ�ģ���¡�
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
	 *		RGE�汾��Ϣֵ��
	 */
	rb_define_const(rb_mRGE, "VERSION", rb_str_new2(RGE_VERSION));
	
	/**
	 *	@classname
	 *		BaseError
	 *
	 *	@desc
	 *		RGE�д�������쳣��Ϣ�Ļ��ࡣ
	 */
	rb_eRGEBaseError = rb_define_class_under(rb_mRGE, "BaseError", rb_eStandardError);

	/**
	 *	@classname
	 *		RuntimeError
	 *
	 *	@desc
	 *		RGE������ʱ�쳣�ࡣ
	 */
	rb_eRGERuntimeError = rb_define_class_under(rb_mRGE, "RuntimeError", rb_eRGEBaseError);

	/**
	 *	@classname
	 *		AssertError
	 *
	 *	@desc
	 *		RGE�ж����쳣���ࡣ
	 */
	rb_eRGEAssertError = rb_define_class_under(rb_mRGE, "AssertError", rb_eRGEBaseError);
}
