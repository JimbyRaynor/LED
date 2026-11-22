import math
import LEDlib


def createLEDcolourSolid2(canvas, x,y, colour, LEDpoints, mypsize):
 p2 = canvas.create_rectangle(x, y, x+mypsize, y+mypsize, fill=colour, outline = "")
 LEDpoints.append(p2)

def createCharColourSolid2(canvas,x,y,colourpoints, LEDpoints, mypsize):
  for p in colourpoints:
    createLEDcolourSolid2(canvas,x+p[0]*mypsize,y+p[1]*mypsize,p[2], LEDpoints, mypsize)




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


class LEDobj2:
    def __init__(self, canvas,x=0,y=0, CharPointsList = [], pixelsize = 2):
         global psize
         self.alive = True
         self.AniNumber = 0 # Animation index
         self.x = x
         self.y = y
         self.canvas = canvas
         self.LEDPoints = [] # canvas storage for points
         self.CharPointsList = CharPointsList
         self.CharPoints = CharPointsList[0] # character point list from LEDColour C++ program
         self.pixelsize = pixelsize
         createCharColourSolid2(canvas,x,y,self.CharPoints,self.LEDPoints, pixelsize)
    def loadchar(self, NewChar):
        self.CharPoints = NewChar
        self.draw() 
    def resetposition(self,x,y):
        self.x, self.y = x,y
        self.draw()
    def undraw(self):
         for p in self.LEDPoints:
            self.canvas.delete(p)
         self.LEDPoints.clear()
    def draw(self):
        self.undraw()
        createCharColourSolid2(self.canvas,self.x,self.y,self.CharPoints,self.LEDPoints, self.pixelsize)
    def Animate(self):
        self.AniNumber += 1
        if self.AniNumber < len(self.CharPointsList):
           self.loadchar(self.CharPointsList[self.AniNumber])           
        else:
           self.AniNumber = -1
