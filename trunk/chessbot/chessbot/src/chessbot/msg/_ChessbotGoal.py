# autogenerated by genmsg_py from ChessbotGoal.msg. Do not edit.
import roslib.message
import struct


class ChessbotGoal(roslib.message.Message):
  _md5sum = "a89dc6763697b95e76194f808753f94e"
  _type = "chessbot/ChessbotGoal"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
#goal definition
int8 origin_row
int8 origin_col
int8 destination_row
int8 destination_col
bool capture


"""
  __slots__ = ['origin_row','origin_col','destination_row','destination_col','capture']
  _slot_types = ['int8','int8','int8','int8','bool']

  ## Constructor. Any message fields that are implicitly/explicitly
  ## set to None will be assigned a default value. The recommend
  ## use is keyword arguments as this is more robust to future message
  ## changes.  You cannot mix in-order arguments and keyword arguments.
  ##
  ## The available fields are:
  ##   origin_row,origin_col,destination_row,destination_col,capture
  ##
  ## @param self: self
  ## @param args: complete set of field values, in .msg order
  ## @param kwds: use keyword arguments corresponding to message field names
  ## to set specific fields. 
  def __init__(self, *args, **kwds):
    if args or kwds:
      super(ChessbotGoal, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.origin_row is None:
        self.origin_row = 0
      if self.origin_col is None:
        self.origin_col = 0
      if self.destination_row is None:
        self.destination_row = 0
      if self.destination_col is None:
        self.destination_col = 0
      if self.capture is None:
        self.capture = False
    else:
      self.origin_row = 0
      self.origin_col = 0
      self.destination_row = 0
      self.destination_col = 0
      self.capture = False

  ## internal API method
  def _get_types(self): return self._slot_types

  ## serialize message into buffer
  ## @param buff StringIO: buffer
  def serialize(self, buff):
    try:
      buff.write(struct.pack('<4bB', self.origin_row, self.origin_col, self.destination_row, self.destination_col, self.capture))
    except struct.error, se: self._check_types(se)
    except TypeError, te: self._check_types(te)

  ## unpack serialized message in str into this message instance
  ## @param self: self
  ## @param str str: byte array of serialized message
  def deserialize(self, str):
    try:
      end = 0
      start = end
      end += 5
      (self.origin_row, self.origin_col, self.destination_row, self.destination_col, self.capture,) = struct.unpack('<4bB',str[start:end])
      self.capture = bool(self.capture)
      return self
    except struct.error, e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill


  ## serialize message with numpy array types into buffer
  ## @param self: self
  ## @param buff StringIO: buffer
  ## @param numpy module: numpy python module
  def serialize_numpy(self, buff, numpy):
    try:
      buff.write(struct.pack('<4bB', self.origin_row, self.origin_col, self.destination_row, self.destination_col, self.capture))
    except struct.error, se: self._check_types(se)
    except TypeError, te: self._check_types(te)

  ## unpack serialized message in str into this message instance using numpy for array types
  ## @param self: self
  ## @param str str: byte array of serialized message
  ## @param numpy module: numpy python module
  def deserialize_numpy(self, str, numpy):
    try:
      end = 0
      start = end
      end += 5
      (self.origin_row, self.origin_col, self.destination_row, self.destination_col, self.capture,) = struct.unpack('<4bB',str[start:end])
      self.capture = bool(self.capture)
      return self
    except struct.error, e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill
