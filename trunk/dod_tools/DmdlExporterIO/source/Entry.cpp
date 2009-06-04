#include "IIOControl.h"
#include "IEntry.h"
#include "DodClrHost.h"

#include "Max.h"

//DISPID dispid;
//LPOLESTR rgszName = L"start";
//pDisp->GetIDsOfNames(IID_NULL, &rgszName, 1, LOCALE_SYSTEM_DEFAULT, &dispid);

//DISPPARAMS dispArgs = {NULL, NULL, 0, 0};
//dispArgs.cArgs = 1;
//VARIANTARG	vargs;
//VariantInit(&vargs);

//vargs.vt = VT_PTR;
//vargs.v = IIOControlPtr(new IOControl());

//dispArgs.rgvarg = &vargs;

//pDisp->Invoke(dispid, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dispArgs, NULL, NULL, NULL);

HINSTANCE hInstance = NULL;

#include "core/DodGlobalVar.h"
DodGlobalVar	g_vars;


static DodClrHost g_clr_host;

BOOL WINAPI DllMain(HINSTANCE hinstDLL,ULONG fdwReason,LPVOID /*lpvReserved*/)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		hInstance = hinstDLL;
	}
	return TRUE;
}

extern "C" __declspec(dllexport)
int	DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts, DWORD options)
{
//	DodScene lScene(ei->theScene, i->GetTime(), i);

	if (!g_clr_host.Start())
	{
		MessageBoxA(i->GetMAXHWnd(), "Start CLR Environment Failed!", "Error", MB_ICONERROR);
		return TRUE;
	}

	char szDllPath[_MAX_PATH];
	{
		DWORD uDllPathLen = GetModuleFileName(hInstance, szDllPath, _MAX_PATH);
		for (DWORD idx = uDllPathLen - 1; idx >= 0; --idx)
		{
			if (szDllPath[idx] == '\\')
			{
				szDllPath[idx + 1] = 0;
				break;
			}
		}
	}
	g_clr_host.AddSearchPath(_bstr_t(szDllPath));

	try
	{
		CComPtr<IDispatch>& pDisp = g_clr_host.CreateInstance(L"DmdlExporterEntry", L"DmdlExporterEntry.Entry");
		if (pDisp)
		{
			CComPtr<IEntry>	pEntry = NULL;

			pDisp->QueryInterface(IID_IEntry, (void**)&pEntry);

			if (pEntry)
			{
				IIOControlPtr pControlPtr(new IOControl);
				if (FAILED(pEntry->start(pControlPtr)))
				{
					MessageBoxA(i->GetMAXHWnd(), "Call `start' Method Failed!", "Error", MB_ICONERROR);
				}

				pEntry = NULL;
				pControlPtr = NULL;
			}
			else
			{
				MessageBoxA(i->GetMAXHWnd(), "Get `IEntry' Interface Pointer Failed!", "Error", MB_ICONERROR);
			}
		}
		else
		{
			MessageBoxA(i->GetMAXHWnd(), "Get `IID_IEntry' Interface Pointer Failed!", "Error", MB_ICONERROR);
		}
	}
	catch(...)
	{
		MessageBoxA(i->GetMAXHWnd(), "Get `IDispatch' Interface Pointer Failed!", "Error", MB_ICONERROR);
	}

	g_clr_host.Stop();

	return TRUE;
}