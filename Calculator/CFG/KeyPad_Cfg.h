

#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

#define Rows  4
#define Cols  5

#define NO_KEY  'F'

#define FIRST_OUTPUT  PINC5
#define FIRST_INPUT   PIND7


#if KEYPAD_PRG
const u8 KeysArr[Rows][Cols]={{'7','8','9','/'},
							  {'4','5','6','*'},
							  {'1','2','3','-'},
							  {'C','0','=','+'}};

#endif


#endif /* KEYPAD_CFG_H_ */