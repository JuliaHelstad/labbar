import java.lang.Boolean;
import java.util.ArrayList;

public class Room {

    //  public ArrayList<Room> roomList = new ArrayList<Room>();

    private String name;
    private Item item;
    private Teacher teacher;
    private Student student;
    public Door doorN;
    public Door doorE;
    public Door doorS;
    public Door doorW;
    private Sfinx sfinx;

    public Room(String name, Item item, Teacher teacher, Student student,  Door doorN, Door doorE, Door doorS, Door doorW, Sfinx sfinx){
	this.name = name;
	this.item = item;
	this.teacher = teacher;
	this.student = student;
	this.doorN = doorN;
	this.doorE = doorE;
	this.doorS = doorS;
	this.doorW = doorW;
	this.sfinx = sfinx;
	
    }

    public Sfinx getSfinx() {
	return this.sfinx;
    }

    public String getName() {
	return this.name;
    }

    public String roomItem(){
	return this.item.toStringItem();
    }

    public void removeItem(){
	item = null;
    }

    public Item getItem(){
	return this.item;
    }

    public Student getStudent() {
	return this.student;
    }
    
    public Teacher getTeacher(){
	return this.teacher;
    }

    public String roomInfo(){	
	String str = "The current room, " + getName() + " have: " + "\n";
	if (this.item != null){
		str += "The item: " + this.item.toStringItem()+ "\n";
	    }
	if(this.teacher != null){
		str += "The teacher: " + this.teacher.toString() +"\n";
	    }
	if(this.student != null) {
	    str += "The student: " + this.student.toString() + "\n";
	}
	if(this.item == null && this.teacher == null){
		str+= "NOTHING";
	    }
	return str;
    }


    public String roomToString(){
	String str = "";
	System.out.println("You are now in room: " + this.name + "\n");
	str+= "North: " + doorToString(this.doorN) + "\n";
	str+= "East: " + doorToString(this.doorE) + "\n";
	str+= "South: " + doorToString(this.doorS) +  "\n";
	str+= "West: " + doorToString(this.doorW) +  "\n";
	str+= roomInfo();
	return str;
    }


    public String doorToString(Door door){
	if (door==null){
	    return "X";
	    }
	else return door.getName() +" (" + door.isOpen() + ")";
    }

   
}

