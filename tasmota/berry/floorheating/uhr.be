import persist

class controller
  static settings = persist
  var target_temp

  def set_temp(target)
      self.settings.dest_temp=target
      self.settings.save()
      print("Huraa")
  end

  def get_temp()
      return self.settings.dest_temp
  end
end

lv.start()

tasmota.cmd("DisplayDimmer 20")

hres = lv.get_hor_res()       # should be 320
vres = lv.get_ver_res()       # should be 240

scr = lv.scr_act()            # default screean object
f20 = lv.montserrat_font(20)  # load embedded Montserrat 20
#f40 = lv.montserrat_font(40)
f16 = lv.seg7_font(28)
 
scr.clean()

#scr.set_style_bg_color(lv.color(0x000010), lv.PART_MAIN | lv.STATE_DEFAULT)
#ren_back = lv.img(scr)

meter = lv.meter(scr)
meter.set_size(220, 220)
meter.center()

# Create another scale for the hours. It's only visual and contains only major ticks
scale_hour = meter.add_scale()
meter.set_scale_ticks(scale_hour, 12, 0, 0, lv.color(lv.COLOR_GRAY))  # 12 ticks
meter.set_scale_major_ticks(scale_hour, 1, 2, 20, lv.color_black(), 10)         # Every tick is major
meter.set_scale_range(scale_hour, 1, 12, 330, 300)                             # [1..12] values in an almost full circle


# Create a scale for the minutes
# 61 ticks in a 360 degrees range (the last and the first line overlaps)
scale_min = meter.add_scale()
meter.set_scale_ticks(scale_min, 61, 1, 10, lv.color(lv.COLOR_GRAY))
meter.set_scale_range(scale_min, 0, 60, 360, 270)

# Add a needle line indicator
needle_min = meter.add_needle_line(scale_min, 4, lv.color_black(), -10)
needle_hour = meter.add_needle_line(scale_min, 5, lv.color_black(), -25)
needle_sec = meter.add_needle_line(scale_min, 2, lv.color(lv.COLOR_RED), -5)
meter.set_indicator_value(needle_min, 5)
meter.set_indicator_value(needle_hour, 10)

t = controller()
#t.set_temp(250)
print(t.get_temp())


def update_watch()
    var now = tasmota.time_dump(tasmota.rtc()['local'])
    var h=now['hour']
    var m=now['min']

    if h>12 h=h-12 end
    h=h*5+m/12
    #print(now)
    meter.set_indicator_value(needle_min, m)
    meter.set_indicator_value(needle_hour, h)
    meter.set_indicator_value(needle_sec, now['sec'])
    tasmota.set_timer(1300, update_watch)
  end
  update_watch()
  