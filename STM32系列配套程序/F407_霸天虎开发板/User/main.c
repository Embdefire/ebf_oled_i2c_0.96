/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   OLED����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./systick/bsp_SysTick.h"
#include "OLED_I2C.h"
#include "./led/bsp_led.h"

extern const unsigned char BMP1[];

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
	
int main(void)
{
	unsigned char i;
	
	/*��ʼ��LED������*/
  LED_GPIO_Config();
	Debug_USART_Config(); 
	LED_BLUE;
	  
  printf("\r\n ��ӭʹ��Ұ��  STM32 F407 ������  �\\r\n");		 

	printf("\r\n ����һ��I2C����OLED�������̣� \r\n");
  
	SysTick_Init();   //��ʼ���ӳٺ���
	I2C_Configuration();//����CPU��Ӳ��I2C
	OLED_Init();    //��ʼ��OLED
	
	printf("\r\n OLED��ʼ���ɹ�,OLED���ڹ����� \r\n");
	
	while(1)
	{
		OLED_Fill(0xFF);//ȫ������
		Delay_s(2);		// 2s
		
		OLED_Fill(0x00);//ȫ����
		Delay_s(2);		// 2s
		
		LED_GREEN;
		for(i=0;i<4;i++)
		{
			OLED_ShowCN(22+i*16,0,i);									//������ʾ����
		}
		Delay_s(2);		// 2s
		OLED_ShowStr(0,3,(unsigned char*)"Wildfire Tech",1);				//����6*8�ַ�
		OLED_ShowStr(0,4,(unsigned char*)"Hello wildfire",2);				//����8*16�ַ�
		Delay_s(200);		// 2*100=200s
		OLED_CLS();//����
		OLED_OFF();//����OLED����
		Delay_s(2);		// 2s
		OLED_ON();//����OLED���ߺ���
		OLED_DrawBMP(0,0,128,8,(unsigned char *)BMP1);//����BMPλͼ��ʾ
		Delay_s(200);		// 2*100=200s
	} 

}


/*********************************************END OF FILE**********************/

