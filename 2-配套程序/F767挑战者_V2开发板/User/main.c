/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   OLED测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 767 开发板
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
#include "main.h"  
#include "stm32f7xx.h"
#include "./led/bsp_led.h" 
#include "./usart/bsp_usart.h"
#include "./oled/OLED_I2C.h"
#include "./i2c/bsp_i2c_gpio.h"
#include "./delay/core_delay.h"

extern unsigned char F16x16[];
extern const unsigned char F6x8[][6];
extern const unsigned char F8X16[];
extern unsigned char BMP1[];


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
    uint8_t i;   
    /* 配置系统时钟为216 MHz */
    SystemClock_Config();

    /* 初始化RGB彩灯 */
    LED_GPIO_Config();

    /* 初始化USART1 配置模式为 115200 8-N-1 */
    UARTx_Config();
	
		i2c_CfgGpio();//配置软件I2C
		
		OLED_Init();    //初始化OLED
		
		printf("\r\n OLED初始化成功,OLED正在工作！ \r\n");
		
		while(1)
		{
			OLED_Fill(0xFF);//全屏点亮
			HAL_Delay(2000);		// 2s
			
			OLED_Fill(0x00);//全屏灭
			HAL_Delay(2000);		// 2s
			
			LED_GREEN;
			for(i=0;i<4;i++)
			{
				OLED_ShowCN(22+i*16,0,i);									//测试显示中文
			}
			HAL_Delay(2000);		// 2s
			OLED_ShowStr(0,3,(unsigned char*)"Wildfire Tech",1);				//测试6*8字符
			OLED_ShowStr(0,4,(unsigned char*)"Hello wildfire",2);				//测试8*16字符
			HAL_Delay(2000);		// 2*100=200s
			OLED_CLS();//清屏
			OLED_OFF();//测试OLED休眠
			HAL_Delay(2000);		// 2s
			OLED_ON();//测试OLED休眠后唤醒
			OLED_DrawBMP(0,0,128,8,(unsigned char *)BMP1);//测试BMP位图显示
			CPU_TS_Tmr_Delay_S(10);	// 10s
		} 
}



/**
  * @brief  System Clock 配置
  *         system Clock 配置如下 : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  无
  * @retval 无
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* 使能HSE，配置HSE为PLL的时钟源，配置PLL的各种分频因子M N P Q 
	 * PLLCLK = HSE/M*N/P = 25M / 25 *432 / 2 = 216M
	 */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* 激活 OverDrive 模式以达到216M频率  */  
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* 选择PLLCLK作为SYSCLK，并配置 HCLK, PCLK1 and PCLK2 的时钟分频因子 
	 * SYSCLK = PLLCLK     = 216M
	 * HCLK   = SYSCLK / 1 = 216M
	 * PCLK2  = SYSCLK / 2 = 108M
	 * PCLK1  = SYSCLK / 4 = 54M
	 */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2; 
  
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }  
}
void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/

