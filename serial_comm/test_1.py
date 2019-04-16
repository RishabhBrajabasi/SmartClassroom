#!/user/bin/env python
path_file = '/Users/sakthi/Sites/file.txt'

flag = 1;

while flag == 1:

	f = open(path_file, "r")
	if f.read() == '1':
		print "GOT!!"
		flag = 0
	f.close()
print "EXECUTING!!!"