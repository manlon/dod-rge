#ifndef __DOD_OBJECT_MANAGER_H__
#define __DOD_OBJECT_MANAGER_H__

#include "DOD_G3dobj.h"
#include "DOD_G2dobj.h"

#include <vector>

namespace Dod
{
typedef	std::vector<DOD_G3dobj*>	DODG3DLIST;
typedef std::vector<DOD_G2dobj*>	DODG2DLIST;

class DOD_ObjManager
{
public:
	DOD_ObjManager();
	~DOD_ObjManager();
	
public:
	void	AddG3dobj(DOD_G3dobj *pObj) const;
	void	AddG2dobj(DOD_G2dobj *pObj) const;
	void	RemoveG3dobj(DOD_G3dobj *pObj) const;
	void	RemoveG2dobj(DOD_G2dobj *pObj) const;
	
	DODG3DLIST*		GetG3dList() const { return m_pG3dList; }
	DODG2DLIST*		GetG2dList() const { return m_pG2dList; }
	
private:
	
	DODG3DLIST		*m_pG3dList;
	DODG2DLIST		*m_pG2dList;
};
}

#endif
