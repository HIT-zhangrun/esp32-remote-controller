#ifndef __MPU6050_H__
#define __MPU6050_H__

#include <stdint.h>

#define MPU6050ADDR                 0x68

#define MPU6050_RA_SMPLRT_DIV       0x19
#define MPU6050_RA_CONFIG           0x1A
#define MPU6050_RA_GYRO_CONFIG      0x1B
#define MPU6050_RA_ACCEL_CONFIG     0x1C

#define MPU6050_RA_INT_PIN_CFG      0x37
#define MPU6050_RA_INT_ENABLE       0x38

#define MPU6050_RA_ACCEL_XOUT_H     0x3B
#define MPU6050_RA_ACCEL_XOUT_L     0x3C
#define MPU6050_RA_ACCEL_YOUT_H     0x3D
#define MPU6050_RA_ACCEL_YOUT_L     0x3E
#define MPU6050_RA_ACCEL_ZOUT_H     0x3F
#define MPU6050_RA_ACCEL_ZOUT_L     0x40
#define MPU6050_RA_TEMP_OUT_H       0x41
#define MPU6050_RA_TEMP_OUT_L       0x42
#define MPU6050_RA_GYRO_XOUT_H      0x43
#define MPU6050_RA_GYRO_XOUT_L      0x44
#define MPU6050_RA_GYRO_YOUT_H      0x45
#define MPU6050_RA_GYRO_YOUT_L      0x46
#define MPU6050_RA_GYRO_ZOUT_H      0x47
#define MPU6050_RA_GYRO_ZOUT_L      0x48

#define MPU6050_RA_PWR_MGMT_1       0x6B
#define MPU6050_RA_PWR_MGMT_2       0x6C
#define MPU6050_RA_WHO_AM_I         0x75

enum MPU6050_PWR
{
    MPU6050_RST          = 0x80,
    MPU6050_SLEEP        = 0x40,
    MPU6050_NORMAL       = 0x00,
    MPU6050_TMP_DISABLE  = 0x08,
    MPU6050_CLK_DISABLE  = 0x07,
};

enum MPU6050_GYRO
{
    MPU6050_GYRO_250  = 0x00,
    MPU6050_GYRO_500  = 0x08,
    MPU6050_GYRO_1000 = 0x10,
    MPU6050_GYRO_2000 = 0x18,
};

enum MPU6050_ACC
{
    MPU6050_ACC_2  = 0x00,
    MPU6050_ACC_4  = 0x08,
    MPU6050_ACC_8  = 0x10,
    MPU6050_ACC_16 = 0x18,
};

enum MPU6050_DLPF_BW
{
    MPU6050_DLPF_BW_256 = 0x00,
    MPU6050_DLPF_BW_188 = 0x01,
    MPU6050_DLPF_BW_98  = 0x02,
    MPU6050_DLPF_BW_42  = 0x03,
    MPU6050_DLPF_BW_20  = 0x04,
    MPU6050_DLPF_BW_10  = 0x05,
    MPU6050_DLPF_BW_5   = 0x06,
};

uint8_t mpu6050_init(void);
#endif