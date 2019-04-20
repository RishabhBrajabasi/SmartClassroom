seat_1 = 1
seat_2 = 1
logs = ""
seat_array = []

r_val_1 = 0
g_val_1 = 255
r_val_2 = 0
g_val_2 = 255

def setup():
    global logs
    global seat_array
    
    logs = loadStrings("file.txt")

    for l in logs:
        seat_array.append(int(l))
    print seat_array
    
    size(480, 480)
    background(255,255,255)
    textSize(20)
    fill(0,0,0)
    text("WEH 5312 CLASSROOM SEATING:", 90, 20);
    
    fill(10,66,44)
    rect(30, 50, 410, 110, 7)
    textSize(16)
    fill(0,0,0)
    text("Face this way", 165, 180);
    
    fill(r_val_1, g_val_1, 0)
    rect(150, 230, 55, 55, 7)
    textSize(12)
    fill(0,0,0)
    text("Seat 1", 160, 300);
    
    fill(r_val_2, g_val_2, 0)
    rect(245, 230, 55, 55, 7)
    textSize(12)
    fill(0,0,0)
    text("Seat 2", 255, 300);
    
def draw():
    global seat_1
    global seat_2
    global seat_3
    global r_val_1
    global g_val_1
    global r_val_2
    global g_val_2
    global logs
    
    logs = loadStrings("file.txt")
    seat_array = []
    try:
        for l in logs:
            seat_array.append(int(l))
        #print seat_array
        seat_1 = seat_array[0]
        seat_2 = seat_array[1]
    except:
        print "Old values"
    
    if seat_1 == 1:
        r_val_1 = 255
        g_val_1 = 0
        
    elif seat_1 == 0:
        r_val_1 = 0
        g_val_1 = 255
        
    if seat_2 == 1:
        r_val_2 = 255
        g_val_2 = 0
        
    elif seat_2 == 0:
        r_val_2 = 0
        g_val_2 = 255
    
    fill(r_val_1, g_val_1, 0)
    rect(150, 230, 55, 55, 7)
    
    fill(r_val_2, g_val_2, 0)
    rect(245, 230, 55, 55, 7)
