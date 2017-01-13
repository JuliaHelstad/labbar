import java.util.ArrayList;
import java.util.Scanner;
import java.util.LinkedList;


public class Game{
    Scanner scan;
    String choice;
    String gamer;
    Avatar avatar;
    Scanner input;
    
    public Game(){
	
    }
    
    public void ask(Avatar avatar)  {
	choice = "continue";
	while(!choice.equals("exit")){
	    System.out.println("what do you want to do now?" + "\n" + "Type help if you need help with commands");
	    Scanner scan = new Scanner(System.in);
	    choice = scan.nextLine();
	    
	
	    String[] words = choice.split(" ");
	    if (words[0].equals("pick") && words[1].equals("up") && words[2].equals(avatar.getCurrentRoom().getItem().getName())){
		System.out.println("you picked up " + avatar.getCurrentRoom().getItem().getName());
		avatar.pickUp(avatar.getCurrentRoom().getItem());
	    }
	    	    
	    if (words[0].equals("drop")){
		avatar.drop(words[1]);
	    }

	    if(words[0].equals("go") && words[1].equals("to")){

		if ( words[2].equals("east")){ 
		    if (!(avatar.findRoom(avatar.getCurrentRoom().doorE.getName()).equals(null))){
			if (avatar.getCurrentRoom().doorE.isOpen().equals("locked")){
			    System.out.println("The door is locked. Do you want to use a key to open it? yes/no");
			    String answer = scan.nextLine();
			    if (answer.equals("yes") && avatar.inventoryContainsKey()==true){				
				avatar.useKey(avatar.getCurrentRoom().doorE);
				avatar.go(avatar.getCurrentRoom().doorE.getName());
			    }
			    if (answer.equals("yes") && avatar.inventoryContainsKey()==false){
				System.out.println("You need a key");
			    }  
			}
			else avatar.go(avatar.findRoom(avatar.getCurrentRoom().doorE.getName()).getName());	
		    }		
		    else  System.out.println("You can't go east, try another direction");
		}

		if ( words[2].equals("south")){ 
		    if (!(avatar.findRoom(avatar.getCurrentRoom().doorS.getName()).getName()).equals("null")){
			if (avatar.getCurrentRoom().doorS.isOpen().equals("locked")){
			    System.out.println("The door is locked. Do you want to use a key to open it? yes/no");
			    String answer = scan.nextLine();
			    if (answer.equals("yes") && avatar.inventoryContainsKey()==true){				
				avatar.useKey(avatar.getCurrentRoom().doorS);
				avatar.go(avatar.getCurrentRoom().doorS.getName());
			    }
			    if (answer.equals("yes") && avatar.inventoryContainsKey()==false){
				System.out.println("You need a key");
			    }  
			}
			else avatar.go(avatar.findRoom(avatar.getCurrentRoom().doorS.getName()).getName());	
		    }		
		    else  System.out.println("You can't go south, try another direction");
		}

		if ( words[2].equals("west")){ 
		    if (!(avatar.findRoom(avatar.getCurrentRoom().doorW.getName()).getName()).equals("null")){
			if (avatar.getCurrentRoom().doorW.isOpen().equals("locked")){
			    System.out.println("The door is locked. Do you want to use a key to open it? yes/no");
			    String answer = scan.nextLine();
			    if (answer.equals("yes") && avatar.inventoryContainsKey()==true){				
				avatar.useKey(avatar.getCurrentRoom().doorW);
				avatar.go(avatar.getCurrentRoom().doorW.getName());
			    }
			    if (answer.equals("yes") && avatar.inventoryContainsKey()==false){
				System.out.println("You need a key");
			    }  
			}
			else avatar.go(avatar.findRoom(avatar.getCurrentRoom().doorW.getName()).getName());	
		    }		
		    else  System.out.println("You can't go west, try another direction");
		}

		if ( words[2].equals("north")){ 
		    if (!(avatar.findRoom(avatar.getCurrentRoom().doorN.getName()).getName()).equals("null")){
			if (avatar.getCurrentRoom().doorN.isOpen().equals("locked")){
			    System.out.println("The door is locked. Do you want to use a key to open it? yes/no");
			    String answer = scan.nextLine();
			    if (answer.equals("yes") && avatar.inventoryContainsKey()==true){				
				avatar.useKey(avatar.getCurrentRoom().doorN);
				avatar.go(avatar.getCurrentRoom().doorN.getName());
			    }
			    if (answer.equals("yes") && avatar.inventoryContainsKey()==false){
				System.out.println("You need a key");
			    }  
			}
			else avatar.go(avatar.findRoom(avatar.getCurrentRoom().doorN.getName()).getName());	
		    }		
		    else  System.out.println("You can't go north, try another direction");
		}	
	    }	

	    if ( choice.equals("drink coffee")){
		avatar.drinkUp();
	    }
	    
	    if(choice.equals("show inventory")){
		System.out.println(avatar.inventoryToString());
	    }

	    if(choice.equals("help")){
		System.out.println(help());
	    }

	    if(choice.equals("show status")){
		System.out.println(avatar.status() + avatar.getCurrentRoom().roomInfo());
	    }

	    if(words[0].equals("take") && words[1].equals("exam")){
		
		if(avatar.findCourse(avatar.getCurrentRoom().getTeacher().getCourse()) == false){
		    avatar.examMe(avatar.getCurrentRoom().getTeacher());
		} else {
		    System.out.println("You already took my class stupid");
		}
	    }
	    if(words[0].equals("talk") && words[1].equals("to") && words[2].equals("teacher")) {
		try {
		    System.out.println(avatar.talk(avatar.getCurrentRoom().getTeacher()));
		} catch (Exception e) {
		    System.out.println("Can't talk with someone who is not there");
		}
	    }
	    
	    if(words[0].equals("talk") && words[1].equals("to") && words[2].equals("student")) {
		try {
		    System.out.println(avatar.talk(avatar.getCurrentRoom().getStudent()));
		} catch(Exception e){
		    System.out.println("Can't talk with someone who is not there");
		}
	    }

	    if(words[0].equals("show") && words[1].equals("courses")){
		System.out.println("Done courses:" + " \n" +  avatar.toString(avatar.doneCourses) + "\n" + "Undone courses: \n" + avatar.toString(avatar.undoneCourses));
	    }

	    if(choice.equals("directions")) {
		    System.out.println(avatar.getCurrentRoom().roomToString());
		}

	    if(choice.equals("graduate")  && avatar.readyToGraduate()) {
		System.out.println("DIPLOMA!! for " +avatar.getName() + "\n" + avatar.toString(avatar.doneCourses));
		System.out.println(avatar.getCurrentRoom().getSfinx().graduate());
	     }

	     if(words[0].equals("talk") && words[1].equals("to") && words[2].equals("sfinx")) {
		 System.out.println(avatar.talk(avatar.getCurrentRoom().getSfinx()));
	     }

	if(choice.equals("exit")){
	    System.out.println("BYE");
	    System.exit(0);
	}
	    
	  
	}
    }
    



	public String help(){

	    return "Command:                Action:" + "\n" + "pick up <item>          picks up the chosen item" + "\n" + "drop <item>             drops chosen item" + "\n" + "talk to <person>        talks to chosen person" +"\n" + "go to <direction>       goes to chosen direction" + "\n" + "drink coffee            drinks coffee" + "\n" + "show inventory          shows inventory" + "\n"+ "show status             shows status" + "\n"+ "show courses            shows courses" + "\n" + "take exam               takes exam" + "\n" + "smash door              totaly destroyes the door" + "\n" + "directions              Shows where you can go" + "\n" + "graduate                graduate at the Sfinx" + "\n" + "exit                    exit game" + "\n";

	}

public static void main(String [] args) {
    

     World world = new World("input.txt");
    LinkedList<Room> list = new LinkedList();
    list = world.lineReader();
    Game gamer = new Game();
    Avatar avatar = new Avatar(list.get(0), list);
    System.out.println( avatar.getName() + ", are you ready for the time of your life? You start in philosopherRoom! Lets go!");
    

     gamer.ask(avatar);
}
}
