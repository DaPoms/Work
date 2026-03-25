public class Test {
    public static Integer modify(int a, Integer b) {

    a += 5;

    return (b += 5); // b = new Integer( b.intValue() + 5);

    }//end main
    public static void main(String[] args) {

    int x = 10;

    Integer y = 10;

    y = modify(x, y);

    System.out.println(x + " " + y);

    }//end main
    
}
