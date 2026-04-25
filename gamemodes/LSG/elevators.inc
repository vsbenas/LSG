

// CONSTANT ACCROSS ALL ELEVATORS

#define ELEVATOR_SPEED      (5.0)   // Movement speed of the elevator.
#define DOORS_SPEED         (4.0)   // Movement speed of the doors.
#define ELEVATOR_WAIT_TIME  (5000)  // Time in ms that the elevator will wait in each floor before continuing with the queue.
									// Be sure to give enough time for doors to open.


#define ELEVATOR_STATE_IDLE     (0)
#define ELEVATOR_STATE_WAITING  (1)
#define ELEVATOR_STATE_MOVING   (2)
#define ELEVATOR_STATE_CLOSING	(3)


#define INVALID_FLOOR           (-1)


#define MAX_ELEVATORS (3)
	
/* ------------------
// Constants:
-------------------*/
new const FloorNames[21][] =
{
	"Parkingas",
	"Pirmas",
	"Antras",
	"Trecias",
	"Ketvirtas",
	"Penktas",
	"Sestas",
	"Septintas",
	"Astuntas",
	"Devintas",
	"Desimtas",
	"Vienuoliktas",
	"Dvyliktas",
	"Tryliktas",
	"Keturioliktas",
	"Penkioliktas",
	"Sesioliktas",
	"Septynioliktas",
	"Astuonioliktas",
	"Devynioliktas",
	"Pastogë"
};

// END CONSTANTS

	
// Private:

new const NumFloors[MAX_ELEVATORS] =
{
	21, // KOBRA
	14, // beachside
	11 // ligonine
};
new const Float:FloorZOffsets[MAX_ELEVATORS][21] =
{
	{
	    0.0,		// 0.0,
	    8.5479,		// 8.5479,
	    13.99945,   // 8.5479 + (5.45155 * 1.0),
	    19.45100,   // 8.5479 + (5.45155 * 2.0),
	    24.90255,   // 8.5479 + (5.45155 * 3.0),
	    30.35410,   // 8.5479 + (5.45155 * 4.0),
	    35.80565,   // 8.5479 + (5.45155 * 5.0),
	    41.25720,   // 8.5479 + (5.45155 * 6.0),
	    46.70875,   // 8.5479 + (5.45155 * 7.0),
	    52.16030,   // 8.5479 + (5.45155 * 8.0),
	    57.61185,   // 8.5479 + (5.45155 * 9.0),
	    63.06340,   // 8.5479 + (5.45155 * 10.0),
	    68.51495,   // 8.5479 + (5.45155 * 11.0),
	    73.96650,   // 8.5479 + (5.45155 * 12.0),
	    79.41805,   // 8.5479 + (5.45155 * 13.0),
	    84.86960,   // 8.5479 + (5.45155 * 14.0),
	    90.32115,   // 8.5479 + (5.45155 * 15.0),
	    95.77270,   // 8.5479 + (5.45155 * 16.0),
	    101.22425,  // 8.5479 + (5.45155 * 17.0),
	    106.67580,	// 8.5479 + (5.45155 * 18.0),
	    112.12735	// 8.5479 + (5.45155 * 19.0)
	},
	{
	    0.0, 		// Car Park
	    15.069729,  // Ground Floor
	    29.130733,	// First Floor
	    33.630733,  // Second Floor = 29.130733 + 4.5
	    38.130733,  // Third Floor = 33.630733 + 4.5
	    42.630733,  // Fourth Floor = 38.130733 + 4.5
	    47.130733,  // Fifth Floor = 42.630733 + 4.5
	    51.630733,  // Sixth Floor = 47.130733 + 4.5
	    56.130733,  // Seventh Floor = 51.630733 + 4.5
	    60.630733,  // Eighth Floor = 56.130733 + 4.5
	    65.130733,  // Ninth Floor = 60.630733 + 4.5
	    69.630733,  // Tenth Floor = 65.130733 + 4.5
	    74.130733,  // Eleventh Floor = 69.630733 + 4.5
	    78.630733,  // Twelfth Floor = 74.130733 + 4.5
	},
	{
	    0.0, 		// Car Park
	    13.604544,	// Ground Floor
	    18.808519,	// First Floor = 13.604544 + 5.203975
	    24.012494,  // Second Floor = 18.808519 + 5.203975
	    29.216469,  // Third Floor = 24.012494 + 5.203975
	    34.420444,  // Fourth Floor = 29.216469 + 5.203975
	    39.624419,  // Fifth Floor = 34.420444 + 5.203975
	    44.828394,  // Sixth Floor = 39.624419 + 5.203975
	    50.032369,  // Seventh Floor = 44.828394 + 5.203975
	    55.236344,  // Eighth Floor = 50.032369 + 5.203975
	    60.440319   // Ninth Floor = 55.236344 + 5.203975
	}

};




new const Float:ElevatorObjects[MAX_ELEVATORS][6] = 
{
	{1786.678100, -1303.459472, 14.511476 ,0.000000, 0.000000, 270.000000}, // ELEVATOR_X, ELEVATOR_Y, GROUND_Z_COORD
	{287.942413,-1609.341064,18.755348,0.000000, 0.000000, 80.000000}, // beachside
	{1181.622924,-1180.554687,20.879316,0.000000, 0.000000, 0.000000}// ligonine
};

new const Float:ElevatorFloorDoors[MAX_ELEVATORS][6] = 
{
	{1786.678100, -1303.171142, 0.0 ,0.000000, 0.000000, 270.000000}, // ELEVATOR_X, custom, custom...
	{287.942413, -1609.586064, 0.0, 0.000000, 0.000000, 80.00000},
	{1181.377924,-1180.554687,20.879316,0.000000, 0.000000, 0.000000}// ligonine
};

new const Float:FloorLabels[MAX_ELEVATORS][2] =
{
	{1783.9799, -1300.7660},
	{289.942413,-1612.341064},
	{1179.122924,-1183.054687}
};


new const Float:ElevatorOffsets[MAX_ELEVATORS] =
{
	0.059523, // ELEVATOR_OFFSET
	0.0, // beachside
	0.059523
};

new const Float:ElevatorCoordsInside[MAX_ELEVATORS][4] = {
	{1784.1555,1786.2131,-1303.2417,-1301.4}, // minx,maxx,miny,maxy
	{286.142425,289.742401,-1611.141113,-1607.541015},
	{1179.822924,1183.422924,-1182.354687,-1178.754687}
};
new const Float:ElevatorCoordsOutside[MAX_ELEVATORS][4] = {
	{1781.9902,1785.6147,-1301.4,-1299.1447}, // minx,maxx,miny,maxy
	{289.152404,291.742401,-1613.386108,-1611.396118},
	{1177.822924,1179.812924,-1184.354687,-1182.364687}
};




new const Float:LeftDoorOpen[MAX_ELEVATORS][2] =
{
	{1788.227685,0.0}, // x,y
	{286.342407,-1609.076049},
	{0.0,-1178.935917}
};

new const Float:RightDoorOpen[MAX_ELEVATORS][2] =
{
	{1785.027685,0.0},
	{289.542419,-1609.640991},
	{0.0,-1182.135917}
};


new const Float:ElevatorLabels[MAX_ELEVATORS][3] = 
{
	{1784.9822, -1302.0426, 13.6491},
	{289.542413 ,-1611.191064,18.355348}, // X_ELEVATOR_POS + 1.6, Y_ELEVATOR_POS - 1.85, GROUND_Z_COORD - 0.4
	{1179.922924,-1182.304687,20.479316} //X_ELEVATOR_POS - 1.7, Y_ELEVATOR_POS - 1.75, GROUND_Z_COORD - 0.4
};




/* ------------------
// Variables:
-------------------*/
new Obj_Elevator[MAX_ELEVATORS], 
	Obj_ElevatorDoors[MAX_ELEVATORS][2],
	Obj_FloorDoors[MAX_ELEVATORS][21][2];

new Text3D:Label_Elevator[MAX_ELEVATORS], 
	Text3D:Label_Floors[MAX_ELEVATORS][21];



new ElevatorState[MAX_ELEVATORS],
	ElevatorFloor[MAX_ELEVATORS];  // If Idle or Waiting, this is the current floor. If Moving, the floor it's moving to.



new ElevatorQueue[MAX_ELEVATORS][21],  	// Floors in queue.
	FloorRequestedBy[MAX_ELEVATORS][21];   // FloorRequestedBy[floor_id] = playerid; - Points out who requested which floor.

new ElevatorBoostTimer[MAX_ELEVATORS];     // Timer that makes the elevator move faster after players start surfing the object.

/* ------------------
*  Function forwards:
-------------------*/
// Public:
/*forward CallElevator(playerid, floorid);    // You can use INVALID_PLAYER_ID too.
forward ShowElevatorDialog(playerid,elid);

// Private:
forward Elevator_Initialize();
forward Elevator_Destroy();

forward Elevator_OpenDoors();
forward Elevator_CloseDoors();
forward Floor_OpenDoors(floorid);
forward Floor_CloseDoors(floorid);

forward ReadNextFloorInQueue();
forward RemoveFirstQueueFloor();
forward AddFloorToQueue(floorid);
forward IsFloorInQueue(floorid);
forward ResetElevatorQueue();

forward DidPlayerRequestElevator(playerid);

forward Elevator_MoveToFloor(floorid);
*/
forward Elevator_Boost(floorid,elid);        	// Increases the elevator speed until it reaches 'floorid'.
forward Elevator_TurnToIdle(elid);

forward Float:GetElevatorZCoordForFloor(floorid,elid);
forward Float:GetDoorsZCoordForFloor(floorid,elid);

forward OnElevatorObjectMoved(objectid);

public OnElevatorObjectMoved(objectid)
{
	for(new elid;elid < MAX_ELEVATORS; elid++)
	{
		new Float:x, Float:y, Float:z;
		new floors = NumFloors[elid];
		for(new i; i < floors; i ++)
		{
			if(objectid == Obj_FloorDoors[elid][i][0])
			{
			    GetDynamicObjectPos(Obj_FloorDoors[elid][i][0], x, y, z);

			    if(ElevatorState[elid] == ELEVATOR_STATE_CLOSING)   // Some floor doors have shut, move the elevator to next floor in queue:
			    {
					Elevator_MoveToFloor(ElevatorQueue[elid][0],elid);
					RemoveFirstQueueFloor(elid);
				}
				return 1;
			}
		}

		if(objectid == Obj_Elevator[elid])   // The elevator reached the specified floor.
		{
		    KillTimer(ElevatorBoostTimer[elid]);  // Kills the timer, in case the elevator reached the floor before boost.
			ElevatorBoostTimer[elid]=-1;
		    FloorRequestedBy[elid][ElevatorFloor[elid]] = INVALID_PLAYER_ID;

		    Elevator_OpenDoors(elid);
		    Floor_OpenDoors(ElevatorFloor[elid],elid);

		    GetDynamicObjectPos(Obj_Elevator[elid], x, y, z);
		    Label_Elevator[elid]	= CreateDynamic3DTextLabel("Spausk [ENTER], kad pasinaudotum liftu", 0xFFFFDD,  ElevatorLabels[elid][0],ElevatorLabels[elid][1], z - 0.9, 4.0, _,_, 1);

		    ElevatorState[elid]	= ELEVATOR_STATE_WAITING;
		    SetTimerEx("Elevator_TurnToIdle", ELEVATOR_WAIT_TIME, 0, "i",elid);
		    return 1;
		}
	}
	return 0;
}

stock KvieciaLifta(playerid)
{
	new Float:pos[3];
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    for(new elid;elid<MAX_ELEVATORS;elid++)
    {
    	if((ElevatorCoordsInside[elid][0] < pos[0] < ElevatorCoordsInside[elid][1]) && (ElevatorCoordsInside[elid][2] < pos[1] < ElevatorCoordsInside[elid][3]))
    	{
    		ShowElevatorDialog(playerid,elid);
    		return 1;
    	}
		if((ElevatorCoordsOutside[elid][0] < pos[0] < ElevatorCoordsOutside[elid][1]) && (ElevatorCoordsOutside[elid][2] < pos[1] < ElevatorCoordsOutside[elid][3]))
    	{
    		// He is most likely using it, check floor:
			new i=NumFloors[elid]-1;
			while(pos[2] < GetDoorsZCoordForFloor(i,elid) + 3.5 && i > 0)
				i --;

			if(i == 0 && pos[2] < GetDoorsZCoordForFloor(0,elid) + 2.0)
				i = -1;

			if(i <= 19)
			{
				CallElevator(playerid, i + 1,elid);
				GameTextForPlayer(playerid, "~r~Liftas iskviestas", 3500, 4);
			}
			return 1;
    	}

    }
    return 0;
}


stock Elevator_MoveToFloor(floorid,elid)
{
	// Moves the elevator to specified floor (doors are meant to be already closed).

	ElevatorState[elid] = ELEVATOR_STATE_MOVING;
	ElevatorFloor[elid] = floorid;

	// Move the elevator slowly, to give time to clients to sync the object surfing. Then, boost it up:
	MoveDynamicObject(Obj_Elevator[elid], ElevatorObjects[elid][0], ElevatorObjects[elid][1], GetElevatorZCoordForFloor(floorid,elid), 0.5);
    MoveDynamicObject(Obj_ElevatorDoors[elid][0], ElevatorObjects[elid][0], ElevatorObjects[elid][1], GetDoorsZCoordForFloor(floorid,elid), 0.5);
    MoveDynamicObject(Obj_ElevatorDoors[elid][1], ElevatorObjects[elid][0], ElevatorObjects[elid][1], GetDoorsZCoordForFloor(floorid,elid), 0.5);
    DestroyDynamic3DTextLabel(Label_Elevator[elid]);

	ElevatorBoostTimer[elid] = SetTimerEx("Elevator_Boost", 2000, 0, "ii", floorid,elid);

	return 1;
}

public Elevator_Boost(floorid,elid)
{
	// Increases the elevator's speed until it reaches 'floorid'

	MoveDynamicObject(Obj_Elevator[elid], ElevatorObjects[elid][0], ElevatorObjects[elid][1], GetElevatorZCoordForFloor(floorid,elid), ELEVATOR_SPEED);
    MoveDynamicObject(Obj_ElevatorDoors[elid][0], ElevatorObjects[elid][0], ElevatorObjects[elid][1], GetDoorsZCoordForFloor(floorid,elid), ELEVATOR_SPEED);
    MoveDynamicObject(Obj_ElevatorDoors[elid][1], ElevatorObjects[elid][0], ElevatorObjects[elid][1], GetDoorsZCoordForFloor(floorid,elid), ELEVATOR_SPEED);

	return 1;
}

public Elevator_TurnToIdle(elid)
{
	ElevatorState[elid] = ELEVATOR_STATE_IDLE;
	ReadNextFloorInQueue(elid);

	return 1;
}

stock RemoveFirstQueueFloor(elid)
{
	// Removes the data in ElevatorQueue[0], and reorders the queue accordingly.
	new floors = NumFloors[elid];
	for(new i; i < floors - 1; i ++)
	    ElevatorQueue[elid][i] = ElevatorQueue[elid][i + 1];

	ElevatorQueue[elid][floors - 1] = INVALID_FLOOR;

	return 1;
}

stock AddFloorToQueue(floorid,elid)
{
 	// Adds 'floorid' at the end of the queue.
	new floors = NumFloors[elid];
	// Scan for the first empty space:
	new slot = -1;
	for(new i; i < floors; i ++)
	{
	    if(ElevatorQueue[elid][i] == INVALID_FLOOR)
	    {
	        slot = i;
	        break;
	    }
	}

	if(slot != -1)
	{
	    ElevatorQueue[elid][slot] = floorid;

     	// If needed, move the elevator.
	    if(ElevatorState[elid] == ELEVATOR_STATE_IDLE)
	        ReadNextFloorInQueue(elid);

	    return 1;
	}

	return 0;
}

stock ResetElevatorQueue()
{
	// Resets the queue.
	for(new elid;elid < MAX_ELEVATORS; elid++)
	{
		new floors = NumFloors[elid];
		for(new i; i < floors; i ++)
		{
		    ElevatorQueue[elid][i] 	= INVALID_FLOOR;
		    FloorRequestedBy[elid][i] = INVALID_PLAYER_ID;
		}
	}
	return 1;
}

stock IsFloorInQueue(floorid,elid)
{
	// Checks if the specified floor is currently part of the queue.
	new floors = NumFloors[elid];
	for(new i; i < floors; i ++)
	    if(ElevatorQueue[elid][i] == floorid)
	        return 1;

	return 0;
}

stock ReadNextFloorInQueue(elid)
{
	// Reads the next floor in the queue, closes doors, and goes to it.

	if(ElevatorState[elid] != ELEVATOR_STATE_IDLE || ElevatorQueue[elid][0] == INVALID_FLOOR)
	    return 0;

	Elevator_CloseDoors(elid);
	Floor_CloseDoors(ElevatorFloor[elid],elid);

	return 1;
}

stock DidPlayerRequestElevator(playerid,elid)
{
	new floors = NumFloors[elid];
	for(new i; i < floors; i ++)
	    if(FloorRequestedBy[elid][i] == playerid)
	        return 1;

	return 0;
}

stock GetPolygonHouseId(aukstas,elid)
{
	if(elid == 0)
		return 0;

	for(new i;i<NUM_POLYGONS;i++)
	{
		if(IsValidDynamicArea(Polygons[i]))
		{
			if(PolygonBuilding[i] == elid && PolygonAukstas[i] == aukstas)
			{
				// ok now find the actual house..
				foreach(Houses,hid)
				{
					if(hInfo[hid][polyId] == i)
						return hid;
				}
				return 0;
			}
		}
	}
	return 0;
}
stock ShowElevatorDialog(playerid,elid)
{
	new string[1524];
	new floors = NumFloors[elid];
	for(new i; i < floors; i ++)
	{
	    if(FloorRequestedBy[elid][i] != INVALID_PLAYER_ID)
	        strcat(string, "{5079ff}");
		else
			strcat(string, "{FFFFFF}");
		new hid = GetPolygonHouseId(i,elid);

	    strcat(string, FloorNames[i]);
	    if(hid)
		{
			if(strcmp(hInfo[hid][Name],"Nera",true) == 0)
				format(string,sizeof(string),"%s [Namas %i: Parduodamas]",string,hid);
			else if(hInfo[hid][Locked] && !hInfo[hid][islauztos])
				format(string,sizeof(string),"%s {FF0000}[Namas %i: %s]",string,hid,hInfo[hid][Name]);
			else
				format(string,sizeof(string),"%s {00FF00}[Namas %i: %s]",string,hid,hInfo[hid][Name]);
		}
			
	    strcat(string, "\n");
	}
	SetPVarInt(playerid, "ElevatorID", elid);
	ShowPlayerDialog(playerid, 874, DIALOG_STYLE_LIST, "Liftas", string, "Pasirinkti", "Atsaukti");

	return 1;
}

stock ElevatorDialogResponse(playerid,listitem)
{
	new elid = GetPVarInt(playerid, "ElevatorID");
	// listitem is aukstas
	new hid = GetPolygonHouseId(listitem,elid);

    if(hid)
	{
		new pname[24];
		GetPlayerName(playerid, pname, 24);
	
		if(strcmp(hInfo[hid][Name],"Nera",true) == 0 || strcmp(hInfo[hid][Name],pname,true) == 0 || strcmp(hInfo[hid][Renter],pname,true) == 0 || hInfo[hid][islauztos] || !hInfo[hid][Locked] )
		{

		}
		else
		{
			if(playerDB[playerid][specialybe]!=81 && playerDB[playerid][specialybe] != 83 && !playerDB[playerid][admin])
				SendInfoMessage(playerid,"~r~Aukstas uzrakintas!");
			else
				Lauztis(playerid,hid);
			return;
		}
	}


	if(FloorRequestedBy[elid][listitem] != INVALID_PLAYER_ID || IsFloorInQueue(listitem,elid))
		GameTextForPlayer(playerid, "~r~Liftas jau iskviestas", 3500, 4);
	else if(DidPlayerRequestElevator(playerid,elid))
		GameTextForPlayer(playerid, "~r~Tu jau kvietei lifta!", 3500, 4);
	else
		CallElevator(playerid, listitem,elid);
}

stock CallElevator(playerid, floorid,elid)
{
	// Calls the elevator (also used with the elevator dialog).
	if(FloorRequestedBy[elid][floorid] != INVALID_PLAYER_ID || IsFloorInQueue(floorid,elid))
	    return 0;
	FloorRequestedBy[elid][floorid] = playerid;
	AddFloorToQueue(floorid,elid);

	return 1;
}

stock Float:GetElevatorZCoordForFloor(floorid,elid)
    return (ElevatorObjects[elid][2] + FloorZOffsets[elid][floorid] + ElevatorOffsets[elid]); // A small offset for the elevator object itself.

stock Float:GetDoorsZCoordForFloor(floorid,elid)
	return (ElevatorObjects[elid][2] + FloorZOffsets[elid][floorid]);



stock Elevator_Initialize()
{
	for(new elid;elid < MAX_ELEVATORS; elid++)
	{
		new Float:zcoord = ElevatorObjects[elid][2]+ ElevatorOffsets[elid];
		Obj_Elevator[elid]			= CreateDynamicObject(18755, ElevatorObjects[elid][0], ElevatorObjects[elid][1],zcoord,ElevatorObjects[elid][3],ElevatorObjects[elid][4],ElevatorObjects[elid][5]);
		Obj_ElevatorDoors[elid][0] 	= CreateDynamicObject(18757, ElevatorObjects[elid][0], ElevatorObjects[elid][1],zcoord,ElevatorObjects[elid][3],ElevatorObjects[elid][4],ElevatorObjects[elid][5]);
		Obj_ElevatorDoors[elid][1] 	= CreateDynamicObject(18756, ElevatorObjects[elid][0], ElevatorObjects[elid][1],zcoord,ElevatorObjects[elid][3],ElevatorObjects[elid][4],ElevatorObjects[elid][5]);

		Label_Elevator[elid]          = CreateDynamic3DTextLabel("Spausk [ENTER]", 0xFFFFDD, ElevatorLabels[elid][0],ElevatorLabels[elid][1],ElevatorLabels[elid][2] , 4.0, _,_, 1);

		new string[128];
		new floors = NumFloors[elid];
		for(new i; i < floors; i ++)
		{
			zcoord = GetDoorsZCoordForFloor(i,elid);
		    Obj_FloorDoors[elid][i][0] 	= CreateDynamicObject(18757, ElevatorFloorDoors[elid][0], ElevatorFloorDoors[elid][1],zcoord,ElevatorFloorDoors[elid][3],ElevatorFloorDoors[elid][4],ElevatorFloorDoors[elid][5]);
			Obj_FloorDoors[elid][i][1] 	= CreateDynamicObject(18756, ElevatorFloorDoors[elid][0], ElevatorFloorDoors[elid][1],zcoord,ElevatorFloorDoors[elid][3],ElevatorFloorDoors[elid][4],ElevatorFloorDoors[elid][5]);


			format(string, sizeof(string), "%s\nSpausk [ENTER]", FloorNames[i]);

			Label_Floors[elid][i]         = CreateDynamic3DTextLabel(string, 0xFFFFDD,FloorLabels[elid][0], FloorLabels[elid][1], zcoord - 0.6, 10.5, _,_, 1);
			// Label_Elevator, Text3D:Label_Floors[21];
		}

		// Open ground floor doors:
		Floor_OpenDoors(0,elid);
		Elevator_OpenDoors(elid);
	}
	return 1;
}

// customer per elevator


stock Elevator_OpenDoors(elid)
{
	// Opens the elevator's doors.

	new Float:xl, Float:yl, Float:zl;
	new Float:xr, Float:yr, Float:zr;
	GetDynamicObjectPos(Obj_ElevatorDoors[elid][0], xl, yl, zl);
	GetDynamicObjectPos(Obj_ElevatorDoors[elid][0], xr, yr, zr);

	if(LeftDoorOpen[elid][0] != 0.0)
		xl = LeftDoorOpen[elid][0];
	if(LeftDoorOpen[elid][1] != 0.0)
		yl = LeftDoorOpen[elid][1];

	if(RightDoorOpen[elid][0] != 0.0)
		xr = RightDoorOpen[elid][0];
	if(RightDoorOpen[elid][1] != 0.0)
		yr = RightDoorOpen[elid][1];

	MoveDynamicObject(Obj_ElevatorDoors[elid][0], xl, yl, zl, DOORS_SPEED);
	MoveDynamicObject(Obj_ElevatorDoors[elid][1], xr, yr, zr, DOORS_SPEED);

	return 1;
}

stock Elevator_CloseDoors(elid)
{
    // Closes the elevator's doors.

    if(ElevatorState[elid] == ELEVATOR_STATE_MOVING)
	    return 0;

    new Float:x, Float:y, Float:z;

	GetDynamicObjectPos(Obj_ElevatorDoors[elid][0], x, y, z);
	MoveDynamicObject(Obj_ElevatorDoors[elid][0], ElevatorObjects[elid][0], ElevatorObjects[elid][1], z, DOORS_SPEED);
	MoveDynamicObject(Obj_ElevatorDoors[elid][1], ElevatorObjects[elid][0], ElevatorObjects[elid][1], z, DOORS_SPEED);
	ElevatorState[elid] = ELEVATOR_STATE_CLOSING;
	return 1;
}

stock Floor_OpenDoors(floorid,elid)
{
    // Opens the doors at the specified floor.
	new Float:xl, Float:yl;
	new Float:xr, Float:yr;

	xl = ((LeftDoorOpen[elid][0] != 0.0) ? (LeftDoorOpen[elid][0]) : (ElevatorFloorDoors[elid][0]));
	yl = ((LeftDoorOpen[elid][1] != 0.0) ? (LeftDoorOpen[elid][1]) : (ElevatorFloorDoors[elid][1]));

	xr = ((RightDoorOpen[elid][0] != 0.0) ? (RightDoorOpen[elid][0]) : (ElevatorFloorDoors[elid][0]));
	yr = ((RightDoorOpen[elid][1] != 0.0) ? (RightDoorOpen[elid][1]) : (ElevatorFloorDoors[elid][1]));

    MoveDynamicObject(Obj_FloorDoors[elid][floorid][0], xl, yl, GetDoorsZCoordForFloor(floorid,elid), DOORS_SPEED);
	MoveDynamicObject(Obj_FloorDoors[elid][floorid][1], xr, yr, GetDoorsZCoordForFloor(floorid,elid), DOORS_SPEED);

	PlaySoundForPlayersInRange(6401, 50.0, xl, yl, GetDoorsZCoordForFloor(floorid,elid) + 5.0);

	return 1;
}

stock Floor_CloseDoors(floorid,elid)
{
    // Closes the doors at the specified floor.

    MoveDynamicObject(Obj_FloorDoors[elid][floorid][0], ElevatorFloorDoors[elid][0], ElevatorFloorDoors[elid][1], GetDoorsZCoordForFloor(floorid,elid), DOORS_SPEED);
	MoveDynamicObject(Obj_FloorDoors[elid][floorid][1], ElevatorFloorDoors[elid][0], ElevatorFloorDoors[elid][1], GetDoorsZCoordForFloor(floorid,elid), DOORS_SPEED);

	PlaySoundForPlayersInRange(6401, 50.0, ElevatorFloorDoors[elid][0], ElevatorFloorDoors[elid][1], GetDoorsZCoordForFloor(floorid,elid) + 5.0);

	return 1;
}
