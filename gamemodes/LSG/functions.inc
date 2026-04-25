
bool:Boolint(number)
{
	if(number>0) return true;
	return false;
}

stock SendMessageToTeisesauga(color,text[])
{
	foreach (Player, i)
	{
		if(playerDB[i][specialybe]==80 || playerDB[i][specialybe]==82 || playerDB[i][specialybe]==81 || playerDB[i][specialybe]==83 || playerDB[i][specialybe]==84)
		{
			SendClientMessage(i,color,text);
		}
	}
	printf("[TEISESAUGA] %s",text);
}
stock SendMessageToApsauga(color,text[])
{
	foreach(Player, i)
	{
		if(playerDB[i][specialybe]==82)
		{
			SendClientMessage(i,color,text);
		}
	}
}
stock SendMessageToInka(color,text[])
{
	foreach(Player, i)
	{
		if(playerDB[i][specialybe]==60)
		{
			SendClientMessage(i,color,text);
		}
	}
}
stock SendMessageToGaisras(color,text[])
{
	foreach (Player, i)
	{
		if(playerDB[i][specialybe]==66)
		{
			SendClientMessage(i,color,text);
		}
	}
}
stock SendMessageToNTA(color,text[])
{
	foreach (Player, i)
	{
		if(playerDB[i][specialybe]==34)
		{
			SendClientMessage(i,color,text);
		}
	}
}

stock SendMessageToSunys(color,text[])
{
	foreach (Player, i)
	{
		if(playerDB[i][specialybe]==58)
		{
			SendClientMessage(i,color,text);
		}
	}
}
stock SendMessageToDeal(color,text[])
{
	foreach (Player, i)
	{
		if(playerDB[i][specialybe]==32)
		{
			SendClientMessage(i,color,text);
		}
	}
}


stock SendMessageToKont(color,text[])
{
	foreach (Player, i)
	{
		if(playerDB[i][specialybe]==31)
		{
			SendClientMessage(i,color,text);
		}
	}
}

stock SendMessageToTune(color,text[])
{
	foreach (Player, i)
	{
		if(playerDB[i][specialybe]==28 || playerDB[i][specialybe]==51)
		{
			SendClientMessage(i,color,text);
		}
	}
}





/*
stock StringToInt(string[])
{
	new thestring[14];
	strmid(thestring,string,0,strlen(string),sizeof(thestring));
	return strval(thestring);
}
*/
stock StringToInt(string[]) return strval(string);

stock SendMessageToAutospecai(color,text[])
{
	foreach (Player, i)
	{
		 if(playerDB[i][specialybe]==6)
		 {
			SendClientMessage(i,color,text);
		 }
	}
}

stock SendMessageToValstybe(color,text[])
{
	foreach (Player, i)
	{
		if(playerDB[i][specialybe]==50 || playerDB[i][specialybe]==51)
		{
			SendClientMessage(i,color,text);
		}
	}
}

stock SendMessageToFuristai(color,text[])
{
	foreach (Player, i)
	{
		if(playerDB[i][specialybe]==41 || playerDB[i][specialybe]==44)
		{
			SendClientMessage(i,color,text);
		}
	}
}
stock SendMessageToKlubai(color,text[])
{
	foreach (Player, i)
	{
		if(playerDB[i][specialybe]==70 || playerDB[i][specialybe]==72 || playerDB[i][specialybe]==73)
		{
            SendClientMessage(i,color,text);
		}
	}
}

stock SendMessageToBaikeriai(color,text[])
{
	foreach (Player, i)
	{
		if(playerDB[i][specialybe]==71)
		{
			SendClientMessage(i,color,text);
		}
	}
}



stock SendMessageToTransportas(color,text[])
{
	foreach (Player, i)
	{
		if(playerDB[i][specialybe]==3 || playerDB[i][specialybe]==20 || playerDB[i][specialybe]==39 )
		{
			SendClientMessage(i,color,text);
		}	
	}
}

stock SendMessageToMedics(color,text[])
{
	printf("[MEDIKAI] %s",formatwithoutLT(text));
	foreach (Player, i)
	{
		if(playerDB[i][specialybe]==2 || playerDB[i][specialybe]==93)
		{
			SendClientMessage(i,color,text);
		}	
	}
}

stock SendMessageToCrew(crewid,color,text[])
{
	foreach (Player, i)
	{
		if(playerDB[i][lektuvas]==crewid)
		{
			SendClientMessage(i,color,text);
		}	
	}
}

stock SendMessageToAdmin(text[])
{
	foreach (Player, i)
	{
		if(playerDB[i][admin])
		{
			SendClientMessage(i,ADMIN_COLOR,text);
		}	
	}
}
stock SendMessageToPrez(text[])
{
	foreach (Player, i)
	{
			if(playerDB[i][prez])
			{
				SendClientMessage(i,PREZ_COLOR,text);
			}	
	}
}

stock tohash(buf[]) {
	new length=strlen(buf);
    new s1 = 1;
    new s2 = 0;
    new n;
    for (n=0; n<length; n++)
    {
       s1 = (s1 + buf[n]) % 65521;
       s2 = (s2 + s1)     % 65521;
    }
    return (s2 << 16) + s1;
}

stock CheckPass(file[],password[])
{
	if(dini_Int(file,"slaptazodis")==tohash(password)) return true;
	return false;
}

stock GetWeaponSlot(playerid,weapon)
{
	new weid,ammo;

	for(new slot=0; slot < 13; slot++)
	{
		GetPlayerWeaponData(playerid,slot,weid,ammo);
		if(weid == weapon)
		{
			return slot;
		}
	}
	return -1;
}





stock GetArgument(argument, const string[], untillend)
{
	new index = 0;
	new end = 0;
	new returns[256]="0";

	for(new loop = 0; loop < argument; loop++){
	index = strfind(string," ",true,index)+1;
	if(!strcmp(string[index]," ",true,1)){return returns;}
	if (index == 0){return returns;}
	}
	if(untillend == 0){
	end = strfind(string[index]," ",true,0);}
	if (end== -1 || untillend==1) end = 256-index;
	strmid(returns,string[index],0,end);
	return returns;
}

stock GetXYInFrontOfPlayer(playerid, &Float:x, &Float:y, Float:distance)
{       // Created by Y_Less

        new Float:a;

        GetPlayerPos(playerid, x, y, a);
        GetPlayerFacingAngle(playerid, a);

        if (GetPlayerVehicleID(playerid)) {
            GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
        }

        x += (distance * floatsin(-a, degrees));
        y += (distance * floatcos(-a, degrees));
}

stock PreloadAnimLib(playerid, animlib[])
{
	ApplyAnimation(playerid,animlib,"null",0.0,0,0,0,0,0);
}

stock PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z)
{
    if(IsPlayerConnected(playerid))
	{
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		tempposx = (oldposx -x);
		tempposy = (oldposy -y);
		tempposz = (oldposz -z);
		if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
		{
			return 1;
		}
	}
	return 0;
}

stock GetPlayeridMid(name[]) //Boylett
{
	foreach(Player, i) if(!playerDB[i][invisible])
	{
            new gPlayerName[MAX_PLAYER_NAME];
            GetPlayerName(i, gPlayerName, MAX_PLAYER_NAME);
            if(strfind(gPlayerName, name, true) != -1)
            {
                return i;
            }
    }
    return INVALID_PLAYER_ID;
}
stock GetPlayeridMidEx(name[]) //Boylett
{
	foreach(Player, i)
	{
            new gPlayerName[MAX_PLAYER_NAME];
            GetPlayerName(i, gPlayerName, MAX_PLAYER_NAME);
            if(strfind(gPlayerName, name, true) != -1)
            {
                return i;
            }
    }
    return INVALID_PLAYER_ID;
}

stock OutputVehicleData(lower)
{
	new bool:models[212],smodels[212],vehicles,tmodels;

	for(new vehicle=0; vehicle<MAX_VEHICLES; vehicle++)
	{
		new model = GetVehicleModel(vehicle);
		if(model > 399)
		{
			models[model-400]=true;
			smodels[model-400]++;
		}
		if(model !=0) vehicles++;
	}

	for(new model=0;model<212; model++)
	{
		if(models[model]) tmodels++;
	}

	printf("Total vehicles: %i",vehicles);
	printf("Total Models: %i",tmodels);
	print("\nPrinting model data:\n");

	for(new prints=0; prints<212; prints++)
	{
		if(smodels[prints] != 0 && smodels[prints] < lower)
			printf("Number of %s(ID:%i): %i",aVehicleNames[prints],prints+400,smodels[prints]);
	}

}

stock hexstr(string[])
{
	new
		ret,
		val,
		i;
	if (string[0] == '0' && (string[1] == 'x' || string[1] == 'X')) i = 2;
	while (string[i])
	{
		ret <<= 4;
		val = string[i++] - '0';
		if (val > 0x09) val -= 0x07;
		if (val > 0x0F) val -= 0x20;
		if (val < 0x01) continue;
		if (val < 0x10) ret += val;
	}
	return ret;
}

new MaxSeats[212] = {
4,2,2,2,4,4,1,2,2,4,2,2,2,4,2,2,4,2,4,2,4,4,2,2,2,1,4,4,4,2,1,9,1,2,2,1,2,9,4,2,
4,1,2,2,2,4,1,2,1,6,1,2,1,1,1,2,2,2,4,4,2,2,2,2,2,2,4,4,2,2,4,2,1,1,2,2,1,2,2,4,
2,1,4,3,1,1,1,4,2,2,4,2,4,1,2,2,2,4,4,2,2,2,2,2,2,2,2,4,2,1,1,2,1,1,2,2,4,2,2,1,
1,2,2,2,2,2,2,2,2,4,1,1,1,2,2,2,2,0,0,1,4,2,2,2,2,2,4,4,2,2,4,4,2,1,2,2,2,2,2,2,
4,4,2,2,1,2,4,4,1,0,0,1,1,2,1,2,2,2,2,4,4,2,4,1,1,4,2,2,2,2,6,1,2,2,2,1,4,4,4,2,
2,2,2,2,4,2,1,1,1,4,1,1
};
stock GetMaxSeats(modelis)
{
	return MaxSeats[(modelis- 400)];
}

stock PlaySound(playerid,soundid)
{
	PlayerPlaySound(playerid, soundid, 0.0, 0.0, 0.0); 
}

stock split(const strsrc[], strdest[][], delimiter)
{
    new i, li;
    new aNum;
    new len;
    while(i <= strlen(strsrc))
	{
		if(strsrc[i]==delimiter || i==strlen(strsrc))
		{
	        len = strmid(strdest[aNum], strsrc, li, i, 128);
	        strdest[aNum][len] = 0;
	        li = i+1;
	        aNum++;
		}
		i++;
    }
    return 1;
}

stock crossp(Float:v1x, Float:v1y, Float:v1z, Float:v2x, Float:v2y, Float:v2z, &Float:output)
{
        new
                Float:c1 = (v1y * v2z) - (v1z * v2y),
                Float:c2 = (v1z * v2x) - (v1x * v2z),
                Float:c3 = (v1x * v2y) - (v1y * v2x);
        output = floatsqroot ((c1 * c1) + (c2 * c2) + (c3 * c3));
        return 0;
}

stock GetDistanceFromPointToLine(&Float:distance, Float:line_vector_x, Float:line_vector_y, Float:line_vector_z, Float:line_x, Float:line_y, Float:line_z, Float:point_x, Float:point_y, Float:point_z)
{
        //A line is defined by a point (which is on the line (line_x/y/z)) and a vector which defines the direction (line_vector_x/y/z).
        static Float:output;
        crossp(line_vector_x, line_vector_y, line_vector_z, point_x - line_x, point_y - line_y, point_z - line_z, output);//Cross product of 2 vectors.
        new Float:divres = floatsqroot ((line_vector_x * line_vector_x) + (line_vector_y * line_vector_y) + (line_vector_z * line_vector_z));
        if(divres == 0.0)
        	divres = 1.0;
        distance = output / divres;
        return 0;
}

stock encode_lights(light1, light2, light3, light4)
{
	return light1 | (light2 << 1) | (light3 << 2) | (light4 << 3);
}

stock BoolInt(bool:lol)
{
	return (lol)?1:0;
}

stock BreakingLines(string[])
{
	new newstring[2048];
	strcpy(newstring,string,2048);
	new chars=0;
	new nocount=0;
	for(new i,j=strlen(newstring);i<j;i++)
	{
		if(string[i] == '\n')
			chars=0;
		else if(string[i] == '{')
			nocount=1;
		else if(string[i] == '}')
			nocount=0;
		if(!nocount)
			chars++;
		if(chars > 100 && string[i] == ' ')
		{
			newstring[i] = '\n';
			chars=0;
		}
	}
	return newstring;
}

stock numstr(num)// by Y_Less
{
        new
                str[32];
        format(str, sizeof (str), "%d", num);
        return str;
}

//(3, 4, 5, 6, 8, 42, 65, 86, 119, 149, 208, 273, 289) 
stock GetWeaponsSlot(weaponid)
{
	new slot;
	switch(weaponid)
	{
	    case 0,1: slot = 0;
	    case 2..9: slot = 1;
	    case 10..15: slot = 10;
	    case 16,17,18,19,39: slot = 8;
	    case 22,23,24: slot = 2;
	    case 25,26,27: slot = 3;
	    case 28,29,32: slot = 4;
	    case 30,31: slot = 5;
	    case 33,34: slot = 6;
	    case 35..38: slot = 7;
	    case 40: slot = 12;
	    case 41,42,43: slot = 9;
		case 44..46: slot = 11;
	    default: slot = 0;
	}
    return slot;
}


stock Float:GetDistanceBetweenPoints(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2)
{
	return floatsqroot((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1));
}

stock sha256_hash(buf[])
{
	new rethash[128];
	SHA256_PassHash(buf, PASSWORD_SALT, rethash, 128);
	return rethash;
}

stock GetWeekDay()
{
	new year,month,day;
	getdate(year, month, day);
	new j, e;
	if (month <= 2)
	{
		month += 12;
		--year;
	}
	j = year % 100;
	e = year / 100;
	return ((day + (month+1)*26/10 + j + j/4 + e/4 - 2*e) % 7);
	/*
		case 0: weekday_str = "Saturday";
		case 1: weekday_str = " Sunday";
		case 2: weekday_str = " Monday";
		case 3: weekday_str = " Tuesday";
		case 4: weekday_str = "Wednesday";
		case 5: weekday_str = "Thursday";
		case 6: weekday_str = " Friday";
	*/
}


stock replaceChar(strSrc[], chWhat, chWith)
{
    for(new i; strSrc[i] != EOS; ++i)
    {
        if(strSrc[i] == chWhat)
        {
            strSrc[i] = chWith;
        }
    }
}


stock IsComponentidCompatible(modelid, componentid)
{
    if(componentid == 1025 || componentid == 1073 || componentid == 1074 || componentid == 1075 || componentid == 1076 ||
         componentid == 1077 || componentid == 1078 || componentid == 1079 || componentid == 1080 || componentid == 1081 ||
         componentid == 1082 || componentid == 1083 || componentid == 1084 || componentid == 1085 || componentid == 1096 ||
         componentid == 1097 || componentid == 1098 || componentid == 1087 || componentid == 1086)
         return true;

    switch (modelid)
    {
        case 400: return (componentid == 1020 || componentid == 1021 || componentid == 1019 || componentid == 1018 || componentid == 1013 || componentid == 1024 || componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 401: return (componentid == 1005 || componentid == 1004 || componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 114 || componentid == 1020 || componentid == 1019 || componentid == 1013 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1006 || componentid == 1001 || componentid == 1003 || componentid == 1017 || componentid == 1007);
        case 402: return (componentid == 1009 || componentid == 1009 || componentid == 1010);
        case 404: return (componentid == 1020 || componentid == 1021 || componentid == 1019 || componentid == 1013 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1002 || componentid == 1016 || componentid == 1000 || componentid == 1017 || componentid == 1007);
        case 405: return (componentid == 1020 || componentid == 1021 || componentid == 1019 || componentid == 1018 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1001 || componentid == 1014 || componentid == 1023 || componentid == 1000);
        case 409: return (componentid == 1009);
        case 410: return (componentid == 1019 || componentid == 1021 || componentid == 1020 || componentid == 1013 || componentid == 1024 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1001 || componentid == 1023 || componentid == 1003 || componentid == 1017 || componentid == 1007);
        case 411: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 412: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 415: return (componentid == 1019 || componentid == 1018 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1001 || componentid == 1023 || componentid == 1003 || componentid == 1017 || componentid == 1007);
        case 418: return (componentid == 1020 || componentid == 1021 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1006 || componentid == 1002 || componentid == 1016);
        case 419: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 420: return (componentid == 1005 || componentid == 1004 || componentid == 1021 || componentid == 1019 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1001 || componentid == 1003);
        case 421: return (componentid == 1020 || componentid == 1021 || componentid == 1019 || componentid == 1018 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1014 || componentid == 1023 || componentid == 1016 || componentid == 1000);
        case 422: return (componentid == 1020 || componentid == 1021 || componentid == 1019 || componentid == 1013 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1017 || componentid == 1007);
        case 426: return (componentid == 1005 || componentid == 1004 || componentid == 1021 || componentid == 1019 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1006 || componentid == 1001 || componentid == 1003);
        case 429: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 436: return (componentid == 1020 || componentid == 1021 || componentid == 1022 || componentid == 1019 || componentid == 1013 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1006 || componentid == 1001 || componentid == 1003 || componentid == 1017 || componentid == 1007);
        case 438: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 439: return (componentid == 1003 || componentid == 1023 || componentid == 1001 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1017 || componentid == 1007 || componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145 || componentid == 1013);
        case 442: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 445: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 451: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 458: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 466: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 467: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 474: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 475: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 477: return (componentid == 1020 || componentid == 1021 || componentid == 1019 || componentid == 1018 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1006 || componentid == 1017 || componentid == 1007);
        case 478: return (componentid == 1005 || componentid == 1004 || componentid == 1012 || componentid == 1020 || componentid == 1021 || componentid == 1022 || componentid == 1013 || componentid == 1024 || componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 479: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 480: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 489: return (componentid == 1005 || componentid == 1004 || componentid == 1020 || componentid == 1019 || componentid == 1018 || componentid == 1013 || componentid == 1024 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1006 || componentid == 1002 || componentid == 1016 || componentid == 1000);
        case 491: return (componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145 || componentid == 1020 || componentid == 1021 || componentid == 1019 || componentid == 1018 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1014 || componentid == 1023 || componentid == 1003 || componentid == 1017 || componentid == 1007);
        case 492: return (componentid == 1005 || componentid == 1004 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1006 || componentid == 1016 || componentid == 1000);
        case 496: return (componentid == 1006 || componentid == 1017 || componentid == 1007 || componentid == 1011 || componentid == 1019 || componentid == 1023 || componentid == 1001 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1003 || componentid == 1002 || componentid == 1142 || componentid == 1143 || componentid == 1020);
        case 500: return (componentid == 1020 || componentid == 1021 || componentid == 1019 || componentid == 1013 || componentid == 1024 || componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 506: return (componentid == 1009);
        case 507: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 516: return (componentid == 1004 || componentid == 1020 || componentid == 1021 || componentid == 1019 || componentid == 1018 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1002 || componentid == 1015 || componentid == 1016 || componentid == 1000 || componentid == 1017 || componentid == 1007);
        case 517: return (componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145 || componentid == 1020 || componentid == 1019 || componentid == 1018 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1002 || componentid == 1023 || componentid == 1016 || componentid == 1003 || componentid == 1017 || componentid == 1007);
        case 518: return (componentid == 1005 || componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145 || componentid == 1020 || componentid == 1018 || componentid == 1013 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1006 || componentid == 1001 || componentid == 1023 || componentid == 1003 || componentid == 1017 || componentid == 1007);
        case 526: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 527: return (componentid == 1021 || componentid == 1020 || componentid == 1018 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1001 || componentid == 1014 || componentid == 1015 || componentid == 1017 || componentid == 1007);
        case 529: return (componentid == 1012 || componentid == 1011 || componentid == 1020 || componentid == 1019 || componentid == 1018 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1006 || componentid == 1001 || componentid == 1023 || componentid == 1003 || componentid == 1017 || componentid == 1007);
        case 533: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 534: return (componentid == 1126 || componentid == 1127 || componentid == 1179 || componentid == 1185 || componentid == 1100 || componentid == 1123 || componentid == 1125 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1180 || componentid == 1178 || componentid == 1101 || componentid == 1122 || componentid == 1124 || componentid == 1106);
        case 535: return (componentid == 1109 || componentid == 1110 || componentid == 1113 || componentid == 1114 || componentid == 1115 || componentid == 1116 || componentid == 1117 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1120 || componentid == 1118 || componentid == 1121 || componentid == 1119);
        case 536: return (componentid == 1104 || componentid == 1105 || componentid == 1182 || componentid == 1181 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1184 || componentid == 1183 || componentid == 1128 || componentid == 1103 || componentid == 1107 || componentid == 1108);
        case 540: return (componentid == 1004 || componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145 || componentid == 1020 || componentid == 1019 || componentid == 1018 || componentid == 1024 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1006 || componentid == 1001 || componentid == 1023 || componentid == 1017 || componentid == 1007);
        case 541: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 542: return (componentid == 1144 || componentid == 1145 || componentid == 1020 || componentid == 1021 || componentid == 1019 || componentid == 1018 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1014 || componentid == 1015);
        case 545: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 546: return (componentid == 1004 || componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145 || componentid == 1019 || componentid == 1018 || componentid == 1024 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1006 || componentid == 1002 || componentid == 1001 || componentid == 1023 || componentid == 1017 || componentid == 1007);
        case 547: return (componentid == 1142 || componentid == 1143 || componentid == 1020 || componentid == 1021 || componentid == 1019 || componentid == 1018 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1016 || componentid == 1003 || componentid == 1000);
        case 549: return (componentid == 1012 || componentid == 1011 || componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145 || componentid == 1020 || componentid == 1019 || componentid == 1018 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1001 || componentid == 1023 || componentid == 1003 || componentid == 1017 || componentid == 1007);
        case 550: return (componentid == 1005 || componentid == 1004 || componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145 || componentid == 1020 || componentid == 1019 || componentid == 1018 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1006 || componentid == 1001 || componentid == 1023 || componentid == 1003);
        case 551: return (componentid == 1005 || componentid == 1020 || componentid == 1021 || componentid == 1019 || componentid == 1018 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1006 || componentid == 1002 || componentid == 1023 || componentid == 1016 || componentid == 1003);
        case 555: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 558: return (componentid == 1092 || componentid == 1089 || componentid == 1166 || componentid == 1165 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1168 || componentid == 1167 || componentid == 1088 || componentid == 1091 || componentid == 1164 || componentid == 1163 || componentid == 1094 || componentid == 1090 || componentid == 1095 || componentid == 1093);
        case 559: return (componentid == 1065 || componentid == 1066 || componentid == 1160 || componentid == 1173 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1159 || componentid == 1161 || componentid == 1162 || componentid == 1158 || componentid == 1067 || componentid == 1068 || componentid == 1071 || componentid == 1069 || componentid == 1072 || componentid == 1070 || componentid == 1009);
        case 560: return (componentid == 1028 || componentid == 1029 || componentid == 1169 || componentid == 1170 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1141 || componentid == 1140 || componentid == 1032 || componentid == 1033 || componentid == 1138 || componentid == 1139 || componentid == 1027 || componentid == 1026 || componentid == 1030 || componentid == 1031);
        case 561: return (componentid == 1064 || componentid == 1059 || componentid == 1155 || componentid == 1157 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1154 || componentid == 1156 || componentid == 1055 || componentid == 1061 || componentid == 1058 || componentid == 1060 || componentid == 1062 || componentid == 1056 || componentid == 1063 || componentid == 1057);
        case 562: return (componentid == 1034 || componentid == 1037 || componentid == 1171 || componentid == 1172 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1149 || componentid == 1148 || componentid == 1038 || componentid == 1035 || componentid == 1147 || componentid == 1146 || componentid == 1040 || componentid == 1036 || componentid == 1041 || componentid == 1039);
        case 565: return (componentid == 1046 || componentid == 1045 || componentid == 1153 || componentid == 1152 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1150 || componentid == 1151 || componentid == 1054 || componentid == 1053 || componentid == 1049 || componentid == 1050 || componentid == 1051 || componentid == 1047 || componentid == 1052 || componentid == 1048);
        case 566: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 567: return (componentid == 1129 || componentid == 1132 || componentid == 1189 || componentid == 1188 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1187 || componentid == 1186 || componentid == 1130 || componentid == 1131 || componentid == 1102 || componentid == 1133);
        case 575: return (componentid == 1044 || componentid == 1043 || componentid == 1174 || componentid == 1175 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1176 || componentid == 1177 || componentid == 1099 || componentid == 1042);
        case 576: return (componentid == 1136 || componentid == 1135 || componentid == 1191 || componentid == 1190 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1192 || componentid == 1193 || componentid == 1137 || componentid == 1134);
        case 579: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 580: return (componentid == 1020 || componentid == 1018 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1006 || componentid == 1001 || componentid == 1023 || componentid == 1017 || componentid == 1007);
        case 585: return (componentid == 1142 || componentid == 1143 || componentid == 1144 || componentid == 1145 || componentid == 1020 || componentid == 1019 || componentid == 1018 || componentid == 1013 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1006 || componentid == 1001 || componentid == 1023 || componentid == 1003 || componentid == 1017 || componentid == 1007);
        case 587: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 589: return (componentid == 1005 || componentid == 1004 || componentid == 1144 || componentid == 1145 || componentid == 1020 || componentid == 1018 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1024 || componentid == 1013 || componentid == 1006 || componentid == 1016 || componentid == 1000 || componentid == 1017 || componentid == 1007);
        case 600: return (componentid == 1005 || componentid == 1004 || componentid == 1020 || componentid == 1022 || componentid == 1018 || componentid == 1013 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1006 || componentid == 1017 || componentid == 1007);
        case 602: return (componentid == 1008 || componentid == 1009 || componentid == 1010);
        case 603: return (componentid == 1144 || componentid == 1145 || componentid == 1142 || componentid == 1143 || componentid == 1020 || componentid == 1019 || componentid == 1018 || componentid == 1024 || componentid == 1008 || componentid == 1009 || componentid == 1010 || componentid == 1006 || componentid == 1001 || componentid == 1023 || componentid == 1017 || componentid == 1007);
    }
    return false;
}

stock small_hash(buf[])
{
    new int,len=strlen(buf);
    for(new i=0;i<len;i++)
	{
		if(buf[i]=='{') buf[i]='}';
		int+=buf[i];
	}
    return int;
}

stock RandomPw(length)
{
	new string[100];
	new ch;
	for(new i;i<length;i++)
	{
		switch(random(3))
		{
			case 0: ch=48+random(10);
			case 1: ch=65+random(25);
			case 2: ch=97+random(25);
		}
		if(ch == 'l' || ch == 'I') ch='a';
		format(string,sizeof(string),"%s%c",string,ch);
	}
	return string;
}


stock str_repeat(const sSource[], iMultiplier)
{
	new
		iInputLength = strlen(sSource),
		iItteration = (iInputLength * iMultiplier),
		iIndex,
		sReturn[24];

	while(iIndex < iItteration && iIndex < 24)
	{
		strins(sReturn, sSource, iIndex);
		iIndex += iInputLength;
	}

	return sReturn;
}


stock Float:GetServerPacketLoss()
{
	new stats[400+1];
    GetNetworkStats(stats, sizeof(stats)); // get the servers networkstats
    new start = strfind(stats, "Packetloss", true);
    new dest[20];
    strmid(dest,stats,start+12,start+15);
    return floatstr(dest);
}
stock gradient(num,min,max)
{
	new str[12];
	new middle = (min + max) / 2;
	new scale = 255 / (middle - min);

	if(num <= min)
		format(str,12,"FF0000");
	else if(num >= max)
		format(str,12,"00FF00");
	else if(num < middle)
		format(str,12,"FF%02x00", (num - min) * scale);
	else
		format(str,12,"%02xFF00", 255 - (num - middle) * scale);
	return str;
}


stock IsNumeric(const string[])
{
	if(strlen(string) > 9 || strval(string) < 0) return 0;
	for (new i = 0, j = strlen(string); i < j; i++)
	{
		if (string[i] > '9' || string[i] < '0') return 0;
	}
	return 1;
}

stock GetPokerNumber(string[])
{
	new len = strlen(string);
	if(len > 9 || len == 0) return 0;

	new Float:num;
	new letter = string[len-1];
	string[len-1] = '\0';

	if(!sscanf(string,"f",num))
    {
		if(num < 0 || num >= 1000)
			return 0;
		if(letter == 'k' || letter == 'K')
			num = num * 1000;
		else if(letter == 'm' || letter == 'M')
			num = num * 1000000;
		else
			return 0;

		if(num < 0)
			return 0;	
		
		return floatround(num);
	}
	return 0;
}



		