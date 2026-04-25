new kiausostate = 0;
new kiausasobj;

stock VelykuEvent()
{
	if(kiausostate == 0)
	{
		kiausasobj = CreateObject(19343, -237.1774,2670.1448,70.0816, 0, 135.0, 0);
		SetObjectMaterial(kiausasobj,0, 18646, "MatColours", "white", 0xFFFFFFFF);

		PHY_InitObject(kiausasobj);


		kiausostate++;
	}
	else if(kiausostate == 1)
	{	
		new speed = 5;
		new Float:a = 0.0;
		new Float:sin = floatsin( -a, degrees );
		new Float:cos = floatcos( -a, degrees );
		new obj = kiausasobj;
		PHY_SetObjectVelocity(obj, speed*sin, speed*cos, 1);
		PHY_SetObjectGhost(obj);
		PHY_SetObjectFriction(obj, 100); // This will stop the object when it touchs the ground.
		PHY_SetObjectGravity(obj, 10);

		PHY_SetObjectZBound(obj, 62.6545, _, 0.0);


		kiausostate = 2;
	}

}
stock KiausasDropped()
{
	PHY_DeleteObject(kiausasobj);
	new Float:Coo[3];
	new Float:K[3];
	GetObjectPos(kiausasobj,K[0],K[1],K[2]);
	foreach(Player, i) 
	{
		if(GetPlayerState(i) == PLAYER_STATE_DRIVER && GetVehicleModel(GetPlayerVehicleID(i)) == 543)
		{

			GetVehicleBackPos(GetPlayerVehicleID(i),Coo[0],Coo[1],Coo[2]);
			new Float:Distas;
			Distas = floatsqroot((Coo[0]-K[0])*(Coo[0]-K[0])   + (Coo[1]-K[1])*(Coo[1]-K[1]) + (Coo[2]-K[2])*(Coo[2]-K[2]));

			if(Distas < 2.5)
			{
				if(GetPVarInt(i, "Playerkiausas"))
					DestroyObject(GetPVarInt(i, "Playerkiausas"));

				SetObjectPos(kiausasobj, Coo[0], Coo[1], -10.0);

				AttachObjectToVehicle(kiausasobj, GetPlayerVehicleID(i), 0, -2.0, 0.5, 0,0,0); //, Float:RotZ)
				SetPVarInt(i, "Playerkiausas", kiausasobj);

				kiausostate=0;
				return;
			}

		}
	}

	CreateExplosion(K[0],K[1],K[2], 12, 2.0);
	DestroyObject(kiausasobj);
	kiausasobj = -1;
	kiausostate = 0;
}


stock KiausasSpray(playerid,veh)
{
	new spray = GetPVarInt(playerid, "KiausasSpray");
	if(ac_InPayNSpray(playerid) && GetPVarInt(playerid, "PlayerKiausas") > 0 && GetVehicleModel(veh) == 543)
	{
		SetPVarInt(playerid, "KiausasSpray", spray+1);
		if(spray+1 == 4)
		{
			new ki = GetPVarInt(playerid, "PlayerKiausas");
			DestroyObject(ki);
			ki = CreateObject(19341+random(3), 0, 0, 0, 0, 0, 0);
			AttachObjectToVehicle(ki, veh, 0, -2.0, 0.5, 0,0,0); //, Float:RotZ)
			SetPVarInt(playerid, "PlayerKiausas", ki);
			SetPVarInt(playerid, "KiausasNudazytas",1);
		}
	}
	else
	{
		SetPVarInt(playerid, "KiausasSpray", 0);
	}
}

stock PlaceKiausas(playerid,model)
{
	new Float:Pos[3] = {1479.6218,-1639.6728,14.0469};
	new angle = random(360);
	new Float:sin = floatsin( angle, degrees );
	new Float:cos = floatcos( angle, degrees );
	new radius = 2 + random(8);
	Pos[0] += sin * radius;
	Pos[1] += cos * radius;

	new Float:tilt1 = random(2) == 0 ? 35 : -35;
	new Float:tilt2 = random(2) == 0 ? 35 : -35;

	if(random(2) == 0) {
		tilt2=0;
		tilt1 = 0;
	}
	else if(random(2) == 0)
		tilt1 = 0;
	else if(random(2) == 0)
		tilt2 = 0;

	CreateDynamicObject(model, Pos[0], Pos[1], Pos[2], tilt1,tilt2, 0); //, Float:rz, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_OBJECT_SD, Float:drawdistance = STREAMER_OBJECT_DD, STREAMER_TAG_AREA areaid = STREAMER_TAG_AREA -1, priority = 0)
	SetPlayerCheckpoint(playerid, Pos[0], Pos[1], Pos[2], 2.0);
}

stock PickupVelykos(playerid)
{
	if(GetPlayerScore(playerid) < 100)
		return SendClientMessage(playerid, RED, " * Sugrizk kai turesi 100 XP!");

	if(GetPVarInt(playerid, "VelykosDone") == 1)
	{
		ShowPlayerDialog(playerid, 19644, DIALOG_STYLE_MSGBOX, "Velyku eventas","\t\t\t\t{cb4335}Los Santos Gyvenimas\n{FFFFFF}\t\t\t\t     Ðv. Velykos 2022\n\n\n\
			\n\n{f2d7d5}Sveikiname ávykdþius velykø eventà!\nTavo kiauðinis bus puiki dekoracija Los Santos miestui Velykø proga. \n\nAèiû uþ dalyvavimà!\n\n\nLSG Administracija", "Gerai", ""); 
		return 1;
	}
	new ki = GetPVarInt(playerid, "PlayerKiausas");
	new Float:Coo[3];
	GetPlayerPos(playerid, Coo[0], Coo[1], Coo[2]);
	if(ki != 0)
	{
		if(GetVehicleModel(PlayerCar[playerid]) == 543)
		{
			if(GetVehicleDistanceFromPoint(PlayerCar[playerid], Coo[0], Coo[1], Coo[2]) > 15.0)
			{
				SendClientMessage(playerid, RED, " * Priveþk savo automobilá arèiau!");
				return 1;
			}
			if(GetPVarInt(playerid, "KiausasNudazytas") == 0)
				return SendClientMessage(playerid, RED, " * Nudaþyk savo kiauðiná Pay'n'Spray daþykloje!");
			new model = GetObjectModel(ki);
			PlaceKiausas(playerid,model);
			DestroyObject(ki);
			SetPVarInt(playerid, "KiausasNudazytas",0);
			SetPVarInt(playerid, "PlayerKiausas", 0);

			if(playerDB[playerid][vip] || playerDB[playerid][admin])
			{
				ShowPlayerDialog(playerid, 19644, DIALOG_STYLE_MSGBOX, "Velyku eventas","\t\t\t\t{cb4335}Los Santos Gyvenimas\n{FFFFFF}\t\t\t\t     Ðv. Velykos 2022\n\n\n\
				\n\n{f2d7d5}Sveikiname ávykdþius velykø eventà!\nTavo kiauðinis bus puiki dekoracija Los Santos miestui Velykø proga. Turime tau porà dovanø:\n\n\
				1) +5 dienos VIP statuso\n\
				2) 500 M4 kulkø.\n\
				3) 300 Deagle kulkø.\n\n\
				Aèiû uþ dalyvavimà!\n\n\nLSG Administracija", "Gerai", ""); 
				DeletePlayerWeapon(playerid, 31);
				if(playerDB[playerid][specialybe]==83)
					DeletePlayerWeapon(playerid, 24);
				GivePlayerWeaponEx(playerid, 31, 500);
				GivePlayerWeaponEx(playerid, 24, 300);
				SetPlayerKVS(playerid, "Velykos2022", "1");
			}
			else
			{
				ShowPlayerDialog(playerid, 19644, DIALOG_STYLE_MSGBOX, "Velyku eventas","\t\t\t\t{cb4335}Los Santos Gyvenimas\n{FFFFFF}\t\t\t\t     Ðv. Velykos 2022\n\n\n\
				\n\n{f2d7d5}Sveikiname ávykdþius velykø eventà!\nTavo kiauðinis bus puiki dekoracija Los Santos miestui Velykø proga. Turime tau porà dovanø:\n\n\
				1) +5 dienos VIP statuso\n\
				2) Viðèiuko skinas. Já rasi savo inventoriuje paraðæs /i\n\n\
				Aèiû uþ dalyvavimà!\n\n\nLSG Administracija", "Gerai", ""); 

				new skinid=167;
				SetPlayerSkin(playerid,skinid);
				playerDB[playerid][drabuziai]=skinid;

				SendInfoMessage(playerid,"Sveikiname gavus naujaji skina!");
				playerDB[playerid][uniformd]=false;
				ApplyAnimation(playerid,"PLAYIDLES","stretch",4.1,0,0,0,0,0);

				new uzrasas[256];
				//SendClientMessage(playerid,RED," * Butinai issaugokite zaidima, antraip dings jusu skinas.");
				format(uzrasas,sizeof(uzrasas),"INSERT INTO `Spinta`(`Vardas`,`Skin`,`LastUsed`) VALUES ('%s',%i,NOW())",ReturnName(playerid),skinid);
				mysql_query(uzrasas);
				ProcessAchievement(playerid,48);
				
				SetPlayerKVS(playerid, "Velykos2022", "2");
			}
			playerDB[playerid][vip]=true;

			new query[256];
			format(query,sizeof(query),"UPDATE `Account` SET `Vip`=`Vip`+5 WHERE `Name` = '%s'",ReturnName(playerid));
			mysql_query(query);

			SetPVarInt(playerid, "VelykosDone", 1);

			//GivePlayerMoneyA(playerid,10000);
			//GivePlayerWeaponEx(playerid,24,200);
			/*new ip[16];
			GetPlayerIp(playerid, ip, sizeof ip);
			new uzrasas[256];
			format(uzrasas,sizeof(uzrasas),"INSERT INTO `Easter19`(`Vardas`,`IP`) VALUES ('%s','%s')",ReturnName(playerid),ip);
			mysql_query(uzrasas);*/

		}

	}
	else
	{
		ShowPlayerDialog(playerid, 19644, DIALOG_STYLE_MSGBOX, "Velyku eventas","\t\t\t\t{cb4335}Los Santos Gyvenimas\n{FFFFFF}\t\t\t\t     Ðv. Velykos 2022\n\n\n\
			\n\n{f2d7d5}Sveikiname tave su Ðv. Velykomis! Los Santos mieste trûksta nudaþytø kiauðiniø, todël mums reikia tavo pagalbos!\nÐtai, kà turi padaryti, kad gautum velykiná prizà:\n\n1) Paimk pieno iðveþiotojo automobilá. Já naudosime kiauðiniø perveþimui.\n2) Viename ið miesteliø rasi didelæ viðtà. Surask jà ir pagauk kiauðiná naudodamas pienveþio bagaþinæ.\n3) Apsilankyk viename ið daþyklø Pay'n'Spray ir nudaþyk savo kiauðiná.\n4) Sugráþk èia ir pristatyk savo kiauðiná!", "Gerai", ""); 

	}


	return 1;
}
stock CheckVelykos(playerid)
{
	if(GetPVarInt(playerid, "PlayerKiausas") > 0)
	{
		DestroyObject(GetPVarInt(playerid, "PlayerKiausas"));
		SetPVarInt(playerid, "PlayerKiausas", 0);
		SetPVarInt(playerid, "KiausasNudazytas",0);
		if(IsPlayerAdmin(playerid))
			SendClientMessage(playerid, -1, "[DEBUG] Kiausas destroyed!");
		return 1;
	}
	return 0;
}


CMD:placekiausas(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	PlaceKiausas(playerid, 19341+random(3));
	return 1;
}
/*
stock PickupKiausas(playerid, kiausoid)
{
	new query[155];
	format(query,sizeof(query),"SELECT `k%i` FROM `Easter18` WHERE Vardas='%s'",kiausoid + 1, ReturnName(playerid));

	mysql_function_query(SQL, query, true, "SQL_CheckKiausas", "ii",playerid,kiausoid);
	
}

query:CheckKiausas(playerid,kiausoid)
{
	RestartCheck();
	new numrows,fields;
	cache_get_data(numrows,fields);
	new give = 1;
	if(!numrows)
	{
		give = 1;
		new IP[24];
		GetPlayerIp(playerid, IP, 24);
		new query[256];
		format(query,sizeof(query),"INSERT INTO `Easter18`(Vardas,IP,k%i) VALUES ('%s','%s',1)",kiausoid + 1,ReturnName(playerid),IP);
		mysql_query(query);
	}
	else
	{
		new row[10];
		cache_get_row(0,0,row);
		if(strval(row) != 0)
			give = 0;
		else
		{
			new query[256];
			format(query,sizeof(query),"UPDATE `Easter18` SET k%i = 1 WHERE Vardas='%s'",kiausoid + 1,ReturnName(playerid));
			mysql_query(query);
		}
	}
	if(give)
	{
		SendClientMessage(playerid, -1, " *** Gimtadienis ***");
		SendClientMessage(playerid, TEXTCOL_GOLD, " * Gavai viena gimtadienio dovana!");
		ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);

	}
	else
	{
		SendClientMessage(playerid, -1, " * Tu si priza jau turi! Pasidek ji namuose naudodamas /gimtadienis");
	}
	//new msg[4024];
	
}
*/