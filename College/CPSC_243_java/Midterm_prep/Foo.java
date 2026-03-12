import java.util.Arrays;

class Foo
{
    public static void alterPassByVal(int[] lst)
    {
        lst = new int[]{1,2,3}; // should do nothing to the lst that was passed, as passing by value means that the parameter in the call is not changed
    }


    public static void main(String[] args) 
    {
        int[] myArr = {5,5,5,5};
        alterPassByVal(myArr);
        System.out.print(Arrays.toString(myArr));
        
    }
}
