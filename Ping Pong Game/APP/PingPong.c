
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "LCD_Interface.h"
#include "PingPong_Interface.h"

#define F_CPU 8000000
#include <util/delay.h>




static u16 flag=0,lineBallFlag1=0,lineBallFlag2=0,i2=0;
static s8 LineBall=0,LinePlayer1=0,LinePlayer2=0;
static u16 x=1;
static u8 Player1Score=0,Player2Score=0;


static u8 Player[] = {
	0x04,
	0x0A,
	0x04,
	0x0E,
	0x04,
	0x0E,
	0x0A,
	0x00
};

static u8 Ball[] = {
	0x0E,
	0x0E,
	0x0E,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00
};


void PingPong_Init(void)
{
	LCD_CustomChar(0,Player);
	LCD_CustomChar(1,Ball);
	
	
	LCD_GoTo(0,6);
	LCD_WriteString("Welcome");
	LCD_GoTo(1,4);
	LCD_WriteString("Ping Pong Ball");
	_delay_ms(2000);
	LCD_ClearPosition(0,0,18);
	LCD_ClearPosition(1,0,18);
	LCD_GoTo(3,8);
	LCD_WriteString("Score");
	
	
	LCD_GoTo(0,0);
	LCD_WriteChar(0);
	LCD_GoTo(0,19);
	LCD_WriteChar(0);
	
	LCD_GoTo(0,1);
	LCD_WriteChar(1);
}


void PingPong_Runnable(void)
{
	if ((x>=1) && (x<20))
	{
		if (flag==0)
		{
			LCD_GoTo(LineBall,x);
			LCD_ClearPosition(LineBall,x,1);
			x++;
			LCD_GoTo(LineBall,x);
			LCD_WriteChar(1);
		}
		else
		{
			LCD_GoTo(LineBall,x);
			LCD_ClearPosition(LineBall,x,1);
			
			x--;
			LCD_GoTo(LineBall,x);
			LCD_WriteChar(1);
			
		}
		
	}
	
	if ((x==1) && (LinePlayer2==LineBall))
	{
		flag=0;
	}
	else if ((x==18) && (LinePlayer1==LineBall))
	{
		flag=1;
	}
	else if ((x==1) && (LinePlayer2!=LineBall))
	{
		LCD_GoTo(LineBall,x);
		LCD_ClearPosition(LineBall,x,1);
		x--;
		_delay_ms(200);
		LCD_GoTo(LineBall,x);
		LCD_WriteChar(1);
		_delay_ms(200);
		LCD_GoTo(LineBall,x);
		LCD_ClearPosition(LineBall,x,1);
		flag=1;
		x=18;
		Player2Score++;
	}
	else if ((x==18) && (LinePlayer1!=LineBall))
	{
		LCD_GoTo(LineBall,x);
		LCD_ClearPosition(LineBall,x,1);
		x++;
		_delay_ms(200);
		LCD_GoTo(LineBall,x);
		LCD_WriteChar(1);
		_delay_ms(200);
		LCD_GoTo(LineBall,x);
		LCD_ClearPosition(LineBall,x,1);
		flag=0;
		x=1;
		Player1Score++;
	}
	
	
	if (!READ_BIT(PIND,3))
	{
		if ((x>=17) && (LinePlayer1==LineBall))
		{
			lineBallFlag1=1;
		}
		LCD_ClearPosition(LinePlayer1,15,5);
		LinePlayer1++;
		if (LinePlayer1>2)
		{
			LinePlayer1=2;
		}
		
		LCD_GoTo(LinePlayer1,19);
		LCD_WriteChar(0);
		while(!READ_BIT(PIND,3));
	}
	
	if (!READ_BIT(PIND,5))
	{
		if ((x>=17) && (LinePlayer1==LineBall))
		{
			lineBallFlag2=1;
		}
		LCD_ClearPosition(LinePlayer1,15,5);
		LinePlayer1--;
		if (LinePlayer1<0)
		{
			LinePlayer1=0;
		}
		LCD_GoTo(LinePlayer1,19);
		LCD_WriteChar(0);
		while(!READ_BIT(PIND,5));
	}
	
	if (!READ_BIT(PIND,7))
	{
		if ((x<=2) && (LinePlayer2==LineBall))
		{
			lineBallFlag1=1;
		}
		LCD_ClearPosition(LinePlayer2,0,5);
		LinePlayer2++;
		if (LinePlayer2>2)
		{
			LinePlayer2=2;
		}
		LCD_GoTo(LinePlayer2,0);
		LCD_WriteChar(0);
		while(!READ_BIT(PIND,7));
	}
	
	if (!READ_BIT(PIND,6))
	{
		if ((x<=2) && (LinePlayer2==LineBall))
		{
			lineBallFlag2=1;
		}
		LCD_ClearPosition(LinePlayer2,0,5);
		LinePlayer2--;
		if (LinePlayer2<0)
		{
			LinePlayer2=0;
		}
		LCD_GoTo(LinePlayer2,0);
		LCD_WriteChar(0);
		while(!READ_BIT(PIND,6));
	}
	
	
	if (lineBallFlag1)
	{
		LineBall++;
		if (LineBall>2)
		{
			LineBall=2;
		}
		lineBallFlag1=0;
	}
	
	if (lineBallFlag2)
	{
		LineBall--;
		if (LineBall<0)
		{
			LineBall=0;
		}
		lineBallFlag2=0;
	}
	
	
	LCD_GoTo(3,18);
	LCD_WriteNumber(Player1Score);
	LCD_GoTo(3,1);
	LCD_WriteNumber(Player2Score);
	
	if ((Player1Score==5) || (Player2Score==5))
	{
		LCD_Clear();
		LCD_GoTo(1,5);
		LCD_WriteString("Game Over");
		_delay_ms(2000);
		LCD_Clear();
		PingPong_Init();
		Player1Score=0;
		Player2Score=0;
		x=1;
	}
	
	_delay_ms(200);
}