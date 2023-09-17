#include <stdio.h>
#include <conio.h>
#include <dos.h>

//------------- Fix Variable -----------
#define Frame_W 34
#define Frame_H 20
#define yFrame_T 4
#define kEsc 27
#define kEnter 13
#define kLeft 75
#define kRight 77
#define kSpace 32
#define rB 3
#define cB 10

//------------- Global Variables -----------
int xFrame_L = 41 - (Frame_W/2), xFrame_R = 40 + (Frame_W/2);
int yFrame_B = yFrame_T + Frame_H;
int iScore = 0, iLife = 1;
int xPlank, yPlank, LP = 10; //LP: Long Plank
int xBall, yBall;
int SHB, SVB; //SHB: Status Horizontal Ball, V: Vertical
int GamePlay;
int aBlock_S1[rB][cB] = { {1,1,1,1,1,1,1,1,1,1},
			  {1,1,1,1,1,1,1,1,1,1},
			  {1,1,1,1,1,1,1,1,1,1}};

//------------- Function declaration -----------
void Frame();
void Plank();
void CheckKey(int);
void Ball();
void MakeBlock();
int CheckBlock();
void FillBlock();

//------------- Main Function -----------
void main()
{
	int KeyHit;

	Regame:
	//Set variables
	xPlank = 41 - (LP/2);
	yPlank = yFrame_B - 2;
	SHB = 1;
	SVB = 1;
	GamePlay = 0;
	iScore = 0, iLife = 1;
	FillBlock();

	clrscr();

	//Game Loop
	do
	{
		CheckKey(KeyHit);

		while(kbhit() == 0)
		{
			if(iLife == 0)
			{
				gotoxy(36, 15); textcolor(4); cprintf("Game Over");
				getch();
				gotoxy(xBall, yBall); textcolor(4); cprintf("%c",15);
				getch();
				gotoxy(xBall, yBall); printf(" "); textcolor(15);
				getch();
				goto Regame;
			}

			if(CheckBlock() == 0)
			{
				gotoxy(34, 15); printf("## You Win ##");
				goto EndGame;
			}

			clrscr();
			Frame();
			Plank();
			Ball();
			MakeBlock();

			delay(100);
		}

	}while((KeyHit = getch()) != kEsc);

	EndGame:
	getch();
}

//------------- Frame -----------
void Frame()
{
	int i;
	int HL = 205, VL = 186, CTL = 201, CTR = 187, CBL = 200, CBR = 188;
	//C : Corner, H : Horizontal, V : Vertical, T : Top, B : Bottom

	for(i=xFrame_L;i<=xFrame_R;i++)
	{
		gotoxy(i, yFrame_T); printf("%c",HL);
		gotoxy(i, yFrame_B); printf("%c",HL);
	}
	for(i=yFrame_T;i<=yFrame_B;i++)
	{
		gotoxy(xFrame_L, i); printf("%c",VL);
		gotoxy(xFrame_R, i); printf("%c",VL);
	}
	gotoxy(xFrame_L, yFrame_T); printf("%c",CTL);
	gotoxy(xFrame_R, yFrame_T); printf("%c",CTR);
	gotoxy(xFrame_R, yFrame_B); printf("%c",CBR);
	gotoxy(xFrame_L, yFrame_B); printf("%c",CBL);

	//Score
	gotoxy(xFrame_L+1, yFrame_T-1);
	printf("Score : %d", iScore);
}

//------------- Plank -----------
void Plank()
{
	int i;

	for(i=0;i<LP;i++)
	{
		gotoxy(xPlank+i, yPlank);
		printf("%c",219);
	}

}

//------------- Check Key -----------
void CheckKey(int rKey)
{
	if((rKey == kLeft || rKey == 65 || rKey == 97) && xPlank > xFrame_L+1)
	{
		xPlank--;
	}
	if((rKey == kRight || rKey == 68 || rKey == 100) && xPlank+LP < xFrame_R)
	{
		xPlank++;
	}
	if(rKey == kSpace)
	{
		GamePlay = 1;
	}

}

//------------- Ball -----------
void Ball()
{
	int i;

	if(GamePlay == 0)
	{
		xBall = xPlank + (LP/2);
		yBall = yPlank - 1;
	}
	else
	{
		//Ball Move Left-Right
		if(xBall < xFrame_R-1 && SHB == 1)
		{
			xBall++;
		}
		else
		{
			xBall--;
		}
	
		//Ball Move Up-Down
		if(yBall > yFrame_T+1 && SVB == 1)
		{
			yBall--;
		}
		else
		{
			yBall++;
		}
	
		//Check status horizontal ball
		if(xBall == xFrame_R-1)
		{
			SHB = 0;  //Move Left
		}
		if(xBall == xFrame_L+1)
		{
			SHB = 1;  //Move Right
		}
		//Check status vartical ball
		if(yBall == yFrame_T+1)
		{
			SVB = 0;  //Move down
		}
		if(yBall == yFrame_B-1)
		{
			SVB = 1;  //Move up
			GamePlay = 0;
			iLife--;
		}
	
		//Check ball hit plank
		if(yBall == yPlank-1)
		{
			for(i=0;i<LP;i++)
			{
				if(xBall == xPlank+i)
				{
					SVB = 1;  //Move up
				}
			}
		}

	}

	gotoxy(xBall, yBall); textcolor(4); cprintf("%c",3); textcolor(15);
}

//------------- Make Block -----------
void MakeBlock()
{
	int r, c, LB = 3, i;
	int xB = xFrame_L+2, yB = yFrame_T+2;

	for(r=0;r<rB;r++)
	{
		xB = xFrame_L+2;
		for(c=0;c<cB;c++)
		{
			for(i=0; i<LB;i++)
			{
				if(xBall == xB && yBall == yB+r && aBlock_S1[r][c] == 1)
				{
					aBlock_S1[r][c] = 0;
					iScore+=20;
					if(SVB == 1)
					{
						SVB = 0;
					}
					else
					{
						SVB = 1;
					}
				}

				if(aBlock_S1[r][c] == 1)
				{
					gotoxy(xB, yB+r);
					printf("%c",178);
				}
				xB++;
			}
		}
	}

}

//------------- Check Block -----------
int CheckBlock()
{
	int r, c, iSumB = 0;
	for(r=0;r<rB;r++)
	{
		for(c=0;c<cB;c++)
		{
			if(aBlock_S1[r][c] == 1)
			{
				iSumB++;
			}
		}
	}

	return iSumB;
}

//------------- Fill Block -----------
void FillBlock()
{
	int r, c, iSumB = 0;
	for(r=0;r<rB;r++)
	{
		for(c=0;c<cB;c++)
		{
			aBlock_S1[r][c] = 1;
		}
	}
}
