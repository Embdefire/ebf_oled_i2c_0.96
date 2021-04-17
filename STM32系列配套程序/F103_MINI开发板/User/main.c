/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   OLED测试（软件模拟I2C）
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-MINI STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "bsp_i2c_gpio.h"
#include "./usart/bsp_usart.h"
#include "./led/bsp_led.h" 
#include "OLED_I2C.h"
#include "./systick/bsp_SysTick.h"


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
	  LED_GPIO_Config();     /* LED初始化 */
		USART_Config();        /* 串口初始化 */
	
	  SysTick_Init();        /*初始化延迟函数*/
		i2c_CfgGpio();				 /*I2C总线的GPIO初始化*/
	  OLED_Init();					 /* OLED初始化 */

	printf("\r\n 欢迎使用野火 F103-MINI STM32 开发板\r\n");		
	printf("\r\n OLED软件模拟i2c测试例程 \r\n");		
	
	  /*OLED检测测试*/
	  if(OLED_Test()==0)
		{          
			/* 没有检测到EEPROM */
			printf("\r\n 没有检测到OLED！\r\n");
			LED1_ON;//D4亮	
		}
		else
		{
			printf("\r\n OLED检测成功,OLED正在工作！\r\n");
			LED2_ON;//D5亮
		}
		
		while(1)
	{
		OLED_Fill(0xFF);//全屏点亮
		Delay_s(2);
		
		OLED_Fill(0x00);//全屏灭
		Delay_s(2);
		
		for(i=0;i<4;i++)
		{
			OLED_ShowCN(22+i*16,0,i);									//测试显示中文
		}
		Delay_s(2);
		OLED_ShowStr(0,3,(unsigned char*)"Wildfire Tech",1);				//测试6*8字符
		OLED_ShowStr(0,4,(unsigned char*)"Hello wildfire",2);				//测试8*16字符
		Delay_s(200);
		OLED_CLS();//清屏
		OLED_OFF();//测试OLED休眠
		Delay_s(2);
		OLED_ON();//测试OLED休眠后唤醒
		OLED_DrawBMP(0,0,128,8,(unsigned char *)BMP1);//测试BMP位图显示
		Delay_s(20);
	}
}
/*********************************************END OF FILE**********************/
