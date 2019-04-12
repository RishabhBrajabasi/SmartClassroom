#!/user/bin/env python
import serial
port = "/dev/ttyACM0"
crct_ans = 79
import ctypes
c_uint8 = ctypes.c_uint8
d_1 = 0
d_2 = 0
d_3 = 0
path_file = '/home/pi/sketchbook/Seat_Map/file.txt'
class bits(ctypes.LittleEndianStructure):
    _fields_ = [
                ("occupancy", c_uint8, 1),
                

    ]
class Flags_bits( ctypes.LittleEndianStructure ):
    _fields_ = [
                ("answers",     c_uint8, 4 ),  # asByte & 1
                ("deviceID", c_uint8, 3 ),  # asByte & 2
                ("type",    c_uint8, 1 ),  # asByte & 4
                # ("idle",       c_uint8, 1 ),  # asByte & 8
               ]

class Flags( ctypes.Union ):
    _anonymous_ = ("bit", "quiz")
    _fields_ = [
                ("bit",    bits ),
                ("asByte", c_uint8),
                ("quiz", Flags_bits)

               ]

flags = Flags()

s1 = serial.Serial(port, 9600)
s1.flushInput()
while True:
	if s1.inWaiting()>0:
		inputValue = s1.read(2) # need to change this to 3 or figure out a way to solve this
		print "RAW: " + inputValue
		flags.asByte = c_uint8(int(inputValue))
		if(flags.type == 1):
			# flags.asByte = c_uint8(int(inputValue))
			ans = '{0:04b}'.format(flags.answers)
			ans_arr = [int(i) for i in ans] #for populating the csv
			if ans_arr[0] == 1:
			    print('A')
			if ans_arr[1] == 1:
			    print('B')
			if ans_arr[2] == 1:
			    print('C')
			if ans_arr[3] == 1:
			    print('D')
			# print(ans[5])
			print( "type: %i"      % flags.type     )
			print( "deviceID:  %i" % flags.deviceID )
			print( "answers   :  %i" % flags.answers    )
			s1.write('%d'%crct_ans)
		else:
			print( "deviceID:  %i" % flags.deviceID )
			print( "occupancy   :  %i" % flags.occupancy)
			if flags.occupancy == 1:
				if flags.deviceID == 1:
					d_1 = 1
				else:
					d_2 = 1
				print "occupied"
			else:
				if flags.deviceID == 1:
					d_1 = 0
				else:
					d_2 = 0
				print "Not occupied"
			

		f = open(path_file, "w")

		f.write(str(d_1) + '\n' + str(d_2) + '\n' + str(d_3) + '\n')
		f.close()
