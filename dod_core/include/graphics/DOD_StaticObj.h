#ifndef __DOD_STATIC_OBJ_H__
#define __DOD_STATIC_OBJ_H__

#include "DOD_G3dobj.h"

#include "DOD_FileFormat.h"

#include "DOD_Mesh.h"

namespace Dod
{
class DOD_StaticObj : public DOD_G3dobj
{
public:
	bool	LoadMesh(const char* pFileName);
	bool	LoadMeshFromMemory(void* pDataStream, u32 uLength);

	//void	Update();
	void	Render();

private:
	void	render_node(struct dod_dmdl_node*);

private:
	DOD_Mesh	m_mesh;
};
}

#endif
