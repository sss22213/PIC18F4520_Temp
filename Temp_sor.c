#include "Temp_sor.h"
unsigned char temp1;
unsigned char temp2;

unsigned char reset(void)
{
    unsigned char outbit;
    TRISA4=0;					//设置RA4位输出口
    RA4=0;					    //设置RA4=0;
    __delay_us(503);                //延时503us
    TRISA4=1;                   //设置RA4为输入口，以释放总线等电阻拉高总线
    __delay_us(70);                  //延时70us
    if(RA4==1) outbit=0;        //没有接收到应答信号，继续复位
    else outbit=1;              //接收到应答信号
    __delay_us(430);                   //延时430us
    return outbit;  	        //带参数返回，如果接收到应答，返回1，否则返回0
}
//---------------------------------------
//名称: 写字节函数
//作者：cby
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20110601
//-----------------------------------------
void write_byte(unsigned char  val)
{
 	unsigned char i;
 	unsigned char temp;
 	for(i=8;i>0;i--)
 	{
   		temp=val&0x01;              //最低位移出
   		TRISA4=0;					//设置RA4位输出口
		RA4=0;					    //设置RA4=0;
   		NOP();
   		NOP();
   		NOP();
   		NOP();
   		NOP();                      //从高拉至低电平,产生写时间隙
   		if(temp==1)  TRISA4=1;      //如果写1,拉高电平
   		__delay_us(63);                    //延时63us
   		TRISA4=1;                   //设置RA4为输入口，以释放总线等电阻拉高总线
   		NOP();
   		NOP();
   		val=val>>1;                //右移一位
  	}
}
//---------------------------------------
//名称: 读字节函数
//作者：cby
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20110601
//-----------------------------------------
unsigned char read_byte(void)
{
 unsigned char i;
 unsigned char value=0;                                //读出温度
 for(i=8;i>0;i--)
 {
   value>>=1;
   TRISA4=0;					//设置RA4位输出口
   RA4=0;					    //设置RA4=0;
   NOP();
   NOP();
   NOP();
   NOP();
   NOP();
   NOP();                      //6us
   TRISA4=1;                   //设置RA4为输入口
   NOP();
   NOP();
   NOP();
   NOP();                      //4us
   if(RA4==1) value|=0x80;     //如果接收到数据为1,从最高位往右移
   __delay_us(63);                     //63us
  }
  return(value);
}
//---------------------------------------
//名称: 启动读温度函数
//作者：cby
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20110601
//-----------------------------------------
void convert_T(void)
{
    if(reset()==1)            //如果复位成功
	{
        write_byte(0xcc);     // 跳过多器件识别
        write_byte(0x44);     // 启动温度转换
    }
}
//---------------------------------------
//名称: 读温度函数
//作者：cby
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20110601
//-----------------------------------------
void read_T(void)
{
    unsigned char Lsb,Msb;
    if(reset()==1)
	{
        write_byte(0xcc);      // 跳过多器件识别
        write_byte(0xbe);      // 读暂存器
        Lsb=read_byte();       // 低字节
        Msb=read_byte();  	   // 高字节
		temp2=Lsb&0x0f;        //LSB的低4位为小数部分
		temp1=(Lsb>>4)|(Msb<<4);//LSB的高4位和MSB拼成整数部分
    }
} 