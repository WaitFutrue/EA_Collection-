#ifndef __SERVO_H_
#define __SERVO_H_
/*包含头文件*/
#include "tim.h"
#include "math.h"
#include "usart.h"
#include <stdio.h>
/*位定义*/
#define TOTAL_ANGLE 180.0f
#define Cnt_Period  20000 //20 ms

/*变量声明*/
// 舵机控制结构体
typedef struct {
    TIM_HandleTypeDef* htim;
    uint32_t channel;
    float current_angle;
    float target_angle;
    float step;
    uint32_t duration_ms;
} ServoController;
/*函数声明*/
void Servo_Init(ServoController* s, TIM_HandleTypeDef* htim, uint32_t channel) ;
void Servo_SetAngle(ServoController* s, float angle, uint32_t duration_ms) ;
void Servo_Update(ServoController* s) ;
float easeInOutQuad(float t) ;
void Servo_SmoothMove(ServoController* s, float start, float end, uint32_t duration) ;
void servo_control(ServoController* s, float angle, uint32_t duration) ;
#endif
