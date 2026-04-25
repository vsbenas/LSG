static bool: IsModelACar(modelid) 
{
    switch(modelid)
    {
        case 430, 446, 452, 453, 454, 472, 473, 484, 493, 595: return false; // Boats.
        case 448, 461, 462, 463, 468, 471, 481, 509, 510, 521, 522, 523, 581, 586: return false; // Bikes
        case 417, 425, 447, 460, 469, 476, 487, 488, 497, 511, 512, 513, 519, 520, 548, 553, 563, 577, 592, 593: return false; // Airplanes
    }
    return true;
}
enum {
    DRIFT_STATE_NONE,
    DRIFT_STATE_DRIFTING
}
enum e_DRIFT_PLAYER_STRUCT {
    Float:  vHealth,

    timeoutTicks,
    driftState
}
// constants
#define MIN_DRIFT_ANGLE     (12.0)   // minimum drift angle to start a drift
#define MAX_DRIFT_ANGLE     (80.0)  // maximum drift angle to start a drift
#define MIN_DRIFT_SPEED     (30.0)  // minimum speed to start a drift
#define TIMEOUT_TICKS 20

new g_DriftPlayers[MAX_PLAYERS][e_DRIFT_PLAYER_STRUCT];

stock DriftCheck() // called in fades.inc
{
    foreach(PlayersDrifting,playerid)
    {

        new vehicleID = GetPlayerVehicleID(playerid);
        if(vehicleID && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsModelACar(GetVehicleModel(vehicleID)))
        {
            new Float: vX, Float: vY, Float: vZ;
            GetVehicleVelocity(vehicleID, vX, vY, vZ);

            new Float: angle;
            GetVehicleZAngle(vehicleID, angle);

            new Float: speed = floatsqroot(vX*vX + vY*vY + vZ*vZ) * 161.48;
            
            new Float: direction;
            direction = atan2(vY, vX);
            direction -= 90.0;
    
            if(direction < 0) direction += 360.0;

            new Float: driftAngle, Float:driftAngleReal;
            driftAngleReal = angle - floatabs(direction);

            if(driftAngleReal > 270.0) driftAngleReal -= 270.0;
            if(driftAngleReal < -270.0) driftAngleReal += 270.0;

            driftAngle = floatabs(driftAngleReal);
        
            switch(g_DriftPlayers[playerid][driftState])
            {
                case DRIFT_STATE_NONE:
                {
                    if(MIN_DRIFT_ANGLE <= driftAngle <= MAX_DRIFT_ANGLE && speed >= MIN_DRIFT_SPEED)
                    {                        
                        g_DriftPlayers[playerid][driftState] = DRIFT_STATE_DRIFTING;
                        g_DriftPlayers[playerid][timeoutTicks] = 0;

                        GetVehicleHealth(vehicleID, g_DriftPlayers[playerid][vHealth]);
                        OnPlayerDriftStart(playerid);
                    }
                }
                case DRIFT_STATE_DRIFTING:
                {
                    new Float: vehicleHealth;
                    GetVehicleHealth(vehicleID, vehicleHealth);
                    if(IsPlayerAfk(playerid))
                    {
                        g_DriftPlayers[playerid][driftState] = DRIFT_STATE_NONE;
                        g_DriftPlayers[playerid][timeoutTicks] = 0;
                        OnPlayerDriftEnd(playerid);
                    }
                    else if(vehicleHealth+11 < g_DriftPlayers[playerid][vHealth])
                    {
                        g_DriftPlayers[playerid][driftState] = DRIFT_STATE_NONE;
                        g_DriftPlayers[playerid][timeoutTicks] = 0;

                        OnPlayerDriftEnd(playerid);
                    }
                    else if(MIN_DRIFT_ANGLE <= driftAngle <= MAX_DRIFT_ANGLE && speed >= MIN_DRIFT_SPEED)
                    {
                        g_DriftPlayers[playerid][timeoutTicks] = 0;
                        OnPlayerDriftUpdate(playerid, driftAngleReal, speed);
                    }
                    else
                    {
                        g_DriftPlayers[playerid][timeoutTicks]++;

                        if(g_DriftPlayers[playerid][timeoutTicks] >= TIMEOUT_TICKS)
                        {
                            g_DriftPlayers[playerid][driftState] = DRIFT_STATE_NONE;
                            g_DriftPlayers[playerid][timeoutTicks] = 0;
                            OnPlayerDriftEnd(playerid);
                        }
                    }
                }
            }
        }

    }
}
new DriftPoints[MAX_PLAYERS];
new DriftBonus[MAX_PLAYERS];
new Passengers[MAX_PLAYERS][4];
new LastAngle[MAX_PLAYERS];
forward OnPlayerDriftStart(playerid);
public OnPlayerDriftStart(playerid)
{
    DriftPoints[playerid]=0;
    LastAngle[playerid]=0;
    DriftBonus[playerid]=0;
    new veh = GetPlayerVehicleID(playerid);
    for(new i;i<4;i++)
        Passengers[playerid][i]=-1;
    for(new i;i<MAX_PLAYERS;i++) if(IsPlayerConnected(i))
    {
        if(GetPlayerVehicleID(i) == veh)
        {
            new seat = GetPlayerVehicleSeat(i);
            if( 0 <= seat < 4)
                Passengers[playerid][seat] = i;
        }
    }
    return true;
}
new LastUpdate[MAX_PLAYERS];
forward OnPlayerDriftUpdate(playerid, Float: drift_angle, Float: speed);
public OnPlayerDriftUpdate(playerid, Float: drift_angle, Float: speed)
{
    if(GetTickCount()-LastUpdate[playerid] < 1000)
    {
        if(drift_angle*LastAngle[playerid] < 0 && DriftBonus[playerid] < 5)
            DriftBonus[playerid]++;
    }
    else
    {
        DriftBonus[playerid]=1;
    }
    LastUpdate[playerid] = GetTickCount();
    DriftPoints[playerid] += floatround(floatabs(speed * drift_angle) * DriftBonus[playerid]);

    if(drift_angle < 0.0)
        LastAngle[playerid] = -1;
    else
        LastAngle[playerid] = 1;

    new message[128];
    new coloras[25];
    new extra[20] = "~w~";
    if(DriftPoints[playerid] >= 1000000)
    {
        coloras = "~p~";
        new stars = DriftPoints[playerid] / 1000000;
        if(stars > 15)
        {
            stars-=15;
            extra = "~b~";
            if(stars > 5)
                stars = 5;
        }
        if(stars > 10)
        {
            stars-=10;
            extra = "~r~";
            
        }
        else if(stars > 5)
        {
            stars -= 5;
            extra = "~y~";
            
        }
        for(new i;i<stars;i++)
            extra[i+3]=']';
    }
    else if(DriftPoints[playerid] >= 750000)
        coloras = "~y~";
    else if(DriftPoints[playerid] >= 500000)
        coloras = "~y~~h~";
    else if(DriftPoints[playerid] >= 200000)
        coloras = "~y~~h~~h~";
    else if(DriftPoints[playerid] >= 100000)
        coloras = "~y~~h~~h~~h~";
    

    if(DriftBonus[playerid] == 1)
        format(message, sizeof message, "~y~DRIFT~n~ ~w~%s%s~n~%s", coloras,FormatNumber(DriftPoints[playerid]),extra);
    else if(DriftBonus[playerid] == 2)
        format(message, sizeof message, "~y~DRIFT~n~ ~w~%s%s ~p~~h~x%i~n~%s",coloras,FormatNumber(DriftPoints[playerid]),DriftBonus[playerid],extra);
    else if(DriftBonus[playerid] == 3)
        format(message, sizeof message, "~y~DRIFT~n~ ~w~%s%s ~p~x%i~n~%s",coloras,FormatNumber(DriftPoints[playerid]),DriftBonus[playerid],extra);
    else if(DriftBonus[playerid] == 4)
        format(message, sizeof message, "~y~DRIFT~n~ ~w~%s%s ~r~~h~x%i~n~%s",coloras,FormatNumber(DriftPoints[playerid]),DriftBonus[playerid],extra);
    else if(DriftBonus[playerid] >= 5)
        format(message, sizeof message, "~y~DRIFT~n~ ~w~%s%s ~r~x%i~n~%s",coloras,FormatNumber(DriftPoints[playerid]),DriftBonus[playerid],extra);

    for(new i;i<4;i++) if(Passengers[playerid][i] != -1)
        GameTextForPlayer(Passengers[playerid][i], message, 1000, 4);
    return true;
}
forward OnPlayerDriftEnd(playerid);
public OnPlayerDriftEnd(playerid)
{
    if(DriftPoints[playerid] == 0)
        return 1;
    HandleChristmasDriftEnd(playerid);
    ProcessAchievement(playerid,102,DriftPoints[playerid]);
    new message[128];
    new coloras[25];
    new extra[20] = "~w~";
    if(DriftPoints[playerid] >= 1000000)
    {
        coloras = "~p~";
        new stars = DriftPoints[playerid] / 1000000;
        if(stars > 15)
        {
            stars-=15;
            extra = "~b~";
            if(stars > 5)
                stars = 5;
        }
        if(stars > 10)
        {
            stars-=10;
            extra = "~r~";
            
        }
        else if(stars > 5)
        {
            stars -= 5;
            extra = "~y~";
            
        }
        for(new i;i<stars;i++)
            extra[i+3]=']';
    }
    else if(DriftPoints[playerid] >= 750000)
        coloras = "~y~";
    else if(DriftPoints[playerid] >= 500000)
        coloras = "~y~~h~";
    else if(DriftPoints[playerid] >= 200000)
        coloras = "~y~~h~~h~";
    else if(DriftPoints[playerid] >= 100000)
        coloras = "~y~~h~~h~~h~";
    else
        coloras = "~w~";
    format(message, sizeof message, "~w~DRIFT BAIGTAS!~n~~b~Taskai: %s%s~n~%s", coloras,FormatNumber(DriftPoints[playerid]),extra);
    new msgas[128];
    format(msgas,128,"[DRIFT] Surinkti taðkai: %s.",FormatNumber(DriftPoints[playerid]));
    printf("[DRIFT] %s: %s",ReturnName(playerid),msgas);
    for(new i;i<4;i++) if(Passengers[playerid][i] != -1)
    {
        GameTextForPlayer(Passengers[playerid][i], message, 3000, 4);
        SendClientMessageLT(Passengers[playerid][i], -1, msgas);
    }
    return true; 
}