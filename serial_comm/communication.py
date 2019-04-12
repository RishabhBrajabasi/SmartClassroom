import ctypes
c_uint8 = ctypes.c_uint8

class Flags_bits( ctypes.LittleEndianStructure ):
    _fields_ = [
                ("answers",     c_uint8, 4 ),  # asByte & 1
                ("deviceID", c_uint8, 3 ),  # asByte & 2
                ("type",    c_uint8, 1 ),  # asByte & 4
                # ("idle",       c_uint8, 1 ),  # asByte & 8
               ]

class Flags( ctypes.Union ):
    _anonymous_ = ("bit",)
    _fields_ = [
                ("bit",    Flags_bits ),
                ("asByte", c_uint8    )
               ]

flags = Flags()
flags.asByte = 0x97  # ->0010
ans = '{0:04b}'.format(flags.answers)
ans_arr = [int(i) for i in ans]
if ans_arr[0] == 1:
    print('A')
if ans_arr[1] == 1:
    print('B')
if ans_arr[2] == 1:
    print('C')
if ans_arr[3] == 1:
    print('D')
# print( "logout: %i"      % flags.bit.logout   )
# `bit` is defined as anonymous field, so its fields can also be accessed directly:
print( "type: %i"      % flags.type     )
print( "deviceID:  %i" % flags.deviceID )
print( "answers   :  %i" % flags.answers    )
# print( "idle  : %i"      % flags.idle       )