#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

char chest[30][30],res[3];
char horizontal,vertical;
int chest_O,chest_X,winner;
int i=0,a=0,k=0,b=0;

int step=0,gameover=0,restart=0;
	
void full_screen()  //�������Ualt+enter,��ܥ��ù� 
{
	keybd_event(VK_MENU,0,0,0);
    keybd_event(VK_RETURN,0,0,0);
    keybd_event(VK_MENU,0,KEYEVENTF_KEYUP,0);
    keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);
}	

int checkerboard()    	//��l�ѽL�c�� 
{
	for(i=0;i<15;i++)
	{
		for(a=0;a<15;a++)
		{
			chest[i][a]='+';
		}
	}
}

int over()				//�C������,�ӧQ����� 
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

int check_x() //�P�_x�b��V�O�_�����l�s�u 
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

int check_y() //�P�_y�b��V�O�_�����l�s�u  
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

check_yx() //�P�_�׽u��V�O�_�����l�s�u 
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

int check_xy() //�P�_�ϱ׽u��V�O�_�����l�s�u  
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

int win() //�C����������P�_ 
{
	int space=0;
	check_x(); //�P�_x��V�O�_�����l�s�u 
	check_y(); //�P�_y��V�O�_�����l�s�u 
	check_xy(); //�P�_�׽u��V�O�_�����l�s�u 
	check_yx(); //�P�_�ϱ׽u��V�O�_�����l�s�u 
	for(i=0;i<15;i++)
	{
		for(a=0;a<15;a++)
		{
			if(chest[a][i]!='+')
				space=space+1;
		}
	}
	if(space>=255) //�p�G�S���Ŷ��F,�N���� 
	{
		gameover=1;
		winner=3;
	}
	else
	{
		space=0;
	}
}

enter()  //��J 
{
	char word=65;
	printf("  A   B   C   D   E   F   G   H   I   J   K   L   M   N   O\n\n");//�ѽL�Ĥ@��y��  
	for(i=0;i<15;i++) // �U�� 
	{
		printf("%c%",word+i);
		printf(" ");
		for(a=0;a<15;a++)
		{
			printf("%c   ",chest[i][a]);
		}
		printf("\n\n");
	}
	if(step==0)																						//��J�y�� 
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);	//����Ŧr 
		printf("O�п�J�y��:"); 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);  //��ܬ��r 
		printf("X�п�J�y��:"); 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);  
	}
	scanf(" %c %c",&vertical,&horizontal);
	fflush(stdin);
	if (chest[horizontal-65][vertical-65] !='+')													//error�P�_ 
	{
		if((chest[horizontal-65][vertical-65] =='O')||(chest[horizontal-65][vertical-65] =='X'))	//��error 
		{
			printf("\nError:���i��J���Ʈy��\n\n");
			system("pause");
		}
		else
		{	
			printf("\nError:�S�����y��\n\n");
			system("pause");
		}
	} 
	else 																							//�S��error 
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

int start()//�}�l�C���_�k 
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

int main()//�C���D�{�� 
{
	full_screen();
	printf("�w��Ө줭�l�ѹC��\n\n�{���]�p:���f�M\n�{������:���a��\n\n");  //�C���}�l�e�� 
	system("pause");
	system("cls");

	printf("�C���W�h�p�U:\n\n");										   //�C���W�h���� 
	printf("1.��J�覡:�п�J�j�g�y��,��X�b�bY�b �Ҧp:AB \n");
	printf("2.�C���H��:2�H\n"); 
	printf("3.�p�G��J�W�L��Ӧr,�N�u�|Ū���e�����\n\n"); 
	system("pause");
	system("cls");
	
	while(restart!=1)													  //�C���}�l 
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
			printf("����O��o�ӧQ\n\n"); 
		}
		else if(winner==2)
		{
			printf("����X��o�ӧQ\n\n"); 
		}
		else if(winner==3)
		{
			printf("����\n\n"); 
		}
		while(1)
		{
			printf("�O�_�A�Ӥ@��YES/NOT:"); //�O�_�A�Ӥ@�� 
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
				printf("��J�榡���~\n");
				fflush(stdin);
			}
		}
	}
}

