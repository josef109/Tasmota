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

for i:0..2
  tasmota.cmd(string.format("temptargetset%i %i.%i", i+1, t[i] / 10, t[i] % 10))
  if (ch & (1 << i)) == 0
    tasmota.cmd(string.format("ThermostatModeSet%i 0", i+1))
  else
    tasmota.cmd(string.format("ThermostatModeSet%i 1", i+1))
  end
end

tasmota.cmd(string.format("controllermodeset1 1"))
tasmota.cmd(string.format("controllermodeset2 1"))
tasmota.cmd(string.format("controllermodeset3 1"))

tasmota.cmd(string.format("PropBandSet1 1"))
tasmota.cmd(string.format("PropBandSet2 1"))
tasmota.cmd(string.format("PropBandSet3 1"))

tasmota.cmd(string.format("TimeMaxActionSet1 60"))
tasmota.cmd(string.format("TimeMaxActionSet2 61"))
tasmota.cmd(string.format("TimeMaxActionSet3 62"))

tasmota.cmd(string.format("TimePiCycleSet2 61"))
tasmota.cmd(string.format("TimePiCycleSet3 62"))

