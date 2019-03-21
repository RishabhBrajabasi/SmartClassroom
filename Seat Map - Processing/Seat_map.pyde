def setup():
    size(240, 240)
    background(255,255,255)
    textSize(16)
    fill(0,0,0)
    text("Classroom Seating:", 55, 20);

seat_1 = 1
seat_2 = 1
seat_3 = 1

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
    
def mouseClicked():
    global seat_1
    global seat_2
    global seat_3
    if (mouseX > x1) and (mouseX < x1+w1) and (mouseY > y1) and (mouseY < y1+h1):
        seat_1 = not seat_1
    if (mouseX > x2) and (mouseX < x2+w2) and (mouseY > y2) and (mouseY < y2+h2):
        seat_2 = not seat_2
    if (mouseX > x3) and (mouseX < x3+w3) and (mouseY > y3) and (mouseY < y3+h3):
        seat_3 = not seat_3
    
    
    
