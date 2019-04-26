#!/user/bin/env python
import serial
import csv
port = "/dev/ttyACM0"
crct_ans = 0x4B
start_bit = 0xFF
index_flag = 0
index = 0
correct = 0
i_correct = 0
import ctypes
c_uint8 = ctypes.c_uint8
d_1 = 0
d_2 = 0
d_3 = 0
ans_crct = []
path_file = '/home/pi/sketchbook/Seat_Map/file.txt'
quiz_file = '/var/www/html/file.txt'
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

s1 = serial.Serial(port, 9600)
s1.flushInput()
flag = 1;

while flag == 1:

	f = open(quiz_file, "r")
	if str(f.read(1)) == "1":
		print "GOT!!"
		flag = 0
		# s1.write('%d'%start_bit)
	#print (int(f.read()))
	f.close()
print "EXECUTING!!!"
#TODO: read csv file here
with open('answers.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    for row in csv_reader:
        ans_crct.append((int(row[0])))
    print ans_crct
while True:
	if s1.inWaiting()>0:
		inputValue = s1.readline() # need to change this to 3 or figure out a way to solve this
		# print "RAW: " + inputValue
		#comparision
		flags.asByte = c_uint8(int(inputValue))
		if(flags.type == 1):
			flags.asByte = c_uint8(int(inputValue))
			send_ans = Flags()
			send_ans.asByte = c_uint8(int(ans_crct[index]))
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

			index_flag = index_flag + 1
			if(index_flag == 2):
				s1.write('%d'%ans_crct[index])
				print ans_crct[index]
				s1.write('\0')
				index_flag = 0
				index = index + 1
				

			if(index_flag <= 2):
				#compare
				# print ans_crct[index]
				if(int(flags.answers) == int(send_ans.answers)):
					# print "yes"
					correct = correct + 1
				else:
					# print "NO"
					i_correct = i_correct + 1
				# index_flag = 0
				print  "correct: " 
				print correct
				print  "incorrect: " 
				print i_correct
			if(index == len(ans_crct)):
				print "DONE"
				#print index
				
			
		#else:
		#	print( "deviceID:  %i" % flags.deviceID )
		#	print( "occupancy   :  %i" % flags.answers)
		#	if flags.answers == 1:
		#		if flags.deviceID == 1:
		#			d_1 = 1
		#		else:
		#			d_2 = 1
		#		print "occupied"
		#	else:
		#		if flags.deviceID == 1:
		#			d_1 = 0
		#		else:
		#			d_2 = 0
		#		print "Not occupied"
		#	
                
		#	f = open(path_file, "w")

		#	f.write(str(d_1) + '\n' + str(d_2) + '\n') #removed
		#	f.close()
