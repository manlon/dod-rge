#ifndef __RGE_BASE_H__
#define __RGE_BASE_H__

#include "RgeManager.h"
#include "ResManager.h"
//#include "MRgeRGE.h"

/*
 *	生成ruby对象并返回
 */
#define return_RgeBase_Make_Class(rbklass, cppklass) do \
{\
	cppklass *dmy = new (cppklass);\
	SafeObjectNew(dmy);\
	return (dmy->__obj = Data_Wrap_Struct(rbklass, ObjMark, ObjFree, dmy));\
} while (0)

/*
 *	定义ruby实例方法（无参数）
 */
#define dm_method(name)\
	virtual	VALUE name();\
	static	VALUE dm_##name(VALUE obj);\

/*
 *	定义ruby实例方法（指定参数）
 */
#define dm_method_any(name, ...)\
	virtual VALUE name(__VA_ARGS__);\
	static	VALUE dm_##name(VALUE obj, __VA_ARGS__);\

/*
 *	定义ruby实例方法（不定参数）
 */
#define dm_method_vargs(name)\
	virtual VALUE name(int argc, VALUE *argv, VALUE obj);\
	static	VALUE dm_##name(int argc, VALUE *argv, VALUE obj);\

/*
 *	定义ruby类方法（无参数）
 */
#define dm_class_method(name)		dm_method(name)

/*
 *	定义ruby类方法（指定参数）
 */
#define dm_class_method_any(name, ...)	dm_method_any(name, __VA_ARGS__)

/*
 *	定义ruby类方法（不定参数）
 */
#define dm_class_method_vargs(name)	dm_method_vargs(name)

/*
 *	定义ruby只读属性
 */
#define attr_reader(attr)\
	virtual	VALUE get_##attr();\
	static	VALUE dm_get_##attr(VALUE obj);\

/*
 *	定义ruby只写属性
 */
#define attr_writer(attr)\
	virtual	VALUE set_##attr(VALUE attr);\
	static	VALUE dm_set_##attr(VALUE obj, VALUE attr);\

/*
 *	定义ruby可读可写属性
 */
#define attr_accessor(attr)\
	attr_reader(attr)\
	attr_writer(attr)\

/*
 *	实现ruby实例方法（无参数）
 */
#define imp_method(klass, name)\
	VALUE klass::dm_##name(VALUE obj)\
	{\
		klass	*obj_##klass;\
		Data_Get_Struct(obj, klass, obj_##klass);\
		return obj_##klass->name();\
	}\

/*
 *	实现ruby实例方法（指定参数）
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
 *	实现ruby实例方法（不定参数）
 */
#define imp_method_vargs(klass, name)\
	VALUE klass::dm_##name(int argc, VALUE *argv, VALUE obj)\
	{\
		klass	*obj_##klass;\
		Data_Get_Struct(obj, klass, obj_##klass);\
		return obj_##klass->name(argc, argv, obj);\
	}\

/*
 *	实现ruby类方法（无参数）
 */
#define imp_class_method(klass, name)		//	实现不确定

/*
 *	实现ruby类方法（不定参数）
 */
#define imp_class_method_vargs(klass, name)	//	实现不确定

/*
 *	实现ruby只读属性
 */
#define imp_attr_reader(klass, attr)\
	VALUE klass::dm_get_##attr(VALUE obj)\
	{\
		klass	*obj_##klass;\
		Data_Get_Struct(obj, klass, obj_##klass);\
		return obj_##klass->get_##attr();\
	}\

/*
 *	实现ruby只写属性
 */
#define imp_attr_writer(klass, attr)\
	VALUE klass::dm_set_##attr(VALUE obj, VALUE attr)\
	{\
		klass	*obj_##klass;\
		Data_Get_Struct(obj, klass, obj_##klass);\
		return obj_##klass->set_##attr(attr);\
	}\

/*
 *	实现ruby可读可写属性
 */
#define imp_attr_accessor(klass, attr)\
	imp_attr_reader(klass, attr)\
	imp_attr_writer(klass, attr)\

/**
 *	RgeBase
 *
 *		RGE中Ruby对象的顶层基类。
 */
class RgeBase
{
public:
	RgeBase(){ __obj = Qnil; }
	virtual ~RgeBase(){}														//	Ruby对象Free函数

public:
	VALUE			GetValue() const { return __obj; }
	
protected:
	virtual void	mark(){}													//	Ruby对象Mark函数
	virtual VALUE	initialize(int argc, VALUE *argv, VALUE obj){ return obj; }	//	Ruby对象initialize函数

protected:
	static void		ObjFree(RgeBase *baseobj);
	static void		ObjMark(RgeBase *baseobj);

protected:
	static VALUE	dm_initialize(int argc, VALUE *argv, VALUE obj);

protected:
	VALUE			__obj;														//	对该Ruby对象自身的引用 无需标记
};

#endif
