#define NO_LEAD 0
#define LEAD_MEDIKAI 2
#define LEAD_TRANSPORTAS 3
#define LEAD_APSAUGA 4
#define LEAD_FURISTAS 5
#define LEAD_AUTOSPECAI 6
#define LEAD_GAISRAS 66
#define LEAD_KLUBAI 70
#define LEAD_TEISESAUGA 80
#define LEAD_VALSTYBE 50
#define LEAD_GIDAI 53
#define LEAD_BAIKERIAI 98
#define LEAD_DEAL 90
#define LEAD_PADUGNES 58

forward WantPickup(playerid);


enum item{
hasmoney,
montuoja,
adr,
bool:dirtymoney,
bool:droppedgibs,
bool:pospawn,
bool:varmor,
bool:treniruojasi,
bool:vgun,
bool:laikrastis,
bool:teises,
bool:teisess,
bool:teisesm,
bool:spaz,
bool:mire,
bool:pickup,
bool:ikalintas,
bool:pasislepes,
bool:bilietas,
bool:atvaziavobank,
bool:telon,
bool:narkomanas,
bool:suristas,
bool:admin,
bool:prez,
bool:jisbanke,
bool:rbool[2],
bool:leanvited[100],
bool:fejerverkai[8],
bool:teor,
bool:ginvited[6],
bool:tiuningykloj,
bool:uniformd,
bool:bypass,
bool:pila,
bool:logina,
bool:laikrodis,
bool:gunk[52],
bool:pucia,
bool:vip,
bool:ant,
bool:kortele,
bool:imtuvas,
bool:virve,
bool:banned,
bool:meskere,
minuoja,
bool:zvejoja,
bool:kimba,
bool:bakelis,
kills,
raktas,
kreditai,
balas, // vm ;D
masina,
banke,
wstyle,
stotis,
klausoimtuvo,
apmokymai,
klausosi,
klausoisadmin,
textas,
jobpts,
leidimas,
pradirbo,
zole,
amfetaminas,
perveda,
loterijos,
bool:specina,
paskutinisrubas,
issirinkoak, // akinius
specialybe,
kalejimo_laikas,
kalejimo_total,
rkaina[2],
rid[7],
rkiekis[2],
rrusis,
namu,
gesintuvok,
draudimas,
authstate,
psratasvydis,
narko[3],
pastas[10],
ratai,
lsd,
pgang,
biznis,
lytis,
drabuziai,
uniforma,
skambutis,
lektuvas,
mobsas,
plead,
spdata[31],
Float:spos[3],
Float:shealth[2],
Float:sotumas,
pinigai,
bool:draudimasg,
seklos,
pFS,
pBoxiSkill,
pKneeSkill,
pKungSkill,
pGrabSkill,
pElbowSkill,
pCar,
pAirbreaking,
airbrk,
pLastCheck,
Float:pCurrentPos[3],
Float:pSetPos[3],
ammok[52],
akiniai,
masalas,
zuvis,
MotoTest,
DrivingTest,
FlyingTest,
bool:SpawnDance,
Float:SpawnAngle,
SpawnTimer,
maistas,
maistaslauk,
aksesuaras,
kepure,
salmas,
imaginkla,
cekis,
daiktas,
action,
actionmax,
cigaretes,
bool:parukes,
ruko,
invisible,
pjauna,
baikeruzd,
playingpoker,
pligonis
}

new playerDB[MAX_PLAYERS][item];



stock LoadSpawns(){
AddPlayerClass(20,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(7,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(19,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(22,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(23,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(26,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(46,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(58,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(101,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(111,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(147,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(186,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(188,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(202,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(223,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);


// bobos
AddPlayerClass(55,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(56,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(93,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(190,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(192,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(211,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(298,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(233,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(226,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(192,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
AddPlayerClass(193,1743.1915,-1944.5928,13.5661,173.6375,0,0,0,0,0,0);
}


stock AllignMaxPlayers()
{
	if(MAX_PLAYERS<GetServerVarAsInt("maxplayers"))
	{
		printf("Warning: The Player number is higher than expected, please lower the number to atleast: %i",MAX_PLAYERS);
		print("RPGLT: The server cannot continue and will now be killed.");
		new msg[2];
		SendClientMessageToAll(0,msg);
	}
}



public WantPickup(playerid) playerDB[playerid][pickup]=true;