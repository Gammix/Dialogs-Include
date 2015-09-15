/*
	Dialogs Include (dialogs.inc) - Version 2.0.1
	* The one and only include which adds up new dialog styles to SAMP dialogs GUI.
	* Current new dialog styles:
 		- DIALOG_STYLE_PREVMODEL
  	 	- DIALOG_STYLE_PREVMODEL_LIST

 	Author: (creator)
	* Gammix

	Contributors:
	* Y_Less - Dialog_CountPages macro

	(c) Copyright 2015
  	* This file is provided as is (no warranties).
*/

/*
FUNCTIONS:
native ShowPlayerDialog(playerid, dialogid, style, caption[], info[], button1[], button2[] = "", infosize = sizeof(info));

CALLBACKS:
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
*/

#define DIALOG_STYLE_PREVMODEL 			(6)
#define DIALOG_STYLE_PREVMODEL_LIST 	(DIALOG_STYLE_PREVMODEL + 1)

#define DIALOG_SELECTION_COLOR 			(0xFF0000BB)
#define DIALOG_MODELNONSELECTION_COLOR 	(169090660)
#define DIALOG_BARNONSELECTION_COLOR 	(169093220)

#define DIALOG_MAXINFO_SIZE 			(1024)

#define DIALOG_STYLE1_ITEMSPERPAGE 		(6 * 4)
#define DIALOG_STYLE2_ITEMSPERPAGE 		(5)

#define Dialog_CountPages(%0,%1) 		(((%0)-1)/(%1)+1)

#pragma dynamic 						(100000)

enum e_DIALOG_BASE {
	Text:   	e_txtHeaderBox,
	Text:   	e_txtContentBox[7],
	Text:   	e_txtScrollUp[2],
	Text:   	e_txtScrollDown[2],
	Text:   	e_txtButtonLeft[5],
	Text:   	e_txtButtonRight[5],
	Text:       e_txtButtonCenter[5]
};

enum e_PLAYER_DIALOG_HUDS {
	PlayerText: e_txtPlayerDialogTitle,
	PlayerText: e_txtPlayerDialogButtonLeft,
	PlayerText: e_txtPlayerDialogButtonRight,
	PlayerText: e_txtPlayerDialogButtonCenter
};

stock static
				g_DialogBase[e_DIALOG_BASE],
	Text:   	g_txtDialogModels[DIALOG_STYLE1_ITEMSPERPAGE],
	PlayerText:	g_txtPlayerDialogLabels[MAX_PLAYERS][DIALOG_STYLE1_ITEMSPERPAGE],
	Text:   	g_txtDialogModels_List[DIALOG_STYLE2_ITEMSPERPAGE],
	PlayerText:	g_txtPlayerDialogLabels_List[MAX_PLAYERS][DIALOG_STYLE2_ITEMSPERPAGE],
	Text:   	g_txtDialogBars_List[DIALOG_STYLE2_ITEMSPERPAGE],
	            g_PlayerDialogHUDS[MAX_PLAYERS][e_PLAYER_DIALOG_HUDS]
;

stock static Dialog_TDCreate(varname[], &Text:var, Float:posX, Float:posY, string[], bgcolor, font, Float:lettersizeX, Float:lettersizeY, textcolor, allign = 0, outline = 1, proportional = 1, shadow = 1, usebox = 0, boxcolor = 0, Float:textsizeX = -1.0, Float:textsizeY = -1.0, model = 0, Float:rotX = 0.0, Float:rotY = 0.0, Float:rotZ = 0.0, Float:zoom = 1.0, selectable = 0) {
    var = TextDrawCreate(posX, posY, string);
    SetSVarInt(varname, _:var);
    
	TextDrawBackgroundColor(var, bgcolor);
	TextDrawFont(var, font);
	TextDrawLetterSize(var, lettersizeX, lettersizeY);
	TextDrawColor(var, textcolor);
	TextDrawAlignment(var, allign);
	TextDrawSetOutline(var, outline);
	TextDrawSetProportional(var, proportional);
	TextDrawSetShadow(var, shadow);
	TextDrawUseBox(var, usebox);
	TextDrawSetSelectable(var, selectable);
	if(usebox) {
		TextDrawBoxColor(var, boxcolor);
 	}
	if(textsizeX != -1.0 || textsizeY != -1.0) {
		TextDrawTextSize(var, textsizeX, textsizeY);
 	}
	if(font == 5) {
		TextDrawSetPreviewModel(var, model);
		TextDrawSetPreviewRot(var, rotX, rotY, rotZ, zoom);
	}
}

stock static Dialog_PTDCreate(&PlayerText:var, playerid, Float:posX, Float:posY, string[], bgcolor, font, Float:lettersizeX, Float:lettersizeY, textcolor, allign = 0, outline = 1, proportional = 1, shadow = 1, usebox = 0, boxcolor = 0, Float:textsizeX = -1.0, Float:textsizeY = -1.0, model = 0, Float:rotX = 0.0, Float:rotY = 0.0, Float:rotZ = 0.0, Float:zoom = 1.0, selectable = 0) {
	var = CreatePlayerTextDraw(playerid, posX, posY, string);
	PlayerTextDrawBackgroundColor(playerid, var, bgcolor);
	PlayerTextDrawFont(playerid, var, font);
	PlayerTextDrawLetterSize(playerid, var, lettersizeX, lettersizeY);
	PlayerTextDrawColor(playerid, var, textcolor);
	PlayerTextDrawAlignment(playerid, var, allign);
	PlayerTextDrawSetOutline(playerid, var, outline);
	PlayerTextDrawSetProportional(playerid, var, proportional);
	PlayerTextDrawSetShadow(playerid, var, shadow);
	PlayerTextDrawUseBox(playerid, var, usebox);
	PlayerTextDrawSetSelectable(playerid, var, selectable);
	if(usebox) {
		PlayerTextDrawBoxColor(playerid, var, boxcolor);
	}
	if(textsizeX != -1.0 || textsizeY != -1.0) {
		PlayerTextDrawTextSize(playerid, var, textsizeX, textsizeY);
	}
	if(font == 5) {
		PlayerTextDrawSetPreviewModel(playerid, var, model);
		PlayerTextDrawSetPreviewRot(playerid, var, rotX, rotY, rotZ, zoom);
	}
}

#if defined FILTERSCRIPT
	public OnFilterScriptInit() {
#else
	public OnGameModeInit() {
#endif

	SetSVarInt("Dialog_Platforms", GetSVarInt("Dialog_Platforms") + 1);

	if (GetSVarInt("Dialog_Platforms") <= 1) {
	    Dialog_TDCreate("e_txtHeaderBox", g_DialogBase[e_txtHeaderBox], 173.000000, 122.000000, "_", 50, 1, 0.000000, 0.599999, -1, 0, 0, 1, 1, 1, 200, 462.000000, 19.000000);

		Dialog_TDCreate("e_txtContentBox_0", g_DialogBase[e_txtContentBox][0], 173.000000, 131.000000, "_", 50, 1, 0.000000, 21.599998, -1, 0, 0, 1, 1, 1, 150, 462.000000, 19.000000);
		Dialog_TDCreate("e_txtContentBox_1", g_DialogBase[e_txtContentBox][1], 177.000000, 135.000000, "_", 50, 1, 0.000000, 18.299997, -1, 0, 0, 1, 1, 1, 100, 458.000000, 19.000000);
		Dialog_TDCreate("e_txtContentBox_2", g_DialogBase[e_txtContentBox][2], 177.000000, 134.000000, "_", 50, 1, 0.000000, 18.499998, -1, 0, 0, 1, 1, 1, -106, 173.000000, 19.000000);
		Dialog_TDCreate("e_txtContentBox_3", g_DialogBase[e_txtContentBox][3], 454.000000, 135.000000, "_", 50, 1, 0.000000, 18.299997, -1, 0, 0, 1, 1, 1, -106, 452.000000, 19.000000);
		Dialog_TDCreate("e_txtContentBox_4", g_DialogBase[e_txtContentBox][4], 461.000000, 135.000000, "_", 50, 1, 0.000000, 18.299997, -1, 0, 0, 1, 1, 1, -106, 459.000000, 19.000000);
		Dialog_TDCreate("e_txtContentBox_5", g_DialogBase[e_txtContentBox][5], 462.000000, 134.000000, "_", 50, 1, 0.000000, -0.300001, -1, 0, 0, 1, 1, 1, -106, 174.000000, 19.000000);
		Dialog_TDCreate("e_txtContentBox_6", g_DialogBase[e_txtContentBox][6], 462.000000, 304.000000, "_", 50, 1, 0.000000, -0.400001, -1, 0, 0, 1, 1, 1, -106, 173.000000, 19.000000);

		Dialog_TDCreate("e_txtScrollUp_0", g_DialogBase[e_txtScrollUp][0], 453.000000, 133.000000, "LD_POOL:ball", 50, 4, 0.500000, 1.000000, -106, 0, 0, 1, 1, 1, 255, 7.000000, 9.00000, .selectable = 1);
		Dialog_TDCreate("e_txtScrollUp_1", g_DialogBase[e_txtScrollUp][1], 454.000000, 134.000000, "LD_BEAT:up", 255, 4, 0.500000, 1.000000, 255, 0, 0, 1, 1, 1, 255, 5.000000, 6.000000);

		Dialog_TDCreate("e_txtScrollDown_0", g_DialogBase[e_txtScrollDown][0], 453.000000, 293.000000, "LD_POOL:ball", 50, 4, 0.500000, 1.000000, -106, 0, 0, 1, 1, 1, 255, 7.000000, 9.00000, .selectable = 1);
		Dialog_TDCreate("e_txtScrollDown_1", g_DialogBase[e_txtScrollDown][1], 454.000000, 295.000000, "LD_BEAT:down", 255, 4, 0.500000, 1.000000, 255, 0, 0, 1, 1, 1, 255, 5.000000, 6.000000);

		Dialog_TDCreate("e_txtButtonLeft_0", g_DialogBase[e_txtButtonLeft][0], 302.000000, 310.000000, "_", 50, 1, 0.000000, -0.400001, -1, 0, 0, 1, 1, 1, -106, 253.000000, 19.000000);
		Dialog_TDCreate("e_txtButtonLeft_1", g_DialogBase[e_txtButtonLeft][1], 302.000000, 324.000000, "_", 50, 1, 0.000000, -0.400001, -1, 0, 0, 1, 1, 1, -106, 253.000000, 19.000000);
		Dialog_TDCreate("e_txtButtonLeft_2", g_DialogBase[e_txtButtonLeft][2], 253.000000, 304.000000, "(", 0, 1, 0.200000, 2.000000, -106, 0, 0, 1, 1);
		Dialog_TDCreate("e_txtButtonLeft_3", g_DialogBase[e_txtButtonLeft][3], 299.000000, 304.000000, ")", 0, 1, 0.200000, 2.000000, -106, 0, 0, 1, 1);
		Dialog_TDCreate("e_txtButtonLeft_4", g_DialogBase[e_txtButtonLeft][4], 254.000000, 309.000000, "ld_plan:tvbase", 50, 4, 0.000000, 0.899998, 255, 0, 0, 1, 1, 1, 255, 46.000000, 13.000000, .selectable = 1);

		Dialog_TDCreate("e_txtButtonRight_0", g_DialogBase[e_txtButtonRight][0], 372.000000, 310.000000, "_", 50, 1, 0.000000, -0.400001, -1, 0, 0, 1, 1, 1, -106, 323.000000, 19.000000);
		Dialog_TDCreate("e_txtButtonRight_1", g_DialogBase[e_txtButtonRight][1], 372.000000, 324.000000, "_", 50, 1, 0.000000, -0.400001, -1, 0, 0, 1, 1, 1, -106, 323.000000, 19.000000);
		Dialog_TDCreate("e_txtButtonRight_2", g_DialogBase[e_txtButtonRight][2], 323.000000, 304.000000, "(", 0, 1, 0.210000, 2.000000, -106, 0, 0, 1, 1);
		Dialog_TDCreate("e_txtButtonRight_3", g_DialogBase[e_txtButtonRight][3], 369.000000, 304.000000, ")", 0, 1, 0.230000, 1.999999, -106, 0, 0, 1, 1);
		Dialog_TDCreate("e_txtButtonRight_4", g_DialogBase[e_txtButtonRight][4], 324.000000, 309.000000, "ld_plan:tvbase", 50, 4, 0.000000, 0.899998, 255, 0, 0, 1, 1, 1, 255, 46.000000, 13.000000, .selectable = 1);

		Dialog_TDCreate("e_txtButtonCenter_0", g_DialogBase[e_txtButtonCenter][0], 342.000000, 310.000000, "_", 50, 1, 0.000000, -0.400001, -1, 0, 0, 1, 1, 1, -106, 293.000000, 19.000000);
		Dialog_TDCreate("e_txtButtonCenter_1", g_DialogBase[e_txtButtonCenter][1], 342.000000, 324.000000, "_", 50, 1, 0.000000, -0.400001, -1, 0, 0, 1, 1, 1, -106, 293.000000, 19.000000);
		Dialog_TDCreate("e_txtButtonCenter_2", g_DialogBase[e_txtButtonCenter][2], 293.000000, 304.000000, "(", 0, 1, 0.200000, 2.000000, -106, 0, 0, 1, 1);
		Dialog_TDCreate("e_txtButtonCenter_3", g_DialogBase[e_txtButtonCenter][3], 339.000000, 304.000000, ")", 0, 1, 0.219999, 2.000000, -106, 0, 0, 1, 1);
		Dialog_TDCreate("e_txtButtonCenter_4", g_DialogBase[e_txtButtonCenter][4], 294.000000, 309.000000, "ld_plan:tvbase", 50, 4, 0.000000, 0.899998, 255, 0, 0, 1, 1, 1, 255, 46.000000, 13.000000, .selectable = 1);

		new
			t_iCount = 0,
		    Float:t_fBase[2] = {179.000000, 134.000000},
		    t_sVarname[40]
		;
		for (new i = 0; i < DIALOG_STYLE1_ITEMSPERPAGE; i++) {
			format(t_sVarname, sizeof(t_sVarname), "g_txtDialogModels_%i", i);
			Dialog_TDCreate(t_sVarname, g_txtDialogModels[i], t_fBase[0], t_fBase[1], "_", DIALOG_MODELNONSELECTION_COLOR, 5, 0.129998, 0.799998, -1, 0, 0, 1, 1, 1, 0, 44.000000, 41.000000, .selectable = 1);

	        t_fBase[0] += 45.000000;
	        t_iCount += 1;

	        if (t_iCount == 6) {
	            t_fBase[0] = 179.000000;
	            t_fBase[1] += 42.000000;

	            t_iCount = 0;
			}
		}

		for (new i = 0; i < DIALOG_STYLE2_ITEMSPERPAGE; i++) {
			format(t_sVarname, sizeof(t_sVarname), "g_txtDialogModels_List_%i", i);
			Dialog_TDCreate(t_sVarname, g_txtDialogModels_List[i], 178.000000, (134.000000 + (33.0 * i)), "_", DIALOG_MODELNONSELECTION_COLOR, 5, 0.129997, 0.799997, -1, 0, 0, 1, 1, 1, 0, 34.000000, 30.000000);

			format(t_sVarname, sizeof(t_sVarname), "g_txtDialogBars_List_%i", i);
			Dialog_TDCreate(t_sVarname, g_txtDialogBars_List[i], 177.000000, (134.000000 + (33.0 * i)), "ld_plan:tvbase", 50, 4, 0.129997, 0.799997, DIALOG_BARNONSELECTION_COLOR, 0, 0, 1, 1, 1, 0, 274.000000, 32.000000, .selectable = 1);
		}
	}
	else {
		g_DialogBase[e_txtHeaderBox] = Text:GetSVarInt("e_txtHeaderBox");

		g_DialogBase[e_txtContentBox][0] = Text:GetSVarInt("e_txtContentBox_0");
		g_DialogBase[e_txtContentBox][1] = Text:GetSVarInt("e_txtContentBox_1");
		g_DialogBase[e_txtContentBox][2] = Text:GetSVarInt("e_txtContentBox_2");
		g_DialogBase[e_txtContentBox][3] = Text:GetSVarInt("e_txtContentBox_3");
		g_DialogBase[e_txtContentBox][4] = Text:GetSVarInt("e_txtContentBox_4");
		g_DialogBase[e_txtContentBox][5] = Text:GetSVarInt("e_txtContentBox_5");
		g_DialogBase[e_txtContentBox][6] = Text:GetSVarInt("e_txtContentBox_6");

		g_DialogBase[e_txtScrollUp][0] = Text:GetSVarInt("e_txtScrollUp_0");
		g_DialogBase[e_txtScrollUp][1] = Text:GetSVarInt("e_txtScrollUp_1");

		g_DialogBase[e_txtScrollDown][0] = Text:GetSVarInt("e_txtScrollDown_0");
		g_DialogBase[e_txtScrollDown][1] = Text:GetSVarInt("e_txtScrollDown_1");

		g_DialogBase[e_txtButtonLeft][0] = Text:GetSVarInt("e_txtButtonLeft_0");
		g_DialogBase[e_txtButtonLeft][1] = Text:GetSVarInt("e_txtButtonLeft_1");
		g_DialogBase[e_txtButtonLeft][2] = Text:GetSVarInt("e_txtButtonLeft_2");
		g_DialogBase[e_txtButtonLeft][3] = Text:GetSVarInt("e_txtButtonLeft_3");
		g_DialogBase[e_txtButtonLeft][4] = Text:GetSVarInt("e_txtButtonLeft_4");

		g_DialogBase[e_txtButtonRight][0] = Text:GetSVarInt("e_txtButtonRight_0");
		g_DialogBase[e_txtButtonRight][1] = Text:GetSVarInt("e_txtButtonRight_1");
		g_DialogBase[e_txtButtonRight][2] = Text:GetSVarInt("e_txtButtonRight_2");
		g_DialogBase[e_txtButtonRight][3] = Text:GetSVarInt("e_txtButtonRight_3");
		g_DialogBase[e_txtButtonRight][4] = Text:GetSVarInt("e_txtButtonRight_4");

		g_DialogBase[e_txtButtonCenter][0] = Text:GetSVarInt("e_txtButtonCenter_0");
		g_DialogBase[e_txtButtonCenter][1] = Text:GetSVarInt("e_txtButtonCenter_1");
		g_DialogBase[e_txtButtonCenter][2] = Text:GetSVarInt("e_txtButtonCenter_2");
		g_DialogBase[e_txtButtonCenter][3] = Text:GetSVarInt("e_txtButtonCenter_3");
		g_DialogBase[e_txtButtonCenter][4] = Text:GetSVarInt("e_txtButtonCenter_4");
		
		new
		    t_sVarname[40]
		;
		for (new i = 0; i < DIALOG_STYLE1_ITEMSPERPAGE; i++) {
			format(t_sVarname, sizeof(t_sVarname), "g_txtDialogModels_%i", i);
			g_txtDialogModels[i] = Text:GetSVarInt(t_sVarname);
		}

		for (new i = 0; i < DIALOG_STYLE2_ITEMSPERPAGE; i++) {
			format(t_sVarname, sizeof(t_sVarname), "g_txtDialogModels_List_%i", i);
			g_txtDialogModels_List[i] = Text:GetSVarInt(t_sVarname);
			
			format(t_sVarname, sizeof(t_sVarname), "g_txtDialogBars_List_%i", i);
			g_txtDialogBars_List[i] = Text:GetSVarInt(t_sVarname);
		}
	}

#if defined FILTERSCRIPT
	    #if defined Dialog_OnFilterScriptInit
			return Dialog_OnFilterScriptInit();
		#else
			return 1;
		#endif
	}
	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif
	#define OnFilterScriptInit Dialog_OnFilterScriptInit
	#if defined Dialog_OnFilterScriptInit
		forward Dialog_OnFilterScriptInit();
	#endif
#else
    #if defined Dialog_OnGameModeInit
			return Dialog_OnGameModeInit();
		#else
			return 1;
		#endif
	}
	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif
	#define OnGameModeInit Dialog_OnGameModeInit
	#if defined Dialog_OnGameModeInit
		forward Dialog_OnGameModeInit();
	#endif
#endif

#if defined FILTERSCRIPT
	public OnFilterScriptExit() {
#else
	public OnGameModeExit() {
#endif

	SetSVarInt("Dialog_Platforms", GetSVarInt("Dialog_Platforms") - 1);
	if (GetSVarInt("Dialog_Platforms") <= 0) {
		DeleteSVar("Dialog_Platforms");

		TextDrawDestroy(g_DialogBase[e_txtHeaderBox]);
		DeleteSVar("e_txtHeaderBox");

		TextDrawDestroy(g_DialogBase[e_txtContentBox][0]);
		TextDrawDestroy(g_DialogBase[e_txtContentBox][1]);
		TextDrawDestroy(g_DialogBase[e_txtContentBox][2]);
		TextDrawDestroy(g_DialogBase[e_txtContentBox][3]);
		TextDrawDestroy(g_DialogBase[e_txtContentBox][4]);
		TextDrawDestroy(g_DialogBase[e_txtContentBox][5]);
		TextDrawDestroy(g_DialogBase[e_txtContentBox][6]);
		DeleteSVar("e_txtContentBox_0");
		DeleteSVar("e_txtContentBox_1");
		DeleteSVar("e_txtContentBox_2");
		DeleteSVar("e_txtContentBox_3");
		DeleteSVar("e_txtContentBox_4");
		DeleteSVar("e_txtContentBox_5");
		DeleteSVar("e_txtContentBox_6");

		TextDrawDestroy(g_DialogBase[e_txtScrollUp][0]);
		TextDrawDestroy(g_DialogBase[e_txtScrollUp][1]);
		DeleteSVar("e_txtScrollUp_0");
		DeleteSVar("e_txtScrollUp_1");

		TextDrawDestroy(g_DialogBase[e_txtScrollDown][0]);
		TextDrawDestroy(g_DialogBase[e_txtScrollDown][1]);
		DeleteSVar("e_txtScrollDown_0");
		DeleteSVar("e_txtScrollDown_1");

		TextDrawDestroy(g_DialogBase[e_txtButtonLeft][0]);
		TextDrawDestroy(g_DialogBase[e_txtButtonLeft][1]);
		TextDrawDestroy(g_DialogBase[e_txtButtonLeft][2]);
		TextDrawDestroy(g_DialogBase[e_txtButtonLeft][3]);
		TextDrawDestroy(g_DialogBase[e_txtButtonLeft][4]);
		DeleteSVar("e_txtButtonLeft_0");
		DeleteSVar("e_txtButtonLeft_1");
		DeleteSVar("e_txtButtonLeft_2");
		DeleteSVar("e_txtButtonLeft_3");
		DeleteSVar("e_txtButtonLeft_4");

		TextDrawDestroy(g_DialogBase[e_txtButtonRight][0]);
		TextDrawDestroy(g_DialogBase[e_txtButtonRight][1]);
		TextDrawDestroy(g_DialogBase[e_txtButtonRight][2]);
		TextDrawDestroy(g_DialogBase[e_txtButtonRight][3]);
		TextDrawDestroy(g_DialogBase[e_txtButtonRight][4]);
		DeleteSVar("e_txtButtonRight_0");
		DeleteSVar("e_txtButtonRight_1");
		DeleteSVar("e_txtButtonRight_2");
		DeleteSVar("e_txtButtonRight_3");
		DeleteSVar("e_txtButtonRight_4");

		TextDrawDestroy(g_DialogBase[e_txtButtonCenter][0]);
		TextDrawDestroy(g_DialogBase[e_txtButtonCenter][1]);
		TextDrawDestroy(g_DialogBase[e_txtButtonCenter][2]);
		TextDrawDestroy(g_DialogBase[e_txtButtonCenter][3]);
		TextDrawDestroy(g_DialogBase[e_txtButtonCenter][4]);
		DeleteSVar("e_txtButtonCenter_0");
		DeleteSVar("e_txtButtonCenter_1");
		DeleteSVar("e_txtButtonCenter_2");
		DeleteSVar("e_txtButtonCenter_3");
		DeleteSVar("e_txtButtonCenter_4");
		
		new
		    t_sVarname[40]
		;
		for (new i = 0; i < DIALOG_STYLE1_ITEMSPERPAGE; i++) {
			TextDrawDestroy(g_txtDialogModels[i]);
			format(t_sVarname, sizeof(t_sVarname), "g_txtDialogModels_%i", i);
			DeleteSVar(t_sVarname);
		}

		for (new i = 0; i < DIALOG_STYLE2_ITEMSPERPAGE; i++) {
			TextDrawDestroy(g_txtDialogModels_List[i]);
			TextDrawDestroy(g_txtDialogBars_List[i]);
			format(t_sVarname, sizeof(t_sVarname), "g_txtDialogModels_List_%i", i);
			DeleteSVar(t_sVarname);
			format(t_sVarname, sizeof(t_sVarname), "g_txtDialogBars_List_%i", i);
			DeleteSVar(t_sVarname);
		}
	}
	
#if defined FILTERSCRIPT
		#if defined Dialog_OnFilterScriptExit
			return Dialog_OnFilterScriptExit();
		#else
			return 1;
		#endif
	}
	#if defined _ALS_OnFilterScriptExit
		#undef OnFilterScriptExit
	#else
		#define _ALS_OnFilterScriptExit
	#endif
	#define OnFilterScriptExit Dialog_OnFilterScriptExit
	#if defined Dialog_OnFilterScriptExit
		forward Dialog_OnFilterScriptExit();
	#endif
#else
    #if defined Dialog_OnGameModeExit
			return Dialog_OnGameModeExit();
		#else
			return 1;
		#endif
	}
	#if defined _ALS_OnGameModeExit
		#undef OnGameModeExit
	#else
		#define _ALS_OnGameModeExit
	#endif
	#define OnGameModeExit Dialog_OnGameModeExit
	#if defined Dialog_OnGameModeExit
		forward Dialog_OnGameModeExit();
	#endif
#endif

stock Dialog_ShowBase(playerid, bool:dualbuttons = true) {
    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtHeaderBox]);

    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtContentBox][0]);
    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtContentBox][1]);
    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtContentBox][2]);
    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtContentBox][3]);
    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtContentBox][4]);
    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtContentBox][5]);
    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtContentBox][6]);

    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtScrollUp][0]);
    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtScrollUp][1]);

    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtScrollDown][0]);
    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtScrollDown][1]);

	if (dualbuttons) {
	    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtButtonLeft][0]);
	    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtButtonLeft][1]);
	    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtButtonLeft][2]);
	    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtButtonLeft][3]);
	    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtButtonLeft][4]);

	    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtButtonRight][0]);
	    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtButtonRight][1]);
	    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtButtonRight][2]);
	    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtButtonRight][3]);
	    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtButtonRight][4]);

	    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonCenter][0]);
	    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonCenter][1]);
	    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonCenter][2]);
	    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonCenter][3]);
	    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonCenter][4]);
	}
	else {
	    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonLeft][0]);
	    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonLeft][1]);
	    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonLeft][2]);
	    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonLeft][3]);
	    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonLeft][4]);

	    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonRight][0]);
	    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonRight][1]);
	    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonRight][2]);
	    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonRight][3]);
	    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonRight][4]);

	    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtButtonCenter][0]);
	    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtButtonCenter][1]);
	    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtButtonCenter][2]);
	    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtButtonCenter][3]);
	    TextDrawShowForPlayer(playerid, g_DialogBase[e_txtButtonCenter][4]);
	}
}

stock Dialog_HideBase(playerid) {
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtHeaderBox]);

    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtContentBox][0]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtContentBox][1]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtContentBox][2]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtContentBox][3]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtContentBox][4]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtContentBox][5]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtContentBox][6]);

    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtScrollUp][0]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtScrollUp][1]);

    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtScrollDown][0]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtScrollDown][1]);

    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonLeft][0]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonLeft][1]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonLeft][2]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonLeft][3]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonLeft][4]);

    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonRight][0]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonRight][1]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonRight][2]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonRight][3]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonRight][4]);

    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonCenter][0]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonCenter][1]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonCenter][2]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonCenter][3]);
    TextDrawHideForPlayer(playerid, g_DialogBase[e_txtButtonCenter][4]);
}

stock Dialog_ShowHUDS(playerid, title[], button1[], button2[]) {
	Dialog_PTDCreate(g_PlayerDialogHUDS[playerid][e_txtPlayerDialogTitle], playerid, 173.000000, 121.000000, title, 50, 1, 0.129998, 0.799998, -36, 0, 0, 1, 1, 0);
	PlayerTextDrawShow(playerid, g_PlayerDialogHUDS[playerid][e_txtPlayerDialogTitle]);

	if (button2[0]) {
		Dialog_PTDCreate(g_PlayerDialogHUDS[playerid][e_txtPlayerDialogButtonLeft], playerid, 278.000000, 311.000000, button1, 50, 1, 0.129998, 0.799998, -36, 2, 0, 1, 1, 0);
		PlayerTextDrawShow(playerid, g_PlayerDialogHUDS[playerid][e_txtPlayerDialogButtonLeft]);

		Dialog_PTDCreate(g_PlayerDialogHUDS[playerid][e_txtPlayerDialogButtonRight], playerid, 348.000000, 311.000000, button2, 50, 1, 0.140000, 0.899999, -36, 2, 0, 1, 1, 0);
		PlayerTextDrawShow(playerid, g_PlayerDialogHUDS[playerid][e_txtPlayerDialogButtonRight]);

		SetPVarInt(playerid, "Dialog_Buttons", 2);
	}
	else {
		Dialog_PTDCreate(g_PlayerDialogHUDS[playerid][e_txtPlayerDialogButtonCenter], playerid, 317.000000, 311.000000, button1, 50, 1, 0.140000, 0.899999, -36, 2, 0, 1, 1, 0);
		PlayerTextDrawShow(playerid, g_PlayerDialogHUDS[playerid][e_txtPlayerDialogButtonCenter]);

		SetPVarInt(playerid, "Dialog_Buttons", 1);
	}
}

stock Dialog_HideHUDS(playerid) {
	PlayerTextDrawDestroy(playerid, g_PlayerDialogHUDS[playerid][e_txtPlayerDialogTitle]);

	if (GetPVarInt(playerid, "Dialog_Buttons") == 2) {
		PlayerTextDrawDestroy(playerid, g_PlayerDialogHUDS[playerid][e_txtPlayerDialogButtonLeft]);
		PlayerTextDrawDestroy(playerid, g_PlayerDialogHUDS[playerid][e_txtPlayerDialogButtonRight]);
	}
	else {
		PlayerTextDrawDestroy(playerid, g_PlayerDialogHUDS[playerid][e_txtPlayerDialogButtonCenter]);
	}

	DeletePVar(playerid, "Dialog_Buttons");
}

stock static Dialog_Split(const src[], dest[][], delimeter = ' ', size = sizeof(dest[])) {
	new
	    k,
	    l
	;
	for (new i = 0, j = strlen(src); i <= j; i++) {
		if (src[i] == delimeter || i == j) {
			new
			    m = strmid(dest[k], src, l, i, size)
			;

   			dest[k][m] = 0;

   			l = i + 1;
   			k += 1;
		}
	}

	return k;
}

stock static Dialog_ShowListitem(playerid, index, model, label[], bool:selected = false, Float:mx = 0.0, Float:my = 0.0, Float:mz = 0.0, Float:mzoom = 1.0) {
	if (GetPVarInt(playerid, "Dialog_Style") == DIALOG_STYLE_PREVMODEL) {
	    if (model >= 0) {
	  		if (selected) {
				TextDrawBackgroundColor(g_txtDialogModels[index], DIALOG_SELECTION_COLOR);
	   		}
	    	else {
	     		TextDrawBackgroundColor(g_txtDialogModels[index], DIALOG_MODELNONSELECTION_COLOR);
		    }
			TextDrawSetPreviewModel(g_txtDialogModels[index], model);
	  		TextDrawSetPreviewRot(g_txtDialogModels[index], mx, my, mz, mzoom);
	    	TextDrawShowForPlayer(playerid, g_txtDialogModels[index]);

			if (label[0]) {
				new
					Float:t_fPos[2] = {181.000000, 135.000000},
				    t_iCount = 0
				;
				for (new i = 0; i < index; i++) {
				    t_fPos[0] += 45.000000;
					t_iCount += 1;

					if (t_iCount == 6) {
		   				t_fPos[0] = 181.000000;
				     	t_fPos[1] += 42.000000;
				    }
				}

				Dialog_PTDCreate(g_txtPlayerDialogLabels[playerid][index], playerid, t_fPos[0], t_fPos[1], label, 50, 1, 0.140000, 0.899999, -36, 0, 1, 1, 2, 0);
				PlayerTextDrawShow(playerid, g_txtPlayerDialogLabels[playerid][index]);
	  		}
		}
	}
	else if (GetPVarInt(playerid, "Dialog_Style") == DIALOG_STYLE_PREVMODEL_LIST) {
	    if (model >= 0) {
			TextDrawBackgroundColor(g_txtDialogModels_List[index], DIALOG_MODELNONSELECTION_COLOR);
			TextDrawSetPreviewModel(g_txtDialogModels_List[index], model);
	  		TextDrawSetPreviewRot(g_txtDialogModels_List[index], mx, my, mz, mzoom);
	    	TextDrawShowForPlayer(playerid, g_txtDialogModels_List[index]);

	  		if (selected) {
				TextDrawColor(g_txtDialogBars_List[index], DIALOG_SELECTION_COLOR);
	   		}
	    	else {
	     		TextDrawColor(g_txtDialogBars_List[index], DIALOG_BARNONSELECTION_COLOR);
		    }
	    	TextDrawShowForPlayer(playerid, g_txtDialogBars_List[index]);

			if (label[0]) {
				Dialog_PTDCreate(g_txtPlayerDialogLabels_List[playerid][index], playerid, 215.000000, (135.000000 + (index * 33)), label, 50, 1, 0.099999, 0.599997, -36, 0, 1, 1, 2, 0);
				PlayerTextDrawShow(playerid, g_txtPlayerDialogLabels_List[playerid][index]);
	  		}
		}
	}
}

stock Dialog_ShowList(playerid, info[], page, selected) {
	new
	    t_sSplit[DIALOG_MAXINFO_SIZE][30],
	    t_iSplitSize = Dialog_Split(info, t_sSplit, '\n'),
	    t_iSplitItems
	;
    t_iSplitItems = floatround(t_iSplitSize / 2);
    if ((t_iSplitItems % 2) > 0) {
        t_iSplitItems -= 1;
	}
	if (page >= Dialog_CountPages(t_iSplitItems, ((GetPVarInt(playerid, "Dialog_Style") == DIALOG_STYLE_PREVMODEL) ? DIALOG_STYLE1_ITEMSPERPAGE : DIALOG_STYLE2_ITEMSPERPAGE)) || page < 0) {
		return false;
	}

	Dialog_HideList(playerid);

  	new
		t_iIndex,
		i,
		d
	;
	if (GetPVarInt(playerid, "Dialog_Style") == DIALOG_STYLE_PREVMODEL) {
        d = DIALOG_STYLE1_ITEMSPERPAGE * 2;
        i = 2 + (page)*d;
	}
	else {
        d = DIALOG_STYLE2_ITEMSPERPAGE * 2;
        i = 2 + (page)*d;
	}
	for (; i <= t_iSplitSize; i += 2) {
	    if (t_iIndex < ((GetPVarInt(playerid, "Dialog_Style") == DIALOG_STYLE_PREVMODEL) ? DIALOG_STYLE1_ITEMSPERPAGE : DIALOG_STYLE2_ITEMSPERPAGE)) {
			if (t_iIndex == selected) {
				Dialog_ShowListitem(playerid, t_iIndex, strval(t_sSplit[i - 2]), t_sSplit[i - 1], true);
	 		}
	  		else {
				Dialog_ShowListitem(playerid, t_iIndex, strval(t_sSplit[i - 2]), t_sSplit[i - 1], false);
	 		}

			t_iIndex += 1;
		}
	}
	return true;
}

stock Dialog_HideList(playerid) {
	if (GetPVarInt(playerid, "Dialog_Style") == DIALOG_STYLE_PREVMODEL) {
	    for (new i = 0; i < DIALOG_STYLE1_ITEMSPERPAGE; i++) {
 			TextDrawHideForPlayer(playerid, g_txtDialogModels[i]);

 			if (g_txtPlayerDialogLabels[playerid][i] != PlayerText:INVALID_TEXT_DRAW) {
	        	PlayerTextDrawDestroy(playerid, g_txtPlayerDialogLabels[playerid][i]);
	        }
	        g_txtPlayerDialogLabels[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
	    }
	}
	else if (GetPVarInt(playerid, "Dialog_Style") == DIALOG_STYLE_PREVMODEL_LIST) {
	    for (new i = 0; i < DIALOG_STYLE2_ITEMSPERPAGE; i++) {
 			TextDrawHideForPlayer(playerid, g_txtDialogModels_List[i]);
 			TextDrawHideForPlayer(playerid, g_txtDialogBars_List[i]);

 			if (g_txtPlayerDialogLabels_List[playerid][i] != PlayerText:INVALID_TEXT_DRAW) {
	        	PlayerTextDrawDestroy(playerid, g_txtPlayerDialogLabels_List[playerid][i]);
	        }
	        g_txtPlayerDialogLabels_List[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
	    }
	}
}

stock Dialog_ShowPlayerDialog(playerid, dialogid, style, caption[], info[], button1[], button2[]) {
	if (dialogid <= -1) {
	    if (GetPVarType(playerid, "Dialog_Style") != PLAYER_VARTYPE_NONE) {
	 		Dialog_HideBase(playerid);
			Dialog_HideHUDS(playerid);
			Dialog_HideList(playerid);

			CancelSelectTextDraw(playerid);
			SetPVarInt(playerid, "Dialog_CancelTextDraw", 1);

			DeletePVar(playerid, "Dialog_Style");
			DeletePVar(playerid, "Dialog_Id");
			DeletePVar(playerid, "Dialog_Listitem");
			DeletePVar(playerid, "Dialog_Page");
			DeletePVar(playerid, "Dialog_Tick");

			return true;
		}
	}

	switch (style) {
		case DIALOG_STYLE_PREVMODEL, DIALOG_STYLE_PREVMODEL_LIST: {
            SetPVarString(playerid, "Dialog_Info", info);
			SetPVarInt(playerid, "Dialog_Style", style);
			SetPVarInt(playerid, "Dialog_Id", dialogid);
			SetPVarInt(playerid, "Dialog_Listitem", 0);
			SetPVarInt(playerid, "Dialog_Page", 0);
			SetPVarInt(playerid, "Dialog_Tick", 0);
			DeletePVar(playerid, "Dialog_CancelTextDraw");

			if (style == DIALOG_STYLE_PREVMODEL) {
				for (new i = 0; i < DIALOG_STYLE1_ITEMSPERPAGE; i++) {
	                g_txtPlayerDialogLabels[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
				}
			}
			else {
				for (new i = 0; i < DIALOG_STYLE2_ITEMSPERPAGE; i++) {
	                g_txtPlayerDialogLabels_List[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
				}
			}

	 		if (button2[0]) {
				Dialog_ShowBase(playerid);
	        }
	        else {
				Dialog_ShowBase(playerid, false);
	    	}
			Dialog_ShowHUDS(playerid, caption, button1, button2);
			Dialog_ShowList(playerid, info, 0, 0);

			SelectTextDraw(playerid, DIALOG_SELECTION_COLOR);

			return true;
		}

		default: {
            ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
		}
	}

	return true;
}
#if defined _ALS_ShowPlayerDialog
	#undef ShowPlayerDialog
#else
	#define _ALS_ShowPlayerDialog
#endif
#define ShowPlayerDialog Dialog_ShowPlayerDialog

public OnPlayerClickTextDraw(playerid, Text:clickedid) {
	if (GetPVarType(playerid, "Dialog_CancelTextDraw") == PLAYER_VARTYPE_NONE && GetPVarType(playerid, "Dialog_Style") != PLAYER_VARTYPE_NONE) {
		new
			t_sSplit[DIALOG_MAXINFO_SIZE][30],
   			t_sInfo[DIALOG_MAXINFO_SIZE * 2]
		;

		if (clickedid == Text:INVALID_TEXT_DRAW || clickedid == g_DialogBase[e_txtButtonRight][4]) {
			if (funcidx("OnDialogResponse") != -1) {
				if (! CallLocalFunction("OnDialogResponse", "iiiis", playerid, GetPVarInt(playerid, "Dialog_Id"), 0, GetPVarInt(playerid, "Dialog_Listitem"), "(null)")) {
					CallRemoteFunction("OnDialogResponse", "iiiis", playerid, GetPVarInt(playerid, "Dialog_Id"), 0, GetPVarInt(playerid, "Dialog_Listitem"), "(null)");
				}
			}
			else {
				CallRemoteFunction("OnDialogResponse", "iiiis", playerid, GetPVarInt(playerid, "Dialog_Id"), 0, GetPVarInt(playerid, "Dialog_Listitem"), "(null)");
			}

			Dialog_ShowPlayerDialog(playerid, -1, DIALOG_STYLE_PREVMODEL, "", "", "", "");
		}
		else if (clickedid == g_DialogBase[e_txtButtonLeft][4] || clickedid == g_DialogBase[e_txtButtonCenter][4]) {
			if (funcidx("OnDialogResponse") != -1) {
				if (! CallLocalFunction("OnDialogResponse", "iiiis", playerid, GetPVarInt(playerid, "Dialog_Id"), 1, GetPVarInt(playerid, "Dialog_Listitem"), "(null)")) {
					CallRemoteFunction("OnDialogResponse", "iiiis", playerid, GetPVarInt(playerid, "Dialog_Id"), 1, GetPVarInt(playerid, "Dialog_Listitem"), "(null)");
				}
			}
			else {
				CallRemoteFunction("OnDialogResponse", "iiiis", playerid, GetPVarInt(playerid, "Dialog_Id"), 1, GetPVarInt(playerid, "Dialog_Listitem"), "(null)");
			}

			Dialog_ShowPlayerDialog(playerid, -1, DIALOG_STYLE_PREVMODEL, "", "", "", "");
		}
		else if (clickedid == g_DialogBase[e_txtScrollUp][0]) {
			GetPVarString(playerid, "Dialog_Info", t_sInfo, sizeof(t_sInfo));
		    if (! Dialog_ShowList(playerid, t_sInfo, GetPVarInt(playerid, "Dialog_Page") - 1, 0)) {
      			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		    }
		    else {
				SetPVarInt(playerid, "Dialog_Page", GetPVarInt(playerid, "Dialog_Page") - 1);
			}
		}
		else if (clickedid == g_DialogBase[e_txtScrollDown][0]) {
			GetPVarString(playerid, "Dialog_Info", t_sInfo, sizeof(t_sInfo));
		    if (! Dialog_ShowList(playerid, t_sInfo, GetPVarInt(playerid, "Dialog_Page") + 1, 0)) {
      			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		    }
		    else {
				SetPVarInt(playerid, "Dialog_Page", GetPVarInt(playerid, "Dialog_Page") + 1);
			}
		}
		else {
			GetPVarString(playerid, "Dialog_Info", t_sInfo, sizeof(t_sInfo));
			new
			    t_iSplitSize = Dialog_Split(t_sInfo, t_sSplit, '\n'),
				t_iIndex,
				i,
				d
			;
			d = ((GetPVarInt(playerid, "Dialog_Style") == DIALOG_STYLE_PREVMODEL) ? DIALOG_STYLE1_ITEMSPERPAGE : DIALOG_STYLE2_ITEMSPERPAGE) * 2;
		    i = 2 + (GetPVarInt(playerid, "Dialog_Page"))*d;

		    if (GetPVarInt(playerid, "Dialog_Style") == DIALOG_STYLE_PREVMODEL) {
				for (; i <= t_iSplitSize; i += 2) {
				    if (t_iIndex < DIALOG_STYLE1_ITEMSPERPAGE) {
						if (clickedid == g_txtDialogModels[t_iIndex]) {
						    if ((GetTickCount() - GetPVarInt(playerid, "Dialog_Tick")) <= 200) {
								if (funcidx("OnDialogResponse") != -1) {
									if (! CallLocalFunction("OnDialogResponse", "iiiis", playerid, GetPVarInt(playerid, "Dialog_Id"), 1, (t_iIndex + (GetPVarInt(playerid, "Dialog_Page") * DIALOG_STYLE1_ITEMSPERPAGE)), "(null)")) {
										CallRemoteFunction("OnDialogResponse", "iiiis", playerid, GetPVarInt(playerid, "Dialog_Id"), 1, (t_iIndex + (GetPVarInt(playerid, "Dialog_Page") * DIALOG_STYLE1_ITEMSPERPAGE)), "(null)");
									}
								}
								else {
									CallRemoteFunction("OnDialogResponse", "iiiis", playerid, GetPVarInt(playerid, "Dialog_Id"), 1, (t_iIndex + (GetPVarInt(playerid, "Dialog_Page") * DIALOG_STYLE1_ITEMSPERPAGE)), "(null)");
								}

								Dialog_ShowPlayerDialog(playerid, -1, DIALOG_STYLE_PREVMODEL, "", "", "", "");

								SetPVarInt(playerid, "Dialog_Tick", GetTickCount());

						        break;
						    }

							TextDrawBackgroundColor(g_txtDialogModels[t_iIndex], DIALOG_SELECTION_COLOR);

							SetPVarInt(playerid, "Dialog_Listitem", (t_iIndex + (GetPVarInt(playerid, "Dialog_Page") * DIALOG_STYLE1_ITEMSPERPAGE)));
				 		}
				  		else {
							TextDrawBackgroundColor(g_txtDialogModels[t_iIndex], DIALOG_MODELNONSELECTION_COLOR);
				 		}
				 		TextDrawShowForPlayer(playerid, g_txtDialogModels[t_iIndex]);
					}
					else {
				 		TextDrawHideForPlayer(playerid, g_txtDialogModels[t_iIndex]);
					}

					t_iIndex += 1;
				}

				SetPVarInt(playerid, "Dialog_Tick", GetTickCount());
			}
			else {
				for (; i <= t_iSplitSize; i += 2) {
				    if (t_iIndex < DIALOG_STYLE2_ITEMSPERPAGE) {
						if (clickedid == g_txtDialogBars_List[t_iIndex]) {
						    if ((GetTickCount() - GetPVarInt(playerid, "Dialog_Tick")) <= 200) {
								if (funcidx("OnDialogResponse") != -1) {
									if (! CallLocalFunction("OnDialogResponse", "iiiis", playerid, GetPVarInt(playerid, "Dialog_Id"), 1, (t_iIndex + (GetPVarInt(playerid, "Dialog_Page") * DIALOG_STYLE2_ITEMSPERPAGE)), "(null)")) {
										CallRemoteFunction("OnDialogResponse", "iiiis", playerid, GetPVarInt(playerid, "Dialog_Id"), 1, (t_iIndex + (GetPVarInt(playerid, "Dialog_Page") * DIALOG_STYLE2_ITEMSPERPAGE)), "(null)");
									}
								}
								else {
									CallRemoteFunction("OnDialogResponse", "iiiis", playerid, GetPVarInt(playerid, "Dialog_Id"), 1, (t_iIndex + (GetPVarInt(playerid, "Dialog_Page") * DIALOG_STYLE2_ITEMSPERPAGE)), "(null)");
								}

								Dialog_ShowPlayerDialog(playerid, -1, DIALOG_STYLE_PREVMODEL, "", "", "", "");

								SetPVarInt(playerid, "Dialog_Tick", GetTickCount());

						        break;
						    }

							TextDrawColor(g_txtDialogBars_List[t_iIndex], DIALOG_SELECTION_COLOR);

							SetPVarInt(playerid, "Dialog_Listitem", (t_iIndex + (GetPVarInt(playerid, "Dialog_Page") * DIALOG_STYLE2_ITEMSPERPAGE)));
				 		}
				  		else {
							TextDrawColor(g_txtDialogBars_List[t_iIndex], DIALOG_BARNONSELECTION_COLOR);
				 		}
				 		TextDrawShowForPlayer(playerid, g_txtDialogBars_List[t_iIndex]);
					}
					else {
				 		TextDrawHideForPlayer(playerid, g_txtDialogBars_List[t_iIndex]);
					}

					t_iIndex += 1;
				}

				SetPVarInt(playerid, "Dialog_Tick", GetTickCount());
			}
		}
	}
	else {
		DeletePVar(playerid, "Dialog_CancelTextDraw");
	}

    #if defined Dialog_OnPlayerClickTextDraw
       	return Dialog_OnPlayerClickTextDraw(playerid, Text:clickedid);
	#else
	   	return 1;
	#endif
}
#if defined _ALS_OnPlayerClickTextDraw
    #undef OnPlayerClickTextDraw
#else
    #define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw Dialog_OnPlayerClickTextDraw
#if defined Dialog_OnPlayerClickTextDraw
    forward Dialog_OnPlayerClickTextDraw(playerid, Text:clickedid);
#endif
