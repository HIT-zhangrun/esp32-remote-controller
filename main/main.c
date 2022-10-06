#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_err.h"

#define mainDELAY_LOOP_COUNT 100
#define SPIN_TASK_PRIO      2
void task_1()
{
    const char* task_name = "task_1";
    volatile uint32_t ul;
    while(1)
    {
        printf("%s\n", task_name);
        for(ul = 0; ul < mainDELAY_LOOP_COUNT; ul++)
        {
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void task_2()
{
    const char* task_name = "task_2";
    volatile uint32_t ul;
    while(1)
    {
        printf("%s\n", task_name);
        for(ul = 0; ul < mainDELAY_LOOP_COUNT; ul++)
        {
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void app_main(void)
{
    xTaskCreatePinnedToCore(task_1, "TASK1", 4096, NULL, SPIN_TASK_PRIO, NULL, tskNO_AFFINITY);
    xTaskCreatePinnedToCore(task_2, "TASK2", 4096, NULL, SPIN_TASK_PRIO, NULL, tskNO_AFFINITY);
}
