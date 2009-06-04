#include "DOD_StaticObj.h"
#include "DOD_ResManager.h"

namespace Dod
{

/**
 *	从文件加载静态模型(DMDL)文件
 */
bool DOD_StaticObj::LoadMesh(const char* pFileName)
{
	u32	uSize;
	
	void* pData = Dod_GetResManager()->LoadResource(pFileName, &uSize);
	
	if (pData)
	{
		bool bResult = LoadMeshFromMemory(pData, uSize);
		
		Dod_GetResManager()->FreeResource(pData);
		
		return bResult;
	}
	else
	{
		return false;
	}
}

/**
 *	从内存加载静态模型(DMDL)文件
 */
bool DOD_StaticObj::LoadMeshFromMemory(void* pDataStream, u32 uLength)
{
	if (uLength < sizeof(dod_dmdl_header))
		return false;
	
	dod_dmdl_header* pHeader = (dod_dmdl_header*)pDataStream;
	
	if (pHeader->magic_number != DOD_DMDL_MAGIC_NUM)
		return false;
	
	if (uLength < pHeader->file_size)
		return false;

	if (!DOD_DMDL_CHECK_VERSION(pHeader->version))
		return false;
	
	return true;
}

void DOD_StaticObj::render_node(struct dod_dmdl_node* p_node)
{
	if (!p_node)
		return;

	u32 uMatIdx = p_node->material_index;
	u32 uTexIdx = p_node->texture_index;

	if (uMatIdx >= m_mesh.header.material_count)
		return;

	if (uTexIdx >= m_mesh.header.texture_count)
		return;

	//dod_dmdl_material* pMat = &m_mesh.header.p_material_list[uMatIdx];
	//dod_dmdl_texture* pTex = &m_mesh.header.p_texture_list[uTexIdx];
	//dod_matrix4x4* pTransformationMtx = &p_node->transformation_matrix;
	//if (p_node->p_parent_node)
	//{
	//	dod_matrix4x4* pParentMtx = &p_node->p_parent_node->transformation_matrix;
		// x
	//}

	//	设置变换矩阵
	//	设置纹理
	//	设置材质

	//	描绘三角形

	for (u32 uSubNodeIdx = 0; uSubNodeIdx < p_node->child_node_count; ++uSubNodeIdx)
	{
		render_node(p_node->p_child_node_list[uSubNodeIdx]);
	}
}

void DOD_StaticObj::Render()
{
	render_node(m_mesh.header.p_root_node);
}

}	//	namespace Dod

