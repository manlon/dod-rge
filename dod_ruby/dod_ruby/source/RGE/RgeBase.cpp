#include "RgeBase.h"

void RgeBase::ObjFree(RgeBase *baseobj)
{
	if (baseobj) delete baseobj;
}
void RgeBase::ObjMark(RgeBase *baseobj)
{
	if (baseobj) baseobj->mark();
}
VALUE RgeBase::dm_initialize(int argc, VALUE *argv, VALUE obj)
{
	RgeBase	*baseobj;
	Data_Get_Struct(obj, RgeBase, baseobj);

	return baseobj->initialize(argc, argv, obj);
}
