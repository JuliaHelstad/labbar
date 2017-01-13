public class Simulator
{
    public static void main(String args[])
    {
	int maxQueue = 3;
	Store newStore = new Store(6, maxQueue);
	Simulation s = new Simulation(newStore, 1, 50, 10, maxQueue);

	for(int i = 0; i< 10000; i++)
	    {
		System.out.print("\033[2J\033[;H");
		s.step();
		System.out.println(s);
		try
		    {
			Thread.sleep(1000);				
		    }
		catch(InterruptedException milo)
		    {
			System.out.println("No sleep for Babak");
		    }

	    }
    }
}
