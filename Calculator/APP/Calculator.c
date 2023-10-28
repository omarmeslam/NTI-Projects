#include "StdTypes.h"
#include "KeyPad_Interface.h"
#include "LCD_Interface.h"
#include "Calculator_Interface.h"



static u8 k=NO_KEY;
static s16 num=0, Result=0;
static c8 OperatorsArr[20]={0};
static s16 NumbersArr[20]={0};
static u8 StorageIdx=0, StorageSize,FlagToCalc=0;



void Calculator_Init(void)
{
	LCD_Clear();
}

void Calculator_Runnable(void)
{
	k=KEYPAD_GetKey();
	
	if (k != NO_KEY)
	{	
		
		if(k>='0' && k<='9')
		{
			num = num*10 + (k-'0');
			
		}
		else if ((k=='*') || (k=='/') || (k=='+') || (k=='-') || (k=='='))
		{
			NumbersArr[StorageIdx]=num;
			OperatorsArr[StorageIdx]=k;
			StorageIdx++;
			num=0;
			if (k=='=')
			{
				FlagToCalc=1;
			}
		}
		LCD_WriteChar(k);
		
	}
	
	if (FlagToCalc)
	{
		OperatorsArr[StorageIdx-1]=0;
		StorageSize=StorageIdx;
		
		
		
		for (u8 i=0; i<StorageSize; i++)
		{
			if (OperatorsArr[i]=='*')
			{
				u16 TempRes=NumbersArr[i]*NumbersArr[i+1];
				for (u8 j=i; j<StorageSize-1; j++)
				{
					NumbersArr[j]=NumbersArr[j+1];
					OperatorsArr[j]=OperatorsArr[j+1];
				}
				NumbersArr[i]=TempRes;
				StorageSize--;
				i--;
			}
		}
		
		for (u8 i=0; i<StorageSize; i++)
		{
			if (OperatorsArr[i]=='/')
			{
				u16 TempRes=NumbersArr[i]/NumbersArr[i+1];
				for (u8 j=i; j<StorageSize-1; j++)
				{
					NumbersArr[j]=NumbersArr[j+1];
					OperatorsArr[j]=OperatorsArr[j+1];
				}
				NumbersArr[i]=TempRes;
				StorageSize--;
				i--;
			}
		}
		
		
		Result=NumbersArr[0];
		for (u8 i=0; i<StorageSize; i++)
		{
			if (OperatorsArr[i]=='+')
			{
				Result=Result+NumbersArr[i+1];
			}
			else if (OperatorsArr[i]=='-')
			{
				Result-=NumbersArr[i+1];
			}
		}
		
		LCD_GoTo(2,0);
		LCD_WriteNumber(Result);
		FlagToCalc=0;
	}
}