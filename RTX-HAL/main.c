#include <stm32f0xx_hal_conf.h>
#include <cmsis_os.h>

void LED1 (void const *argument);

osThreadId t_led1;                         /* assigned task id of task: ledOn   */
osThreadDef(LED1, osPriorityNormal, 1, 0);  

int main (void) {
  
	osKernelInitialize ();                    // initialize CMSIS-RTOS
	
	t_led1 = osThreadCreate(osThread(LED1), NULL);
	
	osKernelStart ();                         // start thread execution 
}

void LED1 (void const *argument) 
{
		GPIO_InitTypeDef GPIO_InitStructure;
	/* GPIOA Periph clock enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	/* Configure PA0 and PA1 in output pushpull mode */
	GPIO_InitStructure.Pin = GPIO_PIN_4;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	while (1) 
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
		osDelay(500); 
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_RESET);
		osDelay(500); 
	}
}
