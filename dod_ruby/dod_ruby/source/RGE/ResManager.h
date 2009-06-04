#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

//#include <windows.h>

#include "auxSingleton.h"
#include "RgeTypes.h"

#define _MAX_PATH	256

#ifdef UNICODE
typedef	wchar_t	rgechar;

#define	rgestrlen	wcslen
#define	rgestrcpy	wcscpy_s
#define rgestrcat	wcscat_s
#else
typedef	char	rgechar;

#define	rgestrlen	strlen
#define	rgestrcpy	strcpy
#define	rgestrcat	strcat
#endif	// !UNICODE

class ResManager : public AuxSingleton<ResManager>
{
public:
	void	Init(const char *app_path);

	void*	Resource_Load(const rgechar *filename, Dod::u32 *size);
	void	Resource_Free(void *data);

	rgechar*	Resource_MakePath(const rgechar *filename);

private:
	rgechar	szTmpFilename[_MAX_PATH];
	rgechar	szAppPath[_MAX_PATH];
};

inline ResManager*		GetResManager() { return ResManager::Instance(); }

#endif
