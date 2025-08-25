
var sensorutil = module("sensorutil")

sensorutil.compute_crc = def (data) 
    # Compute CRC as per datasheet
  var crc = 0xFF
  
  #print(data)
  crc ^= data>>8
  for i: 0..7
    if crc & 0x80 
      crc = (crc << 1) ^ 0x31
    else 
      crc <<= 1
    end
  end
  crc ^= data 
  for i: 0..7
    if crc & 0x80
      crc = (crc << 1) ^ 0x31
    else 
      crc <<= 1;
    end
  end
  return crc & 0xff
end
  
sensorutil.read_words = def (w,addr,n)
  if !n || n==0 return [] end
  var ret=[]
  w._request_from(addr,n*3)  
  while n>0
    var a = w._read()<<8
    a+=w._read()
    var a_crc = w._read()
    if sensorutil.compute_crc(a) == a_crc
      ret.push(a)
    else 
      print("CRC error",addr,n)
      return []
    end
    n-=1
  end
  return ret
end

return sensorutil