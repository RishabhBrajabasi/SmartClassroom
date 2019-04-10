#!/usr/bin/env python

import RPi.GPIO as GPIO
import time
import csv
from datetime import date
import datetime
from mfrc522 import SimpleMFRC522
import threading
timer_1 = 0
timer_2 = 0
timer_3 = 0
def reset_time_1 ():
	global timer_1
	timer_1 = 0
	# print "Timer Reset_1"

def reset_time_2 ():
	global timer_2
	timer_2 = 0
	# print "Timer Reset_2"

def reset_time_3 ():
	global timer_3
	timer_3 = 0
	# print "Timer Reset_3"


reader = SimpleMFRC522()
c1 = 0
c2 = 0
c3 = 0
list_1 = []
list_2 = []
list_3 = []
csv_path = '/var/www/html/data/report.csv'
place_card = 0
try:
	while True:
		if place_card == 0:
			print("Place your card:")
			place_card = 1
		
		id, name = reader.read()
		if id == 218219784636 or id == 428573490223:
			if timer_1 == 0:
				# print(id)
				print "Name: " + name
				if c1 == 0:
					list_1.append('Sakthikarthik Baskar')

					print "Date: " + str(date.today())
					print "Entry time: " + (datetime.datetime.now().strftime("%I:%M:%S %p"))
					list_1.append(str(date.today()))
					list_1.append((datetime.datetime.now().strftime("%I:%M:%S %p")))
					c1 += 1
				elif c1 == 1:
					print "Date: " + str(date.today())
					print "Exit time: " + (datetime.datetime.now().strftime("%I:%M:%S %p"))
					list_1.append((datetime.datetime.now().strftime("%I:%M:%S %p")))
					#append the csv files
					with open(csv_path, 'a') as csvFile:
						Writer = csv.writer(csvFile)
						Writer.writerow(list_1)
					csvFile.close()
					# print list_1
					del list_1[:]
					c1 = 0
				print " "
				timer_1 = 1
				#start timer here that will reset this back to 0
				timer_a = threading.Timer(10.0, reset_time_1)
				timer_a.start()
				place_card = 0

		elif id == 251203660040 or id == 775284314735:
			if timer_2 == 0:
				# print(id)
				print "Name: " + name
				if c2 == 0:
					list_2.append('Smruthi Ramesh')
					print "Date: " + (date.today())
					print "Entry time: " + (datetime.datetime.now().strftime("%I:%M:%S %p"))
					list_2.append(str(date.today()))
					list_2.append((datetime.datetime.now().strftime("%I:%M:%S %p")))

					c2 += 1
				elif c2 == 1:
					print "Date: " + (date.today())
					print "Exit time: " + (datetime.datetime.now().strftime("%I:%M:%S %p"))
					list_2.append((datetime.datetime.now().strftime("%I:%M:%S %p")))
					with open(csv_path, 'a') as csvFile:
						Writer = csv.writer(csvFile)
						Writer.writerow(list_2)
					csvFile.close()
					del list_2[:]
					c2 = 0
				print " "
				timer_2 = 1
				timer_b = threading.Timer(10.0, reset_time_2)
				timer_b.start()
				place_card = 0


		elif id == 440800049540  or id == 881298603775:
			if timer_3 == 0:
				# print(id)
				print "Name: " + name
				if c3 == 0:
					list_3.append('Rishabh Brajabasi')
					print "Date: " + (date.today())
					print "Entry time: " + (datetime.datetime.now().strftime("%I:%M:%S %p"))
					list_3.append(str(date.today()))
					list_3.append((datetime.datetime.now().strftime("%I:%M:%S %p")))

					c3 += 1
				elif c3 == 1:
					print "Date: " + (date.today())
					print "Exit time: " + (datetime.datetime.now().strftime("%I:%M:%S %p"))
					list_3.append((datetime.datetime.now().strftime("%I:%M:%S %p")))
					with open(csv_path, 'a') as csvFile:
						Writer = csv.writer(csvFile)
						Writer.writerow(list_3)
					csvFile.close()
					del list_3[:]
					c3 = 0
				print " "
				timer_3 = 1
				timer_c = threading.Timer(10.0, reset_time_3)
				timer_c.start()
				place_card = 0


		else:
			print "You are not registered for this class"
			place_card = 0
			#print (id)
		# print " "
		time.sleep(2)
except KeyboardInterrupt:
	GPIO.cleanup()
