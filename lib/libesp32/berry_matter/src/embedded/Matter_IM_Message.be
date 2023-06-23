#
# Matter_IM_Message.be - suppport for Matter Interaction Model messages responses
#
# Copyright (C) 2023  Stephan Hadinger & Theo Arends
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

import matter

#@ solidify:Matter_IM_Message,weak
#@ solidify:Matter_IM_Status,weak
#@ solidify:Matter_IM_InvokeResponse,weak
#@ solidify:Matter_IM_WriteResponse,weak
#@ solidify:Matter_IM_ReportData,weak
#@ solidify:Matter_IM_ReportDataSubscribed,weak
#@ solidify:Matter_IM_SubscribedHeartbeat,weak
#@ solidify:Matter_IM_SubscribeResponse,weak

#################################################################################
# Matter_IM_Message
#
# Superclass for all IM responses
#################################################################################
class Matter_IM_Message
  static var MSG_TIMEOUT = 5000       # 5s
  var expiration                      # expiration time for the reporting 
  var resp                            # response Frame object
  var ready                           # bool: ready to send (true) or wait (false)
  var finish                          # if true, the message is removed from the queue
  var data                            # TLV data of the response (if any)
  var last_counter                    # counter value of last sent packet (to match ack)

  #################################################################################
  # build a response message stub
  #
  # Args:
  #   - msg: the message object
  #   - opcode: (int) the Matter opcode of the response
  #   - reliable: (bool) if true, then we send the response as reliable, i.e. we expect a Ack to confirm it was received
  def init(msg, opcode, reliable)
    self.reset(msg, opcode, reliable)
  end

  #################################################################################
  def reset(msg, opcode, reliable)
    self.resp = (msg != nil) ? msg.build_response(opcode, reliable) : nil # is nil for spontaneous reports
    self.ready = true                # by default send immediately
    self.expiration = tasmota.millis() + self.MSG_TIMEOUT
    self.last_counter = 0            # avoid `nil` value
    self.finish = false
  end

  #################################################################################
  # the message is being removed due to expiration
  def reached_timeout()
    # log(f"MTR: IM_Message reached_timeout exch={self.resp.exchange_id}", 3)
  end

  #################################################################################
  # ack received for previous message, proceed to next (if any)
  # return true if we manage the ack ourselves, false if it needs to be done upper
  def ack_received(msg)
    # tasmota.log("MTR: IM_Message ack_received exch="+str(self.resp.exchange_id), 3)
    self.expiration = tasmota.millis() + self.MSG_TIMEOUT     # give more time
    return false
  end

  #################################################################################
  # Status Report OK received for previous message, proceed to next (if any)
  # return true if we manage the ack ourselves, false if it needs to be done upper
  def status_ok_received(msg)
    # tasmota.log(format("MTR: IM_Message status_ok_received exch=%i", self.resp.exchange_id), 3)
    self.expiration = tasmota.millis() + self.MSG_TIMEOUT     # give more time
    if msg
      self.resp = msg.build_response(self.resp.opcode, self.resp.x_flag_r, self.resp)   # update packet
    end
    self.ready = true
    return true
  end

  #################################################################################
  # we received an ACK error, do any necessary cleaning
  #
  # Arg:
  #   - msg: the message received
  #
  # No return value
  def status_error_received(msg)
  end

  #################################################################################
  # get the exchange-id for this message
  #
  # No return value
  def get_exchangeid()
    return self.resp.exchange_id
  end

  # default responder for data
  #
  # This is the main entry point for seding the next response.
  # This is called only when `ready` is `true`
  #
  # Arg:
  #   - responder: instance of MessageHandler to create the response object
  def send_im(responder)
    # tasmota.log(format("MTR: IM_Message send_im exch=%i ready=%i", self.resp.exchange_id, self.ready ? 1 : 0), 3)
    if !self.ready   return false  end
    var resp = self.resp
    var data_raw = self.data.to_TLV().tlv2raw()    # payload in cleartext
    resp.encode_frame(data_raw)    # payload in cleartext
    resp.encrypt()
    tasmota.log(format("MTR: <snd       (%6i) id=%i exch=%i rack=%s", resp.session.local_session_id, resp.message_counter, resp.exchange_id, resp.ack_message_counter), 4)
    responder.send_response_frame(resp)
    self.last_counter = resp.message_counter
    self.finish = true              # by default we remove the packet after it is sent
  end

end
matter.IM_Message = Matter_IM_Message

#################################################################################
# Matter_IM_Status
#
# Send a simple Status Message
#################################################################################
class Matter_IM_Status : Matter_IM_Message

  #################################################################################
  def init(msg, status)
    super(self).init(msg, 0x01 #-Status Response-#, true #-reliable-#)
    var sr = matter.StatusResponseMessage()
    sr.status = status
    self.data = sr              # prepare the context in `self.data` that will be sent
  end
end
matter.IM_Status = Matter_IM_Status

#################################################################################
# Matter_IM_InvokeResponse
#
# Send a simple Status Message
#################################################################################
class Matter_IM_InvokeResponse : Matter_IM_Message

  #################################################################################
  def init(msg, data)
    super(self).init(msg, 0x09 #-Invoke Response-#, true)
    self.data = data
  end
end
matter.IM_InvokeResponse = Matter_IM_InvokeResponse

#################################################################################
# Matter_IM_WriteResponse
#
# Send a simple Status Message
#################################################################################
class Matter_IM_WriteResponse : Matter_IM_Message

  #################################################################################
  def init(msg, data)
    super(self).init(msg, 0x07 #-Write Response-#, true)
    self.data = data
  end

end
matter.IM_WriteResponse = Matter_IM_WriteResponse

#################################################################################
# Matter_IM_ReportData_Pull
#
# Report Data for a Read Request
#
# This version pull the attributes in lazy mode, only when response is computed
#################################################################################
class Matter_IM_ReportData_Pull : Matter_IM_Message
  static var MAX_MESSAGE = 1200       # max bytes size for a single TLV worklaod
                                      # the maximum MTU is 1280, which leaves 80 bytes for the rest of the message
                                      # section 4.4.4 (p. 114)
  # note: `self.data` (bytes or nil) is containing any remaining responses that could not fit in previous packets
  var generator_or_arr                # a PathGenerator or an array of PathGenerator
  var event_generator_or_arr          # a EventGenerator, or array of EventGenerator, or nil
  var subscription_id                 # if not `nil`, subscription_id in response
  var suppress_response               # if not `nil`, suppress_response attribute
  var data_ev                         # left-overs of events, mirroring of data for attributes

  #################################################################################
  #
  # Args
  #   - msg: message object
  #   - ctx_generator_or_arr: generator(s) for attributes (array, single instance, or nil)
  #   - event_generator_or_arr: generator(s) for events (array, single instance, or nil)
  def init(msg, ctx_generator_or_arr, event_generator_or_arr)
    super(self).init(msg, 0x05 #-Report Data-#, true)
    self.generator_or_arr = ctx_generator_or_arr
    self.event_generator_or_arr = event_generator_or_arr
  end

  # default responder for data
  def send_im(responder)
    # tasmota.log(format("MTR: IM_ReportData send_im exch=%i ready=%i", self.resp.exchange_id, self.ready ? 1 : 0), 3)
    if !self.ready   return false  end
    var resp = self.resp                          # response frame object
    var data = self.data                          # TLV data of the response (if any)
    var was_chunked = data.more_chunked_messages  # is this following a chunked packet?

    # the message were grouped by right-sized binaries upfront, we just need to send one block at time
    var elements = 1                # number of elements added

    # tasmota.log(format("MTR: exch=%i elements=%i msg_sz=%i total=%i", self.get_exchangeid(), elements, msg_sz, sz_attribute_reports), 3)
    var next_elemnts
    if data.attribute_reports != nil
      next_elemnts = data.attribute_reports[elements .. ]
      data.attribute_reports = data.attribute_reports[0 .. elements - 1]
      data.more_chunked_messages = (size(next_elemnts) > 0)
    else
      data.more_chunked_messages = false
    end

    if was_chunked
      # tasmota.log(format("MTR: .Read_Attr next_chunk exch=%i", self.get_exchangeid()), 4)
    end
    if data.more_chunked_messages
      if !was_chunked
        # tasmota.log(format("MTR: .Read_Attr first_chunk exch=%i", self.get_exchangeid()), 4)
      end

      # if we are here, then we exhausted the current generator, and we need to move to the next one
      if not_full
        if isinstance(self.event_generator_or_arr, list)
          self.event_generator_or_arr.remove(0)               # remove first element
          if size(self.event_generator_or_arr) == 0
            self.event_generator_or_arr = nil                 # empty array so we put nil
          end
        else
          self.event_generator_or_arr = nil                   # there was a single entry, so replace with nil
        end
      end

    end

    ########## Response
    # prepare the response
    # Manually craft payload
    var more_chunked_messages = (self.data != nil) || (self.data_ev != nil)
    var raw = bytes(self.MAX_MESSAGE)

    # open struct ReportDataMessage
    raw.add(0x15, 1)                  # add 15
    # open sturct EventDataIB
    if (self.subscription_id != nil)
      raw.add(0x2500, -2)               # add 2500
      raw.add(self.subscription_id, 2)  # add subscription_id as 16 bits
    end
    # do we have attributes?
    if (data != nil && size(data) > 0)
      raw.add(0x3601, -2)             # add 3601
      raw.append(data)
      raw.add(0x18, 1)           # add 18
    end
    # do we have events?
    if (data_ev != nil && size(data_ev) > 0)
      raw.add(0x3602, -2)             # add 3601
      raw.append(data_ev)
      raw.add(0x18, 1)           # add 18
    end
    # MoreChunkedMessages
    if more_chunked_messages    # we got more data to send
      raw.add(0x2903, -2)             # add 2903
    else
      raw.add(0x2803, -2)             # add 2803
    end
    # SuppressResponse
    if (self.suppress_response != nil)
      if self.suppress_response
        raw.add(0x2904, -2)             # add 2904
      else
        raw.add(0x2804, -2)             # add 2804
      end
    end
    # InteractionModelRevision
    raw.add(0x24FF, -2)               # add 24FF
    raw.add(0x01, 1)                  # add 01
    # close struct ReportDataMessage
    raw.add(0x18, 1)                  # add 18
    # log(f">>>: {raw.tohex()}", 3)

    # ##### Previous code
    # var ret = matter.ReportDataMessage()
    # ret.subscription_id = self.subscription_id
    # ret.suppress_response = self.suppress_response
    # if (data != nil && size(data) > 0)
    #   ret.attribute_reports = [data]
    # end
    # if (data_ev != nil && size(data_ev) > 0)
    #   ret.event_reports = [data_ev]
    # end
    # ret.more_chunked_messages = (self.data != nil) || (self.data_ev != nil)    # we got more data to send
    # var encoded_tlv = ret.to_TLV().tlv2raw(bytes(self.MAX_MESSAGE))    # takes time
    # resp.encode_frame(encoded_tlv)    # payload in cleartext, pre-allocate max buffer
    # log(f">>>: {encoded_tlv.tohex()}", 3)
    # ##### Previous code

    resp.encode_frame(raw)    # payload in cleartext, pre-allocate max buffer
    resp.encrypt()
    # print(">>>>> send elements after encrypt")
    # tasmota.log(format("MTR: <snd       (%6i) id=%i exch=%i rack=%s", resp.session.local_session_id, resp.message_counter, resp.exchange_id, resp.ack_message_counter), 4)
    responder.send_response_frame(resp)
    self.last_counter = resp.message_counter

    if next_elemnts != nil && size(next_elemnts) > 0
      data.attribute_reports = next_elemnts
      # tasmota.log(format("MTR: to_be_sent_later size=%i exch=%i", size(data.attribute_reports), resp.exchange_id), 4)
      self.ready = false    # wait for Status Report before continuing sending
      # keep alive
    else
      self.finish = true         # finished, remove
    end

  end

end
matter.IM_ReportData_Pull = Matter_IM_ReportData_Pull

#################################################################################
# Matter_IM_ReportDataSubscribed_Pull
#
# Main difference is that we are the spontaneous initiator
#################################################################################
class Matter_IM_ReportDataSubscribed_Pull : Matter_IM_ReportData_Pull
  #   inherited from Matter_IM_Message
  # static var MSG_TIMEOUT = 5000       # 5s
  # var expiration                      # expiration time for the reporting 
  # var resp                            # response Frame object
  # var ready                           # bool: ready to send (true) or wait (false)
  # var finished                          # if true, the message is removed from the queue
  # var data                            # TLV data of the response (if any)
  # var last_counter                    # counter value of last sent packet (to match ack)
  #   inherited from Matter_IM_ReportData_Pull
  # static var MAX_MESSAGE = 1200       # max bytes size for a single TLV worklaod
  # var generator_or_arr                # a PathGenerator or an array of PathGenerator
  # var event_generator_or_arr          # a EventGenerator, or array of EventGenerator, or nil
  # var subscription_id                 # if not `nil`, subscription_id in response
  var sub                         # subscription object
  var report_data_phase           # true during reportdata

  #################################################################################
  def init(message_handler, session, ctx_generator_or_arr, event_generator_or_arr, sub)
    super(self).init(nil, ctx_generator_or_arr, event_generator_or_arr)     # send msg=nil to avoid creating a reponse
    # we need to initiate a new virtual response, because it's a spontaneous message
    self.resp = matter.Frame.initiate_response(message_handler, session, 0x05 #-Report Data-#, true)
    #
    self.sub = sub
    self.report_data_phase = true
    self.set_subscription_id(sub.subscription_id)
    self.set_suppress_response(false)
  end

  #################################################################################
  def reached_timeout()
    # log(f"MTR: IM_ReportDataSubscribed_Pull reached_timeout()", 3)
    self.sub.remove_self()
  end

  #################################################################################
  # ack received, confirm the heartbeat
  def ack_received(msg)
    # tasmota.log(format("MTR: IM_ReportDataSubscribed ack_received sub=%i", self.sub.subscription_id), 3)
    super(self).ack_received(msg)
    if !self.report_data_phase
      # if ack is received while all data is sent, means that it finished without error
      if self.sub.is_keep_alive   # only if keep-alive, for normal reports, re_arm is called at last StatusReport
        self.sub.re_arm()           # signal that we can proceed to next sub report
      end
      return false                      # proceed to calling send() which removes the message
    else
      return false                      # do nothing
    end
  end

  #################################################################################
  # we received an ACK error, remove subscription
  def status_error_received(msg)
    # tasmota.log(format("MTR: IM_ReportDataSubscribed status_error_received sub=%i exch=%i", self.sub.subscription_id, self.resp.exchange_id), 3)
    self.sub.remove_self()
  end

  #################################################################################
  # ack received for previous message, proceed to next (if any)
  # return true if we manage the ack ourselves, false if it needs to be done upper
  def status_ok_received(msg)
    # tasmota.log(format("MTR: IM_ReportDataSubscribed status_ok_received sub=%i exch=%i", self.sub.subscription_id, self.resp.exchange_id), 3)
    if self.report_data_phase
      return super(self).status_ok_received(msg)
    else
      self.sub.re_arm()                       # always re_arm at last StatusReport. The only case where it does not happen is during keep-alive, hence we need to lookg for Ack (see above)
      super(self).status_ok_received(nil)
      return false                            # let the caller to the ack
    end
  end

  #################################################################################
  # returns true if transaction is complete (remove object from queue)
  # default responder for data
  def send_im(responder)
    # tasmota.log(format("MTR: IM_ReportDataSubscribed send sub=%i exch=%i ready=%i", self.sub.subscription_id, self.resp.exchange_id, self.ready ? 1 : 0), 3)
    # tasmota.log(format("MTR: ReportDataSubscribed::send_im size(self.data.attribute_reports)=%i ready=%s report_data_phase=%s", size(self.data.attribute_reports), str(self.ready), str(self.report_data_phase)), 3)
    if !self.ready   return false  end
    if size(self.data.attribute_reports) > 0      # do we have still attributes to send
      if self.report_data_phase
        super(self).send_im(responder)
        # tasmota.log(format("MTR: ReportDataSubscribed::send_im called super finish=%i", self.finish), 3)
        if !self.finish return end              # ReportData needs to continue
        # ReportData is finished
        self.report_data_phase = false
        self.ready = false
        self.finish = false                     # while a ReadReport would stop here, we continue for subscription
      else
        # send a simple ACK
        var resp = self.resp.build_standalone_ack(false)
        resp.encode_frame()
        resp.encrypt()
        tasmota.log(format("MTR: <Ack       (%6i) ack=%i id=%i", resp.session.local_session_id, resp.ack_message_counter, resp.message_counter), 4)
        responder.send_response_frame(resp)
        self.last_counter = resp.message_counter
        self.finish = true
      end

    else
      # simple heartbeat ReportData
      if self.report_data_phase
        super(self).send_im(responder)
        self.report_data_phase = false
      else
        self.finish = true
      end
    end
  end
end
matter.IM_ReportDataSubscribed_Pull = Matter_IM_ReportDataSubscribed_Pull

#################################################################################
# Matter_IM_SubscribedHeartbeat
#
# Send a subscription heartbeat, which is an empty DataReport with no SuppressResponse
#
# Main difference is that we are the spontaneous initiator
#################################################################################
class Matter_IM_SubscribedHeartbeat : Matter_IM_ReportData
  var sub                         # subscription object

  def init(message_handler, session, data, sub)
    self.resp = matter.Frame.initiate_response(message_handler, session, 0x05 #-Report Data-#, true)
    self.data = data
    self.ready = true                # by default send immediately
    self.expiration = tasmota.millis() + self.MSG_TIMEOUT
    #
    self.sub = sub
  end

  def reached_timeout()
    self.sub.remove_self()
  end

  # ack received, confirm the heartbeat
  def ack_received(msg)
    # tasmota.log(format("MTR: Matter_IM_SubscribedHeartbeat ack_received sub=%i", self.sub.subscription_id), 3)
    super(self).ack_received(msg)
    self.finish = true
    return true                       # proceed to calling send() which removes the message
  end

  # we received an ACK error, remove subscription
  def status_error_received(msg)
    # tasmota.log(format("MTR: Matter_IM_SubscribedHeartbeat status_error_received sub=%i exch=%i", self.sub.subscription_id, self.resp.exchange_id), 3)
    self.sub.remove_self()
    return false                            # let the caller to the ack
  end

  # ack received for previous message, proceed to next (if any)
  # return true if we manage the ack ourselves, false if it needs to be done upper
  def status_ok_received(msg)
    # tasmota.log(format("MTR: Matter_IM_SubscribedHeartbeat status_ok_received sub=%i exch=%i", self.sub.subscription_id, self.resp.exchange_id), 3)
    return false                            # let the caller to the ack
  end

  # default responder for data
  def send_im(responder)
    # tasmota.log(format("MTR: Matter_IM_SubscribedHeartbeat send sub=%i exch=%i ready=%i", self.sub.subscription_id, self.resp.exchange_id, self.ready ? 1 : 0), 3)
    if !self.ready   return false  end

    super(self).send_im(responder)
    self.ready = false
  end
end
matter.IM_SubscribedHeartbeat = Matter_IM_SubscribedHeartbeat

#################################################################################
# Matter_IM_SubscribeResponse
#
# Send a subscription heartbeat, which is an empty DataReport with no SuppressResponse
#
# Main difference is that we are the spontaneous initiator
#################################################################################
class Matter_IM_SubscribedHeartbeat : Matter_IM_ReportData_Pull
  var sub                         # subscription object

  #################################################################################
  def init(message_handler, session, sub)
    super(self).init(nil, nil #-no ctx_generator_or_arr-#, nil #-no event_generator_or_arr-#)     # send msg=nil to avoid creating a reponse
    # we need to initiate a new virtual response, because it's a spontaneous message
    self.resp = matter.Frame.initiate_response(message_handler, session, 0x05 #-Report Data-#, true)
    #
    self.sub = sub
    self.set_subscription_id(sub.subscription_id)
    self.set_suppress_response(true)                # as per Matter definition, heartbeat requires no StatusReport, only a simple Ack
  end

  #################################################################################
  # reached_timeout
  #
  # The heartbeat was not acked within 5 seconds, and after all retries,
  # then the controller is not expecting any more answers,
  # remove the subscription 
  def reached_timeout()
    # log(f"MTR: IM_SubscribedHeartbeat reached_timeout()", 3)
    self.sub.remove_self()
  end

  #################################################################################
  # ack received, confirm the heartbeat and remove the packet from the queue
  def ack_received(msg)
    # log(format("MTR: IM_SubscribedHeartbeat ack_received sub=%i", self.sub.subscription_id), 3)
    super(self).ack_received(msg)
    return false                            # no further response
  end

  #################################################################################
  # we received an ACK error, remove subscription
  def status_error_received(msg)
    # log(format("MTR: IM_SubscribedHeartbeat status_error_received sub=%i exch=%i", self.sub.subscription_id, self.resp.exchange_id), 3)
    self.sub.remove_self()
    return false                            # let the caller to the ack
  end

  #################################################################################
  # ack received for previous message, proceed to next (if any)
  # return true if we manage the ack ourselves, false if it needs to be done upper
  def status_ok_received(msg)
    # log(format("MTR: IM_SubscribedHeartbeat status_ok_received sub=%i exch=%i", self.sub.subscription_id, self.resp.exchange_id), 3)
    return false                            # let the caller to the ack
  end

  #################################################################################
  # default responder for data
  def send_im(responder)
    # log(format("MTR: IM_SubscribedHeartbeat send sub=%i exch=%i ready=%i", self.sub.subscription_id, self.resp.exchange_id, self.ready ? 1 : 0), 3)
    super(self).send_im(responder)
    self.ready = false
  end
end
matter.IM_SubscribedHeartbeat = Matter_IM_SubscribedHeartbeat

#################################################################################
# Matter_IM_SubscribeResponse_Pull
#
# Report Data for a Read Request - pull (lazy) mode
#################################################################################
class Matter_IM_SubscribeResponse_Pull : Matter_IM_ReportData_Pull
  # inherited
  # static var MAX_MESSAGE = 1200       # max bytes size for a single TLV worklaod
  # var generator_or_arr                # a PathGenerator or an array of PathGenerator
  var sub                         # subscription object
  var report_data_phase           # true during reportdata

  #################################################################################
  def init(msg, ctx_generator_or_arr, event_generator_or_arr, sub)
    super(self).init(msg, ctx_generator_or_arr, event_generator_or_arr)
    self.sub = sub
    self.report_data_phase = true
    self.set_subscription_id(sub.subscription_id)
  end

  # default responder for data
  def send_im(responder)
    # tasmota.log(format("MTR: Matter_IM_SubscribeResponse send sub=%i ready=%i", self.sub.subscription_id, self.ready ? 1 : 0), 3)
    if !self.ready   return false  end
    if self.report_data_phase
      super(self).send_im(responder)
      if self.finish
        # finished reporting of data, we still need to send SubscribeResponseMessage after next StatusReport
        self.report_data_phase = false
        self.finish = false       # we continue to subscribe response
      end
      self.ready = false    # wait for Status Report before continuing sending

    else

      # send the final SubscribeReponse
      var resp = self.resp
      var sr = matter.SubscribeResponseMessage()
      sr.subscription_id = self.sub.subscription_id
      sr.max_interval = self.sub.max_interval

      self.resp.opcode = 0x04 #- Subscribe Response -#
      resp.encode_frame(sr.to_TLV().tlv2raw())    # payload in cleartext
      resp.encrypt()
      responder.send_response_frame(resp)
      self.last_counter = resp.message_counter
      # tasmota.log(format("MTR: Send SubscribeResponseMessage sub=%i id=%i", self.sub.subscription_id, resp.message_counter), 3)
      self.sub.re_arm()
      self.finish = true          # remove exchange
    end
  end

  # Status ok received
  def status_ok_received(msg)
    # tasmota.log(format("MTR: IM_SubscribeResponse status_ok_received sub=%i exch=%i ack=%i last_counter=%i", self.sub.subscription_id, self.resp.exchange_id, msg.ack_message_counter ? msg.ack_message_counter : 0 , self.last_counter), 3)
    # once we receive ack, open flow for subscriptions
    tasmota.log(format("MTR: >Sub_OK    (%6i) sub=%i", msg.session.local_session_id, self.sub.subscription_id), 3)
    return super(self).status_ok_received(msg)
    if !self.report_data_phase
      self.finishing = true
    end
  end

end
matter.IM_SubscribeResponse_Pull = Matter_IM_SubscribeResponse_Pull
