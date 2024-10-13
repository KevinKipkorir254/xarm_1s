import tkinter as tk
from tkinter import ttk
import math

class VirtualGamepad:
    def __init__(self, master):
        self.master = master
        master.title("Virtual Gamepad")
        
        self.left_stick = [0, 0]
        self.right_stick = [0, 0]
        self.buttons = {'A': False, 'B': False, 'X': False, 'Y': False}
        
        self.create_widgets()
        
    def create_widgets(self):
        # Left Stick
        self.left_canvas = tk.Canvas(self.master, width=100, height=100, bg='lightgray')
        self.left_canvas.grid(row=0, column=0, padx=10, pady=10)
        self.left_stick_visual = self.left_canvas.create_oval(45, 45, 55, 55, fill='red')
        self.left_canvas.bind('<B1-Motion>', self.move_left_stick)
        self.left_canvas.bind('<ButtonRelease-1>', self.reset_left_stick)
        
        # Right Stick
        self.right_canvas = tk.Canvas(self.master, width=100, height=100, bg='lightgray')
        self.right_canvas.grid(row=0, column=1, padx=10, pady=10)
        self.right_stick_visual = self.right_canvas.create_oval(45, 45, 55, 55, fill='red')
        self.right_canvas.bind('<B1-Motion>', self.move_right_stick)
        self.right_canvas.bind('<ButtonRelease-1>', self.reset_right_stick)
        
        # Buttons
        button_frame = ttk.Frame(self.master)
        button_frame.grid(row=1, column=0, columnspan=2, pady=10)
        for btn in self.buttons:
            ttk.Button(button_frame, text=btn, command=lambda b=btn: self.toggle_button(b)).pack(side=tk.LEFT, padx=5)
        
        # Status
        self.status_text = tk.Text(self.master, height=6, width=40)
        self.status_text.grid(row=2, column=0, columnspan=2, padx=10, pady=10)
        self.update_status()
        
    def move_left_stick(self, event):
        self.move_stick(event, self.left_canvas, self.left_stick_visual, 'left')
        
    def move_right_stick(self, event):
        self.move_stick(event, self.right_canvas, self.right_stick_visual, 'right')
        
    def move_stick(self, event, canvas, stick_visual, stick_name):
        canvas_width = canvas.winfo_width()
        canvas_height = canvas.winfo_height()
        x = event.x - canvas_width / 2
        y = event.y - canvas_height / 2
        distance = math.sqrt(x*x + y*y)
        max_distance = min(canvas_width, canvas_height) / 2 - 5
        if distance > max_distance:
            x = x * max_distance / distance
            y = y * max_distance / distance
        canvas.coords(stick_visual, x+47, y+47, x+53, y+53)
        if stick_name == 'left':
            self.left_stick = [round(x / max_distance, 2), round(-y / max_distance, 2)]
        else:
            self.right_stick = [round(x / max_distance, 2), round(-y / max_distance, 2)]
        self.update_status()
        
    def reset_left_stick(self, event):
        self.reset_stick(self.left_canvas, self.left_stick_visual, 'left')
        
    def reset_right_stick(self, event):
        self.reset_stick(self.right_canvas, self.right_stick_visual, 'right')
        
    def reset_stick(self, canvas, stick_visual, stick_name):
        canvas.coords(stick_visual, 45, 45, 55, 55)
        if stick_name == 'left':
            self.left_stick = [0, 0]
        else:
            self.right_stick = [0, 0]
        self.update_status()
        
    def toggle_button(self, button):
        self.buttons[button] = not self.buttons[button]
        self.update_status()
        
    def update_status(self):
        status = f"Left Stick: {self.left_stick}\n"
        status += f"Right Stick: {self.right_stick}\n"
        status += "Buttons:\n"
        for btn, state in self.buttons.items():
            status += f"  {btn}: {'Pressed' if state else 'Released'}\n"
        self.status_text.delete('1.0', tk.END)
        self.status_text.insert(tk.END, status)

root = tk.Tk()
virtual_gamepad = VirtualGamepad(root)
root.mainloop()