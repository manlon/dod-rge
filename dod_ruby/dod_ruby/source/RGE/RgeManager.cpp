#include "RgeManager.h"

#include "CRgeBitmap.h"
#include "CRgeColor.h"
//#include "CRgeDistortedSprite.h"
//#include "CRgeFlash.h"
//#include "CRgeFont.h"
#include "CRgePlane.h"
//#include "CRgeRect.h"
#include "CRgeSprite.h"
//#include "CRgeTable.h"
//#include "CRgeTilemap.h"
#include "CRgeTone.h"
//#include "CRgeViewport.h"
//#include "CRgeWindow.h"

static VALUE dm_retrun_nil(int argc, VALUE *argv, VALUE self)
{
	return Qnil;
}

RgeManager::RgeManager() :
	m_added_font_list(0)//,
//	m_screen_render_tree(0)
{
//	m_fullscreen_start = false;
//	m_forbid_fullscreen = false;
//	m_forbid_switch = false;

//	m_screen_width = 0;
//	m_screen_height = 0;

//	memset(&m_caps, 0, sizeof(m_caps));

	m_rgep_internal_reader = Qnil;
}
RgeManager::~RgeManager()
{
	SAFE_DELETE(m_added_font_list);
//	SAFE_DELETE(m_screen_render_tree);
}

bool RgeManager::Start()
{
	m_added_font_list = new std::vector<ID>();
	
	//m_screen_render_tree = new RgeRenderTree();

//	m_screen_width = 640;
//	m_screen_height = 480;

	return true;
}

void RgeManager::RemoveUserFont()
{
	//int rge_remove_font(LPCWSTR name);	//	in cRgeFont.cpp

	//if (m_added_font_list)
	//{
	//	for (std::vector<ID>::iterator it = m_added_font_list->begin();
	//		it != m_added_font_list->end(); ++it)
	//	{
	//		char *name = rb_id2name(*it);
	//		if (name)
	//		{
	//			rge_remove_font(rgefnm(name).UTF8ToUnicode());
	//		}
	//	}
	//}
}
void RgeManager::AppendFont(ID id)
{
	if (m_added_font_list)
		m_added_font_list->push_back(id);
}


void RgeManager::ReplaceRubyMethod()
{
	__replace_io_methods(rb_stdin);
	__replace_io_methods(rb_stdout);
	__replace_io_methods(rb_stderr);

	rb_define_global_function("gets",		(RbFunc)dm_retrun_nil, -1);
	rb_define_global_function("readline",	(RbFunc)dm_retrun_nil, -1);
	rb_define_global_function("getc",		(RbFunc)dm_retrun_nil, -1);
	rb_define_global_function("readlines",	(RbFunc)dm_retrun_nil, -1);
}

void RgeManager::InitRGEInternClass()
{
	Init_mRGE();
	Init_mInput();
	Init_mGraphics();

	CRgeBitmap::Init();
 	CRgeColor::Init();
//	CRgeDistortedSprite::Init();
//	CRgeFlash::Init();
//	CRgeFont::Init();
	CRgePlane::Init();
//	CRgeRect::Init();
	CRgeSprite::Init();
//	CRgeTable::Init();
//	CRgeTilemap::Init();
 	CRgeTone::Init();
//	CRgeViewport::Init();
//	CRgeWindow::Init();
}

void RgeManager::__replace_io_methods(const VALUE io)
{
	rb_define_singleton_method(io, "reopen",	(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "each",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "each_line", (RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "each_byte", (RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "syswrite",	(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "sysread",	(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "fileno",	(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "to_i",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "to_io",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "fsync",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "sync",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "sync=",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "lineno",	(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "lineno=",	(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "readlines", (RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "read",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "write",		(RbFunc)dm_retrun_nil, 1);
	rb_define_singleton_method(io, "gets",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "readline",	(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "getc",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "readchar",	(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "ungetc",	(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "flush",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "tell",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "seek",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "rewind",	(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "pos",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "pos=",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "eof",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "eof?",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "close",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "closed?",	(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "close_read",	(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "close_write",	(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "isatty",	(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "tty?",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "binmode",	(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "sysseek",	(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "ioctl",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "fcntl",		(RbFunc)dm_retrun_nil, -1);
	rb_define_singleton_method(io, "pid",		(RbFunc)dm_retrun_nil, -1);
}
