public class Customer 
{
    private double bornTime;
    private int groceries;


    public Customer(double bornTime, int groceries)
    {
	this.bornTime = bornTime;
	this.groceries = groceries;
    }

    /**
     * makes a string.
     * 
     * @return
     * a string of the customers borntime and groceries.
     */    
    public String toString()
    {
	String str = "bornTime = " + bornTime + ", groceries = " + groceries;
	return str;
    }

    /**
     * gets groceries. 
     * 
     * @return
     * the customer's groceries.
     */    
    public int getCustomerGorceries()
    {
	return groceries;
    }

    /**
     * gets borntime. 
     * 
     * @return
     * the customer's borntime.
     */    
    public double getBornTime() 
    {
	return bornTime;
    }

    /**
     * finds out if a customer is done. 
     * 
     * @return
     * true if the customer is done. Else it will return false.
     */    
    public boolean isDone ()
    {
	if (this.groceries == 0)
	    {
		return true;
	    }
	else 
	    {
		return false;
	    }
    }

    /**
     * subtracts the customer's groceries by one.
     */    
    public void serve ()
    {	
	groceries--;
    }

}


