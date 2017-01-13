import java.util.ArrayList;
import java.lang.Math;
import java.util.Scanner;
import java.util.LinkedList;

public class Avatar {



    private String name;
    private int hp;
    public ArrayList<Course> undoneCourses;
    public ArrayList<Course> doneCourses;
    public ArrayList<Item> inventory;
    public int space;
    private int energy =100 ;
    private Scanner scan;
    private Room currentRoom;

    public LinkedList<Room> roomList;


    public  Avatar(Room currentRoom, LinkedList<Room> list) {
	System.out.println("Enter name: ");
	Scanner scan = new Scanner(System.in);
	this.name = scan.nextLine();
	this.hp = 60;
	this.undoneCourses = new ArrayList<Course>();
	this.doneCourses = new ArrayList<Course>();
	this.inventory = new ArrayList<Item>();
	this.space = 0;
	this.currentRoom = currentRoom;
	this.roomList = list;
    }

    /**
     *@return the name of the avatar.
     */
    public String getName() {
	return this.name;
    }

    /**
     *@return the room the avatar is in right now.
     */
    public Room getCurrentRoom(){
	return this.currentRoom;
    }

    /**
     *@return the current HP.
     */
    public int getHP() {
	return this.hp;
    }

    /**
     *@return the energy the avatar has.
     */
    public int getEnergy() {
	return this.energy;
    }

    /**
     *@return all the rooms.
     */
    public String roomListToString() {
	String a = "";
	for ( int i = 0; i < roomList.size(); i++) {
	    a = a + roomList.get(i).getName();
	}
	return a;
    }

    /**
     *@param room is the room to be added to the roomlist.
     */
    public void addToRoomList(Room room){
	this.roomList.add(room);
    }

    /**
     *@param room is the name of the room you want to find.
     *@return the found room.
     */
    public Room findRoom(String room){
	for(int i = 0; i < this.roomList.size(); i++){
		if(roomList.get(i).getName().equals(room)){
		return  roomList.get(i);
		}
	} 
	return null;
    }

     /**
     *@param door is the door you want to use the key to.
     */
    public void useKey(Door door) {	
	door.openDoor();
	drop("Key");
    }

     /**
     *@return true if the avatar has enough HP. False otherwise.
     */
    public Boolean readyToGraduate(){
	if(hp >= 180 && this.undoneCourses.size() == 0){
	    return true;
	}
	else return false;
    }

     /**
     *@param door is the name of the room you want to go to.
     */
    public void go(String door){

	this.currentRoom = findRoom(door);
    
       	System.out.println(this.currentRoom.roomToString());
	}

     /**
     *@param list is the list of courses you want to print.
     *@return the string of the courses.
     */
    public String toString(ArrayList<Course> list){
	String tmp = "";
	for ( int i= 0; i<list.size() ; i++)  {
	    tmp = tmp +  "Coursename: " + list.get(i).getName() + " HP: " + list.get(i).getHP() + " Coursebook: " + list.get(i).getBook() + "\n";
	}
	return tmp;
    }

     /**
     *@return if the inventory has a key it return true. Otherwise false.
     */
    public Boolean inventoryContainsKey() {
	for(int i =0; i<inventory.size(); i++){
	    if(inventory.get(i).getName() == "Key") {
		return true;
	    }
	}
	     return false;
	
    }
	
    /**
     *@return a string that shows the inventory.
     */
    public String inventoryToString(){
	int keys = 0;
	String str = "" + "Bag content: " + "\n" + "Occupied space: " + space + "/10" + "\n";
	for(int i =0; i<inventory.size(); i++){
	    if(inventory.get(i).getName() == "Key") {
		keys ++;
	    }
	    if (inventory.get(i).getName() != "Key" && inventory.get(i).getName() != "Coffee") {
		str = str + "Coursebook: " + inventory.get(i).getName() + " Size:"+ inventory.get(i).getSize() + "\n";
	    }
	    if (inventory.get(i).getName() == "Coffee") {
		str =  str + "Coffee: " + inventory.get(i).getName() + " Size:"+ inventory.get(i).getSize() + "\n";
	}
	}
	return str + "Number of keys " + keys ;
    }

     /**
     *@return a string that shows the status of the avatar.
     */
    public String status() {
	String str = "";
	str = "Energy: " + getEnergy() + "%" + "\n";
	str = str + "Occupied space: " + space + "/10" + "\n";
	str = str + "HP:" + getHP() + "/180" + "\n";
	if ( energy < 40){
	    str = str + "Maybe time for some coffee!";
	} 
	return str;
    }
	
    /**
     *@param course is the course you want to find.
     *@return true if it finds the course in the course list otherwise false.
     */
    public Boolean findCourse(Course course) {
	for (int i = 0; i < this.doneCourses.size(); i++){
	    if(this.doneCourses.get(i).getName().equals(course.getName())) {
		return true;
	    }
	}
	    return false;
    }

     /**
     *@param course is the course you want to add to the doneCourses list.
     */
    public void courseIsDone(Course course){	
	hp = hp + course.getHP();
	doneCourses.add(course);
	undoneCourses.remove(course);
    }

     /**
     *@param item is the item you want to pick up.
     */
    public void pickUp(Item item){
	if (space + item.getSize() >= 10)
	    {
		System.out.println("Not enough room in bag");
	    }

	inventory.add(currentRoom.getItem());
	space = space + item.getSize();
	this.currentRoom.removeItem();
    }

    public void drop(String item){
	if (space == 0){
	    System.out.println("Nothing to drop");
	    return;
	}
	for(int i = 0; i<inventory.size(); i++){
	    if (inventory.get(i).getName().equals(item)){
		space = space - inventory.get(i).getSize();
		inventory.remove(i);
		return;
	    }
	}
	System.out.println("Can't find requested object to drop");
    }

     /**
     *@param coffee is the the used coffee.
     */
    public void drop(Coffee coffee) {
	if(inventory.contains("Coffee")) {
	    inventory.remove("Coffee");
	    space --;
	}
    }

     /**
     *@breif drinks up cooffee and gives energy to the avatar.
     */
    public void drinkUp() {
	int tmp;
	for(int i = 0; i<inventory.size(); i++){
	    if (inventory.get(i).getName().equals("Coffee")){
		drop("Coffee");
		tmp =(int)( Math.random()*3)+1;
		if(tmp == 1) {
		    System.out.println("Gud va svagt kaffe, här blir man ju inte pigg av");
		    if ( energy <= 80){
			energy = energy + 20;
		    }
		} else if(tmp == 2) {
		    System.out.println("hmm... Lite sprit saknas");
		    if( energy <= 60) {
			energy = energy + 40;
		    }
		} else if (tmp == 3) {
		    System.out.println("WOOOOH, den här va ju irish!");
		    energy = 100;
		}
	    }
	}
    }
    
    /**
     *@param creature is the creature you want to talk to.
     *@return the string of what the creature says.
     */
    public String talk(Creature creature) {
	return creature.talk();
    }

     /**
     *@param teacher is the teacher you want to take the exam from.
     */
    public void examMe(Teacher teacher) {
	Course c = teacher.askQuestion();
	this.energy = energy - 20;
	if ( c != null) {
	    courseIsDone(c);
	}
    }	    
	
}

