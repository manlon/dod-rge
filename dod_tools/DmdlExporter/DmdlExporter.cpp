//**************************************************************************/
// Copyright (c) 1998-2007 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Appwizard generated plugin
// AUTHOR: syalon
//***************************************************************************/

#include "DmdlExporter.h"

//	���������Ϣ����
static DmdlExporterClassDesc sDmdlExporterDesc;

//	��ȡ���������Ϣ����ָ��
ClassDesc2* GetDmdlExporterDesc() { return &sDmdlExporterDesc; }

/*****
 *	��������ӿں���
 */
int	DmdlExporter::DoExport(const TCHAR* pFileName,ExpInterface* pExpIf,Interface* pIf, BOOL suppressPrompts, DWORD options)
{
	m_pExpIf = pExpIf;
	m_pIf = pIf;
	m_pFileName = pFileName;

	m_iCurrentTime = m_pIf->GetTime();

	doNodes();
	doHeader();
#if 0
	char	szDllPath[_MAX_PATH];
	DWORD	dwDllPathLen = GetModuleFileName(hInstance, szDllPath, _MAX_PATH);

	for (DWORD idx = dwDllPathLen - 1; idx >= 0; --idx)
	{
		if (szDllPath[idx] == '\\' || szDllPath[idx] == '/')
		{
			szDllPath[idx + 1] = 0;
			break;
		}
	}

	strcat(szDllPath, "DmdlExporterIO");

	HMODULE hIoDll = ::LoadLibraryA(szDllPath);

	if (!hIoDll)
	{
		MessageBoxA(i->GetMAXHWnd(), "Load DmdlExporterIO.dll Failed!", "Error", MB_ICONERROR);
		return TRUE;
	}

	int iResult = TRUE;

	int	(*pDoExportFunc)(const TCHAR*, ExpInterface*, Interface*, BOOL, DWORD) = 
		(int (*)(const TCHAR*, ExpInterface*, Interface*, BOOL, DWORD))GetProcAddress(hIoDll, "DoExport");

	if (!pDoExportFunc)
	{
		MessageBoxA(i->GetMAXHWnd(), "Get `DoExport' Proc Failed!", "Error", MB_ICONERROR);
		::FreeLibrary(hIoDll);
		return TRUE;
	}

	iResult = pDoExportFunc(name, ei, i, suppressPrompts, options);

	::FreeLibrary(hIoDll);

	return iResult;
#endif
	return TRUE;
}

void DmdlExporter::reset()
{
	m_pExpIf = 0;
	m_pIf = 0;
	m_pFileName = 0;
	m_iCurrentTime = 0;
	m_bOnlyExportSelectedNode = FALSE;

	m_uFileOffset = 0;
	m_uNodeId = 0;
	m_uParentNodeId = 0;

	m_pParentDNode = 0;
	m_tChildrenNodeList.ZeroCount();

	memset(&m_mesh_header, 0, sizeof(m_mesh_header));
}

BOOL DmdlExporter::doNodes()
{
	//	��ȡ�����
	INode* pRootNode = m_pIf->GetRootNode();

#ifdef _DEBUG
	const char * pModelName = pRootNode->GetName();
#endif	//	_DEBUG

	//	���������ӽ��
	int iChildrenNums = pRootNode->NumberOfChildren();

	for (int idx = 0; idx < iChildrenNums; ++idx)
	{
		doOneNode(pRootNode->GetChildNode(idx));
	}

	return TRUE;
}

BOOL DmdlExporter::doHeader()
{
	m_mesh_header.magic_number = DOD_DMDL_MAGIC_NUM;
	m_mesh_header.version = DOD_DMDL_VERSION;

	//strcpy((char*)m_mesh_header.model_name, "teapot");

	return TRUE;
}

/*
 *	��������� �ɹ������ý�㷵��TRUE ���򷵻�FALSE
 */
BOOL DmdlExporter::doOneNode(INode* pNode)
{
	if (!pNode)
		return FALSE;

	//if (m_bOnlyExportSelectedNode && !pNode->Selected())
	//	return FALSE;

	Object*	pObj = pNode->EvalWorldState(m_iCurrentTime).obj;

	if (!pObj)
		return FALSE;

	switch (pObj->SuperClassID())
	{
	//	TRIOBJ_CLASS_ID
	//	PATCHOBJ_CLASS_ID

	//	BOXOBJ_CLASS_ID��SPHERE_CLASS_ID��CYLINDER_CLASS_ID��CONE_CLASS_ID��TORUS_CLASS_ID��
	//	TUBE_CLASS_ID��HEDRA_CLASS_ID��TEAPOT_CLASS_ID1��TEAPOT_CLASS_ID2

	//	PATCHGRID_CLASS_ID
	case GEOMOBJECT_CLASS_ID:		//	��������󵼳�
		return exportGeomObject(pNode);

	//	OMNI_LIGHT_CLASS_ID
	//	SPOT_LIGHT_CLASS_ID
	//	DIR_LIGHT_CLASS_ID
	//	FSPOT_LIGHT_CLASS_ID
	//	TDIR_LIGHT_CLASS_ID
	case LIGHT_CLASS_ID:			//	��Դ���󵼳�
		return exportLightObject(pNode);

	//	SIMPLE_CAM_CLASS_ID
	//	LOOKAT_CAM_CLASS_ID
	case CAMERA_CLASS_ID:			//	��������󵼳�
		return exportCameraObject(pNode);

	//	DUMMY_CLASS_ID
	//	BONE_CLASS_ID
	//	TAPEHELP_CLASS_ID
	//	GRIDHELP_CLASS_ID
	//	POINTHELP_CLASS_ID
	//	PROTHELP_CLASS_ID
	case HELPER_CLASS_ID:			//	�����ȸ������󵼳�
		return exportHelperObject(pNode);

	default:
		return FALSE;
	}
}

/***
 *	�������������
 */
BOOL DmdlExporter::exportGeomObject(INode* pNode)
{
	//	��㲻�ɼ�����
	if (pNode->IsHidden())
		return FALSE;

	Object*	pObj = pNode->EvalWorldState(m_iCurrentTime).obj;

	//	����ָ����Ч����
	if (!pObj)
		return FALSE;

	//	 PATCHģ�Ͷ��󷵻�(�˰汾�ݲ�����)
	if (pObj->ClassID() == Class_ID(PATCHOBJ_CLASS_ID, 0) || pObj->ClassID() == Class_ID(PATCHGRID_CLASS_ID, 0))
		return FALSE;

	//	����ת��Ϊ�����ζ��󷵻�
	if (!pObj->CanConvertToType(triObjectClassID))
		return FALSE;

	//	��ʼ����ģ��
	TriObject *pTriObj = (TriObject *)pObj->ConvertToType(m_iCurrentTime, Class_ID(TRIOBJ_CLASS_ID, 0));

	//	ת��������ʧ�ܷ���
	if (!pTriObj)
		return FALSE;

	//	�Ƿ���Ҫɾ�������ж�
	BOOL bDelTriObj = (pTriObj != pObj);

	//	***** ��ʼ��ȡģ����Ϣ *****
	dod_dmdl_node* pdnode = new dod_dmdl_node;
	{
		pdnode->p_parent_node = 0;
		pdnode->node_id = m_uNodeId++;
		strcpy((char*)&pdnode->node_name[0], pNode->GetName());
	}
	
	//	��ȡMesh����ָ��
	Mesh* pMesh = &pTriObj->mesh;

	//pMesh->buildNormals();

	//	��ȡ���������Ŀ
	int iVertNums = pMesh->getNumVerts();
	int iFaceNums = pMesh->getNumFaces();
	{
		pdnode->vertex_count = u32(iVertNums);
		pdnode->p_vertex_list = new dod_dmdl_vertex[iVertNums];

		pdnode->triangle_count = u32(iFaceNums);
		pdnode->p_triangle_list = new dod_dmdl_index_triangle[iFaceNums];
	}

	//	���������� ���ڱ�Ƕ����Ƿ��Ѿ�����
	u8* bVertexMark = new u8[iVertNums];

	memset(bVertexMark, 0, sizeof(u8) * iVertNums);
	
	//	�淨����
	Point3*	pFaceNormals = new Point3[iFaceNums];

	//	ѭ������������
	for (int idx = 0; idx < iFaceNums; ++idx)
	{
		//	��ȡ������������
		TVFace* pTvFace = &pMesh->tvFace[idx];

		for (int i = 0; i < 3; ++i)
		{
			//	��ȡ��������
			u32 uVertexIndex = pMesh->faces[idx].v[i];

			//	��¼�涥������
			pdnode->p_triangle_list[idx].indices[i] = uVertexIndex;

			//	������δ������Ķ���
			if (!bVertexMark[uVertexIndex])
			{
				Point3* pVertex = &pMesh->verts[uVertexIndex];

				UVVert* pTvVert = &pMesh->tVerts[pTvFace->t[i]];

				struct dod_dmdl_vertex* pVtxOut = &pdnode->p_vertex_list[uVertexIndex];
				{
					pVtxOut->position.x = pVertex->x;
					pVtxOut->position.y = pVertex->z;
					pVtxOut->position.z = -pVertex->y;

					pVtxOut->texcoord.u = pTvVert->x;
					pVtxOut->texcoord.v = pTvVert->y;

					pVtxOut->normal.x = 0.0f;
					pVtxOut->normal.y = 1.0f;
					pVtxOut->normal.z = 0.0f;
				}

				bVertexMark[uVertexIndex] = 1;
			}
		}

		//	����������
		//Point3* pVertex01 = &pMesh->verts[pMesh->faces[idx].v[0]];
		//Point3* pVertex02 = &pMesh->verts[pMesh->faces[idx].v[1]];
		//Point3* pVertex03 = &pMesh->verts[pMesh->faces[idx].v[2]];

		//Point3 v12 = *pVertex02 - *pVertex01;
		//Point3 v13 = *pVertex03 - *pVertex01;

		//pFaceNormals[idx] = v13 ^ v12;
		//pFaceNormals[idx].Normalize();
	}

	//	ɾ���������
	delete [] bVertexMark;

	//	ɾ���淨��������
	delete [] pFaceNormals;

	//	ɾ��ת�����ɵ������ζ���
	if (bDelTriObj)
		pTriObj->DeleteMe();

	//	�ݹ�����ӽ��
	int iChildrenNums = pNode->NumberOfChildren();

	for (int idx = 0; idx < iChildrenNums; ++idx)
	{
		doOneNode(pNode->GetChildNode(idx));
	}

	return TRUE;
}

/***
 *	������Դ�������
 */
BOOL DmdlExporter::exportLightObject(INode* pNode)
{
	return TRUE;
}

/***
 *	�������������
 */
BOOL DmdlExporter::exportCameraObject(INode* pNode)
{
	return TRUE;
}

/***
 *	���������ȸ�������
 */
BOOL DmdlExporter::exportHelperObject(INode* pNode)
{
	return TRUE;
}