from tkinter import *
import LEDlib
import re


mainwin = Tk(className = " LED Simulator")
mainwin.geometry("1200x880")
canvas1 = Canvas(mainwin,width = 1200, height = 880, bg = "black")
canvas1.place(x=-1,y=-1)

psize = 12

LEDpoints = []
    

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
        LEDlib.createChar(canvas1,10, 10, whitebuttonsxy,LEDpoints)


buttons = []
for i in range(24):
    for j in range(24):
      button = Button(mainwin, text=" ", bg="black", fg="white")
      button.place(x=i*35+200,y=20+j*30+10)
      buttons.append(ButtonManager(button,i,j))


textInput = Text(mainwin,width=80,height=6,bg="black",fg="yellow")
textInput.place(x=0,y=750)
textOutput = Text(mainwin,width=80,height=6,bg="black",fg="orange")
textOutput.place(x=600,y=750)

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

def Erase():
    LEDlib.Erasepoints(canvas1,LEDpoints)

btnErase = Button(mainwin,text="Erase", bg="black", fg="white", command = Erase)
btnErase.place(x=100,y=500)

mainwin.mainloop()
