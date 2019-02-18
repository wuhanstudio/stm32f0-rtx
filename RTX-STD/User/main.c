/***************************************************************************//**
  * @file    main.c
  * @author  �����
  * @version V1.0.0
  * @date    2012��8��16��
  * @brief   ������
  ******************************************************************************
  @verbatim
  ������
  ���������
  ����������ַ��http://hi.baidu.com/wuguoyana/home
  @endverbatim
  * @attention
  *
  * ֣��������
  * ���ļ�ֻ�����ṩ�����ο����������ļ����������κ�������ף��ҸŲ�����
  *
  * <h2><center> &copy; COPYRIGHT 2011 wuguoyana </center></h2>
*******************************************************************************/

/* ������ͷ�ļ�---------------------------------------------------------------*/
#include <RTL.h>
#include "stm32f0xx.h"

/* ˽�����Ͷ���---------------------------------------------------------------*/
/* ˽�ж��� ------------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
#define LED3            GPIO_Pin_4
#define LED4            GPIO_Pin_8

#define LED_PORT        GPIOA
#define LED_GPIO_CLK    RCC_AHBPeriph_GPIOA

/* ˽�б��� ------------------------------------------------------------------*/
OS_TID t_led1;                         /* assigned task id of task: ledOn   */
OS_TID t_led2;                        /* assigned task id of task: ledOff  */
/* ˽�к��� ------------------------------------------------------------------*/
void LED_Configuration(void);

/* ����ϵͳ���� --------------------------------------------------------------*/
__task void LED1 (void);
__task void LED2 (void);
__task void init (void);

/***************************************************************************//**
  * @brief  ��������Ӳ����ʼ����ʵ��LED1-LED4��˸
  * @note   ��
  * @param  ��
  * @retval ��
*******************************************************************************/
int main(void)
{
    os_sys_init (init);   //��ʼ��RTX����ϵͳ����������ϵͳ
    while (1)
    {
    }
}


/***************************************************************************//**
  * @brief  LED1_Task��ʵ��LED3 1s��˸
  * @note   ��
  * @param  ��
  * @retval ��
*******************************************************************************/
__task void LED1_Task (void) 
{
    for (;;) 
    {
        GPIO_SetBits(LED_PORT,LED3);  //����LED1                                  
        os_dly_wait (500);            //��ʱ0.5s 
        GPIO_ResetBits(LED_PORT,LED3);//Ϩ��LED1
        os_dly_wait (500);            
    }
}

/***************************************************************************//**
  * @brief  LED2_Task��ʵ��LED4 0.4s��˸
  * @note   ��
  * @param  ��
  * @retval ��
*******************************************************************************/
__task void LED2_Task (void) 
{
    for (;;) 
    {
        GPIO_SetBits(LED_PORT,LED4);  //����LED1                                  
        os_dly_wait (200);            //��ʱ0.2s
        GPIO_ResetBits(LED_PORT,LED4);//Ϩ��LED1
        os_dly_wait (200);  
    }
}

/***************************************************************************//**
  * @brief  init�������ʼ������
  * @note   ��
  * @param  ��
  * @retval ��
*******************************************************************************/
__task void init (void) 
{

    LED_Configuration();                      /* Initialize LEDs                  */

    t_led1  = os_tsk_create (LED1_Task, 0);   /* start task 'ledOn'               */
    t_led2 = os_tsk_create  (LED2_Task, 0);   /* start task 'ledOff'              */
    os_tsk_delete_self ();
}

/***************************************************************************//**
  * @brief  ����ʹ��LED
  * @note   LED��صĶ�����Ҫ���������ú궨�����޸�
  * @param  ��
  * @retval ��
*******************************************************************************/
void LED_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    //ʹ��LED����GPIO��ʱ��
    RCC_AHBPeriphClockCmd(LED_GPIO_CLK, ENABLE);

    //��ʼ��LED��GPIO
    GPIO_InitStructure.GPIO_Pin = LED3 | LED4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);

    GPIO_ResetBits(LED_PORT,LED3 | LED4);  //Ϩ��LED3-4
}


#ifdef  USE_FULL_ASSERT
/***************************************************************************//**
  * @brief  �����ڼ�������������ʱ��Դ�ļ����ʹ�������
  * @param  file: ָ������ļ���Դ�ļ���
  * @param  line: �����Դ������������
  * @retval ��
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
    /* �û����������Լ��Ĵ������ڱ��������ļ�������������,
       ���磺printf("�������ֵ: �ļ��� %s �� %d��\r\n", file, line) */

    /* ��ѭ�� */
    while (1)
    {
    }
}
#endif

/******************* (C) COPYRIGHT wuguoyana ***************�ļ�����***********/
