#var mainscreen = module('mainscreen')
import string
import persist
import global


var t=persist.temptarget
if !t
  t=[22.0,22.0,22.0]
  persist.temptarget = t
  persist.save()
end

var ch = persist.channel
if !ch
  ch = 1
  persist.channel = ch
  persist.save()
end

def save_temptarget()
  var t=[22.0,22.0,22.0]
  for i:0..2
    var a = string.format("TempTargetSet%i", i+1)  
    t[i] = tasmota.cmd(a)[a]
  end
  persist.temptarget = t
  persist.save()
end

for i:0..2
  tasmota.cmd(string.format("temptargetset%i %s", i+1, t[i]))
  if (ch & (1 << i)) == 0
    tasmota.cmd(string.format("ThermostatModeSet%i 0", i+1))
  else
    tasmota.cmd(string.format("ThermostatModeSet%i 1", i+1))
  end
end

tasmota.cmd("controllermodeset1 1")
tasmota.cmd("controllermodeset2 1")
tasmota.cmd("controllermodeset3 1")

tasmota.cmd("SensorInputSet1 1")
tasmota.cmd("SensorInputSet2 1")
tasmota.cmd("SensorInputSet3 1")

tasmota.cmd("PropBandSet1 1")
tasmota.cmd("PropBandSet2 1")
tasmota.cmd("PropBandSet3 1")

tasmota.cmd("TimeMaxActionSet1 60")
tasmota.cmd("TimeMaxActionSet2 61")
tasmota.cmd("TimeMaxActionSet3 62")

tasmota.cmd("TimePiCycleSet2 61")
tasmota.cmd("TimePiCycleSet3 62")

