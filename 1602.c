#include "1602.H"
void LCD_init()
{
    __delay_ms(150);
    write_com(0x38);  //設定1602為8bits
    __delay_ms(50);
    write_com(0x38);  //設定1602為8bits
    __delay_ms(50);
    write_com(0x38);  //設定1602為8bits
    busy_bus();
    write_com(0x38);  //設定1602為8bits
    busy_bus();
    write_com(0x08);  //關閉螢幕
    busy_bus();
    write_com(0x01);  //清除螢幕
    busy_bus();
    write_com(0x06);  //設置輸入模式，完成一個字傳送後，游標自動右移
    busy_bus();
    write_com(0x0C);  //開啟螢幕
}
void busy_bus()
{
    TRISD7=1;
    RS=0;
    RW=1;
    E=1;
    while(RD7==1);
    E=0;
    TRISD7=0;
}
void write_com(unsigned char data)
{
    RS=0;
    RW=0;
    LCD_BUS=data;
    E=1;
    asm("nop");
    E=0;

}
void write_data(unsigned char data)
{
    busy_bus();
    RS=1;
    RW=0;
    LCD_BUS=data;
    E=1;
    asm("nop");
    E=0;
}
void dispalay(unsigned char x,unsigned char data)
{

    busy_bus();
    write_com(x);
    busy_bus();
    write_data(data);
    busy_bus();

}
void dispalay_string(char *sp,unsigned char start_addr)
{
    //set_start
    dispalay(start_addr,*sp);
    int  str_length=1;

     //display_other(RAM can auto plus)
    while(*(sp+str_length)!='\0')
    {
        busy_bus();
        write_data(*(sp+str_length));
        str_length++;
    }
}
void Clean_screen(void)
{
    busy_bus();
    write_com(0x01);  //清除螢幕
    busy_bus();

}
