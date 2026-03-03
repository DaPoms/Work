

public class Course {
    String courseName;
    private final int MAXCAPACITY = 100;
    private String courseCode;
    private int seatsLeft;
    private int creditHours;
    private String courseAttribute;
    private Faculty instructor;
    private ArrayList<Course> preReqs;
    private ArrayList<studentList> studentList;

    public boolean addStudent(Student s) 
    {
        if(s.hasTakenCourse)
        if(s.hasTakenCourse(this)) return false;
        for(Course c : preReqs)
        {
            if(s.hasTakenCourse())
            {
                s.addCourse
            }
        }
    }
    public boolean dropStudent(Student s)
    {
        seatsLeft++;
        studentList.remove(s);
    }
    
}
