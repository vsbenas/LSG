#include <discord-connector>

#define NUM_CHANNELS 200
#define NUM_PARENTS 4
#define DIST_VOICE 20.0

new DCC_Channel:ChannelId[NUM_CHANNELS];
#define GUILD_ID "723968837447450627"
#define CH_ID "723972671292834282"
#define CH_ID2 "724271864301748347"
#define CH_ID3 "724280335122300928"
#define CH_ID4 "724280381787996251"

#define CH_TYLA "724324749454344253"

#define CH_PATVIRTINIMAS "723968837963481161"

forward ChannelCreated(id);

new const DC_Channels_Gaujos[][] = {
	"724289629658022002",//"The Ballas",
	"724289630454939679",//"Varios Los Aztecas",
	"724289631125897308",//"Grove Street Families",
	"724289631780208662",//"Los Santos Vagos",
	"724289632459685930",//"The Mafia",
	"724289633499742269"//"Da Nang Boys"
};

new const DC_Channels_Darbai[][] = {
	"", // 0 - Bedarbis
	"", // 1 - Nezinomas
	"724289620501594183", // 2 - Medikas
	"724289622019932170", // 3 - Taksistas
	"", // 4 - Traukinio vairuotojas
	"", // 5 - Autobuso vairuotojas
	"724289622259007541", // 6 - Mechanikas
	"", // 7 - Nezinomas
	"", // 8 - Nezinomas
	"", // 9 - Nezinomas
	"", // 10 - Nezinomas
	"", // 11 - Nezinomas
	"", // 12 - Reporteris
	"", // 13 - Nezinomas
	"", // 14 - Pakrantes apsauga
	"", // 15 - Advokatas
	"", // 16 - Nezinomas
	"", // 17 - Nezinomas
	"", // 18 - Nezinomas
	"", // 19 - Nezinomas
	"724289622019932170", // 20 - Transporteris
	"", // 21 - Nezinomas
	"", // 22 - Nezinomas
	"", // 23 - Nezinomas
	"", // 24 - Nezinomas
	"", // 25 - Nezinomas
	"", // 26 - Nezinomas
	"", // 27 - Nezinomas
	"", // 28 - Nezinomas
	"", // 29 - Nezinomas
	"", // 30 - Kriminalistas
	"724289623458709514", // 31 - Kontrabandininkas
	"724289623458709514", // 32 - Dyleris
	"", // 33 - Nezinomas
	"724289628210987019", // 34 - N.Turto agentas
	"", // 35 - Kunigas
	"", // 36 - BMX'eris
	"", // 37 - Picos isvez
	"", // 38 - Nezinomas
	"724289622019932170", // 39 - Limuzino vairuotojas
	"", // 40 - Nezinomas
	"724300773122375762", // 41 - Fiistas
	"", // 42 - Pasienietis
	"", // 43 - Nezinomas
	"724300773122375762", // 44 - Kurjeris
	"", // 45 - Lakunas
	"", // 46 - Nezinomas
	"", // 47 - Nezinomas
	"", // 48 - Nezinomas
	"", // 49 - Nezinomas
	"724300772300554301", // 50 - Skelbejas
	"", // 51 - Nezinomas
	"", // 52 - Nezinomas
	"", // 53 - Nezinomas
	"", // 54 -slavejas
	"", // 55 - M.Autobuso vairuotojas
	"", // 56 - kazkaskininkas
	"", // 57 - Nezinomas
	"724289627661271110", // 58 - Vagis
	"", // 59 - Nezinomas
	"724289628655583277", // 60 - Inkasatorius
	"", // 61 - Nezinomas
	"", // 62 - Siuksliavevezys
	"", // 63 - Nezinomas
	"", // 64 - Nezinomas
	"", // 65 - Nezinomas
	"724300771923067010", // 66 - Gaisrininkas
	"", // 67 - Nezinomas
	"", // 68 - Nezinomas
	"", // 69 - Bankininkas
	"724289624893030441", // 70 - Automanas
	"724289625618776145", // 71 - Baikeris
	"", // 72 - Nezinomas
	"724289624893030441", // 73 - Motomanas
	"", // 74 - Nezinomas
	"", // 75 - Nezinomas
	"", // 76 - Nezinomas
	"", // 77 - Nezinomas
	"", // 78 - Nezinomas
	"", // 79 - Statybininkas
	"724300589827096596", // 80 - Policininkas
	"724300589827096596", // 81 - ARAS
	"724300589827096596", // 82 - VST
	"724300589827096596", // 83 - Kareivis
	"724300589827096596", // 84 - Kobra 11
	"", // 85 - Nezinomas
	"", // 86 - Nezinomas
	"", // 87 - Nezinomas
	"", // 88 - Sokeja
	"", // 89 - Nezinomas
	"", // 90 - Nezinomas
	"", // 91 - Nezinomas
	"", // 92 - Nezinomas
	"724289620501594183", // 93 - Privatus medikas
	"", // 94 - Nezinomas
	"", // 95 - Nezinomas
	"", // 96 - Nezinomas
	"", // 97 - Nezinomas
	"", // 98 - Nezinomas
	"" // 99 - Nezinomas
};


new DCC_Channel:parent[NUM_PARENTS];
new DCC_Channel:tyla;
new DCC_Channel:patvirtinimas;

new DCC_Guild:guildnr;


new Iterator:PlayersVoice<MAX_PLAYERS>;


stock InitDC()
{
	guildnr = DCC_FindGuildById(GUILD_ID);
	printf("%i", _:guildnr);
	parent[0] = DCC_FindChannelById(CH_ID);
	parent[1] = DCC_FindChannelById(CH_ID2);
	parent[2] = DCC_FindChannelById(CH_ID3);
	parent[3] = DCC_FindChannelById(CH_ID4);
	tyla = DCC_FindChannelById(CH_TYLA);
	patvirtinimas = DCC_FindChannelById(CH_PATVIRTINIMAS);
	printf("DC Parents: %i %i %i %i",_:parent[0],_:parent[1],_:parent[2],_:parent[3]);
	for(new i;i<NUM_CHANNELS;i++)
	{
		new str[24];
		format(str,24,"LSGV%i",i);
		CreateChannelIfNotExists(str,i);
	}
	SetTimer("UpdateDiscord",3999,1);


	DCTD[0] = TextDrawCreate(628.298461, 424.810729, "~r~T"); // tyla
	TextDrawLetterSize(DCTD[0], 0.335333, 1.032222);
	TextDrawAlignment(DCTD[0], 1);
	TextDrawColor(DCTD[0], -1);
	TextDrawSetShadow(DCTD[0], 0);
	TextDrawSetOutline(DCTD[0], 0);
	TextDrawBackgroundColor(DCTD[0], 255);
	TextDrawFont(DCTD[0], 0);
	TextDrawSetProportional(DCTD[0], 1);
	TextDrawSetShadow(DCTD[0], 0);
	TextDrawSetSelectable(DCTD[0], true);

	DCTD[1] = TextDrawCreate(628.298461, 424.810729, "~w~A"); // aplinkiniai
	TextDrawLetterSize(DCTD[1], 0.335333, 1.032222);
	TextDrawAlignment(DCTD[1], 1);
	TextDrawColor(DCTD[1], -1);
	TextDrawSetShadow(DCTD[1], 0);
	TextDrawSetOutline(DCTD[1], 0);
	TextDrawBackgroundColor(DCTD[1], 255);
	TextDrawFont(DCTD[1], 0);
	TextDrawSetProportional(DCTD[1], 1);
	TextDrawSetShadow(DCTD[1], 0);
	TextDrawSetSelectable(DCTD[1], true);

	DCTD[2] = TextDrawCreate(628.298461, 424.810729, "~g~R"); // racija
	TextDrawLetterSize(DCTD[2], 0.335333, 1.032222);
	TextDrawAlignment(DCTD[2], 1);
	TextDrawColor(DCTD[2], -1);
	TextDrawSetShadow(DCTD[2], 0);
	TextDrawSetOutline(DCTD[2], 0);
	TextDrawBackgroundColor(DCTD[2], 255);
	TextDrawFont(DCTD[2], 0);
	TextDrawSetProportional(DCTD[2], 1);
	TextDrawSetShadow(DCTD[2], 0);
	TextDrawSetSelectable(DCTD[2], true);

	DCTD[3] = TextDrawCreate(628.298461, 424.810729, "~p~G"); // gauja
	TextDrawLetterSize(DCTD[3], 0.335333, 1.032222);
	TextDrawAlignment(DCTD[3], 1);
	TextDrawColor(DCTD[3], -1);
	TextDrawSetShadow(DCTD[3], 0);
	TextDrawSetOutline(DCTD[3], 0);
	TextDrawBackgroundColor(DCTD[3], 255);
	TextDrawFont(DCTD[3], 0);
	TextDrawSetProportional(DCTD[3], 1);
	TextDrawSetShadow(DCTD[3], 0);
	TextDrawSetSelectable(DCTD[3], true);

	//new DCC_User:user = DCC_FindUserByName("Benas","6769");
	//printf("User %i",_:user);
}

/* return codes:
1 - success
0 - no DC connected
-1 - not a gang member
-2 - job does not have radio
-3 - error finding channel
*/
stock SetDiscordType(playerid,type,dryrun=0)
{
	new user = GetPVarInt(playerid, "DCID");
	new prevType = GetPVarInt(playerid, "DCTYPE");
	TextDrawHideForPlayer(playerid, DCTD[prevType]);
	new gang = playerDB[playerid][pgang];
	new spec = playerDB[playerid][specialybe];
	if(user == 0)
	{
		return 0;
	}
	new DCC_Channel:ch;
	new DCC_Channel:curr;
	DCC_GetGuildMemberVoiceChannel(guildnr,DCC_User:user,curr);
	if(curr == DCC_INVALID_CHANNEL)
	{
		return -3;
	}

	
	if(type == 0)
	{
		ch = tyla;
	}
	else if(type == 1) // global
	{
		ch = tyla;
	}
	else if(type == 2) // job
	{
		if(strlen(DC_Channels_Darbai[spec]) == 0)
			return -2;

		ch = DCC_FindChannelById(DC_Channels_Darbai[spec]);
	}
	else if(type == 3) // gang
	{
		if(gang == -1)
			return -1;

		ch = DCC_FindChannelById(DC_Channels_Gaujos[gang]);
	}

	if(ch == DCC_INVALID_CHANNEL)
	{
		printf("[discord] Channel not found. Player %i, Type %i, Gang %i, Spec %i",playerid,type,gang,spec);
		return -3;
	}
	if(dryrun == 1)
		return 1;
	if(type == 1)
	{
		if(!Iter_Contains(PlayersVoice, playerid))
		{
			Iter_Add(PlayersVoice, playerid);
		}
	}
	else
	{
		if(Iter_Contains(PlayersVoice, playerid))
		{
			Iter_Remove(PlayersVoice,playerid);
		}
	}

	MoveToChannel(DCC_User:user, ch);
	TextDrawShowForPlayer(playerid, DCTD[type]);
	new const messages[][] = {
		"~r~Tylos kambarys",
		"~w~Aplinkiniai",
		"~g~Racija",
		"~p~Gauja"
	};
	SendInfoMessage(playerid,messages[type]);
	SetPVarInt(playerid, "DCTYPE", type);
	return 1;
}
stock SetDCId(playerid,DCC_User:user)
{
	SetPVarInt(playerid, "DCID", _:user);
}
stock CreateChannelIfNotExists(name[],id)
{
	new DCC_Channel:ch = DCC_FindChannelByName(name);

	if(ch == DCC_INVALID_CHANNEL)
	{
		new escname[50]; 
		DCC_EscapeMarkdown(name,escname);
		printf("Creating channel %s %s",name,escname);


		DCC_CreateGuildChannel(guildnr, escname, GUILD_VOICE , "ChannelCreated","i",id); //, const format[] = "", {Float, _}:...);
	}
	else
	{
		//printf("Channel %s exists",name);
		ParentChannel(ch,id);
	}
}	
stock ParentChannel(DCC_Channel:ch,id)
{
	if(id == -1)
	{
		return;
	}
	new parentid = id / 50;//discord hard 50 channel limit per category
	ChannelId[id] = ch;
	//DCC_SetChannelParentCategory(ch,parent[parentid]);
}

public ChannelCreated(id)
{
	new DCC_Channel:ch = DCC_GetCreatedGuildChannel();
	printf("Channel %i created!",_:ch);
	ParentChannel(ch,id);
}

#define NUM_USERS 5000
new DCC_Channel:UserChannels[NUM_USERS];
public DCC_OnGuildMemberVoiceUpdate(DCC_Guild:guild, DCC_User:user, DCC_Channel:channel)
{
	printf("Voice update %i %i %i!",_:guild,_:user,_:channel);
	if(_:user < NUM_USERS)
	{
		UserChannels[_:user] = channel;
	}
	printf("Voice update2 %i %i %i!",_:guild,_:user,_:channel);
	new uid = -1;
	foreach(PlayersVoice, i)
	{
		new useris = GetPVarInt(i, "DCID");
		new type = GetPVarInt(i, "DCTYPE");
		if(useris == _:user && type == 1)
		{
			uid = i;

			break;
		}
	}
	if(uid != -1)
	{
		new found = 0;
		if(channel == tyla)
			found = 1;
		for(new i;i<NUM_CHANNELS && found == 0;i++)
		{
			if(UserChannels[_:user] == ChannelId[i])
			{
				SetPlayerChatBubble(uid, "Balsas", 0x2DB82FFF, 11.0, 3000);
				found = 1;
			}
		}
		if(found == 0)
		{
			TextDrawHideForPlayer(uid, DCTD[1]);
			TextDrawShowForPlayer(uid, DCTD[0]);
			SetPVarInt(uid, "DCTYPE", 0);
			Iter_Remove(PlayersVoice, uid);
		}
	}
}

/*
DBSCAN(DB, distFunc, eps, minPts) {
    C = 0                                                 
    for each point P in database DB {
        if label(P) â‰  undefined then continue              
        Neighbors N = RangeQuery(DB, distFunc, P, eps)    
        if |N| < minPts then {                            
            label(P) = Noise                               
            continue
        }
        C = C + 1                                         
        label(P) = C                                     
        Seed set S = N \ {P}                               
        for each point Q in S {                          
            if label(Q) = Noise then label(Q) = C          
            if label(Q) â‰  undefined then continue          
            label(Q) = C                                  
            Neighbors N = RangeQuery(DB, distFunc, Q, eps) 
            if |N| >= minPts then {               
                S = S U N                                 
            }
        }
    }
}
*/
new NeighbourArray[MAX_PLAYERS];
new NumNeighbours = 0;
stock ResetNeighbours()
{
	//for(new i;i<NumNeighbours;i++)
	//	NeighbourArray[i] = 0;
	NumNeighbours = 0;
}
stock GetNeighbours(playerid)
{
	new skamb = playerDB[playerid][skambutis];
	new tick = GetTickCount();
	if(skamb != -1)
	{
		if(IsPlayerConnected(skamb))
		{
			NeighbourArray[NumNeighbours] = skamb;
			NumNeighbours++;
		}
	}
	else if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING || IsPlayerAfkEx(playerid,tick))
	{

	}
	else
	{
		new Float:Coo[3];
		GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
		new vw = GetPlayerVirtualWorld(playerid);
		new int = GetPlayerInterior(playerid);
		foreach(PlayersVoice, p) if(p != playerid)
		{
			if(!IsPlayerAfkEx(p,tick) && GetPlayerState(p) != PLAYER_STATE_SPECTATING && playerDB[p][skambutis] == -1 && IsPlayerInRangeOfPoint(p,DIST_VOICE,Coo[0],Coo[1],Coo[2]) && GetPlayerVirtualWorld(p) == vw && GetPlayerInterior(p) == int)
			{
				NeighbourArray[NumNeighbours] = p;
				NumNeighbours++;
			}
		}
	}
}

forward UpdateDiscord();
public UpdateDiscord()
{
	//printf("UpdateDiscord");
	//printf("Updating discord!");
	new Label[MAX_PLAYERS]; // what cluster is the player in
	new LabelCount[MAX_PLAYERS];
	new cluster = 0;
	/* Implementing DBSCAN */
	foreach(PlayersVoice, i)
	{
		if(Label[i] != 0)
			continue;		
		ResetNeighbours();
		GetNeighbours(i);

		cluster++;
		Label[i] = cluster;
		LabelCount[cluster]++;

		for(new a;a<NumNeighbours;a++) // NumNeighbours can increase within the loop
		{
			new p = NeighbourArray[a];
			if(Label[p] != 0)
				continue;
			Label[p] = cluster;
			LabelCount[cluster]++;
			GetNeighbours(p);
		}
	}
	foreach(PlayersVoice, c) 
	{
		new dcid = GetPVarInt(c, "DCID");
		new label = Label[c];
		new count = LabelCount[label];
		if(label == 0 || count == 0)
		{
			printf("[discord] Error! Pid %i Label %i Count %i",c,label,count);
			continue;
		}
		if(count == 1) // Move to tylos channel
		{
			MoveToChannel(DCC_User:dcid, tyla);
		}
		else if(label <= NUM_CHANNELS) // make a group
		{
			MoveToChannel(DCC_User:dcid, ChannelId[label-1]);
		}
	}
}
stock MoveToChannel(DCC_User:dcid,DCC_Channel:ch)
{
	if(_:dcid < NUM_USERS)
	{
		if(UserChannels[_:dcid] == ch)
		{
			return 0;
		}

		//UserChannels[_:dcid] = ch;
	}
	printf("MoveToChannel");
	DCC_SetGuildMemberVoiceChannel(guildnr, dcid, ch);

	return 1;
}
public DCC_OnMessageCreate(DCC_Message:message)
{
	printf("OnMessageCreate %i",_:message);
	new DCC_Channel:ch;
	DCC_GetMessageChannel(message, ch);
	printf("OnMessageCreate %i %i",_:message,_:ch);
	if(ch == patvirtinimas)
	{
		printf("Patvirtinimas1!");
		new dest[128];
		DCC_GetMessageContent(message,dest,128);
		new rest[24],name[24];
		
		if (strcmp("!dc ", dest, true, 4) == 0)
    	{
    		printf("Command match! sscanf now");
    		if(sscanf(dest,"s[24]s[24]",rest,name))
			{
				printf("bad format");
				return 1;
			}
    	}
    	else
    	{
    		printf("No match");
    		return 1;
    	}
		printf("Patvirtinimas2!");
		new id = GetIdForAlgos(name);
		if(id == INVALID_PLAYER_ID)
		{
			DCC_SendChannelMessage(ch, "Toks zaidejas neprisijunges serveryje!");
		}
		else
		{
			new DCC_User:user;
			DCC_GetMessageAuthor(message, user);
			if(GetPVarInt(id, "DCID") != 0)
			{
				DCC_SendChannelMessage(ch, "Sis zaidejas jau patvirtino savo Discord!");
			}
			else if(GetPVarInt(id,"DCVERIFY") == 0)
			{
				DCC_SendChannelMessage(ch, "Pirmiausiai patvirtink savo discord zaidime! Rasyk /dc");
			}
			else
			{
				if(GetPVarInt(id,"DCVERIFY") == _:user && user != DCC_INVALID_USER)
				{
					DCC_SendChannelMessage(ch, "Sekmingai patvirtinai savo Discord!");
					SetPVarInt(id, "DCVERIFY", 0);
					SetPVarInt(id, "DCID", _:user);
					new discordid[DCC_ID_SIZE];
					DCC_GetUserId(user,  discordid);
					new query[300];
					format(query,sizeof(query),"REPLACE INTO `Discord`(`Vardas`,`Discord`) VALUES('%s','%s')",ReturnName(id),discordid);
					mysql_query(query);
					ConnectDC(id,discordid);
				}
			}
		}
		
	}
	return 1;
}
stock ConnectDC(playerid,discordid[])
{
	printf("ConnectDC %i",playerid);
	new DCC_User:usr = DCC_FindUserById(discordid);
	if(usr == DCC_INVALID_USER)
	{
		SendClientMessageLT(playerid, RED, "[Discord] Klaida jungiantis prie Discord serverio. Pabandyk is naujo prijungti savo Discord per Nustatymus paraðæs /p");
	}
	else
	{
		SetPVarInt(playerid, "DCID", _:usr);
		new res = SetDiscordType(playerid,0); // tylos kambarys
		if(res == -3)
		{
			TextDrawShowForPlayer(playerid, DCTD[0]);
			SendClientMessageLT(playerid, RED, "[Discord] Tu neprisijungæs á joká Discord kanalà, todël balsas þaidime neveiks. Prisijunk á bet kurá kanalà per Discord programà!");
		}
		else
		{
			SendClientMessageLT(playerid, ORANGE, "[Discord] Sëkmingai prisijungei á Discord serverá!");
		}
	}
}
stock SkambutisDiscord(pid1, pid2)
{
	if(GetPVarInt(pid1, "DCID") && GetPVarInt(pid2, "DCID"))
	{
		new res = SetDiscordType(pid1,1,1);
		new res2 = SetDiscordType(pid2,1,1);
		if(res == 1 && res2 == 1)
		{
			SetDiscordType(pid1,1);
			SetDiscordType(pid2,1);
			return 1;
		}
	}
	return 0;
}