from tkinter import *
import random
import os

mainwin = Tk(className = "Centipede")
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
  

createChar(10,10,[(3,0),(4,0), (4,1),(3,1),(2,1),(4,2),(3,2), (4,3),(3,3), (4,4),(3,4), (4,5),(3,5),\
                   (4,6),(3,6),(2,6),(5,6),(1,6),(6,6), (4,7),(3,7), (2,7),(5,7), (1,7),(6,7)])

mainwin.mainloop()
