#! /usr/bin/python -i
from Tkinter import *
from tkFont import *
import demo;

class Application(Frame):
    def __init__(self, master=None):
        Frame.__init__(self, master)
        self.pack()
        self.font = Font(family="helvetica", weight=BOLD, size=14)
        for d in dir(demo):
            if eval('demo.'+d).__class__.__name__ == 'function':
                btn = Button(self)
                btn["text"] = d
                btn["command"] =  eval('demo.'+d)
                btn.config(width=16, height=1, font=self.font)
                btn.pack()

        btn = Button(self)
        btn["text"] = "QUIT"
        btn["command"] = self.quit
        btn["fg"]   = "red"
        btn.config(width=16, height=2, font=self.font)
        btn.pack()

root = Tk()
root.title("HIRO Control Panel")
#root.wm_attributes("-topmost", 1)
app = Application()
app.mainloop()
root.destroy()
