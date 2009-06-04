/**
 *	@file		main.cpp
 *
 *	@desc		DodInput≤‚ ‘π§≥Ã
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11
 */
#include <DodInput.h>

//	define the sample title
#define DOD_SAMPLE_TITLE "DodInputTest"

//	include common cpp
#include "../common.cpp"

int main(void)
{
	pspDebugScreenInit();
	SetupCallbacks();

	Dod::DodInput::Init();

	while(!g_done)
	{
		pspDebugScreenSetXY(0, 2);

		Dod::DodInput::Update();

		printf("Analog X = %d", Dod::DodInput::GetAnalogX());
		printf("Analog Y = %d\n", Dod::DodInput::GetAnalogY());

		if (Dod::DodInput::IsPress(Dod::DodInput::DOD_KEY_SQUARE))
		{
			printf("Square press \n");
		}
		if (Dod::DodInput::IsTrigger(Dod::DodInput::DOD_KEY_TRIANGLE))
		{
			printf("Triangle trigger \n");
		} 
		if (Dod::DodInput::IsRelease(Dod::DodInput::DOD_KEY_CIRCLE))
		{
			printf("Cicle release \n");
		} 
		if (Dod::DodInput::IsRepeat(Dod::DodInput::DOD_KEY_CROSS))
		{
			printf("Cross repeat \n");
		}
	}

	sceKernelExitGame();

	return 0;
}
