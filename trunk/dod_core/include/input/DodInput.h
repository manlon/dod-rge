#ifndef __DOD_INPUT_H__
#define __DOD_INPUT_H__

#include <pspctrl.h>

#include "dod_types.h"
 
namespace Dod
{
namespace DodInput
{
	/**
	 * Enumeration for the digital controller buttons.
	 *
	 * @note DOD_KEY_NOTE, DOD_KEY_SCREEN, DOD_KEY_VOLUP, DOD_KEY_VOLDOWN, DOD_KEY_DISC, DOD_KEY_WLAN_UP, DOD_KEY_REMOTE, DOD_KEY_MS can only be read in kernel mode
	 */
	enum DodButtons
	{
		DOD_KEY_SELECT     	= 0x000001,	//	Select button
		DOD_KEY_START      	= 0x000008,	//	Start button
		DOD_KEY_UP         	= 0x000010,	//	Up D-Pad button
		DOD_KEY_RIGHT      	= 0x000020,	//	Right D-Pad button
		DOD_KEY_DOWN      	= 0x000040,	//	Down D-Pad button
		DOD_KEY_LEFT    	= 0x000080,	//	Left D-Pad button
		DOD_KEY_LTRIGGER   	= 0x000100,	//	Left trigger
		DOD_KEY_RTRIGGER   	= 0x000200,	//	Right trigger
		DOD_KEY_TRIANGLE   	= 0x001000,	//	Triangle button
		DOD_KEY_CIRCLE     	= 0x002000,	//	Circle button
		DOD_KEY_CROSS      	= 0x004000,	//	Cross button
		DOD_KEY_SQUARE     	= 0x008000,	//	Square button
		DOD_KEY_HOME       	= 0x010000,	//	Home button
		DOD_KEY_HOLD       	= 0x020000,	//	Hold button
		DOD_KEY_NOTE       	= 0x800000,	//	Music Note button
		DOD_KEY_SCREEN     	= 0x400000,	//	Screen button
		DOD_KEY_VOLUP      	= 0x100000,	//	Volume up button
		DOD_KEY_VOLDOWN    	= 0x200000,	//	Volume down button
		DOD_KEY_WLAN_UP    	= 0x040000,	//	Wlan switch up
		DOD_KEY_REMOTE     	= 0x080000,	//	Remote hold position
		DOD_KEY_DISC       	= 0x1000000,//	Disc present
		DOD_KEY_MS         	= 0x2000000,//	Memory stick present
	};
	
	#define	DOD_KEY_MAX_NUMS 			32
	#define DOD_DEFAULT_START_FRAME		3
	#define DOD_DEFAULT_INTERVAL_FRAME 	6
	
	struct KeyStatus
	{
		u32	press;
		u32	trigger;
		u32	release;
		u32	repeat;	
		u8	x, y;
		u8	prevX, prevY;
	};
	
	struct KeyRepeat
	{
		u32  frameCnt[DOD_KEY_MAX_NUMS];
		u32  startFrame;
		u32  intervalFrame;
	};
	
	void	Init();
	
	void 	SetRepeat(u32 start, u32 interval);

	void	Update();
	
	bool	IsPress(DodButtons key);
	bool	IsTrigger(DodButtons key);
	bool	IsRelease(DodButtons key);
	bool	IsRepeat(DodButtons key);
	
	u8		GetAnalogX();
	u8		GetAnalogY();
	u8		GetAnalogPrevX();
	u8		GetAnalogPrevY();
}
}

#endif
