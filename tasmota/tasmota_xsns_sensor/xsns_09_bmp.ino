/*
  xsns_09_bmp.ino - BMP pressure, temperature, humidity and gas sensor support for Tasmota

  Copyright (C) 2021  Heiko Krupp and Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifdef USE_I2C
#ifdef USE_BMP
/*********************************************************************************************\
 * BMP085, BMP180, BMP280, BME280, BME680 - Pressure, Temperature, Humidity (BME280/BME680) and gas (BME680)
 *
 * Source: Heiko Krupp and Adafruit Industries
 *
 * I2C Address: 0x76 or 0x77
\*********************************************************************************************/

#define XSNS_09 9
#define XI2C_10 10 // See I2CDEVICES.md

#ifdef USE_BME680
#define USE_BME68X
#endif

#define BMP_ADDR1 0x76
#define BMP_ADDR2 0x77

#define BMP180_CHIPID 0x55
#define BMP280_CHIPID 0x58
#define BME280_CHIPID 0x60
#define BME680_CHIPID 0x61

#define BMP_REGISTER_CHIPID 0xD0

#define BMP_REGISTER_RESET 0xE0 // Register to reset to power on defaults (used for sleep)

#define BMP_CMND_RESET 0xB6 // I2C Parameter for RESET to put BMP into reset state

#ifdef USE_I2C_BUS2
#define BMP_MAX_SENSORS 4 // 2 busses
#else
  #define BMP_MAX_SENSORS 2
xx
#endif

#ifndef BMP_MAX_SENSORS
xxx
#endif

#ifdef USE_UFILESYS
    extern FS *ffsp;
#endif

#include "iaq_class.h"

const char kBmpTypes[] PROGMEM = "BMP180|BMP280|BME280|BME680";

typedef struct
{
  uint8_t bmp_address; // I2C address
  uint8_t bmp_bus;     // I2C bus
  char bmp_name[7];    // Sensor name - "BMPXXX"
  uint8_t bmp_type;
  uint8_t bmp_model;
#ifdef USE_BME68X
  uint8_t bme680_state;
  float bmp_gas_resistance;
  IAQTracker IaqTr;
#endif // USE_BME68X
  float bmp_temperature;
  float bmp_pressure;
  float bmp_humidity;
  uint16_t bmp_iaq;
} bmp_sensors_t;

uint8_t bmp_addresses[] = {BMP_ADDR1, BMP_ADDR2};
uint8_t bmp_count = 0;
#ifdef USE_DEEPSLEEP
uint8_t bmp_deepsleep = 0; // Prevent updating measurments once BMP has been put to sleep (just before ESP enters deepsleep)
#endif

bmp_sensors_t *bmp_sensors = nullptr;

/*********************************************************************************************\
 * BMP085 and BME180
\*********************************************************************************************/

#define BMP180_REG_CONTROL 0xF4
#define BMP180_REG_RESULT 0xF6
#define BMP180_TEMPERATURE 0x2E
#define BMP180_PRESSURE3 0xF4 // Max. oversampling -> OSS = 3

#define BMP180_AC1 0xAA
#define BMP180_AC2 0xAC
#define BMP180_AC3 0xAE
#define BMP180_AC4 0xB0
#define BMP180_AC5 0xB2
#define BMP180_AC6 0xB4
#define BMP180_VB1 0xB6
#define BMP180_VB2 0xB8
#define BMP180_MB 0xBA
#define BMP180_MC 0xBC
#define BMP180_MD 0xBE

#define BMP180_OSS 3

typedef struct
{
  int16_t cal_ac1;
  int16_t cal_ac2;
  int16_t cal_ac3;
  int16_t cal_b1;
  int16_t cal_b2;
  int16_t cal_mc;
  int16_t cal_md;
  uint16_t cal_ac4;
  uint16_t cal_ac5;
  uint16_t cal_ac6;
} bmp180_cal_data_t;

bmp180_cal_data_t *bmp180_cal_data = nullptr;

bool Bmp180Calibration(uint8_t bmp_idx)
{
  if (!bmp180_cal_data)
  {
    bmp180_cal_data = (bmp180_cal_data_t *)malloc(BMP_MAX_SENSORS * sizeof(bmp180_cal_data_t));
  }
  if (!bmp180_cal_data)
  {
    return false;
  }

  uint8_t address = bmp_sensors[bmp_idx].bmp_address;
  uint8_t bus = bmp_sensors[bmp_idx].bmp_bus;
  bmp180_cal_data[bmp_idx].cal_ac1 = I2cRead16(address, BMP180_AC1, bus);
  bmp180_cal_data[bmp_idx].cal_ac2 = I2cRead16(address, BMP180_AC2, bus);
  bmp180_cal_data[bmp_idx].cal_ac3 = I2cRead16(address, BMP180_AC3, bus);
  bmp180_cal_data[bmp_idx].cal_ac4 = I2cRead16(address, BMP180_AC4, bus);
  bmp180_cal_data[bmp_idx].cal_ac5 = I2cRead16(address, BMP180_AC5, bus);
  bmp180_cal_data[bmp_idx].cal_ac6 = I2cRead16(address, BMP180_AC6, bus);
  bmp180_cal_data[bmp_idx].cal_b1 = I2cRead16(address, BMP180_VB1, bus);
  bmp180_cal_data[bmp_idx].cal_b2 = I2cRead16(address, BMP180_VB2, bus);
  bmp180_cal_data[bmp_idx].cal_mc = I2cRead16(address, BMP180_MC, bus);
  bmp180_cal_data[bmp_idx].cal_md = I2cRead16(address, BMP180_MD, bus);
  // Check for Errors in calibration data. Value never is 0x0000 or 0xFFFF
  if (!bmp180_cal_data[bmp_idx].cal_ac1 |
      !bmp180_cal_data[bmp_idx].cal_ac2 |
      !bmp180_cal_data[bmp_idx].cal_ac3 |
      !bmp180_cal_data[bmp_idx].cal_ac4 |
      !bmp180_cal_data[bmp_idx].cal_ac5 |
      !bmp180_cal_data[bmp_idx].cal_ac6 |
      !bmp180_cal_data[bmp_idx].cal_b1 |
      !bmp180_cal_data[bmp_idx].cal_b2 |
      !bmp180_cal_data[bmp_idx].cal_mc |
      !bmp180_cal_data[bmp_idx].cal_md)
  {
    return false;
  }

  if ((bmp180_cal_data[bmp_idx].cal_ac1 == (int16_t)0xFFFF) |
      (bmp180_cal_data[bmp_idx].cal_ac2 == (int16_t)0xFFFF) |
      (bmp180_cal_data[bmp_idx].cal_ac3 == (int16_t)0xFFFF) |
      (bmp180_cal_data[bmp_idx].cal_ac4 == 0xFFFF) |
      (bmp180_cal_data[bmp_idx].cal_ac5 == 0xFFFF) |
      (bmp180_cal_data[bmp_idx].cal_ac6 == 0xFFFF) |
      (bmp180_cal_data[bmp_idx].cal_b1 == (int16_t)0xFFFF) |
      (bmp180_cal_data[bmp_idx].cal_b2 == (int16_t)0xFFFF) |
      (bmp180_cal_data[bmp_idx].cal_mc == (int16_t)0xFFFF) |
      (bmp180_cal_data[bmp_idx].cal_md == (int16_t)0xFFFF))
  {
    return false;
  }
  return true;
}

void Bmp180Read(uint8_t bmp_idx)
{
  if (!bmp180_cal_data)
  {
    return;
  }

  uint8_t address = bmp_sensors[bmp_idx].bmp_address;
  uint8_t bus = bmp_sensors[bmp_idx].bmp_bus;
  I2cWrite8(address, BMP180_REG_CONTROL, BMP180_TEMPERATURE, bus);
  delay(5); // 5ms conversion time
  int ut = I2cRead16(address, BMP180_REG_RESULT, bus);
  int32_t xt1 = (ut - (int32_t)bmp180_cal_data[bmp_idx].cal_ac6) * ((int32_t)bmp180_cal_data[bmp_idx].cal_ac5) >> 15;
  int32_t xt2 = ((int32_t)bmp180_cal_data[bmp_idx].cal_mc << 11) / (xt1 + (int32_t)bmp180_cal_data[bmp_idx].cal_md);
  int32_t bmp180_b5 = xt1 + xt2;
  bmp_sensors[bmp_idx].bmp_temperature = ((bmp180_b5 + 8) >> 4) / 10.0f;

  I2cWrite8(address, BMP180_REG_CONTROL, BMP180_PRESSURE3, bus); // Highest resolution
  delay(2 + (4 << BMP180_OSS));                                  // 26ms conversion time at ultra high resolution
  uint32_t up = I2cRead24(address, BMP180_REG_RESULT, bus);
  up >>= (8 - BMP180_OSS);

  int32_t b6 = bmp180_b5 - 4000;
  int32_t x1 = ((int32_t)bmp180_cal_data[bmp_idx].cal_b2 * ((b6 * b6) >> 12)) >> 11;
  int32_t x2 = ((int32_t)bmp180_cal_data[bmp_idx].cal_ac2 * b6) >> 11;
  int32_t x3 = x1 + x2;
  int32_t b3 = ((((int32_t)bmp180_cal_data[bmp_idx].cal_ac1 * 4 + x3) << BMP180_OSS) + 2) >> 2;

  x1 = ((int32_t)bmp180_cal_data[bmp_idx].cal_ac3 * b6) >> 13;
  x2 = ((int32_t)bmp180_cal_data[bmp_idx].cal_b1 * ((b6 * b6) >> 12)) >> 16;
  x3 = ((x1 + x2) + 2) >> 2;
  uint32_t b4 = ((uint32_t)bmp180_cal_data[bmp_idx].cal_ac4 * (uint32_t)(x3 + 32768)) >> 15;
  uint32_t b7 = ((uint32_t)up - b3) * (uint32_t)(50000UL >> BMP180_OSS);

  int32_t p;
  if (b7 < 0x80000000)
  {
    p = (b7 * 2) / b4;
  }
  else
  {
    p = (b7 / b4) * 2;
  }
  x1 = (p >> 8) * (p >> 8);
  x1 = (x1 * 3038) >> 16;
  x2 = (-7357 * p) >> 16;
  p += ((x1 + x2 + (int32_t)3791) >> 4);
  bmp_sensors[bmp_idx].bmp_pressure = (float)p / 100.0f; // convert to mbar
}

/*********************************************************************************************\
 * BMP280 and BME280
 *
 * Programmer : BMP280/BME280 Datasheet and Adafruit with changes by Theo Arends
\*********************************************************************************************/

#define BME280_REGISTER_CONTROLHUMID 0xF2
#define BME280_REGISTER_CONTROL 0xF4
#define BME280_REGISTER_CONFIG 0xF5
#define BME280_REGISTER_PRESSUREDATA 0xF7
#define BME280_REGISTER_TEMPDATA 0xFA
#define BME280_REGISTER_HUMIDDATA 0xFD

#define BME280_REGISTER_DIG_T1 0x88
#define BME280_REGISTER_DIG_T2 0x8A
#define BME280_REGISTER_DIG_T3 0x8C
#define BME280_REGISTER_DIG_P1 0x8E
#define BME280_REGISTER_DIG_P2 0x90
#define BME280_REGISTER_DIG_P3 0x92
#define BME280_REGISTER_DIG_P4 0x94
#define BME280_REGISTER_DIG_P5 0x96
#define BME280_REGISTER_DIG_P6 0x98
#define BME280_REGISTER_DIG_P7 0x9A
#define BME280_REGISTER_DIG_P8 0x9C
#define BME280_REGISTER_DIG_P9 0x9E
#define BME280_REGISTER_DIG_H1 0xA1
#define BME280_REGISTER_DIG_H2 0xE1
#define BME280_REGISTER_DIG_H3 0xE3
#define BME280_REGISTER_DIG_H4 0xE4
#define BME280_REGISTER_DIG_H5 0xE5
#define BME280_REGISTER_DIG_H6 0xE7

typedef struct
{
  uint16_t dig_T1;
  int16_t dig_T2;
  int16_t dig_T3;
  uint16_t dig_P1;
  int16_t dig_P2;
  int16_t dig_P3;
  int16_t dig_P4;
  int16_t dig_P5;
  int16_t dig_P6;
  int16_t dig_P7;
  int16_t dig_P8;
  int16_t dig_P9;
  int16_t dig_H2;
  int16_t dig_H4;
  int16_t dig_H5;
  uint8_t dig_H1;
  uint8_t dig_H3;
  int8_t dig_H6;
} Bme280CalibrationData_t;

Bme280CalibrationData_t *Bme280CalibrationData = nullptr;

bool Bmx280Calibrate(uint8_t bmp_idx)
{
  //  if (I2cRead8(bmp_address, BMP_REGISTER_CHIPID, bus) != BME280_CHIPID) return false;

  if (!Bme280CalibrationData)
  {
    Bme280CalibrationData = (Bme280CalibrationData_t *)malloc(BMP_MAX_SENSORS * sizeof(Bme280CalibrationData_t));
  }
  if (!Bme280CalibrationData)
  {
    return false;
  }

  uint8_t address = bmp_sensors[bmp_idx].bmp_address;
  uint8_t bus = bmp_sensors[bmp_idx].bmp_bus;
  Bme280CalibrationData[bmp_idx].dig_T1 = I2cRead16LE(address, BME280_REGISTER_DIG_T1, bus);
  Bme280CalibrationData[bmp_idx].dig_T2 = I2cReadS16_LE(address, BME280_REGISTER_DIG_T2, bus);
  Bme280CalibrationData[bmp_idx].dig_T3 = I2cReadS16_LE(address, BME280_REGISTER_DIG_T3, bus);
  Bme280CalibrationData[bmp_idx].dig_P1 = I2cRead16LE(address, BME280_REGISTER_DIG_P1, bus);
  Bme280CalibrationData[bmp_idx].dig_P2 = I2cReadS16_LE(address, BME280_REGISTER_DIG_P2, bus);
  Bme280CalibrationData[bmp_idx].dig_P3 = I2cReadS16_LE(address, BME280_REGISTER_DIG_P3, bus);
  Bme280CalibrationData[bmp_idx].dig_P4 = I2cReadS16_LE(address, BME280_REGISTER_DIG_P4, bus);
  Bme280CalibrationData[bmp_idx].dig_P5 = I2cReadS16_LE(address, BME280_REGISTER_DIG_P5, bus);
  Bme280CalibrationData[bmp_idx].dig_P6 = I2cReadS16_LE(address, BME280_REGISTER_DIG_P6, bus);
  Bme280CalibrationData[bmp_idx].dig_P7 = I2cReadS16_LE(address, BME280_REGISTER_DIG_P7, bus);
  Bme280CalibrationData[bmp_idx].dig_P8 = I2cReadS16_LE(address, BME280_REGISTER_DIG_P8, bus);
  Bme280CalibrationData[bmp_idx].dig_P9 = I2cReadS16_LE(address, BME280_REGISTER_DIG_P9, bus);
  if (BME280_CHIPID == bmp_sensors[bmp_idx].bmp_type)
  { // #1051
    Bme280CalibrationData[bmp_idx].dig_H1 = I2cRead8(address, BME280_REGISTER_DIG_H1, bus);
    Bme280CalibrationData[bmp_idx].dig_H2 = I2cReadS16_LE(address, BME280_REGISTER_DIG_H2, bus);
    Bme280CalibrationData[bmp_idx].dig_H3 = I2cRead8(address, BME280_REGISTER_DIG_H3, bus);
    Bme280CalibrationData[bmp_idx].dig_H4 = (I2cRead8(address, BME280_REGISTER_DIG_H4, bus) << 4) | (I2cRead8(address, BME280_REGISTER_DIG_H4 + 1, bus) & 0xF);
    Bme280CalibrationData[bmp_idx].dig_H5 = (I2cRead8(address, BME280_REGISTER_DIG_H5 + 1, bus) << 4) | (I2cRead8(address, BME280_REGISTER_DIG_H5, bus) >> 4);
    Bme280CalibrationData[bmp_idx].dig_H6 = (int8_t)I2cRead8(address, BME280_REGISTER_DIG_H6, bus);
    I2cWrite8(address, BME280_REGISTER_CONTROL, 0x00, bus); // sleep mode since writes to config can be ignored in normal mode (Datasheet 5.4.5/6 page 27)
    // Set before CONTROL_meas (DS 5.4.3)
    I2cWrite8(address, BME280_REGISTER_CONTROLHUMID, 0x01, bus); // 1x oversampling
    I2cWrite8(address, BME280_REGISTER_CONFIG, 0xA0, bus);       // 1sec standby between measurements (to limit self heating), IIR filter off
    I2cWrite8(address, BME280_REGISTER_CONTROL, 0x27, bus);      // 1x oversampling, normal mode
  }
  else
  {
    I2cWrite8(address, BME280_REGISTER_CONTROL, 0xB7, bus); // 16x oversampling, normal mode (Adafruit)
  }
  return true;
}

void Bme280Read(uint8_t bmp_idx)
{
  if (!Bme280CalibrationData)
  {
    return;
  }

  uint8_t address = bmp_sensors[bmp_idx].bmp_address;
  uint8_t bus = bmp_sensors[bmp_idx].bmp_bus;
  int32_t adc_T = I2cRead24(address, BME280_REGISTER_TEMPDATA, bus);
  adc_T >>= 4;

  int32_t vart1 = ((((adc_T >> 3) - ((int32_t)Bme280CalibrationData[bmp_idx].dig_T1 << 1))) * ((int32_t)Bme280CalibrationData[bmp_idx].dig_T2)) >> 11;
  int32_t vart2 = (((((adc_T >> 4) - ((int32_t)Bme280CalibrationData[bmp_idx].dig_T1)) * ((adc_T >> 4) - ((int32_t)Bme280CalibrationData[bmp_idx].dig_T1))) >> 12) *
                   ((int32_t)Bme280CalibrationData[bmp_idx].dig_T3)) >>
                  14;
  int32_t t_fine = vart1 + vart2;
  float T = (t_fine * 5 + 128) >> 8;
  bmp_sensors[bmp_idx].bmp_temperature = T / 100.0f;

  int32_t adc_P = I2cRead24(address, BME280_REGISTER_PRESSUREDATA, bus);
  adc_P >>= 4;

  int64_t var1 = ((int64_t)t_fine) - 128000;
  int64_t var2 = var1 * var1 * (int64_t)Bme280CalibrationData[bmp_idx].dig_P6;
  var2 = var2 + ((var1 * (int64_t)Bme280CalibrationData[bmp_idx].dig_P5) << 17);
  var2 = var2 + (((int64_t)Bme280CalibrationData[bmp_idx].dig_P4) << 35);
  var1 = ((var1 * var1 * (int64_t)Bme280CalibrationData[bmp_idx].dig_P3) >> 8) + ((var1 * (int64_t)Bme280CalibrationData[bmp_idx].dig_P2) << 12);
  var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)Bme280CalibrationData[bmp_idx].dig_P1) >> 33;
  if (0 == var1)
  {
    return; // avoid exception caused by division by zero
  }
  int64_t p = 1048576 - adc_P;
  p = (((p << 31) - var2) * 3125) / var1;
  var1 = (((int64_t)Bme280CalibrationData[bmp_idx].dig_P9) * (p >> 13) * (p >> 13)) >> 25;
  var2 = (((int64_t)Bme280CalibrationData[bmp_idx].dig_P8) * p) >> 19;
  p = ((p + var1 + var2) >> 8) + (((int64_t)Bme280CalibrationData[bmp_idx].dig_P7) << 4);
  bmp_sensors[bmp_idx].bmp_pressure = (float)p / 25600.0f;

  if (BMP280_CHIPID == bmp_sensors[bmp_idx].bmp_type)
  {
    return;
  }

  int32_t adc_H = I2cRead16(address, BME280_REGISTER_HUMIDDATA, bus);

  int32_t v_x1_u32r = (t_fine - ((int32_t)76800));
  v_x1_u32r = (((((adc_H << 14) - (((int32_t)Bme280CalibrationData[bmp_idx].dig_H4) << 20) -
                  (((int32_t)Bme280CalibrationData[bmp_idx].dig_H5) * v_x1_u32r)) +
                 ((int32_t)16384)) >>
                15) *
               (((((((v_x1_u32r * ((int32_t)Bme280CalibrationData[bmp_idx].dig_H6)) >> 10) *
                    (((v_x1_u32r * ((int32_t)Bme280CalibrationData[bmp_idx].dig_H3)) >> 11) + ((int32_t)32768))) >>
                   10) +
                  ((int32_t)2097152)) *
                     ((int32_t)Bme280CalibrationData[bmp_idx].dig_H2) +
                 8192) >>
                14));
  v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) *
                             ((int32_t)Bme280CalibrationData[bmp_idx].dig_H1)) >>
                            4));
  v_x1_u32r = (v_x1_u32r < 0) ? 0 : v_x1_u32r;
  v_x1_u32r = (v_x1_u32r > 419430400) ? 419430400 : v_x1_u32r;
  float h = (v_x1_u32r >> 12);
  bmp_sensors[bmp_idx].bmp_humidity = h / 1024.0f;
}

#ifdef USE_BME68X
/*********************************************************************************************\
 * BME68x support by Bosch https://github.com/BoschSensortec/BME68x-Sensor-API
\*********************************************************************************************/

// #define BME68X_DO_NOT_USE_FPU

#include <bme68x.h>

struct bme68x_dev *bme_dev = nullptr;
struct bme68x_conf *bme_conf = nullptr;
struct bme68x_heatr_conf *bme_heatr_conf = nullptr;
/* Heater temperature in degree Celsius */
uint16_t temp_prof[10] = {0, 320, 320, 320, 320, 320, 320, 320, 320, 0};

/* Heating duration in milliseconds */
uint16_t dur_prof[10] = {1000, 150, 150, 150, 150, 150, 150, 150, 250, 5000};

uint8_t bmp68x_bus = 0;

// bme68x callbacks
static void Bme68x_Delayus(uint32_t period, void *intf_ptr)
{
  delayMicroseconds(period);
}
int8_t Bme68x_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
  uint8_t dev_addr = *(uint8_t *)intf_ptr;
  return I2cReadBuffer(dev_addr, reg_addr, reg_data, (uint16_t)len, bmp68x_bus);
}
int8_t Bme68x_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
  uint8_t dev_addr = *(uint8_t *)intf_ptr;
  return I2cWriteBuffer(dev_addr, reg_addr, (uint8_t *)reg_data, (uint16_t)len, bmp68x_bus);
}

void state_load(uint8_t sens_no)
{
#ifdef USE_UFILESYS
  if (ffsp)
  {
    char file[] = "/bme68xstate_x.bin";
    file[13] = char('0') + sens_no;

    File fp = ffsp->open(file, "r");
    size_t res;
    if (fp > 0)
    {
      AddLog(LOG_LEVEL_DEBUG, PSTR("BME: Reading file"));
      if (!bmp_sensors[sens_no].IaqTr.loadFromBinaryFile(fp))
        AddLog(LOG_LEVEL_ERROR, PSTR("BME: Reading file error"));
      fp.close();
    }
    else
      AddLog(LOG_LEVEL_INFO, PSTR("BME: No state file"));
  }
#endif // USE_UFILESYS
}

// void save(uint8_t sens_no)
// {
// #ifdef USE_UFILESYS
//   //    uint32_t crc32 = GetCfgCrc32((uint8_t*)&NeoPoolSettings +4, sizeof(NeoPoolSettings) -4);  // Skip crc32
//   //    if (crc32 != NeoPoolSettings.crc32) {
//   //      NeoPoolSettings.crc32 = crc32;
//   char filename[] = "/bme68xstate_x.bin";
//   filename[13] = char('0') + sens_no;

//   if (TfsSaveFile(filename, (const uint8_t *)&bmp_sensors[sens_no].IaqTr, sizeof(bmp_sensors[sens_no].IaqTr)))
//   {
//     AddLog(LOG_LEVEL_DEBUG, PSTR("BME: saved to file '%s'"), filename);
//   }
//   else
//   {
//     // File system not ready: No flash space reserved for file system
//     AddLog(LOG_LEVEL_DEBUG, PSTR("BME: ERROR file system not ready or unable to save file '%s'"), filename);
//   }
//   //    }
// #endif // USE_UFILESYS
// }

bool state_save(uint8_t sens_no)
{
#ifdef USE_UFILESYS
  if (ffsp && (BME680_CHIPID == bmp_sensors[sens_no].bmp_type))
  {
    char file[] = "/bme68xstate_x.bin";
    file[13] = char('0') + sens_no;
    File fp = ffsp->open(file, "w");
    if (fp > 0)
    {
      bmp_sensors[sens_no].IaqTr.saveToBinaryFile(fp);
      fp.close();
      AddLog(LOG_LEVEL_DEBUG, PSTR("BME: Writing file"));
      return true;
    }
    else
      AddLog(LOG_LEVEL_ERROR, PSTR("BME: State write error"));
  }
#endif // USE_UFILESYS
  return false;
}

bool check_rslt(int8_t idx, int8_t rslt)
{
  switch (rslt)
  {
  case BME68X_OK:
    return true;
    /* Do nothing */
    break;
  case BME68X_E_NULL_PTR:
    AddLog(LOG_LEVEL_ERROR, PSTR("BME: Idx: %d Error [%d] : Null pointer"), idx, rslt);
    break;
  case BME68X_E_COM_FAIL:
    AddLog(LOG_LEVEL_ERROR, PSTR("BME: Idx: %d Error [%d] : Communication failure"), idx, rslt);
    break;
  case BME68X_E_INVALID_LENGTH:
    AddLog(LOG_LEVEL_ERROR, PSTR("BME: Idx: %d Error [%d] : Incorrect length parameter"), idx, rslt);
    //    printf("API name [%s]  Error [%d] : Incorrect length parameter\r\n", api_name, idx, rslt);
    break;
  case BME68X_E_DEV_NOT_FOUND:
    AddLog(LOG_LEVEL_ERROR, PSTR("BME: Idx: %d Error [%d] : Device not found"), idx, rslt);
    //    printf("API name [%s]  Error [%d] : Device not found\r\n", api_name, idx, rslt);
    break;
  case BME68X_E_SELF_TEST:
    AddLog(LOG_LEVEL_ERROR, PSTR("BME: Idx: %d Error [%d] : Self test error"), idx, rslt);
    //    printf("API name [%s]  Error [%d] : Self test error\r\n", api_name, idx, rslt);
    break;
  case BME68X_W_NO_NEW_DATA:
    AddLog(LOG_LEVEL_DEBUG, PSTR("BME: Idx: %d Warning [%d] : No new data found"), idx, rslt);
    //    printf("API name [%s]  Warning [%d] : No new data found\r\n", api_name, idx, rslt);
    break;
  default:
    AddLog(LOG_LEVEL_ERROR, PSTR("BME: Idx: %d Error [%d] : Unknown error code"), idx, rslt);
    //    printf("API name [%s]  Error [%d] : Unknown error code\r\n", api_name, rslt);
    break;
  }
  return false;
}

bool Bme680Init(uint8_t bmp_idx)
{
  bmp68x_bus = bmp_sensors[bmp_idx].bmp_bus;

  if (!bme_dev)
  {
    bme_heatr_conf = (bme68x_heatr_conf *)malloc(BMP_MAX_SENSORS * sizeof(bme68x_heatr_conf));
    bme_conf = (bme68x_conf *)malloc(BMP_MAX_SENSORS * sizeof(bme68x_conf));
    bme_dev = (bme68x_dev *)malloc(BMP_MAX_SENSORS * sizeof(bme68x_dev));
  }
  if (!bme_dev)
  {
    return false;
  }

  bmp_sensors[bmp_idx].IaqTr = IAQTracker();
  state_load(bmp_idx);

  bme_dev[bmp_idx].intf_ptr = &bmp_sensors[bmp_idx].bmp_address;
  bme_dev[bmp_idx].intf = BME68X_I2C_INTF;
  bme_dev[bmp_idx].read = Bme68x_i2c_read;
  bme_dev[bmp_idx].write = Bme68x_i2c_write;
  bme_dev[bmp_idx].delay_us = Bme68x_Delayus;
  // amb_temp can be set to 25 prior to configuring the gas sensor
  // or by performing a few temperature readings without operating the gas sensor.
  bme_dev[bmp_idx].amb_temp = 25;

  if (!check_rslt(1, bme68x_init(&bme_dev[bmp_idx])))
  {
    return false;
  }

  AddLog(LOG_LEVEL_DEBUG, PSTR("BME: Gas variant %d"), bme_dev[bmp_idx].variant_id);

  //  rslt = bme68x_get_conf(&bme_conf[bmp_idx], &bme_dev[bmp_idx]);
  //  if (rslt != BME68X_OK) { return false; }
  // Set the temperature, pressure and humidity settings
  bme_conf[bmp_idx].os_hum = BME68X_OS_2X;
  bme_conf[bmp_idx].os_pres = BME68X_OS_4X;
  bme_conf[bmp_idx].os_temp = BME68X_OS_8X;
  bme_conf[bmp_idx].filter = BME68X_FILTER_SIZE_3;
  bme_conf[bmp_idx].odr = BME68X_ODR_1000_MS; // This parameter defines the sleep duration after each profile

  if (!check_rslt(2, bme68x_set_conf(&bme_conf[bmp_idx], &bme_dev[bmp_idx])))
  {
    return false;
  }

  // Set the gas sensor settings
  bme_heatr_conf[bmp_idx].enable = BME68X_ENABLE;
  // bme_heatr_conf[bmp_idx].enable = BME68X_DISABLE;

  // Create a ramp heat waveform in 3 steps
  bme_heatr_conf[bmp_idx].heatr_temp = 320; // degree Celsius
  bme_heatr_conf[bmp_idx].heatr_dur = 150;  // milliseconds
  bme_heatr_conf[bmp_idx].heatr_temp_prof = temp_prof;
  bme_heatr_conf[bmp_idx].heatr_dur_prof = dur_prof;
  bme_heatr_conf[bmp_idx].profile_len = 2;

  if (!check_rslt(3, bme68x_set_heatr_conf(BME68X_SEQUENTIAL_MODE, &bme_heatr_conf[bmp_idx], &bme_dev[bmp_idx])))
  {
    return false;
  }

  bmp_sensors[bmp_idx].bme680_state = 0;

  if (!check_rslt(4, bme68x_set_op_mode(BME68X_SEQUENTIAL_MODE, &bme_dev[bmp_idx])))
  {
    return false;
  }

  return true;
}

void Bme680Read(uint8_t bmp_idx)
{
  struct bme68x_dev bme;

  struct bme68x_conf conf;

  static int64_t t;

  if (!bme_dev)
  {
    AddLog(LOG_LEVEL_DEBUG, PSTR("BME: nein Error [%d] : Null pointer"), bmp_idx);

    return;
  }

  bmp68x_bus = bmp_sensors[bmp_idx].bmp_bus;

  if (BME680_CHIPID == bmp_sensors[bmp_idx].bmp_type)
  {
    //    uint32_t del_period = bme68x_get_meas_dur(BME68X_SEQUENTIAL_MODE, &conf, &bme) + (bme_heatr_conf[bmp_idx].heatr_dur_prof[0] * 1000);
    //    AddLog(LOG_LEVEL_DEBUG, PSTR("BME: meas_dur %d"), del_period);
    struct bme68x_data data;
    uint8_t n_fields;
    int8_t ret_val = bme68x_get_data(BME68X_SEQUENTIAL_MODE, &data, &n_fields, &bme_dev[bmp_idx]);
    if (ret_val == BME68X_W_NO_NEW_DATA)
    {
 //     AddLog(LOG_LEVEL_DEBUG, PSTR("BME: nix da"));
      return;
    }

    if (!check_rslt(5, ret_val))
      return;

#ifdef BME68X_DO_NOT_USE_FPU
    bmp_sensors[bmp_idx].bmp_temperature = data.temperature / 100.0f; // Temperature in degree celsius x100
    bmp_sensors[bmp_idx].bmp_humidity = data.humidity / 1000.0f;      // Humidity in % relative humidity x1000
#else
    bmp_sensors[bmp_idx].bmp_temperature = data.temperature; // Temperature in degree celsius
    bmp_sensors[bmp_idx].bmp_humidity = data.humidity;       // Humidity in % relative humidity
#endif
    bmp_sensors[bmp_idx].bmp_temperature += bmp_sensors[bmp_idx].IaqTr.getTemOfs();
    bmp_sensors[bmp_idx].bmp_humidity += bmp_sensors[bmp_idx].IaqTr.getHumOfs();

    bmp_sensors[bmp_idx].bmp_pressure = data.pressure / 100.0f; // Pressure in Pascal (converted to hPa)
    // Avoid using measurements from an unstable heating setup
    if (data.gas_index == 1)
    {
      if (data.status & BME68X_GASM_VALID_MSK)
      {
        bmp_sensors[bmp_idx].bmp_gas_resistance = data.gas_resistance / 1000.0f; // Gas resistance in Ohms (converted to kOhm)
      }
      else
      {
        bmp_sensors[bmp_idx].bmp_gas_resistance = 0;
      }
      bmp_sensors[bmp_idx].bme680_state = 1;
    }
    int64_t act = esp_timer_get_time();
    AddLog(LOG_LEVEL_DEBUG, PSTR("BME: %ld %f %f %f %f %d %d"), act - t, data.temperature,
           data.humidity, bmp_sensors[bmp_idx].bmp_pressure, data.gas_resistance, data.gas_index, data.meas_index);
    if (data.gas_index == 1)
      t = act;
  }
  return;
}

void Bme680IaqCalc(void)
{
  for (uint32_t bmp_idx = 0; bmp_idx < bmp_count; bmp_idx++)
  {
    if ((bmp_sensors[bmp_idx].bmp_type == BME680_CHIPID) && (bmp_sensors[bmp_idx].bme680_state == 1))
    {
      bmp_sensors[bmp_idx].bmp_iaq = bmp_sensors[bmp_idx].IaqTr.getIAQ(bmp_sensors[bmp_idx].bmp_temperature, bmp_sensors[bmp_idx].bmp_humidity, bmp_sensors[bmp_idx].bmp_gas_resistance * 1000.0f);
      bmp_sensors[bmp_idx].bme680_state = 0;
    }
  }
}

#endif // USE_BME68X

/********************************************************************************************/

void BmpDetect(void)
{
  if (!bmp_sensors)
  {
    bmp_sensors = (bmp_sensors_t *)calloc(BMP_MAX_SENSORS, sizeof(bmp_sensors_t));
  }
  if (!bmp_sensors)
  {
    AddLog(LOG_LEVEL_ERROR, PSTR("BME: Memory Error"));
    return;
  }

  for (uint32_t i = 0; i < BMP_MAX_SENSORS; i++)
  {
    uint8_t bus = i >> 1;
    if (!I2cSetDevice(bmp_addresses[i & 1], bus))
    {
      continue;
    }
    uint8_t bmp_type = I2cRead8(bmp_addresses[i & 1], BMP_REGISTER_CHIPID, bus);
    if (bmp_type)
    {
      AddLog(LOG_LEVEL_DEBUG, PSTR("BME: Idx: %d Sensor found"), i);

      bmp_sensors[bmp_count].bmp_address = bmp_addresses[i & 1];
      bmp_sensors[bmp_count].bmp_bus = bus;
      bmp_sensors[bmp_count].bmp_type = bmp_type;
      bmp_sensors[bmp_count].bmp_model = 0;

      bool success = false;
      switch (bmp_type)
      {
      case BMP180_CHIPID:
        success = Bmp180Calibration(bmp_count);
        break;
      case BME280_CHIPID:
        bmp_sensors[bmp_count].bmp_model++; // 2
      case BMP280_CHIPID:
        bmp_sensors[bmp_count].bmp_model++; // 1
        success = Bmx280Calibrate(bmp_count);
        break;
#ifdef USE_BME68X
      case BME680_CHIPID:
        bmp_sensors[bmp_count].bmp_model = 3; // 3
        success = Bme680Init(bmp_count);
        break;
#endif // USE_BME68X
      }
      if (success)
      {
        GetTextIndexed(bmp_sensors[bmp_count].bmp_name, sizeof(bmp_sensors[bmp_count].bmp_name), bmp_sensors[bmp_count].bmp_model, kBmpTypes);
        I2cSetActiveFound(bmp_sensors[bmp_count].bmp_address, bmp_sensors[bmp_count].bmp_name, bmp_sensors[bmp_count].bmp_bus);
        bmp_count++;
      }
    }
    else
      AddLog(LOG_LEVEL_DEBUG, PSTR("BME: Idx: %d Sensor not found"), i);
  }
}

void BmpRead(void)
{
#ifdef USE_DEEPSLEEP
  // Prevent updating measurments once BMP has been put to sleep (just before ESP enters deepsleep)
  if (bmp_deepsleep)  
    return;
#endif

  for (uint32_t bmp_idx = 0; bmp_idx < bmp_count; bmp_idx++)
  {
    //AddLog(LOG_LEVEL_DEBUG, PSTR("BME: rennnt %d"), bmp_idx);

    switch (bmp_sensors[bmp_idx].bmp_type)
    {
    case BMP180_CHIPID:
      Bmp180Read(bmp_idx);
      break;
    case BMP280_CHIPID:
    case BME280_CHIPID:
      Bme280Read(bmp_idx);
      break;
#ifdef USE_BME68X
    case BME680_CHIPID:
      Bme680Read(bmp_idx);
      break;
#endif // USE_BME68X
    }
    //AddLog(LOG_LEVEL_DEBUG, PSTR("BME: rennt %d"), bmp_idx);
  }
}

void BmpShow(bool json)
{
  for (uint32_t bmp_idx = 0; bmp_idx < bmp_count; bmp_idx++)
  {
    if (bmp_sensors[bmp_idx].bmp_type)
    {
      float bmp_sealevel = ConvertPressureForSeaLevel(bmp_sensors[bmp_idx].bmp_pressure);
      float bmp_temperature = ConvertTemp(bmp_sensors[bmp_idx].bmp_temperature);
      float bmp_pressure = ConvertPressure(bmp_sensors[bmp_idx].bmp_pressure);
      // TasmotaGlobal.iaq = bmp_sensors[bmp_idx].bmp_iaq;

      char name[16];
      // BMP280
      strlcpy(name, bmp_sensors[bmp_idx].bmp_name, sizeof(bmp_sensors[bmp_idx].bmp_name));
      if (bmp_count > 1)
      {
        // BMP280-77
        snprintf_P(name, sizeof(name), PSTR("%s%c%02X"), name, IndexSeparator(), bmp_sensors[bmp_idx].bmp_address);
#ifdef USE_I2C_BUS2
        if (TasmotaGlobal.i2c_enabled[1])
        { // Second bus enabled
          uint8_t bus = bmp_sensors[0].bmp_bus;
          for (uint32_t i = 1; i < bmp_count; i++)
          {
            if (bus != bmp_sensors[i].bmp_bus)
            { // Different busses
              // BMP280-77-1
              snprintf_P(name, sizeof(name), PSTR("%s%c%d"), name, IndexSeparator(), bmp_sensors[bmp_idx].bmp_bus + 1);
              break;
            }
          }
        }
#endif // USE_I2C_BUS2
      }

      char pressure[33];
      dtostrfd(bmp_pressure, Settings->flag2.pressure_resolution, pressure);
      char sea_pressure[33];
      dtostrfd(bmp_sealevel, Settings->flag2.pressure_resolution, sea_pressure);

      float bmp_humidity = ConvertHumidity(bmp_sensors[bmp_idx].bmp_humidity);
      char humidity[33];
      dtostrfd(bmp_humidity, Settings->flag2.humidity_resolution, humidity);
      float f_dewpoint = CalcTempHumToDew(bmp_temperature, bmp_humidity);
      char dewpoint[33];
      dtostrfd(f_dewpoint, Settings->flag2.temperature_resolution, dewpoint);
#ifdef USE_HEAT_INDEX
      float f_heatindex = CalcTemHumToHeatIndex(bmp_temperature, bmp_humidity);
      char heatindex[33];
      dtostrfd(f_heatindex, Settings->flag2.temperature_resolution, heatindex);
#endif // USE_HEAT_INDEX
#ifdef USE_BME68X
      char gas_resistance[33];
      dtostrfd(bmp_sensors[bmp_idx].bmp_gas_resistance, 2, gas_resistance);
#endif // USE_BME68X

      if (json)
      {
        char json_humidity[100];
#ifdef USE_HEAT_INDEX
        snprintf_P(json_humidity, sizeof(json_humidity), PSTR(",\"" D_JSON_HUMIDITY "\":%s,\"" D_JSON_DEWPOINT "\":%s,\"" D_JSON_HEATINDEX "\":%s"), humidity, dewpoint, heatindex);
#else
        snprintf_P(json_humidity, sizeof(json_humidity), PSTR(",\"" D_JSON_HUMIDITY "\":%s,\"" D_JSON_DEWPOINT "\":%s"), humidity, dewpoint);
#endif // USE_HEAT_INDEX
        char json_sealevel[40];
        snprintf_P(json_sealevel, sizeof(json_sealevel), PSTR(",\"" D_JSON_PRESSUREATSEALEVEL "\":%s"), sea_pressure);
#ifdef USE_BME68X
        char json_gas[40];
        snprintf_P(json_gas, sizeof(json_gas), PSTR(",\"" D_JSON_GAS "\":%s"), gas_resistance);
        char json_iaq[40];
        snprintf_P(json_iaq, sizeof(json_iaq), PSTR(",\"" D_JSON_AIRQUALITY "\":%d"), bmp_sensors[bmp_idx].bmp_iaq);

        ResponseAppend_P(PSTR(",\"%s\":{\"" D_JSON_TEMPERATURE "\":%*_f%s,\"" D_JSON_PRESSURE "\":%s%s%s%s}"),
                         name,
                         Settings->flag2.temperature_resolution, &bmp_temperature,
                         (bmp_sensors[bmp_idx].bmp_model >= 2) ? json_humidity : "",
                         pressure,
                         (Settings->altitude != 0) ? json_sealevel : "",
                         (bmp_sensors[bmp_idx].bmp_model >= 3) ? json_gas : "",
                         (bmp_sensors[bmp_idx].bmp_model >= 3) ? json_iaq : "");

#else
        ResponseAppend_P(PSTR(",\"%s\":{\"" D_JSON_TEMPERATURE "\":%*_f%s,\"" D_JSON_PRESSURE "\":%s%s}"),
                         name, Settings->flag2.temperature_resolution, &bmp_temperature, (bmp_sensors[bmp_idx].bmp_model >= 2) ? json_humidity : "", pressure, (Settings->altitude != 0) ? json_sealevel : "");
#endif // USE_BME68X

#ifdef USE_DOMOTICZ
        if ((0 == TasmotaGlobal.tele_period) && (0 == bmp_idx))
        { // We want the same first sensor to report to Domoticz in case a read is missed
          DomoticzTempHumPressureSensor(bmp_temperature, bmp_humidity, bmp_pressure);
#ifdef USE_BME68X
          if (bmp_sensors[bmp_idx].bmp_model >= 3)
          {
            DomoticzSensor(DZ_AIRQUALITY, (uint32_t)bmp_sensors[bmp_idx].bmp_gas_resistance);
          }
#endif // USE_BME68X
        }
#endif // USE_DOMOTICZ

#ifdef USE_KNX
        if (0 == TasmotaGlobal.tele_period)
        {
          KnxSensor(KNX_TEMPERATURE, bmp_temperature);
          KnxSensor(KNX_HUMIDITY, bmp_humidity);
        }
#endif // USE_KNX

#ifdef USE_WEBSERVER
      }
      else
      {
        WSContentSend_Temp(name, bmp_temperature);
        if (bmp_sensors[bmp_idx].bmp_model >= 2)
        {
          WSContentSend_PD(HTTP_SNS_HUM, name, humidity);
          WSContentSend_PD(HTTP_SNS_DEW, name, dewpoint, TempUnit());
#ifdef USE_HEAT_INDEX
          WSContentSend_PD(HTTP_SNS_HEATINDEX, name, heatindex, TempUnit());
#endif // USE_HEAT_INDEX
        }
        WSContentSend_PD(HTTP_SNS_PRESSURE, name, pressure, PressureUnit().c_str());
        if (Settings->altitude != 0)
        {
          WSContentSend_PD(HTTP_SNS_SEAPRESSURE, name, sea_pressure, PressureUnit().c_str());
        }
#ifdef USE_BME68X
        if (bmp_sensors[bmp_idx].bmp_model >= 3)
        {
          WSContentSend_PD(PSTR("{s}%s " D_GAS "{m}%s " D_UNIT_KILOOHM "{e}"), name, gas_resistance);
          WSContentSend_PD(PSTR("{s}%s " D_AIR_QUALITY "{m}%d "), name, bmp_sensors[bmp_idx].bmp_iaq);
        }
#endif // USE_BME68X

#endif // USE_WEBSERVER
      }
    }
  }
}

#ifdef USE_DEEPSLEEP

void BMP_EnterSleep(void)
{
  if (DeepSleepEnabled())
  {
    for (uint32_t bmp_idx = 0; bmp_idx < bmp_count; bmp_idx++)
    {
      switch (bmp_sensors[bmp_idx].bmp_type)
      {
      case BMP180_CHIPID:
      case BMP280_CHIPID:
      case BME280_CHIPID:
        I2cWrite8(bmp_sensors[bmp_idx].bmp_address, BMP_REGISTER_RESET, BMP_CMND_RESET, bmp_sensors[bmp_idx].bmp_bus);
        break;
      default:
        break;
      }
    }
  }
}

#endif // USE_DEEPSLEEP

const char kBME68xCommands[] PROGMEM = "|" // No prefix
                                       "BME68xsave"
                                       "|"
                                       "BME68xclean"
                                       "|"
                                       "BME68xTempOffsets"
                                       "|"
                                       "BME68xHumOffsets";

void (*const BME68xCommand[])(void) PROGMEM = {
    &CmndBME68xSave, &CmndBME68xClean, &CmndBME68xTempOffset, &CmndBME68xHumOffset};

void CmndBME68xTempOffset()
{

  if ((XdrvMailbox.index >= 0) && (XdrvMailbox.index <= 3))
    if (bmp_sensors[XdrvMailbox.index].bmp_type == BME680_CHIPID)
    {
      if (XdrvMailbox.data_len > 0)
        bmp_sensors[XdrvMailbox.index].IaqTr.setTempOfs(CharToFloat(XdrvMailbox.data));
      ResponseCmndFloat(bmp_sensors[XdrvMailbox.index].IaqTr.getTemOfs(), 1);
    }
}

void CmndBME68xHumOffset()
{

  if ((XdrvMailbox.index >= 0) && (XdrvMailbox.index <= 3))
    if (bmp_sensors[XdrvMailbox.index].bmp_type == BME680_CHIPID)
    {
      if (XdrvMailbox.data_len > 0)
        bmp_sensors[XdrvMailbox.index].IaqTr.setHumOfs(CharToFloat(XdrvMailbox.data));
      ResponseCmndFloat(bmp_sensors[XdrvMailbox.index].IaqTr.getHumOfs(), 1);
    }
}

void CmndBME68xSave(void)
{
  if ((XdrvMailbox.index >= 0) && (XdrvMailbox.index <= 3))
    if (bmp_sensors[XdrvMailbox.index].bmp_type == BME680_CHIPID)
    {
      state_save(XdrvMailbox.index);
      ResponseCmndDone();
    }
}

void CmndBME68xClean(void)
{
  if ((XdrvMailbox.index >= 0) && (XdrvMailbox.index <= 3))
    if (bmp_sensors[XdrvMailbox.index].bmp_type == BME680_CHIPID)
    {
      bmp_sensors[XdrvMailbox.index].IaqTr.clean();
      ResponseCmndDone();
    }
}

void BMESettingsSave(void)
{
  for (uint32_t bmp_idx = 0; bmp_idx < bmp_count; bmp_idx++)
    if (bmp_sensors[bmp_idx].bmp_type == BME680_CHIPID)
      state_save(bmp_idx);
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

bool Xsns09(uint32_t function)
{
  if (!I2cEnabled(XI2C_10))
  {
    return false;
  }

  bool result = false;

  if (FUNC_INIT == function)
  {
    BmpDetect();
  }
  else if (bmp_count)
  {
    switch (function)
    {
    case FUNC_SAVE_AT_MIDNIGHT:
      BMESettingsSave();
      break;
    case FUNC_EVERY_250_MSECOND: // FUNC_EVERY_SECOND_LATE:
      //AddLog(LOG_LEVEL_DEBUG, PSTR("BME: %d rennt"),bmp_count);

      BmpRead();
      break;
    case FUNC_EVERY_SECOND: // FUNC_EVERY_SECOND_LATE:
      Bme680IaqCalc();
      break;
    case FUNC_JSON_APPEND:
      BmpShow(1);
      break;
#ifdef USE_WEBSERVER
    case FUNC_WEB_SENSOR:
      BmpShow(0);
      break;
#endif // USE_WEBSERVER
    case FUNC_SAVE_BEFORE_RESTART:
#ifdef USE_DEEPSLEEP
      // BMP_EnterSleep();                  ??????????????????????
      // bmp_deepsleep = 1;
#endif // USE_DEEPSLEEP
      BMESettingsSave();
      break;

    case FUNC_COMMAND:
      result = DecodeCommand(kBME68xCommands, BME68xCommand);
      break;
    }
  }
  else
    AddLog(LOG_LEVEL_DEBUG, PSTR("BME: No Devices found"));
  return result;
}

#endif // USE_BMP
#endif // USE_I2C
