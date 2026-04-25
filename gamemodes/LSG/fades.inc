///////////////////////////////////////
///////////Made by Joe Staff///////////
///////////////////////////////////////

//#include <a_samp>
#define _UPDATERATE 98 //milliseconds
#define _TELEPORTFADECOLORR 0
#define _TELEPORTFADECOLORG 0
#define _TELEPORTFADECOLORB 0
#define _TELEPORTFADECOLORA 255

#define WALK_DEFAULT    0
#define WALK_NORMAL     1
#define WALK_PED        2
#define WALK_GANGSTA    3
#define WALK_GANGSTA2   4
#define WALK_OLD        5
#define WALK_FAT_OLD    6
#define WALK_FAT        7
#define WALK_LADY       8
#define WALK_LADY2      9
#define WALK_WHORE      10
#define WALK_WHORE2     11
#define WALK_DRUNK      12
#define WALK_BLIND      13

forward _UpdateFadeTimer();
//forward OnFadeComplete(playerid,beforehold);
new _pEndColor[MAX_PLAYERS][4];
new _pCurrentColor[MAX_PLAYERS][4];
new _pRateColor[MAX_PLAYERS][4];
new _pStep[MAX_PLAYERS];
new _pHold[MAX_PLAYERS];
new _pText[MAX_PLAYERS];
new _PlayerTeleporting[MAX_PLAYERS];
new _pTPInt[MAX_PLAYERS];
new _pTPVW[MAX_PLAYERS];
new Float:_pTPToPos[MAX_PLAYERS][4];
new _pTPSteps[MAX_PLAYERS];
new _pTPVeh[MAX_PLAYERS];
new Text:_text; //Look, only one!
/*
native ConvertToColor(RR,GG,BB,AA);
native StopPlayerFade(playerid);
native FadeColorForPlayer(playerid,RR1,GG1,BB1,AA1,RR2,GG2,BB2,AA2,steps,hold);
native FadeInit();
native FadeExit();
native FadePlayerConnect(playerid);
native FadePlayerDisonnect(playerid);
native SetPlayerPosFade(playerid,steps,Float:x,Float:y,Float:z);
*/

//SetPlayerPosFade(playerid,20,x,y,z);
//SetVehiclePosFade(playerid,20,x,y,z);
stock SetPlayerPosFade(playerid,steps,Float:x,Float:y,Float:z,interior = -1,virtualworld = -1)
{
	//if(_PlayerTeleporting[playerid]) return;
	_PlayerTeleporting[playerid]=1;
	_pTPToPos[playerid][0]=x;
	_pTPToPos[playerid][1]=y;
	_pTPToPos[playerid][2]=z;
	_pTPSteps[playerid]=steps;
	_pTPInt[playerid]=interior;
	_pTPVW[playerid]=virtualworld;
	_pTPVeh[playerid]=0;
	steps=floatround(steps/2);
	FadeColorForPlayer(playerid,0,0,0,0,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,steps,0);
	return 1;
}
stock SetVehiclePosFade(playerid,steps,Float:x,Float:y,Float:z,Float:a,interior = -1,virtualworld = -1)
{
	//if(_PlayerTeleporting[playerid]) return;
	_PlayerTeleporting[playerid]=4;
	_pTPToPos[playerid][0]=x;
	_pTPToPos[playerid][1]=y;
	_pTPToPos[playerid][2]=z;
	_pTPToPos[playerid][3]=a;
	_pTPSteps[playerid]=steps;
	_pTPInt[playerid]=interior;
	_pTPVW[playerid]=virtualworld;
	steps=floatround(steps/2);
	FadeColorForPlayer(playerid,0,0,0,0,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,steps,0);
}
//4278190080+16711680+65280
stock ConvertToColor(RR,GG,BB,AA)return (RR*16777216)+(GG*65536)+(BB*256)+AA;

stock FadeColorForPlayer(playerid,RR1,GG1,BB1,AA1,RR2,GG2,BB2,AA2,steps,hold)
{
	Iter_Add(PlayersFading,playerid);
	_pStep[playerid]=steps;//countdown, sorta
	_pTPSteps[playerid]=steps;
	new tmpsteps; //This will have to be added to incase the math is messed up (programming annoyance)
	_pHold[playerid]=hold;//How long the last color is held before disappearing (Divide this by UPDATERATE to get the time Ex:hold=10, in milliseconds that's 1000)
	_pEndColor[playerid][0]=RR2;
	_pEndColor[playerid][1]=GG2;
	_pEndColor[playerid][2]=BB2;
	_pEndColor[playerid][3]=AA2;
	_pCurrentColor[playerid][0]=RR1;
	_pCurrentColor[playerid][1]=GG1;
	_pCurrentColor[playerid][2]=BB1;
	_pCurrentColor[playerid][3]=AA1;
	_pRateColor[playerid][0]=(RR1-RR2)/steps;
	_pRateColor[playerid][1]=(GG1-GG2)/steps;
	_pRateColor[playerid][2]=(BB1-BB2)/steps;
	_pRateColor[playerid][3]=(AA1-AA2)/steps;
	//No dividing by 0!
	if(_pRateColor[playerid][0]!=0)if(((RR1-RR2)/_pRateColor[playerid][0])>steps)tmpsteps=((RR1-RR2)/_pRateColor[playerid][0])-steps;
	if(_pRateColor[playerid][1]!=0)if(((GG1-GG2)/_pRateColor[playerid][1])>steps+tmpsteps)tmpsteps=((GG1-GG2)/_pRateColor[playerid][1])-steps;
	if(_pRateColor[playerid][2]!=0)if(((BB1-BB2)/_pRateColor[playerid][2])>steps+tmpsteps)tmpsteps=((BB1-BB2)/_pRateColor[playerid][2])-steps;
	if(_pRateColor[playerid][3]!=0)if(((AA1-AA2)/_pRateColor[playerid][3])>steps+tmpsteps)tmpsteps=((AA1-AA2)/_pRateColor[playerid][3])-steps;
	if(tmpsteps)_pStep[playerid]+=tmpsteps+1;
	return 1;
}
#define START_BENCH(%0); {new __a=%0,__b=0,__c,__d=GetTickCount(),__e=1;do{}\
    while(__d==GetTickCount());__c=GetTickCount();__d=__c;while(__c-__d<__a||\
    __e){if(__e){if(__c-__d>=__a){__e=0;__c=GetTickCount();do{}while(__c==\
    GetTickCount());__c=GetTickCount();__d=__c;__b=0;}}{
#define FINISH_BENCH(%0); }__b++;__c=GetTickCount();}printf(" Bench for "\
    %0": executes, by average, %.2f times/ms.",floatdiv(__b,__a));}
FadeInit()
{
	_text=TextDrawCreate(0.0,0.0,"~r~");
	TextDrawTextSize(_text,640,480);
	TextDrawLetterSize(_text,0.0,50.0);
	TextDrawUseBox(_text,1);
	SetTimer("_UpdateFadeTimer",_UPDATERATE,1);
	/*START_BENCH( 1000 );
	{
		_UpdateFadeTimer();
	}
	FINISH_BENCH( "FadeTimer" );*/
	return 1;
}
/*FadeExit()
{
	TextDrawDestroy(_text);
	return 1;
}*/
stock FadePlayerConnect(playerid)
{
	_pHold[playerid]=0;
	_pStep[playerid]=0;
	_PlayerTeleporting[playerid]=0;
	_pTPInt[playerid]=-1;
	_pTPVW[playerid]=-1;
	_pText[playerid]=0;
	return 1;
}

stock StopPlayerFade(playerid)
{
	_pStep[playerid]=0;
	_pHold[playerid]=0;
}
new forwalk;
public _UpdateFadeTimer() // (playerid)
{
	DriftCheck();
	if(RocketManager != INVALID_PLAYER_ID)
		RocketManagerFunc();
	forwalk++;
	if(forwalk== 1)
	{
		CheckMoneySpray();
	}
	if(forwalk==2)
	{
		forwalk=0;
		foreach(PlayersWalking,playerid)
		{
			if(!gPlayerUsingLoopingAnim[playerid])
			{
				new keys,updown,leftright;
				GetPlayerKeys(playerid,keys,updown,leftright);
				if(!(keys & KEY_FIRE) && !(keys & KEY_HANDBRAKE))
				{
					if(!Jumped[playerid] && !JumpStatus[playerid])
					{
						if((keys & KEY_WALK) && ((updown & KEY_UP || updown & KEY_DOWN) || (leftright & KEY_LEFT || leftright & KEY_RIGHT)))
						{
							//printf(GetAnimNameForWalk(playerDB[playerid][wstyle]));
							//ApplyAnimation(playerid,"PED",GetAnimNameForWalk(playerDB[playerid][wstyle]),4.1,1,1,1,1,1);
							//printf("%i",GetPlayerAnimationIndex(playerid));
						}
						else 
							ApplyAnimation(playerid,"PED",GetAnimNameForWalk(playerDB[playerid][wstyle]),4.0,0,0,0,0,1), PlayerWalking[playerid]=0;
					}
				}
				else 
					ApplyAnimation(playerid,"PED",GetAnimNameForWalk(playerDB[playerid][wstyle]),4.0,0,0,0,0,1), PlayerWalking[playerid]=0;
				
			}
			if(!PlayerWalking[playerid])
				Iter_SafeRemove(PlayersWalking,playerid,playerid);
		}
	}
	new tickas = GetTickCount();
	foreach(PlayersFading,playerid)
	{
		if(fs_balloon_pl[playerid][0] == 1)
		{
			ControlBalloon(playerid);
		}
		if(_pHold[playerid])
		{
			_pHold[playerid]--;
		}
		else if(_pStep[playerid])
		{
			_pStep[playerid]--;
			for(new color;color<4;color++)
			{
				_pCurrentColor[playerid][color]-=_pRateColor[playerid][color];
				if(_pRateColor[playerid][color]>0)
				{
					if(_pCurrentColor[playerid][color]<_pEndColor[playerid][color])_pCurrentColor[playerid][color]=_pEndColor[playerid][color];
				}
				if(_pRateColor[playerid][color]<0)
				{
					if(_pCurrentColor[playerid][color]>_pEndColor[playerid][color])_pCurrentColor[playerid][color]=_pEndColor[playerid][color];
				}
				if(_pCurrentColor[playerid][color]<0)_pCurrentColor[playerid][color]=0;
				if(_pCurrentColor[playerid][color]>255)_pCurrentColor[playerid][color]=255;
			}
			TextDrawBoxColor(_text,ConvertToColor(_pCurrentColor[playerid][0],_pCurrentColor[playerid][1],_pCurrentColor[playerid][2],_pCurrentColor[playerid][3]));
			TextDrawShowForPlayer(playerid,_text);


			if(_pStep[playerid]==0)
			{
				switch(_PlayerTeleporting[playerid])
				{
					case 1:
					{
						SetPlayerPoz(playerid,_pTPToPos[playerid][0],_pTPToPos[playerid][1],_pTPToPos[playerid][2],_pTPInt[playerid],_pTPVW[playerid]); 
						FadeColorForPlayer(playerid,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,0,0,0,0,_pTPSteps[playerid],3);
						_PlayerTeleporting[playerid]=2;
					}
					case 2:
					{
						_PlayerTeleporting[playerid]=0;
						TextDrawHideForPlayer(playerid,_text);
					}
					case 4:
					{
						new vehicleid = GetPlayerVehicleID(playerid);
						SetVehiclePoz(vehicleid,_pTPToPos[playerid][0],_pTPToPos[playerid][1],_pTPToPos[playerid][2]);
						SetVehicleZAngle(vehicleid, _pTPToPos[playerid][3]);
						if(_pTPInt[playerid] != -1) LinkVehicleToInterior(vehicleid, _pTPInt[playerid]),SetPlayerInterior(playerid, _pTPInt[playerid]);
						if(_pTPVW[playerid] != -1) SetVehicleVirtualWorld(vehicleid, _pTPVW[playerid]),SetPlayerVirtualWorld(playerid, _pTPVW[playerid]);
						FadeColorForPlayer(playerid,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,0,0,0,0,_pTPSteps[playerid],3);
						_PlayerTeleporting[playerid]=2;
					}
					case 5:
					{
						_PlayerTeleporting[playerid]=2;
						new did = GetPlayerVirtualWorld(playerid)-(MAX_HOUSES*2+MAX_BUSINESSES);
						if(did < 0) continue;
						//Daugiabuciai[did][dLiftU]=false;
						new id = Daugiabuciai[did][dLift];
						SetPlayerPoz(playerid,VLiftoDurys[id][0],VLiftoDurys[id][1],VLiftoDurys[id][2]);
						FadeColorForPlayer(playerid,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,0,0,0,0,_pTPSteps[playerid],3);
						TogglePlayerControllable(playerid,true);
					}
					case 6:
					{
						_PlayerTeleporting[playerid]=2;
						FadeColorForPlayer(playerid,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,0,0,0,0,_pTPSteps[playerid],3);
						new world=GetPlayerVirtualWorld(playerid);
						new int=GetPlayerInterior(playerid);
						new job=PlayerLastJob[playerid][0];
						new car=PlayerLastJob[playerid][1];
						//PlayerCar[playerid] = CreateVehicle(DarbinesCar[job][car][DCmodel],DarbinesCar[job][car][DCX],DarbinesCar[job][car][DCY],DarbinesCar[job][car][DCZ],DarbinesCar[job][car][DCR],DarbinesCar[job][car][DCcolor1],DarbinesCar[job][car][DCcolor2],-3);
						SetVehiclePos(PlayerCar[playerid],DarbinesCar[job][car][DCX],DarbinesCar[job][car][DCY],DarbinesCar[job][car][DCZ]);
						SetVehicleZAngle(PlayerCar[playerid],DarbinesCar[job][car][DCR]);
						TogglePlayerControllable(playerid,true);
						LinkVehicleToInterior(PlayerCar[playerid],int);
						SetVehicleVirtualWorld(PlayerCar[playerid],world);
						PutPlayerInVehicle(playerid,PlayerCar[playerid],0);
						
					}
					case 7:
					{
						_PlayerTeleporting[playerid]=2;
						FadeColorForPlayer(playerid,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,0,0,0,0,_pTPSteps[playerid],3);
						new world=GetPlayerVirtualWorld(playerid);
						new int=GetPlayerInterior(playerid);
						new Float:Coo[4];
						GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
						GetPlayerFacingAngle(playerid,Coo[3]);
						//PlayerCar[playerid] = CreateVehicle(DarbinesCar[job][car][DCmodel],DarbinesCar[job][car][DCX],DarbinesCar[job][car][DCY],DarbinesCar[job][car][DCZ],DarbinesCar[job][car][DCR],DarbinesCar[job][car][DCcolor1],DarbinesCar[job][car][DCcolor2],-3);
						SetVehiclePos(PlayerCar[playerid],Coo[0],Coo[1],Coo[2]);
						SetVehicleZAngle(PlayerCar[playerid],Coo[3]);
						TogglePlayerControllable(playerid,true);
						if(!RogesActive[playerid])
							LinkVehicleToInterior(PlayerCar[playerid],int);
						SetVehicleVirtualWorld(PlayerCar[playerid],world);
						PutPlayerInVehicle(playerid,PlayerCar[playerid],0);
						
					}
					case 8:
					{
						_PlayerTeleporting[playerid]=2;
						FadeColorForPlayer(playerid,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,0,0,0,0,_pTPSteps[playerid],3);
						UpgradePlayerCar(playerid);
						
					}
					case 0:
					{
						TextDrawHideForPlayer(playerid,_text);
					}
					//default: CallLocalFunction("OnFadeComplete","ii",playerid,1);
				}
			}

			if(_pTPSteps[playerid] && _pTPSteps[playerid] >= _pStep[playerid]*2)
			{
				if(_PlayerTeleporting[playerid] == 2)
				{
					if(BitFlag_Get(PConfig[playerid],PCFG_SHOWALKIS))
					{
						SetProgressBarValue(Alkis, playerDB[playerid][sotumas]+10.0);
						ShowProgressBarForPlayer(playerid,Alkis);
					}
					if(BitFlag_Get(PConfig[playerid],PCFG_SHOWTIME))
					{
						//PConfig[playerid][showtime]=false;
						TextDrawShowForPlayer(playerid, TextdrawTime);
					}
					if(playerDB[playerid][logina])
						TextDrawShowForPlayer(playerid,LogTD);
				}
				else if(_PlayerTeleporting[playerid] > 0)
				{
					if(BitFlag_Get(PConfig[playerid],PCFG_SHOWALKIS))
						HideProgressBarForPlayer(playerid,Alkis);
					if(BitFlag_Get(PConfig[playerid],PCFG_SHOWTIME))
					{
						TextDrawHideForPlayer(playerid, TextdrawTime);
					}
					if(playerDB[playerid][logina])
						TextDrawHideForPlayer(playerid,LogTD);
				}
			}
		}
		if(_pText[playerid])
		{
			_pText[playerid]-=2; // 150
			if(_pText[playerid] == 600)
			{
				_pText[playerid]=0;
				PlayerTextDrawHide(playerid,JobText[playerid]);
			}
			else if(_pText[playerid] < 4)
			{
				_pText[playerid]=0;
				PlayerTextDrawHide(playerid,PlayerText[playerid]);
				
			}
			else if(_pText[playerid] < 60)
			{
				//_pText[playerid]--; 
				new val = _pText[playerid]*4;
				//TextDrawBoxColor(PlayerText[playerid],val);
				PlayerTextDrawColor(playerid,PlayerText[playerid],4294967040+val);
				PlayerTextDrawBackgroundColor(playerid,PlayerText[playerid],val);
				PlayerTextDrawShow(playerid,PlayerText[playerid]);
			}
		}
		if(pLastTick[playerid] != 0)
			PowerBarPlayer(playerid,tickas);
		if(playerDB[playerid][action])
		{
			playerDB[playerid][action]--;
			SetProgressBarMaxValue(Veiksmai, playerDB[playerid][actionmax]);
			SetProgressBarValue(Veiksmai, playerDB[playerid][action]);
			ShowProgressBarForPlayer(playerid, Veiksmai);
			UpdateProgressBar(Veiksmai,playerid);
			if(playerDB[playerid][action] <= 5)
			{
				playerDB[playerid][action]=0;
				HideProgressBarForPlayer(playerid,Veiksmai);
				OnSomethingFinish(playerid, playerDB[playerid][actionmax]);
				playerDB[playerid][actionmax]=0;
			}
		}
		else
		{
			if(!_pHold[playerid] && !_pStep[playerid] && !_pText[playerid] && pLastTick[playerid]==0 && fs_balloon_pl[playerid][0] != 1)
				Iter_SafeRemove(PlayersFading,playerid,playerid);
		
		}

	}
	foreach(Deganti,veh)
	{
		if(vehicleDB[veh][dega])
		{
			vehicleDB[veh][dega]--;
			vehicleDB[veh][sprogs]--;
			if(vehicleDB[veh][sprogs] == 0)
			{
				SetVehicleHealth(veh,240.0);
				vehicleDB[veh][sprogs]=20;
			}
			if(vehicleDB[veh][sprogs] == 2)
			{
				SetVehicleHealth(veh,300.0);
			}
			if(vehicleDB[veh][dega]==1)
			{
				vehicleDB[veh][sprogs]=0;
				vehicleDB[veh][dega]=0;
				Iter_SafeRemove(Deganti,veh,veh);
				SetVehicleHealth(veh,100.0);
				if(!ArNuosava(veh)) SetTimerEx("Respawnint",10000,false,"i",veh);
			}
			
		}
		else
		{
			printf("Reik isimt!");
			Iter_SafeRemove(Deganti,veh,veh);
			break;
		}
	}
}
stock GetAnimNameForWalk(style)
{
	new type[24];
	switch(style)
	{
		case WALK_NORMAL: type = "WALK_player";
		case WALK_PED: type = "WALK_civi";
		case WALK_GANGSTA: type = "WALK_gang1";
		case WALK_GANGSTA2 : type = "WALK_gang2";
		case WALK_OLD: type = "WALK_old";
		case WALK_FAT_OLD: type = "WALK_fatold";
		case WALK_FAT: type = "WALK_fat";
		case WALK_LADY: type = "WOMAN_walknorm";
		case WALK_LADY2: type = "WOMAN_walkbusy";
		case WALK_WHORE: type = "WOMAN_walkpro";
		case WALK_WHORE2: type = "WOMAN_walksexy";
		case WALK_DRUNK: type = "WALK_drunk";
		case WALK_BLIND: type = "WALK_Wuzi";	
		default: type = "WALK_player";
	}
	return type;
}