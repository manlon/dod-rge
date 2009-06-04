#ifndef __RGE_BASE_H__
#define __RGE_BASE_H__

#include "RgeManager.h"
#include "ResManager.h"
//#include "MRgeRGE.h"

/*
 *	����ruby���󲢷���
 */
#define return_RgeBase_Make_Class(rbklass, cppklass) do \
{\
	cppklass *dmy = new (cppklass);\
	SafeObjectNew(dmy);\
	return (dmy->__obj = Data_Wrap_Struct(rbklass, ObjMark, ObjFree, dmy));\
} while (0)

/*
 *	����rubyʵ���������޲�����
 */
#define dm_method(name)\
	virtual	VALUE name();\
	static	VALUE dm_##name(VALUE obj);\

/*
 *	����rubyʵ��������ָ��������
 */
#define dm_method_any(name, ...)\
	virtual VALUE name(__VA_ARGS__);\
	static	VALUE dm_##name(VALUE obj, __VA_ARGS__);\

/*
 *	����rubyʵ������������������
 */
#define dm_method_vargs(name)\
	virtual VALUE name(int argc, VALUE *argv, VALUE obj);\
	static	VALUE dm_##name(int argc, VALUE *argv, VALUE obj);\

/*
 *	����ruby�෽�����޲�����
 */
#define dm_class_method(name)		dm_method(name)

/*
 *	����ruby�෽����ָ��������
 */
#define dm_class_method_any(name, ...)	dm_method_any(name, __VA_ARGS__)

/*
 *	����ruby�෽��������������
 */
#define dm_class_method_vargs(name)	dm_method_vargs(name)

/*
 *	����rubyֻ������
 */
#define attr_reader(attr)\
	virtual	VALUE get_##attr();\
	static	VALUE dm_get_##attr(VALUE obj);\

/*
 *	����rubyֻд����
 */
#define attr_writer(attr)\
	virtual	VALUE set_##attr(VALUE attr);\
	static	VALUE dm_set_##attr(VALUE obj, VALUE attr);\

/*
 *	����ruby�ɶ���д����
 */
#define attr_accessor(attr)\
	attr_reader(attr)\
	attr_writer(attr)\

/*
 *	ʵ��rubyʵ���������޲�����
 */
#define imp_method(klass, name)\
	VALUE klass::dm_##name(VALUE obj)\
	{\
		klass	*obj_##klass;\
		Data_Get_Struct(obj, klass, obj_##klass);\
		return obj_##klass->name();\
	}\

/*
 *	ʵ��rubyʵ��������ָ��������
 */
#define imp_method_any_01(klass, name, ...)\
	VALUE klass::dm_##name(VALUE obj, __VA_ARGS__)\

#define imp_method_any_02(klass, name, ...)\
	{\
		klass	*obj_##klass;\
		Data_Get_Struct(obj, klass, obj_##klass);\
		return obj_##klass->name(__VA_ARGS__);\
	}\

/*
 *	ʵ��rubyʵ������������������
 */
#define imp_method_vargs(klass, name)\
	VALUE klass::dm_##name(int argc, VALUE *argv, VALUE obj)\
	{\
		klass	*obj_##klass;\
		Data_Get_Struct(obj, klass, obj_##klass);\
		return obj_##klass->name(argc, argv, obj);\
	}\

/*
 *	ʵ��ruby�෽�����޲�����
 */
#define imp_class_method(klass, name)		//	ʵ�ֲ�ȷ��

/*
 *	ʵ��ruby�෽��������������
 */
#define imp_class_method_vargs(klass, name)	//	ʵ�ֲ�ȷ��

/*
 *	ʵ��rubyֻ������
 */
#define imp_attr_reader(klass, attr)\
	VALUE klass::dm_get_##attr(VALUE obj)\
	{\
		klass	*obj_##klass;\
		Data_Get_Struct(obj, klass, obj_##klass);\
		return obj_##klass->get_##attr();\
	}\

/*
 *	ʵ��rubyֻд����
 */
#define imp_attr_writer(klass, attr)\
	VALUE klass::dm_set_##attr(VALUE obj, VALUE attr)\
	{\
		klass	*obj_##klass;\
		Data_Get_Struct(obj, klass, obj_##klass);\
		return obj_##klass->set_##attr(attr);\
	}\

/*
 *	ʵ��ruby�ɶ���д����
 */
#define imp_attr_accessor(klass, attr)\
	imp_attr_reader(klass, attr)\
	imp_attr_writer(klass, attr)\

/**
 *	RgeBase
 *
 *		RGE��Ruby����Ķ�����ࡣ
 */
class RgeBase
{
public:
	RgeBase(){ __obj = Qnil; }
	virtual ~RgeBase(){}														//	Ruby����Free����

public:
	VALUE			GetValue() const { return __obj; }
	
protected:
	virtual void	mark(){}													//	Ruby����Mark����
	virtual VALUE	initialize(int argc, VALUE *argv, VALUE obj){ return obj; }	//	Ruby����initialize����

protected:
	static void		ObjFree(RgeBase *baseobj);
	static void		ObjMark(RgeBase *baseobj);

protected:
	static VALUE	dm_initialize(int argc, VALUE *argv, VALUE obj);

protected:
	VALUE			__obj;														//	�Ը�Ruby������������� ������
};

#endif
