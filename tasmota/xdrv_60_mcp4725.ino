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

  if (I2cSetDevice(USE_MCP4725_ADDR))
  {
    mcp4725_detected = true;
    I2cSetActiveFound(USE_MCP4725_ADDR, "MCP4725");
    MCP4725_Reset(); // Reset the controller
  }
}

void MCP4725_Reset(void)
{
  MCP4725_setVoltage(0);
  Response_P(PSTR("{\"MCP4725\":{\"RESET\":\"OK\"}}"));
}

void MCP4725_setVoltage(uint16_t output)
{

  uint8_t reg = MCP4725_CMD_WRITE_FAST_MODE | MCP4725_NORMAL_MODE; //
  reg |= (output >> 8) & 0xf;
  uint16_t val = output << 8;
  I2cWrite8(USE_MCP4725_ADDR, reg, val); //
  mcp4725_dac_value = output;
}

bool MCP4735SendUpdateCommandIfRequired(void)
{
  uint8_t light_state_dimmer = light_state.getDimmer();
  // Dimming acts odd below 10% - this mirrors the threshold set on the faceplate itself
  light_state_dimmer = (light_state_dimmer < Settings->dimmer_hw_min) ? Settings->dimmer_hw_min : light_state_dimmer;
  light_state_dimmer = (light_state_dimmer > Settings->dimmer_hw_max) ? Settings->dimmer_hw_max : light_state_dimmer;

  MCP4725_setVoltage(light_state_dimmer);
  return true;
}


void MCP4725_OutputTelemetry(bool telemetry)
{
  ResponseTime_P(PSTR(",\"MCP4725\":{\"Value\":%i,"), mcp4725_dac_value);
  ResponseAppend_P(PSTR("\"END\":1}}"));
  if (telemetry)
  {
    MqttPublishTeleSensor();
  }
}

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
    case FUNC_EVERY_SECOND:
      if (TasmotaGlobal.tele_period == 0)
      {
        MCP4725_OutputTelemetry(true);
      }
      break;

    case FUNC_SET_DEVICE_POWER:
    case FUNC_SET_CHANNELS:
      result = MCP4735SendUpdateCommandIfRequired();
      break;
    }
  }
  return result;
}

#endif // USE_MCP4725
#endif // USE_IC2
