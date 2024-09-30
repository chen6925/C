#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

char chest[30][30],res[3];
char horizontal,vertical;
int chest_O,chest_X,winner;
int i=0,a=0,k=0,b=0;

int step=0,gameover=0,restart=0;
	
void full_screen()  //模擬按下alt+enter,顯示全螢幕 
{
	keybd_event(VK_MENU,0,0,0);
    keybd_event(VK_RETURN,0,0,0);
    keybd_event(VK_MENU,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);
}	

int checkerboard()    	//初始棋盤構建 
{
	for(i=0;i<15;i++)
	{
		for(a=0;a<15;a++)
		{
			chest[i][a]='+';
		}
	}
}

int over()				//遊戲結束,勝利者顯示 
{
	if(chest_O>=5||chest_X>=5)
	{
		gameover=1;
		if(chest_O>=5)
			winner=1;
		if(chest_X>=5)
			winner=2;
	}
} 

int check_x() //判斷x軸方向是否有五子連線 
{
	for(i=0;i<15;i++)
	{
		for(a=0;a<15;a++)
		{	
			over();
			if(chest[i][a]=='O')
			{
				chest_O++;
				chest_X=0;
			}
			else if(chest[i][a]=='X')
			{
				chest_X++;
				chest_O=0;
			}
			else if(chest[i][a]=='+')
			{
				chest_X=0;
				chest_O=0;
			}
		}		
	}
	chest_X=0;
	chest_O=0;	
}

int check_y() //判斷y軸方向是否有五子連線  
{
	for(i=0;i<15;i++)
	{
		for(a=0;a<15;a++)
		{	
			over();
			if(chest[a][i]=='O')
			{
				chest_O++;
				chest_X=0;
			}
			else if(chest[a][i]=='X')
			{
				chest_X++;
				chest_O=0;
			}
			else if(chest[a][i]=='+')
			{
				chest_X=0;
				chest_O=0;
			}
		}
	}
	chest_X=0;
	chest_O=0;	
}

check_yx() //判斷斜線方向是否有五子連線 
{
	for(i=0;i<15;i++)
	{
		for(a=0;a<15;a++)
		{	
			for(b=0;b<5;b++)
			{
				over();
				if(chest[a+b][i+b]=='O')
				{
					chest_O++;
					chest_X=0;
				}
				else if(chest[a+b][i+b]=='X')
				{
					chest_X++;
					chest_O=0;
				}
				else
				{
					chest_X=0;
					chest_O=0;
				}
			}
		}
	}
	chest_X=0;
	chest_O=0;
} 

int check_xy() //判斷反斜線方向是否有五子連線  
{
	for(i=0;i<15;i++)
	{
		for(a=0;a<15;a++)
		{	
			for(b=0;b<5;b++)
			{
				if(chest[i+b][a-b]=='O')
				{
					chest_O++;
					chest_X=0;
				}
				else if(chest[i+b][a-b]=='X')
				{
					chest_X++;
					chest_O=0;
				}
				else
				{
					chest_X=0;
					chest_O=0;
				}
				over();
			}
		}
	}
	chest_X=0;
	chest_O=0;
} 

int win() //遊戲結束條件判斷 
{
	int space=0;
	check_x(); //判斷x方向是否有五子連線 
	check_y(); //判斷y方向是否有五子連線 
	check_xy(); //判斷斜線方向是否有五子連線 
	check_yx(); //判斷反斜線方向是否有五子連線 
	for(i=0;i<15;i++)
	{
		for(a=0;a<15;a++)
		{
			if(chest[a][i]!='+')
				space=space+1;
		}
	}
	if(space>=255) //如果沒有空間了,就平手 
	{
		gameover=1;
		winner=3;
	}
	else
	{
		space=0;
	}
}

enter()  //輸入 
{
	char word=65;
	printf("  A   B   C   D   E   F   G   H   I   J   K   L   M   N   O\n\n");//棋盤第一行座標  
	for(i=0;i<15;i++) // 下棋 
	{
		printf("%c%",word+i);
		printf(" ");
		for(a=0;a<15;a++)
		{
			printf("%c   ",chest[i][a]);
		}
		printf("\n\n");
	}
	if(step==0)																						//輸入座標 
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);	//顯示藍字 
		printf("O請輸入座標:"); 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);  //顯示紅字 
		printf("X請輸入座標:"); 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);  
	}
	scanf(" %c %c",&vertical,&horizontal);
	fflush(stdin);
	if (chest[horizontal-65][vertical-65] !='+')													//error判斷 
	{
		if((chest[horizontal-65][vertical-65] =='O')||(chest[horizontal-65][vertical-65] =='X'))	//有error 
		{
			printf("\nError:不可輸入重複座標\n\n");
			system("pause");
		}
		else
		{	
			printf("\nError:沒有此座標\n\n");
			system("pause");
		}
	} 
	else 																							//沒有error 
	{
		if (step==0)
		{
			chest[horizontal-65][vertical-65]='O';
			step=1;
		}
		else if(step==1)
		{
			chest[horizontal-65][vertical-65]='X';
			step=0;
		} 
	}
 	system("cls");
} 

int start()//開始遊戲復歸 
{
	chest_X=0;
	chest_O=0;
	step=0;
	gameover=0;
	winner=0;
	checkerboard();
	system("cls");
	fflush(stdin);
} 

int main()//遊戲主程式 
{
	full_screen();
	printf("歡迎來到五子棋遊戲\n\n程式設計:陳柏霖\n程式測試:李家興\n\n");  //遊戲開始畫面 
	system("pause");
	system("cls");

	printf("遊戲規則如下:\n\n");										   //遊戲規則介紹 
	printf("1.輸入方式:請輸入大寫座標,先X軸在Y軸 例如:AB \n");
	printf("2.遊玩人數:2人\n"); 
	printf("3.如果輸入超過兩個字,將只會讀取前面兩位\n\n"); 
	system("pause");
	system("cls");
	
	while(restart!=1)													  //遊戲開始 
	{
		start();
		while(gameover!=1)
		{
			win();
			if(gameover!=1)
				enter();
		}
		if (winner==1)
		{
			printf("恭喜O獲得勝利\n\n"); 
		}
		else if(winner==2)
		{
			printf("恭喜X獲得勝利\n\n"); 
		}
		else if(winner==3)
		{
			printf("平手\n\n"); 
		}
		while(1)
		{
			printf("是否再來一局YES/NOT:"); //是否再來一局 
			scanf("%c%c%c",&res[0],&res[1],&res[2]);
			if(res[0]=='Y'&&res[1]=='E'&&res[2]=='S')
			{	
				restart=0;
				fflush(stdin);
				break;
			}
			else if(res[0]=='N'&&res[1]=='O'&&res[2]=='T')
			{ 
				restart=1;
				break;
			}
			else
			{
				printf("輸入格式錯誤\n");
				fflush(stdin);
			}
		}
	}
}

