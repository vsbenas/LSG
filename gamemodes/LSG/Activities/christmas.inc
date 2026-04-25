
new kaleduRaceState[MAX_PLAYERS];
new lastRaceUpdate[MAX_PLAYERS];
new raceStart[MAX_PLAYERS];
new const Float:QuadRace[][3] = 
{
    {936.806457,-2506.021972,53.810344},
    {867.458923,-2470.834228,53.612968},
    {822.943481,-2349.497314,50.961597},
    {833.305053,-2311.65039,48.709545},
    {790.620544,-2341.497558,47.535514},
    {786.40686,-2399.480224,50.469699},
    {786.972412,-2439.503662,50.471473},
    {849.026977,-2488.713623,46.151966},
    {912.190917,-2519.694091,46.879287},
    {997.035522,-2529.930664,50.204807},
    {1025.176757,-2484.650146,50.163028},
    {1039.438598,-2419.880126,28.931188},
    {1027.752441,-2359.659667,18.386812},
    {974.89685,-2297.300048,19.77518},
    {890.747314,-2227.316894,31.703447},
    {975.654479,-2349.83496,39.985248},
    {951.061096,-2366.081542,42.646621},
    {880.872802,-2313.681884,50.86922},
    {906.427856,-2419.481201,53.880508},
    {887.101013,-2453.909912,53.875232},
    {921.010742,-2476.13916,53.874984}
};


new PlayerText:raceTimer[MAX_PLAYERS];

stock initChristmas() 
{
    //initChristmasMountain();
	//initChristmasCar();
	//initChristmasEgles();
}

stock initChristmasCar() {
	AddJobCar(141,0,562,3,-1,-1,682.9197,-441.9109,15.9950,93.0431);
	SetTimer("ChristmasTimer", 100, true);
}

new Float:EglesPos[][3] = { // 0 - 5
		{1057.9858,-1799.1412,14.8178}, // gabe egle
		{835.7191,-1970.0006,13.4906},// tasty egle
		{700.7830,-1287.7617,15.8640}, // nang egle
		{2240.8550,-1432.8157,25.1454}, // ballas egle
		{1722.3889,-1704.1637,13.6000}, // hotel egle kamikadze
		{1948.3444,-2335.5146,13.6469} // baben egle airport
};

stock CaptureEgle(playerid)
{
	if(GetPVarInt(playerid, "Kaledos2024") != 1)
	{
		return -1;
	}
	if(IsPlayerAttachedObjectSlotUsed(playerid,CAP_SLOT))
	{
		SendInfoMessage(playerid, "~r~ Nusiimk kepure!");
		return -1;
	}
	if(IsPlayerAttachedObjectSlotUsed(playerid,AKINIU_SLOT))
	{
		SendInfoMessage(playerid, "~r~ Nusiimk akinius!");
		return -1;
	}
	new Float:mindist = 9999.9;
	new egluteid = -1;
	for(new i;i<sizeof(EglesPos);i++)
	{
		new Float:dist = GetPlayerDistanceFromPoint(playerid, EglesPos[i][0], EglesPos[i][1], EglesPos[i][2]);
		if(dist < mindist)
		{
			mindist = dist;
			egluteid = i;
		}
	}
	if(mindist > 100.0)
	{
		SendInfoMessage(playerid,"~r~Per toli!");
		return -1;
	}
	new eglestr[24];
	format(eglestr, 24, "Egle%i",egluteid);
	if(GetPVarInt(playerid, eglestr) == 1)
	{
		return -1;
	}

	new
		Float:RL_CameraPos[3],
		Float:RL_CameraVectors[3];

	GetPlayerCameraWeaponVector(playerid, RL_CameraVectors[0], RL_CameraVectors[1], RL_CameraVectors[2]);                     
	GetPlayerCameraPos(playerid, RL_CameraPos[0], RL_CameraPos[1], RL_CameraPos[2]);
	new Float:vectordist[3];
	new i = egluteid;
	GetDistanceFromPointToLine(vectordist[0], RL_CameraVectors[0], RL_CameraVectors[1], RL_CameraVectors[2], RL_CameraPos[0], RL_CameraPos[1], RL_CameraPos[2],EglesPos[i][0], EglesPos[i][1], EglesPos[i][2]);
	GetDistanceFromPointToLine(vectordist[1], RL_CameraVectors[0], RL_CameraVectors[1], RL_CameraVectors[2], RL_CameraPos[0], RL_CameraPos[1], RL_CameraPos[2],EglesPos[i][0], EglesPos[i][1], EglesPos[i][2]+10.0);
	GetDistanceFromPointToLine(vectordist[2], RL_CameraVectors[0], RL_CameraVectors[1], RL_CameraVectors[2], RL_CameraPos[0], RL_CameraPos[1], RL_CameraPos[2],EglesPos[i][0], EglesPos[i][1], EglesPos[i][2]+20.0);

	if(vectordist[0] < 10.0 || vectordist[1] < 10.0 || vectordist[2] < 10.0)
	{
		SetPVarInt(playerid, eglestr, 1);
		SendInfoMessage(playerid, "~g~LSG ~r~Kaledos ~w~2024");
	}
	new count = 0;
	for(new c=0;c<6;c++)
	{
		format(eglestr, 24, "Egle%i",c);
		if(GetPVarInt(playerid, eglestr) == 1)
		{
			count++;
		}
	}
	if(count == 6)
	{
		SendClientMessage(playerid, -1, "{FF0000}[LSG Kalëdos] {FFFFFF}Tu nufotografavai visas LSG eglutes, dabar gali gráþti atsiimti savo dovanà.");
		SetPVarInt(playerid,"Kaledos2024", 2);
	}
	return 1;
}

stock HandleChristmasKeyPress(playerid, newkeys, oldkeys)
{
	if(GetPlayerWeapon(playerid) == 43)
	{
		if(newkeys & KEY_HANDBRAKE && oldkeys & KEY_HANDBRAKE && newkeys & KEY_FIRE && !(oldkeys & KEY_FIRE))
		{
			CaptureEgle(playerid);
		}
	}
	if(GetPlayerWeapon(playerid) == 9)
	{
		if(newkeys & KEY_FIRE && !(oldkeys & KEY_FIRE))
		{
			if(!IsPlayerInRangeOfPoint(playerid, 5.0, -571.9276,-198.7326,78.6303))
				return;
			if(GetPVarInt(playerid, "Kaledos2025") != 4)
				return;
			if(GetPVarInt(playerid,"Loading"))
				return;
			SetPVarInt(playerid,"Loading",1);
			//FadeColorForPlayer(playerid,0,0,0,0,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,10,5);
			new Float:C[3];
			GetPlayerPos(playerid, C[0], C[1], C[2]);
			SetPlayerPosFade(playerid,20, C[0],C[1],C[2]);
			TogglePlayerControllable(playerid,false);
			SetTimerEx("DelayChristmas", 1000, false, "ii",playerid, 7);
		}
	}
	if(GetPVarInt(playerid,"Kaledos2025") == 6)
	{
		if(!IsChristmasEventCar(playerid))
			return;
		// fast and furious
		AddVehicleComponent(GetPlayerVehicleID(playerid), 1010);
		ReduceChristmasBomb(playerid);
	}
}

stock HandleChristmasVehicleMod(playerid, vehicleid, componentid)
{
	#pragma unused vehicleid, componentid
	if(GetPVarInt(playerid, "Kaledos2025") != 1)
		return;
	if(!IsChristmasEventCar(playerid))
		return;
	ChristmasModAdded(playerid, 1);
}
stock HandleChristmasCheckpoint(playerid)
{


	if(GetPVarInt(playerid, "Kaledos2025") < 2)
		return;

	if(GetPVarInt(playerid,"Kaledos2025") == 2)
	{
		if(!IsPlayerInRangeOfPoint(playerid, 10.0, 1975.4083,2162.5107,10.7271))
			return;
		if(!IsChristmasEventCar(playerid))
			return;
		SetTimerEx("DelayChristmas", 1000, false, "ii",playerid, 5);
	}
	else if(GetPVarInt(playerid,"Kaledos2025") == 3)
	{
		// do nothing
		if(!IsPlayerInRangeOfPoint(playerid, 10.0, -566.4586,-176.7756,78.406))
			return;
		Kaledos(playerid, 6);
	}
	else if(GetPVarInt(playerid, "Kaledos2025") == 5)
	{
		// grizo i miesta
		if(!IsPlayerInRangeOfPoint(playerid, 20.0, 84.1876,-1542.7083,5.4038))
			return;
		Kaledos(playerid, 9);
	}
}
CMD:debugkaledos(playerid, params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	SetPVarInt(playerid, "Kaledos2025", strval(params));
	SendClientMessage(playerid, -1, "Done");
	return 1;
}

CMD:debugkaledosfunc(playerid, params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	Kaledos(playerid, strval(params));
	SendClientMessage(playerid, -1, "Done");
	return 1;
}
forward DelayChristmas(playerid, id);
public DelayChristmas(playerid, id)
{
	Kaledos(playerid, id);
	TogglePlayerControllable(playerid, true);
	SetPVarInt(playerid,"Loading",0);
}

stock ChristmasModAdded(playerid, count)
{
	if(GetPVarInt(playerid, "Kaledumods") < 3)
		SetPVarInt(playerid, "Kaledumods", GetPVarInt(playerid, "Kaledumods")+count);
	new msg[256];
	format(msg,256,"Modai: ~p~%i~w~/3",GetPVarInt(playerid, "Kaledumods"));
	SendInfoMessage(playerid, msg);
	PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
}
stock HandleChristmasDriftEnd(playerid)
{
	new points = DriftPoints[playerid];
	if(points >= 1000000 && GetPVarInt(playerid,"Kaledos2025") == 6)
	{
		Kaledos(playerid, 10);
	}
}
stock HandleChristmasEnterExitModShop(playerid, enterexit, interiorid)
{
	#pragma unused interiorid
	if(GetPVarInt(playerid, "Kaledos2025") != 1)
		return;
	if(!IsChristmasEventCar(playerid))
		return;
	if(enterexit) 
	{
		// entered
		ChristmasModAdded(playerid, 0);
	}
	else
	{
		if(GetPVarInt(playerid, "Kaledumods") >= 3)
		{
			Kaledos(playerid, 4);
		}
	}
}
stock Kaledos(playerid, id)
{
	printf("Kaledos(%s, %i)", ReturnName(playerid), id);
    if(id == 0) 
    {
		GiveChristmasHat(playerid);
        new year,month,day;
        getdate(year, month, day);
        if(month != 12 || day > 27 || GetPVarInt(playerid, "Kaledos2025kvs") == 2)
        {
            return SendInfoMessage(playerid,"Aciu uz dalyvavima Kaledu evente! Iki susitikimo kitais metais!");
        }
        else if(month == 12 && day < 25)
        {
            return SendInfoMessage(playerid, "Sugrizk gruodzio 25-27 dienomis!");
        }
        else if(GetPlayerScore(playerid) < 1000)
        {
            return SendInfoMessage(playerid, "Sugrizk kai turesi bent 1000 XP!");
        }
		if(GetPVarInt(playerid, "Kaledos2025") == 7)
		{
			Kaledos(playerid, 11);
			return 1;
		}
		PlayAudioStreamForPlayer(playerid, "http://www.lsgyvenimas.lt/sounds/christmas4.mp3");
        ShowPlayerDialog(playerid,15536,DIALOG_STYLE_MSGBOX,"Kaledu Eglute", "\
                {FFFFFF}LSG sveikina tave su Ðv. Kalëdom!\n\n\n\n\
                {95d7f0}Linkime paèiø graþiausiø ir ðilèiausiø ðvenèiø ir dþiaugiamës, kad jas minite kartu su mumis!\n\
                Turime jums dovanø, taèiau prieð tai turësite ávykdyti vienà maþà uþduotá!", "Gerai", "Atsaukti");
    }
	else if(id == 1)
    {
		new msg[2048];
		format(msg,2048,"\
			{FFFFFF}Kalëdø Senelá pasiekë gandai, jog Los Santos mieste trûksta Kalëdiniø egluèiø!\n\
			Jis be galo norëtø jas visas pastatyti, taèiau per ðventiná laikotarpá jis tam neturi laiko...\n\n\n\n\
			{95d7f0}Tavo uþduotis: {FFFFFF}stilingai pristatyk á Los Santos miestà dar vienà Kalëdinæ eglutæ!\n\n\n\
			Pirmas þingsnis - pasiimk stilingà automobilá.\nÞemelapyje paþymëtoje vietoje rasi Kalëdø senelio palikta transportà.\n\
			Tolimesnius þingsnius rasi automobilio viduje.\n");

		ShowPlayerDialog(playerid,15532,DIALOG_STYLE_MSGBOX,"Kaledu Eglute", msg, "Gerai", "Atsaukti");
		SetPlayerCheckpoint(playerid, 682.9197,-441.9109,15.9950,6.0);
		SetPVarInt(playerid,"Kaledos2025", 1);
		//SendClientMessage(playerid, -1, "Ivyko klaida!!!");
	}
	else if(id == 2)
	{
		// do nothing, dialog response from above
	}
	else if(id == 3)
	{
		if(GetPVarInt(playerid, "Kaledos2025kvs") == 0)
		{
			ShowPlayerDialog(playerid,15532,DIALOG_STYLE_MSGBOX,"Kalëdø misija", "{A9C4E4}Radai Kalëdø senelio automobilá!\n\n\
			Automobilio daiktinëje radai {107eb1}5.000€{A9C4E4} bei raðtelá:\n\n\n\
			Matau automobilá jau suradai, taèiau prieð pristatant eglutæ, reikia já papuoðti Kalëdoms!\n\n\
			{FFFFFF}Nuvaþiuok á automobiliø tiuningà ir uþdëk ant automobilio {FF0000}bent tris modifikacijas{FFFFFF}.\n\
			Tiuningo vietà paþymëjau tavo GPS.", "Gerai", "Atsaukti");
			SetPlayerKVS(playerid, "Kaledos2025kvs", "1");
			SetPVarInt(playerid, "Kaledos2025kvs", 1);
			GivePlayerMoneyA(playerid, 5000);
		}
		else
		{
			ShowPlayerDialog(playerid,15532,DIALOG_STYLE_MSGBOX,"Kalëdø misija", "Radai Kalëdø senelio automobilá!\n\n\
			Automobilio daiktinëje radai raðtelá:\n\n\n\
			Matau automobilá jau suradai, taèiau prieð pristatant eglutæ, reikia já papuoðti Kalëdoms!\n\n\
			{FFFFFF}Nuvaþiuok á automobiliø tiuningà ir uþdëk ant automobilio {FF0000}bent tris modifikacijas{FFFFFF}.\n\
			Tiuningo vietà paþymëjau tavo GPS.", "Gerai", "Atsaukti");
		}
		SetPlayerCheckpoint(playerid, -2711.8806,216.5502,3.8764,6.0);
	}
	else if(id == 4)
	{
		ShowPlayerDialog(playerid,15532,DIALOG_STYLE_MSGBOX,"Kalëdø misija", "Toliau skaitai Kalëdø senelio raðtelá...\n\n\n\
		Tiuningas jau yra, bet automobilis vis dar neslysta.\n\n\
		Tau reikia nuvaþiuoti á drift garaþà ir ásidëti drift paketà.\n\
		{FFFFFF}Garaþo vietà paþymëjau tavo GPS.", "Gerai", "Atsaukti");
		SetPlayerCheckpoint(playerid, 1975.4083,2162.5107,10.7271,6.0);
		SetPVarInt(playerid, "Kaledos2025", 2);
	}
	else if(id == 5)
	{
		if(!GetPlayerVehicleID(playerid))
			return 1;
		StartDrift(playerid);
		new veh = GetPlayerVehicleID(playerid);
		AddVehicleComponent(veh,1010);
		LastNitro[veh]=GetTickCount();
		PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		CallRemoteFunction("EnableSniegas", "i", playerid);
		ShowPlayerDialog(playerid,15532,DIALOG_STYLE_MSGBOX,"Kalëdø misija", "Toliau skaitai Kalëdø senelio raðtelá...\n\n\n\
		Kol rinkaisi automobilio detales, Los Santos miestà uþpûstë didþiausia puga!\n\
		Tiuningas jau yra, drift pakuotë yra.. Dabar tu pasiruoðæs paimti Kalëdø eglutæ.\n\n\
		Vaþiuok á Los Santos miðkà ir nukirsk vienà eglutæ!\n\
		{FFFFFF}Miðko vietà paþymëjau tavo GPS.", "Gerai", "Atsaukti");
		SetPlayerCheckpoint(playerid, -566.4586,-176.7756,78.4063,4.0);
		SetPVarInt(playerid, "Kaledos2025", 3);
	}
	else if(id == 6)
	{
		GivePlayerWeaponEx(playerid,9,1);
		SetPlayerCheckpoint(playerid, -571.9276,-198.7326,78.6303,4.0);
		SetPVarInt(playerid, "Kaledos2025", 4);
		SendInfoMessage(playerid, "Nupjauk egle miske");
	}
	else if(id == 7)
	{
		SetPVarInt(playerid, "Kaledos2025", 5);
		DeletePlayerWeapon(playerid, 9);
		SendInfoMessage(playerid, "Grizk i automobili");
		new forplayerid = -1; // can set to playerid to reduce spam
		new Float:Coo[3];
		new vehid = PlayerCar[playerid];
		if(GetVehicleModel(vehid) != 562)
		{
			SendClientMessage(playerid, -1, "Ivyko klaida!");
			return 1;
		}
		GetPlayerPos(playerid, Coo[0], Coo[1], Coo[2]);
		new objid = CreateDynamicObject(779, Coo[0],Coo[1],Coo[2]+ 10.0, 0, 0, 0, -1, -1, forplayerid);
		AttachDynamicObjectToVehicle(objid, vehid, 0, -4, 0.9,270,0,0);
		SetPVarInt(playerid, "ChristmasTree", objid);
	}
	else if(id == 8)
	{
		SendInfoMessage(playerid, "Parvezk eglute i Los Santos!");
		SetPlayerCheckpoint(playerid, 84.1876,-1542.7083,5.4038,4.0);
	}
	else if(id == 9)
	{
		SetPVarInt(playerid, "Kaledos2025", 6);
		PlayAudioStreamForPlayer(playerid, "http://www.lsgyvenimas.lt/sounds/drift.mp3");
		ShowPlayerDialog(playerid,15532,DIALOG_STYLE_MSGBOX,"Kalëdø misija", "{FF0000} Tavo drift paketas uþminuotas!!!\n\n\n\
		{FFFFFF}Da Nang Boys gaujos nariai á tavo drift paketà ámontavo bombà.\n\n\
		Vienintelis bûdas jà iðminuoti - surinkti 1,000,000 DRIFT taðkø.\n\n\
		Bombos laikas bus pristabdytas {107eb1}greitai vaþiuojant {FFFFFF}arba junginëjant {107eb1}NOS{FFFFFF}(MOUSE1).", "Gerai", "Atsaukti");
		AddChristmasBomb(playerid);
		StartDrift(playerid);
	}
	else if(id == 10)
	{
		SetPVarInt(playerid, "Kaledos2025", 7);
		StopAudioStreamForPlayer(playerid);
		ShowPlayerDialog(playerid,15532,DIALOG_STYLE_MSGBOX,"Kalëdø misija", "{00FF00} Bomba isminuota!\n\n\n\
		{FFFFFF}Dabar gali pristatyti eglute kaledu seneliui!", "Gerai", "Atsaukti");
		SetPlayerCheckpoint(playerid, 963.7131,-2481.4651,55.2993,4.0);
		EndChristmasBomb(playerid);
	}
	else if(id == 11)
	{
		new pcar = PlayerCar[playerid];
		if(GetVehicleModel(pcar) != 562)
		{
			SendClientMessage(playerid, -1, "Ivyko klaida!");
			return 1;
		}
		new Float:pos[3];
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		new Float:dist = GetVehicleDistanceFromPoint(pcar, pos[0], pos[1], pos[2]);
		if(dist > 20.0)
		{
			SendClientMessage(playerid, -1, "Tavo masina per toli!");
			return 1;
		}
		ShowPlayerDialog(playerid,15532,DIALOG_STYLE_MSGBOX,"Kalëdø misija", "{FF0000} Sekmingai pristatei seneliui Kalëdø eglutæ!!!\n\n\n\
		{FFFFFF}Uþ tavo pastangas Kalëdø senelis tau dovanoja:\n\
		{107eb1}- Chainsaw\n\
		- VIP 30 dienø\n\
		- 20.000€\n\n\n\
		{FFFFFF}Dëkojame uþ dalyvavimà LSG Kalëdø evente.\n\
		LSG komanda linki jums ðilèiausiø ðv. Kalëdø ir nuostabiø Naujøjø metø!", "Aèiû", "");
		SetPlayerKVS(playerid, "Kaledos2025kvs", "2");
		SetPVarInt(playerid, "Kaledos2025kvs", 2);
		SetPVarInt(playerid, "Kaledos2025", 0);
		GivePrize2025(playerid);
		DestroyChristmasTree(playerid);
	}
    else
    {
        SendClientMessage(playerid, -1, "Ivyko klaida!");
    }
    return 1;
}
stock StartDrift(playerid)
{
	DriftPoints[playerid]=0;
	LastAngle[playerid]=0;
	DriftBonus[playerid]=0;
	g_DriftPlayers[playerid][driftState] = DRIFT_STATE_NONE;
	g_DriftPlayers[playerid][timeoutTicks] = 0;
	Iter_Add(PlayersDrifting, playerid);
}
stock AddChristmasBomb(playerid)
{
	SetProgressBarMaxValue(Veiksmai, 150);
	SetProgressBarValue(Veiksmai,0);
	ShowProgressBarForPlayer(playerid, Veiksmai);
	StartVeiksmas(playerid,"Bomba");
	SetPVarInt(playerid,"ChristmasBomb", 10);
}
stock EndChristmasBomb(playerid)
{
	EndVeiksmas(playerid);
	SetPVarInt(playerid, "ChristmasBomb", 0);
}

stock ChristmasHandleVehicleDeath(playerid,vehicleid, model)
{
	#pragma unused vehicleid
	new pstate = GetPVarInt(playerid, "Kaledos2025");
	if(model != 562)
		return;
	if(pstate < 2)
		return;
	if(pstate == 2 || pstate == 3 || pstate == 4)
	{
		SetPVarInt(playerid,"Kaledos2025", 1);
		return;
	}
	if(pstate == 5 || pstate == 6 || pstate == 7)
	{
		SetPVarInt(playerid, "Kaledos2025", 1);
		DestroyChristmasTree(playerid);
		return;
	}
}

forward ChristmasTimer();
public ChristmasTimer()
{
	foreach(Player, i)
	{
		new bomb = GetPVarInt(i, "ChristmasBomb");
		if(!bomb)
			continue;
		if(GetPlayerDialogID(i) == 15532)
			continue;
		if(DriftPoints[i] > 1000000)
			continue;
		new speed_decrease = min(GetSpeed(i) / 20, 3);
		new delta = 5 - speed_decrease;
		bomb += delta;
		if(bomb >=150)
		{
			BlowChristmasBomb(i);
			continue;
		}
		SetPVarInt(i, "ChristmasBomb", bomb);
		SetProgressBarValue(Veiksmai, bomb);
		ShowProgressBarForPlayer(i, Veiksmai);
		new Float:VHP;
		new vehicleid = GetPlayerVehicleID(i);
		GetVehicleHealth(vehicleid, VHP);
		if(VHP <= 500)
		{
			SetVehicleHealth(vehicleid, 600);
		}
	}
}
stock ReduceChristmasBomb(playerid)
{
	new bomb = GetPVarInt(playerid, "ChristmasBomb");
	new delta = max(bomb / 10, 1);
	if(bomb > delta)
	{
		bomb -= delta;
		SetPVarInt(playerid, "ChristmasBomb", bomb);
		SetProgressBarValue(Veiksmai, bomb);
		ShowProgressBarForPlayer(playerid, Veiksmai);
	}
}
stock BlowChristmasBomb(playerid)
{
	new veh = GetPlayerVehicleID(playerid);
	SetVehicleHealth(veh, 0.0);
	SetPVarInt(playerid, "ChristmasBomb", 0);
	EndChristmasBomb(playerid);
	new Float:Pos[3];
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	CreateExplosion(Pos[0], Pos[1], Pos[2], 7, 10.0);
	CreateExplosion(Pos[0], Pos[1], Pos[2], 7, 10.0);
	CreateExplosion(Pos[0], Pos[1], Pos[2], 7, 10.0);
	SetPlayerHealth(playerid, 0.0);
	SetPlayerArmour(playerid, 0.0);
	ChristmasHandleVehicleDeath(playerid, PlayerCar[playerid], 562);
}

stock DestroyChristmasTree(playerid)
{
	new tree = GetPVarInt(playerid, "ChristmasTree");
	if(!tree)
		return;
	DestroyDynamicObject(tree);
	SetPVarInt(playerid, "ChristmasTree", 0);
}

stock GivePrize2025(playerid)
{
	GivePlayerMoneyA(playerid, 20000);
	GivePlayerWeaponEx(playerid, WEAPON_CHAINSAW, 1);
	playerDB[playerid][vip]=true;
	new query[256];
	format(query,sizeof(query),"UPDATE `Account` SET `Vip`=`Vip`+30 WHERE `Name` = '%s'",ReturnName(playerid));
	mysql_query(query);
}

stock EgleStatus(status)
{
	new str[24];
	if(status)
	{
		format(str,sizeof(str),"{00FF00}Yra");
	}
	else 
	{
		format(str,sizeof(str),"{FF0000}Nëra");
	}
	return str;
}
stock GiveChristmasHat(playerid)
{
	if(!InvalidCapSkin(GetPlayerSkin(playerid))) 
	{
		playerDB[playerid][kepure]=13;
		SetPlayerAttachedObject(playerid, CAP_SLOT, Kepures[playerDB[playerid][kepure]-1], 2, 0.120000, 0.040000, -0.003500, 0, 100, 100, 1.4, 1.4, 1.4);
	}
}
stock GiveChristmasPrize(playerid)
{
	GiveChristmasHat(playerid);
	if(playerDB[playerid][vip])
	{
		ShowPlayerDialog(playerid, 15531, DIALOG_STYLE_MSGBOX, "Kalëdø Senelis", "{FFFFFF}Aèiû uþ dalyvavimà mûsø Kalëdø evente!\n\n\
		Dovanø jums turime {d61135}30 dienø VIP{FFFFFF} ir {d61135}50.000€{FFFFFF}!\nNepamirðkite paskaityti VIP taisykliø, kadangi uþ jø paþeidimus bûsite grieþtai baudþiami!\n\n\
		{d61135}Linksmø ðv. Kalëdø ir Naujøjø metø jums linki visa LSG komanda!", "Gerai", "");
		GivePlayerMoneyA(playerid, 50000);
	}
	else
	{
		ShowPlayerDialog(playerid, 15531, DIALOG_STYLE_MSGBOX, "Kalëdø Senelis", "{FFFFFF}Aèiû uþ dalyvavimà mûsø Kalëdø evente!\n\n\
		Dovanø jums turime {d61135}30 dienø VIP{FFFFFF} ir {d61135}10.000€{FFFFFF}!\nNepamirðkite paskaityti VIP taisykliø, kadangi uþ jø paþeidimus bûsite grieþtai baudþiami!\n\n\
		{d61135}Linksmø ðv. Kalëdø ir Naujøjø metø jums linki visa LSG komanda!", "Gerai", "");
		GivePlayerMoneyA(playerid, 10000);
	}
	playerDB[playerid][vip]=true;
	new query[256];
	format(query,sizeof(query),"UPDATE `Account` SET `Vip`=`Vip`+30 WHERE `Name` = '%s'",ReturnName(playerid));
	mysql_query(query);
}

forward SQL_KaleduRace(playerid);
public SQL_KaleduRace(playerid)
{
    RestartCheck();
    new rows,cols;
    cache_get_data(rows, cols);
    new msg[4096];
    format(msg,4096, "{FFFFFF}Iveik Kaledø Senelio trasà per maþiau nei {ed2459}1:25{ffffff}!\n\n\
    Tam tau prireiks keturracio {ed2459}Quad{FFFFFF}, kuri gali pasiimti Mount Chiliad papëdëje.\n\n\n\n\
    {2e24ed}TOP SENELIAI:{FFFFFF}\n\n");
    for(new i=0;i<rows && i < 10;i++)
    {
        new name[24],time[24];
        cache_get_row(i, 0, name);
        cache_get_row(i, 2, time);
        format(msg,sizeof(msg),"%s%i.\t%s [{00ffee}%s{ffffff}]\n",msg, i+1,name, formatTimeString(strval(time)));
    }
    ShowPlayerDialog(playerid,15532,DIALOG_STYLE_MSGBOX,"Kaledu Eglute", msg, "Gerai", "Atsaukti");
    new id = 0;
    SetPlayerRaceCheckpoint(playerid, 1, QuadRace[id][0],QuadRace[id][1],QuadRace[id][2], QuadRace[id+1][0],QuadRace[id+1][1], QuadRace[id+1][2], 3.0);
}

stock KaleduShopas(playerid) 
{
   //new baldai[] = {2470, 2472, 2492, 2464, 2485, 2493, 2465, 2481, 2489, 2503, 2480, 2501, 2487, 11704, 954}; // 2023
   new baldai[] = {1609,1600,1736,1895,1985,1946,19128,918,19917,19609,19088}; // 2025
   new cat = 13;
   ShowModelSelectionMenuEx(playerid, baldai, sizeof(baldai), "Pasirinkite dovanas", GUI_BALDAI+cat, 340.0, 0.0, 180.0, 1.5,0xed87a2BB,0xed245999,0x88888899);
}



stock ChristmasStateChange(playerid, newstate, oldstate)
{
    #pragma unused oldstate
    new veh = GetPlayerVehicleID(playerid);
    if(newstate == PLAYER_STATE_DRIVER && GetVehicleModel(veh) == 562)
	{
		if(PlayerCar[playerid] != veh)
			return;
		new kaledos = GetPVarInt(playerid, "Kaledos2025");
		if(kaledos == 1)
			Kaledos(playerid, 3);
		else if (kaledos == 2)
			Kaledos(playerid, 4);
		else if(kaledos == 3 || kaledos == 4) // before or after picking up chainsaw
			Kaledos(playerid, 5);
		else if(kaledos == 5) // tree attached
			Kaledos(playerid, 8);
		else if(kaledos == 6) // bomb attached
		{
			BlowChristmasBomb(playerid);
		}
		
		
	}

}

stock IsChristmasEventCar(playerid)
{
	new veh = GetPlayerVehicleID(playerid);
	if(GetVehicleModel(veh) != 562)
		return 0;
	if(PlayerCar[playerid] != veh)
		return 0;
	if(GetPVarInt(playerid, "Kaledos2025") == 0)
		return 0;
	return 1;
}

CMD:kaledos(playerid,params[]) 
{
	new stata = GetPlayerState(playerid);
	new vehicleid = GetPlayerVehicleID(playerid);
	if(stata == PLAYER_STATE_DRIVER && (playerDB[playerid][specialybe]==5 || playerDB[playerid][specialybe]==55 || playerDB[playerid][specialybe]==62 || vagia[playerid] || vpakrauta[vehicleid]==1 || vbankomatams[vehicleid]==1) )
	{
		SendInfoMessage(playerid,"Prasome islipti is automobilio.");
		return 1;
	}
	SetPlayerCheckpoint(playerid,966.3466,-2489.4946,54.5054,6.0);
	SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten rasite Kaledu eventa.");
	return 1;		
}



stock ResetChristmas(playerid)
{
    DisablePlayerRaceCheckpoint(playerid);
    DisableRemoteVehicleCollisions(playerid, 0);
    kaleduRaceState[playerid] = 0;
    PlayerTextDrawDestroy(playerid, raceTimer[playerid]);
	raceTimer[playerid] = PlayerText:-1;
    new id = 0;
    SetPlayerRaceCheckpoint(playerid, 1, QuadRace[id][0],QuadRace[id][1],QuadRace[id][2], QuadRace[id+1][0],QuadRace[id+1][1], QuadRace[id+1][2], 3.0);
}


stock StartQuadRace(playerid)
{
    new vehid = GetPlayerVehicleID(playerid);
    if(GetVehicleModel(vehid) != 471)
    {
        return SendInfoMessage(playerid, "Sugrizk su Quad keturraciu!");
    }
    SetVehicleHealthEx(vehid, 2000.0);
    raceStart[playerid] = GetTickCount();
    kaleduRaceState[playerid] = 1;
    new id = 1;
    SetPlayerRaceCheckpoint(playerid, 0, QuadRace[id][0],QuadRace[id][1],QuadRace[id][2], QuadRace[id+1][0],QuadRace[id+1][1], QuadRace[id+1][2], 3.0);
    DisableRemoteVehicleCollisions(playerid, 1);
	raceTimer[playerid] = CreatePlayerTextDraw(playerid, 11.000000, 129.000000, "00:00.00");
	PlayerTextDrawBackgroundColor(playerid,raceTimer[playerid], 255);
	PlayerTextDrawFont(playerid,raceTimer[playerid], 2);
	PlayerTextDrawLetterSize(playerid,raceTimer[playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,raceTimer[playerid], -1);
	PlayerTextDrawSetOutline(playerid,raceTimer[playerid], 0);
	PlayerTextDrawSetProportional(playerid,raceTimer[playerid], 1);
	PlayerTextDrawSetShadow(playerid,raceTimer[playerid], 1);
    return 1;
}

stock ChristmasPlayerDisconnect(playerid)
{
	if(kaleduRaceState[playerid])
	{
		ResetChristmas(playerid);
	}
    kaleduRaceState[playerid] = 0;
}

stock KaleduRaceCP(playerid) 
{
    if(!kaleduRaceState[playerid])
    {
        if(IsPlayerInRangeOfPoint(playerid, 10.0, QuadRace[0][0], QuadRace[0][1],QuadRace[0][2]))
        {
            StartQuadRace(playerid);
        }
        
        return 0;
    }
    new vehid = GetPlayerVehicleID(playerid);
    if(GetVehicleModel(vehid) != 471)
    {
        return SendInfoMessage(playerid, "Sugrizk su Quad keturraciu!");
    }
    kaleduRaceState[playerid]++;
    new id = kaleduRaceState[playerid];
    if(id == sizeof(QuadRace))
    {
        EndChristmasEvent(playerid);
        ResetChristmas(playerid);
        return 1;
    }
    if(id == sizeof(QuadRace) - 1)
    {
        SetPlayerRaceCheckpoint(playerid, 1, QuadRace[id][0],QuadRace[id][1],QuadRace[id][2], 0.0, 0.0, 0.0, 3.0);
        return 1;
    }
    else
    {
        SetPlayerRaceCheckpoint(playerid, 0, QuadRace[id][0],QuadRace[id][1],QuadRace[id][2], QuadRace[id+1][0],QuadRace[id+1][1], QuadRace[id+1][2], 3.0);
        return 1;
    }
}

stock EndChristmasEvent(playerid)
{
    new time = GetTickCount() - raceStart[playerid];
    
    if(time >= 85 * 1000)
    {
        SendInfoMessage(playerid, "~r~Bandyk dar karta!");
        return;
    }
    if(GetPVarInt(playerid, "Kaledos2023") == 0)
    {
        SetPVarInt(playerid, "Kaledos2023", 1);
    }
    new last = GetPVarInt(playerid, "Race2023");

    new msg[256];
    
    if(last > time) 
    {
        format(msg,256,"Trasa iveikei per ~g~%s~w~!~n~Naujas rekordas!", formatTimeString(time));
    }
    else
    {
        format(msg,256,"Trasa iveikei per ~g~%s~w~!", formatTimeString(time));
    }
    SendInfoMessage(playerid, msg);

    
    if(last != 0 && last < time) 
        return;
    SetPVarInt(playerid, "Race2023", time);

    new timestr[24];
    format(timestr,24,"%i",time);
    SetPlayerKVS(playerid, "Race2023", timestr);

}

stock formatTimeString(ms)
{
    new msg[25];
    new minutes = ms / 1000 / 60;
    new seconds = (ms / 1000) % 60;
    new tenths = (ms % 1000) / 100;
    format(msg,25,"%02d:%02d.%d", minutes, seconds, tenths);
    return msg;
}

stock raceUpdate(playerid)
{
    if(!kaleduRaceState[playerid]) 
    {
        return;
    }
    new tick = GetTickCount();
    if(tick - lastRaceUpdate[playerid] < 100) 
    {
        return;
    }
    lastRaceUpdate[playerid] = tick;
    new duration = tick - raceStart[playerid];

    PlayerTextDrawSetString(playerid, raceTimer[playerid], formatTimeString(duration));
    PlayerTextDrawShow(playerid, raceTimer[playerid]);

    if(duration > 3 * 60 * 1000)
    {
        SendInfoMessage(playerid, "~r~Nespejai laiku pabaigti evento!");
        ResetChristmas(playerid);
    }
}

stock initChristmasMountain() // 2023 and 2025
{
    SafeZone[23] = CreateDynamicCube(771.8580,-2607.1367,1,1068.8651,-2317.0579,200);

    pickups[0][dovana]=CreatePickupA(19135, 2, 966.3466,-2489.4946,54.5054);
    CreateDynamic3DTextLabel("Los Santos\n{e299ff}Kalëdø Eglutë",COLOR_WHITE, 966.3466,-2489.4946,55.3054,50,_,_,1);
    CreateDynamicMapIcon(966.3466,-2489.4946,54.5054, 12, 0,_,_,_,_,MAPICON_LOCAL); // pink C icon

    pickups[0][kaledushop]=CreatePickupA(1274, 2, 934.3618,-2443.5767,54.6159);

    pickups[0][kaledugerimai]=CreatePickupA(1274, 2, 962.5444,-2410.9314,55.9259);


    CreateDynamicObject(691, 1182.21, -2327.56, 12.63,   356.86, 0.00, -2.53);
	CreateDynamicObject(4241, 720.71, -2612.76, -5.53,   0.00, 0.00, 1.85);
	CreateDynamicObject(4241, 708.51, -2235.06, -5.53,   0.00, 0.00, 1.85);
	CreateDynamicObject(4241, 717.58, -2515.97, -5.51,   0.00, 0.00, 1.85);
	CreateDynamicObject(4241, 1119.68, -2599.83, -5.53,   0.00, 0.00, 1.85);
	CreateDynamicObject(4241, 920.16, -2606.30, -5.53,   0.00, 0.00, 1.85);
	CreateDynamicObject(664, 970.34, -2495.42, 54.12,   0.00, 0.00, 0.00);
	CreateDynamicObject(664, 970.34, -2495.42, 54.12,   0.00, 0.00, 81.30);
	CreateDynamicObject(664, 970.34, -2495.42, 54.12,   0.00, 0.00, 44.82);
	CreateDynamicObject(4241, 711.17, -2317.59, -5.51,   0.00, 0.00, 1.85);
	CreateDynamicObject(4241, 904.70, -2131.18, -104.79,   90.00, 0.00, 181.53);
	CreateDynamicObject(4241, 908.02, -2228.66, -5.53,   0.00, 0.00, 1.85);
	CreateDynamicObject(4241, 705.35, -2136.50, -104.79,   90.00, 0.00, 181.53);
	CreateDynamicObject(4241, 608.89, -2238.93, -104.80,   90.00, 0.00, 271.85);
	CreateDynamicObject(4241, 615.32, -2437.69, -104.74,   90.00, 0.00, 271.85);
	CreateDynamicObject(4241, 621.02, -2615.40, -104.74,   90.00, 0.00, 271.85);
	CreateDynamicObject(4241, 922.72, -2704.52, -104.79,   90.00, 0.00, 2.01);
	CreateDynamicObject(4241, 723.94, -2711.50, -104.75,   90.00, 0.00, 2.01);
	CreateDynamicObject(4241, 1122.13, -2697.52, -104.79,   90.00, 0.00, 2.01);
	CreateDynamicObject(4241, 1123.96, -2698.75, -104.79,   90.00, 0.00, 1.35);
	CreateDynamicObject(970, 897.79, -2425.52, 54.14,   0.00, 0.00, 52.95);
	CreateDynamicObject(970, 885.36, -2442.08, 54.14,   0.00, 0.00, 54.68);
	CreateDynamicObject(970, 895.29, -2428.83, 54.14,   0.00, 0.00, 52.95);
	CreateDynamicObject(970, 892.79, -2432.13, 54.14,   0.00, 0.00, 52.95);
	CreateDynamicObject(970, 890.28, -2435.44, 54.14,   0.00, 0.00, 52.95);
	CreateDynamicObject(970, 887.78, -2438.74, 54.14,   0.00, 0.00, 52.95);
	CreateDynamicObject(970, 878.09, -2452.16, 54.14,   0.00, 0.00, 53.96);
	CreateDynamicObject(970, 882.96, -2445.45, 54.14,   0.00, 0.00, 53.96);
	CreateDynamicObject(970, 880.53, -2448.81, 54.14,   0.00, 0.00, 53.96);
	CreateDynamicObject(970, 875.68, -2455.46, 54.14,   0.00, 0.00, 53.96);
	CreateDynamicObject(970, 873.76, -2461.59, 54.14,   0.00, 0.00, 325.46);
	CreateDynamicObject(970, 873.35, -2458.70, 54.14,   0.00, 0.00, 53.96);
	CreateDynamicObject(970, 880.59, -2466.25, 54.14,   0.00, 0.00, 325.87);
	CreateDynamicObject(970, 877.18, -2463.93, 54.14,   0.00, 0.00, 325.87);
	CreateDynamicObject(970, 887.45, -2470.93, 54.14,   0.00, 0.00, 325.87);
	CreateDynamicObject(970, 884.03, -2468.60, 54.14,   0.00, 0.00, 325.87);
	CreateDynamicObject(970, 890.85, -2473.24, 54.14,   0.00, 0.00, 325.87);
	CreateDynamicObject(970, 894.27, -2475.55, 54.14,   0.00, 0.00, 325.87);
	CreateDynamicObject(970, 897.67, -2477.88, 54.14,   0.00, 0.00, 325.87);
	CreateDynamicObject(970, 901.09, -2480.21, 54.14,   0.00, 0.00, 325.87);
	CreateDynamicObject(970, 904.53, -2482.53, 54.14,   0.00, 0.00, 325.87);
	CreateDynamicObject(970, 907.95, -2484.84, 54.14,   0.00, 0.00, 325.87);
	CreateDynamicObject(970, 911.37, -2487.18, 54.14,   0.00, 0.00, 325.87);
	CreateDynamicObject(970, 914.80, -2489.52, 54.14,   0.00, 0.00, 325.87);
	CreateDynamicObject(970, 918.20, -2491.82, 54.14,   0.00, 0.00, 325.87);
	CreateDynamicObject(970, 949.82, -2452.92, 54.14,   0.00, 0.00, 10.67);
	CreateDynamicObject(970, 934.15, -2480.01, 54.14,   0.00, 0.00, 55.89);
	CreateDynamicObject(970, 921.99, -2494.41, 54.14,   0.00, 0.00, 325.87);
	CreateDynamicObject(970, 924.87, -2493.84, 54.14,   0.00, 0.00, 56.40);
	CreateDynamicObject(970, 927.18, -2490.38, 54.14,   0.00, 0.00, 56.40);
	CreateDynamicObject(970, 929.48, -2486.90, 54.14,   0.00, 0.00, 56.40);
	CreateDynamicObject(970, 931.81, -2483.48, 54.14,   0.00, 0.00, 55.89);
	CreateDynamicObject(970, 936.39, -2476.76, 54.14,   0.00, 0.00, 55.89);
	CreateDynamicObject(970, 935.81, -2473.84, 54.14,   0.00, 0.00, 144.88);
	CreateDynamicObject(970, 901.65, -2450.31, 54.14,   0.00, 0.00, 145.27);
	CreateDynamicObject(970, 932.45, -2471.45, 54.14,   0.00, 0.00, 144.15);
	CreateDynamicObject(970, 929.08, -2469.05, 54.14,   0.00, 0.00, 144.97);
	CreateDynamicObject(970, 925.66, -2466.67, 54.14,   0.00, 0.00, 145.48);
	CreateDynamicObject(970, 922.24, -2464.35, 54.14,   0.00, 0.00, 145.88);
	CreateDynamicObject(970, 918.82, -2462.02, 54.14,   0.00, 0.00, 145.88);
	CreateDynamicObject(970, 915.37, -2459.68, 54.14,   0.00, 0.00, 145.88);
	CreateDynamicObject(970, 911.91, -2457.34, 54.14,   0.00, 0.00, 145.88);
	CreateDynamicObject(970, 908.47, -2455.00, 54.14,   0.00, 0.00, 145.88);
	CreateDynamicObject(970, 905.07, -2452.67, 54.14,   0.00, 0.00, 145.27);
	CreateDynamicObject(19377, 941.40, -2449.65, 57.03,   0.00, 90.00, 10.16);
	CreateDynamicObject(19377, 931.13, -2451.49, 57.03,   0.00, 90.00, 10.16);
	CreateDynamicObject(19377, 930.15, -2445.99, 57.01,   0.00, 90.00, 10.16);
	CreateDynamicObject(19377, 940.41, -2444.14, 57.01,   0.00, 90.00, 10.16);
	CreateDynamicObject(970, 921.65, -2494.18, 54.14,   0.00, 0.00, 325.87);
	CreateDynamicObject(970, 958.83, -2444.91, 54.14,   0.00, 0.00, 100.84);
	CreateDynamicObject(970, 953.90, -2452.15, 54.14,   0.00, 0.00, 10.67);
	CreateDynamicObject(970, 957.97, -2451.38, 54.14,   0.00, 0.00, 10.67);
	CreateDynamicObject(970, 959.60, -2448.96, 54.14,   0.00, 0.00, 100.84);
	CreateDynamicObject(970, 958.05, -2440.83, 54.14,   0.00, 0.00, 100.84);
	CreateDynamicObject(970, 957.50, -2437.94, 54.14,   0.00, 0.00, 100.84);
	CreateObject(18259, 961.27, -2413.14, 54.84,   0.00, 0.00, 96.55); // for npc
	CreateDynamicObject(970, 920.79, -2419.20, 54.14,   0.00, 0.00, 10.81);
	CreateDynamicObject(970, 924.84, -2418.42, 54.14,   0.00, 0.00, 10.81);
	CreateDynamicObject(970, 928.91, -2417.64, 54.14,   0.00, 0.00, 10.81);
	CreateDynamicObject(970, 932.99, -2416.86, 54.14,   0.00, 0.00, 10.81);
	CreateDynamicObject(970, 937.08, -2416.08, 54.14,   0.00, 0.00, 10.81);
	CreateDynamicObject(970, 941.14, -2415.30, 54.14,   0.00, 0.00, 10.81);
	CreateDynamicObject(970, 945.22, -2414.52, 54.14,   0.00, 0.00, 10.81);
	CreateDynamicObject(970, 949.29, -2413.75, 54.14,   0.00, 0.00, 10.81);
	CreateDynamicObject(970, 953.42, -2412.91, 54.14,   0.00, 0.00, 10.81);
	CreateDynamicObject(19121, 1019.36, -2321.98, 12.64,   0.00, 0.00, 0.00);
	CreateDynamicObject(19121, 1025.55, -2338.17, 12.64,   0.00, 0.00, 0.00);
	CreateDynamicObject(19122, 992.41, -2313.31, 16.98,   0.00, 0.00, 0.00);
	CreateDynamicObject(19122, 982.36, -2321.85, 16.98,   0.00, 0.00, 0.00);
	CreateDynamicObject(19123, 951.10, -2259.58, 25.09,   0.00, 0.00, 0.00);
	CreateDynamicObject(19123, 940.46, -2267.14, 25.09,   0.00, 0.00, 0.00);
	CreateDynamicObject(19124, 909.12, -2218.38, 30.19,   0.00, 0.00, 0.00);
	CreateDynamicObject(19124, 905.54, -2230.74, 30.19,   0.00, 0.00, 0.00);
	CreateDynamicObject(19125, 905.92, -2271.22, 34.35,   0.00, 0.00, 0.00);
	CreateDynamicObject(19125, 915.80, -2263.08, 34.09,   0.00, 0.00, 0.00);
	CreateDynamicObject(19126, 963.95, -2342.28, 39.77,   0.00, 0.00, 0.00);
	CreateDynamicObject(19126, 974.63, -2335.25, 39.61,   0.00, 0.00, 0.00);
	CreateDynamicObject(19127, 943.68, -2350.13, 44.27,   0.00, 0.00, 0.00);
	CreateDynamicObject(19127, 933.29, -2358.06, 44.27,   0.00, 0.00, 0.00);
	CreateDynamicObject(19121, 916.53, -2314.67, 49.03,   0.00, 0.00, 0.00);
	CreateDynamicObject(19121, 905.57, -2321.78, 49.03,   0.00, 0.00, 0.00);
	CreateDynamicObject(19122, 878.98, -2337.24, 51.08,   0.00, 0.00, 0.00);
	CreateDynamicObject(19122, 891.38, -2335.03, 51.08,   0.00, 0.00, 0.00);
	CreateDynamicObject(19123, 900.79, -2418.87, 54.14,   0.00, 0.00, 0.00);
	CreateDynamicObject(19123, 914.28, -2416.26, 54.14,   0.00, 0.00, 0.00);
	CreateDynamicObject(790, 963.54, -2238.94, 12.07,   0.00, 0.00, 0.00);
	CreateDynamicObject(790, 977.89, -2378.56, 43.44,   0.00, 0.00, 0.00);
	CreateDynamicObject(791, 829.45, -2246.00, 10.95,   0.00, 0.00, 291.56);
	CreateDynamicObject(791, 798.22, -2342.24, 32.69,   0.00, 0.00, 20.29);
	CreateDynamicObject(791, 881.08, -2269.44, 31.84,   0.00, 0.00, 323.71);
	CreateDynamicObject(791, 896.21, -2510.59, 37.04,   0.00, 0.00, 213.67);
	CreateDynamicObject(791, 940.63, -2387.67, 32.69,   0.00, 0.00, 324.59);
	CreateDynamicObject(791, 847.75, -2364.12, 32.69,   0.00, 0.00, 108.90);
	CreateDynamicObject(721, 973.64, -2331.76, -5.97,   0.00, 0.00, 143.53);
	CreateDynamicObject(721, 996.06, -2307.31, -34.70,   0.00, 0.00, 133.65);
	CreateDynamicObject(790, 1014.86, -2461.25, 51.04,   0.00, 0.00, 189.54);
	CreateDynamicObject(721, 954.94, -2348.01, -0.48,   0.00, 0.00, 164.90);
	CreateDynamicObject(726, 941.86, -2240.40, 26.84,   0.00, 0.00, 175.82);
	CreateDynamicObject(726, 868.61, -2334.31, 49.04,   0.00, 0.00, 22.72);
	CreateDynamicObject(726, 950.71, -2297.50, 35.59,   0.00, 0.00, 70.02);
	CreateDynamicObject(726, 1029.07, -2342.84, 12.33,   0.00, 0.00, 323.94);
	CreateDynamicObject(790, 988.07, -2281.68, 12.07,   0.00, 0.00, 0.00);
	CreateDynamicObject(726, 1012.33, -2323.40, 12.33,   0.00, 0.00, 50.12);
	CreateDynamicObject(722, 1049.02, -2396.82, 12.06,   0.00, 0.00, 0.00);
	CreateDynamicObject(791, 1015.47, -2366.72, 11.05,   0.00, 0.00, 21.48);
	CreateDynamicObject(791, 1031.82, -2531.04, 9.71,   0.00, 0.00, 20.14);
	CreateDynamicObject(791, 1013.69, -2503.25, 35.09,   0.00, 0.00, 175.88);
	CreateDynamicObject(790, 921.04, -2295.45, 40.52,   0.00, 0.00, 291.56);
	CreateDynamicObject(790, 997.32, -2415.85, 48.84,   0.00, 0.00, 78.68);
	CreateDynamicObject(790, 810.01, -2406.34, 51.04,   0.00, 0.00, 176.31);
	CreateDynamicObject(790, 859.67, -2461.98, 51.04,   0.00, 0.00, 57.68);
	CreateDynamicObject(790, 875.02, -2382.50, 51.04,   0.00, 0.00, 57.68);
	CreateDynamicObject(791, 1053.90, -2443.22, 9.71,   0.00, 0.00, 78.37);
	CreateDynamicObject(790, 845.43, -2494.40, 47.99,   0.00, 0.00, 217.44);
	CreateDynamicObject(790, 939.36, -2528.09, 51.04,   0.00, 0.00, 114.17);
	CreateDynamicObject(790, 976.50, -2545.09, 51.04,   0.00, 0.00, 189.54);
	CreateDynamicObject(726, 899.43, -2324.02, 49.04,   0.00, 0.00, 22.72);
	CreateDynamicObject(721, 967.05, -2271.86, -17.78,   0.00, 0.00, 185.58);
	CreateDynamicObject(721, 922.83, -2215.88, -6.99,   0.00, 0.00, 233.87);
	CreateDynamicObject(726, 907.25, -2237.79, 30.88,   0.00, 0.00, 165.31);
	CreateDynamicObject(790, 918.16, -2350.71, 43.44,   0.00, 0.00, 0.00);
	CreateDynamicObject(790, 938.94, -2316.27, 43.44,   0.00, 0.00, 0.00);
	CreateDynamicObject(791, 859.36, -2299.79, 38.46,   0.00, 0.00, 0.00);
	CreateDynamicObject(721, 937.05, -2282.77, -5.97,   0.00, 0.00, 239.60);
	CreateDynamicObject(721, 921.74, -2251.57, -5.97,   0.00, 0.00, 284.42);
	CreateDynamicObject(790, 830.49, -2466.31, 51.04,   0.00, 0.00, 176.31);
	CreateDynamicObject(791, 862.21, -2425.17, 32.69,   0.00, 0.00, 20.29);
	CreateDynamicObject(2412, 925.21, -2442.17, 53.59,   0.00, 0.00, 12.50);
	CreateDynamicObject(2412, 944.75, -2439.53, 53.59,   0.00, 0.00, 280.63);
	CreateDynamicObject(2460, 928.36, -2454.38, 53.53,   0.00, 0.00, 191.47);
	CreateDynamicObject(2414, 927.25, -2456.51, 53.57,   0.00, 0.00, 100.61);
	CreateDynamicObject(2626, 929.81, -2454.01, 54.10,   0.00, 0.00, 190.31);
	CreateDynamicObject(2475, 944.76, -2453.78, 53.58,   0.00, 0.00, 189.82);
	CreateDynamicObject(2475, 934.93, -2455.48, 53.58,   0.00, 0.00, 189.82);
	CreateDynamicObject(14558, 947.28, -2452.44, 54.36,   0.00, 0.00, 280.04);
	CreateDynamicObject(2475, 933.46, -2455.74, 53.58,   0.00, 0.00, 189.82);
	CreateDynamicObject(2475, 946.22, -2453.52, 53.58,   0.00, 0.00, 189.82);
	CreateDynamicObject(2475, 947.13, -2452.37, 53.58,   0.00, 0.00, 280.53);
	CreateDynamicObject(2475, 946.86, -2450.91, 53.58,   0.00, 0.00, 280.53);
	CreateDynamicObject(2509, 940.71, -2454.53, 54.90,   0.00, 0.00, 190.11);
	CreateDynamicObject(2503, 937.18, -2455.04, 55.22,   0.00, 0.00, 190.06);
	CreateDynamicObject(2503, 936.40, -2455.20, 55.22,   0.00, 0.00, 190.06);
	CreateDynamicObject(2507, 936.84, -2455.38, 55.03,   0.00, 0.00, 10.97);
	CreateDynamicObject(2509, 936.78, -2455.22, 54.90,   0.00, 0.00, 190.21);
	CreateDynamicObject(2493, 939.08, -2454.75, 54.92,   0.00, 0.00, 190.09);
	CreateDynamicObject(2493, 943.01, -2444.03, 54.52,   0.00, 0.00, 190.99);
	CreateDynamicObject(2509, 938.78, -2454.89, 54.90,   0.00, 0.00, 190.11);
	CreateDynamicObject(2492, 937.13, -2447.32, 54.51,   0.00, 0.00, 11.16);
	CreateDynamicObject(2489, 944.36, -2453.76, 55.23,   0.00, 0.00, 189.68);
	CreateDynamicObject(2481, 946.18, -2448.68, 53.90,   0.00, 0.00, 280.24);
	CreateDynamicObject(2484, 934.24, -2447.74, 55.60,   0.00, 0.00, 10.37);
	CreateDynamicObject(2460, 933.59, -2447.76, 53.68,   0.00, 0.00, 11.27);
	CreateDynamicObject(2465, 934.53, -2455.55, 55.32,   0.00, 0.00, 183.62);
	CreateDynamicObject(2485, 934.31, -2447.65, 53.98,   0.00, 0.00, 135.18);
	CreateDynamicObject(2485, 934.79, -2455.27, 53.77,   0.00, 0.00, 313.71);
	CreateDynamicObject(2490, 933.51, -2455.63, 54.51,   0.00, 0.00, 189.51);
	CreateDynamicObject(2460, 931.26, -2448.20, 53.68,   0.00, 0.00, 10.77);
	CreateDynamicObject(2464, 931.75, -2448.10, 54.92,   0.00, 0.00, 0.00);
	CreateDynamicObject(2491, 943.25, -2444.01, 53.55,   0.00, 0.00, 11.04);
	CreateDynamicObject(2491, 929.62, -2448.05, 53.55,   0.00, 0.00, 12.61);
	CreateDynamicObject(2460, 939.26, -2446.59, 53.68,   0.00, 0.00, 12.16);
	CreateDynamicObject(2493, 943.09, -2444.57, 54.51,   0.00, 0.00, 10.80);
	CreateDynamicObject(2492, 940.35, -2454.54, 54.93,   0.00, 0.00, 190.26);
	CreateDynamicObject(2492, 943.29, -2444.25, 54.51,   0.00, 0.00, 100.83);
	CreateDynamicObject(18092, 934.24, -2442.53, 54.09,   0.00, 0.00, 190.26);
	CreateDynamicObject(1491, 931.55, -2440.90, 52.07,   0.00, 0.00, 281.40);
	CreateDynamicObject(1491, 936.13, -2440.12, 52.07,   0.00, 0.00, 280.63);
	CreateDynamicObject(2492, 940.99, -2454.43, 54.93,   0.00, 0.00, 190.26);
	CreateDynamicObject(2493, 938.45, -2454.86, 54.92,   0.00, 0.00, 190.09);
	CreateDynamicObject(2475, 946.39, -2448.47, 53.58,   0.00, 0.00, 280.53);
	CreateDynamicObject(2489, 934.31, -2455.48, 54.52,   0.00, 0.00, 189.68);
	CreateDynamicObject(2490, 947.10, -2452.78, 55.20,   0.00, 0.00, 280.43);
	CreateDynamicObject(2489, 946.13, -2447.80, 53.85,   0.00, 0.00, 278.99);
	CreateDynamicObject(2489, 944.99, -2453.64, 55.23,   0.00, 0.00, 189.68);
	CreateDynamicObject(2489, 945.61, -2453.52, 55.23,   0.00, 0.00, 189.68);
	CreateDynamicObject(2489, 946.26, -2453.42, 55.23,   0.00, 0.00, 189.68);
	CreateDynamicObject(2490, 932.86, -2455.73, 54.51,   0.00, 0.00, 189.51);
	CreateDynamicObject(2490, 947.00, -2452.18, 55.20,   0.00, 0.00, 280.43);
	CreateDynamicObject(2490, 946.88, -2451.58, 55.20,   0.00, 0.00, 280.43);
	CreateDynamicObject(2490, 946.77, -2450.97, 55.20,   0.00, 0.00, 280.43);
	CreateDynamicObject(2480, 946.14, -2447.25, 54.98,   0.00, 0.00, 276.34);
	CreateDynamicObject(2475, 946.12, -2447.00, 53.58,   0.00, 0.00, 280.53);
	CreateDynamicObject(2491, 937.27, -2446.80, 53.55,   0.00, 0.00, 11.04);
	CreateDynamicObject(2492, 937.04, -2446.81, 54.51,   0.00, 0.00, 192.91);
	CreateDynamicObject(2492, 942.81, -2444.35, 54.51,   0.00, 0.00, 281.45);
	CreateDynamicObject(2493, 929.38, -2448.08, 54.52,   0.00, 0.00, 192.78);
	CreateDynamicObject(2493, 929.49, -2448.57, 54.51,   0.00, 0.00, 12.72);
	CreateDynamicObject(2472, 939.78, -2446.15, 54.76,   0.00, 0.00, 0.00);
	CreateDynamicObject(2470, 937.03, -2447.25, 55.42,   0.00, 0.00, 59.67);
	CreateDynamicObject(2470, 929.44, -2448.28, 55.42,   0.00, 0.00, 211.85);
	CreateDynamicObject(2412, 926.94, -2441.87, 53.59,   0.00, 0.00, 12.50);
	CreateDynamicObject(2412, 945.07, -2441.27, 53.59,   0.00, 0.00, 280.63);
	CreateDynamicObject(18868, 939.07, -2446.77, 53.93,   0.00, 0.00, 10.44);
	CreateDynamicObject(18868, 940.37, -2446.46, 53.93,   0.00, 0.00, 10.44);
	CreateDynamicObject(18865, 940.61, -2446.35, 53.92,   0.00, 0.00, 10.47);
	CreateDynamicObject(18865, 939.29, -2446.73, 53.92,   0.00, 0.00, 10.47);
	CreateDynamicObject(18866, 940.23, -2446.47, 53.93,   0.00, 0.00, 11.65);
	CreateDynamicObject(18866, 939.19, -2446.75, 53.93,   0.00, 0.00, 11.65);
	CreateDynamicObject(18866, 940.09, -2446.50, 53.93,   0.00, 0.00, 11.65);
	CreateDynamicObject(18865, 939.43, -2446.70, 53.92,   0.00, 0.00, 10.47);
	CreateDynamicObject(2485, 933.09, -2455.47, 53.77,   0.00, 0.00, 129.97);
	CreateDynamicObject(2474, 931.64, -2447.82, 53.97,   0.00, 0.00, 0.00);
	CreateDynamicObject(2817, 943.97, -2439.71, 53.62,   0.00, 0.00, 279.92);
	CreateDynamicObject(19452, 943.84, -2443.63, 53.53,   0.00, 90.00, 9.88);
	CreateDynamicObject(19452, 944.80, -2449.06, 53.51,   0.00, 90.00, 9.88);
	CreateDynamicObject(19452, 941.36, -2449.66, 53.51,   0.00, 90.00, 9.88);
	CreateDynamicObject(19452, 940.39, -2444.22, 53.53,   0.00, 90.00, 9.88);
	CreateDynamicObject(19452, 936.94, -2444.83, 53.53,   0.00, 90.00, 9.88);
	CreateDynamicObject(19452, 937.93, -2450.25, 53.51,   0.00, 90.00, 9.88);
	CreateDynamicObject(19452, 934.50, -2450.85, 53.51,   0.00, 90.00, 9.88);
	CreateObject(19452, 933.50, -2445.45, 53.53,   0.00, 90.00, 9.88); // for npc
	CreateDynamicObject(19452, 930.08, -2446.05, 53.53,   0.00, 90.00, 9.88);
	CreateDynamicObject(19452, 931.08, -2451.45, 53.51,   0.00, 90.00, 9.88);
	CreateDynamicObject(19452, 927.65, -2452.06, 53.51,   0.00, 90.00, 9.88);
	CreateDynamicObject(19452, 926.70, -2446.63, 53.53,   0.00, 90.00, 9.88);
	CreateDynamicObject(2818, 925.42, -2443.10, 53.61,   0.00, 0.00, 10.79);
	CreateDynamicObject(2481, 933.45, -2455.69, 55.27,   0.00, 0.00, 189.16);
	CreateDynamicObject(2489, 934.96, -2455.38, 54.52,   0.00, 0.00, 189.68);
	CreateDynamicObject(2489, 946.03, -2447.18, 53.85,   0.00, 0.00, 278.99);
	CreateDynamicObject(2509, 929.27, -2441.41, 54.90,   0.00, 0.00, 10.72);
	CreateDynamicObject(2501, 928.90, -2441.72, 54.98,   0.00, 0.00, 9.84);
	CreateDynamicObject(2501, 929.67, -2441.61, 54.98,   0.00, 0.00, 9.84);
	CreateDynamicObject(1824, 965.63, -2416.32, 55.39,   0.00, 0.00, 7.81);
	CreateDynamicObject(16151, 961.33, -2409.44, 55.25,   0.00, 0.00, 98.80);
	CreateDynamicObject(8042, 897.58, -2438.83, 55.86,   0.00, 0.00, 27.97);
	CreateDynamicObject(12808, 976.57, -2457.18, 56.28,   0.00, 0.00, 54.93);
	CreateDynamicObject(18609, 954.58, -2451.40, 54.70,   0.00, 0.00, 14.57);
	CreateDynamicObject(18609, 957.20, -2450.76, 54.70,   0.00, 0.00, 14.57);
	CreateDynamicObject(18609, 951.88, -2452.06, 54.70,   0.00, 0.00, 14.57);
	CreateDynamicObject(1805, 966.02, -2414.81, 55.16,   0.00, 0.00, 0.00);
	CreateDynamicObject(1805, 964.83, -2415.04, 55.16,   0.00, 0.00, 9.48);
	CreateDynamicObject(1710, 955.37, -2415.90, 54.91,   0.00, 0.00, 100.84);
	CreateDynamicObject(1711, 958.54, -2417.69, 54.89,   0.00, 0.00, 187.44);
	CreateDynamicObject(18885, 969.86, -2411.85, 56.03,   0.00, 0.00, 279.36);
	CreateDynamicObject(19054, 965.54, -2493.29, 54.90,   0.00, 0.00, 0.00);
	CreateDynamicObject(19055, 970.47, -2499.10, 54.82,   0.00, 0.00, 0.00);
	CreateDynamicObject(19056, 971.02, -2490.74, 55.04,   0.00, 0.00, 0.00);
	CreateDynamicObject(19057, 965.19, -2498.13, 54.86,   0.00, 0.00, 0.00);
	CreateDynamicObject(19058, 968.41, -2490.75, 54.94,   0.00, 0.00, 0.00);
	CreateDynamicObject(19055, 969.78, -2491.60, 55.10,   0.00, 0.00, 0.00);
	CreateDynamicObject(19054, 975.46, -2493.01, 55.16,   0.00, 0.00, 0.00);
	CreateDynamicObject(19058, 973.86, -2492.89, 55.16,   0.00, 0.00, 0.00);
	CreateDynamicObject(19058, 974.59, -2497.99, 55.02,   0.00, 0.00, 0.00);
	CreateDynamicObject(19056, 973.88, -2494.49, 55.10,   0.00, 0.00, 0.00);
	CreateDynamicObject(19056, 975.90, -2496.64, 55.12,   0.00, 0.00, 0.00);
	CreateDynamicObject(19057, 972.52, -2491.62, 55.14,   0.00, 0.00, 0.00);
	CreateDynamicObject(19054, 973.94, -2496.30, 55.06,   0.00, 0.00, 0.00);
	CreateDynamicObject(19055, 975.46, -2494.65, 55.10,   0.00, 0.00, 0.00);
	CreateDynamicObject(19057, 974.06, -2499.65, 54.92,   0.00, 0.00, 0.00);
	CreateDynamicObject(19054, 966.98, -2499.29, 54.78,   0.00, 0.00, 0.00);
	CreateDynamicObject(19056, 972.54, -2499.19, 54.90,   0.00, 0.00, 0.00);
	CreateDynamicObject(19058, 966.76, -2494.81, 54.92,   0.00, 0.00, 0.00);
	CreateDynamicObject(19055, 965.36, -2495.73, 54.90,   0.00, 0.00, 0.00);
	CreateDynamicObject(19057, 968.77, -2500.53, 54.72,   0.00, 0.00, 0.00);
	CreateDynamicObject(19056, 967.55, -2492.28, 54.94,   0.00, 0.00, 0.00);
	CreateDynamicObject(19054, 971.19, -2500.66, 54.80,   0.00, 0.00, 0.00);
	CreateDynamicObject(19056, 966.59, -2497.00, 54.88,   0.00, 0.00, 0.00);
	CreateDynamicObject(19425, 910.91, -2417.34, 53.39,   0.00, 0.00, 10.39);
	CreateDynamicObject(19425, 905.09, -2418.45, 53.39,   0.00, 0.00, 10.39);
	CreateDynamicObject(19122, 970.41, -2505.16, 80.81,   0.00, 0.00, 358.65);
	CreateDynamicObject(19122, 968.59, -2474.76, 69.45,   0.00, 0.00, 358.95);
	CreateDynamicObject(19122, 981.36, -2477.75, 69.37,   0.00, 0.00, 358.95);
	CreateDynamicObject(19122, 990.27, -2490.14, 69.37,   0.00, 0.00, 358.95);
	CreateDynamicObject(19122, 981.07, -2495.84, 63.46,   0.00, 0.00, 358.95);
	CreateDynamicObject(19122, 978.83, -2488.45, 75.31,   0.00, 0.00, 358.95);
	CreateDynamicObject(19122, 962.25, -2487.24, 76.84,   0.00, 0.00, 358.95);
	CreateDynamicObject(19122, 971.80, -2487.67, 86.32,   0.00, 0.00, 358.95);
	CreateDynamicObject(19122, 960.80, -2501.41, 73.41,   0.00, 0.00, 358.95);
	CreateDynamicObject(19122, 970.84, -2517.64, 68.95,   0.00, 0.00, 358.95);
	CreateDynamicObject(19124, 962.02, -2486.04, 83.99,   0.00, 0.00, 0.00);
	CreateDynamicObject(19124, 972.31, -2482.88, 69.99,   0.00, 0.00, 0.00);
	CreateDynamicObject(19124, 982.63, -2489.48, 73.13,   0.00, 0.00, 0.00);
	CreateDynamicObject(19124, 989.99, -2503.81, 69.92,   0.00, 0.00, 0.00);
	CreateDynamicObject(19124, 975.20, -2495.33, 79.25,   0.00, 0.00, 0.00);
	CreateDynamicObject(19124, 949.71, -2498.68, 69.66,   0.00, 0.00, 0.00);
	CreateDynamicObject(19124, 964.95, -2489.87, 64.06,   0.00, 0.00, 0.00);
	CreateDynamicObject(19123, 983.85, -2504.24, 73.06,   0.00, 0.00, 0.00);
	CreateDynamicObject(19123, 962.32, -2495.17, 90.02,   0.00, 0.00, 0.00);
	CreateDynamicObject(19123, 956.47, -2480.73, 69.52,   0.00, 0.00, 0.00);
	CreateDynamicObject(19123, 970.40, -2485.75, 64.36,   0.00, 0.00, 0.00);
	CreateDynamicObject(19123, 970.24, -2485.47, 75.95,   0.00, 0.00, 0.00);
	CreateDynamicObject(19123, 984.19, -2491.90, 83.31,   0.00, 0.00, 0.00);
	CreateDynamicObject(19123, 957.94, -2512.26, 69.68,   0.00, 0.00, 0.00);
	CreateDynamicObject(19123, 965.24, -2499.40, 80.27,   0.00, 0.00, 0.00);
	CreateDynamicObject(19125, 962.77, -2506.59, 83.92,   0.00, 0.00, 0.00);
	CreateDynamicObject(19125, 959.95, -2495.48, 64.11,   0.00, 0.00, 0.00);
	CreateDynamicObject(19125, 961.00, -2492.86, 75.36,   0.00, 0.00, 0.00);
	CreateDynamicObject(19125, 973.54, -2493.16, 92.79,   0.00, 0.00, 0.00);
	CreateDynamicObject(19125, 978.52, -2489.87, 81.19,   0.00, 0.00, 0.00);
	CreateDynamicObject(19125, 985.04, -2494.19, 73.15,   0.00, 0.00, 0.00);
	CreateDynamicObject(19125, 974.75, -2510.08, 70.87,   0.00, 0.00, 0.00);
	CreateDynamicObject(19125, 962.64, -2507.46, 72.19,   0.00, 0.00, 0.00);
	CreateDynamicObject(19121, 975.92, -2485.44, 74.80,   0.00, 0.00, 0.00);
	CreateDynamicObject(19121, 956.80, -2486.15, 72.32,   0.00, 0.00, 0.00);
	CreateDynamicObject(19121, 957.06, -2498.95, 73.81,   0.00, 0.00, 0.00);
	CreateDynamicObject(19121, 968.68, -2506.67, 73.81,   0.00, 0.00, 0.00);
	CreateDynamicObject(19121, 969.70, -2503.60, 86.88,   0.00, 0.00, 0.00);
	CreateDynamicObject(19121, 977.14, -2490.01, 87.20,   0.00, 0.00, 0.00);
	CreateDynamicObject(19121, 970.31, -2489.51, 80.15,   0.00, 0.00, 0.00);
	CreateDynamicObject(7666, 970.63, -2495.08, 105.85,   0.00, 0.00, 60.21);
	CreateDynamicObject(7666, 970.63, -2495.08, 105.85,   0.00, 0.00, 218.47);
	CreateDynamicObject(7666, 970.63, -2495.08, 105.85,   0.00, 0.00, 92.53);
	CreateDynamicObject(7666, 970.63, -2495.08, 105.85,   0.00, 0.00, 131.19);
	CreateDynamicObject(7666, 970.63, -2495.08, 105.85,   0.00, 0.00, 161.46);
	CreateDynamicObject(7666, 970.63, -2495.08, 105.85,   0.00, 0.00, 186.15);
	CreateDynamicObject(19127, 970.54, -2515.86, 69.85,   0.00, 0.00, 0.00);
	CreateDynamicObject(19127, 977.72, -2480.40, 71.63,   0.00, 0.00, 0.00);
	CreateDynamicObject(19127, 968.09, -2486.17, 85.17,   0.00, 0.00, 0.00);
	CreateDynamicObject(19127, 960.37, -2495.08, 79.13,   0.00, 0.00, 0.00);
	CreateDynamicObject(19127, 957.62, -2481.25, 70.81,   0.00, 0.00, 0.00);
	CreateDynamicObject(19127, 972.15, -2484.48, 64.40,   0.00, 0.00, 0.00);
	CreateDynamicObject(19127, 991.66, -2487.85, 69.52,   0.00, 0.00, 0.00);
	CreateDynamicObject(19127, 980.38, -2495.70, 77.81,   0.00, 0.00, 0.00);
	CreateDynamicObject(19127, 970.54, -2506.22, 77.81,   0.00, 0.00, 0.00);
	CreateDynamicObject(18864, 950.06, -2504.42, -19.11,   0.00, 0.00, 33.18);//snow
	CreateDynamicObject(18864, 889.37, -2293.56, -19.11,   0.00, 0.00, 31.49);//snow
	CreateDynamicObject(19315, 896.02, -2405.61, 54.57,   0.00, 0.00, 58.52);
	CreateDynamicObject(19315, 915.44, -2410.69, 54.21,   0.00, 0.00, 157.83);
	CreateDynamicObject(19315, 914.96, -2411.70, 54.21,   0.00, 0.00, 128.35);
	CreateDynamicObject(19315, 896.87, -2405.47, 54.21,   0.00, 0.00, 76.57);
	CreateDynamicObject(19315, 895.33, -2404.49, 54.57,   0.00, 0.00, 36.80);
	CreateDynamicObject(19315, 1026.48, -2339.26, 12.46,   0.00, 0.00, 59.63);
	CreateDynamicObject(19315, 1027.21, -2339.68, 12.46,   0.00, 0.00, 77.35);

//rock textures
	new tmpobjid;
    tmpobjid = CreateDynamicObject(18751, 937.01, -2220.65, -1.94,   0.00, 0.00, 305.44);
   	SetDynamicObjectMaterial(tmpobjid, 0, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 1, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);

    tmpobjid = CreateDynamicObject(18751, 958.02, -2280.09, 7.80,   0.00, 0.00, 305.44);
   	SetDynamicObjectMaterial(tmpobjid, 0, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 1, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);

	tmpobjid = CreateDynamicObject(18751, 766.61, -2239.62, 3.26,   0.00, 0.00, 62.09);
   	SetDynamicObjectMaterial(tmpobjid, 0, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 1, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);



	tmpobjid = CreateDynamicObject(18751, 811.93, -2207.26, 3.86,   0.00, 0.00, 18.43);
	SetDynamicObjectMaterial(tmpobjid, 0, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 1, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);


	tmpobjid = CreateDynamicObject(18751, 721.91, -2236.05, 0.56,   0.00, 0.00, 86.82);
	SetDynamicObjectMaterial(tmpobjid, 0, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 1, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);

	tmpobjid = CreateDynamicObject(18751, 762.61, -2355.29, 0.56,   0.00, 0.00, 114.76);
	SetDynamicObjectMaterial(tmpobjid, 0, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 1, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);


	tmpobjid = CreateDynamicObject(18751, 766.96, -2412.61, 2.22,   0.00, 0.00, 92.01);
	SetDynamicObjectMaterial(tmpobjid, 0, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 1, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);

	tmpobjid = CreateDynamicObject(18751, 792.95, -2455.85, 2.22,   0.00, 0.00, 136.83);
	SetDynamicObjectMaterial(tmpobjid, 0, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 1, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);

	tmpobjid = CreateDynamicObject(18751, 882.50, -2590.48, 3.05,   0.00, 0.00, 136.83);
	SetDynamicObjectMaterial(tmpobjid, 0, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 1, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);

	tmpobjid = CreateDynamicObject(18751, 950.16, -2556.82, 4.92,   0.00, 0.00, 201.12);
	SetDynamicObjectMaterial(tmpobjid, 0, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 1, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);

	tmpobjid = CreateDynamicObject(18751, 1009.88, -2518.76, 2.67,   0.00, 0.00, 221.43);
	SetDynamicObjectMaterial(tmpobjid, 0, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 1, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);

	tmpobjid = CreateDynamicObject(18751, 887.98, -2194.55, 3.32,   0.00, 0.00, 354.66);
   	SetDynamicObjectMaterial(tmpobjid, 0, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 1, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);

	tmpobjid = CreateDynamicObject(18751, 926.42, -2240.99, 6.41,   0.00, 0.00, 305.44);
	SetDynamicObjectMaterial(tmpobjid, 0, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 1, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);

	tmpobjid = CreateDynamicObject(18751, 955.19, -2282.06, 9.15,   0.00, 0.00, 305.44);
   	SetDynamicObjectMaterial(tmpobjid, 0, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 1, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);

	tmpobjid = CreateDynamicObject(18751, 747.97, -2304.88, 0.56,   0.00, 0.00, 89.57);
   	SetDynamicObjectMaterial(tmpobjid, 0, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 1, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);

	tmpobjid = CreateDynamicObject(18751, 704.70, -2269.46, 0.56,   0.00, 0.00, 86.82);
	SetDynamicObjectMaterial(tmpobjid, 0, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 1, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);


	tmpobjid = CreateDynamicObject(18751, 706.46, -2307.04, -6.26,   0.00, 0.00, 93.98);
   	SetDynamicObjectMaterial(tmpobjid, 0, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 1, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);

//Shop Texture
	tmpobjid = CreateDynamicObject(19456, 946.61, -2448.70, 55.33,   0.00, 0.00, 10.64);
	SetDynamicObjectMaterial(tmpobjid, 0, 16070, "des_stownmain1", "des_brick1", 0);

	tmpobjid = CreateDynamicObject(19456, 941.01, -2454.59, 55.33,   0.00, 0.00, 280.04);
	SetDynamicObjectMaterial(tmpobjid, 0, 16070, "des_stownmain1", "des_brick1", 0);

	tmpobjid = CreateDynamicObject(19456, 931.57, -2456.26, 55.33,   0.00, 0.00, 280.04);
	SetDynamicObjectMaterial(tmpobjid, 0, 16070, "des_stownmain1", "des_brick1", 0);

	tmpobjid = CreateDynamicObject(19456, 925.04, -2446.90, 55.33,   0.00, 0.00, 10.02);
	SetDynamicObjectMaterial(tmpobjid, 0, 16070, "des_stownmain1", "des_brick1", 0);

	tmpobjid = CreateDynamicObject(19456, 940.02, -2439.38, 55.33,   0.00, 0.00, 280.34);
	SetDynamicObjectMaterial(tmpobjid, 0, 16070, "des_stownmain1", "des_brick1", 0);

	tmpobjid = CreateDynamicObject(19456, 931.98, -2440.83, 55.33,   0.00, 0.00, 280.34);
	SetDynamicObjectMaterial(tmpobjid, 0, 16070, "des_stownmain1", "des_brick1", 0);

	tmpobjid = CreateDynamicObject(19456, 946.15, -2446.32, 55.33,   0.00, 0.00, 10.64);
	SetDynamicObjectMaterial(tmpobjid, 0, 16070, "des_stownmain1", "des_brick1", 0);

	tmpobjid = CreateDynamicObject(19456, 926.02, -2452.44, 55.33,   0.00, 0.00, 10.02);
	SetDynamicObjectMaterial(tmpobjid, 0, 16070, "des_stownmain1", "des_brick1", 0);

	tmpobjid = CreateDynamicObject(19456, 942.84, -2454.26, 55.33,   0.00, 0.00, 280.04);
	SetDynamicObjectMaterial(tmpobjid, 0, 16070, "des_stownmain1", "des_brick1", 0);

	tmpobjid = CreateDynamicObject(19393, 944.95, -2440.06, 55.33,   0.00, 0.00, 10.23);
	SetDynamicObjectMaterial(tmpobjid, 0, 16070, "des_stownmain1", "des_brick1", 0);

	tmpobjid = CreateDynamicObject(19393, 925.71, -2441.97, 55.33,   0.00, 0.00, 280.34);
	SetDynamicObjectMaterial(tmpobjid, 0, 16070, "des_stownmain1", "des_brick1", 0);

//entrance
    tmpobjid = CreateDynamicObject(3715, 1027.67, -2328.83, 21.13,   0.00, 0.00, 308.5198);
   	SetDynamicObjectMaterial(tmpobjid, 2, 3915, "libertyhi3", "mp_snow", 0);


//text
    //tmpobjid = CreateDynamicObject(19481, 925.50, -2448.91, 55.33,   0.00, 0.00, 10.00);
    //SetDynamicObjectMaterialText(tmpobjid, 0,  "{FFFFFF}Linksmu {00FBFF}Kaledu!", 140,"Arial", 28, 0, 0xFFFF8200, 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);

	tmpobjid = CreateDynamicObject(19481, 932.17, -2440.68, 55.39,   0.00, 0.00, 100.00);
    SetDynamicObjectMaterialText(tmpobjid, 0, "{FFFFFF}Gift {00FBFF}Shop", 140,"Arial", 28, 0, 0xFFFF8200, 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);

	//tmpobjid = CreateDynamicObject(19481, 934.95, -2455.36, 56.48,   0.00, 0.00, 100.00);
    //SetDynamicObjectMaterialText(tmpobjid, 0, "{FFFFFF}Snow is falling", 140,"Arial", 28, 0, 0xFFFF8200, 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);

//entrance text
	tmpobjid = CreateDynamicObject(19481, 1028.35, -2328.57, 21.40,   0.00, 0.00, 38.50);
	SetDynamicObjectMaterialText(tmpobjid, 0, "{f5514e}Kaledu Miestelis", 100,"Arial", 23, 0, 0xFFFF8200, 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);

//snow mountain textures
    tmpobjid = CreateDynamicObject(16109, 928.42, -2303.11, 28.88,   0.00, 0.00, 190.79);
	SetDynamicObjectMaterial(tmpobjid, 1, 3915, "libertyhi3", "mp_snow", 0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);

 	tmpobjid = CreateDynamicObject(16147, 808.61, -2495.53, 21.50,   0.00, 0.00, 190.79);
	SetDynamicObjectMaterial(tmpobjid, 0, 3915, "libertyhi3", "mp_snow", 0);
    SetDynamicObjectMaterial(tmpobjid, 4, 10166, "p69_rocks", "sfe_rock1",0);//rock onside
    SetDynamicObjectMaterial(tmpobjid, 5, 10166, "p69_rocks", "sfe_rock1",0);//rock onside
    SetDynamicObjectMaterial(tmpobjid, 1, 3915, "libertyhi3", "mp_snow", 0);//rock onside



 	tmpobjid = CreateDynamicObject(16148, 1007.14, -2442.03, -3.38,   0.00, 0.00, 216.11);
	SetDynamicObjectMaterial(tmpobjid, 0, 3915, "libertyhi3", "mp_snow", 0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);//rock onside
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);//rock onside


	tmpobjid = CreateDynamicObject(16264, 866.61, -2195.44, 16.70,   0.00, 0.00, 190.79);
    SetDynamicObjectMaterial(tmpobjid, 0, 3915, "libertyhi3", "mp_snow", 0);
	SetDynamicObjectMaterial(tmpobjid, 1, 3915, "libertyhi3", "mp_snow", 0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);//rock onside

	tmpobjid = CreateDynamicObject(16149, 756.42, -2298.31, 20.01,   0.00, 0.00, 190.79);
	SetDynamicObjectMaterial(tmpobjid, 2, 3915, "libertyhi3", "mp_snow", 0);
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);//rock onside
	SetDynamicObjectMaterial(tmpobjid, 4, 10166, "p69_rocks", "sfe_rock1",0);//rock onside


	tmpobjid = CreateObject(16148, 969.96, -2477.20, 31.30,   0.00, 0.00, 190.79); // for npc
	SetObjectMaterial(tmpobjid, 0, 3915, "libertyhi3", "mp_snow", 0);
	SetObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);//rock onside
	SetObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);//rock onside

	tmpobjid = CreateDynamicObject(16148, 978.53, -2497.10, 7.30,   0.00, 0.00, 175.75);
	SetDynamicObjectMaterial(tmpobjid, 0, 3915, "libertyhi3", "mp_snow", 0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);//rock onside
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);//rock onside

	tmpobjid = CreateDynamicObject(16148, 996.83, -2479.45, 7.30,   0.00, 0.00, 199.06);
	SetDynamicObjectMaterial(tmpobjid, 0, 3915, "libertyhi3", "mp_snow", 0);
	SetDynamicObjectMaterial(tmpobjid, 2, 10166, "p69_rocks", "sfe_rock1",0);//rock onside
	SetDynamicObjectMaterial(tmpobjid, 3, 10166, "p69_rocks", "sfe_rock1",0);//rock onside

    tmpobjid = CreateDynamicObject(16141, 904.18, -2550.39, -2.48,   0.00, 0.00, 20.92);
	SetDynamicObjectMaterial(tmpobjid, 0, 3915, "libertyhi3", "mp_snow", 0);
	SetDynamicObjectMaterial(tmpobjid, 1, 3915, "libertyhi3", "mp_snow", 0);


    tmpobjid = CreateDynamicObject(16141, 847.90, -2518.85, -2.69,   0.00, 0.00, 20.92);
	SetDynamicObjectMaterial(tmpobjid, 0, 3915, "libertyhi3", "mp_snow", 0);
	SetDynamicObjectMaterial(tmpobjid, 1, 3915, "libertyhi3", "mp_snow", 0);


    CreateActor(49,967.0925,-2490.5212,55.3092,40.6813); // kaledu senelis
    CreateActor(214,960.6804,-2409.7263,55.9259,192.8178); // barmene
    CreateActor(233,934.1066,-2441.9690,54.6159,187.3350); // pardaveja
}

stock initChristmasEgles() // 2024 
{
	pickups[0][dovana]=CreatePickupA(19135, 2, 834.8083,-1966.8887,12.9672);
    CreateDynamic3DTextLabel("Los Santos\n{e299ff}Kalëdø Eglutë",COLOR_WHITE, 834.8083,-1966.8887,12.9672,20,_,_,1);
	new tmpobjid;
	// kaledos 2024
	// nang aziz
	tmpobjid = CreateDynamicObject(18771,700.821105,-1290.306274,12.768720,0.000000,0.000000,-5.300037);
	SetDynamicObjectMaterial(tmpobjid,0,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	SetDynamicObjectMaterial(tmpobjid,2,1355,"break_s_bins","CJ_RED_LEATHER",0);
	tmpobjid = CreateDynamicObject(18771,700.821105,-1290.306274,12.768720,0.000000,0.000000,129.800003);
	SetDynamicObjectMaterial(tmpobjid,0,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	SetDynamicObjectMaterial(tmpobjid,2,1355,"break_s_bins","CJ_RED_LEATHER",0);
	tmpobjid = CreateDynamicObject(18771,700.821105,-1290.306274,12.768720,0.000000,0.000000,-116.300071);
	SetDynamicObjectMaterial(tmpobjid,0,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	SetDynamicObjectMaterial(tmpobjid,2,1355,"break_s_bins","CJ_RED_LEATHER",0);
	tmpobjid = CreateDynamicObject(7666,700.148620,-1289.490722,80.994041,0.000000,0.000000,-90.699966);
	tmpobjid = CreateDynamicObject(7666,700.148620,-1289.490722,80.994041,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,703.114074,-1275.923339,16.596441,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,705.574157,-1275.923339,16.646442,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,700.823425,-1275.923339,16.646442,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,698.772460,-1275.923339,16.726444,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,707.773498,-1276.093505,16.786445,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,696.562316,-1275.913330,16.846446,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,709.764587,-1276.143554,16.896448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19574,704.787963,-1287.208129,14.022385,0.000000,0.000000,-31.400005);
	SetDynamicObjectMaterial(tmpobjid,0,19523,"sampicons","reeedgrad32",-16777216);
	tmpobjid = CreateDynamicObject(19574,704.881530,-1287.054321,14.022385,0.000000,0.000000,-31.400005);
	SetDynamicObjectMaterial(tmpobjid,0,19523,"sampicons","reeedgrad32",-16777216);
	tmpobjid = CreateDynamicObject(18638,704.981689,-1287.229736,14.134980,15.199998,-89.900054,59.800006);
	tmpobjid = CreateDynamicObject(19055,704.053833,-1286.775390,14.447768,0.000000,21.800014,-25.099998);
	tmpobjid = CreateDynamicObject(2237,704.458251,-1286.591064,14.207104,-40.499786,-10.100004,30.200229);
	tmpobjid = CreateDynamicObject(2237,704.170593,-1287.247558,14.149336,-40.499786,-10.100004,76.100242);
	tmpobjid = CreateDynamicObject(1946,704.925170,-1287.192382,13.892473,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,16093,"a51_ext","ws_whitewall2_top",0);
	tmpobjid = CreateDynamicObject(1598,704.772033,-1287.072509,13.492569,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,16093,"a51_ext","ws_whitewall2_top",0);
	tmpobjid = CreateDynamicObject(19059,704.697265,-1286.997680,13.042042,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16093,"a51_ext","ws_whitewall2_top",0);
	tmpobjid = CreateDynamicObject(1575,697.478027,-1285.980834,14.022153,-24.199874,-102.300003,224.500000);
	tmpobjid = CreateDynamicObject(1575,698.936340,-1286.377319,13.973443,25.300016,-99.700134,272.100006);
	tmpobjid = CreateDynamicObject(19574,698.220581,-1285.987426,13.952383,0.000000,0.000000,332.399993);
	SetDynamicObjectMaterial(tmpobjid,0,19523,"sampicons","reeedgrad32",-16777216);
	tmpobjid = CreateDynamicObject(19574,698.379882,-1286.070922,13.952383,0.000000,0.000000,-27.600000);
	SetDynamicObjectMaterial(tmpobjid,0,19523,"sampicons","reeedgrad32",-16777216);
	tmpobjid = CreateDynamicObject(19064,698.243103,-1286.161865,14.107872,0.000000,29.699962,74.600044);
	tmpobjid = CreateDynamicObject(2237,697.688964,-1285.965454,14.004218,318.600158,24.700004,98.200149);
	tmpobjid = CreateDynamicObject(2237,698.785888,-1286.290771,14.044210,-41.399860,24.700000,-59.799854);
	tmpobjid = CreateDynamicObject(1946,698.234802,-1286.191406,13.892473,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,16093,"a51_ext","ws_whitewall2_top",0);
	tmpobjid = CreateDynamicObject(1598,698.231750,-1286.192138,13.492569,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,16093,"a51_ext","ws_whitewall2_top",0);
	tmpobjid = CreateDynamicObject(19059,698.247009,-1286.206909,13.042042,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16093,"a51_ext","ws_whitewall2_top",0);
	tmpobjid = CreateDynamicObject(19056,700.005004,-1288.000488,14.383548,0.000000,0.000000,9.500003);
	tmpobjid = CreateDynamicObject(19054,699.343017,-1287.292358,13.223543,0.000000,0.000000,116.899932);
	tmpobjid = CreateDynamicObject(19054,702.686340,-1289.114990,14.383548,0.000000,0.000000,-61.699974);
	tmpobjid = CreateDynamicObject(18962,695.557006,-1275.070434,14.133713,357.800018,271.200012,130.399932);
	tmpobjid = CreateDynamicObject(19138,695.673217,-1274.976440,13.957037,0.000000,0.000000,36.200000);
	tmpobjid = CreateDynamicObject(355,695.913635,-1275.131713,13.604161,-6.499998,34.600002,120.199958);
	tmpobjid = CreateDynamicObject(1946,695.554931,-1275.070922,13.892473,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,16093,"a51_ext","ws_whitewall2_top",0);
	tmpobjid = CreateDynamicObject(1598,695.551269,-1275.092529,13.492569,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,16093,"a51_ext","ws_whitewall2_top",0);
	tmpobjid = CreateDynamicObject(19059,695.537231,-1275.095947,13.042042,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16093,"a51_ext","ws_whitewall2_top",0);
	tmpobjid = CreateDynamicObject(19574,710.642150,-1275.073364,13.952383,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19523,"sampicons","reeedgrad32",-16777216);
	tmpobjid = CreateDynamicObject(19574,710.712219,-1274.923217,13.952383,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19523,"sampicons","reeedgrad32",-16777216);
	tmpobjid = CreateDynamicObject(19058,703.505187,-1289.594116,13.203540,0.000000,0.000000,20.400007);
	tmpobjid = CreateDynamicObject(18972,710.811401,-1275.071289,14.092836,0.000000,11.000003,343.600006);
	tmpobjid = CreateDynamicObject(19578,710.898193,-1274.544555,13.917408,20.400003,-99.100006,4.799999);
	SetDynamicObjectMaterial(tmpobjid,0,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2237,710.626098,-1275.434082,13.806081,320.500000,0.000001,155.900054);
	tmpobjid = CreateDynamicObject(2237,710.893615,-1274.738647,13.798274,320.500030,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,7400.000000,-1279.457763,14.912079,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1946,710.806152,-1275.070922,13.892473,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,16093,"a51_ext","ws_whitewall2_top",0);
	tmpobjid = CreateDynamicObject(1598,710.821777,-1275.092529,13.492569,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,16093,"a51_ext","ws_whitewall2_top",0);
	tmpobjid = CreateDynamicObject(19059,710.848022,-1275.095947,13.042042,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16093,"a51_ext","ws_whitewall2_top",0);
	tmpobjid = CreateDynamicObject(18654,712.898498,-1308.280883,15.553536,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(18654,687.608093,-1308.251708,15.553536,0.000000,0.000000,179.100021);
	tmpobjid = CreateDynamicObject(2773,688.710693,-1307.651000,15.800128,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,688.727111,-1305.780761,15.800128,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,688.743041,-1303.910278,15.800128,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,688.759094,-1302.050170,15.800128,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(3675,688.156311,-1308.283081,13.648150,0.000000,0.199999,88.599975);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(2773,711.103637,-1307.572753,15.800130,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,711.119140,-1305.701171,15.800130,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,711.135009,-1303.840454,15.800130,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,711.150695,-1301.989501,15.800130,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(3675,711.401916,-1308.216918,13.473539,0.000000,0.000000,269.600006);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(2773,688.777893,-1299.869750,15.800128,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,688.793945,-1298.009399,15.800128,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,688.809387,-1296.147949,15.800128,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,688.854248,-1294.287231,15.800128,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,688.873413,-1292.056152,15.800128,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,688.889282,-1290.195922,15.800128,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,688.905456,-1288.325439,15.800128,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,688.921325,-1286.494628,15.800128,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,688.938232,-1284.493408,15.800128,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,688.954467,-1282.622680,15.810131,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,688.971069,-1280.752197,15.800130,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,688.986877,-1278.922363,15.800130,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,711.170227,-1299.799804,15.800130,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,711.186157,-1297.939453,15.800130,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,711.202392,-1296.058959,15.800130,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,711.218383,-1294.238769,15.800130,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,711.238464,-1291.887451,15.800130,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,711.254394,-1290.047119,15.800130,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,711.270690,-1288.196289,15.800130,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,711.286987,-1286.356811,15.800130,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,711.301513,-1284.696899,15.800130,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(3472,681.588989,-1276.257324,11.898257,0.000000,0.000000,-132.899978);
	tmpobjid = CreateDynamicObject(3472,719.459899,-1276.257324,11.898257,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(2773,711.317932,-1282.806518,15.800130,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,711.334167,-1280.957031,15.800130,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(2773,711.350219,-1279.095825,15.800130,0.000000,0.000000,359.500000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,1,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(19087,697.372131,-1275.928344,17.272653,0.000000,93.799850,-0.400012);
	tmpobjid = CreateDynamicObject(19087,699.765319,-1275.947753,17.113618,0.000000,93.799850,-0.400006);
	tmpobjid = CreateDynamicObject(19087,702.135253,-1275.968139,17.088804,0.000000,90.599899,359.500000);
	tmpobjid = CreateDynamicObject(19087,704.205261,-1275.995971,17.110496,0.000000,89.399925,-0.799993);
	tmpobjid = CreateDynamicObject(11712,592.608276,-1254.589233,63.345890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19087,706.622192,-1276.060180,17.203413,0.000000,87.799957,358.500000);
	tmpobjid = CreateDynamicObject(19087,711.446655,-1276.183471,17.561595,0.000000,84.500000,358.500000);
	tmpobjid = CreateDynamicObject(19087,709.048950,-1276.122314,17.330575,0.000000,86.999969,358.500000);
	tmpobjid = CreateDynamicObject(18653,687.725280,-1300.831787,15.553536,0.000000,0.000000,179.100021);
	tmpobjid = CreateDynamicObject(18654,687.848510,-1292.992919,15.553536,0.000000,0.000000,179.100021);
	tmpobjid = CreateDynamicObject(18653,687.971313,-1285.183593,15.553536,0.000000,0.000000,179.100021);
	tmpobjid = CreateDynamicObject(18654,688.081176,-1278.243408,15.643534,0.000000,0.000000,179.100021);
	tmpobjid = CreateDynamicObject(18653,712.898498,-1300.950195,15.553536,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(18654,712.898498,-1293.187866,15.553536,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(18653,712.898498,-1285.436767,15.553536,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(18654,712.898498,-1278.473632,15.553536,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(3675,688.337463,-1300.864257,13.622243,0.000000,0.199999,88.599975);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,688.527893,-1293.063598,13.595011,0.000000,0.199999,88.599975);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,688.719055,-1285.234130,13.567666,0.000000,0.199999,88.599975);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,688.888000,-1278.316040,13.543507,0.000000,0.199999,88.599975);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,711.452148,-1300.904785,13.473539,0.000000,0.000000,-90.399986);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,711.505249,-1293.122436,13.473539,0.000000,0.000000,-90.399986);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(19060,699.520690,-1287.153442,76.013397,0.000000,0.000000,111.499877);
	tmpobjid = CreateDynamicObject(19063,703.050415,-1288.193603,75.673416,0.000000,0.000000,100.899856);
	tmpobjid = CreateDynamicObject(19062,697.246704,-1290.103027,75.483398,0.000000,0.000000,100.899856);
	tmpobjid = CreateDynamicObject(19061,699.018127,-1292.206176,71.823356,0.000000,0.000000,115.299942);
	tmpobjid = CreateDynamicObject(19060,703.988525,-1292.355712,71.823356,0.000000,0.000000,115.299942);
	tmpobjid = CreateDynamicObject(19059,700.920776,-1291.199707,76.403404,0.000000,0.000000,100.899856);
	tmpobjid = CreateDynamicObject(19062,701.242126,-1286.767211,71.823356,0.000000,0.000000,145.499984);
	tmpobjid = CreateDynamicObject(19063,697.027160,-1287.993652,71.823356,0.000000,0.000000,115.299942);
	tmpobjid = CreateDynamicObject(19063,698.790771,-1295.968750,67.433364,0.000000,0.000000,172.000000);
	tmpobjid = CreateDynamicObject(19059,694.828857,-1292.403930,67.433364,0.000000,0.000000,172.000000);
	tmpobjid = CreateDynamicObject(19059,695.359619,-1286.764282,67.433364,0.000000,0.000000,172.000000);
	tmpobjid = CreateDynamicObject(19063,698.935852,-1284.390136,67.433364,0.000000,0.000000,172.000000);
	tmpobjid = CreateDynamicObject(19061,704.257385,-1285.319091,67.433364,0.000000,0.000000,127.199966);
	tmpobjid = CreateDynamicObject(19059,706.776184,-1290.213378,67.433364,0.000000,0.000000,63.600013);
	tmpobjid = CreateDynamicObject(19062,704.236572,-1295.327270,67.433364,0.000000,0.000000,10.500028);
	tmpobjid = CreateDynamicObject(19061,693.975341,-1283.311645,62.043403,0.000000,0.000000,-149.599777);
	tmpobjid = CreateDynamicObject(19060,702.419860,-1280.621582,62.043403,0.000000,0.000000,161.700149);
	tmpobjid = CreateDynamicObject(19059,708.903076,-1285.172485,62.043403,0.000000,0.000000,98.199996);
	tmpobjid = CreateDynamicObject(19063,709.686645,-1292.990112,62.043403,0.000000,0.000000,44.800022);
	tmpobjid = CreateDynamicObject(19061,704.361938,-1298.783081,62.043403,0.000000,0.000000,44.800022);
	tmpobjid = CreateDynamicObject(19059,691.174194,-1289.208251,62.043403,0.000000,0.000000,44.800022);
	tmpobjid = CreateDynamicObject(19062,695.497558,-1298.174194,62.043403,0.000000,0.000000,44.800022);
	tmpobjid = CreateDynamicObject(19063,691.188293,-1299.630126,54.563415,0.000000,0.000000,12.700014);
	tmpobjid = CreateDynamicObject(661,700.565002,-1290.064331,43.382476,1.799999,49.699939,-129.199951);
	tmpobjid = CreateDynamicObject(19062,695.924682,-1277.385864,54.563415,0.000000,0.000000,12.700014);
	tmpobjid = CreateDynamicObject(19060,688.254211,-1284.423583,54.563415,0.000000,0.000000,12.700014);
	tmpobjid = CreateDynamicObject(19061,687.976318,-1294.337890,54.563415,0.000000,0.000000,12.700014);
	tmpobjid = CreateDynamicObject(19060,700.073120,-1303.735595,54.633434,0.000000,0.000000,43.899997);
	tmpobjid = CreateDynamicObject(19059,709.232238,-1300.705688,54.633434,0.000000,0.000000,43.899997);
	tmpobjid = CreateDynamicObject(19062,714.168701,-1290.016479,54.633434,0.000000,0.000000,43.899997);
	tmpobjid = CreateDynamicObject(19063,709.252929,-1279.718017,54.633434,0.000000,0.000000,43.899997);
	tmpobjid = CreateDynamicObject(19062,695.875610,-1305.009765,48.063465,0.000000,0.000000,66.699958);
	tmpobjid = CreateDynamicObject(19059,691.807189,-1279.143188,48.063465,0.000000,0.000000,66.699958);
	tmpobjid = CreateDynamicObject(19062,688.082580,-1298.813476,48.063465,0.000000,0.000000,66.699958);
	tmpobjid = CreateDynamicObject(19063,686.040649,-1287.601196,48.063465,0.000000,0.000000,66.699958);
	tmpobjid = CreateDynamicObject(661,700.388549,-1290.934326,38.746780,1.799998,57.099910,130.399871);
	tmpobjid = CreateDynamicObject(19061,704.717102,-1276.817749,48.063465,0.000000,0.000000,66.699958);
	tmpobjid = CreateDynamicObject(19063,713.514099,-1284.289306,48.063465,0.000000,0.000000,22.599992);
	tmpobjid = CreateDynamicObject(19060,714.739013,-1293.904418,48.063465,0.000000,0.000000,-14.200008);
	tmpobjid = CreateDynamicObject(19062,708.526977,-1303.126098,48.093490,0.000000,0.000000,27.099998);
	tmpobjid = CreateDynamicObject(19063,701.708129,-1306.969604,41.833522,0.000000,0.000000,-7.700002);
	tmpobjid = CreateDynamicObject(19062,713.568359,-1299.703002,41.833522,0.000000,0.000000,-7.700002);
	tmpobjid = CreateDynamicObject(19062,691.363647,-1304.652465,41.833522,0.000000,0.000000,146.800003);
	tmpobjid = CreateDynamicObject(19061,684.608276,-1295.480834,41.833522,0.000000,0.000000,106.599960);
	tmpobjid = CreateDynamicObject(19062,685.391296,-1282.405151,41.833522,0.000000,0.000000,54.199977);
	tmpobjid = CreateDynamicObject(19063,696.353332,-1273.872680,41.833522,0.000000,0.000000,8.599987);
	tmpobjid = CreateDynamicObject(19060,710.515075,-1277.041870,41.833522,0.000000,0.000000,36.699993);
	tmpobjid = CreateDynamicObject(19059,717.051879,-1289.458129,41.833522,0.000000,0.000000,-7.700002);
	tmpobjid = CreateDynamicObject(19059,684.049438,-1297.909790,34.573532,0.000000,0.000000,-74.199935);
	tmpobjid = CreateDynamicObject(19060,683.869628,-1287.661743,34.573532,0.000000,0.000000,-34.200000);
	tmpobjid = CreateDynamicObject(19061,690.060607,-1276.270874,34.573532,0.000000,0.000000,-34.200000);
	tmpobjid = CreateDynamicObject(19059,704.515563,-1274.108398,34.573532,0.000000,0.000000,-34.200000);
	tmpobjid = CreateDynamicObject(19062,717.105041,-1282.661987,34.573532,0.000000,0.000000,-34.200000);
	tmpobjid = CreateDynamicObject(19061,719.108642,-1292.811401,34.573532,0.000000,0.000000,-34.200000);
	tmpobjid = CreateDynamicObject(19060,689.914794,-1305.405517,34.573532,0.000000,0.000000,-34.200000);
	tmpobjid = CreateDynamicObject(19061,702.930725,-1308.565063,34.573532,0.000000,0.000000,-34.200000);
	tmpobjid = CreateDynamicObject(19063,710.210510,-1309.060668,29.683582,0.000000,0.000000,-48.000007);
	tmpobjid = CreateDynamicObject(19059,712.072509,-1305.053100,34.573532,0.000000,0.000000,-34.200000);
	tmpobjid = CreateDynamicObject(19063,716.420227,-1300.823852,34.573532,0.000000,0.000000,-34.200000);
	tmpobjid = CreateDynamicObject(19062,702.585571,-1311.718750,26.723543,0.000000,-0.000000,2.500000);
	tmpobjid = CreateDynamicObject(19059,691.080078,-1308.796264,26.533571,0.000000,0.000000,56.900020);
	tmpobjid = CreateDynamicObject(19061,693.421081,-1311.215942,29.713575,0.000000,0.000000,-19.300004);
	tmpobjid = CreateDynamicObject(19063,683.894592,-1303.452026,26.589841,0.000000,0.000000,-131.299972);
	tmpobjid = CreateDynamicObject(19062,679.933288,-1296.428344,29.813583,0.000000,0.000000,12.900004);
	tmpobjid = CreateDynamicObject(19061,680.258239,-1285.284912,28.983562,0.000000,0.000000,11.899998);
	tmpobjid = CreateDynamicObject(19060,679.578430,-1291.675903,26.603551,0.000000,0.000000,1.999995);
	tmpobjid = CreateDynamicObject(19063,683.955810,-1276.849121,29.779844,0.000000,0.000000,1.300005);
	tmpobjid = CreateDynamicObject(19059,681.348937,-1280.774780,26.533571,0.000000,0.000000,56.900020);
	tmpobjid = CreateDynamicObject(19062,686.946533,-1274.203369,26.493568,0.000000,0.000000,44.600006);
	tmpobjid = CreateDynamicObject(19060,691.178466,-1272.507202,29.493562,0.000000,0.000000,22.700004);
	tmpobjid = CreateDynamicObject(19061,695.073059,-1269.782226,26.663513,0.000000,0.000000,11.899997);
	tmpobjid = CreateDynamicObject(654,700.958984,-1290.272949,23.071924,360.000000,72.599899,92.999870);
	tmpobjid = CreateDynamicObject(19063,700.087951,-1269.240722,29.009830,0.000000,0.000000,1.300005);
	tmpobjid = CreateDynamicObject(19061,714.197570,-1306.251953,26.423583,0.000000,0.000000,-55.899993);
	tmpobjid = CreateDynamicObject(19060,716.002380,-1305.435424,29.683582,0.000000,0.000000,-48.000007);
	tmpobjid = CreateDynamicObject(19059,717.167602,-1295.048461,29.413574,0.000000,0.000000,28.800016);
	tmpobjid = CreateDynamicObject(19062,720.667968,-1299.314453,29.763544,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,722.134887,-1290.378173,26.413560,0.000000,0.000000,-2.099994);
	tmpobjid = CreateDynamicObject(19063,722.759094,-1289.132690,29.689842,0.000000,0.000000,6.899997);
	tmpobjid = CreateDynamicObject(19061,720.416564,-1285.114868,27.613527,0.000000,0.000000,-95.599929);
	tmpobjid = CreateDynamicObject(19063,718.289062,-1277.003295,29.689842,0.000000,0.000000,42.899993);
	tmpobjid = CreateDynamicObject(19059,719.244689,-1280.375000,26.533571,0.000000,0.000000,28.800016);
	tmpobjid = CreateDynamicObject(19062,704.818237,-1270.772338,26.303565,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,709.692749,-1270.387207,29.693567,0.000000,0.000000,-18.599994);
	tmpobjid = CreateDynamicObject(661,700.895629,-1290.362670,54.582508,1.799999,11.599829,171.700088);
	tmpobjid = CreateDynamicObject(661,700.895629,-1290.362670,54.582508,1.799999,11.599829,119.900085);
	tmpobjid = CreateDynamicObject(661,700.895629,-1290.362670,54.582508,1.799999,11.599829,67.200042);
	tmpobjid = CreateDynamicObject(661,700.574584,-1290.080932,54.262622,1.799999,11.399740,-105.799919);
	tmpobjid = CreateDynamicObject(661,700.895629,-1290.362670,54.582508,1.799999,11.599829,-9.199962);
	tmpobjid = CreateDynamicObject(661,700.648193,-1290.234619,50.676654,1.799999,19.799703,-94.299888);
	tmpobjid = CreateDynamicObject(661,700.648193,-1290.234619,50.676654,1.799999,19.799703,-144.199996);
	tmpobjid = CreateDynamicObject(661,700.648193,-1290.234619,50.676654,1.799999,19.799703,161.199920);
	tmpobjid = CreateDynamicObject(661,700.648193,-1290.234619,50.676654,1.799999,19.799703,68.000068);
	tmpobjid = CreateDynamicObject(661,700.648193,-1290.234619,50.676654,1.799999,19.799703,120.800079);
	tmpobjid = CreateDynamicObject(3675,711.557739,-1285.399902,13.473539,0.000000,0.000000,-90.399986);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(654,700.379028,-1289.383056,58.921855,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(661,700.648193,-1290.234619,50.676654,1.799999,19.799703,14.800033);
	tmpobjid = CreateDynamicObject(661,700.648193,-1290.234619,50.676654,1.799999,19.799703,-38.999973);
	tmpobjid = CreateDynamicObject(661,700.694580,-1290.081176,46.880039,1.799999,32.199821,143.300018);
	tmpobjid = CreateDynamicObject(661,700.694580,-1290.081176,46.880039,1.799999,32.199821,-176.299880);
	tmpobjid = CreateDynamicObject(661,700.694580,-1290.081176,46.880039,1.799999,32.199821,-113.699989);
	tmpobjid = CreateDynamicObject(661,700.694580,-1290.081176,46.880039,1.799999,32.199821,-58.799953);
	tmpobjid = CreateDynamicObject(661,700.694580,-1290.081176,46.880039,1.799999,32.199821,-9.199962);
	tmpobjid = CreateDynamicObject(661,700.694580,-1290.081176,46.880039,1.799999,32.199821,39.200035);
	tmpobjid = CreateDynamicObject(661,700.694580,-1290.081176,46.880039,1.799999,32.199821,88.000030);
	tmpobjid = CreateDynamicObject(661,700.565002,-1290.064331,43.382476,1.799999,49.699939,-86.700019);
	tmpobjid = CreateDynamicObject(661,700.565002,-1290.064331,43.382476,1.799999,49.699939,-45.600082);
	tmpobjid = CreateDynamicObject(661,700.565002,-1290.064331,43.382476,1.799999,49.699939,5.900035);
	tmpobjid = CreateDynamicObject(661,700.565002,-1290.064331,43.382476,1.799999,49.699939,55.100059);
	tmpobjid = CreateDynamicObject(661,700.565002,-1290.064331,43.382476,1.799999,49.699939,115.400001);
	tmpobjid = CreateDynamicObject(661,700.565002,-1290.064331,43.382476,1.799999,49.699939,160.799957);
	tmpobjid = CreateDynamicObject(661,700.565002,-1290.064331,43.382476,1.799999,49.699939,-156.100082);
	tmpobjid = CreateDynamicObject(661,700.388549,-1290.934326,38.746780,1.799999,57.099918,171.299987);
	tmpobjid = CreateDynamicObject(661,700.126403,-1290.606201,38.733600,1.799999,57.099910,218.699905);
	tmpobjid = CreateDynamicObject(661,700.388549,-1290.934326,38.746780,1.799999,57.099918,-102.999992);
	tmpobjid = CreateDynamicObject(661,700.388549,-1290.934326,38.746780,1.799999,57.099918,-52.099990);
	tmpobjid = CreateDynamicObject(661,700.533569,-1290.134887,38.772602,1.799999,57.099918,349.599975);
	tmpobjid = CreateDynamicObject(661,700.388549,-1290.934326,38.746780,1.799999,57.099918,31.199993);
	tmpobjid = CreateDynamicObject(661,700.388549,-1290.934326,38.746780,1.799999,57.099918,77.499977);
	tmpobjid = CreateDynamicObject(661,700.042419,-1290.074951,35.855278,1.799999,69.799949,-117.100067);
	tmpobjid = CreateDynamicObject(661,700.042419,-1290.074951,35.855278,1.799999,69.799949,-80.500091);
	tmpobjid = CreateDynamicObject(661,700.236450,-1289.421264,35.833946,1.799999,69.799949,-33.699947);
	tmpobjid = CreateDynamicObject(661,700.236450,-1289.421264,35.833946,1.799999,69.799949,3.600052);
	tmpobjid = CreateDynamicObject(661,700.042419,-1290.074951,35.855278,1.799999,69.799949,54.799972);
	tmpobjid = CreateDynamicObject(661,700.042419,-1290.074951,35.855278,1.799999,69.799949,106.399971);
	tmpobjid = CreateDynamicObject(661,700.042419,-1290.074951,35.855278,1.799999,69.799949,155.799942);
	tmpobjid = CreateDynamicObject(661,700.236450,-1289.421264,35.833946,1.799999,69.799949,204.800033);
	tmpobjid = CreateDynamicObject(661,700.577392,-1290.047729,33.289466,0.000000,85.299926,26.899959);
	tmpobjid = CreateDynamicObject(661,700.825439,-1291.179931,33.205047,0.000000,85.299926,80.400009);
	tmpobjid = CreateDynamicObject(661,700.577392,-1290.047729,33.289466,0.000000,85.299926,130.099960);
	tmpobjid = CreateDynamicObject(661,700.825439,-1291.179931,33.205047,0.000000,85.299926,171.000122);
	tmpobjid = CreateDynamicObject(19061,714.102233,-1273.480468,26.663513,0.000000,0.000000,-36.299999);
	tmpobjid = CreateDynamicObject(661,700.825439,-1291.179931,33.205047,0.000000,85.299926,-155.199966);
	tmpobjid = CreateDynamicObject(661,700.825439,-1291.179931,33.205047,0.000000,85.299926,-124.699966);
	tmpobjid = CreateDynamicObject(661,700.825439,-1291.179931,33.205047,0.000000,85.299926,-80.600006);
	tmpobjid = CreateDynamicObject(661,700.825439,-1291.179931,33.205047,0.000000,85.299926,-48.200012);
	tmpobjid = CreateDynamicObject(661,700.825439,-1291.179931,33.205047,0.000000,85.299926,-28.800018);
	tmpobjid = CreateDynamicObject(661,700.825439,-1291.179931,33.205047,0.000000,85.299926,357.799987);
	tmpobjid = CreateDynamicObject(654,700.976684,-1290.285400,25.568037,0.000000,78.599929,167.000061);
	tmpobjid = CreateDynamicObject(654,701.366516,-1290.471679,27.073736,0.000000,80.899925,-45.300003);
	tmpobjid = CreateDynamicObject(654,700.847045,-1291.276367,27.073736,0.199999,80.899909,-109.800430);
	tmpobjid = CreateDynamicObject(654,700.583007,-1291.002685,27.073736,0.000000,80.899917,-164.600265);
	tmpobjid = CreateDynamicObject(654,700.829345,-1290.088745,27.073736,0.000000,80.899909,119.299606);
	tmpobjid = CreateDynamicObject(654,700.778930,-1289.738891,27.073736,0.000001,80.899909,65.799972);
	tmpobjid = CreateDynamicObject(654,701.152282,-1289.908081,27.073736,0.000001,80.899909,37.600009);
	tmpobjid = CreateDynamicObject(654,701.366516,-1290.471679,27.073736,0.000000,80.899925,-63.999980);
	tmpobjid = CreateDynamicObject(654,701.366516,-1290.471679,27.073736,0.000000,80.899925,-24.000064);
	tmpobjid = CreateDynamicObject(654,701.347595,-1290.161987,27.073736,0.000001,80.899909,3.500017);
	tmpobjid = CreateDynamicObject(654,700.557434,-1290.543212,27.073736,0.000000,80.899902,140.999725);
	tmpobjid = CreateDynamicObject(654,701.134643,-1290.286376,23.071924,0.000000,78.599929,-50.000080);
	tmpobjid = CreateDynamicObject(654,701.023498,-1290.387084,23.071924,0.000000,78.599929,-85.200096);
	tmpobjid = CreateDynamicObject(654,701.023498,-1290.387084,23.071924,0.000000,78.599929,-117.800056);
	tmpobjid = CreateDynamicObject(654,700.713745,-1290.224121,23.071924,0.000000,78.599929,-141.200180);
	tmpobjid = CreateDynamicObject(654,700.713745,-1290.224121,23.071924,0.000000,78.599929,-175.700088);
	tmpobjid = CreateDynamicObject(654,700.713745,-1290.224121,23.071924,0.000000,78.599929,154.299896);
	tmpobjid = CreateDynamicObject(654,700.713745,-1290.224121,23.071924,0.000000,78.599929,131.199890);
	tmpobjid = CreateDynamicObject(654,700.713745,-1290.224121,23.071924,0.000000,78.599929,105.899887);
	tmpobjid = CreateDynamicObject(654,700.713745,-1290.224121,23.071924,0.000000,78.599929,78.699935);
	tmpobjid = CreateDynamicObject(654,700.958984,-1290.272949,23.071924,0.000000,78.599929,52.499980);
	tmpobjid = CreateDynamicObject(664,700.396240,-1290.288940,12.296320,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(654,700.958984,-1290.272949,23.071924,0.000000,78.599929,29.100002);
	tmpobjid = CreateDynamicObject(654,700.958984,-1290.272949,23.071924,0.000000,78.599929,0.000000);
	tmpobjid = CreateDynamicObject(3675,711.606018,-1278.389282,13.473539,0.000000,0.000000,-90.399986);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(19057,701.488037,-1287.845947,14.383548,0.000000,0.000000,-41.999988);
	tmpobjid = CreateDynamicObject(19056,702.100219,-1286.994384,13.263539,0.000000,0.000000,344.600006);
	tmpobjid = CreateDynamicObject(19055,703.026184,-1288.201049,13.203540,0.000000,0.000000,38.599998);
	tmpobjid = CreateDynamicObject(19055,700.801025,-1287.433227,13.223543,0.000000,0.000000,10.300017);
	// tasty  tiltas
	tmpobjid = CreateDynamicObject(19578,842.482482,-1817.293212,12.087424,0.000000,-0.100118,140.600433);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19578,842.730224,-1816.567382,12.527897,0.000000,-0.100118,140.600433);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,842.439086,-1817.418823,12.187181,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,842.599304,-1817.228637,12.197181,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,842.669311,-1816.688110,12.617191,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,842.859497,-1816.507934,12.617191,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,821.464050,-1822.240234,12.253281,0.000000,-0.100118,80.200012);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,821.349182,-1822.273071,12.367184,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,821.589416,-1822.273071,12.367184,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,823.257873,-1822.201904,12.703774,0.000000,-0.100118,82.199981);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,823.120788,-1822.243041,12.807194,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,823.371032,-1822.243041,12.807194,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,822.259521,-1822.791870,12.812517,0.000000,-0.100118,82.199981);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,822.149902,-1822.893676,12.927197,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,822.400146,-1822.873657,12.927197,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(1598,842.684082,-1817.487792,12.077177,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,842.684082,-1817.487792,11.577165,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,842.924316,-1816.777099,12.527187,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,842.924316,-1816.777099,12.047176,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,842.924316,-1816.777099,11.577165,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,823.249145,-1822.500244,12.707181,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,823.249145,-1822.500244,12.187170,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,823.249145,-1822.500244,11.737159,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,821.477600,-1822.510253,12.237171,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,821.477600,-1822.510253,11.697158,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,822.268371,-1823.120849,12.797183,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,822.268371,-1823.120849,12.287172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,822.268371,-1823.120849,11.767162,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(19294,844.082092,-1981.565307,22.417306,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,854.022949,-1980.391479,22.207252,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,816.119995,-1981.050781,21.937271,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,841.242126,-1955.178955,22.247219,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,833.380981,-1971.382446,47.500961,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,833.441467,-1971.343994,47.500961,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,838.686096,-1965.226806,32.697383,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,835.956970,-1971.981445,46.912960,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,838.669006,-1968.022338,39.339042,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,832.922180,-1965.835571,41.047664,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,836.930664,-1959.758422,24.997327,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(3675,822.624084,-1908.685791,13.843452,-14.799928,-6.299987,178.899200);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(19057,849.175476,-1887.710937,12.567180,0.000000,0.000000,-15.700013);
	tmpobjid = CreateDynamicObject(19056,848.548339,-1889.035034,11.837167,0.000000,0.000000,13.100017);
	tmpobjid = CreateDynamicObject(19057,849.410156,-1890.359375,12.227175,0.000000,0.000000,-14.500005);
	tmpobjid = CreateDynamicObject(19054,850.879760,-1890.145751,12.527179,0.000000,0.000000,-47.299991);
	tmpobjid = CreateDynamicObject(19055,850.061523,-1888.921142,12.067169,0.000000,0.000000,20.400011);
	tmpobjid = CreateDynamicObject(3675,848.013854,-1887.041381,13.157724,-9.399984,-7.299998,159.399795);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,847.973144,-1890.395874,13.979709,-11.699995,-6.299983,-35.200519);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,823.596740,-1912.353027,13.445529,-17.399938,-6.799990,37.099624);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(19058,821.517639,-1911.076538,12.567180,0.000000,0.000000,-20.500009);
	tmpobjid = CreateDynamicObject(19055,823.043212,-1911.462524,12.227176,0.000000,0.000000,21.199953);
	tmpobjid = CreateDynamicObject(11718,825.255737,-1974.065429,13.153654,-14.600008,175.499084,138.199966);
	tmpobjid = CreateDynamicObject(19054,822.756347,-1910.122192,11.927166,0.000000,0.000000,-58.400154);
	tmpobjid = CreateDynamicObject(19066,823.897155,-1972.746948,13.477204,0.000000,0.000000,57.199752);
	tmpobjid = CreateDynamicObject(19066,822.449951,-1969.590087,13.507205,0.000000,0.000000,35.700004);
	tmpobjid = CreateDynamicObject(19585,822.992431,-1970.872070,12.939040,-0.399999,171.000015,26.900003);
	tmpobjid = CreateDynamicObject(19066,822.086120,-1968.073974,13.497204,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19574,825.163757,-1973.803344,12.837214,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,825.414001,-1973.823364,12.837214,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,825.303100,-1973.740966,12.757221,0.000000,-0.100118,74.799758);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19578,824.123046,-1972.432006,13.217171,0.000000,-0.100118,42.500015);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,823.943359,-1972.421997,13.297219,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,824.183593,-1972.582153,13.297219,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,823.348327,-1970.880249,12.746877,0.000000,-0.100118,21.700027);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,823.192626,-1970.810424,12.807208,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,823.402832,-1971.030639,12.807208,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,822.747680,-1969.377319,13.246880,0.000000,-0.100118,21.700027);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,822.612060,-1969.291015,13.327198,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,822.782226,-1969.561279,13.327198,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,822.516235,-1968.097290,13.246193,0.000000,-0.100118,-7.799995);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,822.441894,-1967.959838,13.327198,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,822.441894,-1968.240112,13.327198,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(1598,825.269042,-1974.050537,12.737184,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,823.927734,-1972.699218,13.207195,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,823.927734,-1972.699218,12.697183,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,823.126953,-1971.067626,12.707183,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,822.506347,-1969.536132,13.217195,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,822.506347,-1969.536132,12.697183,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,822.206054,-1968.094726,13.237195,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,822.206054,-1968.094726,12.737184,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,825.269042,-1974.050537,12.207172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,823.927734,-1972.699218,12.207172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,823.126953,-1971.067626,12.207172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(19054,826.587341,-1986.117797,14.797216,0.000000,0.000000,-27.900003);
	SetDynamicObjectMaterial(tmpobjid,0,15042,"svsfsm","AH_filthrug1",0);
	tmpobjid = CreateDynamicObject(19057,826.489807,-1985.333862,13.677206,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,5408,"tempstuff_lae","examball1_LAe",0);
	tmpobjid = CreateDynamicObject(19056,827.283508,-1986.602416,13.677208,0.000000,0.000000,11.999989);
	SetDynamicObjectMaterial(tmpobjid,0,9583,"bigshap_sfw","boatfunnel1_128",0);
	tmpobjid = CreateDynamicObject(19054,825.806274,-1986.568847,13.681543,0.000000,0.000000,-19.200014);
	tmpobjid = CreateDynamicObject(19058,823.619079,-1984.943847,11.927169,0.000000,0.000000,0.800000);
	tmpobjid = CreateDynamicObject(19054,829.064208,-1987.705566,11.957170,0.000000,0.000000,20.100036);
	tmpobjid = CreateDynamicObject(19058,830.016601,-1986.338256,11.927168,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18049,"ammu_twofloor","CJ_BACK_BOARD",0);
	tmpobjid = CreateDynamicObject(19057,828.938110,-1984.944580,11.917168,0.000000,0.000000,-10.800001);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","hatmap2",0);
	tmpobjid = CreateDynamicObject(19055,826.384216,-1983.166259,11.867172,0.000000,0.000000,42.900054);
	tmpobjid = CreateDynamicObject(19056,827.525085,-1984.040893,11.887168,0.000000,0.000000,17.400001);
	SetDynamicObjectMaterial(tmpobjid,0,18996,"mattextures","bluefoil",0);
	tmpobjid = CreateDynamicObject(19054,825.057189,-1983.917602,11.887179,0.000000,0.000000,-12.200008);
	tmpobjid = CreateDynamicObject(19058,827.771057,-1988.296630,12.587183,0.000000,0.000000,-55.000015);
	SetDynamicObjectMaterial(tmpobjid,0,19655,"mattubes","purpledirt1",0);
	tmpobjid = CreateDynamicObject(19055,828.704895,-1986.351074,12.587170,0.000000,0.000000,9.799876);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanathingy",0);
	tmpobjid = CreateDynamicObject(19054,826.272277,-1987.631835,12.567183,0.000000,0.000000,108.299873);
	SetDynamicObjectMaterial(tmpobjid,0,18065,"ab_sfammumain","ab_wallpaper02",0);
	tmpobjid = CreateDynamicObject(19057,827.448425,-1986.864379,12.617184,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19058,827.577148,-1985.401000,12.567183,0.000000,0.000000,27.600011);
	SetDynamicObjectMaterial(tmpobjid,0,14803,"bdupsnew","Bdup2_wallpaper",0);
	tmpobjid = CreateDynamicObject(19055,826.248107,-1984.665771,12.597184,0.000000,0.000000,-9.199974);
	SetDynamicObjectMaterial(tmpobjid,0,16644,"a51_detailstuff","steel256128",0);
	tmpobjid = CreateDynamicObject(19056,825.043640,-1986.809326,12.547183,0.000000,0.000000,34.800022);
	SetDynamicObjectMaterial(tmpobjid,0,18064,"ab_sfammuunits","rubber_mat",0);
	tmpobjid = CreateDynamicObject(19058,824.981018,-1985.360107,12.557183,0.000000,0.000000,23.000001);
	SetDynamicObjectMaterial(tmpobjid,0,18787,"matramps","knot_woodpaint128",0);
	tmpobjid = CreateDynamicObject(19054,826.264343,-1986.019653,12.577183,0.000000,0.000000,-20.800003);
	tmpobjid = CreateDynamicObject(3675,817.134460,-1821.303588,14.707253,0.000000,0.000000,313.899505);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,843.836791,-1818.215820,14.707253,0.000000,0.000000,42.299522);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,849.595642,-1911.933227,14.707253,0.000000,0.000000,67.099639);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,850.395385,-1853.552124,14.707253,0.000000,0.000000,67.099639);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,822.654418,-1876.779663,14.707253,0.000000,0.000000,-71.700225);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(1550,845.721313,-1954.833007,12.857187,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1924,846.073913,-1954.471557,12.597178,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1915,846.353576,-1954.420532,12.587181,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1916,846.446533,-1954.435058,12.577180,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1550,844.973205,-1955.160888,12.600846,73.999839,3.299979,0.000000);
	tmpobjid = CreateDynamicObject(1550,845.552185,-1954.520141,12.527627,0.000000,-90.199935,49.300098);
	tmpobjid = CreateDynamicObject(1575,845.300720,-1954.457641,13.037191,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1575,845.299255,-1954.468017,12.857187,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1575,845.139160,-1954.086425,12.517179,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1575,845.142883,-1954.088867,12.347141,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1550,845.626159,-1953.710693,12.747184,0.000000,0.000000,-124.899955);
	tmpobjid = CreateDynamicObject(1550,844.654785,-1954.177001,12.717176,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1550,845.159179,-1953.706542,12.777185,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1550,844.673217,-1953.701782,12.747184,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19055,846.023010,-1954.811889,14.147215,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14808,"lee_strip2","HS3_wall1",0);
	tmpobjid = CreateDynamicObject(19056,844.982299,-1954.797119,13.857208,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,7985,"vgsswarehse02c","vgsSpinkshop03",0);
	tmpobjid = CreateDynamicObject(11745,846.236694,-1954.428710,12.517142,0.000000,0.000000,90.899887);
	tmpobjid = CreateDynamicObject(19058,844.959960,-1953.627929,13.657201,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,11150,"ab_acc_control","ws_shipmetal5",0);
	tmpobjid = CreateDynamicObject(341,845.498779,-1955.625366,12.488749,32.500007,-66.299926,-3.000000);
	tmpobjid = CreateDynamicObject(19054,845.975463,-1953.616088,14.007213,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1829,845.866943,-1953.850585,12.874355,0.000000,0.000000,-89.299842);
	tmpobjid = CreateDynamicObject(370,844.904846,-1955.674438,13.404367,0.000000,0.000000,-124.700126);
	tmpobjid = CreateDynamicObject(360,845.147766,-1956.237060,13.388103,27.500022,-93.800071,5.599998);
	tmpobjid = CreateDynamicObject(359,844.720947,-1956.207153,13.156328,34.699974,-94.500045,0.000000);
	tmpobjid = CreateDynamicObject(373,846.318786,-1956.114257,13.084360,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1550,844.675170,-1954.864624,12.904356,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(351,845.331787,-1955.632568,12.352204,28.600032,-91.399940,2.400028);
	tmpobjid = CreateDynamicObject(362,845.353942,-1955.492919,12.694356,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(355,844.975646,-1955.743164,12.593172,28.400032,-96.700080,2.600341);
	tmpobjid = CreateDynamicObject(361,844.680114,-1955.091552,12.458389,0.000000,-21.699985,-93.899803);
	tmpobjid = CreateDynamicObject(19055,823.072326,-1833.280883,12.220188,0.000000,0.000000,-38.599918);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanazigzag",0);
	tmpobjid = CreateDynamicObject(19056,824.316833,-1837.310302,11.596252,0.000000,0.000000,-16.099998);
	SetDynamicObjectMaterial(tmpobjid,0,19655,"mattubes","purpledirt1",0);
	tmpobjid = CreateDynamicObject(19057,822.815490,-1837.296264,11.967495,0.000000,0.000000,-48.099941);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanabluish",0);
	tmpobjid = CreateDynamicObject(19054,821.871826,-1836.263061,12.351668,0.199999,0.000000,19.900022);
	tmpobjid = CreateDynamicObject(19055,824.777343,-1835.928222,11.460464,0.000000,0.000000,48.599868);
	tmpobjid = CreateDynamicObject(19058,824.025390,-1834.589355,11.842530,0.000000,0.000000,-84.499885);
	tmpobjid = CreateDynamicObject(19057,822.452758,-1834.655273,12.106769,0.000000,0.000000,32.200031);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanacloth1",0);
	tmpobjid = CreateDynamicObject(19054,823.321655,-1835.943237,11.725062,0.000000,0.000000,-21.799972);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanathingy",0);
	tmpobjid = CreateDynamicObject(19056,849.905883,-1833.097900,12.679657,0.000000,0.000000,1.700015);
	SetDynamicObjectMaterial(tmpobjid,0,18065,"ab_sfammumain","ab_wallpaper02",0);
	tmpobjid = CreateDynamicObject(19054,850.131958,-1833.088256,11.518339,0.000000,0.000000,-67.599952);
	tmpobjid = CreateDynamicObject(19057,848.570434,-1832.266601,12.026222,0.000000,0.000000,-62.199951);
	tmpobjid = CreateDynamicObject(19055,847.944030,-1836.566406,11.294346,0.000000,0.000000,-29.100027);
	SetDynamicObjectMaterial(tmpobjid,0,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(19054,850.375366,-1834.805053,12.179499,0.000000,0.000000,-25.900028);
	SetDynamicObjectMaterial(tmpobjid,0,8391,"ballys01","ballyledge01_128",0);
	tmpobjid = CreateDynamicObject(19058,847.708007,-1833.417724,11.726364,0.000000,0.000000,-28.200023);
	SetDynamicObjectMaterial(tmpobjid,0,16093,"a51_ext","ws_whitewall2_top",0);
	tmpobjid = CreateDynamicObject(19057,849.178771,-1835.732788,11.495265,0.000000,0.000000,-59.299827);
	tmpobjid = CreateDynamicObject(19055,848.973876,-1834.250122,11.841204,0.000000,0.000000,-38.299919);
	tmpobjid = CreateDynamicObject(19054,847.744812,-1834.968994,11.560468,0.000000,0.000000,-66.999938);
	tmpobjid = CreateDynamicObject(19057,827.489685,-1824.423461,12.072734,0.000000,0.000000,19.300006);
	tmpobjid = CreateDynamicObject(19058,825.206420,-1823.881713,11.838419,0.000000,0.000000,-29.000045);
	tmpobjid = CreateDynamicObject(19055,826.064758,-1822.287719,11.258272,0.000000,0.000000,-10.699994);
	tmpobjid = CreateDynamicObject(19054,827.280944,-1822.861694,11.549048,0.000000,0.000000,-25.900024);
	tmpobjid = CreateDynamicObject(19076,826.301025,-1824.042480,11.322486,0.000000,0.000000,-13.899997);
	tmpobjid = CreateDynamicObject(3675,850.340942,-1958.983764,14.707253,0.000000,0.099999,61.399982);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,821.850891,-1963.203247,14.707253,0.000000,0.000000,-35.100101);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(19574,845.168151,-1943.016845,14.507211,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18996,"mattextures","sampred",0);
	tmpobjid = CreateDynamicObject(1736,845.167297,-1943.329101,14.386119,-32.400058,0.000000,178.200149);
	tmpobjid = CreateDynamicObject(19315,845.169372,-1943.549438,13.913019,0.000000,-22.600034,92.999862);
	tmpobjid = CreateDynamicObject(1736,845.878845,-1944.607788,13.898323,327.599945,360.000000,178.200149);
	tmpobjid = CreateDynamicObject(1736,844.625244,-1944.665893,13.870064,-32.400058,0.000000,178.200149);
	tmpobjid = CreateDynamicObject(19315,845.857055,-1944.809082,13.375005,0.000000,-22.600034,92.999862);
	tmpobjid = CreateDynamicObject(19315,844.607727,-1944.873779,13.375005,0.000000,-22.600034,92.999862);
	tmpobjid = CreateDynamicObject(1736,845.889648,-1946.175659,13.107195,-23.300033,0.000000,178.200149);
	tmpobjid = CreateDynamicObject(1736,844.699768,-1946.137084,13.107195,-23.300033,0.000000,178.200149);
	tmpobjid = CreateDynamicObject(19315,844.685729,-1946.385986,12.693885,0.000000,-15.300006,92.999862);
	tmpobjid = CreateDynamicObject(19315,845.854797,-1946.324707,12.693885,0.000000,-15.300006,92.999862);
	tmpobjid = CreateDynamicObject(1736,845.944824,-1947.650146,12.787188,0.000000,0.000000,178.200149);
	tmpobjid = CreateDynamicObject(1736,844.743713,-1947.610595,12.787188,0.000000,0.000000,178.200149);
	tmpobjid = CreateDynamicObject(19315,845.942138,-1947.993896,12.427180,0.000000,0.000000,92.999862);
	tmpobjid = CreateDynamicObject(19315,844.722717,-1948.057006,12.427180,0.000000,0.000000,92.999862);
	tmpobjid = CreateDynamicObject(1736,845.960937,-1949.363769,12.787188,0.000000,0.000000,178.200149);
	tmpobjid = CreateDynamicObject(19315,845.939331,-1949.639160,12.427180,0.000000,0.000000,92.999862);
	tmpobjid = CreateDynamicObject(1736,844.789855,-1949.323120,12.787188,0.000000,0.000000,178.200149);
	tmpobjid = CreateDynamicObject(19315,844.809936,-1949.697387,12.427180,0.000000,0.000000,92.999862);
	tmpobjid = CreateDynamicObject(19054,844.317932,-1985.254882,14.877211,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14714,"vghss1int2","HS2_2Wall5",0);
	tmpobjid = CreateDynamicObject(19058,843.552673,-1984.964721,13.727204,0.000000,0.000000,35.099998);
	SetDynamicObjectMaterial(tmpobjid,0,14736,"whorerooms","AH_flrwll",0);
	tmpobjid = CreateDynamicObject(19056,845.017639,-1984.524536,13.727209,0.000000,0.000000,-46.199993);
	SetDynamicObjectMaterial(tmpobjid,0,7985,"vgsswarehse02c","vgsSpinkshop03",0);
	tmpobjid = CreateDynamicObject(19054,844.702941,-1986.019287,13.727210,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14803,"bdupsnew","Bdup2_wallpaper",0);
	tmpobjid = CreateDynamicObject(19058,846.602661,-1982.599487,12.037188,0.000000,0.000000,-36.100036);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","hatmap1",0);
	tmpobjid = CreateDynamicObject(19056,843.425720,-1987.511596,11.987174,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,841.890502,-1986.756469,11.967171,0.000000,0.000000,26.900033);
	tmpobjid = CreateDynamicObject(19058,840.875854,-1985.649047,11.967174,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","hatmap2",0);
	tmpobjid = CreateDynamicObject(19055,841.372924,-1984.204467,11.937169,0.000000,0.000000,-48.999961);
	tmpobjid = CreateDynamicObject(19056,842.165100,-1982.940551,12.017170,0.000000,0.000000,19.400020);
	SetDynamicObjectMaterial(tmpobjid,0,19129,"dancefloors","dancefloor1",0);
	tmpobjid = CreateDynamicObject(19057,843.473083,-1982.223754,12.027172,0.000000,0.000000,-125.099746);
	tmpobjid = CreateDynamicObject(19058,845.127380,-1982.302978,12.047171,0.000000,0.000000,-51.300033);
	tmpobjid = CreateDynamicObject(19055,843.377075,-1986.106811,12.597184,0.000000,0.000000,-18.000013);
	SetDynamicObjectMaterial(tmpobjid,0,4552,"ammu_lan2","sunsetammu2",0);
	tmpobjid = CreateDynamicObject(19054,842.215148,-1985.344848,12.577183,0.000000,0.000000,-15.300007);
	SetDynamicObjectMaterial(tmpobjid,0,14787,"ab_sfgymbits02","ab_rollmat02",0);
	tmpobjid = CreateDynamicObject(19054,844.814086,-1986.458007,12.617184,0.000000,0.000000,-41.799934);
	SetDynamicObjectMaterial(tmpobjid,0,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(19057,842.909423,-1984.156738,12.567183,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanacloth3",0);
	tmpobjid = CreateDynamicObject(19056,844.194274,-1983.450927,12.577183,0.000000,0.000000,24.999958);
	SetDynamicObjectMaterial(tmpobjid,0,18065,"ab_sfammumain","ab_wallpaper02",0);
	tmpobjid = CreateDynamicObject(19058,844.138366,-1984.936157,12.547183,0.000000,0.000000,-14.800002);
	tmpobjid = CreateDynamicObject(19055,845.678833,-1983.661376,12.517182,0.000000,0.000000,-19.200023);
	tmpobjid = CreateDynamicObject(19054,845.533203,-1985.065063,12.547183,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1021,844.533508,-1951.693237,11.427147,-91.199798,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1021,844.533508,-1951.697875,11.237197,-91.199798,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1021,846.515258,-1951.693481,11.417150,-91.199798,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1021,846.515258,-1951.696899,11.277187,-91.199798,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1021,846.565307,-1955.352050,11.273666,-91.199798,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1021,844.553283,-1955.352050,11.273666,-91.199798,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1134,844.526062,-1955.366088,12.057172,0.000000,0.000000,-179.700332);
	tmpobjid = CreateDynamicObject(1134,844.512939,-1953.365844,12.057172,0.000000,0.000000,179.499618);
	tmpobjid = CreateDynamicObject(1108,846.600708,-1955.349365,12.007184,0.000000,0.000000,-1.300000);
	tmpobjid = CreateDynamicObject(1113,844.557800,-1951.612670,11.997179,0.000000,0.000000,-178.799957);
	tmpobjid = CreateDynamicObject(1108,846.640625,-1952.635009,12.007184,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1113,846.619262,-1951.587280,11.997183,-0.900000,0.000000,180.800018);
	tmpobjid = CreateDynamicObject(1108,846.590698,-1953.365722,12.007184,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1134,846.582824,-1952.101928,12.057172,0.000000,0.000000,179.499618);
	tmpobjid = CreateDynamicObject(1134,846.592590,-1953.423461,12.057172,0.000000,0.000000,179.499618);
	tmpobjid = CreateDynamicObject(1134,846.597717,-1955.385620,12.057172,0.000000,0.000000,179.499618);
	tmpobjid = CreateDynamicObject(1108,844.518737,-1951.854492,12.007184,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1108,844.518737,-1953.395751,12.007184,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1108,844.538757,-1955.347656,12.007184,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1134,844.530395,-1952.694091,12.037172,0.000000,0.000000,179.499618);
	tmpobjid = CreateDynamicObject(2639,845.505676,-1951.613525,12.967192,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19130,"matarrows","red-2-2",0);
	tmpobjid = CreateDynamicObject(2808,845.506225,-1952.555786,12.967192,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19130,"matarrows","red-2-2",0);
	tmpobjid = CreateDynamicObject(19589,845.575500,-1954.616821,12.237178,0.000000,0.000000,-89.799903);
	SetDynamicObjectMaterial(tmpobjid,0,19130,"matarrows","red-2-2",0);
	tmpobjid = CreateDynamicObject(19063,845.184875,-1833.101806,19.545623,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,839.890502,-1833.077758,19.501722,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,834.528015,-1833.077026,19.569982,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,829.113098,-1833.096679,19.541656,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,823.594848,-1833.250488,19.524562,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,839.944458,-1826.919433,19.525163,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,829.139343,-1826.868041,19.532970,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,834.489135,-1826.881958,19.481094,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,823.468078,-1826.752075,19.455549,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,845.315185,-1826.832031,19.501985,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,820.622741,-1977.633422,15.337229,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,820.712280,-1966.327636,15.367214,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,820.456848,-1955.688232,15.487218,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,820.352722,-1944.786254,15.487217,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,820.300476,-1920.201049,15.397208,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,820.341979,-1903.303344,15.397234,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,820.332702,-1889.889770,15.397206,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,852.921386,-1973.050781,15.347223,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,852.774597,-1964.688232,15.417215,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,852.415832,-1952.596313,15.467222,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,852.300292,-1942.324707,15.347191,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,852.249816,-1930.286987,15.377212,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,852.036010,-1895.596557,15.347193,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,820.387023,-1880.242309,15.477203,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,851.994201,-1856.477294,15.317215,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,820.327087,-1852.858520,15.397217,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19057,842.663085,-1825.140502,11.657110,0.000000,0.000000,33.000034);
	tmpobjid = CreateDynamicObject(19058,840.749023,-1824.265747,11.811154,0.000000,0.000000,-144.100463);
	tmpobjid = CreateDynamicObject(19055,841.378479,-1823.015747,11.437976,0.000000,0.000000,-23.100032);
	tmpobjid = CreateDynamicObject(19054,842.697937,-1823.291748,11.151722,0.000000,0.000000,145.899566);
	tmpobjid = CreateDynamicObject(19076,841.864929,-1824.536499,11.322486,0.000000,0.000000,23.600048);
	tmpobjid = CreateDynamicObject(19061,820.293579,-1928.517333,15.317236,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,820.348815,-1935.654052,15.417228,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,852.215148,-1922.618041,15.387193,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,852.205627,-1905.280517,15.457213,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,852.049926,-1885.714599,15.377207,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,852.154113,-1865.447021,15.437221,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,820.337768,-1858.872558,15.347208,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(18838,878.397521,-1977.760253,38.980422,0.000000,91.199836,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,1373,"traincross","rednwhite",0);
	tmpobjid = CreateDynamicObject(18842,886.122802,-1977.743774,5.910178,0.000000,0.000000,179.499252);
	SetDynamicObjectMaterial(tmpobjid,0,1373,"traincross","rednwhite",0);
	tmpobjid = CreateDynamicObject(18838,799.676513,-1979.766723,44.652168,0.000000,90.199851,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,1373,"traincross","rednwhite",0);
	tmpobjid = CreateDynamicObject(18842,791.665283,-1979.796142,11.780245,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,1373,"traincross","rednwhite",0);
	tmpobjid = CreateDynamicObject(19281,834.802062,-1972.239624,55.988739,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(7666,834.819274,-1972.215209,55.938529,0.000000,0.000000,158.799438);
	tmpobjid = CreateDynamicObject(7666,834.819274,-1972.215209,55.938529,0.000000,0.000000,69.999862);
	tmpobjid = CreateDynamicObject(19294,825.079467,-1972.180908,15.907236,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19282,834.969055,-1982.047607,15.457215,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1598,822.506347,-1969.536132,12.207172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,822.206054,-1968.094726,12.207172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(19578,823.638671,-1957.463745,13.205624,0.000000,-0.100118,-7.799995);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,823.613037,-1957.342529,13.317197,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,823.613037,-1957.572753,13.317197,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,824.698059,-1944.479125,13.244401,0.000000,-0.100118,-7.799995);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,824.644042,-1944.342163,13.317197,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,824.624023,-1944.602416,13.317197,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,823.134399,-1902.750122,13.231810,0.000000,-0.100118,-7.799995);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,823.093566,-1902.615356,13.337198,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,823.093566,-1902.875610,13.337198,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,823.506591,-1930.480712,13.239032,0.000000,-0.100118,-7.799995);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,823.473022,-1930.345947,13.317197,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,823.473022,-1930.596191,13.317197,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,821.803405,-1915.551879,13.232541,0.000000,-0.100118,-7.799995);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,821.761352,-1915.425048,13.317197,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,821.761352,-1915.685302,13.317197,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,821.066955,-1889.044433,13.224990,0.000000,-0.100118,-7.799995);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,820.991516,-1888.909301,13.337198,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,820.991516,-1889.179565,13.337198,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,824.466491,-1877.518920,13.228150,0.000000,-0.100118,-7.799995);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,824.413940,-1877.388305,13.337198,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,824.413940,-1877.628540,13.337198,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,822.789672,-1864.731201,13.220005,0.000000,-0.100118,-13.700015);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,822.732482,-1864.605957,13.317197,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,822.732482,-1864.866210,13.317197,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,820.502746,-1843.314208,13.047265,0.000000,-0.100118,-13.700015);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,820.450256,-1843.153442,13.157194,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,820.470275,-1843.423706,13.157194,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,850.027160,-1940.275268,13.156340,0.000000,177.399841,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,850.077209,-1940.404785,13.257196,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,850.077209,-1940.144531,13.257196,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,851.849121,-1924.700195,13.158990,0.000000,177.399841,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,851.917785,-1924.573120,13.257196,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,851.897766,-1924.843383,13.257196,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,849.905456,-1844.745605,13.050606,0.000000,177.399841,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,849.965698,-1844.865112,13.157194,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,849.965698,-1844.594848,13.157194,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,851.816711,-1857.703613,13.277548,0.000000,177.399841,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,851.867553,-1857.819702,13.367198,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,851.867553,-1857.559448,13.367198,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,850.147949,-1873.616577,13.171794,0.000000,177.399841,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,850.196350,-1873.744262,13.277196,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,850.196350,-1873.484008,13.277196,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,852.228576,-1882.078857,13.226208,0.000000,177.399841,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,852.317443,-1882.211669,13.317197,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,852.317443,-1881.951416,13.317197,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,851.417175,-1895.047119,13.209422,0.000000,177.399841,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,851.466613,-1894.929565,13.317197,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,851.446594,-1895.169799,13.317197,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19064,849.165832,-1906.331909,13.467195,0.000000,0.000000,-179.400131);
	tmpobjid = CreateDynamicObject(19578,848.785156,-1906.327758,13.200002,0.000000,177.399841,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19574,848.825866,-1906.450561,13.297197,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,848.825866,-1906.210327,13.297197,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(1598,823.368713,-1957.458374,13.167194,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,823.368713,-1957.458374,12.687183,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,824.399719,-1944.453979,13.187194,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,824.399719,-1944.453979,12.687183,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,823.218566,-1930.469482,13.217195,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,823.218566,-1930.469482,12.717184,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,821.516967,-1915.538452,13.187194,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,821.516967,-1915.538452,12.687183,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,822.838012,-1902.742675,13.217195,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,822.838012,-1902.742675,12.717184,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,820.756042,-1889.023681,13.217195,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,820.756042,-1889.023681,12.707183,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,824.148071,-1877.503173,13.237195,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,824.148071,-1877.503173,12.707183,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,822.488403,-1864.721679,13.207195,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,822.488403,-1864.721679,12.697183,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,820.216369,-1843.300659,13.047191,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,820.216369,-1843.300659,12.547180,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,850.327636,-1940.277832,13.157194,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,850.327636,-1940.277832,12.677183,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,852.138183,-1924.711547,13.137193,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,852.138183,-1924.711547,12.647182,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,849.076843,-1906.334838,13.197194,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,849.076843,-1906.334838,12.717184,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,851.697753,-1895.077880,13.227195,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,851.697753,-1895.077880,12.727184,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,852.548583,-1882.092529,13.217195,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,852.548583,-1882.092529,12.717184,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,850.447265,-1873.616699,13.177194,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,850.447265,-1873.616699,12.717184,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,852.098876,-1857.696899,13.247195,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,852.098876,-1857.696899,12.737183,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,850.197021,-1844.732055,13.037191,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,850.197021,-1844.732055,12.547180,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(7666,834.819274,-1972.215209,55.938529,0.000000,0.000000,-151.200256);
	tmpobjid = CreateDynamicObject(1598,823.368713,-1957.458374,12.197172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,824.399719,-1944.453979,12.197172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,823.218566,-1930.469482,12.197172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,821.516967,-1915.538452,12.197172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,822.838012,-1902.742675,12.197172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,820.756042,-1889.023681,12.197172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,824.148071,-1877.503173,12.197172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,822.488403,-1864.721679,12.197172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,820.216369,-1843.300659,12.057168,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,850.327636,-1940.277832,12.197172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,852.138183,-1924.711547,12.177171,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,849.076843,-1906.334838,12.227172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,851.697753,-1895.077880,12.227172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,852.548583,-1882.092529,12.227172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,850.447265,-1873.616699,12.227172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,852.098876,-1857.696899,12.227172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,850.197021,-1844.732055,12.037168,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(2773,838.458129,-1970.150390,12.467181,0.000000,0.000000,-150.099380);
	tmpobjid = CreateDynamicObject(2773,839.230163,-1971.902954,12.467181,0.000000,0.000000,-162.200042);
	tmpobjid = CreateDynamicObject(2773,839.200500,-1973.726928,12.467181,0.000000,0.000000,158.800186);
	tmpobjid = CreateDynamicObject(2773,838.289550,-1975.400024,12.467181,0.000000,0.000000,144.199493);
	tmpobjid = CreateDynamicObject(2773,836.944335,-1976.747070,12.467181,0.000000,0.000000,125.599205);
	tmpobjid = CreateDynamicObject(2773,830.470703,-1970.791259,12.467181,0.000000,0.000000,-32.000202);
	tmpobjid = CreateDynamicObject(2773,830.055725,-1972.577880,12.467181,0.000000,0.000000,5.099864);
	tmpobjid = CreateDynamicObject(2773,830.610961,-1974.378784,12.467181,0.000000,0.000000,28.399921);
	tmpobjid = CreateDynamicObject(2773,831.759521,-1975.887084,12.467181,0.000000,0.000000,46.499897);
	tmpobjid = CreateDynamicObject(2773,833.344116,-1976.920410,12.467181,0.000000,0.000000,67.099922);
	tmpobjid = CreateDynamicObject(19054,834.385070,-1969.514526,11.967169,0.000000,0.000000,-9.199881);
	tmpobjid = CreateDynamicObject(19054,835.681335,-1969.983886,11.967169,0.000000,0.000000,-28.699954);
	SetDynamicObjectMaterial(tmpobjid,0,8391,"ballys01","ws_floortiles4",0);
	SetDynamicObjectMaterial(tmpobjid,15,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19058,833.664855,-1970.489379,12.287177,0.000000,0.000000,56.399726);
	tmpobjid = CreateDynamicObject(19058,836.700988,-1970.761596,12.287177,0.000000,0.000000,40.899925);
	SetDynamicObjectMaterial(tmpobjid,0,9514,"711_sfw","ws_carpark2",0);
	tmpobjid = CreateDynamicObject(2773,835.189697,-1977.298950,12.467181,0.000000,0.000000,88.499763);
	tmpobjid = CreateDynamicObject(19056,835.023254,-1974.096069,13.627204,0.000000,0.000000,-1.700000);
	SetDynamicObjectMaterial(tmpobjid,0,7526,"vgnlowbild","vegaspillar12_128",0);
	tmpobjid = CreateDynamicObject(19054,833.074951,-1972.297119,13.657208,0.000000,0.000000,3.999999);
	tmpobjid = CreateDynamicObject(19055,832.671264,-1974.325073,12.477181,0.000000,0.000000,-14.900006);
	tmpobjid = CreateDynamicObject(19058,835.528137,-1974.276977,12.497181,0.000000,0.000000,-26.200027);
	tmpobjid = CreateDynamicObject(19056,834.247863,-1973.895507,12.487181,0.000000,0.000000,51.099822);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanaflag",0);
	tmpobjid = CreateDynamicObject(19058,831.846923,-1972.797241,12.517184,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,833.075317,-1973.053955,12.497181,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19055,831.961242,-1971.467773,12.507182,0.000000,0.000000,-6.599996);
	tmpobjid = CreateDynamicObject(18838,799.634216,-1884.281250,35.362236,0.000000,90.199851,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,1373,"traincross","rednwhite",0);
	tmpobjid = CreateDynamicObject(18842,791.665283,-1884.280639,2.400234,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,1373,"traincross","rednwhite",0);
	tmpobjid = CreateDynamicObject(18838,879.162048,-1884.281250,42.275379,0.000000,91.199836,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,1373,"traincross","rednwhite",0);
	tmpobjid = CreateDynamicObject(19056,833.188110,-1971.736938,12.497181,0.000000,0.000000,-13.400012);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanataidai",0);
	tmpobjid = CreateDynamicObject(18842,886.939147,-1884.280639,9.320237,0.000000,0.000000,179.499252);
	SetDynamicObjectMaterial(tmpobjid,0,1373,"traincross","rednwhite",0);
	tmpobjid = CreateDynamicObject(19057,837.345642,-1972.972412,13.647208,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19574,845.672973,-1901.605834,13.357198,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19574,845.672973,-1901.876098,13.357198,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19578,845.589172,-1901.734741,13.255076,0.000000,177.399841,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(1598,845.934509,-1901.768798,13.277196,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(1598,845.934509,-1901.768798,12.757184,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(19058,838.189575,-1973.204956,12.487165,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1598,845.934509,-1901.768798,12.247173,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(19059,825.410034,-1970.171020,26.347324,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,834.939147,-1982.117065,15.447196,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,832.389953,-1964.011962,15.627170,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,825.067565,-1972.220825,15.957168,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,844.973815,-1969.369750,15.387163,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,842.647644,-1962.377197,35.785037,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,847.977050,-1977.473266,35.420291,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,832.430847,-1976.744018,40.768672,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,842.770202,-1987.794311,20.927190,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,834.725402,-1980.159301,37.240913,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,820.903381,-1974.289672,35.307323,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,828.598815,-1974.176025,41.519432,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,833.273803,-1975.139160,44.971069,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(7666,834.819274,-1972.215209,55.938529,0.000000,0.000000,-57.899951);
	tmpobjid = CreateDynamicObject(19059,819.815673,-1973.313476,23.977293,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19281,823.590454,-1833.293334,19.288024,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,828.225280,-1981.605712,35.985218,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,832.905334,-1965.859985,41.074321,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19281,845.153808,-1833.084838,19.587432,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,848.514343,-1968.473022,34.972160,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,842.174621,-1972.226928,41.738517,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19282,839.865051,-1833.117919,19.497142,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,840.460693,-1979.516967,36.938171,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19283,829.156616,-1833.068481,19.300518,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19055,836.815673,-1973.434570,12.487181,0.000000,0.000000,-16.199995);
	tmpobjid = CreateDynamicObject(19062,826.665405,-1980.502197,16.817186,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,816.111572,-1981.051391,21.927293,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,854.015441,-1980.392822,22.197250,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,837.808471,-1982.659301,18.887233,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,844.219665,-1981.578979,22.187322,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,842.906860,-1976.753906,31.762277,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,837.756591,-1982.596801,28.702228,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19284,834.503845,-1833.044555,19.405361,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,829.020568,-1988.323852,22.655298,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,826.957885,-1964.363159,20.247200,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,829.297363,-1966.539916,32.877166,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,824.182922,-1965.843505,36.567203,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,830.189514,-1964.199584,37.217201,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,823.904785,-1972.323852,28.947229,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,837.338256,-1972.053833,12.497181,0.000000,0.000000,12.000007);
	tmpobjid = CreateDynamicObject(19063,827.106201,-1956.395141,22.347208,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,832.866638,-1961.359985,36.297603,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,832.218322,-1963.180541,30.777351,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,836.921081,-1959.682983,24.747323,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,841.627441,-1965.051879,30.477478,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,839.984863,-1962.926513,20.067199,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,816.934692,-1961.989990,22.227262,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,825.443786,-1963.189819,22.067245,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,831.604675,-1955.765869,22.667299,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,841.270629,-1955.154418,22.277198,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,834.972412,-1959.922485,21.617244,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,847.440124,-1968.207397,24.917289,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,852.546020,-1962.395141,21.427242,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,855.678710,-1967.326660,20.917366,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(664,834.560241,-1972.240234,5.977097,0.000000,0.000000,16.300037);
	tmpobjid = CreateDynamicObject(664,834.730041,-1972.055786,5.936926,0.000000,0.000000,0.000000);
	// kamikadze pagr hotel
	tmpobjid = CreateDynamicObject(19055,1724.707275,-1700.926147,12.979991,0.000000,0.000000,-48.100002);
	tmpobjid = CreateDynamicObject(19089,1727.277343,-1708.343750,18.381927,89.199951,2.999999,-3.799998);
	tmpobjid = CreateDynamicObject(655,1722.411499,-1701.740966,8.624071,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,1719.164916,-1702.217163,13.149997,0.000000,0.000000,26.799997);
	tmpobjid = CreateDynamicObject(19059,1719.549072,-1701.207519,16.659996,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,1720.263061,-1702.033935,30.414072,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,1732.849975,-1703.171020,14.876334,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,1733.280273,-1703.751098,13.746329,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,1731.907836,-1702.971801,13.846326,0.000000,0.000000,18.500000);
	tmpobjid = CreateDynamicObject(19059,1700.765380,-1693.832397,20.257997,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","reddirt1",0);
	tmpobjid = CreateDynamicObject(19059,1700.785400,-1695.663208,20.257997,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","bluedirt1",0);
	tmpobjid = CreateDynamicObject(19059,1700.725341,-1697.543212,20.257997,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","yellowdirt1",0);
	tmpobjid = CreateDynamicObject(19059,1700.725341,-1699.373657,20.257997,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","greendirt1",0);
	tmpobjid = CreateDynamicObject(19059,1700.625244,-1702.893920,20.257997,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","yellowdirt1",0);
	tmpobjid = CreateDynamicObject(19059,1700.675292,-1705.104858,20.257997,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","reddirt1",0);
	tmpobjid = CreateDynamicObject(19059,1700.625244,-1707.106079,20.257997,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","greendirt1",0);
	tmpobjid = CreateDynamicObject(19059,1700.625244,-1708.835937,20.257997,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","bluedirt1",0);
	tmpobjid = CreateDynamicObject(19059,1700.475097,-1712.375000,20.257997,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","yellowdirt1",0);
	tmpobjid = CreateDynamicObject(19059,1700.475097,-1714.315673,20.257997,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","purpledirt1",0);
	tmpobjid = CreateDynamicObject(19059,1700.475097,-1715.975708,20.257997,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","bluedirt1",0);
	tmpobjid = CreateDynamicObject(19054,1742.932373,-1686.982666,11.582810,0.000000,0.000000,19.700002);
	tmpobjid = CreateDynamicObject(19059,1700.475097,-1717.546020,20.257997,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","greendirt1",0);
	tmpobjid = CreateDynamicObject(19063,1732.545898,-1706.775268,22.136344,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","yellowdirt1",0);
	tmpobjid = CreateDynamicObject(19089,1732.559692,-1701.686523,22.663505,357.299987,-90.299972,270.000061);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(19063,1732.545898,-1701.754882,22.136344,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","bluedirt1",0);
	tmpobjid = CreateDynamicObject(19063,1732.545898,-1697.014770,22.136344,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","greendirt1",0);
	tmpobjid = CreateDynamicObject(19054,1732.664916,-1699.326049,22.317548,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,1732.664916,-1704.047119,22.317548,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19089,1700.852905,-1692.765869,20.631977,357.299987,269.700042,269.100067);
	tmpobjid = CreateDynamicObject(19089,1700.782104,-1697.315185,20.655784,357.299987,-90.299972,-90.899940);
	tmpobjid = CreateDynamicObject(19089,1700.670532,-1704.523559,20.693504,357.299987,-90.299972,-90.899940);
	tmpobjid = CreateDynamicObject(19089,1700.560546,-1711.623046,20.730648,357.299987,-90.299972,-90.899940);
	tmpobjid = CreateDynamicObject(3675,1701.872192,-1692.408691,17.995779,0.000000,0.000000,89.100120);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,1701.735839,-1701.117919,17.995779,0.000000,0.000000,89.100120);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,1701.588500,-1710.506469,17.995779,0.000000,0.000000,89.100128);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,1701.454101,-1719.055053,17.995779,0.000000,0.000000,89.100128);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,1743.984252,-1696.048095,17.995779,0.000000,0.000000,-90.999954);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,1743.891601,-1711.658691,17.995779,0.000000,0.000000,269.000061);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(2491,1721.370483,-1717.126342,10.061079,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1276,1722.179565,-1712.750000,13.224054,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1274,1731.549072,-1715.823486,9.902285,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(323,1725.063110,-1703.680908,13.609290,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1318,1722.182495,-1708.160400,9.166833,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19055,1710.278808,-1701.946411,13.864064,2.100000,0.000000,-25.400005);
	tmpobjid = CreateDynamicObject(19054,1709.699951,-1703.173217,13.814062,0.000000,0.000000,-33.599998);
	tmpobjid = CreateDynamicObject(19054,1711.547241,-1702.730468,13.804061,0.000000,0.000000,-24.199998);
	tmpobjid = CreateDynamicObject(19056,1712.051391,-1704.532226,12.384064,0.000000,0.000000,-30.699998);
	tmpobjid = CreateDynamicObject(1341,1729.564819,-1713.120971,13.503410,0.000000,0.000000,-135.700027);
	SetDynamicObjectMaterial(tmpobjid,2,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(1340,1713.255126,-1714.595947,13.600000,0.000000,0.000000,-45.700038);
	SetDynamicObjectMaterial(tmpobjid,6,2772,"airp_prop","CJ_red_COUNTER",0);
	tmpobjid = CreateDynamicObject(642,1713.252075,-1714.586303,14.562589,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1744.806762,-1713.930786,20.152820,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19523,"sampicons","reeedgrad32",-65536);
	tmpobjid = CreateDynamicObject(19059,1744.806762,-1710.908691,20.152820,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","yellowdirt1",0);
	tmpobjid = CreateDynamicObject(19059,1744.806762,-1707.840820,20.152820,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","greendirt1",0);
	tmpobjid = CreateDynamicObject(19059,1744.806762,-1717.028686,20.152820,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","bluedirt1",0);
	tmpobjid = CreateDynamicObject(19059,1744.806762,-1718.721557,20.152820,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19655,"mattubes","yellowdirt1",0);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","yellowdirt1",0);
	tmpobjid = CreateDynamicObject(19059,1744.806762,-1690.200561,20.152820,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","purpledirt1",0);
	tmpobjid = CreateDynamicObject(19059,1744.806762,-1695.229614,20.152820,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","greendirt1",0);
	tmpobjid = CreateDynamicObject(19059,1744.806762,-1699.359130,20.152820,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","bluedirt1",0);
	tmpobjid = CreateDynamicObject(19059,1744.806762,-1715.472167,20.152820,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","greendirt1",0);
	tmpobjid = CreateDynamicObject(19059,1744.806762,-1709.390625,20.152820,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","reddirt1",0);
	tmpobjid = CreateDynamicObject(19059,1744.806762,-1697.180175,20.152820,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","reddirt1",0);
	tmpobjid = CreateDynamicObject(19059,1744.806762,-1692.928955,20.152820,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","yellowdirt1",0);
	tmpobjid = CreateDynamicObject(19059,1744.806762,-1706.370239,20.152820,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","purpledirt1",0);
	tmpobjid = CreateDynamicObject(19059,1744.806762,-1701.230102,20.152820,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19523,"sampicons","reeedgrad32",-65536);
	tmpobjid = CreateDynamicObject(643,1711.234741,-1718.255737,11.177577,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1744.806762,-1712.501708,20.152820,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","bluedirt1",0);
	tmpobjid = CreateDynamicObject(19089,1732.559692,-1701.686523,22.663505,357.299987,-90.299972,270.000061);
	tmpobjid = CreateDynamicObject(642,1713.252075,-1714.586303,14.562589,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19089,1732.559082,-1694.906127,22.628040,357.299987,-90.299972,270.000061);
	tmpobjid = CreateDynamicObject(19089,1744.787597,-1709.223022,20.664630,357.299987,-90.299972,270.000061);
	tmpobjid = CreateDynamicObject(19089,1744.787719,-1712.263427,20.680532,357.299987,-90.299972,270.000061);
	tmpobjid = CreateDynamicObject(19089,1744.787475,-1704.181884,20.638271,357.299987,-90.299972,270.000061);
	tmpobjid = CreateDynamicObject(19089,1744.785400,-1688.872558,20.558210,357.299987,-90.299972,270.000061);
	tmpobjid = CreateDynamicObject(19061,1721.956665,-1703.949951,31.760066,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19089,1744.786132,-1696.213012,20.596590,357.299987,-90.299972,270.000061);
	tmpobjid = CreateDynamicObject(19059,1720.041137,-1705.973144,18.940000,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,1723.243896,-1705.559082,24.609907,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1722.160034,-1706.136840,18.937324,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(3675,1744.114135,-1688.588378,17.995779,0.000000,0.000000,-90.999954);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,1743.847656,-1703.877319,17.995779,0.000000,0.000000,-90.999954);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,1743.750610,-1719.787719,17.995779,0.000000,0.000000,269.000061);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(19059,1724.103515,-1705.589233,19.518199,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1719.959472,-1701.282714,24.724086,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1723.756469,-1702.060180,28.307104,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1724.980346,-1703.440185,21.346328,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(655,1721.521484,-1703.939941,10.456870,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1481,1711.840209,-1715.246826,13.229998,0.000000,0.000000,-167.700042);
	tmpobjid = CreateDynamicObject(373,1723.483032,-1710.556884,10.030360,-24.299997,-22.099990,-128.600006);
	tmpobjid = CreateDynamicObject(324,1735.588134,-1712.653930,11.489999,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(324,1719.668334,-1708.093750,9.412166,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(355,1730.974487,-1711.189208,13.570549,-35.500011,-72.899993,-29.700002);
	tmpobjid = CreateDynamicObject(2985,1730.325683,-1710.672729,13.114053,0.000000,0.000000,-147.600006);
	tmpobjid = CreateDynamicObject(349,1731.368041,-1711.375976,13.609196,-43.400001,-77.400001,0.000000);
	tmpobjid = CreateDynamicObject(19054,1732.115234,-1710.846191,15.054063,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1276,1731.828247,-1711.161865,13.935937,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,1732.624877,-1711.346313,13.944063,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,1731.474609,-1710.245605,13.944063,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19065,1726.362182,-1710.493896,14.890013,0.000000,0.000000,-139.499908);
	tmpobjid = CreateDynamicObject(2745,1726.507690,-1710.396118,13.710001,0.000000,0.000000,-49.400009);
	tmpobjid = CreateDynamicObject(658,1722.258178,-1703.229125,1.832825,0.000000,0.000000,-13.300001);
	tmpobjid = CreateDynamicObject(19315,1710.832153,-1710.690673,13.568932,0.000000,0.000000,-52.700012);
	tmpobjid = CreateDynamicObject(19315,1736.125488,-1695.715576,13.544061,0.000000,0.000000,-102.800010);
	tmpobjid = CreateDynamicObject(19315,1735.828857,-1695.349609,13.634062,0.000000,0.000000,-102.800010);
	tmpobjid = CreateDynamicObject(19055,1735.875122,-1694.083251,15.064066,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19055,1735.285278,-1694.083251,13.944065,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19055,1736.445312,-1694.083251,13.944065,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,1709.191040,-1711.437500,14.964060,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,1709.191040,-1712.027709,13.914059,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,1709.191040,-1710.827392,13.914059,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(967,1710.718872,-1705.926879,13.206357,0.000000,0.000000,-60.000030);
	SetDynamicObjectMaterial(tmpobjid,0,18996,"mattextures","sampwhite",0);
	SetDynamicObjectMaterial(tmpobjid,1,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	SetDynamicObjectMaterial(tmpobjid,2,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(967,1708.618652,-1708.936523,13.206357,0.000000,0.000000,-67.700027);
	SetDynamicObjectMaterial(tmpobjid,0,18996,"mattextures","sampwhite",0);
	SetDynamicObjectMaterial(tmpobjid,1,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	SetDynamicObjectMaterial(tmpobjid,2,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(967,1734.868774,-1703.566772,13.206357,0.000000,0.000000,82.600006);
	SetDynamicObjectMaterial(tmpobjid,0,18996,"mattextures","sampwhite",0);
	SetDynamicObjectMaterial(tmpobjid,1,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	SetDynamicObjectMaterial(tmpobjid,2,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(967,1732.179077,-1701.006835,13.206357,0.000000,0.000000,-71.400024);
	SetDynamicObjectMaterial(tmpobjid,0,18996,"mattextures","sampwhite",0);
	SetDynamicObjectMaterial(tmpobjid,1,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	SetDynamicObjectMaterial(tmpobjid,2,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(1946,1732.757812,-1713.412841,14.474064,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18996,"mattextures","sampwhite",0);
	tmpobjid = CreateDynamicObject(1598,1732.750976,-1713.393798,14.047088,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18996,"mattextures","sampwhite",0);
	tmpobjid = CreateDynamicObject(967,1732.856933,-1697.005859,13.206357,0.000000,0.000000,43.599998);
	SetDynamicObjectMaterial(tmpobjid,0,18996,"mattextures","sampwhite",0);
	SetDynamicObjectMaterial(tmpobjid,1,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	SetDynamicObjectMaterial(tmpobjid,2,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(19063,1732.778564,-1713.380615,13.576318,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,18996,"mattextures","sampwhite",0);
	tmpobjid = CreateDynamicObject(19315,1710.484130,-1710.629882,13.568932,0.000000,0.000000,-52.700012);
	tmpobjid = CreateDynamicObject(19066,1732.755981,-1713.351074,14.627459,0.000000,0.000000,-105.399986);
	tmpobjid = CreateDynamicObject(19059,1727.047241,-1694.563232,17.604070,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","greendirt1",0);
	tmpobjid = CreateDynamicObject(19060,1727.376953,-1701.399169,17.814062,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1727.357299,-1704.992675,17.806337,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","reddirt1",0);
	tmpobjid = CreateDynamicObject(19060,1727.154052,-1696.266113,17.724073,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","purpledirt1",0);
	tmpobjid = CreateDynamicObject(19059,1727.305297,-1707.017700,17.886341,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","bluedirt1",0);
	tmpobjid = CreateDynamicObject(19061,1716.486083,-1705.287719,17.934061,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","reddirt1",0);
	tmpobjid = CreateDynamicObject(19060,1716.532592,-1700.837768,17.840007,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","purpledirt1",0);
	tmpobjid = CreateDynamicObject(19063,1716.506103,-1702.925292,17.846338,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","yellowdirt1",0);
	tmpobjid = CreateDynamicObject(19063,1727.225952,-1698.265014,17.726337,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","bluedirt1",0);
	tmpobjid = CreateDynamicObject(19063,1727.345825,-1703.256225,17.856340,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","greendirt1",0);
	tmpobjid = CreateDynamicObject(19089,1716.443603,-1707.102050,18.374639,89.199951,2.999999,-3.799998);
	tmpobjid = CreateDynamicObject(19089,1727.277343,-1708.343750,18.381927,89.199951,2.999999,-3.799998);
	tmpobjid = CreateDynamicObject(19089,1727.380249,-1701.140258,18.280889,89.199951,2.999999,0.000000);
	tmpobjid = CreateDynamicObject(19087,1720.373535,-1737.207397,13.490332,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(2232,1719.921020,-1710.316040,13.169991,0.000000,0.000000,38.999996);
	tmpobjid = CreateDynamicObject(2232,1724.432861,-1710.156616,13.159979,0.000000,0.000000,-40.199993);
	tmpobjid = CreateDynamicObject(1841,1713.109741,-1716.277221,11.426866,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19147,1723.905395,-1718.239257,10.926869,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(18657,1722.332153,-1718.447509,-104.929359,91.499977,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,1738.946533,-1720.323242,13.126863,0.000000,0.000000,-52.499992);
	tmpobjid = CreateDynamicObject(19054,1736.372314,-1719.444213,13.126863,0.000000,0.000000,-50.799991);
	tmpobjid = CreateDynamicObject(19054,1738.407836,-1718.592529,13.126863,0.000000,0.000000,-66.000000);
	tmpobjid = CreateDynamicObject(19054,1737.401733,-1721.344482,13.126863,0.000000,0.000000,-20.099996);
	tmpobjid = CreateDynamicObject(3935,1709.889160,-1709.072753,8.620390,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19632,1713.114379,-1714.376586,13.186248,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1432,1726.263305,-1713.383666,12.658802,0.000000,0.000000,-56.299995);
	tmpobjid = CreateDynamicObject(1432,1729.859741,-1716.376464,12.658802,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(658,1721.868041,-1703.259033,7.012807,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19848,1723.865112,-1723.529296,9.359359,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(2232,1720.554809,-1710.001586,14.359994,0.000000,0.000000,24.999998);
	tmpobjid = CreateDynamicObject(2232,1720.554809,-1710.001586,13.169991,0.000000,0.000000,24.999998);
	tmpobjid = CreateDynamicObject(2232,1723.777099,-1709.884643,14.449994,0.000000,0.000000,-22.599996);
	tmpobjid = CreateDynamicObject(2232,1723.777099,-1709.884643,13.259995,0.000000,0.000000,-22.599996);
	tmpobjid = CreateDynamicObject(2233,1712.814331,-1709.119995,10.237641,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19610,1722.100097,-1709.527343,14.260015,15.200001,-5.099999,0.000000);
	tmpobjid = CreateDynamicObject(19611,1722.089233,-1709.522583,12.639012,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1432,1713.934082,-1718.045043,12.694415,0.000000,0.000000,-98.000000);
	tmpobjid = CreateDynamicObject(1432,1716.720336,-1716.748046,12.694415,0.000000,0.000000,-53.099994);
	tmpobjid = CreateDynamicObject(1432,1717.574707,-1713.631103,12.694415,0.000000,0.000000,0.000000);
	//tmpobjid = CreateDynamicObject(13625,1730.601928,-1699.282470,6.690000,0.000000,0.000000,0.000000); stands
	tmpobjid = CreateDynamicObject(19076,1737.738647,-1719.826904,12.297060,0.000000,0.000000,-62.100006);
	tmpobjid = CreateDynamicObject(2511,1713.234375,-1714.666748,15.182147,-15.099998,11.299999,48.300003);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(2469,1723.734985,-1709.061035,12.022213,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,1722.509033,-1706.360473,13.150003,0.000000,0.000000,7.199999);
	tmpobjid = CreateDynamicObject(2745,1711.095825,-1715.955688,13.760003,0.000000,0.000000,32.099987);
	tmpobjid = CreateDynamicObject(1519,1731.528808,-1707.171264,11.149994,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,1721.980346,-1703.043212,34.951606,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(18695,1720.602905,-1729.908691,13.640469,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19126,1720.448730,-1706.552246,12.965549,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1729.320556,-1708.161621,9.489998,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,1714.621948,-1713.085083,13.119699,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1340,1713.255126,-1714.595947,13.600000,0.000000,0.000000,-45.700038);
	SetDynamicObjectMaterial(tmpobjid,6,2772,"airp_prop","CJ_red_COUNTER",0);
	tmpobjid = CreateDynamicObject(19062,1723.637573,-1701.162963,17.596328,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(2428,1706.843017,-1708.564208,10.665195,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(5730,1735.516723,-1704.631103,4.000000,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19468,1733.615356,-1714.057983,14.764844,0.000000,168.000030,0.000000);
	tmpobjid = CreateDynamicObject(19063,1733.679565,-1714.070678,13.576318,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,18996,"mattextures","sampwhite",0);
	tmpobjid = CreateDynamicObject(1598,1733.696899,-1714.133056,14.019618,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18996,"mattextures","sampwhite",0);
	tmpobjid = CreateDynamicObject(1946,1733.697631,-1714.082885,14.414064,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18996,"mattextures","sampwhite",0);
	tmpobjid = CreateDynamicObject(3054,1736.453002,-1713.938232,10.714352,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1716.411621,-1699.479370,17.480001,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(19063,1727.452392,-1700.200073,17.480001,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,1715.505615,-1699.357055,15.619997,0.000000,0.000000,-90.700088);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,1715.519653,-1707.096801,15.619997,0.000000,0.000000,-94.800041);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,1728.474731,-1708.186767,15.619997,0.000000,0.000000,91.400024);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,1728.163452,-1693.389160,15.619997,0.000000,0.000000,91.400024);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,1728.276245,-1700.058959,15.619997,0.000000,0.000000,91.400024);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(19060,1722.400878,-1700.716430,23.394056,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1720.479736,-1700.632934,21.498119,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1722.345336,-1703.953857,29.566312,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1719.979003,-1704.019287,29.274068,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1721.380004,-1700.962524,26.624073,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1718.319335,-1703.081542,18.534061,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1723.530273,-1701.721191,20.484060,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,1724.654418,-1703.675781,26.854059,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19055,1719.538574,-1704.354370,12.979991,0.000000,0.000000,-10.200000);
	tmpobjid = CreateDynamicObject(19054,1720.194702,-1700.374389,13.150003,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,1726.026000,-1703.104614,13.150003,0.000000,0.000000,-29.799997);
	tmpobjid = CreateDynamicObject(19056,1726.044677,-1702.574829,10.216333,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19055,1724.561157,-1705.411865,12.979991,0.000000,0.000000,-10.200000);
	tmpobjid = CreateDynamicObject(19058,1720.384521,-1706.384521,13.041936,0.000000,0.000000,-22.199998);
	tmpobjid = CreateDynamicObject(19061,1722.702148,-1704.684936,15.875579,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19315,1715.311035,-1708.680297,13.618929,0.000000,0.000000,-20.000009);
	tmpobjid = CreateDynamicObject(19315,1715.261474,-1708.289794,13.448928,0.000000,0.000000,-20.000009);
	tmpobjid = CreateDynamicObject(19315,1715.311035,-1708.680297,13.568932,0.000000,0.000000,340.000000);
	tmpobjid = CreateDynamicObject(19062,1723.637573,-1701.162963,17.596328,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1721.339599,4.000000,16.614061,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1723.956420,-1702.815307,24.216333,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,1724.704467,-1704.246215,18.774061,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1723.099487,-1705.522338,22.238140,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,1720.004028,-1705.995361,21.664077,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1719.567749,-1703.203735,22.746351,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1721.316162,-1700.254516,18.626338,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1720.076293,-1703.344116,15.336334,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1720.775634,-1704.906616,26.636323,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(18670,1725.743041,-1696.139038,13.500000,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(7666,1721.892089,-1703.097778,34.849815,0.000000,0.000000,264.699981);
	tmpobjid = CreateDynamicObject(7666,1721.869750,-1703.066772,34.909866,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(3120,1715.105712,-1705.081787,13.603734,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19608,1710.967041,-1708.724365,7.797307,0.000000,0.000000,45.700050);
	tmpobjid = CreateDynamicObject(658,1721.986572,-1702.773803,7.012807,0.000000,0.000000,-25.800031);
	tmpobjid = CreateDynamicObject(658,1722.258178,-1703.229125,7.012807,0.000000,0.000000,-13.300001);
	tmpobjid = CreateDynamicObject(658,1722.258178,-1702.788818,7.012807,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(660,1713.606933,-1725.630371,-3.177186,0.000000,0.000000,0.000000);
	// Gabe prie hotel tilto
	tmpobjid = CreateDynamicObject(15038,1059.236328,-1811.276977,12.929577,0.000000,0.000000,41.399936);
	tmpobjid = CreateDynamicObject(19315,1058.831176,-1811.055908,13.191506,0.000000,0.000000,-40.399990);
	tmpobjid = CreateDynamicObject(15038,1059.361572,-1811.418823,12.939578,0.000000,0.000000,41.399936);
	tmpobjid = CreateDynamicObject(15038,1059.191772,-1811.316284,12.839575,0.000000,0.000000,41.399936);
	tmpobjid = CreateDynamicObject(15038,1059.519897,-1811.598266,12.839575,0.000000,0.000000,41.399936);
	tmpobjid = CreateDynamicObject(950,1059.278564,-1811.436157,12.979252,0.000000,0.000000,-39.099994);
	tmpobjid = CreateDynamicObject(15038,1059.359741,-1811.428100,12.839575,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(2241,1059.390502,-1811.454345,12.552344,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19315,1059.648803,-1810.972778,13.201503,0.000000,0.000000,-124.699874);
	tmpobjid = CreateDynamicObject(1665,1057.477416,-1784.152099,13.452446,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19897,1057.626953,-1784.000854,13.446533,0.000000,0.000000,-110.400016);
	tmpobjid = CreateDynamicObject(2773,1058.903198,-1806.480346,41.691547,27.599897,2.689998,0.100123);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.899780,-1804.840454,42.548599,27.599897,2.689998,0.100123);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.896728,-1803.183349,43.414905,27.599897,2.689998,0.100123);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.883422,-1801.606079,44.601760,45.699916,2.689998,0.100123);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.876098,-1800.728637,46.480262,83.499938,2.689998,0.100123);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.876098,-1800.517578,48.328300,83.499938,2.689998,0.100123);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.876098,-1800.308227,50.156471,83.499938,2.689998,0.100123);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.876098,-1800.098510,51.994575,83.499938,2.689998,0.100123);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.890258,-1799.667602,53.648513,66.599945,2.689998,0.100123);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.890258,-1798.935791,55.337223,66.599945,2.689998,0.100123);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.909790,-1797.980224,56.491436,32.499961,2.689998,0.100123);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.897094,-1788.764160,41.592559,-29.599988,0.299983,359.800140);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.892578,-1790.372070,42.506378,-29.599988,0.299983,359.800140);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.887329,-1791.989379,43.425113,-29.599988,0.299983,359.800140);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.882446,-1793.146850,45.127536,-80.399963,0.299983,359.800140);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.882446,-1793.466064,47.010803,-80.399963,0.299983,359.800140);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.884643,-1793.782226,48.831214,-82.200019,0.299983,359.800140);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.887817,-1794.115478,50.610736,-79.000030,0.299983,359.800140);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.892211,-1794.437255,52.386608,280.800109,0.299983,359.800140);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.893798,-1794.994140,53.962303,300.599975,0.299983,359.800140);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.891723,-1797.015136,56.624565,325.699951,2.689998,0.100123);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.892089,-1795.961059,55.517055,300.599975,0.299983,359.800140);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(1974,1061.166625,-1783.167236,16.051170,0.000000,0.000000,86.800018);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(1974,1060.986450,-1783.156860,15.541158,0.000000,0.000000,86.800018);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(1974,1061.390502,-1783.120849,15.541158,0.000000,0.000000,86.800018);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19980,1060.713989,-1783.706298,10.488492,0.000000,0.000000,271.300201);
	SetDynamicObjectMaterial(tmpobjid,2,16640,"a51","a51_glass",0);
	tmpobjid = CreateDynamicObject(19980,1062.555786,-1783.668457,10.498484,0.000000,0.000000,91.100112);
	SetDynamicObjectMaterial(tmpobjid,2,16640,"a51","a51_glass",0);
	tmpobjid = CreateDynamicObject(18736,1061.157348,-1783.083740,14.476202,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(3042,1061.220336,-1783.768554,14.500440,0.000000,0.000000,4.900054);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(1240,1061.655639,-1784.721679,14.715803,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1974,1061.150024,-1784.719848,13.581156,0.000000,0.000000,86.800018);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19980,1060.713989,-1783.706298,11.418500,0.000000,0.000000,271.300201);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-93-percent",0);
	tmpobjid = CreateDynamicObject(19980,1062.555786,-1783.668457,11.418500,0.000000,0.000000,91.100112);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-93-percent",0);
	tmpobjid = CreateDynamicObject(19980,1061.663818,-1784.686523,10.478487,0.000000,0.000000,1.200199);
	SetDynamicObjectMaterial(tmpobjid,2,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(19980,1061.663818,-1784.686523,11.418500,0.000000,0.000000,1.200199);
	SetDynamicObjectMaterial(tmpobjid,2,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(8407,1061.626831,-1783.701171,13.793674,0.000000,0.000000,-88.800041);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	SetDynamicObjectMaterial(tmpobjid,1,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	SetDynamicObjectMaterial(tmpobjid,2,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(18736,1048.541259,-1791.583862,11.928715,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(18735,1067.937622,-1805.838012,14.705232,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1240,1066.573730,-1804.836669,14.764159,0.000000,0.000000,42.899944);
	tmpobjid = CreateDynamicObject(1368,1049.605102,-1801.721069,14.096250,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19433,1050.985717,-1800.245971,14.149892,-102.300056,88.199996,-91.699966);
	SetDynamicObjectMaterial(tmpobjid,0,18996,"mattextures","sampred",0);
	tmpobjid = CreateDynamicObject(19433,1048.232299,-1800.244873,14.157055,-72.899948,89.299949,-91.199981);
	SetDynamicObjectMaterial(tmpobjid,0,18996,"mattextures","sampred",0);
	tmpobjid = CreateDynamicObject(19433,1049.182495,-1800.239501,13.449403,0.000003,89.599945,270.299987);
	SetDynamicObjectMaterial(tmpobjid,0,18996,"mattextures","sampred",0);
	tmpobjid = CreateDynamicObject(19089,1048.874389,-1801.999633,13.399861,287.199951,336.100036,343.899963);
	tmpobjid = CreateDynamicObject(1946,1074.708496,-1792.918334,13.091949,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1074.828613,-1792.708129,12.991943,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1074.828613,-1792.487915,12.991943,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1074.378173,-1792.678100,13.091949,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1074.568359,-1792.748168,13.091949,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1074.568359,-1792.437866,13.091949,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1074.498291,-1792.578002,13.001947,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1074.858642,-1792.578002,12.871944,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1074.738525,-1792.347778,12.871944,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1074.288085,-1792.387817,12.871944,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1074.308105,-1792.567993,12.901946,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1074.668457,-1792.858276,13.001947,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1074.758544,-1792.738159,12.951946,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1074.778564,-1792.527954,12.871944,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1074.778564,-1792.437866,12.871944,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1074.648437,-1792.237670,12.871944,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1074.478271,-1792.878295,12.951946,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1074.308105,-1792.698120,12.951946,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1074.388183,-1792.447875,12.871944,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1074.468261,-1792.237670,12.871944,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(19057,1057.473632,-1794.000488,12.594192,0.000000,0.000000,21.700014);
	SetDynamicObjectMaterial(tmpobjid,0,14702,"masmall3int2","HS3_wall6",0);
	SetDynamicObjectMaterial(tmpobjid,1,18996,"mattextures","bluefoil",0);
	tmpobjid = CreateDynamicObject(19056,1061.053710,-1794.291137,12.760492,0.000000,0.000000,46.200031);
	SetDynamicObjectMaterial(tmpobjid,0,14808,"lee_strip2","HS3_wall1",0);
	SetDynamicObjectMaterial(tmpobjid,1,18646,"matcolours","grey-60-percent",0);
	tmpobjid = CreateDynamicObject(19056,1062.725585,-1797.361206,12.680487,0.000000,0.000000,0.799988);
	SetDynamicObjectMaterial(tmpobjid,0,14623,"mafcasmain","casino_carp",0);
	SetDynamicObjectMaterial(tmpobjid,1,9514,"711_sfw","ws_carpark2",0);
	tmpobjid = CreateDynamicObject(19058,1060.976684,-1800.147827,12.685823,0.000000,0.000000,137.500076);
	SetDynamicObjectMaterial(tmpobjid,0,14832,"lee_stripclub","cl_floornew_256",0);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","bluedirt1",0);
	tmpobjid = CreateDynamicObject(19055,1055.699340,-1798.974365,12.783680,0.000000,0.000000,-23.999969);
	SetDynamicObjectMaterial(tmpobjid,0,8391,"ballys01","ballywall02_128",0);
	SetDynamicObjectMaterial(tmpobjid,1,19775,"matcopstuff","copholster1",0);
	tmpobjid = CreateDynamicObject(19055,1055.241333,-1797.295776,12.993685,0.000000,0.000000,-23.699974);
	SetDynamicObjectMaterial(tmpobjid,0,3096,"bbpcpx","blugrad32",0);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","purpledirt1",0);
	tmpobjid = CreateDynamicObject(19054,1060.182495,-1799.411743,14.481701,0.000000,0.000000,96.999992);
	SetDynamicObjectMaterial(tmpobjid,0,14668,"711c","CJ_7_11_TILE",0);
	SetDynamicObjectMaterial(tmpobjid,1,19853,"mihouse1","redwall1",0);
	tmpobjid = CreateDynamicObject(19054,1058.938598,-1799.150756,14.451076,1.600000,9.400001,97.199905);
	SetDynamicObjectMaterial(tmpobjid,0,1949,"barrier","pierlegs",0);
	SetDynamicObjectMaterial(tmpobjid,1,19853,"mihouse1","tilesswimmingpool2",0);
	tmpobjid = CreateDynamicObject(19054,1059.382080,-1800.153808,13.321691,0.000000,0.000000,71.599990);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanazigzag",0);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","greendirt1",0);
	tmpobjid = CreateDynamicObject(19055,1056.269775,-1797.917114,13.403688,0.000000,0.000000,-27.399995);
	SetDynamicObjectMaterial(tmpobjid,0,10810,"ap_build4e","redwhite_stripe",0);
	SetDynamicObjectMaterial(tmpobjid,1,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(19057,1057.343505,-1795.692749,14.454202,0.000000,0.000000,40.800003);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","sm_conc_hatch",0);
	tmpobjid = CreateDynamicObject(19057,1058.609375,-1794.874267,14.454202,0.000000,0.000000,22.600000);
	SetDynamicObjectMaterial(tmpobjid,0,14801,"lee_bdupsmain","Bdup_KitchFloor",0);
	SetDynamicObjectMaterial(tmpobjid,1,18996,"mattextures","sampred",0);
	tmpobjid = CreateDynamicObject(19057,1056.895141,-1795.398315,13.254198,0.000000,0.000000,54.699996);
	SetDynamicObjectMaterial(tmpobjid,0,14476,"carlslounge","ah_blu_paper2",0);
	SetDynamicObjectMaterial(tmpobjid,1,18996,"mattextures","lime",0);
	tmpobjid = CreateDynamicObject(19056,1060.078125,-1795.321411,14.480504,0.000000,0.000000,52.899997);
	SetDynamicObjectMaterial(tmpobjid,0,14706,"labig2int2","HS3_wall2",0);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","purpledirt1",0);
	tmpobjid = CreateDynamicObject(19058,1060.872436,-1798.109619,14.475840,0.000000,0.000000,149.099990);
	SetDynamicObjectMaterial(tmpobjid,0,14415,"carter_block_2","mp_motel_carpet1",0);
	SetDynamicObjectMaterial(tmpobjid,1,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19057,1061.262817,-1796.634155,14.421195,-8.599998,1.399999,-7.199995);
	SetDynamicObjectMaterial(tmpobjid,1,19523,"sampicons","reeedgrad32",-1946157056);
	tmpobjid = CreateDynamicObject(19058,1061.648559,-1798.859375,13.335829,0.000000,0.000000,105.600006);
	SetDynamicObjectMaterial(tmpobjid,0,15041,"bigsfsave","ah_wpaper7",0);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","yellowdirt1",0);
	tmpobjid = CreateDynamicObject(19056,1061.829345,-1796.121582,13.160495,0.000000,0.000000,59.099990);
	SetDynamicObjectMaterial(tmpobjid,0,2823,"gb_kitchtake","deep_red64",0);
	SetDynamicObjectMaterial(tmpobjid,1,19058,"xmasboxes","wrappingpaper1",0);
	tmpobjid = CreateDynamicObject(19056,1059.667358,-1794.685424,13.310498,0.000000,0.000000,52.899997);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","hatmap2",0);
	SetDynamicObjectMaterial(tmpobjid,1,18996,"mattextures","sampwhite",0);
	tmpobjid = CreateDynamicObject(1946,1049.944702,-1783.376464,12.581938,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1049.764526,-1783.376464,12.581938,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1049.564331,-1783.246337,12.581938,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1049.564331,-1782.996093,12.581938,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1049.624389,-1782.805908,12.581938,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1049.734497,-1782.755859,12.581938,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1049.984741,-1782.755859,12.581938,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1049.874633,-1782.755859,12.581938,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1050.184936,-1782.755859,12.581938,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1050.355102,-1782.755859,12.581938,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1050.355102,-1782.936035,12.581938,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1049.784912,-1782.913940,12.721941,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1049.975097,-1782.893920,12.721941,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1368,1046.722900,-1789.661865,13.445367,-1.399990,0.399993,67.000053);
	tmpobjid = CreateDynamicObject(1368,1046.375366,-1792.574096,13.466367,0.000009,0.399993,99.999900);
	tmpobjid = CreateDynamicObject(928,1046.416870,-1790.417358,13.006614,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19057,1061.262817,-1796.634155,14.421195,-8.599998,1.399999,-7.199995);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","Bow_Abpave_Gen",-16777216);
	SetDynamicObjectMaterial(tmpobjid,1,18646,"matcolours","lightblue",0);
	tmpobjid = CreateDynamicObject(19055,1068.468139,-1804.556762,13.270485,0.000000,0.000000,-49.299926);
	SetDynamicObjectMaterial(tmpobjid,0,4552,"ammu_lan2","sunsetammu2",0);
	SetDynamicObjectMaterial(tmpobjid,1,18996,"mattextures","sampred",0);
	tmpobjid = CreateDynamicObject(19055,1068.499145,-1806.597900,13.270485,0.000000,0.000000,-49.299926);
	SetDynamicObjectMaterial(tmpobjid,0,18787,"matramps","knot_woodpaint128",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","sl_vicwall02",0);
	tmpobjid = CreateDynamicObject(3042,1067.535156,-1805.180908,14.530441,0.000000,0.000000,-127.799942);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(1974,1066.880004,-1804.469116,13.681159,0.000000,0.000000,39.900005);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19980,1066.574462,-1804.841674,10.528485,0.000000,0.000000,221.500198);
	SetDynamicObjectMaterial(tmpobjid,2,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(19980,1067.932739,-1804.947875,11.588496,0.000000,0.000000,131.600204);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,2,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(19980,1066.553222,-1806.182006,11.588496,0.000000,0.000000,311.200164);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",-1946157056);
	SetDynamicObjectMaterial(tmpobjid,2,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(19980,1066.574462,-1804.841674,10.528485,0.000000,0.000000,221.500198);
	SetDynamicObjectMaterial(tmpobjid,2,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(19980,1066.574584,-1804.841552,11.458501,0.000000,0.000000,221.500198);
	SetDynamicObjectMaterial(tmpobjid,2,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(3408,1067.530639,-1806.949340,12.575093,0.000000,0.000000,-55.899993);
	tmpobjid = CreateDynamicObject(2856,1046.284301,-1791.360961,12.803020,0.000000,0.299982,68.499977);
	tmpobjid = CreateDynamicObject(2866,1046.037719,-1791.275634,12.786999,0.000000,0.000000,91.100051);
	tmpobjid = CreateDynamicObject(11706,1045.843872,-1791.048095,12.748109,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1946,1050.205322,-1782.893920,12.721941,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(19079,1049.455688,-1782.965209,24.597480,1.500033,-89.500152,-9.199994);
	tmpobjid = CreateDynamicObject(19078,1054.603271,-1814.176391,20.747873,2.700052,269.299987,306.499816);
	tmpobjid = CreateDynamicObject(19078,1077.981079,-1780.483154,20.108530,0.000000,-90.999992,-177.900039);
	tmpobjid = CreateDynamicObject(2856,1045.598510,-1791.449340,12.834849,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1946,1050.205322,-1783.144165,12.781943,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2855,1070.183593,-1794.142822,12.561834,0.000000,0.000000,-93.499938);
	tmpobjid = CreateDynamicObject(3935,1057.304321,-1811.294677,13.698401,0.000000,0.000000,-36.099990);
	tmpobjid = CreateDynamicObject(3927,1059.968383,-1798.186035,19.152526,0.000000,93.500007,75.300018);
	SetDynamicObjectMaterialText(tmpobjid,0,"made by gabe.",90,"Arial",24,1,-1,0,0);
	tmpobjid = CreateDynamicObject(2958,1058.204711,-1784.053833,13.521762,0.599999,-13.000000,5.600002);
	tmpobjid = CreateDynamicObject(3027,1057.944580,-1784.329467,13.453711,88.299880,0.000000,84.500000);
	tmpobjid = CreateDynamicObject(330,1057.905517,-1784.810058,13.414361,93.000022,1.199999,-92.699989);
	tmpobjid = CreateDynamicObject(331,1057.607421,-1784.346801,13.466676,-92.500114,-1.600006,-3.099977);
	tmpobjid = CreateDynamicObject(365,1080.765747,-1803.020874,12.607302,88.999923,102.799987,-7.899997);
	tmpobjid = CreateDynamicObject(365,1080.935913,-1803.270385,12.611227,88.999923,-69.000022,-7.899997);
	tmpobjid = CreateDynamicObject(365,1081.265869,-1803.104370,12.607566,88.999923,34.499996,-7.899997);
	tmpobjid = CreateDynamicObject(1946,1050.034790,-1783.214477,12.691941,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(19076,1049.989501,-1782.977539,12.515272,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19076,1074.580200,-1792.588867,12.631589,0.000000,0.000000,68.500000);
	tmpobjid = CreateDynamicObject(19076,1048.870605,-1802.879272,14.387498,357.700012,69.800010,89.699974);
	tmpobjid = CreateDynamicObject(19066,1049.776000,-1801.824829,14.030453,0.000001,43.900024,-103.000038);
	tmpobjid = CreateDynamicObject(1974,1067.982910,-1801.473510,13.132788,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18064,"ab_sfammuunits","gun_blackbox",0);
	tmpobjid = CreateDynamicObject(1974,1068.012939,-1801.473510,13.202790,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18064,"ab_sfammuunits","gun_blackbox",0);
	tmpobjid = CreateDynamicObject(1974,1068.052978,-1801.473510,13.252791,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18064,"ab_sfammuunits","gun_blackbox",0);
	tmpobjid = CreateDynamicObject(2894,1057.991210,-1784.466430,13.433670,0.000000,0.000000,88.099998);
	tmpobjid = CreateDynamicObject(19058,1050.222778,-1800.111816,14.189338,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanaflag",0);
	SetDynamicObjectMaterial(tmpobjid,1,16644,"a51_detailstuff","steel256128",0);
	tmpobjid = CreateDynamicObject(19058,1050.403076,-1799.641357,15.319340,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanawash1",0);
	SetDynamicObjectMaterial(tmpobjid,1,14668,"711c","CJ_7_11_TILE",0);
	tmpobjid = CreateDynamicObject(19058,1050.252807,-1798.900756,14.189338,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,2591,"ab_partition1","ab_fabricCheck2",0);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","greendirt1",0);
	tmpobjid = CreateDynamicObject(19058,1048.961669,-1800.312133,14.189338,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10765,"airportgnd_sfse","ap_metal1",0);
	SetDynamicObjectMaterial(tmpobjid,1,18996,"mattextures","sampred",0);
	tmpobjid = CreateDynamicObject(19089,1050.368652,-1801.890625,13.455784,287.199951,336.100036,343.899963);
	tmpobjid = CreateDynamicObject(19433,1050.103393,-1800.235229,13.449403,0.000003,89.599945,270.299987);
	SetDynamicObjectMaterial(tmpobjid,0,18996,"mattextures","sampred",0);
	tmpobjid = CreateDynamicObject(1020,1050.309692,-1801.652465,12.457280,270.200775,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1020,1050.309692,-1801.652099,12.317279,270.200775,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1020,1050.309692,-1798.879760,12.496972,270.200775,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1020,1050.309692,-1798.879272,12.326972,270.200775,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1020,1050.309692,-1798.878906,12.136970,270.200775,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1020,1050.309692,-1801.651611,12.117279,270.200775,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1020,1048.898437,-1801.682495,12.487161,-89.899055,0.000000,-18.699993);
	tmpobjid = CreateDynamicObject(1020,1048.898437,-1801.682006,12.307161,270.200775,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1020,1048.898437,-1801.681640,12.097167,270.200775,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1020,1048.898437,-1798.879638,12.456972,270.200775,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1020,1048.898437,-1798.879394,12.316970,270.200775,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1020,1048.898437,-1798.878906,12.106969,270.200775,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1020,1048.898437,-1800.281250,12.502062,270.200775,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1020,1048.898437,-1800.280761,12.312062,270.200775,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1020,1050.299804,-1800.281127,12.462062,270.200775,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1020,1050.299804,-1800.280761,12.282061,270.200775,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1020,1050.299804,-1800.280273,12.102061,270.200775,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1020,1048.898437,-1800.280273,12.102061,270.200775,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1797.670043,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1018,1048.815429,-1799.308105,12.894002,359.899993,359.600006,179.799972);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1797.770141,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1797.890258,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1798.090454,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1798.280639,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1798.440795,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1798.640991,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1798.841186,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1799.021362,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1799.181518,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1799.351684,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1799.531860,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1799.692016,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1799.872192,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1800.042358,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1800.212524,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1800.402709,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1800.582885,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1800.763061,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1048.811645,-1800.953247,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1018,1048.811645,-1801.153442,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1018,1050.397338,-1799.314086,12.902977,-0.099999,-0.399989,179.799972);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1797.680175,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1797.870239,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1798.040649,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1798.220581,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1798.380737,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1798.570922,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1798.751098,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1798.921264,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1799.081420,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1799.251586,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1799.431762,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1799.621948,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1799.792114,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1799.962280,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1800.152465,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1800.652954,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1018,1050.383178,-1801.153442,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1800.953247,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1800.753051,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1800.542846,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1019,1050.383178,-1800.342651,12.901448,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19433,1049.632934,-1800.236694,13.449403,0.000003,89.599945,270.299987);
	SetDynamicObjectMaterial(tmpobjid,0,18996,"mattextures","sampred",0);
	tmpobjid = CreateDynamicObject(1946,1071.582275,-1804.740844,12.881945,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1071.672363,-1804.850952,12.691941,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1071.432128,-1804.850952,12.691941,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1071.752441,-1804.690795,12.691941,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1071.432128,-1804.690795,12.691941,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1056.087524,-1809.440551,12.981947,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1056.217651,-1809.380493,12.801943,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1056.227661,-1809.660766,12.801943,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1055.927368,-1809.640747,12.801943,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1055.927368,-1809.250366,12.801943,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1051.636352,-1785.535888,12.821944,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1046.126220,-1794.677856,13.031949,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1045.946044,-1794.747924,12.821944,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1046.266357,-1794.848022,12.801943,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1046.086181,-1794.487670,12.821944,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1046.286376,-1794.487670,12.821944,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1051.436157,-1785.515869,13.071949,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1051.406127,-1785.395751,12.811944,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1051.536254,-1785.726074,12.821944,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1051.215942,-1785.726074,12.821944,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(19969,1042.151489,-1799.334838,12.678285,0.000000,0.000000,307.299987);
	tmpobjid = CreateDynamicObject(19969,1043.354614,-1772.673828,12.522792,0.000000,0.000000,-91.099929);
	tmpobjid = CreateDynamicObject(19056,1061.398559,-1797.453491,13.310498,0.000000,0.000000,-6.700009);
	SetDynamicObjectMaterial(tmpobjid,0,18065,"ab_sfammumain","gun_ceiling1",0);
	SetDynamicObjectMaterial(tmpobjid,1,10765,"airportgnd_sfse","black64",0);
	tmpobjid = CreateDynamicObject(19054,1058.247192,-1799.447753,13.321691,0.000000,0.000000,71.599990);
	SetDynamicObjectMaterial(tmpobjid,0,14803,"bdupsnew","Bdup2_carpet",0);
	SetDynamicObjectMaterial(tmpobjid,1,18996,"mattextures","sampwhite",0);
	tmpobjid = CreateDynamicObject(19424,1070.630981,-1795.583618,15.727110,-9.998241,358.300048,-5.199950);
	tmpobjid = CreateDynamicObject(19317,1070.793090,-1794.937866,15.729458,-89.799964,-1.700000,24.999998);
	tmpobjid = CreateDynamicObject(19319,1070.260620,-1795.253295,15.728240,270.201751,358.300048,358.200042);
	tmpobjid = CreateDynamicObject(19330,1057.792968,-1783.350585,13.284685,-4.800010,270.700042,182.099975);
	tmpobjid = CreateDynamicObject(1432,1057.751586,-1784.277954,12.819089,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,2,16644,"a51_detailstuff","steel256128",0);
	tmpobjid = CreateDynamicObject(1946,1049.824951,-1783.244262,12.781943,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1212,1072.170166,-1794.673583,12.647461,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1212,1072.210449,-1794.886840,12.647461,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(349,1071.869140,-1795.051025,12.669897,-97.799919,6.100000,91.100059);
	tmpobjid = CreateDynamicObject(1212,1071.921386,-1794.596191,12.647461,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1550,1071.889892,-1795.221801,12.661773,316.800048,358.299987,359.200012);
	tmpobjid = CreateDynamicObject(1575,1071.014892,-1795.577880,12.778284,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1575,1071.014892,-1795.577880,12.668282,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1575,1071.014892,-1795.577880,12.518279,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(2484,1071.145629,-1794.591308,14.244735,0.000000,0.000000,-37.700027);
	tmpobjid = CreateDynamicObject(2464,1072.188720,-1796.089843,12.723639,0.000000,0.000000,-95.600006);
	tmpobjid = CreateDynamicObject(2481,1069.924194,-1795.211425,14.752965,-2.100000,-0.099958,-93.200027);
	tmpobjid = CreateDynamicObject(2469,1069.890380,-1794.442626,14.555288,0.000000,0.000000,292.900054);
	tmpobjid = CreateDynamicObject(1946,1070.515258,-1795.804809,13.956168,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(356,1071.321533,-1797.078369,12.901239,341.700042,268.899993,359.600006);
	tmpobjid = CreateDynamicObject(355,1071.162963,-1796.945556,12.721294,18.100036,190.399993,176.100006);
	tmpobjid = CreateDynamicObject(2028,1069.993408,-1796.291259,13.858980,359.799743,0.199975,270.399780);
	tmpobjid = CreateDynamicObject(346,1069.128051,-1794.585937,13.413911,88.700477,186.299957,173.300094);
	tmpobjid = CreateDynamicObject(346,1069.369873,-1794.548339,13.410247,89.000442,186.299957,356.999816);
	tmpobjid = CreateDynamicObject(344,1069.324829,-1795.272094,13.400342,89.999946,0.000000,173.299911);
	tmpobjid = CreateDynamicObject(19055,1070.535522,-1795.270996,15.211561,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19523,"sampicons","reeedgrad32",-1946157056);
	tmpobjid = CreateDynamicObject(19057,1070.075073,-1794.990722,14.061551,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19523,"sampicons","reeedgrad32",-1946157056);
	tmpobjid = CreateDynamicObject(2773,1078.702758,-1801.851562,13.107216,0.000000,0.000000,179.900253);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1078.698608,-1803.771972,13.107216,0.000000,0.000000,179.900253);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1078.709350,-1798.010742,13.107216,0.000000,0.000000,179.900253);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1078.707153,-1799.932495,13.107216,0.000000,0.000000,179.900253);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(19058,1071.276245,-1795.731445,14.061551,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","purpledirt1",0);
	tmpobjid = CreateDynamicObject(2773,1078.712524,-1796.090698,13.117217,0.000000,0.000000,179.900253);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1078.717651,-1794.172241,13.117217,0.000000,0.000000,179.900253);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1078.720092,-1792.251831,13.117217,0.000000,0.000000,179.900253);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1078.723754,-1790.330566,13.117217,0.000000,0.000000,179.900253);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(19058,1069.984985,-1796.271972,13.271547,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19523,"sampicons","reeedgrad32",-1929379841);
	tmpobjid = CreateDynamicObject(2773,1078.731079,-1785.667724,13.147217,0.000000,0.000000,179.900253);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1078.734008,-1783.746337,13.137217,0.000000,0.000000,179.900253);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1078.738647,-1781.826049,13.137217,0.000000,0.000000,179.900253);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1066.923095,-1809.885864,13.197206,0.000000,0.000000,115.099800);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1071.919799,-1780.641357,13.107215,0.000000,0.000000,268.600097);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1073.850097,-1780.688476,13.107215,0.000000,0.000000,268.600097);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1075.779907,-1780.735595,13.107215,0.000000,0.000000,268.600097);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1077.691162,-1780.782226,13.107215,0.000000,0.000000,268.600097);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1067.973022,-1780.544921,13.107215,0.000000,0.000000,268.600097);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1066.044189,-1780.497802,13.107215,0.000000,0.000000,268.600097);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1064.122558,-1780.450927,13.107215,0.000000,0.000000,268.600097);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1062.203369,-1780.404052,13.107213,0.000000,0.000000,268.600097);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1060.286865,-1780.357177,13.107213,0.000000,0.000000,268.600097);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1058.368408,-1780.310302,13.117208,0.000000,0.000000,268.600097);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1056.450683,-1780.263427,13.147209,0.000000,0.000000,268.600097);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1054.530395,-1780.216552,13.197210,0.000000,0.000000,268.600097);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1052.613281,-1780.169677,13.157205,0.000000,0.000000,268.600097);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1050.691894,-1780.122802,13.157205,0.000000,0.000000,268.600097);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1048.773071,-1780.075927,13.117204,0.000000,0.000000,-91.399909);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1045.476684,-1781.138671,13.117204,0.000000,0.000000,348.000000);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1045.080322,-1783.007446,13.147205,0.000000,0.000000,348.000000);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1046.853759,-1780.029052,13.117204,0.000000,0.000000,-91.399909);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1044.111206,-1787.573120,13.197206,0.000000,0.000000,348.000000);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1043.712768,-1789.450805,13.257207,0.000000,0.000000,348.000000);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1043.311523,-1791.336914,13.287208,0.000000,0.000000,348.000000);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1042.913085,-1793.214477,13.327209,0.000000,0.000000,348.000000);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1042.514648,-1795.091918,13.367210,0.000000,0.000000,-11.999995);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1079.197387,-1804.581787,13.097065,0.499999,0.100000,96.199897);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1077.365112,-1805.052734,13.093491,0.499999,0.100000,111.799842);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1075.605224,-1805.812011,13.127166,0.099999,-0.499999,115.099792);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1073.875732,-1806.623779,13.140502,0.099999,-0.499999,115.099792);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1068.662353,-1809.070678,13.197206,0.000000,0.000000,115.099800);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1072.137939,-1807.438354,13.157207,0.199999,-0.000000,115.099792);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1070.400024,-1808.253662,13.167206,0.000000,0.000000,115.099800);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1063.346191,-1811.419921,13.235822,0.299999,0.000000,111.399833);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1061.567871,-1812.118530,13.245838,0.299999,0.000000,111.399833);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1059.770507,-1812.822021,13.255943,0.299999,0.000000,111.399833);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1057.983398,-1813.523315,13.266005,0.299999,0.000000,111.399833);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1052.360595,-1810.386108,13.367210,0.000000,0.000000,34.099983);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1048.353759,-1804.957763,13.367210,0.000000,0.000000,34.399982);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1046.183959,-1801.790771,13.367210,0.000000,0.000000,34.399986);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1054.513427,-1813.565551,13.367210,0.000000,0.000000,34.399982);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1053.427246,-1811.982299,13.368937,0.100006,0.000000,33.799987);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1056.196166,-1814.223999,13.276070,0.299999,0.000000,111.399833);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1049.457275,-1806.537597,13.364845,359.799987,0.099999,36.799972);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1047.260742,-1803.379394,13.367210,0.000000,0.000000,34.399982);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1042.899047,-1797.045410,13.367210,0.000000,0.000000,34.399986);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1043.975463,-1798.634643,13.367210,0.000000,0.000000,33.599990);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2773,1045.073608,-1800.222412,13.367210,0.000000,0.000000,35.999973);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(19904,1073.330322,-1788.906982,13.061946,0.000000,0.000000,0.199922);
	SetDynamicObjectMaterial(tmpobjid,0,2772,"airp_prop","CJ_red_COUNTER",0);
	tmpobjid = CreateDynamicObject(19056,1069.624633,-1794.940673,12.921543,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19055,1071.056030,-1794.820556,12.921543,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","greendirt1",0);
	tmpobjid = CreateDynamicObject(19054,1071.366333,-1796.322021,12.921543,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","reddirt1",0);
	tmpobjid = CreateDynamicObject(19904,1073.329956,-1788.796875,13.061946,0.000000,0.000000,180.000000);
	SetDynamicObjectMaterial(tmpobjid,0,2772,"airp_prop","CJ_red_COUNTER",0);
	tmpobjid = CreateDynamicObject(1530,1080.042724,-1804.202636,14.767341,0.000000,0.000000,-91.600067);
	tmpobjid = CreateDynamicObject(1240,1081.303588,-1804.306884,14.790943,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(18661,1082.381225,-1804.266723,14.767341,0.000000,0.000000,-91.600067);
	tmpobjid = CreateDynamicObject(363,1073.042846,-1788.898559,13.061949,0.000000,0.000000,-37.500000);
	tmpobjid = CreateDynamicObject(348,1073.578125,-1788.837036,13.121951,0.000000,0.000000,93.900016);
	tmpobjid = CreateDynamicObject(19077,1073.344848,-1788.896972,13.471924,-88.100013,1.899987,-88.400169);
	SetDynamicObjectMaterial(tmpobjid,0,10765,"airportgnd_sfse","black64",0);
	tmpobjid = CreateDynamicObject(19077,1073.344482,-1788.867065,13.481954,271.900024,1.900002,271.599761);
	SetDynamicObjectMaterial(tmpobjid,0,10765,"airportgnd_sfse","black64",0);
	tmpobjid = CreateDynamicObject(19077,1073.345336,-1788.836914,13.471989,-88.100013,1.899987,-88.400169);
	SetDynamicObjectMaterial(tmpobjid,0,10765,"airportgnd_sfse","black64",0);
	tmpobjid = CreateDynamicObject(19033,1073.340209,-1788.786865,13.481954,0.000000,0.000000,89.699851);
	SetDynamicObjectMaterial(tmpobjid,0,10765,"airportgnd_sfse","black64",0);
	tmpobjid = CreateDynamicObject(18931,1073.349365,-1788.830078,13.562060,-21.099988,-90.099998,4.100062);
	SetDynamicObjectMaterial(tmpobjid,0,2772,"airp_prop","CJ_red_COUNTER",0);
	tmpobjid = CreateDynamicObject(18903,1073.339111,-1788.810180,13.309947,98.800086,1.900002,0.199883);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper1",0);
	tmpobjid = CreateDynamicObject(19578,1073.348876,-1788.739135,13.396262,6.000220,0.899941,80.699920);
	SetDynamicObjectMaterial(tmpobjid,0,2772,"airp_prop","CJ_red_COUNTER",0);
	tmpobjid = CreateDynamicObject(19142,1073.331787,-1785.687133,13.085501,-4.600005,-90.999977,-1.100085);
	tmpobjid = CreateDynamicObject(19142,1073.340087,-1785.767211,13.092092,-3.900004,-90.999977,-179.100036);
	tmpobjid = CreateDynamicObject(19578,1073.348876,-1785.800903,13.412106,173.999786,-179.100067,86.699989);
	SetDynamicObjectMaterial(tmpobjid,0,2772,"airp_prop","CJ_red_COUNTER",0);
	tmpobjid = CreateDynamicObject(1974,1073.316650,-1785.787963,13.453968,0.000000,-0.499917,-87.099998);
	SetDynamicObjectMaterial(tmpobjid,0,19775,"matcopstuff","copholster1",0);
	tmpobjid = CreateDynamicObject(1974,1073.385986,-1785.784179,13.453968,0.000000,359.500091,272.899993);
	SetDynamicObjectMaterial(tmpobjid,0,19775,"matcopstuff","copholster1",0);
	tmpobjid = CreateDynamicObject(334,1073.136352,-1785.746337,13.000843,0.100000,244.300048,91.799896);
	tmpobjid = CreateDynamicObject(19942,1073.558471,-1785.755737,13.214735,-17.800003,10.600002,88.299980);
	tmpobjid = CreateDynamicObject(18636,1073.345581,-1785.755737,13.523708,0.000000,-0.499917,-87.099998);
	tmpobjid = CreateDynamicObject(19775,1073.407958,-1785.893310,13.247894,-20.300020,-0.400000,0.000000);
	tmpobjid = CreateDynamicObject(2114,1073.339965,-1788.866943,13.391957,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2114,1073.339965,-1788.866943,13.121951,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1073.339965,-1788.866943,12.821944,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2114,1073.339965,-1785.726074,13.381956,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2114,1073.339965,-1785.726074,13.161951,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1073.339965,-1785.726074,12.821944,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(357,1068.093627,-1801.060058,13.484097,1.700000,325.899993,184.699935);
	tmpobjid = CreateDynamicObject(371,1068.348022,-1801.478271,13.211899,0.000000,0.000000,88.799919);
	tmpobjid = CreateDynamicObject(334,1068.222412,-1801.693481,13.182565,-0.599999,-26.800006,92.900108);
	tmpobjid = CreateDynamicObject(334,1068.070434,-1801.248535,13.174122,-0.599999,-26.800006,-79.599983);
	tmpobjid = CreateDynamicObject(1974,1068.062988,-1801.413452,13.492796,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,16644,"a51_detailstuff","steel256128",0);
	tmpobjid = CreateDynamicObject(1974,1068.062988,-1801.523559,13.492796,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,16644,"a51_detailstuff","steel256128",0);
	tmpobjid = CreateDynamicObject(1946,1068.167114,-1801.492187,12.821944,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(2114,1068.151855,-1801.483886,13.442822,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(1946,1068.167114,-1801.492187,13.131953,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(19584,1068.166503,-1801.680175,13.600299,164.200042,0.000000,5.800000);
	tmpobjid = CreateDynamicObject(19061,1053.181030,-1811.835449,20.240320,0.000000,0.000000,35.399993);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","bluedirt1",0);
	tmpobjid = CreateDynamicObject(19059,1050.855834,-1808.567871,20.240320,0.000000,0.000000,35.399993);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","yellowdirt1",0);
	tmpobjid = CreateDynamicObject(19062,1048.517822,-1805.272338,20.240320,0.000000,0.000000,35.399993);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","greendirt1",0);
	tmpobjid = CreateDynamicObject(19061,1046.279052,-1802.115722,20.240320,0.000000,0.000000,35.399993);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","bluedirt1",0);
	tmpobjid = CreateDynamicObject(19060,1044.006347,-1798.908935,20.240320,0.000000,0.000000,35.399993);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","purpledirt1",0);
	tmpobjid = CreateDynamicObject(19062,1042.929321,-1792.743530,20.172849,0.000000,0.000000,348.300018);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","greendirt1",0);
	tmpobjid = CreateDynamicObject(19061,1043.811889,-1788.341430,20.172849,0.000000,0.000000,348.300018);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","reddirt1",0);
	tmpobjid = CreateDynamicObject(19059,1044.768676,-1783.616455,20.172849,0.000000,0.000000,348.300018);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","yellowdirt1",0);
	tmpobjid = CreateDynamicObject(1974,1067.999511,-1805.570068,16.071157,0.000000,0.000000,39.900005);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(1974,1067.871093,-1805.651611,15.701152,0.000000,0.000000,39.900005);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(1974,1068.124877,-1805.439208,15.701152,0.000000,0.000000,39.900005);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(19059,1050.069458,-1780.153320,20.141572,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","purpledirt1",0);
	tmpobjid = CreateDynamicObject(19060,1054.503051,-1780.223388,20.061571,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","yellowdirt1",0);
	tmpobjid = CreateDynamicObject(19062,1058.755981,-1780.283447,19.951568,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","bluedirt1",0);
	tmpobjid = CreateDynamicObject(19061,1063.039062,-1780.353515,19.851566,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","greendirt1",0);
	tmpobjid = CreateDynamicObject(19059,1066.832641,-1780.413574,19.801565,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","purpledirt1",0);
	tmpobjid = CreateDynamicObject(19061,1070.992919,-1780.443603,19.701562,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","reddirt1",0);
	tmpobjid = CreateDynamicObject(19060,1075.355957,-1780.503662,19.621561,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","yellowdirt1",0);
	tmpobjid = CreateDynamicObject(19059,1078.511230,-1800.937377,16.301788,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","yellowdirt1",0);
	tmpobjid = CreateDynamicObject(19062,1078.521240,-1796.183227,16.981803,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","reddirt1",0);
	tmpobjid = CreateDynamicObject(19061,1078.521240,-1792.102661,17.511816,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","purpledirt1",0);
	tmpobjid = CreateDynamicObject(19060,1078.581298,-1788.012451,18.031827,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","greendirt1",0);
	tmpobjid = CreateDynamicObject(19059,1078.581298,-1783.718627,18.621841,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","bluedirt1",0);
	tmpobjid = CreateDynamicObject(19062,1075.120117,-1805.727905,16.103942,0.000000,0.000000,-66.900024);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","reddirt1",0);
	tmpobjid = CreateDynamicObject(19061,1071.898803,-1807.145141,16.333948,0.000000,0.000000,-66.900024);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","purpledirt1",0);
	tmpobjid = CreateDynamicObject(19060,1068.618774,-1808.576904,16.573953,0.000000,0.000000,-66.900024);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","yellowdirt1",0);
	tmpobjid = CreateDynamicObject(19059,1065.115356,-1810.125854,16.793958,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","greendirt1",0);
	tmpobjid = CreateDynamicObject(19063,1061.081909,-1811.876831,17.073965,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","purpledirt1",0);
	tmpobjid = CreateDynamicObject(19121,1046.680297,-1802.611816,13.207202,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19121,1051.823242,-1809.603515,13.207202,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19121,1062.434082,-1811.751831,13.057199,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19121,1071.246582,-1807.830322,13.037199,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19121,1078.689331,-1795.147949,12.987208,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19089,1078.545166,-1789.692382,18.348608,-74.999992,59.599834,60.149578);
	tmpobjid = CreateDynamicObject(19121,1078.689331,-1786.645507,12.987208,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19121,1072.889160,-1780.704589,12.917206,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19121,1063.170288,-1780.444335,12.987208,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19121,1053.560913,-1780.244140,13.047209,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19121,1044.899536,-1783.932983,12.957207,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19121,1043.488159,-1790.393676,13.167211,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1056.820434,-1813.728149,17.383972,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","reddirt1",0);
	tmpobjid = CreateDynamicObject(19089,1078.292846,-1780.551391,20.065485,1.699999,91.200004,-0.799999);
	tmpobjid = CreateDynamicObject(19089,1074.524536,-1780.500976,20.144401,1.699999,91.200004,-0.799999);
	tmpobjid = CreateDynamicObject(19089,1067.329345,-1780.405273,20.295116,1.699999,91.200004,-0.799999);
	tmpobjid = CreateDynamicObject(19089,1060.252563,-1780.310424,20.443336,1.699999,91.200004,-0.799999);
	tmpobjid = CreateDynamicObject(19089,1052.975952,-1780.212158,20.595727,1.699999,91.200004,-0.799999);
	tmpobjid = CreateDynamicObject(19089,1043.992065,-1787.428344,20.725999,270.000000,275.750000,84.250000);
	tmpobjid = CreateDynamicObject(19089,1043.655151,-1789.093872,20.725999,270.000000,342.500000,151.000000);
	tmpobjid = CreateDynamicObject(19089,1042.188476,-1796.308227,20.725999,270.000000,275.750000,84.250000);
	tmpobjid = CreateDynamicObject(19089,1078.593872,-1780.770751,19.527334,-74.999992,59.599834,60.149578);
	tmpobjid = CreateDynamicObject(19089,1078.584960,-1782.465942,19.303375,-74.999992,59.599834,60.149578);
	tmpobjid = CreateDynamicObject(19089,1078.545166,-1789.692382,18.348608,-74.999992,59.599834,60.149578);
	tmpobjid = CreateDynamicObject(19089,1078.505126,-1796.967529,17.387275,-74.999992,59.599834,60.149578);
	tmpobjid = CreateDynamicObject(3675,1044.958129,-1780.072753,17.887418,0.199996,359.899993,87.999855);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,1078.680175,-1779.903930,17.955774,0.199996,359.899993,-2.900123);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(19089,1055.245361,-1814.438720,18.028635,-84.100387,-51.949913,61.549789);
	tmpobjid = CreateDynamicObject(19089,1071.703857,-1807.231933,16.888334,-84.100387,-51.949913,61.549789);
	tmpobjid = CreateDynamicObject(19089,1058.274047,-1813.114013,17.818943,-84.100387,-51.949913,61.549789);
	tmpobjid = CreateDynamicObject(19089,1064.992675,-1810.171875,17.353317,-84.100387,-51.949913,61.549789);
	tmpobjid = CreateDynamicObject(19089,1050.638916,-1808.376220,20.725999,270.000000,342.500000,17.499998);
	tmpobjid = CreateDynamicObject(19089,1046.416870,-1802.348266,20.725999,270.000000,342.500000,17.499998);
	tmpobjid = CreateDynamicObject(19089,1042.188476,-1796.308227,20.725999,270.000000,342.500000,17.499998);
	tmpobjid = CreateDynamicObject(3675,1054.465332,-1814.984252,18.027431,0.199996,359.899993,112.299865);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(8407,1067.233032,-1805.562377,13.793674,0.000000,0.000000,-48.600002);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	SetDynamicObjectMaterial(tmpobjid,1,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	SetDynamicObjectMaterial(tmpobjid,2,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3675,1041.458374,-1796.444213,18.083427,0.199996,359.899993,112.299865);
	SetDynamicObjectMaterial(tmpobjid,0,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(19632,1048.800292,-1791.335693,12.741888,0.000000,0.000000,89.599914);
	tmpobjid = CreateDynamicObject(19632,1048.801391,-1791.376831,12.751888,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,1057.229614,-1798.682250,13.371692,0.000000,0.000000,64.900032);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanathingy",0);
	tmpobjid = CreateDynamicObject(19057,1058.269042,-1794.998413,13.254198,0.000000,0.000000,18.800004);
	SetDynamicObjectMaterial(tmpobjid,0,14707,"labig3int2","HS2_3Carpet1",0);
	SetDynamicObjectMaterial(tmpobjid,1,19655,"mattubes","greendirt1",0);
	tmpobjid = CreateDynamicObject(19056,1060.650146,-1795.590820,13.310498,0.000000,0.000000,52.899997);
	SetDynamicObjectMaterial(tmpobjid,0,14760,"sfhosemed2","ah_wpaper5",0);
	SetDynamicObjectMaterial(tmpobjid,1,18787,"matramps","redrailing",0);
	tmpobjid = CreateDynamicObject(19058,1060.316772,-1799.054687,13.335829,0.000000,0.000000,126.599998);
	SetDynamicObjectMaterial(tmpobjid,0,14815,"whore_main","WH_Wall",0);
	tmpobjid = CreateDynamicObject(19055,1056.543701,-1796.629272,13.403688,0.000000,0.000000,-27.399995);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanacloth4",0);
	tmpobjid = CreateDynamicObject(2773,1068.474975,-1796.889648,31.612815,-86.300048,4.399974,-86.099922);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1068.353637,-1796.897338,33.498893,-86.300048,4.399974,-86.099922);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1068.235595,-1796.905273,35.335075,-86.300048,4.399974,-86.099922);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1068.114746,-1796.913452,37.211174,-86.300048,4.399974,-86.099922);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1067.820434,-1796.967773,38.952148,-75.500167,4.399974,-83.699935);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1067.197265,-1797.045043,40.555526,-62.500114,4.399974,-83.599937);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1066.333862,-1797.141235,42.223068,-62.500114,4.399974,-83.599937);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1065.283813,-1797.255004,43.422241,323.299896,4.399974,276.800018);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1064.106201,-1797.400024,45.153499,285.699981,4.399975,276.799987);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1063.612304,-1797.466918,46.945854,285.699981,4.399975,276.799987);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1063.113769,-1797.525146,48.736797,285.699951,4.399979,276.799987);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1062.624511,-1797.588134,50.541023,285.699951,4.399979,276.799987);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1062.159423,-1797.647094,52.384910,283.200012,0.699984,275.199951);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1061.526123,-1797.629638,53.957458,300.599975,0.299985,270.000000);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1060.588623,-1797.587768,55.577983,300.599975,0.299982,266.600036);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1059.503417,-1797.471191,56.626979,331.499969,2.689997,265.200134);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1048.377441,-1796.745849,30.389785,276.899963,5.199958,84.699989);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1048.599121,-1796.767333,32.226398,276.899963,5.199958,84.699989);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1048.822387,-1796.790039,34.072849,276.899963,5.199958,84.699989);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1049.045532,-1796.812133,35.919326,276.899963,5.199958,84.699989);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1049.265869,-1796.834228,37.745967,276.899963,5.199958,84.699989);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1049.489379,-1796.856933,39.592449,-83.099960,5.199975,84.699974);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1049.981689,-1796.906005,41.225753,-64.400054,5.199975,84.599975);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1050.986450,-1797.013916,42.450950,-36.700099,4.399976,83.200042);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1052.480590,-1797.203979,43.575126,-36.700099,4.399976,83.200042);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1053.653198,-1797.351806,45.249927,-74.300018,4.399976,83.200042);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1054.155029,-1797.411376,47.050186,-74.300018,4.399976,83.200042);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1054.675292,-1797.464599,48.835201,-74.300018,4.399976,83.200042);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1055.176757,-1797.514648,50.625637,-74.300018,4.399976,83.200042);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1055.654541,-1797.518920,52.398853,-76.799972,0.699983,84.800178);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1056.297363,-1797.497802,53.970333,300.599975,0.299982,90.200103);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1057.249877,-1797.506469,55.579910,-59.400016,0.299983,90.200103);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(2773,1058.381591,-1797.502197,56.622470,-28.500026,2.699985,90.700103);
	SetDynamicObjectMaterial(tmpobjid,0,16640,"a51","a51_glass",0);
	SetDynamicObjectMaterial(tmpobjid,2,18646,"matcolours","grey-40-percent",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(19060,1058.817260,-1803.339477,20.855432,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19295,1058.926513,-1797.465942,59.691486,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(7666,1058.926513,-1797.465942,59.691486,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19290,1058.882324,-1797.312744,17.057535,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19290,1058.711425,-1796.846435,23.748281,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19290,1058.530273,-1798.300903,34.992435,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19290,1058.931274,-1795.732788,43.810420,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(7666,1058.926513,-1797.465942,59.691486,0.000000,0.000000,135.000000);
	tmpobjid = CreateDynamicObject(7666,1058.926513,-1797.465942,59.691486,0.000000,0.000000,45.000000);
	tmpobjid = CreateDynamicObject(7666,1058.926513,-1797.465942,59.691486,0.000000,0.000000,90.000000);
	tmpobjid = CreateDynamicObject(19062,1055.905395,-1800.301147,18.784803,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1068.386474,-1797.307739,16.992774,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1060.179443,-1795.839965,52.270992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1059.716186,-1797.118896,47.086265,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1059.960083,-1799.897827,48.771522,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1057.214965,-1798.359985,47.615261,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1064.522705,-1799.515991,42.723796,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1063.184082,-1802.698730,41.996810,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1058.037963,-1799.862670,44.551002,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1056.081054,-1806.987060,40.986145,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1053.335937,-1799.070556,43.325817,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1054.113403,-1795.756835,44.787887,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1060.897583,-1792.036010,44.875946,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1056.248046,-1791.719238,45.648635,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,1058.200561,-1792.942138,43.678009,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1064.092163,-1793.548217,42.983177,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1072.182495,-1793.606201,36.281364,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,1064.619262,-1789.899658,41.241218,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1064.785278,-1795.548828,40.148132,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1063.348632,-1799.518066,31.481407,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1064.920288,-1799.741943,35.943477,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1061.906860,-1800.982788,32.018550,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1061.092895,-1802.148559,36.562881,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,1058.918579,-1805.309204,34.767814,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1057.953613,-1803.854003,31.529697,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1055.235839,-1802.407470,39.809505,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1055.864379,-1805.774658,34.958759,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1052.428710,-1803.768676,32.837993,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,1052.954589,-1804.226684,30.580257,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1052.037841,-1800.742553,36.073822,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1051.195800,-1795.380737,39.454948,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,1046.369750,-1799.515136,37.071983,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1050.716796,-1797.269042,35.021343,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1048.801513,-1797.016601,29.729412,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1056.479125,-1790.904174,39.824024,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1053.699707,-1788.038452,29.711887,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1053.410156,-1791.673706,33.406375,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1055.352172,-1796.218017,36.353984,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1058.931396,-1791.527832,33.846088,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1059.485961,-1795.848632,36.383735,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1065.623657,-1794.361083,32.548885,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1068.768310,-1787.193359,28.473638,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1062.273925,-1788.278808,31.760734,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,1063.054687,-1793.078125,32.555885,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1061.149414,-1780.580810,26.640310,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1071.636474,-1782.837402,26.079515,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,1063.879882,-1787.534545,26.626337,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1065.779907,-1790.382080,17.198354,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1062.239013,-1793.930175,25.573949,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,1063.769531,-1795.213378,28.891910,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1066.148437,-1790.046752,21.036556,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1066.734741,-1793.763671,21.772006,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1072.438964,-1793.287231,25.410831,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1067.943237,-1800.841552,19.906501,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,1074.974975,-1803.535156,24.457517,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1068.345214,-1800.968017,23.958921,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1063.113159,-1801.519775,25.494581,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1062.751220,-1801.181884,17.217151,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1062.585571,-1805.361328,23.895854,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1058.947875,-1804.135253,17.733724,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1066.414428,-1806.550781,28.451629,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,1061.980468,-1806.577148,26.562515,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,1058.876342,-1806.751953,24.157245,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1054.615478,-1812.319824,27.574199,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1055.176147,-1807.743164,20.446456,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1055.360107,-1807.099853,25.045295,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1051.178100,-1809.190795,24.788600,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1045.776123,-1808.463500,27.424549,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1053.743164,-1802.419799,26.350824,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1051.674194,-1804.516113,24.427629,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1049.647583,-1801.801635,23.940773,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1048.615600,-1800.062377,27.103805,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1049.816894,-1797.309204,17.375957,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,1043.043090,-1795.100341,26.852203,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1039.666381,-1800.422241,23.196105,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1048.335815,-1797.304809,24.364557,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1052.741821,-1797.279785,25.418121,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1047.144409,-1790.807739,26.224275,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1051.394653,-1794.747802,22.961696,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1054.543334,-1792.970214,26.821363,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1043.017456,-1788.375610,24.315776,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,1052.000610,-1794.973022,19.528669,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,1054.387451,-1792.836425,21.028137,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1055.278320,-1793.671875,17.237827,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1050.850341,-1783.972656,27.328735,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1059.495361,-1783.150634,27.973855,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1055.588867,-1780.860107,23.822298,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1057.465942,-1794.285156,28.763256,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,1058.875366,-1791.785278,25.772722,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1054.347290,-1787.701416,23.619075,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19063,1054.916625,-1788.840209,19.278015,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,1058.866821,-1791.652099,20.137472,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,1058.871459,-1788.983886,16.785663,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(974,1045.983764,-1829.025756,12.418185,85.499542,359.399993,358.299987);
	tmpobjid = CreateDynamicObject(664,1058.671630,-1797.110961,7.060999,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(664,1058.671020,-1797.630981,9.670000,0.000000,0.000000,69.899002);
	// Baben airport
	tmpobjid = CreateDynamicObject(695,1905.635986,-2277.303710,1.430000,0.000000,0.000000,165.899948);
	tmpobjid = CreateDynamicObject(695,1912.821289,-2280.196777,1.730000,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1290,1970.259887,-2289.626953,13.539985,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1290,1970.212280,-2265.731445,13.539985,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1290,1970.272216,-2278.393310,13.539985,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(738,1978.180297,-2272.626220,12.760005,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16640,"a51","a51_glass",0);
	tmpobjid = CreateDynamicObject(738,1978.173095,-2284.797363,12.760005,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16640,"a51","a51_glass",0);
	tmpobjid = CreateDynamicObject(695,1901.874389,-2298.620117,1.430000,0.000000,0.000000,45.500000);
	tmpobjid = CreateDynamicObject(695,1994.100463,-2267.687011,1.430000,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(695,1906.856445,-2345.912109,1.430000,0.000000,0.000000,71.599998);
	tmpobjid = CreateDynamicObject(695,1994.100463,-2285.097412,1.430000,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(695,1908.300903,-2324.275878,1.430000,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1290,1938.109863,-2321.433105,13.539985,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1290,1937.879028,-2299.877197,13.539985,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1290,1938.109863,-2310.712158,13.539985,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1290,1937.879028,-2289.641845,13.539985,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1290,1937.879028,-2277.246582,13.539985,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(738,1929.409301,-2272.626220,12.760005,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16640,"a51","a51_glass",0);
	tmpobjid = CreateDynamicObject(738,1929.428710,-2284.748779,12.760005,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16640,"a51","a51_glass",0);
	tmpobjid = CreateDynamicObject(738,1929.428100,-2295.451171,12.760005,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16640,"a51","a51_glass",0);
	tmpobjid = CreateDynamicObject(1290,1937.879028,-2265.731445,13.539985,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(738,1929.387695,-2305.591064,12.760005,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16640,"a51","a51_glass",0);
	tmpobjid = CreateDynamicObject(738,1929.406005,-2316.401367,12.760005,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16640,"a51","a51_glass",0);
	tmpobjid = CreateDynamicObject(3528,1947.287353,-2335.744140,56.264736,0.000000,52.499984,154.200180);
	SetDynamicObjectMaterial(tmpobjid,0,1676,"wshxrefpump","petrolpumptop_128",0);
	tmpobjid = CreateDynamicObject(3528,1948.724731,-2336.440429,56.239223,0.000000,52.499984,63.899990);
	SetDynamicObjectMaterial(tmpobjid,0,1676,"wshxrefpump","petrolpumptop_128",0);
	tmpobjid = CreateDynamicObject(8492,1947.773559,-2334.534423,53.947238,360.000000,182.199935,119.100013);
	SetDynamicObjectMaterial(tmpobjid,1,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(8492,1947.929931,-2334.672851,53.955329,0.000000,-177.800064,31.100034);
	SetDynamicObjectMaterial(tmpobjid,1,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1954.158325,-2335.216064,43.007026,0.000272,-90.200454,-89.999107);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1939.612182,-2335.173339,49.609817,-90.199775,-89.800460,-90.199127);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1939.598266,-2335.212890,45.439815,-90.199775,-89.800460,-90.199127);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1950.756347,-2335.216064,43.007026,0.000272,-90.200454,-89.999107);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1946.964843,-2335.216064,43.007026,0.000272,-90.200454,-89.999107);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1942.111328,-2335.216064,43.007026,0.000272,-90.200454,-89.999107);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1942.101440,-2335.192626,51.986915,0.000272,-90.200454,-89.999107);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1944.483398,-2335.192626,51.986915,0.000272,-90.200454,-89.999107);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1949.184936,-2335.192626,51.986915,0.000272,-90.200454,-89.999107);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1954.155151,-2335.192626,51.986915,0.000272,-90.200454,-89.999107);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1956.556640,-2335.192626,49.556919,-89.999717,-90.200454,-89.999107);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1956.561035,-2335.194824,45.537021,-89.999717,-90.200454,-89.999107);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1947.604492,-2330.867675,42.970272,-179.799942,-90.200454,-179.699142);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1947.622314,-2334.321044,42.982318,-179.799942,-90.200454,-179.699142);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1947.646484,-2339.165527,42.999179,-179.799942,-90.200454,-179.699142);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1947.654296,-2341.575927,45.567043,-89.999717,-90.200454,-179.699142);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1947.654296,-2341.575927,49.756744,-89.999717,-90.200454,-179.699142);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1947.646118,-2339.062011,52.084766,0.700257,-89.400466,-179.899154);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1947.643554,-2335.848876,52.045581,0.700257,-89.400466,-179.899154);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1947.634277,-2330.906494,51.985256,0.700257,-89.400466,-179.899154);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1947.647094,-2328.471191,49.524948,89.800209,287.299407,163.000411);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(19866,1947.647216,-2328.466552,45.445159,89.800209,287.299407,163.000411);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(18765,1951.538574,-2336.564941,49.509807,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper1",0);
	tmpobjid = CreateDynamicObject(18765,1944.613159,-2336.574951,49.499755,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper1",0);
	tmpobjid = CreateDynamicObject(18765,1944.603149,-2333.481933,49.499755,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper1",0);
	tmpobjid = CreateDynamicObject(19824,1943.841308,-2322.510009,13.969954,-1.100005,-88.999969,-89.500007);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","orange",0);
	tmpobjid = CreateDynamicObject(18771,1940.040405,-2341.082031,-7.010068,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,1281,"benches","trafficcone",0);
	SetDynamicObjectMaterial(tmpobjid,1,1281,"benches","trafficcone",0);
	SetDynamicObjectMaterial(tmpobjid,2,1281,"benches","trafficcone",0);
	SetDynamicObjectMaterial(tmpobjid,3,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3100,1382.452636,8257.245117,12.899999,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-95-percent",0);
	tmpobjid = CreateDynamicObject(18765,1951.538574,-2333.481933,49.509807,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper1",0);
	tmpobjid = CreateDynamicObject(18765,1944.605590,-2336.574707,45.539951,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper1",0);
	tmpobjid = CreateDynamicObject(18765,1951.538574,-2336.574707,45.539951,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper1",0);
	tmpobjid = CreateDynamicObject(18765,1951.538574,-2333.481933,45.539951,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper1",0);
	tmpobjid = CreateDynamicObject(19064,1943.861938,-2322.476806,14.270866,0.000000,37.699996,93.200019);
	tmpobjid = CreateDynamicObject(19545,1937.544921,-2294.423583,12.610004,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(18700,1947.480712,-2333.346679,42.685241,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(18771,1956.081542,-2340.997314,-7.010068,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,1281,"benches","trafficcone",0);
	SetDynamicObjectMaterial(tmpobjid,1,1281,"benches","trafficcone",0);
	SetDynamicObjectMaterial(tmpobjid,2,1281,"benches","trafficcone",0);
	SetDynamicObjectMaterial(tmpobjid,3,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(3790,1964.433471,-2292.871582,13.189994,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(3790,1964.370483,-2293.396484,13.149993,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(3788,1964.616455,-2290.967529,13.119993,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19616,1985.784423,-2338.419189,12.589993,0.000000,0.000000,-90.399932);
	tmpobjid = CreateDynamicObject(19616,1985.955200,-2329.957275,12.589993,0.000000,0.000000,-90.399932);
	tmpobjid = CreateDynamicObject(2511,1977.755615,-2319.434082,14.838034,0.000000,10.100000,-84.599998);
	tmpobjid = CreateDynamicObject(2486,1978.307983,-2319.456787,13.069998,0.000000,1.099999,-93.299964);
	tmpobjid = CreateDynamicObject(2480,1980.118041,-2318.836669,12.519990,0.000000,0.000000,-85.800025);
	tmpobjid = CreateDynamicObject(2490,1980.175170,-2318.716796,13.610004,0.000000,0.000000,-89.600013);
	tmpobjid = CreateDynamicObject(2483,1978.611816,-2318.954833,13.270001,0.000000,0.000000,-96.800033);
	tmpobjid = CreateDynamicObject(18728,1990.594238,-2338.438964,14.139998,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(18728,1986.434570,-2330.063232,14.189995,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(18728,1990.807495,-2330.257812,14.099997,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(18728,1986.124267,-2338.358886,14.099997,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19610,1987.433349,-2334.038818,14.192380,14.800000,0.000000,-89.799995);
	tmpobjid = CreateDynamicObject(19611,1987.447509,-2334.032958,12.569984,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19609,1988.212524,-2336.884033,12.569980,0.000000,0.000000,-100.299949);
	tmpobjid = CreateDynamicObject(19056,1986.335571,-2327.015136,13.199992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19057,1989.256713,-2327.015136,13.219992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19058,1988.341308,-2328.900878,13.186848,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(2690,1978.264648,-2303.921630,13.710002,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(2501,1980.059082,-2319.947998,13.610004,0.000000,0.000000,-88.799995);
	tmpobjid = CreateDynamicObject(1210,1978.293212,-2304.367431,13.318700,-87.099899,-88.599990,0.000000);
	tmpobjid = CreateDynamicObject(19054,1987.057861,-2328.799072,13.249993,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(2428,1978.873046,-2297.005126,14.790002,0.000000,0.000000,-94.299987);
	tmpobjid = CreateDynamicObject(19812,1979.797607,-2297.620849,12.999999,0.000000,0.000000,39.400028);
	tmpobjid = CreateDynamicObject(1551,1978.564697,-2295.682617,13.550006,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1551,1978.324462,-2297.604248,13.550006,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1667,1978.516845,-2297.895507,13.450004,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1667,1978.516845,-2298.025634,13.450004,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1667,1978.516845,-2298.175781,13.450004,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1667,1977.716308,-2296.804687,13.450004,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1667,1977.756225,-2296.324218,13.450004,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(18872,1978.637207,-2303.696777,13.330001,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(18765,1944.603149,-2333.481933,45.539951,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19058,"xmasboxes","wrappingpaper1",0);
	tmpobjid = CreateDynamicObject(19920,1978.029052,-2303.486572,13.390006,0.000000,0.000000,50.299995);
	tmpobjid = CreateDynamicObject(19623,1978.573242,-2303.357666,13.420001,0.000000,0.000000,-57.399997);
	tmpobjid = CreateDynamicObject(19052,1978.157348,-2303.206298,13.369999,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19044,1978.219238,-2303.076904,13.399999,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19039,1977.990478,-2303.106933,13.399999,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1600,1978.473999,-2312.986572,13.252639,-1.299999,106.999847,0.299999);
	tmpobjid = CreateDynamicObject(1600,1977.903686,-2312.465820,13.251626,0.000000,106.300018,0.000000);
	tmpobjid = CreateDynamicObject(1599,1978.178344,-2311.791503,13.249395,0.000000,100.399978,0.000000);
	tmpobjid = CreateDynamicObject(1607,1978.781494,-2312.002197,15.635569,3.399999,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1600,1978.164184,-2311.026123,13.327105,0.400000,104.199974,46.599998);
	tmpobjid = CreateDynamicObject(695,1994.100463,-2299.067626,1.430000,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(695,1994.100463,-2312.319335,1.430000,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(695,1906.856445,-2345.912109,1.430000,0.000000,0.000000,71.599998);
	tmpobjid = CreateDynamicObject(2228,1978.257080,-2304.760009,13.354014,-89.700119,-97.099876,-14.300013);
	tmpobjid = CreateDynamicObject(3467,1977.971191,-2306.650634,13.200000,0.000000,0.000000,89.399971);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-90-percent",0);
	tmpobjid = CreateDynamicObject(19079,1978.885131,-2320.565185,13.067242,0.000000,-90.399971,84.600013);
	tmpobjid = CreateDynamicObject(3467,1978.062866,-2299.076660,13.200000,0.000000,0.000000,89.399971);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-90-percent",0);
	tmpobjid = CreateDynamicObject(19079,1978.907592,-2320.324951,13.068913,0.000000,-90.399971,84.600013);
	tmpobjid = CreateDynamicObject(3467,1978.060791,-2299.083007,13.200000,0.000000,0.000000,89.299987);
	SetDynamicObjectMaterialText(tmpobjid,0,"          Karstas vynas",90,"Arial",24,1,-1,0,0);
	tmpobjid = CreateDynamicObject(3467,1977.968383,-2306.654541,13.200000,0.000000,0.000000,89.299987);
	SetDynamicObjectMaterialText(tmpobjid,0,"         Lombardas",90,"Arial",24,1,-1,0,0);
	tmpobjid = CreateDynamicObject(3267,1965.774414,-2296.075195,12.149991,0.000000,0.000000,-56.300003);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","ferry_build14",0);
	SetDynamicObjectMaterial(tmpobjid,4,14668,"711c","cj_white_wall2",0);
	SetDynamicObjectMaterial(tmpobjid,5,1560,"7_11_door","cj_sheetmetal2",0);
	tmpobjid = CreateDynamicObject(2060,1968.789428,-2299.388183,12.985442,0.000000,52.199947,319.600006);
	tmpobjid = CreateDynamicObject(2060,1967.688964,-2298.448242,13.028613,0.000000,-32.299999,319.600006);
	tmpobjid = CreateDynamicObject(3467,1977.881225,-2314.302978,13.200000,0.000000,0.000000,89.399971);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-90-percent",0);
	tmpobjid = CreateDynamicObject(2060,1968.268676,-2298.947509,13.030016,0.000000,0.000000,319.600006);
	tmpobjid = CreateDynamicObject(3467,1977.875000,-2314.308105,13.200000,0.000000,0.000000,89.299987);
	SetDynamicObjectMaterialText(tmpobjid,0,"           Rukyta zuvis",90,"Arial",24,1,-1,0,0);
	tmpobjid = CreateDynamicObject(2060,1968.545288,-2299.275634,12.699994,0.000000,0.000000,-38.300022);
	tmpobjid = CreateDynamicObject(2060,1967.791015,-2298.533935,12.780011,0.000000,0.000000,319.600006);
	tmpobjid = CreateDynamicObject(2064,1967.751342,-2299.510498,13.219995,0.000000,0.000000,139.799880);
	tmpobjid = CreateDynamicObject(18637,1968.149291,-2302.799072,13.309997,0.000000,0.000000,73.400001);
	tmpobjid = CreateDynamicObject(1242,1968.128417,-2303.227294,13.550003,0.000000,0.000000,-105.300025);
	tmpobjid = CreateDynamicObject(3467,1977.781494,-2321.973144,13.200000,0.000000,0.000000,89.299987);
	SetDynamicObjectMaterialText(tmpobjid,0,"                  Zaislai",90,"Arial",24,1,-1,0,0);
	tmpobjid = CreateDynamicObject(1252,1967.715820,-2303.614013,13.469473,-84.599853,34.399974,73.400009);
	tmpobjid = CreateDynamicObject(3467,1977.791503,-2321.974121,13.200000,0.000000,0.000000,89.399971);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-90-percent",0);
	tmpobjid = CreateDynamicObject(1575,1967.023193,-2304.178222,13.319997,0.000000,0.000000,-14.000001);
	tmpobjid = CreateDynamicObject(1577,1966.401123,-2304.694335,13.329998,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1578,1966.278564,-2305.168701,13.329998,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1578,1965.956787,-2305.676757,13.330007,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1579,1965.896484,-2306.314941,13.350008,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1579,1965.923461,-2306.765869,13.349998,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1654,1966.193237,-2307.423828,13.492962,-42.599990,-83.399879,112.000091);
	tmpobjid = CreateDynamicObject(1636,1966.448852,-2308.071777,13.500000,0.000000,0.000000,38.400001);
	tmpobjid = CreateDynamicObject(2045,1966.976196,-2309.000976,13.460001,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(2044,1967.467895,-2309.299316,13.420000,0.000000,0.000000,118.399971);
	tmpobjid = CreateDynamicObject(2037,1967.582641,-2309.874267,13.480016,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(2036,1967.692138,-2310.849853,13.409998,0.000000,0.000000,-49.599987);
	tmpobjid = CreateDynamicObject(2035,1967.437377,-2311.498291,13.389998,0.000000,0.000000,123.500061);
	tmpobjid = CreateDynamicObject(2034,1967.005371,-2312.449218,13.399999,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(2034,1967.046997,-2312.066650,13.420007,0.000000,0.000000,-47.099994);
	tmpobjid = CreateDynamicObject(2033,1967.381347,-2312.253662,13.440000,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1672,1967.001220,-2313.161376,13.406281,0.000000,-86.600006,0.000000);
	tmpobjid = CreateDynamicObject(2184,1967.890014,-2303.969970,12.591355,0.300000,0.000000,61.800144);
	tmpobjid = CreateDynamicObject(2184,1966.699951,-2303.878906,12.593289,-0.899999,0.000000,-116.899887);
	tmpobjid = CreateDynamicObject(2184,1965.659790,-2306.603759,12.616856,-0.899999,0.000000,-73.999877);
	tmpobjid = CreateDynamicObject(2184,1968.068603,-2310.796386,12.614173,-0.899999,0.000000,106.600280);
	tmpobjid = CreateDynamicObject(2184,1967.060913,-2313.553466,12.610567,-0.899999,0.000000,63.800178);
	tmpobjid = CreateDynamicObject(1946,1952.270874,-2333.728759,12.780003,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14832,"lee_stripclub","mirror_ref1",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(1946,1952.263305,-2335.020263,12.780000,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14808,"lee_strip2","strip_neon_Flat",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(1946,1952.270874,-2336.400634,12.780003,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14832,"lee_stripclub","mirror_ref1",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(1946,1952.263305,-2337.661376,12.780000,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14808,"lee_strip2","strip_neon_Flat",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(19473,1950.996582,-2338.775390,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1946,1951.142089,-2339.101562,12.780000,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14808,"lee_strip2","strip_neon_Flat",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(1946,1950.100830,-2339.072509,12.780003,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14832,"lee_stripclub","mirror_ref1",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(1946,1952.200805,-2339.072509,12.780003,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14832,"lee_stripclub","mirror_ref1",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(1946,1948.881713,-2339.101562,12.780000,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14808,"lee_strip2","strip_neon_Flat",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(1946,1945.411010,-2339.072509,12.780003,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14832,"lee_stripclub","mirror_ref1",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(1946,1947.720825,-2339.072509,12.780003,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14832,"lee_stripclub","mirror_ref1",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(19128,1967.265625,-2303.610107,16.726877,0.000000,-179.800216,0.000000);
	tmpobjid = CreateDynamicObject(19128,1967.265625,-2304.571044,16.726877,0.000000,-179.800216,0.000000);
	tmpobjid = CreateDynamicObject(19128,1967.265625,-2308.554443,16.726877,0.000000,-179.800216,0.000000);
	tmpobjid = CreateDynamicObject(19128,1967.265625,-2312.558349,16.726877,0.000000,-179.800216,0.000000);
	tmpobjid = CreateDynamicObject(19157,1967.218627,-2303.442626,14.120011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19157,1967.218627,-2307.896972,14.120011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19157,1967.218627,-2312.381103,14.120011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1946,1946.472778,-2339.071289,12.780000,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14808,"lee_strip2","strip_neon_Flat",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(1946,1945.411010,-2339.072509,12.780003,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14832,"lee_stripclub","mirror_ref1",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(1946,1945.311645,-2337.490478,12.780000,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14808,"lee_strip2","strip_neon_Flat",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(1946,1945.300903,-2336.011230,12.780003,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14832,"lee_stripclub","mirror_ref1",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(1946,1945.311645,-2334.779052,12.780000,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14808,"lee_strip2","strip_neon_Flat",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(1946,1945.300903,-2333.419677,12.780003,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14832,"lee_stripclub","mirror_ref1",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(1946,1945.311645,-2332.287841,12.780000,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14808,"lee_strip2","strip_neon_Flat",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(1946,1946.391723,-2332.238525,12.780007,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14832,"lee_stripclub","mirror_ref1",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(1946,1947.382202,-2332.287841,12.780000,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14808,"lee_strip2","strip_neon_Flat",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(1946,1948.641845,-2332.238525,12.780007,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14832,"lee_stripclub","mirror_ref1",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(2630,1978.797607,-2304.337890,14.840004,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1946,1949.912597,-2332.287841,12.780000,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14808,"lee_strip2","strip_neon_Flat",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(3861,1978.864013,-2296.840820,13.697920,0.000010,1.100000,270.200073);
	SetDynamicObjectMaterial(tmpobjid,0,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(1946,1951.232543,-2332.238525,12.780007,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14832,"lee_stripclub","mirror_ref1",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(19545,1970.044067,-2294.403564,12.610004,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(3861,1978.890258,-2304.347412,13.693921,0.000000,1.100000,-89.799949);
	SetDynamicObjectMaterial(tmpobjid,0,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(3786,1964.574462,-2290.904052,13.219996,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(3789,1964.445556,-2293.097167,12.979992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1280,1971.873779,-2336.843750,12.949989,0.000000,0.000000,-178.399810);
	SetDynamicObjectMaterial(tmpobjid,0,16639,"a51_labs","ws_trainstationwin1",0);
	SetDynamicObjectMaterial(tmpobjid,1,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(1280,1973.644287,-2336.796386,12.949989,0.000000,0.000000,-178.399810);
	SetDynamicObjectMaterial(tmpobjid,0,16639,"a51_labs","ws_trainstationwin1",0);
	SetDynamicObjectMaterial(tmpobjid,1,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(1280,1976.774780,-2336.707763,12.949989,0.000000,0.000000,-178.399810);
	SetDynamicObjectMaterial(tmpobjid,0,16639,"a51_labs","ws_trainstationwin1",0);
	SetDynamicObjectMaterial(tmpobjid,1,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(1280,1978.604614,-2336.656982,12.949989,0.000000,0.000000,-178.399810);
	SetDynamicObjectMaterial(tmpobjid,0,16639,"a51_labs","ws_trainstationwin1",0);
	SetDynamicObjectMaterial(tmpobjid,1,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(1280,1973.502807,-2332.516113,12.949989,0.000000,0.000000,-178.399810);
	SetDynamicObjectMaterial(tmpobjid,0,16639,"a51_labs","ws_trainstationwin1",0);
	SetDynamicObjectMaterial(tmpobjid,1,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(1280,1974.963745,-2332.476806,12.949989,0.000000,0.000000,-178.399810);
	SetDynamicObjectMaterial(tmpobjid,0,16639,"a51_labs","ws_trainstationwin1",0);
	SetDynamicObjectMaterial(tmpobjid,1,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(1280,1976.685180,-2332.432128,12.949989,0.000000,0.000000,-178.399810);
	SetDynamicObjectMaterial(tmpobjid,0,16639,"a51_labs","ws_trainstationwin1",0);
	SetDynamicObjectMaterial(tmpobjid,1,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(1280,1978.506347,-2332.385742,12.949989,0.000000,0.000000,-178.399810);
	SetDynamicObjectMaterial(tmpobjid,0,16639,"a51_labs","ws_trainstationwin1",0);
	SetDynamicObjectMaterial(tmpobjid,1,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(1280,1980.426635,-2332.333007,12.949989,0.000000,0.000000,-178.399810);
	SetDynamicObjectMaterial(tmpobjid,0,16639,"a51_labs","ws_trainstationwin1",0);
	SetDynamicObjectMaterial(tmpobjid,1,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(1280,1975.073974,-2336.755859,12.949989,0.000000,0.000000,-178.399810);
	SetDynamicObjectMaterial(tmpobjid,0,16639,"a51_labs","ws_trainstationwin1",0);
	SetDynamicObjectMaterial(tmpobjid,1,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(1280,1980.544799,-2336.604492,12.949989,0.000000,0.000000,-178.399810);
	SetDynamicObjectMaterial(tmpobjid,0,16639,"a51_labs","ws_trainstationwin1",0);
	SetDynamicObjectMaterial(tmpobjid,1,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(1280,1971.741821,-2332.563232,12.949989,0.000000,0.000000,-178.399810);
	SetDynamicObjectMaterial(tmpobjid,0,16639,"a51_labs","ws_trainstationwin1",0);
	SetDynamicObjectMaterial(tmpobjid,1,19058,"xmasboxes","wrappingpaper4-2",0);
	tmpobjid = CreateDynamicObject(1946,1952.393432,-2332.287841,12.780000,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14808,"lee_strip2","strip_neon_Flat",0);
	SetDynamicObjectMaterial(tmpobjid,1,10101,"2notherbuildsfe","Bow_Abpave_Gen",0);
	tmpobjid = CreateDynamicObject(695,1925.965820,-2349.685791,1.430000,0.000000,0.000000,73.500000);
	tmpobjid = CreateDynamicObject(19632,1922.659912,-2313.348876,12.539991,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,1920.458374,-2305.122070,13.236857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19315,1918.749267,-2312.934570,13.049988,0.000000,0.000000,87.600036);
	tmpobjid = CreateDynamicObject(19315,1922.128417,-2303.157470,13.049988,0.000000,0.000000,-4.400012);
	tmpobjid = CreateDynamicObject(19079,1921.670532,-2306.460449,15.336720,3.099998,-89.300003,-125.899955);
	tmpobjid = CreateDynamicObject(1457,1920.406005,-2305.438232,13.630002,0.000000,0.000000,52.800052);
	tmpobjid = CreateDynamicObject(695,2005.191040,-2338.971191,1.430000,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(695,1984.891845,-2349.458496,1.430000,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(695,1955.038452,-2351.400634,1.430000,-2.099999,-3.899999,-53.600002);
	tmpobjid = CreateDynamicObject(695,1966.271606,-2353.822753,1.430000,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19076,1925.757446,-2310.703613,12.369999,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19293,1948.711669,-2336.023437,15.140014,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(11431,1918.450561,-2317.024658,13.919997,0.000000,0.000000,-53.600063);
	tmpobjid = CreateDynamicObject(19955,1956.519409,-2189.382080,12.426858,0.000000,0.000000,-178.999816);
	tmpobjid = CreateDynamicObject(19127,1958.578369,-2216.249023,17.924663,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19127,1943.905517,-2216.249023,17.924663,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19127,1947.906250,-2216.249023,17.924663,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19127,1951.876586,-2216.249023,17.924663,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19127,1955.707763,-2216.249023,17.924663,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19127,1961.599975,-2216.249023,17.924663,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19127,1965.430175,-2216.249023,17.924663,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19127,1969.033569,-2216.249023,17.924663,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19529,1946.238647,-2346.763671,12.560000,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19597,"lsbeachside","carpet19-128x128",0);
	SetDynamicObjectMaterial(tmpobjid,15,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(18771,1956.081542,-2328.894775,-7.010068,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,1281,"benches","trafficcone",0);
	SetDynamicObjectMaterial(tmpobjid,1,1281,"benches","trafficcone",0);
	SetDynamicObjectMaterial(tmpobjid,2,1281,"benches","trafficcone",0);
	SetDynamicObjectMaterial(tmpobjid,3,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(18771,1940.040405,-2328.894775,-7.010068,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,1281,"benches","trafficcone",0);
	SetDynamicObjectMaterial(tmpobjid,1,1281,"benches","trafficcone",0);
	SetDynamicObjectMaterial(tmpobjid,2,1281,"benches","trafficcone",0);
	SetDynamicObjectMaterial(tmpobjid,3,10839,"aircarpkbarier_sfse","chevron_red_64HVa",0);
	tmpobjid = CreateDynamicObject(19076,1948.819213,-2335.695068,5.120000,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(738,1945.668334,-2316.401367,12.760005,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16640,"a51","a51_glass",0);
	tmpobjid = CreateDynamicObject(738,1945.668334,-2305.591064,12.760005,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16640,"a51","a51_glass",0);
	tmpobjid = CreateDynamicObject(738,1945.668334,-2295.451171,12.760005,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16640,"a51","a51_glass",0);
	tmpobjid = CreateDynamicObject(738,1945.668334,-2284.748779,12.760005,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16640,"a51","a51_glass",0);
	tmpobjid = CreateDynamicObject(738,1945.668334,-2272.626220,12.760005,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16640,"a51","a51_glass",0);
	tmpobjid = CreateDynamicObject(738,1961.889160,-2272.626220,12.760005,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16640,"a51","a51_glass",0);
	tmpobjid = CreateDynamicObject(738,1961.889160,-2284.797363,12.760005,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16640,"a51","a51_glass",0);
	tmpobjid = CreateDynamicObject(3438,1954.110839,-2312.029296,14.219989,0.000000,0.000000,-89.699874);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanaflag",0);
	tmpobjid = CreateDynamicObject(738,1961.889160,-2295.577880,12.760005,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16640,"a51","a51_glass",0);
	tmpobjid = CreateDynamicObject(3438,1954.055053,-2301.407226,14.219989,0.000000,0.000000,-89.699874);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanaflag",0);
	tmpobjid = CreateDynamicObject(3438,1954.000976,-2290.996093,14.219989,0.000000,0.000000,-89.699874);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanaflag",0);
	tmpobjid = CreateDynamicObject(3438,1953.936279,-2278.473632,14.219989,0.000000,0.000000,-89.699874);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanaflag",0);
	tmpobjid = CreateDynamicObject(738,1961.889160,-2305.682617,12.760005,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16640,"a51","a51_glass",0);
	tmpobjid = CreateDynamicObject(3438,1953.897705,-2271.083007,14.219989,0.000000,0.000000,-89.699874);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanaflag",0);
	tmpobjid = CreateDynamicObject(1550,1935.425537,-2335.632812,12.856860,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1550,1934.775756,-2336.813964,12.771260,0.000000,35.900062,0.000000);
	tmpobjid = CreateDynamicObject(1550,1933.334106,-2336.083251,12.856860,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19055,1933.287597,-2334.878417,14.356882,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19058,1934.679443,-2337.821289,13.146868,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19056,1932.302368,-2335.715332,13.226877,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,1932.447875,-2337.809082,14.326878,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19056,1932.805297,-2338.297607,13.226877,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19055,1932.348388,-2334.267822,13.176866,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19058,1933.188110,-2336.970458,13.146868,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19057,1931.399902,-2337.847900,13.196867,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19056,1934.384033,-2334.844482,13.226877,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,1935.779174,-2336.349853,13.216867,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(3438,1953.863525,-2264.511474,14.219989,0.000000,0.000000,-89.699874);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanaflag",0);
	tmpobjid = CreateDynamicObject(738,1961.889160,-2316.457519,12.760005,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,16640,"a51","a51_glass",0);
	tmpobjid = CreateDynamicObject(19545,1953.342651,-2255.894775,12.590003,0.000000,0.000000,-89.400024);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(19608,1988.439819,-2334.266601,12.539980,0.000000,0.000000,-91.900054);
	tmpobjid = CreateDynamicObject(19545,1953.790527,-2294.423583,12.610004,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","ferry_build14",0);
	tmpobjid = CreateDynamicObject(19529,1946.238647,-2307.066406,12.560000,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19597,"lsbeachside","carpet19-128x128",0);
	tmpobjid = CreateDynamicObject(8375,1953.414672,-2233.243408,14.436517,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(8375,1955.533325,-2233.243408,14.436517,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(8375,1959.447143,-2233.243408,14.436517,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(8375,1953.221801,-2230.821044,15.436534,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(8375,1955.563720,-2230.801025,15.436534,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(8375,1959.447143,-2230.801025,15.436534,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(8375,1951.750732,-2222.163085,15.436534,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(8375,1955.643676,-2222.113037,15.436534,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(8375,1958.534790,-2220.041015,14.446514,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(8375,1959.447143,-2222.113037,15.436534,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(8375,1953.552001,-2219.980957,14.456514,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(8375,1955.523925,-2219.980957,14.456514,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19293,1948.887817,-2335.586425,26.449499,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19291,1948.577758,-2336.226074,18.190017,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19290,1948.800415,-2335.833496,27.202592,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(8375,1959.447143,-2219.980957,14.446514,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(12922,1961.492797,-2175.733398,15.866847,0.000000,0.000000,-179.700103);
	SetDynamicObjectMaterial(tmpobjid,0,19332,"balloon_texts","balloon07",0);
	SetDynamicObjectMaterial(tmpobjid,1,5819,"buildtestlawn","lawshopwall4",0);
	SetDynamicObjectMaterialText(tmpobjid,2,"{9D00FF} Sveskime Kaledas Kartu!",90,"Arial",24,1,-1,0,0);
	tmpobjid = CreateDynamicObject(1292,1971.030639,-2197.042236,13.056868,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(8040,2011.758300,-2207.521972,13.365036,0.000000,0.000000,-179.999877);
	tmpobjid = CreateDynamicObject(19290,1948.800292,-2335.757568,13.560000,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19292,1948.907226,-2335.817382,24.640026,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,1949.186279,-2335.666992,21.470056,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19293,1948.711669,-2336.023437,15.140014,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.980346,-2335.682373,26.877172,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.930297,-2335.412109,26.877172,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.809448,-2333.610351,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.930297,-2335.882568,26.877172,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.980346,-2335.882568,26.877172,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(16144,1982.344116,-2336.949707,12.596855,0.000000,0.000000,-179.899978);
	SetDynamicObjectMaterial(tmpobjid,0,14803,"bdupsnew","Bdup2_wallpaperB",0);
	SetDynamicObjectMaterial(tmpobjid,1,18996,"mattextures","sampred",0);
	tmpobjid = CreateDynamicObject(19473,1948.810180,-2335.992675,26.377161,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.080444,-2335.992675,26.377161,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.080444,-2335.622314,26.377161,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.750122,-2335.612304,26.397161,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.640014,-2335.552246,25.877149,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.160522,-2335.552246,25.877149,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.160522,-2336.022705,25.877149,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.640014,-2336.022705,25.877149,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.569946,-2336.142822,25.357137,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.320678,-2336.142822,25.357137,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.980346,-2335.672363,27.587188,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.260620,-2335.422119,25.357137,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(16144,1933.598510,-2332.494384,12.596855,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,14803,"bdupsnew","Bdup2_wallpaperB",0);
	SetDynamicObjectMaterial(tmpobjid,1,18996,"mattextures","sampred",0);
	tmpobjid = CreateDynamicObject(19473,1948.619995,-2335.422119,25.357137,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.519897,-2335.842529,24.727123,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(18864,1937.331420,-2288.432617,13.610004,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.519897,-2335.291992,24.727123,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.360717,-2335.291992,24.727123,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.360717,-2335.832519,24.727123,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.509887,-2336.272949,24.727123,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.690063,-2336.272949,24.727123,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.360717,-2336.272949,24.727123,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(3861,1978.943725,-2319.471923,13.403664,360.000000,1.100000,270.200073);
	SetDynamicObjectMaterial(tmpobjid,0,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(7666,1948.977294,-2335.646728,30.842634,0.000000,0.000000,90.700012);
	tmpobjid = CreateDynamicObject(19473,1948.439819,-2335.732421,24.047107,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.439819,-2336.383056,24.047107,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.840209,-2336.383056,24.047107,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.409790,-2335.201904,24.047107,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.950317,-2335.201904,24.047107,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.580932,-2335.201904,24.047107,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.339721,-2336.443115,23.357091,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.319702,-2335.952636,23.357091,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.319702,-2335.101806,23.357091,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.580932,-2335.732421,24.047107,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.900268,-2335.101806,23.357091,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.199584,-2336.552978,22.867080,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.900268,-2336.552978,22.867080,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.610961,-2336.443115,23.357091,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.610961,-2335.732421,23.357091,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.610961,-2335.101806,23.357091,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.189575,-2336.552978,22.867080,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.990356,-2336.552978,22.867080,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.661010,-2336.552978,22.867080,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.661010,-2336.092529,22.867080,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.661010,-2335.572265,22.867080,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.661010,-2334.981689,22.867080,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.260620,-2334.981689,22.867080,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.870361,-2334.981689,22.867080,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.159667,-2334.981689,22.867080,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.119628,-2335.521728,22.187065,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.119628,-2336.102294,22.187065,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.119628,-2336.592773,22.187065,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.750244,-2336.592773,22.187065,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.489990,-2336.763427,21.417047,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.290771,-2336.592773,22.187065,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.751220,-2336.592773,22.187065,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.751220,-2336.032714,22.187065,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.751220,-2335.472167,22.187065,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.751220,-2334.881591,22.187065,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.280761,-2334.881591,22.187065,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.660156,-2334.881591,22.187065,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.039550,-2334.881591,22.187065,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.841308,-2335.021728,21.417047,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.841308,-2335.422119,21.417047,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.841308,-2335.912597,21.417047,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.841308,-2336.373046,21.417047,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.841308,-2336.763427,21.417047,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.150634,-2336.763427,21.417047,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.489990,-2336.763427,21.417047,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.969482,-2336.373046,21.417047,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.969482,-2336.763427,21.417047,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.969482,-2336.032714,21.417047,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.969482,-2335.372070,21.417047,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.969482,-2334.801513,21.417047,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.570068,-2334.801513,21.417047,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.270629,-2334.801513,21.417047,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.931274,-2334.801513,21.417047,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.359863,-2334.711425,20.777032,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.200561,-2334.711425,20.777032,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.759277,-2334.681396,20.777032,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1974,1944.006958,-2322.193359,14.040003,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-93-percent",0);
	tmpobjid = CreateDynamicObject(19473,1949.971313,-2334.711425,20.777032,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.971313,-2334.892578,20.777032,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.971313,-2335.362060,20.777032,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.971313,-2335.842529,20.777032,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(7666,1948.977294,-2335.646728,30.762632,0.000000,0.000000,-31.200004);
	tmpobjid = CreateDynamicObject(19473,1949.971313,-2336.363037,20.777032,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.971313,-2336.913574,20.777032,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(7666,1948.977294,-2335.646728,30.842634,0.000000,0.000000,-150.100189);
	tmpobjid = CreateDynamicObject(19473,1947.759277,-2334.681396,20.777032,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.759277,-2335.241943,20.777032,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.759277,-2336.082763,20.777032,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.560913,-2336.913574,20.777032,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.660156,-2336.913574,20.777032,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.759277,-2336.913574,20.777032,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1974,1943.706665,-2322.183349,14.050004,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-93-percent",0);
	tmpobjid = CreateDynamicObject(19473,1950.071533,-2336.533203,19.827011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.071533,-2335.882568,19.827011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.071533,-2335.201904,19.827011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.071533,-2334.581298,19.827011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.460937,-2334.581298,19.827011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.820312,-2334.581298,19.827011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.279785,-2334.581298,19.827011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.709228,-2334.581298,19.827011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.709228,-2334.781494,19.827011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.709228,-2335.332031,19.827011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.709228,-2335.942626,19.827011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.709228,-2336.473144,19.827011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.709228,-2337.033691,19.827011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.369873,-2337.033691,19.827011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.980468,-2337.033691,19.827011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.571044,-2337.033691,19.827011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.201660,-2337.033691,19.827011,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.458984,-2337.193847,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.458984,-2337.103759,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.458984,-2336.403076,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.458984,-2335.742431,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.458984,-2335.041748,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.739624,-2337.183837,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.300048,-2337.183837,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.940429,-2337.183837,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.661132,-2337.183837,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.321777,-2337.183837,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.321777,-2336.703125,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.321777,-2336.092773,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.321777,-2335.452148,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.321777,-2334.901611,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.321777,-2334.381103,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.811279,-2334.381103,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.290771,-2334.381103,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.720214,-2334.381103,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.119628,-2334.381103,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.458984,-2334.381103,18.996992,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.208740,-2334.741455,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.388916,-2335.241943,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.388916,-2336.002685,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.388916,-2336.663330,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.388916,-2337.323974,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.219726,-2337.323974,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.030395,-2337.323974,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.861206,-2337.323974,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.461791,-2337.323974,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.461791,-2337.133789,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.461791,-2336.583251,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.461791,-2335.912597,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.461791,-2335.382080,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.461791,-2334.741455,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.461791,-2334.130859,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.031494,-2334.130859,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.450927,-2334.130859,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.880371,-2334.130859,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.269775,-2334.130859,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.689208,-2334.130859,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.208740,-2334.130859,17.956968,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.699218,-2337.474121,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.510009,-2337.474121,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.280761,-2337.474121,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.021484,-2337.474121,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.752197,-2337.474121,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.752197,-2337.113769,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.752197,-2336.423095,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19291,1948.773193,-2335.655029,26.310020,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.752197,-2334.641357,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.752197,-2333.930664,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.231689,-2333.930664,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.631103,-2333.930664,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.950439,-2333.930664,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.249755,-2333.930664,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.609130,-2333.930664,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.028564,-2333.930664,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.028564,-2334.591308,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.028564,-2335.342041,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.028564,-2336.032714,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.028564,-2336.893554,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.028564,-2337.574218,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.768432,-2333.890625,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.788330,-2334.431152,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.788330,-2335.021728,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.788330,-2335.752441,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.788330,-2336.563232,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.788330,-2337.203857,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.788330,-2337.754394,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.038574,-2337.754394,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.579101,-2337.754394,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.179687,-2337.754394,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.980468,-2337.754394,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.591064,-2337.754394,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.892456,-2337.754394,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.191650,-2337.754394,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19343,1943.857299,-2322.480468,13.746843,0.000000,179.600082,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(19473,1950.892456,-2337.754394,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.892456,-2336.933593,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.892456,-2336.252929,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(3861,1978.917114,-2312.009521,13.546875,0.000000,1.100000,-89.799949);
	SetDynamicObjectMaterial(tmpobjid,0,14651,"ab_trukstpd","Bow_bar_pool_tablebase",0);
	tmpobjid = CreateDynamicObject(19473,1950.752197,-2335.582275,16.896944,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.892456,-2334.220947,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.892456,-2333.610351,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.411987,-2333.610351,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.871459,-2333.610351,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.170776,-2333.610351,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.460083,-2333.610351,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.212768,-2335.392333,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.238891,-2333.610351,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.768432,-2333.610351,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.758422,-2333.610351,15.926921,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(18718,1949.028686,-2335.647216,30.756959,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19343,1943.865478,-2322.480468,12.706856,0.000000,179.600082,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(18864,1944.672607,-2296.062988,13.610004,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(7666,1948.977294,-2335.646728,30.842634,0.000000,0.000000,-54.599948);
	tmpobjid = CreateDynamicObject(19473,1947.088745,-2333.370117,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.749389,-2333.370117,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.440063,-2333.370117,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.180786,-2333.370117,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.861450,-2333.370117,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.622192,-2333.370117,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.212768,-2333.370117,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.212768,-2334.030761,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.212768,-2334.611328,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.892456,-2335.092041,16.106925,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.212768,-2336.152832,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.212768,-2336.893554,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.212768,-2337.544189,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.212768,-2338.084716,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.002563,-2338.094726,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.331909,-2338.094726,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.581176,-2338.094726,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.530883,-2336.383056,24.047107,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.900512,-2338.094726,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.189819,-2338.094726,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.569213,-2338.094726,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.988647,-2338.094726,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.478149,-2338.094726,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.478149,-2337.354003,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.478149,-2336.603271,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.478149,-2335.842529,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.478149,-2335.031738,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.478149,-2334.291015,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.478149,-2333.490234,15.236909,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.708251,-2333.209960,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.328857,-2333.209960,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.929443,-2333.209960,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.670166,-2333.209960,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.430908,-2333.209960,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.121582,-2333.209960,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.812255,-2333.209960,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.372802,-2333.209960,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.372802,-2333.860595,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.372802,-2334.511230,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.372802,-2335.261962,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.372802,-2336.112792,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.372802,-2336.963623,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.372802,-2337.804443,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.372802,-2338.455078,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.122558,-2338.375000,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.531982,-2338.375000,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.791259,-2338.375000,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.070678,-2338.375000,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.339965,-2338.375000,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.579223,-2338.375000,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.858520,-2338.375000,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.237915,-2338.375000,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.237915,-2337.584228,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.237915,-2336.803466,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.237915,-2336.152832,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.237915,-2335.492187,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.237915,-2334.721435,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.237915,-2333.950683,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.237915,-2333.229980,14.266890,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.572021,-2332.909667,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.881469,-2332.909667,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.200805,-2332.909667,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.560180,-2332.909667,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.879516,-2332.909667,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.118774,-2332.909667,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.518188,-2332.909667,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.202026,-2332.919677,13.216877,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.582397,-2332.989746,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.582397,-2333.510253,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.582397,-2334.050781,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.582397,-2334.781494,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.582397,-2335.502197,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.582397,-2336.192871,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.582397,-2336.993652,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.582397,-2337.654296,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.582397,-2338.214843,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.582397,-2338.725341,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.182006,-2338.725341,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.521362,-2338.725341,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.940795,-2338.725341,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.360351,-2338.725341,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.759765,-2338.725341,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.199218,-2338.725341,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.608642,-2338.725341,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.998046,-2338.725341,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.507568,-2338.725341,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.957031,-2338.725341,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.927612,-2338.375000,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.927612,-2337.754394,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.927612,-2337.143798,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.927612,-2336.383056,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.927612,-2335.712402,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.927612,-2334.971679,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.927612,-2334.311035,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.927612,-2333.640380,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.927612,-2332.909667,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.847778,-2333.240234,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.847778,-2333.900878,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.847778,-2334.551513,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.847778,-2335.232177,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.847778,-2335.972656,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.847778,-2336.723388,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.847778,-2337.484130,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.847778,-2338.244873,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.847778,-2338.775390,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19343,1943.861572,-2322.480468,13.216850,0.000000,179.600082,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18646,"matcolours","grey-10-percent",0);
	tmpobjid = CreateDynamicObject(19473,1945.661865,-2338.094726,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.996582,-2338.775390,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.661865,-2338.735351,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.824829,-2338.775390,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.214233,-2338.775390,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.927612,-2338.375000,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.833007,-2338.775390,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.282470,-2338.775390,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.186035,-2338.775390,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.505371,-2338.775390,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.661865,-2337.374023,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.453613,-2338.775390,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.661865,-2336.493164,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.927612,-2338.375000,13.226872,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.661865,-2335.221923,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.661865,-2334.551269,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.661865,-2335.802490,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.661865,-2333.189941,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.661865,-2332.499267,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.812988,-2332.499267,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1945.661865,-2333.760498,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1947.663696,-2332.499267,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1949.400268,-2332.559326,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1950.301147,-2332.559326,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1951.202026,-2332.559326,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1948.582641,-2332.499267,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1946.202392,-2332.499267,12.196857,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19473,1952.022827,-2332.559326,12.196858,0.000000,0.000000,0.000000);
	// bret ballas
	tmpobjid = CreateDynamicObject(3675,2237.212890,-1433.310424,24.308198,-12.399999,-2.399999,96.100013);
	SetDynamicObjectMaterial(tmpobjid,0,19278,"skydiveplatforms","hazardtile19-2",0);
	tmpobjid = CreateDynamicObject(3675,2251.323974,-1433.719848,25.268226,-20.699987,-2.399999,-93.599983);
	SetDynamicObjectMaterial(tmpobjid,0,19278,"skydiveplatforms","hazardtile19-2",0);
	tmpobjid = CreateDynamicObject(19292,2246.283691,-1433.258056,36.769767,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19289,2245.070312,-1431.450561,35.308216,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,2243.885986,-1431.367431,34.819725,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,2242.064208,-1431.367431,33.869747,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19289,2241.279541,-1431.718139,32.808212,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,2240.601562,-1432.668701,32.169803,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19292,2240.225341,-1433.673950,31.689794,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19289,2240.438720,-1434.669799,31.318225,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,2240.601562,-1435.789306,30.759805,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19292,2240.956054,-1436.795654,30.219789,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,2242.093017,-1437.650024,29.569778,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19289,2243.276367,-1437.923339,29.048192,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19008,2231.843505,-1433.534667,24.218626,0.000000,0.000000,-172.299942);
	tmpobjid = CreateDynamicObject(323,2231.436035,-1435.328735,23.638860,19.300001,-104.200042,-141.899963);
	tmpobjid = CreateDynamicObject(19292,2244.558593,-1438.176513,28.749767,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(323,2231.116455,-1435.425903,23.622751,19.300001,-104.200042,0.000000);
	tmpobjid = CreateDynamicObject(19033,2230.984375,-1431.159179,24.417110,0.000000,0.000000,-96.099967);
	tmpobjid = CreateDynamicObject(19294,2245.595458,-1437.650024,28.429756,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19775,2231.127197,-1431.201293,24.111461,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(353,2231.242431,-1430.946777,24.106300,0.000000,10.999998,-92.899986);
	tmpobjid = CreateDynamicObject(19161,2231.028320,-1431.048706,24.481529,0.000000,265.600036,170.199996);
	tmpobjid = CreateDynamicObject(19289,2246.359130,-1437.252685,27.908180,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1946,2231.012695,-1431.034423,24.314178,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19853,"mihouse1","redwall1",0);
	tmpobjid = CreateDynamicObject(1946,2231.012695,-1431.034423,24.044172,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19853,"mihouse1","redwall1",0);
	tmpobjid = CreateDynamicObject(1946,2231.012695,-1431.034423,23.754165,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19853,"mihouse1","redwall1",0);
	tmpobjid = CreateDynamicObject(19292,2248.291259,-1435.854492,26.969741,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,2249.267089,-1435.409423,26.419731,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19027,2231.224609,-1435.210327,24.037776,0.000000,0.000000,115.099967);
	tmpobjid = CreateDynamicObject(333,2231.933349,-1433.529785,23.675073,32.300022,-5.199999,0.000000);
	tmpobjid = CreateDynamicObject(337,2247.251220,-1429.517333,23.790102,-2.800000,8.699995,-40.200000);
	tmpobjid = CreateDynamicObject(334,2230.332763,-1432.390991,24.098920,0.000000,-139.099990,178.000015);
	tmpobjid = CreateDynamicObject(19294,2246.055908,-1434.249633,38.419799,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(724,2244.060546,-1439.077880,28.238201,0.000000,-179.500061,0.000000);
	tmpobjid = CreateDynamicObject(19058,2247.930908,-1430.012939,23.974353,-2.599999,2.400001,49.900005);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanataidai",0);
	SetDynamicObjectMaterial(tmpobjid,1,18901,"matclothes","bowleryellow",0);
	tmpobjid = CreateDynamicObject(19058,2248.845214,-1431.503051,24.084571,357.299987,3.699999,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanaflag",0);
	tmpobjid = CreateDynamicObject(1550,2250.551757,-1431.435302,23.668560,14.000000,14.400000,0.000000);
	tmpobjid = CreateDynamicObject(1550,2250.650634,-1431.864746,23.768178,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(2919,2270.016357,-1426.245971,22.963310,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(334,2231.162109,-1432.432495,24.048627,0.000000,-139.099990,-2.899998);
	tmpobjid = CreateDynamicObject(18638,2231.283447,-1435.337890,24.212764,0.099999,-87.000022,20.799997);
	tmpobjid = CreateDynamicObject(373,2249.252197,-1439.744384,24.300405,20.200004,33.300010,0.000000);
	tmpobjid = CreateDynamicObject(19058,2249.967773,-1435.791015,24.912399,2.700024,-12.900000,200.699981);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanacloth5",0);
	SetDynamicObjectMaterial(tmpobjid,1,19278,"skydiveplatforms","hazardtile19-2",0);
	tmpobjid = CreateDynamicObject(3106,2228.649902,-1430.392700,27.740011,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,10101,"2notherbuildsfe","sl_vicwall02",0);
	tmpobjid = CreateDynamicObject(19352,2231.984863,-1433.510009,24.341709,0.000000,0.000000,8.900000);
	tmpobjid = CreateDynamicObject(19058,2246.226562,-1430.428833,24.074357,-10.499995,8.400000,49.900005);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanazigzag",0);
	SetDynamicObjectMaterial(tmpobjid,1,19775,"matcopstuff","copholster1",0);
	tmpobjid = CreateDynamicObject(1946,2231.282958,-1435.364379,23.964168,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19853,"mihouse1","redwall1",0);
	tmpobjid = CreateDynamicObject(1946,2231.983642,-1433.514526,24.144174,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19853,"mihouse1","redwall1",0);
	tmpobjid = CreateDynamicObject(2005,2234.519775,-1439.404907,24.299087,0.000000,0.000000,-155.599990);
	tmpobjid = CreateDynamicObject(1946,2231.983642,-1433.514526,23.884168,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19853,"mihouse1","redwall1",0);
	tmpobjid = CreateDynamicObject(1550,2234.677246,-1440.540771,25.354969,-23.199996,19.400003,-102.199897);
	SetDynamicObjectMaterial(tmpobjid,1,18901,"matclothes","hatmap2",0);
	tmpobjid = CreateDynamicObject(2481,2234.523925,-1439.647949,24.762582,0.499999,0.000000,175.200012);
	tmpobjid = CreateDynamicObject(1946,2231.983642,-1433.514526,23.604162,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19853,"mihouse1","redwall1",0);
	tmpobjid = CreateDynamicObject(1946,2231.282958,-1435.364379,23.654163,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19853,"mihouse1","redwall1",0);
	tmpobjid = CreateDynamicObject(1946,2231.282958,-1435.364379,23.334157,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19853,"mihouse1","redwall1",0);
	tmpobjid = CreateDynamicObject(19632,2230.545166,-1434.043457,23.248159,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1946,2230.732421,-1432.444458,24.174173,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19853,"mihouse1","redwall1",0);
	tmpobjid = CreateDynamicObject(1946,2230.732421,-1432.444458,23.874166,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19853,"mihouse1","redwall1",0);
	tmpobjid = CreateDynamicObject(18929,2230.740966,-1432.435058,24.389450,-5.500000,-89.300003,116.200004);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","hatmancblk",0);
	tmpobjid = CreateDynamicObject(334,2248.446044,-1438.759887,24.525758,-127.099990,-81.499961,178.999954);
	tmpobjid = CreateDynamicObject(2907,2250.214843,-1437.214111,24.508632,1.500000,33.599994,0.000000);
	tmpobjid = CreateDynamicObject(2060,2233.311279,-1439.486206,24.090782,0.000000,0.000000,87.099975);
	tmpobjid = CreateDynamicObject(1829,2238.162109,-1431.834838,24.651165,-10.000017,-8.699997,-122.500022);
	tmpobjid = CreateDynamicObject(19625,2230.696533,-1432.630737,24.110242,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1279,2234.387207,-1439.136596,23.912382,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1550,2233.379882,-1440.208740,24.446212,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,1,18901,"matclothes","bandanaskull",0);
	tmpobjid = CreateDynamicObject(1550,2233.009033,-1440.508422,24.289484,-10.899998,19.400003,-102.199897);
	SetDynamicObjectMaterial(tmpobjid,1,18901,"matclothes","hatmap2",0);
	tmpobjid = CreateDynamicObject(1114,2234.712890,-1440.192749,23.811798,29.300018,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1114,2234.712890,-1438.667724,23.292152,-33.200000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1114,2233.011718,-1438.497070,23.282014,-33.900020,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19138,2230.719482,-1432.571044,24.258409,0.800000,0.000000,-96.099998);
	tmpobjid = CreateDynamicObject(1114,2233.001708,-1440.152343,23.947301,38.200000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1114,2232.991699,-1440.314819,23.233339,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1114,2232.991699,-1439.304443,23.233339,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1114,2232.991699,-1438.083984,23.233339,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(1114,2234.712890,-1438.083984,23.233339,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19589,2233.929687,-1439.877441,23.808124,0.000000,0.000000,266.500000);
	SetDynamicObjectMaterial(tmpobjid,0,1355,"break_s_bins","CJ_RED_LEATHER",0);
	tmpobjid = CreateDynamicObject(1114,2234.712890,-1439.254882,23.233339,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19054,2234.224853,-1440.230712,24.586223,1.899992,1.599995,259.700073);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","hatmap1",0);
	tmpobjid = CreateDynamicObject(19087,2234.418212,-1446.772583,23.795669,91.500007,-2.799999,0.000000);
	tmpobjid = CreateDynamicObject(19833,2234.173583,-1446.147338,22.987749,0.000000,0.000000,1.299999);
	tmpobjid = CreateDynamicObject(19833,2233.032714,-1446.173095,22.987749,0.000000,0.000000,1.299999);
	tmpobjid = CreateDynamicObject(19087,2232.635742,-1446.755493,23.796125,91.500007,-2.799999,0.000000);
	tmpobjid = CreateDynamicObject(19087,2234.534912,-1444.385864,23.858158,91.500007,-2.799999,0.000000);
	tmpobjid = CreateDynamicObject(19087,2232.755859,-1444.298950,23.860435,91.500007,-2.799999,0.000000);
	tmpobjid = CreateDynamicObject(19833,2234.309570,-1444.091186,22.987749,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19833,2233.059326,-1444.091186,22.987749,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,2244.173583,-1432.776000,39.796020,-15.900001,-0.500004,147.400024);
	tmpobjid = CreateDynamicObject(19060,2244.896728,-1434.418823,39.487262,-19.000005,-6.299994,0.000000);
	tmpobjid = CreateDynamicObject(19063,2242.878173,-1433.756958,38.623497,0.000000,33.499992,0.000000);
	tmpobjid = CreateDynamicObject(19062,2249.240478,-1433.447021,28.865589,-0.799994,-45.099967,0.000000);
	tmpobjid = CreateDynamicObject(19061,2245.498779,-1434.242309,37.154430,-10.200003,-6.599998,0.499999);
	tmpobjid = CreateDynamicObject(1114,2234.712890,-1440.394775,23.233339,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,2245.419921,-1431.953979,37.476078,24.099998,-7.100002,0.000000);
	tmpobjid = CreateDynamicObject(19061,2243.383544,-1431.857788,36.811798,2.600000,17.200002,0.499999);
	tmpobjid = CreateDynamicObject(19060,2246.467041,-1432.495971,35.014236,24.099998,-7.100002,0.000000);
	tmpobjid = CreateDynamicObject(19063,2247.015136,-1434.353515,33.391452,-7.699997,-12.699999,-8.899999);
	tmpobjid = CreateDynamicObject(700,2244.189941,-1433.370971,25.298051,0.000000,0.000000,31.200016);
	tmpobjid = CreateDynamicObject(19294,2245.887695,-1432.148071,35.719711,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(700,2244.060791,-1433.358886,25.797996,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,2245.575927,-1436.906982,28.993608,1.699991,28.499998,132.600006);
	tmpobjid = CreateDynamicObject(7666,2244.588623,-1433.152709,42.018096,0.000000,0.000000,-64.599952);
	tmpobjid = CreateDynamicObject(19063,2248.025634,-1434.606689,30.309761,-7.699997,-12.699999,-8.899999);
	tmpobjid = CreateDynamicObject(19061,2249.758544,-1434.959960,26.132921,0.599996,-23.600000,0.499999);
	tmpobjid = CreateDynamicObject(3675,2245.231445,-1439.594482,23.969402,-12.399999,-2.399999,-148.399948);
	SetDynamicObjectMaterial(tmpobjid,0,19278,"skydiveplatforms","hazardtile19-2",0);
	tmpobjid = CreateDynamicObject(19060,2248.975097,-1432.056274,26.594198,19.600000,-7.100002,0.000000);
	tmpobjid = CreateDynamicObject(349,2240.610595,-1429.490478,24.065124,6.999997,282.799987,358.500000);
	tmpobjid = CreateDynamicObject(19059,2245.442626,-1430.642578,31.082973,-15.900001,-0.500004,147.400024);
	tmpobjid = CreateDynamicObject(19061,2243.552490,-1439.456176,25.911666,-26.099998,0.500000,0.000000);
	tmpobjid = CreateDynamicObject(19062,2247.617431,-1430.575195,28.385850,28.400007,-11.199972,0.000000);
	tmpobjid = CreateDynamicObject(19060,2239.762939,-1431.697143,25.592227,0.000000,21.700008,0.000000);
	tmpobjid = CreateDynamicObject(19061,2245.533935,-1429.204223,26.913602,31.399997,-0.599997,0.499999);
	tmpobjid = CreateDynamicObject(19054,2240.420166,-1437.924804,24.765464,8.399991,14.199994,-69.899925);
	tmpobjid = CreateDynamicObject(19059,2241.783691,-1429.287231,26.438339,1.000001,-20.700000,147.400024);
	tmpobjid = CreateDynamicObject(19060,2241.646972,-1434.418823,34.028339,0.000000,17.000003,0.000000);
	tmpobjid = CreateDynamicObject(19058,2241.134521,-1439.148315,24.345239,3.399998,-18.199998,61.399997);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanacloth1",0);
	SetDynamicObjectMaterial(tmpobjid,1,18996,"mattextures","sampwhite",0);
	tmpobjid = CreateDynamicObject(19059,2238.339111,-1434.083496,26.661506,29.400001,-29.299997,147.400024);
	tmpobjid = CreateDynamicObject(19057,2239.519531,-1430.795776,24.664937,-2.600001,7.799998,28.700000);
	SetDynamicObjectMaterial(tmpobjid,0,18901,"matclothes","bandanaskull",0);
	tmpobjid = CreateDynamicObject(19055,2240.971435,-1430.275268,24.362831,1.400000,6.199999,-2.299999);
	tmpobjid = CreateDynamicObject(19061,2244.282958,-1435.710571,34.649734,-47.599998,0.500000,0.000000);
	tmpobjid = CreateDynamicObject(19054,2242.528076,-1429.629882,24.327222,-0.199999,6.599998,37.500003);
	SetDynamicObjectMaterial(tmpobjid,5,19523,"sampicons","reeedgrad32",0);
	tmpobjid = CreateDynamicObject(19063,2240.766845,-1432.636352,32.154178,0.000000,33.499992,0.000000);
	tmpobjid = CreateDynamicObject(1946,2230.732421,-1432.444458,23.604162,0.000000,0.000000,0.000000);
	SetDynamicObjectMaterial(tmpobjid,0,19853,"mihouse1","redwall1",0);
	tmpobjid = CreateDynamicObject(736,2247.670410,-1433.349487,14.767096,-68.099975,-176.200088,-49.399993);
	tmpobjid = CreateDynamicObject(363,2248.361083,-1428.867065,23.601879,0.299999,-4.199999,-42.099983);
	tmpobjid = CreateDynamicObject(3675,2245.059326,-1428.412597,23.869674,-20.699987,-2.399999,-24.399965);
	SetDynamicObjectMaterial(tmpobjid,0,19278,"skydiveplatforms","hazardtile19-2",0);
	tmpobjid = CreateDynamicObject(19060,2245.630126,-1435.740478,31.569736,0.000000,326.399993,0.000000);
	tmpobjid = CreateDynamicObject(3675,2242.495605,-1440.045410,25.228796,-12.399999,-2.399999,143.400009);
	SetDynamicObjectMaterial(tmpobjid,0,19278,"skydiveplatforms","hazardtile19-2",0);
	tmpobjid = CreateDynamicObject(19062,2244.913330,-1430.791137,34.334144,23.800003,0.200000,0.000000);
	tmpobjid = CreateDynamicObject(1368,2233.722167,-1441.909423,24.246114,0.000000,0.000000,356.200012);
	SetDynamicObjectMaterial(tmpobjid,0,1560,"7_11_door","cj_sheetmetal2",0);
	tmpobjid = CreateDynamicObject(19055,2247.670410,-1437.844726,25.350936,4.800012,2.600002,8.700000);
	tmpobjid = CreateDynamicObject(19292,2242.611083,-1430.886108,33.929748,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19060,2242.448730,-1431.316162,32.859733,0.000000,30.999996,0.000000);
	tmpobjid = CreateDynamicObject(19060,2240.095458,-1436.889160,27.182170,0.000000,17.000003,0.000000);
	tmpobjid = CreateDynamicObject(19063,2243.186523,-1430.191162,29.964351,23.999998,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(2907,2239.926269,-1429.308593,23.909006,-14.799996,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19289,2244.161132,-1435.569580,37.028236,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19289,2244.579833,-1430.339477,32.948238,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19062,2240.383300,-1431.606567,28.929733,38.799999,43.500007,0.000000);
	tmpobjid = CreateDynamicObject(19062,2243.194091,-1438.140502,29.053981,337.399993,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19292,2246.553955,-1431.206420,31.669761,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,2245.135009,-1435.831176,37.679782,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19289,2247.919433,-1432.601196,30.378179,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,2243.063476,-1435.230957,36.639797,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,2242.064697,-1433.759277,35.709800,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19292,2248.495849,-1434.305053,29.289764,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,2241.794433,-1431.858032,34.749767,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,2243.584960,-1430.427734,33.639774,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,2245.685791,-1430.427734,32.379776,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19289,2247.749267,-1435.681030,27.908180,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,2247.246337,-1431.888549,31.079774,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,2248.586425,-1433.418579,29.789770,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19292,2246.920166,-1437.305664,26.969741,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,2248.586425,-1435.099121,28.629753,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,2247.226562,-1436.509155,27.469739,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19294,2246.225585,-1437.949707,26.499731,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(11733,2238.691162,-1435.960693,24.338665,12.400001,-1.800000,-23.299991);
	tmpobjid = CreateDynamicObject(7666,2244.725341,-1433.276367,42.018096,0.000000,0.000000,28.100004);
	tmpobjid = CreateDynamicObject(19294,2281.645507,-1449.479248,32.759742,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,2281.641357,-1449.408447,32.859733,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19292,2242.611083,-1434.616943,36.229763,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19061,2239.776611,-1435.093872,29.346572,2.600000,17.200002,0.499999);
	tmpobjid = CreateDynamicObject(19289,2241.968994,-1432.909667,35.248229,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,2243.013916,-1435.841308,32.412998,29.400001,4.400003,147.400024);
	tmpobjid = CreateDynamicObject(19292,2245.644042,-1435.117431,37.909824,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2244.682373,-1433.296997,37.898094,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2243.341064,-1433.123413,34.618129,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2244.281982,-1432.996459,34.898162,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2244.552246,-1433.994873,34.618129,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2245.463134,-1433.296997,34.618129,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2244.682373,-1433.296997,36.348110,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2244.191894,-1432.206542,32.818202,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2246.235351,-1433.688110,33.148189,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2242.520263,-1433.296997,32.898170,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2244.682373,-1434.498168,33.148189,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2244.322021,-1431.546264,31.198158,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2244.356689,-1430.811035,28.777391,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2244.682373,-1435.578369,30.948158,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2240.691650,-1433.674926,28.902748,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2241.519775,-1433.296997,31.068159,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2247.034423,-1433.627319,30.988178,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2246.116943,-1431.551757,28.777391,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2244.682373,-1433.296997,34.748165,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2244.682373,-1433.296997,32.978172,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2244.682373,-1433.296997,30.988153,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2247.738037,-1433.771240,28.777391,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2242.197265,-1431.989501,28.767410,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2244.356689,-1430.811035,28.777391,0.000000,0.000000,0.000000);
	//tmpobjid = CreateDynamicObject(9100,2511.146972,-1681.813598,13.374019,0.000000,0.000000,0.000000); gsf
	tmpobjid = CreateDynamicObject(647,2245.457519,-1433.470581,28.767410,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2241.414062,-1435.363647,28.897415,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2246.526611,-1435.781494,26.827409,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2246.767333,-1431.449584,26.717399,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2241.858642,-1436.020629,26.707406,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2244.356689,-1436.502807,28.777391,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2243.906250,-1437.731323,26.707406,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2242.273193,-1431.414428,26.672744,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2240.101074,-1433.374755,26.672744,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2248.697509,-1433.911376,26.827409,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2244.148437,-1429.923095,26.567398,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2245.457519,-1433.470581,28.767410,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2241.954345,-1433.370117,26.577425,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2245.645751,-1433.449829,26.737428,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2243.767333,-1435.201049,26.717422,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(647,2243.756347,-1431.400268,26.867424,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19058,2249.135009,-1437.561279,25.256826,-9.699982,1.300002,200.699981);
	tmpobjid = CreateDynamicObject(647,2243.702148,-1433.347290,26.920888,0.000000,0.000000,0.000000);
	tmpobjid = CreateDynamicObject(19059,2247.781250,-1432.573852,32.857872,-24.700008,-0.500004,132.600006);
}
