import string

class mover : Driver
  var running
  var out_old 
  var unchange #= []
  var moving_active #= []
  var channel #= 0
  #- define the global symbol for reference -#

  def init()
    # register ourself
    tasmota.add_driver(self)
    print("init ")
    self.start()
  end

  def start()
    self.unchange = [0, 0, 0]
    self.out_old = [false, false, false]
    self.moving_active = [0, 0, 0]
    self.channel = 0
    var x = tasmota.cmd("ThermostatModeSet1")
    if x.contains('ThermostatModeSet1') 
      if x['ThermostatModeSet1'] == 1   
        self.channel = 1
      end
    end
    x = tasmota.cmd("ThermostatModeSet2")
    if x.contains('ThermostatModeSet2')
      if x['ThermostatModeSet2'] == 1   
        self.channel |= 2
      end
    end
    x = tasmota.cmd("ThermostatModeSet3")
    if x.contains('ThermostatModeSet3')
      if x['ThermostatModeSet3'] == 1
        self.channel |= 4
      end
    end
    print("channels", self.channel)
    self.mover_cycle()
  end 

  def mover_cycle()
    tasmota.set_timer(10000, /-> self.mover_cycle())
     self.update_mover()
  end

  def stop()
  end

  def update_mover()
    var outputs = tasmota.get_power()

    for i:0..2
      if (self.channel & (1 << i)) == 0
        continue
      end

      self.unchange[i] += 1

      if self.moving_active[i] == 1
        if self.unchange[i] > 30
          self.moving_active[i] = 2
          self.unchange[i] = 0
          tasmota.set_power(i, false)
          print("Ausgang", i, "aus")
          # Ausgang ausschalten
        end

      elif self.moving_active[i] == 2
        if self.unchange[i] > 30 #30
          self.moving_active[i] = 0 
          self.unchange[i] = 0
          # Ausgang abschalten
          var txt = string.format("EnableOutputSet%d 1", i)
          tasmota.cmd(txt)
          print("Ausgang", i, "Thermostat")
        end

      else
        if outputs[i] != self.out_old[i]
          self.unchange[i] = 0
        end
        if self.unchange[i] > 9000
          self.moving_active[i] = 1
          # Ausgang einschalten
          self.unchange[i] = 0
          var txt = string.format("EnableOutputSet%d 0", i)
          tasmota.cmd(txt)
          tasmota.set_power(i, true)
          print("Ausgang", i, "ein")
        end
      end
    end
    self.out_old = outputs
    #print (self.unchange)
  end    
end

return  mover()  # return instance