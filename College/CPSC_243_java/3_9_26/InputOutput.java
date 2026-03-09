import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.ArrayList;

public class InputOutput
{
    public static void main(String[] args) 
    {
        //BufferedReader + BufferedWriter - the most efficient
        //FileReader, fileWriter - more efficient for reading / writing to a file
        //Scanner PrintWriter - simplified file I/O
        Scanner cin = new Scanner(System.in);
        Scanner fileScan = null;
        PrintWriter fileOut = null;
        File inFile,outFile;
        ArrayList<Integer> intList = new ArrayList<>();
        boolean isValid = false;

        //Creates filenames and the associated files
        do
        {
            System.out.println("Please enter a file name for input: ");
            String filename = cin.nextLine();
            

            inFile = new File(filename);

            System.out.println("Please enter a file name for output: ");
            filename = cin.nextLine();

            outFile = new File(filename);


            //lins files to readers and writers
            try
            {
                fileScan = new Scanner(inFile); //Note that the file pathing does not need to be included ONLY if the current working directory is set to the same as the one this file is in
                fileOut = new PrintWriter(outFile);
                isValid = true;
            } catch(FileNotFoundException e)
            {
                System.out.println(e.getMessage());
                isValid = false;
            }
        } while (!isValid);


        //read from file
        while(fileScan.hasNextInt())
            intList.add(fileScan.nextInt());
        
        //close fileScan
        fileScan.close();

        for(int i = 0; i < intList.size(); i++)
            intList.set(i,intList.get(i) * 2);
        
        for(Integer i : intList)
            fileOut.println(i); 


        fileOut.close();




    }
}
