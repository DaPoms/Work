import java.util.ArrayList;
class ArrayListTest
{
    enum Days {MONDAY,TUESDAY,WEDNESDAY,THURSDAY,FRIDAY,SATURDAY,SUNDAY}
    public static void main(String[] args)
    {
        ArrayList<Integer> myVect = new ArrayList<>();
        myVect.add(5);
        myVect.add(7);
        myVect.add(12);
        System.out.println(myVect.get(1));
        myVect.remove(0);

        for(int i = 0; i < myVect.size(); i++)
                System.out.println(myVect.get(i));

        Days today = Days.FRIDAY;
        Days yesterday = Days.THURSDAY;
        System.out.println(today.ordinal() > yesterday.ordinal());
        for ( Days d : Days.values() )
        {
            System.out.println(d);
        } 
    }   
}
