public abstract class Creature {

    protected Course course;
    protected String name;
    protected String talk;

    public Creature(String name, Course course, String talk) {
	this.name = name;
	this.course = course;
	this.talk = talk;
    }

    public String toString (){
	return "" + this.name + ", that has the course: " + this.course.getName();
    }

    public String talk (){
	return this.talk;
    }

} 
