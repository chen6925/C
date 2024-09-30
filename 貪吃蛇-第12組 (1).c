#include <stdio.h>
#include <windows.h> 
#include <stdlib.h>
#include <time.h> 
char up = 'w',down = 's',left = 'a',right = 'd',up_2 = 'H',down_2 = 'P',left_2 = 'K',right_2 = 'M';
int num_people = 0,snack_xy[2][60] = {0},direction = 3,direction_2 = 4,snack2_xy[2][60] = {0},food_xy[2] = {30,15},length = 3,length_2 = 3,gameover = 0,background = 0,grade[11] = {0},g = 0,hard = 0,speed = 100,x_xy[100][2]={0},set[2],coin = 1500,skin_have[4],skin = 0;
void full_screen()  //��ܥ��ù� 
{
	keybd_event(VK_MENU,0x38,0,0);  //�������Ualt 
    keybd_event(VK_RETURN,0x1c,0,0); 	//�������Uenter 
    keybd_event(VK_MENU,0xb8,KEYEVENTF_KEYUP,0); //������}alt 
    keybd_event(VK_RETURN,0x9c,KEYEVENTF_KEYUP,0); //������}enter 
}

int gotoxy(int x,int y) //���ʴ�� 
{
	COORD coord; //�Ыؤ@��coord���c 
	coord.X = x; //�Nx�Ȧs�J 
	coord.Y = y; // �Ny�Ȧs�J 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord); //�N��Ч��s�y�� 
}

void board_3()  //���ƪO�خثإ� 
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

void board_2() // �C���خثإ� 
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

void board() //�D�e���خثإ� 
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

void start() //�_�l�e�� 
{
	board();
	gotoxy(25,5);
	printf("|�w��Ө�g�Y�D�C��|"); 
	gotoxy(25,8);
	printf("�}�l�C��:");
	gotoxy(25,13);
	printf("��L�ﶵ:");
	gotoxy(25,18);
	printf("�C���]�w:");
	gotoxy(25,23);
	printf("�h�X�C��:");
	gotoxy(45,28);
	printf("[���Uenter�T�{�Ҧ�]"); 
	gotoxy(45,29);
	printf("[�ϥ�%c,%c�����ܼҦ�]",up,down); 
}

void clear(int x1,int x2,int y1,int y2) //�M���y�Ф���ܪ��F�� 
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

void staff()  //�s�@�H���e�� 
{
	char enter;
	board();
	gotoxy(25,5);
	printf("|�s�@�H��|"); 
	gotoxy(25,8);
	printf("1.B11207018 ���f�M");
	gotoxy(25,13);
	printf("2.B11207016 ���a��");
	gotoxy(45,28);
	printf("[�ϥ�esc��^��L�ﶵ]");
	while(1)
	{
	 	enter = getch();
		if(enter == 27) //�p�G��esc�^���L�ﶵ 
		{
			break;
		}
	}
}

void other_board()   //��L�ﶵ�e�� 
{
	board();
	gotoxy(25,5);
	printf("|��L�ﶵ|"); 
	gotoxy(25,8);
	printf("�ө�:");
	gotoxy(25,13);
	printf("�Ʀ�]:");
	gotoxy(25,18);
	printf("�s�@�H��:");
	gotoxy(45,27);
	printf("[���Uesc��^�D�e��]"); 
	gotoxy(45,28);
	printf("[���Uenter�T�{�Ҧ�]"); 
	gotoxy(45,29);
	printf("[�ϥ�%c,%c�����ܼҦ�]",up,down); 
}

void grade_board()   //�Ʀ�]�e�� 
{ 
	int i = 0;
	char enter;
	board();
	gotoxy(25,5);
	printf("|�Ʀ�]|"); 
	for(i = 0;i < 10;i++)
	{
		gotoxy(25,5+2*(i+1));
		printf("No.%d:%d",i+1,grade[i]);	
	}
	gotoxy(45,29);
	printf("[���Uesc��^�D�e��]"); 
	while(1)
	{
		enter = getch();
		if(enter == 27)//�p�G��esc�^���L�ﶵ 
		{
			break;
		}
	}
}

void shop() //�ө��e�� 
{
	board();
	char enter;
	int mode = 0;
	while(1)
	{

		if(enter == down)   //����Ҧ��W�U���� 
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
			if(enter == 13)  //��enter��ܥֽ� 
			{
				skin = 0;
			} 
		}
		else if(mode == 1)
		{
			if(enter == 13)  //��enter��ܥֽ� 
			{
				if(skin_have[1] == 1)
				{
					skin = 1;
				}
				else if(skin_have[1] == 0 && coin >= 100)  //�p�G�S�����ֽ��ݭn�����Ӫ����ʶR 
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
			if(enter == 13)//��enter��ܥֽ� 
			{	
				if(skin_have[2] == 1)
				{
					skin = 2;
				}
				else if(skin_have[2] == 0 && coin >= 500)//�p�G�S�����ֽ��ݭn�����Ӫ����ʶR
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
				
			if(enter == 13) //��enter��ܥֽ�  
			{	
				if(skin_have[3] == 1)
				{
					skin = 3;
				}
				else if(skin_have[3] == 0 && coin >= 1000)//�p�G�S�����ֽ��ݭn�����Ӫ����ʶR
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
		if(enter == 27) //��esc�^���L�ﶵ 
		{
			break;	
		}
		gotoxy(25,8);
		if(skin == 0)
		{ 
			printf("1.�� �� �� �� �� (�ϥΤ�)");
		}
		else
		{
			printf("1.�� �� �� �� �� (�w�֦�)");
		}
		gotoxy(25,13);
		if(skin_have[1] == 0)
		{
			printf("2.O O O O O (100��)");
		}
		else if(skin == 1)
		{
			printf("2.O O O O O (�ϥΤ�)");
		}
		else if(skin_have[1] == 1)
		{
			printf("2.O O O O O (�w�֦�)");	
		}
		gotoxy(25,18);
		if(skin_have[2] == 0)
		{
			printf("3.�� �� �� �� ��(500��)");
		}
		else if(skin == 2)
		{
			printf("3.�� �� �� �� �� (�ϥΤ�)");
		}
		else if(skin_have[2] == 1)
		{
			printf("3.�� �� �� �� �� (�w�֦�)");
		}
		gotoxy(25,23);
		if(skin_have[3] == 0)
		{
			printf("4.# $ % ^ @ * (1000��)");
		}
		else if(skin == 3)
		{
			printf("4.# $ % ^ @ * (�ϥΤ�)");		
		}
		else if(skin_have[3] == 1)
		{
			printf("4.# $ % ^ @ * (�w�֦�)");	
		}
		gotoxy(45,27);
		printf("[���Uesc��^�D�e��]"); 
		gotoxy(45,28);
		printf("[���Uenter�ʶR]"); 
		gotoxy(45,29);
		printf("[�ϥ�%c,%c������]",up,down); 		
		gotoxy(25,5);
		printf("|�ө�| ����:%d  ",coin); 
		enter = getch();
	}
}

void other()  //��L�ﶵ�e�� 
{
	char enter;
	other_board();
	int mode = 0;
	while(1){
		if(enter == down)  //����Ҧ��W�U 
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

void over()  //�C�������P�_ 
{
	int i,j,num;
	if(snack_xy[0][0] >= 60 || snack_xy[0][0] <= 0 || snack_xy[1][0] == 0 || snack_xy[1][0] == 30) //�p�G�I����ɴN���� 
	{
		gameover = 1;
	}
	for(i = length - 1;i > 0;i--)
	{
		if(snack_xy[0][0] == snack_xy[0][i] && snack_xy[1][0] == snack_xy[1][i]) //�p�G�I�쨭��N���� 
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
	for(i = 0;i < num;i++)  //�p�G�I���ê���N���� 
	{
		if((x_xy[i][0] == snack_xy[0][0]) && (x_xy[i][1] == snack_xy[1][0]))
		{
			gameover = 1;
		}
		if(num_people == 1) 	//�p�G�����H�Ҧ�,�ݭn��ĤG���D���@�˪��P�_ 
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

void x(int num)  //��ê�� 
{
	int i,j,k,a;
	if(num > 100)  //�̦h100�ӻ�ê�� 
	{
		num = 100;
	}
	for(j = 0;j < num;j++)  //�H���ͦ���ê������m 
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

void game()  //�C������ 
{	
	char trash; 
	int i = 0;
	snack_xy[0][0] = 10;  //���a�@��l�]�m 
	snack_xy[0][1] = 8;
	snack_xy[0][2] = 6;
	snack_xy[1][0] = 7;
	snack_xy[1][1] = 7;
	snack_xy[1][2] = 7;
	if(num_people == 1)  //���a�G��l�]�m 
	{
		snack2_xy[0][0] = 50;
		snack2_xy[0][1] = 52;
		snack2_xy[0][2] = 54;
		snack2_xy[1][0] = 23;
		snack2_xy[1][1] = 23;
		snack2_xy[1][2] = 23;
		gotoxy(snack2_xy[0][0],snack2_xy[1][0]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12 + background * 240);  //�]�w�r�鬰���� 
		printf("��");
		gotoxy(snack2_xy[0][0],snack2_xy[1][0]);
		printf("��");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 + background * 225);  //�]�w�r�鬰�զ� 
	}
	board_3();
	switch(hard)  //�ھ����׳]�w��ê�����ƶq 
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
	for(i = 0;i < 2;i++)  //�ھڳ]�w���ֽ���ܳD������ 
	{
		gotoxy(snack_xy[0][i],snack_xy[1][i]);
		if(skin == 0)
		{
			printf("��");
		}
		else if(skin == 1)
		{
			printf("O");
		}
		else if(skin == 2)
		{
			printf("��");
		}
		else if(skin == 3)
		{
			printf("%c",rand()%94+33);
		}
	}
	gotoxy(30,15);
	printf("$");
	for(i = 3;i > 0;i--) //�}�l�e����ƤT�� 
	{
		gotoxy(85,15);
		printf("�˼�:%d",i); 
		Sleep(1000);
		while(kbhit())   
		{
			trash = getch();
		}
	}
	while(gameover == 0) //�p�G�S������F��N�~�� 
	{
		Sleep(speed);  //�t�׳]�m 
		clear(85,91,15,15);
		if(num_people == 0)  //��H�Ҧ����p���O��� 
		{
			gotoxy(85,10);
			printf("����:%d",g); 
			gotoxy(85,13);
			printf("����:%d",coin); 
			gotoxy(85,16);
			printf("�ϥ�%c,%c,%c,%c����",up,left,down,right); 
			gotoxy(85,19);
			if(grade[0] > g)
			{ 
				printf("���v�̰���:%d",grade[0]); 
			}
			else if(grade[0] <= g)
			{
				printf("���v�̰���:%d",g);
			}
		}
		else if(num_people == 1) //���H�Ҧ����p���O��� 
		{
			gotoxy(85,10);
			printf("�դ�ϥ�%c,%c,%c,%c����",up,left,down,right); 
			gotoxy(85,13);
			printf("����ϥ�%c,%c,%c,%c����",up_2,left_2,down_2,right_2); 
		}
		move();  //���� 
		over(hard);  //�����P�_ 
	}
}

void food()  //�����]�m 
{
	int i = 0,j = 0,a = 0;
	g += 100 * hard;  //����++ 
	if(num_people == 0)
	{
		coin += 10 * hard;
	}
	for(i = 0;i < 2;i++) //�H���ͦ����� 
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

void mode_choose()//���׿�ܵe�� 
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;

	int mode = 0;
	char enter;
	gotoxy(23,5);
	printf("|���׿��|"); 
	gotoxy(23,8);
	printf("1.²��");
	gotoxy(23,13);
	printf("2.���q");
	gotoxy(23,18);
	printf("3.�x��");
	gotoxy(23,23);
	printf("4.�ۭq(�t�� ��ê�ƶq)");
	gotoxy(45,28);
	printf("[�ϥ�enter�������]");
	gotoxy(45,29);
	printf("[�ϥ�%c,%c�����ܼҦ�]",up,down); 
	while(1)
	{
		char input[100];
		if(enter == down)   //�������פW�U��� 
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
					    info.bVisible = TRUE;   //��ܴ�� 
						SetConsoleCursorInfo(handle, &info);
						if(fgets(input,100,stdin) != NULL)
						{
							if (sscanf(input,"%d%d",&set[0],&set[1]) == 2) //�P�_�O�_��J����� 
							{
								if(set[0] <= 0 || set[1] <= 0)
								{
									gotoxy(45,23);
									printf("�п�J�����"); 
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
								printf("�п�J�Ʀr");
								Sleep(2000);
								clear(45,55,23,23); 
							}
							gotoxy(45,23);
						}
					}
					if(enter == 13)
					{
						info.bVisible = FALSE; //���ô�� 
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

int move() //�D���ʱ��� 
{
	int i = 0,j = 0; 
	char enter,enter_2;
	if(kbhit())  //�������H�P�ɫ��U,�ҥH�ڳ]�m�F���getch 
	{
		enter = getch();
	}
	if(kbhit())
	{
		enter_2 = getch();
	} 
	if((enter == up || enter_2 == up)&& direction != 2) //�ھکҫ��U����]�w�e�i��V 
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
	if(num_people == 1)//���a2���� 
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
		switch(direction_2) //�W�[�D������ 
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
		if(food_xy[0] == snack2_xy[0][0] && food_xy[1] == snack2_xy[1][0]) //�P�_�O�_�Y�쭹�� 
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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12 + background * 240);//�]�w�C�⬰���� 
		printf("��");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 + background * 225);
	}
	for(i = length - 1;i > 0;i--)
	{
		for(j = 0;j < 2;j++)
		{
			snack_xy[j][i] = snack_xy[j][i-1];	
		} 
	}
	switch(direction)  //�ھګe�i��V�W�[�D������ 
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
		printf("��");
	}
	else if(skin == 1)
	{
		printf("O");
	}
	else if(skin == 2)
	{
		printf("��");
	}
	else if(skin == 3)
	{
		printf("%c",rand()%94+33);
	}	
}

int setting(int light)  //�C���]�m 
{
	int step = 0;
	char enter;
	gotoxy(30,4);
	printf("�]���Ҧ�: "); 
	gotoxy(30,7);
	printf("�������� (��enter����U�Q�n�ק諸��:a~z��A~Z) ");
	gotoxy(30,9);
	printf("�V�W����:%c",up); 
	gotoxy(30,11);
	printf("�V�U����:%c",down);
	gotoxy(30,13);
	printf("�V������:%c",left);
	gotoxy(30,15);
	printf("�V�k����:%c",right);
	gotoxy(30,17);
	printf("�V�W����__��:%c",up_2); 
	gotoxy(30,19);
	printf("�V�U����__��:%c",down_2);
	gotoxy(30,21);
	printf("�V������__��:%c",left_2);
	gotoxy(30,23);
	printf("�V�k����__��:%c",right_2);
	gotoxy(45,28);
	printf("[�ϥ�esc��^�D�e��]"); 
	gotoxy(45,29);
	printf("[�ϥ�%c,%c�����ܼҦ�]",up,down); 
	while(1)
	{
		if(enter == 27)//�p�G���Uesc�^�D�e�� 
		{
			break;
		}
		else if(enter == down && step < 8)  //����b�Y�W�U 
		{
			step = step + 1;
		}
		else if(enter == up && step > 0)
		{
			step = step - 1;
		}
		if(step == 0)// �I����� 
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
		else if(step == 1) //�]�w���� 
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
						printf("[�ϥ�%c,%c�����ܼҦ�]",up,down); 
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
						printf("[�ϥ�%c,%c�����ܼҦ�]",up,down); 
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
						printf("[�ϥ�%c,%c�����ܼҦ�]",up,down); 
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
						printf("[�ϥ�%c,%c�����ܼҦ�]",up,down); 
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
						printf("[�ϥ�%c,%c�����ܼҦ�]",up,down); 
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
						printf("[�ϥ�%c,%c�����ܼҦ�]",up,down); 
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
						printf("[�ϥ�%c,%c�����ܼҦ�]",up,down); 
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
						printf("[�ϥ�%c,%c�����ܼҦ�]",up,down); 
						break;
					}
				}
			}
		}
		enter = getch();
	}
	return light;
}

void rule()  //�W�h�e�� 
{
	gotoxy(25,5);
	printf("|�W�h|"); 
	if(num_people == 0)
	{ 
		gotoxy(25,8);
		printf("1.�ϥ�%c %c %c %c����",up,right,down,left);
		gotoxy(25,13);
		printf("2.��������άO�ۤv�����C��");
		gotoxy(25,18);
		printf("3.�Y��$����|�ܪ�");
		gotoxy(25,23);
		printf("4.�C���|�b�˼�3���}�l"); 
		gotoxy(41,29);
		printf("[���Uenter�e���U�@�B]"); 
	}
	else if(num_people == 1) 
	{
		gotoxy(25,8);
		printf("1.�զ�ϥ�%c %c %c %c����",up,right,down,left);
		gotoxy(25,12);
		printf("2.����ϥ�%c %c %c %c����",up_2,right_2,down_2,left_2);
		gotoxy(25,16);
		printf("3.��������άO�ۤv�����C��");
		gotoxy(25,20);
		printf("4.�Y��$����|�ܪ�");
		gotoxy(25,24);
		printf("5.�C���|�b�˼�3���}�l"); 
		gotoxy(41,29);
		printf("[���Uenter�e���U�@�B]"); 	
	}
}

void final() //�C�������e�� 
{
	board();
	char enter;
	gotoxy(47,5);
	printf("|�C������|");
	gotoxy(41,29);
	printf("[���Uenter�^��D�e��]"); 
	if(num_people == 0)
	{
		gotoxy(47,15);
		printf("����:%d",g); 
	}
	else if(num_people == 1)
	{
		gotoxy(47,15);
		if(gameover == 1)
		{
			printf("�������"); 
		} 
		else if(gameover == 2)
		{
			printf("�դ����"); 
		} 
		else if(gameover == 3)
		{
			printf("����"); 
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
	srand(time(NULL)); //�]�w�H���ؤl 
	int step = 0,mode = 0,color = 0,people = 0,i,j;
	char enter;
	full_screen();//���ù� 
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
			case 0: //�D�e����� 
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
						printf("1.��H�Ҧ�");
						gotoxy(25,15);
						printf("2.���H�Ҧ�"); 
						gotoxy(35,10);
						printf("<-");
						gotoxy(45,28);
						printf("[���Uenter�T�{�Ҧ�]"); 
						gotoxy(45,29);
						printf("[�ϥ�%c,%c�����ܼҦ�]",up,down); 
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
						keybd_event(VK_MENU,0,0,0);  //�������UALT
						keybd_event(115,0,0,0);  //�������UF4 
						keybd_event(VK_MENU,0,KEYEVENTF_KEYUP,0);  //������}ALT 
						keybd_event(115,0,KEYEVENTF_KEYUP,0);  //������}F4
						return 0;
					} 				
				}
			break;
			case 1://�C���H�Ƴ]�w 
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
			case 5:  //�ܼƴ_�k 
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
				if(num_people == 0)  //��H�Ҧ����ɭԱƧǤ��� 
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
