#include "DOD_GeomObj.h"

#include "dod_macros.h"

#include <stdlib.h>
#include <string.h>

#include <pspgu.h>

namespace Dod
{
DOD_GeomObj::DOD_GeomObj()
: m_pVertexs(0), m_pIndices(0)
{
}

DOD_GeomObj::~DOD_GeomObj()
{
	SAFE_FREE(m_pVertexs);
	SAFE_FREE(m_pIndices);
}

void DOD_GeomObj::CreateMesh(DOD_GEOM_MESH_TYPE dgmt, DOD_VERTEX_TYPE dvt)
{
	SAFE_FREE(m_pVertexs);
	SAFE_FREE(m_pIndices);
	
	switch (dgmt)
	{
		case DOD_GMT_CUBE: create_mesh_cube(dvt); break;
		default:
			break;
	}
}

void DOD_GeomObj::Render()
{
	sceGuDrawArray(GU_TRIANGLES, dod_vertex_np_fvf | GU_INDEX_16BIT | GU_TRANSFORM_3D, 36, m_pIndices, m_pVertexs);	
}

void DOD_GeomObj::create_mesh_cube(DOD_VERTEX_TYPE dvt)
{
	switch (dvt)
	{
		case DOD_VT_TP:
		{
			m_pVertexs = malloc(sizeof(struct dod_vertex_tp) * 8);
		}
		break;
		case DOD_VT_NP:
		{			
			static struct dod_vertex_np	lVertexs[] =
			{
				{0.f, 1.f, 0.f, -1.f,  1.f, -1.f},
				{0.f, 1.f, 0.f,  1.f,  1.f, -1.f},
				{0.f, 1.f, 0.f,  1.f, -1.f, -1.f},
				{0.f, 1.f, 0.f, -1.f, -1.f, -1.f},
				
				{0.f, 1.f, 0.f, -1.f,  1.f, 1.f},
				{0.f, 1.f, 0.f,  1.f,  1.f, 1.f},
				{0.f, 1.f, 0.f,  1.f, -1.f, 1.f},
				{0.f, 1.f, 0.f, -1.f, -1.f, 1.f},
			};
			
			m_pVertexs = malloc(sizeof(struct dod_vertex_np) * 8);
			memcpy(m_pVertexs, lVertexs, sizeof(lVertexs));
		}
		break;
		case DOD_VT_TCP:
		{
			m_pVertexs = malloc(sizeof(struct dod_vertex_tcp) * 8);
		}
		break;
		case DOD_VT_NTCP:
		{
			m_pVertexs = malloc(sizeof(struct dod_vertex_tcnp) * 8);
		}
		break;
	}
	
	static u16	lIndices[] =
	{
		0, 1, 2, 0, 2, 3,
		4, 6, 7, 4, 6, 5,
		
		6, 4, 0, 6, 4, 3,
		2, 1, 5, 2, 1, 7,
		
		0, 4, 5, 0, 4, 1,
		6, 3, 2, 6, 3, 7
	};
	
	m_pIndices = malloc(sizeof(u16) * 3 * 8);
	memcpy(m_pIndices, lIndices, sizeof(lIndices));
}
}
