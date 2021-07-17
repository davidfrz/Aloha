/**************************************************************************************
*		              EEPROM-IICʵ��												  *
ʵ�����󣺾�����߲����뿴��Ƶ��
		  ���س��������ܺ�4λ��ʾ0����K1������ʾ�����ݣ���K2��ȡ�ϴα�������ݣ�
		  ��K3��ʾ���ݼ�һ����K4��ʾ�������㡣�����д���������255.
		  
ע���������P3.2�ڸ������߹��ã�����������ʵ��ʱΪ�˲��ú�����Ӱ��ʵ��Ч������ðѺ�������ȡ������																				  
***************************************************************************************/

#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
#include "i2c.h"	

typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;	 //���尴���˿�

char num=0;
u8 disp[4];
u8 code smgduan[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

/*******************************************************************************
* �� �� ��         : delay
* ��������		   : ��ʱ������i=1ʱ����Լ��ʱ10us
*******************************************************************************/
void delay(u16 i)
{
	while(i--);	
}


/*******************************************************************************
* ������         :Keypros()
* ��������		 :����������
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void Keypros()
{
	if(k1==0)
	{
		delay(1000);  //��������
		if(k1==0)
		{
			At24c02Write(1,num);   //�ڵ�ַ1��д������num
		}
		while(!k1);
	}
	if(k2==0)
	{
		delay(1000);  //��������
		if(k2==0)
		{
			num=At24c02Read(1);	  //��ȡEEPROM��ַ1�ڵ����ݱ�����num��
		}
		while(!k2);
	}
	if(k3==0)
	{
		delay(100);  //��������
		if(k3==0)
		{
			num++;	   //���ݼ�1
			if(num>255)num=0;
		}
		while(!k3);
	}
	if(k4==0)
	{
		delay(1000);  //��������
		if(k4==0)
		{
			num=0;		 //��������
		}
		while(!k4);
	}		
}

/*******************************************************************************
* ������         :datapros()
* ��������		 :���ݴ�����
* ����           : ��
* ���         	 : ��
*******************************************************************************/
//void datapros()
//{
//	disp[0]=smgduan[num/1000];//ǧλ
//	disp[1]=smgduan[num%1000/100];//��λ
//	disp[2]=smgduan[num%1000%100/10];//��λ
//	disp[3]=smgduan[num%1000%100%10];		
//}
//
//
///*******************************************************************************
//* ������         :DigDisplay()
//* ��������		 :�������ʾ����
//* ����           : ��
//* ���         	 : ��
//*******************************************************************************/
//void DigDisplay()
//{
//	u8 i;
//	for(i=0;i<4;i++)
//	{
//		switch(i)	 //λѡ��ѡ�����������ܣ�
//		{
//			case(0):
//				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
//			case(1):
//				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
//			case(2):
//				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
//			case(3):
//				LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ	
//		}
//		P0=disp[i];//��������
//		delay(100); //���һ��ʱ��ɨ��	
//		P0=0x00;//����
//	}		
//}

/*******************************************************************************
* �� �� ��       : main
* ��������		 : ������
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/
void main()
{	
	while(1)
	{
		Keypros();	 //����������
		datapros();	 //���ݴ�����
		DigDisplay();//�������ʾ����		
	}		
}
//  /*������������������*/
// //*************************************************************
//   ////*****************************************************���Ժ���
//
//void DebugEepromService(void)
//
//{
//
//unchar debug_buf[255];
//
//debug_buf[0]=0x91;
//
//debug_buf[1]=0x92;
//
//debug_buf[2]=0x93;
//
//debug_buf[3]=0x94;
//
//debug_buf[4]=0x95;
//
//debug_buf[250]=0x05;
//
//debug_buf[251]=0x06;
//
//debug_buf[252]=0x07;
//
//debug_buf[253]=0x08;
//
//debug_buf[254]=0x09;
//
//SeqWriteTo24c256(EEP1_ADDR,1,255,debug_buf);
//
//SeqReadFrom24c256(EEP1_ADDR,1,255,debug_buf);
//
//}
//
//
//#define IIC_SDA_PB 0x20
//
//#define IIC_SCL_PB 0x80
//
//#define IIC_DEL_WAIT 0x10 //>4.7us(12.80us) for Fre=11.0592M
//
//#define IIC_DEL_WRITE 0x2700 //>6ms(7266.54us=7.266ms) for Fre=11.0592M
//
//#define EEP1_ADDR 0xa4
//
//#define PAGE_CAP_BYTE 64 //24C256ҳд����:64�ֽ�
//
///*
//
//���ܺ����ļ�
//
//2005-9-22 9:54 by xth
//
//�汾: v1.0
//
//--------------------------------------------
//
//Mcu: mega32 Fr ency: 11.0592M
//
//--------------------------------------------
//
//���ܸ���:Eeprom�����ļ�
//
//--------------------------------------------
//
//*/
//
////=============================��������
//
////----------IIC�������ú���
//
//void IicDelayService(unint delay_time);
//
//void IicStartBitSend(void);
//
//void IicStopBitSend(void);
//
//void IicAckService(unchar ack_data);
//
//unchar IicSendByteService(unchar tx_data);
//
//unchar IicAccByteService(void);
//
////----------At24c256
//
//unchar RandWriteByteTo24c256(unchar sla_add,unint addr_op,unchar data_op);
//
//unchar WritePageTo24c256(unchar sla_add,unint addr_op,unchar *write_data_buf);
//
//unchar SeqWriteTo24c256ByPage(unchar sla_add,unint addr_op,unchar write_size,unchar *write_buf);
//
//unchar SeqWriteTo24c256(unchar sla_add,unint addr_op,unchar write_size,unchar *write_buf);
//
//unchar SeqReadFrom24c256(unchar sla_add,unint addr_op,unchar read_size,unchar *read_buf);
//
////=============================��������
//
//void IicDelayService(unint delay_count)
//
//{
//
//unint count;
//
//for(count=0;count<delay_count;count++)
//
//asm("NOP");
//
//}
//
//void IicStartBitSend(void)
//
//{
//
//PORTB |= IIC_SCL_PB; //������ʼ������ʱ���ź�
//
//asm("NOP");
//
//PORTB |= IIC_SDA_PB; //��ʼ��������ʱ�����4.7us,��ʱ
//
//IicDelayService(IIC_DEL_WAIT);
//
//PORTB &= ~IIC_SDA_PB;
//
//IicDelayService(IIC_DEL_WAIT);
//
//PORTB &= ~IIC_SCL_PB; //ǯסI2C ��׼�����ͻ��������
//
//asm("NOP");
//
//}
//
//void IicStopBitSend(void)
//
//{
//
//PORTB &= ~IIC_SDA_PB;//���ͽ���������ʱ���ź�
//
//IicDelayService(IIC_DEL_WAIT);
//
//PORTB |= IIC_SCL_PB; //������������ʱ�����4��s
//
//IicDelayService(IIC_DEL_WAIT);
//
//PORTB |= IIC_SDA_PB;
//
//asm("NOP");
//
//}
//
//void IicAckService(unchar ack_data)
//
//{//��Ϊ��������Ӧ��->��Ӧ����Ӧ���ź�
//
//if(ack_data==0) PORTB &= ~IIC_SDA_PB;
//
//else PORTB |= IIC_SDA_PB;
//
//IicDelayService(IIC_DEL_WAIT);
//
//PORTB |= IIC_SCL_PB;
//
//IicDelayService(IIC_DEL_WAIT);
//
//PORTB &= ~IIC_SCL_PB;//��ʱ���ߣ�ǯסI2C�����Ա��������
//
//asm("NOP");
//
//}
//
//unchar IicSendByteService(unchar tx_data)
//
//{//���ֽڷ��ͳ�ȥ,�����ǵ�ַ,Ҳ����������,�����ȴ�Ӧ�𲢷���
//
//unchar bit_count,ack_flag;
//
//for(bit_count=0;bit_count<8;bit_count++)
//
//{
//
//if((tx_data<<bit_count)&0x80)
//
//PORTB |= IIC_SDA_PB;
//
//else
//
//PORTB &= ~IIC_SDA_PB;
//
//IicDelayService(IIC_DEL_WAIT);
//
//PORTB |= IIC_SCL_PB; //��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ
//
//IicDelayService(IIC_DEL_WAIT); //��֤ʱ�Ӹߵ�ƽ���ڴ���4��s
//
//PORTB &= ~IIC_SCL_PB;
//
//}
//
//IicDelayService(IIC_DEL_WAIT);
//
//PORTB &= ~IIC_SDA_PB;
//
//DDRB &= ~IIC_SDA_PB; //SDA�ó�����
//
//asm("NOP");
//
//PORTB |= IIC_SCL_PB;
//
//IicDelayService(IIC_DEL_WAIT);
//
//IicDelayService(IIC_DEL_WAIT);
//
//if(PINB&IIC_SDA_PB) //�ж��Ƿ���յ�Ӧ���ź�
//
//ack_flag=NO;
//
//else
//
//ack_flag=YES; //��Ӧ���ź�
//
//DDRB |= IIC_SDA_PB;
//
//PORTB &= ~IIC_SCL_PB;
//
//asm("NOP");
//
//return(ack_flag);
//
//}
//
//unchar IicAccByteService(void)
//
//{//���մ���������������,���ж����ߴ���
//
//unchar bit_count,get_data;
//
//DDRB &= ~IIC_SDA_PB;
//
//get_data=0;
//
//for(bit_count=0;bit_count<8;bit_count++)
//
//{
//
//asm("NOP");
//
//PORTB &= ~IIC_SCL_PB; //��ʱ����Ϊ�ͣ�׼����������λ
//
//IicDelayService(IIC_DEL_WAIT); //ʱ�ӵ͵�ƽ���ڴ���4.7��s;
//
//PORTB |= IIC_SCL_PB; //��ʱ����Ϊ��ʹ��������������Ч
//
//get_data<<=1;
//
//if(PINB&IIC_SDA_PB)
//
//get_data++;
//
//asm("NOP");
//
//asm("NOP");
//
//}
//
//PORTB &= ~IIC_SCL_PB;
//
//DDRB |= IIC_SDA_PB;
//
//asm("NOP");
//
//return(get_data);
//
//}
//
//unchar RandWriteByteTo24c256(unchar sla_add,unint addr_op,unchar data_op)
//
//{
//
//unchar result_now,temp_data;
//
//IicStartBitSend(); //��ʼ����
//
//temp_data=sla_add; //��������ַ
//
//result_now=IicSendByteService(temp_data);
//
//if(result_now==NO) return(result_now);
//
//temp_data=addr_op>>8; //������Ԫ��ַ��8λ
//
//result_now=IicSendByteService(temp_data);
//
//if(result_now==NO) return(result_now);
//
//temp_data=addr_op; //������Ԫ��ַ��8λ
//
//result_now=IicSendByteService(temp_data);
//
//if(result_now==NO) return(result_now);
//
//temp_data=data_op; //��������
//
//result_now=IicSendByteService(temp_data);
//
//if(result_now==NO) return(result_now);
//
//IicStopBitSend(); //ֹͣ����
//
//IicDelayService(IIC_DEL_WRITE);
//
//result_now=YES;
//
//return(result_now);
//
//}
//
//unchar SeqReadFrom24c256(unchar sla_add,unint addr_op,unchar read_size,unchar *read_buf)
//
//{//addr ��roll over�� during read:from last byte of the last page, to the first byte of the first page
//
//unchar result_now,temp_data,read_count;
//
//IicStartBitSend(); //��ʼ����
//
//temp_data=sla_add; //��������ַ
//
//result_now=IicSendByteService(temp_data);
//
//if(result_now==NO) return(result_now);
//
//temp_data=addr_op>>8; //������Ԫ��ַ��8λ
//
//result_now=IicSendByteService(temp_data);
//
//if(result_now==NO) return(result_now);
//
//temp_data=addr_op; //������Ԫ��ַ��8λ
//
//result_now=IicSendByteService(temp_data);
//
//if(result_now==NO) return(result_now);
//
//IicStartBitSend();
//
//temp_data=sla_add+1; //������
//
//result_now=IicSendByteService(temp_data);
//
//if(result_now==NO) return(result_now);
//
//for(read_count=0;read_count<read_size-1;read_count++)
//
//{ //����������
//
//*(read_buf+read_count)=IicAccByteService();
//
//IicAckService(NO);
//
//}
//
//*(read_buf+read_count)=IicAccByteService();
//
//IicAckService(YES);
//
//IicStopBitSend();
//
//result_now=YES;
//
//return(result_now);
//
//}
//
//unchar WritePageTo24c256(unchar sla_add,unint addr_op,unchar *write_data_buf)
//
//{//ҳд
//
//unchar count,result_now,temp_data;
//
//IicStartBitSend(); //��ʼ����
//
//temp_data=sla_add; //��������ַ
//
//result_now=IicSendByteService(temp_data);
//
//if(result_now==NO) return(result_now);
//
//temp_data=addr_op>>8; //������Ԫ��ַ��8λ
//
//result_now=IicSendByteService(temp_data);
//
//if(result_now==NO) return(result_now);
//
//temp_data=addr_op; //������Ԫ��ַ��8λ
//
//result_now=IicSendByteService(temp_data);
//
//if(result_now==NO) return(result_now);
//
//for(count=0;count<PAGE_CAP_BYTE;count++)
//
//{//����д
//
//temp_data=*(write_data_buf+count);
//
//result_now=IicSendByteService(temp_data);
//
//if(result_now==NO) return(result_now);
//
//}
//
//IicStopBitSend(); //ֹͣ����
//
//IicDelayService(IIC_DEL_WRITE);
//
//result_now=YES;
//
//return(result_now);
//
//}
//
//unchar SeqWriteTo24c256ByPage(unchar sla_add,unint addr_op,unchar write_size,unchar *write_buf)
//
//{//addr ��roll over�� during write:from last byte of the current page to first byte of the same page.
//
//unint page_write,read_addr,temp_op_int;
//
//unchar data_count,result_out,modify_count,count,write_data_buf[PAGE_CAP_BYTE];
//
//result_out=YES;
//
//data_count=0;
//
//while(write_size>0)
//
//{
//
//page_write=addr_op/PAGE_CAP_BYTE; //�õ���ǰҳ
//
//read_addr=page_write*PAGE_CAP_BYTE;
//
//SeqReadFrom24c256(sla_add,read_addr,PAGE_CAP_BYTE,write_data_buf);
//
//temp_op_int=addr_op&(PAGE_CAP_BYTE-1); //�õ���ҳ�ڵ���ʼ�ֽڵ�ַ
//
//if(temp_op_int+write_size>=PAGE_CAP_BYTE)
//
//{
//
//modify_count=PAGE_CAP_BYTE;
//
//addr_op=(page_write+1)*PAGE_CAP_BYTE; //д��һҳ����ʼ��ַ
//
//}
//
//else
//
//modify_count=write_size;
//
//count=temp_op_int;
//
//write_size=write_size-modify_count+count; //д��һҳ��������
//
//for(;count<modify_count;count++,data_count++)
//
//write_data_buf[count]=*(write_buf+data_count);
//
//result_out=WritePageTo24c256(sla_add,read_addr,write_data_buf);
//
//}
//
//return(result_out);
//
//}
//
//unchar SeqWriteTo24c256(unchar sla_add,unint addr_op,unchar write_size,unchar *write_buf)
//
//{//����д(��ҳд)
//
//unchar write_result;
//
//if(write_size<3)
//
//{//���Ҫд�������С��3��,�������дʵ��
//
//write_result=RandWriteByteTo24c256(sla_add,addr_op,*write_buf);
//
//write_result=RandWriteByteTo24c256(sla_add,addr_op+1,*(write_buf+1));
//
//}
//
//else
//
//write_result=SeqWriteTo24c256ByPage(sla_add,addr_op,write_size,write_buf);
//
//return(write_result);
//
//}
//
//
