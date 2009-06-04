#ifndef __AUX_KCODE_CONVERT_H__
#define __AUX_KCODE_CONVERT_H__

#include <assert.h>

struct auxKconv
{
	typedef char*		MB_STRING;
	typedef wchar_t*	WB_STRING;

	MB_STRING	mb_origin_string;	// 多字节 原始字符串
	WB_STRING	wb_origin_string;	// 宽字节 原始字符串

	MB_STRING	mb_utf8_string;		// 多字节 目标UTF8字符串
	MB_STRING	mb_ansi_string;		// 多字节 目标ANSI字符串
	WB_STRING	wb_string;			// 宽字节 目标Unicode字符串

	BOOL		bIsUTF8;			// 是否为UTF8字符传，TRUE即UTF8，FALSE为Ansi。

	auxKconv()
	{
	}

	auxKconv(MB_STRING str, BOOL isUTF8 = TRUE)
	{
		assert(str);

		mb_origin_string = str;
		wb_origin_string = 0;
		mb_utf8_string = 0;
		mb_ansi_string = 0;
		wb_string = 0;

		bIsUTF8 = isUTF8;
	}

	auxKconv(WB_STRING str)
	{
		assert(str);

		wb_origin_string = str;
		mb_origin_string = 0;
		mb_utf8_string = 0;
		mb_ansi_string = 0;
		wb_string = 0;
	}

	~auxKconv()
	{
		if (mb_utf8_string)
		{
			delete [] mb_utf8_string;
			mb_utf8_string = 0;
		}
		if (mb_ansi_string)
		{
			delete [] mb_ansi_string;
			mb_ansi_string = 0;
		}
		if (wb_string)
		{
			delete [] wb_string;
			wb_string = 0;
		}
		mb_origin_string = 0;
		wb_origin_string = 0;
	}

	/*
	 *	Ansi 转 Unicode
	 */
	WB_STRING AnsiToUnicode()
	{
		// 检查原来的字符串是否为Ansi字符串
		assert(mb_origin_string && !bIsUTF8);

		// 如果已经转换了则直接返回目标宽字符串指针
		if (wb_string) return wb_string;

		// Ansi 转 Unicode
		int wide_str_len = MultiByteToWideChar(CP_ACP, 0, mb_origin_string, -1, NULL, 0);
		wb_string = new wchar_t[wide_str_len];

		assert(wb_string);

		MultiByteToWideChar(CP_ACP, 0, mb_origin_string, -1, wb_string, wide_str_len);

		return wb_string;
	}

	/*
	 *	UTF8 转 Unicode
	 */
	WB_STRING UTF8ToUnicode()
	{
		// 检查原来的字符串是否为UTF8字符串
		assert(mb_origin_string && bIsUTF8);

		// 如果已经转换了则直接返回目标宽字符串指针
		if (wb_string) return wb_string;

		// UTF8 转 Unicode
		int wide_str_len = MultiByteToWideChar(CP_UTF8, 0, mb_origin_string, -1, NULL, 0);
		wb_string = new wchar_t[wide_str_len];

		assert(wb_string);

		MultiByteToWideChar(CP_UTF8, 0, mb_origin_string, -1, wb_string, wide_str_len);

		return wb_string;
	}

	/*
	 *	Unicode 转 Ansi
	 */
	MB_STRING UnicodeToAnsi()
	{
		//	检查原来的字符串是否为Unicode字符串
		assert(wb_origin_string);

		// 如果已经转换了则直接返回Ansi字符串指针
		if (mb_ansi_string) return mb_ansi_string;

		//	Unicode 转 Ansi
		int ansi_len = WideCharToMultiByte(CP_ACP, 0, wb_origin_string, -1, NULL, 0, NULL, NULL);
		mb_ansi_string = new char[ansi_len];

		assert(mb_ansi_string);

		WideCharToMultiByte(CP_ACP, 0, wb_origin_string, -1, (LPSTR)mb_ansi_string, ansi_len, NULL, NULL);

		return mb_ansi_string;
	}

	/*
	 *	Unicode 转 UTF8
	 */
	MB_STRING UnicodeToUTF8()
	{
		//	检查原来的字符串是否为Unicode字符串
		assert(wb_origin_string);

		// 如果已经转换了则直接返回UTF8字符串指针
		if (mb_utf8_string) return mb_utf8_string;

		//	Unicode 转 UTF8
		int utf8_len = WideCharToMultiByte(CP_UTF8, 0, wb_origin_string, -1, NULL, 0, NULL, NULL);
		mb_utf8_string = new char[utf8_len];

		assert(mb_utf8_string);

		WideCharToMultiByte(CP_UTF8, 0, wb_origin_string, -1, (LPSTR)mb_utf8_string, utf8_len, NULL, NULL);

		return mb_utf8_string;
	}

	/*
	 *	UTF8 转 Ansi
	 */
	MB_STRING UTF8ToAnsi()
	{
		//	检查原来的字符串是否为UTF8字符串
		assert(mb_origin_string && bIsUTF8);

		//	已经转换好了的则直接返回UTF8字符串指针
		if (mb_utf8_string)	return mb_utf8_string;

		//	UTF8 转 Unicode
		int wide_str_len = MultiByteToWideChar(CP_UTF8, 0, mb_origin_string, -1, NULL, 0);
		wchar_t	*wide_str_buf = new wchar_t[wide_str_len];

		assert(wide_str_buf);

		MultiByteToWideChar(CP_UTF8, 0, mb_origin_string, -1, wide_str_buf, wide_str_len);

		//	Unicode 转 Ansi
		int ansi_len = WideCharToMultiByte(CP_ACP, 0, wide_str_buf, -1, NULL, 0, NULL, NULL);
		mb_ansi_string = new char[ansi_len];

		assert(mb_ansi_string);

		WideCharToMultiByte(CP_ACP, 0, wide_str_buf, -1, (LPSTR)mb_ansi_string, ansi_len, NULL, NULL);

		//	释放中间缓冲区
		delete [] wide_str_buf;

		//	返回Ansi字符串指针
		return mb_ansi_string;
	}

	/*
	 *	Ansi 转 UTF8
	 */
	MB_STRING AnsiToUTF8()
	{
		//	检查原来的字符串是否为Ansi字符串
		assert(mb_origin_string && !bIsUTF8);

		//	已经转换好了的则直接返回Ansi字符串指针
		if (mb_ansi_string)	return mb_ansi_string;

		// Ansi 转 Unicode
		int wide_str_len = MultiByteToWideChar(CP_ACP, 0, mb_origin_string, -1, NULL, 0);
		wchar_t	*wide_str_buf = new wchar_t[wide_str_len];

		assert(wide_str_buf);

		MultiByteToWideChar(CP_ACP, 0, mb_origin_string, -1, wide_str_buf, wide_str_len);

		//	Unicode 转 UTF8
		int utf8_len = WideCharToMultiByte(CP_UTF8, 0, wb_origin_string, -1, NULL, 0, NULL, NULL);
		mb_utf8_string = new char[utf8_len];

		assert(mb_utf8_string);

		WideCharToMultiByte(CP_UTF8, 0, wb_origin_string, -1, (LPSTR)mb_utf8_string, utf8_len, NULL, NULL);

		//	释放中间缓冲区
		delete [] wide_str_buf;

		return mb_utf8_string;
	}
};

#endif