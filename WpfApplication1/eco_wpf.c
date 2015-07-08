/****************************************************************

eco_platform.c

=============================================================

Copyright 1996-2015 Tom Barbalet. All rights reserved.

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

This software and Noble Ape are a continuing work of Tom Barbalet,
begun on 13 June 1996. No apes or cats were harmed in the writing
of this software.

****************************************************************/
///* ecowind.c */
//#include <QuickDraw.h>
//#include <Types.h>
//#include <Dialogs.h>
//#include <Desk.h>
//#include <ToolUtils.h>
//#include <Packages.h>
//#include <Files.h>
//
//#include <Controls.h>
//#include <Events.h>
//#include <Windows.h>
//#include <Menus.h>
//
#include "eco_system.h"

#include "ecosim.h"
#include "windows.h"

//WindowPtr		awind, pwind, gwind;
//PicHandle		phnd, phnd2;
HWND	anich[7], plch, gobut;
//MenuHandle		appleMenu, fileMenu, editMenu, graphMenu, animalsMenu;
//CIconHandle		icons[15];

short			curcrit = -1;
short			timdel;
char			running = 1;
short			prevplant, prevanimal;

RECT			dragRect = { 0, 0, 2048, 1024 };

short			values[14];
short			highest;
short			drvals[14], odrvals[14];

long			stime;
unsigned char	graphvar[14][280];


void InitGraphin()
{
	short	lp;

	highest = -1;
	lp = 0;
	while (lp<14)
	{
		values[lp] = GetPop(lp);
		if (values[lp]>highest) highest = values[lp];
		odrvals[lp] = 0;
		lp++;
	}

	if (highest == 0) highest = 1;

	lp = 0;
	while (lp<14)
	{
		drvals[lp] = ((80 * values[lp]) / highest);
		lp++;
	}
}

void LoadGraphin()
{
	short	lp;

	highest = -1;
	lp = 0;
	while (lp<14)
	{
		values[lp] = GetPop(lp);
		if (values[lp]>highest) highest = values[lp];
		lp++;
	}

	if (highest == 0) highest = 1;

	lp = 0;
	while (lp<14)
	{
		odrvals[lp] = drvals[lp];
		drvals[lp] = ((80 * values[lp]) / highest);
		lp++;
	}
}

void DrawGraphin(HDC gDC)
{
	short	lp, diflp;
	HPEN grayPen;
	HPEN whitePen;

	grayPen = CreatePen(PS_SOLID, 2, RGB(128, 128, 128));
	whitePen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));

	//SetPort(gwind);
	lp = 0;
	while (lp<14)
	{
		if (drvals[lp]>odrvals[lp])
		{
			SelectObject(gDC, grayPen);
			//PenPat(&qd.gray);
			diflp = odrvals[lp];
			while (diflp <= drvals[lp])
			{
				
				MoveToEx(gDC, 6 + (lp * 21), 95 - diflp, NULL);
				LineTo(gDC, 17 + (lp * 21), 95 - diflp);
				diflp++;
			}
		}
		if (drvals[lp]<odrvals[lp])
		{
			SelectObject(gDC, whitePen);
			//PenPat(&qd.white);
			diflp = drvals[lp];
			while (diflp <= odrvals[lp])
			{
				MoveToEx(gDC, 6 + (lp * 21), 95 - diflp, NULL);
				LineTo(gDC, 17 + (lp * 21), 95 - diflp);
				diflp++;
			}
		}

		lp++;
	}
	DeleteObject(grayPen);
	DeleteObject(whitePen);
}

void DrawControlIcns()
{

	//Rect 	conts;

	//conts.top = 29;
	//conts.left = 32;
	//conts.bottom = conts.top + 32;
	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[cApe]);

	//conts.left = 104;

	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[cLiz]);

	//conts.left = 166;


	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[cCat]);

	//conts.top = 112;
	//conts.left = 32;
	//conts.bottom = conts.top + 32;

	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[cIEB]);

	//conts.left = 104;
	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[cFrog]);

	//conts.left = 166;
	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[cBoP]);


	//conts.top = 198;
	//conts.left = 3;
	//conts.bottom = conts.top + 32;
	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[cSeEB]);
	//conts.left = 68;
	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[cIns]);
	//conts.left = 134;
	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[cMous]);
	//conts.left = 200;
	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[cSeaB]);

	//conts.top = 282;
	//conts.left = 3;
	//conts.bottom = conts.top + 32;
	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[cBush]);
	//conts.left = 68;
	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[cTree]);
	//conts.left = 134;
	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[cGrass]);
	//conts.left = 200;
	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[cFish]);
}


void DrawAni(num)

short	num;
{
	//Rect 	conts;

	//short	na = 14, nb = 14, nc = 14, nd = 14, ne = 14;

	//if (num == cSeEB)
	//	na = cBush;

	//if (num == cIns)
	//{
	//	na = cBush;
	//	nb = cTree;
	//	nc = cGrass;
	//}
	//if (num == cBoP)
	//{
	//	na = cMous;
	//	nb = cFrog;
	//	nc = cFish;
	//}
	//if (num == cApe)
	//{
	//	na = cBush;
	//	nb = cFish;
	//	nc = cLiz;
	//}

	//if (num == cLiz)
	//{
	//	nd = cSeEB;
	//	ne = cIEB;
	//	nc = cFrog;
	//	nb = cMous;
	//	na = cIns;
	//}

	//if (num == cCat)
	//{
	//	na = cSeaB;
	//	nb = cIEB;
	//	nc = cLiz;
	//	nd = cBoP;
	//	ne = cApe;
	//}

	//if (num == cMous)
	//	na = cGrass;
	//if (num == cSeaB)
	//	na = cFish;
	//if (num == cFrog)
	//	na = cIns;
	//if (num == cIEB)
	//	na = cIns;

	//conts.top = 18;
	//conts.left = 2;
	//conts.bottom = conts.top + 32;
	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[num]);

	//conts.top = 60;
	//conts.left = 36;
	//conts.bottom = conts.top + 32;
	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[na]);

	//conts.top = 96;
	//conts.left = 36;
	//conts.bottom = conts.top + 32;
	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[nc]);

	//conts.top = 60;
	//conts.left = 166;
	//conts.bottom = conts.top + 32;
	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[nb]);

	//conts.top = 96;
	//conts.left = 166;
	//conts.bottom = conts.top + 32;
	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[nd]);

	//conts.top = 128;
	//conts.left = 166;
	//conts.bottom = conts.top + 32;
	//conts.right = conts.left + 32;
	//PlotCIcon(&conts, icons[ne]);

}



void MenuNumLinkCall(num)
short	num;
{
	//SetPort(awind);
	//DrawAni(num);
}

void SetNaming(num, anim)
short	num, anim;
{
	/*short	lp = 0, lp2;

	SetPort(awind);

	if (num == -1)
		HiliteControl(anich[1], 255);
	else
		HiliteControl(anich[1], 0);

	while (lp<num)
	{
		HiliteControl(anich[lp + 2], 0);
		lp++;
	}

	lp2 = 0;
	while (lp2<5)
	{
		if (num>lp2)
			SetControlValue(anich[2 + lp2], GetVar(anim, lp2));
		lp2++;
	}

	if (lp<5) while (lp<5)
	{
		HiliteControl(anich[lp + 2], 255);
		lp++;
	}
	SetControlValue(anich[0], GetPop(anim));
	SetControlValue(anich[1], GetGrow(anim));*/

}

void SetValues(num, anim)
short	num, anim;
{
	//short	lp;

	//SetPop(anim, GetControlValue(anich[0]));
	//SetGrow(anim, GetControlValue(anich[1]));
	//lp = 0;
	//while (lp<5)
	//{
	//	if (num>lp)
	//		SetVal(anim, lp, GetControlValue(anich[2 + lp]));
	//	lp++;
	//}
}


void EndWindows()
{
	/*short	lp;

	if (awind != 0)
		DisposeWindow(awind);
	if (pwind != 0)
		DisposeWindow(pwind);
	if (gwind != 0)
		DisposeWindow(gwind);

	if (phnd != 0)
		KillPicture(phnd);
	if (phnd2 != 0)
		KillPicture(phnd2);

	lp = 0;
	while (lp<7)
	{
		if (anich[lp] != 0)
			DisposeControl(anich[lp]);
		lp++;
	}
	if (plch != 0)
		DisposeControl(plch);
	if (gobut != 0)
		DisposeControl(gobut);

	if (appleMenu != 0)
		DisposeMenu(appleMenu);
	if (fileMenu != 0)
		DisposeMenu(fileMenu);
	if (editMenu != 0)
		DisposeMenu(editMenu);
	if (graphMenu != 0)
		DisposeMenu(graphMenu);
	if (animalsMenu != 0)
		DisposeMenu(animalsMenu);
	lp = 0;
	while (lp<15)
	{
		if (icons[lp] != 0)
			DisposeCIcon(icons[lp]);
		lp++;
	}
*/
}



void SetUpCtrls(num)
short	num;
{
	//curcrit = num;
	//switch (num)
	//{

	//case cGrass:
	//case cBush:
	//case cTree:
	//	SetNaming(0, num);
	//	break;

	//case cIEB:
	//case cSeEB:
	//case cSeaB:
	//case cMous:
	//case cFrog:
	//	SetNaming(1, num);
	//	break;

	//case cBoP:
	//case cIns:
	//case cApe:
	//	SetNaming(3, num);
	//	break;

	//case cLiz:
	//case cCat:
	//	SetNaming(5, num);
	//	break;

	//case cFish:
	//	SetNaming(-1, num);
	//	break;

	//}
}


void ReplaceCtrls(num)
short	num;
{
	//switch (num)
	//{
	//case cGrass:
	//case cBush:
	//case cTree:
	//	SetValues(0, num);
	//	break;

	//case cIEB:
	//case cSeEB:
	//case cSeaB:
	//case cMous:
	//case cFrog:
	//	SetValues(1, num);
	//	break;

	//case cBoP:
	//case cIns:
	//case cApe:
	//	SetValues(3, num);
	//	break;

	//case cLiz:
	//case cCat:
	//	SetValues(5, num);
	//	break;

	//case cFish:
	//	SetValues(-1, num);
	//	break;
	//}
}

void NumtoMenu(num)
short	num;
{
	//short	tmp;

	//tmp = num + 1;
	//if (num>2) tmp++;
	//if (num>6) tmp++;
	//if (num>11) tmp++;

	//SetItemMark(animalsMenu, prevanimal, noMark);
	//SetItemMark(animalsMenu, prevanimal = tmp, checkMark);
}


short	num_menu(num)
short	num;
{
	short	tmp;

	tmp = num - 1;
	if (num>14)tmp--;
	if (num>8) tmp--;
	if (num>3) tmp--;
	return(tmp);
}

void DoCommand(mResult)
long mResult;
{
	/*int			theItem;
	Str255		name;
	char		quit = 1;
	short		tmp;

	theItem = LoWord(mResult);
	switch (HiWord(mResult))
	{
	case appleID:
		if (theItem == 1)
		{
			SysBeep(3);
		}
		else
		{
			GetMenuItemText(appleMenu, theItem, name);
			OpenDeskAcc(name);
		}
		break;
	case fileID:
		switch (theItem)
		{
		case fmQuit:
			EndWindows();
			ExitToShell();
			break;
		}
		break;

	case animalsID:
		if (prevanimal != theItem)
		{
			ReplaceCtrls(num_menu(prevanimal));
			SetItemMark(animalsMenu, prevanimal, noMark);
			SetItemMark(animalsMenu, prevanimal = theItem, checkMark);
			GetMenuItemText(animalsMenu, theItem, name);
			tmp = num_menu(theItem);
			SetUpCtrls(tmp);
			MenuNumLinkCall(tmp);

		}
		switch (theItem)
		{
		}
		break;
	}
	HiliteMenu(0);*/
}

//void ScrollProc(ControlHandle theControl, short theCode)
//{
//	int	scrollAmt;
//	int oldCtl;
//
//	if (theCode == 0)
//		return;
//
//	switch (theCode)
//	{
//	case 22: /* formerly inPageUp: */
//		scrollAmt = -5;
//		break;
//	case 20: /* formerly inUpButton: */
//		scrollAmt = -1;
//		break;
//	case 23: /* formerly inPageDown: */
//		scrollAmt = 5;
//		break;
//	case 21: /* formerly inDownButton: */
//		scrollAmt = 1;
//		break;
//	}
//
//	oldCtl = GetControlValue(theControl);
//	SetControlValue(theControl, oldCtl + scrollAmt);
//
//}


//void DoWindowTouch(whichWindow, where)
//WindowPtr	whichWindow;
//Point		where;
//
//{
//	char		icnclick = 0;
//	short		icnnum;
//	short	loop = 1;
//	Rect	r = { 0, 0, 400, 400 };
//	int				cntlCode;
//
//	ControlHandle 	theControl;
//
//	SetPort(whichWindow);
//	GlobalToLocal(&where);
//
//	cntlCode = FindControl(where, whichWindow, &theControl);
//
//	if (cntlCode != 0)
//	{
//		if (theControl != gobut)
//		{
//			if (!running)
//			{
//				TrackControl(theControl, where, 0L);
//				ScrollProc(theControl, cntlCode);
//			}
//			else SysBeep(2);
//		}
//		else
//		{
//			running = !running;
//			if (running)
//			{
//				SetControlTitle(gobut, "\pStop");
//				timdel = GetControlValue(plch);
//				ReplaceCtrls(curcrit);
//
//				stime = 0;
//				while (loop<14)
//				{
//					graphvar[loop][0] = GetPopMap(loop);
//					loop++;
//				}
//				SetPort(awind);
//				EraseRect(&r);
//				MoveTo(12, 10);
//				LineTo(12, 150);
//				LineTo(292, 150);
//				while (loop<10)
//				{
//					MoveTo(12, 150 - (loop * 14));
//					LineTo(10, 150 - (loop * 14));
//					MoveTo((loop * 28) + 12, 150);
//					LineTo((loop * 28) + 12, 152);
//					loop++;
//				}
//			}
//			else
//				SetControlTitle(gobut, "\pStart");
//			SetControlValue(anich[0], GetPop(curcrit));
//		}
//
//	}
//
//
//
//	if (whichWindow == pwind)
//	{
//		if ((where.v>26) && (where.v<63))
//		{
//			if ((where.h>30) && (where.h<66))
//			{
//				icnnum = cApe;
//				icnclick = 1;
//			}
//			if ((where.h>102) && (where.h<138))
//			{
//				icnnum = cLiz;
//				icnclick = 1;
//			}
//			if ((where.h>164) && (where.h<200))
//			{
//				icnnum = cCat;
//				icnclick = 1;
//			}
//		}
//
//		if ((where.v>109) && (where.v<146))
//		{
//			if ((where.h>30) && (where.h<66))
//			{
//				icnnum = cIEB;
//				icnclick = 1;
//			}
//			if ((where.h>102) && (where.h<138))
//			{
//				icnnum = cFrog;
//				icnclick = 1;
//			}
//			if ((where.h>164) && (where.h<200))
//			{
//				icnnum = cBoP;
//				icnclick = 1;
//			}
//		}
//
//		if ((where.v>195) && (where.v<232))
//		{
//			if ((where.h>0) && (where.h<36))
//			{
//				icnnum = cSeEB;
//				icnclick = 1;
//			}
//			if ((where.h>65) && (where.h<101))
//			{
//				icnnum = cIns;
//				icnclick = 1;
//			}
//			if ((where.h>131) && (where.h<167))
//			{
//				icnnum = cMous;
//				icnclick = 1;
//			}
//			if ((where.h>198) && (where.h<234))
//			{
//				icnnum = cSeaB;
//				icnclick = 1;
//			}
//		}
//
//
//		if ((where.v>279) && (where.v<316))
//		{
//			if ((where.h>0) && (where.h<36))
//			{
//				icnnum = cBush;
//				icnclick = 1;
//			}
//			if ((where.h>65) && (where.h<101))
//			{
//				icnnum = cTree;
//				icnclick = 1;
//			}
//			if ((where.h>131) && (where.h<167))
//			{
//				icnnum = cGrass;
//				icnclick = 1;
//			}
//			if ((where.h>198) && (where.h<234))
//			{
//				icnnum = cFish;
//				icnclick = 1;
//			}
//		}
//
//		if ((icnclick) && (icnnum != curcrit))
//		{
//			if (!running)
//			{
//				ReplaceCtrls(curcrit);
//				SetUpCtrls(icnnum);
//				MenuNumLinkCall(icnnum);
//				NumtoMenu(icnnum);
//				LoadGraphin();
//				DrawGraphin();
//			}
//			else SysBeep(3);
//		}
//	}
//}


void Simulate(HDC dc)
{
	short	lp = 0;
	short	mx;
	long	tmpset;

	if (running)
	{

		//tmpset = TickCount() + (timdel * 6);
		//while ((tmpset>TickCount()) && Button()) {}
		docycle();
		LoadGraphin();
		DrawGraphin(dc);

		//SetPort(awind);

		//stime++;
		//PenPat(&qd.white);
		//mx = stime % 280;

		//if (mx<279)while (lp<14)
		//{
		//	MoveTo(13 + mx, 150 - graphvar[lp][mx + 1]);
		//	LineTo(12 + mx, 150 - graphvar[lp][mx]);
		//	graphvar[lp][mx] = GetPopMap(lp);
		//	lp++;
		//}

		//while (lp<14)
		//{
		//	graphvar[lp][mx] = GetPopMap(lp);
		//	lp++;
		//}

		//PenPat(&qd.black);
		//lp = 0;
		//if (mx>0)while (lp<14)
		//{
		//	MoveTo(11 + mx, 150 - graphvar[lp][mx - 1]);
		//	LineTo(12 + mx, 150 - graphvar[lp][mx]);
		//	lp++;
		//}
		//MoveTo(11 + mx, 150);
		//LineTo(13 + mx, 150);
	}
}

void UpdateContWind()
{
	//Rect	conts;


	//conts.top = 0;
	//conts.bottom = 320;
	//conts.left = 0;
	//conts.right = 238;
	//DrawPicture(phnd, &conts);
	//DrawControlIcns();

	//TextFont(3);
	//TextSize(9);

	//MoveTo(55, 325);
	//DrawString("\pSimulation Rate");

}


void UpdateGrapWind(HDC )
{

	//Rect	conts;


	//conts.top = 100;
	//conts.bottom = 175;
	//conts.left = 0;
	//conts.right = 300;
	//DrawPicture(phnd2, &conts);

	LoadGraphin();
	DrawGraphin();
	InitGraphin();
	DrawGraphin();
}




void UpdateAnimWind()
{
	//TextFont(3);
	//TextSize(9);
	//MoveTo(140, 13);
	//DrawString("\pPopulation");

	//MoveTo(145, 40);
	//DrawString("\pGrowth");

	//DrawAni(curcrit);
}

void RedrawWindow(HWND theWindow)
{
	if (theWindow == graphWindow)
	{
		UpdateGraphWindow();
	}
}

//void RedrawWindow(theWindow)
//WindowPtr	theWindow;
//
//{
//	if (theWindow == awind)
//	{
//		SetPort(awind);
//		BeginUpdate(awind);
//		DrawControls(awind);
//		UpdateAnimWind();
//		EndUpdate(awind);
//
//	}
//	if (theWindow == pwind)
//	{
//		SetPort(pwind);
//		BeginUpdate(pwind);
//		DrawControls(pwind);
//		UpdateContWind();
//		EndUpdate(pwind);
//
//	}
//	if (theWindow == gwind)
//	{
//		SetPort(gwind);
//		BeginUpdate(gwind);
//		UpdateGrapWind();
//		EndUpdate(gwind);
//
//	}
//}
//
void MainEvent(HDC graphDC)
{
	//EventRecord		myEvent;
	//WindowPtr		whichWindow = 0L;
	//int				windinfo;
	//char			tmp;

	//SystemTask();

	//if (GetNextEvent(everyEvent, &myEvent))
	//{
	//	switch (myEvent.what)
	//	{
	//	case mouseDown:

	//		tmp = 0;
	//		windinfo = FindWindow(myEvent.where, &whichWindow);
	//		switch (windinfo)
	//		{
	//		case inDesk:
	//			SysBeep(10);
	//			break;
	//		case inMenuBar:
	//			DoCommand(MenuSelect(myEvent.where));
	//			break;
	//		case inSysWindow:
	//			SystemClick(&myEvent, whichWindow);
	//			break;
	//		case inDrag:
	//			DragWindow(whichWindow, myEvent.where, &dragRect);
	//			RedrawWindow(whichWindow);
	//			break;

	//		case inContent:

	//			if (whichWindow != FrontWindow())
	//			{
	//				SelectWindow(whichWindow);
	//				RedrawWindow(whichWindow);
	//			}
	//			else
	//				DoWindowTouch(whichWindow, myEvent.where);

	//			break;
	//		}
	//		break;

	//	case keyDown:
	//	case autoKey:
	//	{
	//		register char	theChar;

	//		theChar = myEvent.message & charCodeMask;
	//		if ((myEvent.modifiers & cmdKey) != 0)
	//			DoCommand(MenuKey(theChar));
	//		break;
	//	}

	//	case updateEvt:
	//		RedrawWindow((WindowPtr)myEvent.message);
	//		break;

	//	case activateEvt:
	//		break;
	//	}
	//}
	Simulate(graphDC);
}

void InitToolBox()
{
	//short	lp = 200;
	//Rect	base, conts;

	//InitGraf((Ptr)&qd.thePort);
	//InitFonts();
	//InitWindows();
	//InitMenus();
	//FlushEvents(everyEvent, 0);
	//TEInit();
	//InitDialogs(0L);
	//InitCursor();

	init_system();

	//while (lp<215)
	//{
	//	icons[lp - 200] = GetCIcon(lp);
	//	lp++;
	//}

	//appleMenu = NewMenu(appleID, "\p\024");
	//AppendMenu(appleMenu, "\pAbout Ecosim�");
	//AppendMenu(appleMenu, "\p(-");
	//AppendResMenu(appleMenu, 'DRVR');
	//InsertMenu(appleMenu, 0);

	//fileMenu = NewMenu(fileID, "\pFile");
	//AppendMenu(fileMenu, "\pNew�/N;Open�/O;Close/W;Save/S;Save As�;(-;Preferences�;(-;Quit/Q");
	//InsertMenu(fileMenu, 0);

	//editMenu = NewMenu(editID, "\pEdit");
	//AppendMenu(editMenu, "\pUndo/Z;(-;Cut/X;Copy/C;Paste/V;Clear;(-;Select All/A");
	//InsertMenu(editMenu, 0);
	//DisableItem(editMenu, 0);

	//animalsMenu = NewMenu(animalsID, "\pSpecies");
	//AppendMenu(animalsMenu, "\pGrasses;Bushes;Trees;-);Seed-Eating Birds;Insect-Eating Birds;Sea Birds;Birds of Prey;-);Fish;Insects;Mice;Frogs;Lizards;-);Cats;Monkeys");
	//InsertMenu(animalsMenu, 0);



	//SetItemMark(animalsMenu, prevanimal = 1, checkMark);

	//DrawMenuBar();

	//base.top = 50;
	//base.bottom = 216;
	//base.left = 10;
	//base.right = 310;

	//awind = NewWindow(0L, &base, "\p", true, noGrowDocProc, (WindowPtr)-1L, false, 1);

	//SetPort(awind);


	//TextFont(3);
	//TextSize(9);
	//MoveTo(140, 13);
	//DrawString("\pPopulation");

	//MoveTo(145, 40);
	//DrawString("\pGrowth");


	//conts.top = 18;
	//conts.bottom = 28;
	//conts.left = 40;
	//conts.right = 290;

	//anich[0] = NewControl(awind, &conts, "\p", 1, 0, 0, 200, scrollBarProc, 0L);

	//conts.top = 45;
	//conts.bottom = 55;

	//anich[1] = NewControl(awind, &conts, "\p", 1, 0, 0, 40, scrollBarProc, 0L);


	//conts.left = 70;
	//conts.right = 160;

	//conts.top = 75;
	//conts.bottom = 85;

	//anich[2] = NewControl(awind, &conts, "\p", 1, 5, 0, 25, scrollBarProc, 0L);

	//conts.left = 200;
	//conts.right = 290;

	//anich[3] = NewControl(awind, &conts, "\p", 1, 5, 0, 25, scrollBarProc, 0L);


	//conts.left = 70;
	//conts.right = 160;

	//conts.top = 107;
	//conts.bottom = 117;

	//anich[4] = NewControl(awind, &conts, "\p", 1, 5, 0, 25, scrollBarProc, 0L);

	//conts.left = 200;
	//conts.right = 290;

	//anich[5] = NewControl(awind, &conts, "\p", 1, 5, 0, 25, scrollBarProc, 0L);

	//conts.top = 139;
	//conts.bottom = 149;

	//conts.left = 200;
	//conts.right = 290;

	//anich[6] = NewControl(awind, &conts, "\p", 1, 5, 0, 25, scrollBarProc, 0L);

	//base.top = 50;
	//base.bottom = base.top + 350;
	//base.left = 330;
	//base.right = base.left + 238;

	//pwind = NewWindow(0L, &base, "\p", true, noGrowDocProc, (WindowPtr)-1L, false, 1);

	//SetPort(pwind);

	//conts.top = 0;
	//conts.bottom = 320;
	//conts.left = 0;
	//conts.right = 238;
	//DrawPicture(phnd = (PicHandle)GetResource('PICT', 1000), &conts);
	//DrawControlIcns();

	//TextFont(3);
	//TextSize(9);

	//MoveTo(55, 325);
	//DrawString("\pSimulation Rate");

	//conts.left = 10;
	//conts.top = 330;
	//conts.bottom = 340;
	//conts.right = 168;

	//plch = NewControl(pwind, &conts, "\p", 1, 0, 0, 24, scrollBarProc, 0L);

	//conts.top = 325;
	//conts.bottom = 345;
	//conts.left = 178;
	//conts.right = 228;

	//gobut = NewControl(pwind, &conts, "\pStart", 1, 0, 0, 1, pushButProc, 0L);


	//SetUpCtrls(1);

	//base.top = 251;
	//base.bottom = 426;
	//base.left = 10;
	//base.right = 310;


	//gwind = NewWindow(0L, &base, "\p", true, noGrowDocProc, (WindowPtr)-1L, false, 1);

	//SetPort(gwind);

	//conts.top = 100;
	//conts.bottom = 175;
	//conts.left = 0;
	//conts.right = 300;
	//DrawPicture(phnd2 = (PicHandle)GetResource('PICT', 1001), &conts);

	//InitGraphin();
	//DrawGraphin();

	//SetUpCtrls(0);
	//MenuNumLinkCall(0);
	//NumtoMenu(0);

}

