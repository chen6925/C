#include <stdio.h>
#include <windows.h> 
#include <stdlib.h>
#include <time.h> 
char up = 'w',down = 's',left = 'a',right = 'd',up_2 = 'H',down_2 = 'P',left_2 = 'K',right_2 = 'M';
int num_people = 0,snack_xy[2][60] = {0},direction = 3,direction_2 = 4,snack2_xy[2][60] = {0},food_xy[2] = {30,15},length = 3,length_2 = 3,gameover = 0,background = 0,grade[11] = {0},g = 0,hard = 0,speed = 100,x_xy[100][2]={0},set[2],coin = 1500,skin_have[4],skin = 0;
void full_screen()  //顯示全螢幕 
{
	keybd_event(VK_MENU,0x38,0,0);  //模擬按下alt 
    keybd_event(VK_RETURN,0x1c,0,0); 	//模擬按下enter 
    keybd_event(VK_MENU,0xb8,KEYEVENTF_KEYUP,0); //模擬放開alt 
    keybd_event(VK_RETURN,0x9c,KEYEVENTF_KEYUP,0); //模擬放開enter 
}

int gotoxy(int x,int y) //移動游標 
{
	COORD coord; //創建一個coord結構 
	coord.X = x; //將x值存入 
	coord.Y = y; // 將y值存入 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord); //將游標改到新座標 
}

void board_3()  //分數板框框建立 
{
	int i = 0,j = 0;
	for(i = 5;i <= 25;i++)
	{
		for(j = 80;j <= 120;j++)
		{
			if(i == 5 || i == 25)
			{
				gotoxy(j,i);
				printf("-");
			}
			else if(i > 5 && i < 25)
			{ 
				if(j == 80 || j == 120)
				{
					gotoxy(j,i);
					printf("|");
				}
			}
		}
		printf("\n");
	}
}

void board_2() // 遊戲框框建立 
{
	int i = 0,j = 0;
	for(i = 0;i <= 30;i++)
	{
		for(j = 0;j <= 60;j++)
		{
			if(i == 0 || i == 30)
			{
				gotoxy(j,i);
				printf("-");
			}
			else if(i > 0 && i < 30)
			{ 
				if(j == 0 || j == 60)
				{
					gotoxy(j,i);
					printf("|");
				}
			}
		}
		printf("\n");
	}
}

void board() //主畫面框框建立 
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

void start() //起始畫面 
{
	board();
	gotoxy(25,5);
	printf("|歡迎來到貪吃蛇遊戲|"); 
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

void staff()  //製作人員畫面 
{
	char enter;
	board();
	gotoxy(25,5);
	printf("|製作人員|"); 
	gotoxy(25,8);
	printf("1.B11207018 陳柏霖");
	gotoxy(25,13);
	printf("2.B11207016 李家興");
	gotoxy(45,28);
	printf("[使用esc返回其他選項]");
	while(1)
	{
	 	enter = getch();
		if(enter == 27) //如果按esc回到其他選項 
		{
			break;
		}
	}
}

void other_board()   //其他選項畫面 
{
	board();
	gotoxy(25,5);
	printf("|其他選項|"); 
	gotoxy(25,8);
	printf("商店:");
	gotoxy(25,13);
	printf("排行榜:");
	gotoxy(25,18);
	printf("製作人員:");
	gotoxy(45,27);
	printf("[按下esc返回主畫面]"); 
	gotoxy(45,28);
	printf("[按下enter確認模式]"); 
	gotoxy(45,29);
	printf("[使用%c,%c控制選擇模式]",up,down); 
}

void grade_board()   //排行榜畫面 
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
		if(enter == 27)//如果按esc回到其他選項 
		{
			break;
		}
	}
}

void shop() //商店畫面 
{
	board();
	char enter;
	int mode = 0;
	while(1)
	{

		if(enter == down)   //控制模式上下移動 
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
			clear(45,46,13,13);
			gotoxy(50,8);
			printf("<-");
			if(enter == 13)  //按enter選擇皮膚 
			{
				skin = 0;
			} 
		}
		else if(mode == 1)
		{
			if(enter == 13)  //按enter選擇皮膚 
			{
				if(skin_have[1] == 1)
				{
					skin = 1;
				}
				else if(skin_have[1] == 0 && coin >= 100)  //如果沒有此皮膚需要先消耗金幣購買 
				{
					skin_have[1] = 1;
					skin = 1;
					coin = coin - 100;
				} 
			} 
			clear(50, 51, 8, 8);
			clear(50, 51, 18, 18);
			gotoxy(45,13);
			printf("<-");
		}
		else if(mode == 2)
		{
			if(enter == 13)//按enter選擇皮膚 
			{	
				if(skin_have[2] == 1)
				{
					skin = 2;
				}
				else if(skin_have[2] == 0 && coin >= 500)//如果沒有此皮膚需要先消耗金幣購買
				{
					skin_have[2] = 1;
					skin = 2;
					coin = coin - 500;
				} 
			} 
			clear(45,46,13,13);
			clear(46,47,23,23);
			gotoxy(50,18);
			printf("<-");
		}
		else if(mode == 3)
		{
				
			if(enter == 13) //按enter選擇皮膚  
			{	
				if(skin_have[3] == 1)
				{
					skin = 3;
				}
				else if(skin_have[3] == 0 && coin >= 1000)//如果沒有此皮膚需要先消耗金幣購買
				{
					skin_have[3] = 1;
					skin = 3;
					coin = coin - 1000;
				} 
			} 
			clear(50, 51, 18, 18);
			gotoxy(46,23);
			printf("<-");
		}
		if(enter == 27) //按esc回到其他選項 
		{
			break;	
		}
		gotoxy(25,8);
		if(skin == 0)
		{ 
			printf("1.■ ■ ■ ■ ■ (使用中)");
		}
		else
		{
			printf("1.■ ■ ■ ■ ■ (已擁有)");
		}
		gotoxy(25,13);
		if(skin_have[1] == 0)
		{
			printf("2.O O O O O (100塊)");
		}
		else if(skin == 1)
		{
			printf("2.O O O O O (使用中)");
		}
		else if(skin_have[1] == 1)
		{
			printf("2.O O O O O (已擁有)");	
		}
		gotoxy(25,18);
		if(skin_have[2] == 0)
		{
			printf("3.☆ ☆ ☆ ☆ ☆(500塊)");
		}
		else if(skin == 2)
		{
			printf("3.☆ ☆ ☆ ☆ ☆ (使用中)");
		}
		else if(skin_have[2] == 1)
		{
			printf("3.☆ ☆ ☆ ☆ ☆ (已擁有)");
		}
		gotoxy(25,23);
		if(skin_have[3] == 0)
		{
			printf("4.# $ % ^ @ * (1000塊)");
		}
		else if(skin == 3)
		{
			printf("4.# $ % ^ @ * (使用中)");		
		}
		else if(skin_have[3] == 1)
		{
			printf("4.# $ % ^ @ * (已擁有)");	
		}
		gotoxy(45,27);
		printf("[按下esc返回主畫面]"); 
		gotoxy(45,28);
		printf("[按下enter購買]"); 
		gotoxy(45,29);
		printf("[使用%c,%c控制選擇]",up,down); 		
		gotoxy(25,5);
		printf("|商店| 金幣:%d  ",coin); 
		enter = getch();
	}
}

void other()  //其他選項畫面 
{
	char enter;
	other_board();
	int mode = 0;
	while(1){
		if(enter == down)  //控制模式上下 
		{ 
			if(mode != 2)
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
				shop();
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
				grade_board();
				system("cls");
				other_board();
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
				staff();
				system("cls");
				other_board();
			} 
			clear(35, 36, 13, 13);
			gotoxy(35,18);
			printf("<-");
		}
		if(enter == 27)
		{
			break;	
		}
		enter = getch();
	}
}

void over()  //遊戲結束判斷 
{
	int i,j,num;
	if(snack_xy[0][0] >= 60 || snack_xy[0][0] <= 0 || snack_xy[1][0] == 0 || snack_xy[1][0] == 30) //如果碰到邊界就結束 
	{
		gameover = 1;
	}
	for(i = length - 1;i > 0;i--)
	{
		if(snack_xy[0][0] == snack_xy[0][i] && snack_xy[1][0] == snack_xy[1][i]) //如果碰到身體就結束 
		{
			gameover = 1;
		}
	}
	if(hard == 3)
	{
		num = 10;	
	}
	else if(hard == 4)
	{
		num = set[1];
	}
	for(i = 0;i < num;i++)  //如果碰到障礙物就結束 
	{
		if((x_xy[i][0] == snack_xy[0][0]) && (x_xy[i][1] == snack_xy[1][0]))
		{
			gameover = 1;
		}
		if(num_people == 1) 	//如果為雙人模式,需要對第二隻蛇做一樣的判斷 
		{
			if((x_xy[i][0] == snack2_xy[0][0]) && (x_xy[i][1] == snack2_xy[1][0])) 
			{
				if(gameover == 0)
				{
					gameover = 2;
				}	
				else if(gameover == 1)
				{
					gameover =3;
				} 
				
			}
		}
	}
	if(num_people == 1)
	{
		if(snack2_xy[0][0] >= 60 || snack2_xy[0][0] <= 0 || snack2_xy[1][0] == 0 || snack2_xy[1][0] == 30)
		{
			gameover = 2;
		}
		for(i = length_2 - 1;i > 0;i--)
		{
			if(snack2_xy[0][0] == snack2_xy[0][i] && snack2_xy[1][0] == snack2_xy[1][i])
			{
				gameover = 2;
			}
		}
		for(i = length ;i > 1;i--)
		{
			if(snack2_xy[0][0] == snack_xy[0][i] && snack2_xy[1][0] == snack_xy[1][i])
			{
				gameover = 2;
			}
			else if(snack_xy[0][0] == snack2_xy[0][i] && snack_xy[1][0] == snack2_xy[1][i])
			{
				gameover = 1;
			}
		}
		if((snack_xy[0][0] == snack2_xy[0][0] && snack_xy[1][0] == snack2_xy[1][0] )|| (gameover == 2 && (snack_xy[0][0] >= 60 || snack_xy[0][0] <= 0 || snack_xy[1][0] == 0 || snack_xy[1][0] == 30)))
		{
			gameover = 3; 
		}
	}	
	
}

void x(int num)  //障礙物 
{
	int i,j,k,a;
	if(num > 100)  //最多100個障礙物 
	{
		num = 100;
	}
	for(j = 0;j < num;j++)  //隨機生成障礙物的位置 
	{
		for(i = 0;i < 2;i++)
		{
			do
			{
				if(num_people == 0)
				{
					if(i == 0)
					{
						x_xy[j][i] = (rand() % 24) * 2 + 10;
					}
					else
					{
						x_xy[j][i] = rand() % 29 + 1;
					}
				}
				else if(num_people == 1)
				{
					if(i == 0)
					{
						x_xy[j][i] = (rand() % 20)*2 + 10;
					}
					else
					{
						x_xy[j][i] = rand() % 29 + 1;
					}
				}
				a = 0;
			}
			while(a == 1);
		}	
		gotoxy(x_xy[j][0],x_xy[j][1]);
		printf("X");
	}
}

void game()  //遊戲部分 
{	
	char trash; 
	int i = 0;
	snack_xy[0][0] = 10;  //玩家一初始設置 
	snack_xy[0][1] = 8;
	snack_xy[0][2] = 6;
	snack_xy[1][0] = 7;
	snack_xy[1][1] = 7;
	snack_xy[1][2] = 7;
	if(num_people == 1)  //玩家二初始設置 
	{
		snack2_xy[0][0] = 50;
		snack2_xy[0][1] = 52;
		snack2_xy[0][2] = 54;
		snack2_xy[1][0] = 23;
		snack2_xy[1][1] = 23;
		snack2_xy[1][2] = 23;
		gotoxy(snack2_xy[0][0],snack2_xy[1][0]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12 + background * 240);  //設定字體為紅色 
		printf("■");
		gotoxy(snack2_xy[0][0],snack2_xy[1][0]);
		printf("■");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 + background * 225);  //設定字體為白色 
	}
	board_3();
	switch(hard)  //根據難度設定障礙物的數量 
	{
		case 3:
			x(10);
		break;
		case 4: 
			x(set[1]);
			speed = set[0];
		break;
		default:
		break;
	}
	for(i = 0;i < 2;i++)  //根據設定的皮膚顯示蛇的身體 
	{
		gotoxy(snack_xy[0][i],snack_xy[1][i]);
		if(skin == 0)
		{
			printf("■");
		}
		else if(skin == 1)
		{
			printf("O");
		}
		else if(skin == 2)
		{
			printf("☆");
		}
		else if(skin == 3)
		{
			printf("%c",rand()%94+33);
		}
	}
	gotoxy(30,15);
	printf("$");
	for(i = 3;i > 0;i--) //開始前先到數三秒 
	{
		gotoxy(85,15);
		printf("倒數:%d",i); 
		Sleep(1000);
		while(kbhit())   
		{
			trash = getch();
		}
	}
	while(gameover == 0) //如果沒有撞到東西就繼續 
	{
		Sleep(speed);  //速度設置 
		clear(85,91,15,15);
		if(num_people == 0)  //單人模式的計分板顯示 
		{
			gotoxy(85,10);
			printf("分數:%d",g); 
			gotoxy(85,13);
			printf("金幣:%d",coin); 
			gotoxy(85,16);
			printf("使用%c,%c,%c,%c控制",up,left,down,right); 
			gotoxy(85,19);
			if(grade[0] > g)
			{ 
				printf("歷史最高分:%d",grade[0]); 
			}
			else if(grade[0] <= g)
			{
				printf("歷史最高分:%d",g);
			}
		}
		else if(num_people == 1) //雙人模式的計分板顯示 
		{
			gotoxy(85,10);
			printf("白方使用%c,%c,%c,%c控制",up,left,down,right); 
			gotoxy(85,13);
			printf("紅方使用%c,%c,%c,%c控制",up_2,left_2,down_2,right_2); 
		}
		move();  //移動 
		over(hard);  //結束判斷 
	}
}

void food()  //食物設置 
{
	int i = 0,j = 0,a = 0;
	g += 100 * hard;  //分數++ 
	if(num_people == 0)
	{
		coin += 10 * hard;
	}
	for(i = 0;i < 2;i++) //隨機生成食物 
	{
		do
		{
			if(i == 0)
			{
				food_xy[i] = (rand() % 28)*2 + 2;
			}
			else
			{
				food_xy[i] = rand() % 29 + 1;
			}
			a = 0;
			for(j = length;j > 0;j--)
 			{
	 			if(food_xy[i] == snack_xy[i][j] )
	 			{
	 				a = 1;
	 			}
	 			if(num_people == 1)
	 			{
		 			if(food_xy[i] == snack2_xy[i][j] )
		 			{
		 				a = 1;
		 			}	
	 			}
	 		}
	 		for(j = 0;j < 100;j++)
			{
				if(food_xy[0] == x_xy[i][0] && food_xy[1] == x_xy[i][1])
				{
					a = 1; 
				}
			}
		}
		while(a == 1);
	}
	gotoxy(food_xy[0],food_xy[1]);
	printf("$");
}

void mode_choose()//難度選擇畫面 
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;

	int mode = 0;
	char enter;
	gotoxy(23,5);
	printf("|難度選擇|"); 
	gotoxy(23,8);
	printf("1.簡單");
	gotoxy(23,13);
	printf("2.普通");
	gotoxy(23,18);
	printf("3.困難");
	gotoxy(23,23);
	printf("4.自訂(速度 障礙數量)");
	gotoxy(45,28);
	printf("[使用enter選擇難度]");
	gotoxy(45,29);
	printf("[使用%c,%c控制選擇模式]",up,down); 
	while(1)
	{
		char input[100];
		if(enter == down)   //控制難度上下選擇 
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
				hard = 1;
				speed = 150;
				break;
			}
		}
		else if(mode == 1)
		{
			clear(35, 36, 8, 8);
			clear(35, 36, 18, 18);
			gotoxy(35,13);
			printf("<-");
			if(enter == 13)
			{
				hard = 2;
				speed = 100;
				break;
			}
		}
		else if(mode == 2)
		{
			clear(45, 46, 23, 23);
			clear(35, 36, 13, 13);
			gotoxy(35,18);
			printf("<-");
			if(enter == 13)
			{
				hard = 3;
				speed = 75;
				break;
			}
		}
		else if(mode == 3)
		{
			clear(35, 36, 18, 18);
			gotoxy(45,23);
			printf("<-");
			if(enter == 13)
			{
				gotoxy(45,23);
				while(1)
				{
					hard = 4;
					clear(45, 46, 23, 23);
					gotoxy(45,23);
					while(1)
					{
						set:
					    info.bVisible = TRUE;   //顯示游標 
						SetConsoleCursorInfo(handle, &info);
						if(fgets(input,100,stdin) != NULL)
						{
							if (sscanf(input,"%d%d",&set[0],&set[1]) == 2) //判斷是否輸入正整數 
							{
								if(set[0] <= 0 || set[1] <= 0)
								{
									gotoxy(45,23);
									printf("請輸入正整數"); 
									Sleep(2000);
									clear(45,55,23,23); 
									gotoxy(45,23);
									goto set;
								}
								break;	
							}
							else
							{
								gotoxy(45,23);
								printf("請輸入數字");
								Sleep(2000);
								clear(45,55,23,23); 
							}
							gotoxy(45,23);
						}
					}
					if(enter == 13)
					{
						info.bVisible = FALSE; //隱藏游標 
						SetConsoleCursorInfo(handle, &info);
						break;
					}
					enter = getch();
				}
				break;
			}				
		}
		enter = getch();
	}
}

int move() //蛇移動控制 
{
	int i = 0,j = 0; 
	char enter,enter_2;
	if(kbhit())  //防止雙人同時按下,所以我設置了兩個getch 
	{
		enter = getch();
	}
	if(kbhit())
	{
		enter_2 = getch();
	} 
	if((enter == up || enter_2 == up)&& direction != 2) //根據所按下的鍵設定前進方向 
	{
		direction = 1;
	}
	else if((enter == down || enter_2 == down) && direction != 1)
	{
		direction = 2;
	}
	else if((enter == right || enter_2 == right) && direction != 4)
	{
		direction = 3;
	}
	else if((enter == left || enter_2 == left) && direction != 3)
	{
		direction = 4;
	}
	if(num_people == 1)//玩家2控制 
	{
		if((enter == up_2 || enter_2 == up_2)&& direction_2 != 2)
		{
			direction_2 = 1;
		}
		else if((enter == down_2 || enter_2 == down_2) && direction_2 != 1)
		{
			direction_2 = 2;
		}
		else if((enter == right_2 || enter_2 == right_2) && direction_2 != 4)
		{
			direction_2 = 3;
		}
		else if((enter == left_2 || enter_2 == left_2) && direction_2 != 3)
		{
			direction_2 = 4;
		}
		for(i = length_2 - 1;i > 0;i--)
		{
			for(j = 0;j < 2;j++)
			{
				snack2_xy[j][i] = snack2_xy[j][i-1];	
			} 
		}
		switch(direction_2) //增加蛇的長度 
		{
			case 1:
				snack2_xy[1][0] = snack2_xy[1][0] - 1;	
			break;
			case 2:
				snack2_xy[1][0] = snack2_xy[1][0] + 1;
			break;
			case 3:
				snack2_xy[0][0] = snack2_xy[0][0] + 2;
			break;
			case 4:
				snack2_xy[0][0] = snack2_xy[0][0] - 2;
			break;
			default:
			break;
		}
		if(food_xy[0] == snack2_xy[0][0] && food_xy[1] == snack2_xy[1][0]) //判斷是否吃到食物 
		{
			food();
			length_2++;
		}
		else
		{
			gotoxy(snack2_xy[0][length_2 - 1],snack2_xy[1][length_2 - 1]);
			printf("  ");
		}
		gotoxy(snack2_xy[0][0],snack2_xy[1][0]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12 + background * 240);//設定顏色為紅色 
		printf("■");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 + background * 225);
	}
	for(i = length - 1;i > 0;i--)
	{
		for(j = 0;j < 2;j++)
		{
			snack_xy[j][i] = snack_xy[j][i-1];	
		} 
	}
	switch(direction)  //根據前進方向增加蛇的長度 
	{
		case 1:
			snack_xy[1][0] = snack_xy[1][0] - 1;	
		break;
		case 2:
			snack_xy[1][0] = snack_xy[1][0] + 1;
		break;
		case 3:
			snack_xy[0][0] = snack_xy[0][0] + 2;
		break;
		case 4:
			snack_xy[0][0] = snack_xy[0][0] - 2;
		break;
		default:
		break;
	}
	if(food_xy[0] == snack_xy[0][0] && food_xy[1] == snack_xy[1][0])
	{
		food();
		length++;
	}
	else
	{
		gotoxy(snack_xy[0][length - 1],snack_xy[1][length - 1]);
		printf("  ");
	}
	gotoxy(snack_xy[0][0],snack_xy[1][0]);
	if(skin == 0)
	{
		printf("■");
	}
	else if(skin == 1)
	{
		printf("O");
	}
	else if(skin == 2)
	{
		printf("☆");
	}
	else if(skin == 3)
	{
		printf("%c",rand()%94+33);
	}	
}

int setting(int light)  //遊戲設置 
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
		if(enter == 27)//如果按下esc回主畫面 
		{
			break;
		}
		else if(enter == down && step < 8)  //控制箭頭上下 
		{
			step = step + 1;
		}
		else if(enter == up && step > 0)
		{
			step = step - 1;
		}
		if(step == 0)// 背景更改 
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
				system("color 0F");
			}
			else if(light == 1)
			{
				gotoxy(39,4);
				printf("X");
				system("color F0");		
			} 
		} 
		else if(step == 1) //設定按鍵 
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

void rule()  //規則畫面 
{
	gotoxy(25,5);
	printf("|規則|"); 
	if(num_people == 0)
	{ 
		gotoxy(25,8);
		printf("1.使用%c %c %c %c控制",up,right,down,left);
		gotoxy(25,13);
		printf("2.撞到牆壁或是自己結束遊戲");
		gotoxy(25,18);
		printf("3.吃到$身體會變長");
		gotoxy(25,23);
		printf("4.遊戲會在倒數3秒後開始"); 
		gotoxy(41,29);
		printf("[按下enter前往下一步]"); 
	}
	else if(num_people == 1) 
	{
		gotoxy(25,8);
		printf("1.白色使用%c %c %c %c控制",up,right,down,left);
		gotoxy(25,12);
		printf("2.紅色使用%c %c %c %c控制",up_2,right_2,down_2,left_2);
		gotoxy(25,16);
		printf("3.撞到牆壁或是自己結束遊戲");
		gotoxy(25,20);
		printf("4.吃到$身體會變長");
		gotoxy(25,24);
		printf("5.遊戲會在倒數3秒後開始"); 
		gotoxy(41,29);
		printf("[按下enter前往下一步]"); 	
	}
}

void final() //遊戲結束畫面 
{
	board();
	char enter;
	gotoxy(47,5);
	printf("|遊戲結束|");
	gotoxy(41,29);
	printf("[按下enter回到主畫面]"); 
	if(num_people == 0)
	{
		gotoxy(47,15);
		printf("分數:%d",g); 
	}
	else if(num_people == 1)
	{
		gotoxy(47,15);
		if(gameover == 1)
		{
			printf("紅方獲勝"); 
		} 
		else if(gameover == 2)
		{
			printf("白方獲勝"); 
		} 
		else if(gameover == 3)
		{
			printf("平手"); 
		}
	}
	while(1)
	{
		enter = getch();
		if(enter == 13)
		{
			system("cls");
			break;
		}
	}
}

int main()
{
	srand(time(NULL)); //設定隨機種子 
	int step = 0,mode = 0,color = 0,people = 0,i,j;
	char enter;
	full_screen();//全螢幕 
	Sleep(500); 
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(handle, &info);
    info.bVisible = FALSE;
    SetConsoleCursorInfo(handle, &info);
	restart:
	start();
	board();
	while(1)
	{
		if(color == 0)
		{
			system("color 0F");
			background = 0;
		}
		else 
		{
			system("color F0");
			background = 1;
		}
		switch(step)
		{
			case 0: //主畫面顯示 
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
						gotoxy(45,28);
						printf("[按下enter確認模式]"); 
						gotoxy(45,29);
						printf("[使用%c,%c控制選擇模式]",up,down); 
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
			case 1://遊戲人數設定 
				if(enter == down)
				{ 
					num_people = 1;
				}
				else if(enter == up)
				{ 
					num_people = 0;
				}
				if(num_people == 0)
				{
					clear(35, 36, 15,15);
					gotoxy(35,10);
					printf("<-");
					if(enter == 13)
					{
						step = 2;
						system("cls");
						board();
						rule();
					} 
				}
				else if(num_people == 1)
				{
					clear(35, 36, 10, 10);
					gotoxy(35,15);
					printf("<-");
					if(enter == 13)
					{
						step = 2;
						system("cls");
						board();
						rule();
					} 
				}
			break;
			case 2:
				if(enter == 13)
				{
					step = 3;
				}
			
			break;
			case 3:
				system("cls");
				board();
				mode_choose();
				step = 4;
				system("cls");
			break;
			case 4:
				board_2();
				game();
				system("cls");
				step = 5;
			break;
			case 5:  //變數復歸 
				final();
				int temp;
				mode = 0;
				enter = 0;
				length = 3;
				length_2 = 3;
				gameover = 0;
				direction = 3;
				direction_2 = 4;
				food_xy[0] = 30;
				food_xy[1] = 15;
				if(num_people == 0)  //單人模式的時候排序分數 
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
				num_people = 0;
				g = 0;
				step = 0;
				hard = 0;
				speed = 100;
				for(i = 0;i < 100;i++)
				{
					for(j = 0;j < 2;j++)
					{
						x_xy[i][j] = 0;
					}
				}
				goto restart;
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
