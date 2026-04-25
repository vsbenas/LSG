
new VehicleDestroyed = 136;
new ClientJoin = 25;

new authkeys[MAX_PLAYERS][50];
forward setAuthKey(playerid, key[]);
public setAuthKey(playerid,key[])
{
	format(authkeys[playerid],50,"%s",key);
}
stock initAuthKey(playerid)
{
    SetPVarString(playerid, "authkey", authkeys[playerid]);
}
IRPC:ClientJoin(playerid, BitStream:bs)
{
	new iVersion, byteMod, byteNickNameLen;
	new nickname[32], uiClientChallengeResponse, byteAuthKeyLen;
	new authKey[512];
	new iClientVerLen;
	new clientVersion[32];
	BS_ReadInt32(bs, iVersion);
	BS_ReadUint8(bs, byteMod);
	BS_ReadUint8(bs, byteNickNameLen);
	BS_ReadString(bs, nickname, byteNickNameLen);
	BS_ReadUint32(bs, uiClientChallengeResponse);
	BS_ReadUint8(bs, byteAuthKeyLen);
	BS_ReadString(bs, authKey, byteAuthKeyLen);
	BS_ReadUint8(bs, iClientVerLen);
	BS_ReadString(bs, clientVersion, iClientVerLen);
	printf("[clientJoin]: %s v:%i b:%i c:%i k:%s cv:%s",nickname, iVersion, byteMod, uiClientChallengeResponse, authKey, clientVersion);
    if(strlen(authKey) > 0)
        setAuthKey(playerid, authKey);
	return 1;
}

IRPC:VehicleDestroyed(playerid, BitStream:bs)
{
    new vehicleid;

    BS_ReadUint16(bs, vehicleid);

    if (GetVehicleModel(vehicleid) < 400)
    {
        return 0;
    }

    return OnVehicleDeathRequest(vehicleid, playerid);
}

forward OnVehicleDeathRequest(vehicleid, killerid);
public OnVehicleDeathRequest(vehicleid, killerid)
{
    new Float:health;

    GetVehicleHealth(vehicleid, health);
	
	new Float:Coo[3];
	GetVehiclePos(vehicleid, Coo[0], Coo[1], Coo[2]);
	//MapAndreas_FindZ_For2DCoord(Coo[0], Coo[1], Coo[2]);
	//new pp = GetDriver(vehicleid);
	/*if(pp != INVALID_PLAYER_ID && IsPlayerConnected(pp) && !IsPlayerInRangeOfPointEx (350.0, pp, playerDB[pp][pCurrentPos][0], playerDB[pp][pCurrentPos][1], playerDB[pp][pCurrentPos][2]))
	{
		printf("%s Vehicle Death denied",ReturnName(pp));
		//AC_Ban(pp, "Car TP Boomer",1);
		return 0;
	}*/
    if ((Coo[2] > 800.0 || health >= 250.0) && GetVehicleModel(vehicleid) == 539)
    {
        if(IsPlayerAdmin(0))
        	SendClientMessage(0, -1, "[DEBUG] Vortex saved");
        return 0;

    }

    return 1;
}


const AIM_SYNC = 203; // 0.3.7

IPacket:AIM_SYNC(playerid, BitStream:bs) // incoming packet
{
    new aimData[PR_AimSync];
    
    BS_IgnoreBits(bs, 8); // packet id (byte)
    BS_ReadAimSync(bs, aimData);

    if (aimData[PR_aimZ] != aimData[PR_aimZ]) // is NaN
    {
        /*aimData[PR_aimZ] = 0.0; // FIX AIMZ invisible

        BS_SetWriteOffset(bs, 8);
        BS_WriteAimSync(bs, aimData); // rewrite data */
        return 0;
    }

    return 1; // continue processing
}  
const PLAYER_SYNC = 207;

IPacket:PLAYER_SYNC(playerid, BitStream:bs)
{
	new onFootData[PR_OnFootSync];

    BS_IgnoreBits(bs, 8); // ignore packetid (byte)
    BS_ReadOnFootSync(bs, onFootData);

    if (onFootData[PR_surfingVehicleId] != 0 && // FIX SURVING VEHICLE INVISIBLE
        onFootData[PR_surfingVehicleId] != INVALID_VEHICLE_ID) 
    {
        if ((floatabs(onFootData[PR_surfingOffsets][0]) >= 50.0) ||
            (floatabs(onFootData[PR_surfingOffsets][1]) >= 50.0) ||
            (floatabs(onFootData[PR_surfingOffsets][2]) >= 50.0)) 
        {
            return 0; // ignore bad packet
        } 
    }

    return 1;
}


const UNOCCUPIED_SYNC = 209;

#if !defined IsNaN
    #define IsNaN(%0) ((%0) != (%0))
#endif

IPacket:UNOCCUPIED_SYNC(playerid, BitStream:bs)
{
    new unoccupiedData[PR_UnoccupiedSync];
 
    BS_IgnoreBits(bs, 8);
    BS_ReadUnoccupiedSync(bs, unoccupiedData);
 
    if (IsNaN(unoccupiedData[PR_roll][0]) ||
        IsNaN(unoccupiedData[PR_roll][1]) ||
        IsNaN(unoccupiedData[PR_roll][2]) ||
        IsNaN(unoccupiedData[PR_direction][0]) ||
        IsNaN(unoccupiedData[PR_direction][1]) ||
        IsNaN(unoccupiedData[PR_direction][2]) ||
        IsNaN(unoccupiedData[PR_position][0]) ||
        IsNaN(unoccupiedData[PR_position][1]) ||
        IsNaN(unoccupiedData[PR_position][2]) ||
        IsNaN(unoccupiedData[PR_angularVelocity][0]) ||
        IsNaN(unoccupiedData[PR_angularVelocity][1]) ||
        IsNaN(unoccupiedData[PR_angularVelocity][2]) ||
        IsNaN(unoccupiedData[PR_velocity][0]) ||
        IsNaN(unoccupiedData[PR_velocity][1]) ||
        IsNaN(unoccupiedData[PR_velocity][2]) ||
        (floatabs(unoccupiedData[PR_roll][0]) > 1.0) ||
        (floatabs(unoccupiedData[PR_roll][1]) > 1.0) ||
        (floatabs(unoccupiedData[PR_roll][2]) > 1.0) ||
        (floatabs(unoccupiedData[PR_direction][0]) > 1.0) ||
        (floatabs(unoccupiedData[PR_direction][1]) > 1.0) ||
        (floatabs(unoccupiedData[PR_direction][2]) > 1.0) ||
        (floatabs(unoccupiedData[PR_position][0]) >= 20000.0) ||
        (floatabs(unoccupiedData[PR_position][1]) >= 20000.0) ||
        (floatabs(unoccupiedData[PR_position][2]) >= 20000.0) ||
        (floatabs(unoccupiedData[PR_angularVelocity][0]) >= 1.0) ||
        (floatabs(unoccupiedData[PR_angularVelocity][1]) >= 1.0) ||
        (floatabs(unoccupiedData[PR_angularVelocity][2]) >= 1.0) ||
        (floatabs(unoccupiedData[PR_velocity][0]) >= 100.0) ||
        (floatabs(unoccupiedData[PR_velocity][1]) >= 100.0) ||
        (floatabs(unoccupiedData[PR_velocity][2]) >= 100.0)
    ) {
        return 0; // ignore bad packet
    }
    if ((
            unoccupiedData[PR_roll][0] == unoccupiedData[PR_direction][0] &&
            unoccupiedData[PR_roll][1] == unoccupiedData[PR_direction][1] &&
            unoccupiedData[PR_roll][2] == unoccupiedData[PR_direction][2]
        ) || (
            unoccupiedData[PR_roll][0] == unoccupiedData[PR_roll][1] &&
            unoccupiedData[PR_roll][1] == unoccupiedData[PR_roll][2]
        ) || (
            unoccupiedData[PR_direction][0] == unoccupiedData[PR_direction][1] &&
            unoccupiedData[PR_direction][1] == unoccupiedData[PR_direction][2]
        )
    ) {
        return 0; // ignore bad packet
    }
	if((
            unoccupiedData[PR_roll][0] * unoccupiedData[PR_direction][0] +
            unoccupiedData[PR_roll][1] * unoccupiedData[PR_direction][1] +
            unoccupiedData[PR_roll][2] * unoccupiedData[PR_direction][2] >= 0.000001
        ) || (
            floatabs(
                1.0 - VectorSize(
                    unoccupiedData[PR_roll][0],
                    unoccupiedData[PR_roll][1],
                    unoccupiedData[PR_roll][2]
                )
            ) >= 0.000001
        ) || (
            floatabs(
                1.0 - VectorSize(
                    unoccupiedData[PR_direction][0],
                    unoccupiedData[PR_direction][1],
                    unoccupiedData[PR_direction][2]
                )
            ) >= 0.000001
        )) 
	{
        return 0; // ignore bad packet
    }


    return 1;
}
const TRAILER_SYNC = 210;


IPacket:TRAILER_SYNC(playerid, BitStream:bs)
{
    new trailerData[PR_TrailerSync];

    BS_IgnoreBits(bs, 8);
    BS_ReadTrailerSync(bs, trailerData);

    //Anything you want to see here
    new Float:ac_dist = GetVehicleDistanceFromPoint(trailerData[PR_trailerId], trailerData[PR_position][0], trailerData[PR_position][1], trailerData[PR_position][2]);
    
    if(ac_dist >= 45.0)
    {
        printf("[beno ac] Car teleport cheat %s teleported %i distance %.2f", ReturnName(playerid), trailerData[PR_trailerId], ac_dist);
        if(LastCarTp[playerid] != trailerData[PR_trailerId])
        {
            LastCarTp[playerid] = trailerData[PR_trailerId];
            TpCarCount[playerid]++;
            if(TpCarCount[playerid] > 5)
            {
                AC_Ban(playerid, "Car TP");
            }
        }
        return 0;
    }

    return 1;
}

const SPECTATING_SYNC = 212;

OPacket:SPECTATING_SYNC(playerid, BitStream:bs)
{
    //new spectatingData[PR_SpectatingSync];

    //BS_IgnoreBits(bs, 8);
    //BS_ReadSpectatingSync(bs, spectatingData);

    //Anything you want to see here
    new msg[25];
    format(msg,25,"OPacket %i", playerid);
    if(IsPlayerAdmin(playerid))
        SendClientMessage(playerid, -1, msg);

    return 1;
}

IRawPacket:20(playerid, BitStream:bs) {
    new packetid, rpcid, NumberOfBitsOfData;
    BS_ReadValue(bs, PR_UINT8, packetid, PR_UINT8, rpcid, PR_CUINT32, NumberOfBitsOfData);
    if (packetid == 40 || (NumberOfBitsOfData >= 0x1FFFFF || NumberOfBitsOfData <= 0x80000000 || NumberOfBitsOfData < 0)) {
        printf("Crasher Detected - RPCID: %d, NumberOfBitsOfData: %d", rpcid, NumberOfBitsOfData);
        BanEx(playerid, "Raknet Bot");
        return false;
    }
    return true;
}