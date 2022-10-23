#include "mpu6050.h"
#include "driver/i2c.h"
#include "esp_log.h"

static const char *TAG = "mpu6050";

#define I2C_MASTER_SCL_IO           19      /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           18      /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000

static esp_err_t mpu6050_read(uint8_t reg_addr, uint8_t *data, size_t len)
{
    return i2c_master_write_read_device(I2C_MASTER_NUM, MPU6050ADDR, &reg_addr, 1, data, len, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
}

static esp_err_t mpu6050_write(uint8_t reg_addr, uint8_t data)
{
    esp_err_t ret;
    uint8_t write_buf[2] = {reg_addr, data};

    ret = i2c_master_write_to_device(I2C_MASTER_NUM, MPU6050ADDR, write_buf, sizeof(write_buf), I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);

    return ret;
}

uint8_t mpu6050_get_device_id(void)
{
    static uint8_t buf;
    mpu6050_read(MPU6050_RA_WHO_AM_I, &buf, sizeof(buf));
    return buf;
}

uint8_t mpu6050_is_connected(void)
{
    if(mpu6050_get_device_id() == MPU6050ADDR)
    {
        return 0;
    }
    return 1;
}

void mpu6050_acc_read(int16_t *accData)
{
    uint8_t buf[6];
    mpu6050_read(MPU6050_RA_ACCEL_XOUT_H, buf, sizeof(buf));
    accData[0] = (int16_t)((buf[0] << 8) | buf[1]);
    accData[1] = (int16_t)((buf[2] << 8) | buf[3]);
    accData[2] = (int16_t)((buf[4] << 8) | buf[5]);
}

static esp_err_t i2c_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t i2c_config = {0};
    i2c_config.mode             = I2C_MODE_MASTER;
    i2c_config.sda_io_num       = I2C_MASTER_SDA_IO;
    i2c_config.scl_io_num       = I2C_MASTER_SCL_IO;
    i2c_config.sda_pullup_en    = GPIO_PULLUP_DISABLE;
    i2c_config.scl_pullup_en    = GPIO_PULLUP_DISABLE;
    i2c_config.master.clk_speed = I2C_MASTER_FREQ_HZ;
    //i2c_config.clk_flags        = 0;

    i2c_param_config(i2c_master_port, &i2c_config);

    return i2c_driver_install(i2c_master_port, i2c_config.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}



uint8_t mpu6050_init()
{
    i2c_init();
    while(mpu6050_is_connected())
    {
        ESP_LOGE(TAG, "mpu6050 disconnect");
    }
    ESP_LOGI(TAG, "mpu6050 connect");
    mpu6050_write(MPU6050_RA_PWR_MGMT_1, 0x80);
    mpu6050_write(MPU6050_RA_PWR_MGMT_1, 0x01);
    mpu6050_write(MPU6050_RA_INT_ENABLE, 0x00);
    mpu6050_write(MPU6050_RA_GYRO_CONFIG, 0x18);
    mpu6050_write(MPU6050_RA_ACCEL_CONFIG, 0x08);
    mpu6050_write(MPU6050_RA_CONFIG, MPU6050_DLPF_BW_20);
    mpu6050_write(MPU6050_RA_SMPLRT_DIV, 0x00);
    mpu6050_write(MPU6050_RA_INT_PIN_CFG, 0x02);

    return 0;
}