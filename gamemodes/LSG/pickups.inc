#define RANGE 50
new Float:PickupIDs[MAX_PICKUPS][3],PModels[MAX_PICKUPS];
#define FIX_PICKUPS if(!IsPickedUp(playerid,pickupid)) return 0; // pickupid = GetPickupNearPlayer(playerid,5.0);

stock CreatePickupA(model,type,Float:x,Float:y,Float:z,world = -1)
{
	new tmp;
	if(type < 1) type=2;
	tmp = CreatePickup(model,type,Float:x,Float:y,Float:z,world);
	//tmp = CreateDynamicPickup(model, type, x, y, z, world);
	PickupIDs[tmp][0]=x; PickupIDs[tmp][1]=y; PickupIDs[tmp][2]=z;
	PModels[tmp]=type;
	return tmp;
}


stock IsPickedUp(playerid,pickupid)
{
	new Float:range = 5.0;
	if(IsPlayerInAnyVehicle(playerid)) 
	{
		range = 25.0;
	}
	if(!IsPlayerInRangeOfPoint(playerid,range,PickupIDs[pickupid][0],PickupIDs[pickupid][1],PickupIDs[pickupid][2]))
		return 0;
	return 1;
}

stock IsPlayerNearPickup(playerid, pickupid)
{
	new Float:range = 20.0;
	if(!IsPlayerInRangeOfPoint(playerid,range,PickupIDs[pickupid][0],PickupIDs[pickupid][1],PickupIDs[pickupid][2]))
		return 0;
	return 1;
}
	

stock GetPickupNearPlayer(playerid,Float:radi)
{
	new Float:oldposx, Float:oldposy, Float:oldposz;
	GetPlayerPos(playerid, oldposx, oldposy, oldposz);

	for(new npickup=0; npickup<2000; npickup++)
	{		
		new Float:tempposx, Float:tempposy, Float:tempposz;
		tempposx = (oldposx -PickupIDs[npickup][0]);
		tempposy = (oldposy -PickupIDs[npickup][1]);
		tempposz = (oldposz -PickupIDs[npickup][2]);

		if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
		{
			return npickup;
		}
	}
	return -1;
}

enum pdata{
degaline,
para, // shiutas
bankas,
regitra,
pelnininkas,
aturgus,
draudimas,
farai,
medikai,
tazeriai,
taxi,
traukinys,
autobusas,
namai,
medikailiftas,
gunkraut,
gunkraut2,
gunkraut3,
narkraut,
gunisk,
narkisk,
motomanai,
narkotikai,
statybininkas,
mikro,
begtjail,
sautuvai,
//fever,
stadionas,
stadgalai,
//kioskas,
savegame,
seklos,
kontrabanda,
dealer,
info,
inf1,
kastuvas,
inf2,
kortele,
//inf3,
loterija,
jail,
jail2,
baudam,
gerimai,
bizniss,
abzn,
SWAT,
kobra,
vagys,
operatore,
kma,
mentai,
parkas,
padangos,
valgis,
SIUKSLEVEZIS,
KRANTAS,
ARMIJA,
ARMIJAG,
BAIKERIUG,
ZINIOS,
VSTG,
MENTAI,
KARDAS,
VST,
mechanikas,
//konfiskuota,
bankininkas,
konfiskavimas,
TRANS,
TEIS,
ZIN,
turtas,
kriminalika,
inkasatorius,
kunigas,
bmxxx,
pizza,
sokeja,
ukininkai,
taisykla,
slavejai,
limuzin,
pilotas,
/*
backine,*/
dezes,
pas,
bankomatas,
gaujos,
gaisrinee,
automanai,
baikeriai,
kurjerai,
baikeriuuzd,
//jachtos,
stadbzn,
furistai,
/*
pridavimas,
telikai,
telikatv,
*/
gerimaijack,
/*
pautai,
pautatv,
*/
cilifon,
meskereshop,
gydymas,
/*
kur_kioskai,
kur_sexs,
kur_maistas,
kur_cig,
kur_rubai,
kur_fejerverkai,
kur_gerimai,*/
//kurobak,
lsdvieta,
ratuvieta,
pdvieta,
piniguvieta,
m4vieta,
//traukdegal,
bankocekiai,
bankoalgos,
bankopervedimai,
bankokortele,
bankopop,
darbinescar,
pastininkai,
mokesciai,
sratasvydis,
sratasvydis2,
sratasvydis3,
baldu_verslas,
jetpack,
inkaofisas,
elektr_verslas,
interjer_verslas,
privatus,
pligonine,
dovana,
kaledugerimai,
roges,
fuleinfo,
saudykla,
elniai,
velykos,
atomine,
lsgsiena,
transportosaugykla,
kaledushop,
laivotp
}

new pickups[2][pdata];
 // jail

new laukas;
new lauke;
new isejimas;
new iejimas;
// baseinas
new entersp;
new exitsp;
new entersauna;
new exitsauna;
new bigjump;
new anima;


stock OutputPickupDebugInfo(){
	printf("Pickup Info:");
	printf("Degalines: %i - %i", pickups[0][degaline],pickups[1][degaline]);
	printf("I banka: %i, is banko: %i",pickups[0][bankas],pickups[1][bankas]);
	printf("Darbai:");
	printf("Faru: %i, Mediku: %i, Taxi: %i, Traukinisto: %i, Autobuso: %i",pickups[0][farai],pickups[0][medikai],pickups[0][taxi],pickups[0][traukinys],pickups[0][autobusas]);
	printf("Namai: %i - %i",pickups[0][namai],pickups[1][namai]);
	printf("Narkotikai: %i - %i",pickups[0][narkotikai],pickups[1][narkotikai]);
	printf("I stadiona: %i; is: %i, Degalai stadione: %i",pickups[0][stadionas],pickups[1][stadionas],pickups[0][stadgalai]);
	printf("Savegame: %i - %i",pickups[0][savegame],pickups[1][savegame]);

}

stock LoadPickups()
{
	CreatePickupA(1274 ,2,-1685.1217,409.1019,700.1797); // just a bugfix
	//pickups[0][velykos]=CreatePickupA(19342,2, 1479.3293,-1624.1665,14.0469);
	//CreateDynamic3DTextLabel("{00864b}Ðv. Velykos 2022",COLOR_WHITE,1479.3293,-1624.1665,14.0469,50,_,_,1);

	//pickups[0][roges]=CreatePickupA(19056,2, 1776.6597,-2544.5569,14);
	pickups[0][saudykla]=CreatePickupA(1248,2,300.0830,-134.1843,1004.0625);
	pickups[1][saudykla]=CreatePickupA(1248,2,1017.1052,1262.1913,1805.7701);
	pickups[0][degaline]=CreatePickupA(1274 ,2,-1685.1217,409.1019,7.1797); // sf
	{
		CreatePickupA(1274 ,2, 1383.076049, 458.077423, 19.989109);  // {Angle: 337.231109}, kaimas!
		CreatePickupA(1274 ,2,-93.3981,-1160.9077,2.1805); // netoli miesto
		CreatePickupA(1274 ,2,1004.107971, -938.740051, 42.42422); // prie vinewood
		CreatePickupA(1274 ,2,1943.108032, -1776.481689, 13.635081); // cj degaleliai
		CreatePickupA(1274 ,2,180.7695, 386.9162, 2.6452); // laivams
		CreatePickupA(1274 ,2, 1257.1649, -811.5940, 84.1406); // mano namas :)
		CreatePickupA(1274 ,2,-2027.1273,156.1537,29.0391); // sf centras
		CreatePickupA(1274 ,2,611.2366,1696.0830,6.9922); // prie lv
		CreatePickupA(1274 ,2,618.0706,1686.6412,6.9922); // prie lv
		CreatePickupA(1274 ,2,-1611.3607,-2722.0205,48.5391); // apacioj
		CreatePickupA(1274 ,2,655.0458,-565.0072,16.3359); // dillimore
		CreatePickupA(1274 ,2,2066.5549,-2548.1636,19.3621);
		CreatePickupA(1274,2,829.9098,-2071.8821,3.7080);
		// ballas
		CreatePickupA(1274 ,2,2521.2771,-1472.8452,24.0490);
		CreatePickupA(1274 ,2,2520.5891,-1478.5557,24.0590);
	}
	pickups[1][degaline]=CreatePickupA(1274 ,2,2067.5862,-2549.1460,13.5469); // oro uostas
	/*
	pickups[0][traukdegal]=CreatePickupA(1274,2,1751.0728,-1950.0059,13.5462); // Traukiniu DEG LS
		CreatePickupA(1274,2,2858.7947,1323.5166,11.3906); // Traukiniu DEG LV
		CreatePickupA(1274,2,1421.7234,2640.0938,11.3926); // Traukiniu DEG LV 2
	pickups[1][traukdegal]=CreatePickupA(1274,2,-1950.0244,142.6336,26.2813); // Traukiniu DEG SF
	*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	pickups[0][bankomatas]=CreatePickupA(1274 ,2,1610.1804,-2326.6047,13.5469);// BANKOMATAs ;D
	{
		CreatePickupA(1274 ,2,1854.9199,-1749.7072,3206.0859); // BANKOMATAS buvo prie automanu dbr jail
		CreatePickupA(1274 ,2,2232.6501,-1162.9500,25.8906); // BANKOMATAS
		CreatePickupA(1274 ,2,2820.2939,-1469.3621,16.2568); // BANKOMATAS
		CreatePickupA(1274 ,2,1811.3835,-1869.5535,13.5842); // BANKOMATAS
		CreatePickupA(1274 ,2,1631.8303,-1656.3499,13.6097); // BANKOMATAS
		CreatePickupA(1274 ,2,1302.9098,-797.2277,84.1406); // BANKOMATAS
		CreatePickupA(1274 ,2,1172.6854,-1319.1035,15.3937); // BANKOMATAS
		CreatePickupA(1274 ,2,3427.3325,-1660.0107,3.1988); // olimpinis
		CreatePickupA(1274,2,2157.5356,1599.6312,1006.1797); // casino
		CreatePickupA(1274,2,2042.3306,-1430.1816,17.1641); // prie privacios ligonines
		CreatePickupA(1274,2,1992.0450,1031.8245,994.4688); // casino four dragons
		CreatePickupA(1274,2,651.2588,-521.0915,16.1359); // dilimore
	}
	pickups[1][bankomatas]=CreatePickupA(1274 ,2,359.9899,-1803.0359,4.7196); // BANKOMATAS
	/////////////////////////////////////////////////////////////////////////
	pickups[0][gerimai]=CreatePickupA(1274 ,2,-2657.0027,1416.0853,906.2734);
	CreatePickupA(1274 ,2,-225.0728,1404.1805,27.7734);
	CreatePickupA(1274 ,2,495.0171,-76.0374,998.7578);
	CreatePickupA(1274 ,2,182.1227,-1811.6929,4.3881);
	CreatePickupA(1274,2,2000.3344,1005.4028,994.4688);
	pickups[1][gerimai]=CreatePickupA(1274 ,2,835.4216,-2007.0631,12.8672);
	pickups[0][baudam]=CreatePickupA(1274 ,2,1258.4417,563.6721,1067.6913);// bauda pd viduj
	pickups[1][baudam]=CreatePickupA(1274 ,2,325.5403,307.4812,999.1484);// bauda pd viduj dilimore
	// privati ligonine
	pickups[0][pligonine]=CreatePickupA(1274 ,2,-202.1688,-1741.7441,675.7687);// bauda pd viduj
////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
	//Stadionas
	pickups[0][stadionas]=CreatePickupA(1559 ,2,2695.5962,-1704.6184,11.8438); //I
	pickups[1][stadionas]=CreatePickupA(1559 ,2,-1442.9984,932.2237,1036.4900); //IS
	pickups[0][stadgalai]=CreatePickupA(1274 ,2,-1424.2174,931.4201,1036.4027); //Degalai pesciom
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
	pickups[0][laivotp]=CreatePickupA(1239 ,2, -2329.0654,1528.8497,0.4975); 
	pickups[0][inf1]=CreatePickupA(1239 ,2, 1735.2341,-1944.4779,13.5618); 
	pickups[0][inf2]=CreatePickupA(1239 ,2, 1751.1981,-1944.4370,13.5618); 
	pickups[0][fuleinfo]=CreatePickupA(1239 ,2, 2670.7007,-1810.2816,422.8215); 
	pickups[0][lsgsiena]=CreatePickupA(1239, 2, 1181.5242,-2046.8264,69.0078);
//	pickups[0][inf3]=CreatePickupA(1239 ,2, 1636.8876,-1705.6852,13.5110); 
	pickups[0][begtjail]=CreatePickupA(1239, 2, 3171.3145,-868.5535,9.3741);
	pickups[0][gerimaijack]=CreatePickupA(1274 ,2,218.4830,-1202.2859,75.3125);
/////////////////////////////////////////////////////////////////////////////////
	//pickups[1][gerimai]=CreatePickupA(1274 ,2,1210.7059,-14.8923,1000.9219);
	pickups[0][inkaofisas]=CreatePickupA(1274, 2,1553.1379,-1355.6760,226.4853);
	pickups[0][savegame]=CreatePickupA(1277 ,2,2260.5498,-1222.4381,1049.0234); //
	{
		CreatePickupA(1277 ,2,2233.9912,-1165.8258,1029.7969); //
		CreatePickupA(1277 ,2,2230.6248,-1185.1382,1029.7969); //
		CreatePickupA(1277 ,2,2210.6860,-1201.7000,1029.7969); //
		CreatePickupA(1277 ,2,2199.7458,-1174.9613,1029.8043); //
		CreatePickupA(1277 ,2,2187.1663,-1159.5842,1029.7969); //
	}
	pickups[1][savegame]=CreatePickupA(1277 ,2,2200.0374,-1161.3164,1029.7969); //

	pickups[0][dezes]=CreatePickupA(1230, 2, 3182.0803,-858.7607,10.0477); // Dezes
	{
		CreatePickupA(1230, 2, 3180.3669,-857.3898,9.9057); // Dezes
		CreatePickupA(1230, 2, 3179.1892,-855.9348,9.5456); // Dezes
		CreatePickupA(1230, 2, 3177.7507,-854.7341,9.3738); // Dezes

		CreatePickupA(1230, 2, 3182.0803,-858.7607,12.0477); // Dezes
		CreatePickupA(1230, 2, 3180.3669,-857.3898,11.9057); // Dezes
		CreatePickupA(1230, 2, 3179.1892,-855.9348,11.5456); // Dezes
	}
	pickups[1][dezes]=CreatePickupA(1230, 2, 3177.7507,-854.7341,11.3738); // Dezes
	
	//pickups[0][sautuvai]=CreatePickupA(1274 ,2, 2452.720459,-1963.575806,13.348365);
	
	//pickups[0][ukines]=CreatePickupA(1274 ,2, 2443.985352,-1963.212891,13.341334);
	pickups[0][loterija]=CreatePickupA(1274 ,2,822.2601,2.1007,1004.1797);
	pickups[0][valgis]=CreatePickupA(1274, 2,1867.4838,-1733.9126,3209.6880); // kalejime
	pickups[1][valgis]=CreatePickupA(1274, 2,1944.3390,1039.6155,992.4609); // four dragons 
	//CreatePickupA(1274 ,2,370.8077,-119.2070,1001.4995);
	
	//pickups[1][valgis]=CreatePickupA(1274 ,2,376.4373,-6.8294,1001.8516);
///////////////////////////////////////////////////////////////////////////////////////         
	pickups[0][MENTAI]=CreatePickupA(1220 ,2,1340.1013,516.2841,1067.7477); //mentu ginklai
	pickups[1][MENTAI]=CreatePickupA(1220 ,2,322.0873,317.1044,999.1484); //mentu ginklai dilimore
	pickups[0][aturgus]=CreatePickupA(1239 ,2,-2139.093017,219.994766,35.359375);
	pickups[0][parkas]=CreatePickupA(1239 ,2,-2482.002197,-285.251800,40.545665);
	pickups[0][KRANTAS]=CreatePickupA(1275 ,2,651.6191,-1871.2081,5.4609); //bakenonai 
	pickups[0][SIUKSLEVEZIS]=CreatePickupA(1275, 2,2201.2314,-1969.7465,13.7841); //siukslininkai
	//pickups[0][PICA]=CreatePickupA(1275 ,2,-2346.719238,-139.451797,35.554687); // //pica boy
	pickups[0][ARMIJAG]=CreatePickupA(1220 ,2,2770.5835,-2392.6445,13.6328); // Armijos ginklais TIKRAS
	pickups[0][slavejai]=CreatePickupA(1275,2,1636.3925,-1905.2928,13.5504); // slavejai
	pickups[0][BAIKERIUG]=CreatePickupA(1220 ,2,2809.7598,-1406.9023,-0.0484); // Baikeriu ginklai
        
    pickups[0][inkasatorius] = CreatePickupA(1275, 2,1562.3695,-1341.8190,226.4853);
    pickups[1][inkasatorius]=CreatePickupA(1220 ,2,1553.9972,-1341.1534,226.4853); //inkasatoriu ginklai
	pickups[0][ZINIOS]=CreatePickupA(1275 ,2,784.2620,-1333.0282,13.5406); //reporteriai
	pickups[0][VST]=CreatePickupA(1275 ,2,1345.8868,521.9305,1067.7562); //VST
	//pickups[0][VSTG]=CreatePickupA(1220 ,2,1087.3425,-1223.8234,15.8203);  //VST ginklu deze
	pickups[0][TRANS]=CreatePickupA(1275 ,2,895.9285,-1673.8705,13.5469); // Transporteris
	pickups[0][TEIS]=CreatePickupA(1275 ,2,1004.7285,-1125.1222,23.8984); // advokatas 
	pickups[0][KARDAS]=CreatePickupA(1220 ,2,302.23,-128.14,1004.06); // Ginklu dealerio ginklu paketas
	pickups[0][ZIN]=CreatePickupA(1275, 2,800.3235,-1323.3992,710.2907); // skelbejai
	pickups[0][kriminalika]=CreatePickupA(1275, 2,783.6016,-1380.9467,13.6776); // kriminalas
	pickups[0][turtas]=CreatePickupA(1275, 2,1870.0470,2430.2769,20.8316); // turtas 
	pickups[0][kunigas]=CreatePickupA(1275, 2,934.9195,-1085.8289,24.2891); // kunigas
	pickups[0][bmxxx]=CreatePickupA(1275, 2,1859.5493,-1392.1375,13.5625); // BMX
	pickups[0][baikeriai]=CreatePickupA(1275, 2,2809.5422,-1416.0919,16.2500); // BMX
	pickups[0][automanai]=CreatePickupA(1275, 2,2463.4329,2307.4607,91.7515); //Automanai
	pickups[0][pizza]=CreatePickupA(1275, 2,2104.4744,-1820.8206,13.5547); // Pizaa
	//pickups[0][limuzin]=CreatePickupA(1275, 2,477.1216,-1496.3582,20.4286); // limuzin    
	pickups[0][operatore]=CreatePickupA(1239 ,2,-2024.6622,-114.0485,1035.1719); //operatore
	pickups[0][bankas]=CreatePickupA(1550 ,2,2316.3713,-15.5894,26.7422); // bankas
	pickups[0][pelnininkas]=CreatePickupA(1550 ,2,2309.2727,-8.3591,26.7422); // twarkyt pelna
//	pickups[0][draudimas]=CreatePickupA(1314 ,2, 1675.6698,-1634.5798,14.2266); // draudimas
	pickups[0][draudimas]=CreatePickupA(1239 ,2, -2168.0098,643.5247,1052.3750); // draudimas
	pickups[0][farai]=CreatePickupA(1275 ,2,1345.7152,518.5157,1067.7562); //Faru darbas
	pickups[0][SWAT]=CreatePickupA(1275 ,2,915.6300,-1235.3546,17.2109); //SWAT
	pickups[1][SWAT]=CreatePickupA(1220 ,2,920.2745,-1240.4723,16.9766); //SWAT ginklai
	pickups[0][medikai]=CreatePickupA(1275 ,2,1173.082397, -1327.809937, 15.021232); //Mediku darbas
	pickups[0][privatus]=CreatePickupA(1275 ,2,2025.3667,-1404.1603,17.2109); //Privaciu Mediku darbas
	//pickups[0][taxi]=CreatePickupA(1275 ,2, 1490.2881,1305.0903,1093.2964); //Taxi darbas
	pickups[0][taxi]=CreatePickupA(1275 ,2, 991.6368,-4.8654,2740.5122); //Taxi darbas
	pickups[0][motomanai]=CreatePickupA(1275, 2, 1627.6857,-1002.4310,24.0646);
	//pickups[0][motomanai]=CreatePickupA(1275, 2, 895.9285,-1673.8705,13.5469); // motomanu darbas  
	//pickups[0][jachtos]=CreatePickupA(1275,2,723.1079,-1494.6093,1.9343); // jachtu klubas
	pickups[0][kobra]=CreatePickupA(1275,2,1776.9199,-1306.2755,13.6604);
	pickups[1][kobra]=CreatePickupA(1220,2,1797.7418,-1306.0280,13.6441);
	pickups[0][mikro]=CreatePickupA(1275 ,2,1539.5917,-2299.0200,13.5469); // Mikrushkes
	pickups[0][kurjerai]=CreatePickupA(1275, 2,1094.1445,2113.9644,15.3504);
	pickups[0][traukinys]=CreatePickupA(1275 ,2,1685.0159,-1944.7394,13.5469); //Traukinio darbas
	pickups[0][autobusas]=CreatePickupA(1275 ,2,1451.3656,-2355.0891,13.5469); //Autobusisto darbas
	pickups[0][ARMIJA]=CreatePickupA(1275, 2,2723.3723,-2416.0327,13.6276); // Armija
	pickups[0][pas]=CreatePickupA(1275, 2,210.1804,-1434.0956,13.2025); // pasienis
	pickups[0][pilotas]=CreatePickupA(1275, 2, 1596.6449,-2638.3730,13.5469); // pilotas
	pickups[0][mechanikas]=CreatePickupA(1275, 2, 1615.9764,-1526.8292,13.6237); // mechanikas
	//pickups[0][konfiskuota]=CreatePickupA(1274, 2, 1463.4097,-1496.8733,13.5469); //konfiskuotos
    pickups[0][konfiskavimas]=CreatePickupA(1247, 2, 1523.8451,-1493.8091,13.5620); //masinas priduodu cia
	pickups[0][gaisrinee]=CreatePickupA(1275, 2, 1466.5741,-999.7215,675.6033); //gaisrines darbas
	pickups[0][furistai]=CreatePickupA(1275, 2, 2474.5759,-2082.1638,13.6464); //Furistu darbas
	pickups[0][vagys]=CreatePickupA(1275, 2, 2598.2981,-2178.2754,1.0544); //vagys
	pickups[0][jail]=CreatePickupA(1247, 2, 3104.5986,-743.3250,11.0320); // jailas
	pickups[0][jail2]=CreatePickupA(1247, 2, 1568.6050,-1690.2515,5.8906); // jailas 2 PD
	pickups[1][jail2]=CreatePickupA(1247, 2, 611.1253,-584.6782,17.6409); // jailas 2 DILIMORE
	pickups[0][sokeja]=CreatePickupA(1275, 2, 745.6555,1438.9974,1102.7031);
	pickups[0][ukininkai]=CreatePickupA(1275,2,1090.9701,-306.0299,73.9922);
	//CreatePickupA(1247, 2, 1568.0664,-1478.3700,13.1723); taisykla
	pickups[0][darbinescar]=CreatePickupA(1247, 14, 1017.7556,-917.3123,42.4931);
	{
		CreatePickupA(1247, 14, 1911.2146,-1775.0718,13.5318);
		CreatePickupA(1247, 14,666.1385,-616.0114,16.3396);
		CreatePickupA(1247, 14,2066.8318,-2556.4392,19.3621); // malunsparniu.
	}
	pickups[1][darbinescar]=CreatePickupA(1247, 14, 2456.0039,-1460.7887,24.1489);
	pickups[0][pastininkai]=CreatePickupA(1239, 2, 616.8500,-1458.9423,14.4306);
	pickups[0][mokesciai]=CreatePickupA(1239, 2, 361.8299,173.6071,1008.3828);
	pickups[0][bankininkas]=CreatePickupA(1275 ,2,1473.3879,-1771.9489,18.7958); //Bankininkai
	pickups[0][statybininkas]=CreatePickupA(1275 ,2,1243.3801,-1258.2739,13.1690); //Statybininkai
	pickups[0][baikeriuuzd]=CreatePickupA(1247, 2, 2351.3904,-651.9200,127.6273); // baikeriu uzduotis/atrakinimas
	pickups[0][kontrabanda]=CreatePickupA(1275 ,2,1630.4290,-1845.7972,13.8913); //Kontrabanda
	pickups[0][dealer]=CreatePickupA(1275 ,2,1407.3196,-1300.3998,13.5503); //Dealeriai
	pickups[0][atomine]=CreatePickupA(19605, 2, 222.2627,1822.9048,5.2141);
	//Papildomi
	pickups[0][para] = CreatePickupA(371 ,2,3.7422,23.1672,1199.6012); //Parasiutas lektuve
	CreatePickupA(371 ,2, -2185.744629, 230.849060, 2667.396484); //Parasiutas lektuve
	pickups[1][para] =CreatePickupA(371 ,2, -2307.647217, -1617.564697, 1076.863647); //Parasiutas virs kalno

/////////////////////////////////////////////////////////////////////////////////////////////////////


/*
	pickups[0][backine]=CreatePickupA(1274 ,2,-986.79,-710.74,32.01);
	pickups[0][pridavimas]=CreatePickupA(1244 ,2,2478.93,-2078.63,13.55); //pas furistus
	{
		CreatePickupA(1244 ,2,-2414.9436,995.9910,45.3016); // 
        CreatePickupA(1244 ,2,-2038.6443,141.0242,28.8429); // 
        CreatePickupA(1244 ,2,-1700.5726,415.7048,7.1797); // 
        CreatePickupA(1244 ,2,1609.4260,2240.9463,10.8203); // 
        CreatePickupA(1244 ,2,2188.0750,2464.7031,11.2422); // 
        CreatePickupA(1244 ,2,2877.2361,920.4135,10.7500); // 
        CreatePickupA(1244 ,2,-72.2638,-1163.2455,1.8936); // 
        CreatePickupA(1244 ,2,638.3459,1683.8516,6.9922); // 
    }
	pickups[1][pridavimas]=CreatePickupA(1244 ,2,-1739.3656,177.4001,3.5547); // 

	pickups[0][telikai]=CreatePickupA(1221 ,2,-18.8600,-270.5700,5.4300); //pasikrauti teliku

	pickups[0][telikatv]=CreatePickupA(1230 ,2,2876.0300,920.5000,10.7500); //priduoti
    CreatePickupA(1230 ,2,1682.4900,2326.8700,10.8200); //priduoti
	pickups[1][telikatv]=CreatePickupA(1230 ,2,1438.2200,975.6000,10.8100); //priduoti

	pickups[0][pautai]=CreatePickupA(1299 ,2,-1866.5500,-1715.6100,22.7000); //pasikrauti kiausiniu

	pickups[0][pautatv]=CreatePickupA(1210 ,2,-2457.4172,790.4736,35.1719); //priduoti kiausinius
	pickups[1][pautatv]=CreatePickupA(1210 ,2,-2540.2522,-52.6456,16.5594); //priduoti kiausinius
*/




// KONTRABANDA
	pickups[0][gunkraut]=CreatePickupA(1254 ,2,255.2211,-158.0174,1.5703); //pasikrauti gun
	pickups[0][gunkraut2]=CreatePickupA(1254 ,2,-2107.7827,-2401.7698,31.3832);
	pickups[0][gunkraut3]=CreatePickupA(1254 ,2,-2430.1716,2314.5378,4.9844); 
	pickups[0][gunisk]=CreatePickupA(1254 ,2,1412.7268,-1304.4078,9.5317); //priduoti, pirkti gun


	pickups[0][narkraut]=CreatePickupA(1241 ,2,-1117.0293,-1621.2343,76.3739); //pasikrauti teliku

	pickups[0][narkisk]=CreatePickupA(1241 ,2,1407.7506,-1304.8969,9.0368); //priduoti

	pickups[0][kastuvas]=CreatePickupA(1221 ,2,-366.1150,2263.4016,42.6397); // KASTUVAS MIRES MIESTAS
	pickups[0][cilifon]=CreatePickupA(1274 ,2,1852.4066,-1750.1937,3206.0859); // Cilifon


	pickups[0][tazeriai]=CreatePickupA(18642,2,1339.8137,520.1154,1067.7477); // pd
	{
		CreatePickupA(18642,2,919.3408,-1251.9867,16.2109); // swat
	}
	pickups[1][tazeriai]=CreatePickupA(18642,2,2748.7827,-2451.8804,13.8623); // armija



	pickups[0][seklos]=CreatePickupA(1276, 2, -366.4687,-1423.9979,25.7266); //seklos
	pickups[0][lsdvieta]=CreatePickupA(1276, 2, -60.0339,47.9782,3.1103); //LSD
	pickups[0][ratuvieta]=CreatePickupA(1276, 2, 2318.1348,38.3088,26.4844); //RATAI
	pickups[0][pdvieta]=CreatePickupA(1276,2,213.9083,1866.8762,13.1406); // pd
	pickups[0][piniguvieta]=CreatePickupA(1276,2,2548.2683,-1293.5137,1044.1250);
	pickups[0][m4vieta]=CreatePickupA(1276,2,-1309.4672,501.9740,11.1953);
	//pickups[0][dovana]=CreatePickupA(19058, 2, 2302.3359,-1528.9720,26.9137);
	//pickups[0][elniai]=CreatePickupA(1239, 2, 391.5240,-1560.5220,29.5992);

	//pickups[0][roges]=CreatePickupA(19056, 2, 1976.8904,-2553.4766,13.5469);
	pickups[0][medikailiftas]=CreatePickupA(1239 ,2,1286.3759,-1329.3732,13.5530); // medikai liftas
	pickups[1][medikailiftas]=CreatePickupA(1239 ,2,1296.9393,-1324.7837,38.8828); // medikai liftas virsuj
	// zvejyba
	pickups[0][meskereshop]=CreatePickupA(1239, 2,386.7198,-1817.888,7.884);
	pickups[0][gydymas]=CreatePickupA(1239, 2,1167.2052,-1309.4410,1350.4003);
	pickups[0][sratasvydis]=CreatePickupA(1314, 2,-974.3956,1061.0923,1345.6760);
	CreatePickupA(1314,2,-1175.2446,-1018.6884,1129.3781);
	CreatePickupA(1314,2,-1086.9492,-967.9758,1129.3781);
	CreatePickupA(1314,2,2753.1478,-1897.6180,1060.7545);
	CreatePickupA(1314,2,2715.6992,-1838.1071,1060.7534);

	// miestas
	CreatePickupA(1314,2,-3654.3152,1592.4504,14.1313);
	CreatePickupA(1314,2,-3496.6931,1708.3046,13.9280);


	pickups[1][sratasvydis]=CreatePickupA(1314,2,-1131.4135,1057.5618,1346.4147);
	pickups[0][sratasvydis2]=CreatePickupA(1314, 2, 813.2457,65.2541,1205.6963);
	pickups[1][sratasvydis2]=CreatePickupA(1314,2,838.2165,29.5242,1205.6963);

	pickups[0][sratasvydis3]=CreatePickupA(1314, 2,-959.2112,1848.8022,9.0000);
	pickups[1][sratasvydis3]=CreatePickupA(1314,2,-957.8459,1952.1409,5.0000);

	pickups[0][jetpack]=CreatePickupA(370, 2, -938.5796,1848.5188,5.0000);
	pickups[1][jetpack]=CreatePickupA(370,2,-938.5903,1952.4993,5.0000);
	//Papildomi
	CreatePickupA(371 ,2,	3.7422,23.1672,1199.6012); //Parasiutas lektuve
	CreatePickupA(371 ,2, -2185.744629, 230.849060, 2667.396484); //Parasiutas lektuve
	CreatePickupA(371 ,2, 1600.8500,-2638.4116,13.5469); //Parasiutas prie darbo
	CreatePickupA(371 ,2, -2307.647217, -1617.564697, 1076.863647); //Parasiutas virs kalno
	
	pickups[0][taisykla] = CreatePickupA(3096,14,1526.4025,1642.5685,11.7228);

	// kurjerai

	//pickups[0][kurobak] = CreatePickupA(1650,2,1930.1796,-1785.3894,13.5469);
	//pickups[1][kurobak] = CreatePickupA(1650,2,1009.2345,-930.5139,42.1797);
		
	pickups[0][kortele] = CreatePickupA(1581,2,2306.1042,-0.8117,26.7422);
	//pickups[0][fever]= CreatePickupA(1252,2,-2237.3037,130.1799,1035.4141); // bomba
	pickups[0][regitra]= CreatePickupA(1581,2,1563.8010,-1554.7915,13.6372);
	
	pickups[0][bankocekiai]=CreatePickupA(1239, 2, 1131.6102,-354.6893,1055.4397); // BANKAI, PASIRINKTI OPERACIJA.
	pickups[0][bankoalgos]=CreatePickupA(1274, 2, 1137.4589,-361.8358,1055.4397); // BANKAI, pervesti algas
	pickups[0][bankopervedimai]=CreatePickupA(1274, 2, 1135.2079,-361.6229,1055.4397); // BANKAI, pervesti pinigus
	pickups[0][bankokortele]=CreatePickupA(1581, 2, 1132.9083,-361.6798,1055.4397); // BANKAI, Pasiimti kortele
	pickups[0][bankopop]=CreatePickupA(1274, 2, 1130.4135,-361.8669,1055.4397); // BANKAI, pasideti/paimti pinigus
	pickups[1][bankopop]=CreatePickupA(1274, 2, 1128.1134,-361.8667,1055.4397); // BANKAI, pasideti/paimti pinigus
	pickups[0][baldu_verslas]=CreatePickupA(1239, 2, 1999.8833,698.2463,2819.5959);
	pickups[0][elektr_verslas]=CreatePickupA(1239, 2, -884.2061,-1220.6892,3248.4958);
	pickups[0][interjer_verslas]=CreatePickupA(1239, 2, -900.8217,-2584.0078,2146.0549);
	pickups[0][transportosaugykla]=CreatePickupA(1318,2,2726.7976,-2003.9595,13.5472);
	
	//pickups[0][dovana]=CreatePickupA(19055, 2, 1715.2030,-1706.8192,14.1641);

	/*
	iejimas = CreatePickupA(1559, 2, 3088.5879,-782.1381,11.3664);
	eiti = CreatePickupA(1559, 2, 3213.1133, -976.1373, 282.9921);
	eiti2 = CreatePickupA(1559, 2, 3223.6257, -970.4005, 282.9921);
	kaleimas = CreatePickupA(1559, 2, 3195.0420, -977.6880, 286.9957); // ten kur iseisi is jail
	laukas = CreatePickupA(1559, 2, 3206.1143, -980.7029, 293.3473);
	lauke = CreatePickupA(1559, 2, 3105.1458,-819.6287,11.0997);
	ikameras = CreatePickupA(1559, 2, 3214.6392, -954.4645, 293.3473);
	iofisa = CreatePickupA(1559, 2, 3230.6790, -979.7006, 299.7059);
	kamerose = CreatePickupA(1559, 2, 3087.3621, -1515.5938, 106.0223);
	ofise = CreatePickupA(1559, 2, 3212.9063, -942.7680, 282.8607);
	*/
	iejimas = CreatePickupA(1559, 2, 3088.5879,-782.1381,11.3664);
	isejimas = CreatePickupA(1559, 2, 1862.2736,-1700.0896,3202.5859);
	laukas = CreatePickupA(1559, 2, 1847.8577,-1732.6593,3202.5859);
	lauke = CreatePickupA(1559, 2, 3105.1458,-819.6287,11.0997);
	//iaikstele = CreatePickupA(1559, 2, 3222.3635, -980.8408, 293.3473); // boksteliai
	//aikstele = CreatePickupA(1559, 2, 3236.6829,-783.9623,11.0545);
	
	entersp = CreatePickupA(1318,2,559.5461,-2033.9458,16.1743,20000);
	exitsp =  CreatePickupA(1318,2,559.5261,-2095.8760,2.6254,20000);
	entersauna = CreatePickupA(1318,2,570.5856,-2095.8291,2.6077,20000);
	exitsauna = CreatePickupA(1318,2,530.4130,-2082.5781,17.2253,20000);
	bigjump = CreatePickupA(1318,2,578.6855,-2195.5337,1.6288,20000);
	anima = CreatePickupA(1318,2,578.6855,-2195.5337,1.6288,20000);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////