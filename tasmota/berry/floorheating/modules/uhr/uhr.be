
class uhr
  var running
  var scr_original
  var scr_uhr
  var scale, scale_hour, scale_min, needle_min, needle_hour, needle_sec, hour_hand, minute_hand
  var sec, min, hour

  def init(parent)
    super(self).init(parent)

    self.set_width(parent.get_width())
    self.set_pos(0, 0)

    self.set_style_bg_color(lv.color(0x000000), lv.PART_MAIN | lv.STATE_DEFAULT)
    self.set_style_bg_opa(100, lv.PART_MAIN | lv.STATE_DEFAULT)
    self.move_background()
    self.set_style_border_opa(255, lv.PART_MAIN | lv.STATE_DEFAULT)
    self.set_style_radius(0, lv.PART_MAIN | lv.STATE_DEFAULT)
    self.set_style_pad_all(2, lv.PART_MAIN | lv.STATE_DEFAULT)
    self.set_style_border_color(lv.color(0x0099EE), lv.PART_MAIN | lv.STATE_DEFAULT)
    self.set_style_border_width(1, lv.PART_MAIN | lv.STATE_DEFAULT)

    self.set_style_text_color(lv.color(0xFFFFFF), lv.PART_MAIN | lv.STATE_DEFAULT)
    self.set_long_mode(lv.LABEL_LONG_CLIP)
    var lg_font = lv.font_montserrat(14)
    self.set_style_text_font(lg_font, lv.PART_MAIN | lv.STATE_DEFAULT)

    self.add_event_cb(/->self.before_del(), lv.EVENT_DELETE, 0)   # register `before_del` to be called when object is deleted
    tasmota.add_driver(self)
  end
  



  def start()
    if self.running
      return
    else
      lv.start()
      #print(lv.is_double_buffered())
      if self.scr_uhr == nil
        self.scr_original = lv.scr_act()
        var scr_uhr = lv.obj(lv.layer_sys()) #lv.layer_top() 
        scr_uhr.set_style_radius(0, 0)
        scr_uhr.set_style_border_width(0, 0)
        scr_uhr.set_style_bg_opa(255, 0)
        scr_uhr.set_pos(0, 0)
        scr_uhr.set_width(lv.get_hor_res())
        scr_uhr.set_height(lv.get_ver_res())
        print(lv.get_ver_res())
        print(lv.get_hor_res())
        
        scr_uhr.add_event_cb(/->self.stop(), lv.EVENT_PRESSED, 0)
        self.scr_uhr = scr_uhr
        lv.scr_load(self.scr_uhr)
      end

      self.scr_uhr.set_style_bg_color(lv.color(lv.COLOR_BLACK), lv.PART_MAIN | lv.STATE_DEFAULT)
      self.scr_uhr.clean()
      #ren_back = lv.img(scr)
      self.scale = lv.scale(self.scr_uhr)
      self.scale.set_mode(lv.SCALE_MODE_ROUND_INNER)
      self.scale.set_size(220, 220)
      self.scale.center()
      self.scale.set_style_radius(lv.RADIUS_CIRCLE,0)
      self.scale.set_style_clip_corner(true,0)
      self.scale.set_angle_range(360)
      self.scale.set_range(0, 60)
      self.scale.set_rotation(270)
      self.scale.set_label_show(false)
      self.scale.set_total_tick_count(61)
      self.scale.set_major_tick_every(5)
      self.scale.set_style_length(8, lv.PART_INDICATOR)
      self.scale.set_style_length(8, lv.PART_ITEMS)
      self.scale.set_style_line_width(5, lv.PART_INDICATOR)
      #scale.set_arc_width(5)
      self.minute_hand = lv.line(self.scale)
      self.minute_hand.set_style_line_width(10, 0)
      self.minute_hand.set_style_line_rounded(True, 0)
      #minute_hand.set_points_mutable(minute_hand_points, 2);
      #self.scale.set_line_needle_value(self.minute_hand, 50, 5)
      self.hour_hand = lv.line(self.scale)
      self.hour_hand.set_style_line_width(10, 0)
      self.hour_hand.set_style_line_rounded(True, 0)
      #self.scale.set_line_needle_value(self.hour_hand, 90, 20)
      self.needle_sec = lv.line(self.scale)
      self.needle_sec.set_style_line_width(2, 0)
      self.needle_sec.set_style_line_rounded(True, 0)
      self.needle_sec.set_style_line_color(lv.color(lv.COLOR_RED), 0);
      
      
      # Create another scale for the hours. It's only visual and contains only major ticks
      #self.scale_hour = self.meter.add_scale()
      #self.meter.set_scale_ticks(self.scale_hour, 12, 0, 0, lv.color(lv.COLOR_GRAY))  # 12 ticks
      #self.meter.set_scale_major_ticks(self.scale_hour, 1, 2, 20, lv.color_black(), 10)         # Every tick is major
      #self.meter.set_scale_range(self.scale_hour, 1, 12, 330, 300)                             # [1..12] values in an almost full circle
  
  
      # Create a scale for the minutes
      # 61 ticks in a 360 degrees range (the last and the first line overlaps)
      #self.scale_min = self.meter.add_scale()
      #self.meter.set_scale_ticks(self.scale_min, 61, 1, 10, lv.color(lv.COLOR_GRAY))
      #self.meter.set_scale_range(self.scale_min, 0, 60, 360, 270)
  
      # Add a needle line indicator
      #self.needle_min = self.meter.add_needle_line(self.scale_min, 4, lv.color_black(), -10)
      #self.needle_hour = self.meter.add_needle_line(self.scale_min, 5, lv.color_black(), -25)
      #self.needle_sec = self.meter.add_needle_line(self.scale_min, 2, lv.color(lv.COLOR_RED), -5)
      #self.meter.set_indicator_value(self.needle_min, 5)
      #self.meter.set_indicator_value(self.needle_hour, 10)
    
      #self.scr_original = lv.scr_act()
      #self.scr_uhr = lv.obj(0)
      #lv.scr_load(self.scr_uhr)
      self.scr_uhr.add_flag(lv.OBJ_FLAG_CLICKABLE)

      self.running = true
      self.cycle()
    end
  end 

  def cycle()
    if !self.running  || self.scr_uhr == nil return; end
    tasmota.set_timer(1300, /-> self.cycle())
    self.update_watch()
  end

  def stop()
    if self.running || self.scr_uhr != nil
      lv.scr_load(self.scr_original)
      self.running = false
      self.scr_uhr.clear_flag(lv.OBJ_FLAG_CLICKABLE)

      #self.scr_uhr.remove_event_cb(/->self.stop())
      #self.scr_uhr.del()
      #self.scr_uhr = nil
    end    
  end

  def update_watch()
    var now = tasmota.time_dump(tasmota.rtc()['local'])
    var h=now['hour']
    var m=now['min']
    var s=now['sec']

    if h>=12 h-=12 end
    h=h*5+m/12
    #print(now)
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
    
    #self.meter.set_indicator_value(self.needle_min, m)
    #self.meter.set_indicator_value(self.needle_hour, h)
    #self.meter.set_indicator_value(self.needle_sec, now['sec'])
  end    

  def before_del()
    tasmota.remove_driver(self)
  end
end

return uhr


