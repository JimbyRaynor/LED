import math
from LEDlib import *
import pygame

digits = [ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE]
charactermap = [charA,charB,charC,charD,charE,charF,charG,charH,charI,charJ,charK,charL,charM,charN,charO,charP,charQ,charR,charS,charT,charU,charV,charW,charX,charY,charZ] 

def pygamecreateCharBlockColour2(screen,x,y,colour, points,solid=False):
    for p in points:
      if solid == True:
       srect = pygame.Rect(x+p[0]*psize,y+p[1]*psize, psize, psize)
       pygame.draw.rect(screen, colour, srect)
      else:
       pygame.draw.circle(screen,colour,(x+p[0]*psize+psize/2,y+p[1]*psize+psize/2),psize/2)

def pygameShowColourScore2(canvas,x,y,colour, myscore,numzeros=9,solid=False):
    stringscore = str(myscore).zfill(numzeros) 
    for i,c in enumerate(stringscore):
       pygamecreateCharBlockColour2(canvas,x+i*charwidth,y,colour,digits[int(c)], solid = solid)
      
def pygameShowColourText2(canvas,x,y,colour, mytext, solid = False):
    mytext = mytext.upper()
    AdjustPos = 0
    for i,c in enumerate(mytext):  # i=0 pairs with c = first char in mytext, i = 1 pairs with c = second char, etc
       if c in ["M","W","V"]:
           AdjustPos =  AdjustPos + charwidth/8
       if c in ["I"]:
           AdjustPos =  AdjustPos - charwidth/8
       if c != ' ':
          if c in "0123456789":
            pygamecreateCharBlockColour2(canvas,x+i*charwidth+AdjustPos,y,colour,digits[int(c)], solid = solid)
          elif c == "%":
            pygamecreateCharBlockColour2(canvas,x+i*charwidth+AdjustPos,y,colour,charPercent, solid = solid)
          elif c == ".":
            AdjustPos = AdjustPos-2*charwidth/8
            pygamecreateCharBlockColour2(canvas,x+i*charwidth+AdjustPos,y,colour,charDot, solid = solid)
          elif c == ":":
            AdjustPos = AdjustPos-2*charwidth/8
            pygamecreateCharBlockColour2(canvas,x+i*charwidth+AdjustPos,y,colour,charColon, solid = solid)
          elif ord(c)-65 >= 0 and ord(c)-65 < len(charactermap):
            pygamecreateCharBlockColour2(canvas,x+i*charwidth+AdjustPos,y,colour, charactermap[ord(c)-65], solid = solid)  
       if c in ["I"]:
           AdjustPos =  AdjustPos - charwidth/8    

class pygameLEDtextobj:
    def __init__(self, screen,x=0,y=0, text = "", colour = "white", pixelsize = 2, charwidth=23, solid = False):
         self.x = x
         self.y = y
         self.text = text
         self.screen = screen
         self.colour = colour
         self.pixelsize = pixelsize
         self.charwidth = charwidth
         self.solid = solid
         self.draw()
    def draw(self):
        global charwidth, psize
        charwidth = self.charwidth
        psize = self.pixelsize
        pygameShowColourText2(self.screen,self.x,self.y,self.colour,self.text, self.solid) 
    def update(self,mytext):
        self.text = mytext
        self.draw()

class pygameLEDscoreobj:
    def __init__(self, screen,x=0,y=0, score = 0, colour = "white", pixelsize = 2, charwidth=23, numzeros = 0, solid = False):
         self.x = x
         self.y = y
         self.score = score
         self.screen = screen
         self.colour = colour
         self.pixelsize = pixelsize
         self.charwidth = charwidth
         self.numzeros = numzeros 
         self.solid = solid
         self.draw()
    def draw(self):
        global psize, charwidth
        charwidth = self.charwidth
        psize = self.pixelsize
        pygameShowColourScore2(self.screen,self.x,self.y,self.colour,self.score, self.numzeros, self.solid) 
    def update(self,myscore):
        self.score = myscore
        self.draw()

def checkcollisionrect(object1,object2):
     x1,y1,x2,y2 = object1.collisionrect 
     a1,b1,a2,b2 = object2.collisionrect
     x1 = x1 + object1.x
     y1 = y1 + object1.y
     x2 = x2 + object1.x
     y2 = y2 + object1.y 
     a1 = a1 + object2.x
     b1 = b1 + object2.y
     a2 = a2 + object2.x
     b2 = b2 + object2.y 
     if x2 < a1 or x1 > a2 or y2 < b1 or y1 > b2:
          return False
     else:
          return True
     
def checkcollisionPointsinRect(object1,object2,pixelsize):
    a1,b1,a2,b2 = object2.collisionrect
    a1 = a1 + object2.x
    b1 = b1 + object2.y
    a2 = a2 + object2.x
    b2 = b2 + object2.y
    for p in object1.RotatedCollisionPoints:
        x1 = p[0]*pixelsize + object1.x
        y1 = p[1]*pixelsize + object1.y
        if x1 >= a1 and x1 <= a2 and y1 >= b1 and y1 <= b2:
            return True
    return False

def rotatepoints(points,angle,center):
         newpoints = []
         anglerad = math.radians(angle)
         cx,cy = center
         for x,y,z in points:
              x = x - cx
              y = y - cy
              newx = x* math.cos(anglerad)- y*math.sin(anglerad) + cx
              newy = x * math.sin(anglerad) + y*math.cos(anglerad) + cy
              newpoints.append((newx,newy,z))
         return newpoints

def pygameCreateCharColourSolid(screen,x,y,colourpoints,pixelsize):
  for p in colourpoints:
    pygame.draw.rect(screen, p[2], (x+p[0]*pixelsize,y+p[1]*pixelsize, pixelsize, pixelsize)) # p[2]=colour, (xloc,yloc,width,height)=rect

class pygameLEDobj:
    def __init__(self, screen,x=0,y=0,dx=0,dy=0, CharPoints = [], pixelsize = 2):
         self.alive = True
         self.x = x
         self.y = y
         self.dx = dx
         self.dy = dy
         self.screen = screen
         self.OriginalCharPoints = CharPoints
         self.CharPoints = CharPoints.copy()
         self.collisionrect = (0,0,0,0)  # top left to bottom right
         self.CollisionPoints = [(0,0,0)]
         self.RotatedCollisionPoints = [(0,0,0)]
         self.collisionimage = 0
         self.collisionlinesimage = 0
         self.collisionrectshow = False
         self.collisionlinesshow = False
         self.pixelsize = pixelsize
    def resetposition(self,x,y):
        self.x, self.y = x,y
        self.dx, self.dy = 0,0
        self.draw()
    def draw(self):
        pygameCreateCharColourSolid(self.screen,self.x,self.y,self.CharPoints,self.pixelsize)
    def move(self): 
         self.x = self.x + self.dx
         self.y = self.y + self.dy
    def rotate(self,angledeg):
         centerx = sum(x for x,y,z in self.OriginalCharPoints)/len(self.OriginalCharPoints)
         centery = sum(y for x,y,z in self.OriginalCharPoints)/len(self.OriginalCharPoints)
         self.CharPoints = rotatepoints(self.OriginalCharPoints,angle=angledeg,center=(centerx,centery))
         self.RotatedCollisionPoints = rotatepoints(self.CollisionPoints,angle=angledeg,center=(centerx,centery))
         self.draw()

