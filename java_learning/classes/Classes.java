public class Classes
{
    int y = 5;
    public static void main(String[] args)
    {
        Classes myObj = new Classes();
        System.out.println(myObj.y);

        Mammal fox = new Mammal();
        
        fox.age = 5;
        fox.height = 13;
        fox.name = "Fox";
        fox.describe();
        fox.timePass(731);
        fox.describe();
    }
}
