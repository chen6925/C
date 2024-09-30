#include <stdio.h>
#include <windows.h> 
#include <stdlib.h>
#include <time.h>  
#include <math.h>

char up = 'w',down = 's',left = 'a',right = 'd',up_2 = 'H',down_2 = 'P',left_2 = 'K',right_2 = 'M';
int no_space1,no_space2,one_xy[4][4] = {0},two_xy[4][4] = {0},grade[11] = {0},background = 0,gameover = 0,lock = 1,g = 0,lock2 = 1,g1 = 0,gameover2 = 0;

void first()  //基礎設置 

{	keybd_event(VK_MENU,0x38,0,0);  //模擬按下alt 
    keybd_event(VK_RETURN,0x1c,0,0); 	//模擬按下enter 
    keybd_event(VK_MENU,0xb8,KEYEVENTF_KEYUP,0); //模擬放開alt 
    keybd_event(VK_RETURN,0x9c,KEYEVENTF_KEYUP,0); //模擬放開enter 
    srand(time(NULL));
    Sleep(500);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); 
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(handle, &info);
    info.bVisible = FALSE;  //隱藏光標
    SetConsoleCursorInfo(handle, &info);
}

int gotoxy(int x,int y) //移動游標 
{
	COORD coord; //創建一個coord結構 
	coord.X = x; //將x值存入 
	coord.Y = y; // 將y值存入 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord); //將游標改到新座標 
}

void board() //框框建立 
{
	int i = 0,j = 0;
	for(i = 0;i <= 30;i++)
	{
		for(j = 0;j <= 100;j++)
		{
			if(i == 0 || i == 30)
			{
				gotoxy(j,i);
				printf("-");
			}
			else if(i > 0 && i < 30)
			{ 
				if(j == 0 || j == 100)
				{
					gotoxy(j,i);
					printf("|");
				}
			}
		}
		printf("\n");
	}
}

void one_player_board()//單人模式框框建立 
{
	int i = 0,j = 0,k = 0;
	gotoxy(20,10);
	for(i = 1;i <= 5;i++)
	{
		for(j = 1;j <= 33;j++)
		{
			if(j % 8 == 1)
			{
				printf("+");
			}
			else
			{
				printf("-");	
			}
		}
		gotoxy(20,i * 4 + 10);
	}
	for(i = 0;i < 4;i++)
	{
		for(j = 1;j <= 3;j++)
		{
			for(k = 0;k < 5;k++)
			{
				gotoxy(k * 8 + 20,j + (i * 4) + 10);
				printf("|"); 
			}
		}
	} 
	for(i = 10;i <= 25;i++)
	{
		gotoxy(60,i);
		if(i == 10 || i == 25)
		{
			printf("+-----------------------+");	
		}
		else
		{
			printf("|                       |");	
		}
	}
}

void two_player_board() //雙人模式框框建立 
{
	int i = 0,j = 0,k = 0,z = 0;
	for(z = 0;z < 2;z++)
	{
		gotoxy(20 + (z * 50),10);
		for(i = 1;i <= 5;i++)
		{
			for(j = 1;j <= 33;j++)
			{
				if(j % 8 == 1)
				{
					printf("+");
				}
				else
				{
					printf("-");	
				}
			}
			gotoxy(20 + (z * 50),i * 4 + 10);
		}
		for(i = 0;i < 4;i++)
		{
			for(j = 1;j <= 3;j++)
			{
				for(k = 0;k < 5;k++)
				{
					gotoxy((k * 8) + 20 + (z * 50),j + (i * 4) + 10);
					printf("|"); 
				}
			}
		} 
	}
}

void other_board() //其他選項畫面  
{
	board();
	gotoxy(25,5);
	printf("|其他選項|"); 
	gotoxy(25,8);
	printf("排行榜:");
	gotoxy(25,13);
	printf("製作人員:");
	gotoxy(45,27);
	printf("[按下esc返回主畫面]"); 
	gotoxy(45,28);
	printf("[按下enter確認模式]"); 
	gotoxy(45,29);
	printf("[使用%c,%c控制選擇模式]",up,down); 
}

void grade_board() //排行榜 
{
	int i = 0;
	char enter;
	board();
	gotoxy(25,5);
	printf("|排行榜|"); 
	for(i = 0;i < 10;i++)
	{
		gotoxy(25,5+2*(i+1));
		printf("No.%d:%d",i+1,grade[i]);	
	}
	gotoxy(45,29);
	printf("[按下esc返回主畫面]"); 
	while(1)
	{
		enter = getch();
		if(enter == 27)
		{
			break;
		}
	}
}

void start()//主畫面 
{
	int i = 0,j = 0;
	board();
	gotoxy(25,8);
	printf("開始遊戲:");
	gotoxy(25,13);
	printf("其他選項:");
	gotoxy(25,18);
	printf("遊戲設定:");
	gotoxy(25,23);
	printf("退出遊戲:");
	gotoxy(45,28);
	printf("[按下enter確認模式]"); 
	gotoxy(45,29);
	printf("[使用%c,%c控制選擇模式]",up,down); 
}

void clear(int x1,int x2,int y1,int y2) //清除座標內顯示的東西 
{
	int i = 0,j = 0;
	for(i = y1;i <= y2;i++)
	{
		for(j = x1;j <= x2;j++)
		{
			gotoxy(j,i);
			printf(" ");
		}
	}
}

void staff()//製作人員畫面 
{
	char enter;
	board();
	gotoxy(25,5);
	printf("|製作人員|"); 
	gotoxy(25,8);
	printf("1.B11207018 陳柏霖");
	gotoxy(25,13);
	printf("2.B11207016 李家興");
	gotoxy(25,18);
	printf("3.B11208019 謝宇廷"); 
	gotoxy(45,28);
	printf("[使用esc返回其他選項]");
	while(1)
	{
	 	enter = getch();
		if(enter == 27)
		{
			break;
		}
	}
}

void other()//其他選項箭頭上下控制 
{
	char enter;
	other_board();
	int mode = 0;
	while(1){
		if(enter == down)
		{ 
			if(mode != 1)
			{
				mode = mode + 1;
			}
		}
		else if(enter == up)
		{ 
			if(mode != 0)
			{
				mode = mode - 1;	
			}
		}
		if(mode == 0)
		{
			if(enter == 13)
			{
				system("cls");
				grade_board();
				system("cls");
				other_board();
			} 
			clear(35, 36, 13, 13);
			gotoxy(35,8);
			printf("<-");
		}
		else if(mode == 1)
		{
			if(enter == 13)
			{
				system("cls");
				staff();
				system("cls");
				other_board();
			} 
			clear(35, 36, 8, 8);
			gotoxy(35,13);
			printf("<-");
		}
		if(enter == 27)
		{
			break;	
		}
		enter = getch();
	}
}

int setting(int light)//遊戲設定 
{
	int step = 0;
	char enter;
	gotoxy(30,4);
	printf("夜間模式: "); 
	gotoxy(30,7);
	printf("控制鍵更改 (按enter後按下想要修改的鍵:a~z或A~Z) ");
	gotoxy(30,9);
	printf("向上移動:%c",up); 
	gotoxy(30,11);
	printf("向下移動:%c",down);
	gotoxy(30,13);
	printf("向左移動:%c",left);
	gotoxy(30,15);
	printf("向右移動:%c",right);
	gotoxy(30,17);
	printf("向上移動__紅:%c",up_2); 
	gotoxy(30,19);
	printf("向下移動__紅:%c",down_2);
	gotoxy(30,21);
	printf("向左移動__紅:%c",left_2);
	gotoxy(30,23);
	printf("向右移動__紅:%c",right_2);
	gotoxy(45,28);
	printf("[使用esc返回主畫面]"); 
	gotoxy(45,29);
	printf("[使用%c,%c控制選擇模式]",up,down); 
	while(1)
	{
		if(enter == 27)
		{
			break;
		}
		else if(enter == down && step < 8)
		{
			step = step + 1;
		}
		else if(enter == up && step > 0)
		{
			step = step - 1;
		}
		if(step == 0) //更改背景顏色 
		{
			gotoxy(40,4);
			printf("<-");
			clear(40,41,9,9);
			if(enter == 13 && light == 0)
			{
				light = 1;
			}
			else if(enter == 13 && light == 1)
			{
				light = 0;
			}
			if(light == 0)
			{
				gotoxy(39,4);
				printf("O");
				background = 0;
				system("color 0F");
			}
			else if(light == 1)
			{
				gotoxy(39,4);
				printf("X");
				background = 1;
				system("color F0");		
			} 
		} 
		else if(step == 1)
		{
			gotoxy(40,9);
			printf("<-");
			clear(40,41,4,4);
			clear(40,41,11,11);
			if(enter == 13)
			{
				while(1)
				{
					gotoxy(39,9);
					printf(" ");
					enter = getch();
					if(((enter >= 65 && enter <= 90)||enter >= 97 && enter <= 122) && enter != down && enter != left && enter != right && enter != up_2 &&enter != down_2 && enter != left_2 && enter != right_2)
					{	
						gotoxy(39,9);
						printf("%c",enter);
						up = enter;
						gotoxy(45,29);
						printf("[使用%c,%c控制選擇模式]",up,down); 
						break;
					}
				}
			}
		}
		else if(step == 2)
		{
			gotoxy(40,11);
			printf("<-");
			clear(40,41,9,9);
			clear(40,41,13,13);
			if(enter == 13)
			{
				while(1)
				{
					gotoxy(39,11);
					printf(" ");
					enter = getch();
					if(((enter >= 65 && enter <= 90)||enter >= 97 && enter <= 122) && enter != up && enter !=right && enter != left && enter != up_2 &&enter != down_2 && enter != left_2 && enter != right_2) 
					{	
						gotoxy(39,11);
						printf("%c",enter);
						down = enter;
						gotoxy(45,29);
						printf("[使用%c,%c控制選擇模式]",up,down); 
						break;
					}
				}
			}
		}
		else if(step == 3)
		{
			gotoxy(40,13);
			printf("<-");
			clear(40,41,11,11);
			clear(40,41,15,15);
			if(enter == 13)
			{
				while(1)
				{
					gotoxy(39,13);
					printf(" ");
					enter = getch();
					if(((enter >= 65 && enter <= 90)||enter >= 97 && enter <= 122) && enter != up && enter != right && enter != down && enter != up_2 &&enter != down_2 && enter != left_2 && enter != right_2)
					{	
						gotoxy(39,13);
						printf("%c",enter);
						left = enter;
						gotoxy(45,29);
						printf("[使用%c,%c控制選擇模式]",up,down); 
						break;
					}
				}
			}
		}
		else if(step == 4)
		{
			gotoxy(40,15);
			printf("<-");
			clear(40,41,13,13);
			clear(44,45,17,17);
			if(enter == 13)
			{
				while(1)
				{
					gotoxy(39,15);
					printf(" ");
					enter = getch();
					if(((enter >= 65 && enter <= 90)||enter >= 97 && enter <= 122) && enter != up && enter != left && enter != down && enter != up_2 &&enter != down_2 && enter != left_2 && enter != right_2)
					{	
						gotoxy(39,15);
						printf("%c",enter);
						right = enter;
						gotoxy(45,29);
						printf("[使用%c,%c控制選擇模式]",up,down); 
						break;
					}
				}
			}
		}
		else if(step == 5)
		{
			gotoxy(44,17);
			printf("<-");
			clear(40,41,15,15);
			clear(44,45,19,19);
			if(enter == 13)
			{
				while(1)
				{
					gotoxy(43,17);
					printf(" ");
					enter = getch();
					if(((enter >= 65 && enter <= 90)||enter >= 97 && enter <= 122) && enter != up && enter != down && enter != left && enter != right &&enter != down_2 && enter != left_2 && enter != right_2)
					{	
						gotoxy(43,17);
						printf("%c",enter);
						up_2 = enter;
						gotoxy(45,29);
						printf("[使用%c,%c控制選擇模式]",up,down); 
						break;
					}
				}
			}
		}
		else if(step == 6)
		{
			gotoxy(44,19);
			printf("<-");
			clear(44,45,17,17);
			clear(44,45,21,21);
			if(enter == 13)
			{
				while(1)
				{
					gotoxy(43,19);
					printf(" ");
					enter = getch();
					if(((enter >= 65 && enter <= 90)||enter >= 97 && enter <= 122) && enter != up && enter != down && enter != left && enter != right && enter != up_2 && enter != left_2 && enter != right_2) 
					{	
						gotoxy(43,19);
						printf("%c",enter);
						down_2 = enter;
						gotoxy(45,29);
						printf("[使用%c,%c控制選擇模式]",up,down); 
						break;
					}
				}
			}
		}
		else if(step == 7)
		{
			gotoxy(44,21);
			printf("<-");
			clear(44,45,19,19);
			clear(44,45,23,23);
			if(enter == 13)
			{
				while(1)
				{
					gotoxy(43,21);
					printf(" ");
					enter = getch();
					if(((enter >= 65 && enter <= 90)||enter >= 97 && enter <= 122) && enter != up && enter != down && enter != left && enter != right && enter != up_2 &&enter != down_2 && enter != right_2)
					{	
						gotoxy(43,21);
						printf("%c",enter);
						left_2 = enter;
						gotoxy(45,29);
						printf("[使用%c,%c控制選擇模式]",up,down); 
						break;
					}
				}
			}
		}
		else if(step == 8)
		{
			gotoxy(44,23);
			printf("<-");
			clear(44,45,21,21);
			if(enter == 13)
			{
				while(1)
				{
					gotoxy(43,23);
					printf(" ");
					enter = getch();
					if(((enter >= 65 && enter <= 90)||enter >= 97 && enter <= 122) && enter != up && enter != down && enter != left && enter != right && enter != up_2 &&enter != down_2 && enter != left_2)
					{	
						gotoxy(43,23);
						printf("%c",enter);
						right_2 = enter;
						gotoxy(45,29);
						printf("[使用%c,%c控制選擇模式]",up,down); 
						break;
					}
				}
			}
		}
		enter = getch();
	}
	return light;
}

void rule(int num_player)//顯示規則畫面 
{
	if(num_player == 1)
	{
		gotoxy(25,5);
		printf("|規則|"); 
		gotoxy(25,8);
		printf("1.使用%c%c%c%c控制",up,left,down,right);
		gotoxy(25,13);
		printf("2.每合併一個東西加一分");
		gotoxy(45,28);
		printf("[按enter開始]");
	}
	else
	{
		gotoxy(25,5);
		printf("|規則|"); 
		gotoxy(25,8);
		printf("1.玩家1使用%c%c%c%c控制",up,left,down,right);
		gotoxy(25,12);
		printf("2.玩家2使用%c%c%c%c控制",up_2,left_2,down_2,right_2);
		gotoxy(25,16);
		printf("3.每合併一個東西加一分");
		gotoxy(25,20);
		printf("4.每8分攻擊一次"); 
		gotoxy(25,24);
		printf("5.倒數三秒後開始遊戲"); 
		gotoxy(45,28);
		printf("[按enter開始]");
	}
}

void over(int num_player) //遊戲結束判斷 
{
	int i,j,no1 = 0,no2 = 0;
	if(gameover == 1)//如果玩家一已經結束了,那就跳過他的判斷 
	{
		no1 = 1;
	}
	if(gameover2 == 1)
	{
		no2 = 1;
	}
	gameover = 1;
	if(no1 != 1)
	{
		for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				if(one_xy[i][j] == 0) //如果還有空位 
				{
					gameover = 0;
					break;	
				}
				if(j < 3)
				{
					if(one_xy[i][j] == one_xy[i][j+1]) //如果還可以合成 
					{
						gameover = 0;
						break;	
					}
				}
				if(i < 3)
				{
					if(one_xy[i][j] == one_xy[i+1][j])
					{
						gameover = 0;	
						break;
					}
				}
			}
		}
	}
	if(num_player == 2 && no2 != 1)
	{	
		gameover2 = 1;
		for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				if(two_xy[i][j] == 0)
				{
					gameover2 = 0;
					break;	
				}
				if(j < 3)
				{
					if(two_xy[i][j] == two_xy[i][j+1])
					{
						gameover2 = 0;
						break;	
					}
				}
				if(i < 3)
				{
					if(two_xy[i][j] == two_xy[i+1][j])
					{
						gameover2 = 0;	
						break;
					}
				}
			}
		}
	}
}

void move(int num_player) //數字移動 
{
	char enter,enter2;
	enter = '0';
	int x,y,i,j,k,h,a,l,c,n,no = 100;	
	gotoxy(0,0);
	if(gameover != 1)
	{
		if(lock == 1)
		{
			for(i = 0;i < 4;i++)
			{
				for(j = 0;j < 4;j++)
				{ 
					gotoxy(22+i*8,12+j*4);
					printf("    "); 
				} 
			}
			do  //隨機生成2或4 
			{
				a = 0;
				x = rand() % 4;
				y = rand() % 4;
				if(one_xy[x][y] != 0)
				{
					a = 1;		
				}
			}while(a == 1);
			one_xy[x][y] = 2 * (rand() % 2 + 1);
	
			for(i = 0;i < 4;i++)
			{
				for(j = 0;j < 4;j++)
				{ 
					gotoxy(22+i*8,12+j*4);
					n = one_xy[i][j];
					c = 0;
					while(n > 1)
					{
						n /= 2;
						c++;
					}
					if(background == 0)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c); //字體色更改 
					}
					else
					{				
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c+240);
					}
					printf("%d",one_xy[i][j]); 
				}
			}
		
		}
		lock = 0;
	}
	if(kbhit())//輸入 
	{
		enter = getch();
	}
	over(num_player);//結束判斷 
	if(num_player == 2)  //玩家二移動與數字生成 
	{
		if(gameover2 != 1)
		{
			if(lock2 == 1)
			{
				for(i = 0;i < 4;i++)
				{
					for(j = 0;j < 4;j++)
					{ 
						gotoxy(72+i*8,12+j*4);
						printf("    "); 
					} 
				}
				do //玩家二隨機生成2或4 
				{
					a = 0;
					x = rand() % 4;
					y = rand() % 4;
					if(two_xy[x][y] != 0)
					{
						a = 1;
					}
				}while(a == 1);
				two_xy[x][y] = 2 * (rand() % 2 + 1);
				for(i = 0;i < 4;i++)
				{
					for(j = 0;j < 4;j++)
					{ 
						gotoxy(72+i*8,12+j*4);
						n = two_xy[i][j];
						c = 0;
						while(n > 1)
						{
							n /= 2;
							c++;
						}
						if(background == 0)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c); //顏色設定 
						}
						else
						{				
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c+240);
						}
						printf("%d",two_xy[i][j]); 
					}
				}
			}
			lock2 = 0;
			
			if(enter == up_2 || enter2 == up_2) //判斷玩家二按下的鍵 
			{
				for(i = 0;i < 4;i++)
				{
					no = 100;
					for(j = 0;j < 4;j++)
					{
						if(g1 % 8 == 0 && g1 != 0) //攻擊時,如果對方已經沒有位子了,對方停止遊戲 
						{
							lock = 1;
							g1++;
							gameover = 1;
							for(k = 0;k < 4;k++)
							{
								for( h = 0;h < 4;h++)
								{
									if(one_xy[k][h] == 0)
									{
										gameover = 0;	
										break;
									}
								}
							}
						}
						if(two_xy[i][j] != 0)
						{
							for(k = 0;k <= j;k++)
							{	
								if(two_xy[i][k] == 0)
								{	
									two_xy[i][k] = two_xy[i][j];
									two_xy[i][j] = 0; 
									j = k;
									lock2 = 1;
								}
							}
							if(j > 0)
							{
								if(two_xy[i][j-1] == two_xy[i][j] && j-1 != no)
								{
									two_xy[i][j-1] *= 2;
									two_xy[i][j] = 0;
									no = j-1;
									lock2 = 1;
									g1++;
								}
							}
						}
					}
				} 
			}
			else if(enter == down_2 || enter2 == down_2)
			{
				for(i = 0;i < 4;i++)
				{
					no = 100;
					for(j = 3;j >= 0;j--)
					{
						if(g1 % 8 == 0 && g1 != 0)
						{
							lock = 1;
							g1++;
							gameover = 1;
								for(k = 0;k < 4;k++)
							{
								for( h = 0;h < 4;h++)
								{
									if(one_xy[k][h] == 0)
									{
										gameover = 0;	
										break;
									}
								}
							}
						}
						if(two_xy[i][j] != 0)
						{
							for(k = 3;k >= j;k--)
							{	
								if(two_xy[i][k] == 0)
								{	
									two_xy[i][k] = two_xy[i][j];
									two_xy[i][j] = 0; 
									j = k;
									lock2 = 1;
								}
							}
							if(j < 3)
							{
								if(two_xy[i][j+1] == two_xy[i][j] && j+1 != no)
								{
									two_xy[i][j+1] *= 2;
									two_xy[i][j] = 0;
									no = j+1;
									lock2 = 1;
									g1++;
								}
							}
						}
					}
				} 
			}
			else if(enter == right_2 || enter2 == right_2)
			{
				for(j= 0;j < 4;j++)
				{
					no = 100;
					for(i = 3;i >= 0;i--)
					{
						if(g1 % 8 == 0 && g1 != 0)
						{
							lock = 1;
							g1++;
							gameover = 1;
								for(k = 0;k < 4;k++)
							{
								for( h = 0;h < 4;h++)
								{
									if(one_xy[k][h] == 0)
									{
										gameover = 0;	
										break;
									}
								}
							}
						}
						if(two_xy[i][j] != 0)
						{
							for(k = 3;k >= i;k--)
							{	
								if(two_xy[k][j] == 0)
								{	
									two_xy[k][j] = two_xy[i][j];
									two_xy[i][j] = 0; 
									i = k;
									lock2 = 1;
								}
							}
							if(i < 3)
							{
								if((two_xy[i+1][j] == two_xy[i][j]) && i+1 != no)
								{
									two_xy[i+1][j] *= 2;
									two_xy[i][j] = 0;
									no = i+1;
									lock2 = 1;
									g1++;
								}
							}
						}
					}
				} 
			}
			else if(enter == left_2 || enter2 == left_2)
			{
				for(j= 0;j < 4;j++)
				{
					no = 100;
					for(i = 0;i < 4;i++)
					{
						if(g1 % 8 == 0 && g1 != 0)
						{
							lock = 1;
							g1++;
							gameover = 1;
							for(k = 0;k < 4;k++)
							{
								for( h = 0;h < 4;h++)
								{
									if(one_xy[k][h] == 0)
									{
										gameover = 0;	
										break;
									}
								}
							}
						}
						if(two_xy[i][j] != 0)
						{
							for(k = 0;k <= i;k++)
							{	
								if(two_xy[k][j] == 0)
								{	
									two_xy[k][j] = two_xy[i][j];
									two_xy[i][j] = 0; 
									i = k;
									lock2 = 1;
								}
							}
							if(i > 0)
							{
								if((two_xy[i-1][j] == two_xy[i][j]) && i-1 != no)
								{
									two_xy[i-1][j] *= 2;
									two_xy[i][j] = 0;
									no = i-1;
									lock2 = 1;
									g1++;
								}
							}
						}
					}
				} 
			}
		}
	}
	if(gameover != 1)//玩家一移動 
	{
		if(enter == up || enter2 == up)   //判斷玩家二按下的鍵 
		{
			for(i = 0;i < 4;i++)
			{
				no = 100;
				for(j = 0;j < 4;j++)
				{
					if(num_player == 2) //攻擊時,如果對方已經沒有位子了,對方停止遊戲 
					{
						if(g % 8 == 0 && g != 0)
						{
							lock2 = 1;
							g++;
							gameover2 = 1;
							for(k = 0;k < 4;k++)
							{
								for(h = 0;h < 4;h++)
								{
									if(two_xy[k][h] == 0)
									{
										gameover2 = 0;	
										break;
									}
								}
							}
						}
					}
					if(one_xy[i][j] != 0)
					{
						for(k = 0;k <= j;k++)
						{	
							if(one_xy[i][k] == 0)
							{	
								one_xy[i][k] = one_xy[i][j];
								one_xy[i][j] = 0; 
								j = k;
								lock = 1;
							}
						}
						if(j > 0)
						{
							if(one_xy[i][j-1] == one_xy[i][j] && j-1 != no)
							{
								one_xy[i][j-1] *= 2;
								one_xy[i][j] = 0;
								no = j-1;
								lock = 1;
								g++;
							}
						}
					}
				}
			} 
		}
		else if(enter == down || enter2 == down)
		{
			for(i = 0;i < 4;i++)
			{
				no = 100;
				for(j = 3;j >= 0;j--)
				{
					if(one_xy[i][j] != 0)
					{
						if(num_player == 2)
						{
							if(g % 8 == 0 && g != 0)
							{
								lock2 = 1;
								g++;
								gameover2 = 1;
								for(k = 0;k < 4;k++)
								{
									for(h = 0;h < 4;h++)
									{
										if(two_xy[k][h] == 0)
										{
											gameover2 = 0;	
											break;
										}
									}
								}
							}
						}
						for(k = 3;k >= j;k--)
						{	
							if(one_xy[i][k] == 0)
							{	
								one_xy[i][k] = one_xy[i][j];
								one_xy[i][j] = 0; 
								j = k;
								lock = 1;
							}
						}
						if(j < 3)
						{
							if(one_xy[i][j+1] == one_xy[i][j] && j+1 != no)
							{
								one_xy[i][j+1] *= 2;
								one_xy[i][j] = 0;
								no = j+1;
								lock = 1;
								g++;
							}
						}
					}
				}
			} 
		}
		else if(enter == right || enter2 == right)
		{
			for(j= 0;j < 4;j++)
			{
				no = 100;
				for(i = 3;i >= 0;i--)
				{
					if(num_player == 2)
					{
						if(g % 8 == 0 && g != 0)
						{
							lock2 = 1;
							g++;
							gameover2 = 1;
							for(k = 0;k < 4;k++)
							{
								for(h = 0;h < 4;h++)
								{
									if(two_xy[k][h] == 0)
									{
										gameover2 = 0;	
										break;
									}
								}
							}
						}
					}
					if(one_xy[i][j] != 0)
					{
						for(k = 3;k >= i;k--)
						{	
							if(one_xy[k][j] == 0)
							{	
								one_xy[k][j] = one_xy[i][j];
								one_xy[i][j] = 0; 
								i = k;
								lock = 1;
							}
						}
						if(i < 3)
						{
							if((one_xy[i+1][j] == one_xy[i][j]) && i+1 != no)
							{
								one_xy[i+1][j] *= 2;
								one_xy[i][j] = 0;
								no = i+1;
								lock = 1;
								g++;
							}
						}
					}
				}
			} 
		}
		else if(enter == left || enter2 == left)
		{
			for(j= 0;j < 4;j++)
			{
				no = 100;
				for(i = 0;i < 4;i++)
				{
					if(num_player == 2)
					{
					    if(g % 8 == 0 && g != 0)
						{
							lock2 = 1;
							g++;
							gameover2 = 1;
							for(k = 0;k < 4;k++)
							{
								for(h = 0;h < 4;h++)
								{
									if(two_xy[k][h] == 0)
									{
										gameover2 = 0;	
										break;
									}
								}
							}
						}
					}
					if(one_xy[i][j] != 0)
					{
						for(k = 0;k <= i;k++)
						{	
							if(one_xy[k][j] == 0)
							{	
								one_xy[k][j] = one_xy[i][j];
								one_xy[i][j] = 0; 
								i = k;
								lock = 1;
							}
						}
						if(i > 0)
						{
							if((one_xy[i-1][j] == one_xy[i][j]) && i-1 != no)
							{
								one_xy[i-1][j] *= 2;
								one_xy[i][j] = 0;
								no = i-1;
								lock = 1;
								g++;
							}
						}
					}
				}
			} 
		}
	}
	
}

void game(int num_player)//遊戲畫面 
{
	int i = 0;
	char enter;
	if(num_player == 1) //初始值設定 
	{
		one_player_board();
		one_xy[0][0] = 2;
	}
	else if(num_player == 2)  //初始值設定  
	{
		two_player_board();	
		two_xy[0][0] = 2;
		one_xy[0][0] = 2;
	}
	for(i = 3;i > 0;i--)//開始先到數3秒 
	{
		char trash;
		gotoxy(54,15);
		printf("倒數:%d",i); 
		Sleep(1000);
		while(kbhit())
		{	
			trash = getch();
		}
	}
	gotoxy(54,15);
	printf("      ");
	while(1)
	{
		if(num_player == 1)//單人模式記分板控制 
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 + background * 225);
			gotoxy(62,12);
			printf("分數:%d",g); 
			gotoxy(62,14);
			printf("使用%c%c%c%c控制",up,left,down,right);
			gotoxy(62,16);
			if(grade[0] > g)
			{ 
				printf("歷史最高分:%d",grade[0]); 
			}
			else if(grade[0] <= g)
			{
				printf("歷史最高分:%d",g);
			}  
			move(num_player);
			if(gameover == 1)
			{
				break;
			}
		}
		else if(num_player == 2)//雙人模式分數與攻擊倒數顯示 
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 + background * 225);
			gotoxy(22,5);
			printf("分數:%d",g);
			if(gameover == 1)
			{
				printf(" loss");
			}
			gotoxy(22,7);
			printf("攻擊倒數:");
			for(i = 0;i < g % 8;i++)
			{
				printf("█ ");
			}
			printf("           ");
			gotoxy(72,5);
			printf("分數:%d",g1); 
			if(gameover2 == 1)
			{
				printf(" loss");
			}
			gotoxy(72,7);
			printf("攻擊倒數:");
			for(i = 0;i < g1 % 8;i++)
			{
				printf("█ ");
			}
			printf("           ");
			move(num_player);
			if(gameover == 1 && gameover2 == 1)
			{
				break;	
			}
		}
	}
} 

void final(int num_player)//遊戲結束畫面 
{
	board();
	char enter;
	gotoxy(47,5);
	printf("|遊戲結束|");
	gotoxy(41,29);
	printf("[按下enter回到主畫面]"); 
	if(num_player == 1)
	{
		if(gameover == 1)
		{
			gotoxy(47,15);
			printf("分數:%d",g); 
		}
	}
	else if(num_player == 2)
	{
		if(g > g1)
		{
			gotoxy(47,15);
			printf("玩家1勝利"); 	
		}
		else
		{
			gotoxy(47,15);
			printf("玩家2勝利"); 	
		}
	}
	while(1)
	{
		enter = getch();
		if(enter == 13)
		{
			break;
		}
	}
}

int main()
{
	int i,j,step = 0,mode = 0,color = 0,num_player = 1;
	char enter;
	first();  //初始化 
	restart:
	start();
	board();
	while(1)
	{
		if(color == 0)
		{
			system("color 0F");//背景顏色顯示 
		}
		else 
		{
			system("color F0");
		}
		switch(step)
		{
			case 0: //主畫面選擇模式 
				if(enter == down)
				{ 
					if(mode != 3)
					{
						mode = mode + 1;	
					}
				}
				else if(enter == up)
				{ 
					if(mode != 0)
					{
						mode = mode - 1;	
					}
				}
				if(mode == 0)
				{
					clear(35, 36, 13, 13);
					gotoxy(35,8);
					printf("<-");
					if(enter == 13)
					{
						step = 1;
						system("cls");
						board();
						gotoxy(25,10);
						printf("1.單人模式");
						gotoxy(25,15);
						printf("2.雙人模式"); 
						gotoxy(35,10);
						printf("<-");
					} 
				}
				else if(mode == 1)
				{
					if(enter == 13)
					{
						system("cls");
						board();
						other();
						system("cls");
						start();
						board();
					} 
					clear(35, 36, 8, 8);
					clear(35, 36, 18, 18);
					gotoxy(35,13);
					printf("<-");
				}
				else if(mode == 2)
				{
					if(enter == 13)
					{	
						system("cls");
						board();
						color = setting(color);
						system("cls");
						start();
						board();
					} 
					clear(35, 36, 23, 23);
					clear(35, 36, 13, 13);
					gotoxy(35,18);
					printf("<-");
				}
				else if(mode == 3)
				{
					clear(35, 36, 18, 18);
					gotoxy(35,23);
					printf("<-");
					if(enter == 13)
					{
						keybd_event(VK_MENU,0,0,0);  //模擬按下ALT
						keybd_event(115,0,0,0);  //模擬按下F4 
						keybd_event(VK_MENU,0,KEYEVENTF_KEYUP,0);  //模擬放開ALT 
						keybd_event(115,0,KEYEVENTF_KEYUP,0);  //模擬放開F4
						return 0;
					} 				
				}
			break;
			case 1: //選擇人數 
				if(enter == down)
				{ 
					num_player = 2;
				}
				else if(enter == up)
				{ 
					num_player = 1;
				}
				if(num_player == 1)
				{
					clear(35, 36, 15,15);
					gotoxy(35,10);
					printf("<-");
					if(enter == 13)
					{
						step = 2;
						system("cls");
						board();
						rule(num_player);
					} 
				}
				else if(num_player == 2)
				{
					clear(35, 36, 10, 10);
					gotoxy(35,15);
					printf("<-");
					if(enter == 13)
					{
						step = 2;
						system("cls");
						board();
						rule(num_player);
					} 
				}
			break;
			case 2: //顯示規則 
				if(enter == 13)
				{
					step = 3;
					system("cls");
				}
			
			break;
			case 3://開始遊戲 
				game(num_player);
				system("cls");
				step = 4;
			break;
			case 4://變數復歸 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 + background * 225);
				final(num_player);
				int temp;
				gameover = 0;
				if(num_player == 1)//如果是單人模式,儲存成績 
				{
					grade[10] = g; 
					for(i = 0;i < 11;i++)
					{
						for(j = 11-(i+1);j >= 0;j--)
						{
							if(grade[j] < grade[j + 1])
							{
								temp = grade[j];
								grade[j] = grade[j + 1];
								grade[j + 1] = temp;
							}
						}
					}
				}
				gameover2 = 0;
				g1 = 0;
				g = 0;
				for(i = 0;i < 4;i++)
				{
					for(j = 0;j < 4;j++)
					{
						one_xy[i][j] = 0;
						two_xy[i][j] = 0;
					}
				}
				num_player = 1;
				mode = 0;
				step = 0;
				lock = 1;
				lock2 = 1;
				enter = '0';
				system("cls");
				goto restart;
			break;
			default:
			break;
		}
		if(step == 0 || step == 1 || step == 2)
		{
			enter = getch();
		}
	}
	return 0;
}
