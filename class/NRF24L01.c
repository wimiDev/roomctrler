#include"NRF24L01.h"
//#include"reg52.h"
//#include"Allhead.h"
//sbit CE=P1^2;  //RX/TX模式选择端
//sbit IRQ=P1^3; //可屏蔽中断端
//sbit CSN=P1^4; //SPI片选端//就是SS
//sbit MOSI=P1^5;	//SPI主机输出从机输入端
//sbit MISO=P1^6;	//SPI主机输出从机输出端
//sbit SCLK=P1^7;	//SPI时钟端
  sbit IRQ = P4^7;
  sbit CE =  P1^4;
  sbit CSN=  P1^0;
  sbit SCLK=  P1^3;
  sbit MOSI= P1^1;
  sbit MISO= P1^2;
unsigned char RevTempDate0[5];//同道0接收数据

unsigned char code RxAddr0[]={0x34,0x43,0x10,0x10,0x01};//编号3接收地址这个地址和发送方地址一样!
//unsigned char code RxAddr1[]={0xc2,0xc2,0xc2,0xc2,0xd1};//编号2
//unsigned char code RxAddr2[]={0xc2,0xc2,0xc2,0xc2,0xc1};//编号1
/*****************状态标志*****************************************/
unsigned char  bdata sta;   //状态标志
sbit RX_DR=sta^6;
sbit TX_DS=sta^5;
sbit MAX_RT=sta^4;
/*****************SPI时序函数******************************************/
unsigned char NRFSPI(unsigned char date)
{
    unsigned char i;
   	for(i=0;i<8;i++)          // 循环8次
   	{
	  if(date&0x80)
	    MOSI=1;
	  else
	    MOSI=0;   // byte最高位输出到MOSI
   	  date<<=1;             // 低一位移位到最高位
   	  SCLK=1; 
	  if(MISO)               // 拉高SCK，nRF24L01从MOSI读入1位数据，同时从MISO输出1位数据
   	    date|=0x01;       	// 读MISO到byte最低位
   	  SCLK=0;            	// SCK置低
   	}
    return(date);           	// 返回读出的一字节
}
/**********************NRF24L01初始化函数*******************************/
void NRF24L01Int()
{
	NRFDelay(2);//让系统什么都不干
	CE=0;
	CSN=1;  
	SCLK=0;
	IRQ=1; 
}
/*****************SPI读寄存器一字节函数*********************************/
unsigned char NRFReadReg(unsigned char RegAddr)
{
   unsigned char BackDate;
   CSN=0;//启动时序
   NRFSPI(RegAddr);//写寄存器地址
   BackDate=NRFSPI(0x00);//写入读寄存器指令  
   CSN=1;
   return(BackDate); //返回状态
}
/*****************SPI写寄存器一字节函数*********************************/
unsigned char NRFWriteReg(unsigned char RegAddr,unsigned char date)
{
   unsigned char BackDate;
   CSN=0;//启动时序
   BackDate=NRFSPI(RegAddr);//写入地址
   NRFSPI(date);//写入值
   CSN=1;  
   return(BackDate);
}
/*****************SPI读取RXFIFO寄存器的值********************************/
unsigned char NRFReadRxDate(unsigned char RegAddr,unsigned char *RxDate,unsigned char DateLen)
{  //寄存器地址//读取数据存放变量//读取数据长度//用于接收
    unsigned char BackDate,i;
	CSN=0;//启动时序
	BackDate=NRFSPI(RegAddr);//写入要读取的寄存器地址
	for(i=0;i<DateLen;i++) //读取数据
	  {
	     RxDate[i]=NRFSPI(0);
	  } 
    CSN=1;
   return(BackDate); 
}
/*****************SPI写入TXFIFO寄存器的值**********************************/
unsigned char NRFWriteTxDate(unsigned char RegAddr,unsigned char *TxDate,unsigned char DateLen)
{ //寄存器地址//写入数据存放变量//读取数据长度//用于发送
   unsigned char BackDate,i;
   CSN=0;
   BackDate=NRFSPI(RegAddr);//写入要写入寄存器的地址
   for(i=0;i<DateLen;i++)//写入数据
     {
	    NRFSPI(*TxDate++);
	 }   
   CSN=1;
   return(BackDate);
}
/*****************NRF设置为发送模式并发送数据******************************/
void NRFSetTxMode(unsigned char *TxDate)
{  //发送模式 
    CE=0;   
   	NRFWriteTxDate(W_REGISTER+TX_ADDR,RxAddr0,TX_ADDR_WITDH);//写寄存器指令+P0地址使能指令+发送地址+地址宽度
	NRFWriteTxDate(W_TX_PAYLOAD,TxDate,TX_DATA_WITDH);//写入数据 
	/******下面有关寄存器配置**************/
  	NRFWriteReg(W_REGISTER+EN_AA,0x01);       // 使能接收通道0自动应答
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);   // 使能接收通道0
  	NRFWriteReg(W_REGISTER+SETUP_RETR,0x0a);  // 自动重发延时等待250us+86us，自动重发10次
  	NRFWriteReg(W_REGISTER+RF_CH,0x40);         // 选择射频通道0x40
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);    // 数据传输率1Mbps，发射功率0dBm，低噪声放大器增益
  	NRFWriteReg(W_REGISTER+CONFIG,0x0e);      // CRC使能，16位CRC校验，上电	
	CE=1;	
	NRFDelay(5);//保持10us秒以上
} 
/*****************NRF设置为接收模式并接收数据******************************/
//接收模式
void NRFSetRXMode()
{
    CE=0;
  	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,RxAddr0,TX_ADDR_WITDH);  // 接收设备接收通道0使用和发送设备相同的发送地址
//	NRFWriteTxDate(W_REGISTER+RX_ADDR_P1,RxAddr1,TX_ADDR_WITDH);  // 接收设备接收通道1使用和发送设备相同的发送地址
//  	NRFWriteTxDate(W_REGISTER+RX_ADDR_P2,RxAddr2,TX_ADDR_WITDH);  // 接收设备接收通道2使用和发送设备相同的发送地址

	NRFWriteReg(W_REGISTER+EN_AA,0x03);               // 使能数据通道0和1自动应答
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x03);           // 使能接收通道0和1
             
  	NRFWriteReg(W_REGISTER+RX_PW_P0,TX_DATA_WITDH);  // 接收通道0选择和发送通道相同有效数据宽度
	NRFWriteReg(W_REGISTER+RX_PW_P1,TX_DATA_WITDH);  // 接收通道1选择和发送通道相同有效数据宽度
  	NRFWriteReg(W_REGISTER+RX_PW_P2,TX_DATA_WITDH);  // 接收通道2选择和发送通道相同有效数据宽度

	NRFWriteReg(W_REGISTER+RF_CH,0x40);// 选择射频通道0x40 
	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);            // 数据传输率1Mbps，发射功率0dBm，低噪声放大器增益
	NRFWriteReg(W_REGISTER+CONFIG,0x0f);             // CRC使能，16位CRC校验，上电，接收模式     
  	CE = 1; 
	NRFDelay(5);    
}
/****************************检测是否有接收到数据******************************/
void CheckACK()
{  //用于发射模式接收应答信号
	sta=NRFReadReg(R_REGISTER+STATUS);                    // 返回状态寄存器
	if(TX_DS)
	   NRFWriteReg(W_REGISTER+STATUS,0xff);  // 清除TX_DS或MAX_RT中断标志
}
/*************************接收数据*********************************************/
void GetDate()				 
{
	char i = 0;
    unsigned char RX_P_NO;//接收通道号
	sta=NRFReadReg(R_REGISTER+STATUS);//发送数据后读取状态寄存器
    if(RX_DR)				// 判断是否接收到数据
     {
	   RX_P_NO=sta&0x0e;//获取通道号
	   CE=0;//待机 
	   switch(RX_P_NO)
	    {
		   case 0x00:NRFReadRxDate(R_RX_PAYLOAD,RevTempDate0,RX_DATA_WITDH);break;// 从RXFIFO读取数据通道0
//		   case 0x02:NRFReadRxDate(R_RX_PAYLOAD,RevTempDate1,RX_DATA_WITDH);break;// 从RXFIFO读取数据通道1
//		   case 0x04:NRFReadRxDate(R_RX_PAYLOAD,RevTempDate2,RX_DATA_WITDH);break;// 从RXFIFO读取数据通道2
		   default:break;
		}
	   NRFWriteReg(W_REGISTER+STATUS,0xff); //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标
	   CSN=0;
	   NRFSPI(FLUSH_RX);//用于清空FIFO ！！关键！！不然会出现意想不到的后果！！！大家记住！！ 
	   CSN=1;		 
     }
    //NRFWriteReg(W_REGISTER+STATUS,0xff); //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标	  
} 