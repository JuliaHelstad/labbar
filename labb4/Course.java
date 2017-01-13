public class Course{

    private String book;
    private int hp;
    private String name;

    public  Course (String name, int hp, String book){
	this.book = book;
	this.hp = hp;
	this.name = name;
    }

    public int getHP(){
	return this.hp;
    }

    public String getBook(){
	return this.book;
    }

    public String getName(){
	return this.name;
    }

    /* public ArrayList<Course> UndoneCourses(){
	return 
	}*/
}
