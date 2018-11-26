import os
from tkinter import *
from tkinter import messagebox
import matplotlib.pyplot as plt


root = Tk()
root.title('Scheduling Algorithms GUI')


# Add a grid
mainframe = Frame(root)
mainframe.grid(column=0, row=0, sticky=(N, W, E, S))
mainframe.columnconfigure(0, weight=1)
mainframe.rowconfigure(0, weight=1)
mainframe.pack(pady=100, padx=100)

Label(mainframe, text="Input File Path: ").grid(row=1, column=1)
filenameVar = StringVar()
en = Entry(mainframe, textvariable=filenameVar, bd=3)
en.grid(row=1, column=2)
en.focus_set()


# Create a Tkinter variable
algoVar = StringVar(root)

# Dictionary with options
choices = {'FCFS', 'HPF', 'RR', 'SRTN'}
algoVar.set('FCFS')  # set the default option

popupMenu = OptionMenu(mainframe, algoVar, *choices)
Label(mainframe, text="Choose an Algo").grid(row=2, column=1)
popupMenu.grid(row=2, column=2)


Label(mainframe, text="Context Switch  Time: ").grid(row=3, column=1)
contextVar = StringVar()
Entry(mainframe, textvariable=contextVar, bd=3).grid(row=3, column=2)

Label(mainframe, text="Time Quantum: ").grid(row=4, column=1)
quantumVar = StringVar()
Entry(mainframe, textvariable=quantumVar, bd=3).grid(row=4, column=2)

algos = {'HPF': '0', 'FCFS': '1', 'RR': '2', 'SRTN': '3'}


def callback():
    if algoVar.get() == 'RR' and quantumVar.get() == '':
        messagebox.showerror(
            "Error", "You forgot to enter quantum time while choosing RR")
        return
    cmnd = './scheduler '
    cmnd = cmnd + filenameVar.get() + ' '
    cmnd = cmnd + filenameVar.get() + '_output '
    cmnd = cmnd + algos[algoVar.get()] + ' '
    cmnd = cmnd + contextVar.get() + ' '
    cmnd = cmnd + quantumVar.get()
    print(cmnd)
    os.system(cmnd)
    print('-------------------------------------------------------------------------')


Button(mainframe, text="Run Algorithm", command=callback).grid(row=5, column=2)



root.mainloop()
