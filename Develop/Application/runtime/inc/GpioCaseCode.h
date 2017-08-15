#ifndef __GPIO_CASE_CODES_H__
#define __GPIO_CASE_CODES_H__
/*
addby lanjun  2013.11.10
*date		version			detail					author
*20131116  	V0		initial version release.    	lanjun
*20140117  	V1		delete  "case INPUT_PB27"   	lanjun  usefulless
*					add  "case OUTPUT_PC31"			lanjun  PC31 use for can reset   2014.3.18
ioctl(fd,CASE_CODES,arg) instruction:
1.CASE_CODES  can be defined as follows.
2.If CASE_CODE is output_class ,you need to give the arg to
tell driver  what you want to output: HIGH or LOW.
3.Corresponding  to each case, there is only one pin . 

*/
//input pins CASE_CODES without pullup inside of CPU
#define	INPUT_PB21	(1) //��ͣ���أ��ͼ�ͣ������
#define	INPUT_PB22 	(8)
#define	INPUT_PB23	(3)
#define	INPUT_PB24	(4)
#define	INPUT_PB25	(5)
#define	INPUT_PB26	(6) //�����������͹���
//#define	INPUT_PB27	(7)
#define	INPUT_PC11	(7)// ac_cc �͵�ƽ S�պ�
#define	INPUT_PB20	(10) 

//output pins CASE_CODES
//#define	OUTPUT_PB20	(10) //RFID card reset
#define	OUTPUT_PB28	(11) //led1
#define	OUTPUT_PB29	(12) //led2
#define	OUTPUT_PB30	(13) //led3
#define	OUTPUT_PB31	(14) //led4
#define	OUTPUT_PC24	(15)  //�����������
#define	OUTPUT_PC22	(16)  //�����������
#define	OUTPUT_PC20	(17)  //�������Ӵ�������
#define	OUTPUT_PC18	(18)  //�������Ӵ�������
#define	OUTPUT_PC16	(19)  //gprs_powet_en
//MCP2515 reset  added by lan  20140117
// 0:reset activity    
// 1:reset unactivity
#define	OUTPUT_PC31	(24)  // PC31 use for can0 reset
#define	OUTPUT_PC29	(25)  // PC29 use for can1 reset
#define	OUTPUT_PC27	(26)  // PC27 use for can2 reset
#define	OUTPUT_PC11	(27)  // 

#define	OUTPUT_PC10	(21)  //AC_PWM �͵�ƽ���12V���ߵ�ƽ���PWM
#define	OUTPUT_PD25	(22)  //LCD ������ƣ��ߵ�ƽ�������͵�ƽȫ����
#define	OUTPUT_PE0	(23)  //LCD ������ƣ��ߵ������͵�ƽ�ء�



#define	HIGH	1
#define	LOW		0
#endif
