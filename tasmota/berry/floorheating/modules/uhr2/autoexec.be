#-
 - Example of Smart Watch on a 240x240 screen.
 -
 - Assets are borrowed from https://www.facer.io/watchface/HC77XaKNNM?watchModel=waldhoffrenaissance
 - and simulates The Waldhoff Renaissance
 -
 - Copy all assets in the file-system, including this file
 -#

lv.start()

scr = lv.scr_act()

scr.set_style_bg_color(lv.color(lv.COLOR_BLACK), lv.PART_MAIN | lv.STATE_DEFAULT)

var wd = tasmota.wd

ren_back = lv.img(scr)
ren_back.set_src("A:/"+wd+"/watch_ren_back_240.png")
ren_back.set_align(lv.ALIGN_CENTER)

ren_day = lv.label(ren_back)
ren_day.set_style_text_color( lv.color(lv.COLOR_BLACK), lv.PART_MAIN | lv.STATE_DEFAULT) 

ren_day.set_long_mode(lv.LABEL_LONG_SCROLL)
ren_day.set_align(lv.ALIGN_CENTER)
ren_day.set_text("")
ren_day.set_width(18)
ren_day.set_height(16)
ren_day.set_pos(184,112)

ren_hour = lv.img(ren_back)
ren_hour.set_src("A:/"+wd+"/watch_ren_hour_240.png")
ren_hour.set_pos(110,45)

ren_min = lv.img(ren_back)
ren_min.set_src("A:/"+wd+"/watch_ren_min_240.png")

ren_sec = lv.img(ren_back)
ren_sec.set_src("A:/"+wd+"/watch_ren_sec_240.png")
ren_sec.set_pos(110,10)

prev_day = -1
def set_watch()
    var now = tasmota.rtc()
    var time_raw = now['local'] + now['timezone'] * 60
    var time = tasmota.time_dump(time_raw)
    # set second
    ren_sec.set_angle(60 * time['sec'])
    # set minutes
    ren_min.set_angle(60 * time['min'])
    # set hours
    ren_hour.set_angle(300 * (time['hour'] % 12) + time['min'] * 5)
    # set day
    if time['day'] != prev_day
        ren_day.set_text(str(time['day']))
        prev_day = time['day']
    end
end

def run_watch()
    set_watch()
    tasmota.set_timer(1000, run_watch)
end
run_watch()
