#ifndef __DOD_GEOMETRY_OBJ_H__
#define __DOD_GEOMETRY_OBJ_H__

#include "DOD_StaticObj.h"

namespace Dod
{
enum DOD_GEOM_MESH_TYPE
{
	DOD_GMT_CUBE = 0
};

class DOD_GeomObj : public DOD_StaticObj
{
public:
	DOD_GeomObj();
	~DOD_GeomObj();
	
public:
	void	CreateMesh(DOD_GEOM_MESH_TYPE dgmt, DOD_VERTEX_TYPE dvt);
	
	virtual void	Render();
	
protected:
	void	*m_pVertexs;
	void	*m_pIndices;
	
private:
	void	create_mesh_cube(DOD_VERTEX_TYPE dvt);
};
}

#endif
