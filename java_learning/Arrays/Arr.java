public class Arr
{
    public static void main(String[] args)
    {
        int[] nums = {1,2,3,4}; //I've learned that java enforces heap-based-arrays unlike c++
        // int[] nums = new int[]{1,2,3,4};// thats why this is also equivalent to the above
        for(int num : nums)
            System.out.println(num);

        System.out.println("The size is " + nums.length); // notice .length used for length, but in C++, arrays don't have a way to directly call for length other than by doing .sizeOf manipulation of the size of the array divided by the size of the data type

        int[] coolNums = new int[4]; // note the use of the new keyword means this will be stored on the heap (just like c++). Creates empty array

        for(int i = 0; i < coolNums.length; i++)
        {
            coolNums[i] = i * 2;
            System.out.println(coolNums[i]);
        }
        
        int[][] intMatrix = {
        {1,1,1}, 
        {1,2,1},
        {1,1,3,4} // notice how this works with an uneven matrix
        };
        for(int r = 0; r < intMatrix.length; r++) 
        {
            for(int c = 0; c < intMatrix[r].length; c++) // because of the possibility of uneven matrices, using r for the .length is important to make sure we account for all differences
            {
                System.out.print(intMatrix[r][c] + " ");
            }            System.out.println();
        }
    }
}
