#define MAX_RACECHECKPOINTS 128 // Change if you want more room for checkpoints than this
#define MAX_BUILDERS 2 // Change if you want more builderslots than this
#define RACEFILE_VERSION 2 // !!! DO NOT CHANGE !!!
#define MENUSYSTEM // Enable menus, comment to disable, this script uses 11 menus so it might conflict with your stuff
				   // if you are using a lot of menus yourself (global limit for SA-MP: 128)
				   // Do note, however, that I plan on retiring most of the commands that can as of now (v0.4) reached
				   // by menus to make the script more "user friendly" (this is depending on feedback I get on the topic)

//########################################################//
// VARIABLES YOU MIGHT WANT TO MODIFY TO SUIT YOUR TASTES //
//  THESE CAN BE CHANGED VIA MENUS INGAME, BUT SETTINGS   //
//  ARE NOT SAVED (YET), SO YOU MIGHT WANT TO SET DEFAULT //
//  VALUES FROM HERE. < THIS SPACE IS LEFT BLANK >        //
//########################################################//
new MajorityDelay = 60; // Default delay to wait for other racers once half are ready (can be changed ingame via Admin menu)
new RRotation = -1;      // Is automatic Race Rotation enabled by defaul? (can be changed ingame via Admin menu) (-1 = disabled, 0+ = enabled)
new RRotationDelay = 300000; // How often will we poll for new race start if RRotation is enabled? (Default: 5 minutes, can't be changed IG)
new BuildAdmin = 1; //Require admin privileges for building races? 1)  yes, 0) no. (Can be changed ingame in Admin menu)
new RaceAdmin = 1;  //Require admin privileges for starting races? 1)  yes, 0) no. (Can be changed ingame in Admin menu)
new PrizeMode=0;        //Mode for winnings: 0 - Fixed, 1 - Dynamic, 2 - Entry fee, 3 - EF+F, 4 EF+D [Admin menu ingame]
new Prize=30000;        //Fixed prize sum (15,000$ for winner, 12,5000$ for 2nd and 10,000$ for 3rd) [Admin menu ingame]
new DynaMP=1;           //Dynamic prize multiplier. (Default: 1$/m) [Admin menu ingame]
new JoinFee=1000;     //Amount of $ it costs to /join a race      [Admin menu ingame]
//################################################//
// CHANGE THINGS PAST THIS POINT ON YOUR OWN RISK //
//################################################//
					
#if defined MENUSYSTEM
forward RefreshMenuHeader(playerid,Menu:menu,text[]);
new Menu:MAdmin, Menu:MPMode, Menu:MPrize, Menu:MDyna, Menu:MBuild, Menu:MLaps;
new Menu:MRace, Menu:MRacemode, Menu:MFee, Menu:MCPsize, Menu:MDelay;
#endif

#define COLORYR_GREEN 0x33AA33AA
#define COLORYR_RED 0xAA3333AA
#define COLORYR_YELLOW 0xFFFF00AA
#define COLORYR_WHITE 0xFFFFFFAA

forward RaceRotation();
forward LockRacers();
forward UnlockRacers();
forward SaveScores();   				// After race, if new best times have been made, saves them.
forward GetRaceTick(playerid);			// Gets amount of ticks the player was racing
forward GetLapTick(playerid); 		 	// Gets amount of ticks the player spend on the lap
forward ReadyRefresh();      	  		// Check the /ready status of players and start the race when ready
forward RaceSound(playerid,sound);      // Plays <sound> for <playerid>
forward BActiveCP(playerid,sele);       // Gives the player selected checkpoint
forward endrace();                      // Ends the race, whether it ended normally or by /endrace. Cleans the variables.
forward countdown();                    // Handles the countdown
forward mscountdown();                  //Majority Start countdown handler
forward strtokex(const string[],&index);
forward SetNextCheckpoint(playerid);    // Gives the next checkpoint for the player during race
forward CheckBestLap(playerid, laptime);	// Check if <laptime> is better than any of the ones in highscore list, and update.
forward CheckBestRace(playerid,racetime);   // Check if <racetime> is better than any of the ones in highscore list, and update.
forward ChangeLap(playerid);            // Change player's lap, print out time and stuff.
forward SetRaceCheckpoint(playerid,target,next);    // Race-mode checkpoint setter
forward SetBRaceCheckpoint(playerid,target,next);   // Builder-mode checkpoint  setter
//forward LoadTimes(playerid,timemode,tmp[]);     // bestlap and bestrace-parameter race loader
#define b(%0) (RaceBuilders[%0]-1)
forward Float:Distance(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2);
forward CreateRaceMenus();
// General variables
new RotationTimer;
new ystring[256];    // ystring
new CBuilder[MAX_PLAYER_NAME], CRaceName[50];        //Creator of the race and the filename, for score changing purposes.
// Racing-related variables
new Pot=0;              //Join fees go here
new Ranking;            //Finishing order for prizes
new Countdown=-1;          //Countdown timer
new cd;                 //Countdown time
new MajStart=0;         //Status of the Majority Start timer
new MajStartTimer;      //Majority Start timer
new mscd;               //Majority Start time
new RaceActive;         //Is a race active?
new RaceStart;          //Has race started?
new Float:RaceCheckpoints[MAX_RACECHECKPOINTS][3];  //Current race CP array
new LCurrentCheckpoint;                             //Current race array pointer
new CurrentCheckpoint[MAX_PLAYERS];                 //Current race array pointer array :V
new CurrentLap[MAX_PLAYERS];                        //Current lap array
new RaceParticipant[MAX_PLAYERS];                   //Has the player /joined the race
  // \_values: 0 - not in race, 1 - joined, 2 - arrived to start CP, 3 - /ready, 4 - racing, 5 - Last CP
new Participants;                                   //Amount of participants
new PlayerVehicles[MAX_PLAYERS];                    //For slapping the player back in their vehicle.
new ORacelaps, ORacemode;   //Saves the laps/mode from file in case they aren't changed
new OAirrace, Float:OCPsize;
new Racelaps, Racemode;		//If mode/laps has been changed, the new scores won't be saved.
new ScoreChange;            //Flag for new best times, so they are saved.
new RaceTick;               //Startime of the race
new LastLapTick[MAX_PLAYERS];       //Array that stores the times when players started the lap
new TopRacers[6][MAX_PLAYER_NAME]; // Stores 5 top scores, 6th isn't
new TopRacerTimes[6];              // saved to file, used to simplify
new TopLappers[6][MAX_PLAYER_NAME];// for() loops on CheckBestLap and
new TopLapTimes[6];                // CheckBestRace.
new Float:CPsize;                        // Checkpoint size for the race
new Airrace;                       // Is the race airrace?
new Ghost;
new Float:RLenght, Float:LLenght; //Lap lenght and race lenght
// Building-related variables
new BCurrentCheckpoints[MAX_BUILDERS];               //Buildrace array pointers
new BSelectedCheckpoint[MAX_BUILDERS];               //Selected checkpoint during building
new RaceBuilders[MAX_PLAYERS];                       //Who is building a race?
new BuilderSlots[MAX_BUILDERS];                      //Stores the racebuilder pids
new Float:BRaceCheckpoints[MAX_BUILDERS][MAX_RACECHECKPOINTS][3]; //Buildrace CP array
new Bracemode[MAX_BUILDERS];
new Blaps[MAX_BUILDERS];
new Float:BCPsize[MAX_BUILDERS];
new BAirrace[MAX_BUILDERS];



new PlayerText:TDEditor_PTD[MAX_PLAYERS][10];





/*
#include <streamer>
stock GetXYInFrontOfPlayer(playerid, &Float:x, &Float:y, Float:distance)
{
    new
        Float:a;
    GetPlayerPos( playerid, x, y, a );
    GetPlayerFacingAngle( playerid, a );
    x += ( distance * floatsin( -a, degrees ));
    y += ( distance * floatcos( -a, degrees ));
}
CMD:createobj(playerid,params[])
{
	new Float:Coo[3];
	GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
	GetXYInFrontOfPlayer(playerid, Coo[0],Coo[1], 5);
	new Float:a;
	GetPlayerFacingAngle(playerid,a);
	CreateDynamicObject(strval(params),Coo[0],Coo[1],Coo[2],0.0,0.0,(floatround(a+90) % 360));
	return 1;
}*/

stock LoadYRace()
{
	print("\n+--------------------------------+");
	print("| Yagu's Race Filterscript v0.4a |");
	print("+--------------LOADED------------+\n");
	// maps
	Ghost=0;
	RaceActive=0;
	Ranking=1;
	LCurrentCheckpoint=0;
	Participants=0;
	for(new i;i<MAX_BUILDERS;i++)
	{
	    BuilderSlots[i]=MAX_PLAYERS+1;
	}
	for(new i;i<MAX_PLAYERS;i++) if(IsPlayerConnected(i)) OnPlayerConnect(i);
	
	if(RRotation != -1) SetTimer("RaceRotation",RRotationDelay,1);
	SetTimer("UpdateTDs",1003,1);
	#if defined MENUSYSTEM
		CreateRaceMenus();
	#endif
	return 1;
}
forward UpdateTDs();
public UpdateTDs()
{
	if(RaceActive==1 )
	{
		if(Racemode <= 1) // default and ring
		{
			new TotalCPS[MAX_PLAYERS][4]; // {cp,dist,playerid,lap}
			new totalppl = 0;
			for(new c;c<MAX_PLAYERS;c++) if(IsPlayerConnected(c))
			{
				if(RaceParticipant[c]>=4) // 
				{
					totalppl++;
					new cp = CurrentCheckpoint[c];
					new Float:d = GetPlayerDistanceFromPoint(c, RaceCheckpoints[cp][0],RaceCheckpoints[cp][1],RaceCheckpoints[cp][2]);
					if(Racemode == 1 && cp == 0)
						cp=LCurrentCheckpoint+1;
					TotalCPS[totalppl-1][0]=cp;
					TotalCPS[totalppl-1][1]=floatround(d);
					TotalCPS[totalppl-1][2]=c; // playerid
					TotalCPS[totalppl-1][3]=CurrentLap[c];
				}
				else
				{
					for(new x;x<10;x++)
						PlayerTextDrawHide(c,TDEditor_PTD[c][x]);
				}
			}
			// bubble sort that shit
			new swaped = 1;
			while(swaped)
			{
				swaped=0;
				for(new a;a<totalppl-1;a++)
				{
					if(TotalCPS[a][3] < TotalCPS[a+1][3]) // laps of left side less than laps of rhs
					{
						swaped=1;
						new temp[4];
						temp[0] = TotalCPS[a][0];
						temp[1] = TotalCPS[a][1];
						temp[2] = TotalCPS[a][2];
						temp[3] = TotalCPS[a][3];
						TotalCPS[a][0] = TotalCPS[a+1][0];
						TotalCPS[a][1] = TotalCPS[a+1][1];
						TotalCPS[a][2] = TotalCPS[a+1][2];
						TotalCPS[a][3] = TotalCPS[a+1][3];
						TotalCPS[a+1][0] = temp[0];
						TotalCPS[a+1][1] = temp[1];
						TotalCPS[a+1][2] = temp[2];
						TotalCPS[a+1][3] = temp[3];
					
					}
					else if(TotalCPS[a][3] == TotalCPS[a+1][3]) // same lap
					{
						if(TotalCPS[a][0] < TotalCPS[a+1][0]) // cps of left side less than laps of rhs
						{
							swaped=1;
							new temp[4];
							temp[0] = TotalCPS[a][0];
							temp[1] = TotalCPS[a][1];
							temp[2] = TotalCPS[a][2];
							temp[3] = TotalCPS[a][3];
							TotalCPS[a][0] = TotalCPS[a+1][0];
							TotalCPS[a][1] = TotalCPS[a+1][1];
							TotalCPS[a][2] = TotalCPS[a+1][2];
							TotalCPS[a][3] = TotalCPS[a+1][3];
							TotalCPS[a+1][0] = temp[0];
							TotalCPS[a+1][1] = temp[1];
							TotalCPS[a+1][2] = temp[2];
							TotalCPS[a+1][3] = temp[3];
						}
						else if(TotalCPS[a][0] == TotalCPS[a+1][0])
						{
							if(TotalCPS[a][1] > TotalCPS[a+1][1]) // distance to cp of left side more than distance of right side
							{
								swaped=1;
								new temp[4];
								temp[0] = TotalCPS[a][0];
								temp[1] = TotalCPS[a][1];
								temp[2] = TotalCPS[a][2];
								temp[3] = TotalCPS[a][3];
								TotalCPS[a][0] = TotalCPS[a+1][0];
								TotalCPS[a][1] = TotalCPS[a+1][1];
								TotalCPS[a][2] = TotalCPS[a+1][2];
								TotalCPS[a][3] = TotalCPS[a+1][3];
								TotalCPS[a+1][0] = temp[0];
								TotalCPS[a+1][1] = temp[1];
								TotalCPS[a+1][2] = temp[2];
								TotalCPS[a+1][3] = temp[3];
							}
						
						}
					
					}
				
				}
			}
			// now to find places of each player
			new TopName[3][MAX_PLAYER_NAME];
			for(new x;x<3;x++)
			{
				if(RaceParticipant[TotalCPS[x][2]] >= 4)
					GetPlayerName(TotalCPS[x][2],TopName[x],MAX_PLAYER_NAME);
			}
			
			for(new x;x<totalppl;x++)
			{
				new i = TotalCPS[x][2]; // player id
				new place = x+1;
				new cp = TotalCPS[x][0];
				new msg[20];
	
				format(msg,sizeof(msg),"%i/%i",cp,LCurrentCheckpoint+1);
				PlayerTextDrawSetString(i,TDEditor_PTD[i][3],msg); // set checkpoints
				format(msg,sizeof(msg),"%i/%i",place,totalppl);
				PlayerTextDrawSetString(i,TDEditor_PTD[i][2],msg); // set place
					
				for(new z;z<3;z++)
				{
					PlayerTextDrawSetString(i,TDEditor_PTD[i][7+z],TopName[z]); // set checkpoints
				}
				for(new z;z<10;z++)
					PlayerTextDrawShow(i,TDEditor_PTD[i][z]);
				
			}
			/*
			for(new i;i<MAX_PLAYERS;i++) if(IsPlayerConnected(i))
			{
				if(RaceParticipant[i]>=4) // 
				{
					new msg[20];
					new target = CurrentCheckpoint[i];
					new Float:disttocp = GetPlayerDistanceFromPoint(i, RaceCheckpoints[target][0],RaceCheckpoints[target][1],RaceCheckpoints[target][2]);
					format(msg,sizeof(msg),"%i/%i",CurrentCheckpoint[i],LCurrentCheckpoint+1);
					PlayerTextDrawSetString(i,TDEditor_PTD[i][3],msg); // set checkpoints
					// now to find his place:
					new place=1;
					new totalppl = 0;
					
					for(new c;c<MAX_PLAYERS;c++)  if(IsPlayerConnected(c))
					{
						if(RaceParticipant[c] >=4)
						{
							totalppl++;
							
							if(i != c)
							{
								if(CurrentCheckpoint[c] > CurrentCheckpoint[i])
									place++;
								else if(CurrentCheckpoint[c] == CurrentCheckpoint[i])
								{
									new Float:dist = GetPlayerDistanceFromPoint(c, RaceCheckpoints[target][0],RaceCheckpoints[target][1],RaceCheckpoints[target][2]);
									if(dist < disttocp)
										place++;
								}
							}
							if(paskaiciavom == 0)
							{
								new cp = CurrentCheckpoint[c];
								new Float:d = GetPlayerDistanceFromPoint(c, RaceCheckpoints[cp][0],RaceCheckpoints[cp][1],RaceCheckpoints[cp][2]);
								TotalCPS[totalppl-1][0]=cp;
								TotalCPS[totalppl-1][1]=floatround(d);
								TotalCPS[totalppl-1][2]=c; // playerid
								
								
							}
						}
						
					}
					if(paskaiciavom == 0)
					{
						// bubble sort that shit
						new swaped = 1;
						while(swaped)
						{
							swaped=0;
							for(new a;a<totalppl-1;a++)
							{
								if(TotalCPS[a][0] < TotalCPS[a+1][0])
								{
									swaped=1;
									new temp[3];
									temp[0] = TotalCPS[a][0];
									temp[1] = TotalCPS[a][1];
									temp[2] = TotalCPS[a][2];
									TotalCPS[a][0] = TotalCPS[a+1][0];
									TotalCPS[a][1] = TotalCPS[a+1][1];
									TotalCPS[a][2] = TotalCPS[a+1][2];
									TotalCPS[a+1][0] = temp[0];
									TotalCPS[a+1][1] = temp[1];
									TotalCPS[a+1][2] = temp[2];
								}
								else if(TotalCPS[a][0] == TotalCPS[a+1][0])
								{
									if(TotalCPS[a][1] > TotalCPS[a+1][1])
									{
										swaped=1;
										new temp[3];
										temp[0] = TotalCPS[a][0];
										temp[1] = TotalCPS[a][1];
										temp[2] = TotalCPS[a][2];
										TotalCPS[a][0] = TotalCPS[a+1][0];
										TotalCPS[a][1] = TotalCPS[a+1][1];
										TotalCPS[a][2] = TotalCPS[a+1][2];
										TotalCPS[a+1][0] = temp[0];
										TotalCPS[a+1][1] = temp[1];
										TotalCPS[a+1][2] = temp[2];
									}
								
								}
							
							}
						}
						paskaiciavom = 1;
					}
					format(msg,sizeof(msg),"%i/%i",place,totalppl);
					PlayerTextDrawSetString(i,TDEditor_PTD[i][2],msg); // set checkpoints
					
					for(new x;x<3;x++)
					{
						new name[24];
						if(RaceParticipant[TotalCPS[x][2]] >= 4)
							GetPlayerName(TotalCPS[x][2],name,24);
						PlayerTextDrawSetString(i,TDEditor_PTD[i][7+x],name); // set checkpoints
					}
					for(new x;x<10;x++)
						PlayerTextDrawShow(i,TDEditor_PTD[i][x]);
				}
				else
				{
					for(new x;x<10;x++)
						PlayerTextDrawHide(i,TDEditor_PTD[i][x]);
				}
			}
			*/
		}
	}
	return 1;
}
public OnFilterScriptExit()
{
	print("\n+--------------------------------+");
	print("| Yagu's Race Filterscript v0.4a |");
	print("+------------UNLOADED------------+\n");
	#if defined MENUSYSTEM
	DestroyMenu(MAdmin);
	DestroyMenu(MPMode);
	DestroyMenu(MPrize);
	DestroyMenu(MDyna);
	DestroyMenu(MBuild);
	DestroyMenu(MLaps);
	DestroyMenu(MRace);
	DestroyMenu(MRacemode);
	DestroyMenu(MFee);
	DestroyMenu(MCPsize);
	DestroyMenu(MDelay);
	#endif
	return 1;
}
/*

public OnPlayerCommandText(playerid, cmdtext[])
{
	dcmd(racehelp,8,cmdtext);	// Racehelp - there's a lot of commands!
	dcmd(buildhelp,9,cmdtext);	// Buildhelp - there's a lot of commands!
	dcmd(buildrace,9,cmdtext);	// Buildrace - Start building a new race (suprising!)
	dcmd(cp,2,cmdtext);		  	// cp - Add a checkpoint
	dcmd(scp,3,cmdtext);		// scp - Select a checkpoint
	dcmd(rcp,3,cmdtext);		// rcp - Replace the current checkpoint with a new one
	dcmd(mcp,3,cmdtext);		// mcp - Move the selected checkpoint
	dcmd(dcp,3,cmdtext);       	// dcp - Delete the selected waypoint
	dcmd(clearrace,9,cmdtext);	// clearrace - Clear the current (new) race.
	dcmd(editrace,8,cmdtext);	// editrace - Load an existing race into the builder
	dcmd(saverace,8,cmdtext);	// saverace - Save the current checkpoints to a file
	dcmd(setlaps,7,cmdtext);	// setlaps - Set amount of laps to drive
	dcmd(racemode,8,cmdtext);	// racemode - Set the current racemode
	dcmd(loadrace,8,cmdtext);	// loadrace - Load a race from file and start it
	dcmd(startrace,9,cmdtext);  // starts the loaded race
	dcmd(join,4,cmdtext);		// join - Join the announced race.
	dcmd(leave,5,cmdtext);		// leave - leave the current race.
	dcmd(endrace,7,cmdtext);	// endrace - Complete the current race, clear tables & variables, stop the timer.
	dcmd(ready,5,cmdtext);		// ready - Player is ready to start, lock the controls, prepare for CD.
	dcmd(bestlap,7,cmdtext);	// bestlap - Display the best lap times for the current race
	dcmd(bestrace,8,cmdtext);	// bestrace - Display the best race times for the current race
	dcmd(deleterace,10,cmdtext);// deleterace - Remove the race from disk
	dcmd(airrace,7,cmdtext);    // airrace - Changes the checkpoints to air CPs and back
	dcmd(cpsize,6,cmdtext);     // cpsize - changes the checkpoint size
	dcmd(prizemode,9,cmdtext);
	dcmd(setprize,8,cmdtext);
	dcmd(gogogo,6,cmdtext);
	#if defined MENUSYSTEM
	dcmd(raceadmin,9,cmdtext);
	dcmd(buildmenu,9,cmdtext);
	#endif
	return 0;
} */


CMD:racehelp(playerid, params[])
{
    #pragma unused params
	SendClientMessage(playerid, COLORYR_GREEN, "Race script racing help:");
	SendClientMessage(playerid, COLORYR_WHITE, "/loadrace [name] to load a track and start it. Use /join to jo in, and /ready");
	SendClientMessage(playerid, COLORYR_WHITE, "once at start to begin the race once others are ready as well. /leave to leave");
	SendClientMessage(playerid, COLORYR_WHITE, "the race./endrace to aborts the race. /bestlap and /bestrace can be used to");
	SendClientMessage(playerid, COLORYR_WHITE, "display record times for the races, you can also specify a race to see the");
	SendClientMessage(playerid, COLORYR_WHITE, "times for it. For info on building races, see /buildhelp. For additional");
	SendClientMessage(playerid, COLORYR_WHITE, "settings, see /raceadmin.");
	return 1;
}

CMD:buildhelp(playerid, params[])
{
    #pragma unused params
	SendClientMessage(playerid, COLORYR_GREEN, "Race script building help:");
	SendClientMessage(playerid, COLORYR_WHITE, "/buildrace to start building, /cp for new a checkpoint, /scp to select an old");
	SendClientMessage(playerid, COLORYR_WHITE, "checkpoint, /dcp to delete, /mcp to move and /rcp to replace with a new one.");
	SendClientMessage(playerid, COLORYR_WHITE, "/saverace [name] to save the race and");
	SendClientMessage(playerid, COLORYR_WHITE, "/buildmenu to set racemode/laps/etc. For info on racing itself, see /racehelp");
	SendClientMessage(playerid, COLORYR_WHITE, "For additional settings, see /raceadmin.");
	return 1;
}
CMD:buildrace(playerid, params[])
{
    #pragma unused params
	if(BuildAdmin == 1 && IsNotAdmin(playerid)) return 1;
	if(RaceBuilders[playerid] != 0)
	{
		SendClientMessage(playerid, COLORYR_YELLOW, "You are already building a race, dork.");
	}
	else if(RaceParticipant[playerid]>0)
	{
	    SendClientMessage(playerid, COLORYR_YELLOW, "You are participating in a race, can't build a race.");
	}
	else
	{
		new slot;
		slot=GetBuilderSlot(playerid);
		if(slot == 0)
		{
			SendClientMessage(playerid, COLORYR_YELLOW, "No builderslots available!");
			return 1;
		}
		format(ystring,sizeof(ystring),"You are now building a race (Slot: %d)",slot);
		SendClientMessage(playerid, COLORYR_GREEN, ystring);
		RaceBuilders[playerid]=slot;
		BCurrentCheckpoints[b(playerid)]=0;
		Bracemode[b(playerid)]=0;
		Blaps[b(playerid)]=0;
		BAirrace[b(playerid)] = 0;
		BCPsize[b(playerid)] = 8.0;
	}
	return 1;
}

CMD:cp(playerid, params[])
{
	#pragma unused params
	if(RaceBuilders[playerid] != 0 && BCurrentCheckpoints[b(playerid)] < MAX_RACECHECKPOINTS)
	{
		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid,x,y,z);
		format(ystring,sizeof(ystring),"Checkpoint %d created: %f,%f,%f.",BCurrentCheckpoints[b(playerid)],x,y,z);
		SendClientMessage(playerid, COLORYR_GREEN, ystring);
		BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]][0]=x;
		BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]][1]=y;
		BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]][2]=z;
		BSelectedCheckpoint[b(playerid)]=BCurrentCheckpoints[b(playerid)];
		SetBRaceCheckpoint(playerid,BCurrentCheckpoints[b(playerid)],-1);
		BCurrentCheckpoints[b(playerid)]++;
	}
	else if(RaceBuilders[playerid] != 0 && BCurrentCheckpoints[b(playerid)] == MAX_RACECHECKPOINTS)
	{
		format(ystring,sizeof(ystring),"Sorry, maximum amount of checkpoints reached (%d).",MAX_RACECHECKPOINTS);
		SendClientMessage(playerid, COLORYR_YELLOW, ystring);
	}
	else
	{
		SendClientMessage(playerid, COLORYR_RED, "You are not building a race!");
	}
	return 1;
}

CMD:scp(playerid, params[])
{
	new sele, tmp[256], idx;
    tmp = strtokex(params, idx);
    if(!strlen(tmp)) {
		SendClientMessage(playerid, COLORYR_WHITE, "USAGE: /scp [checkpoint]");
		return 1;
    }
    sele = strval(tmp);
	if(RaceBuilders[playerid] != 0)
	{
		if(sele>BCurrentCheckpoints[b(playerid)]-1 || BCurrentCheckpoints[b(playerid)] < 1 || sele < 0)
		{
			SendClientMessage(playerid, COLORYR_YELLOW, "Invalid checkpoint!");
			return 1;
		}
		format(ystring,sizeof(ystring),"Selected checkpoint %d.",sele);
		SendClientMessage(playerid, COLORYR_GREEN, ystring);
		BActiveCP(playerid,sele);
		BSelectedCheckpoint[b(playerid)]=sele;
	}
	else
	{
		SendClientMessage(playerid, COLORYR_RED, "You are not building a race!");
	}
	return 1;
}

CMD:rcp(playerid, params[])
{
	#pragma unused params
	if(RaceBuilders[playerid] == 0)
	{
		SendClientMessage(playerid, COLORYR_RED, "You are not building a race!");
		return 1;
	}
	else if(BCurrentCheckpoints[b(playerid)] < 1)
	{
		SendClientMessage(playerid, COLORYR_YELLOW, "No checkpoint to replace!");
		return 1;
	}
	new Float:x,Float:y,Float:z;
	GetPlayerPos(playerid,x,y,z);
	format(ystring,sizeof(ystring),"Checkpoint %d replaced: %f,%f,%f.",BSelectedCheckpoint[b(playerid)],x,y,z);
	SendClientMessage(playerid, COLORYR_GREEN, ystring);
	BRaceCheckpoints[b(playerid)][BSelectedCheckpoint[b(playerid)]][0]=x;
	BRaceCheckpoints[b(playerid)][BSelectedCheckpoint[b(playerid)]][1]=y;
	BRaceCheckpoints[b(playerid)][BSelectedCheckpoint[b(playerid)]][2]=z;
	BActiveCP(playerid,BSelectedCheckpoint[b(playerid)]);
    return 1;
}

CMD:mcp(playerid, params[])
{
	if(RaceBuilders[playerid] == 0)
	{
		SendClientMessage(playerid, COLORYR_RED, "You are not building a race!");
		return 1;
	}
	else if(BCurrentCheckpoints[b(playerid)] < 1)
	{
		SendClientMessage(playerid, COLORYR_YELLOW, "No checkpoint to move!");
		return 1;
	}
	new idx, direction, dir[32];
	dir=strtokex(params, idx);
	new Float:amount=floatstr(strtokex(params,idx));
	if(amount == 0.0 || (dir[0] != 'x' && dir[0]!='y' && dir[0]!='z'))
	{
		SendClientMessage(playerid, COLORYR_WHITE, "USAGE: /mcp [x,y or z] [amount]");
		return 1;
	}
    if(dir[0] == 'x') direction=0;
    else if (dir[0] == 'y') direction=1;
    else if (dir[0] == 'z') direction=2;
    BRaceCheckpoints[b(playerid)][BSelectedCheckpoint[b(playerid)]][direction]=BRaceCheckpoints[b(playerid)][BSelectedCheckpoint[b(playerid)]][direction]+amount;
	BActiveCP(playerid,BSelectedCheckpoint[b(playerid)]);
	return 1;
}

CMD:dcp(playerid, params[])
{
	#pragma unused params
	if(RaceBuilders[playerid] == 0)
	{
		SendClientMessage(playerid, COLORYR_RED, "You are not building a race!");
		return 1;
	}
	else if(BCurrentCheckpoints[b(playerid)] < 1)
	{
		SendClientMessage(playerid, COLORYR_YELLOW, "No checkpoint to delete!");
		return 1;
	}
	for(new i=BSelectedCheckpoint[b(playerid)];i<BCurrentCheckpoints[b(playerid)];i++)
	{
		BRaceCheckpoints[b(playerid)][i][0]=BRaceCheckpoints[b(playerid)][i+1][0];
		BRaceCheckpoints[b(playerid)][i][1]=BRaceCheckpoints[b(playerid)][i+1][1];
		BRaceCheckpoints[b(playerid)][i][2]=BRaceCheckpoints[b(playerid)][i+1][2];
	}
	BCurrentCheckpoints[b(playerid)]--;
	BSelectedCheckpoint[b(playerid)]--;
	if(BCurrentCheckpoints[b(playerid)] < 1)
	{
	    DisablePlayerRaceCheckpoint(playerid);
	    BSelectedCheckpoint[b(playerid)]=0;
		return 1;
	}
	else if(BSelectedCheckpoint[b(playerid)] < 0)
	{
	    BSelectedCheckpoint[b(playerid)]=0;
	}
	BActiveCP(playerid,BSelectedCheckpoint[b(playerid)]);
	SendClientMessage(playerid,COLORYR_GREEN,"Checkpoint deleted!");
	return 1;
}

CMD:clearrace(playerid,params[])
{
	#pragma unused params
	if(RaceBuilders[playerid] != 0) clearrace(playerid);
	else SendClientMessage(playerid, COLORYR_RED, "You are not building a race!");
	return 1;
}
/*
CMD:editrace(playerid,params[])
{
	if(RaceBuilders[playerid] == 0)
	{
		SendClientMessage(playerid, COLORYR_RED, "You are not building a race!");
		return 1;
	}
	if(BCurrentCheckpoints[b(playerid)]>0) //Clear the old race if there is such.
	{
		for(new i=0;i<BCurrentCheckpoints[b(playerid)];i++)
		{
			BRaceCheckpoints[b(playerid)][i][0]=0.0;
			BRaceCheckpoints[b(playerid)][i][1]=0.0;
			BRaceCheckpoints[b(playerid)][i][2]=0.0;
		}
		BCurrentCheckpoints[b(playerid)]=0;
	}
	new tmp[256],idx;
    tmp = strtokex(params, idx);
    if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLORYR_WHITE, "USAGE: /editrace [name]");
		return 1;
    }
	new race_name[32],templine[42];
	format(race_name,sizeof(race_name), "%s.yr",tmp);
	if(!fexist(race_name))
	{
		format(ystring,sizeof(ystring), "The race \"%s\" doesn't exist.",tmp);
		SendClientMessage(playerid, COLORYR_RED, ystring);
		return 1;
	}
    BCurrentCheckpoints[b(playerid)]=-1;
	new File:f, i;
	f = fopen(race_name, io_read);
	fread(f,templine,sizeof(templine));
	if(templine[0] == 'Y') //Checking if the racefile is v0.2+
	{
		new fileversion;
	    strtokex(templine,i); // read off YRACE
		fileversion = strval(strtokex(templine,i)); // read off the file version
		if(fileversion > RACEFILE_VERSION) // Check if the race is made with a newer version of the racefile format
		{
		    format(ystring,128,"Race \'%s\' is created with a newer version of YRACE, unable to load.",tmp);
		    SendClientMessage(playerid,COLORYR_RED,ystring);
		    return 1;
		}
		strtokex(templine,i); // read off RACEBUILDER
		Bracemode[b(playerid)] = strval(strtokex(templine,i)); // read off racemode
		Blaps[b(playerid)] = strval(strtokex(templine,i)); // read off amount of laps
		if(fileversion >= 2)
		{
		    BAirrace[b(playerid)] = strval(strtokex(templine,i));
		    BCPsize[b(playerid)] = floatstr(strtokex(templine,i));
		}
		else
		{
			BAirrace[b(playerid)] = 0;
			BCPsize[b(playerid)] = 8.0;
		}
		fread(f,templine,sizeof(templine)); // read off best race times, not saved due to editing the track
		fread(f,templine,sizeof(templine)); // read off best lap times,          -||-
	}
	else //Otherwise add the lines as checkpoints, the file is made with v0.1 (or older) version of the script.
	{
		BCurrentCheckpoints[b(playerid)]++;
		BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]][0] = floatstr(strtokex(templine,i));
		BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]][1] = floatstr(strtokex(templine,i));
		BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]][2] = floatstr(strtokex(templine,i));
	}
	while(fread(f,templine,sizeof(templine),false))
	{
		BCurrentCheckpoints[b(playerid)]++;
		i=0;
		BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]][0] = floatstr(strtokex(templine,i));
		BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]][1] = floatstr(strtokex(templine,i));
		BRaceCheckpoints[b(playerid)][BCurrentCheckpoints[b(playerid)]][2] = floatstr(strtokex(templine,i));
	}
	fclose(f);
	BCurrentCheckpoints[b(playerid)]++; // # of next CP to be created
	format(ystring,sizeof(ystring),"Race \"%s\" has been loaded for editing. (%d checkpoints)",tmp,BCurrentCheckpoints[b(playerid)]);
	SendClientMessage(playerid, COLORYR_GREEN,ystring);
    return 1;
}
*/
CMD:saverace(playerid, params[])
{
	if(RaceBuilders[playerid] != 0)
	{
		new tmp[256], idx;
	    tmp = strtokex(params, idx);
	    if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLORYR_WHITE, "USAGE: /saverace [name]");
			return 1;
	    }
	    if(BCurrentCheckpoints[b(playerid)] < 2)
	    {
	        SendClientMessage(playerid, COLORYR_YELLOW, "You need atleast 2 checkpoints to save!");
	        return 1;
	    }
		if(!IsValidText(tmp) || strlen(tmp) >= 30) return SendClientMessage(playerid,COLORYR_RED,"Netinkamas pavadinimas!!!");
		SaveRace(playerid, tmp, /*phase=*/1);
		
	}
	else
	{
		SendClientMessage(playerid, COLORYR_RED, "You are not building a race!");
	}
	return 1;
}
stock SaveRace(playerid, racename[], phase)
{
	if(phase == 1) 
	{
		new query[256];
		format(query,256,"SELECT * FROM yrace WHERE raceid = '%s'", racename);
		mysql_function_query(SQL, query, true, "SQL_SaveRaceExists", "is", playerid, racename);
	}
	else
	{
		new Float:x,Float:y,Float:z, Bcreator[MAX_PLAYER_NAME], configas[256], bestline[128];
		GetPlayerName(playerid, Bcreator, MAX_PLAYER_NAME);
		new query[512];

		format(configas,sizeof(configas),"YRACE %d %s %d %d %d %f", RACEFILE_VERSION, Bcreator, Bracemode[b(playerid)], Blaps[b(playerid)], BAirrace[b(playerid)], BCPsize[b(playerid)]);
		format(bestline,sizeof(bestline),"A 0 A 0 A 0 A 0 A 0"); //Best complete race times
		format(query,sizeof(query), "INSERT INTO yrace (raceid,creator,config,best_race,best_lap) VALUES ('%s','%s','%s','%s','%s')",
			racename, Bcreator, configas, bestline, bestline);
		mysql_query(query);

		for(new i = 0; i < BCurrentCheckpoints[b(playerid)];i++)
		{
			x=BRaceCheckpoints[b(playerid)][i][0];
			y=BRaceCheckpoints[b(playerid)][i][1];
			z=BRaceCheckpoints[b(playerid)][i][2];
			format(query,sizeof(query),"INSERT INTO Checkpoints(type,id,cpid,x,y,z) VALUES ('yrace', '%s', %i, '%f', '%f', '%f')",
				racename, i, x, y, z);
			mysql_query(query);
		}
		format(ystring,sizeof(ystring),"Lenktynës \"%s\" iðsaugotos!",racename);
   		SendClientMessage(playerid, COLORYR_GREEN, ystring);
	}
}


stock IsValidText(text[])
{
	for(new i,l=strlen(text);i<l;i++)
	{
		if(text[i] == '_' || (text[i] >= 'a' && text[i] <= 'z') || (text[i] >='A' && text[i] <= 'Z') || (text[i] >= '0' && text[i] <= '9')) continue;
		else return 0;
	}
	return 1;
}
CMD:setlaps(playerid,params[])
{
	new tmp[256], idx;
    tmp = strtokex(params, idx);
    if(!strlen(tmp) || strval(tmp) <= 0)
	{
		SendClientMessage(playerid, COLORYR_WHITE, "USAGE: /setlaps [amount of laps (min: 1)]");
		return 1;
   	}
	if(RaceBuilders[playerid] != 0)
    {
		Blaps[b(playerid)] = strval(tmp);
		format(tmp,sizeof(tmp),"Amount of laps set to %d.", Blaps[b(playerid)]);
		SendClientMessage(playerid, COLORYR_GREEN, tmp);
        return 1;
    }
	if(RaceAdmin == 1 && IsNotAdmin(playerid)) return 1;
	if(RaceActive == 1 || RaceStart == 1) SendClientMessage(playerid, COLORYR_RED, "Race already in progress!");
	else if(LCurrentCheckpoint == 0) SendClientMessage(playerid, COLORYR_YELLOW, "No race loaded.");
	else
	{
	    Racelaps=strval(tmp);
		format(tmp,sizeof(tmp),"Amount of laps set to %d for current race.", Racelaps);
		SendClientMessage(playerid, COLORYR_GREEN, tmp);
	}
	return 1;
}

CMD:racemode(playerid,params[])
{
	new tmp[256], idx, tempmode;
    tmp = strtokex(params, idx);
    if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLORYR_WHITE, "USAGE: /racemode [0/1/2/3]");
		return 1;
   	}
	if(tmp[0] == 'd') tempmode=0;
	else if(tmp[0] == 'r') tempmode=1;
	else if(tmp[0] == 'y') tempmode=2;
	else if(tmp[0] == 'm') tempmode=3;
	else tempmode=strval(tmp);

	if (0 > tempmode || tempmode > 3)
   	{
   	    SendClientMessage(playerid, COLORYR_YELLOW, "Invalid racemode!");
		return 1;
   	}
	if(RaceBuilders[playerid] != 0)
    {
		if(tempmode == 2 && BCurrentCheckpoints[b(playerid)] < 3)
		{
		    SendClientMessage(playerid, COLORYR_YELLOW, "Can't set racemode 2 on races with only 2 CPs. Changing to mode 1 instead.");
		    Bracemode[b(playerid)] = 1;
		    return 1;
		}
		Bracemode[b(playerid)] = tempmode;
		format(tmp,sizeof(tmp),"Racemode set to %d.", Bracemode[b(playerid)]);
		SendClientMessage(playerid, COLORYR_GREEN, tmp);
        return 1;
    }
	if(RaceAdmin == 1 && IsNotAdmin(playerid)) return 1;
	if(RaceActive == 1 || RaceStart == 1) SendClientMessage(playerid, COLORYR_RED, "Race already in progress!");
	else if(LCurrentCheckpoint == 0) SendClientMessage(playerid, COLORYR_YELLOW, "No race loaded.");
	else
	{
		if(tempmode == 2 && LCurrentCheckpoint < 2)
		{
		    SendClientMessage(playerid, COLORYR_YELLOW, "Can't set racemode 2 on races with only 2 CPs. Changing to mode 1 instead.");
		    Racemode = 1;
		    return 1;
		}
	    Racemode=tempmode;
		format(tmp,sizeof(tmp),"Racemode set to %d.", Racemode);
		SendClientMessage(playerid, COLORYR_GREEN, tmp);
	}
	return 1;
}
CMD:allraces(playerid,params[])
	return cmd_races(playerid,params);

CMD:races(playerid, params[])
{
	if(RaceAdmin == 1 && IsNotAdmin(playerid)) return 1;
	new tmp[128], idx;
    tmp = strtokex(params, idx);
    if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLORYR_WHITE, "Naudojimas: /races [Vardas_Pavarde]");
		return 1;
    }

	if(!IsValidText(tmp) || strlen(tmp) >= 25) return SendClientMessage(playerid,COLORYR_RED,"Netinkamas vardas_pavarde!!!");
		
	new query[512];
	format(query,sizeof(query),"SELECT raceid, COUNT(cpid) FROM yrace JOIN Checkpoints ON Checkpoints.id = yrace.raceid WHERE creator = '%s' and type='yrace' GROUP BY raceid", tmp);
	mysql_function_query(SQL, query, true, "SQL_ShowRaces", "i", playerid);
	return 1;
}

CMD:loadrace(playerid, params[])
{
	if(RaceAdmin == 1 && IsNotAdmin(playerid)) return 1;
	Racemode = 0; Racelaps = 1;
	Ghost=0;
	new tmp[128], idx;
    tmp = strtokex(params, idx);
    if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLORYR_WHITE, "Naudojimas: /loadrace [pavadinimas]");
		return 1;
    }
    if(RaceActive == 1)
    {
		SendClientMessage(playerid, COLORYR_RED, "Lenktynës jau vyksta!");
		return 1;
    }
	if(!IsValidText(tmp) || strlen(tmp) >= 30) return SendClientMessage(playerid,COLORYR_RED,"Netinkamas pavadinimas!!!");
		
	LoadRace(playerid, tmp, /*phase=*/ 1);
	return 1;
}

CMD:startrace(playerid, params[])
{
	#pragma unused params
    if(RaceAdmin == 1 && IsNotAdmin(playerid)) return 1;
	if(LCurrentCheckpoint == 0) SendClientMessage(playerid,COLORYR_YELLOW,"No race loaded!");
	else if (RaceActive == 1) SendClientMessage(playerid,COLORYR_YELLOW,"Race is already active!");
	else startrace();
	return 1;
}


CMD:deleterace(playerid, params[])
{
	if((RaceAdmin == 1 || BuildAdmin == 1) && IsNotAdmin(playerid)) return 1;
	new filename[128], idx;
	filename = strtokex(params,idx);
	if(!(strlen(filename)))
	{
	    SendClientMessage(playerid, COLORYR_WHITE, "USAGE: /deleterace [race]");
	    return 1;
	}
	format(filename,sizeof(filename),"%s.yr",filename);
	if(!fexist(filename))
	{
		format(ystring,sizeof(ystring), "The race \"%s\" doesn't exist.",filename);
		SendClientMessage(playerid, COLORYR_RED, ystring);
		return 1;
	}
	fremove(filename);
	format(ystring,sizeof(ystring), "The race \"%s\" has been deleted.",filename);
	SendClientMessage(playerid, COLORYR_GREEN, ystring);
	return 1;
}

CMD:join(playerid,params[])
{
	#pragma unused params
	if(RaceBuilders[playerid] != 0)
	{
	    SendClientMessage(playerid, COLORYR_YELLOW, "You are currently building a race, can't join. Use /clearrace to exit build mode.");
	    return 1;
	}
	if(RaceParticipant[playerid]>0)
	{
	    SendClientMessage(playerid, COLORYR_YELLOW, "Tu jau prisijungei!");
	}
	else if(RaceActive==1 && RaceStart==0)
	{
		if(PrizeMode >= 2 && GetPlayerMoney(playerid) < JoinFee)
		{
			format(ystring,sizeof(ystring),"You don't have enough money to join the race! (Join fee: %d$)",JoinFee);
			SendClientMessage(playerid, COLORYR_YELLOW, ystring);
			return 1;
		}
		else if (PrizeMode >= 2)
		{
			//new tempval;
			//tempval=(-1)*JoinFee;
		    //GivePlayerMoney(playerid,tempval);
		    Pot+=JoinFee;
		}
		CurrentCheckpoint[playerid]=0;
		if(Racemode == 3)
		{
			SetRaceCheckpoint(playerid,LCurrentCheckpoint,LCurrentCheckpoint-1);
			CurrentCheckpoint[playerid]=LCurrentCheckpoint;
		}
		else SetRaceCheckpoint(playerid,0,1);
		RaceParticipant[playerid]=1;
		CurrentLap[playerid]=0;
		SendClientMessage(playerid, COLORYR_GREEN, "Prisijungei prie lenktyniu, vaziuok i starta! Atvaziaves butinai parasyk /ready !!!");
		Participants++;
	}
	else if(RaceActive==1 && RaceStart==1)
	{
	    SendClientMessage(playerid, COLORYR_YELLOW, "Lenktynes jau prasidejo, negali prisijungt.");
	}
	else
	{
	    SendClientMessage(playerid, COLORYR_YELLOW, "Nevyksta lenktynes.");
	}
	return 1;
}

CMD:leave(playerid,params[])
{
	#pragma unused params
	if(RaceParticipant[playerid] > 0)
	{
       	if(RaceParticipant[playerid]==3 && RaceStart == 1) //Countdown in progress, no leaving during it.
		{
			SendClientMessage(playerid,COLORYR_RED,"Unable to leave at this time: Countdown in progress.");
			return 1;
		}
		DisablePlayerRaceCheckpoint(playerid);
		DisableRemoteVehicleCollisions(playerid,0);
		RaceParticipant[playerid]=0;
		Participants--;
		SendClientMessage(playerid,COLORYR_YELLOW,"You have left the race.");
		if(PrizeMode >= 2 && RaceStart == 0)
		{
		    //GivePlayerMoney(playerid,JoinFee/2);
		    Pot-=JoinFee/2;
		}
        if(Participants == 0) endrace();
		else if(RaceStart == 0)ReadyRefresh();
	}
	else SendClientMessage(playerid, COLORYR_YELLOW, "You aren't in a race.");
    return 1;
}

CMD:endrace(playerid, params[])
{
	#pragma unused params
	if(RaceAdmin == 1 && IsNotAdmin(playerid)) return 1;
    if(RaceActive==0)
    {
        SendClientMessage(playerid, COLORYR_YELLOW, "There is no race active.");
		return 1;
    }
    endrace();
	return 1;
}

CMD:ready(playerid, params[])
{
	#pragma unused params
	new PState=GetPlayerState(playerid);
	if(RaceParticipant[playerid]==2 && PState != PLAYER_STATE_PASSENGER)
	{
		SendClientMessage(playerid,COLORYR_GREEN,"Tu pasiruoses! Rasyk /ready dar karta, kad atsauktum.");
		RaceParticipant[playerid]=3;
		ReadyRefresh();
		if(Ghost)
			DisableRemoteVehicleCollisions(playerid,1);
	}
	else if (RaceParticipant[playerid]==3 && RaceStart==0)
	{
	    SendClientMessage(playerid,COLORYR_YELLOW,"Tu nepasiruoses! Rasyk /ready kai busi pasiruoses.");
	    RaceParticipant[playerid]=2;
		DisableRemoteVehicleCollisions(playerid,0);
	}
	else if (PState == PLAYER_STATE_PASSENGER) SendClientMessage(playerid,COLORYR_YELLOW,"Turi pats vairuot!");
	else if(RaceParticipant[playerid] == 1) SendClientMessage(playerid,COLORYR_YELLOW,"Turi atvykt i starta, pries rasydamas /ready.");
	else SendClientMessage(playerid,COLORYR_YELLOW,"Tu nedalyvauji lenktynese, pirmiau parasyk /ready");
    return 1;
}
CMD:gogogo(playerid, params[])
{
	#pragma unused params
	if(IsNotAdmin(playerid)) return 1;
	SendClientMessageToAll(COLORYR_GREEN,"Visi pasiruose?");
	SendClientMessageToAll(COLORYR_GREEN,"Visi pasiruose?");
	SendClientMessageToAll(COLORYR_GREEN,"Visi pasiruose?");
	SendClientMessageToAll(COLORYR_RED,"Pradekim!");
	cd=5;
	if(Countdown != -1) KillTimer(Countdown),Countdown=-1;
	Countdown = SetTimer("countdown",1000,1);
    return 1;
}
/*
CMD:bestlap(playerid,params[])
{
	new tmp[64], idx;
    tmp = strtokex(params, idx);
	if(LoadTimes(playerid,1,tmp)) return 1;
	if(TopLapTimes[0] == 0)
	{
	    SendClientMessage(playerid,COLORYR_YELLOW,"No scores available.");
		return 1;
	}
	else if(ORacemode == 0)
	{
	    SendClientMessage(playerid,COLORYR_YELLOW,"This race doesn't have any laps.");
		return 1;
	}
	format(ystring,sizeof(ystring),"%s by %s - Best Laps:",CRaceName,CBuilder);
	SendClientMessage(playerid,COLORYR_GREEN,ystring);
	for(new i;i<5;i++)
	{
		if(TopLapTimes[i] == 0)
		{
		    format(ystring,sizeof(ystring),"%d. None yet",i+1);
			i=6;
		}
		else
		{
	 	   format(ystring,sizeof(ystring),"%d. %s - %s",i+1,BeHuman(TopLapTimes[i]),TopLappers[i]);
	    }
	    SendClientMessage(playerid,COLORYR_GREEN,ystring);
	}
    return 1;
}

CMD:bestrace(playerid,params[])
{
	new tmp[64], idx;
    tmp = strtokex(params, idx);
	if(LoadTimes(playerid,0,tmp)) return 1;
	if(TopRacerTimes[0] == 0)
	{
	    SendClientMessage(playerid,COLORYR_YELLOW,"No scores available.");
		return 1;
	}
	format(ystring,sizeof(ystring),"%s by %s - Best Race times:",CRaceName,CBuilder);
	SendClientMessage(playerid,COLORYR_GREEN,ystring);
	for(new i;i<5;i++)
	{
		if(TopRacerTimes[i] == 0)
		{
		    format(ystring,sizeof(ystring),"%d. None yet",i+1);
			i=6;
		}
		else
		{
	 	   format(ystring,sizeof(ystring),"%d. %s - %s",i+1,BeHuman(TopRacerTimes[i]),TopRacers[i]);
	    }
	    SendClientMessage(playerid,COLORYR_GREEN,ystring);
	}
    return 1;
}
*/
CMD:airrace(playerid,params[])
{
	#pragma unused params
	if(RaceBuilders[playerid] != 0)
	{
	    if(BAirrace[b(playerid)] == 0)
	    {
	        SendClientMessage(playerid,COLORYR_GREEN,"Air race enabled.");
			BAirrace[b(playerid)]=1;
	    }
	    else
	    {
	        SendClientMessage(playerid,COLORYR_GREEN,"Air race disabled.");
			BAirrace[b(playerid)]=0;
	    }
		return 1;
	}
	if(RaceAdmin == 1 && IsNotAdmin(playerid)) return 1;
	if(RaceActive == 1 || RaceStart == 1) SendClientMessage(playerid, COLORYR_YELLOW, "Race is already in progress!");
	else if(LCurrentCheckpoint == 0) SendClientMessage(playerid, COLORYR_YELLOW, "No race loaded!");
	else if(Airrace == 0)
    {
        SendClientMessage(playerid,COLORYR_GREEN,"Air race enabled.");
		Airrace = 1;
    }
    else if(Airrace == 1)
    {
        SendClientMessage(playerid,COLORYR_GREEN,"Air race disabled.");
		Airrace = 0;
    }
    else printf("Error in /airrace detected. RaceActive: %d, RaceStart: %d LCurrentCheckpoint: %d, Airrace: %d", RaceActive,RaceStart,LCurrentCheckpoint,Airrace);
	return 1;
}

CMD:cpsize(playerid,params[])
{
	new idx, tmp[32];
	tmp = strtokex(params,idx);
	if(!(strlen(tmp)) || floatstr(tmp) <= 0.0)
	{
	    SendClientMessage(playerid,COLORYR_WHITE,"USAGE: /cpsize [size]");
	    return 1;
	}
	if(RaceBuilders[playerid] != 0)
	{
	    BCPsize[b(playerid)] = floatstr(tmp);
	    format(ystring,sizeof(ystring),"Checkpoint size set to %f",floatstr(tmp));
		SendClientMessage(playerid,COLORYR_GREEN,ystring);
	    return 1;
	}
	if(RaceAdmin == 1 && IsNotAdmin(playerid)) return 1;
	if(RaceActive == 1) SendClientMessage(playerid, COLORYR_YELLOW, "Race has already been activated!");
	else if(LCurrentCheckpoint == 0) SendClientMessage(playerid, COLORYR_YELLOW, "No race loaded!");
	else
	{
	    CPsize = floatstr(tmp);
	    format(ystring,sizeof(ystring),"Checkpoint size set to %f",floatstr(tmp));
		SendClientMessage(playerid,COLORYR_GREEN,ystring);
	}
	return 1;
}

CMD:prizemode(playerid,params[])
{
	if(IsNotAdmin(playerid)) return 1;
	new idx, tmp;
	tmp=strval(strtokex(params,idx));
    if(tmp < 0 || tmp > 4) SendClientMessage(playerid,COLORYR_WHITE,"USAGE: /prizemode [0-4]");
	else if(RaceActive == 1) SendClientMessage(playerid,COLORYR_YELLOW,"Race is already active!");
    else
    {
        PrizeMode = tmp;
        format(ystring,sizeof(ystring),"Prizemode set to %d",PrizeMode);
		SendClientMessage(playerid,COLORYR_GREEN,ystring);
    }
	return 1;
}

CMD:setprize(playerid,params[])
{
	if(IsNotAdmin(playerid)) return 1;
	new idx, tmp;
    tmp = strval(strtokex(params, idx));
    if(0 >= tmp) SendClientMessage(playerid,COLORYR_WHITE,"USAGE: /setprize [amount]");
	else if(RaceActive == 1) SendClientMessage(playerid,COLORYR_YELLOW,"Race is already active!");
    else
    {
        Prize = tmp;
        format(ystring,sizeof(ystring),"Prize set to %d",Prize);
		SendClientMessage(playerid,COLORYR_GREEN,ystring);
    }
	return 1;
}

#if defined MENUSYSTEM
/*
CMD:raceadmin(playerid,params[])
{
	#pragma unused params
	if(IsNotAdmin(playerid)) return 1;
	if(!IsValidMenu(MAdmin)) CreateRaceMenus();
	TogglePlayerControllable(playerid,0);
	ShowMenuForPlayer(MAdmin,playerid);
	return 1;
}*/

CMD:buildmenu(playerid,params[])
{
	#pragma unused params
	if(BuildAdmin == 1 && IsNotAdmin(playerid)) return 1;
	if(RaceBuilders[playerid] == 0)
	{
		SendClientMessage(playerid,COLORYR_YELLOW,"You are not building a race!");
		return 1;
	}
	if(BAirrace[b(playerid)] == 0) SetMenuColumnHeader(MBuild,0,"Air race: off");
	else SetMenuColumnHeader(MBuild,0,"Air race: on");
	if(!IsValidMenu(MBuild)) CreateRaceMenus();
	TogglePlayerControllable(playerid,0);
	ShowMenuForPlayer(MBuild,playerid);
	return 1;
}
#endif
forward SetCPS(playerid,kiek,iskiek);
public SetCPS(playerid,kiek,iskiek) 
{
	new msg[128];
	format(msg,sizeof(msg),"%i/%i",kiek,iskiek);
	new i = playerid;
	PlayerTextDrawSetString(i,TDEditor_PTD[i][3],msg); // set checkpoints
	PlayerTextDrawShow(i,TDEditor_PTD[i][0]);
	PlayerTextDrawShow(i,TDEditor_PTD[i][3]);
}
forward HideCPS(playerid);
public HideCPS(playerid) 
{
	PlayerTextDrawHide(playerid,TDEditor_PTD[playerid][0]);
	PlayerTextDrawHide(playerid,TDEditor_PTD[playerid][3]);
}
CMD:testcps(playerid,params[])
{
	new msg[128];
	format(msg,sizeof(msg),"%i/%i",strval(params),56);
	new i = playerid;
	PlayerTextDrawSetString(i,TDEditor_PTD[i][3],msg); // set checkpoints
	PlayerTextDrawShow(i,TDEditor_PTD[i][0]);
	PlayerTextDrawShow(i,TDEditor_PTD[i][3]);
	return 1;
}
/*public OnPlayerUpdate(playerid) 
{
	new veh = GetPlayerVehicleID(playerid);
	new mod = GetVehicleModel(veh);
	if(mod == 406)
		RepairVehicle(veh);
	return 1;
}*/
stock YRace_OnPlayerConnect(playerid)
{
	TDEditor_PTD[playerid][0] = CreatePlayerTextDraw(playerid, 37.083320, 160.762939, "Checkpoint"); // static
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][0], 0.143333, 0.641482);
	PlayerTextDrawTextSize(playerid, TDEditor_PTD[playerid][0], -0.969999, 41.000000);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][0], 2);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, TDEditor_PTD[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, TDEditor_PTD[playerid][0], 100);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][0], 128);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][0], 0);

	TDEditor_PTD[playerid][1] = CreatePlayerTextDraw(playerid, 83.333305, 160.762954, "Position"); // static
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][1], 0.143333, 0.641482);
	PlayerTextDrawTextSize(playerid, TDEditor_PTD[playerid][1], -0.969999, 41.000000);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][1], 2);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][1], -1);
	PlayerTextDrawUseBox(playerid, TDEditor_PTD[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, TDEditor_PTD[playerid][1], 100);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][1], 128);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][1], 0);

	TDEditor_PTD[playerid][2] = CreatePlayerTextDraw(playerid, 83.416580, 169.796234, "0/0"); // dalyviai
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][2], 0.297500, 1.668149);
	PlayerTextDrawTextSize(playerid, TDEditor_PTD[playerid][2], -0.969999, 41.000000);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][2], 2);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][2], 1942756607);
	PlayerTextDrawUseBox(playerid, TDEditor_PTD[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, TDEditor_PTD[playerid][2], 100);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][2], 128);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][2], 0);

	TDEditor_PTD[playerid][3] = CreatePlayerTextDraw(playerid, 36.983299, 169.796188, "0/0"); // cps
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][3], 0.358333, 1.647406);
	PlayerTextDrawTextSize(playerid, TDEditor_PTD[playerid][3], -0.969999, 41.000000);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][3], 2);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][3], -1928350465);
	PlayerTextDrawUseBox(playerid, TDEditor_PTD[playerid][3], 1);
	PlayerTextDrawBoxColor(playerid, TDEditor_PTD[playerid][3], 100);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][3], 128);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][3], 0);

	TDEditor_PTD[playerid][4] = CreatePlayerTextDraw(playerid, 20.916650, 215.995712, "2");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][4], 0.192083, 1.035556);
	PlayerTextDrawTextSize(playerid, TDEditor_PTD[playerid][4], -0.969999, -14.000000);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][4], 2);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][4], 200);
	PlayerTextDrawUseBox(playerid, TDEditor_PTD[playerid][4], 1);
	PlayerTextDrawBoxColor(playerid, TDEditor_PTD[playerid][4], -128);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][4], 128);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][4], 2);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][4], 0);

	TDEditor_PTD[playerid][5] = CreatePlayerTextDraw(playerid, 20.916650, 233.896804, "3");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][5], 0.192083, 1.035556);
	PlayerTextDrawTextSize(playerid, TDEditor_PTD[playerid][5], -0.969999, -14.000000);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][5], 2);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][5], 200);
	PlayerTextDrawUseBox(playerid, TDEditor_PTD[playerid][5], 1);
	PlayerTextDrawBoxColor(playerid, TDEditor_PTD[playerid][5], -128);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][5], 128);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][5], 2);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][5], 0);

	TDEditor_PTD[playerid][6] = CreatePlayerTextDraw(playerid, 20.916650, 198.094619, "1");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][6], 0.262500, 1.040741);
	PlayerTextDrawTextSize(playerid, TDEditor_PTD[playerid][6], -0.969999, -14.000000);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][6], 2);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][6], 200);
	PlayerTextDrawUseBox(playerid, TDEditor_PTD[playerid][6], 1);
	PlayerTextDrawBoxColor(playerid, TDEditor_PTD[playerid][6], -128);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][6], 128);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][6], 2);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][6], 0);

	TDEditor_PTD[playerid][7] = CreatePlayerTextDraw(playerid, 27.916646, 200.170333, "pirmas_zaidejas");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][7], 0.143333, 0.641482);
	PlayerTextDrawTextSize(playerid, TDEditor_PTD[playerid][7], 104.000000, -0.969999);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][7], 1);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][7], -1);
	PlayerTextDrawUseBox(playerid, TDEditor_PTD[playerid][7], 1);
	PlayerTextDrawBoxColor(playerid, TDEditor_PTD[playerid][7], 100);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][7], 128);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][7], 2);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][7], 0);

	TDEditor_PTD[playerid][8] = CreatePlayerTextDraw(playerid, 27.916646, 217.971420, "antras_zaidejas");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][8], 0.143333, 0.641482);
	PlayerTextDrawTextSize(playerid, TDEditor_PTD[playerid][8], 104.000000, -0.969999);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][8], 1);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][8], -1);
	PlayerTextDrawUseBox(playerid, TDEditor_PTD[playerid][8], 1);
	PlayerTextDrawBoxColor(playerid, TDEditor_PTD[playerid][8], 100);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][8], 128);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][8], 2);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][8], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][8], 0);

	TDEditor_PTD[playerid][9] = CreatePlayerTextDraw(playerid, 27.916646, 235.672500, "trecias_zaidejas");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][9], 0.143333, 0.641482);
	PlayerTextDrawTextSize(playerid, TDEditor_PTD[playerid][9], 104.000000, -0.969999);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][9], 1);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][9], -1);
	PlayerTextDrawUseBox(playerid, TDEditor_PTD[playerid][9], 1);
	PlayerTextDrawBoxColor(playerid, TDEditor_PTD[playerid][9], 100);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][9], 128);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][9], 2);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][9], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][9], 0);
	
	for(new i;i<10;i++)
		PlayerTextDrawHide(playerid,TDEditor_PTD[playerid][i]);
	return 1;
}
stock YRace_OnPlayerDisconnect(playerid)
{
	for(new i;i<10;i++)
		PlayerTextDrawDestroy(playerid,TDEditor_PTD[playerid][i]);
	if(RaceParticipant[playerid]>=1)
	{
		if(Participants==1) //Last participant leaving, ending race.
		{
			endrace();
		}
		if(RaceParticipant[playerid] < 3 && RaceStart == 0 && !(RaceParticipant[playerid]==3 && RaceStart == 1)) 
		{ //Doing readycheck since someone left, but not if they disconnected during countdown.
		    ReadyRefresh();
		}
	    Participants--;
	    RaceParticipant[playerid]=0;
	    DisablePlayerRaceCheckpoint(playerid);
	}
	if(RaceBuilders[playerid] != 0)
	{
   	    DisablePlayerRaceCheckpoint(playerid);
	    for(new i;i<BCurrentCheckpoints[b(playerid)];i++)
	    {
	        BRaceCheckpoints[b(playerid)][i][0]=0.0;
   	        BRaceCheckpoints[b(playerid)][i][1]=0.0;
	        BRaceCheckpoints[b(playerid)][i][2]=0.0;
		}
		BuilderSlots[b(playerid)] = MAX_PLAYERS+1;
		RaceBuilders[playerid] = 0;
	} 
	return 1;
}

strtokex(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}

public LockRacers()
{
	for(new i;i<MAX_PLAYERS;i++)
	{
		if(RaceParticipant[i] != 0)
		{
			TogglePlayerControllable(i,0);
			if(IsPlayerInAnyVehicle(i)) PlayerVehicles[i]=GetPlayerVehicleID(i);
			else PlayerVehicles[i]=0;
		}
	}
}

public UnlockRacers()
{
	for(new i;i<MAX_PLAYERS;i++)
	{
		if(RaceParticipant[i]>0)
		{
			TogglePlayerControllable(i,1);
			if(PlayerVehicles[i] != 0)
			{
				PutPlayerInVehicle(i,PlayerVehicles[i],0);
				PlayerVehicles[i]=0;
			}
		}
	}
}

public countdown() {
	if(RaceStart == 0)  // Locking players, setting the reward and
	{
		RaceStart=1;
		LockRacers();
		new tmpprize, OPot;
		OPot=Pot;
		if(PrizeMode == 1 || PrizeMode == 4)
		{
			if(Racemode == 0 || Racemode == 3) tmpprize = floatround(RLenght);
			else if(Racemode == 1) tmpprize = floatround(LLenght * Racelaps);
			else if(Racemode == 2) tmpprize = floatround(RLenght * 2 * Racelaps);
		}
		tmpprize *= DynaMP;
		if(PrizeMode == 0 || PrizeMode == 3) Pot += Prize;
		else if(PrizeMode == 1 || PrizeMode == 4) Pot += tmpprize;
		if(Participants == 1) Pot=OPot; // Only 1 racer, force reward to entrance fees.
	}
	if(cd>0)
	{
		format(ystring, sizeof(ystring), "%d...",cd);
		for(new i=0;i<MAX_PLAYERS;i++)
		{
			if(RaceParticipant[i]>1)
			{
				RaceSound(i,1056);
			    GameTextForPlayer(i,ystring,1000,3);
		    }
	    }
	}
	else if(cd == 0)
	{
		format(ystring, sizeof(ystring), "~g~GO!");
	    KillTimer(Countdown),Countdown=-1;
		for(new i=0;i<MAX_PLAYERS;i++)
		{
			if(RaceParticipant[i]>1)
			{
				RaceSound(i,1057);
			    GameTextForPlayer(i,ystring,3000,3);
				RaceParticipant[i]=4;
				CurrentLap[i]=1;
				if(Racemode == 3) SetRaceCheckpoint(i,LCurrentCheckpoint,LCurrentCheckpoint-1);
				else SetRaceCheckpoint(i,0,1);
		    }
	    }
		UnlockRacers();
		RaceTick=GetTickCount();
	}
	cd--;
}

public SetNextCheckpoint(playerid)
{
	if(Racemode == 0) // Default Mode
	{
		CurrentCheckpoint[playerid]++;
		if(CurrentCheckpoint[playerid] == LCurrentCheckpoint)
		{
			SetRaceCheckpoint(playerid,CurrentCheckpoint[playerid],-1);
			RaceParticipant[playerid]=6;
		}
		else SetRaceCheckpoint(playerid,CurrentCheckpoint[playerid],CurrentCheckpoint[playerid]+1);
	}
	else if(Racemode == 1) // Ring Mode
	{
		CurrentCheckpoint[playerid]++;
		if(CurrentCheckpoint[playerid] == LCurrentCheckpoint+1 && CurrentLap[playerid] == Racelaps)
		{
			SetRaceCheckpoint(playerid,0,-1);
			RaceParticipant[playerid]=6;
		}
		else if (CurrentCheckpoint[playerid] == LCurrentCheckpoint+1 && CurrentLap[playerid] != Racelaps)
		{
			CurrentCheckpoint[playerid]=0;
			SetRaceCheckpoint(playerid,0,1);
			RaceParticipant[playerid]=5;
		}
		else if(CurrentCheckpoint[playerid] == 1 && RaceParticipant[playerid]==5)
		{
			ChangeLap(playerid);
			if(LCurrentCheckpoint==1)
			{
				SetRaceCheckpoint(playerid,CurrentCheckpoint[playerid],0);
			}
			else
			{
				SetRaceCheckpoint(playerid,CurrentCheckpoint[playerid],2);
            }
  		    RaceParticipant[playerid]=4;
		}
		else
		{
			if(LCurrentCheckpoint==1 || CurrentCheckpoint[playerid] == LCurrentCheckpoint) SetRaceCheckpoint(playerid,CurrentCheckpoint[playerid],0);
			else SetRaceCheckpoint(playerid,CurrentCheckpoint[playerid],CurrentCheckpoint[playerid]+1);
		}
	}
	else if(Racemode == 2) // Yoyo-mode
	{
		if(RaceParticipant[playerid]==4)
		{
			if(CurrentCheckpoint[playerid] == LCurrentCheckpoint) // @ Last CP, trigger last-1
			{
			    RaceParticipant[playerid]=5;
				CurrentCheckpoint[playerid]=LCurrentCheckpoint-1;
				SetRaceCheckpoint(playerid,CurrentCheckpoint[playerid],CurrentCheckpoint[playerid]-1);
			}
			else if(CurrentCheckpoint[playerid] == LCurrentCheckpoint-1) // Second last CP, set next accordingly
			{
				CurrentCheckpoint[playerid]++;
				SetRaceCheckpoint(playerid,CurrentCheckpoint[playerid],CurrentCheckpoint[playerid]-1);
			}
			else
			{
				CurrentCheckpoint[playerid]++;
				SetRaceCheckpoint(playerid,CurrentCheckpoint[playerid],CurrentCheckpoint[playerid]+1);
			}
		}
		else if(RaceParticipant[playerid]==5)
		{
			if(CurrentCheckpoint[playerid] == 1 && CurrentLap[playerid] == Racelaps) //Set the finish line
			{
				SetRaceCheckpoint(playerid,0,-1);
				RaceParticipant[playerid]=6;
			}
			else if(CurrentCheckpoint[playerid] == 0) //At finish line, change lap.
			{
				ChangeLap(playerid);
				if(LCurrentCheckpoint==1)
				{
					SetRaceCheckpoint(playerid,1,0);
				}
				else
				{
					SetRaceCheckpoint(playerid,1,2);
	            }
	  		    RaceParticipant[playerid]=4;
			}
			else if(CurrentCheckpoint[playerid] == 1)
			{
				CurrentCheckpoint[playerid]--;
				SetRaceCheckpoint(playerid,0,1);
			}
			else
			{
				CurrentCheckpoint[playerid]--;
				SetRaceCheckpoint(playerid,CurrentCheckpoint[playerid],CurrentCheckpoint[playerid]-1);
			}
		}
	}
	else if(Racemode == 3) // Mirror Mode
	{
		CurrentCheckpoint[playerid]--;
		if(CurrentCheckpoint[playerid] == 0)
		{
			SetRaceCheckpoint(playerid,CurrentCheckpoint[playerid],-1);
			RaceParticipant[playerid]=6;
		}
		else
		{
			 SetRaceCheckpoint(playerid,CurrentCheckpoint[playerid],CurrentCheckpoint[playerid]-1);
	    }
	}
}

public SetRaceCheckpoint(playerid,target,next)
{
	if(next == -1 && Airrace == 0) SetPlayerRaceCheckpoint(playerid,1,RaceCheckpoints[target][0],RaceCheckpoints[target][1],RaceCheckpoints[target][2],0.0,0.0,0.0,CPsize);
	else if(next == -1 && Airrace == 1) SetPlayerRaceCheckpoint(playerid,4,RaceCheckpoints[target][0],RaceCheckpoints[target][1],RaceCheckpoints[target][2],0.0,0.0,0.0,CPsize);
	else if(Airrace == 1) SetPlayerRaceCheckpoint(playerid,3,RaceCheckpoints[target][0],RaceCheckpoints[target][1],RaceCheckpoints[target][2],RaceCheckpoints[next][0],
							RaceCheckpoints[next][1],RaceCheckpoints[next][2],CPsize);
	else SetPlayerRaceCheckpoint(playerid,0,RaceCheckpoints[target][0],RaceCheckpoints[target][1],RaceCheckpoints[target][2],RaceCheckpoints[next][0],RaceCheckpoints[next][1],
							RaceCheckpoints[next][2],CPsize);
}
public SetBRaceCheckpoint(playerid,target,next)
{
	new ar = BAirrace[b(playerid)];
	if(next == -1 && ar == 0) SetPlayerRaceCheckpoint(playerid,1,BRaceCheckpoints[b(playerid)][target][0],BRaceCheckpoints[b(playerid)][target][1],
								BRaceCheckpoints[b(playerid)][target][2],0.0,0.0,0.0,BCPsize[b(playerid)]);
	else if(next == -1 && ar == 1) SetPlayerRaceCheckpoint(playerid,4,BRaceCheckpoints[b(playerid)][target][0],
				BRaceCheckpoints[b(playerid)][target][1],BRaceCheckpoints[b(playerid)][target][2],0.0,0.0,0.0,
				BCPsize[b(playerid)]);
	else if(ar == 1) SetPlayerRaceCheckpoint(playerid,3,BRaceCheckpoints[b(playerid)][target][0],BRaceCheckpoints[b(playerid)][target][1],BRaceCheckpoints[b(playerid)][target][2],
						BRaceCheckpoints[b(playerid)][next][0],BRaceCheckpoints[b(playerid)][next][1],BRaceCheckpoints[b(playerid)][next][2],BCPsize[b(playerid)]);
	else SetPlayerRaceCheckpoint(playerid,0,BRaceCheckpoints[b(playerid)][target][0],BRaceCheckpoints[b(playerid)][target][1],BRaceCheckpoints[b(playerid)][target][2],
			BRaceCheckpoints[b(playerid)][next][0],BRaceCheckpoints[b(playerid)][next][1],BRaceCheckpoints[b(playerid)][next][2],BCPsize[b(playerid)]);
}

public GetLapTick(playerid)
{
	new tick, lap;
	tick=GetTickCount();
	if(CurrentLap[playerid]==1)
	{
		lap=tick-RaceTick;
		LastLapTick[playerid]=tick;
	}
	else
	{
		lap=tick-LastLapTick[playerid];
		LastLapTick[playerid]=tick;
	}
	return lap;
}

public GetRaceTick(playerid)
{
	new tick, race;
	tick=GetTickCount();
	race=tick-RaceTick;
	return race;
}

stock YRace_OnPlayerEnterRaceCP(playerid)
{
	if(RaceParticipant[playerid]>=1) // See if the player is participating in a race, allows race builders to do their stuff in peace.
	{
	    //if(CallRemoteFunction("CheckVm","i",playerid)) return 1;
		if(RaceParticipant[playerid] == 6) // Player reaches the checkered flag.
	    {
			new name[MAX_PLAYER_NAME], LapTime, RaceTime;
			LapTime=GetLapTick(playerid);
			RaceTime=GetRaceTick(playerid);
			GetPlayerName(playerid, name, MAX_PLAYER_NAME);
			RaceParticipant[playerid]=0;
			RaceSound(playerid,1139);
			format(ystring,sizeof(ystring)," * %s pabaige lenktynes, vieta: %d. Laikas: %s",name,Ranking,BeHuman(RaceTime));
			if(Ranking == 1)
			{
				//CallRemoteFunction("AchievementMain","iif",playerid,7,1.0);
				//CallRemoteFunction("AchievementMain","iif",playerid,8,1.0);
				AchievementMain(playerid,7,1.0);
				AchievementMain(playerid,8,1.0);
			}
			//if (Ranking < 4) 
			SendClientMessageToAll(COLORYR_GREEN,ystring);
			//else SendClientMessage(playerid,COLORYR_GREEN,ystring);
			if(Racemode == ORacemode && ORacelaps == Racelaps)
			{
				new	LapString[10],RaceString[10], laprank, racerank;
				LapString=BeHuman(LapTime);
				RaceString=BeHuman(RaceTime);
				format(ystring,sizeof(ystring),"~w~Racetime: %s",RaceString);
				if(ORacemode!=0) format(ystring,sizeof(ystring),"%s~n~Laptime: %s",ystring,LapString);
				laprank=CheckBestLap(playerid,LapTime);
				if(laprank == 1)
				{
				    format(ystring,sizeof(ystring),"%s~n~~y~LAP RECORD!",ystring);
				}
				racerank=CheckBestRace(playerid,RaceTime);
				if(racerank == 1)
				{
				    format(ystring,sizeof(ystring),"%s~n~~y~TRACK RECORD!",ystring);
				}
			    GameTextForPlayer(playerid,ystring,13000,3);
		    }

			Ranking++;
			Participants--;
	        DisablePlayerRaceCheckpoint(playerid);
			for(new i;i<10;i++)
				PlayerTextDrawHide(playerid,TDEditor_PTD[playerid][i]);
	        if(Participants == 0)
	        {
	            endrace();
	        }
	    }
	    else if (RaceStart == 0 && RaceParticipant[playerid]==1) // Player arrives to the start CP for 1st time
	    {
			SendClientMessage(playerid,COLORYR_YELLOW,"DEMESIO! Privalai parasyt /ready");
			RaceParticipant[playerid]=2;
	    }
	    else if (RaceStart==1) // Otherwise switch to the next race CP.
	    {
			RaceSound(playerid,1138);
			SetNextCheckpoint(playerid);
	    }
	    return 1;
	}
	return 0;
}
forward IsInRace(playerid);
public IsInRace(playerid)
	return (RaceParticipant[playerid]);
public endrace()
{
    SaveScores(); //If the race had already started, and mode & laps are as originally, save the lapscores and racescores.
	for(new i=0;i<LCurrentCheckpoint;i++)
	{
	    RaceCheckpoints[i][0]=0.0;
	    RaceCheckpoints[i][1]=0.0;
	    RaceCheckpoints[i][2]=0.0;
	}
	LCurrentCheckpoint=0;
    for(new i=0;i<MAX_PLAYERS;i++)
    {
		for(new x;x<10;x++)
			PlayerTextDrawHide(i,TDEditor_PTD[i][x]);
		LastLapTick[i]=0;
        if(RaceParticipant[i]>0) 
		{
			DisablePlayerRaceCheckpoint(i);
			DisableRemoteVehicleCollisions(i,0);
		}
		if(RaceParticipant[i]==3) //Player was still /ready-locked, unlocking.
		{
				TogglePlayerControllable(i,1);
		        if(PlayerVehicles[i] != 0)
		        {
		            PutPlayerInVehicle(i,PlayerVehicles[i],0);
		            PlayerVehicles[i]=0;
		        }
				//KillTimer(Countdown);
				//Countdown=-1;
		}
		
        RaceParticipant[i]=0;
    }
	RaceActive=0;
	RaceStart=0;
	Participants=0;
	Pot = 0;
	cd=0;
    SendClientMessageToAll(COLORYR_YELLOW, " * Lenktynes buvo pabaigtos.");
}

public BActiveCP(playerid,sele)
{
	if(BCurrentCheckpoints[b(playerid)]-1 == sele) SetBRaceCheckpoint(playerid,sele,-1);
	else SetBRaceCheckpoint(playerid,sele,sele+1);
}

public RaceSound(playerid,sound)
{
	new Float:x,Float:y,Float:z;
	GetPlayerPos(playerid,x,y,z);
	PlayerPlaySound(playerid,sound,x,y,z);
}

public ReadyRefresh()
{
	if(RaceActive==1) //No countdown if no race is active (could occur with /leave)
	{
		new Waiting=0, Ready=0;
		for(new i=0;i<MAX_PLAYERS;i++)
		{
			if(RaceParticipant[i] == 1 || RaceParticipant[i] == 2) Waiting++;
			else if(RaceParticipant[i] == 3) Ready++;
		}
		if(Waiting==0)
		{
			SendClientMessageToAll(COLORYR_GREEN," * Visi pasiruose! Lenktynes pradedamos!");
			cd=5;
			if(Countdown != -1) KillTimer(Countdown),Countdown=-1;
			Countdown = SetTimer("countdown",1000,1);
		}
		else if(Ready >= Waiting && MajorityDelay > 0 && MajStart == 0)
		{
			MajStart=1;
			format(ystring,sizeof(ystring)," * Puse dalyviu jau pasiruose, lenktynes prasides po %d secondziu!", MajorityDelay);
			SendClientMessageToAll(COLORYR_GREEN,ystring);
			MajStartTimer = SetTimer("mscountdown",10000,1);
			mscd= MajorityDelay;
		}
	}
}

public mscountdown()
{
	if(RaceStart == 1 || MajStart == 0)
	{
		MajStart=0;
		KillTimer(MajStartTimer);
	}
	else
	{
		mscd-=10;
		if(mscd <= 0)
		{
			for(new i;i<MAX_PLAYERS;i++)
			{
				if(RaceParticipant[i] != 3 && RaceParticipant[i] != 0)
				{
					GameTextForPlayer(i,"~r~Nespejai!!",6000,3);
					DisablePlayerRaceCheckpoint(i);
					RaceParticipant[i]=0;
					Participants--;
				}
				else if (RaceParticipant[i]!=0) SendClientMessage(i,COLORYR_GREEN," * Skaiciavimas baigtas, lenktynes prasideda!");
			}
			KillTimer(MajStartTimer);
			cd=5;
			if(Countdown != -1) KillTimer(Countdown),Countdown=-1;
			Countdown = SetTimer("countdown",1000,1);
		}
		else
		{

			new hurry_string[64];
			format(ystring,sizeof(ystring),"~y~Lenktynes prasideda uz ~w~%d~y~ sekundziu!",mscd);
			format(hurry_string,sizeof(hurry_string),"%s~n~~r~Paskubek ir rasyk /READY",ystring);
			for(new i;i<MAX_PLAYERS;i++)
			{
				if(RaceParticipant[i] < 3 && RaceParticipant[i] >0 && mscd < 31) GameTextForPlayer(i,hurry_string,6000,3);
				else if(RaceParticipant[i] > 0) GameTextForPlayer(i,ystring,6000,3);
			}
		}
	}
}

public CheckBestLap(playerid,laptime)
{
	if(TopLapTimes[4]<laptime && TopLapTimes[4] != 0 || Racemode == 0)
	{
		return 0;  // If the laptime is more than the previous 5th on the top list, skip to end
	}              // Or the race is gamemode 0 where laps don't really apply
	for(new i;i<5;i++)
	{
	    if(TopLapTimes[i] == 0)
	    {
			new playername[MAX_PLAYER_NAME];
	        GetPlayerName(playerid,playername,MAX_PLAYER_NAME);
	        TopLappers[i]=playername;
	        TopLapTimes[i]=laptime;
			ScoreChange=1;
			return i+1;
	    }
		else if(TopLapTimes[i] > laptime)
		{
		    for(new j=4;j>=i;j--)
		    {
		        TopLapTimes[j+1]=TopLapTimes[j];
		        TopLappers[j+1]=TopLappers[j];
		    }
			new playername[MAX_PLAYER_NAME];
	        GetPlayerName(playerid,playername,MAX_PLAYER_NAME);
		    TopLapTimes[i]=laptime;
			TopLappers[i]=playername;
			ScoreChange=1;
			return i+1;
		}
	}
	return -1; //Shouldn't get here.
}

public CheckBestRace(playerid,racetime)
{
	if(TopRacerTimes[4]<racetime && TopRacerTimes[4] != 0) return 0;
	for(new i;i<5;i++)
	{
	    if(TopRacerTimes[i] == 0)
	    {
			new playername[MAX_PLAYER_NAME];
	        GetPlayerName(playerid,playername,MAX_PLAYER_NAME);
	        TopRacers[i]=playername;
	        TopRacerTimes[i]=racetime;
			ScoreChange=1;
			return i+1;
	    }
		else if(TopRacerTimes[i] > racetime)
		{
		    for(new j=4;j>=i;j--)
		    {
		        TopRacerTimes[j+1]=TopRacerTimes[j];
		        TopRacers[j+1]=TopRacers[j];
		    }
			new playername[MAX_PLAYER_NAME];
	        GetPlayerName(playerid,playername,MAX_PLAYER_NAME);
		    TopRacerTimes[i]=racetime;
			TopRacers[i]=playername;
			ScoreChange=1;
			return i+1;
		}
	}
	return -1; //Shouldn't get here.
}

public SaveScores()
{
	if(ScoreChange == 1)
	{
		new query[2048];

		new configas[512], best_race[512], best_lap[512];
		format(configas,sizeof(configas),"YRACE %d %s %d %d %d %f", RACEFILE_VERSION, CBuilder, ORacemode, ORacelaps, OAirrace, OCPsize);
		
		format(best_race,sizeof(best_race),"%s %d %s %d %s %d %s %d %s %d",
				TopRacers[0],TopRacerTimes[0],TopRacers[1], TopRacerTimes[1], TopRacers[2],TopRacerTimes[2],
	 			TopRacers[3],TopRacerTimes[3],TopRacers[4], TopRacerTimes[4]);
		format(best_lap,sizeof(best_lap),"%s %d %s %d %s %d %s %d %s %d",
				TopLappers[0],TopLapTimes[0],TopLappers[1], TopLapTimes[1], TopLappers[2],TopLapTimes[2],
	 			TopLappers[3],TopLapTimes[3],TopLappers[4], TopLapTimes[4]);

		format(query,sizeof(query),"UPDATE yrace SET config = '%s', best_race = '%s', best_lap = '%s' WHERE raceid = '%s'",
			configas, best_race, best_lap, CRaceName);
		mysql_query(query);	


	}
	ScoreChange=0;
}
public ChangeLap(playerid)
{
	new LapTime, TimeString[10], checklap;
	LapTime=GetLapTick(playerid);
	TimeString=BeHuman(LapTime);
	format(ystring,sizeof(ystring),"~w~Lap %d/%d - time: %s", CurrentLap[playerid], Racelaps, TimeString);
	if(Racemode == ORacemode && ORacelaps == Racelaps)
	{
		checklap=CheckBestLap(playerid,LapTime);
		if(checklap==1) format(ystring,sizeof(ystring),"%s~n~~y~LAP RECORD!",ystring);
	}
	CurrentLap[playerid]++;
	if(CurrentLap[playerid] == Racelaps) format(ystring,sizeof(ystring),"%s~n~~g~Final lap!",ystring);
	GameTextForPlayer(playerid,ystring,6000,3);
}
/*
stock BeHuman(ticks)
{
	new string[10]="-1";
	if(ticks < 0) return string;
	new HumanTime[10], minutes, seconds, secstring[2], msecstring[3];
	minutes=ticks/60000;
	ticks=ticks-(minutes*60000);
	seconds=ticks/1000;
	ticks=ticks-(seconds*1000);
	if(seconds <10) format(secstring,sizeof(secstring),"0%d",seconds);
	else format(secstring,sizeof(secstring),"%d",seconds);
	format(HumanTime,sizeof(HumanTime),"%d:%s",minutes,secstring);
	if(ticks < 10) format(msecstring,sizeof(msecstring),"00%d", ticks);
	else if(ticks < 100) format(msecstring,sizeof(msecstring),"0%d",ticks);
	else format(msecstring,sizeof(msecstring),"%d",ticks);
	format(HumanTime,sizeof(HumanTime),"%s.%s",HumanTime,msecstring);
	return HumanTime;
}
*/

stock BeHuman(ticks)
{
	new minutes,seconds;
	while(ticks>60000)
	{
		minutes++;
		ticks-=60000;
	}
	while(ticks>1000)
	{
		seconds++;
		ticks-=1000;
	}
	new string[10];
	format(string,sizeof(string),"%s%d:%d:%d",((minutes < 10)?("0"):("")),minutes,seconds,floatround(ticks/10));
	return string;
}
/*
public LoadTimes(playerid,timemode,tmp[])
{
	new temprace[67], idx;
	format(temprace,sizeof(temprace),"%s.yr",tmp);
    if(strlen(tmp))
    {
		if(!fexist(temprace))
		{
			format(ystring,sizeof(ystring),"Race \'%s\' doesn't exist!",tmp);
			SendClientMessage(playerid,COLORYR_YELLOW,ystring);
			return 1;
		}
		else
		{
			new File:f, templine[256], TBuilder[MAX_PLAYER_NAME], TempLapper[MAX_PLAYER_NAME], TempLap;
			idx=0;
			f = fopen(temprace, io_read);
			fread(f,templine,sizeof(templine)); // Read header-line
			if(templine[0] == 'Y') //Checking if the racefile is v0.2+
			{
				new fileversion;
			    strtokex(templine,idx); // read off YRACE
				fileversion = strval(strtokex(templine,idx)); // read off the file version
				if(fileversion > RACEFILE_VERSION) // Check if the race is made with a newer version of the racefile format
				{
				    format(ystring,sizeof(ystring),"Race \'%s\' is created with a newer version of YRACE, unable to load.",tmp);
				    SendClientMessage(playerid,COLORYR_RED,ystring);
				    return 1;
				}
				TBuilder=strtokex(templine,idx); // read off RACEBUILDER
				fread(f,templine,sizeof(templine)); // read off best race times
				if(timemode ==1) fread(f,templine,sizeof(templine)); // read off best lap times
				idx=0;
				if(timemode == 0) format(ystring,sizeof(ystring),"%s by %s - Best race times:",tmp,TBuilder);
				else if(timemode == 1) format(ystring,sizeof(ystring),"%s by %s - Best laps:",tmp,TBuilder);
				else return 1;
				SendClientMessage(playerid,COLORYR_GREEN,ystring);
				for(new i=0;i<5;i++)
				{
				    TempLapper=strtokex(templine,idx);
				    TempLap=strval(strtokex(templine,idx));
					if(TempLap == 0)
					{
					    format(ystring,sizeof(ystring),"%d. None yet",i+1);
						i=6;
					}
					else format(ystring,sizeof(ystring),"%d. %s - %s",i+1,BeHuman(TempLap),TempLapper);
					SendClientMessage(playerid,COLORYR_GREEN,ystring);
				}
				return 1;
			}
			else
			{
				format(ystring,sizeof(ystring),"Race \'%s\' doesn't contain any time data.",tmp);
				SendClientMessage(playerid,COLORYR_GREEN,ystring);
				return 1;
			}
		}
    }
	return 0;
}
*/
stock IsNotAdmin(playerid)
{
	//new isadmin = CallRemoteFunction("IsAdminCall","i",playerid);
    if (!playerDB[playerid][admin])
	{
	    SendClientMessage(playerid, COLORYR_RED, " * Si komanda tik administratoriams!");
	    return 1;
    }
    return 0;
}

stock GetBuilderSlot(playerid)
{
	for(new i;i < MAX_BUILDERS; i++)
	{
	    if(!(BuilderSlots[i] < MAX_PLAYERS+1))
	    {
	        BuilderSlots[i] = playerid;
	        RaceBuilders[playerid] = i+1;
			return i+1;
	    }
	}
	return 0;
}



public Float:Distance(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2)
{
	new Float:temp=floatsqroot((x1-x2) * (x1-x2) + (y1-y2) * (y1-y2) + (z1-z2) * (z1-z2));
	if(temp < 0) temp=temp*(-1);
	return temp;
}

stock clearrace(playerid)
{
	for(new i=0;i<BCurrentCheckpoints[b(playerid)];i++)
	{
		BRaceCheckpoints[b(playerid)][i][0]=0.0;
		BRaceCheckpoints[b(playerid)][i][1]=0.0;
		BRaceCheckpoints[b(playerid)][i][2]=0.0;
	}
	BCurrentCheckpoints[b(playerid)]=0;
	DisablePlayerRaceCheckpoint(playerid);
	SendClientMessage(playerid, COLORYR_GREEN, "Your race has been cleared! Use /buildrace to start a new one.");
	BuilderSlots[b(playerid)] = MAX_PLAYERS+1;
	RaceBuilders[playerid]=0;
}

stock startrace()
{
	format(ystring,128,"Lenktynes \'%s\' tuoj prasides, rasykite /join kad prisijungt!",CRaceName);
	SendClientMessageToAll(COLORYR_GREEN,ystring);
	if(Racemode == 0) format(ystring,sizeof(ystring),"iprastas");
	else if(Racemode == 1) format(ystring,sizeof(ystring),"ring");
	else if(Racemode == 2) format(ystring,sizeof(ystring),"yoyo");
	else if(Racemode == 3) format(ystring,sizeof(ystring),"mirror");
	format(ystring,sizeof(ystring),"Lenktyniu tipas: %s Ratu: %d",ystring,Racelaps);
	if(PrizeMode >= 2) format(ystring,sizeof(ystring),"%s Join fee: %d",ystring,JoinFee);
	if(Airrace == 1) format(ystring,sizeof(ystring),"%s Oro lenktynes",ystring);
	if(Racemode == 0 || Racemode == 3) format(ystring,sizeof(ystring),"%s Atstumas: %0.2fkm", ystring, RLenght/1000);
	else if(Racemode == 1) format(ystring,sizeof(ystring),"%s Rato atstumas: %.2fkm, Isviso: %.2fkm", ystring, LLenght/1000, LLenght * Racelaps / 1000);
	SendClientMessageToAll(COLORYR_GREEN,ystring);
	RaceStart=0;
	RaceActive=1;
	ScoreChange=0;
	Ranking=1;
}

ReturnModeName(mode)
{
	new modename[8];
	if(mode == 0) modename="Default";
	else if(mode == 1) modename="Ring";
	else if(mode == 2) modename="Yoyo";
	else if(mode == 3) modename="Mirror";
	return modename;
}

stock LoadRace(playerid, racename[], phase)
{
	if(phase == 1)
	{
		new query[256];
		format(query,256,"SELECT * FROM yrace LEFT JOIN Checkpoints ON Checkpoints.id = yrace.raceid WHERE raceid = '%s' AND type = 'yrace' ORDER BY cpid asc", racename);
		mysql_function_query(SQL, query, true, "SQL_LoadRace", "is", playerid, racename);
		return 1;
	}
	else
	{
		format(ystring,sizeof(ystring),"Lenktynës \'%s\' pakrautos. Autorius: %s",CRaceName, CBuilder);
		SendClientMessage(playerid,COLORYR_GREEN,ystring);
		if(LCurrentCheckpoint<2 && Racemode == 2)
		{
			Racemode = 1; // Racemode 2 doesn't work well with only 2CPs, and mode 1 is just the same when playing with 2 CPs.
		}                 // Setting racemode 2 is prevented from racebuilder so this shouldn't happen anyways.
	#if defined MENUSYSTEM
		if(!IsValidMenu(MRace)) CreateRaceMenus();
		if(Airrace == 0)
		{
			if(Ghost == 0)
				SetMenuColumnHeader(MRace,0,"Air: OFF, Ghost: OFF");
			else
				SetMenuColumnHeader(MRace,0,"Air: OFF, Ghost: ON");
		}
		else 
		{
			if(Ghost == 0)
				SetMenuColumnHeader(MRace,0,"Air: ON, Ghost: OFF");
			else
				SetMenuColumnHeader(MRace,0,"Air: ON, Ghost: ON");
		}
		TogglePlayerControllable(playerid,0);
		ShowMenuForPlayer(MRace,playerid);
	#endif
		RaceStart=0;
		return 1;
	}
}

public RaceRotation()
{
	return 1;
}

#if defined MENUSYSTEM
public OnPlayerExitedMenu(playerid)
{
	if(!IsValidMenu(GetPlayerMenu(playerid))) return 1;
	ShowMenuForPlayer(GetPlayerMenu(playerid), playerid);
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	new Menu:Current = GetPlayerMenu(playerid);
	if(Current == MAdmin)
	{
		if(row <=4 && RaceActive == 1)
		{
		    SendClientMessage(playerid,COLORYR_RED,"Race active, cannot change this setting!");
			ShowMenuForPlayer(MAdmin,playerid);
		    return 1;
		}
		if(row == 0) ShowMenuForPlayer(MPMode,playerid);
		else if (row == 1) ShowMenuForPlayer(MPrize,playerid);
		else if (row == 2) ShowMenuForPlayer(MDyna,playerid);
		else if (row == 3) ShowMenuForPlayer(MFee,playerid);
		else if (row == 4) ShowMenuForPlayer(MDelay,playerid);
		else if (row == 5)
		{
		    if(RaceActive == 1) endrace();
		    else SendClientMessage(playerid,COLORYR_YELLOW,"No race active!");
		    ShowMenuForPlayer(MAdmin,playerid);
		}
		else if (row == 9)
		{
			TogglePlayerControllable(playerid,1);
			HideMenuForPlayer(MAdmin,playerid);
		}
		else
		{
			if(row == 6 && RaceAdmin == 1) RaceAdmin=0;
			else if(row == 6 && RaceAdmin == 0) RaceAdmin=1;
			else if(row == 7 && BuildAdmin == 1) BuildAdmin=0;
			else if(row == 7 && BuildAdmin == 0) BuildAdmin=1;
			else if(row == 8 && RRotation >= 0) RRotation = -1;
			else RRotation = 0;
			if(RaceAdmin == 1) format(ystring,sizeof(ystring),"RA: ON");
			else format(ystring,sizeof(ystring),"RA: off");
			if(BuildAdmin == 1) format(ystring,sizeof(ystring),"%s BA: ON",ystring);
			else format(ystring,sizeof(ystring),"%s BA: off",ystring);
			if(RRotation >= 0) format(ystring,sizeof(ystring),"%s RR: ON",ystring);
			else format(ystring,sizeof(ystring),"%s RR: off",ystring);
			if(RRotation >= 0 && row == 8)  RotationTimer = SetTimer("RaceRotation",RRotationDelay,1);
			else if(RRotation -1 && row == 8) KillTimer(RotationTimer);
			RefreshMenuHeader(playerid,MAdmin,ystring);
		}
	}
	else if(Current == MPMode)
	{
		if(row == 5)
		{
			 ShowMenuForPlayer(MAdmin,playerid);
			 return 1;
		}
		PrizeMode = row;
		if     (PrizeMode == 0) ystring = "Fixed";
		else if(PrizeMode == 1) ystring = "Dynamic";
		else if(PrizeMode == 2) ystring = "Join Fee";
		else if(PrizeMode == 3) ystring = "Join Fee + Fixed";
		else if(PrizeMode == 4) ystring = "Join Fee + Dynamic";
		format(ystring,sizeof(ystring),"Mode: %s",ystring);
		RefreshMenuHeader(playerid,MPMode,ystring);
	}
	else if(Current == MPrize)
	{
	    if(row == 6)
	    {
	        ShowMenuForPlayer(MAdmin,playerid);
	        return 1;
	    }
	    if     (row == 0) Prize += 100;
	    else if(row == 1) Prize += 1000;
	    else if(row == 2) Prize += 10000;
	    else if(row == 3) Prize -= 100;
	    else if(row == 4) Prize -= 1000;
	    else if(row == 5) Prize -= 10000;
	    if(Prize < 0) Prize = 0;
		format(ystring,sizeof(ystring),"Amount: %d",Prize);
		RefreshMenuHeader(playerid,MPrize,ystring);
	}
	else if(Current == MDyna)
	{
		if(row == 4)
		{
		    ShowMenuForPlayer(MAdmin,playerid);
		    return 1;
		}
		if     (row == 0) DynaMP++;
		else if(row == 1) DynaMP+=5;
		else if(row == 2) DynaMP--;
		else if(row == 3) DynaMP-=5;
		else if(DynaMP < 1) DynaMP = 1;
		format(ystring,sizeof(ystring),"Multiplier: %dx",DynaMP);
		RefreshMenuHeader(playerid,MDyna,ystring);
	}
	else if(Current == MBuild)
	{

	    if (row == 0)
		{
			format(ystring,sizeof(ystring),"Laps: %d",Blaps[b(playerid)]);
			SetMenuColumnHeader(MLaps,0,ystring);
			ShowMenuForPlayer(MLaps,playerid);
		}
	    else if (row == 1)
		{
			format(ystring,sizeof(ystring),"Mode: %s",ReturnModeName(Bracemode[b(playerid)]));
			SetMenuColumnHeader(MRacemode,0,ystring);
			ShowMenuForPlayer(MRacemode,playerid);
		}
		else if (row == 2)
		{
		    format(ystring,sizeof(ystring),"Size: %0.2f",BCPsize[b(playerid)]);
		    SetMenuColumnHeader(MCPsize,0,ystring);
		    ShowMenuForPlayer(MCPsize,playerid);
		}
	    else if (row == 3)
	    {
	        if(BAirrace[b(playerid)] == 0)
			{
				BAirrace[b(playerid)] = 1;
				format(ystring,sizeof(ystring),"Air race: ON");
			}
   	        else if(BAirrace[b(playerid)] == 1)
			{
				BAirrace[b(playerid)] = 0;
				format(ystring,sizeof(ystring),"Air race: off");
			}
   	        RefreshMenuHeader(playerid,MBuild,ystring);
	    }
	    else if(row == 4)
	    {
	        clearrace(playerid);
	        HideMenuForPlayer(MBuild,playerid);
	        TogglePlayerControllable(playerid,1);
			return 1;
	    }
	    else if(row == 5)
	    {
	        HideMenuForPlayer(MBuild,playerid);
			TogglePlayerControllable(playerid,1);
	    }
	}
	else if(Current == MLaps)
	{

	    if(row == 6)
	    {
	        if(RaceBuilders[playerid] != 0) ShowMenuForPlayer(MBuild,playerid);
	        else ShowMenuForPlayer(MRace,playerid);
	        return 1;
		}
		new change=0;
	    if     (row == 0) change++;
		else if(row == 1) change+=5;
		else if(row == 2) change+=10;
		else if(row == 3) change--;
		else if(row == 4) change-=5;
		else if(row == 5) change-=10;
		if(RaceBuilders[playerid] != 0)
		{
		    Blaps[b(playerid)] += change;
			if(Blaps[b(playerid)] < 1) Blaps[b(playerid)] = 1;
			format(ystring,sizeof(ystring),"Laps: %d",Blaps[b(playerid)]);
			RefreshMenuHeader(playerid,MLaps,ystring);
		}
		else
		{
			Racelaps += change;
			if(Racelaps < 1) Racelaps = 1;
			format(ystring,sizeof(ystring),"Laps: %d",Racelaps);
			RefreshMenuHeader(playerid,MLaps,ystring);
		}

	}
	else if(Current == MRacemode)
	{
		if(row == 4)
		{
		    if(RaceBuilders[playerid] != 0) ShowMenuForPlayer(MBuild,playerid);
		    else ShowMenuForPlayer(MRace,playerid);
		    return 1;
		}
		if(RaceBuilders[playerid] != 0)
		{
		    Bracemode[b(playerid)]=row;
			if(Bracemode[b(playerid)] == 2 && BCurrentCheckpoints[b(playerid)] < 3)
			{
				SendClientMessage(playerid,COLORYR_YELLOW,"Cannot set racemode 2 with only 2 CPs!");
				Bracemode[b(playerid)] = 1;
			}
			format(ystring,sizeof(ystring),"Mode: %s",ReturnModeName(Bracemode[b(playerid)]));
			RefreshMenuHeader(playerid,MRacemode,ystring);
			return 1;
		}
		else
		{
		    Racemode = row;
			if(Racemode == 2 && LCurrentCheckpoint < 2)
			{
				SendClientMessage(playerid,COLORYR_YELLOW,"Cannot set racemode 2 with only 2 CPs!");
				Racemode = 1;
			}
			format(ystring,sizeof(ystring),"Mode: %s",ReturnModeName(Racemode));
			RefreshMenuHeader(playerid,MRacemode,ystring);
			return 1;
		}
	}
	else if(Current == MRace)
	{
	    if(row == 0)
		{
			format(ystring,sizeof(ystring),"Laps: %d",Racelaps);
			SetMenuColumnHeader(MLaps,0,ystring);
			ShowMenuForPlayer(MLaps,playerid);
		}
	    else if(row == 1)
		{
			format(ystring,sizeof(ystring),"Mode: %s",ReturnModeName(Racemode));
			SetMenuColumnHeader(MRacemode,0,ystring);
            ShowMenuForPlayer(MRacemode,playerid);
		}
		else if(row == 2)
		{
		    format(ystring,sizeof(ystring),"Size: %0.2f",CPsize);
		    SetMenuColumnHeader(MCPsize,0,ystring);
		    ShowMenuForPlayer(MCPsize,playerid);
		}
	    else if(row == 3)
	    {
			new strr[40];
			if(Ghost == 0)
			{
				format(strr,sizeof(strr),"Ghost: OFF, ");
			}
			else
			{
				format(strr,sizeof(strr),"Ghost: ON, ");
			}
	        if(Airrace == 0)
			{
				Airrace = 1;
				format(ystring,sizeof(ystring),"%sAir: ON",strr);
			}
			else if(Airrace == 1)
			{
				Airrace = 0;
				format(ystring,sizeof(ystring),"%sAir: OFF",strr);
			}
			RefreshMenuHeader(playerid,MRace,ystring);
	    }
		else if(row == 4)
	    {
			new strr[40];
			if(Airrace == 0)
			{
				format(strr,sizeof(strr),"Air: OFF, ");
			}
			else
			{
				format(strr,sizeof(strr),"Air: ON, ");
			}
	        if(Ghost == 0)
			{
				Ghost = 1;
				format(ystring,sizeof(ystring),"%sGhost: ON",strr);
			}
			else if(Ghost == 1)
			{
				Ghost = 0;
				format(ystring,sizeof(ystring),"%sGhost: OFF",strr);
			}
			RefreshMenuHeader(playerid,MRace,ystring);
	    }
		else if(row == 5)
		{
			if(RaceActive == 0)
			{
				startrace();
		        HideMenuForPlayer(MRace,playerid);
				TogglePlayerControllable(playerid,1);
			}
			else
			{
			    SendClientMessage(playerid,COLORYR_YELLOW,"Race is already active!");
			    
			}
		}
		else if(row == 6)
		{
	        HideMenuForPlayer(MRace,playerid);
			TogglePlayerControllable(playerid,1);
		}
	}
	else if(Current == MFee)
	{
	    if(row == 6)
	    {
	        ShowMenuForPlayer(MAdmin,playerid);
	        return 1;
	    }
	    if(row == 0) JoinFee +=100;
	    if(row == 1) JoinFee +=1000;
	    if(row == 2) JoinFee +=10000;
	    if(row == 3) JoinFee -=100;
	    if(row == 4) JoinFee -=1000;
	    if(row == 5) JoinFee -=10000;
	    if(JoinFee < 0) JoinFee = 0;
		format(ystring,sizeof(ystring),"Fee: %d$",JoinFee);
	    RefreshMenuHeader(playerid,MFee,ystring);
	}
	else if(Current == MCPsize)
	{
	    if(row == 6)
	    {
			if(RaceBuilders[playerid] != 0) ShowMenuForPlayer(MBuild,playerid);
			else ShowMenuForPlayer(MRace,playerid);
	        return 1;
	    }
		new Float:change;
	    if(row == 0) change +=0.1;
	    if(row == 1) change +=1.0;
	    if(row == 2) change +=10.0;
		if(row == 3) change -=0.1;
		if(row == 4) change -=1.0;
		if(row == 5) change -=10.0;
		if(RaceBuilders[playerid] != 0)
		{
		    BCPsize[b(playerid)] += change;
			if(BCPsize[b(playerid)] < 1.0) BCPsize[b(playerid)] = 1.0;
			if(BCPsize[b(playerid)] > 32.0) BCPsize[b(playerid)] = 32.0;
			format(ystring,sizeof(ystring),"Size %0.2f",BCPsize[b(playerid)]);
			RefreshMenuHeader(playerid,MCPsize,ystring);
		}
		else
		{
		    CPsize += change;
		    if(CPsize < 1.0) CPsize = 1.0;
		    if(CPsize > 32.0) CPsize = 32.0;
		    format(ystring,sizeof(ystring),"Size %0.2f",CPsize);
		    RefreshMenuHeader(playerid,MCPsize,ystring);
		}
	}
	else if(Current == MDelay)
	{
	    if(row == 4)
	    {
	        ShowMenuForPlayer(MAdmin,playerid);
	        return 1;
	    }
		if      (row == 0) MajorityDelay+=10;
		else if (row == 1) MajorityDelay+=60;
		else if (row == 2) MajorityDelay-=10;
		else if (row == 3) MajorityDelay-=60;
		if(MajorityDelay <= 0)
		{
			MajorityDelay=0;
			format(ystring,sizeof(ystring),"Delay: disabled");
		}
		else format(ystring,sizeof(ystring),"Delay: %ds",MajorityDelay);
		RefreshMenuHeader(playerid,MDelay,ystring);
	}
	return 1;
}

public RefreshMenuHeader(playerid,Menu:menu,text[])
{
	SetMenuColumnHeader(menu,0,text);
	ShowMenuForPlayer(menu,playerid);
}

public CreateRaceMenus()
{
	//Admin menu
	MAdmin = CreateMenu("Admin menu", 1, 25, 170, 220, 25);
	AddMenuItem(MAdmin,0,"Set prizemode...");
	AddMenuItem(MAdmin,0,"Set fixed prize...");
	AddMenuItem(MAdmin,0,"Set dynamic prize...");
	AddMenuItem(MAdmin,0,"Set entry fees...");
	AddMenuItem(MAdmin,0,"Majority delay...");
	AddMenuItem(MAdmin,0,"End current race");
	AddMenuItem(MAdmin,0,"Toggle Race Admin [RA]");
	AddMenuItem(MAdmin,0,"Toggle Build Admin [BA]");
	AddMenuItem(MAdmin,0,"Toggle Race Rotation [RR]");
	AddMenuItem(MAdmin,0,"Leave");
	if(RaceAdmin == 1) format(ystring,sizeof(ystring),"RA: ON");
	else format(ystring,sizeof(ystring),"RA: off");
	if(BuildAdmin == 1) format(ystring,sizeof(ystring),"%s BA: ON",ystring);
	else format(ystring,sizeof(ystring),"%s BA: off",ystring);
	if(RRotation >= 0) format(ystring,sizeof(ystring),"%s RR: ON",ystring);
	else format(ystring,sizeof(ystring),"%s RR: off",ystring);
	SetMenuColumnHeader(MAdmin,0,ystring);
	//Prizemode menu [Admin submenu]
	MPMode = CreateMenu("Set prizemode:", 1, 25, 170, 220, 25);
	AddMenuItem(MPMode,0,"Fixed");
	AddMenuItem(MPMode,0,"Dynamic");
	AddMenuItem(MPMode,0,"Entry Fee");
	AddMenuItem(MPMode,0,"Entry Fee + Fixed");
	AddMenuItem(MPMode,0,"Entry Fee + Dynamic");
	AddMenuItem(MPMode,0,"Back");
	SetMenuColumnHeader(MPMode,0,"Mode: Fixed");
	//Fixed prize menu
	MPrize = CreateMenu("Fixed prize:", 1, 25, 170, 220, 25);
	AddMenuItem(MPrize,0,"+100$");
	AddMenuItem(MPrize,0,"+1000$");
	AddMenuItem(MPrize,0,"+10000$");
	AddMenuItem(MPrize,0,"-100$");
	AddMenuItem(MPrize,0,"-1000$");
	AddMenuItem(MPrize,0,"-10000$");
	AddMenuItem(MPrize,0,"Back");
	format(ystring,sizeof(ystring),"Amount: %d",Prize);
	SetMenuColumnHeader(MPrize,0,ystring);
	//Dynamic prize menu
	MDyna = CreateMenu("Dynamic Prize:", 1, 25, 170, 220, 25);
	AddMenuItem(MDyna,0,"+1x");
	AddMenuItem(MDyna,0,"+5x");
	AddMenuItem(MDyna,0,"-1x");
	AddMenuItem(MDyna,0,"-5x");
	AddMenuItem(MDyna,0,"Leave");
	format(ystring,sizeof(ystring),"Multiplier: %dx",DynaMP);
	SetMenuColumnHeader(MDyna,0,ystring);
	//Build Menu
	MBuild = CreateMenu("Build Menu", 1, 25, 170, 220, 25);
	AddMenuItem(MBuild,0,"Set laps...");
	AddMenuItem(MBuild,0,"Set racemode...");
	AddMenuItem(MBuild,0,"Checkpoint size...");
	AddMenuItem(MBuild,0,"Toggle air race");
	AddMenuItem(MBuild,0,"Clear the race and exit");
	AddMenuItem(MBuild,0,"Leave");
	SetMenuColumnHeader(MBuild,0,"Air race: off");
	//Laps menu
	MLaps = CreateMenu("Set laps", 1, 25, 170, 220, 25);
	AddMenuItem(MLaps,0,"+1");
	AddMenuItem(MLaps,0,"+5");
	AddMenuItem(MLaps,0,"+10");
	AddMenuItem(MLaps,0,"-1");
	AddMenuItem(MLaps,0,"-5");
	AddMenuItem(MLaps,0,"-10");
	AddMenuItem(MLaps,0,"Back");
	//Racemode menu
	MRacemode = CreateMenu("Racemode", 1, 25, 170, 220, 25);
	AddMenuItem(MRacemode,0,"Default");
	AddMenuItem(MRacemode,0,"Ring");
	AddMenuItem(MRacemode,0,"Yoyo");
	AddMenuItem(MRacemode,0,"Mirror");
	AddMenuItem(MRacemode,0,"Back");
	//Race menu
	MRace = CreateMenu("Race Menu", 1, 25, 170, 220, 25);
	AddMenuItem(MRace,0,"Set laps...");
	AddMenuItem(MRace,0,"Set racemode...");
	AddMenuItem(MRace,0,"Set checkpoint size...");
	AddMenuItem(MRace,0,"Toggle air race");
	AddMenuItem(MRace,0,"Toggle ghost mode");
	AddMenuItem(MRace,0,"Start race");
	AddMenuItem(MRace,0,"Abort new race");
	//Entry fee menu
	MFee = CreateMenu("Entry fees", 1, 25, 170, 220, 25);
	AddMenuItem(MFee,0,"+100");
	AddMenuItem(MFee,0,"+1000");
	AddMenuItem(MFee,0,"+10000");
	AddMenuItem(MFee,0,"-100");
	AddMenuItem(MFee,0,"-1000");
	AddMenuItem(MFee,0,"-10000");
	AddMenuItem(MFee,0,"Back");
	format(ystring,sizeof(ystring),"Fee: %d$",JoinFee);
	SetMenuColumnHeader(MFee,0,ystring);
	//CP size menu
	MCPsize = CreateMenu("CP size", 1, 25, 170, 220, 25);
	AddMenuItem(MCPsize,0,"+0.1");
	AddMenuItem(MCPsize,0,"+1");
	AddMenuItem(MCPsize,0,"+10");
	AddMenuItem(MCPsize,0,"-0.1");
	AddMenuItem(MCPsize,0,"-1");
	AddMenuItem(MCPsize,0,"-10");
	AddMenuItem(MCPsize,0,"Back");
	//Majority Delay menu
	MDelay = CreateMenu("Majority Delay", 1, 25, 170, 220, 25);
	AddMenuItem(MDelay,0,"+10s");
	AddMenuItem(MDelay,0,"+60s");
	AddMenuItem(MDelay,0,"-10s");
	AddMenuItem(MDelay,0,"-60s");
	AddMenuItem(MDelay,0,"Back");
	if(MajorityDelay == 0) format(ystring,sizeof(ystring),"Delay: disabled");
	else format(ystring,sizeof(ystring),"Delay: %ds",MajorityDelay);
	SetMenuColumnHeader(MDelay,0,ystring);
}

#endif
