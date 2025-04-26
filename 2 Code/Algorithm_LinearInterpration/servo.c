#include "servo.h"
extern void Servo_PrintWaveform(ServoController* s) ;



/*******************************************************************************************************************
* 函数功能 ：线性插值实现代码
* 参数功能 ：
* 返回值	   ：无
*******************************************************************************************************************/
//结构体数据初始化
void Servo_Init(ServoController* s, TIM_HandleTypeDef* htim, uint32_t channel) {
    s->htim = htim;
    s->channel = channel;
    s->current_angle = 0.0f;//90.0f
    s->target_angle = 90.0f;
    s->step = 0.0f;
    s->duration_ms = 1000;
}
//设定角度
void Servo_SetAngle(ServoController* s, float angle, uint32_t duration_ms) {
    s->target_angle = angle;
    s->duration_ms = duration_ms;//20ms更新一次，1000ms内更新50次，
    s->step = (s->target_angle - s->current_angle) / (duration_ms / 20.0f);// 步进值=（目标角度-当前角度）/50次=每次更新的步进值
}
//更新角度
void Servo_Update(ServoController* s) {
    if(fabs(s->current_angle - s->target_angle) > 0.1f) {
        s->current_angle += s->step;
        uint16_t pulse = (uint16_t)(1500 + s->current_angle * (Cnt_Period / TOTAL_ANGLE));
        __HAL_TIM_SET_COMPARE(s->htim, s->channel, pulse);
        
        //Servo_PrintWaveform(s); // 新增波形打印
    }
}
/*******************************************************************************************************************
* 函数功能 ：缓动函数实现（Quadratic Ease-In-Out）
* 参数功能 ：
* 返回值	   ：无
*******************************************************************************************************************/
// 二次函数曲线——机械臂运动曲线一般拟合抛物线
float easeInOutQuad(float t) {
    return t < 0.5 ? 2 * t * t : 1 - pow(-2 * t + 2, 2) / 2;// 0.5是中点，t<0.5时加速，t>0.5时减速
}
//平滑移动函数， 通过缓动函数实现平滑移动
void Servo_SmoothMove(ServoController* s, float start, float end, uint32_t duration) {
    uint32_t start_time = HAL_GetTick();// 获取当前时间
    uint32_t elapsed = 0;// 过去的时间
    
    while(elapsed < duration) { 
        elapsed = HAL_GetTick() - start_time;           // 计算经过的时间
        float progress = (float)elapsed / duration;     // 计算进度=已用/总用
        float eased = easeInOutQuad(progress);          // 计算缓动值
        float current = start + (end - start) * eased;  // 计算当前值=起始值+步进值*缓动值
        
        uint16_t pulse = (uint16_t)(1500 + current * (2000 / 180.0f));   // 计算脉冲宽度=500+当前值*比例→500是TIM初始脉冲宽度？？，2000是最大脉冲宽度
        __HAL_TIM_SET_COMPARE(s->htim, s->channel, pulse);// 设置PWM脉冲宽度
        
        //Servo_PrintWaveform(s); // 新增波形打印
        
        HAL_Delay(20); // 配合50Hz更新频率
    }
}
