# autogenerated by genmsg_py from Chessboard.msg. Do not edit.
import roslib.message
import struct

import geometry_msgs.msg

class Chessboard(roslib.message.Message):
  _md5sum = "cfee5ce35555e8905c14b144b9872d2a"
  _type = "chessbot/Chessboard"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """float32 sidelength
geometry_msgs/Point centerpoint
float32 rotation
================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

"""
  __slots__ = ['sidelength','centerpoint','rotation']
  _slot_types = ['float32','geometry_msgs/Point','float32']

  ## Constructor. Any message fields that are implicitly/explicitly
  ## set to None will be assigned a default value. The recommend
  ## use is keyword arguments as this is more robust to future message
  ## changes.  You cannot mix in-order arguments and keyword arguments.
  ##
  ## The available fields are:
  ##   sidelength,centerpoint,rotation
  ##
  ## @param self: self
  ## @param args: complete set of field values, in .msg order
  ## @param kwds: use keyword arguments corresponding to message field names
  ## to set specific fields. 
  def __init__(self, *args, **kwds):
    if args or kwds:
      super(Chessboard, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.sidelength is None:
        self.sidelength = 0.
      if self.centerpoint is None:
        self.centerpoint = geometry_msgs.msg.Point()
      if self.rotation is None:
        self.rotation = 0.
    else:
      self.sidelength = 0.
      self.centerpoint = geometry_msgs.msg.Point()
      self.rotation = 0.

  ## internal API method
  def _get_types(self): return self._slot_types

  ## serialize message into buffer
  ## @param buff StringIO: buffer
  def serialize(self, buff):
    try:
      buff.write(struct.pack('<f3df', self.sidelength, self.centerpoint.x, self.centerpoint.y, self.centerpoint.z, self.rotation))
    except struct.error, se: self._check_types(se)
    except TypeError, te: self._check_types(te)

  ## unpack serialized message in str into this message instance
  ## @param self: self
  ## @param str str: byte array of serialized message
  def deserialize(self, str):
    try:
      if self.centerpoint is None:
        self.centerpoint = geometry_msgs.msg.Point()
      end = 0
      start = end
      end += 32
      (self.sidelength, self.centerpoint.x, self.centerpoint.y, self.centerpoint.z, self.rotation,) = struct.unpack('<f3df',str[start:end])
      return self
    except struct.error, e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill


  ## serialize message with numpy array types into buffer
  ## @param self: self
  ## @param buff StringIO: buffer
  ## @param numpy module: numpy python module
  def serialize_numpy(self, buff, numpy):
    try:
      buff.write(struct.pack('<f3df', self.sidelength, self.centerpoint.x, self.centerpoint.y, self.centerpoint.z, self.rotation))
    except struct.error, se: self._check_types(se)
    except TypeError, te: self._check_types(te)

  ## unpack serialized message in str into this message instance using numpy for array types
  ## @param self: self
  ## @param str str: byte array of serialized message
  ## @param numpy module: numpy python module
  def deserialize_numpy(self, str, numpy):
    try:
      if self.centerpoint is None:
        self.centerpoint = geometry_msgs.msg.Point()
      end = 0
      start = end
      end += 32
      (self.sidelength, self.centerpoint.x, self.centerpoint.y, self.centerpoint.z, self.rotation,) = struct.unpack('<f3df',str[start:end])
      return self
    except struct.error, e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill

