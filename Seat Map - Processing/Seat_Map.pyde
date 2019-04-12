seat_1 = 1
seat_2 = 1
seat_3 = 1
logs = ""
seat_array = []

r_val_1 = 0
g_val_1 = 255
r_val_2 = 0
g_val_2 = 255
r_val_3 = 0
g_val_3 = 255

x1 = 50;
y1 = 50;
w1 = 100;
h1 = 75;

x2 = 45;
y2 = 45;
w2 = 95;
h2 = 70;

x3 = 65;
y3 = 55;
w3 = 105;
h3 = 80;

def setup():
    global logs
    global seat_array
    
    logs = loadStrings("file.txt")

    for l in logs:
        seat_array.append(int(l))
    print seat_array
    size(480, 480)
    background(255,255,255)
    textSize(16)
    fill(0,0,0)
    text("Classroom Seating:", 55, 20);
    
def draw():
    global seat_1
    global seat_2
    global seat_3
    global r_val_1
    global g_val_1
    global r_val_2
    global g_val_2
    global r_val_3
    global g_val_3
    global logs
    
    logs = loadStrings("file.txt")
    seat_array = []
    for l in logs:
        seat_array.append(int(l))
    print seat_array
    
    seat_1 = seat_array[0]
    seat_2 = seat_array[1]
    seat_3 = seat_array[2]
    
    if seat_1 == 0:
        r_val_1 = 255
        g_val_1 = 0
        
    elif seat_1 == 1:
        r_val_1 = 0
        g_val_1 = 255
        
    if seat_2 == 0:
        r_val_2 = 255
        g_val_2 = 0
        
    elif seat_2 == 1:
        r_val_2 = 0
        g_val_2 = 255
    
    if seat_3 == 0:
        r_val_3 = 255
        g_val_3 = 0
        
    elif seat_3 == 1:
        r_val_3 = 0
        g_val_3 = 255
    
    fill(r_val_1, g_val_1, 0)
    rect(30, 50, 55, 55, 7)
    
    fill(r_val_2, g_val_2, 0)
    rect(95, 50, 55, 55, 7)
    
    fill(r_val_3, g_val_3, 0)
    rect(160, 50, 55, 55, 7)
