#include "ResManager.h"
#include "RgeMacros.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ResManager::Init(const char *app_path)
{
	strcpy(szAppPath, app_path);
	char *last = strrchr(szAppPath, '/');
	*++last = 0;
}

void* ResManager::Resource_Load(const rgechar *filename, u32 *size)
{
	void	*data = 0;
	
	FILE	*fr = NULL;
	
	u32		file_size;

	if (size) *size = 0;	//	init it !
	
	if (!(fr = fopen(Resource_MakePath(filename), "rb")))
		return 0;
	
	fseek(fr, 0, SEEK_END);
	file_size = ftell(fr);
	fseek(fr, 0, SEEK_SET);
	
	if (!(data = malloc(file_size)))
		goto failed_return;
	
	file_size = fread(data, 1, file_size, fr);
	if (file_size == 0)
		goto failed_return;
	
	fclose(fr);
	
	if (size) *size = file_size;
	
	return data;
	
failed_return:
	SAFE_CLOSE(fr);
	SAFE_FREE(data);
	
	return 0;
}

void ResManager::Resource_Free(void *data)
{
	SAFE_FREE(data);
}

rgechar* ResManager::Resource_MakePath(const rgechar *filename)
{
	//int i;

	if (!filename)
		rgestrcpy(szTmpFilename, szAppPath);
	else if (filename[0] == '\\' || filename[0] == '/' || filename[1] == ':')
		rgestrcpy(szTmpFilename, filename);
	else
	{
		rgestrcpy(szTmpFilename, szAppPath);
		if (filename) rgestrcat(szTmpFilename, filename);
	}

	//for (i = 0; szTmpFilename[i]; ++i) { if (szTmpFilename[i] == '/') szTmpFilename[i] = '\\'; }
	
	return szTmpFilename;
}
