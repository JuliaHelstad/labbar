public class Register
{
    private boolean open;
    public Queue queue;
    public int customerServed = 0;
    public double averageQueueTime = 0;
    public int numberOfDoneCustomers = 0;
    private double totalQueueTime = 0;
  

    public Register()
    {
	this.open = false;
	this.queue = new Queue();	
    }

    /**
     * opens the register. 
     */    
    public void open()
    {
	open = true;
    }

    /**
     * closes the register. 
     */    
    public void close()
    {
	open = false;
    }

    /**
     * finds out if a register is open. 
     * 
     * @return
     * true if the register is open. Else it will return false.
     */    
    public boolean isOpen()
    {
	return this.open;
    }

    /** 
     * tells what the register will do either if the current customer is done or not done.
     * 
     * @throws
     * throws an exception if the register doesn't have any customers.
     */    
    public void step() throws ExceptionThing
    {

	if(queue.length() == 0)
	    {
		throw new ExceptionThing("No Customers!");
	    }

	else
	    {
		if (currentCustomerIsDone() == true)
		    {
			double bornTime = queue.first().getBornTime();
			double queueTime = Simulation.time - bornTime;
			if (Simulation.time < bornTime) {
			    System.out.println("orginalBabaks fel");
			    System.exit(0);
			}
			numberOfDoneCustomers ++;
			updateAverageQueueTime (queueTime);
			removeCurrentCustomer();
			
		    }
		else
		    {
			queue.first().serve();
			customerServed ++;	
		    }
        
	    }
    }

    /**
     * gets the average queue time of the register.
     * 
     * @return
     * the average queue time.
     */    
    public double getAverageQueueTime ()
    {
	return averageQueueTime;
    }

    /**
     * updates the register's average queue time. 
     *	
     * @param queueTime 
     * the waiting time of the most recently done customer at the register.
     */    
      private void updateAverageQueueTime (double queueTime)
    {
	totalQueueTime = totalQueueTime + queueTime;
	averageQueueTime = totalQueueTime / numberOfDoneCustomers;
    }

    /**
     * finds out if a register has any customers. 
     * 
     * @return
     * true if the register's queue length is greater than 0. Else it will return false.
     */    
    public boolean hasCustomers()
    {
	if(queue.length > 0)
	    {
		return true;
	    }
	else
	    {
		return false;
	    }
    }

    /**
     * finds out if the served customer in the register is done. 
     * 
     * @return
     * true if the customer is done. if the customer is not done or there is an empty queue it will return false.
     */    
    public boolean currentCustomerIsDone()
    {
	if(getQueueLength() == 0)
	    {
		return false;
	    }
	
	return queue.first().isDone();
    }
	
    /**
     * adds a customer to the register's queue.
     * 
     * @param c 
     * the customer to be added.
     */    
    public void addToQueue(Customer c)
    {
	queue.enqueue(c);
    }

    /**
     * removes a customer from the register's queue. 
     * 
     * @return
     * the removed customer.
     */    
    public Customer removeCurrentCustomer()
    {
	return queue.dequeue();
    }

    /**
     * finds out the length of the register's queue.
     *
     * @return
     * the length of the register's queue.
     */    
    public int getQueueLength()
    {
	return queue.length();
    }
}
