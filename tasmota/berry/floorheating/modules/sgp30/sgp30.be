import persist
import global

#sgp30 = module("sgp30")

#sgp30.init = def (m)

  class MY_SGP30 : Driver
    var addr
    var serial, wire, tvoc_base, eco2_base
    var tvoc, tvoc_filt, eco2, eco2_filt
    var timer
    var error
    
    def sgp_write_word(data)
      if !self.wire return nil end  #- exit if not initialized -#
      self.wire._begin_transmission(self.addr)
      self.wire._write(data>>8)
      self.wire._write(data)
      self.wire._end_transmission()
    end
  
    def iaq_init()
      self.sgp_write_word(0x2003)
    end
  
    def messure_iaq()
      self.sgp_write_word(0x2008)
    end
  
    def restart()
      import sensorutil

      self.error=0
      self.wire = tasmota.wire_scan(self.addr)
      if !self.wire self.wire=nil; return nil end
      self.sgp_write_word(0x3682)     # get serial ID
      var serial=sensorutil.read_words(self.wire,self.addr, 3)
      if serial!=[]
        print("sgp serial: ",serial)
      else
        print("init sgp30 failed")
        self.wire=nil
        return nil     #- wrong device -#
      end
      self.sgp_write_word(0x202f)    # get feature set”
      var fs=sensorutil.read_words(self.wire,self.addr, 1)
      print("sgp feature set: ",fs)
      if fs!=[34] 
        print("Wrong feature set")
        self.wire=nil; 
        return nil 
      end
      self.set_iaq_baseline()
      
      #self.iaq_init()
      self.messure_iaq()
      return true
    end

    def init(addr)
      #import persist
      self.addr=addr
      self.timer=0
      self.tvoc=0
      self.eco2=0
      self.tvoc_filt=0
      self.eco2_filt=0
      self.restart()
    end
  
    def sgp_write_2_16(command,p1,p2)
      import sensorutil
      if !self.wire return nil end  #- exit if not initialized -#
      self.wire._begin_transmission(self.addr)
      self.wire._write(command>>8)
      self.wire._write(command&0xff)
      self.wire._write(p1>>8)
      self.wire._write(p1&0xff)
      self.wire._write(sensorutil.compute_crc(p1))  
      if p2 
        self.wire._write(p2>>8)
        self.wire._write(p2&0xff)
        self.wire._write(sensorutil.compute_crc(p2))
      end
      self.wire._end_transmission()
    end
  
    def set_humidity(h)
      self.sgp_write_2_16(0x2061,h)
    end
  
    def set_iaq_baseline()
      self.iaq_init()
      if persist.eco2_base && persist.tvoc_base
        var eco2_base=persist.eco2_base
        var tvoc_base=persist.tvoc_base
        print("set base:",eco2_base, tvoc_base)
        self.sgp_write_2_16(0x201e,tvoc_base,eco2_base) 
      end
    end
  
    def get_iaq_baseline()
      import sensorutil
      
      self.sgp_write_word(0x2015)
      var r=sensorutil.read_words(self.wire,self.addr, 2)
      if r!=[]
        self.eco2_base=r[0]
        self.tvoc_base=r[1]
        print("base:",r)
        persist.eco2_base=self.eco2_base
        persist.tvoc_base=self.tvoc_base
        persist.save()
      else
        print("Baseline read failed")
      end
    end
  
    def sgp_read_measurement()
      import sensorutil
      if !self.wire return nil end  #- exit if not initialized -#
      var r= sensorutil.read_words(self.wire,self.addr, 2)
      if r!=[]
        self.eco2=r[0]
        self.tvoc=r[1]
        self.tvoc_filt -= self.tvoc_filt >> 3
        self.tvoc_filt += self.tvoc
        self.eco2_filt -= self.eco2_filt >> 3
        self.eco2_filt += self.eco2
      else
        print("read sgp30 messure failed")
        self.error+=1
        if self.error>10
          self.wire=nil
        end
      end
    end
    
  #- add sensor value to teleperiod -#
  def json_append()
    import string
  
    var msg = string.format(",\"SGP30\":{\"Tvoc\":%i,\"eCO2\":%i}", self.tvoc_filt >> 3,self.eco2)
    tasmota.response_append(msg)
  end

  #- display sensor value in the web UI -#
  def web_sensor()
    import string

    tasmota.web_send_decimal(string.format(
      "{s}Tvoc{m}%i ppb{e}"..
      "{s}eCO2{m}%i ppm{e}"
      ,
      self.tvoc,self.eco2))
  end

    def every_second()
      #import global
      if !self.wire
        self.restart()
        return;
      end
      self.sgp_read_measurement()
      global.sgp_tvoc=self.tvoc
      global.sgp_eco2=self.eco2
      if self.timer & 0xff == 60 && global.sht31_absoluteHumidity
          self.set_humidity(int(global.sht31_absoluteHumidity*256)) 
      end
      if self.timer==600
        self.get_iaq_baseline() 
      end
      self.timer += 1
      if self.timer>10000 self.timer=0 end
      self.messure_iaq()
    end
  end
#  return MY_SGP30()
#end
sgp30=MY_SGP30(0x58)
tasmota.add_driver(sgp30)


return sgp30