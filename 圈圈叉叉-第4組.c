#include <stdio.h>  //�ŧi�{���w 
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

void full_screen()  //��ܥ��ù� 
{
	keybd_event(VK_MENU,0,0,0);  //�������Ualt 
    keybd_event(VK_RETURN,0,0,0); 	//�������Uenter 
    keybd_event(VK_MENU,0,KEYEVENTF_KEYUP,0); //������}alt 
    keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0); //������}enter 
}

void board()  //���O��� 
{
	system("cls");  //�����e�� 
	printf("\n");
	for (i=0;i<30;i++) 
	{
    	printf("%s\n", show[i]);
	}
}

void board_2()  //�E�c����� 
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
    				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),249); //�]�wO����C�� (�թ��Ŧr) 
    			}
    			else if(show[i][j]=='X')
    			{
    				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),252);//�]�wX����C��(�թ����r) 
    			}
    			else
    			{
    				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);//�]�w�E�c��I���C��(�թ�) 
    			}
			}
    		else
    		{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15); //��L�Ҭ��¦� 
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

int win()  //�ӧQ�P�_ 
{
	int no_space=0;  	//����P�_ 
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
	if(no_space==9) //�p�G�S��l�F �N���� 
	{
		over=3;
	}
	for(i=0;i<3;i++) //�P�_x��V�O�_���H��� 
	{
		for(j = 0;j<=3;j++)
		{
			if(over_X==3)//�p�GX��� 
			{
				over=1;
			}
			else if(over_O==3)//�p�GO��� 
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
	for(j=0;j<3;j++) //�P�_y��V�O�_���H��� 
	{
		for(i = 0;i<=3;i++)
		{
			if(over_X==3) //�p�GX��� 
			{
				over=1;
			}
			else if(over_O==3) //�p�GO��� 
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
	if(show_2[1][2]=='O' && show_2[5][8] =='O'&& show_2[9][14]=='O') //�P�_O�׽u��V�O�_��� 
	{
		over_O=3;
		over=2;
	}
	else if(show_2[9][2]=='O' && show_2[5][8]=='O' && show_2[1][14]=='O') //�P�_O�ϱ׽u��V�O�_��� 
	{
		over_O=3;
		over=2;
	}
	else if(show_2[1][2]=='X' && show_2[5][8]=='X' && show_2[9][14]=='X') //�P�_X�׽u��V�O�_���
	{
		over_X=3;
		over=1;
	}
	else if(show_2[9][2]=='X' && show_2[5][8]=='X' && show_2[1][14]=='X')//�P�_X�ϱ׽u��V�O�_���
	{
		over_X=3;
		over=1;
	}
	return over;
}

void one_player()  //��H�Ҧ� 
{
	a:
	srand(time(NULL));  //�]�w�H���� 
	int randomx,randomy;
	if(who==0) //AI���^�X 
	{
		int AI_x=0;	
		if(hard==0) //²������ 
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
		else if(hard==1)  //���q���� 
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
					for(i=0;i<3;i++) //�P�_X��V�O�_�����O�s�u 
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
					for(j=0;j<3;j++)  //�P�_y��V�O�_�����O�s�u 
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
					for(i=0;i<3;i++) //�P�_X�׽u�V�O�_�����O�s�u
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
					for(i=0;i<3;i++)  //�P�_X�ϱ׽u�V�O�_�����O�s�u 
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
					while(1) //�p�G���S���N�H�K�U 
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
	if(win()==0)  //�p�G�S��AI��� 
	{
		a=getch();  //Ū�����U����   ���a���^�X 
	}
	if(a=='S'||a=='s')  //�V�U�@�� 
	{ 
		if(y<3)
		{ 
			show_2[2+(y-1)*4][2+(x-1)*6]=' ';
			y++;
			show_2[2+(y-1)*4][2+(x-1)*6]='.';
			board_2();
		} 
	}
	else if(a=='W'||a=='w') //�V�W�@�� 
	{
		if(y>1)
		{
			show_2[2+(y-1)*4][2+(x-1)*6]=' ';
			y--;
			show_2[2+(y-1)*4][2+(x-1)*6]='.';
			board_2();
		}
	}
	else if(a=='A'||a=='a') //�V���@�� 
	{
		if(x>1)
		{
			show_2[2+(y-1)*4][2+(x-1)*6]=' ';
			x--;
			show_2[2+(y-1)*4][2+(x-1)*6]='.';
			board_2();
		}
	}
	else if(a=='D'||a=='d')//���k�@�� 
	{
		if(x<3)
		{
			show_2[2+(y-1)*4][2+(x-1)*6]=' ';
			x++;	
			show_2[2+(y-1)*4][2+(x-1)*6]='.';
			board_2(); 
		}
	}
	else if(a==13) //���Uenter�U�� 
	{
		if(who==1 && show_2[1+(y-1)*4][2+(x-1)*6]==' ')
		{
			show_2[1+(y-1)*4][2+(x-1)*6]='O';
			board_2();
			who=0;
		}
	}
	 
}


void two_player() //���H�Ҧ� 
{	
	char a=getch();
	if(a=='S'||a=='s')//�V�U�@��
	{ 
		if(y<3)
		{ 
			show_2[2+(y-1)*4][2+(x-1)*6]=' ';
			y++;
			show_2[2+(y-1)*4][2+(x-1)*6]='.';
			board_2();
		} 
	}
	else if(a=='W'||a=='w')//�V�W�@��
	{
		if(y>1)
		{
			show_2[2+(y-1)*4][2+(x-1)*6]=' ';
			y--;
			show_2[2+(y-1)*4][2+(x-1)*6]='.';
			board_2();
		}
	}
	else if(a=='A'||a=='a')//�V���@��
	{
		if(x>1)
		{
			show_2[2+(y-1)*4][2+(x-1)*6]=' ';
			x--;
			show_2[2+(y-1)*4][2+(x-1)*6]='.';
			board_2();
		}
	}
	else if(a=='D'||a=='d')//�V�k�@��
	{
		if(x<3)
		{
			show_2[2+(y-1)*4][2+(x-1)*6]=' ';
			x++;	
			show_2[2+(y-1)*4][2+(x-1)*6]='.';
			board_2(); 
		}
	}
	else if(a==13) //��enter�U�� 
	{
		if(who == 1 && show_2[1+(y-1)*4][2+(x-1)*6]==' ') //O���^�X 
		{
			show_2[1+(y-1)*4][2+(x-1)*6]='O';
			board_2();
			who = 0;
		}
		else if(who == 0 && show_2[1+(y-1)*4][2+(x-1)*6]==' ') //X���^�X 
		{
			show_2[1+(y-1)*4][2+(x-1)*6]='X';
			board_2();	
			who = 1;
		}
	}
} 
int start() //�@�}�l�C����ܪ��e�� 
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

void clear()  //�M���e�� 
{
	for(i=1;i<29;i++)
	{
		for(j=1;j<99;j++)
		{ 
			show[i][j]=' ';
		}		
	}
}

void gameover() //�C�������e�� 
{
	
	clear();
	{ 
		char str[]="Game over";
		for(i=0;i<strlen(str);i++)
		{	
			show[15][45+i]=str[i];
		}
	} 
	if(over==1)  //X��� 
	{
		char str[]="X win";
		for(i=0;i<strlen(str);i++)
		{	
			show[17][45+i]=str[i];
		}
	}
	else if(over==2) //O��� 
	{
		char str[]="O win";
		for(i=0;i<strlen(str);i++)
		{	
			show[17][45+i]=str[i];
		}
	}
	else //���� 
	{
	
		char str[]="Tie";
		for(i=0;i<strlen(str);i++)
		{	
			show[17][45+i]=str[i];
		}
	}
	{
		char str[]="[Press enter to restart]"; //���s�}�l 
		for(i=0;i<strlen(str);i++)
		{ 
			show[28][37+i]=str[i];
		}
	}
	board();
}
void rule() //�W�h�e�� 
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

void staff()  //�s�@�H���e�� 
{
	clear();
	{
		char str[]="1.B11207018";  //�{���s�g100% �{������40% ���i�s�@50% 
		for(i=0;i<strlen(str);i++)
		{
			show[8][15+i]=str[i];
		}
	}
	{
		char str[]="2.B11207019"; //���i�s�@25% �{������30%
		for(i=0;i<strlen(str);i++)
		{
			show[10][15+i]=str[i];
		}
	}
	{
		char str[]="3.B11207016"; //���i�s�@25% �{������30%
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

int main() //�D�{�� 
{
	full_screen();//�I�s���ù� 
	restart:
	step=0;
	start();
	Sleep(1000); //�Ȱ��@�� 
	board();
	while(step==0) //��ܲĤ@�ӵe�� 
	{
		char a=getch();
		if((a=='W'||a=='w')&&step1>1) //��W�V�W�@�� 
		{ 
			step1=step1-1;
		}
		else if((a=='S'||a=='s')&&step1<3) //��S�V�U�@�� 
		{
			step1=step1+1;
		}
		if(step1==1)  //���* 
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
		if(step1==1&&a==13)  //�}�l�C�� 
		{
			step=1;
			break;
		}
		else if(step1==2&&a==13)  //�h�X�C�� 
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
		else if(step1==3&&a==13) //��ܻs�@�H���e�� 
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
	while(step==1) //��� 
	{   
		char a=getch();
		if((a=='W'||a=='w')&&step1>1)//��W�V�W�@�� 
		{ 
			step1=step1-1;
		}
		else if((a=='S'||a=='s')&&step1<2) //��S�V�U�@��  
		{
			step1=step1+1;
		}
		if(step1==1)  //���* 
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
	if(step==7) //��H�Ҧ�������� 
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
			if((a=='W'||a=='w')&&step1>1)//��W�V�W�@�� 
			{ 
				step1=step1-1;
			}
			else if((a=='S'||a=='s')&&step1<2) //��S�V�U�@��  
			{
				step1=step1+1;
			}
			if(step1==1)  //���* 
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
	while(step==4)//��ܳW�h�e�� 
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
	while(step==2) //�I�s��H�禡�����H�禡 
	{
		if(com==0)
		{
			two_player();
		} 
		else if(com==1)
		{
			one_player();
		}
		if(win()!=0)  //�p�G���H��өΥ��� 
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
	while(step==3) //���ҹC�� �_�k 
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
