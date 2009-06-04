#ifndef __I_ENTRY_H__
#define __I_ENTRY_H__

#include <comdef.h>

// {8B1E9531-98EF-4c86-83D7-9F2B3BDAE30E}
static const GUID IID_IEntry = 
{ 0x8b1e9531, 0x98ef, 0x4c86, { 0x83, 0xd7, 0x9f, 0x2b, 0x3b, 0xda, 0xe3, 0xe } };

struct __declspec(novtable) IEntry : public IDispatch
{
//	STDMETHOD(start)(IControlPtr pControl, BSTR);
	STDMETHOD(start)(IIOControlPtr pControl);
};

#endif	//	__I_ENTRY_H__