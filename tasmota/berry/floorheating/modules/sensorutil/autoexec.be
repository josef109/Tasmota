#  ------------------------------------------------------------------------------------------------------
#  autoexec.be - Berry scripting language
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



var wd = tasmota.wd

import sys

if size(wd) sys.path().push(wd) end

# [...] you can import files from within the archive
import sensorutil


if size(wd) sys.path().pop() end



