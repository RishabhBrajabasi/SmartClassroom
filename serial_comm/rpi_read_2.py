#!/user/bin/env python
import serial
import time
port = "/dev/ttyACM0"

s1 = serial.Serial(port, 9600)
s1.flushInput()
list_comp = ["From arduino\r\n"]
while True:
	if s1.inWaiting()>0:
		inputValue = s1.readline()
		print(inputValue)
		if inputValue in list_comp:
			try:
				n = input("From pi Enter flash times: ")
				s1.write('%d'%n)
			except:
				print("ERROR")
				s1.write('0')
		