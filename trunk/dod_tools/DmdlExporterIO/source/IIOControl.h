#ifndef __I_IO_CONTROL_H__
#define __I_IO_CONTROL_H__

#include <comdef.h>
#include <atlbase.h>
#include <atlcom.h>

// {885DD576-4317-41f6-8517-64AE3A3B460C}
static const GUID IID_IIOControl = 
{ 0x885dd576, 0x4317, 0x41f6, { 0x85, 0x17, 0x64, 0xae, 0x3a, 0x3b, 0x46, 0xc } };

struct __declspec(novtable) IIOControl : public IDispatch
{
//	STDMETHOD(GetCast)(Config cfg, struct ICast** pRetVal) = 0;
//	STDMETHOD(GetMovie)(Config cfg, struct IMovie** pRetVal) = 0;
//	STDMETHOD(GetDefaultConfig)(struct IDefaultConfig** pRetVal) = 0;
};

struct __declspec(uuid("885DD576-4317-41f6-8517-64AE3A3B460C")) IIOControl;
_COM_SMARTPTR_TYPEDEF(IIOControl, __uuidof(IIOControl));

class IOControl : public IDispatchImpl<IIOControl>
{
public:
	IOControl() : m_dwRef(0){}
	~IOControl(){}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void __RPC_FAR *__RPC_FAR *ppvObject);
	ULONG	STDMETHODCALLTYPE AddRef(void);
	ULONG	STDMETHODCALLTYPE Release(void);

private:
	DWORD			m_dwRef;
};

#endif	//	__I_IO_CONTROL_H__