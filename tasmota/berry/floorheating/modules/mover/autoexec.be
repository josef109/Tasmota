# Register the command 'Antiburn'
# Module loaded in memory only when the command is first used

import sys

var wd = tasmota.wd


if size(wd) sys.path().push(wd) end

# [...] you can import files from within the archive
import mover


if size(wd) sys.path().pop() end

x = mover
x.start()


