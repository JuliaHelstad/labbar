import java.util.Scanner;

public class Teacher extends Creature{

    private String ans1;
    private String ans2;
    private String ans3;
    private int rightAnswer;

    public Teacher(String name, Course course, String talk, String ans1, String ans2, String ans3, int rightAnswer) {
	super(name, course, talk);
	this.ans1 = ans1;
	this.ans2 = ans2;
	this.ans3 = ans3;
	this.rightAnswer = rightAnswer;
    }

    public Course askQuestion() {
	int answer;
	System.out.print(this.talk + "\n" + "1. " + this.ans1 + "\n" + "2. " + this.ans2 + "\n" + "3. " + this.ans3 + "\n");
	Scanner scan = new Scanner(System.in);
	try {
	    answer = scan.nextInt();
	} catch( Exception e) {
	    System.out.println("Totally wrong answer, try again");
	    answer = 0;
	}
	if ( answer == this.rightAnswer) {
	    System.out.println("WOOOOOOW du kommer fortfarande få CSN!");
	    return this.course;
    } else {
	    System.out.println("Try again later loser");
	}
	return null;
    }



    public Course getCourse() {
	return this.course;
    }




}


