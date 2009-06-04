#include "DodClrHost.h"

bool DodClrHost::Start()
{
	if (m_started)
		return true;

	if (FAILED(CorBindToRuntimeEx(
		NULL,
		L"wks",
		STARTUP_LOADER_OPTIMIZATION_SINGLE_DOMAIN | STARTUP_CONCURRENT_GC,
		CLSID_CorRuntimeHost,
		IID_ICorRuntimeHost ,
		(void**)&m_pCorHost)))
		return FALSE;

	if (FAILED(m_pCorHost->Start()))
		return FALSE;

	CComPtr<IUnknown>	pUnk = NULL;

	if (FAILED(m_pCorHost->CurrentDomain(&pUnk)))
		return FALSE;

	m_pAppDomain = pUnk;
	pUnk = NULL;

	return (m_started = true);
}

void DodClrHost::Stop()
{
	if (m_started)
	{
		m_pAppDomain = NULL;
		m_pCorHost->Stop();
		m_pCorHost = NULL;

		m_pDispatch = NULL;

		m_started = false;
	}
}

void DodClrHost::AddSearchPath(_bstr_t Path)
{
	if (m_started)
	{
		m_pAppDomain->AppendPrivatePath(Path);
	}
}

CComPtr<IDispatch>& DodClrHost::CreateInstance(_bstr_t AssemblyName, _bstr_t typeName)
{
	m_pDispatch = NULL;

	if (!m_started)	return m_pDispatch;
	
	mscorlib::_ObjectHandlePtr pObj = m_pAppDomain->CreateInstance(AssemblyName, typeName);

	m_pDispatch = pObj->Unwrap().pdispVal;

	return m_pDispatch;
}