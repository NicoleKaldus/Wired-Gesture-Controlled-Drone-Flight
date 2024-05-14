#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "driver/i2c.h"
#include "mpu6050.h"
#include "esp_system.h"
#include "esp_log.h"
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <math.h>


#define I2C_MASTER_SCL_IO 1//19      /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO 0//18      /*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM I2C_NUM_0  /*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ 100000 /*!< I2C master clock frequency */

static const char *TAG = "mpu6050 test";
static mpu6050_handle_t mpu6050 = NULL;

/**
 * @brief i2c master initialization
 */
static void i2c_bus_init(void)
{
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = (gpio_num_t)I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = (gpio_num_t)I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    conf.clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL;

    esp_err_t ret = i2c_param_config(I2C_MASTER_NUM, &conf);
    if (ret != ESP_OK) {
        // ESP_LOGE(TAG, "I2C config returned error");
        return;
        }

        ret = i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
        if (ret != ESP_OK) {
            // ESP_LOGE(TAG, "I2C install returned error");
            return;
        }
    }

    /**
     * @brief i2c master initialization
     */
    static void i2c_sensor_mpu6050_init(void)
    {
        esp_err_t ret;

        i2c_bus_init();
        mpu6050 = mpu6050_create(I2C_MASTER_NUM, MPU6050_I2C_ADDRESS);
        if (mpu6050 == NULL) {
            // ESP_LOGE(TAG, "MPU6050 create returned NULL");
            return;
        }

        ret = mpu6050_config(mpu6050, ACCE_FS_4G, GYRO_FS_500DPS);
        if (ret != ESP_OK) {
            // ESP_LOGE(TAG, "MPU6050 config error");
            return;
        }

        ret = mpu6050_wake_up(mpu6050);
        if (ret != ESP_OK) {
            // ESP_LOGE(TAG, "MPU6050 wake up error");
            return;
        }
    }

    void app_main()
    {
        //sensor set up
        esp_err_t ret;
        uint8_t mpu6050_deviceid;
        mpu6050_acce_value_t acce;
        mpu6050_gyro_value_t gyro;

        i2c_sensor_mpu6050_init();

        ret = mpu6050_get_deviceid(mpu6050, &mpu6050_deviceid);
        if (ret != ESP_OK) {
            // ESP_LOGE(TAG, "Failed to get MPU6050 device ID");
        } 


        //prepare to read the files
        int numMovements = 4;
        int numFilesPerMovement = 1;
        int numReadingsPerFile = 1000;
        printf("acce_x,acce_y,acce_z,gyro_x,gyro_y,gyro_z\n"); 
        int readingCount = 0;
        // while(numMovements > 0){ //for each type of movement
        while(readingCount < 10000000 ){ //for each gesture
                readingCount += 1;
                clock_t start_t = clock(); //get the start time of the gesture

                while(numReadingsPerFile > 0){ //for each reading of the gesture
                    //get the acceleration data
                    ret = mpu6050_get_acce(mpu6050, &acce);
                    if (ret != ESP_OK) {
                        // ESP_LOGE(TAG, "Failed to get accelerometer data");
                    }
                    //get the gyroscopic data
                    ret = mpu6050_get_gyro(mpu6050, &gyro);
                    if (ret != ESP_OK) {
                        // ESP_LOGE(TAG, "Failed to get gyroscopic data");
                    }
                    double timeInSeconds = ((double)(clock() - start_t))/((double)CLOCKS_PER_SEC);
                    // printf("%f", timeInSeconds);
                    printf("%.3f,%.3f,%.3f,%.3f,%.3f,%.3f\n",acce.acce_x,acce.acce_y,acce.acce_z,gyro.gyro_x,gyro.gyro_y,gyro.gyro_z);
                    numReadingsPerFile = numReadingsPerFile - 1;
                } //file reading done

                numReadingsPerFile = 200; //reset variable
                numFilesPerMovement = numFilesPerMovement - 1; //change number of files left to make

                // int milli_seconds = 1000 * 1.5;
                // clock_t pause_start = clock();
                // while (clock() < pause_start + milli_seconds){}//pause for a moment
            // }
            
            // numFilesPerMovement = 1; //reset variable
            // numMovements = numMovements - 1;

            // int milli_seconds = 1000 * 1.5;
            // clock_t pause_start = clock();
            // while (clock() < pause_start + milli_seconds){}//pause for a moment
        }
    mpu6050_delete(mpu6050);
    ret = i2c_driver_delete(I2C_MASTER_NUM);
    if (ret != ESP_OK) {
        // ESP_LOGE(TAG, "Failed to delete I2C driver");
    }
}