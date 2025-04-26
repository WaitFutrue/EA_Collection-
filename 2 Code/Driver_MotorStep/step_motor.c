#include "step_motor.h"
//基本操作函数设计

/********************************************************************
   * @brief  : //设置方向函数：根据传入参数将方向控制引脚设置为相应电平。
   * @param  :
   * @retval :
*********************************************************************/
void StepMotor_SetDirection(Motor_DirTypeDef dir) {
    if (dir == MOTOR_DIR_CW)         MOTOR_DIR_UP;
    else                             MOTOR_DIR_DOWN;
}
/********************************************************************
   * @brief  : //设置速度函数：转速RPM= 60 * f_PWM / K,其中K为步进电机每转一圈所需的脉冲数
   * @param  :
   * @retval :
*********************************************************************/
void StepMotor_SetSpeed(float RPM) {
    //__HAL_TIM_SET_AUTORELOAD(&htim2, 1000000 * 60/RPM / MOTOR_MicroStep - 1);//MicroStep为细分对应的总脉冲数，eg6400
    //若想优化可改为
    __HAL_TIM_SET_AUTORELOAD(&htim2, (uint16_t)(9375.0/RPM - 1.0));
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,(uint16_t)( ( 9375.0/RPM - 1.0) / 2.0));  // 保持占空比 50%
    __HAL_TIM_SET_COUNTER(&htim2, 0); //重置计数器，以确保修改立即生效。
}
void StepMotor_SetPWMFreq(uint32_t targetFreq)
{
    uint32_t newARR = 72000000 / 72 / targetFreq - 1;

    __HAL_TIM_SET_AUTORELOAD(&htim2, newARR);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, newARR / 2);  // 保持占空比 50%
    __HAL_TIM_SET_COUNTER(&htim2, 0);  // 重置计数器
}
/********************************************************************
   * @brief  : //单步函数：实现单次步进操作，即产生一个脉冲，然后更新当前位置。
   * @param  :
   * @retval :
*********************************************************************/
 uint16_t Pulse_exp_Cnt = 0; //预期产生的脉冲数
void StepMotor_SetStep(uint16_t step) {
   if (step)
   {
      /*开启定时器更新中断*/
		HAL_TIM_Base_Start_IT(&htim2);
		/*开始输出PWM*/
		HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
		Pulse_exp_Cnt=step; 
   }
   else
      HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);//关闭PWM
  
}
/********************************************************************
   * @brief  : //将上面三个函数整合到一个函数中，便于调用
   * @param  :
   * @retval :但是不可用于for循环
*********************************************************************/
void StepMotor_Config(Motor_DirTypeDef dir, float RPM, uint16_t step_target) {
    StepMotor_SetDirection(dir);
    StepMotor_SetSpeed(RPM);
    StepMotor_SetStep(step_target);
}

/********************************************************************
   * @brief  : //初始化函数→配置方向，打开PWM,
   * @param  :
   * @retval :
*********************************************************************/
void StepMotor_Init()
{

}
