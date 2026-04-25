//
// A Driver NPC that goes around a path continuously
// Kye 2009
//
//#include <a_samp>
#include <a_npc>

//native CallRemoteFunction(const function[], const format[], {Float,_}:...);
//------------------------------------------

main(){}

//------------------------------------------
forward NextPlayback();
public NextPlayback()
{
	//CallRemoteFunction("BusAtPlace","i",0);
	StartRecordingPlayback(PLAYER_RECORDING_TYPE_DRIVER,"Autobusai");
}
	

//------------------------------------------

public OnRecordingPlaybackEnd()
{
    NextPlayback();
}

//------------------------------------------

public OnNPCEnterVehicle(vehicleid, seatid)
{
    NextPlayback();
}

//------------------------------------------

public OnNPCExitVehicle()
{
    StopRecordingPlayback();
}

//------------------------------------------
