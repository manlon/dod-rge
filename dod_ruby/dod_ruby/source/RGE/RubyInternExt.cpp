/*
**
**	erbintc.cpp file
** 
**  ext ruby internal class
**  
*/

//#include "RGE.h"
//#include "Utils/rgefnm.h"
//#include "Utils/rgesafemem.h"
//#include "Utils/rgesaferead.h"
//#include "Utils/rgemacros.h"
//
//#include "RGESIO.h"
#include "Rge.h"
#include "RgeManager.h"

//#include "MRgeRGE.h"

/**
 *	@call
 *		assert(expression)			-> nil 。
 *		assert(expression, ...)		-> nil 。
 *
 *	@desc
 *		断言处理，表达式expression为真则继续执行，为假则抛出异常，可以指定异常信息（支持sprintf格式化字符串）。
 */
static VALUE dm_assert(int argc, VALUE *argv/*, VALUE caller*/)
{
	VALUE errormsg;
	VALUE cond, rest;

	rb_scan_args(argc, argv, "1*", &cond, &rest);

	if (RTEST(cond))
		return Qnil;
	
	if (argc == 1)
		errormsg = rb_str_new2("Assertion Failed!"/*__UTF8("Assertion Failed!")*/);
	else
		errormsg = rb_f_sprintf(argc - 1, argv + 1);

	rb_raise(rb_eRGEAssertError, RSTRING_PTR(errormsg));

	return Qnil;
}

/**
 *	@call
 *		maddr		-> fixnum 或 bignum 对象 。
 *
 *	@desc
 *		返回字符串对象在内存中的位置。
 */
static VALUE dm_str_mem_addr(VALUE str)
{
 	return ULONG2NUM((u32)RSTRING_PTR(str));
}

/**
 *	@call
 *		p(...)		-> nil 。
 *
 *	@desc
 *		以通俗易懂的方式输出对象描述字符串。具体参照print方法。
 */
static VALUE rdm_p(int argc, VALUE *argv/*, VALUE caller*/)
{
	int i;

	VALUE str = rb_str_buf_new(0);

	for (i = 0; i < argc; ++i)
	{
		rb_str_buf_append(str, rb_inspect(argv[i]));
		rb_str_buf_append(str, rb_default_rs);
	}

	RgeDbgPrintf(RSTRING_PTR(str));

	return Qnil;
}

/**
 *	@call
 *		print(...)		-> nil 。
 *
 *	@desc
 *		依次输出参数。若把非字符串对象传给参数的话，将对该对象使用 to_s 方法将其变为字符串后输出。[ENDLINE]
 *		若是 nil 的话则输出字符串"nil"。[ENDLINE]
 *		Ruby 中通常输出为标准输出，然而 RGSS 重定义了该方法，变更为输出到 Windows 的信息框。[ENDLINE]
 *		返回 nil。
 */
static VALUE rdm_print(int argc, VALUE *argv/*, VALUE caller*/)
{
	int i;

	VALUE str = rb_str_buf_new(0);

	for (i = 0; i < argc; ++i)
		rb_str_buf_append(str, NIL_P(argv[i]) ? rb_str_new2("nil") : rb_obj_as_string(argv[i]));

 	RgeDbgPrintf(RSTRING_PTR(str));
 	
	return Qnil;
}

void RgeManager::InitRubyInternClassExt()
{
	// add new ruby method to the internal class
//	rb_define_method(rb_cString,"maddr",(RbFunc)dm_str_mem_addr,0);

	// redefine ruby method
 	rb_define_global_function("p", (RbFunc)rdm_p, -1);
	rb_define_global_function("print",(RbFunc)rdm_print,-1);

	rb_define_global_function("assert",(RbFunc)dm_assert,-1);

	//rb_define_global_function("require_rges", (RGE_RB_FUNC)dm_require_rges, 1);

	////rb_define_global_function("save_data", (RGE_RB_FUNC)rdm_save_data, 1);
	//rb_define_global_function("load_data", (RGE_RB_FUNC)dm_load_data, 1);
}
