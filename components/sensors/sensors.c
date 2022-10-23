#include "sensors.h"
#include "mpu6050.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void run_all_sensor()
{
    static uint32_t clock = 0;
    //gyro_process(clock);
    //acc_process();
}


void sensors_init()
{
    mpu6050_init();

    xTaskCreatePinnedToCore(run_all_sensor, "run_all_sensor", 4096, NULL, 2, NULL, tskNO_AFFINITY);
}