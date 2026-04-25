/**********************************
 *                                *
 *   @Author:      ZeeX           *
 *   @Version:     0.3.1          *
 *   @Released:    31/10/2009     *
 *                                *
 **********************************/

#if defined _zcmd_included
	#endinput
#endif
#define _zcmd_included

#define MAX_FUNC_NAME (32)

#define COMMAND:%1(%2)          \
			forward cmd_%1(%2); \
			public cmd_%1(%2)

#define CMD:%1(%2) \
			COMMAND:%1(%2)

#define command(%1,%2,%3) \
			COMMAND:%1(%2, %3)

#define cmd(%1,%2,%3) \
			COMMAND:%1(%2, %3)

#if !defined isnull
	#define isnull(%1) \
				((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif


forward OnPlayerCommandReceived(playerid, cmdtext[]);
forward OnPlayerCommandPerformed(playerid, cmdtext[], success);


static
	bool:zcmd_g_HasOPCS = false,
	bool:zcmd_g_HasOPCE = false;

#if defined FILTERSCRIPT

public OnFilterScriptInit()
{
	zcmd_g_HasOPCS = funcidx("OnPlayerCommandReceived") != -1;
	zcmd_g_HasOPCE = funcidx("OnPlayerCommandPerformed") != -1;
    return CallLocalFunction("zcmd_OnFilterScriptInit", "");
}

#if defined _ALS_OnFilterScriptInit
    #undef OnFilterScriptInit
#else
    #define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit zcmd_OnFilterScriptInit
forward zcmd_OnFilterScriptInit();

#else /*not a filterscript*/

public OnGameModeInit()
{
	zcmd_g_HasOPCS = funcidx("OnPlayerCommandReceived") != -1;
	zcmd_g_HasOPCE = funcidx("OnPlayerCommandPerformed") != -1;
	if (funcidx("zcmd_OnGameModeInit") != -1)
	{
		return CallLocalFunction("zcmd_OnGameModeInit", "");
	}
	return 1;
}

#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit zcmd_OnGameModeInit
forward zcmd_OnGameModeInit();

#endif /*if defined FILTERSCRIPT*/
new ignorecmd[MAX_PLAYERS] = 0;

public OnPlayerCommandText(playerid, cmdtext[])
{
	if(isnull(cmdtext)) return 0;
	replaceChar(cmdtext, '%', '#');
	if(GetPlayerState(playerid)==PLAYER_STATE_WASTED) return SendClientMessage(playerid,COLOR," * Ilsekis ramybeje!"),1;
	if(ignorecmd[playerid] == 0)
	{
		MsgCount[playerid]++;
		if(gPlayerDialog[playerid]!= -1) 
		{
			if(playerDB[playerid][ant] || playerDB[playerid][banned])
				return SendClientMessage(playerid,COLOR," * Uzdaryk dialoga!");

		}
		PlayerAfk2[playerid]=GetTickCount();
		new var = small_hash(cmdtext);
		if(var == PaskutineCmd[playerid])
		{
			KiekFlood[playerid]++;
			if(KiekFlood[playerid]>=3)
			{
				SendClientMessage(playerid,RED," * SPAM! Palaukite, pries rasydami dar viena zinute.");
				return 1;
			}
			if(KiekFlood[playerid]>=20)
			{
				new msg[128]; format(msg,128," * LSG Anti-Cheat: %s buvo iskickintas uz spam.",ReturnName(playerid));
				SendClientMessageToAll(RED,msg);
		        Kick(playerid);
				return 1;
			}
		}
		else
		{
			KiekFlood[playerid]=0;
		}
		PaskutineCmd[playerid]=var;
	}
	//format(PaskutineCmd[playerid],128,cmdtext);


 	if(playerDB[playerid][authstate]==0 || !playerDB[playerid][pospawn] || playerDB[playerid][banned]){SendClientMessage(playerid,0x134FECFF,"* LSG: Pirmiausia prisijunkite"); return 1;}
	
   	new tnam[MAX_PLAYER_NAME];
   	GetPlayerName(playerid,tnam,sizeof(tnam));
   	printf("[COMM] %s: %s",tnam,formatwithoutLT(cmdtext));

   

	if (zcmd_g_HasOPCS && !CallLocalFunction("OnPlayerCommandReceived", "is", playerid, cmdtext))
	{
		return 1;
	}

	new
		pos,
		funcname[MAX_FUNC_NAME];

    while (cmdtext[++pos] > ' ')
	{
		if(pos-1 >=MAX_FUNC_NAME) break;
		funcname[pos-1] = tolower(cmdtext[pos]);
	}
	format(funcname, sizeof(funcname), "cmd_%s", funcname);
    while (cmdtext[pos] == ' ') pos++;
	if (!cmdtext[pos])
	{
		if (zcmd_g_HasOPCE)
		{
			return CallLocalFunction("OnPlayerCommandPerformed", "isi", playerid, cmdtext, CallLocalFunction(funcname, "is", playerid, "\1"));
		}
		return CallLocalFunction(funcname, "is", playerid, "\1");
	}
	if (zcmd_g_HasOPCE)
	{
		return CallLocalFunction("OnPlayerCommandPerformed", "isi", playerid, cmdtext, CallLocalFunction(funcname, "is", playerid, cmdtext[pos]));
	}
	return CallLocalFunction(funcname, "is", playerid, cmdtext[pos]);
}

public OnPlayerCommandPerformed(playerid,cmdtext[],success)
{
	if(!success)//Script hasn't ZCMD anywhere else and there was no JunkBuster command performed by ZCMD, so OnPlayerCommandText must be performed.
	    return CallLocalFunction("zcmd_OnPlayerCommandText","is",playerid,cmdtext);
	return 1;//JunkBuster command performed.
}
#if defined _ALS_OnPlayerCommandText
    #undef OnPlayerCommandText
#else
    #define _ALS_OnPlayerCommandText
#endif
stock OnPlayerCommandTextReal(playerid,cmdtext[])
{
	OnPlayerCommandText(playerid, cmdtext);
}
#define OnPlayerCommandText zcmd_OnPlayerCommandText
forward zcmd_OnPlayerCommandText(playerid, cmdtext[]);

