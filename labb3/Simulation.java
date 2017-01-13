import java.util.LinkedList;

public class Simulation
{
    public Store store;
    public static int time = 0;
    public int intensity;
    public int maxGroceries;
    public int thresholdForNewRegister;
    public double averageQueue = 0;

    public Simulation(Store store, int time, int intensity, int maxGroceries, int thresholdForNewRegister)
    {
	this.store = store;
	this.time = time;
	this.intensity = intensity;
	this.maxGroceries = maxGroceries;
	this.thresholdForNewRegister = thresholdForNewRegister;
    }
    
    /**
     * gets the sold groceries.
     * 
     * @return
     * the number of total sold groceries.
     */    
    public int soldGroceries()
    {
        return store.getTotalGroceries();
    }
    
    /**
     * finds out the threshold for the queues in the store. 
     * 
     * @return
     * the threshold for the store's queues.
     */    
    public double thresholdQueue()
    {
	averageQueue = store.getAverageQueueLength() + averageQueue;
	return averageQueue/time;
    }

    /**
     * gets the average wait time.
     * 
     * @return
     * the number of the average wait time at the store.
     */    
    public double averageWaitTime()
    {
	return store.averageWaitTime();
    }

    /**
     * makes a string of all the thing you want to print out.
     * 
     * @return
     * a strng of the registers states and statistics.
     */    
    public String toString()
	{
	    String str = "";
	    str += store.toString();
	    str += "\n" + "Time: " + time;
	    str += "\n" + "Total groceries sold: " + soldGroceries();
	    str += "\n" + "Threshold for the queues: " + thresholdQueue();
	    str += "\n" + "Average wait time: "+ averageWaitTime();
	  
	    return str;
	}
    
    /** 
     * tells what the store will do for each step. 
     */    
    public void step()
    {
	time ++;
	int randomNumber = (int)(Math.random() * 100)+0;
	
	if(randomNumber < intensity)
	    {
		int randomGroceries = (int)(Math.random() * maxGroceries)+1;
		Customer newCustomer = new Customer(time, randomGroceries);
		store.newCustomer(newCustomer);
	    }

	if(store.getAverageQueueLength() > thresholdForNewRegister)
	    {
		store.openNewRegister();
	    }

	store.step();
       

	return;
    }

}
