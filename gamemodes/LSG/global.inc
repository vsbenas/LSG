forward GlobalUpdate();
new diena,dabartinis;
stock GlobalSystem()
{
	GenerateCars();
	new val[3];
	getdate(val[0],val[1],val[2]);
	diena=val[2];
	AllowInteriorWeapons(1);
	SendRconCommand("mapname Los Santos | Dillimore");
	new tmp[256];
	format(tmp,256,"%s %s %s",GAMEMODE, VERSIJA, KODUOTE);
	SetGameModeText(tmp);
	EnableStuntBonusForAll(false);
	LimitGlobalChatRadius(25);
	SetWorldTime(7);
//	ShowNameTags(0);
	SetNameTagDrawDistance(25);
}

public GlobalUpdate()
{
	SaveBusinesses();
	NarkoPildymas();
	FuruRespawn();
	SavePelnai();
	new val[3];
	getdate(val[0],val[1],val[2]);
	if(val[2] != diena && IsProdEnvironment())
	{
		BombaYra[3]=1;
		GenerateCars();
		//mysql_reconnect();
		diena=val[2];
		SaveVars();
		SavePelnai();
		ApleistiVerslai();
		SaveBusinesses();
		//LoadBombike();
		mysql_query("CALL NightlyProcedure()");
		ApleistiGaujas();
	}
	if(GetTickCount() >= 2000000000 && !autorestart)
	{
		printf("Scheduling autorestart because of tickcount = %i", GetTickCount());
		autorestart = true;
	}
	new hrs,mins,secs;
	gettime(hrs,mins,secs);
	if(hrs == 4)
	{
		if(autorestart)
		{
			for(new i;i<5;i++) SendClientMessageToAll(COLOR," * Serverio restartas uz minutes!!");
			SetTimer("Restartas",60000,false);
			autorestart=false;
		}
	}
	for(new pi;pi<MAX_FAMILY;pi++) SaveFamily(pi);
	for(new ip;ip<MAX_NARKO;ip++) SaveNarko(ip);
	ReloadGangIspejimai();
	new i;
	for(i=0; i<sizeof(aVehicleNames); i++) { SetVehicleToRespawn(aVehicleNames[i][Carid]); }
	printf("GLOBALUPDATE");
	if(!helovynas)
	{
		dabartinis++;
	   	if(dabartinis == 15) {dabartinis = 0;}
	   	if(dabartinis == 20) {dabartinis = random(8);}
		if(dabartinis == 8)
		{
			if(random(10) != 2)
				dabartinis=10;
		}
	}
  	SetWeather(dabartinis);
  	FixBot();
  	//return 
						
	LoadAchievementMax();
	//SetGravity(0.008);
	
}