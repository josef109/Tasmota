# This is a simple demo of displaying Renaissance Watch adapted for 480x480 displays
#
# Just install `haspmota_watch_480.tapp` in the filesystem
#
# Generate with
# rm haspmota_watch_480.tapp ; zip -j -0 haspmota_watch_480.tapp ../haspmota_src/haspmota_watch_480/*

if !tasmota.memory().contains("psram")
    print("HSP: Error: OpenHASP demo requires PSRAM")
    return
end

import string
import mqtt


class waste_screen

  var topic_waste 
  var topic_waste_pass 
  var waste_str
  var running, src_waste, scr_original, ren_back, ren_day, ren_waste

  def init()
    self.topic_waste = "homeassistant/sensor/muell/erinnerung"
    self.topic_waste_pass = "homeassistant/sensor/muell/passiv"
  end    

  def stop()
    if self.running || self.src_waste != nil
      lv.scr_load(self.scr_original)
      self.running = false
      self.src_waste.clear_flag(lv.OBJ_FLAG_CLICKABLE)
      self.src_waste.del()    
      tasmota.cmd("Backlog DisplayDimmer 10")
    end      
  end

  def pub()
    mqtt.publish(self.topic_waste_pass, "1")
  end
  
  def display_waste(w, d)
    if self.running
      return
    end
    var f28 = lv.font_embedded("robotocondensed", 24)  # load embedded Montserrat 28
  
    lv.start()
    self.scr_original = lv.scr_act()        # save the current screen to restore it later
    print("Hallo")
    self.scr_original.clean()

    self.src_waste = lv.obj(lv.layer_sys())                 # create a new temporary screen for the calibration
    self.src_waste.set_style_radius(0, 0)
    self.src_waste.set_style_border_width(0, 0)

    #self.src_waste.set_style_local_bg_color(lv.OBJ_PART_MAIN, lv.STATE_DEFAULT, lv.color(lv.COLOR_BLACK))
    #src_waste.set_style_bg_color(lv.color(0xD00000), lv.PART_MAIN | lv.STATE_DEFAULT)    # background #D00000

    self.src_waste.set_style_bg_opa(255, 0)
    self.src_waste.set_pos(0, 0)
    self.src_waste.set_width(lv.get_hor_res())
    self.src_waste.set_height(lv.get_ver_res())
    self.src_waste.move_background()  
    self.src_waste.clean()
    
    self.src_waste.add_event_cb(/->self.pub(), lv.EVENT_PRESSED, 0)
    self.src_waste.set_style_bg_color(lv.color(lv.COLOR_BLACK), lv.PART_MAIN | lv.STATE_DEFAULT)
    self.ren_back = lv.img(self.src_waste)
    var wd = tasmota.wd
    self.ren_back.set_src("A:/"+wd+"/blue.png")
    self.ren_back.set_style_img_recolor_opa(255, 0)
    self.ren_back.set_align(lv.ALIGN_CENTER)

    self.ren_day = lv.label(self.src_waste)
    #self.src_waste.clean()

    lv.scr_load(self.src_waste)

    if f28 != self.ren_day.set_style_text_font(f28, 0) end
    self.ren_day.set_style_text_color(lv.color(lv.COLOR_RED), lv.PART_MAIN)    
    self.ren_day.set_text(w)
    self.ren_day.align(lv.ALIGN_BOTTOM_MID, 0, -50)
    #self.ren_day.set_x(80)
    self.src_waste.add_flag(lv.OBJ_FLAG_CLICKABLE)
    self.running = true
    var z = "niemals"
    if d == "1"
      z = "morgen"
    elif d == "0"
      z = "heute"
    end
    var ren_waste = lv.label(self.src_waste)
    ren_waste.set_text(z)
    ren_waste.set_align(lv.ALIGN_BOTTOM_MID)
    if f28 != ren_waste.set_style_text_font(f28, 0) end
    ren_waste.set_style_text_color(lv.color(lv.COLOR_RED), lv.PART_MAIN)    
    #ren_waste.set_y(10)
    tasmota.cmd("Backlog DisplayDimmer 80")
    print("ja an")
    print(d)
  end

  def waste_cb(a,dummy,data)

    if a == nil
      return
    end
    
    print(data)
    try
      self.waste_str = string.split(data, " ") 
      print(self.waste_str)
      self.display_waste(self.waste_str[0], self.waste_str[2])
      print("an")
    except .. as e, m
      print(e,m)
      print("aus")
      self.stop()
    end

    # print(a,dummy,data)
    # print(self.waste_str)
    return true
  end

  def subscribes()
    mqtt.unsubscribe()
    mqtt.subscribe(self.topic_waste, / a,dummy,data -> self.waste_cb(a,dummy,data))
    print("subsc")
  end

end

waste = waste_screen()

waste.init()

waste.subscribes()

