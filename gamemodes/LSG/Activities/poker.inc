// This is a comment
// uncomment the line below if you want to write a filterscript

#include <a_samp>

#include <md-sort>

#define POKERLAPS 52 // 4 * 13 laps (2, 3 ... K, A
#define SOUND_CHECK 1163
#define SOUND_FOLD 1085
#define SOUND_CALL 1054
#define SOUND_RAISE 1083
#define SOUND_WIN 5448 // 5449 5450
#define SOUND_BYE 5453 // 5454
#define SOUND_NEBERA 5405// - "Sir doesn't have sufficient money to back another bet."
#define SOUND_NETURI 5406// - neturi pakankamai pinigu
#define TEXTDRAW_FOLD -1431655851
#define TEXDRAW_DEFAULT -1
#define POKER_ROUND_TIME 20
#define notstock:%0(%1) forward %0(%1); public %0(%1)
enum
{
	TWO = 2,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE
};

new
	LD_POKE[POKERLAPS][] =
{
	{ "LD_POKE:cd2c" }, { "LD_POKE:cd3c" }, { "LD_POKE:cd4c" }, { "LD_POKE:cd5c" }, { "LD_POKE:cd6c" }, { "LD_POKE:cd7c" }, { "LD_POKE:cd8c" },
	{ "LD_POKE:cd9c" }, { "LD_POKE:cd10c" }, { "LD_POKE:cd11c" }, { "LD_POKE:cd12c" }, { "LD_POKE:cd13c" }, { "LD_POKE:cd1c" },

	{ "LD_POKE:cd2d" }, { "LD_POKE:cd3d" }, { "LD_POKE:cd4d" }, { "LD_POKE:cd5d" }, { "LD_POKE:cd6d" }, { "LD_POKE:cd7d" }, { "LD_POKE:cd8d" },
	{ "LD_POKE:cd9d" }, { "LD_POKE:cd10d" }, { "LD_POKE:cd11d" }, { "LD_POKE:cd12d" }, { "LD_POKE:cd13d" }, { "LD_POKE:cd1d" },

	{ "LD_POKE:cd2h" }, { "LD_POKE:cd3h" }, { "LD_POKE:cd4h" }, { "LD_POKE:cd5h" }, { "LD_POKE:cd6h" }, { "LD_POKE:cd7h" }, { "LD_POKE:cd8h" },
	{ "LD_POKE:cd9h" }, { "LD_POKE:cd10h" }, { "LD_POKE:cd11h" }, { "LD_POKE:cd12h" }, { "LD_POKE:cd13h" }, { "LD_POKE:cd1h" },

	{ "LD_POKE:cd2s" }, { "LD_POKE:cd3s" }, { "LD_POKE:cd4s" }, { "LD_POKE:cd5s" }, { "LD_POKE:cd6s" }, { "LD_POKE:cd7s" }, { "LD_POKE:cd8s" },
	{ "LD_POKE:cd9s" }, { "LD_POKE:cd10s" }, { "LD_POKE:cd11s" }, { "LD_POKE:cd12s" }, { "LD_POKE:cd13s" }, { "LD_POKE:cd1s" }
};

/*
new ranks[13][3] = 
{
"2",
"3",
"4",
"5",
"6",
"7",
"8",
"9",
"10",
"J",
"Q",
"K",
"A"	
};

new suits[4] =
{
'C', // kryziai
'D',
'H',
'S' 
};
*/

//new ranks[13];
enum card
{
	rank,
	suit
};
#define MAX_POKER_GAMES 5
enum TheGame
{
	GameUsed=0,
	players[6],
	watching,
	//Cards[Card],
	CardsR[52],
	CardsS[52],
	TableR[5],
	TableS[5],
	CardsUsed,
	Bankas,
	DabartinisStat,
	Eile,
	Playing[6],
	PStatymas[6],
	LastSmall,
	SmallBlind,
	BigBlind,
	FirstTurn,
	PFondas[6],
	TheStep,
	handPoints[6],
	Text:TableKorta[5],
	Text:JusuEile,
	Text:BankTD,
	Text:PokerName[6],
	Text:PokerMoney[6],
	Text:PokerAction[6],
	PBankai[6],
	TimeLeft,
	PlayerCombo[6],
	PlayerComboCard[6],
	PlayerSecond[6],
	PlayerKicker1[6],
	PlayerKicker2[6],
	PlayerKicker3[6]
};
/*


*/
new Poker[MAX_POKER_GAMES][TheGame];
//new 
new PHand[MAX_PLAYERS][2][card];
new hand[5][card] = 
{ {0,0},{0,0},{0,0},{0,0},{0,0}
};

new PlayerText:Korta[MAX_PLAYERS][6][2];
new PlayerText:Mygtukas[5][MAX_PLAYERS];
//new Text:JusuEile;
//new Text:TableKorta[5];

stock shuffle(id)
{
	for (new i=0;i<4;i++)
	{
		for (new j=0;j<13;j++)
		{
			Poker[id][CardsS][i*13+j] = i;
			Poker[id][CardsR][i*13+j] = j;
		}
	}	
		
	
	//sleep(2);
	new tempCard[2];
	new x;
	for (new z;z<2;z++)
	{
		for (new i=0;i<52;i++)
		{
			x = random(52);
			tempCard[0] = Poker[id][CardsR][i];
			tempCard[1] = Poker[id][CardsS][i];
			Poker[id][CardsR][i] = Poker[id][CardsR][x];
			Poker[id][CardsS][i] = Poker[id][CardsS][x];
			Poker[id][CardsR][x] = tempCard[0];
			Poker[id][CardsS][x] = tempCard[1];
		}
	}
}

stock evaluateHands(id)
{
	//printf("Pradzia: %i",GetTickCount());
//	new handas[7][card];
	//new array[7][Card];
	new combo,combocard,second,kicker1,kicker2,kicker3;
	// senas: [7][6][5][4][3] = 2520
	for(new i;i<6;i++)
	{
		if(Poker[id][players][i] != -1 && Poker[id][Playing][i])
		{
			for(new a;a<5;a++)
			{
				for(new b;b<5;b++)
				{
					if(b != a)
					{
						for(new c;c<5;c++)
						{
							if(c != a && c != b)
							{
								hand[0][rank]=Poker[id][TableR][a];
								hand[0][suit]=Poker[id][TableS][a];
								hand[1][rank]=Poker[id][TableR][b];
								hand[1][suit]=Poker[id][TableS][b];
								hand[2][rank]=Poker[id][TableR][c];
								hand[2][suit]=Poker[id][TableS][c];
								hand[3]=PHand[Poker[id][players][i]][0];
								hand[4]=PHand[Poker[id][players][i]][1];
								//currentPoints = getScore(Poker[id][players][i],Poker[id][PlayerCombo][i],Poker[id][PlayerSecond][i],Poker[id][PlayerKicker1][i],Poker[id][PlayerKicker2][i],Poker[id][PlayerKicker3][i]);
								getScore(Poker[id][players][i],combo,combocard,second,kicker1,kicker2,kicker3);
								if (combo > Poker[id][PlayerCombo][i])
								{
									Poker[id][PlayerCombo][i]=combo;
									Poker[id][PlayerComboCard][i]=combocard;
									Poker[id][PlayerSecond][i]=second;
									Poker[id][PlayerKicker1][i]=kicker1;
									Poker[id][PlayerKicker2][i]=kicker2;
									Poker[id][PlayerKicker3][i]=kicker3;
								}
								else if(combo == Poker[id][PlayerCombo][i])
								{
									if(combocard > Poker[id][PlayerComboCard][i])
									{
										Poker[id][PlayerComboCard][i]=combocard;
										Poker[id][PlayerSecond][i]=second;
										Poker[id][PlayerKicker1][i]=kicker1;
										Poker[id][PlayerKicker2][i]=kicker2;
										Poker[id][PlayerKicker3][i]=kicker3;
									}
									else if(combocard == Poker[id][PlayerComboCard][i])
									{
										if(second > Poker[id][PlayerSecond][i])
										{
											Poker[id][PlayerSecond][i]=second;
											Poker[id][PlayerKicker1][i]=kicker1;
											Poker[id][PlayerKicker2][i]=kicker2;
											Poker[id][PlayerKicker3][i]=kicker3;
										}
										else if(second == Poker[id][PlayerSecond][i])
										{
											if(kicker1 > Poker[id][PlayerKicker1][i])
											{
												Poker[id][PlayerKicker1][i]=kicker1;
												Poker[id][PlayerKicker2][i]=kicker2;
												Poker[id][PlayerKicker3][i]=kicker3;			
											}
											else if(kicker1==Poker[id][PlayerKicker1][i])
											{
												if(kicker2>Poker[id][PlayerKicker2][i])
												{
													Poker[id][PlayerKicker2][i]=kicker2;
													Poker[id][PlayerKicker3][i]=kicker3;	
												}
												else if(kicker2 == Poker[id][PlayerKicker2][i])
												{
													if(kicker3 > Poker[id][PlayerKicker3][i])
													{
														Poker[id][PlayerKicker3][i]=kicker3;
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			// [5][4][3] = 60
			for(new a;a<2;a++)
			{
				for(new b;b<5;b++)
				{
					for(new x;x<5;x++)
					{
						hand[x][rank]=Poker[id][TableR][x];
						hand[x][suit]=Poker[id][TableS][x];
					}
					//temp=hand[b];
					hand[b]=PHand[Poker[id][players][i]][a];
					getScore(Poker[id][players][i],combo,combocard,second,kicker1,kicker2,kicker3);
					if (combo > Poker[id][PlayerCombo][i])
					{
						Poker[id][PlayerCombo][i]=combo;
						Poker[id][PlayerComboCard][i]=combocard;
						Poker[id][PlayerSecond][i]=second;
						Poker[id][PlayerKicker1][i]=kicker1;
						Poker[id][PlayerKicker2][i]=kicker2;
						Poker[id][PlayerKicker3][i]=kicker3;
					}
					else if(combo == Poker[id][PlayerCombo][i])
					{
						if(combocard > Poker[id][PlayerComboCard][i])
						{
							Poker[id][PlayerComboCard][i]=combocard;
							Poker[id][PlayerSecond][i]=second;
							Poker[id][PlayerKicker1][i]=kicker1;
							Poker[id][PlayerKicker2][i]=kicker2;
							Poker[id][PlayerKicker3][i]=kicker3;
						}
						else if(combocard == Poker[id][PlayerComboCard][i])
						{
							if(second > Poker[id][PlayerSecond][i])
							{
								Poker[id][PlayerSecond][i]=second;
								Poker[id][PlayerKicker1][i]=kicker1;
								Poker[id][PlayerKicker2][i]=kicker2;
								Poker[id][PlayerKicker3][i]=kicker3;
							}
							else if(second == Poker[id][PlayerSecond][i])
							{
								if(kicker1 > Poker[id][PlayerKicker1][i])
								{
									Poker[id][PlayerKicker1][i]=kicker1;
									Poker[id][PlayerKicker2][i]=kicker2;
									Poker[id][PlayerKicker3][i]=kicker3;			
								}
								else if(kicker1==Poker[id][PlayerKicker1][i])
								{
									if(kicker2>Poker[id][PlayerKicker2][i])
									{
										Poker[id][PlayerKicker2][i]=kicker2;
										Poker[id][PlayerKicker3][i]=kicker3;	
									}
									else if(kicker2 == Poker[id][PlayerKicker2][i])
									{
										if(kicker3 > Poker[id][PlayerKicker3][i])
										{
											Poker[id][PlayerKicker3][i]=kicker3;
										}
									}
								}
							}
						}
					}
				}
			} 
			// [5]*2 = 10
			for(new x;x<5;x++)
			{
				hand[x][rank]=Poker[id][TableR][x];
				hand[x][suit]=Poker[id][TableS][x];
			}
			getScore(Poker[id][players][i],combo,combocard,second,kicker1,kicker2,kicker3);
			if (combo > Poker[id][PlayerCombo][i])
			{
				Poker[id][PlayerCombo][i]=combo;
				Poker[id][PlayerComboCard][i]=combocard;
				Poker[id][PlayerSecond][i]=second;
				Poker[id][PlayerKicker1][i]=kicker1;
				Poker[id][PlayerKicker2][i]=kicker2;
				Poker[id][PlayerKicker3][i]=kicker3;
			}
			else if(combo == Poker[id][PlayerCombo][i])
			{
				if(combocard > Poker[id][PlayerComboCard][i])
				{
					Poker[id][PlayerComboCard][i]=combocard;
					Poker[id][PlayerSecond][i]=second;
					Poker[id][PlayerKicker1][i]=kicker1;
					Poker[id][PlayerKicker2][i]=kicker2;
					Poker[id][PlayerKicker3][i]=kicker3;
				}
				else if(combocard == Poker[id][PlayerComboCard][i])
				{
					if(second > Poker[id][PlayerSecond][i])
					{
						Poker[id][PlayerSecond][i]=second;
						Poker[id][PlayerKicker1][i]=kicker1;
						Poker[id][PlayerKicker2][i]=kicker2;
						Poker[id][PlayerKicker3][i]=kicker3;
					}
					else if(second == Poker[id][PlayerSecond][i])
					{
						if(kicker1 > Poker[id][PlayerKicker1][i])
						{
							Poker[id][PlayerKicker1][i]=kicker1;
							Poker[id][PlayerKicker2][i]=kicker2;
							Poker[id][PlayerKicker3][i]=kicker3;			
						}
						else if(kicker1==Poker[id][PlayerKicker1][i])
						{
							if(kicker2>Poker[id][PlayerKicker2][i])
							{
								Poker[id][PlayerKicker2][i]=kicker2;
								Poker[id][PlayerKicker3][i]=kicker3;	
							}
							else if(kicker2 == Poker[id][PlayerKicker2][i])
							{
								if(kicker3 > Poker[id][PlayerKicker3][i])
								{
									Poker[id][PlayerKicker3][i]=kicker3;
								}
							}
						}
					}
				}
			}
		}
	}
	// 5
	// suma: 75 < 2520
	/*
	for(new i;i<5;i++)
	{
		handas[i][rank]=Poker[id][TableR][i];
		handas[i][suit]=Poker[id][TableS][i];
	}
	for(new i;i<6;i++)
	{
		currentPoints=0;
		if(Poker[id][players][i] != -1 && Poker[id][Playing][i])
		{
			for(new x;x<2;x++)
			{
				handas[x+5] = PHand[Poker[id][players][i]][x];
			}
			for(new a;a<7;a++) // 1 korta
			{
				for(new b;b<7;b++) // 2 korta
				{
					if(b != a)
					{
						for(new c;c<7;c++) // 3 korta
						{
							if(c != a && c != b)
							{
								for(new d;d<7;d++) // 4 korta
								{
									if(d != a && d != b && d != c)
									{
										for(new e;e<7;e++) // 5 korta
										{
											if(e != a && e != b && e != c && e != d)
											{
												hand[0]=handas[a];
												hand[1]=handas[b];
												hand[2]=handas[c];
												hand[3]=handas[d];
												hand[4]=handas[e];
												
												currentPoints = getScore(Poker[id][players][i]);
												if (currentPoints>Poker[id][handPoints][i])
												{
													Poker[id][handPoints][i] = currentPoints;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	*/
	//printf("/: %i",GetTickCount());
}

//1 2 3 4 5


/*
stock evaluateHands(id)
{
	new stack[10],k;
	new currentPoints;
	for(new i;i<6;i++)
	{
		if(Poker[id][players][i] != -1 && Poker[id][Playing][i])
		{
			// keiciam 2 kortas
			stack[0]=-1; 
			new x=0;
			k=0;
			while(x==0)
			{
				if (stack[k]<4){
					stack[k+1] = stack[k] + 1;
					k++;
				}
				else{
					stack[k-1]++;
					k--;
				}

				if (k==0)
					x=1;

				if (k==3)
				{
					currentPoints = tryHand(stack,i,id);
					if (currentPoints>Poker[id][handPoints][i]){
						Poker[id][handPoints][i] = currentPoints;
					}
				}
			}
			// keiciam 1 korta
			x=0;
			k=0;
			stack[0]=-1; 
			while(x==0)
			{
				if (stack[k]<4)
				{
					stack[k+1] = stack[k] + 1;
					k++;
				}
				else
				{
					stack[k-1]++;
					k--;
				}

				if (k==0)
					x=1;

				if (k==4)
				{
					currentPoints = tryHandEx(stack,i,id);
					if (currentPoints>Poker[id][handPoints][i]){
						Poker[id][handPoints][i] = currentPoints;
					}
				}
			}
		}
	}

}
*/
/*
stock tryHand(array[],player,id)
{

	for (new i=1;i<4;i++)
	{
		//hand[i-1] = Table[array[i]];
		hand[i-1][rank] = Poker[id][TableR][array[i]];
		hand[i-1][suit] = Poker[id][TableS][array[i]];
	}
	for (new i=0;i<2;i++)
		hand[i+3] = PHand[Poker[id][players][player]][i];

	return getScore(Poker[id][players][player]);
	
}
*/
forward EndGame(id);
public EndGame(id)
{
	for(new i;i<5;i++)
	{
		TextDrawHideForAll(Poker[id][TableKorta][i]);
		//TextDrawDestroy(TableKorta[i]);
	}
	//TextDrawDestroy(JusuKortos);
	new z;
	for(new i;i<6;i++)
	{
		if(Poker[id][players][i] != -1)
		{
			z++;
			new playerid = Poker[id][players][i];
			for(new y;y<6;y++)
			{
				for(new x;x<2;x++)
					PlayerTextDrawHide(playerid,Korta[playerid][y][x]);
			}
			for(new x;x<5;x++)
				PlayerTextDrawHide(playerid,Mygtukas[x][playerid]);
		}
	}
	if(z > 1)
		NewSet(id);
	else
		EndPokerGame(id);
	return 1;
}
stock LeaveGame(playerid,id,pid,esc=0,ending=0)
{
	PlaySoundForPoker(id,playerid,SOUND_BYE+random(2));
	for(new i;i<5;i++)
	{
		TextDrawHideForPlayer(playerid,Poker[id][TableKorta][i]);
		//TextDrawDestroy(TableKorta[i]);
	}
	TextDrawSetString(Poker[id][PokerAction][pid],"Leave");
	//TextDrawDestroy(JusuKortos);
	TextDrawHideForPlayer(playerid,Poker[id][BankTD]);
	TextDrawHideForPlayer(playerid,Poker[id][JusuEile]);
	for(new y;y<6;y++)
	{
		TextDrawHideForPlayer(playerid,Poker[id][PokerAction][y]);
		TextDrawHideForPlayer(playerid,Poker[id][PokerMoney][y]);
		TextDrawHideForPlayer(playerid,Poker[id][PokerName][y]);
		for(new x;x<2;x++)
		{
			PlayerTextDrawHide(playerid,Korta[playerid][y][x]);
			PlayerTextDrawDestroy(playerid,Korta[playerid][y][x]);
		}
	}
	for(new x;x<5;x++)
	{
		PlayerTextDrawHide(playerid,Mygtukas[x][playerid]);
		PlayerTextDrawDestroy(playerid,Mygtukas[x][playerid]);
	}
	GivePlayerMoneyA(playerid,Poker[id][PFondas][pid]);
	Poker[id][Playing][pid]=0;
	Poker[id][players][pid]=-1;
	//Poker[id][PFondas][pid]=0;
	Poker[id][Bankas]+=Poker[id][PStatymas][pid];
	Poker[id][PBankai][pid]+=Poker[id][PStatymas][pid];
	Poker[id][PStatymas][pid]=0;
	playerDB[playerid][playingpoker]=0;
	SetCameraBehindPlayer(playerid);
	if(!esc) 
		CancelSelectTextDraw(playerid);
	ApplyAnimation(playerid, "CARRY", "crry_prtial", 1.0, 0, 0, 0, 0, 0);
	if(!ending)
	{
		if(Poker[id][Eile]==pid)
		{
			Poker[id][Eile]=NextTurn(id,pid);
			Poker[id][Playing][pid]=0;
			NextPlayer(id);
		}
		else
		{
			new var;
			for(new x;x<6;x++)
			{
				if(Poker[id][players][x] != -1) var++;
			}
			if(var < 2) return EndPokerGame(id,1);
		}
		if(Poker[id][FirstTurn]==pid)
		{
			Poker[id][FirstTurn] = NextTurn(id,pid);
		}
	}
	
	AddPokerQuePlayer(id);
	/*
	new da,dx,leid;
	for(new x;x<6;x++)
	{
		if(Poker[id][players][x] != -1) da++;
		if(Poker[id][Playing][x])
		{
			dx++;
			leid=x;
		}
	}
	if(da==1) { EndPokerGame(id); return 0;}
	else if(dx == 1)
	{
		Poker[id][PFondas][leid]+=Poker[id][Bankas];
		Poker[id][Bankas]=0;
		NewSet(id);
	}*/
	return 1;
}
stock InitPokerGame(id,small,big,plone,pltwo)
{
	/*new id=-1;
	for(new i;i<MAX_POKER_GAMES;i++)
	{
		if(!Poker[i][GameUsed])
		{
			Poker[i][GameUsed]=1,id=i;
			break;
		}
	}
	if(id==-1) return 0; */
	Poker[id][watching]=-1;
	Poker[id][Bankas]=0;
	Poker[id][GameUsed]=1;
	Poker[id][DabartinisStat]=0;
	Poker[id][CardsUsed]=0;
	Poker[id][Eile]=0;
	Poker[id][SmallBlind]=small;
	Poker[id][BigBlind]=big;
	Poker[id][TimeLeft]=POKER_ROUND_TIME+5;
	shuffle(id);
	//new playerid[6] = {-1,...};
	for(new i;i<6;i++)
	{
		Poker[id][players][i]=-1;
		
	}
	Poker[id][players][0]=plone;
	Poker[id][players][1]=pltwo;
	Poker[id][Playing][0]=1;
	Poker[id][Playing][1]=1;
	CreatePlayerTextDraws(plone);
	CreatePlayerTextDraws(pltwo);

	CreatePokerTextDraws(id);
	NewSet(id);
	return id;
}
stock EndPokerGame(id,prize=0)
{
	if(prize) GivePrize(id);
	Poker[id][GameUsed]=0;

	if(Poker[id][watching] != -1)
	{
		new playerid = Poker[id][watching];
		Poker[id][watching]=-1;
		for(new i;i<5;i++)
		{
			TextDrawHideForPlayer(playerid,Poker[id][TableKorta][i]);
			//TextDrawDestroy(TableKorta[i]);
		}
		//TextDrawDestroy(JusuKortos);
		TextDrawHideForPlayer(playerid,Poker[id][BankTD]);
		TextDrawHideForPlayer(playerid,Poker[id][JusuEile]);
		for(new y;y<6;y++)
		{
			TextDrawHideForPlayer(playerid,Poker[id][PokerAction][y]);
			TextDrawHideForPlayer(playerid,Poker[id][PokerMoney][y]);
			TextDrawHideForPlayer(playerid,Poker[id][PokerName][y]);
			for(new z;z<2;z++)
			{
				PlayerTextDrawHide(playerid,Korta[playerid][y][z]);
				PlayerTextDrawDestroy(playerid,Korta[playerid][y][z]);
			}
		}
		for(new z;z<5;z++)
		{
			PlayerTextDrawHide(playerid,Mygtukas[z][playerid]);
			PlayerTextDrawDestroy(playerid,Mygtukas[z][playerid]);
		}
	}
	for(new i;i<5;i++)
	{
		TextDrawDestroy(Poker[id][TableKorta][i]);
	}
	TextDrawDestroy(Poker[id][JusuEile]);
	TextDrawDestroy(Poker[id][BankTD]);
	for(new i;i<6;i++)
	{
		TextDrawDestroy(Poker[id][PokerName][i]);
		TextDrawDestroy(Poker[id][PokerAction][i]);
		TextDrawDestroy(Poker[id][PokerMoney][i]);
		if(Poker[id][players][i] != -1)
		{
			new playerid = Poker[id][players][i];
			LeaveGame(playerid,id,i,0,1);
		}
	}
	return 1;

}
stock NewSet(id)
{
	//Poker[id][handPoints][i]
	Poker[id][TimeLeft]=POKER_ROUND_TIME+5;
	Poker[id][CardsUsed]=0;
	Poker[id][TheStep]=0;
	shuffle(id);
	TextDrawSetString(Poker[id][BankTD],"0EUR");
	new txt[128];
	new txt2[128];
	format(txt,sizeof(txt),"S.Blind(%iEUR)",Poker[id][SmallBlind]);
	format(txt2,sizeof(txt2),"B.Blind(%iEUR)",Poker[id][BigBlind]);
//	TextDrawSetString(Poker[id][PokerAction][x],txt);
//	TextDrawShowForPlayer(playerid,Poker[id][PokerAction][x]);
	for(new i;i<6;i++)
	{
		Poker[id][PBankai][i]=0;
		if(Poker[id][players][i] == -1) continue;
		ProcessAchievement(Poker[id][players][i],60);
		if(Poker[id][PFondas][i] < Poker[id][BigBlind])
		{
			if(!LeaveGame(Poker[id][players][i],id,i))
				break;
			continue;
		}
		Poker[id][PlayerCombo][i]=0;
		Poker[id][PlayerComboCard][i]=0;
		Poker[id][PlayerSecond][i]=0;
		Poker[id][PlayerKicker1][i]=0;
		Poker[id][PlayerKicker2][i]=0;
		Poker[id][PlayerKicker3][i]=0;
		Poker[id][handPoints][i]=0;
		Poker[id][Playing][i]=1;
		Poker[id][PStatymas][i]=0;
		for(new x;x<2;x++)
		{
			PHand[Poker[id][players][i]][x][rank]=Poker[id][CardsR][Poker[id][CardsUsed]];
			PHand[Poker[id][players][i]][x][suit]=Poker[id][CardsS][Poker[id][CardsUsed]];
			for(new y;y<6;y++)
				PlayerTextDrawSetString(Poker[id][players][i],Korta[Poker[id][players][i]][y][x],"LD_POKE:cdback");
				
			Poker[id][CardsUsed]++;
		}
		TextDrawShowForPlayer(Poker[id][players][i],Poker[id][BankTD]);
		TextDrawSetString(Poker[id][PokerAction][i],"-");
		
		//TextDrawShowForPlayer(playerid,Poker[id][PokerAction][x]);
		//Poker[id][CardsUsed]-
	}
	if(Poker[id][watching] != -1)
		TextDrawShowForPlayer(Poker[id][watching],Poker[id][BankTD]);
	
	new pid = NextTurn(id,Poker[id][LastSmall]-1);
	if(pid != -1) Poker[id][PStatymas][pid]=Poker[id][SmallBlind];
	Poker[id][LastSmall] = pid;
	new pid2 = NextTurn(id,pid);
	if(pid2 != -1) Poker[id][PStatymas][pid2]=Poker[id][BigBlind];
	Poker[id][Eile] = NextTurn(id,pid2);
	Poker[id][FirstTurn]=Poker[id][Eile];
	if(pid != -1)TextDrawSetString(Poker[id][PokerAction][pid],txt);
	if(pid2 != -1) TextDrawSetString(Poker[id][PokerAction][pid2],txt2);
	if(Poker[id][Eile] != -1) ShowJusuEile(Poker[id][players][Poker[id][Eile]], id);
	//TextDrawSetString(Poker[id][PokerName][x],"Action");
	//TextDraw
	//TextDrawShowForPlayer(playerid,Poker[id][PokerAction][x]);
	//TextDrawSetTring
	//Poker[id][FirstTurn]=Poker[id][Eile];
	for(new i;i<6;i++)
	{
		if(Poker[id][PStatymas][i])
		{
			Poker[id][PFondas][i]-=Poker[id][PStatymas][i];
		}
	}
	//Poker[id][Bankas]+=small+big;
	Poker[id][DabartinisStat]+=Poker[id][SmallBlind]+Poker[id][BigBlind];
	
	Poker[id][LastSmall]++;
	if(Poker[id][LastSmall] == 6) Poker[id][LastSmall]=0;
							//Poker[id][BankTD] = TextDrawCreate(321.000000, 221.000000, "1,000,000LT");
	
	SetTimerEx("CardsUnpack",1000,false,"iii",id,0,0);
	return 1;
}
stock NextPlayer(id,first=0)
{
	Poker[id][TimeLeft]=POKER_ROUND_TIME;
	if(Poker[id][Eile]==-1)
	{
		new pid=-1,idx=-1;
		for(new i;i<6;i++)
		{
			
			if(Poker[id][players][i] != -1 && Poker[id][Playing][i])
			{
				TextDrawHideForPlayer(Poker[id][players][i],Poker[id][JusuEile]);
				Poker[id][Bankas]+=Poker[id][PStatymas][i];
				Poker[id][PBankai][i]+=Poker[id][PStatymas][i];
				Poker[id][PStatymas][i]=0;
				pid=Poker[id][players][i]; 
				idx=i;
			}
		}
		if(pid==-1) return EndPokerGame(id);//;
		Poker[id][Eile]=0;
		PlaySoundForPoker(id,pid,SOUND_WIN+random(3));
		Poker[id][PFondas][idx]+=Poker[id][Bankas];
		Poker[id][Bankas]=0;
		new msgx[128];
		format(msgx,sizeof(msgx),"[POKER] Nugaletojas: %s",ReturnName(Poker[id][players][idx]));
		SendMessageToPokerTable(id,TEXTCOL_GOLD,msgx);
		EndGame(id);
		//NewSet(id);
		return 1;
	}
	new playerid = Poker[id][players][Poker[id][Eile]];
	new maxstafke,stafkininkas;
	for(new i;i<6;i++)
	{
		if(Poker[id][players][i] != -1)
		{
			TextDrawHideForPlayer(Poker[id][players][i],Poker[id][JusuEile]);
			if(Poker[id][PStatymas][i] > maxstafke)
			{
				maxstafke=Poker[id][PStatymas][i];
				stafkininkas=i;
			}
			/*new playa=Poker[id][players][i];
			for(new x;x<5;x++)
			{
				PlayerTextDrawShow(playa, Mygtukas[x][playa]);
				//PlayerTextDrawSetSelectable(playa, Mygtukas[x][playa], 0);
			} */
		}
		
	}
	ShowJusuEile(playerid, id);
	new bool:ending=false;
	if(!first)
	{
		if(Poker[id][FirstTurn] == Poker[id][Eile] && Poker[id][PStatymas][Poker[id][Eile]] == maxstafke)
		{
			for(new i;i<6;i++)
			{
				if(Poker[id][players][i] != -1)
				{
					Poker[id][Bankas]+=Poker[id][PStatymas][i];
					Poker[id][PBankai][i]+=Poker[id][PStatymas][i];
					Poker[id][PStatymas][i]=0;
				}
			}
			new txt[128];
			format(txt,sizeof(txt),"%sEUR",FormatNumber(Poker[id][Bankas]));
			TextDrawSetString(Poker[id][BankTD],txt);
			if(Poker[id][TheStep]==3) ending=true;
			Flop(id,Poker[id][TheStep]);
			Poker[id][FirstTurn]=Poker[id][Eile];
			Poker[id][TheStep]++;
			
		}
		for(new x;x<6;x++)
		{
			new pid = Poker[id][players][x];
			if(pid != -1 && x != Poker[id][Eile])
			{
				for(new y;y<5;y++)
				{
//					PlayerTextDrawHide(pid, Mygtukas[y][pid]);
					PlayerTextDrawSetSelectable(pid, Mygtukas[y][pid], 0);
					PlayerTextDrawShow(pid, Mygtukas[y][pid]);
				}
			}
		}
	}
	//else
		//Poker[id][TheStep]=0;
	if(ending) return 1;
	maxstafke=0;
	for(new i;i<6;i++)
	{
		if(Poker[id][players][i] != -1 && Poker[id][Playing][i])
		{
			if(Poker[id][PStatymas][i] > maxstafke)
			{
				maxstafke=Poker[id][PStatymas][i];
				stafkininkas=i;
			}
		}
		
	}
	if(playerid != -1)
	{
		if(Poker[id][Eile]==stafkininkas || Poker[id][PStatymas][Poker[id][Eile]] >= maxstafke)
		{
			SetPVarInt(playerid, "CanCheck", 1);
			PlayerTextDrawSetSelectable(playerid, Mygtukas[0][playerid], 1); // check
			PlayerTextDrawSetSelectable(playerid, Mygtukas[2][playerid], 1); // raise
			PlayerTextDrawSetSelectable(playerid, Mygtukas[3][playerid], 1); // fold
			PlayerTextDrawSetSelectable(playerid, Mygtukas[4][playerid], 1); // leave
			for(new x;x<5;x++)
				PlayerTextDrawShow(playerid, Mygtukas[x][playerid]);
			
		}
		else if(Poker[id][PStatymas][Poker[id][Eile]] < maxstafke)
		{
			SetPVarInt(playerid, "CanCheck", 0);
			PlayerTextDrawSetSelectable(playerid, Mygtukas[1][playerid], 1); // call
			if(Poker[id][PFondas][Poker[id][Eile]] > maxstafke)
			{
				PlayerTextDrawSetSelectable(playerid, Mygtukas[2][playerid], 1); // raise
			}
			PlayerTextDrawSetSelectable(playerid, Mygtukas[3][playerid], 1); // fold
			PlayerTextDrawSetSelectable(playerid, Mygtukas[4][playerid], 1); // leave
			for(new x;x<5;x++)
				PlayerTextDrawShow(playerid, Mygtukas[x][playerid]);
		}
	}
	return 1;
	//SelectTextDraw(playerid, 0xACCBF1FF);
	/*for(new x;x<5;x++)
	{
		PlayerTextDrawSetSelectable(playerid, Mygtukas[x], true);
	} */
}
stock OnPlayerClickPoker(playerid, PlayerText:playertextid)
{
	new id=-1,pid=-1;
	for(new i;i<MAX_POKER_GAMES;i++)
	{
		for(new x;x<6;x++)
		{
			if(Poker[i][players][x]==playerid)
			{
				pid=x;
				id=i;
				break;
			}
		}
	}
	if(id==-1) return 0;
	if(playertextid == Mygtukas[4][playerid]) // leave
	{
	//	CancelSelectTextDraw(playerid);
		LeaveGame(playerid,id,pid);
		
		return 1;
	}
	if(Poker[id][Eile] != pid) return SendInfoMessage(playerid,"Dabar ne jusu eile!");
	if(playertextid == Mygtukas[0][playerid]) // check
	{
		//CancelSelectTextDraw(playerid);
		if(GetPVarInt(playerid, "CanCheck") == 0)
		{
			return SendInfoMessage(playerid,"~r~Dabar checkinti negali!");
		}
		PlaySoundForPoker(id,-1,SOUND_CHECK);
		new msg[128];
		format(msg,sizeof(msg),"[POKER] %s: Check",ReturnName(Poker[id][players][pid]));
		SendMessageToPokerTable(id,-1,msg);
		new txt[128];
		for(new x;x<6;x++)
		{
			if(Poker[id][players][x] != -1 && Poker[id][Playing][x])
			{
				new ppid = Poker[id][players][x];
				format(txt,sizeof(txt),"%sEUR",FormatNumber(Poker[id][PFondas][Poker[id][Eile]]));
				TextDrawSetString(Poker[id][PokerMoney][Poker[id][Eile]],txt);
				TextDrawShowForPlayer(ppid,Poker[id][PokerMoney][Poker[id][Eile]]);
				TextDrawSetString(Poker[id][PokerAction][Poker[id][Eile]],"Check");
				TextDrawShowForPlayer(ppid,Poker[id][PokerAction][Poker[id][Eile]]);
			}
		}
		if(Poker[id][watching] != -1)
		{
			new ppid = Poker[id][watching];
			format(txt,sizeof(txt),"%sEUR",FormatNumber(Poker[id][PFondas][Poker[id][Eile]]));
			TextDrawSetString(Poker[id][PokerMoney][Poker[id][Eile]],txt);
			TextDrawShowForPlayer(ppid,Poker[id][PokerMoney][Poker[id][Eile]]);
			TextDrawSetString(Poker[id][PokerAction][Poker[id][Eile]],"Check");
			TextDrawShowForPlayer(ppid,Poker[id][PokerAction][Poker[id][Eile]]);
	
		}
		Poker[id][Eile] = NextTurn(id,pid);
		NextPlayer(id);
		return 1;
	}
	else if(playertextid == Mygtukas[1][playerid]) // call
	{
		//CancelSelectTextDraw(playerid);
		PlaySoundForPoker(id,-1,SOUND_CALL);
		new amount;
		for(new i;i<6;i++)
		{
			if(Poker[id][players][i] != -1 && Poker[id][players][i] != playerid)
			{
				if(Poker[id][PStatymas][i] > amount)
				{
					amount = Poker[id][PStatymas][i];
				}
			}
		}
		new bool:allined=false;
		amount-=Poker[id][PStatymas][Poker[id][Eile]];
		if(Poker[id][PFondas][Poker[id][Eile]] < amount)
		{
			allined=true;
			Poker[id][PStatymas][Poker[id][Eile]]+=Poker[id][PFondas][Poker[id][Eile]];
			amount=Poker[id][PFondas][Poker[id][Eile]];
			Poker[id][PFondas][Poker[id][Eile]]=0;
		}
		else
		{
			Poker[id][PStatymas][Poker[id][Eile]]+=amount;
			Poker[id][PFondas][Poker[id][Eile]]-=amount;
		}
		new txt[128];
		for(new x;x<6;x++)
		{
			if(Poker[id][players][x] != -1 && Poker[id][Playing][x])
			{
				new ppid = Poker[id][players][x];
				format(txt,sizeof(txt),"%sEUR",FormatNumber(Poker[id][PFondas][Poker[id][Eile]]));
				TextDrawSetString(Poker[id][PokerMoney][Poker[id][Eile]],txt);
				TextDrawShowForPlayer(ppid,Poker[id][PokerMoney][Poker[id][Eile]]);
				if(allined)
					format(txt,sizeof(txt),"All_In(%sEUR)",FormatNumber(amount));
				else if(!amount)
					format(txt,sizeof(txt),"Check");
				else
					format(txt,sizeof(txt),"Call(%sEUR)",FormatNumber(amount));
				TextDrawSetString(Poker[id][PokerAction][Poker[id][Eile]],txt);
				TextDrawShowForPlayer(ppid,Poker[id][PokerAction][Poker[id][Eile]]);
			}
		}
		if(Poker[id][watching] != -1)
		{
			new ppid = Poker[id][watching];
			format(txt,sizeof(txt),"%sEUR",FormatNumber(Poker[id][PFondas][Poker[id][Eile]]));
			TextDrawSetString(Poker[id][PokerMoney][Poker[id][Eile]],txt);
			TextDrawShowForPlayer(ppid,Poker[id][PokerMoney][Poker[id][Eile]]);
			if(allined)
				format(txt,sizeof(txt),"All_In(%sEUR)",FormatNumber(amount));
			else if(!amount)
				format(txt,sizeof(txt),"Check");
			else
				format(txt,sizeof(txt),"Call(%sEUR)",FormatNumber(amount));
			TextDrawSetString(Poker[id][PokerAction][Poker[id][Eile]],txt);
			TextDrawShowForPlayer(ppid,Poker[id][PokerAction][Poker[id][Eile]]);
		}
		/*new Array[6]={-1,...};
		new playerstotal;
		for(new i;i<6;i++)
		{
			if(Poker[id][players][i] != -1 && Poker[id][Playing][i])
			{
				Array[playerstotal]=i;
				playerstotal++;
			}
		} */
//		new pid = Poker[id][Eile];
		Poker[id][Eile] = NextTurn(id,pid);
		NextPlayer(id);
		new msg[128];
		if(allined)
			format(msg,sizeof(msg),"[POKER] %s: All in(%sEUR)",ReturnName(Poker[id][players][pid]),FormatNumber(amount));
		else if(!amount)
			format(msg,sizeof(msg),"[POKER] %s: Check",ReturnName(Poker[id][players][pid]));
		else
			format(msg,sizeof(msg),"[POKER] %s: Call(%sEUR)",ReturnName(Poker[id][players][pid]),FormatNumber(amount));
		if(amount > 100000)
			ProcessAchievement(Poker[id][players][pid],61);
		SendMessageToPokerTable(id,-1,msg);
		return 1;
	}
	else if(playertextid == Mygtukas[2][playerid]) // raise
	{
		//CancelSelectTextDraw(playerid);
		new text[256];
		new maxstafke,currentbid;
		new x;
		for(new i;i<6;i++)
		{
			if(Poker[id][players][i] != -1)
			{
				if(Poker[id][players][i]==playerid) x=i;
				if(Poker[id][Playing][i] && Poker[id][players][i] != playerid )
				{
					if(Poker[id][PFondas][i] + Poker[id][PStatymas][i] > maxstafke)
					{
						maxstafke=Poker[id][PFondas][i] + Poker[id][PStatymas][i];
					}
					if(Poker[id][PStatymas][i] > currentbid)
					{
						currentbid=Poker[id][PStatymas][i];
					}
				}

			}
		}
		currentbid*=2;
		if(currentbid > maxstafke) currentbid=maxstafke;
		if(Poker[id][PFondas][x] < currentbid)
		{
			return SendInfoMessage(playerid,"Jus neturite daugiau pinigu!");
		}
		else if(Poker[id][PFondas][x] < maxstafke)
		{
			maxstafke=Poker[id][PFondas][x];
		}
		format(text,sizeof(text),"Iraðykite sumà, kurià norite raisinti.\nGalite naudoti trumpinius pvz.: 100k, 1.2m\n\nÐiuo metu galite didinti nuo %s iki %s EUR.",FormatNumber(currentbid),FormatNumber(maxstafke));
		ShowPlayerDialogEx(playerid,9998,DIALOG_STYLE_INPUT,"Raise",text,"Gerai","Atsaukti");
		return 1;
	}
	else if(playertextid == Mygtukas[3][playerid]) // folded
	{
		//CancelSelectTextDraw(playerid);
		PlaySoundForPoker(id,-1,SOUND_FOLD);
//		new pid;
		new txt[128];
		for(new x;x<6;x++)
		{
			if(Poker[id][players][x] != -1)
			{
				new pa=Poker[id][players][x];
				PlayerTextDrawColor(pa,Korta[pa][pid][0], TEXTDRAW_FOLD);
				PlayerTextDrawColor(pa,Korta[pa][pid][1], TEXTDRAW_FOLD);
				PlayerTextDrawShow(pa,Korta[pa][pid][0]);
				PlayerTextDrawShow(pa,Korta[pa][pid][1]);
				
			}
			if(Poker[id][players][x] != -1 && Poker[id][Playing][x])
			{
				new ppid = Poker[id][players][x];
				format(txt,sizeof(txt),"%sEUR",FormatNumber(Poker[id][PFondas][Poker[id][Eile]]));
				TextDrawSetString(Poker[id][PokerMoney][Poker[id][Eile]],txt);
				TextDrawShowForPlayer(ppid,Poker[id][PokerMoney][Poker[id][Eile]]);
				TextDrawSetString(Poker[id][PokerAction][Poker[id][Eile]],"Fold");
				TextDrawShowForPlayer(ppid,Poker[id][PokerAction][Poker[id][Eile]]);
			}
		}
		if(Poker[id][watching] != -1)
		{
			new pa = Poker[id][watching];
			PlayerTextDrawColor(pa,Korta[pa][pid][0], TEXTDRAW_FOLD);
			PlayerTextDrawColor(pa,Korta[pa][pid][1], TEXTDRAW_FOLD);
			PlayerTextDrawShow(pa,Korta[pa][pid][0]);
			PlayerTextDrawShow(pa,Korta[pa][pid][1]);
			new ppid = Poker[id][watching];
			format(txt,sizeof(txt),"%sEUR",FormatNumber(Poker[id][PFondas][Poker[id][Eile]]));
			TextDrawSetString(Poker[id][PokerMoney][Poker[id][Eile]],txt);
			TextDrawShowForPlayer(ppid,Poker[id][PokerMoney][Poker[id][Eile]]);
			TextDrawSetString(Poker[id][PokerAction][Poker[id][Eile]],"Fold");
			TextDrawShowForPlayer(ppid,Poker[id][PokerAction][Poker[id][Eile]]);
		}
		


		Poker[id][Bankas]+=Poker[id][PStatymas][pid];
		Poker[id][PBankai][pid]+=Poker[id][PStatymas][pid];
		Poker[id][PStatymas][pid]=0;
		Poker[id][Playing][pid]=0;
		Poker[id][Eile] = NextTurn(id,pid);
		if(Poker[id][FirstTurn]==pid)
		{
			Poker[id][FirstTurn] = Poker[id][Eile];
			NextPlayer(id,1);
		}
		else 
			NextPlayer(id);
		

		new msg[128];
		format(msg,sizeof(msg),"[POKER] %s: Fold",ReturnName(Poker[id][players][pid]));
		SendMessageToPokerTable(id,-1,msg);
		return 1;
	}
	return 0;
}
stock NextTurn(id,player)
{
	new left;
	for(new i;i<6;i++)
	{
		if(Poker[id][players][i] != -1 && Poker[id][Playing][i])
			left++;
	}
	if(left < 2) return -1;
	if(player == 5)
	{
		for(new i;i<6;i++)
		{
			if(Poker[id][players][i] != -1 && Poker[id][Playing][i]) return i;
		}
	}
	else
	{
		for(new i=player+1;i<6;i++)
		{
			if(Poker[id][players][i] != -1 && Poker[id][Playing][i]) return i;
		}
		for(new i=0;i<6;i++)
		{
			if(Poker[id][players][i] != -1 && Poker[id][Playing][i]) return i;
		}
	}
	return -1;
	/*
	new playersleft;
	new currentslot=-1,array[6]={-1,-1,...};
	new curentslotex=-1;
	for(new i;i<6;i++)
	{
		if(i==player)
		{
			curentslotex=playersleft;
		
		}
		//if(i==player) currentslot=playersleft;
		if(Poker[id][players][i] != -1 && Poker[id][Playing][i])
		{
			array[playersleft]=i;
			if(i==player) currentslot=playersleft;
			playersleft++;
		}
	}
	if(currentslot == -1 && curentslotex != -1)
	{
		if(array[curen
	}
	if(playersleft==1) return -1;
	if(currentslot != -1)
	{
		if(currentslot == 5)
		{
			return array[0];
		}
		if(array[currentslot+1] != -1) return array[currentslot+1];
	}
	return array[0];
	*/
}
stock Raising(playerid,amount)
{	

	new id=-1;
	for(new i;i<MAX_POKER_GAMES;i++)
	{
		for(new x;x<6;x++)
		{
			if(Poker[i][players][x]==playerid)
			{
				id=i;
				break;
			}
		}
	}
	if(id==-1) return 0;
	new maxstafke,pley=-1,currentbid;
	for(new i;i<6;i++)
	{
		if(Poker[id][players][i] != -1 && Poker[id][Playing][i])
		{
			if(Poker[id][players][i] == playerid) pley=i;
			if(Poker[id][Playing][i] && Poker[id][players][i] != playerid )
			{
				if(Poker[id][PFondas][i] + Poker[id][PStatymas][i] > maxstafke)
				{
					maxstafke=Poker[id][PFondas][i] + Poker[id][PStatymas][i];
				}
				if(Poker[id][PStatymas][i] > currentbid)
				{
					currentbid=Poker[id][PStatymas][i];
				}
			}
		}
	}
	if(pley == -1) return 0;
	if(Poker[id][Eile] != pley) return 0;
	currentbid*=2;
	if(currentbid > maxstafke) currentbid=maxstafke;
	if(amount < currentbid)
		return SendInfoMessage(playerid,"Tiek jau pastatyta!");
	if(Poker[id][PFondas][pley] < amount)
		return SendInfoMessage(playerid,"Jus tiek neturite!");
	else if(amount > maxstafke || !amount)
	{
		return SendInfoMessage(playerid,"Tiek statyti negalite!");
	}
	else
	{
		Poker[id][PStatymas][pley]+=amount;
		Poker[id][PFondas][pley]-=amount;
		//Poker[id][Bankas]+=Poker[id][PStatymas][pley];
	}
	if(amount > 100000)
		ProcessAchievement(playerid,61);
	Poker[id][FirstTurn]=pley;
	new txt[128];
	for(new x;x<6;x++)
	{
		if(Poker[id][players][x] != -1 && Poker[id][Playing][x])
		{	
			new ppid = Poker[id][players][x];
			format(txt,sizeof(txt),"%sEUR",FormatNumber(Poker[id][PFondas][pley]));
			TextDrawSetString(Poker[id][PokerMoney][pley],txt);
			TextDrawShowForPlayer(ppid,Poker[id][PokerMoney][pley]);
			if(maxstafke == amount || Poker[id][PFondas][pley] == 0)
				format(txt,sizeof(txt),"All_In(%sEUR)",FormatNumber(amount));
			else
				format(txt,sizeof(txt),"Raise(%sEUR)",FormatNumber(amount));
			TextDrawSetString(Poker[id][PokerAction][pley],txt);
			TextDrawShowForPlayer(ppid,Poker[id][PokerAction][pley]);
		}
	}
	if(Poker[id][watching] != -1)
	{
		new ppid = Poker[id][watching];
		format(txt,sizeof(txt),"%sEUR",FormatNumber(Poker[id][PFondas][pley]));
		TextDrawSetString(Poker[id][PokerMoney][pley],txt);
		TextDrawShowForPlayer(ppid,Poker[id][PokerMoney][pley]);
		if(maxstafke == amount || Poker[id][PFondas][pley] == 0)
			format(txt,sizeof(txt),"All_In(%sEUR)",FormatNumber(amount));
		else
			format(txt,sizeof(txt),"Raise(%sEUR)",FormatNumber(amount));
		TextDrawSetString(Poker[id][PokerAction][pley],txt);
		TextDrawShowForPlayer(ppid,Poker[id][PokerAction][pley]);
	}
	//CancelSelectTextDraw(playerid);
	PlaySoundForPoker(id,-1,SOUND_RAISE);
	new msg[128];
	format(msg,sizeof(msg),"[POKER] %s: Raise(%sEUR)",ReturnName(Poker[id][players][pley]),FormatNumber(amount));
	SendMessageToPokerTable(id,-1,msg);
	Poker[id][Eile] = NextTurn(id,pley);
	NextPlayer(id);
	return 1;
}
stock Flop(id,flop)
{
	if(!flop)
	{	
		for(new x;x<3;x++)
		{
			Poker[id][TableR][x]=Poker[id][CardsR][Poker[id][CardsUsed]];
			Poker[id][TableS][x]=Poker[id][CardsS][Poker[id][CardsUsed]];
			Poker[id][CardsUsed]++;
			TextDrawSetString(Poker[id][TableKorta][x],"LD_POKE:cdback");
		}
		SetTimerEx("CardsUnpack",500,false,"iii",id,1,0);
		SendMessageToPokerTable(id,TEXTCOL_GREEN,"[POKER] FLOP");
	}
	else if(flop == 1)
	{
		Poker[id][TableR][3]=Poker[id][CardsR][Poker[id][CardsUsed]];
		Poker[id][TableS][3]=Poker[id][CardsS][Poker[id][CardsUsed]];
		Poker[id][CardsUsed]++;
		TextDrawSetString(Poker[id][TableKorta][3],"LD_POKE:cdback");
		SetTimerEx("CardsUnpack",1000,false,"iii",id,2,0);
		SendMessageToPokerTable(id,TEXTCOL_GREEN,"[POKER] TURN");
	}
	else if(flop == 2)
	{
		Poker[id][TableR][4]=Poker[id][CardsR][Poker[id][CardsUsed]];
		Poker[id][TableS][4]=Poker[id][CardsS][Poker[id][CardsUsed]];
		Poker[id][CardsUsed]++;
		TextDrawSetString(Poker[id][TableKorta][4],"LD_POKE:cdback");
		SetTimerEx("CardsUnpack",1000,false,"iii",id,3,0);
		SendMessageToPokerTable(id,TEXTCOL_GREEN,"[POKER] RIVER");
	}
	else if(flop == 3)
	{
		Poker[id][TheStep]=0;
		Poker[id][Eile]=-1;
		SetTimerEx("FinishGame",1000,false,"i",id);
		//FinishGame(id);
	}
	
}
forward FinishGame(id);
public FinishGame(id)
{
	for(new i;i<7;i++)
	{
		new playerid;
		if(i < 6)
			playerid=Poker[id][players][i];
		else
			playerid = Poker[id][watching];
		
		if(playerid != -1)
		{
			for(new x;x<6;x++)
			{
				if(Poker[id][Playing][x])
				{
					new pid =Poker[id][players][x];
					PlayerTextDrawSetString(playerid,Korta[playerid][x][0],LD_POKE[GetTDName(PHand[pid][0][rank],PHand[pid][0][suit])]);
					PlayerTextDrawSetString(playerid,Korta[playerid][x][1],LD_POKE[GetTDName(PHand[pid][1][rank],PHand[pid][1][suit])]);
				}
			}
		}
	}
	SetTimerEx("GivePrize",2000,false,"i",id);
}
new const ComboArray[10][] = 
{
	"HIGH CARD",
	"ONE PAIR",
	"TWO PAIRS",
	"THREE OF A KIND",
	"STRAIGHT",
	"FLUSH",
	"FULL HOUSE",
	"FOUR OF A KIND",
	"STRAIGHT FLUSH",
	"ROYAL FLUSH"
};
forward GivePrize(id);
public GivePrize(id)
{
	if(Poker[id][GameUsed]==0) return;
	evaluateHands(id);
	new hcombo,hcombocard,hsecond,hkicker1,hkicker2,hkicker3;
	new winner[6],winners,maxplayer;
	for(new i;i<6;i++)
	{
		if(Poker[id][players][i] != -1 && Poker[id][Playing][i])
		{
			if(Poker[id][PlayerCombo][i] > hcombo)
				hcombo=Poker[id][PlayerCombo][i];
		}
	}
	for(new i;i<6;i++)
	{
		if(Poker[id][players][i] != -1 && Poker[id][Playing][i] && Poker[id][PlayerCombo][i]==hcombo)
		{
			if(Poker[id][PlayerComboCard][i] > hcombocard)
				hcombocard=Poker[id][PlayerComboCard][i];
		}
	}
	for(new i;i<6;i++)
	{
		if(Poker[id][players][i] != -1 && Poker[id][Playing][i] && Poker[id][PlayerCombo][i]==hcombo && hcombocard==Poker[id][PlayerComboCard][i])
		{
			if(Poker[id][PlayerSecond][i] > hsecond)
				hsecond=Poker[id][PlayerSecond][i];
		}
	}
	for(new i;i<6;i++)
	{
		if(Poker[id][players][i] != -1 && Poker[id][Playing][i] && Poker[id][PlayerCombo][i]==hcombo && hcombocard==Poker[id][PlayerComboCard][i] && hsecond==Poker[id][PlayerSecond][i])
		{
			if(Poker[id][PlayerKicker1][i] > hkicker1)
				hkicker1=Poker[id][PlayerKicker1][i];
		}
	}
	for(new i;i<6;i++)
	{
		if(Poker[id][players][i] != -1 && Poker[id][Playing][i] && Poker[id][PlayerCombo][i]==hcombo && hcombocard==Poker[id][PlayerComboCard][i] && hsecond==Poker[id][PlayerSecond][i] && hkicker1==Poker[id][PlayerKicker1][i])
		{
			if(Poker[id][PlayerKicker2][i] > hkicker2)
				hkicker2=Poker[id][PlayerKicker2][i];
		}
	}
	for(new i;i<6;i++)
	{
		if(Poker[id][players][i] != -1 && Poker[id][Playing][i] && Poker[id][PlayerCombo][i]==hcombo && hcombocard==Poker[id][PlayerComboCard][i] && hsecond==Poker[id][PlayerSecond][i] && hkicker1==Poker[id][PlayerKicker1][i] && hkicker2==Poker[id][PlayerKicker2][i])
		{
			if(Poker[id][PlayerKicker3][i] > hkicker3)
				hkicker3=Poker[id][PlayerKicker3][i];
		}
	}
	for(new i;i<6;i++)
	{
		if(Poker[id][players][i] != -1 && Poker[id][Playing][i] && Poker[id][PlayerCombo][i]==hcombo && hcombocard==Poker[id][PlayerComboCard][i] && hsecond==Poker[id][PlayerSecond][i] && hkicker1==Poker[id][PlayerKicker1][i] && hkicker2==Poker[id][PlayerKicker2][i] && hkicker3==Poker[id][PlayerKicker3][i])
		{
			winner[i]=1;
			maxplayer=i;
			//winners++;
		}
	}

	new howmanyppl;
	new biggestbank;
	new Suma;
	for(new x;x<6;x++)
	{
		if(Poker[id][players][x] != -1)
		{
			if(Poker[id][Playing][x])
				howmanyppl++;
			//howmanyppl++;
			if(winner[x])
			{
				Suma+=Poker[id][PBankai][x];
				if(Poker[id][PBankai][x] > biggestbank)
				{
					biggestbank=Poker[id][PBankai][x];
				}
				winners++;
			}
			else
			{
				for(new y;y<6;y++)
				{
					if(Poker[id][players][y] != -1)
					{
						new pid = Poker[id][players][y];
						PlayerTextDrawColor(pid,Korta[pid][x][0], TEXTDRAW_FOLD);
						PlayerTextDrawColor(pid,Korta[pid][x][1], TEXTDRAW_FOLD);
						PlayerTextDrawShow(pid,Korta[pid][x][0]);
						PlayerTextDrawShow(pid,Korta[pid][x][1]);
					}
					
				}
				if(Poker[id][watching] != -1)
				{
					new pid = Poker[id][watching];
					PlayerTextDrawColor(pid,Korta[pid][x][0], TEXTDRAW_FOLD);
					PlayerTextDrawColor(pid,Korta[pid][x][1], TEXTDRAW_FOLD);
					PlayerTextDrawShow(pid,Korta[pid][x][0]);
					PlayerTextDrawShow(pid,Korta[pid][x][1]);
				}
			}
		}
	}
	new msga[128]; 
	new Win=0;
	for(new i;i<6;i++) if(Poker[id][PBankai][i] > 0)
	{
		if(Poker[id][PBankai][i] <= biggestbank)
		{
			Win+=Poker[id][PBankai][i];
			if(!winner[i]) Poker[id][PBankai][i]=0;
			//Poker[id][PBankai][i]=0;
		}
		else
		{
			Win+=biggestbank;
			if(Poker[id][Playing][i])
			{
				new diff = Poker[id][PBankai][i]-biggestbank;
				format(msga,sizeof(msga),"[POKER] Jums grazinama %iEUR suma.",diff);
				SendClientMessage(Poker[id][players][i],TEXTCOL_WHITE,msga);
				Poker[id][PFondas][i]+=diff;
			}
			if(!winner[i]) Poker[id][PBankai][i]=0;
		}
	}
	
	if(winners == 1)
	{
		
		format(msga,sizeof(msga),"[POKER] Laimejo %s, turedamas %s",ReturnName(Poker[id][players][maxplayer]),ComboArray[Poker[id][PlayerCombo][maxplayer]]);
		SendMessageToPokerTable(id,TEXTCOL_GOLD,msga);
		new msgas[127];
		format(msgas,sizeof(msgas),"[POKER] Jus laimejote %iEUR.",Win);
		if(Win >= 1000000)
			ProcessAchievement(Poker[id][players][maxplayer],95);
		SendClientMessage(Poker[id][players][maxplayer],TEXTCOL_WHITE,msgas);
		Poker[id][PFondas][maxplayer]+=Win;
		Poker[id][Bankas]=0;
		/*if(Poker[id][PFondas][maxplayer] == 0 && biggestbank > Poker[id][PBankai][maxplayer])
		{
			new howmanyget = Poker[id][PBankai][maxplayer]*howmanyppl;
			if(Poker[id][Bankas] < howmanyget) howmanyget = Poker[id][Bankas];
			Poker[id][PFondas][maxplayer]+=howmanyget;
			Poker[id][Bankas]-=howmanyget;
			
			for(new x;x<6;x++)
			{
				if(Poker[id][Bankas])
				{
					if(Poker[id][players][x] != -1 && Poker[id][Playing][x] && x != maxplayer)
					{
						if(Poker[id][PBankai][x] > Poker[id][PBankai][maxplayer])
						{
							new moneys=Poker[id][PBankai][x] - Poker[id][PBankai][maxplayer];
							Poker[id][PFondas][x]+=moneys;
							Poker[id][Bankas]-=moneys;
						}
					}
				}
			}
			Poker[id][Bankas]=0;
		}
		else
		{
			Poker[id][PFondas][maxplayer]+=Poker[id][Bankas];
			Poker[id][Bankas]=0;
		}*/
	}
	else
	{
		format(msga,sizeof(msga),"[POKER] Laimejo:");
		new Float:wratio;
		//new maximum[6];
		for(new x;x<6;x++)
		{
			if(winner[x])
			{
				format(msga,sizeof(msga),"%s %s,",msga,ReturnName(Poker[id][players][x]));
				wratio=((Float:Poker[id][PBankai][x])/(Float:Suma)); // suma tai kiek laimetojai pastate
				new msgas[127];
				new winas=floatround(wratio*Win,floatround_floor);
				format(msgas,sizeof(msgas),"[POKER] Jus laimejote %iEUR.",winas);
				if(winas >= 1000000)
					ProcessAchievement(Poker[id][players][x],95);
				SendClientMessage(Poker[id][players][x],TEXTCOL_WHITE,msgas);
				Poker[id][PFondas][x]+=winas;
				/*new howmanyget = Poker[id][PBankai][x]*howmanyppl;
				maximum[x]=howmanyget;*/
				
			}
			//Poker[id][PBankai][x]=0;
		}
		/*new oldsplitas = -1;
		while(Poker[id][Bankas] > 10)
		{
			new splitas = floatround(Poker[id][Bankas]/winners);
			if(splitas == oldsplitas) break;
			oldsplitas = splitas;
			new left;
			for(new x;x<6;x++)
			{
				if(winner[x])
				{
					left++;
					if(splitas > maximum[x])
					{
						Poker[id][Bankas]-=maximum[x];
						Poker[id][PFondas][x]+=maximum[x];
						winner[x]=0;
						Poker[id][PBankai][x]=0;
					}
					else
					{
						Poker[id][Bankas]-=splitas;
						Poker[id][PFondas][x]+=splitas;
						maximum[x]-=splitas;
					}
				}
				
			}
			if(!left) break;
		}*/
		Poker[id][Bankas]=0;
		
		format(msga,sizeof(msga),"%s turedami %s",msga,ComboArray[Poker[id][PlayerCombo][maxplayer]]);
		SendMessageToPokerTable(id,TEXTCOL_GOLD,msga);
		Poker[id][Bankas]=0;
		
	
	}
	for(new i;i<6;i++) Poker[id][PBankai][i]=0;
	SetTimerEx("EndGame",5000,false,"i",id);
	//EndGame(id);
	//NewSet(id);
	
}
forward CardsUnpack(id,unpack,step);
public CardsUnpack(id,unpack,step)
{

	for(new i;i<7;i++)
	{
		new playerid;
		if(i < 6) playerid = Poker[id][players][i];
		else playerid=Poker[id][watching];
		if(playerid != -1)
		{
			if(!unpack) // gavo kortas
			{
				if(!step)
				{
					new txt[20];
					TextDrawHideForPlayer(playerid,Poker[id][JusuEile]);
					for(new x;x<6;x++)
					{
						if(Poker[id][players][x] != -1 && Poker[id][Playing][x])
						{
							new name[MAX_PLAYER_NAME];
							GetPlayerName(Poker[id][players][x],name,MAX_PLAYER_NAME);
							TextDrawSetString(Poker[id][PokerName][x],name);
							TextDrawShowForPlayer(playerid,Poker[id][PokerName][x]);
							format(txt,sizeof(txt),"%sEUR",FormatNumber(Poker[id][PFondas][x]));
							TextDrawSetString(Poker[id][PokerMoney][x],txt);
							
							TextDrawShowForPlayer(playerid,Poker[id][PokerMoney][x]);
							PlayerTextDrawSetString(playerid,Korta[playerid][x][0],"LD_POKE:cdback");
							PlayerTextDrawSetString(playerid,Korta[playerid][x][1],"LD_POKE:cdback");
							PlayerTextDrawColor(playerid,Korta[playerid][x][0],TEXDRAW_DEFAULT);
							PlayerTextDrawColor(playerid,Korta[playerid][x][1],TEXDRAW_DEFAULT);
							PlayerTextDrawShow(playerid, Korta[playerid][x][0]);
							PlayerTextDrawShow(playerid, Korta[playerid][x][1]);
							TextDrawShowForPlayer(playerid,Poker[id][PokerAction][x]);
						}
						else if(Poker[id][players][x] == -1)
						{
							TextDrawHideForPlayer(playerid,Poker[id][PokerAction][x]);
							TextDrawHideForPlayer(playerid,Poker[id][PokerMoney][x]);
							TextDrawHideForPlayer(playerid,Poker[id][PokerName][x]);
							for(new z;z<2;z++)
							{
								PlayerTextDrawHide(playerid,Korta[playerid][x][z]);
							}
						}
					}
				}
				else if(step == 1 && i != 6)
				{
					PlayerTextDrawSetString(playerid,Korta[playerid][i][0],LD_POKE[GetTDName(PHand[playerid][0][rank],PHand[playerid][0][suit])]);
				}
				else if(step == 2 && i != 6)
				{
					PlayerTextDrawSetString(playerid,Korta[playerid][i][1],LD_POKE[GetTDName(PHand[playerid][1][rank],PHand[playerid][1][suit])]);
				}
				else if(step == 3) return 1;
			}
			else if(unpack == 1)
			{
				if(step < 3)
				{
					TextDrawShowForPlayer(playerid, Poker[id][TableKorta][step]);
				}
				else if(step < 6)
				{
					TextDrawSetString(Poker[id][TableKorta][step-3],LD_POKE[GetTDName(Poker[id][TableR][step-3],Poker[id][TableS][step-3])]);
					TextDrawShowForPlayer(playerid, Poker[id][TableKorta][step-3]);
				}
				else return 1;
			}
			else if(unpack == 2)
			{
				if(!step)
				{
					TextDrawShowForPlayer(playerid, Poker[id][TableKorta][3]);
				}
				else if(step == 1)
				{
					TextDrawSetString(Poker[id][TableKorta][3],LD_POKE[GetTDName(Poker[id][TableR][3],Poker[id][TableS][3])]);
					TextDrawShowForPlayer(playerid, Poker[id][TableKorta][3]);
				}
				else return 1;
			}
			else if(unpack == 3)
			{
				if(!step)
				{
					TextDrawShowForPlayer(playerid, Poker[id][TableKorta][4]);
				}
				else if(step == 1)
				{
					TextDrawSetString(Poker[id][TableKorta][4], LD_POKE[GetTDName(Poker[id][TableR][4],Poker[id][TableS][4])]);
					TextDrawShowForPlayer(playerid, Poker[id][TableKorta][4]);
				}
				else return 1;
			}
		}
	}
	if(!unpack)
		SetTimerEx("CardsUnpack",1000,false,"iii",id,unpack,step+1);
	if(!unpack && step == 2) NextPlayer(id,1);
	else if(unpack == 1 || unpack == 2 || unpack == 3)
		SetTimerEx("CardsUnpack",500,false,"iii",id,unpack,step+1);
	return 1;
}

stock ShowJusuEile(playerid, id)
{
	new amount;
	for(new i;i<6;i++)
	{
		if(Poker[id][players][i] != -1 && Poker[id][players][i] != playerid)
		{
			if(Poker[id][PStatymas][i] > amount)
			{
				amount = Poker[id][PStatymas][i];
			}
		}
	}
	amount-=Poker[id][PStatymas][Poker[id][Eile]];
	
	new msg[256];
	if(amount > 0)
	{
		format(msg,sizeof(msg),"jusu eile~n~~n~~n~~n~~n~               %s",shortformat(amount));
	}
	else
	{
		format(msg,sizeof(msg),"jusu eile");
	}
	TextDrawSetString(Poker[id][JusuEile], msg);
	TextDrawShowForPlayer(playerid,Poker[id][JusuEile]);
}

stock shortformat(number)
{
	new str[25];
	if(number < 1000) 
	{
		format(str,sizeof(str),"%i",number);
	}
	else if(number < 10000)
	{
		format(str,sizeof(str),"%.1fk",(number/1000.0));
	}
	else if(number < 1000000)
	{
		new thousands = floatround(number / 1000, floatround_ceil);
		format(str,sizeof(str),"%ik",thousands);
	}
	else
	{
		format(str,sizeof(str),"%.1fm",(number / 1000000.0));
	}
	return str;
}

/*
0- high card/no pair
1- one pair
2- two pair
3- three of a kind
4- straight
5- flush
6- full house
7- four of a kind
8- straight flush
9- royal flush
*/

stock getScore(player,&combo,&combocard,&combosecond,&kicker1,&kicker2,&kicker3)
{
	#pragma unused player
	//quickSort(hand,0, sizeof(hand) - 1);
	SortDeepArray(hand, rank);
	combo=0;
	combocard=0;
	combosecond=0;
	kicker1=0;
	kicker2=0;
	kicker3=0;
	new straight,flush,four;
	new k;
	/*checks for flush*/
	while (k<4&&hand[k][suit]==hand[k+1][suit])
		k++;
	if (k==4)
	{
		combo=5; // flush
		combocard=hand[k][rank];
		combosecond=hand[k-1][rank];
		kicker1=hand[k-2][rank];
		kicker2=hand[k-3][rank];
		kicker3=hand[k-4][rank];
		flush=1;
	}

	/* checks for straight*/
	k=0;
	while (k<4&&hand[k][rank]==hand[k+1][rank]-1)
		k++;
	if (k==4)
	{
		combo=4; // straight
		combocard=hand[k][rank];
		combosecond=hand[k-1][rank];
		kicker1=hand[k-2][rank];
		kicker2=hand[k-3][rank];
		kicker3=hand[k-4][rank];
		straight=1;
	}
	if(hand[4][rank] == 12 && hand[0][rank] == 0 && hand[1][rank] == 1 && hand[2][rank]== 2 && hand[3][rank] == 3)
	{
		combo=4; // straight
		combocard=hand[3][rank];
		combosecond=hand[2][rank];
		kicker1=hand[1][rank];
		kicker2=hand[0][rank];
		kicker3=hand[4][rank];
		straight=1;
	}
	if(straight && flush)
	{
		combo=8; // straight flush
		combocard=hand[4][rank];
		combosecond=hand[3][rank];
		kicker1=hand[2][rank];
		kicker2=hand[1][rank];
		kicker3=hand[0][rank];

		if(hand[4][rank] == 12)
		{
			combo=9; // royal
			combocard=hand[4][rank];
			combosecond=hand[3][rank];
			kicker1=hand[2][rank];
			kicker2=hand[1][rank];
			kicker3=hand[0][rank];
		}
	}
	/* checks for fours */
	k=0;
	for (new i=0;i<2;i++)
	{
		k = i;
		while (k<i+3&&hand[k][rank]==hand[k+1][rank])
			k++;
		if (k==i+3)
		{
			combo=7; // four of a kind
			four=1;
			if(i==0)
			{	
				kicker1=hand[4][rank];
				kicker2=0;
				kicker3=0;
			}
			else
			{
				kicker1=hand[0][rank];
				kicker2=0;
				kicker3=0;
			}
			combocard=hand[2][rank];
			combosecond=0;
		}
	}

	/*checks for threes and fullhouse*/
	if (!four)
	{
		for (new i=0;i<3;i++)
		{
			k = i;
			while (k<i+2&&hand[k][rank]==hand[k+1][rank])
				k++;
			if (k==i+2)
			{
				combo=3; // three of a kind
				combocard=hand[k][rank];
				combosecond=0;
				kicker1=hand[2][rank];
				kicker2=hand[1][rank];
				kicker3=hand[0][rank];
				if (i==0)
				{
					if (hand[3][rank]==hand[4][rank])
					{
						combo=6;//full house
						combosecond=hand[3][rank];
						kicker1=0;
						kicker2=0;
						kicker3=0;
						//kickers+=hand[3][rank]*10;
					}
					else
					{
						kicker1=hand[4][rank];
						kicker2=hand[3][rank];
						kicker3=0;
					}
				}
				else if(i==1)
				{
					if (hand[0][rank]==hand[4][rank])
					{
						combo=6;//full house
						combosecond=hand[0][rank];
						kicker1=0;
						kicker2=0;
						kicker3=0;
					}
					else
					{
						kicker1=hand[4][rank];
						kicker2=hand[0][rank];
						kicker3=0;
					}
				}
				else
				{
					if (hand[0][rank]==hand[1][rank])
					{
						combo=6;//full house
						combosecond=hand[0][rank];
						kicker1=0;
						kicker2=0;
						kicker3=0;
					}
					else
					{
						kicker1=hand[1][rank];
						kicker2=hand[0][rank];
						kicker3=0;
					}
				}

			}
		}
	}
	if(combo) return combo;
	/* checks for pairs*/
	new inpair[5];
	combo=0;
	for (k=0;k<4;k++)
	{
		if (hand[k][rank]==hand[k+1][rank])
		{
			inpair[k]=1;
			inpair[k+1]=1;
			combo++; // pair
			if(combo==1)
			{
				combocard=hand[k][rank];
				combosecond=0;
			}
			else
			{
				if(combocard < hand[k][rank])
				{
					combosecond=combocard;
					combocard=hand[k][rank];
				}
				else
				{
					combosecond=hand[k][rank];
				}
			}
		}
	}
	new slot[3];
	//new highestslot=-1;
	if(combo)
	{
		for(new i;i<5;i++)
		{
			if(!inpair[i])
			{
				if(hand[i][rank] >= slot[0])
				{
					slot[2]=slot[1];
					slot[1]=slot[0];
					slot[0]=hand[i][rank];
				}
				else if(hand[i][rank] >= slot[1])
				{
					slot[2]=slot[1];
					slot[1]=hand[i][rank];
				}
				else
				{
					slot[2]=hand[i][rank];
				}
				//kickers+=((hand[i][rank])*(i+1));
			}
		}
	}
	kicker1=slot[0];
	kicker2=slot[1];
	kicker3=slot[2];
	if(!combo)
	{
		combocard=hand[4][rank];
		combosecond=hand[3][rank];
		kicker1=hand[2][rank];
		kicker2=hand[1][rank];
		kicker3=hand[0][rank];
	}
	return combo;
	/*
	//high*=10;
	if (pairs==2)
		return 5000 + high + secondhigh + kickers;
	else if(pairs)
		return 3000 + high + kickers;
	high = hand[4][rank]*100;
	secondhigh = hand[3][rank]*10;
	new thirdhigh,fourthhigh,fifthhigh;
	thirdhigh = hand[2][rank]*5;
	fourthhigh = hand[1][rank]*2;
	fifthhigh = hand[0][rank];
	//for(new i;i<3;i++)
	//	kickers+=hand[i][rank]*(10^(i+1));
	return high+secondhigh+thirdhigh+fourthhigh+fifthhigh;*/
}
/*
stock mysort(array[][Card])
{
	new temparray[Card];
	for(new i;i<5;i++)
	{
		if(array[i][
	
	}

} */
stock quickSort(array[][card], left, right)
{
    new
        tempLeft = left,
        tempRight = right,
        pivot = array[(left + right) / 2][rank],
        tempVar,
		tempsuit
    ;
    while(tempLeft <= tempRight)
    {
        while(array[tempLeft][rank] < pivot) tempLeft++;
        while(array[tempRight][rank] > pivot) tempRight--;
        
        if(tempLeft <= tempRight)
        {
            tempVar = array[tempLeft][rank], array[tempLeft][rank] = array[tempRight][rank], array[tempRight][rank] = tempVar;
			tempsuit = array[tempLeft][suit], array[tempLeft][suit] = array[tempRight][suit], array[tempRight][suit] = tempsuit;
            tempLeft++, tempRight--;
        }
    }
    if(left < tempRight) quickSort(array, left, tempRight);
    if(tempLeft < right) quickSort(array, tempLeft, right);
}

stock GetTDName(rankas,suitas)
{
	return (rankas+(suitas*13));
}
//#include <zcmd>

stock PlaySoundForPoker(id,playerid,soundid)
{
	//new falsas=0;
	//if(!falsas) return 0;
	new Float:Coo[3];
	if(playerid == -1)
	{
		for(new i;i<6;i++)
		{
			if(Poker[id][players][i] != -1)
			{
				GetPlayerPos(Poker[id][players][i],Coo[0],Coo[1],Coo[2]);
				PlayerPlaySound(Poker[id][players][i],soundid,Coo[0],Coo[1],Coo[2]);
			}
		}
	}
	else
	{
		GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
		PlayerPlaySound(playerid,soundid,Coo[0],Coo[1],Coo[2]);
	}

	return 1;
}

stock CreatePokerTextDraws(id)
{
	Poker[id][PokerName][0] = TextDrawCreate(465.000000, 176.000000, "Vardenis_Pavardenis");
	TextDrawAlignment(Poker[id][PokerName][0], 2);
	TextDrawBackgroundColor(Poker[id][PokerName][0], 255);
	TextDrawFont(Poker[id][PokerName][0], 1);
	TextDrawLetterSize(Poker[id][PokerName][0], 0.220000, 0.699999);
	TextDrawColor(Poker[id][PokerName][0], -1);
	TextDrawSetOutline(Poker[id][PokerName][0], 0);
	TextDrawSetProportional(Poker[id][PokerName][0], 1);
	TextDrawSetShadow(Poker[id][PokerName][0], 0);
	TextDrawUseBox(Poker[id][PokerName][0], 1);
	TextDrawBoxColor(Poker[id][PokerName][0], 842202980);
	TextDrawTextSize(Poker[id][PokerName][0], 232.000000, -80.000000);

	Poker[id][PokerName][1] = TextDrawCreate(562.000000, 318.000000, "Vardenis_Pavardenis");
	TextDrawAlignment(Poker[id][PokerName][1], 2);
	TextDrawBackgroundColor(Poker[id][PokerName][1], 255);
	TextDrawFont(Poker[id][PokerName][1], 1);
	TextDrawLetterSize(Poker[id][PokerName][1], 0.220000, 0.699999);
	TextDrawColor(Poker[id][PokerName][1], -1);
	TextDrawSetOutline(Poker[id][PokerName][1], 0);
	TextDrawSetProportional(Poker[id][PokerName][1], 1);
	TextDrawSetShadow(Poker[id][PokerName][1], 0);
	TextDrawUseBox(Poker[id][PokerName][1], 1);
	TextDrawBoxColor(Poker[id][PokerName][1], 842202980);
	TextDrawTextSize(Poker[id][PokerName][1], 232.000000, -80.000000);

	Poker[id][PokerName][2] = TextDrawCreate(375.000000, 366.000000, "Vardenis_Pavardenis");
	TextDrawAlignment(Poker[id][PokerName][2], 2);
	TextDrawBackgroundColor(Poker[id][PokerName][2], 255);
	TextDrawFont(Poker[id][PokerName][2], 1);
	TextDrawLetterSize(Poker[id][PokerName][2], 0.220000, 0.699999);
	TextDrawColor(Poker[id][PokerName][2], -1);
	TextDrawSetOutline(Poker[id][PokerName][2], 0);
	TextDrawSetProportional(Poker[id][PokerName][2], 1);
	TextDrawSetShadow(Poker[id][PokerName][2], 0);
	TextDrawUseBox(Poker[id][PokerName][2], 1);
	TextDrawBoxColor(Poker[id][PokerName][2], 842202980);
	TextDrawTextSize(Poker[id][PokerName][2], 232.000000, -80.000000);

	Poker[id][PokerName][3] = TextDrawCreate(235.000000, 366.000000, "Vardenis_Pavardenis");
	TextDrawAlignment(Poker[id][PokerName][3], 2);
	TextDrawBackgroundColor(Poker[id][PokerName][3], 255);
	TextDrawFont(Poker[id][PokerName][3], 1);
	TextDrawLetterSize(Poker[id][PokerName][3], 0.220000, 0.699999);
	TextDrawColor(Poker[id][PokerName][3], -1);
	TextDrawSetOutline(Poker[id][PokerName][3], 0);
	TextDrawSetProportional(Poker[id][PokerName][3], 1);
	TextDrawSetShadow(Poker[id][PokerName][3], 0);
	TextDrawUseBox(Poker[id][PokerName][3], 1);
	TextDrawBoxColor(Poker[id][PokerName][3], 842202980);
	TextDrawTextSize(Poker[id][PokerName][3], 232.000000, -80.000000);

	Poker[id][PokerName][4] = TextDrawCreate(101.000000, 316.000000, "Vardenis_Pavardenis");
	TextDrawAlignment(Poker[id][PokerName][4], 2);
	TextDrawBackgroundColor(Poker[id][PokerName][4], 255);
	TextDrawFont(Poker[id][PokerName][4], 1);
	TextDrawLetterSize(Poker[id][PokerName][4], 0.220000, 0.699999);
	TextDrawColor(Poker[id][PokerName][4], -1);
	TextDrawSetOutline(Poker[id][PokerName][4], 0);
	TextDrawSetProportional(Poker[id][PokerName][4], 1);
	TextDrawSetShadow(Poker[id][PokerName][4], 0);
	TextDrawUseBox(Poker[id][PokerName][4], 1);
	TextDrawBoxColor(Poker[id][PokerName][4], 842202980);
	TextDrawTextSize(Poker[id][PokerName][4], 232.000000, -80.000000);

	Poker[id][PokerName][5] = TextDrawCreate(175.000000, 176.000000, "Vardenis_Pavardenis");
	TextDrawAlignment(Poker[id][PokerName][5], 2);
	TextDrawBackgroundColor(Poker[id][PokerName][5], 255);
	TextDrawFont(Poker[id][PokerName][5], 1);
	TextDrawLetterSize(Poker[id][PokerName][5], 0.220000, 0.699999);
	TextDrawColor(Poker[id][PokerName][5], -1);
	TextDrawSetOutline(Poker[id][PokerName][5], 0);
	TextDrawSetProportional(Poker[id][PokerName][5], 1);
	TextDrawSetShadow(Poker[id][PokerName][5], 0);
	TextDrawUseBox(Poker[id][PokerName][5], 1);
	TextDrawBoxColor(Poker[id][PokerName][5], 842202980);
	TextDrawTextSize(Poker[id][PokerName][5], 232.000000, -80.000000);

	Poker[id][PokerMoney][0] = TextDrawCreate(465.000000, 186.000000, "0EUR");
	TextDrawAlignment(Poker[id][PokerMoney][0], 2);
	TextDrawBackgroundColor(Poker[id][PokerMoney][0], 255);
	TextDrawFont(Poker[id][PokerMoney][0], 1);
	TextDrawLetterSize(Poker[id][PokerMoney][0], 0.220000, 0.699999);
	TextDrawColor(Poker[id][PokerMoney][0], -1);
	TextDrawSetOutline(Poker[id][PokerMoney][0], 0);
	TextDrawSetProportional(Poker[id][PokerMoney][0], 1);
	TextDrawSetShadow(Poker[id][PokerMoney][0], 0);
	TextDrawUseBox(Poker[id][PokerMoney][0], 1);
	TextDrawBoxColor(Poker[id][PokerMoney][0], 855585380);
	TextDrawTextSize(Poker[id][PokerMoney][0], 270.000000, -80.000000);

	Poker[id][PokerMoney][1] = TextDrawCreate(562.000000, 328.000000, "0EUR");
	TextDrawAlignment(Poker[id][PokerMoney][1], 2);
	TextDrawBackgroundColor(Poker[id][PokerMoney][1], 255);
	TextDrawFont(Poker[id][PokerMoney][1], 1);
	TextDrawLetterSize(Poker[id][PokerMoney][1], 0.220000, 0.699999);
	TextDrawColor(Poker[id][PokerMoney][1], -1);
	TextDrawSetOutline(Poker[id][PokerMoney][1], 0);
	TextDrawSetProportional(Poker[id][PokerMoney][1], 1);
	TextDrawSetShadow(Poker[id][PokerMoney][1], 0);
	TextDrawUseBox(Poker[id][PokerMoney][1], 1);
	TextDrawBoxColor(Poker[id][PokerMoney][1], 855585380);
	TextDrawTextSize(Poker[id][PokerMoney][1], 270.000000, -80.000000);

	Poker[id][PokerMoney][2] = TextDrawCreate(375.000000, 376.000000, "0EUR");
	TextDrawAlignment(Poker[id][PokerMoney][2], 2);
	TextDrawBackgroundColor(Poker[id][PokerMoney][2], 255);
	TextDrawFont(Poker[id][PokerMoney][2], 1);
	TextDrawLetterSize(Poker[id][PokerMoney][2], 0.220000, 0.699999);
	TextDrawColor(Poker[id][PokerMoney][2], -1);
	TextDrawSetOutline(Poker[id][PokerMoney][2], 0);
	TextDrawSetProportional(Poker[id][PokerMoney][2], 1);
	TextDrawSetShadow(Poker[id][PokerMoney][2], 0);
	TextDrawUseBox(Poker[id][PokerMoney][2], 1);
	TextDrawBoxColor(Poker[id][PokerMoney][2], 855585380);
	TextDrawTextSize(Poker[id][PokerMoney][2], 270.000000, -80.000000);

	Poker[id][PokerMoney][3] = TextDrawCreate(235.000000, 376.000000, "0EUR");
	TextDrawAlignment(Poker[id][PokerMoney][3], 2);
	TextDrawBackgroundColor(Poker[id][PokerMoney][3], 255);
	TextDrawFont(Poker[id][PokerMoney][3], 1);
	TextDrawLetterSize(Poker[id][PokerMoney][3], 0.220000, 0.699999);
	TextDrawColor(Poker[id][PokerMoney][3], -1);
	TextDrawSetOutline(Poker[id][PokerMoney][3], 0);
	TextDrawSetProportional(Poker[id][PokerMoney][3], 1);
	TextDrawSetShadow(Poker[id][PokerMoney][3], 0);
	TextDrawUseBox(Poker[id][PokerMoney][3], 1);
	TextDrawBoxColor(Poker[id][PokerMoney][3], 855585380);
	TextDrawTextSize(Poker[id][PokerMoney][3], 270.000000, -80.000000);

	Poker[id][PokerMoney][4] = TextDrawCreate(101.000000, 326.000000, "0EUR");
	TextDrawAlignment(Poker[id][PokerMoney][4], 2);
	TextDrawBackgroundColor(Poker[id][PokerMoney][4], 255);
	TextDrawFont(Poker[id][PokerMoney][4], 1);
	TextDrawLetterSize(Poker[id][PokerMoney][4], 0.220000, 0.699999);
	TextDrawColor(Poker[id][PokerMoney][4], -1);
	TextDrawSetOutline(Poker[id][PokerMoney][4], 0);
	TextDrawSetProportional(Poker[id][PokerMoney][4], 1);
	TextDrawSetShadow(Poker[id][PokerMoney][4], 0);
	TextDrawUseBox(Poker[id][PokerMoney][4], 1);
	TextDrawBoxColor(Poker[id][PokerMoney][4], 855585380);
	TextDrawTextSize(Poker[id][PokerMoney][4], 270.000000, -80.000000);

	Poker[id][PokerMoney][5] = TextDrawCreate(175.000000, 186.000000, "0EUR");
	TextDrawAlignment(Poker[id][PokerMoney][5], 2);
	TextDrawBackgroundColor(Poker[id][PokerMoney][5], 255);
	TextDrawFont(Poker[id][PokerMoney][5], 1);
	TextDrawLetterSize(Poker[id][PokerMoney][5], 0.220000, 0.699999);
	TextDrawColor(Poker[id][PokerMoney][5], -1);
	TextDrawSetOutline(Poker[id][PokerMoney][5], 0);
	TextDrawSetProportional(Poker[id][PokerMoney][5], 1);
	TextDrawSetShadow(Poker[id][PokerMoney][5], 0);
	TextDrawUseBox(Poker[id][PokerMoney][5], 1);
	TextDrawBoxColor(Poker[id][PokerMoney][5], 855585380);
	TextDrawTextSize(Poker[id][PokerMoney][5], 270.000000, -80.000000);

	Poker[id][PokerAction][0] = TextDrawCreate(465.000000, 196.000000, "Action");
	TextDrawAlignment(Poker[id][PokerAction][0], 2);
	TextDrawBackgroundColor(Poker[id][PokerAction][0], 255);
	TextDrawFont(Poker[id][PokerAction][0], 1);
	TextDrawLetterSize(Poker[id][PokerAction][0], 0.220000, 0.699999);
	TextDrawColor(Poker[id][PokerAction][0], -1);
	TextDrawSetOutline(Poker[id][PokerAction][0], 0);
	TextDrawSetProportional(Poker[id][PokerAction][0], 1);
	TextDrawSetShadow(Poker[id][PokerAction][0], 0);
	TextDrawUseBox(Poker[id][PokerAction][0], 1);
	TextDrawBoxColor(Poker[id][PokerAction][0], -13487516);
	TextDrawTextSize(Poker[id][PokerAction][0], 270.000000, -80.000000);

	Poker[id][PokerAction][1] = TextDrawCreate(562.000000, 338.000000, "Action");
	TextDrawAlignment(Poker[id][PokerAction][1], 2);
	TextDrawBackgroundColor(Poker[id][PokerAction][1], 255);
	TextDrawFont(Poker[id][PokerAction][1], 1);
	TextDrawLetterSize(Poker[id][PokerAction][1], 0.220000, 0.699999);
	TextDrawColor(Poker[id][PokerAction][1], -1);
	TextDrawSetOutline(Poker[id][PokerAction][1], 0);
	TextDrawSetProportional(Poker[id][PokerAction][1], 1);
	TextDrawSetShadow(Poker[id][PokerAction][1], 0);
	TextDrawUseBox(Poker[id][PokerAction][1], 1);
	TextDrawBoxColor(Poker[id][PokerAction][1], -13487516);
	TextDrawTextSize(Poker[id][PokerAction][1], 270.000000, -80.000000);

	Poker[id][PokerAction][2] = TextDrawCreate(375.000000, 386.000000, "Action");
	TextDrawAlignment(Poker[id][PokerAction][2], 2);
	TextDrawBackgroundColor(Poker[id][PokerAction][2], 255);
	TextDrawFont(Poker[id][PokerAction][2], 1);
	TextDrawLetterSize(Poker[id][PokerAction][2], 0.220000, 0.699999);
	TextDrawColor(Poker[id][PokerAction][2], -1);
	TextDrawSetOutline(Poker[id][PokerAction][2], 0);
	TextDrawSetProportional(Poker[id][PokerAction][2], 1);
	TextDrawSetShadow(Poker[id][PokerAction][2], 0);
	TextDrawUseBox(Poker[id][PokerAction][2], 1);
	TextDrawBoxColor(Poker[id][PokerAction][2], -13487516);
	TextDrawTextSize(Poker[id][PokerAction][2], 270.000000, -80.000000);

	Poker[id][PokerAction][3] = TextDrawCreate(235.000000, 386.000000, "Action");
	TextDrawAlignment(Poker[id][PokerAction][3], 2);
	TextDrawBackgroundColor(Poker[id][PokerAction][3], 255);
	TextDrawFont(Poker[id][PokerAction][3], 1);
	TextDrawLetterSize(Poker[id][PokerAction][3], 0.220000, 0.699999);
	TextDrawColor(Poker[id][PokerAction][3], -1);
	TextDrawSetOutline(Poker[id][PokerAction][3], 0);
	TextDrawSetProportional(Poker[id][PokerAction][3], 1);
	TextDrawSetShadow(Poker[id][PokerAction][3], 0);
	TextDrawUseBox(Poker[id][PokerAction][3], 1);
	TextDrawBoxColor(Poker[id][PokerAction][3], -13487516);
	TextDrawTextSize(Poker[id][PokerAction][3], 270.000000, -80.000000);

	Poker[id][PokerAction][4] = TextDrawCreate(101.000000, 336.000000, "Action");
	TextDrawAlignment(Poker[id][PokerAction][4], 2);
	TextDrawBackgroundColor(Poker[id][PokerAction][4], 255);
	TextDrawFont(Poker[id][PokerAction][4], 1);
	TextDrawLetterSize(Poker[id][PokerAction][4], 0.220000, 0.699999);
	TextDrawColor(Poker[id][PokerAction][4], -1);
	TextDrawSetOutline(Poker[id][PokerAction][4], 0);
	TextDrawSetProportional(Poker[id][PokerAction][4], 1);
	TextDrawSetShadow(Poker[id][PokerAction][4], 0);
	TextDrawUseBox(Poker[id][PokerAction][4], 1);
	TextDrawBoxColor(Poker[id][PokerAction][4], -13487516);
	TextDrawTextSize(Poker[id][PokerAction][4], 270.000000, -80.000000);

	Poker[id][PokerAction][5] = TextDrawCreate(175.000000, 196.000000, "Action");
	TextDrawAlignment(Poker[id][PokerAction][5], 2);
	TextDrawBackgroundColor(Poker[id][PokerAction][5], 255);
	TextDrawFont(Poker[id][PokerAction][5], 1);
	TextDrawLetterSize(Poker[id][PokerAction][5], 0.220000, 0.699999);
	TextDrawColor(Poker[id][PokerAction][5], -1);
	TextDrawSetOutline(Poker[id][PokerAction][5], 0);
	TextDrawSetProportional(Poker[id][PokerAction][5], 1);
	TextDrawSetShadow(Poker[id][PokerAction][5], 0);
	TextDrawUseBox(Poker[id][PokerAction][5], 1);
	TextDrawBoxColor(Poker[id][PokerAction][5], -13487516);
	TextDrawTextSize(Poker[id][PokerAction][5], 270.000000, -80.000000);

	Poker[id][TableKorta][0] = TextDrawCreate(226.000000, 241.000000, "LD_POKE:cdback");
	TextDrawBackgroundColor(Poker[id][TableKorta][0], 255);
	TextDrawFont(Poker[id][TableKorta][0], 4);
	TextDrawLetterSize(Poker[id][TableKorta][0], 0.500000, 1.000000);
	TextDrawColor(Poker[id][TableKorta][0], -1);
	TextDrawSetOutline(Poker[id][TableKorta][0], 0);
	TextDrawSetProportional(Poker[id][TableKorta][0], 1);
	TextDrawSetShadow(Poker[id][TableKorta][0], 1);
	TextDrawUseBox(Poker[id][TableKorta][0], 1);
	TextDrawBoxColor(Poker[id][TableKorta][0], 255);
	TextDrawTextSize(Poker[id][TableKorta][0], 34.000000, 33.000000);

	Poker[id][TableKorta][1] = TextDrawCreate(263.000000, 241.000000, "LD_POKE:cdback");
	TextDrawBackgroundColor(Poker[id][TableKorta][1], 255);
	TextDrawFont(Poker[id][TableKorta][1], 4);
	TextDrawLetterSize(Poker[id][TableKorta][1], 0.500000, 1.000000);
	TextDrawColor(Poker[id][TableKorta][1], -1);
	TextDrawSetOutline(Poker[id][TableKorta][1], 0);
	TextDrawSetProportional(Poker[id][TableKorta][1], 1);
	TextDrawSetShadow(Poker[id][TableKorta][1], 1);
	TextDrawUseBox(Poker[id][TableKorta][1], 1);
	TextDrawBoxColor(Poker[id][TableKorta][1], 255);
	TextDrawTextSize(Poker[id][TableKorta][1], 34.000000, 33.000000);

	Poker[id][TableKorta][2] = TextDrawCreate(301.000000, 241.000000, "LD_POKE:cdback");
	TextDrawBackgroundColor(Poker[id][TableKorta][2], 255);
	TextDrawFont(Poker[id][TableKorta][2], 4);
	TextDrawLetterSize(Poker[id][TableKorta][2], 0.500000, 1.000000);
	TextDrawColor(Poker[id][TableKorta][2], -1);
	TextDrawSetOutline(Poker[id][TableKorta][2], 0);
	TextDrawSetProportional(Poker[id][TableKorta][2], 1);
	TextDrawSetShadow(Poker[id][TableKorta][2], 1);
	TextDrawUseBox(Poker[id][TableKorta][2], 1);
	TextDrawBoxColor(Poker[id][TableKorta][2], 255);
	TextDrawTextSize(Poker[id][TableKorta][2], 34.000000, 33.000000);

	Poker[id][TableKorta][3] = TextDrawCreate(339.000000, 241.000000, "LD_POKE:cdback");
	TextDrawBackgroundColor(Poker[id][TableKorta][3], 255);
	TextDrawFont(Poker[id][TableKorta][3], 4);
	TextDrawLetterSize(Poker[id][TableKorta][3], 0.500000, 1.000000);
	TextDrawColor(Poker[id][TableKorta][3], -1);
	TextDrawSetOutline(Poker[id][TableKorta][3], 0);
	TextDrawSetProportional(Poker[id][TableKorta][3], 1);
	TextDrawSetShadow(Poker[id][TableKorta][3], 1);
	TextDrawUseBox(Poker[id][TableKorta][3], 1);
	TextDrawBoxColor(Poker[id][TableKorta][3], 255);
	TextDrawTextSize(Poker[id][TableKorta][3], 34.000000, 33.000000);

	Poker[id][TableKorta][4] = TextDrawCreate(377.000000, 241.000000, "LD_POKE:cdback");
	TextDrawBackgroundColor(Poker[id][TableKorta][4], 255);
	TextDrawFont(Poker[id][TableKorta][4], 4);
	TextDrawLetterSize(Poker[id][TableKorta][4], 0.500000, 1.000000);
	TextDrawColor(Poker[id][TableKorta][4], -1);
	TextDrawSetOutline(Poker[id][TableKorta][4], 0);
	TextDrawSetProportional(Poker[id][TableKorta][4], 1);
	TextDrawSetShadow(Poker[id][TableKorta][4], 1);
	TextDrawUseBox(Poker[id][TableKorta][4], 1);
	TextDrawBoxColor(Poker[id][TableKorta][4], 255);
	TextDrawTextSize(Poker[id][TableKorta][4], 34.000000, 33.000000);

	Poker[id][BankTD] = TextDrawCreate(321.000000, 221.000000, "1,000,000EUR");
	TextDrawAlignment(Poker[id][BankTD], 2);
	TextDrawBackgroundColor(Poker[id][BankTD], 255);
	TextDrawFont(Poker[id][BankTD], 1);
	TextDrawLetterSize(Poker[id][BankTD], 0.400000, 0.799999);
	TextDrawColor(Poker[id][BankTD], -1);
	TextDrawSetOutline(Poker[id][BankTD], 0);
	TextDrawSetProportional(Poker[id][BankTD], 1);
	TextDrawSetShadow(Poker[id][BankTD], 1);
	TextDrawUseBox(Poker[id][BankTD], 1);
	TextDrawBoxColor(Poker[id][BankTD], 255);
	TextDrawTextSize(Poker[id][BankTD], 325.000000, 90.000000);

	Poker[id][JusuEile] = TextDrawCreate(11.000000, 129.000000, "Jusu eile");
	TextDrawBackgroundColor(Poker[id][JusuEile], 255);
	TextDrawFont(Poker[id][JusuEile], 2);
	TextDrawLetterSize(Poker[id][JusuEile], 0.500000, 1.000000);
	TextDrawColor(Poker[id][JusuEile], -1);
	TextDrawSetOutline(Poker[id][JusuEile], 0);
	TextDrawSetProportional(Poker[id][JusuEile], 1);
	TextDrawSetShadow(Poker[id][JusuEile], 1);
	return 1;
}

#if defined _formatnumber_included
	#endinput
#else
	#define _formatnumber_included
#endif

#if !defined HEX_PREFIX
	#define HEX_PREFIX  "0x"
#endif

#if !defined BIT_PREFIX
	#define BIT_PREFIX  "0b"
#endif

#if !defined DEFAULT_DECIMAL_COUNT
	#define DEFAULT_DECIMAL_COUNT  8
#endif

#if !defined DEFAULT_THOUSAND_SEP
	#define DEFAULT_THOUSAND_SEP  '.'
#endif

#if !defined DEFAULT_DECIMAL_POINT
	#define DEFAULT_DECIMAL_POINT  ','
#endif

stock FormatNumber( { _, Float, Text3D, Menu, Text, DB, DBResult, bool, File, hex, bit, bit_byte, Bit }:xVariable, iDecimals = -1, iThousandSeparator = DEFAULT_THOUSAND_SEP, iDecimalPoint = DEFAULT_DECIMAL_POINT)
{

	static
		s_szReturn[ 32 ],
		s_szThousandSeparator[ 2 ] = { ' ', EOS },
		s_iDecimalPos,
		s_iChar,
		s_iSepPos
	;
	new neg = 0;

	if(xVariable < 0)
	{
		xVariable = xVariable*(-1);
		neg = 1;
	}

	
	format( s_szReturn, sizeof( s_szReturn ), "%d", xVariable );
	
	if ( iDecimals > 0 )
	{
		strcat( s_szReturn, "." );
		
		while ( iDecimals-- )
			strcat( s_szReturn, "0" );
	}
	
	s_iDecimalPos = strfind( s_szReturn, "." );
	
	if ( s_iDecimalPos == -1 )
		s_iDecimalPos = strlen( s_szReturn );
	else
		s_szReturn[ s_iDecimalPos ] = iDecimalPoint;
	
	if ( s_iDecimalPos >= 4 && iThousandSeparator )
	{
		s_szThousandSeparator[ 0 ] = iThousandSeparator;
		
		s_iChar = s_iDecimalPos;
		s_iSepPos = 0;
		
		while ( --s_iChar > 0 )
		{
			if ( ++s_iSepPos == 3 )
			{
				strins( s_szReturn, s_szThousandSeparator, s_iChar );
				
				s_iSepPos = 0;
			}
		}
	}
	if(neg == 1)
	{
		xVariable = xVariable*(-1);
		format( s_szReturn, sizeof( s_szReturn ), "-%s", s_szReturn );
	}
	return s_szReturn;
}

stock CreatePlayerTextDraws(playerid)
{
	Korta[playerid][0][0] = CreatePlayerTextDraw(playerid,430.000000, 140.000000, "LD_POKE:cdback");
	PlayerTextDrawBackgroundColor(playerid,Korta[playerid][0][0], 255);
	PlayerTextDrawFont(playerid,Korta[playerid][0][0], 4);
	PlayerTextDrawLetterSize(playerid,Korta[playerid][0][0], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,Korta[playerid][0][0], -1);
	PlayerTextDrawSetOutline(playerid,Korta[playerid][0][0], 0);
	PlayerTextDrawSetProportional(playerid,Korta[playerid][0][0], 1);
	PlayerTextDrawSetShadow(playerid,Korta[playerid][0][0], 1);
	PlayerTextDrawUseBox(playerid,Korta[playerid][0][0], 1);
	PlayerTextDrawBoxColor(playerid,Korta[playerid][0][0], 16711935);
	PlayerTextDrawTextSize(playerid,Korta[playerid][0][0], 34.000000, 33.000000);

	Korta[playerid][0][1] = CreatePlayerTextDraw(playerid,464.000000, 140.000000, "LD_POKE:cdback");
	PlayerTextDrawBackgroundColor(playerid,Korta[playerid][0][1], 255);
	PlayerTextDrawFont(playerid,Korta[playerid][0][1], 4);
	PlayerTextDrawLetterSize(playerid,Korta[playerid][0][1], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,Korta[playerid][0][1], -1);
	PlayerTextDrawSetOutline(playerid,Korta[playerid][0][1], 0);
	PlayerTextDrawSetProportional(playerid,Korta[playerid][0][1], 1);
	PlayerTextDrawSetShadow(playerid,Korta[playerid][0][1], 1);
	PlayerTextDrawUseBox(playerid,Korta[playerid][0][1], 1);
	PlayerTextDrawBoxColor(playerid,Korta[playerid][0][1], 255);
	PlayerTextDrawTextSize(playerid,Korta[playerid][0][1], 34.000000, 33.000000);

	Korta[playerid][1][0] = CreatePlayerTextDraw(playerid,527.000000, 282.000000, "LD_POKE:cdback");
	PlayerTextDrawBackgroundColor(playerid,Korta[playerid][1][0], 255);
	PlayerTextDrawFont(playerid,Korta[playerid][1][0], 4);
	PlayerTextDrawLetterSize(playerid,Korta[playerid][1][0], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,Korta[playerid][1][0], -1);
	PlayerTextDrawSetOutline(playerid,Korta[playerid][1][0], 0);
	PlayerTextDrawSetProportional(playerid,Korta[playerid][1][0], 1);
	PlayerTextDrawSetShadow(playerid,Korta[playerid][1][0], 1);
	PlayerTextDrawUseBox(playerid,Korta[playerid][1][0], 1);
	PlayerTextDrawBoxColor(playerid,Korta[playerid][1][0], 255);
	PlayerTextDrawTextSize(playerid,Korta[playerid][1][0], 34.000000, 33.000000);

	Korta[playerid][1][1] = CreatePlayerTextDraw(playerid,561.000000, 282.000000, "LD_POKE:cdback");
	PlayerTextDrawBackgroundColor(playerid,Korta[playerid][1][1], 255);
	PlayerTextDrawFont(playerid,Korta[playerid][1][1], 4);
	PlayerTextDrawLetterSize(playerid,Korta[playerid][1][1], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,Korta[playerid][1][1], -1);
	PlayerTextDrawSetOutline(playerid,Korta[playerid][1][1], 0);
	PlayerTextDrawSetProportional(playerid,Korta[playerid][1][1], 1);
	PlayerTextDrawSetShadow(playerid,Korta[playerid][1][1], 1);
	PlayerTextDrawUseBox(playerid,Korta[playerid][1][1], 1);
	PlayerTextDrawBoxColor(playerid,Korta[playerid][1][1], 255);
	PlayerTextDrawTextSize(playerid,Korta[playerid][1][1], 34.000000, 33.000000);

	Korta[playerid][2][0] = CreatePlayerTextDraw(playerid,340.000000, 330.000000, "LD_POKE:cdback");
	PlayerTextDrawBackgroundColor(playerid,Korta[playerid][2][0], 255);
	PlayerTextDrawFont(playerid,Korta[playerid][2][0], 4);
	PlayerTextDrawLetterSize(playerid,Korta[playerid][2][0], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,Korta[playerid][2][0], -1);
	PlayerTextDrawSetOutline(playerid,Korta[playerid][2][0], 0);
	PlayerTextDrawSetProportional(playerid,Korta[playerid][2][0], 1);
	PlayerTextDrawSetShadow(playerid,Korta[playerid][2][0], 1);
	PlayerTextDrawUseBox(playerid,Korta[playerid][2][0], 1);
	PlayerTextDrawBoxColor(playerid,Korta[playerid][2][0], 255);
	PlayerTextDrawTextSize(playerid,Korta[playerid][2][0], 34.000000, 33.000000);

	Korta[playerid][2][1] = CreatePlayerTextDraw(playerid,374.000000, 330.000000, "LD_POKE:cdback");
	PlayerTextDrawBackgroundColor(playerid,Korta[playerid][2][1], 255);
	PlayerTextDrawFont(playerid,Korta[playerid][2][1], 4);
	PlayerTextDrawLetterSize(playerid,Korta[playerid][2][1], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,Korta[playerid][2][1], -1);
	PlayerTextDrawSetOutline(playerid,Korta[playerid][2][1], 0);
	PlayerTextDrawSetProportional(playerid,Korta[playerid][2][1], 1);
	PlayerTextDrawSetShadow(playerid,Korta[playerid][2][1], 1);
	PlayerTextDrawUseBox(playerid,Korta[playerid][2][1], 1);
	PlayerTextDrawBoxColor(playerid,Korta[playerid][2][1], 255);
	PlayerTextDrawTextSize(playerid,Korta[playerid][2][1], 34.000000, 33.000000);

	Korta[playerid][3][0] = CreatePlayerTextDraw(playerid,203.000000, 330.000000, "LD_POKE:cdback");
	PlayerTextDrawBackgroundColor(playerid,Korta[playerid][3][0], 255);
	PlayerTextDrawFont(playerid,Korta[playerid][3][0], 4);
	PlayerTextDrawLetterSize(playerid,Korta[playerid][3][0], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,Korta[playerid][3][0], -1);
	PlayerTextDrawSetOutline(playerid,Korta[playerid][3][0], 0);
	PlayerTextDrawSetProportional(playerid,Korta[playerid][3][0], 1);
	PlayerTextDrawSetShadow(playerid,Korta[playerid][3][0], 1);
	PlayerTextDrawUseBox(playerid,Korta[playerid][3][0], 1);
	PlayerTextDrawBoxColor(playerid,Korta[playerid][3][0], 255);
	PlayerTextDrawTextSize(playerid,Korta[playerid][3][0], 34.000000, 33.000000);

	Korta[playerid][3][1] = CreatePlayerTextDraw(playerid,237.000000, 330.000000, "LD_POKE:cdback");
	PlayerTextDrawBackgroundColor(playerid,Korta[playerid][3][1], 255);
	PlayerTextDrawFont(playerid,Korta[playerid][3][1], 4);
	PlayerTextDrawLetterSize(playerid,Korta[playerid][3][1], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,Korta[playerid][3][1], -1);
	PlayerTextDrawSetOutline(playerid,Korta[playerid][3][1], 0);
	PlayerTextDrawSetProportional(playerid,Korta[playerid][3][1], 1);
	PlayerTextDrawSetShadow(playerid,Korta[playerid][3][1], 1);
	PlayerTextDrawUseBox(playerid,Korta[playerid][3][1], 1);
	PlayerTextDrawBoxColor(playerid,Korta[playerid][3][1], 255);
	PlayerTextDrawTextSize(playerid,Korta[playerid][3][1], 34.000000, 33.000000);

	Korta[playerid][4][0] = CreatePlayerTextDraw(playerid,67.000000, 280.000000, "LD_POKE:cdback");
	PlayerTextDrawBackgroundColor(playerid,Korta[playerid][4][0], 255);
	PlayerTextDrawFont(playerid,Korta[playerid][4][0], 4);
	PlayerTextDrawLetterSize(playerid,Korta[playerid][4][0], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,Korta[playerid][4][0], -1);
	PlayerTextDrawSetOutline(playerid,Korta[playerid][4][0], 0);
	PlayerTextDrawSetProportional(playerid,Korta[playerid][4][0], 1);
	PlayerTextDrawSetShadow(playerid,Korta[playerid][4][0], 1);
	PlayerTextDrawUseBox(playerid,Korta[playerid][4][0], 1);
	PlayerTextDrawBoxColor(playerid,Korta[playerid][4][0], 255);
	PlayerTextDrawTextSize(playerid,Korta[playerid][4][0], 34.000000, 33.000000);

	Korta[playerid][4][1] = CreatePlayerTextDraw(playerid,101.000000, 280.000000, "LD_POKE:cdback");
	PlayerTextDrawBackgroundColor(playerid,Korta[playerid][4][1], 255);
	PlayerTextDrawFont(playerid,Korta[playerid][4][1], 4);
	PlayerTextDrawLetterSize(playerid,Korta[playerid][4][1], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,Korta[playerid][4][1], -1);
	PlayerTextDrawSetOutline(playerid,Korta[playerid][4][1], 0);
	PlayerTextDrawSetProportional(playerid,Korta[playerid][4][1], 1);
	PlayerTextDrawSetShadow(playerid,Korta[playerid][4][1], 1);
	PlayerTextDrawUseBox(playerid,Korta[playerid][4][1], 1);
	PlayerTextDrawBoxColor(playerid,Korta[playerid][4][1], 255);
	PlayerTextDrawTextSize(playerid,Korta[playerid][4][1], 34.000000, 33.000000);

	Korta[playerid][5][0] = CreatePlayerTextDraw(playerid,141.000000, 140.000000, "LD_POKE:cdback");
	PlayerTextDrawBackgroundColor(playerid,Korta[playerid][5][0], 255);
	PlayerTextDrawFont(playerid,Korta[playerid][5][0], 4);
	PlayerTextDrawLetterSize(playerid,Korta[playerid][5][0], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,Korta[playerid][5][0], -1);
	PlayerTextDrawSetOutline(playerid,Korta[playerid][5][0], 0);
	PlayerTextDrawSetProportional(playerid,Korta[playerid][5][0], 1);
	PlayerTextDrawSetShadow(playerid,Korta[playerid][5][0], 1);
	PlayerTextDrawUseBox(playerid,Korta[playerid][5][0], 1);
	PlayerTextDrawBoxColor(playerid,Korta[playerid][5][0], 255);
	PlayerTextDrawTextSize(playerid,Korta[playerid][5][0], 34.000000, 33.000000);

	Korta[playerid][5][1] = CreatePlayerTextDraw(playerid,175.000000, 140.000000, "LD_POKE:cdback");
	PlayerTextDrawBackgroundColor(playerid,Korta[playerid][5][1], 255);
	PlayerTextDrawFont(playerid,Korta[playerid][5][1], 4);
	PlayerTextDrawLetterSize(playerid,Korta[playerid][5][1], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,Korta[playerid][5][1], -1);
	PlayerTextDrawSetOutline(playerid,Korta[playerid][5][1], 0);
	PlayerTextDrawSetProportional(playerid,Korta[playerid][5][1], 1);
	PlayerTextDrawSetShadow(playerid,Korta[playerid][5][1], 1);
	PlayerTextDrawUseBox(playerid,Korta[playerid][5][1], 1);
	PlayerTextDrawBoxColor(playerid,Korta[playerid][5][1], 255);
	PlayerTextDrawTextSize(playerid,Korta[playerid][5][1], 34.000000, 33.000000);
	Mygtukas[0][playerid] = CreatePlayerTextDraw(playerid,59.000000, 151.000000, "Check");
	PlayerTextDrawAlignment(playerid,Mygtukas[0][playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,Mygtukas[0][playerid], 255);
	PlayerTextDrawFont(playerid,Mygtukas[0][playerid], 2);
	PlayerTextDrawLetterSize(playerid,Mygtukas[0][playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,Mygtukas[0][playerid], -1);
	PlayerTextDrawSetOutline(playerid,Mygtukas[0][playerid], 0);
	PlayerTextDrawSetProportional(playerid,Mygtukas[0][playerid], 1);
	PlayerTextDrawSetShadow(playerid,Mygtukas[0][playerid], 1);
	PlayerTextDrawUseBox(playerid,Mygtukas[0][playerid], 1);
	PlayerTextDrawBoxColor(playerid,Mygtukas[0][playerid], 255);
	PlayerTextDrawTextSize(playerid,Mygtukas[0][playerid], 20.000000, 80.000000);

	Mygtukas[1][playerid] = CreatePlayerTextDraw(playerid,59.000000, 171.000000, "Call");
	PlayerTextDrawAlignment(playerid,Mygtukas[1][playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,Mygtukas[1][playerid], 255);
	PlayerTextDrawFont(playerid,Mygtukas[1][playerid], 2);
	PlayerTextDrawLetterSize(playerid,Mygtukas[1][playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,Mygtukas[1][playerid], -1);
	PlayerTextDrawSetOutline(playerid,Mygtukas[1][playerid], 0);
	PlayerTextDrawSetProportional(playerid,Mygtukas[1][playerid], 1);
	PlayerTextDrawSetShadow(playerid,Mygtukas[1][playerid], 1);
	PlayerTextDrawUseBox(playerid,Mygtukas[1][playerid], 1);
	PlayerTextDrawBoxColor(playerid,Mygtukas[1][playerid], 255);
	PlayerTextDrawTextSize(playerid,Mygtukas[1][playerid], 20.000000, 80.000000);

	Mygtukas[2][playerid] = CreatePlayerTextDraw(playerid,59.000000, 191.000000, "Raise");
	PlayerTextDrawAlignment(playerid,Mygtukas[2][playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,Mygtukas[2][playerid], 255);
	PlayerTextDrawFont(playerid,Mygtukas[2][playerid], 2);
	PlayerTextDrawLetterSize(playerid,Mygtukas[2][playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,Mygtukas[2][playerid], -1);
	PlayerTextDrawSetOutline(playerid,Mygtukas[2][playerid], 0);
	PlayerTextDrawSetProportional(playerid,Mygtukas[2][playerid], 1);
	PlayerTextDrawSetShadow(playerid,Mygtukas[2][playerid], 1);
	PlayerTextDrawUseBox(playerid,Mygtukas[2][playerid], 1);
	PlayerTextDrawBoxColor(playerid,Mygtukas[2][playerid], 255);
	PlayerTextDrawTextSize(playerid,Mygtukas[2][playerid], 20.000000, 80.000000);

	Mygtukas[3][playerid] = CreatePlayerTextDraw(playerid,59.000000, 211.000000, "Fold");
	PlayerTextDrawAlignment(playerid,Mygtukas[3][playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,Mygtukas[3][playerid], 255);
	PlayerTextDrawFont(playerid,Mygtukas[3][playerid], 2);
	PlayerTextDrawLetterSize(playerid,Mygtukas[3][playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,Mygtukas[3][playerid], -1);
	PlayerTextDrawSetOutline(playerid,Mygtukas[3][playerid], 0);
	PlayerTextDrawSetProportional(playerid,Mygtukas[3][playerid], 1);
	PlayerTextDrawSetShadow(playerid,Mygtukas[3][playerid], 1);
	PlayerTextDrawUseBox(playerid,Mygtukas[3][playerid], 1);
	PlayerTextDrawBoxColor(playerid,Mygtukas[3][playerid], 255);
	PlayerTextDrawTextSize(playerid,Mygtukas[3][playerid], 20.000000, 80.000000);

	Mygtukas[4][playerid] = CreatePlayerTextDraw(playerid,59.000000, 231.000000, "Leave");
	PlayerTextDrawAlignment(playerid,Mygtukas[4][playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,Mygtukas[4][playerid], 255);
	PlayerTextDrawFont(playerid,Mygtukas[4][playerid], 2);
	PlayerTextDrawLetterSize(playerid,Mygtukas[4][playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,Mygtukas[4][playerid], -1);
	PlayerTextDrawSetOutline(playerid,Mygtukas[4][playerid], 0);
	PlayerTextDrawSetProportional(playerid,Mygtukas[4][playerid], 1);
	PlayerTextDrawSetShadow(playerid,Mygtukas[4][playerid], 1);
	PlayerTextDrawUseBox(playerid,Mygtukas[4][playerid], 1);
	PlayerTextDrawBoxColor(playerid,Mygtukas[4][playerid], 255);
	PlayerTextDrawTextSize(playerid,Mygtukas[4][playerid], 20.000000, 80.000000);
}
stock SendMessageToPokerTable(id,color,msg[])
{
	for(new i;i<6;i++)
	{
		if(Poker[id][players][i] != -1)
			SendClientMessage(Poker[id][players][i],color,msg);
	}
	if(Poker[id][watching] != -1)
		SendClientMessage(Poker[id][watching],color,msg);
	return 1;
}
