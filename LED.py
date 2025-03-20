from tkinter import *
import random
import os
import re

mainwin = Tk(className = " LED Simulator")
mainwin.geometry("800x680")
canvas1 = Canvas(mainwin,width = 800, height = 600, bg = "blue")
canvas1.place(x=-1,y=-1)

psize = 3


def createLED(x,y):
 canvas1.create_rectangle(x, y, x+psize, y+psize, fill="black")
 canvas1.create_oval(x, y, x+psize, y+psize, fill="white")

def createChar(x,y,points):
  canvas1.create_rectangle(x, y, x+psize*8, y+psize*8, fill="black")
  for p in points:
    createLED(x+p[0]*psize,y+p[1]*psize)
  

createChar(0,0,[(3,0),(4,0), (4,1),(3,1),(2,1),(4,2),(3,2), (4,3),(3,3), (4,4),(3,4), (4,5),(3,5),\
                   (4,6),(3,6),(2,6),(5,6),(1,6),(6,6), (4,7),(3,7), (2,7),(5,7), (1,7),(6,7)])

createChar(60, 10, [
    (1, 7), (2, 7), (3, 7), (4, 7), (5, 7),  # Bottom row
    (0, 6), (6, 6),  # Bottom row, left and right ends
    (0, 5), (6, 5),  # Second row from bottom, left and right ends
    (0, 4), (6, 4),  # Third row from bottom, left and right ends
    (0, 3), (6, 3),  # Fourth row from bottom, left and right ends
    (0, 2), (6, 2),  # Fifth row from bottom, left and right ends
    (1, 1), (5, 1),  # Sixth row from bottom, left and right ends
    (2, 0), (3, 0), (4, 0),  # Top row, middle three LEDs
    (3, 4), (4, 4)  # Middle of the "A"
])

createChar(50, 50, [
    (1, 0), (2, 0), (3, 0), (4, 0), (5, 0),  # Top row
    (6, 1),  # Second row, rightmost end
    (6, 2),  # Third row, rightmost end
    (1, 3), (2, 3), (3, 3), (4, 3), (5, 3),  # Middle row
    (0, 4),  # Fifth row, leftmost end
    (0, 5),  # Sixth row, leftmost end
    (1, 6), (2, 6), (3, 6), (4, 6), (5, 6),  # Bottom row
])

class ButtonManager:
    def __init__(self, button,x,y):
        self.button = button
        self.x = x
        self.y = y
        self.is_white = False  # Track the button's color state
        self.button.config(command=self.toggle_color, activebackground="black")

    def toggle_color(self):
        if self.is_white:
            self.button.config(bg="black", activebackground="black")
        else:
            self.button.config(bg="white", activebackground="white")
        self.is_white = not self.is_white  # Toggle the color state
        textOutput.delete("1.0","end-1c")
        whitebuttons = []
        whitebuttonsxy = []
        for b in buttons:
            if b.is_white:
             whitebuttons.append(b)
             whitebuttonsxy.append((b.x,b.y))
        for b in whitebuttons:
            textOutput.insert(INSERT,"("+str(b.x)+","+str(b.y)+")")
            if b != whitebuttons[-1]:
               textOutput.insert(INSERT,", ")
        createChar(170, 170, whitebuttonsxy)


buttons = []
for i in range(8):
    for j in range(8):
      button = Button(mainwin, text=" ", bg="black", fg="white")
      button.place(x=i*40+400,y=20+j*40+100)
      buttons.append(ButtonManager(button,i,j))


textInput = Text(mainwin,width=80,height=6,bg="black",fg="yellow")
textInput.place(x=0,y=480)
textOutput = Text(mainwin,width=80,height=6,bg="black",fg="orange")
textOutput.place(x=0,y=580)

def cleargrid():
     for b in buttons:
       b.is_white = False
       b.button.config(bg="black") 

def ReadData():
    cleargrid()
    coordinate_string = textInput.get("1.0", END)
    # Regular expression to extract pairs of numbers
    matches = re.findall(r'\((\d+),(\d+)\)', coordinate_string)
    # Convert matches to a list of tuples
    coordinates = [(int(x), int(y)) for x, y in matches]
    for b in buttons:
       if (b.x,b.y) in coordinates:
          b.toggle_color()
       


btnRead = Button(mainwin,text="READ", bg="black", fg="white", command = ReadData)
btnRead.place(x=100,y=400)


mainwin.mainloop()
