var sensor = module('sensor')

import sht31
import sgp30


class DRIVER : Driver
  var sht3x, sgp30, s, settings  

  def init()
    wire2._begin_transmission(0)
    wire2._write(0x6)
    wire2._end_transmission()
    self.s = 0
    self.sht3x = sht31
    sht31.start(0x44)
    self.sgp30 = sgp30(0x58)
    #self.data=SENSOR_DATA()
    print("Sensor init")
  end

  def set_settings(settings)
    self.settings=settings
    self.sgp30.eco2_base=self.settings.eco2_base
    self.sgp30.tvoc_base=self.settings.tvoc_base
    if self.sgp30.eco2_base && self.sgp30.tvoc_base
      self.sgp30.set_iaq_baseline() 
      print("Write baseline ",self.sgp30.eco2_base,self.sgp30.tvoc_base)
    end
  end

  def every_second()
    self.sht3x.every_second()
    self.sgp30.sgp_read_measurement()
    if self.s==10 self.sgp30.set_humidity(int(self.sht3x.absoluteHumidity*256)) end
    if self.s==11 
      self.sgp30.get_iaq_baseline() 
      self.settings.eco2_base=self.sgp30.eco2_base
      self.settings.tvoc_base=self.sgp30.tvoc_base
      self.settings.save()
    end
    self.s += 1
    if self.s>1000 self.s=0 end
    self.sgp30.messure_iaq()
    #self.data.humidity=self.sht3x.humidity
    #, temperature, absoluteHumidity  tvoc, eco2
  end

  #- add sensor value to teleperiod -#
  def json_append()
    if !self.sht3x return nil end  #- exit if not initialized -#
    var t=self.sht3x.temperature
    var msg = string.format(",\"SHT3x\":{\"Temperature\":%i.%i,\"Humidity\":%i}",   t>>4,((t&0xf)*10)>>4,self.sht3x.humidity)
    tasmota.response_append(msg)
  end

  #- display sensor value in the web UI -#
  def web_sensor()
    if !self.sht3x || !self.sgp30 return nil end  #- exit if not insitialized -#
    
    var t=self.sht3x.temperature
    tasmota.web_send_decimal(string.format(
      "{s}Raumtemperatur{m}%i.%i °C{e}"..
      "{s}Raumfeuchte{m}%i %%{e}"..
      "{s}absolute Feuchte{m}%.1f g/m³{e}"..
      "{s}Tvoc{m}%i ppb{e}"..
      "{s}eCo2{m}%i ppm{e}"
      ,
      t>>4,((t&0xf)*10)>>4,self.sht3x.humidity,self.sht3x.absoluteHumidity,self.sgp30.tvoc,self.sgp30.eco2))
  end

end

sensor.driver = DRIVER()



return sensor

#d = DRIVER()
#tasmota.add_driver(d)