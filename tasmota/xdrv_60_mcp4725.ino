/*
  xdrv_15_mcp4725.ino - Support for I2C MCP4725 12bit 16 pin hardware PWM driver on Tasmota

  Copyright (C) 2021  Andre Thomas and Theo Arends

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
#ifdef USE_MCP4725
/*********************************************************************************************\
 * MPC4725 - 12-Bit Digital-to-Analog Converter
 *
 * I2C Address: 0x62
\*********************************************************************************************/

#define XDRV_60 60
#define XI2C_01 1 // See I2CDEVICES.md

#define MCP4725_I2CADD_DEFAULT 0x62 //A0-Pin ohne Beschaltung
#define MCP4725_I2CADD_A0_VDD 0x63  //A0-Pin auf VDD

#define MCP4725_CMD_WRITE_FAST_MODE 0x00
#define MCP4725_CMD_WRITE_DAC_REG 0x40
#define MCP4725_CMD_WRITE_DAC_REG_AND_EEPROM 0x60

#define MCP4725_NORMAL_MODE 0x00
#define MCP4725_POWER_DOWN_1K 0x10
#define MCP4725_POWER_DOWN_100K 0x20
#define MCP4725_POWER_DOWN_500K 0x30

#define MCP4725_EEPROM_READY 0x80

#define MCP4725_NO_EEPROM 0
#define MCP4725_WRITE_EEPROM 1

#ifndef USE_MCP4725_ADDR
#define USE_MCP4725_ADDR 0x62
#endif

bool mcp4725_detected = false;
//uint16_t mcp4725_freq = USE_MCP4725_FREQ;
uint16_t mcp4725_dac_value;


void MCP4725_Detect(void)
{
  if (I2cActive(USE_MCP4725_ADDR))
  {
    return;
  }

  if (I2cSetDevice(USE_MCP4725_ADDR, 0))
  {
    mcp4725_detected = true;
    I2cSetActiveFound(USE_MCP4725_ADDR, "MCP4725",0);
    MCP4725_Reset(); // Reset the controller
  }
}

void MCP4725_Reset(void)
{
  mcp4725_dac_value = 0x800;
  MCP4735SendUpdateCommandIfRequired();
  Response_P(PSTR("{\"MCP4725\":{\"RESET\":\"OK\"}}"));
}

void MCP4725_setVoltage(uint16_t output)
{
  

  if (mcp4725_dac_value != output)
  {
    uint8_t reg = MCP4725_CMD_WRITE_FAST_MODE | MCP4725_NORMAL_MODE; //
    reg |= (output >> 8) & 0xf;
    I2cWrite8(USE_MCP4725_ADDR, reg, output); //

    mcp4725_dac_value = output;
    // AddLog(LOG_LEVEL_INFO, PSTR("Adwert %d"), output);
  }
}

bool MCP4735SendUpdateCommandIfRequired(void)
{
  uint8_t light_state_dimmer = LightGetDimmer(1);
  // Dimming acts odd below 10% - this mirrors the threshold set on the faceplate itself
  light_state_dimmer = (light_state_dimmer < Settings->dimmer_hw_min) ? Settings->dimmer_hw_min : light_state_dimmer;
  light_state_dimmer = (light_state_dimmer > Settings->dimmer_hw_max) ? Settings->dimmer_hw_max : light_state_dimmer;
  uint8_t power = LightPower();
  if(power == 0)
    light_state_dimmer = 0;

  uint32_t temp = (light_state_dimmer << 12) / 100;    // 100 -> 4095, 0 -> 0
  if (temp >= 0xfff)
    temp = 0xfff;
  MCP4725_setVoltage(temp);
  return true;
}

/* void MCP4725_OutputTelemetry(bool telemetry)
{
  uint8_t buf[3];
  uint16_t x;
  I2cReadBuffer_or(USE_MCP4725_ADDR, buf, sizeof(buf));

  // mcp4725_dac_value = buf[1] << 8 + buf[2];
  // mcp4725_dac_value >>= 4;

  x = buf[1];
  x <<= 4;
  x += buf[2] >> 4;
  ResponseTime_P(PSTR(",\"MCP4725\":{\"Value\":%04x,"), x);
  ResponseAppend_P(PSTR("\"END\":1}}"));
  if (telemetry)
  {
    MqttPublishTeleSensor();
  }
} */

bool Xdrv60(uint8_t function)
{
  if (!I2cEnabled(XI2C_01))
  {
    return false;
  }

  bool result = false;

  if (FUNC_INIT == function)
  {
    MCP4725_Detect();
  }
  else if (mcp4725_detected)
  {
    switch (function)
    {
  /*   case FUNC_EVERY_SECOND:
      if (TasmotaGlobal.tele_period == 0)
      {
        MCP4725_OutputTelemetry(true);
      }
      break; */

    //case FUNC_SET_DEVICE_POWER:
    case FUNC_SET_CHANNELS:
      result = MCP4735SendUpdateCommandIfRequired();
      break;
    }
  }
  return result;
}

#endif // USE_MCP4725
#endif // USE_IC2
