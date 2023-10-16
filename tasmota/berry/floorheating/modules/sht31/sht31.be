
import global
#sht31 = module("sht31")
#sht31.init = def (m)
 

  class MY_SHT31 : Driver
    var addr
    var wire                   # contains the wire object if the device was detected
    var humidity
    var temperature
    var absoluteHumidity
    var timer
    var error
  
    def sht_write_word(data)
      if !self.wire return nil end  #- exit if not initialized -#
      self.wire._begin_transmission(self.addr)
      self.wire._write(data>>8)
      self.wire._write(data)
      self.wire._end_transmission()
    end
      
    def sht_read_bytes(len)
      if !self.wire || !len || len==0 return nil end
      self.wire._request_from(self.addr,len)
      var r = bytes(-len)
  
      for i: 0 .. len-1
        r[i] = self.wire._read()
      end
      print(r)
      return r
    end

    def reset()
      self.sht_write_word(0x30a2)
    end
  
    def restart()
      self.error=0
      self.wire = tasmota.wire_scan(self.addr)
      if !self.wire 
        print("nix gefunden bei:",self.addr) 
        return nil 
      end
      self.reset()
      self.sht_write_word(0xf32d)   # read status register
      var status=sensorutil.read_words(self.wire, self.addr,1)
      print(status)
      if status!=[] && (status[0] & 0xfc1f) == 0x8010
        self.start_mesurement()
        return true
      end
      print("Init sht31 failed")
      self.wire=nil
      return nil
    end

    def init(addr)
      #import global

      self.addr=addr
      self.timer=0
      self.humidity=0
      self.temperature=0
      self.absoluteHumidity=0.0
      #log("A",LOG_LEVEL_ERROR)
      self.restart()
    end
    
    def calc_absolute_humidity()
      import math


      var mw = 18.01534 	# molar mass of water g/mol
      var r = 8.31447215 	# Universal gas constant J/mol/K
      var t = self.temperature/16.0
      var temp = math.pow(2.718281828, (17.67 * t) / (t + 243.5))
      self.absoluteHumidity = (6.112 * temp * self.humidity * mw) / ((273.15 + t) * r) 
      global.sht31_absoluteHumidity=self.absoluteHumidity
    end
  
    def start_mesurement()
      self.sht_write_word(0x2400)
    end
  
    def sht_read_measurement()
      import sensorutil
      #import global

      if !self.wire return nil end  #- exit if not initialized -#
      var m=sensorutil.read_words(self.wire,self.addr,2)
      #print(m)
      if m==[] 
        print("read messurement sht failed")
        self.error+=1
        if self.error>10
          self.wire=nil
        end
        return nil 
      end
      self.temperature=((m[0]*175)>>12)-752       # 720 -> 752
      self.humidity=int(m[1]/655.35) + 4
      global.sht31_temperature=self.temperature
      global.sht31_humidity=self.humidity
      #print("mess:",self.temperature>>4,((self.temperature&0xf)*10)>>4,self.humidity)
      #print("t: ",tt," h: ",self.humidity," a: ",self.absoluteHumidity)
      #print("m:",(t >> 1)*875-45,h)
      #print("m:",t/37.4485714286-450.0,h*1000/0xffff)
      #print("m2:",(t*175.0)/65535.0-45.0,h*100.0/65535.0)
    end
  
     #- add sensor value to teleperiod -#
  def json_append()
    import string

    var t=self.temperature
    var msg = string.format(",\"SHT3x\":{\"Temperature\":%i.%i,\"Humidity\":%i}",   t>>4,((t&0xf)*10)>>4,self.humidity)
    tasmota.response_append(msg)
  end

  #- display sensor value in the web UI -#
  def web_sensor()
    import string
    
    var t=self.temperature
    tasmota.web_send_decimal(string.format(
      "{s}Raumtemperatur{m}%i.%i °C{e}"..
      "{s}Raumfeuchte{m}%i %%{e}"..
      "{s}absolute Feuchte{m}%.1f g/m³{e}",
      t>>4,((t&0xf)*10)>>4,self.humidity,self.absoluteHumidity))
  end

    def every_second()
      if self.wire 
        self.sht_read_measurement()     
        if self.timer==50
          self.calc_absolute_humidity()   # nicht jede s
        end
        self.start_mesurement()
      else
        self.restart()
      end
      if self.timer>=100
        self.timer=0
      else
        self.timer+=1
      end
    end
  end
#  return MY_SHT31()
#end
sht31=MY_SHT31(0x44)
tasmota.add_driver(sht31)

return sht31