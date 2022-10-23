#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "esp_err.h"
#include "sensors.h"

#define mainDELAY_LOOP_COUNT 100
#define SPIN_TASK_PRIO      2
void task_1()
{
    const char* task_name = "task_1";
    volatile uint32_t ul;
    while(1)
    {
        TickType_t xLastWakeTime;
        xLastWakeTime = xTaskGetTickCount();
        printf("%s\n", task_name);
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
    }
}

void task_2()
{
    const char* task_name = "task_2";
    volatile uint32_t ul;
    while(1)
    {
        TickType_t xLastWakeTime;
        xLastWakeTime = xTaskGetTickCount();
        printf("%s\n", task_name);
        xTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
    }
}

QueueHandle_t xQueue;
void task_send_queue()
{
    uint32_t send_value = 0;
    BaseType_t status;
    while(1)
    {
        TickType_t xLastWakeTime;
        xLastWakeTime = xTaskGetTickCount();
        send_value++;
        status = xQueueSend(xQueue, &send_value, 0);
        if(status != pdPASS)
        {
            printf("queue is full\n");
        }
        xTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
    }
}

void task_recv_queue()
{
    uint32_t recv_value = 0;
    BaseType_t status;
    while(1)
    {
        TickType_t xLastWakeTime;
        xLastWakeTime = xTaskGetTickCount();
        status = xQueueReceive(xQueue, &recv_value, pdMS_TO_TICKS(2000));
        if(status == pdPASS)
        {
            printf("recv_value = %ld\n", recv_value);
        }
        else
        {
            printf("time out\n");
        }
        xTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
    }
}


void app_main(void)
{
    sensors_init();

    xQueue = xQueueCreate(10, sizeof(uint32_t));
    //xTaskCreatePinnedToCore(task_1, "TASK1", 4096, NULL, SPIN_TASK_PRIO, NULL, tskNO_AFFINITY);
    //xTaskCreatePinnedToCore(task_2, "TASK2", 4096, NULL, SPIN_TASK_PRIO, NULL, tskNO_AFFINITY);
    //xTaskCreatePinnedToCore(task_recv_queue, "send_task", 4096, NULL, SPIN_TASK_PRIO, NULL, tskNO_AFFINITY);
    //xTaskCreatePinnedToCore(task_send_queue, "recv_task", 4096, NULL, SPIN_TASK_PRIO, NULL, tskNO_AFFINITY);
}
