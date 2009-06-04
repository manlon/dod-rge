#include "DodInput.h"

#include <string.h>

namespace Dod
{
namespace DodInput
{
	static SceCtrlData	sPad;
	static KeyStatus	sStatus;

	static KeyRepeat	sRepeat;
	
	void Init()
	{
		sceCtrlSetSamplingCycle(0);
		sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
		
		memset(&sPad, 0, sizeof(sPad));
		memset(&sStatus, 0, sizeof(sStatus));
		memset(&sRepeat, 0, sizeof(sRepeat));
		
		sRepeat.startFrame = DOD_DEFAULT_START_FRAME;
		sRepeat.intervalFrame = DOD_DEFAULT_INTERVAL_FRAME;
	}
	
	void SetRepeat(u32 start, u32 interval)
	{
		sRepeat.startFrame = start;
		sRepeat.intervalFrame = interval;
	}

	void Update()
	{
		//KeyStatus	lPrevStatus;
		//memcpy(&lPrevStatus, &sStatus, sizeof(KeyStatus));
		
	 	sceCtrlReadBufferPositive(&sPad, 1); 
	 	
		sStatus.trigger = ((sStatus.trigger ^ sPad.Buttons) & ~sStatus.press);
		//sStatus.release = ((sStatus.press ^ sStatus.press) & sStatus.press);
		sStatus.release = ((sStatus.release ^ ~sPad.Buttons) & sStatus.press);
		sStatus.press   = sPad.Buttons;

		sStatus.repeat = 0;
		for (s32 id = 0; id < DOD_KEY_MAX_NUMS; ++id)
		{
			const u32  bit = (u32)(1 << id);
			if (sStatus.press & bit)
			{
				const s32 startCnt = (s32)(sRepeat.frameCnt[id] - sRepeat.startFrame);
				if ((sStatus.trigger & bit) || (startCnt >= 0 && startCnt % sRepeat.intervalFrame == 0))   
				{
					sStatus.repeat |= bit;
				}
				++sRepeat.frameCnt[id];
			}
			else
			{
				sRepeat.frameCnt[id] = 0;
			}
		}
		
		sStatus.prevX = sStatus.x;
		sStatus.prevY = sStatus.y;
		sStatus.x = sPad.Lx;
		sStatus.y = sPad.Ly;
	}
	
	bool IsPress(DodButtons key)
	{
		return sStatus.press & key;
	}
	bool IsTrigger(DodButtons key)
	{
		return sStatus.trigger & key;
	}
	bool IsRelease(DodButtons key)
	{
		return sStatus.release & key;
	}
	bool IsRepeat(DodButtons key)
	{
		return sStatus.repeat & key;
	}
	
	u8 GetAnalogX()
	{
		return sStatus.x;
	}
	u8 GetAnalogY()
	{
		return sStatus.y;
	}
	u8 GetAnalogPrevX()
	{
		return sStatus.prevX;
	}
	u8 GetAnalogPrevY()
	{
		return sStatus.prevY;
	}
}
}
