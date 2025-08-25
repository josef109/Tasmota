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

import haspmota
haspmota.start(false, tasmota.wd + "pages.jsonl")

def update_settings()
    import global
    import persist
    import string

    var ch = persist.channel
    for i:0..2
        var ob = string.format("p3b%i", i+212)
        if (ch & (1 << i)) == 0
          global.(ob).toggle = false
        else
          global.(ob).toggle = true
        end
    end
end

import string
import clock_gr

class ui_screen

  var topic_weather 
  var topic_warning 
  var topic_daily 
  var topic_hourly 
                  
  var m
  var warn1
  var warn2 
  var warn3 
  var clock

  def init()
    self.topic_weather = "homi/weather/villingen_schwenn/#"
    self.topic_warning = "homi/sensor/stadt_bad_durrheim_aktuelle_warnstufe/#"
    self.topic_daily = "homi/sensor/wettervorhersage_taglich/forecast/#"
    self.topic_hourly = "homi/sensor/wettervorhersage_stundlich/forecast/#"
                    
    self.m = map()
    self.warn1 = map()
    self.warn2 = map()
    self.warn3 = map()
  
    self.clock = clock_gr()
    self.clock.start()
    #self.subscribes()
  end

  def update_weather_text()
    import global
    try 
      var we = 
          "Temperatur:         " + self.m.item("temperature") + self.m.item("temperature_unit") #+ "\n" +
  #         "Taupunkt:           " + m.item("dew_point") + m.item("temperature_unit") + "\n" +
  #         "Luftfeuchtigkeit:   " + m.item("humidity") + "%\n" +
  #         "Bewölkung:          " + m.item("cloud_coverage") + "%\n" +
  #         "UV Index:           " + m.item("uv_index") + "\n" +
  #         "Luftdruck:          " + m.item("pressure") + " " + string.replace(m.item("pressure_unit"),'"',"") + "\n" +
  #         "Windrichtung:       " + m.item("wind_bearing") + "\n" +
  #         "Windgeschwindigket: " + m.item("wind_speed") + " " + string.replace(m.item("wind_speed_unit"),'"',"")
  #    global.p5b501.text = we
    except .. as e, m
      return
    end
  end

  def p1(a,b,c)
  #  print("mqtt1",a,b,c)

    if a == nil
      return
    end
    var tag = a[(size(self.topic_weather)-1)..]
    var x = {
      "clear-night": "klare\nNacht",
      "cloudy":"bewölkt",
      "exceptional":"außergewöhnliches\nWetter",
      "fog":"Nebel",
      "hail":"Hagel",
      "lightning":"Gewitter",
      "lightning-rainy":"Regen und\nGewitter",
      "partlycloudy":"teilweise\nbewölkt",   #\u00f6lkt",
      "pouring":"starker\nRegen",
      "rainy":"Regen",
      "snowy":"Schnee",
      "snowy-rainy":"Schneeregen",
      "sunny":"sonnig",
      "windy":"windig",
      "windy-variant":"windig und\nbewölkt"
    }
    
    c = string.replace(c,'"',"")
  
    if self.m.contains(tag)
      self.m.setitem(tag,c)
    else
      self.m.insert(tag,c)
    end

    #print(m)


    try
      if tag == "temperature"
        global.p4b21.text = c+"°C"
        global.p2b21.text = c+"°C"
        self.clock.set_temp(c+"°C")
      end
      if tag == "humidity" || tag == "wind_speed"
        global.p4b22.text = self.m["humidity"]+"% "+self.m["wind_speed"]+self.m["wind_speed_unit"]
        global.p2b22.text = self.m["humidity"]+"% "+self.m["wind_speed"]+self.m["wind_speed_unit"]
      end
      if tag == "state"
        global.p4b23.text = x.item(c)
        global.p2b23.text = x.item(c)
        global.p4b1.src = "A:/floor.tapp#z-128-"+c+".png"   #z-32-clear-night.png
        global.p2b1.src = "A:/floor.tapp#z-128-"+c+".png"   #z-32-clear-night.png
        self.clock.set_weather("A:/floor.tapp#z-128-"+c+".png")
      end
    except .. as e, m
      print("no ",e,m)
      return false
    end
    if tag == "supported_features"
      self.update_weather_text()
    end
    return true
  end

  def p2(a,b,c)
    import json
    if a == nil
      return
    end
    var tag = a[(size(self.topic_warning)-1)..]
    if tag == "warning_1" 
      self.warn1 = json.load(c)
    end
    if tag == "warning_2" 
      self.warn2 = json.load(c)
    end
    if tag == "warning_3" 
      self.warn3 = json.load(c)
    end

    try
      global.p5b11.text = self.warn1["headline"]
      global.p5b11.text_color = self.warn1["color"]
      global.p5b12.text = self.warn1["description"]
      global.p5b13.text = self.warn1["instruction"]
    except .. as e, m
      return false
    end
    #global.p5.show()

    #print("mqtt2",tag,c)
    return true
  end

  def p3(a,b,c)
    import json
    if a == nil
      return
    end
    var hrly = json.load(c)
  
    for i:0..5  
      var ob = string.format("p4b%i", i+70)
      global.(ob).text = hrly[i]["datetime"]
      ob = string.format("p4b%i", i+80)
      global.(ob).text = str(hrly[i]["temperature"])+"°C"
      ob = string.format("p4b%i", i+90)
      global.(ob).src = "A:/floor.tapp#z-32-"+(hrly[i]["condition"])+".png"   

      ob = string.format("p2b%i", i+4)
      global.(ob).text = str(hrly[i]["temperature"])+"°C"
      ob = string.format("p2b%i", i+34)
      global.(ob).src = "A:/floor.tapp#z-32-"+(hrly[i]["condition"])+".png"   

    end

    #print("mqtt3",hrly)
    return true
  end

  def setTasmota()
    tasmota.cmd("Backlog DisplayDimmer 10; TimeDST 0,0,3,1,1,120; TimeSTD 0,0,10,1,1,60; Timezone 99; Altitude 711; Latitude 48.0337142518044; Longitude 8.53720307350159; SaveData 3600; SetOption0 0")
  end

  def subscribes()
    import mqtt
  
    mqtt.unsubscribe()
    mqtt.subscribe(self.topic_weather, / a,b,c -> self.p1(a,b,c))
    mqtt.subscribe(self.topic_warning, / a,b,c -> self.p2(a,b,c))
    mqtt.subscribe(self.topic_hourly, / a,b,c -> self.p3(a,b,c))
    print("subsc")
  end
end

ui = ui_screen()
ui.setTasmota()
ui.init()

update_settings()


ui.subscribes()


#tasmota.when_network_up(/-> ui.subscribes())    # start when network is connected

