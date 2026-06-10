  Mini Graphics Engine (Console-Based)
====================================

📖 What is this?
----------------
This is a simple graphics engine written in C that lets you draw basic shapes 
(lines, rectangles, circles, triangles) inside a text-based canvas.  
Instead of using a GUI, the program prints shapes using '*' characters inside 
a fixed grid (60 columns × 20 rows). It’s like a mini drawing board inside 
your terminal.

You can:
- Add shapes interactively
- Undo your last action
- Reset the canvas (clear everything)
- Display the current drawing at any time

▶️ How to Run
-------------
1. Save the code into a file called graphic.c.
2. Compile it using:
   gcc graphic.c -o graphic
3. Run the program:
   ./graphic

🖊️ Menu Options
----------------
When you run the program, you’ll see:

===== MINI GRAPHICS ENGINE =====
1.Add Shape
2.Undo
3.Display
4.Reset
5.Exit
Choice:

Here’s what each option does:
- 1. Add Shape → lets you draw a new shape
- 2. Undo → removes the last shape you added
- 3. Display → shows the current canvas
- 4. Reset → clears all shapes and history
- 5. Exit → quits the program

🎨 How to Add Shapes
--------------------
When you choose Add Shape, you’ll be asked which shape you want:

1.Line
2.Rectangle
3.Circle
4.Triangle
Choice:

Here’s how to give inputs for each shape in plain English:

1. Line
-------
Prompt: Enter Start(x1 y1) and End(x2 y2)
- (x1, y1) = starting point
- (x2, y2) = ending point
Example: 5 5 20 10 → draws a line from (5,5) to (20,10)

2. Rectangle
------------
Prompt: Enter Center(x y) Width Height
- (x, y) = center point
- Width = how wide
- Height = how tall
Example: 30 10 20 6 → rectangle centered at (30,10), 20 units wide, 6 units tall

3. Circle
---------
Prompt: Enter Center(x y) Radius
- (x, y) = center point
- Radius = distance from center to edge
Example: 25 10 5 → circle centered at (25,10) with radius 5

4. Triangle
-----------
Prompt: Enter 3 Points (x1 y1 x2 y2 x3 y3)
- You must give coordinates of all three corners
Example: 10 5 20 5 15 15 → triangle with corners at (10,5), (20,5), (15,15)

🖼️ Canvas Output
----------------
The canvas is displayed inside a box. Example:

+------------------------------------------------------------+
|                                                            |
|        *****                                               |
|       *     *                                              |
|       *     *                                              |
|        *****                                               |
|                                                            |
+------------------------------------------------------------+

Shapes are drawn using green '*' characters.

🔄 Reset and Undo
-----------------
- Undo → removes the last shape you added
- Reset → clears everything (all shapes, history, and canvas)

✅ Tips
-------
- Coordinates (x, y) start at the top-left corner of the canvas:
  - x → horizontal (0 to 59)
  - y → vertical (0 to 19)
- If you enter values outside the canvas size, the shape may not appear correctly.
- Try small shapes first to get a feel for the coordinate system.

🚀 Why is this cool?
--------------------
This project shows how you can build a mini graphics engine using only text 
and algorithms like Bresenham’s line drawing. It’s a fun way to learn:
- How shapes are represented in code
- How to render graphics in a text console
- How to implement undo/reset functionality
