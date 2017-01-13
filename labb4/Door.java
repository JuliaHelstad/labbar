import java.lang.Boolean;
import java.lang.Math;

public class Door {

    private String name;
    private Boolean open;
    private String direction;
  

    public Door(String name, Boolean open, String direction){
	this.open = open;
	this.name = name;
	this.direction = direction;
    }

    public void smashDoor(){
	int randomInt = (int)Math.random()*2+1;
	if(randomInt == 1){
	    System.out.println("You died");
	    System.exit(0);
	    }
	else if(randomInt == 2){
	    System.out.println("You smashed it. You freaking badass! Go you!");
	    this.open = open;
	}
    }

    public String isOpen(){
	if (open == true)
	    return "open";
	else return "locked";
    }

    public void openDoor(){
	if (open == false){
		open = true;
	    }
    }

    public String getDirection(){
	return this.direction;
    }

    public String getName(){
	return this.name;
    }


    /*
    public void setWestDoor(String room, boolean open) {
	this.doorW = new Door (room, open);
    }

    public void setSouthDoor(String room, boolean open) {
	this.doorS = new Door (room, open);
    }

    public void setEastDoor(String room, boolean open) {
	this.doorE = new Door (room, open);
    }

    public void setNorthDoor(String room, boolean open) {
	this.doorN = new Door (room, open);
	}*/

}
