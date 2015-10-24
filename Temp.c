#include "Temp.h"

unsigned char Temp1,Temp2;
unsigned char reset(void)
{
    
    //低電位>430us，表示bus reset
    unsigned char out;
    TRISA4=0;
    RA4=0;
    __delay_us(503);
    TRISA4=1;
    __delay_us(70);
    
    //檢查從機是否存在
    if(RA4==1)
    {
        out=0;
    }
    else
    {
        out=1;
    }
    __delay_us(430);
    return out;
}
void Write_bit(unsigned char data)
{
    unsigned char k;
    unsigned char i;
    for(i=0;i<8;i++)
    {
        k=data&0x01;
        TRISA4=0;
        RA4=0;
        NOP();
        NOP();
   	NOP();
   	NOP();
   	NOP();
        if(k==1)
        {
            TRISA4=1;
        }
        //維持60~120us，將訊號寫入
        __delay_us(63);
        TRISA4=1;
        NOP();
        NOP();
        data = data>>1;
    }
}
unsigned char Read_bit(void)
{
   unsigned char k=0;
   for(int i=0;i<8;i++)
   {
       k>>=1;
       TRISA4=0;
       RA4=0;
       //10us後開始讀取
       NOP();
       NOP();
       NOP();
       NOP();
       NOP();
       NOP();
       TRISA4=1;
       NOP();
       NOP();
       NOP();
       NOP();
       if(RA4==1)
       {
           k|=0x80;

       }
       __delay_us(63);

   }
   return k;
}
void ConvertT(void)
{
    if(reset()==1)
    {
        Write_bit(0xcc); //跳過ROM
        Write_bit(0x44); //溫度轉換
       
    }
}
void read_T(void)
{
    
    unsigned char LSB,MSB;
    
    if(reset()==1)
    {
         Write_bit(0xcc);   //跳過ROM
         Write_bit(0xbe);   //讀取內部9bit的資料
         LSB=Read_bit();
         MSB=Read_bit();
          //LSB的低四位為小數點
         Temp2=LSB&0x0F;
         
         Temp1=(LSB>>4)|(MSB<<4);
    }
    
    
}