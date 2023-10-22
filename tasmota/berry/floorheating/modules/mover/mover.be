var mover = module('mover')

import string

mover.init = def (m)
  class mover
    var running
    var out_old 
    var unchange #= []
    var moving_active #= []
    var channel #= 0

    def init()

    end

    def start()
      if self.running
        return
      else
        self.running = true
        self.unchange = [0, 0, 0]
        self.out_old = [false, false, false]
        self.moving_active = [0, 0, 0]
        self.channel = 0
        var x = tasmota.cmd("CtrDutyCycleRead1")
        if x.contains('CtrDutyCycleRead1')
          self.channel = 1
        end
        x = tasmota.cmd("CtrDutyCycleRead2")
        if x.contains('CtrDutyCycleRead2')
          self.channel |= 2
        end
        x = tasmota.cmd("CtrDutyCycleRead3")
        if x.contains('CtrDutyCycleRead3')
          self.channel |= 4
        end
        print("kanal ", self.channel)
        self.cycle()
      end
    end 

    def cycle()
      if !self.running return; end
      tasmota.set_timer(10000, /->self.cycle())
      self.update_mover()
    end

    def stop()
      if self.running 
        self.running = false
      end    
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
            print("Ausgang aus")
            # Ausgang ausschalten
          end

        elif self.moving_active[i] == 2
          if self.unchange[i] > 30
            self.moving_active[i] = 0 
            self.unchange[i] = 0
            # Ausgang abschalten
            var txt = string.format("EnableOutputSet%d 1", i)
            tasmota.cmd(txt)
            print("Ausgang Termostat")
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
            print("Ausgang ein")
          end
        end

        #print("ich bin da ", outputs)
        #print (self.unchange)
        self.out_old[i] = outputs[i]
      end
    
    end    
  end
  return mover()
end

return mover
