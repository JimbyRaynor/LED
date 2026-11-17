import math
import LEDlib


class scrollboxobj2:
    def __init__(self, canvas,x=0,y=0,width=1000,height=700,maxlines=10,pixelsize = 3, charwidth = 24):
        self.x = x
        self.y = y
        self.maxlines = maxlines
        self.width = width
        self.height = height
        self.canvas = canvas
        self.pixelsize = pixelsize
        self.charwidth = charwidth
        self.walls = 0
        self.scrollboxtext = [] # list of lines of text to display
        self.scrollboxLEDlines = [] # list of canvas objects that draw each line of text
        self.scrollboxstart = 0 # draw lines starting at line scrollboxstart (simulates scrolling), scrolling is automatic after adding 'maxlines' lines
        for i in range(self.maxlines):
            self.scrollboxLEDlines.append(self.drawtext(self.x+5,self.y+5+i*26," "))
        self.draw()
    def __del__(self):  # this will call the destructor of all objects inside this class, e.g. scrollboxLEDlines and all its contents
        self.undraw()
    def drawtext(self,x,y,mytext):
        return LEDlib.LEDtextobj(self.canvas,x=x,y=y,text=mytext,colour="light green",pixelsize = self.pixelsize, charwidth=self.charwidth , solid = False, square=False)
    def scrollboxset(self,i,mytext):
        self.scrollboxLEDlines[i].update(mytext)
    def scrollboxadd(self,mytext):
        if len(self.scrollboxtext) >= self.maxlines: self.scrollboxstart = self.scrollboxstart + 1
        self.scrollboxtext.append(mytext)
        i = 0
        while i <= self.maxlines and i <= len(self.scrollboxtext)-1-self.scrollboxstart:
          self.scrollboxset(i,self.scrollboxtext[self.scrollboxstart+i])
          i = i + 1
    def draw(self):
        self.walls = self.canvas.create_rectangle(self.x,self.y,self.x+self.width,self.y+self.height,outline="light green")
    def undraw(self):
        self.canvas.delete(self.walls)
