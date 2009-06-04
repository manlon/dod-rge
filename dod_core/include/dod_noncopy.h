#ifndef __dod_noncopy_h__
#define __dod_noncopy_h__

namespace Dod
{
class dod_noncopy
{
protected:
	dod_noncopy(){}
	~dod_noncopy(){}

private:
	dod_noncopy(const dod_noncopy&);
	dod_noncopy& operator = (const dod_noncopy&);
};
}


#endif
