/*  SA:MP ServerQuery By Flag Functions  */

#if defined _extrcon_included
	#endinput
#endif
#define _extrcon_included
#pragma library ExternRcon

#define MAX_RULENAMESIZE  9
#define MAX_RULEVALUESIZE 128
#define MAX_RULES 6

native GetInfoPacket(ip[],port);
native iIsPassworded();	
native iGetPlayers();
native iGetMaxPlayers();
native iGetHostname(hostname[]);
native iGetGamemode(gamemode[]);
native iGetMapname(mapname[]);

native GetRulesPacket(ip[],port);
native rGetRulesAmount();
native rGetRuleName(ruleid,rulename[]);
native rGetRuleValue(ruleid,rulevalue[]);

native GetPlayerPacket(ip[],port);
native cGetPlayers();
native cGetPlayerName(playerid,plname[]);
native cGetPlayerScore(playerid);