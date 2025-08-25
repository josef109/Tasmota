
class clock_gr
  var running
  var scr_haspm
  var scr_clock, scr_original
  var scale, scale_hour, scale_min, needle_min, needle_hour, needle_sec, hour_hand, minute_hand, led, led1, led2, led3, label, weather, temp, in_temp, in_hum, in_iaq
  var sec, min, hour
  var ser1 #, ser2

  def init(parent)
  end

  def start()
    if self.running
      return
    else
#      lv.start()
      if self.scr_clock == nil
        #self.scr_original = lv.scr_act()
        var scr_uhr = lv.obj(lv.layer_sys()) #lv.layer_top() 
        scr_uhr.set_style_radius(0, 0)
        scr_uhr.set_style_border_width(0, 0)
        scr_uhr.set_style_bg_opa(255, 0)
        scr_uhr.set_pos(0, 0)
        scr_uhr.set_width(lv.get_hor_res())
        scr_uhr.set_height(lv.get_ver_res())
        scr_uhr.set_scrollbar_mode(lv.SCROLLBAR_MODE_OFF)
        scr_uhr.add_event_cb(/->self.stop(), lv.EVENT_PRESSED, 0)
        self.scr_clock = scr_uhr
        lv.scr_load(self.scr_clock)
      end


      self.scr_clock.set_style_bg_color(lv.color(lv.COLOR_BLACK), lv.PART_MAIN | lv.STATE_DEFAULT)
      self.scr_clock.clean()
      self.scale = lv.scale(self.scr_clock)
      self.scale.set_mode(lv.SCALE_MODE_ROUND_INNER)
      self.scale.set_size(220, 220)
      #self.scale.center()
      self.scale.align(lv.ALIGN_TOP_MID, 0, 0)
      self.scale.set_style_line_color(lv.color(lv.COLOR_LIME), lv.PART_INDICATOR)
      self.scale.set_style_line_color(lv.color(lv.COLOR_LIME), lv.PART_ITEMS)
      self.scale.set_style_radius(lv.RADIUS_CIRCLE,0)
      self.scale.set_style_clip_corner(true,0)
      self.scale.set_angle_range(360)
      self.scale.set_range(0, 60)
      self.scale.set_rotation(270)
      self.scale.set_label_show(false)
      self.scale.set_total_tick_count(61)
      self.scale.set_major_tick_every(5)
      self.scale.set_style_length(18, lv.PART_INDICATOR)
      self.scale.set_style_length(8, lv.PART_ITEMS)
      self.scale.set_style_line_width(5, lv.PART_INDICATOR)
      self.scale.set_style_line_width(2, lv.PART_ITEMS)

      #self.scale.set_style_outline_width(1, lv.PART_INDICATOR)
      #self.scale.set_style_outline_pad(20, lv.PART_INDICATOR)
      
      self.minute_hand = lv.line(self.scale)
      self.minute_hand.set_style_line_width(5, 0)
      self.minute_hand.set_style_line_rounded(false, 0)
      self.minute_hand.set_style_line_color(lv.color(lv.COLOR_LIME), lv.PART_MAIN)
      
      self.scale.set_line_needle_value(self.minute_hand, 70, 5)
      
      self.hour_hand = lv.line(self.scale)
      self.hour_hand.set_style_line_width(7, 0)
      self.hour_hand.set_style_line_rounded(false, 0)
      self.hour_hand.set_style_line_color(lv.color(lv.COLOR_LIME), lv.PART_MAIN)
      
      self.scale.set_line_needle_value(self.hour_hand, 50, 15)
      
      self.needle_sec = lv.line(self.scale)
      self.needle_sec.set_style_line_width(2, 0)
      self.needle_sec.set_style_line_rounded(false, 0)
      self.needle_sec.set_style_line_color(lv.color(lv.COLOR_LIME), 0);
      
      self.scale.set_line_needle_value(self.needle_sec, 83, 30)
      
      self.led = lv.led(self.scale)
      self.led.center()
      self.led.set_style_border_width(5, lv.PART_MAIN)
      self.led.set_style_shadow_width(0, lv.PART_MAIN)

      self.led.set_color(lv.color(lv.COLOR_LIME))
#     self.led.set_brightness(255)
      self.led.on()


      self.led1 = lv.led(self.scale)
      self.led1.align(lv.ALIGN_LEFT_MID, 30, 0)
      self.led1.set_style_border_width(2, lv.PART_MAIN)
      self.led1.set_color(lv.color(lv.COLOR_LIME))
      self.led1.set_size(lv.pct(5), lv.pct(5))
      self.led1.on()
      self.led2 = lv.led(self.scale)
      self.led2.align(lv.ALIGN_LEFT_MID, 50, 0)
      self.led2.set_style_border_width(2, lv.PART_MAIN)
      self.led2.set_color(lv.color(lv.COLOR_LIME))
      self.led2.set_size(lv.pct(5), lv.pct(5))
      self.led2.off()
      self.led3 = lv.led(self.scale)
      self.led3.align(lv.ALIGN_LEFT_MID, 70, 0)
      self.led3.set_style_border_width(2, lv.PART_MAIN)
      self.led3.set_color(lv.color(lv.COLOR_LIME))
      self.led3.set_size(lv.pct(5), lv.pct(5))
      self.led3.off()

      self.label = lv.label(self.scale)
      self.label.set_text("Do 1")
      self.label.align(lv.ALIGN_RIGHT_MID, -30, 0)

#      self.label.set_pos(140,100)
#      self.label.set_size(80, 20)
      self.label.set_style_text_color(lv.color(lv.COLOR_LIME), lv.PART_MAIN)
#      var f28 = lv.montserrat_font(28)
      var f20 = lv.montserrat_font(20)
      var f14 = lv.montserrat_font(14)
      self.label.set_style_text_font(f20, lv.PART_MAIN | lv.STATE_DEFAULT)

      self.weather = lv.img(self.scale)
      self.weather.set_src("A:/floor.tapp#z-128-rainy.png")
      self.weather.set_zoom(150)
      self.weather.set_style_img_recolor_opa(255, 0)  # lv.PART_MAIN | lv.STATE_DEFAULT
      self.weather.set_style_img_recolor(lv.color(lv.COLOR_LIME), 0)    # lv.PART_MAIN | lv.STATE_DEFAULT
      self.weather.align(lv.ALIGN_TOP_MID, 0, -5)

      self.temp = lv.label(self.scale)
      self.temp.set_text("-20°C")
      self.temp.set_style_text_color(lv.color(lv.COLOR_LIME), lv.PART_MAIN)
      self.temp.set_style_text_font(f20, lv.PART_MAIN | lv.STATE_DEFAULT)
      self.temp.align(lv.ALIGN_BOTTOM_MID, 0, -35)

      self.in_temp = lv.label(self.scr_clock)
      self.in_temp.set_text("24,5 °C")
      self.in_temp.set_style_text_color(lv.color(lv.COLOR_LIME), lv.PART_MAIN)
      self.in_temp.set_style_text_font(f14, lv.PART_MAIN | lv.STATE_DEFAULT)
      self.in_temp.align(lv.ALIGN_BOTTOM_LEFT, 0, -30)
      self.in_hum = lv.label(self.scr_clock)
      self.in_hum.set_text("50 %")
      self.in_hum.set_style_text_color(lv.color(lv.COLOR_LIME), lv.PART_MAIN)
      self.in_hum.set_style_text_font(f14, lv.PART_MAIN | lv.STATE_DEFAULT)
      self.in_hum.align(lv.ALIGN_BOTTOM_LEFT, 0, -5)

      self.in_iaq = lv.chart(self.scr_clock)
      self.in_iaq.set_type(lv.CHART_TYPE_LINE)
      self.in_iaq.align(lv.ALIGN_BOTTOM_RIGHT, 10, 10)
      self.in_iaq.set_size(lv.pct(80), lv.pct(25))
      self.in_iaq.set_style_line_color(lv.color(0x404040), lv.PART_MAIN)
      self.in_iaq.set_style_border_width(0, lv.PART_MAIN)
      self.in_iaq.set_div_line_count(4, 4)
      self.in_iaq.set_update_mode(lv.CHART_UPDATE_MODE_SHIFT)
      if lv.version == 8
        self.in_iaq.set_style_size(0, lv.PART_INDICATOR) # don't show dots
      else
        self.in_iaq.set_style_size(0, 0, lv.PART_INDICATOR) # don't show dots
      end
      self.in_iaq.set_style_line_rounded(true, lv.PART_ITEMS)
      self.in_iaq.set_style_line_width(2, lv.PART_ITEMS) # don't show dots

      self.in_iaq.set_point_count(20)

      self.ser1 = self.in_iaq.add_series(lv.color(lv.COLOR_LIME), lv.CHART_AXIS_PRIMARY_Y)
#      self.ser2 = self.in_iaq.add_series(lv.color(lv.COLOR_GREEN), lv.CHART_AXIS_SECONDARY_Y)
      self.in_iaq.set_range(lv.CHART_AXIS_PRIMARY_Y, 0, 500)
#      self.in_iaq.set_range(lv.CHART_AXIS_SECONDARY_Y, 400, 2500)

#      self.in_iaq.set_color(lv.color(lv.COLOR_LIME))

      self.led1.add_flag(lv.OBJ_FLAG_HIDDEN)
      self.led3.add_flag(lv.OBJ_FLAG_HIDDEN)

      self.scr_clock.add_flag(lv.OBJ_FLAG_CLICKABLE)

      self.running = true
      self.cycle_clock()
      self.cycle_date()
      self.cycle_sensor()

    end
  end 

  # def update_leds()
  #   import global
  #   import persist
  #   import string

  #   var ch = persist.channel

  #   if ch == 0
  #   for i:0..2
  #       var ob = string.format("led%i", i+212)
  #       if (ch & (1 << i)) == 0
  #         global.(ob).toggle = false
  #       else
  #         global.(ob).toggle = true
  #       end
  #   end
  # end

  def set_weather(img)
    self.weather.set_src(img)
  end

  def set_temp(t)
    self.temp.set_text(t)
  end

  def cycle_clock()
    if !self.running  || self.scr_clock == nil return; end
    tasmota.set_timer(1300, /-> self.cycle_clock())
    self.update_clock()
  end

  def cycle_date()
    if !self.running  || self.scr_clock == nil return; end
    tasmota.set_timer(50000, /-> self.cycle_date())
    self.update_date()
  end

  def cycle_sensor()
    if !self.running  || self.scr_clock == nil return; end
    tasmota.set_timer(3000, /-> self.cycle_sensor())
    self.update_sensor()
  end

  def stop()
    import global
    if self.running || self.scr_clock != nil
      #lv.scr_load(self.scr_original)
      self.running = false
      self.scr_clock.clear_flag(lv.OBJ_FLAG_CLICKABLE)

      #self.scr_uhr.remove_event_cb(/->self.stop())
      self.scr_uhr.del()
      self.scr_uhr = nil
      global.p1.show()
    end    
  end

  def update_clock()
    var now = tasmota.time_dump(tasmota.rtc()['local'])
    #print("now",now)
    #print("now",tasmota.rtc()['local'])
    var h=now['hour']
    var m=now['min']
    var s=now['sec']
    if h>=12 h-=12 end
    h=h*5+m/12
    #print(now,days)
    if self.sec != s
      self.scale.set_line_needle_value(self.needle_sec, 105, s)
      self.sec = s
    end
    if self.min != m
      self.scale.set_line_needle_value(self.minute_hand, 90, m)
      self.min = m
    end
    if self.hour != h
      self.scale.set_line_needle_value(self.hour_hand, 50, h)
      self.hour = h
    end
  end

  def update_date()
    import string
    import global
    import json
    
    var now = tasmota.time_dump(tasmota.rtc()['local'])
    var d=now['weekday']
    var day=now['day']
    var days = ["So","Mo","Di","Mi","Do","Fr","Sa"]

    self.label.set_text(string.format("%s %i", days[d],day))
  end

  def update_sensor()
    import string
    import global
    import json
  
    var sensors = json.load(tasmota.read_sensors())
    if sensors.contains('SHT3X')
      if sensors['SHT3X'].contains('Temperature')
        self.in_temp.set_text(string.format("%.1f °C", sensors['SHT3X']['Temperature']))
      end
      if sensors['SHT3X'].contains('Humidity')
        self.in_hum.set_text(string.format("%.0f %%", sensors['SHT3X']['Humidity']))
      end
    end
    if sensors.contains('BME680')
      if sensors['BME680'].contains('IAQ')
        var iaq = sensors['BME680']['IAQ']
        self.in_iaq.set_next_value(self.ser1, iaq)
        if iaq > 100 
          if iaq < 150
            self.in_iaq.set_series_color(self.ser1,lv.color(lv.COLOR_YELLOW) )
          elif iaq < 200
            self.in_iaq.set_series_color(self.ser1,lv.color(lv.COLOR_ORANGE) )
          elif iaq < 250
            self.in_iaq.set_series_color(self.ser1,lv.color(lv.COLOR_RED) )
          elif iaq < 350
            self.in_iaq.set_series_color(self.ser1,lv.color(lv.COLOR_MAGENTA) )
          else
            self.in_iaq.set_series_color(self.ser1,lv.color(lv.COLOR_MAROON) )
          end
        else
          self.in_iaq.set_series_color(self.ser1,lv.color(lv.COLOR_LIME) )
        end
      end
    end
    var tas=tasmota.get_power() 
    if tas[0]==true
      self.led2.on()
    else
      self.led2.off()
    end
    if tas[1]==true
      self.led1.off()
    else
      self.led1.off()
     end
    if tas[2]==true
      self.led3.off()
    else
      self.led3.off()
    end

  end    

  def before_del()
    tasmota.remove_driver(self)
  end
end

return clock_gr


