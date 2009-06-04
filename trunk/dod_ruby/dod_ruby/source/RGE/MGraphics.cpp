#include "Rge.h"

#include <DOD_Gx.h>
#include <DOD_SceneManager.h>

VALUE	rb_mGraphics;

/**
 *	@call
 *		Graphics.update						-> nil
 *
 *	@desc
 *		������Ϸ���棬ǰ�� 1 ֡ʱ�䡣�������Ӧ��������Ϸ��ÿ֡���á�
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
 *		Graphics.wait(duration)				-> nil ��
 *
 *	@desc
 *		��Ϸ����ȴ�duration֡��
 */
static VALUE dm_wait(VALUE module, VALUE duration)
{
	return Qnil;
}

/**
 *	@call
 *		Graphics.fadein(duration)				-> nil ��
 *
 *	@desc
 *		������Ϸ���棬durationΪ�����֡����
 */
static VALUE dm_fadein(VALUE module, VALUE duration)
{
	return Qnil;
}

/**
 *	@call
 *		Graphics.fadeout(duration)				-> nil ��
 *
 *	@desc
 *		������Ϸ���棬durationΪ������֡����
 */
static VALUE dm_fadeout(VALUE module, VALUE duration)
{
	return Qnil;
}

/**
 *	@call
 *		Graphics.freezing?			-> true �� false ��
 *
 *	@desc
 *		�жϴ����Ƿ���freezing״̬�¡�
 */
static VALUE dm_is_freezing(VALUE module)
{
	return Qnil;
}

/**
 *	@call
 *		Graphics.freeze					-> nil ��
 *
 *	@desc
 *		׼�����䣬�̶����ڵĻ��档[ENDLINE]
 *		����֮��һֱ������ transition ����������ֹһ�л��������
 */
static VALUE dm_freeze(VALUE module)
{
	return Qnil;
}

/**
 *	@call
 *		Graphics.transition									-> nil ��
 *		Graphics.transition(duration)						-> nil ��
 *		Graphics.transition(duration, filename)				-> nil ��
 *		Graphics.transition(duration, filename, vague)		-> nil ��
 *
 *	@desc
 *		���д��� freeze �����̶��Ļ��浽���ڻ���Ľ��䡣[ENDLINE]
 *		duration �ǽ����֡����ʡ��ʱĬ��Ϊ 8��[ENDLINE]
 *		filename ָ������ͼ�ε��ļ�����δָ���ļ����Ļ�ͨ��Ϊ���浭������[ENDLINE]
 *		vague �Ǵ���Ԫ�ʹ��ʹ��߽��ģ���ȣ���ֵԽ��Խģ����ʡ��ʱĬ��Ϊ 40��
 */
static VALUE dm_transition(int argc,VALUE *argv,VALUE module)
{
	return Qnil;
}

/**
 *	@call
 *		Graphics.frame_reset						-> nil ��
 *
 *	@desc
 *		��RGE�������ã���Ϊ����RMXP���ѡ�
 */
static VALUE dm_frame_reset(VALUE self)
{
	return Qnil;
}

/**
 *	@attr
 *
 *	@call
 *		Graphics.frame_rate			-> fixnum ����
 *		Graphics.frame_rate=		-> �����õ�fps��ֵ��
 *
 *	@desc
 *		��ȡ������RGE������֡�ʡ�
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
 *		Graphics.frame_count			-> fixnum ����
 *		Graphics.frame_count=			-> nil ��
 *
 *	@desc
 *		��ȡ��������Ϸ������֡������Graphics.update���õĴ�����
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
	 *		����RGEͼ�β��ֵ�ģ�顣
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
