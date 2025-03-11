Name: Daniel Tripoli
Major: Computer Science
Course Code: 237 010
Project number: 1
Data submitted: 3/11/25

To compile program:
1. Type: make
To run program:
2. Type: ./application

Question: Which data method do you think was most efficient and why? Is there any alternative that you believe is more efficient?
Also, can you think of some other method that may have been more efficient?

Answer:
Vectors are definitely the most efficient in terms of being able to achieve the main purpose of the program 
without hassle. This is because we do not know how many unique words could possibly
be in the users txt file, so a vector is most fitting as it can adapt to the unique word count.
With the other structures, the static nature of their structures means the code would manually need 
to edited to increase the size of the array if we wanted to list all the words found in the txt file, 
and this could lead to having an unnecessarily large array due to having to guess the size we need
before we run the program. An alternative method that might be more memory efficient but less time efficient would 
be to have a function to find the count of unique words in the txt file so that we can dedicate a very
specifically sized array ahead of time rather than having to constantly resize like we did with vectors.
