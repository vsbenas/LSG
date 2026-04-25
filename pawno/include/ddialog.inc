/*
 _____  _      _____  _
|  __ \| |    |  __ \(_)
| |  | | |    | |  | |_  __ _  __ _
| |  | | |    | |  | | |/ _` |/ _` |
| |__| | |____| |__| | | (_| | (_| |
|_____/|______|_____/|_|\__,_|\__, |
   DynamicListDialog (v1.1)    __/ |
                   ByTheXIII  |___/
                                    */


/*=====================================

native AddDListItem(playerid, Item[], ItemID = -1, ItemParam = -1);
native ShowPlayerDList(playerid, DialogID, Caption[], Button1[], Button2[]);

=====================================*/
                                   
#if defined _DLDiag_included
    #endinput
#endif
#define _DLDiag_included

#if !defined _samp_included
    #error "<a_samp> must be included before <DLDiag>"
#endif

#if !defined DLD_STRING_SIZE
    #define DLD_STRING_SIZE 4096
#endif

#if !defined DLD_MAX_LIST_ITEMS
    #define DLD_MAX_LIST_ITEMS 40
#endif
#define DLItemID DLDPlayerListItems[playerid][listitem]
#define DLParam DLDPlayerListParam[playerid][listitem]
                                   
new DLDString[DLD_STRING_SIZE];
new DLDPlayerListItems[MAX_PLAYERS][DLD_MAX_LIST_ITEMS];
new DLDPlayerListParam[MAX_PLAYERS][DLD_MAX_LIST_ITEMS];
new DLDLastIS;

stock AddDListItem(playerid, Item[], ItemID = -1, ItemParam = -1)
{
    DLDPlayerListItems[playerid][DLDLastIS] = ItemID;
    DLDPlayerListParam[playerid][DLDLastIS] = ItemParam;
    if( !DLDLastIS ){DLDString = ""; format(DLDString, sizeof(DLDString), "%s", Item);}
    else format(DLDString, sizeof(DLDString), "%s\r\n%s", DLDString, Item);
    DLDLastIS++;
    return DLDLastIS -1;
}
stock ShowPlayerDList(playerid, DialogID, Caption[], Button1[], Button2[])
{
    DLDLastIS = 0;
	if(isnull(DLDString)) return 1;
    new cpla=ShowPlayerDialog(playerid, DialogID, DIALOG_STYLE_LIST, Caption, DLDString, Button1, Button2);
	DLDString = "";
	return cpla;
}
stock ShowPlayerDListTab(playerid, DialogID, Caption[], Button1[], Button2[])
{
    DLDLastIS = 0;
    if(isnull(DLDString)) return 1;
    new cpla=ShowPlayerDialog(playerid, DialogID, DIALOG_STYLE_TABLIST, Caption, DLDString, Button1, Button2);
    DLDString = "";
    return cpla;
}
stock ShowPlayerDListHeader(playerid, DialogID, Caption[], Button1[], Button2[], Header[])
{
    DLDLastIS = 0;
    if(isnull(DLDString)) return 1;
    format(DLDString,sizeof(DLDString),"%s\n%s",Header,DLDString);
    new cpla=ShowPlayerDialog(playerid, DialogID, DIALOG_STYLE_TABLIST_HEADERS, Caption, DLDString, Button1, Button2);
    DLDString = "";
    return cpla;
}

