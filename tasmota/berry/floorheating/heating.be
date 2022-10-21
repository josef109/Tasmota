# ------------------------------------------------------------------------------------------------------
#  heating.be - Berry scripting language
#  Copyright (C) 2021 Shaun Brown, Berry language by Guan Wenliang https://github.com/Skiars/berry
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
#  ------------------------------------------------------------------------------------------------------

var heating = module('heating')

# All tasmota calls are accessed via api class

import sensor
#controller.init = def (m)

class HEATINGCONTROLLER
    static settings = persist
    var dest_temp, act_temp, hysterese, s, out, p, i,d

    def init()
        self._start()
    end
    # Start the heating controller
    def _start()
        self.p=10
        print("heating start")
        self.s = sensor
        self.s.driver.set_settings(self.settings)
        #print(self.s)
        #print(self.s.driver)
        tasmota.add_driver(self.s.driver)
        
    end

    def start()
    end

    def set_temp(target)
        self.settings.dest_temp=target
    end

    def set_hyst(hysterese)
        self.hysterese=hysterese
    end

    def get_temp()
        return self.settings.dest_temp
    end

    def get_state(act_temp)
        if act_temp > self.dest_temp 
            self.out=false
        elif act_temp+self.hysterese<self.dest_temp
            self.out=true
        end
        return self.out
    end

    def calc_pi()               # zyklisch
        var d=(self.dest_temp-self.act_temp)
        if d>10 d=10
        elif d<-10 d=-10
        end
        var p=d*self.p    #  + - 100    = 200 min
        if p>0 self.s=p
        else self.s=0
        end
    end

end

heating.controller = nil

#def start()
    heating.controller = HEATINGCONTROLLER()
    #heating.controller._start()
#end

return heating
