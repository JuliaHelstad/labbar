import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException; 
import java.util.*;
import java.util.LinkedList;

public class World{

    public String path;
    private int r = 0;
    //public ArrayList<Room> arrroom = new ArrayList<Room>( femton, sexton);
    private int b = 0;
    // public Book häst;
    // public List<Book> arrbook = Arrays.asList(häst);
    LinkedList<Item> items = new LinkedList<Item>();
    LinkedList<Door> doors = new LinkedList<Door>();
    LinkedList<Room> rooms = new LinkedList<Room>();
    Course course;
    Teacher teacher;
    Student student;
    Sfinx sfinx;
    Room room;

    public World(String path) {
	this.path = path;
    }

    public LinkedList<Room> lineReader(){
	try {
	    //World world = new World("input.txt");
	    FileReader fr = new FileReader(path); 
	    BufferedReader br = new BufferedReader(fr);
	    String str = "";
	    int antalrader = 43;
	    
	    int test = Integer.parseInt("1");
	    for(int i= 0; i<= antalrader; i++){
		str = br.readLine();
		String[] words = str.split(";");	
		if (words[0].equals("sfinx")){
		    if(words[1].equals("null")){
			sfinx = null;}
		  else  sfinx = new Sfinx();
		}
		if (words[0].equals("item")) {
		    if(words[1].equals("null")){
			items.add(null);}
		    if(words[1].equals("Key") ){
			Key key = new Key();
			items.add(key);
		    }
		    else if (words[1].equals("Coffee")) {
			Coffee coffee = new Coffee();
			items.add(coffee);
		    }
		    else {
			Book book = new Book(words[1]);
			items.add(book);
		    }
		}
		if(words[0].equals("course")) {
		    course = new Course(words[1], Integer.parseInt(words[2]), words[3]);
		}
		if (words[0].equals("teacher")){
		    if(words[1].equals("null")){
			teacher = null;}
		    else {
			teacher = new Teacher(words[1],course,words[2],words[3],words[4],words[5], Integer.parseInt(words[6]));
		}
		}
		if (words[0].equals("student")){
		    if(words[1].equals("null")){
			student = null;}
		  else  student = new Student(words[1], course, words[3]);
		}
		if (words[0].equals("door")) {
		    if(words[1].equals("null")) {
			doors.add(null);}
		    else {
			Door door = new Door(words[1],Boolean.parseBoolean(words[2]),words[3]);
		    doors.add(door);
		    r++;
		    }
		}
		if (words[0].equals("room")){
		    room = new Room(words[1], items.get(0), teacher, student, doors.get(0), doors.get(1), doors.get(2), doors.get(3), sfinx);
		    doors.clear();
		    items.clear();
		    rooms.add(room);
		}
	    }    
	} catch (IOException e ) {
	    System.out.println("HEJ");
	
	    /*
	      catch (FileNotFoundException a) {
	      System.out.println("NEJ");
	      }*/
	}
	return rooms;
    }

    public LinkedList<Room> getList() {
	LinkedList list = new LinkedList();
	list = this.lineReader();
	return list;
    }


    public static void main(String [] args) {
	World world = new World("input.txt");
	LinkedList<Room> list = new LinkedList();
	list = world.lineReader();
	System.out.println( list.get(0).getName());
    }




}


 




