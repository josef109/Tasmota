# Register the command 'Antiburn'
# Module loaded in memory only when the command is first used

var wd = tasmota.wd

lv.uhr = def()
    import sys
    var path = sys.path()
    path.push(wd)
    import uhr
    path.pop()
    uhr.start()
end

tasmota.add_cmd("Uhr",
    def ()
        lv.uhr()
        tasmota.resp_cmnd_done()
    end
)
