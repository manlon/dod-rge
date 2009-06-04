#ifndef __RGE_MANAGER_H__
#define __RGE_MANAGER_H__

#include "Rge.h"

#include "auxSingleton.h"

//#include "RgeRenderTree.h"
#include "RgeTypes.h"
//#include <d3d8.h>

#include <vector>

//class RgeRenderTree;

class RgeManager : public AuxSingleton<RgeManager>
{
public:
	RgeManager();
	~RgeManager();

	bool Start();

public:
	void RemoveUserFont();
	void AppendFont(ID id);

	void ReplaceRubyMethod();
	void InitRGEInternClass();
 	void InitRubyInternClassExt();

private:
	void __replace_io_methods(const VALUE io);

public:
//	IDirect3DDevice8*	m_pd3ddevice;
//	D3DCAPS8			m_caps;

//	bool	m_fullscreen_start;
//	bool	m_forbid_fullscreen;
//	bool	m_forbid_switch;

//	u32		m_screen_width;
//	u32		m_screen_height;

	bool	m_render_to_texture;

//	HWND	m_hwnd;

	VALUE	m_rgep_internal_reader;

private:
	std::vector<ID>	*m_added_font_list;
//	RgeRenderTree	*m_screen_render_tree;

private:
//	friend RgeRenderTree*	GetRenderTree();
};

//#include "RgeRenderTree.h"

//inline RgeRenderTree*	GetRenderTree() { return RgeManager::Instance()->m_screen_render_tree; }
inline RgeManager*		GetRGE() { return RgeManager::Instance(); }

#endif
