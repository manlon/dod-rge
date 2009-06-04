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
 *		assert(expression)			-> nil ��
 *		assert(expression, ...)		-> nil ��
 *
 *	@desc
 *		���Դ������ʽexpressionΪ�������ִ�У�Ϊ�����׳��쳣������ָ���쳣��Ϣ��֧��sprintf��ʽ���ַ�������
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
 *		maddr		-> fixnum �� bignum ���� ��
 *
 *	@desc
 *		�����ַ����������ڴ��е�λ�á�
 */
static VALUE dm_str_mem_addr(VALUE str)
{
 	return ULONG2NUM((u32)RSTRING_PTR(str));
}

/**
 *	@call
 *		p(...)		-> nil ��
 *
 *	@desc
 *		��ͨ���׶��ķ�ʽ������������ַ������������print������
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
 *		print(...)		-> nil ��
 *
 *	@desc
 *		����������������ѷ��ַ������󴫸������Ļ������Ըö���ʹ�� to_s ���������Ϊ�ַ����������[ENDLINE]
 *		���� nil �Ļ�������ַ���"nil"��[ENDLINE]
 *		Ruby ��ͨ�����Ϊ��׼�����Ȼ�� RGSS �ض����˸÷��������Ϊ����� Windows ����Ϣ��[ENDLINE]
 *		���� nil��
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
