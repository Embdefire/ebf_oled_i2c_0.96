/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   OLED测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F407 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
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
  * @brief  主函数
  * @param  无
  * @retval 无
  */
	
int main(void)
{
	unsigned char i;
	
	/*初始化LED、串口*/
  LED_GPIO_Config();
	Debug_USART_Config(); 
	LED_BLUE;
	  
  printf("\r\n 欢迎使用野火  STM32 F407 开发板  \r\n");		 

	printf("\r\n 这是一个I2C外设OLED测试例程！ \r\n");
  
	SysTick_Init();   //初始化延迟函数
	I2C_Configuration();//配置CPU的硬件I2C
	OLED_Init();    //初始化OLED
	
	printf("\r\n OLED初始化成功,OLED正在工作！ \r\n");
	
	while(1)
	{
		OLED_Fill(0xFF);//全屏点亮
		Delay_s(2);		// 2s
		
		OLED_Fill(0x00);//全屏灭
		Delay_s(2);		// 2s
		
		LED_GREEN;
		for(i=0;i<4;i++)
		{
			OLED_ShowCN(22+i*16,0,i);									//测试显示中文
		}
		Delay_s(2);		// 2s
		OLED_ShowStr(0,3,(unsigned char*)"Wildfire Tech",1);				//测试6*8字符
		OLED_ShowStr(0,4,(unsigned char*)"Hello wildfire",2);				//测试8*16字符
		Delay_s(200);		// 2*100=200s
		OLED_CLS();//清屏
		OLED_OFF();//测试OLED休眠
		Delay_s(2);		// 2s
		OLED_ON();//测试OLED休眠后唤醒
		OLED_DrawBMP(0,0,128,8,(unsigned char *)BMP1);//测试BMP位图显示
		Delay_s(200);		// 2*100=200s
	} 

}


/*********************************************END OF FILE**********************/

