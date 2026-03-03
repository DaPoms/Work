import java.util.ArrayList;


public enum Student {
    enum Seniority {FRESHMAN,SOPHOMORE,JUNIOR,SENIOR,ALUMNI};
    long studentID;
    String major;
    String name;
    String address;
    Seniority seniority;
    ArrayList<Course> courseList;
    int credits;
    float GPA;


    // Inspectors
    public long getStudentID() {return studentID;}
    public String getMajor() {return major;}
    public String getname() {return name;}
    public Seniority getSeniority() {return seniority;}
    public ArrayList<Course> getCourseList(){ return new ArrayList<Course>(courseList);}
    public int getCredits() {return credits;}
    public float getGPA() {return GPA;}
    String getAddress(){return address;}

    //constructor
    public student()
    {
        this(Math.Random * Long.MAX_VALUE, "Joe Student", "undeclared", );
    }
    public Student(long id, String name, String major, String address, Seniority sen, int credits, float gpa, ArrayList<Course> courseList)
    {
        studentID = id;
        this.name = name;
        this.major = major;
        this.address = address;
        seniority = sen;
        this.GPA = gpa;
        

        
        
    }

    // mutators

    public boolean addCourse(Course c)
    {
        courseList.add(c);
    }
    public boolean dropCourse(Course c)
    {
        courseList.remove(c)
    }

    public void completeCourse()
    {
        credits += c.getCredits(); 
    }

    public void seniorityUP()
    {
        if(seniority == Seniority.FRESHMAN && credits >= 30) seniority = Seniority.SOPHOMORE;
        else if(seniority == Seniority.SOPHOMORE && credits >= 60) seniority = Seniority.JUNIOR;
        else if(seniority == Seniority.JUNIOR && credits >= 90) seniority = Seniority.SENIOR;
        else if(seniority == Seniority.FRESHMAN && credits >= 120) seniority = Seniority.ALUMNI;
    }

    public boolean canGraduate()
    {
        return credits >= 120;
    }

    public boolean hasGraduated()
    {
        return seniority == Seniority.ALUMNI;
    }
}
