
stock ShotSaudykla(playerid,weaponid, objectid)
{

	new shot = 0;
	for(new i;i<50;i++) 
	{
		if(SaudyklosStats[playerid][s_objs][i] == objectid)
		{
			DestroyPlayerObject(playerid, SaudyklosStats[playerid][s_objs][i]);
			SaudyklosStats[playerid][s_objs][i] = -1;
			shot = 1;
		}
	}
	if(shot)
	{
		SaudyklosStats[playerid][s_shot] ++;
		if(SaudyklosStats[playerid][s_gun] == 0)
			SaudyklosStats[playerid][s_gun] = weaponid;
		else if(SaudyklosStats[playerid][s_gun] != weaponid)
		{
			DestroySaudyklosObjektai(playerid);
			SaudyklosStats[playerid][s_id] = 0;
			SendInfoMessage(playerid,"~r~Turi naudoti ta pati ginkla visiems taikiniams!");
		}
		else
			SaudyklosInfo(playerid);
		PlayerPlaySound(playerid, 17802, 0, 0, 0);
	}
	
	if(SaudyklosStats[playerid][s_shot] == SaudyklosStats[playerid][s_outof])
	{
		new time = GetTickCount() - SaudyklosStats[playerid][s_timestart];
		new secs = time / 1000;

		new mins = secs / 60;
		new seconds = secs % 60;
		new ms = (time % 1000) / 10;
		new msg[128];
		format(msg,sizeof(msg)," * [Saudykla] %s iveike saudykla per %i:%s%i.%s%i!",ReturnName(playerid),mins,(seconds < 10 ? ("0"):("")),seconds,(ms < 10? ("0"):("")),ms);
		ProxDetector(100.0, playerid, msg, WHITE,WHITE,WHITE,WHITE,WHITE);
		CheckRekordas(playerid,SaudyklosStats[playerid][s_id],time,weaponid);
		AsmeninisSaudykla(playerid,SaudyklosStats[playerid][s_id],time,weaponid);
		SaudyklosStats[playerid][s_id] = 0;
		

	}


}
stock AsmeninisSaudykla(playerid,saudyklosid,time,weaponid)
{
	new query[256];
	format(query,256,"SELECT Laikas FROM Saudykla Where Saudykla=%i AND Ginklas=%i AND Vardas='%s'",saudyklosid,weaponid,ReturnName(playerid));
	mysql_function_query(SQL,query, true, "SQL_CheckAsmeninis", "iiii", playerid,saudyklosid,time,weaponid);
}

stock CheckRekordas(playerid,saudyklosid,time,weaponid)
{
	new query[256];
	format(query,256,"SELECT COUNT(*) FROM Saudykla Where Saudykla=%i AND Ginklas=%i AND Laikas < %i",saudyklosid,weaponid,time);
	mysql_function_query(SQL,query, true, "SQL_CheckSaudykla", "i", playerid);
}

stock SaudyklosInfo(playerid)
{
	new time = GetTickCount() - SaudyklosStats[playerid][s_timestart];
	new secs = time / 1000;

	new mins = secs / 60;
	new seconds = secs % 60;

	new msg[128];
	format(msg,sizeof(msg),"~r~Taikiniai: ~w~%i/%i~n~~r~Laikas:~w~ %i:%s%i",SaudyklosStats[playerid][s_shot],SaudyklosStats[playerid][s_outof],mins,(seconds < 10 ? ("0"):("")),seconds);
	SendInfoMessage(playerid,msg);
	if(seconds % 2 == 0)
		RespawnObjects(playerid,SaudyklosStats[playerid][s_id]);
	if(mins >= 3 || GetPlayerInterior(playerid) == 0) {
		DestroySaudyklosObjektai(playerid);
		SaudyklosStats[playerid][s_id] = 0;
		SendInfoMessage(playerid,"~r~Baigesi laikas!");
	}
}
stock RespawnObjects(playerid,saudyklosid)
{
	for(new i;i<50;i++) 
	{
		if(SaudyklosStats[playerid][s_objs][i] != -1)
		{
			DestroyPlayerObject(playerid,SaudyklosStats[playerid][s_objs][i]);
			if(saudyklosid == 1)
				SaudyklosStats[playerid][s_objs][i] = CreatePlayerObject(playerid, SaudyklosObjektai[i][s_obj], SaudyklosObjektai[i][s_x],SaudyklosObjektai[i][s_y],SaudyklosObjektai[i][s_z],SaudyklosObjektai[i][s_rx],SaudyklosObjektai[i][s_ry],SaudyklosObjektai[i][s_rz],200.0);
			else
				SaudyklosStats[playerid][s_objs][i] = CreatePlayerObject(playerid, Saudyklos2Objektai[i][s_obj], Saudyklos2Objektai[i][s_x],Saudyklos2Objektai[i][s_y],Saudyklos2Objektai[i][s_z],Saudyklos2Objektai[i][s_rx],Saudyklos2Objektai[i][s_ry],Saudyklos2Objektai[i][s_rz],200.0);
		}
	}
}
stock DestroySaudyklosObjektai(playerid)
{
	SaudyklosStats[playerid][s_id] = 0;
	for(new i;i<50;i++) 
	{
		DestroyPlayerObject(playerid, SaudyklosStats[playerid][s_objs][i]);
		SaudyklosStats[playerid][s_objs][i] = -1;
	}
}

stock LoadSaudykla(playerid,saudyklaid)
{
	DestroySaudyklosObjektai(playerid);

	if(!saudyklaid)
		return;
	ProcessAchievement(playerid,89);
	SaudyklosStats[playerid][s_id] = saudyklaid;
	SaudyklosStats[playerid][s_bullets] = 0;
	SaudyklosStats[playerid][s_timestart] = GetTickCount();
	SaudyklosStats[playerid][s_shot] = 0;
	SaudyklosStats[playerid][s_gun] = 0;
	if(saudyklaid == 1) 
	{
		for(new i;i<sizeof(SaudyklosObjektai);i++)
		{
			SaudyklosStats[playerid][s_objs][i] = CreatePlayerObject(playerid, SaudyklosObjektai[i][s_obj], SaudyklosObjektai[i][s_x],SaudyklosObjektai[i][s_y],SaudyklosObjektai[i][s_z],SaudyklosObjektai[i][s_rx],SaudyklosObjektai[i][s_ry],SaudyklosObjektai[i][s_rz],200.0);
		}
		SaudyklosStats[playerid][s_outof] = sizeof(SaudyklosObjektai);	
	}
	else if(saudyklaid == 2)
	{
		for(new i;i<sizeof(Saudyklos2Objektai);i++)
		{
			SaudyklosStats[playerid][s_objs][i] = CreatePlayerObject(playerid, Saudyklos2Objektai[i][s_obj], Saudyklos2Objektai[i][s_x],Saudyklos2Objektai[i][s_y],Saudyklos2Objektai[i][s_z],Saudyklos2Objektai[i][s_rx],Saudyklos2Objektai[i][s_ry],Saudyklos2Objektai[i][s_rz],200.0);
		}
		SaudyklosStats[playerid][s_outof] = sizeof(Saudyklos2Objektai);	
	}
	SetTimerEx("STimer", 900, false, "ii", playerid,3);

	TogglePlayerControllable(playerid,false);
}
forward STimer(playerid,countd);
public STimer(playerid,countd)
{
	new Float:coo[3];
	if(countd > 0)
	{
		GetPlayerPos(playerid,coo[0],coo[1],coo[2]);
		PlayerPlaySound(playerid,1056,coo[0],coo[1],coo[2]);
		new msg[256];
		format(msg,sizeof(msg),"~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~g~-~y~ %i ~g~-",countd);
		GameTextForPlayer(playerid,msg,1000,3);
		SetTimerEx("STimer", 900, false, "ii", playerid,countd-1);
	}
	else 
	{
		GetPlayerPos(playerid,coo[0],coo[1],coo[2]);
		PlayerPlaySound(playerid,1057,coo[0],coo[1],coo[2]);
		GameTextForPlayer(playerid,"~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~g~-~y~]~g~-~r~!!! GOOO !!!~g~-~y~]~g~-",1000,3);
		TogglePlayerControllable(playerid, true);
	}
	SaudyklosStats[playerid][s_timestart]=GetTickCount();
}