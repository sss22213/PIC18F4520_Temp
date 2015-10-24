#define _XTAL_FREQ 4000000
#include "htc.h"
#include "Temp.h"
#include "1602.H"
extern unsigned char Temp2;
extern unsigned char Temp1;
const unsigned char tablexiao[16]={0,0,1,2,2,3,4,4,5,6,6,7,8,8,9,9};
void __delay_s(int t);
void Clock_display(void);
void Time_display(void);
//中斷計數(500ms*2=1s)
int count=0;
 //Timee_init();
int sec=0;
int min=0;
int hour=0;
int main()
{

   
    
   //DataBus_init
    ADCON1=0x0F;
    TRISA=0xFF;
    TRISD=0x00;
    TRISB=0x00;
    
    //LCD
    LCD_init();

    //Interrupt//

    T1CON=0B11111101;
	//TMR1
    TMR1H=(65536-62500)/256;
    TMR1L=(65536-62500)%256;
    //set flag
    TMR1IF=0;
    TMR1IP=1;
    TMR1IE=1;
    //start
    IPEN=1;
    GIEH=1;
    TRISC=0xFF;
    
    while(1)
    {
         Clock_display();
         //每20s執行一次時間函式
         if(sec%20==0)
         {
            Clean_screen();
            Time_display();
            __delay_s(2);
            Clean_screen();
         }
         if(sec==10)
         {
             //中斷失能
            TMR1IE=0;
            TRISC=0x00;
            PORTC=0xFF;
            TRISC=0xFF;
            if(RC0==0)
            {
                dispalay_string("try_OK",0xC0);
            }
             //中斷致能
             TMR1IE=1;

         }
    }
   
}
void __delay_s(int t)
{
    for(;t>0;t--)
    {
          for(int i=0;i<10;i++)
         {
            __delay_ms(100);
         }
    }
 }
void interrupt  HighInt()
{
    if(TMR1IE && TMR1IF && count==2000)
    {
         count=0;
         //秒數
         sec++;
         TMR1IF=0;
         TMR1IE=0;
         TMR1H=(65536-62500)/256;
         TMR1L=(65536-62500)%256;
         TMR1IE=1;

    }
    else
    {
        TMR1IE=0;
        count++;
        TMR1H=(65536-62500)/256;
        TMR1L=(65536-62500)%256;
        TMR1IE=1;
        

    }

}
void Clock_display(void)
{
     //上排
    dispalay_string("Now Time:",0x80);
    //顯示時間_下排
          if(min>=60)
         {
            hour++;
            min=0;
         }
         if(sec>=60)
         {
            min++;
            sec=0;
         }
         //小時
         dispalay(0xC0,hour/10+0x30);
         dispalay(0xC1,hour%10+0x30);
         dispalay(0xC2,':');
         //分數
         dispalay(0xC3,min/10+0x30);
         dispalay(0xC4,min%10+0x30);
         dispalay(0xC5,':');
         //秒數
         dispalay(0xC6,sec/10+0x30);
         dispalay(0xC7,sec%10+0x30);


}
void Time_display(void)
{
     //上排
    dispalay_string("Now Temp:",0x80);
    //顯示溫度
        unsigned char buf;
     //顯示溫度_下排
        ConvertT();            //啟動溫度轉換

        __delay_ms(94);     //最多在93.74ms轉換完成
         read_T();          //读温度数据

         buf= Temp1/10;
         buf+=0x30;
         dispalay(0xC0,buf);
         buf=Temp1%10;
         buf+=0x30;
         dispalay(0xC1,buf);
         dispalay(0xC2,'.');
         buf=tablexiao[Temp2];
         buf+=0x30;
         dispalay(0xC3,buf);
         dispalay(0xC4,0xDF);
         dispalay(0xC5,'C');
         dispalay(0xC6,',');
         //溫度判斷
         if(Temp1/10==2 && Temp1%10<7 && Temp1%10>4)
         {
            dispalay_string("Good",0xC7);

         }
         else if(Temp1/10>1 && Temp1%10>5)
         {
            dispalay_string("hot",0xC7);

         }
         else
         {
            dispalay_string("cold",0xC7);

         }

}
/*
 *作者:粘博閎
 *日期:2015/04/07
 *功能:顯示文字於LCD1602
*/