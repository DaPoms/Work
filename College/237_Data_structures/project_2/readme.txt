Name: Daniel Tripoli
Major: Computer Science
Course Code: 237 010
Project number: 2
Data submitted: 4/14/25

To compile:
1. make
2. ./stocktracker

I used vectors as a way to store both the StockHist and Stock objects I created. 
I did this because the size of the text file the user provides varies in size, so 
a dynamic data structure such as a vector allows us to store all the data no matter what. 
Also, because the given text file is also already sorted (by date), we can just use the push_back() 
function to efficiently store our objects. Here's a closer breakdown: The StockHist class was used used to 
store a single transaction, so I used the vector to create a list of the transactions. This vector was 
important for all the tables of the project (Portfolio, Transactions, advisory table). 
The Stock class on the other hand stores an individual stock (and its associated data), and was
used to hold the elements of the portfolio table. This vector was made by analyzing the elements of the StockHist vector. 
Since we don't know how many stocks there are in the text file at the start I also used a vector. I could've used the StockHist vector 
to count how many unique stocks there are and instead store with an array, but I decided not to as it would be complicating
a process (by having to create another function) that is not an issue for a vector.


    