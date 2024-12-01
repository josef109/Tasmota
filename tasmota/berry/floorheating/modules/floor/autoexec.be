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

import mqtt
import string

topic = "homi/weather/forecast_home_bd/"
m = map()

def update_weather_text()
  try 
    var we = 
         "Temperatur:         " + m.item("temperature") + m.item("temperature_unit") + "\n" +
         "Taupunkt:           " + m.item("dew_point") + m.item("temperature_unit") + "\n" +
         "Luftfeuchtigkeit:   " + m.item("humidity") + "%\n" +
         "Bewölkung:          " + m.item("cloud_coverage") + "%\n" +
         "UV Index:           " + m.item("uv_index") + "\n" +
         "Luftdruck:          " + m.item("pressure") + " " + string.replace(m.item("pressure_unit"),'"',"") + "\n" +
         "Windrichtung:       " + m.item("wind_bearing") + "\n" +
         "Windgeschwindigket: " + m.item("wind_speed") + " " + string.replace(m.item("wind_speed_unit"),'"',"")
    global.p5b501.text = we
  except .. as e, m
    return
  end
end


def p1(a,b,c)
  var tag = a[size(topic)..]
  var x = {
    "clear-night": "klare Nacht",
    "cloudy":"bewölkt",
    "exceptional":"außergewöhnliches\nWetter",
    "fog":"Nebel",
    "hail":"Hagel",
    "lightning":"Gewitter",
    "lightning-rainy":"Regen und\nGewitter",
    "partlycloudy":"teilweise\nbewölkt",   #\u00f6lkt",
    "pouring":"starker Regen",
    "rainy":"Regen",
    "snowy":"Schnee",
    "snowy-rainy":"Schneeregen",
    "sunny":"sonnig",
    "windy":"windig",
    "windy-variant":"windig und bewölkt"
  }
  
 
  if m.contains(tag)
    m.setitem(tag,c)
  else
    m.insert(tag,c)
  end

  #print(m)

  print("mqtt1",a,b,c)

  if tag == "temperature"
    global.p4b16.text = c+"°C"
  end
  if tag == "humidity"
    global.p4b17.text = c+"%"
  end
  if tag == "state"
    global.p4b18.text = x.item(c)
    global.p4b14.src = "A:/floor.tapp#z-128-"+c+".png"   #z-32-clear-night.png
  end
  if tag == "supported_features"
    update_weather_text()
  end
end


mqtt.subscribe(topic+"#", p1)

update_settings()
