#include <stdio.h>  //宣告程式庫 
#include <windows.h>
#include <conio.h> 
#include <time.h>
#include <string.h>

int step;
int i=0,j=0,k=0,b=0;
char show[30][101],show_2[11][17]= {{' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' '},
									{' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' '},
									{' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' '},
									{'-','-','-','-','-','+','-','-','-','-','-','+','-','-','-','-','-'},
									{' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' '},
									{' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' '},
									{' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' '},
									{'-','-','-','-','-','+','-','-','-','-','-','+','-','-','-','-','-'},
									{' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' '},
									{' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' '},
									{' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' '}};
int y=2,x=2,who=1,over_O=0,over_X=0	,step1=1,com=0,over=0,hard=0;
int step_AI=0,O=0;

void full_screen()  //顯示全螢幕 
{
	keybd_event(VK_MENU,0,0,0);  //模擬按下alt 
    keybd_event(VK_RETURN,0,0,0); 	//模擬按下enter 
    keybd_event(VK_MENU,0,KEYEVENTF_KEYUP,0); //模擬放開alt 
    keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0); //模擬放開enter 
}

void board()  //面板顯示 
{
	system("cls");  //情除畫面 
	printf("\n");
	for (i=0;i<30;i++) 
	{
    	printf("%s\n", show[i]);
	}
}

void board_2()  //九宮格顯示 
{
	for(i=0;i<11;i++)
	{
		for(j=0;j<17;j++)
		{
			show[i+10][j+42]=show_2[i][j];
		}
	}
	system("cls");
	printf("\n");
	for(i=0;i<10;i++)
	{
		printf("%s\n", show[i]);
	}
	for (i=10;i<=20;i++) 
    {
    	for(j=0;j<100;j++)
    	{
    		if(j>=42&&j<59)
    		{
    			if(show[i][j]=='O')
    			{
    				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),249); //設定O顯示顏色 (白底藍字) 
    			}
    			else if(show[i][j]=='X')
    			{
    				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),252);//設定X顯示顏色(白底紅字) 
    			}
    			else
    			{
    				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);//設定九宮格背景顏色(白底) 
    			}
			}
    		else
    		{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15); //其他皆為黑色 
			}
			printf("%c", show[i][j]);
		}
		printf("\n");
	}	
	for(i=21;i<30;i++)
	{
		printf("%s\n", show[i]);
	}
}

int win()  //勝利判斷 
{
	int no_space=0;  	//平手判斷 
	for(j=0;j<3;j++)
	{
		for(i=0;i<3;i++)
		{
			if(show_2[1+i*4][2+j*6]!=' ')
			{
				no_space=no_space+1;
			}
		}
	}
	if(no_space==9) //如果沒格子了 就平手 
	{
		over=3;
	}
	for(i=0;i<3;i++) //判斷x方向是否有人獲勝 
	{
		for(j = 0;j<=3;j++)
		{
			if(over_X==3)//如果X獲勝 
			{
				over=1;
			}
			else if(over_O==3)//如果O獲勝 
			{ 
				over=2;
			}
			if(show_2[1+i*4][2+j*6]=='O')
			{
				over_O=over_O+1;
				over_X=0;
			}
			else if(show_2[1+i*4][2+j*6]=='X')
			{
				over_X=over_X+1;
				over_O=0;
			}
		}
		over_X=0;
		over_O=0;
	}
	for(j=0;j<3;j++) //判斷y方向是否有人獲勝 
	{
		for(i = 0;i<=3;i++)
		{
			if(over_X==3) //如果X獲勝 
			{
				over=1;
			}
			else if(over_O==3) //如果O獲勝 
			{
				over=2;
			}
			if(show_2[1+i*4][2+j*6]=='O')
			{
				over_O=over_O+1;
				over_X=0;
			}
			else if(show_2[1+i*4][2+j*6]=='X')
			{
				over_X=over_X+1;
				over_O=0;
			}
		}
		over_X=0;
		over_O=0;
	}
	if(show_2[1][2]=='O' && show_2[5][8] =='O'&& show_2[9][14]=='O') //判斷O斜線方向是否獲勝 
	{
		over_O=3;
		over=2;
	}
	else if(show_2[9][2]=='O' && show_2[5][8]=='O' && show_2[1][14]=='O') //判斷O反斜線方向是否獲勝 
	{
		over_O=3;
		over=2;
	}
	else if(show_2[1][2]=='X' && show_2[5][8]=='X' && show_2[9][14]=='X') //判斷X斜線方向是否獲勝
	{
		over_X=3;
		over=1;
	}
	else if(show_2[9][2]=='X' && show_2[5][8]=='X' && show_2[1][14]=='X')//判斷X反斜線方向是否獲勝
	{
		over_X=3;
		over=1;
	}
	return over;
}

void one_player()  //單人模式 
{
	a:
	srand(time(NULL));  //設定隨機數 
	int randomx,randomy;
	if(who==0) //AI的回合 
	{
		int AI_x=0;	
		if(hard==0) //簡單難度 
		{
			while(1)
			{	
				randomx = rand()%3+1;
				randomy = rand()%3+1;
				if(show_2[1+(randomy-1)*4][2+(randomx-1)*6]==' ')
				{
					show_2[1+(randomy-1)*4][2+(randomx-1)*6]='X';
					board_2();
					who=1;
					break;
				}
			}
		}
		else if(hard==1)  //普通難度 
		{
			switch(step_AI)
			{
				case 0:        
					if(show_2[5][8]=='O')
					{
						show_2[1][2]='X';
						who=1;
						step_AI=1;
						board_2();
					}
					else if(show_2[5][8]!='O')
					{
						show_2[5][8]='X';
						who=1;
						step_AI=1;
						board_2();
					}
					break;
				case 1:
					for(i=0;i<3;i++) //判斷X方向是否有兩個O連線 
					{
						for(j=0;j<3;j++)
						{
							if(show_2[1+i*4][2+j*6]=='O')
							{
								O=O+1;
							}
							if(O==2)
							{
								for(b=0;b<3;b++)
								{
									if(show_2[1+i*4][2+b*6]==' ')
									{
										show_2[1+i*4][2+b*6]='X';
										who=1;
										O=0;
										board_2();
										goto a;
									}
								}
							}
						}
						O=0;
					}
					for(j=0;j<3;j++)  //判斷y方向是否有兩個O連線 
					{
						for(i=0;i<3;i++)
						{
							if(show_2[1+i*4][2+j*6]=='O')
							{
								O=O+1;
							}
							if(O==2)
							{
								for(b=0;b<3;b++)
								{
									if(show_2[1+b*4][2+j*6]==' ')
									{
										show_2[1+b*4][2+j*6]='X';
										who=1;
										O=0;
										board_2();
										goto a;
									}
								}
							}
						}
						O=0;	
					}
					for(i=0;i<3;i++) //判斷X斜線向是否有兩個O連線
					{
						if(show_2[1+i*4][2+i*6]=='O')
						{
							O=O+1;
						}
						if(O==2)
						{
							for(b=0;b<3;b++)
							{
								if(show_2[1+b*4][2+b*6]==' ')
								{
									show_2[1+b*4][2+b*6]='X';									
									who=1;
									O=0;
									board_2();
									goto a;
								}
							}
						}
					}
					O=0;
					for(i=0;i<3;i++)  //判斷X反斜線向是否有兩個O連線 
					{
						if(show_2[1+i*4][2+(2-i)*6]=='O')
						{
							O=O+1;
						}
						if(O==2)
						{
							for(b=0;b<3;b++)
							{
								if(show_2[1+b*4][2+(2-b)*6]==' ')
								{
									show_2[1+b*4][2+(2-b)*6]='X';										
									who=1;
									O=0;
									board_2();
									goto a;
								}
							}
						}
					}
					O=0;
					while(1) //如果都沒有就隨便下 
					{	
						randomx = rand()%3+1;
						randomy = rand()%3+1;
						if(show_2[1+(randomy-1)*4][2+(randomx-1)*6]==' ')
						{
							show_2[1+(randomy-1)*4][2+(randomx-1)*6]='X';
							board_2();
							who=1;
							goto a;
						}
					}
					break;
				default:
					break;
			}
		}
		
	}
	char a;
	if(win()==0)  //如果沒有AI獲勝 
	{
		a=getch();  //讀取按下的鍵   玩家的回合 
	}
	if(a=='S'||a=='s')  //向下一格 
	{ 
		if(y<3)
		{ 
			show_2[2+(y-1)*4][2+(x-1)*6]=' ';
			y++;
			show_2[2+(y-1)*4][2+(x-1)*6]='.';
			board_2();
		} 
	}
	else if(a=='W'||a=='w') //向上一格 
	{
		if(y>1)
		{
			show_2[2+(y-1)*4][2+(x-1)*6]=' ';
			y--;
			show_2[2+(y-1)*4][2+(x-1)*6]='.';
			board_2();
		}
	}
	else if(a=='A'||a=='a') //向左一格 
	{
		if(x>1)
		{
			show_2[2+(y-1)*4][2+(x-1)*6]=' ';
			x--;
			show_2[2+(y-1)*4][2+(x-1)*6]='.';
			board_2();
		}
	}
	else if(a=='D'||a=='d')//像右一格 
	{
		if(x<3)
		{
			show_2[2+(y-1)*4][2+(x-1)*6]=' ';
			x++;	
			show_2[2+(y-1)*4][2+(x-1)*6]='.';
			board_2(); 
		}
	}
	else if(a==13) //按下enter下棋 
	{
		if(who==1 && show_2[1+(y-1)*4][2+(x-1)*6]==' ')
		{
			show_2[1+(y-1)*4][2+(x-1)*6]='O';
			board_2();
			who=0;
		}
	}
	 
}


void two_player() //雙人模式 
{	
	char a=getch();
	if(a=='S'||a=='s')//向下一格
	{ 
		if(y<3)
		{ 
			show_2[2+(y-1)*4][2+(x-1)*6]=' ';
			y++;
			show_2[2+(y-1)*4][2+(x-1)*6]='.';
			board_2();
		} 
	}
	else if(a=='W'||a=='w')//向上一格
	{
		if(y>1)
		{
			show_2[2+(y-1)*4][2+(x-1)*6]=' ';
			y--;
			show_2[2+(y-1)*4][2+(x-1)*6]='.';
			board_2();
		}
	}
	else if(a=='A'||a=='a')//向左一格
	{
		if(x>1)
		{
			show_2[2+(y-1)*4][2+(x-1)*6]=' ';
			x--;
			show_2[2+(y-1)*4][2+(x-1)*6]='.';
			board_2();
		}
	}
	else if(a=='D'||a=='d')//向右一格
	{
		if(x<3)
		{
			show_2[2+(y-1)*4][2+(x-1)*6]=' ';
			x++;	
			show_2[2+(y-1)*4][2+(x-1)*6]='.';
			board_2(); 
		}
	}
	else if(a==13) //按enter下棋 
	{
		if(who == 1 && show_2[1+(y-1)*4][2+(x-1)*6]==' ') //O的回合 
		{
			show_2[1+(y-1)*4][2+(x-1)*6]='O';
			board_2();
			who = 0;
		}
		else if(who == 0 && show_2[1+(y-1)*4][2+(x-1)*6]==' ') //X的回合 
		{
			show_2[1+(y-1)*4][2+(x-1)*6]='X';
			board_2();	
			who = 1;
		}
	}
} 
int start() //一開始遊戲顯示的畫面 
{
	for(i=0;i<29;i++)
	{
		for(j=0;j<100;j++)
		{
			show[i][j]=' ';
		}
	}
	for(i=0;i<100;i++)
	{
		show[0][i]='-';
		show[29][i]='-';
	}
	for(i=1;i<29;i++)
	{
		show[i][0]='|';
		show[i][99]='|';
	}
	{
		char str[]="start game:";
		for(i=0;i<strlen(str);i++)
		{
			show[10][20+i]=str[i];
		}
	}
	{ 
		char str[]="exit:";
		for(i=0;i<strlen(str);i++)
		{
			show[15][20+i]=str[i];
		}
	} 
	{ 
		char str[]="production staff:";
		for(i=0;i<strlen(str);i++)
		{
			show[20][20+i]=str[i];
		}
		show[10][31]='*';
	} 
	{ 
		char str[]="[Use w and s to up and down]";
		for(i=0;i<strlen(str);i++)
		{
			show[27][35+i]=str[i];
		}
	}
	{	
		char str[]="[Press enter choose mode]";
		for(i=0;i<strlen(str);i++)
		{ 
			show[28][37+i]=str[i];
		} 
	} 
}

void clear()  //清除畫面 
{
	for(i=1;i<29;i++)
	{
		for(j=1;j<99;j++)
		{ 
			show[i][j]=' ';
		}		
	}
}

void gameover() //遊戲結束畫面 
{
	
	clear();
	{ 
		char str[]="Game over";
		for(i=0;i<strlen(str);i++)
		{	
			show[15][45+i]=str[i];
		}
	} 
	if(over==1)  //X獲勝 
	{
		char str[]="X win";
		for(i=0;i<strlen(str);i++)
		{	
			show[17][45+i]=str[i];
		}
	}
	else if(over==2) //O獲勝 
	{
		char str[]="O win";
		for(i=0;i<strlen(str);i++)
		{	
			show[17][45+i]=str[i];
		}
	}
	else //平手 
	{
	
		char str[]="Tie";
		for(i=0;i<strlen(str);i++)
		{	
			show[17][45+i]=str[i];
		}
	}
	{
		char str[]="[Press enter to restart]"; //重新開始 
		for(i=0;i<strlen(str);i++)
		{ 
			show[28][37+i]=str[i];
		}
	}
	board();
}
void rule() //規則畫面 
{
	{
		char str[]="rule:";
		for(i=0;i<strlen(str);i++)
		{
			show[5][15+i]=str[i];
		}
	}
	{
		char str[]="1.Use w.a.s.d to control";
		for(i=0;i<strlen(str);i++)
		{
			show[8][15+i]=str[i];
		}
	}
	{
		char str[]="2.Use enter to confirm";
		for(i=0;i<strlen(str);i++)
		{
			show[10][15+i]=str[i];
		}
	}
	{
		char str[]="3.Play for fun!";
		for(i=0;i<strlen(str);i++)
		{
			show[12][15+i]=str[i];
		}
	}
	{
		char str[]="[Press enter start]";
		for(i=0;i<strlen(str);i++)
		{ 
			show[28][37+i]=str[i];
		}
	}
}

void staff()  //製作人員畫面 
{
	clear();
	{
		char str[]="1.B11207018";  //程式編寫100% 程式測試40% 報告製作50% 
		for(i=0;i<strlen(str);i++)
		{
			show[8][15+i]=str[i];
		}
	}
	{
		char str[]="2.B11207019"; //報告製作25% 程式測試30%
		for(i=0;i<strlen(str);i++)
		{
			show[10][15+i]=str[i];
		}
	}
	{
		char str[]="3.B11207016"; //報告製作25% 程式測試30%
		for(i=0;i<strlen(str);i++)
		{
			show[12][15+i]=str[i];
		}
	}
	{
		char str[]="[Press enter back]";
		for(i=0;i<strlen(str);i++)
		{	 
			show[28][37+i]=str[i];
		}
	}
	board();
}

int main() //主程式 
{
	full_screen();//呼叫全螢幕 
	restart:
	step=0;
	start();
	Sleep(1000); //暫停一秒 
	board();
	while(step==0) //顯示第一個畫面 
	{
		char a=getch();
		if((a=='W'||a=='w')&&step1>1) //按W向上一格 
		{ 
			step1=step1-1;
		}
		else if((a=='S'||a=='s')&&step1<3) //按S向下一格 
		{
			step1=step1+1;
		}
		if(step1==1)  //顯示* 
		{
			show[10][31]='*';
			show[15][25]=' ';
			show[20][37]=' ';
			board();
		}
		else if(step1==2)
		{
			show[10][31]=' ';
			show[15][25]='*';
			show[20][37]=' ';
			board();	
		}
		else if(step1==3)
		{
			show[10][31]=' ';
			show[15][25]=' ';
			show[20][37]='*';
			board();
		}
		if(step1==1&&a==13)  //開始遊戲 
		{
			step=1;
			break;
		}
		else if(step1==2&&a==13)  //退出遊戲 
		{
			clear();
			{
				char str[]="Bye Bye";
				for(i=0;i<strlen(str);i++)
				{ 
					show[15][45+i]=str[i];
				}
			}
			board();
			return 0;
		}
		else if(step1==3&&a==13) //顯示製作人員畫面 
		{
			staff();
			while(1)
			{
				char a=getch();
				if(a==13)
				{
					clear();
					board();
					step1=1;
					break;
				}
			}
			goto restart;	
		}
	}
	clear();
	{
		char str[]="[Use w and s to up and down]";
		for(i=0;i<strlen(str);i++)
		{
			show[27][35+i]=str[i];
		}
	}
	{
		char str[]="[Press enter choose mode]";
		for(i=0;i<strlen(str);i++)
		{	 
			show[28][37+i]=str[i];
		}
	}
	{
		char str[]="One player:";
		for(i=0;i<strlen(str);i++)
		{
			show[10][20+i]=str[i];
		}
	}
	{
		char str[]="Two player:";
		for(i=0;i<strlen(str);i++)
		{
			show[15][20+i]=str[i];
		}
	}
	show[10][31]='*';
	board();
	while(step==1) //選擇 
	{   
		char a=getch();
		if((a=='W'||a=='w')&&step1>1)//按W向上一格 
		{ 
			step1=step1-1;
		}
		else if((a=='S'||a=='s')&&step1<2) //按S向下一格  
		{
			step1=step1+1;
		}
		if(step1==1)  //顯示* 
		{
			show[10][31]='*';
			show[15][31]=' ';
			board();
		}
		else if(step1==2)
		{
			show[10][31]=' ';
			show[15][31]='*';
			board();	
		}
		if(step1==1 && a==13)
		{
			com=1;
			step=7;
		}
		else if(step1==2 && a==13)
		{
			com=0;
			step=4;
		}
	}
	clear();
	if(step==7) //單人模式選擇難度 
	{
		{
			char str[]="[Use w and s to up and down]";
			for(i=0;i<strlen(str);i++)
			{
				show[27][35+i]=str[i];
			}
		}
		{
			char str[]="[Press enter choose mode]";
			for(i=0;i<strlen(str);i++)
			{	 
				show[28][37+i]=str[i];
			}
		}
		{
			char str[]="easy:";
			for(i=0;i<strlen(str);i++)
			{
				show[10][20+i]=str[i];
			}
		}
		{
			char str[]="normal:";
			for(i=0;i<strlen(str);i++)
			{
				show[15][20+i]=str[i];
			}
		}
		show[10][25]='*';
		board();
		while(step==7)
		{
			char a=getch();
			if((a=='W'||a=='w')&&step1>1)//按W向上一格 
			{ 
				step1=step1-1;
			}
			else if((a=='S'||a=='s')&&step1<2) //按S向下一格  
			{
				step1=step1+1;
			}
			if(step1==1)  //顯示* 
			{
				show[10][25]='*';
				show[15][27]=' ';
				board();
			}
			else if(step1==2)
			{
				show[10][25]=' ';
				show[15][27]='*';
				board();	
			}
			if(step1==1 && a==13)
			{
				hard=0;
				step=4;
			}
			else if(step1==2 && a==13)
			{
				hard=1;
				step=4;
			}
		}
	}
	while(step==4)//顯示規則畫面 
	{
		clear();
		rule();
		board();
		char a=getch();
		if(a==13)
		{
			step=2;	
		}
	}
	
	clear();
	show_2[2+(y-1)*4][2+(x-1)*6]='.';
	board_2(); 
	while(step==2) //呼叫單人函式或雙人函式 
	{
		if(com==0)
		{
			two_player();
		} 
		else if(com==1)
		{
			one_player();
		}
		if(win()!=0)  //如果有人獲勝或平手 
		{
			step=3;
			break;
		}
	}
	gameover();
	while(1)
	{
		char a=getch();
		if(a==13)
		{
			break;
		}
	}
	clear();
	board();
	while(step==3) //重啟遊戲 復歸 
	{
		step=0;
		y=2;
		x=2;
		who=1;
		over_O=0;
		over_X=0;
		over=0;
		hard=0;
		com=0;
		O=0;
		step1=1;
		step_AI=0;
		for(i=0;i<11;i++)
		{
			for(j=0;j<17;j++)
			{
				if(i!=3&&i!=7&&j!=5&&j!=11)
				{
					show_2[i][j]=' ';
				}
			}
		}
		goto restart;
	}
	return 0;
}
