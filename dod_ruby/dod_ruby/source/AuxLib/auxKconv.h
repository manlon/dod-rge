#ifndef __AUX_KCODE_CONVERT_H__
#define __AUX_KCODE_CONVERT_H__

#include <assert.h>

struct auxKconv
{
	typedef char*		MB_STRING;
	typedef wchar_t*	WB_STRING;

	MB_STRING	mb_origin_string;	// ���ֽ� ԭʼ�ַ���
	WB_STRING	wb_origin_string;	// ���ֽ� ԭʼ�ַ���

	MB_STRING	mb_utf8_string;		// ���ֽ� Ŀ��UTF8�ַ���
	MB_STRING	mb_ansi_string;		// ���ֽ� Ŀ��ANSI�ַ���
	WB_STRING	wb_string;			// ���ֽ� Ŀ��Unicode�ַ���

	BOOL		bIsUTF8;			// �Ƿ�ΪUTF8�ַ�����TRUE��UTF8��FALSEΪAnsi��

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
	 *	Ansi ת Unicode
	 */
	WB_STRING AnsiToUnicode()
	{
		// ���ԭ�����ַ����Ƿ�ΪAnsi�ַ���
		assert(mb_origin_string && !bIsUTF8);

		// ����Ѿ�ת������ֱ�ӷ���Ŀ����ַ���ָ��
		if (wb_string) return wb_string;

		// Ansi ת Unicode
		int wide_str_len = MultiByteToWideChar(CP_ACP, 0, mb_origin_string, -1, NULL, 0);
		wb_string = new wchar_t[wide_str_len];

		assert(wb_string);

		MultiByteToWideChar(CP_ACP, 0, mb_origin_string, -1, wb_string, wide_str_len);

		return wb_string;
	}

	/*
	 *	UTF8 ת Unicode
	 */
	WB_STRING UTF8ToUnicode()
	{
		// ���ԭ�����ַ����Ƿ�ΪUTF8�ַ���
		assert(mb_origin_string && bIsUTF8);

		// ����Ѿ�ת������ֱ�ӷ���Ŀ����ַ���ָ��
		if (wb_string) return wb_string;

		// UTF8 ת Unicode
		int wide_str_len = MultiByteToWideChar(CP_UTF8, 0, mb_origin_string, -1, NULL, 0);
		wb_string = new wchar_t[wide_str_len];

		assert(wb_string);

		MultiByteToWideChar(CP_UTF8, 0, mb_origin_string, -1, wb_string, wide_str_len);

		return wb_string;
	}

	/*
	 *	Unicode ת Ansi
	 */
	MB_STRING UnicodeToAnsi()
	{
		//	���ԭ�����ַ����Ƿ�ΪUnicode�ַ���
		assert(wb_origin_string);

		// ����Ѿ�ת������ֱ�ӷ���Ansi�ַ���ָ��
		if (mb_ansi_string) return mb_ansi_string;

		//	Unicode ת Ansi
		int ansi_len = WideCharToMultiByte(CP_ACP, 0, wb_origin_string, -1, NULL, 0, NULL, NULL);
		mb_ansi_string = new char[ansi_len];

		assert(mb_ansi_string);

		WideCharToMultiByte(CP_ACP, 0, wb_origin_string, -1, (LPSTR)mb_ansi_string, ansi_len, NULL, NULL);

		return mb_ansi_string;
	}

	/*
	 *	Unicode ת UTF8
	 */
	MB_STRING UnicodeToUTF8()
	{
		//	���ԭ�����ַ����Ƿ�ΪUnicode�ַ���
		assert(wb_origin_string);

		// ����Ѿ�ת������ֱ�ӷ���UTF8�ַ���ָ��
		if (mb_utf8_string) return mb_utf8_string;

		//	Unicode ת UTF8
		int utf8_len = WideCharToMultiByte(CP_UTF8, 0, wb_origin_string, -1, NULL, 0, NULL, NULL);
		mb_utf8_string = new char[utf8_len];

		assert(mb_utf8_string);

		WideCharToMultiByte(CP_UTF8, 0, wb_origin_string, -1, (LPSTR)mb_utf8_string, utf8_len, NULL, NULL);

		return mb_utf8_string;
	}

	/*
	 *	UTF8 ת Ansi
	 */
	MB_STRING UTF8ToAnsi()
	{
		//	���ԭ�����ַ����Ƿ�ΪUTF8�ַ���
		assert(mb_origin_string && bIsUTF8);

		//	�Ѿ�ת�����˵���ֱ�ӷ���UTF8�ַ���ָ��
		if (mb_utf8_string)	return mb_utf8_string;

		//	UTF8 ת Unicode
		int wide_str_len = MultiByteToWideChar(CP_UTF8, 0, mb_origin_string, -1, NULL, 0);
		wchar_t	*wide_str_buf = new wchar_t[wide_str_len];

		assert(wide_str_buf);

		MultiByteToWideChar(CP_UTF8, 0, mb_origin_string, -1, wide_str_buf, wide_str_len);

		//	Unicode ת Ansi
		int ansi_len = WideCharToMultiByte(CP_ACP, 0, wide_str_buf, -1, NULL, 0, NULL, NULL);
		mb_ansi_string = new char[ansi_len];

		assert(mb_ansi_string);

		WideCharToMultiByte(CP_ACP, 0, wide_str_buf, -1, (LPSTR)mb_ansi_string, ansi_len, NULL, NULL);

		//	�ͷ��м仺����
		delete [] wide_str_buf;

		//	����Ansi�ַ���ָ��
		return mb_ansi_string;
	}

	/*
	 *	Ansi ת UTF8
	 */
	MB_STRING AnsiToUTF8()
	{
		//	���ԭ�����ַ����Ƿ�ΪAnsi�ַ���
		assert(mb_origin_string && !bIsUTF8);

		//	�Ѿ�ת�����˵���ֱ�ӷ���Ansi�ַ���ָ��
		if (mb_ansi_string)	return mb_ansi_string;

		// Ansi ת Unicode
		int wide_str_len = MultiByteToWideChar(CP_ACP, 0, mb_origin_string, -1, NULL, 0);
		wchar_t	*wide_str_buf = new wchar_t[wide_str_len];

		assert(wide_str_buf);

		MultiByteToWideChar(CP_ACP, 0, mb_origin_string, -1, wide_str_buf, wide_str_len);

		//	Unicode ת UTF8
		int utf8_len = WideCharToMultiByte(CP_UTF8, 0, wb_origin_string, -1, NULL, 0, NULL, NULL);
		mb_utf8_string = new char[utf8_len];

		assert(mb_utf8_string);

		WideCharToMultiByte(CP_UTF8, 0, wb_origin_string, -1, (LPSTR)mb_utf8_string, utf8_len, NULL, NULL);

		//	�ͷ��м仺����
		delete [] wide_str_buf;

		return mb_utf8_string;
	}
};

#endif