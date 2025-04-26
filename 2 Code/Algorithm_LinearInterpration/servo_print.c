// 波形打印函数
float current_angle;
float target_angle;
void Servo_PrintWaveform(ServoController* s) {
//    static uint32_t last_print = 0;
//    uint32_t now = HAL_GetTick();
//    
//    if(now - last_print >= 20) { // 每20ms采样一次
//        last_print = now;
//        float progress = (s->current_angle - s->target_angle) / (s->target_angle - s->current_angle);
//        int pulse = __HAL_TIM_GET_COMPARE(s->htim, s->channel);
//        
//        // CSV格式：当前角度,目标角度,脉冲宽度
//        printf("%u,%.1f,%.1f,%d\n", 
//               now,
//               s->current_angle,
//               s->target_angle,
//               pulse);
//    }
            current_angle=s->current_angle;
        target_angle=s->target_angle;
        printf("%.2f,%.2f\n", 
                current_angle  ,     
                target_angle        );
}