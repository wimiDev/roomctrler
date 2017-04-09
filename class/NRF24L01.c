#include"NRF24L01.h"
//#include"reg52.h"
//#include"Allhead.h"
//sbit CE=P1^2;  //RX/TXģʽѡ���
//sbit IRQ=P1^3; //�������ж϶�
//sbit CSN=P1^4; //SPIƬѡ��//����SS
//sbit MOSI=P1^5;	//SPI��������ӻ������
//sbit MISO=P1^6;	//SPI��������ӻ������
//sbit SCLK=P1^7;	//SPIʱ�Ӷ�
  sbit IRQ = P4^7;
  sbit CE =  P1^4;
  sbit CSN=  P1^0;
  sbit SCLK=  P1^3;
  sbit MOSI= P1^1;
  sbit MISO= P1^2;
unsigned char RevTempDate0[5];//ͬ��0��������

unsigned char code RxAddr0[]={0x34,0x43,0x10,0x10,0x01};//���3���յ�ַ�����ַ�ͷ��ͷ���ַһ��!
//unsigned char code RxAddr1[]={0xc2,0xc2,0xc2,0xc2,0xd1};//���2
//unsigned char code RxAddr2[]={0xc2,0xc2,0xc2,0xc2,0xc1};//���1
/*****************״̬��־*****************************************/
unsigned char  bdata sta;   //״̬��־
sbit RX_DR=sta^6;
sbit TX_DS=sta^5;
sbit MAX_RT=sta^4;
/*****************SPIʱ����******************************************/
unsigned char NRFSPI(unsigned char date)
{
    unsigned char i;
   	for(i=0;i<8;i++)          // ѭ��8��
   	{
	  if(date&0x80)
	    MOSI=1;
	  else
	    MOSI=0;   // byte���λ�����MOSI
   	  date<<=1;             // ��һλ��λ�����λ
   	  SCLK=1; 
	  if(MISO)               // ����SCK��nRF24L01��MOSI����1λ���ݣ�ͬʱ��MISO���1λ����
   	    date|=0x01;       	// ��MISO��byte���λ
   	  SCLK=0;            	// SCK�õ�
   	}
    return(date);           	// ���ض�����һ�ֽ�
}
/**********************NRF24L01��ʼ������*******************************/
void NRF24L01Int()
{
	NRFDelay(2);//��ϵͳʲô������
	CE=0;
	CSN=1;  
	SCLK=0;
	IRQ=1; 
}
/*****************SPI���Ĵ���һ�ֽں���*********************************/
unsigned char NRFReadReg(unsigned char RegAddr)
{
   unsigned char BackDate;
   CSN=0;//����ʱ��
   NRFSPI(RegAddr);//д�Ĵ�����ַ
   BackDate=NRFSPI(0x00);//д����Ĵ���ָ��  
   CSN=1;
   return(BackDate); //����״̬
}
/*****************SPIд�Ĵ���һ�ֽں���*********************************/
unsigned char NRFWriteReg(unsigned char RegAddr,unsigned char date)
{
   unsigned char BackDate;
   CSN=0;//����ʱ��
   BackDate=NRFSPI(RegAddr);//д���ַ
   NRFSPI(date);//д��ֵ
   CSN=1;  
   return(BackDate);
}
/*****************SPI��ȡRXFIFO�Ĵ�����ֵ********************************/
unsigned char NRFReadRxDate(unsigned char RegAddr,unsigned char *RxDate,unsigned char DateLen)
{  //�Ĵ�����ַ//��ȡ���ݴ�ű���//��ȡ���ݳ���//���ڽ���
    unsigned char BackDate,i;
	CSN=0;//����ʱ��
	BackDate=NRFSPI(RegAddr);//д��Ҫ��ȡ�ļĴ�����ַ
	for(i=0;i<DateLen;i++) //��ȡ����
	  {
	     RxDate[i]=NRFSPI(0);
	  } 
    CSN=1;
   return(BackDate); 
}
/*****************SPIд��TXFIFO�Ĵ�����ֵ**********************************/
unsigned char NRFWriteTxDate(unsigned char RegAddr,unsigned char *TxDate,unsigned char DateLen)
{ //�Ĵ�����ַ//д�����ݴ�ű���//��ȡ���ݳ���//���ڷ���
   unsigned char BackDate,i;
   CSN=0;
   BackDate=NRFSPI(RegAddr);//д��Ҫд��Ĵ����ĵ�ַ
   for(i=0;i<DateLen;i++)//д������
     {
	    NRFSPI(*TxDate++);
	 }   
   CSN=1;
   return(BackDate);
}
/*****************NRF����Ϊ����ģʽ����������******************************/
void NRFSetTxMode(unsigned char *TxDate)
{  //����ģʽ 
    CE=0;   
   	NRFWriteTxDate(W_REGISTER+TX_ADDR,RxAddr0,TX_ADDR_WITDH);//д�Ĵ���ָ��+P0��ַʹ��ָ��+���͵�ַ+��ַ���
	NRFWriteTxDate(W_TX_PAYLOAD,TxDate,TX_DATA_WITDH);//д������ 
	/******�����йؼĴ�������**************/
  	NRFWriteReg(W_REGISTER+EN_AA,0x01);       // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x01);   // ʹ�ܽ���ͨ��0
  	NRFWriteReg(W_REGISTER+SETUP_RETR,0x0a);  // �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10��
  	NRFWriteReg(W_REGISTER+RF_CH,0x40);         // ѡ����Ƶͨ��0x40
  	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);    // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
  	NRFWriteReg(W_REGISTER+CONFIG,0x0e);      // CRCʹ�ܣ�16λCRCУ�飬�ϵ�	
	CE=1;	
	NRFDelay(5);//����10us������
} 
/*****************NRF����Ϊ����ģʽ����������******************************/
//����ģʽ
void NRFSetRXMode()
{
    CE=0;
  	NRFWriteTxDate(W_REGISTER+RX_ADDR_P0,RxAddr0,TX_ADDR_WITDH);  // �����豸����ͨ��0ʹ�úͷ����豸��ͬ�ķ��͵�ַ
//	NRFWriteTxDate(W_REGISTER+RX_ADDR_P1,RxAddr1,TX_ADDR_WITDH);  // �����豸����ͨ��1ʹ�úͷ����豸��ͬ�ķ��͵�ַ
//  	NRFWriteTxDate(W_REGISTER+RX_ADDR_P2,RxAddr2,TX_ADDR_WITDH);  // �����豸����ͨ��2ʹ�úͷ����豸��ͬ�ķ��͵�ַ

	NRFWriteReg(W_REGISTER+EN_AA,0x03);               // ʹ������ͨ��0��1�Զ�Ӧ��
  	NRFWriteReg(W_REGISTER+EN_RXADDR,0x03);           // ʹ�ܽ���ͨ��0��1
             
  	NRFWriteReg(W_REGISTER+RX_PW_P0,TX_DATA_WITDH);  // ����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ��
	NRFWriteReg(W_REGISTER+RX_PW_P1,TX_DATA_WITDH);  // ����ͨ��1ѡ��ͷ���ͨ����ͬ��Ч���ݿ��
  	NRFWriteReg(W_REGISTER+RX_PW_P2,TX_DATA_WITDH);  // ����ͨ��2ѡ��ͷ���ͨ����ͬ��Ч���ݿ��

	NRFWriteReg(W_REGISTER+RF_CH,0x40);// ѡ����Ƶͨ��0x40 
	NRFWriteReg(W_REGISTER+RF_SETUP,0x07);            // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
	NRFWriteReg(W_REGISTER+CONFIG,0x0f);             // CRCʹ�ܣ�16λCRCУ�飬�ϵ磬����ģʽ     
  	CE = 1; 
	NRFDelay(5);    
}
/****************************����Ƿ��н��յ�����******************************/
void CheckACK()
{  //���ڷ���ģʽ����Ӧ���ź�
	sta=NRFReadReg(R_REGISTER+STATUS);                    // ����״̬�Ĵ���
	if(TX_DS)
	   NRFWriteReg(W_REGISTER+STATUS,0xff);  // ���TX_DS��MAX_RT�жϱ�־
}
/*************************��������*********************************************/
void GetDate()				 
{
	char i = 0;
    unsigned char RX_P_NO;//����ͨ����
	sta=NRFReadReg(R_REGISTER+STATUS);//�������ݺ��ȡ״̬�Ĵ���
    if(RX_DR)				// �ж��Ƿ���յ�����
     {
	   RX_P_NO=sta&0x0e;//��ȡͨ����
	   CE=0;//���� 
	   switch(RX_P_NO)
	    {
		   case 0x00:NRFReadRxDate(R_RX_PAYLOAD,RevTempDate0,RX_DATA_WITDH);break;// ��RXFIFO��ȡ����ͨ��0
//		   case 0x02:NRFReadRxDate(R_RX_PAYLOAD,RevTempDate1,RX_DATA_WITDH);break;// ��RXFIFO��ȡ����ͨ��1
//		   case 0x04:NRFReadRxDate(R_RX_PAYLOAD,RevTempDate2,RX_DATA_WITDH);break;// ��RXFIFO��ȡ����ͨ��2
		   default:break;
		}
	   NRFWriteReg(W_REGISTER+STATUS,0xff); //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�
	   CSN=0;
	   NRFSPI(FLUSH_RX);//�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס���� 
	   CSN=1;		 
     }
    //NRFWriteReg(W_REGISTER+STATUS,0xff); //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�	  
} 