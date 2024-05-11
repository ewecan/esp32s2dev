#include "main.h"

//任务管理器
void taskmanager(void *argument)
{
  Soft_Init();
  while (1)
  {
    delay(1);
  }
}

void FREERTOS_Init(void)
{
  Hart_Init();
  //创建任务
  xTaskCreate(
      taskmanager,   //任务函数
      "taskmanager", //任务名称
      1024 * 25,     //任务堆栈大小
      NULL,          //任务参数
      1,             //任务优先级
      NULL           //任务句柄
  );
}

void setup()
{
  FREERTOS_Init();
}

void loop()
{
  delay(1000);
}
