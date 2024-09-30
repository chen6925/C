#include <stdio.h>
#include <windows.h> 
#include <stdlib.h>
#include <time.h>  
#include <math.h>

char up = 'w',down = 's',left = 'a',right = 'd',up_2 = 'H',down_2 = 'P',left_2 = 'K',right_2 = 'M';
int no_space1,no_space2,one_xy[4][4] = {0},two_xy[4][4] = {0},grade[11] = {0},background = 0,gameover = 0,lock = 1,g = 0,lock2 = 1,g1 = 0,gameover2 = 0;

void first()  //��¦�]�m 

{	keybd_event(VK_MENU,0x38,0,0);  //�������Ualt 
    keybd_event(VK_RETURN,0x1c,0,0); 	//�������Uenter 
    keybd_event(VK_MENU,0xb8,KEYEVENTF_KEYUP,0); //������}alt 
    keybd_event(VK_RETURN,0x9c,KEYEVENTF_KEYUP,0); //������}enter 
    srand(time(NULL));
    Sleep(500);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); 
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(handle, &info);
    info.bVisible = FALSE;  //���å���
    SetConsoleCursorInfo(handle, &info);
}

int gotoxy(int x,int y) //���ʴ�� 
{
	COORD coord; //�Ыؤ@��coord���c 
	coord.X = x; //�Nx�Ȧs�J 
	coord.Y = y; // �Ny�Ȧs�J 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord); //�N��Ч��s�y�� 
}

void board() //�خثإ� 
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

void one_player_board()//��H�Ҧ��خثإ� 
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

void two_player_board() //���H�Ҧ��خثإ� 
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

void other_board() //��L�ﶵ�e��  
{
	board();
	gotoxy(25,5);
	printf("|��L�ﶵ|"); 
	gotoxy(25,8);
	printf("�Ʀ�]:");
	gotoxy(25,13);
	printf("�s�@�H��:");
	gotoxy(45,27);
	printf("[���Uesc��^�D�e��]"); 
	gotoxy(45,28);
	printf("[���Uenter�T�{�Ҧ�]"); 
	gotoxy(45,29);
	printf("[�ϥ�%c,%c�����ܼҦ�]",up,down); 
}

void grade_board() //�Ʀ�] 
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
		if(enter == 27)
		{
			break;
		}
	}
}

void start()//�D�e�� 
{
	int i = 0,j = 0;
	board();
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

void staff()//�s�@�H���e�� 
{
	char enter;
	board();
	gotoxy(25,5);
	printf("|�s�@�H��|"); 
	gotoxy(25,8);
	printf("1.B11207018 ���f�M");
	gotoxy(25,13);
	printf("2.B11207016 ���a��");
	gotoxy(25,18);
	printf("3.B11208019 �¦t��"); 
	gotoxy(45,28);
	printf("[�ϥ�esc��^��L�ﶵ]");
	while(1)
	{
	 	enter = getch();
		if(enter == 27)
		{
			break;
		}
	}
}

void other()//��L�ﶵ�b�Y�W�U���� 
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

int setting(int light)//�C���]�w 
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
		if(step == 0) //���I���C�� 
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

void rule(int num_player)//��ܳW�h�e�� 
{
	if(num_player == 1)
	{
		gotoxy(25,5);
		printf("|�W�h|"); 
		gotoxy(25,8);
		printf("1.�ϥ�%c%c%c%c����",up,left,down,right);
		gotoxy(25,13);
		printf("2.�C�X�֤@�ӪF��[�@��");
		gotoxy(45,28);
		printf("[��enter�}�l]");
	}
	else
	{
		gotoxy(25,5);
		printf("|�W�h|"); 
		gotoxy(25,8);
		printf("1.���a1�ϥ�%c%c%c%c����",up,left,down,right);
		gotoxy(25,12);
		printf("2.���a2�ϥ�%c%c%c%c����",up_2,left_2,down_2,right_2);
		gotoxy(25,16);
		printf("3.�C�X�֤@�ӪF��[�@��");
		gotoxy(25,20);
		printf("4.�C8�������@��"); 
		gotoxy(25,24);
		printf("5.�˼ƤT���}�l�C��"); 
		gotoxy(45,28);
		printf("[��enter�}�l]");
	}
}

void over(int num_player) //�C�������P�_ 
{
	int i,j,no1 = 0,no2 = 0;
	if(gameover == 1)//�p�G���a�@�w�g�����F,���N���L�L���P�_ 
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
				if(one_xy[i][j] == 0) //�p�G�٦��Ŧ� 
				{
					gameover = 0;
					break;	
				}
				if(j < 3)
				{
					if(one_xy[i][j] == one_xy[i][j+1]) //�p�G�٥i�H�X�� 
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

void move(int num_player) //�Ʀr���� 
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
			do  //�H���ͦ�2��4 
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
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c); //�r����� 
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
	if(kbhit())//��J 
	{
		enter = getch();
	}
	over(num_player);//�����P�_ 
	if(num_player == 2)  //���a�G���ʻP�Ʀr�ͦ� 
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
				do //���a�G�H���ͦ�2��4 
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
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c); //�C��]�w 
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
			
			if(enter == up_2 || enter2 == up_2) //�P�_���a�G���U���� 
			{
				for(i = 0;i < 4;i++)
				{
					no = 100;
					for(j = 0;j < 4;j++)
					{
						if(g1 % 8 == 0 && g1 != 0) //������,�p�G���w�g�S����l�F,��谱��C�� 
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
	if(gameover != 1)//���a�@���� 
	{
		if(enter == up || enter2 == up)   //�P�_���a�G���U���� 
		{
			for(i = 0;i < 4;i++)
			{
				no = 100;
				for(j = 0;j < 4;j++)
				{
					if(num_player == 2) //������,�p�G���w�g�S����l�F,��谱��C�� 
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

void game(int num_player)//�C���e�� 
{
	int i = 0;
	char enter;
	if(num_player == 1) //��l�ȳ]�w 
	{
		one_player_board();
		one_xy[0][0] = 2;
	}
	else if(num_player == 2)  //��l�ȳ]�w  
	{
		two_player_board();	
		two_xy[0][0] = 2;
		one_xy[0][0] = 2;
	}
	for(i = 3;i > 0;i--)//�}�l�����3�� 
	{
		char trash;
		gotoxy(54,15);
		printf("�˼�:%d",i); 
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
		if(num_player == 1)//��H�Ҧ��O���O���� 
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 + background * 225);
			gotoxy(62,12);
			printf("����:%d",g); 
			gotoxy(62,14);
			printf("�ϥ�%c%c%c%c����",up,left,down,right);
			gotoxy(62,16);
			if(grade[0] > g)
			{ 
				printf("���v�̰���:%d",grade[0]); 
			}
			else if(grade[0] <= g)
			{
				printf("���v�̰���:%d",g);
			}  
			move(num_player);
			if(gameover == 1)
			{
				break;
			}
		}
		else if(num_player == 2)//���H�Ҧ����ƻP�����˼���� 
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 + background * 225);
			gotoxy(22,5);
			printf("����:%d",g);
			if(gameover == 1)
			{
				printf(" loss");
			}
			gotoxy(22,7);
			printf("�����˼�:");
			for(i = 0;i < g % 8;i++)
			{
				printf("�i ");
			}
			printf("           ");
			gotoxy(72,5);
			printf("����:%d",g1); 
			if(gameover2 == 1)
			{
				printf(" loss");
			}
			gotoxy(72,7);
			printf("�����˼�:");
			for(i = 0;i < g1 % 8;i++)
			{
				printf("�i ");
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

void final(int num_player)//�C�������e�� 
{
	board();
	char enter;
	gotoxy(47,5);
	printf("|�C������|");
	gotoxy(41,29);
	printf("[���Uenter�^��D�e��]"); 
	if(num_player == 1)
	{
		if(gameover == 1)
		{
			gotoxy(47,15);
			printf("����:%d",g); 
		}
	}
	else if(num_player == 2)
	{
		if(g > g1)
		{
			gotoxy(47,15);
			printf("���a1�ӧQ"); 	
		}
		else
		{
			gotoxy(47,15);
			printf("���a2�ӧQ"); 	
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
	first();  //��l�� 
	restart:
	start();
	board();
	while(1)
	{
		if(color == 0)
		{
			system("color 0F");//�I���C����� 
		}
		else 
		{
			system("color F0");
		}
		switch(step)
		{
			case 0: //�D�e����ܼҦ� 
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
			case 1: //��ܤH�� 
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
			case 2: //��ܳW�h 
				if(enter == 13)
				{
					step = 3;
					system("cls");
				}
			
			break;
			case 3://�}�l�C�� 
				game(num_player);
				system("cls");
				step = 4;
			break;
			case 4://�ܼƴ_�k 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 + background * 225);
				final(num_player);
				int temp;
				gameover = 0;
				if(num_player == 1)//�p�G�O��H�Ҧ�,�x�s���Z 
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
