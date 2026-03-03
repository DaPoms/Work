import java.util.ArrayList;

public class Faculty {

    enum Seniority{INSTRUCTOR,ASSOCIATE,ASSISTANT,PROFESSOR,RETIRED};
    private long facultyID;
    ArrayList<Course> courseList;
    private String name;
    private String address;
    private String prefix;
    private boolean hasPHD;
    private Seniority seniority;

    public Faculty()
    {
        this((long) (Math.Random*Long.MAX_VALUE)))
    }
    public Faculty(long id, String name, String address, bool hasPHD, ArrayList<Course> courseList, Seniority seniority)
    {
        facultyID = id;
        this.name = name;
        this.address = address;
        this.hasPHD = hasPHD;
        prefix = hasPHD = true ? "Dr." : "Prof.";
        this.courseList = courseList;
        this.seniority = seniority;
    }
    //getters
    public long getFacultyID() {return facultyID;}
    public String getName() {return name;}
    public Seniority getSeniority() {return seniority;}
    public ArrayList<Course> getCourseList(){ return new ArrayList<Course>(courseList);}
    String getAddress(){return address;}

    //mutators
    public void rankUp()
    {
        if (seniority == Seniority.INSTRUCTOR && hasPHD)) seniority = Seniority.ASSOCIATE;
        else if(seniority == Seniority.ASSOCIATE) seniority = Seniority.ASSISTANT;
        else if (seniority == Seniority.ASSISTANT) seniority = Seniority.PROFESSOR;
    }

        public boolean addCourse(Course c)
    {
        courseList.add(c);
    }
    public boolean dropCourse(Course c)
    {
        courseList.remove(c)
    }

    // facilitators
    public boolean isTenured() {return seniority != Seniority.INSTRUCTOR;}
    public boolean isActive() {return seniority == Seniority.RETIRED;}
}
