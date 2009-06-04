#include "Rge.h"

#include <DodInput.h>

VALUE	rb_mInput;
	
/**
 *	@call
 *		Input.set_repeat(start_frame, interval_frame)	-> nil 。
 *
 *	@desc
 *		设置Input.repeat?的起始响应帧数和帧间隔。
 */
static VALUE dm_set_repeat(VALUE module, VALUE start_frame, VALUE interval_frame)
{
	SafeFixnumValue(start_frame);
	SafeFixnumValue(interval_frame);
	
	Dod::DodInput::SetRepeat(FIX2INT(start_frame), FIX2INT(interval_frame));
	return Qnil;
}

/**
 *	@call
 *		Input.update				-> nil 。
 *
 *	@desc
 *		更新输入信息。
 */
static VALUE dm_update(VALUE module)
{
	Dod::DodInput::Update();
	return Qnil;
}

/**
 *	@call
 *		Input.press?(num)			-> true 或 false。
 *
 *	@desc
 *		判断指定的键是否处于按下状态。
 */
static VALUE dm_press(VALUE module, VALUE num)
{
	return C2RbBool(Dod::DodInput::IsPress((Dod::DodInput::DodButtons)FIX2INT(num)));
}

/**
 *	@call
 *		Input.trigger?(num)			-> true 或 false。
 *
 *	@desc
 *		判断指定的键是否按下。
 */
static VALUE dm_trigger(VALUE module, VALUE num)
{
	return C2RbBool(Dod::DodInput::IsTrigger((Dod::DodInput::DodButtons)FIX2INT(num)));
}

/**
 *	@call
 *		Input.release?(num)			-> true 或 false。
 *
 *	@desc
 *		判断指定的键是否弹起。
 */
static VALUE dm_release(VALUE module, VALUE num)
{
	return C2RbBool(Dod::DodInput::IsRelease((Dod::DodInput::DodButtons)FIX2INT(num)));
}

/**
 *	@call
 *		Input.repeat?(num)			-> true 或 false。
 *
 *	@desc
 *		判断指定的键是否重复按下。
 */
static VALUE dm_repeat(VALUE module, VALUE num)
{
	return C2RbBool(Dod::DodInput::IsRepeat((Dod::DodInput::DodButtons)FIX2INT(num)));
}

/**
 *	@call
 *		Input.analog_x			-> fixnum。
 *
 *	@desc
 *		返回摇杆的X坐标。
 */
static VALUE dm_get_analog_x(VALUE module)
{
	return INT2FIX(Dod::DodInput::GetAnalogX());
}
/**
 *	@call
 *		Input.analog_y			-> fixnum。
 *
 *	@desc
 *		返回摇杆的Y坐标。
 */
static VALUE dm_get_analog_y(VALUE module)
{
	return INT2FIX(Dod::DodInput::GetAnalogY());
}
/**
 *	@call
 *		Input.analog_xy		-> array。
 *
 *	@desc
 *		返回摇杆的X和Y坐标的数组。
 */
static VALUE dm_get_analog_xy(VALUE module)
{
	VALUE arr = rb_ary_new();
	
	rb_ary_push(arr, INT2FIX(Dod::DodInput::GetAnalogX()));
	rb_ary_push(arr, INT2FIX(Dod::DodInput::GetAnalogY()));
	
	return arr;
}
/**
 *	@call
 *		Input.analog_prev_x			-> fixnum。
 *
 *	@desc
 *		返回摇杆上一帧的X坐标。
 */
static VALUE dm_get_analog_prev_x(VALUE module)
{
	return INT2FIX(Dod::DodInput::GetAnalogPrevX());
}
/**
 *	@call
 *		Input.analog_prev_y			-> fixnum。
 *
 *	@desc
 *		返回摇杆上一帧的Y坐标。
 */
static VALUE dm_get_analog_prev_y(VALUE module)
{
	return INT2FIX(Dod::DodInput::GetAnalogPrevY());
}
/**
 *	@call
 *		Input.analog_prev_xy		-> array。
 *
 *	@desc
 *		返回摇杆上一帧的X和Y坐标的数组。
 */
static VALUE dm_get_analog_prev_xy(VALUE module)
{
	VALUE arr = rb_ary_new();
	
	rb_ary_push(arr, INT2FIX(Dod::DodInput::GetAnalogPrevX()));
	rb_ary_push(arr, INT2FIX(Dod::DodInput::GetAnalogPrevY()));
	
	return arr;
}

/**
 *	@call
 *		Input.dir4	->	fixnum：2、4、6、8、0
 *
 *	@desc
 *		判断4方向行走输入信息。
 */
static VALUE dm_dir4(VALUE module)
{
	return RUBY_0;
}

/**
 *	@call
 *		Input.dir8	->	fixnum：2、4、6、8、1、3、5、7、0。
 *
 *	@desc
 *		判断8方向行走输入信息。
 */
static VALUE dm_dir8(VALUE module)
{
	return RUBY_0;
}

void Init_mInput()
{
	//	初始化DodInput模块
	Dod::DodInput::Init();
	
	/**
	 *	@modulename
	 *
	 *		Input
	 *
	 *	@desc
	 *		管理RGE键盘输入的模块。
	 */
	rb_mInput = rb_define_module_under(rb_mRGE, "Input");

	// module constants - `RM`
	rb_define_const(rb_mInput, "SELECT",	INT2FIX(Dod::DodInput::DOD_KEY_SELECT));
	rb_define_const(rb_mInput, "START",		INT2FIX(Dod::DodInput::DOD_KEY_START));
	
	rb_define_const(rb_mInput, "UP",		INT2FIX(Dod::DodInput::DOD_KEY_UP));
	rb_define_const(rb_mInput, "DOWN",		INT2FIX(Dod::DodInput::DOD_KEY_DOWN));
	rb_define_const(rb_mInput, "LEFT",		INT2FIX(Dod::DodInput::DOD_KEY_LEFT));
	rb_define_const(rb_mInput, "RIGHT",		INT2FIX(Dod::DodInput::DOD_KEY_RIGHT));
	
	rb_define_const(rb_mInput, "LTRIGGER",	INT2FIX(Dod::DodInput::DOD_KEY_LTRIGGER));
	rb_define_const(rb_mInput, "RTRIGGER",	INT2FIX(Dod::DodInput::DOD_KEY_RTRIGGER));
	
	rb_define_const(rb_mInput, "TRIANGLE",	INT2FIX(Dod::DodInput::DOD_KEY_TRIANGLE));
	rb_define_const(rb_mInput, "CIRCLE",	INT2FIX(Dod::DodInput::DOD_KEY_CIRCLE));
	rb_define_const(rb_mInput, "CROSS",		INT2FIX(Dod::DodInput::DOD_KEY_CROSS));
	rb_define_const(rb_mInput, "SQUARE",	INT2FIX(Dod::DodInput::DOD_KEY_SQUARE));
	
	rb_define_const(rb_mInput, "HOME",		INT2FIX(Dod::DodInput::DOD_KEY_HOME));
	rb_define_const(rb_mInput, "HOLD",		INT2FIX(Dod::DodInput::DOD_KEY_HOLD));
	rb_define_const(rb_mInput, "NOTE",		INT2FIX(Dod::DodInput::DOD_KEY_NOTE));
	rb_define_const(rb_mInput, "SCREEN",	INT2FIX(Dod::DodInput::DOD_KEY_SCREEN));
	rb_define_const(rb_mInput, "VOLUP",		INT2FIX(Dod::DodInput::DOD_KEY_VOLUP));
	rb_define_const(rb_mInput, "VOLDOWN",	INT2FIX(Dod::DodInput::DOD_KEY_VOLDOWN));
	rb_define_const(rb_mInput, "WLANUP",	INT2FIX(Dod::DodInput::DOD_KEY_WLAN_UP));
	rb_define_const(rb_mInput, "REMOTE",	INT2FIX(Dod::DodInput::DOD_KEY_REMOTE));
	rb_define_const(rb_mInput, "DISC",		INT2FIX(Dod::DodInput::DOD_KEY_DISC));
	rb_define_const(rb_mInput, "MS",		INT2FIX(Dod::DodInput::DOD_KEY_MS));

	// module method
	rb_define_module_function(rb_mInput, "set_repeat",		(RbFunc)dm_set_repeat, 2);
	
	rb_define_module_function(rb_mInput, "update",	(RbFunc)dm_update, 0);
	rb_define_module_function(rb_mInput, "press?",	(RbFunc)dm_press, 1);
	rb_define_module_function(rb_mInput, "trigger?",(RbFunc)dm_trigger, 1);
	rb_define_module_function(rb_mInput, "release?",(RbFunc)dm_release, 1);
	rb_define_module_function(rb_mInput, "repeat?",	(RbFunc)dm_repeat, 1);
	
	rb_define_module_function(rb_mInput, "analog_x",		(RbFunc)dm_get_analog_x, 0);
	rb_define_module_function(rb_mInput, "analog_y",		(RbFunc)dm_get_analog_y, 0);
	rb_define_module_function(rb_mInput, "analog_xy",		(RbFunc)dm_get_analog_xy, 0);
	rb_define_module_function(rb_mInput, "analog_prev_x",	(RbFunc)dm_get_analog_prev_x, 0);
	rb_define_module_function(rb_mInput, "analog_prev_y",	(RbFunc)dm_get_analog_prev_y, 0);
	rb_define_module_function(rb_mInput, "analog_prev_xy",	(RbFunc)dm_get_analog_prev_xy, 0);
	
	rb_define_module_function(rb_mInput, "dir4",	(RbFunc)dm_dir4, 0);
	rb_define_module_function(rb_mInput, "dir8",	(RbFunc)dm_dir8, 0);
}
