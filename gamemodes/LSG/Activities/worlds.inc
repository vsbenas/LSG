#define MAX_WORLDS_PLAYER 5 // cant do more than 100
#define MAX_WORLD_OBJECTS 10000

#define BASE_X -10.0
#define BASE_Y 4990.0
#define BASE_Z 21.5000

#include <json>

/*
    There are a couple of concepts to be mindful of
    Houseid - player house id (1-500)
    Worldid - world inside the house (0-9)
    Virtual World - player dimension (100,000 - 200,000)
    Virtual World = 100,000 + houseid * 100 + worldid
*/
enum closestobj
{
    closestobjslot,
    Float:closestobjdist
};
new closestobjs[MAX_WORLD_OBJECTS][closestobj];
enum LoadedWorldEnum 
{
    world_loaded,
    world_title[24],
    world_objects_count,
    world_jetpack,
    world_guns,
    world_cars,
    world_autofix,
    world_nitro,
    world_bounds,
    world_respawn,
    world_tpplayer,
    world_tpmap,
    world_safezone,
    world_editors[75],
    Float:start_pos[3]
}

new Worlds[MAX_HOUSES][MAX_WORLDS_PLAYER][LoadedWorldEnum];

new WorldObjects[MAX_HOUSES][MAX_WORLDS_PLAYER][MAX_WORLD_OBJECTS];

stock Node:WorldToJson(houseid,worldid) 
{
    if(!Worlds[houseid][worldid][world_loaded]) 
    {
        return JSON_Object();
    }
    new Float:start[3];
    start[0] = Worlds[houseid][worldid][start_pos][0];
    start[1] = Worlds[houseid][worldid][start_pos][1];
    start[2] = Worlds[houseid][worldid][start_pos][2];
    return JSON_Object(
        "title", JSON_String(Worlds[houseid][worldid][world_title]),
        "objects", JSON_Int(Worlds[houseid][worldid][world_objects_count]),
        "start_pos", JSON_Array(JSON_Float(start[0]), JSON_Float(start[1]), JSON_Float(start[2])),
        "jetpack",  JSON_Int(Worlds[houseid][worldid][world_jetpack]),
        "guns",  JSON_Int(Worlds[houseid][worldid][world_guns]),
        "cars",  JSON_Int(Worlds[houseid][worldid][world_cars]),
        "autofix",  JSON_Int(Worlds[houseid][worldid][world_autofix]),
        "nitro",  JSON_Int(Worlds[houseid][worldid][world_nitro]),
        "bounds",  JSON_Int(Worlds[houseid][worldid][world_bounds]),
        "respawn",  JSON_Int(Worlds[houseid][worldid][world_respawn]),
        "tpplayer",  JSON_Int(Worlds[houseid][worldid][world_tpplayer]),
        "tpmap",  JSON_Int(Worlds[houseid][worldid][world_tpmap]),
        "safezone",  JSON_Int(Worlds[houseid][worldid][world_safezone]),
        "editors",  JSON_String(Worlds[houseid][worldid][world_editors])
    );
}

stock ParseWorldJson(houseid, worldid, Node:json) 
{
    new ret;
    ret += JSON_GetString(json, "title", Worlds[houseid][worldid][world_title], 24);
    // ret += JSON_GetInt(json, "objects", Worlds[houseid][worldid][world_objects_count]);
    new Node:startpos;
    ret += JSON_GetArray(json, "start_pos", startpos);
    for(new i; i<3; i++) 
    {
        new Float:pos;
        new Node:node;
        ret += JSON_ArrayObject(startpos, i, node);
        ret += JSON_GetNodeFloat(node, pos);
        Worlds[houseid][worldid][start_pos][i]=pos;
    }

    JSON_GetInt(json, "jetpack", Worlds[houseid][worldid][world_jetpack]);
    JSON_GetInt(json, "guns", Worlds[houseid][worldid][world_guns]);
    JSON_GetInt(json, "cars", Worlds[houseid][worldid][world_cars]);
    JSON_GetInt(json, "autofix", Worlds[houseid][worldid][world_autofix]);
    JSON_GetInt(json, "nitro", Worlds[houseid][worldid][world_nitro]);
    JSON_GetInt(json, "bounds", Worlds[houseid][worldid][world_bounds]);
    JSON_GetInt(json, "respawn", Worlds[houseid][worldid][world_respawn]);
    JSON_GetInt(json, "tpplayer", Worlds[houseid][worldid][world_tpplayer]);
    JSON_GetInt(json, "tpmap", Worlds[houseid][worldid][world_tpmap]);
    JSON_GetInt(json, "safezone", Worlds[houseid][worldid][world_safezone]);
    JSON_GetString(json, "editors", Worlds[houseid][worldid][world_editors], 100);
    

    if(ret) 
    {
        printf("ParseWorldJson: some error occurred: %d", ret);
        return;
    }
    Worlds[houseid][worldid][world_loaded] = true;
}

stock HandleWorldDeath(playerid)
{
    if(!IsPlayerInWorld(playerid))
        return 0;
    
    new houseid = GetWorldHouseId(playerid);
    new worldid = GetWorldWorldid(playerid);
    
    if(Worlds[houseid][worldid][world_respawn])
    {
        SetPVarInt(playerid, "MireWorld", GetPlayerVirtualWorld(playerid));
		return 1;
    }

    return 0;
}

stock SaveWorld(houseid, worldid)
{
    if(houseid < 0 || houseid > MAX_HOUSES || worldid < 0 || worldid > MAX_WORLDS_PLAYER) 
    {
        printf("Failed saving world %i %i", houseid, worldid);
        return;
    }
    new id = GetWorldVirtualWorld(houseid, worldid);
    new objects = Worlds[houseid][worldid][world_objects_count];
    new Node:dataJson = WorldToJson(houseid, worldid);
    new rawDataString[3000];
    JSON_Stringify(dataJson, rawDataString, 3000);
    new dataString[3500];
    mysql_real_escape_string(rawDataString, dataString);
    new query[4096];
    format(query,4096, "INSERT INTO Worlds(id, houseid, worldid, data, objects) VALUES (%i, %i, %i, '%s', %i) ON DUPLICATE KEY UPDATE data='%s', objects=%i", id, houseid, worldid, dataString, objects, dataString, objects);
    mysql_query(query);
}

stock InitWorlds() 
{
    printf("Initializing worlds");
    // main platform
    CreateObject(18754, 0.0, 5000.0, 20.0, 0.0, 0.0, 0.0, 1000.0);

    mysql_function_query(SQL, "SELECT * FROM Worlds", true, "SQL_LoadWorlds", "");
    mysql_function_query(SQL, "SELECT * FROM WorldObjects order by worldid desc", true, "SQL_LoadWorldObjects", "");
}

forward SQL_LoadWorlds();
public SQL_LoadWorlds()
{
    RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new row=0;
    new temp[24];
    new data[4000];
	while(row < rows)
	{
		//cache_get_row(row, 0, temp);
        new id, houseid, worldid;
		cache_get_row(row, 0, temp), id = strval(temp);
        cache_get_row(row, 1, temp), houseid = strval(temp);
        cache_get_row(row, 2, temp), worldid = strval(temp);
        cache_get_row(row, 3, data);
        new Node:worldJson;
        new res = JSON_Parse(data, worldJson);
        if(res) 
        {
            printf("Failed parsing world %d to json", id);
        }
        else 
        {
            InitWorld(houseid, worldid);
            ParseWorldJson(houseid, worldid, worldJson);
        }
		row++;
	}
    printf("Loaded %i worlds", row);
}

stock LoadObject(Node:objJson, slotid, vw)
{
    new Float:Coo[6];
    new model, houseid,worldid;
    new Node:posNode;
    new res;
    res += JSON_GetInt(objJson, "model", model);
    res += JSON_GetInt(objJson, "houseid", houseid);
    res += JSON_GetInt(objJson, "worldid", worldid);
    res += JSON_GetArray(objJson, "pos", posNode);
    for(new i; i < 6; i++)
    {
        new Float:pos;
        new Node:node;
        res += JSON_ArrayObject(posNode, i, node);
        res += JSON_GetNodeFloat(node, pos);
        Coo[i] = pos;
    }
    new shouldPrint = ShouldPrint(houseid, worldid);
    if(res) 
    {
        printf("Failed loading world object %s", res);
    }
    else
    {
        WorldObjects[houseid][worldid][slotid] = CreateDynamicObject(model, Coo[0],Coo[1],Coo[2], Coo[3],Coo[4],Coo[5], vw);
        if(shouldPrint) PrintObject(model, Coo[0],Coo[1],Coo[2], Coo[3],Coo[4],Coo[5]);
        Worlds[houseid][worldid][world_objects_count]++;
    }
    new Node:textures;
    if(JSON_GetObject(objJson, "textures", textures) == 0)
    {
        for(new i;i<16;i++)
        {
            new key[20];
            format(key,20,"%i",i);
            new Node:texturenode;
            if(JSON_GetObject(textures, key, texturenode) == 0)
            {
                new modelid, txdname[100], texturename[100], materialcolor;
                new ret = JSON_GetInt(texturenode, "modelid", modelid);
                ret += JSON_GetString(texturenode, "txdname", txdname);
                ret += JSON_GetString(texturenode, "texturename", texturename);
                ret += JSON_GetInt(texturenode, "materialcolor", materialcolor);
                if(ret)
                {
                    printf("Failed loading texture material %i %i %i %i", houseid, worldid, slotid, i);
                }
                else
                {
                    SetDynamicObjectMaterial(WorldObjects[houseid][worldid][slotid], i, modelid, txdname, texturename, materialcolor);
                    if(shouldPrint) PrintObjectMaterial(i, modelid, txdname, texturename, materialcolor);
                }
            }
        }
    }  
    new Node:texts;
    if(JSON_GetObject(objJson, "texts", texts) == 0) 
    {
        for(new i;i<16;i++)
        {
            new key[20];
            format(key,20,"%i",i);
            new Node:textnode;
            if(JSON_GetObject(texts, key, textnode) == 0)
            {
                new text[2048], materialsize, fontface[200], fontsize, bold, fontcolor, backcolor, textalignment;
                new ret = JSON_GetString(textnode, "text", text);
                ret += JSON_GetInt(textnode, "materialsize", materialsize);
                ret += JSON_GetString(textnode, "fontface", fontface);
                ret += JSON_GetInt(textnode, "fontsize", fontsize);
                ret += JSON_GetInt(textnode, "bold", bold);
                ret += JSON_GetInt(textnode, "fontcolor", fontcolor);
                ret += JSON_GetInt(textnode, "backcolor", backcolor);
                ret += JSON_GetInt(textnode, "textalignment", textalignment);
                if(ret)
                {
                    printf("Failed loading texture text %i %i %i %i", houseid, worldid, slotid, i);
                }
                else
                {
                    SetDynamicObjectMaterialText(WorldObjects[houseid][worldid][slotid], i, text, materialsize, fontface, fontsize, bold, fontcolor, backcolor, textalignment);
                    if(shouldPrint) PrintObjectMaterialText(i, text, materialsize, fontface, fontsize, bold, fontcolor, backcolor, textalignment);
                }
            }
        }
    }
}
stock ShouldPrint(houseid, worldid) 
{
    #pragma unused houseid,worldid
    /*
    if(houseid == 478 && worldid == 1) return true;
    if(houseid == 454 && worldid == 0) return true;
    if(houseid == 437 && worldid == 0) return true;
    if(houseid == 96 && worldid == 0) return true;
    if(houseid == 156 && worldid == 1) return true;
    if(houseid == 265 && worldid == 0) return true;
    */
    return false;
}
stock PrintObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    printf("tmpobjid = CreateDynamicObject(%i,%f,%f,%f,%f,%f,%f);", modelid, x, y, z, rx, ry, rz);
}
stock PrintObjectMaterial(materialindex, modelid, const txdname[], const texturename[], materialcolor = 0)
{
    printf("SetDynamicObjectMaterial(tmpobjid,%i,%i,\"%s\",\"%s\",%i);",materialindex,modelid,txdname,texturename,materialcolor);
}
stock PrintObjectMaterialText(materialindex, const text[], materialsize = OBJECT_MATERIAL_SIZE_256x128, const fontface[] = "Arial", fontsize = 24, bold = 1, fontcolor = 0xFFFFFFFF, backcolor = 0, textalignment = 0)
{
    printf("SetDynamicObjectMaterialText(tmpobjid,%i,\"%s\",%i,\"%s\",%i,%i,%i,%i,%i);",materialindex,text,materialsize,fontface,fontsize,bold,fontcolor,backcolor,textalignment);
}

forward SQL_LoadWorldObjects();
public SQL_LoadWorldObjects()
{
    RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new row=0;
    new temp[24];
    new data[4000];
	while(row < rows)
	{
		//cache_get_row(row, 0, temp);
        new vw, slotid;
		cache_get_row(row, 0, temp), vw = strval(temp);
        cache_get_row(row, 1, temp), slotid = strval(temp);
        cache_get_row(row, 2, data);
        new Node:objJson;
        new res = JSON_Parse(data, objJson);
        if(res) 
        {
            printf("Failed parsing world object %d %d to json", vw, slotid);
        }
        else 
        {
            LoadObject(objJson, slotid, vw);
        }
		row++;
	}
    printf("Loaded %i world objects", row);
}

stock WorldPlayerDisconnect(playerid)
{
    if(!IsPlayerInWorld(playerid))
        return;
    new houseid = GetWorldHouseId(playerid);
    new worldid = GetWorldWorldid(playerid);
}

stock GetWorldHouseId(playerid)
{
    new vw = GetPlayerVirtualWorld(playerid);
    new housenumber = (vw - 100000) / 100;
    return housenumber;
}

stock GetWorldWorldid(playerid)
{
    new vw = GetPlayerVirtualWorld(playerid);
    return vw % 100;
}
stock HandleWorldClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
    if(!IsPlayerInWorld(playerid))
        return;
    new houseid = GetWorldHouseId(playerid);
    new worldid = GetWorldWorldid(playerid);
    if(Worlds[houseid][worldid][world_tpmap])
    {
        MapAndreas_FindZ_For2DCoord(fX,fY, fZ);
		if(fX > -6000.0 && fX < 6000.0 && fY > -6000.0 && fY < 6000.0 && fZ > -6000.0 && fZ < 6000.0)
		{
			if(IsPlayerInAnyVehicle(playerid))
				SetVehiclePoz(GetPlayerVehicleID(playerid),fX, fY, fZ+2.0);
			else
				SetPlayerPoz(playerid, fX, fY, fZ+1.0); 
			Surfing[playerid]=INVALID_VEHICLE_ID;
		}
    }
}
stock UpdateWorlds(playerid) // checkas chekas
{
    if(!IsPlayerInWorld(playerid))
    {
        if(WorldsTDShown[playerid])
        {
            WorldsTDShown[playerid]=0;
            TextDrawHideForPlayer(playerid, WorldsTD);
        }
        return;
    }
    if(!WorldsTDShown[playerid])
    {
        WorldsTDShown[playerid]=1;
        TextDrawShowForPlayer(playerid, WorldsTD);
    }
    new Float:Coo[3];
    new houseid = GetWorldHouseId(playerid);
    new worldid = GetWorldWorldid(playerid);
    GetPlayerPos(playerid, Coo[0], Coo[1], Coo[2]);
    if(Coo[2] < 2.0 && Worlds[houseid][worldid][world_bounds])
    {
        TeleportPlayerToWorld(playerid, houseid, worldid, /* fade= */ false);
    }
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK && Coo[2] > 100.0) 
	{
		new lr,ud,keys;
		GetPlayerKeys(playerid, keys, ud, lr);
		new Float:v[3];
        new vchanged = false;
		GetPlayerVelocity( playerid, v[0],v[1],v[2]);
		if(keys & KEY_SPRINT) 
        {
			if(v[2] < 0.1) 
            {
				v[2] = 0.3;
                vchanged = true;
			}
		}
		if(ud < 0) 
        {
			new Float:a;
			GetPlayerFacingAngle(playerid, a);
			v[0] = 0.3 * floatsin(-a, degrees);
			v[1] = 0.3 * floatcos(-a, degrees);
            vchanged = true;
		}
        if(vchanged)
		    SetPlayerVelocity(playerid, v[0],v[1],v[2]);
	}
    if(IsPlayerInAnyVehicle(playerid))
    {
        new veh = GetPlayerVehicleID(playerid);
        if(Worlds[houseid][worldid][world_autofix])
        {
		    PlayerTextDrawSetString(playerid,VehicleHP[playerid],"1000.0");
            RepairVehicleEx(veh);
        }

        if(!IsABike(veh))
        {
            if(Worlds[houseid][worldid][world_nitro])
                AddVehicleComponent(veh,1010);
        }
    }
}

stock GetWorldVirtualWorld(houseid, worldid)
{
    if(!houseid || houseid >= MAX_HOUSES || worldid >= MAX_WORLDS_PLAYER)
    {
        return 0;
    }
    return 100000 + houseid * 100 + worldid;
}

stock TeleportPlayerToWorld(playerid, houseid, worldid, fade = true)
{
    new world = GetWorldVirtualWorld(houseid, worldid);
    if(!world)
        return;
    
    if(fade)
        SetPlayerPosFade(playerid,20,Worlds[houseid][worldid][start_pos][0], Worlds[houseid][worldid][start_pos][1], Worlds[houseid][worldid][start_pos][2], /* interior=*/ 0, world);
    else
    {
        if(IsPlayerInAnyVehicle(playerid))
        {
            SetVehiclePoz(GetPlayerVehicleID(playerid),Worlds[houseid][worldid][start_pos][0], Worlds[houseid][worldid][start_pos][1], Worlds[houseid][worldid][start_pos][2]);
        }
        else
        {
            SetPlayerPoz(playerid, Worlds[houseid][worldid][start_pos][0], Worlds[houseid][worldid][start_pos][1], Worlds[houseid][worldid][start_pos][2], /* interior=*/ 0, world, 1);
        }
    }
    SendInfoMessage(playerid, "Noredami iseiti is pasaulio spauskite ~r~~k~~CONVERSATION_NO~");
}

stock TeleportPlayerFromWorld(playerid, fade = true) 
{
    if(!IsPlayerInWorld(playerid))
        return;
    new housenumber = GetWorldHouseId(playerid);
    if(fade)
        SetPlayerPosFade(playerid,25,Inter[ hInfo[housenumber][vidus] ][ IntX ],Inter[ hInfo[housenumber][vidus] ][ IntY ],Inter[ hInfo[housenumber][vidus] ][ IntZ ],Inter[ hInfo[housenumber][vidus] ][ Int ],housenumber);
    else
        SetPlayerPoz(playerid, Inter[ hInfo[housenumber][vidus] ][ IntX ],Inter[ hInfo[housenumber][vidus] ][ IntY ],Inter[ hInfo[housenumber][vidus] ][ IntZ ],Inter[ hInfo[housenumber][vidus] ][ Int ],housenumber, 1);
}

stock OpenWorldsMenu(playerid)
{
    new housenumber = GetPlayerHouseID(playerid);
	if(!housenumber) 
	{
		return 1;
	}
    for(new worldid; worldid < MAX_WORLDS_PLAYER; worldid++)
    {
        if(Worlds[housenumber][worldid][world_loaded])
        {
            new worldItem[256];
            format(worldItem,256, "%i\t{6799f0}%s\t%i",worldid+1, Worlds[housenumber][worldid][world_title], Worlds[housenumber][worldid][world_objects_count]);
            AddDListItem(playerid, worldItem, worldid);
        }
    }

    if(strcmp(hInfo[housenumber][Name],ReturnName(playerid),false)==0) 
    {
        AddDListItem(playerid, "{f55742}Naujas pasaulis", 1001);
    }
   
    ShowPlayerDListHeader(playerid, 2793, "Pasauliai", "Rinktis", "Atgal", "ID\tPavadinimas\tObjektai");
    return 1;
}

stock IsPlayerInWorld(playerid)
{
    return GetPlace(playerid, /* houses=*/ false) == PLACE_WORLD;
}

stock IsWorldOwner(playerid)
{
    if(!IsPlayerInWorld(playerid))
        return false;
    new houseid = GetWorldHouseId(playerid);
    new isOwner = strcmp(hInfo[houseid][Name],ReturnName(playerid),false)==0;
    return isOwner;
}

stock IsWorldEditor(playerid)
{
    if(!IsPlayerInWorld(playerid))
        return false;
    if(IsWorldOwner(playerid))
        return true;
    new houseid = GetWorldHouseId(playerid);
    new worldid = GetWorldWorldid(playerid);
    new pname[24];
    GetPlayerName(playerid, pname,24);
    new editors[3][24];
    if(strlen(Worlds[houseid][worldid][world_editors]) == 0)
        return false;
    sscanf(Worlds[houseid][worldid][world_editors], "p<,>S()[24]S()[24]S()[24]", editors[0],editors[1],editors[2]);
    for(new i=0;i<3;i++)
    {
        if(strlen(editors[i]) > 0 && strcmp(editors[i], pname, true) == 0)
            return true;
    }
    return false;
}

stock CancelWorldEdit(playerid)
{
    CancelEdit(playerid);
    if(!IsPlayerInWorld(playerid))
        return;
    SetPVarInt(playerid, "EditingID", 0);
}

stock OpenInWorldMenu(playerid)
{
    if(!IsPlayerInWorld(playerid))
        return;
    CancelWorldEdit(playerid);
    if(IsWorldEditor(playerid))
    {
        AddDListItem(playerid, "Statybos", 2);
    }
    new isOwner = IsWorldOwner(playerid);
    new houseid = GetWorldHouseId(playerid);
    new worldid = GetWorldWorldid(playerid);
    if(isOwner)
    {
        AddDListItem(playerid, "Nustatymai", 3);
    }
    if(isOwner || Worlds[houseid][worldid][world_cars])
    {
        AddDListItem(playerid, "Automobiliai", 4);
    }
    if(isOwner || Worlds[houseid][worldid][world_guns])
    {
       // AddDListItem(playerid, "Ginklai", 5);
    }
    if(isOwner || Worlds[houseid][worldid][world_jetpack])
    {
        AddDListItem(playerid, "Jetpack", 6);
    }
    AddDListItem(playerid, "Teleportai", 1);
    AddDListItem(playerid, "{f55742}Iðeiti", 0);
    ShowPlayerDList(playerid, 2974, "Pasaulis", "Rinktis", "Atgal");
}

stock GetFreeWorldId(houseid)
{
    for(new i;i<MAX_WORLDS_PLAYER;i++)
    {
        if(!Worlds[houseid][i][world_loaded])
        {
            return i;
        }
    }
    return -1;
}

stock GetFreeObjectSlot(houseid, worldid)
{
    for(new i;i<MAX_WORLD_OBJECTS;i++)
    {
        if(WorldObjects[houseid][worldid][i] == 0)
        {
            return i;
        }
    }
    return -1;
}

stock HandleInHouseDialog(playerid, itemid)
{
    new houseid = GetPlayerHouseID(playerid);
    if(!houseid)
        return 1;
    if(playerDB[playerid][ant] || GetPlayerWantedLevel(playerid) >=1) return SendInfoMessage(playerid,"~r~Jus gaudomas policijos!");
    if(itemid == 1001)
    {
        new worldid = GetFreeWorldId(houseid);
        if(worldid == -1)
        {
            return SendInfoMessage(playerid, "~r~Nebera vietos naujiems pasauliams!");
        }
        new const PasaulioName[][] = 
        {
            "Pirmas pasaulis",
            "Antras pasaulis",
            "Treèias pasaulis",
            "Ketvirtas pasaulis",
            "Penktas pasaulis",
            "Ðeðtas pasaulis",
            "Septintas pasaulis",
            "Aðtuntas pasaulis",
            "Devintas pasaulis",
            "Deðimtas pasaulis"
        };
        InitWorld(houseid, worldid);
        if(worldid < sizeof(PasaulioName)) 
        {
            format(Worlds[houseid][worldid][world_title], 24, PasaulioName[worldid]);
        }
        SaveWorld(houseid, worldid);
        TeleportPlayerToWorld(playerid, houseid, worldid);
        SendClientMessageLT(playerid, -1, "Sukurei naujà pasaulá!");
    }
    else 
    {
        TeleportPlayerToWorld(playerid, houseid, itemid);
    }
    return 1;
}

stock InitWorld(houseid, worldid) 
{
    if(Worlds[houseid][worldid][world_loaded])
    {
        printf("error init world");
        return;
    }
    Worlds[houseid][worldid][world_loaded] = true;
    Worlds[houseid][worldid][start_pos][0] = BASE_X;
    Worlds[houseid][worldid][start_pos][1] = BASE_Y;
    Worlds[houseid][worldid][start_pos][2] = BASE_Z;
    Worlds[houseid][worldid][world_objects_count] = 0;
    format(Worlds[houseid][worldid][world_title], 24, "Naujas pasaulis");
    Worlds[houseid][worldid][world_jetpack] = 1;
    Worlds[houseid][worldid][world_guns] = 1;
    Worlds[houseid][worldid][world_cars] = 1;
    Worlds[houseid][worldid][world_autofix] = 1;
    Worlds[houseid][worldid][world_nitro] = 1;
    Worlds[houseid][worldid][world_bounds] = 1;
    Worlds[houseid][worldid][world_respawn] = 1;
    Worlds[houseid][worldid][world_tpplayer] = 1;
    Worlds[houseid][worldid][world_tpmap] = 1;
    Worlds[houseid][worldid][world_safezone] = 0;
}

stock HandleInWorldDialog(playerid, dialog, itemid)
{
    if(!IsPlayerInWorld(playerid))
        return;
    new houseid = GetWorldHouseId(playerid);
    new worldid = GetWorldWorldid(playerid);
    if(dialog == 2974) // main menu
    {
        if(itemid == 0)
        {
            TeleportPlayerFromWorld(playerid);
        }
        else if(itemid == 1)
        {
            AddDListItem(playerid, "Á spawn taðkà", 1000);
            if(Worlds[houseid][worldid][world_tpplayer])
            {
                new world = GetPlayerVirtualWorld(playerid);
                foreach(Player, i)
                {
                    if(GetPlayerVirtualWorld(i) == world) // && i != playerid
                    {
                        new msg[256];
                        format(msg,256,"Pas {6799f0}%s",ReturnName(i));
                        AddDListItem(playerid, msg, i);
                    }
                }
            }
            ShowPlayerDList(playerid, 2975, "Teleportai", "Rinktis", "Atgal");
        }
        else if(itemid == 2)
        {
            ShowPlayerDialog(playerid, 2799, DIALOG_STYLE_LIST, "Statybos", "Statyti objektà\nRedaguoti objektà\nKeisti objekto parametrus\nKeisti objekto tekstûras\nKlonuoti objekta\nIðtrinti objektà", "Gerai", "Atgal");
        }
        else if(itemid == 3)
        {
            new settings[4096];
            new Float:Coo[3];
            GetPlayerPos(playerid, Coo[0],Coo[1],Coo[2]);
            
            new Float:dist = 
                GetDistanceBetweenPoints(Coo[0],Coo[1],Coo[2],Worlds[houseid][worldid][start_pos][0],Worlds[houseid][worldid][start_pos][1],Worlds[houseid][worldid][start_pos][2]);
            format(settings,4096, "Nustatymas\tReikðmë\n\
            Pasaulio pavadinimas\t{6799f0}%s\n\
            Atsiradimo taðkas\t{6799f0}Uþ %.1fm\n\
            Statybø leidimai\t{6799f0}%s\n\
            Jetpack\t{6799f0}%s\n\
            Automobiliai\t{6799f0}%s\n\
            Automobilio remontas\t{6799f0}%s\n\
            Nitro\t{6799f0}%s\n\
            Respawn ákritus á vandená\t{6799f0}%s\n\
            Respawn numirus\t{6799f0}%s\n\
            Teleport pas þaidëjus\t{6799f0}%s\n\
            Teleport þemëlapyje\t{6799f0}%s\n\
            Saugi zona\t{6799f0}%s\n\
            {f55742}Trinti pasaulá", 
                Worlds[houseid][worldid][world_title], 
                dist,
                Worlds[houseid][worldid][world_editors],
                SettingValue(Worlds[houseid][worldid][world_jetpack]),
                SettingValue(Worlds[houseid][worldid][world_cars]),
                SettingValue(Worlds[houseid][worldid][world_autofix]),
                SettingValue(Worlds[houseid][worldid][world_nitro]),
                SettingValue(Worlds[houseid][worldid][world_bounds]),
                SettingValue(Worlds[houseid][worldid][world_respawn]),
                SettingValue(Worlds[houseid][worldid][world_tpplayer]),
                SettingValue(Worlds[houseid][worldid][world_tpmap]),
                SettingValue(Worlds[houseid][worldid][world_safezone])
            );

            ShowPlayerDialog(playerid, 2795, DIALOG_STYLE_TABLIST_HEADERS, "Nustatymai", settings, "Keisti", "Atgal");
        }
        else if(itemid == 4)
        {
            new autolist[5000];
            new lastmodel = GetPVarInt(playerid, "Lastcarmodel");
            if(lastmodel)
                format(autolist,5000,"Paskutinis\t{FF0000}%s\n",aVehicleNames[lastmodel-400][Name]);
            else
                format(autolist,5000,"Automobiliai:\t \n");
            for(new i=0; i<sizeof(aVehicleNames); i++)
            {
                format(autolist,5000,"%s%i\t%s\n",autolist,400+i,aVehicleNames[i][Name]);
            }
            ShowPlayerDialog(playerid, 2806, DIALOG_STYLE_TABLIST, "Pasaulis", autolist, "Gerai", "Atgal");
        }
        else if(itemid == 5)
        {
            SendClientMessageLT(playerid, -1, "Ginklai");
        }
        else if(itemid == 6)
        {
            SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USEJETPACK);
        }
    }
    if(dialog == 2975) // teleports
    {
        if(itemid == 1000)
        {
            TeleportPlayerToWorld(playerid, houseid, worldid, /* fade= */ false);
        }
        else
        {
            if(!IsPlayerConnected(itemid) || GetPlayerVirtualWorld(itemid) != GetPlayerVirtualWorld(playerid))
            {
                SendInfoMessage(playerid, "~r~Zaidejo nebera siame pasaulyje!");
                return;
            }
            new Float:coo[3];
            GetPlayerPos(itemid, coo[0],coo[1],coo[2]);
            coo[2]+=3.0;
            coo[1]+=0.5;
            if(IsPlayerInAnyVehicle(playerid))
            {
                SetVehiclePoz(GetPlayerVehicleID(playerid),coo[0],coo[1],coo[2]);
            }
            else
            {
                SetPlayerPoz(playerid,coo[0],coo[1],coo[2]);
            }
        }
    }
    if(dialog == 2795) // nustatymai
    {
        if(itemid == 0)
        {
            ShowPlayerDialog(playerid, 2796, DIALOG_STYLE_INPUT, "Pasaulis", "Áraðykite naujà pasaulio pavadinimà iki 20 simboliø.", "Gerai", "Atgal");
        }
        else if(itemid == 1)
        {
            ShowPlayerDialog(playerid, 2798, DIALOG_STYLE_LIST, "Pasaulis", "Nustatyti naujà spawn pointà èia\nAtstatyti originalø spawn pointà", "Gerai", "Atgal");
        }
        else if(itemid == 2)
        {
            ShowPlayerDialog(playerid, 2805, DIALOG_STYLE_INPUT, "Pasaulis", "Áraðykite þaidëjo vardà, kuriam norite duoti statybø leidimà.\n\n\
            Noredami nuimti visus statybø leidimus palikite ðá laukelá tuðèià.\nGalite áraðyti iki trijø þaidëjø vardø, kuriems norite suteikti leidimus. Pvz.: {FFFFFF}Pirmas_Zaidejas,Antras_Zaidejas,Trecias_Zaidejas", "Gerai", "Atgal");
        }
        else if(itemid == 3)
        {
            Worlds[houseid][worldid][world_jetpack] = 1 - Worlds[houseid][worldid][world_jetpack];
            SaveWorld(houseid,worldid);
            HandleInWorldDialog(playerid, 2974, 3);
        }
        else if(itemid == 4)
        {
            Worlds[houseid][worldid][world_cars] = 1 - Worlds[houseid][worldid][world_cars];
            SaveWorld(houseid,worldid);
            HandleInWorldDialog(playerid, 2974, 3);
        }
        else if(itemid == 5)
        {
            Worlds[houseid][worldid][world_autofix] = 1 - Worlds[houseid][worldid][world_autofix];
            SaveWorld(houseid,worldid);
            HandleInWorldDialog(playerid, 2974, 3);
        }
        else if(itemid == 6)
        {
            Worlds[houseid][worldid][world_nitro] = 1 - Worlds[houseid][worldid][world_nitro];
            SaveWorld(houseid,worldid);
            HandleInWorldDialog(playerid, 2974, 3);
            new vehicleid = GetPlayerVehicleID(playerid);
            if(vehicleid && !IsABike(vehicleid))
            {
                if(Worlds[houseid][worldid][world_nitro])
			        AddVehicleComponent(vehicleid,1010);
                else
                    RemoveVehicleComponent(vehicleid, 1010);
            }
        }
        else if(itemid == 7)
        {
            Worlds[houseid][worldid][world_bounds] = 1 - Worlds[houseid][worldid][world_bounds];
            SaveWorld(houseid,worldid);
            HandleInWorldDialog(playerid, 2974, 3);
        }
        else if(itemid == 8)
        {
            Worlds[houseid][worldid][world_respawn] = 1 - Worlds[houseid][worldid][world_respawn];
            SaveWorld(houseid,worldid);
            HandleInWorldDialog(playerid, 2974, 3);
        }
        else if(itemid == 9)
        {
            Worlds[houseid][worldid][world_tpplayer] = 1 - Worlds[houseid][worldid][world_tpplayer];
            SaveWorld(houseid,worldid);
            HandleInWorldDialog(playerid, 2974, 3);
        }
        else if(itemid == 10)
        {
            Worlds[houseid][worldid][world_tpmap] = 1 - Worlds[houseid][worldid][world_tpmap];
            SaveWorld(houseid,worldid);
            HandleInWorldDialog(playerid, 2974, 3);
        }
        else if(itemid == 11)
        {
            Worlds[houseid][worldid][world_safezone] = 1 - Worlds[houseid][worldid][world_safezone];
            SaveWorld(houseid,worldid);
            HandleInWorldDialog(playerid, 2974, 3);
        }
        else
        {
            ShowPlayerDialog(playerid, 2797, DIALOG_STYLE_MSGBOX, "Pasaulis", "Ar tikrai norite iðtrinti ðá pasaulá?", "Taip", "Ne");
        }
    }
    if(dialog == 2797) // delete world
    {
        if(!IsWorldOwner(playerid))
        {
            return;
        }
        TeleportPlayerFromWorld(playerid);
        SendInfoMessage(playerid, "~r~Istrynei pasauli!");
        DeleteWorld(houseid, worldid);
    }
    if(dialog == 2798) // spawn point
    {
        if(!IsWorldOwner(playerid))
        {
            return;
        }
        if(itemid == 0)
        {
            new Float:Coo[3];
            GetPlayerPos(playerid, Coo[0],Coo[1],Coo[2]);
            Worlds[houseid][worldid][start_pos][0] = Coo[0]; 
            Worlds[houseid][worldid][start_pos][1] = Coo[1]; 
            Worlds[houseid][worldid][start_pos][2] = Coo[2]; 
        }
        else
        {
            Worlds[houseid][worldid][start_pos][0] = BASE_X;
            Worlds[houseid][worldid][start_pos][1] = BASE_Y;
            Worlds[houseid][worldid][start_pos][2] = BASE_Z;
        }
        SendInfoMessage(playerid,"~g~Nustatei nauja spawn!");
        SaveWorld(houseid, worldid);
    }
    if(dialog == 2799) // statybos
    {
        if(!IsWorldEditor(playerid))
            return;
        if(itemid == 0) 
        {
            ShowPlayerDialog(playerid, 2800, DIALOG_STYLE_LIST, "Statybos", "Ávesti objekto modelá\nNaudotis paieðka\nRinktis ið visø objektø (1 dalis)\nRinktis ið visø objektø (2 dalis)\nRinktis ið visø objektø (3 dalis)\nRinktis ið visø objektø (4 dalis)\nRinktis ið visø objektø (5 dalis)", "Gerai", "Atgal");
        }
        if(itemid == 1)
        {
            SetPVarInt(playerid, "selecttype", 1);
            ShowPlayerDialog(playerid, 2803, DIALOG_STYLE_LIST, "Statybos", "Pasirinkti objektà redagavimui\nRedaguoti pagal objekto ID", "Gerai", "Atgal");
        }
        if(itemid == 2)
        {
            SetPVarInt(playerid, "selecttype", 3);
            ShowPlayerDialog(playerid, 2803, DIALOG_STYLE_LIST, "Statybos", "Pasirinkti objektà parametrø keitimui\nKeisti parametrus pagal objekto ID", "Gerai", "Atgal");
        }
        if(itemid == 3)
        {
            SetPVarInt(playerid, "selecttype", 5);
            ShowPlayerDialog(playerid, 2803, DIALOG_STYLE_LIST, "Statybos", "Pasirinkti objektà tekstûrø keitimui\nKeisti tekstûras pagal objekto ID", "Gerai", "Atgal");
        }
        if(itemid == 4)
        {
            SetPVarInt(playerid, "selecttype", 4);
            ShowPlayerDialog(playerid, 2803, DIALOG_STYLE_LIST, "Statybos", "Pasirinkti objektà klonavimui\nKlonuoti pagal objekto ID", "Gerai", "Atgal");
        }
        if(itemid == 5)
        {
            SetPVarInt(playerid, "selecttype", 2);
            ShowPlayerDialog(playerid, 2803, DIALOG_STYLE_LIST, "Statybos", "Pasirinkti objektà iðtrinimui\nIðtrinti pagal objekto ID", "Gerai", "Atgal");
        }
    }
    if(dialog == 2800) // statyti objekta
    {
        if(!IsWorldEditor(playerid))
            return;
        if(itemid == 0) // pagal id
        {
            ShowPlayerDialog(playerid, 2801, DIALOG_STYLE_INPUT, "Statybos", "Áveskite objekto modelá.", "Gerai", "Atgal");
        }
        if(itemid == 1)
        {
             ShowPlayerDialog(playerid, 2802, DIALOG_STYLE_INPUT, "Statybos", "Áveskite paieðkos terminà. Pavyzdþiai:\n\n\
{ffffff} - {60CE65}fence\n\
{ffffff} - {60CE65}wall\n\
{ffffff} - {60CE65}pipe\n\
{ffffff} - {60CE65}road\n\
{ffffff} - {60CE65}house", "Gerai", "Atgal");
        }
        if(itemid == 2)
        {
            ShowItemCatalog(playerid, "", /* part= */ 1);
        }
        if(itemid == 3)
        {
            ShowItemCatalog(playerid, "", /* part= */ 2);
        }
        if(itemid == 4)
        {
            ShowItemCatalog(playerid, "", /* part= */ 3);
        }
        if(itemid == 5)
        {
            ShowItemCatalog(playerid, "", /* part= */ 4);
        }
        if(itemid == 6)
        {
            ShowItemCatalog(playerid, "", /* part= */ 5);
        }
    }
    if(dialog == 2803) // redagavimas
    {
        if(itemid == 0)
        {
            SetTimerEx("Selectint",750,false,"i",playerid);
            SendInfoMessage(playerid, "Pasirinkimo rezima galite isjungti paspaude ~r~ESC~w~~n~Vaizda sukioti galite laikydami ~r~~k~~PED_SPRINT~");
        }
        if(itemid == 1)
        {
            new msg[4096];
            new selectType = GetPVarInt(playerid, "selecttype");
            new const editactions[][] = {"?","redaguoti","iðtrinti","keisti","klonuoti","pakeisti"};
            format(msg,sizeof(msg), "{FFFFFF}Áveskite objekto ID kurá norite {6799f0}%s{FFFFFF}.\n\n\n\nPrie jûsø esantys objektai:\n\n",editactions[selectType]);

            FillClosestObjArray(playerid);
            for(new i;i<10;i++)
            {
                if(closestobjs[i][closestobjslot] != -1 && closestobjs[i][closestobjdist] < 300.0)
                {
                    new slot = closestobjs[i][closestobjslot];
                    new obj = WorldObjects[houseid][worldid][slot];
                    new model = Streamer_GetIntData(STREAMER_TYPE_OBJECT,obj,E_STREAMER_MODEL_ID);
                    format(msg,sizeof(msg),"%s - {FF0000}%i {daf7ad}%s {FFFFFF}(%.1fm)\n",msg, slot, smartSearch(model), closestobjs[i][closestobjdist]);
                }
            }
            ShowPlayerDialog(playerid, 2804, DIALOG_STYLE_INPUT, "Pasirinkimas", msg,"Gerai", "Atsaukti");
        }
    }
    if(dialog == 2806) // auto
    {
        if(itemid >= 213 || itemid < 0)
            return;

        new model = 400 + itemid - 1;
        if(itemid == 0)
        {
            if(GetPVarInt(playerid,"Lastcarmodel"))
                model = GetPVarInt(playerid,"Lastcarmodel");
            else 
            {
                HandleInWorldDialog(playerid, 2974, 4);
                return;
            }
        }
        // disable some trains
        if(model == 449 || model == 537 || model == 538 || model == 569 || model == 570 || model == 590)
        {
            SendInfoMessage(playerid, "~r~Sio transporto imti negalima");
            return;
        }
        DestroyOldCar(playerid);
        new col = random(255);
        new vehicleid = CreateVehicle(model,0.0,0.0,0.0,0.0,col,1,-1);
        PlayerCar[playerid] = vehicleid;
        OnVehicleSpawn(vehicleid);
        SetVehicleNumberPlate(vehicleid,"{00630f}PASAULIAI");
        SetVehicleToRespawn(vehicleid);
        SetVehicleNumberPlate(vehicleid,"{00630f}PASAULIAI");
        SetVehicleParamsEx(vehicleid,false,-1,-1,-1,-1,-1,-1);
        //SetPVarInt(id, "iseventcar", 1);
        //if(oldrida > 0)
        //	vehicleDB[PlayerCar[id]][rida]=oldrida;
        vehicleDB[vehicleid][rida]=0.0;
        vehicleDB[vehicleid][gas]=100.0;
        vehicleDB[vehicleid][energy]=50.0;
        vehicleDB[vehicleid][OldHP]=1000.0;
        vehicleDB[vehicleid][norida]=1;
        
		format(vehicleDB[vehicleid][nuomuoja],24,"no");
		format(vehicleDB[vehicleid][lastuser],MAX_PLAYER_NAME,ReturnName(playerid));
        new world=GetPlayerVirtualWorld(playerid);
        new int=GetPlayerInterior(playerid);
        new Float:Coo[4];
        GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
        GetPlayerFacingAngle(playerid,Coo[3]);
        //vehicleid = CreateVehicle(DarbinesCar[job][car][DCmodel],DarbinesCar[job][car][DCX],DarbinesCar[job][car][DCY],DarbinesCar[job][car][DCZ],DarbinesCar[job][car][DCR],DarbinesCar[job][car][DCcolor1],DarbinesCar[job][car][DCcolor2],-3);
        SetVehiclePos(vehicleid,Coo[0],Coo[1],Coo[2]);
        SetVehicleZAngle(vehicleid,Coo[3]);
        TogglePlayerControllable(playerid,true);
        if(!RogesActive[playerid])
            LinkVehicleToInterior(vehicleid,int);
        SetVehicleVirtualWorld(vehicleid,world);
        PutPlayerInVehicleEx(playerid,vehicleid,0);
        SendClientMessageLT(playerid,GREEN," * Gavote pasaulio automobili.");
        playerInEventCar[playerid]=2;
        if(Worlds[houseid][worldid][world_nitro] && !IsABike(vehicleid))
			AddVehicleComponent(GetPlayerVehicleID(playerid),1010);
        SetPVarInt(playerid, "Lastcarmodel", model);
    }
    if(dialog == 2807)
    {
        SetPVarInt(playerid,"SelectedParam", itemid);
        ShowPlayerDialog(playerid,2808, DIALOG_STYLE_INPUT,"Parametrai", "Iveskite nauja parametro reiksme.", "Gerai", "Atgal");
    }
    if(dialog == 2976)
    {
        new selectedid = GetPVarInt(playerid, "SelectedObj");
        if(!selectedid)
             return;
        new slot = GetWorldObjectSlot(houseid, worldid, selectedid);
        if(slot == -1)
            return;
        if(itemid == 0)
        {
            SetPVarInt(playerid, "dazymas", 1);
            SendClientMessageLT(playerid, ORANGE, " * Tekstûras gali rinktis paspaudæs Y ir N klaviðus. Iðsirinkæs spausk ENTER");
            SendClientMessageLT(playerid, ORANGE, " * Jei þinai tekstûros ID gali naudoti /tekstura [id]");
        }
        if(itemid == 1)
        {
            RemoveDynamicObjectMaterial(selectedid,GetPVarInt(playerid, "matid"));
            SendInfoMessage(playerid, "Istrynei!");
            SaveWorldObject(houseid,worldid,slot);
            SelectedWorldMat(playerid);
        }
        if(itemid == 2)
        {
            ShowPlayerDialog(playerid, 2977, DIALOG_STYLE_INPUT, "Spalva", "Áveskite HEX spalvos kodà.\n\n\nPavyzdþiai:\n\
            {FFFFFF} FFFFFF\n\
            {000000} 000000\n\
            {FF0000} FF0000\n\
            {00FF00} 00FF00\n\
            {0000FF} 0000FF\n", "Rinktis", "Atsaukti");
        }
        if(itemid == 3)
        {
            ShowPlayerDialog(playerid, 2978, DIALOG_STYLE_INPUT, "Spalva", "Áveskite spalvos ryðkumà nuo 0 iki 115", "Rinktis", "Atsaukti");
        }
        if(itemid == 4)
        {
            ShowPlayerDialog(playerid, 2979, DIALOG_STYLE_INPUT, "Tekstas", "Áveskite savo tekstà.\n\nGalite naudoti hax spalvø kodus, pvz.: { 00FF00 }{00ff00}þalias tekstas", "Rinktis", "Atsaukti");
        }
        if(itemid == 5)
        {
            RemoveDynamicObjectMaterialText(selectedid,GetPVarInt(playerid, "matid"));
            SendInfoMessage(playerid, "Istrynei!");
            SaveWorldObject(houseid,worldid,slot);
            SelectedWorldMat(playerid);
        }
    }
}
stock ValidateColorStr(inputstr[])
{
    if(strlen(inputstr) != 6)
    {
        return false;
    }
    for(new i;i<6;i++)
    {
        if(inputstr[i] >= '0' && inputstr[i] <= '9')
            continue;
        if(inputstr[i] >= 'a' && inputstr[i] <= 'f')
            continue;
        if(inputstr[i] >= 'A' && inputstr[i] <= 'F')
            continue;
        return false;
    }
    return true;
}
stock HandleWorldTextDialog(playerid, dialog, text[])
{
    if(!IsPlayerInWorld(playerid))
        return;
    new houseid = GetWorldHouseId(playerid);
    new worldid = GetWorldWorldid(playerid);
    new selectedid = GetPVarInt(playerid, "SelectedObj");
    if(!selectedid)
        return;
    new matid = GetPVarInt(playerid, "matid");
    new slot = GetWorldObjectSlot(houseid, worldid, selectedid);
    if(slot == -1)
        return;
    if(dialog == 2977)
    {
        if(!ValidateColorStr(text))
        {
            SendInfoMessage(playerid, "~r~Netinkamas formatas");
            SelectedWorldMat(playerid);
            return;
        }
        new colorstr[16];
        format(colorstr,16,"0xFF%s",text);

        new modelid, txdname[100], texturename[100], materialcolor;
        GetDynamicObjectMaterial(selectedid, matid, modelid, txdname, texturename, materialcolor);
        new newcolor;
        sscanf(colorstr, "x", newcolor);
        SetDynamicObjectMaterial(selectedid, matid, modelid, txdname, texturename, newcolor);
        SaveWorldObject(houseid,worldid,slot);
        SendInfoMessage(playerid, "Nustatei!");
        SelectedWorldMat(playerid);
    }
    if(dialog == 2978)
    {
        new value = strval(text);
        if(value < 0 || value > 115)
        {
            SendInfoMessage(playerid, "~r~Netinkamas formatas");
            SelectedWorldMat(playerid);
            return;
        }
        value += 140; // first 140 colors are invisible
        new modelid, txdname[100], texturename[100], materialcolor;
        GetDynamicObjectMaterial(selectedid, matid, modelid, txdname, texturename, materialcolor);
        new newcolor = (materialcolor & 0x00FFFFFF) + ((value << 24) & 0xFF000000);
        SetDynamicObjectMaterial(selectedid, matid, modelid, txdname, texturename, newcolor);
        SaveWorldObject(houseid,worldid,slot);
        SendInfoMessage(playerid, "Nustatei!");
        SelectedWorldMat(playerid);
    }
    if(dialog == 2979)
    {
        if(strlen(text) < 1 || strlen(text) > 1024)
        {
            SendInfoMessage(playerid, "~r~Netinkamas formatas");
            SelectedWorldMat(playerid);
            return;
        }
        /*if(IsDynamicObjectMaterialTextUsed(selectedid, matid))
        {
            GetDynamicObjectMaterialText(STREAMER_TAG_OBJECT:objectid, materialindex, text[], &materialsize, fontface[], &fontsize, &bold, &fontcolor, &backcolor, &textalignment, maxtext = sizeof text, maxfontface = sizeof fontface);
        }
        else
        {
             SetDynamicObjectMaterialText(STREAMER_TAG_OBJECT:objectid, materialindex, const text[], materialsize = OBJECT_MATERIAL_SIZE_256x128, const fontface[] = "Arial", fontsize = 24, bold = 1, fontcolor = 0xFFFFFFFF, backcolor = 0, textalignment = 0)
        }*/
        SetDynamicObjectMaterialText(selectedid, matid, text);
        SaveWorldObject(houseid,worldid,slot);
        SendInfoMessage(playerid, "Nustatei!");
        SelectedWorldMat(playerid);
    }
}

stock EditWorldTextures(playerid)
{
    new selectedid = GetPVarInt(playerid, "SelectedObj");
    if(!selectedid)
        return;
    SetPVarInt(playerid, "matid", 0);
    SetPVarInt(playerid, "choosingmat", 1);
    SendClientMessageLT(playerid, ORANGE, " * Objekto dalis gali rinktis paspaudæs Y ir N klaviðus. Iðsirinkæs spausk ENTER");
	SendClientMessageLT(playerid, ORANGE, " * Pasirinkta objekto dalis bus paþymëta raudonai.");
	SendClientMessageLT(playerid, ORANGE, " * Objektai turi daug skirtingø daliø ir jûsø pasirinktas objektas gali neturëti visø 16.");
    TexturizeWorldObject(playerid, GetPVarInt(playerid,"SelectedObj"),GetPVarInt(playerid, "matid"),8932);
}
forward SelectedWorldMat(playerid);
public SelectedWorldMat(playerid)
{
    new selectedid = GetPVarInt(playerid, "SelectedObj");
    if(!selectedid)
        return;
    ShowPlayerDialog(playerid,2976, DIALOG_STYLE_LIST, "Tekstûros", "Keisti tekstûrà\nAtstatyti originalià tekstûrà\nKeisti spalvà\nNustatyti spalvos ryðkumà\nNustatyti tekstà\nIðtrinti tekstà", "Gerai", "Atgal"); 
}
stock TexturizeWorldObject(playerid, objectid, matid, textureid)
{
    if(IsDynamicObjectMaterialUsed(objectid, matid))
    {
        new modelid, txdname[100], texturename[100], materialcolor;
        GetDynamicObjectMaterial(objectid, matid, modelid, txdname, texturename, materialcolor);
        SetPVarInt(playerid, "oldtexture", GetTextureIndex(modelid, txdname, texturename));
        SetPVarInt(playerid, "oldcolor", materialcolor);
    }
    else
    {
        SetPVarInt(playerid, "oldtexture", 0);
    }
    SetDynamicObjectMaterial(objectid, matid, GetTModel(textureid), GetTXDName(textureid), GetTextureName(textureid));
}

stock SetWorldMatTexture(playerid, newmat, oldmat)
{
    new selectedid = GetPVarInt(playerid, "SelectedObj");
    if(!selectedid)
        return;
    // reset old mat, set new mat
    new oldtexture = GetPVarInt(playerid, "oldtexture");
    if(!oldtexture)
        RemoveDynamicObjectMaterial(selectedid, oldmat);
    else
    {
        SetDynamicObjectMaterial(selectedid, oldmat, GetTModel(oldtexture), GetTXDName(oldtexture), GetTextureName(oldtexture), GetPVarInt(playerid, "oldcolor"));
    }

    TexturizeWorldObject(playerid, selectedid,newmat,8932);
}

forward SaveWorldTexture(playerid);
public SaveWorldTexture(playerid)
{
    if(!IsPlayerInWorld(playerid))
        return;
    new houseid = GetWorldHouseId(playerid);
    new worldid = GetWorldWorldid(playerid);
    new selectedid = GetPVarInt(playerid, "SelectedObj");
    if(!selectedid)
        return;
    new slot = GetWorldObjectSlot(houseid, worldid, selectedid);
    if(slot == -1)
        return;
    SetPVarInt(playerid, "dazymas", 0);
    SaveWorldObject(houseid,worldid,slot);
    ShowPlayerDialog(playerid,2976, DIALOG_STYLE_LIST, "Tekstûros", "Keisti tekstûrà\nAtstatyti originalià tekstûrà\nKeisti spalvà\nNustatyti spalvos ryðkumà\nNustatyti tekstà\nIðtrinti tekstà", "Gerai", "Atgal"); 
}

stock HandleNewParam(playerid, text[])
{
    if(!IsPlayerInWorld(playerid))
        return;
    new houseid = GetWorldHouseId(playerid);
    new worldid = GetWorldWorldid(playerid);
    new selectedid = GetPVarInt(playerid, "SelectedObj");
    new selectedparam = GetPVarInt(playerid, "SelectedParam");
    new slot = GetWorldObjectSlot(houseid, worldid, selectedid);
    if(slot == -1)
        return;
    if(selectedparam == 0) // model
    {
        if(!IsNumeric(text))
        {
            SendInfoMessage(playerid,"~r~Skaiciais!");
            HandleSelectWorldObject(playerid, selectedid);
            return;
        }
        new model = strval(text);
        if(model < 0 || model >= 20000)
        {
            SendInfoMessage(playerid,"~r~Netinkamas ID!");
            HandleSelectWorldObject(playerid, selectedid);
            return;
        }
        new objname[50];
        format(objname, 50, smartSearch(model));
        if(!strlen(objname)) 
        {
            SendInfoMessage(playerid,"~r~Objektas nerastas");
            HandleSelectWorldObject(playerid, selectedid);
            return;
        }
        Streamer_SetIntData(STREAMER_TYPE_OBJECT, selectedid, E_STREAMER_MODEL_ID, model);
        SaveWorldObject(houseid,worldid,slot);
        Streamer_Update(playerid);
        SendInfoMessage(playerid, "~g~Pakeitei!");
        HandleSelectWorldObject(playerid, selectedid);
        return;
    }
    new minValue = -10000;
    new maxValue = 10000;
    if(selectedparam == 4 || selectedparam == 5 || selectedparam == 6)
    {
        minValue = -360;
        maxValue = 360;
    }
    new Float:value;
    if(sscanf(text, "f", value))
    {
        SendInfoMessage(playerid, "~r~Netinkamas formatas");
        HandleSelectWorldObject(playerid, selectedid);
        return;
    }
    if(value > maxValue)
    {
        SendInfoMessage(playerid, "~r~Reiksme virsija didziausia leidziama!");
        HandleSelectWorldObject(playerid, selectedid);
        return;
    }
    if(value < minValue)
    {
        SendInfoMessage(playerid, "~r~Reiksme virsija maziausia leidziama!");
        HandleSelectWorldObject(playerid, selectedid);
        return;
    }
    new idx = selectedparam-1;
    new Float:Coo[6];
    GetDynamicObjectPos(selectedid, Coo[0],Coo[1],Coo[2]);
    GetDynamicObjectRot(selectedid, Coo[3],Coo[4],Coo[5]);
    Coo[idx] = value;
    SetDynamicObjectPos(selectedid, Coo[0],Coo[1],Coo[2]);
    SetDynamicObjectRot(selectedid, Coo[3],Coo[4],Coo[5]);
    SaveWorldObject(houseid,worldid,slot);
    SendInfoMessage(playerid,"~g~Pakeitei!");
    Streamer_Update(playerid);
    HandleSelectWorldObject(playerid, selectedid);
}
stock HandleObjectSelectionById(playerid, text[])
{
    if(!IsPlayerInWorld(playerid))
        return 1;
    new houseid = GetWorldHouseId(playerid);
    new worldid = GetWorldWorldid(playerid);

    if(!IsNumeric(text)) return SendInfoMessage(playerid,"~r~Skaiciais!");
    new slot = strval(text);
    if(slot < 0 || slot >= MAX_WORLD_OBJECTS)
        return SendInfoMessage(playerid,"~r~Netinkamas ID!");
    if(!WorldObjects[houseid][worldid][slot])
        return SendInfoMessage(playerid,"~r~Tokio ID nera!");
    
    HandleSelectWorldObject(playerid, WorldObjects[houseid][worldid][slot]);
    return 1;
}
stock SettingValue(val)
{
    new const res[][10] = {"OFF", "ON", "unknown"};
    if(val != 0 && val != 1)
        return res[2];
    return res[val];
}
stock SetStatybuLeidimas(playerid,inputstr[])
{
    if(!IsPlayerInWorld(playerid))
        return;
    new houseid = GetWorldHouseId(playerid);
    new worldid = GetWorldWorldid(playerid);
    if(!IsWorldOwner(playerid))
        return;
    if(strlen(inputstr) >= 99)
    {
        SendInfoMessage(playerid, "~r~Netinkamas zaideju sarasas");
        return;
    }
    new commaCount = 0;
    for(new i;i<strlen(inputstr);i++)
    {
        new c = inputstr[i];
        if(c == ',')
        {
            commaCount ++;
            if(commaCount > 2) 
            {
                SendInfoMessage(playerid, "~r~Netinkamas sarasas");
                return;
            }
            continue;
        }
        if(c == ' ')
        {
            SendInfoMessage(playerid, "~r~Nenaudokite tarpu zaideju sarase");
            return;
        }
        if(c >= 65 && c <= 90) // A-Z
            continue;
        if(c>= 97 && c <= 122) // a-z
            continue;
        if(c == '_')
            continue;

        SendInfoMessage(playerid, "~r~Netinkamas Vardas_Pavarde.");
        return;
    }
    format(Worlds[houseid][worldid][world_editors], 100, inputstr);
    if(strlen(inputstr) == 0)
    {
        SendInfoMessage(playerid, "~g~Sekmingai nuemei statybu leidimus");
    }
    else
    {
        SendInfoMessage(playerid, "~g~Sekmingai suteikei statybu leidimus");
    }
    SaveWorld(houseid,worldid);
    HandleInWorldDialog(playerid, 2974, 3);
}
stock ShowItemCatalog(playerid, searchterm[], part=0)
{
    new availableObjs[20000];
    new idx = 0;
    new start = 1;
    new end = sizeof(ObjectList);
    if(part)
    {
        start = (part - 1)*2000;
        end = start + 2000;
        if(start == 0)
            start = 2; // start from 2 because there is object 0 and 320 that dont work
    }
    for(new i=start;i<end;i++) 
    {
        new find = strfind(ObjectList[i][oName], searchterm, /* ignoreCase= */ true);
        if(find != -1 || strlen(searchterm) == 0) 
        {
            availableObjs[idx] =ObjectList[i][oID];
            idx++; 
        }
    }
    if(idx == 0)
    {
        ShowPlayerDialog(playerid, 2802, DIALOG_STYLE_INPUT, "Statybos", "Áveskite paieðkos terminà. {ff0000} Nieko nerasta!", "Gerai", "Atgal");
    }
    ShowModelSelectionMenuEx(playerid, availableObjs, idx, "Pasirinkite objekta", GUI_OBJEKTAI, -15.0, 0.0, 225.0, 1.0, 0x007F05BB, 0x88888899,0xCE60C9AA);
}
stock HandlePlaceObject(playerid, objectmodel, clonefrom = -1)
{
    if(!IsPlayerInWorld(playerid))
        return;
    if(!IsWorldEditor(playerid))
        return;
    new houseid = GetWorldHouseId(playerid);
    new worldid = GetWorldWorldid(playerid);
    if(!objectmodel || objectmodel >= 20000) 
    {
        SendInfoMessage(playerid, "~r~Netinkamas objektas!");
        return;
    }
    new objname[50];
    format(objname, 50, smartSearch(objectmodel));
    if(!strlen(objname)) 
    {
        SendInfoMessage(playerid,"~r~Objektas nerastas");
        return;
    }
    new slot = GetFreeObjectSlot(houseid, worldid);
    if(slot == -1)
    {
        SendInfoMessage(playerid, "~r~Pasiektas 10,000 objektu limitas");
    }
    if(slot >= 9000)
    {
        SendInfoMessage(playerid, "~p~Artejate prie 10,000 objektu limito");
    }
    new Float:Coo[6];
    new virtualworld = GetWorldVirtualWorld(houseid, worldid);
    if(clonefrom == -1)
    {
        GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
        GetXYInFrontOfPlayer(playerid, Coo[0],Coo[1], 10.0); 
    }
    else
    {
        GetDynamicObjectPos(clonefrom, Coo[0],Coo[1],Coo[2]);
        GetDynamicObjectRot(clonefrom, Coo[3],Coo[4],Coo[5]);
    }

    new objid = CreateDynamicObject(objectmodel, Coo[0],Coo[1],Coo[2], Coo[3],Coo[4],Coo[5], virtualworld);
    WorldObjects[houseid][worldid][slot] = objid;
    Worlds[houseid][worldid][world_objects_count]++;
    if(clonefrom != -1)
    {
        for(new matid;matid < 16;matid++)
        {
            if(IsDynamicObjectMaterialUsed(clonefrom, matid))
            {
                new modelid, txdname[100], texturename[100], materialcolor;
                GetDynamicObjectMaterial(clonefrom, matid, modelid, txdname, texturename, materialcolor);
                SetDynamicObjectMaterial(objid, matid, modelid, txdname, texturename, materialcolor);
            }
            if(IsDynamicObjectMaterialTextUsed(clonefrom, matid))
            {
                new text[2048], materialsize, fontface[200], fontsize, bold, fontcolor, backcolor, textalignment;
                GetDynamicObjectMaterialText(clonefrom, matid, text, materialsize, fontface, fontsize, bold, fontcolor, backcolor, textalignment);
                SetDynamicObjectMaterialText(objid, matid,text, materialsize, fontface, fontsize, bold, fontcolor, backcolor, textalignment);
            }
        }
    }

    Streamer_Update(playerid);
    new msg[256];
    format(msg,256," * Sukurei objekta! Modelis: {FF0000}%i{FFFFFF} Pavadinimas: {FF0000}%s{FFFFFF} ID: {FF0000}%i{FFFFFF}.",objectmodel,objname,slot);
    SendClientMessageLT(playerid, -1, msg);
    SaveWorldObject(houseid,worldid,slot);
    SetPVarInt(playerid, "EditingID", objid);
    SetTimerEx("EditBaldas",1000,false,"ii",playerid,objid);

    /*new Float:Coo[3];
    new Float:Xoo[3];

    GetDynamicObjectPos(obj,Xoo[0],Xoo[1],Xoo[2]);
    
    GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
    GetXYInFrontOfPlayer(playerid, Coo[0],Coo[1], 1.9); //1221
    new Float:Dist = GetDistanceBetweenPoints(Coo[0],Coo[1],Coo[2],Xoo[0],Xoo[1],Xoo[2]);

    //Coo[2]+=1.0;
    if(Dist > 15.0)
        SetDynamicObjectPos(obj, Coo[0]+0.5,Coo[1],Coo[2]-0.5);*/
}
stock HandleSelectWorldObject(playerid, objectid)
{
    if(!IsPlayerInWorld(playerid))
        return;
    if(!IsWorldEditor(playerid))
        return;
    new houseid = GetWorldHouseId(playerid);
    new worldid = GetWorldWorldid(playerid);
    new slotid = GetWorldObjectSlot(houseid, worldid, objectid);
    if(slotid == -1)
        return;
    new selectType = GetPVarInt(playerid, "selecttype");
    if(selectType == 1) // edit
    {
        foreach(Player, i)
        {
            if(GetPVarInt(i,"EditingID") == objectid && i != playerid) 
            {
                SendInfoMessage(playerid,"Si objekta siuo metu redaguoja kitas zaidejas");
                return;
            }
        }
        SetPVarInt(playerid, "EditingID", objectid);
        EditDynamicObject(playerid, objectid);
        SendInfoMessage(playerid, "Redagavimo rezima galite isjungti paspaude ~r~ESC~w~~n~Vaizda sukioti galite laikydami ~r~~k~~PED_SPRINT~");
        return;
    }
    if(selectType == 2) // delete
    {
        PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
        foreach(Player, i)
        {
            if(GetPVarInt(i,"EditingID") == objectid && i != playerid) 
            {
                SendInfoMessage(playerid,"Si objekta siuo metu redaguoja kitas zaidejas");
                return;
            }
        }
        DeleteWorldObject(houseid, worldid, slotid);
        SendInfoMessage(playerid,"Istrynei!");
        //SetTimerEx("Selectint",750,false,"i",playerid);
    }
    if(selectType == 3) // parameters
    {
        foreach(Player, i)
        {
            if(GetPVarInt(i,"EditingID") == objectid && i != playerid) 
            {
                SendInfoMessage(playerid,"Si objekta siuo metu redaguoja kitas zaidejas");
                return;
            }
        }
        new settings[1024];
        new model, Float:Coo[6];
        model = Streamer_GetIntData(STREAMER_TYPE_OBJECT,objectid,E_STREAMER_MODEL_ID);
        GetDynamicObjectPos(objectid, Coo[0], Coo[1],Coo[2]);
        GetDynamicObjectRot(objectid, Coo[3], Coo[4],Coo[5]);

        format(settings,sizeof(settings),"\
Modelis\t{6799f0}%i\n\
Pozicija X\t{6799f0}%.2f\n\
Pozicija Y\t{6799f0}%.2f\n\
Pozicija Z\t{6799f0}%.2f\n\
Rotacija X\t{6799f0}%.2f\n\
Rotacija Y\t{6799f0}%.2f\n\
Rotacija Z\t{6799f0}%.2f\n",
            model,Coo[0],Coo[1],Coo[2],Coo[3],Coo[4],Coo[5]);

        SetPVarInt(playerid, "SelectedObj", objectid);
        ShowPlayerDialog(playerid,2807, DIALOG_STYLE_LIST, "Objekto parametrai", settings, "Keisti","Atgal");
        CancelEdit(playerid);
    }
    if(selectType == 4) // clone
    {
        CancelEdit(playerid);
        new model = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_MODEL_ID);
        HandlePlaceObject(playerid, model, /* clonefrom= */ objectid);
    }
    if(selectType == 5)
    {
        CancelEdit(playerid);
        SetPVarInt(playerid, "SelectedObj", objectid);
        EditWorldTextures(playerid);
    }
}
stock HandleWorldPlacing(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    if(!IsWorldEditor(playerid))
        return 0;

    new houseid = GetWorldHouseId(playerid);
    new worldid = GetWorldWorldid(playerid);
    new slotid = GetWorldObjectSlot(houseid, worldid, objectid);
    if(slotid == -1)
        return 0;
    if(response == EDIT_RESPONSE_UPDATE)
    {
        // update pos for others?
        /*new world = GetPlayerVirtualWorld(playerid);
        foreach(Player, i)
        {
            if(i != playerid && GetPlayerVirtualWorld(i) == playerid)
            {
                SetDynamicObjectPos()
            }
        }*/
        //return 0;
    }

    SetDynamicObjectPos(objectid, x,y,z);
    SetDynamicObjectRot(objectid, rx, ry, rz);
    if(response == EDIT_RESPONSE_FINAL || response == EDIT_RESPONSE_CANCEL)
    {
        CancelWorldEdit(playerid);
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        SaveWorldObject(houseid,worldid,slotid);
    }
    return 0;
}
stock GetWorldObjectSlot(houseid, worldid, objectid)
{
    for(new i;i<MAX_WORLD_OBJECTS;i++)
    {
        if(WorldObjects[houseid][worldid][i] == objectid)
            return i;
    }
    return -1;
}
stock DeleteWorldObject(houseid, worldid, slotid, updateDb = true)
{
    if(WorldObjects[houseid][worldid][slotid] == 0)
        return;
    DestroyDynamicObject(WorldObjects[houseid][worldid][slotid]);
    WorldObjects[houseid][worldid][slotid] = 0;
    Worlds[houseid][worldid][world_objects_count]--;
    if(!updateDb)
        return;
    new vw = GetWorldVirtualWorld(houseid, worldid);
    new query[256];
    format(query,256, "DELETE FROM WorldObjects WHERE worldid = %i AND slotid = %i LIMIT 1", vw, slotid);
    mysql_query(query);
}
stock DeleteWorld(houseid, worldid)
{
    Worlds[houseid][worldid][world_loaded] = false;
    new query[256];
    new id = GetWorldVirtualWorld(houseid, worldid);
    format(query,sizeof(query),"DELETE FROM Worlds Where id = %i", id);
    mysql_query(query);
    for(new i;i<MAX_WORLD_OBJECTS;i++)
    {
        DeleteWorldObject(houseid, worldid, i, /* updateDb= */ false);
    }
}

stock SaveWorldObject(houseid,worldid,slot)
{
    new obj = WorldObjects[houseid][worldid][slot];
    if(!obj)
    {
        printf("SaveWorldObject object not found");
        return;
    }
    new model, Float:Coo[6];
    model = Streamer_GetIntData(STREAMER_TYPE_OBJECT,obj,E_STREAMER_MODEL_ID);
    GetDynamicObjectPos(obj, Coo[0], Coo[1],Coo[2]);
    GetDynamicObjectRot(obj, Coo[3], Coo[4],Coo[5]);
    new Node:textures = JSON_Object();
    new Node:texts = JSON_Object();
    for(new matid;matid < 16;matid++)
    {
        new key[20];
        format(key,20,"%i", matid);
        if(IsDynamicObjectMaterialUsed(obj, matid))
        {
            new modelid, txdname[100], texturename[100], materialcolor;
            GetDynamicObjectMaterial(obj, matid, modelid, txdname, texturename, materialcolor);
            new Node:texturenode = JSON_Object(
                "modelid", JSON_Int(modelid),
                "txdname", JSON_String(txdname),
                "texturename", JSON_String(texturename),
                "materialcolor", JSON_Int(materialcolor));
            JSON_SetObject(textures, key, texturenode);
        }
        if(IsDynamicObjectMaterialTextUsed(obj, matid))
        {
            new text[2048], materialsize, fontface[200], fontsize, bold, fontcolor, backcolor, textalignment;
            GetDynamicObjectMaterialText(obj, matid, text, materialsize, fontface, fontsize, bold, fontcolor, backcolor, textalignment);
            new Node:textnode = JSON_Object(
                "text", JSON_String(text),
                "materialsize", JSON_Int(materialsize),
                "fontface", JSON_String(fontface),
                "fontsize", JSON_Int(fontsize),
                "bold", JSON_Int(bold),
                "fontcolor", JSON_Int(fontcolor),
                "backcolor", JSON_Int(backcolor),
                "textalignment", JSON_Int(textalignment));
            JSON_SetObject(texts, key, textnode);
        }
    }

    new Node:data = JSON_Object(
        "model", JSON_Int(model),
        "houseid", JSON_Int(houseid),
        "worldid", JSON_Int(worldid),
        "pos", JSON_Array(JSON_Float(Coo[0]), JSON_Float(Coo[1]), JSON_Float(Coo[2]), JSON_Float(Coo[3]), JSON_Float(Coo[4]), JSON_Float(Coo[5])),
        "textures", textures,
        "texts", texts
    );
    new rawData[1024];
    JSON_Stringify(data, rawData);
    new dataStr[1500];
    mysql_real_escape_string(rawData, dataStr);
    new query[2048];
    new id = GetWorldVirtualWorld(houseid, worldid);
    format(query, 2048, "INSERT INTO WorldObjects(worldid,slotid,data) VALUES (%i, %i, '%s') ON DUPLICATE KEY UPDATE data='%s'",id, slot, dataStr, dataStr);
    mysql_query(query);
}

stock HandleWorldNameChange(playerid, newname[])
{
    if(!IsPlayerInWorld(playerid))
        return;
    if(!IsWorldOwner(playerid))
        return;
    if(strlen(newname) < 1 || strlen(newname) > 20)
    {
        SendInfoMessage(playerid, "~r~Netinkamas pavadinimas!");
        ShowPlayerDialog(playerid, 2796, DIALOG_STYLE_INPUT, "Pasaulis", "Áraðykite naujà pasaulio pavadinimà iki 20 simboliø.", "Gerai", "Atgal");
        return;
    }
    SendInfoMessage(playerid, "~g~Sekmingai pakeitei pasaulio pavadinima!");
    new houseid = GetWorldHouseId(playerid);
    new worldid = GetWorldWorldid(playerid);
    format(Worlds[houseid][worldid][world_title], 24, newname);
    SaveWorld(houseid, worldid);
}
stock HandleWorldSpawn(playerid)
{
    new vw = GetPVarInt(playerid,"MireWorld");
    if(!vw)
        return 0;
    SetPVarInt(playerid,"MireWorld", 0);
    SetPlayerVirtualWorld(playerid, vw);
    new houseid = GetWorldHouseId(playerid);
    new worldid = GetWorldWorldid(playerid);
    TeleportPlayerToWorld(playerid, houseid, worldid, /*fade=*/ false);
    SetPlayerHealthEx(playerid, 100.0);
    //SetPlayerArmourEx(playerid, 100.0);
    return 1;
}
stock FillClosestObjArray(playerid)
{
    if(!IsPlayerInWorld(playerid))
        return;
    new houseid = GetWorldHouseId(playerid);
    new worldid = GetWorldWorldid(playerid);
    new idx = 0;
    new Float:pp[3],Float:op[3];
    GetPlayerPos(playerid, pp[0],pp[1],pp[2]);
    for(new i;i<MAX_WORLD_OBJECTS;i++)
    {
        closestobjs[i][closestobjslot] = -1;
        closestobjs[i][closestobjdist] = 99999.9999;
        new obj = WorldObjects[houseid][worldid][i];
        if(obj)
        {
            GetDynamicObjectPos(obj, op[0],op[1],op[2]);
            new Float:dist = GetDistanceBetweenPoints(pp[0],pp[1],pp[2],op[0],op[1],op[2]);
            closestobjs[idx][closestobjslot] = i;
            closestobjs[idx][closestobjdist] = dist;
            idx++;
        }
    }
    SortDeepArray(closestobjs, closestobjdist);
}
stock IsPlayerInWorldSafeArea(playerid)
{
    if(!IsPlayerInWorld(playerid))
        return 0;
    new houseid = GetWorldHouseId(playerid);
    new worldid = GetWorldWorldid(playerid);

    return Worlds[houseid][worldid][world_safezone];
}