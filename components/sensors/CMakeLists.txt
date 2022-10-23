idf_component_register(SRCS "sensors.c" 
                  "mpu6050/mpu6050.c"
                  INCLUDE_DIRS "."
                  "mpu6050"
                  REQUIRES driver
                  )