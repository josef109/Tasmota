var uhr = module('uhr')

uhr.init = def (m)
  class UHR
    var running
    var scr_original
    var scr_uhr
    var meter, scale_hour, scale_min, needle_min, needle_hour, needle_sec

    def init()
      lv.start()
      self.running = false

      self.scr_uhr =  lv.obj(0)

      self.scr_uhr.set_style_bg_color(lv.color(0x000010), lv.PART_MAIN | lv.STATE_DEFAULT)
      #ren_back = lv.img(scr)
  
      self.meter = lv.meter(self.scr_uhr)
      self.meter.set_size(220, 220)
      self.meter.center()
  
      # Create another scale for the hours. It's only visual and contains only major ticks
      self.scale_hour = self.meter.add_scale()
      self.meter.set_scale_ticks(self.scale_hour, 12, 0, 0, lv.color(lv.COLOR_GRAY))  # 12 ticks
      self.meter.set_scale_major_ticks(self.scale_hour, 1, 2, 20, lv.color_black(), 10)         # Every tick is major
      self.meter.set_scale_range(self.scale_hour, 1, 12, 330, 300)                             # [1..12] values in an almost full circle
  
  
      # Create a scale for the minutes
      # 61 ticks in a 360 degrees range (the last and the first line overlaps)
      self.scale_min = self.meter.add_scale()
      self.meter.set_scale_ticks(self.scale_min, 61, 1, 10, lv.color(lv.COLOR_GRAY))
      self.meter.set_scale_range(self.scale_min, 0, 60, 360, 270)
  
      # Add a needle line indicator
      self.needle_min = self.meter.add_needle_line(self.scale_min, 4, lv.color_black(), -10)
      self.needle_hour = self.meter.add_needle_line(self.scale_min, 5, lv.color_black(), -25)
      self.needle_sec = self.meter.add_needle_line(self.scale_min, 2, lv.color(lv.COLOR_RED), -5)
      self.meter.set_indicator_value(self.needle_min, 5)
      self.meter.set_indicator_value(self.needle_hour, 10)
    end

    def start()
      if self.running
        return
      else
       
        self.scr_original = lv.scr_act()
        #self.scr_uhr = lv.obj(0)
        lv.scr_load(self.scr_uhr)
        self.meter.add_event_cb(/->self.stop(), lv.EVENT_CLICKED, nil)
        self.running = true
        self.cycle()
      end
    end 

    def cycle()
      if !self.running return; end
      tasmota.set_timer(1300, /->self.cycle())
      self.update_watch()
    end

    def stop()
      if self.running 
        lv.scr_load(self.scr_original)
        self.running = false
        #self.scr_uhr.remove_event_cb(/->self.stop())
        #self.scr_uhr.del()
        #self.scr_uhr = nil
      end    
    end

    def update_watch()
      var now = tasmota.time_dump(tasmota.rtc()['local'])
      var h=now['hour']
      var m=now['min']

      if h>=12 h-=12 end
      h=h*5+m/12
      #print(now)
      self.meter.set_indicator_value(self.needle_min, m)
      self.meter.set_indicator_value(self.needle_hour, h)
      self.meter.set_indicator_value(self.needle_sec, now['sec'])
    end    
  end
  return UHR()
end

return uhr
