------------------------------------------------------------------------
      Name:             Daniel Tripoli
      Last Edited:      9/12/2024
      Due Date:         9/14/2024
      Course:           CPSC136 - Computer Science II
      Professor Name:   Professor Jacklitsch
      Assignment:       Project 1
      Filename:         readme.txt
      Purpose:          To answer questions regarding my project1.cpp
                        implementation
------------------------------------------------------------------------
1. Which sorting algorithm did you use and why?
A.1: I used a Insertion sort because it made the most sense to me to move back the newly inserted struct in the array till it is greater than the value to the left of it,
which is what Insertion sort does. The Insertion sort allowed me to check on the arrays up to the current amount of structs in the array for efficiency, and is more
efficient if there are higher distance values near the end of the user's file, as the while statement in the Insertion sort will have to run far less 

2. What would you have to do differently if the speed provided by the file was in ft/s?
A.2: I would have to change the terminal output for velocity and distance to ft/s. Value wise, gravity would have to be converted to 32.17 ft/s (ish)

3. Which lines in your code would you have to change in order to sort alphabetically by
name instead? What would those changes be?
A.3: My Insertion sort function, particularly on line 214 would have to change to instead check the names of type string in each swing struct, 
     which would be done by changing the arr member references in the while statement to arr[traverse].name and arr[traverse - 1].name 

4. What is the earliest line your program could crash on if the file provided could be
opened normally but was formatted incorrectly?
A.4: Line 193, as it is the first time a value is extracted for a variable other than a string (strings can take most values so it wouldn't crash).
Line 193 extracts a value from the file and makes it of type float, so if a string/char is inserted it will throw an error / crash. 

5. What is the effect of launch speed on distance? What about launch angle?
5.A:  Angles: The steeper the angle (which means from 0-180 the closer the angle is to 90 degrees), the less distance (horizontally) the projectile goes. 
             The closer to 0 or 180 degrees (not inclusive), the farther distance the projectile will go.
Launch Speed: For an increase/decrease in velocity it impacts the distance by the ratio of the new velocity divided by the old, to the power of 2 --> ((new / old) ^ 2).
