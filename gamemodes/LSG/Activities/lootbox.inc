#define SPIN_BG 0xFFFFFF00//-16806144
#define SPIN_COL -16805889
new PlayerText:LotoTD[24];

new LotoCars[8];

new const CarLoto[][2] =
{
	{402, 20}, // buffalo
	{412, 10}, // voodoo
	{457, 3}, // caddy
	{479, 8}, // regina
	{483, 3}, // camper
	{494, 2}, // hotring
	{502, 2}, // hotring a
	{503, 2}, // hotring b
	{508, 5}, // journey
	{513, 2}, // stuntplane
	{545, 10}, // hustler
	{555, 20}, // windsor
	{554, 10}, // yosemite
	{559, 15}, // jester 
	{549, 10}, // tampa
	{471, 5}, // quad
	{571, 2}, // kart
	{452, 3}, // speeder
	{547, 10}, // primo
	// Viena is didziausiu LSG klaidu buvo idet vortex i loterija. Sandeliai po to pasikeite visiems laikams.
	// Todel pries paleidziant LSG koda i viesuma, isemiau vortex is loterijos kad nauji serveriai nuo to nekentetu.
	// Gerai pagalvok ar tikrai nori ji sugrazinti, nes kelio atgal nebus.
	// {539, 1}, // vortex
	{534, 10}, // remington
	{475, 15}, // sabre
	{495, 1}, // sandking
	{583, 2}, // tug
	{485, 2} // baggage
};



stock lotocarid()
{
	new sum = 0;
	for(new i;i<sizeof CarLoto;i++)
	{
		sum += CarLoto[i][1];
	}
	new randomas = random(sum);
	new idas = 0;
	while(randomas > CarLoto[idas][1])
	{
		randomas -= CarLoto[idas][1];
		idas++;
	}

	return CarLoto[idas][0];
}

stock GenerateCars()
{
	for(new i;i<8;i++)
		LotoCars[i] = lotocarid();
}

forward SpinLootCrate(playerid,step,idas,change,nextchange,first,treshold);

public SpinLootCrate(playerid,step, idas,change,nextchange,first,treshold)
{
	if(step == 0)
	{
		SetPVarInt(playerid,"LotoRolling",1);
		ResetLoto(playerid);
		first = 1;
		nextchange = 1;
		treshold = 50 + random(50);
	}
	if(step < 300)
	{
		if(change == 0)
		{
			PlayerPlaySound(playerid, 4202, 0.0, 0.0, 0.0);
			new PlayerText:id = LotoTD[8 + (idas % 8)];
			PlayerTextDrawBackgroundColor(playerid, id, SPIN_BG);
			PlayerTextDrawShow(playerid, id);
			idas ++;
			id = LotoTD[8 + (idas % 8)];
			PlayerTextDrawBackgroundColor(playerid, id, SPIN_COL);
			PlayerTextDrawShow(playerid, id);
			if(step > treshold)
				nextchange = nextchange + random((step-50)/10 + 1);
			change = nextchange;
		}
		else
			change--;
		//SpinLootCrate(playerid,step+1,idas,change);
		SetTimerEx("SpinLootCrate", 50, false,"iiiiiii",playerid,step+1,idas,change,nextchange,first,treshold);// const format[], ...)
	}
	else
	{
		
		LotoEnd(playerid,idas % 8);
	}

}
stock LotoEnd(playerid,idas)
{
	new msg[128];
	format(msg,sizeof(msg)," * Laimejai {0000FF}%s{FFFFFF}!",aVehicleNames[LotoCars[idas]-400][Name]);
	SendClientMessage(playerid, -1, msg);
	PlayerPlaySound(playerid, 4201, 0.0, 0.0, 0.0);
	SetTimerEx("GiveLotoCar", 2000, false, "ii", playerid,LotoCars[idas]);
}

stock ResetLoto(playerid)
{
	for(new i;i<8;i++)
	{
		new PlayerText:id = LotoTD[8 + i];
		PlayerTextDrawBackgroundColor(playerid, id, SPIN_BG);
		PlayerTextDrawShow(playerid, id);
	}
}

stock OnClickLoto(playerid,PlayerText:clickedid)
{
	if(GetPVarInt(playerid,"LotoShown") == 0)
		return 0;
	if(!GetPVarInt(playerid,"LotoRolling"))
	{
		if(clickedid == LotoTD[7]) {
			if(playerDB[playerid][loterijos] < 1)
				return SendInfoMessage(playerid,"~r~Neturi loterijos bilietu!");
			if(Carlist[playerid][Typ]!=-1 && Carlist2[playerid][Typ] != -1 && Carlist3[playerid][Typ] != -1)
				return SendInfoMessage(playerid,"~r~Tu jau turi tris automobilius!");
			playerDB[playerid][loterijos]--;
			PlayerPlaySound(playerid, 4200+random(4), 0.0, 0.0, 0.0);
			SpinLootCrate(playerid,0,0,0,0,0,0);
		}
		else
		{
			HideLotoTextDraws(playerid);
			DestroyLotoTextDraws(playerid);
		}
	}
	else
	{
		SelectTextDraw(playerid, 0x00FF00FF);
	}
	return 1;
}
stock ShowLotoTextDraws(playerid,select=1)
{
	for(new i;i<24;i++)
		PlayerTextDrawShow(playerid, LotoTD[i]);
		//PlayerTextDrawShowForPlayer(playerid, LotoTD[i]);
	if(select)
	{
		SelectTextDraw(playerid, 0x00FF00FF); 
		SetPVarInt(playerid, "LotoShown", 1);
	}
}
stock HideLotoTextDraws(playerid)
{
	for(new i;i<24;i++)
		PlayerTextDrawHide(playerid, LotoTD[i]);
	CancelSelectTextDraw(playerid);
	SetPVarInt(playerid, "LotoShown", 0);
}

stock DestroyLotoTextDraws(playerid)
{
	for(new i;i<24;i++)
		PlayerTextDrawDestroy(playerid, LotoTD[i]);
		//PlayerTextDrawDestroy(playerid,LotoTD[i]);
}

stock CrateLotoTextDraws(playerid)
{
	LotoTD[0] = CreatePlayerTextDraw(playerid,317.083282, 74.370330, "Vienetiniai_automobiliai~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~");
	PlayerTextDrawLetterSize(playerid,LotoTD[0], 0.277498, 1.708888);
	PlayerTextDrawTextSize(playerid,LotoTD[0], 0.000000, 255.000000);
	PlayerTextDrawAlignment(playerid,LotoTD[0], 2);
	PlayerTextDrawColor(playerid,LotoTD[0], -1);
	PlayerTextDrawUseBox(playerid,LotoTD[0], 1);
	PlayerTextDrawBoxColor(playerid,LotoTD[0], 9561);
	PlayerTextDrawSetShadow(playerid,LotoTD[0], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[0], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[0], -2046820291);
	PlayerTextDrawFont(playerid,LotoTD[0], 1);
	PlayerTextDrawSetProportional(playerid,LotoTD[0], 1);
	PlayerTextDrawSetShadow(playerid,LotoTD[0], 0);

	LotoTD[1] = CreatePlayerTextDraw(playerid,318.766937, 112.840721, "_");
	PlayerTextDrawLetterSize(playerid,LotoTD[1], 0.228330, 6.785184);
	PlayerTextDrawTextSize(playerid,LotoTD[1], -0.459998, 237.000000);
	PlayerTextDrawAlignment(playerid,LotoTD[1], 2);
	PlayerTextDrawColor(playerid,LotoTD[1], -1);
	PlayerTextDrawUseBox(playerid,LotoTD[1], 1);
	PlayerTextDrawBoxColor(playerid,LotoTD[1], -1593835603);
	PlayerTextDrawSetShadow(playerid,LotoTD[1], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[1], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[1], 255);
	PlayerTextDrawFont(playerid,LotoTD[1], 1);
	PlayerTextDrawSetProportional(playerid,LotoTD[1], 1);
	PlayerTextDrawSetShadow(playerid,LotoTD[1], 0);

	LotoTD[2] = CreatePlayerTextDraw(playerid,319.000152, 205.101547, "_");
	PlayerTextDrawLetterSize(playerid,LotoTD[2], 0.228330, 6.785184);
	PlayerTextDrawTextSize(playerid,LotoTD[2], -0.459998, 237.000000);
	PlayerTextDrawAlignment(playerid,LotoTD[2], 2);
	PlayerTextDrawColor(playerid,LotoTD[2], -1);
	PlayerTextDrawUseBox(playerid,LotoTD[2], 1);
	PlayerTextDrawBoxColor(playerid,LotoTD[2], -1593835603);
	PlayerTextDrawSetShadow(playerid,LotoTD[2], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[2], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[2], 255);
	PlayerTextDrawFont(playerid,LotoTD[2], 1);
	PlayerTextDrawSetProportional(playerid,LotoTD[2], 1);
	PlayerTextDrawSetShadow(playerid,LotoTD[2], 0);

	LotoTD[3] = CreatePlayerTextDraw(playerid,318.783172, 295.160766, "_");
	PlayerTextDrawLetterSize(playerid,LotoTD[3], 0.228330, 6.785184);
	PlayerTextDrawTextSize(playerid,LotoTD[3], -0.459998, 237.000000);
	PlayerTextDrawAlignment(playerid,LotoTD[3], 2);
	PlayerTextDrawColor(playerid,LotoTD[3], -1);
	PlayerTextDrawUseBox(playerid,LotoTD[3], 1);
	PlayerTextDrawBoxColor(playerid,LotoTD[3], -1593835603);
	PlayerTextDrawSetShadow(playerid,LotoTD[3], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[3], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[3], 255);
	PlayerTextDrawFont(playerid,LotoTD[3], 1);
	PlayerTextDrawSetProportional(playerid,LotoTD[3], 1);
	PlayerTextDrawSetShadow(playerid,LotoTD[3], 0);

	LotoTD[4] = CreatePlayerTextDraw(playerid,225.333297, 113.077514, "__~n~~n~~n~~n~");
	PlayerTextDrawLetterSize(playerid,LotoTD[4], 0.223333, 6.743701);
	PlayerTextDrawTextSize(playerid,LotoTD[4], 0.000000, 50.000000);
	PlayerTextDrawAlignment(playerid,LotoTD[4], 2);
	PlayerTextDrawColor(playerid,LotoTD[4], -1);
	PlayerTextDrawUseBox(playerid,LotoTD[4], 1);
	PlayerTextDrawBoxColor(playerid,LotoTD[4], -1593835603);//-1593877843);
	PlayerTextDrawSetShadow(playerid,LotoTD[4], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[4], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[4], 11075839);
	PlayerTextDrawFont(playerid,LotoTD[4], 1);
	PlayerTextDrawSetProportional(playerid,LotoTD[4], 1);
	PlayerTextDrawSetShadow(playerid,LotoTD[4], 0);

	LotoTD[5] = CreatePlayerTextDraw(playerid,319.083282, 112.558975, "__~n~~n~~n~~n~");
	PlayerTextDrawLetterSize(playerid,LotoTD[5], 0.223333, 6.743701);
	PlayerTextDrawTextSize(playerid,LotoTD[5], 0.000000, 50.000000);
	PlayerTextDrawAlignment(playerid,LotoTD[5], 2);
	PlayerTextDrawColor(playerid,LotoTD[5], -1);
	PlayerTextDrawUseBox(playerid,LotoTD[5], 1);
	PlayerTextDrawBoxColor(playerid,LotoTD[5], -1593835603); //-1593877843);
	PlayerTextDrawSetShadow(playerid,LotoTD[5], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[5], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[5], 11075839);
	PlayerTextDrawFont(playerid,LotoTD[5], 1);
	PlayerTextDrawSetProportional(playerid,LotoTD[5], 1);
	PlayerTextDrawSetShadow(playerid,LotoTD[5], 0);

	LotoTD[6] = CreatePlayerTextDraw(playerid,412.216552, 112.833076, "__~n~~n~~n~~n~");
	PlayerTextDrawLetterSize(playerid,LotoTD[6], 0.223333, 6.743701);
	PlayerTextDrawTextSize(playerid,LotoTD[6], 0.000000, 50.000000);
	PlayerTextDrawAlignment(playerid,LotoTD[6], 2);
	PlayerTextDrawColor(playerid,LotoTD[6], -1);
	PlayerTextDrawUseBox(playerid,LotoTD[6], 1);
	PlayerTextDrawBoxColor(playerid,LotoTD[6], -1593835603); //-1593877843);
	PlayerTextDrawSetShadow(playerid,LotoTD[6], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[6], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[6], 11075839);
	PlayerTextDrawFont(playerid,LotoTD[6], 1);
	PlayerTextDrawSetProportional(playerid,LotoTD[6], 1);
	PlayerTextDrawSetShadow(playerid,LotoTD[6], 0);

	LotoTD[7] = CreatePlayerTextDraw(playerid,319.083190, 226.396209, "SUKTI");
	PlayerTextDrawLetterSize(playerid,LotoTD[7], 0.333748, 1.812592);
	PlayerTextDrawTextSize(playerid,LotoTD[7], 20.079998, 49.799865);
	PlayerTextDrawAlignment(playerid,LotoTD[7], 2);
	PlayerTextDrawColor(playerid,LotoTD[7], -1);
	PlayerTextDrawUseBox(playerid,LotoTD[7], 1);
	PlayerTextDrawBoxColor(playerid,LotoTD[7], 255);
	PlayerTextDrawSetShadow(playerid,LotoTD[7], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[7], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[7], 9502975);
	PlayerTextDrawFont(playerid,LotoTD[7], 1);
	PlayerTextDrawSetProportional(playerid,LotoTD[7], 1);
	PlayerTextDrawSetShadow(playerid,LotoTD[7], 0);
	PlayerTextDrawSetSelectable(playerid,LotoTD[7], true);

	LotoTD[8] = CreatePlayerTextDraw(playerid,198.833343, 111.225936, "_");
	PlayerTextDrawLetterSize(playerid,LotoTD[8], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid,LotoTD[8], 52.930011, 64.120025);
	PlayerTextDrawAlignment(playerid,LotoTD[8], 1);
	PlayerTextDrawColor(playerid,LotoTD[8], -1);
	PlayerTextDrawSetShadow(playerid,LotoTD[8], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[8], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[8], SPIN_BG);
	PlayerTextDrawFont(playerid,LotoTD[8], 5);
	PlayerTextDrawSetProportional(playerid,LotoTD[8], 0);
	PlayerTextDrawSetShadow(playerid,LotoTD[8], 0);
	PlayerTextDrawSetPreviewModel(playerid,LotoTD[8],0);
	PlayerTextDrawSetPreviewRot(playerid,LotoTD[8], 347.000000, 0.000000, 320.000000, 1000);


	LotoTD[9] = CreatePlayerTextDraw(playerid,199.033370, 203.322204, "_");
	PlayerTextDrawLetterSize(playerid,LotoTD[9], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid,LotoTD[9], 52.930011, 64.120025);
	PlayerTextDrawAlignment(playerid,LotoTD[9], 1);
	PlayerTextDrawColor(playerid,LotoTD[9], -1);
	PlayerTextDrawSetShadow(playerid,LotoTD[9], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[9], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[9], SPIN_BG);
	PlayerTextDrawFont(playerid,LotoTD[9], 5);
	PlayerTextDrawSetProportional(playerid,LotoTD[9], 0);
	PlayerTextDrawSetShadow(playerid,LotoTD[9], 0);
	PlayerTextDrawSetPreviewModel(playerid,LotoTD[9],0);
	PlayerTextDrawSetPreviewRot(playerid,LotoTD[9], 347.000000, 0.000000, 320.000000, 1000);


	LotoTD[10] = CreatePlayerTextDraw(playerid,199.033309, 293.544403, "_");
	PlayerTextDrawLetterSize(playerid,LotoTD[10], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid,LotoTD[10], 52.930011, 64.120025);
	PlayerTextDrawAlignment(playerid,LotoTD[10], 1);
	PlayerTextDrawColor(playerid,LotoTD[10], -1);
	PlayerTextDrawSetShadow(playerid,LotoTD[10], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[10], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[10], SPIN_BG);
	PlayerTextDrawFont(playerid,LotoTD[10], 5);
	PlayerTextDrawSetProportional(playerid,LotoTD[10], 0);
	PlayerTextDrawSetShadow(playerid,LotoTD[10], 0);
	PlayerTextDrawSetPreviewModel(playerid,LotoTD[10],0);
	PlayerTextDrawSetPreviewRot(playerid,LotoTD[10], 347.000000, 0.000000, 320.000000, 1000);


	LotoTD[11] = CreatePlayerTextDraw(playerid,292.366607, 293.544372, "_");
	PlayerTextDrawLetterSize(playerid,LotoTD[11], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid,LotoTD[11], 52.930011, 64.120025);
	PlayerTextDrawAlignment(playerid,LotoTD[11], 1);
	PlayerTextDrawColor(playerid,LotoTD[11], -1);
	PlayerTextDrawSetShadow(playerid,LotoTD[11], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[11], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[11], SPIN_BG);
	PlayerTextDrawFont(playerid,LotoTD[11], 5);
	PlayerTextDrawSetProportional(playerid,LotoTD[11], 0);
	PlayerTextDrawSetShadow(playerid,LotoTD[11], 0);
	PlayerTextDrawSetPreviewModel(playerid,LotoTD[11],0);
	PlayerTextDrawSetPreviewRot(playerid,LotoTD[11], 347.000000, 0.000000, 320.000000, 1000);



	LotoTD[12] = CreatePlayerTextDraw(playerid,385.699890, 294.062896, "_");
	PlayerTextDrawLetterSize(playerid,LotoTD[12], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid,LotoTD[12], 52.930011, 64.120025);
	PlayerTextDrawAlignment(playerid,LotoTD[12], 1);
	PlayerTextDrawColor(playerid,LotoTD[12], -1);
	PlayerTextDrawSetShadow(playerid,LotoTD[12], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[12], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[12], SPIN_BG);
	PlayerTextDrawFont(playerid,LotoTD[12], 5);
	PlayerTextDrawSetProportional(playerid,LotoTD[12], 0);
	PlayerTextDrawSetShadow(playerid,LotoTD[12], 0);
	PlayerTextDrawSetPreviewModel(playerid,LotoTD[12],0);
	PlayerTextDrawSetPreviewRot(playerid,LotoTD[12], 347.000000, 0.000000, 320.000000, 1000);



	LotoTD[13] = CreatePlayerTextDraw(playerid,385.883148, 203.840682, "_");
	PlayerTextDrawLetterSize(playerid,LotoTD[13], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid,LotoTD[13], 52.930011, 64.120025);
	PlayerTextDrawAlignment(playerid,LotoTD[13], 1);
	PlayerTextDrawColor(playerid,LotoTD[13], -1);
	PlayerTextDrawSetShadow(playerid,LotoTD[13], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[13], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[13], SPIN_BG);
	PlayerTextDrawFont(playerid,LotoTD[13], 5);
	PlayerTextDrawSetProportional(playerid,LotoTD[13], 0);
	PlayerTextDrawSetShadow(playerid,LotoTD[13], 0);
	PlayerTextDrawSetPreviewModel(playerid,LotoTD[13],0);
	PlayerTextDrawSetPreviewRot(playerid,LotoTD[13], 347.000000, 0.000000, 320.000000, 1000);



	LotoTD[14] = CreatePlayerTextDraw(playerid,385.466613, 111.544410, "_");
	PlayerTextDrawLetterSize(playerid,LotoTD[14], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid,LotoTD[14], 52.930011, 64.120025);
	PlayerTextDrawAlignment(playerid,LotoTD[14], 1);
	PlayerTextDrawColor(playerid,LotoTD[14], -1);
	PlayerTextDrawSetShadow(playerid,LotoTD[14], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[14], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[14], SPIN_BG);
	PlayerTextDrawFont(playerid,LotoTD[14], 5);
	PlayerTextDrawSetProportional(playerid,LotoTD[14], 0);
	PlayerTextDrawSetShadow(playerid,LotoTD[14], 0);
	PlayerTextDrawSetPreviewModel(playerid,LotoTD[14],0);
	PlayerTextDrawSetPreviewRot(playerid,LotoTD[14], 347.000000, 0.000000, 320.000000, 1000);


	LotoTD[15] = CreatePlayerTextDraw(playerid,292.883209, 111.425895, "aaa");
	PlayerTextDrawLetterSize(playerid,LotoTD[15], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid,LotoTD[15], 52.930011, 64.120025);
	PlayerTextDrawAlignment(playerid,LotoTD[15], 1);
	PlayerTextDrawColor(playerid,LotoTD[15], -1);
	PlayerTextDrawSetShadow(playerid,LotoTD[15], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[15], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[15], SPIN_BG);
	PlayerTextDrawFont(playerid,LotoTD[15], 5);
	PlayerTextDrawSetProportional(playerid,LotoTD[15], 0);
	PlayerTextDrawSetShadow(playerid,LotoTD[15], 0);
	PlayerTextDrawSetPreviewModel(playerid,LotoTD[15],0);
	PlayerTextDrawSetPreviewRot(playerid,LotoTD[15], 347.000000, 0.000000, 320.000000, 1000);

	// repeat starts here

	LotoTD[16] = CreatePlayerTextDraw(playerid,198.833343, 111.225936, "");
	PlayerTextDrawLetterSize(playerid,LotoTD[16], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid,LotoTD[16], 52.930011, 64.120025);
	PlayerTextDrawAlignment(playerid,LotoTD[16], 1);
	PlayerTextDrawColor(playerid,LotoTD[16], -1);
	PlayerTextDrawSetShadow(playerid,LotoTD[16], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[16], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[16], SPIN_BG & 0x00);
	PlayerTextDrawFont(playerid,LotoTD[16], 5);
	PlayerTextDrawSetProportional(playerid,LotoTD[16], 0);
	PlayerTextDrawSetShadow(playerid,LotoTD[16], 0);
	PlayerTextDrawSetPreviewModel(playerid,LotoTD[16], LotoCars[0]);
	PlayerTextDrawSetPreviewRot(playerid,LotoTD[16], 347.000000, 0.000000, 320.000000, 0.853976);
	PlayerTextDrawSetPreviewVehCol(playerid,LotoTD[16], -1, -1);

	LotoTD[17] = CreatePlayerTextDraw(playerid,199.033370, 203.322204, "");
	PlayerTextDrawLetterSize(playerid,LotoTD[17], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid,LotoTD[17], 52.930011, 64.120025);
	PlayerTextDrawAlignment(playerid,LotoTD[17], 1);
	PlayerTextDrawColor(playerid,LotoTD[17], -1);
	PlayerTextDrawSetShadow(playerid,LotoTD[17], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[17], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[17], SPIN_BG);
	PlayerTextDrawFont(playerid,LotoTD[17], 5);
	PlayerTextDrawSetProportional(playerid,LotoTD[17], 0);
	PlayerTextDrawSetShadow(playerid,LotoTD[17], 0);
	PlayerTextDrawSetPreviewModel(playerid,LotoTD[17], LotoCars[1]);
	PlayerTextDrawSetPreviewRot(playerid,LotoTD[17], 347.000000, 0.000000, 320.000000, 0.853976);
	PlayerTextDrawSetPreviewVehCol(playerid,LotoTD[17], -1, -1);

	LotoTD[18] = CreatePlayerTextDraw(playerid,199.033309, 293.544403, "");
	PlayerTextDrawLetterSize(playerid,LotoTD[18], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid,LotoTD[18], 52.930011, 64.120025);
	PlayerTextDrawAlignment(playerid,LotoTD[18], 1);
	PlayerTextDrawColor(playerid,LotoTD[18], -1);
	PlayerTextDrawSetShadow(playerid,LotoTD[18], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[18], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[18], SPIN_BG);
	PlayerTextDrawFont(playerid,LotoTD[18], 5);
	PlayerTextDrawSetProportional(playerid,LotoTD[18], 0);
	PlayerTextDrawSetShadow(playerid,LotoTD[18], 0);
	PlayerTextDrawSetPreviewModel(playerid,LotoTD[18], LotoCars[2]);
	PlayerTextDrawSetPreviewRot(playerid,LotoTD[18], 347.000000, 0.000000, 320.000000, 0.853976);
	PlayerTextDrawSetPreviewVehCol(playerid,LotoTD[18], -1, -1);

	LotoTD[19] = CreatePlayerTextDraw(playerid,292.366607, 293.544372, "");
	PlayerTextDrawLetterSize(playerid,LotoTD[19], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid,LotoTD[19], 52.930011, 64.120025);
	PlayerTextDrawAlignment(playerid,LotoTD[19], 1);
	PlayerTextDrawColor(playerid,LotoTD[19], -1);
	PlayerTextDrawSetShadow(playerid,LotoTD[19], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[19], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[19], SPIN_BG);
	PlayerTextDrawFont(playerid,LotoTD[19], 5);
	PlayerTextDrawSetProportional(playerid,LotoTD[19], 0);
	PlayerTextDrawSetShadow(playerid,LotoTD[19], 0);
	PlayerTextDrawSetPreviewModel(playerid,LotoTD[19], LotoCars[3]);
	PlayerTextDrawSetPreviewRot(playerid,LotoTD[19], 347.000000, 0.000000, 320.000000, 0.853976);
	PlayerTextDrawSetPreviewVehCol(playerid,LotoTD[19], -1, -1);

	LotoTD[20] = CreatePlayerTextDraw(playerid,385.699890, 294.062896, "");
	PlayerTextDrawLetterSize(playerid,LotoTD[20], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid,LotoTD[20], 52.930011, 64.120025);
	PlayerTextDrawAlignment(playerid,LotoTD[20], 1);
	PlayerTextDrawColor(playerid,LotoTD[20], -1);
	PlayerTextDrawSetShadow(playerid,LotoTD[20], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[20], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[20], SPIN_BG);
	PlayerTextDrawFont(playerid,LotoTD[20], 5);
	PlayerTextDrawSetProportional(playerid,LotoTD[20], 0);
	PlayerTextDrawSetShadow(playerid,LotoTD[20], 0);
	PlayerTextDrawSetPreviewModel(playerid,LotoTD[20], LotoCars[4]);
	PlayerTextDrawSetPreviewRot(playerid,LotoTD[20], 347.000000, 0.000000, 320.000000, 0.853976);
	PlayerTextDrawSetPreviewVehCol(playerid,LotoTD[20], -1, -1);

	LotoTD[21] = CreatePlayerTextDraw(playerid,385.883148, 203.840682, "");
	PlayerTextDrawLetterSize(playerid,LotoTD[21], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid,LotoTD[21], 52.930011, 64.120025);
	PlayerTextDrawAlignment(playerid,LotoTD[21], 1);
	PlayerTextDrawColor(playerid,LotoTD[21], -1);
	PlayerTextDrawSetShadow(playerid,LotoTD[21], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[21], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[21], SPIN_BG);
	PlayerTextDrawFont(playerid,LotoTD[21], 5);
	PlayerTextDrawSetProportional(playerid,LotoTD[21], 0);
	PlayerTextDrawSetShadow(playerid,LotoTD[21], 0);
	PlayerTextDrawSetPreviewModel(playerid,LotoTD[21], LotoCars[5]);
	PlayerTextDrawSetPreviewRot(playerid,LotoTD[21], 347.000000, 0.000000, 320.000000, 0.853976);
	PlayerTextDrawSetPreviewVehCol(playerid,LotoTD[21], -1, -1);

	LotoTD[22] = CreatePlayerTextDraw(playerid,385.466613, 111.544410, "");
	PlayerTextDrawLetterSize(playerid,LotoTD[22], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid,LotoTD[22], 52.930011, 64.120025);
	PlayerTextDrawAlignment(playerid,LotoTD[22], 1);
	PlayerTextDrawColor(playerid,LotoTD[22], -1);
	PlayerTextDrawSetShadow(playerid,LotoTD[22], 0);
	PlayerTextDrawSetOutline(playerid,LotoTD[22], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[22], SPIN_BG);
	PlayerTextDrawFont(playerid,LotoTD[22], 5);
	PlayerTextDrawSetProportional(playerid,LotoTD[22], 0);
	PlayerTextDrawSetShadow(playerid,LotoTD[22], 0);
	PlayerTextDrawSetPreviewModel(playerid,LotoTD[22], LotoCars[6]);
	PlayerTextDrawSetPreviewRot(playerid,LotoTD[22], 347.000000, 0.000000, 320.000000, 0.853976);
	PlayerTextDrawSetPreviewVehCol(playerid,LotoTD[22], -1, -1);

	LotoTD[23] = CreatePlayerTextDraw(playerid,292.883209, 111.425895, "");
	PlayerTextDrawLetterSize(playerid,LotoTD[23], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid,LotoTD[23], 52.930011, 64.120025);
	PlayerTextDrawAlignment(playerid,LotoTD[23], 1);
	PlayerTextDrawColor(playerid,LotoTD[23], -1);
	PlayerTextDrawSetShadow(playerid,LotoTD[23], 0);
	PlayerTextDrawUseBox(playerid,LotoTD[23],1);//, use)
	PlayerTextDrawBoxColor(playerid,LotoTD[23], 0xFF000000); // color)
	PlayerTextDrawSetOutline(playerid,LotoTD[23], 0);
	PlayerTextDrawBackgroundColor(playerid,LotoTD[23], 0xFF000000);
	PlayerTextDrawFont(playerid,LotoTD[23], 5);
	PlayerTextDrawSetProportional(playerid,LotoTD[23], 0);
	PlayerTextDrawSetShadow(playerid,LotoTD[23], 0);
	PlayerTextDrawSetPreviewModel(playerid,LotoTD[23], LotoCars[7]);
	PlayerTextDrawSetPreviewRot(playerid,LotoTD[23], 347.000000, 0.000000, 320.000000, 0.853976);
	PlayerTextDrawSetPreviewVehCol(playerid,LotoTD[23], -1, -1);



}