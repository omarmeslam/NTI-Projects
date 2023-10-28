
#include "StdTypes.h"
#include "MemMap.h"
#include "LCD_Interface.h"
#include "LittleStory.h"


#define F_CPU 8000000
#include <util/delay.h>

static u8 x=1,c=0,FlagScreen=0;


u8 InjuredPerson[] = {
	0x00,
	0x00,
	0x0B,
	0x1F,
	0x0B,
	0x00,
	0x1F,
	0x00
};

u8 Person[] = {
	0x0E,
	0x11,
	0x0E,
	0x04,
	0x04,
	0x0E,
	0x04,
	0x00
};

u8 KillerPerson[] = {
	0x0E,
	0x11,
	0x1F,
	0x04,
	0x0E,
	0x0F,
	0x04,
	0x04
};


u8 Arrrow[] = {
	0x04,
	0x02,
	0x1F,
	0x02,
	0x04,
	0x00,
	0x00,
	0x00
};


static void StoryDisplayScreen1(void)
{
	LCD_GoTo(0,0);
	LCD_WriteString("You know, Gaza is");
	LCD_GoTo(1,0);
	LCD_WriteString("continuously being");
	LCD_GoTo(2,0);
	LCD_WriteString("bombarded by Israeli");
	LCD_GoTo(3,0);
	LCD_WriteString("forces and");
}

static void StoryDisplayScreen2(void)
{
	LCD_GoTo(0,0);
	LCD_WriteString("the American and");
	LCD_GoTo(1,0);
	LCD_WriteString("British alliances.");
}

static void StoryDisplayScreen3(void)
{
	LCD_GoTo(0,1);
	LCD_WriteChar(3);
	LCD_GoTo(1,0);
	LCD_WriteString("They targets Gaza");
	LCD_GoTo(2,0);
	LCD_WriteString("childrens,women and");
	LCD_GoTo(3,0);
	LCD_WriteString("the elderly.");
}

static void StoryDisplayScreen4(void)
{
	LCD_GoTo(1,0);
	LCD_WriteString("Where is the World?");
	LCD_GoTo(2,0);
	LCD_WriteString("and What happened");
	LCD_GoTo(3,0);
	LCD_WriteString("to the Principles of");
}


static void StoryDisplayScreen5(void)
{
	LCD_GoTo(1,0);
	LCD_WriteString("human rights?Silence");
	LCD_GoTo(2,0);
	LCD_WriteString("Ignorance control on");
	LCD_GoTo(3,0);
	LCD_WriteString("international scene");
}

static void StoryDisplayScreen6(void)
{
	LCD_GoTo(1,0);
	LCD_WriteString("So we as Muslims");
	LCD_GoTo(2,0);
	LCD_WriteString("must reconsider the");
	LCD_GoTo(3,0);
	LCD_WriteString("approach we take in.");
}

static void StoryDisplayScreen7(void)
{
	LCD_GoTo(0,0);
	LCD_WriteString("Because the Western");
	LCD_GoTo(1,0);
	LCD_WriteString("world only sees its");
	LCD_GoTo(2,0);
	LCD_WriteString("own interest and");
	LCD_GoTo(3,0);
	LCD_WriteString("respect the strong.");
}

static void StoryDisplayScreen8(void)
{
	LCD_GoTo(0,5);
	LCD_WriteString("Palestine");
	LCD_GoTo(1,2);
	LCD_WriteString("will remain free");
	LCD_GoTo(2,0);
	LCD_WriteString("#Free_Palestine");
}


static void StoryChar_Display(void)
{
	LCD_GoTo(0,0);
	LCD_WriteChar(0);
	LCD_GoTo(0,9);
	LCD_WriteChar(1);
	LCD_GoTo(0,12);
	LCD_WriteChar(1);
	LCD_GoTo(0,15);
	LCD_WriteChar(1);
	LCD_GoTo(0,18);
	LCD_WriteChar(1);
}




void LittleStory_Init(void)
{
	LCD_CustomChar(0,KillerPerson);
	LCD_CustomChar(1,Person);
	LCD_CustomChar(2,InjuredPerson);
	LCD_CustomChar(3,Arrrow);
	
	
	
	LCD_GoTo(0,7);
	LCD_WriteString("Welcome");
	LCD_GoTo(1,0);
	LCD_WriteString("We will talk about");
	LCD_GoTo(2,0);
	LCD_WriteString("What's happening in");
	LCD_GoTo(3,0);
	LCD_WriteString("Gaza");
	_delay_ms(3000);
	LCD_Clear();
	
}


void LittleStory_Runnable(void)
{
	if (FlagScreen==0)
	{
		StoryDisplayScreen1();
		
		_delay_ms(3000);
		LCD_Clear();
		
		StoryDisplayScreen2();
		
		_delay_ms(3000);
		LCD_Clear();
		
		StoryChar_Display();
		
		StoryDisplayScreen3();
		
		
		FlagScreen=1;
		
	}
	else if ((FlagScreen==1) && (c==0))
	{
		LCD_ClearPosition(1,0,20);
		LCD_ClearPosition(2,0,20);
		LCD_ClearPosition(3,0,20);
		StoryDisplayScreen4();
		FlagScreen=2;
	}
	else if ((FlagScreen==2) && (c==0))
	{
		LCD_ClearPosition(1,0,20);
		LCD_ClearPosition(2,0,20);
		LCD_ClearPosition(3,0,20);
		StoryDisplayScreen5();
		FlagScreen=3;
	}
	else if ((FlagScreen==3) && (c==0))
	{
		LCD_ClearPosition(1,0,20);
		LCD_ClearPosition(2,0,20);
		LCD_ClearPosition(3,0,20);
		StoryDisplayScreen6();
		FlagScreen=4;
	}
	else if ((FlagScreen==4) && (c==0))
	{
		LCD_Clear();
		StoryDisplayScreen7();
		_delay_ms(3000);
		
		LCD_Clear();
		StoryDisplayScreen8();
		_delay_ms(3000);
		LCD_Clear();
		FlagScreen=0;
	}
	
	
	if ((x>=1) && (x<20) && (FlagScreen!=0))
	{
		LCD_ClearPosition(0,x,1);
		if (x<19)
		{
			LCD_WriteChar(3);
			c++;
		}
		
		if (c==8)
		{
			LCD_GoTo(0,c);
			LCD_WriteChar(2);
		}
		else if (c==11)
		{
			LCD_GoTo(0,c);
			LCD_WriteChar(2);
		}
		else if (c==14)
		{
			LCD_GoTo(0,c);
			LCD_WriteChar(2);
		}
		else if (c==17)
		{
			LCD_GoTo(0,c);
			LCD_WriteChar(2);
		}
	}
	x++;
	if (x==20)
	{
		x=1;
		c=0;
		LCD_ClearPosition(0,0,20);
		StoryChar_Display();
	}
	
	_delay_ms(200);
	
	
	
	
}
