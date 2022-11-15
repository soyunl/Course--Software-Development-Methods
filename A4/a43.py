#!/usr/bin/env python3
"""
>>> my_ellipse = Ellipse((500,500,200,100),(250,100,50,1.0))
>>> print(type(my_ellipse))
<class 'a43.Ellipse'>
>>> print(type(my_ellipse.op))
<class 'float'>
>>> myfile:ProEpilogue = ProEpilogue("filename","title")
>>> print(type(myfile.fnam))
<class 'str'>
"""

from typing import IO, List
import random


class Circle:
    """Circle class"""
    def __init__(self, cir: tuple, col: tuple) -> None:
        self.cx: int = cir[0]
        self.cy: int = cir[1]
        self.rad: int = cir[2]
        self.red: int = col[0]
        self.green: int = col[1]
        self.blue: int = col[2]
        self.op: float = col[3]

    def drawCircleLine(self, f: IO[str], t: int) -> None:
        """drawCircle method"""
        ts: str = "   " * t
        line1: str = f'<circle cx="{self.cx}" cy="{self.cy}" r="{self.rad}" '
        line2: str = f'fill="rgb({self.red}, {self.green}, {self.blue})" fill-opacity="{self.op}"></circle>'
        f.write(f"{ts}{line1+line2}\n")

class Rectangle:
    """Rectangle class"""
    def __init__(self, rec: tuple, col: tuple) -> None:
        self.x: int = rec[0]
        self.y: int = rec[1]
        self.width: int = rec[2]
        self.height: int = rec[3]
        self.red: int = col[0]
        self.green: int = col[1]
        self.blue: int = col[2]
        self.op: float = col[3]

    def drawRectangleLine(self, f: IO[str], t: int) -> None:
        """drawRectangle method"""
        ts: str = "   " * t
        line1: str = f'<rect x="{self.x}" y="{self.y}" width="{self.width}" height="{self.height}" '
        line2: str = f'fill="rgb({self.red}, {self.green}, {self.blue})" fill-opacity="{self.op}"></rect>'
        f.write(f"{ts}{line1+line2}\n")

class Ellipse:
    """Ellipse class"""
    def __init__(self, ell: tuple, col: tuple) -> None:
        self.cx: int = ell[0]
        self.cy: int = ell[1]
        self.rx: int = ell[2]
        self.ry: int = ell[3]
        self.red: int = col[0]
        self.green: int = col[1]
        self.blue: int = col[2]
        self.op: float = col[3]

    def drawEllipseLine(self, f: IO[str], t: int) -> None:
        """drawEllipse method"""
        ts: str = "   " * t
        line1: str = f'<ellipse cx="{self.cx}" cy="{self.cy}" rx="{self.rx} ry="{self.ry}" '
        line2: str = f'fill="rgb({self.red}, {self.green}, {self.blue})" fill-opacity="{self.op}"></ellipse>'
        f.write(f"{ts}{line1+line2}\n")

class ProEpilogue:
    """ProEpilogue class"""
    def __init__(self, fnam: str, winTitle: str) -> None:
        self.fnam: str = fnam
        self.winTitle: str = winTitle
        self.f: IO[str] = open(fnam, "w")

    def writeHTMLcomment(self, t: int, com: str) -> None:
        """writeHTMLcomment method"""
        ts: str = "   " * t
        self.f.write(f"{ts}<!--{com}-->\n")

    def writeHTMLline(self, t: int, line: str) -> None:
        """writeLineHTML method"""
        ts: str = "   " * t
        self.f.write(f"{ts}{line}\n")

    def writeHTMLHeader(self, winTitle: str) -> None:
        """writeHeadHTML method"""
        self.writeHTMLline(0, "<html>")
        self.writeHTMLline(0, "<head>")
        self.writeHTMLline(1, f"<title>{winTitle}</title>")
        self.writeHTMLline(0, "</head>")
        self.writeHTMLline(0, "<body>")

    def openSVGcanvas(self, t: int, canvas: tuple) -> None:
        """openSVGcanvas method"""
        ts: str = "   " * t
        self.writeHTMLcomment(t, "Define SVG drawing box")
        self.f.write(f'{ts}<svg width="{canvas[0]}" height="{canvas[1]}">\n')

    def closeSVGcanvas(self, t: int) -> None:
        """closeSVGcanvas method"""
        ts: str = "   " * t
        self.f.write(f"{ts}</svg>\n")
        self.f.write(f"</body>\n")
        self.f.write(f"</html>\n")


    def genArt(self, x:int,y:int,shape:int) -> None:
        """genART method"""
        shape_list:list = GenRandom(x,y,shape).gen_table()
        for list in shape_list:
            if (list[0]==0):
                Circle((list[1],list[2],list[3]),(list[8],list[9],list[10],list[11])).drawCircleLine(self.f,1)
            elif (list[0]==1):
                Rectangle((list[1],list[2],list[6],list[7]),(list[8],list[9],list[10],list[11])).drawRectangleLine(self.f,1)
            else:
                Ellipse((list[1],list[2],list[4],list[5]),(list[8],list[9],list[10],list[11])).drawEllipseLine(self.f,1)


    def close(self) -> None:
        """closes file"""
        self.f.close()
        

class GenRandom:
    """GenRandom class"""
    def __init__(self, canvasX,canvasY,numRows:int) -> None:
        self.canvasX = canvasX
        self.canvasY = canvasY
        self.numRows:int = numRows


    def gen_table(self) -> list:
        shape_list:list = []

        for item in range(self.numRows):
            SHA:int = random.randrange(0,2+1)
            X:int = random.randrange(0,self.canvasX+1)
            Y:int = random.randrange(0,self.canvasY+1)
            RAD:int = random.randrange(0,100+1)
            RX:int = random.randrange(10,30+1)
            RY:int = random.randrange(10,30+1)
            W:int = random.randrange(10,100+1)
            H:int = random.randrange(10,100+1)
            R:int = random.randrange(0,255+1)
            G:int = random.randrange(0,255+1)
            B:int = random.randrange(0,255+1)
            OP:float = round(random.random(),1)
            shape_list.append([SHA,X,Y,RAD,RX,RY,W,H,R,G,B,OP])

        return shape_list
        

class ArtConfig:
    """ArtConfig class"""
    def __init__(self, canvasX:int, canvasY:int, shape:int) -> None:
        self.canvasX:int = canvasX
        self.canvasY:int = canvasY
        self.shape:int = shape


def writeHTMLfile(config:ArtConfig) -> None:
    """writeHTMLfile method"""
    fnam: str = "a43.html"
    winTitle = "SENG 265 Final Assignment"
    myfile:ProEpilogue = ProEpilogue(fnam,winTitle)
    myfile.writeHTMLHeader(winTitle)
    myfile.openSVGcanvas(1,(config.canvasX,config.canvasY))
    myfile.genArt(config.canvasX,config.canvasY,config.shape)
    myfile.closeSVGcanvas(1)
    myfile.close()

def main() -> None:
    """main method, testing 1500 shapes on 600x400 canvas"""
    writeHTMLfile(ArtConfig(600,400,3000))

if __name__ == "__main__":
    main()