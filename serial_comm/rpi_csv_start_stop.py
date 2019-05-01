#!/user/bin/env python
import serial
import csv
import time
import sys
import os
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
write_csv = []
path_file = '/home/pi/sketchbook/Seat_Map/file.txt'
quiz_file = '/var/www/html/file.txt'
quiz_site = '/var/www/html/data.csv'
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

os.remove(quiz_site)
#TODO: read csv file here
with open('answers.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    for row in csv_reader:
        ans_crct.append((int(row[0])))
    print ans_crct
    	# print row[0]
while True:
	# while flag == 1:
	f = open(quiz_file, "r")
	if str(f.read(1)) == "1":
		print "START QUIZ"
		flag = 0
		s1.write('%d'%start_bit)
		s1.write('\0')
	#print (int(f.read()))
	f.close()

	if s1.inWaiting()>0:
		inputValue = s1.readline() # need to change this to 3 or figure out a way to solve this
#		print "RAW: " + inputValue
		#comparision
		flags.asByte = c_uint8(int(inputValue))

		# ANSWER
		if(flags.type == 1):
			print("Rx Answer")
			flags.asByte = c_uint8(int(inputValue))
			send_ans = Flags()
			send_ans.asByte = c_uint8(int(ans_crct[index]))
			ans = '{0:04b}'.format(flags.answers)
			ans_arr = [int(i) for i in ans] #for populating the csv
			if ans_arr[0] == 1:
			    print('\tA')
			if ans_arr[1] == 1:
			    print('\tB')
			if ans_arr[2] == 1:
			    print('\tC')
			if ans_arr[3] == 1:
			    print('\tD')
			# print(ans[5])
			print( "\t type: %i"      % flags.type     )
			print( "\t deviceID:  %i" % flags.deviceID )
			print( "\t answers   :  %i" % flags.answers    )

			index_flag = index_flag + 1
			if(index_flag <= 2):
				print ("Comparing answer ")
				#compare
				# print ans_crct[index]
				if(int(flags.answers) == int(send_ans.answers)):
					# print "yes"
					correct = correct + 1
				else:
					# print "NO"
					i_correct = i_correct + 1
				# index_flag = 0
				print ( "correct: " ,correct)
				print ( "incorrect: ",i_correct)
			if(index_flag == 2): #recieved response from both the nodes
				# Send Correct answer
				s1.write('%d'%ans_crct[index])
				s1.write('\0')
				print("Answer Sent for question no: ",index) #index is the question number
				print ans_crct[index]
				#s1.write('\0')

				# Resetting start of quiz and other variables
				f = open(quiz_file, "w") #redundant
				f.write("0")
				f.close()
				index_flag = 0
				index = index + 1
				#correct and incorrect answer has the correct value. Write to data.csv
				write_csv.append(str(index))
				write_csv.append(str(correct))
				write_csv.append(str(i_correct))
				with open(quiz_site, 'a+') as csvFile:
						Writer = csv.writer(csvFile)
						Writer.writerow(write_csv)
				csvFile.close()
				del write_csv[:]
				correct = 0
				i_correct = 0
				flag = 1
				# Sending start of quiz again
#				time.sleep(5)
#				print("Sending start of quiz again")
#				s1.write('%d'%start_bit)
#				s1.write('\0')
				
			
			if(index == len(ans_crct)):
				print "***ALL QUESTION DONE***"
				sys.exit()

				#print index
				
			
		else:
			print( "deviceID:  %i" % flags.deviceID )
			print( "occupancy   :  %i" % flags.answers)
			if flags.answers == 1:
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

			f.write(str(d_1) + '\n' + str(d_2) + '\n') #removed
			f.close()
