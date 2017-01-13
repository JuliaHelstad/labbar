import java.util.ArrayList;
import java.lang.Math;
import java.util.Scanner;
import java.util.LinkedList;


public class TestAvatar {
    
    static LinkedList<Room> roomList; 
    static Avatar avatar;
    static Key key;
    static Coffee coffee;
    static Door n;
    static Door e;
    static Door s;
    static Door w;
    static Course course;
    static Student student;
    static Room r;
    static Door nn;
    static Door ee;
    static Door ss;
    static Door ww;
    static Room k;
    static ArrayList<Course> undoneCourses;
    static ArrayList<Course> doneCourses;
    static Teacher teacher;
	
    
    public static void main(String [] args)
    {
	roomList = new LinkedList<Room>();
	avatar = new Avatar(r, roomList);
	key = new Key();
	coffee = new Coffee();
	n = new Door("k", false, "north");
	e = new Door(null, null, null);
	s = new Door(null, null, null);
        w = new Door(null, null, null);
	course = new Course("hej",3,"hej");
	student = new Student("jahaja", course, "jahaja");
	teacher = new Teacher("Maja", course, "hejhej", "1", "2", "3", 1);
	r = new Room("r", key, null, student, n, e, s, w, null);
	avatar.addToRoomList(r);
	nn = new Door(null, null, null);
	ee = new Door(null, null, null);
	ss = new Door("r", true, "south");
	ww = new Door(null, null, null);
	k = new Room("k", coffee, teacher, null, nn, ee, ss, ww, null);
	avatar.addToRoomList(k);
	undoneCourses = new ArrayList<Course>();
	doneCourses = new ArrayList<Course>();
	undoneCourses.add(course);
    }
       
    public void testUseKey()
    {
	avatar.pickUp(key);
	assert(avatar.space == 1);
	avatar.useKey(n);
	assert(avatar.space == 0);
    }

    public void testReadyToGraduate()
    {
	assert(avatar.readyToGraduate() == false);
    }

    public void testGo_GetCurrentRoom()
    {
	avatar.go("k");
	assert(avatar.getCurrentRoom() == k);
    }

    public void testInventoryContainsKey()
    {
	avatar.pickUp(key);
	assert(avatar.space == 1);
	assert(avatar.inventoryContainsKey() == true);
    }

    public void testFindCourse_CourseIsDone()
    {	
	assert(avatar.findCourse(course) == false);
	avatar.courseIsDone(course);
	assert(avatar.findCourse(course) == true);	
    }

    public void testPickUp_Drop()
    {
	avatar.pickUp(key);
        assert(avatar.space == 1);
	avatar.drop("key");
	assert(avatar.space == 0);
    }

    public void testTalk()
    {
	assert(avatar.talk(student) == "hej");	
    }

    public void testExamMe()
    {
	avatar.go("k");
	avatar.examMe(teacher);
	assert(avatar.findCourse(course) == true);
    }

    public void testDrinkUp()
    {
	avatar.go("k");
	avatar.pickUp(coffee);
	assert(avatar.space == 1);
	avatar.drinkUp();
	assert(avatar.space == 0);	
    }
}


