import java.util.Scanner;
import java.util.Arrays; // array related class
public class Arrayops
{
      public static void popArray(int[] a, Scanner cin)
        {
            for(int i = 0; i < a.length; i++)
            {
                System.out.println("Enter value for index " + i + ": ");
                a[i] = cin.nextInt();
            }
        }

        public static void printArray(int[] a)
        {
            for(int i : a)
                System.out.println(i);
        }

        public static int calcSumArray(int[] a)
        {
            int sum = 0;
            for(int val : a)
                sum += val;
            return sum;            
        }

        public static int findMaxArray(int[] a)
        {
            int maxI = 0;
            for(int i = 1; i < a.length; i++)
                if(a[i] > a[maxI]) maxI = i;
            return a[maxI];
        }

        public static void shuffle(int[] a)
        {
            for(int i = 0; i < a.length; i++)
            {
                int rnd = (int)(Math.random() * a.length);
                int temp = a[i];
                a[i] = a[rnd];
                a[rnd] = temp;
            }
        }

        public static int[] deepCopyArr(int[] a)
        {
            int[] copyOfArr = new int[a.length];
            for(int i = 0; i < a.length; i++)
                copyOfArr[i] = a[i];

            return copyOfArr;
        }

    public static void main(String args[])
    {
        Scanner cin = new Scanner(System.in);
        int[] arr = new int[5];
       /*  arr[0] = 12; 1
 */
        popArray(arr, cin);
        System.out.println("Array elements:");
        printArray(arr);
        System.out.println("Highest valued element in array: " + findMaxArray(arr));
        System.out.println("Sum of array values: " + calcSumArray(arr));
        shuffle(arr);
        System.out.println("Shuffled array elements:");

        printArray(arr);
        
      int[] arr2 = arr; // Shallow copy: Points arr2 to the same location of the heap as arr (if we were to change arr2, arr would also be affected)
      // shown below
      arr2[0] = -1;
      System.out.println("Oh no this is a shallow copy!");
      printArray(arr);
      printArray(arr2);

      int[] arr3 = deepCopyArr(arr2);
      arr3[0] = 1000000;
      System.out.println("Heres the fix! 'deep copy':");
      printArray(arr3);
      printArray(arr2); // equivalent is System.arrayCopy(arr1, starting point, arr2, starting point, array length (how much we want to read))

      // equivalent
      
    }
}
