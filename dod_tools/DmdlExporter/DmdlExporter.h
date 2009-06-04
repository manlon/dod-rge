#pragma once

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
// DESCRIPTION: Includes for Plugins
// AUTHOR: syalon
//***************************************************************************/

#include "3dsmaxsdk_preinclude.h"
#include "Max.h"
#include "resource.h"
#include "istdplug.h"
#include "iparamb2.h"
#include "iparamm2.h"
//SIMPLE TYPE

#include "../../dod_core/include/graphics/DOD_FileFormat.h"

using namespace Dod;

extern TCHAR *GetString(int id);

extern HINSTANCE hInstance;

//	DMDL����������ID
#define DmdlExporter_CLASS_ID	Class_ID(0x427d0e24, 0x69e9dfdf)

/**
 *	DMDL�����������������
 */
class DmdlExporter : public SceneExport
{
public:
	static HWND hParams;

public:
	/**
	 *	���֧�ֵ���չ��������Ŀǰ����(.DMDL)һ����
	 */
	int				ExtCount() { return 1; }

	/**
	 *	��ȡ��n����չ���ַ���
	 */
	const TCHAR *	Ext(int n) { return _T("DMDL"); }

	/**
	 *	���ڲ���Ľϳ���������Ϣ��
	 */
	const TCHAR *	LongDesc() { return _T("3dsmax Model Exporter for Dod."); }

	/**
	 *	���ڲ���ļ�̵�������Ϣ��
	 */
	const TCHAR *	ShortDesc() { return _T("����ΪDODģ�͸�ʽ"); }

	/**
	 *	�������������Ϣ
	 */
	const TCHAR *	AuthorName() { return _T("hanomirin"); }

	/**
	 *	����İ�Ȩ��Ϣ
	 */
	const TCHAR *	CopyrightMessage() { return _T("Copyright C 2009 by Dod Studio"); }

	/**
	 *	������Ϣ01��02
	 */
	const TCHAR *	OtherMessage1() { return _T(""); }
	const TCHAR *	OtherMessage2() { return _T(""); }

	/**
	 *	����汾��Ϣ ��ʽ��Version number * 100 (i.e. v3.01 = 301)
	 */
	unsigned int	Version() { return 100; }

	/**
	 *	���ڶԻ���
	 */
	void			ShowAbout(HWND hWnd) { MessageBox(hWnd, "DMDL Exporter For 3DSMAX ver1.0 ^ ^!", "����", 0); }

	/**
	 *	���ز�����칦����Ϣ
	 */
	BOOL			SupportsOptions(int ext, DWORD options) { return TRUE; }

	/*****
	 *	�����ʼ�����ӿں���
	 */
	int				DoExport(const TCHAR *pFileName, ExpInterface *ei,Interface *i, BOOL suppressPrompts = FALSE, DWORD options = 0);

public:
	DmdlExporter(){ reset(); }
	~DmdlExporter(){}

private:
	void			reset();

private:
	BOOL			doNodes();
	BOOL			doHeader();

	BOOL			doOneNode(INode* pNode);

	BOOL			exportGeomObject(INode* pNode);
	BOOL			exportLightObject(INode* pNode);
	BOOL			exportCameraObject(INode* pNode);
	BOOL			exportHelperObject(INode* pNode);

private:
	ExpInterface*	m_pExpIf;
	Interface*		m_pIf;
	const TCHAR*	m_pFileName;
	TimeValue		m_iCurrentTime;

	BOOL			m_bOnlyExportSelectedNode;

private:
	u32				m_uFileOffset;

	u32				m_uNodeId;
	u32				m_uParentNodeId;

	dod_dmdl_node*	m_pParentDNode;

	Tab<dod_dmdl_node*>	m_tChildrenNodeList;

private:
	dod_dmdl_header	m_mesh_header;
};

/****
 *	DMDL�����������������
 */
class DmdlExporterClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 	{ return new DmdlExporter(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return SCENE_EXPORT_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return DmdlExporter_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("DmdlExporter"); }			// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
};
