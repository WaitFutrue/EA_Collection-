#include "test_step_motor.h"

/********************************************************************
   * @brief  : 听说步进电机驱动器支持100多K赫兹
   * @param  :
   * @retval :
*********************************************************************/
void test_PWM()
{
    for(int i=100;i<1600;i++)
      {
         StepMotor_SetSpeed(i ) ;
          HAL_Delay(1500);
      }
}
/********************************************************************
   * @brief  : 测试功能函数
   * @param  :
   * @retval :
*********************************************************************/
void test_Fuction()
{
 StepMotor_SetDirection(MOTOR_DIR_CW ) ;
 StepMotor_SetSpeed(10) ;
 StepMotor_SetStep(10) ;
}

void test_OK()//执行时取消注释
{
//  //关键，启动TIM
//		/*开启定时器更新中断*/
//		HAL_TIM_Base_Start_IT(&htim2);
//		/*开始输出PWM*/
//		HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
////    // 初始化梯形参数
//    TrapezoidProfile profile = {
//        .total_steps = 6400/10,      // 移动1000步
//        .max_rpm = 6400/100,           // 最大转速300RPM
//        .accel_rpm = 0.5           // 加速度30RPM/步
//    };//目前最合适的参数640，64，0.5
//    //确定方向
//    StepMotor_SetDirection(MOTOR_DIR_CW ) ;
//  // 计算各阶段步数
//  Trapezoid_Calculate(&profile);

//  // 执行梯形运动
//  StepMotor_TrapezoidMove(&profile);
}
