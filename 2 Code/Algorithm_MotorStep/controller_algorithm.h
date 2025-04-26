#ifndef __controller_algorithm_H_
#define __controller_algorithm_H_
/*包含头文件*/
#include "step_motor.h"
#include <math.h>
#include <stdlib.h>
#include "usart.h"

/*位定义*/

/*变量声明*/
//定义梯形速度参数结构体
typedef struct {
    int32_t total_steps;    // 总步数（方向由正负号表示）
    float max_rpm;          // 最大转速
    float accel_rpm;        // 加速度（RPM/步）
    uint16_t accel_steps;   // 加速阶段总步数
    uint16_t cruise_steps;  // 匀速阶段步数
    uint16_t decel_steps;   // 减速阶段步数
    Motor_DirTypeDef dir;   // 方向
} TrapezoidProfile;
//定义S曲线速度参数结构体
typedef struct {
    int32_t total_steps;    // 总步数（方向由正负号表示）
    float max_rpm;          // 最大转速
    float accel_rpm;        // 加速度（RPM/步）
    uint16_t accel_steps;   // 加速阶段总步数
    uint16_t cruise_steps;  // 匀速阶段步数
    uint16_t decel_steps;   // 减速阶段步数
    Motor_DirTypeDef dir;   // 方向
    float current_rpm;      // 当前转速
} SCurveProfile;
/*函数声明*/
void Trapezoid_Calculate(TrapezoidProfile* profile) ;
void StepMotor_TrapezoidMove(TrapezoidProfile* profile) ;
void S_Curve_Caculation( float target_RPM);
#endif
