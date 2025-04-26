#ifndef __STEP_MOTOR_H_
#define __STEP_MOTOR_H_
/*包含头文件*/
#include "gpio.h"
#include "tim.h"
/*位定义*/
#define GPIO_MOTOR_EN GPIOA
#define PIN_MOTOR_EN GPIO_PIN_11    //步进电机使能

#define GPIO_MOTOR_DIR GPIOA
#define PIN_MOTOR_DIR GPIO_PIN_11    //步进电机方向

#define GPIO_MOTOR_PUL GPIOA
#define PIN_MOTOR_PUL GPIO_PIN_0    //步进电机脉冲

/*宏定义*/
#define MOTOR_DIR_UP     HAL_GPIO_WritePin(GPIO_MOTOR_DIR,PIN_MOTOR_DIR,GPIO_PIN_SET)   //正转
#define MOTOR_DIR_DOWN   HAL_GPIO_WritePin(GPIO_MOTOR_DIR,PIN_MOTOR_DIR,GPIO_PIN_RESET)   //反转_共阴极结法——逆时针

#define MOTOR_EN         HAL_GPIO_WritePin(GPIO_MOTOR_EN,PIN_MOTOR_EN,GPIO_PIN_SET)   //使能
#define MOTOR_LOCK       HAL_GPIO_WritePin(GPIO_MOTOR_EN,PIN_MOTOR_EN,GPIO_PIN_RESET)   //失能，锁机

#define MOTOR_MicroStep 32*200 //32细分，6400
#define MOTOR_REVOLUTION 2

/*变量声明*/

//枚举常用的电机状态
typedef enum {
    MOTOR_STOP = 0, //停止
    MOTOR_RUN = 1,  //运行
} Motor_StateTypeDef;
//枚举常用的电机方向
typedef enum {
    MOTOR_DIR_CW = 0, //顺时针
    MOTOR_DIR_CCW = 1, //逆时针
} Motor_DirTypeDef;
//定义一个步进电机控制句柄（例如一个结构体），其中包含当前状态和配置参数
typedef struct {
    uint8_t motor_state; //电机状态
    uint16_t motor_speed; //电机速度
    uint16_t motor_step_target; //电机目标步数
    uint16_t motor_step_count; //电机步数计数，当前已走的步数
} StepMotor_HandleTypeDef;
/*函数声明*/
void StepMotor_SetDirection(Motor_DirTypeDef dir) ;
void StepMotor_SetSpeed( float RPM) ;
void StepMotor_SetStep(uint16_t step) ;
void StepMotor_Config( Motor_DirTypeDef dir, float RPM, uint16_t step);
void test_accl( float RPM,uint16_t step_target,float accl);
#endif
