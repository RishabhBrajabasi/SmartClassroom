#!/usr/bin/env python

import RPi.GPIO as GPIO
import time
import datetime
from mfrc522 import SimpleMFRC522

reader = SimpleMFRC522()
c1 = 0
c2 = 0
c3 = 0
try:
	while True:

		print("Place your card:")

		id, name = reader.read()
		if id == 218219784636:
			#print(id)
			print "Name: " + name
			if c1 == 0:
				print "Entry time:" + str(datetime.datetime.now())
				c1 += 1
			elif c1 == 1:
				print "Exit time:" + str(datetime.datetime.now())
				c1 = 0
		elif id == 251203660040:
			print(id)
			print "Name: " + name
			if c2 == 0:
				print "Entry time:" + str(datetime.datetime.now())
				c2 += 1
			elif c2 == 1:
				print "Exit time:" + str(datetime.datetime.now())
				c2 = 0
		elif id == 440800049540:
			print(id)
			print "Name: " + name
			if c3 == 0:
				print "Entry time:" + str(datetime.datetime.now())
				c3 += 1
			elif c3 == 1:
				print "Exit time:" + str(datetime.datetime.now())
				c3 = 0
		else:
			print "Not registered for this class"
		print " "
		time.sleep(2)
except KeyboardInterrupt:
	GPIO.cleanup()
