import java.lang.Math;

public abstract class Item {

    protected String name;
    protected int size;

    public Item(String name, int size) {
	this.name = name;
	this.size = size;
    }

   public String getName() {
	return this.name;
    }

    public String toStringItem() {
	return "" + this.name + ", Size: " + this.size;
    }

    public int getSize(){
	return this.size;
    }

   

}
