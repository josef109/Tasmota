#var mainscreen = module('mainscreen')
import string
import persist
import global


class MAINSCREEN #: Driver
  var hres, vres
  var scr, f20, f16
  var stat_line, wifi_icon#, clock_icon
  var btn_style, up_btn, down_btn, prev_label, next_label
  var t_arc, t_act_label, c_label, t_des_label
  var ledstyle, led1, led1img, led2, led2img, led3, led3img
  var heat_image
  var right_bar, left_bar, left_value, right_value
  #var settings
  var timer, inactive, minutes

  def init()
    self.timer=0
    self.inactive=0
    self.minutes=-1
#- start LVGL and init environment -#
    lv.start()

    self.screen_normal()
    #self.settings=persist

    self.hres = lv.get_hor_res()       # should be 320
    self.vres = lv.get_ver_res()       # should be 240

    self.scr = lv.scr_act()            # default screean object
    self.f20 = lv.montserrat_font(20)  # load embedded Montserrat 20
    #f40 = lv.montserrat_font(40)
    self.f16 = lv.seg7_font(28)
 
    self.scr.clean()

    self.scr.set_style_bg_color(lv.color(0x000010), lv.PART_MAIN | lv.STATE_DEFAULT)
    self.statusLine()
    self.buttons()
    self.temperatureArc()
    self.temp_des()
    self.bar()
    self.led()

    #self.set_temp_dest()

    self.up_btn.add_event_cb(/->self.btn_up_clicked_cb(), lv.EVENT_CLICKED, nil)
    self.down_btn.add_event_cb(/->self.btn_down_clicked_cb(), lv.EVENT_CLICKED, nil)
    self.t_arc.add_event_cb(/->self.dest_temp_changed_cb(), lv.EVENT_VALUE_CHANGED, nil)
    self.get_settings()
    self.update_ui()

  end


  def statusLine()
    #self.update_ui()

#- Upper state line -#
    self.stat_line = lv.label(self.scr)
    if self.f20 != nil self.stat_line.set_style_text_font(self.f20, lv.PART_MAIN | lv.STATE_DEFAULT) end
    self.stat_line.set_long_mode(lv.LABEL_LONG_SCROLL)                                        # auto scrolling if text does not fit
    self.stat_line.set_width(self.hres)
    self.stat_line.set_align(lv.TEXT_ALIGN_LEFT)                                              # align text left
    self.stat_line.set_style_bg_color(lv.color(0x1fa3ec), lv.PART_MAIN | lv.STATE_DEFAULT)    # background #000088
    self.stat_line.set_style_bg_opa(lv.OPA_COVER, lv.PART_MAIN | lv.STATE_DEFAULT)            # 100% background opacity
    self.stat_line.set_style_text_color(lv.color(0xFFFFFF), lv.PART_MAIN | lv.STATE_DEFAULT)  # text color #FFFFFF


    self.stat_line.set_text("")
    self.stat_line.refr_size()                                                                # new in LVGL8
    self.stat_line.refr_pos()                                                                 # new in LVGL8

    #- display wifi strength indicator icon (for professionals ;) -#
    self.wifi_icon = lv_wifi_arcs_icon(self.stat_line)    # the widget takes care of positioning and driver stuff
    #self.clock_icon = lv_clock_icon(self.stat_line)
  end

  def buttons()

    #- create a style for the buttons -#
    self.btn_style = lv.style()
    self.btn_style.set_radius(10)                        # radius of rounded corners
    self.btn_style.set_bg_opa(lv.OPA_COVER)              # 100% backgrond opacity
    if self.f20 != nil self.btn_style.set_text_font(self.f20) end  # set font to Montserrat 20
    self.btn_style.set_bg_color(lv.color(0x1fa3ec))      # background color #1FA3EC (Tasmota Blue)
    self.btn_style.set_border_color(lv.color(0x0000FF))  # border color #0000FF
    self.btn_style.set_text_color(lv.color(0xFFFFFF))    # text color white #FFFFFF

    #- create buttons -#
    self.up_btn = lv.btn(self.scr)                            # create button with main screen as parent
    self.up_btn.set_pos(self.hres-100,self.vres-40)                      # position of button
    self.up_btn.set_size(80, 30)                         # size of button
    self.up_btn.add_style(self.btn_style, lv.PART_MAIN | lv.STATE_DEFAULT)   # style of button
    self.prev_label = lv.label(self.up_btn)                   # create a label as sub-object
    self.prev_label.set_text("+")                          # set label text
    self.prev_label.center()

    self.down_btn = lv.btn(self.scr)                            # right button
    self.down_btn.set_pos(20,self.vres-40)
    self.down_btn.set_size(80, 30)
    self.down_btn.add_style(self.btn_style, lv.PART_MAIN | lv.STATE_DEFAULT)
    self.next_label = lv.label(self.down_btn)
    self.next_label.set_text("-")
    self.next_label.center()
  end

  def temperatureArc()
    self.t_arc = lv.arc(self.scr)
    self.t_arc.set_end_angle(200)
    self.t_arc.set_size(150, 150)
    self.t_arc.center()
    self.t_arc.set_range(150,300)
    self.t_arc.set_value(220)


    self.t_act_label = lv.label(self.t_arc)    
    self.t_act_label.set_text("23.1")
    #t_act_label.set_width(150)                         # Set smaller width to make the lines wrap
    self.t_act_label.set_style_text_align(lv.ALIGN_CENTER, 0)
    self.t_act_label.set_style_text_color(lv.color(0xFFFFFF), lv.PART_MAIN | lv.STATE_DEFAULT)  # text color #FFFFFF

    self.t_act_label.center()
    #t_act_label.set_style_text_color(lv.color(0xFFFFFF))
    if self.f16 != nil self.t_act_label.set_style_text_font(self.f16, lv.PART_MAIN | lv.STATE_DEFAULT) end
    #testc = test(t_act_label)
    self.c_label = lv.label(self.t_arc)    
    self.c_label.set_text("°C")
    #t_act_label.set_width(150)                         # Set smaller width to make the lines wrap
    self.c_label.set_style_text_align(lv.ALIGN_CENTER, 0)
    self.c_label.set_style_text_color(lv.color(0xFFFFFF), lv.PART_MAIN | lv.STATE_DEFAULT)  # text color #FFFFFF

    self.c_label.align(lv.ALIGN_CENTER,0,40)   
    self.t_des_label = lv.label(self.t_arc)  
  end

  def set_temp_dest()
    var i=self.t_arc.get_value()
    self.t_des_label.set_text(string.format("%i.%i",i/10,i%10))
    tasmota.cmd(string.format("temptargetset1 %i.%i",i/10,i%10))
    tasmota.cmd(string.format("temptargetset2 %i.%i",i/10,i%10))
    tasmota.cmd(string.format("temptargetset3 %i.%i",i/10,i%10))
    persist.temptarget=i
    persist.save()
    self.inactive=0
    self.screen_normal()
    #temptargetset
  end

  def inc_dest()
    var i=self.t_arc.get_value()
    if i<300 i=i+1 
      self.t_arc.set_value(i) 
      self.set_temp_dest() 
    end
  end

  def dec_dest()
    var i=self.t_arc.get_value()
    if i>150 i=i-1 
      self.t_arc.set_value(i) 
      self.set_temp_dest() 
    end
  end

  def temp_des()
    self.t_des_label.set_style_text_align(lv.ALIGN_CENTER, 0)
    self.t_des_label.set_style_text_color(lv.color(0xFFFFFF), lv.PART_MAIN | lv.STATE_DEFAULT)  # text color #FFFFFF
    self.t_des_label.align(lv.ALIGN_CENTER,0,-35)   
    if self.f20 != nil self.t_des_label.set_style_text_font(self.f20, lv.PART_MAIN | lv.STATE_DEFAULT) end
  end

  def bar()
    var style_indic = lv.style()
    style_indic.init()
    style_indic.set_bg_opa(lv.OPA_COVER)
    style_indic.set_bg_color(lv.palette_main(lv.PALETTE_RED))
    style_indic.set_bg_grad_color(lv.palette_main(lv.PALETTE_BLUE))
    style_indic.set_bg_grad_dir(lv.GRAD_DIR_VER)
    #style_indic.set_bg_main_stop(0)
    #style_indic.set_bg_grad_stop(50)

    self.left_bar = lv.bar(self.scr)
    self.left_bar.add_style(style_indic, lv.PART_INDICATOR)
    self.left_bar.set_size(20, 200)
    self.left_bar.set_pos(10,50)   
    self.left_bar.set_range(0, 5000)
    #left_bar.set_value(20, lv.ANIM_ON)
    self.left_value = lv.label(self.scr)    
    #left_value.set_text("xxx")
    #t_act_label.set_width(150)                         # Set smaller width to make the lines wrap
    self.left_value.set_style_text_align(lv.ALIGN_CENTER, 0)
    self.left_value.set_style_text_color(lv.color(0xFFFFFF), lv.PART_MAIN | lv.STATE_DEFAULT)  # text color #FFFFFF
    self.left_value.set_pos(40,50)

    self.right_bar = lv.bar(self.scr)
    self.right_bar.add_style(style_indic, lv.PART_INDICATOR)
    self.right_bar.set_size(20, 200)
    self.right_bar.set_pos(self.hres-30,50)   
    self.right_bar.set_range(0, 100)
    self.right_value = lv.label(self.scr)    
    self.right_value.set_style_text_align(lv.ALIGN_CENTER, 0)
    self.right_value.set_style_text_color(lv.color(0xFFFFFF), lv.PART_MAIN | lv.STATE_DEFAULT)  # text color #FFFFFF
    self.right_value.set_pos(self.hres-60,50)
  end
    #right_bar.set_bg_grad_stop(50)
    #right_bar.set_value(10, lv.ANIM_ON)

    #- static lv_grad_dsc_t grad_sunset;
    grad_sunset.stops[0] = (lv_gradient_stop_t){ .color = lv_palette_main(LV_PALETTE_RED), .frac = 96 };
    grad_sunset.stops[1] = (lv_gradient_stop_t){ .color = lv_palette_main(LV_PALETTE_ORANGE), .frac = 128 };
    grad_sunset.stops[2] = (lv_gradient_stop_t){ .color = lv_palette_main(LV_PALETTE_BLUE), .frac = 216 };
    grad_sunset.stops_count = 3;
    grad_sunset.dir = LV_GRAD_DIR_VER;
    lv_obj_t* obj03 = lv_obj_create(lv_scr_act());
    lv_obj_set_style_bg_grad(obj03, &grad_sunset, 0);

    -#
    #
    # Create LED's with different brightness and color
    #
  
  def led()
    self.ledstyle = lv.style()
    self.ledstyle.set_radius(20)                        # radius of rounded corners
    self.ledstyle.set_bg_opa(lv.OPA_COVER)              # 100% backgrond opacity
    self.ledstyle.set_bg_color(lv.color(0x1fa3ec))      # background color #1FA3EC (Tasmota Blue)
    self.ledstyle.set_border_color(lv.color(0x0000FF))  # border color #0000FF

    # Create a LED and switch it OFF
    self.led1 = lv.btn(lv.scr_act())                            # create button with main screen as parent
    self.led1.add_style(self.ledstyle, lv.PART_MAIN | lv.STATE_DEFAULT)   # style of button
    self.led1img=lv.img(self.led1)
    self.led1img.set_src("A:/"+wd+"/heatingwhite.png")
    #print(wd+"heatingwhite.png")
    self.led1img.center()
    self.led1.align(lv.ALIGN_CENTER, -60, 90)
    self.led1.set_size(32, 32)   
    self.led1.add_flag(lv.OBJ_FLAG_CHECKABLE)                           # enable toggle mode   

    # Copy the previous LED and set a brightness
    self.led2 = lv.btn(lv.scr_act())                            # create button with main screen as parent
    self.led2.add_style(self.ledstyle, lv.PART_MAIN | lv.STATE_DEFAULT)   # style of button
    self.led2img=lv.img(self.led2)
    self.led2img.set_src("A:/"+wd+"/heatingwhite.png")
    self.led2img.center()
    self.led2.align(lv.ALIGN_CENTER, 0, 90)
    self.led2.set_size(32, 32)   
    self.led2.add_flag(lv.OBJ_FLAG_CHECKABLE)                           # enable toggle mode   

    # Copy the previous LED and switch it ON
    self.led3 = lv.btn(lv.scr_act())                            # create button with main screen as parent
    self.led3.add_style(self.ledstyle, lv.PART_MAIN | lv.STATE_DEFAULT)   # style of button
    self.led3img=lv.img(self.led3)
    self.led3img.set_src("A:/"+wd+"/heatingwhite.png")
    self.led3img.center()
    self.led3.align(lv.ALIGN_CENTER, 60, 90)
    self.led3.set_size(32, 32)   
    self.led3.add_flag(lv.OBJ_FLAG_CHECKABLE)                           # enable toggle mode   

 
#-     style = lv.style()
    style.set_radius(20)                        # radius of rounded corners
    style.set_bg_opa(lv.OPA_COVER)              # 100% backgrond opacity
    style.set_bg_color(lv.color(0x1fa3ec))      # background color #1FA3EC (Tasmota Blue)
    style.set_border_color(lv.color(0x0000FF))  # border color #0000FF

    t_btn = lv.btn(lv.scr_act())                            # create button with main screen as parent
    t_btn.add_style(style, lv.PART_MAIN | lv.STATE_DEFAULT)   # style of button
    bild=lv.img(t_btn)
    bild.set_src("A:/heatingwhite.png")
    bild.center()
    #t_btn.set_pos(100,100)                      # position of button
    t_btn.align(lv.ALIGN_CENTER, 70, 90)
    t_btn.set_size(32, 32)   
    t_btn.add_flag(lv.OBJ_FLAG_CHECKABLE)                           # enable toggle mode   
    b.add_state(lv.STATE_CHECKED)
    b.clear_state(lv.STATE_CHECKED)
 -#

    #self.heat_image.set_pos(110,45)
  end

    #- callback function when a button is pressed, react to EVENT_CLICKED event -#

  def screen_normal()
    tasmota.cmd("DisplayDimmer 80")
  end

  def screen_dimmed()
    tasmota.cmd("DisplayDimmer 20")
  end

  def btn_up_clicked_cb(obj, evt)
    #var code = evt.code
    self.inc_dest()
  end

  def btn_down_clicked_cb(obj, evt)
    self.dec_dest()
  end

  def dest_temp_changed_cb(obj, evt)
    
    #var code = evt.code
    self.set_temp_dest()
    #print(obj.get_value())
  end 

   
   

  def update_ui()
    import json
    #import global

    
    #-   var sens=json.load(tasmota.read_sensors())
      print(sens)
      if !sens.contains('SHT3X')
        #print(sens)
        sens={}
        sens['SHT3X'] = {}
        sens['SHT3X']['Temperature'] = tt
        sens['SHT3X']['Humidity'] = hh
        sens['SGP30'] = {}
        sens['SGP30']['eCO2'] = ee
        tt=tt+0.1 if tt>=30.0 tt=15.0 end
        ee=ee+10.0 if ee>=1000.0 ee=400.0 end
        hh=hh+1.0 if hh>=100.0 hh=0.0 end
        #print(sens)

      end

      var txt = string.format("%.1f", sens['SHT3X']['Temperature'])
      var hum=int(sens['SHT3X']['Humidity'])
      var eco=int(sens['SGP30']['eCO2'])  
      print(sens)
      t_act_label.set_text(txt) -#
      #print(hum)

      #var txt = "HMM" #string.format("%.1f", sens['SHT3X']['Temperature'])
      #print("cxcxc",self.sht_sensor)
    if global.contains("sht31_humidity") && global.contains("sht31_temperature") && global.contains("sgp_tvoc") 

      var hum=global.sht31_humidity
      var t=global.sht31_temperature
      var tvoc=global.sgp_tvoc
    
      self.t_act_label.set_text(string.format("%i.%i", t>>4,((t&0xf)*10)>>4))
      self.right_bar.set_value(hum, lv.ANIM_ON)
      #self.t_act_label.set_text(string.format("%i.%i", t/10,t%10))
      self.left_bar.set_value(tvoc, lv.ANIM_ON)
      self.left_value.set_text(string.format("%i", tvoc))
      self.right_value.set_text(string.format("%i%%", hum))

      
    end
  
    var tas=tasmota.get_power() 
    if tas[0]==true
      self.led1.add_state(lv.STATE_CHECKED)
     else
      self.led1.clear_state(lv.STATE_CHECKED)
    end
    if tas[1]==true
      self.led2.add_state(lv.STATE_CHECKED)
    else
      self.led2.clear_state(lv.STATE_CHECKED)
    end
    if tas[2]==true
      self.led3.add_state(lv.STATE_CHECKED)
    else
      self.led3.clear_state(lv.STATE_CHECKED)
    end
    #tasmota.set_timer(5100, /->self.update_ui())
  end

  def update_date()
    #print("hallole")
    var now = tasmota.time_dump(tasmota.rtc()['local'])
    if now['year'] != 1970 && now['min'] != self.minutes
      self.minutes = now['min']
      var t = string.format("%02d.%02d.%02d    %d:%02d", now['day'],now['month'],now['year'],now['hour'],now['min'])
      self.stat_line.set_text(t)
      tasmota.set_timer(59500, /->self.update_date())
    else
      tasmota.set_timer(1000, /->self.update_date())
    end
  end

  def get_settings()
    var i=persist.temptarget
    if !i i=220 end
    self.t_arc.set_value(i)
    self.t_des_label.set_text(string.format("%i.%i",i/10,i%10))
    tasmota.cmd(string.format("temptargetset1 %i.%i",i/10,i%10))
    tasmota.cmd(string.format("temptargetset2 %i.%i",i/10,i%10))
    tasmota.cmd(string.format("temptargetset3 %i.%i",i/10,i%10))
  end

  def every_3seconds()
    
    self.update_ui()
    self.timer+=1
    if lv.scr_act()._p == self.scr._p
      self.inactive+=1
      if self.inactive<=0
        self.inactive-=1
      end
    else
      self.inactive=0
    end

    tasmota.set_timer(3100, /->self.every_3seconds())
    if self.inactive == 25
      self.screen_dimmed()
    end
    if self.inactive == 200

    #if lv.disp().get_inactive_time() > 1000
      tasmota.cmd("Uhr")
      print("hallo")
    end

  end
end

mainscreen = MAINSCREEN()
mainscreen.every_3seconds()
mainscreen.update_date()
#tasmota.add_driver(mainscreen)
return mainscreen