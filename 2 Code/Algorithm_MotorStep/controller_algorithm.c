#include "controller_algorithm.h"

/********************************************************************
   * @brief  : 计算加速、匀速、减速三个阶段的具体步数：
   * @param  :计算梯形参数
   * @retval :
*********************************************************************/
void Trapezoid_Calculate(TrapezoidProfile* profile) {
    // 确定运动方向
    profile->dir = (profile->total_steps > 0) ? MOTOR_DIR_CW : MOTOR_DIR_CCW;
    uint32_t steps = abs(profile->total_steps);

    // 计算理论加速/减速步数（基于加速度）
    profile->accel_steps = (uint16_t)(profile->max_rpm / profile->accel_rpm);
    profile->decel_steps = profile->accel_steps;

    // 检查总步数是否足够完成加速+减速
    if (profile->accel_steps + profile->decel_steps >= steps) {
        // 不足则重新分配
//        profile->accel_steps = steps / 2;
//        profile->decel_steps = steps - profile->accel_steps;
//        profile->cruise_steps = 0;
                profile->accel_steps = profile->decel_steps = profile->cruise_steps=steps / 3;
    } else {
        profile->cruise_steps = steps - profile->accel_steps - profile->decel_steps;
    }
}
/********************************************************************
   * @brief  : 分阶段执行运动
   * @param  :
   * @retval :
*********************************************************************/
//在加速过程中，由低于步进电机的启动频率开始启动，以固定的加速度增加速度到目标值；
//在匀速过程中，以最大速度匀速运动；
//在减速部分中，以加速度不变的速度递减到0；
void StepMotor_TrapezoidMove(TrapezoidProfile* profile) {
    //加速阶段
    for (int i = 0; i < profile->max_rpm/profile->accel_rpm; i++)
    {
        StepMotor_SetSpeed(profile->accel_rpm*i);
        HAL_Delay(1);//时间间隔，用于模拟物理运动中的dt
        printf("%.3f\n",profile->accel_rpm*i);
    }
    //匀速阶段
    for (int i = profile->max_rpm/profile->accel_rpm; i < profile->total_steps-2*profile->max_rpm/profile->accel_rpm; i++)
    {
        StepMotor_SetSpeed(profile->max_rpm);
        HAL_Delay(1);//时间间隔，用于模拟物理运动中的dt
        printf("%.3f\n",profile->max_rpm);

    }
    //匀减速阶段，与加速度对称，故可优化
    for (int i = profile->max_rpm/profile->accel_rpm; i > 0 ; i--)
    {
        StepMotor_SetSpeed(profile->accel_rpm*i);
        HAL_Delay(1);//时间间隔，用于模拟物理运动中的dt
        printf("%.3f\n",profile->accel_rpm*i);

    }
    //停止
    StepMotor_SetSpeed(0);
}


/********************************************************************
   * @brief  : 计算S曲线参数————函数拟合法
   * @param  :  
   * @retval :
*********************************************************************/
void S_Curve_Caculation( float target_RPM)
{

    for (int  i = 0; i < 20; i++)
    {
      float speed = target_RPM / (1.0 + exp(-2.0 * (i - 5)));
      StepMotor_SetSpeed(speed);
      HAL_Delay(10);
      printf("%.3f\n",speed);
        
//参数已经调好
    }
        for (int  i = 20; i > 0; i--)
    {
      float speed = target_RPM / (1.0 + exp(-2.0 * (i - 5)));
      StepMotor_SetSpeed(speed);
      HAL_Delay(10);
      printf("%.3f\n",speed);
    }
    StepMotor_SetSpeed(0 );//

}
