public class Queue
{
    private Node first;
    private Node last;
    public int length;
   
    private class Node
    {
	public Customer element;
	public Node next;

	public Node(Customer c)
	{
	    this.element = c;
	    this.next = null;
	} 
    }
    
    public Queue(Customer c)
    {
	Node newNode = new Node(c);

	this.first = newNode;
	this.last = newNode;
	this.length = 1;	
    }
    

    public Queue()
    {
	this.first = null;
	this.last = null;
	this.length = 0;	
    } 
    /**
     * gives the length of the queue.
     * 
     * @return 
     * the current queue length.
     */
    public int length()
    {
	return length;
    }
    
    /**
     * adds a customer for the queue.
     * 
     * @param c 
     * The customer to be added.
     */
    public void enqueue(Customer c)
    {
	if (c == null)
	    {
		System.out.println("The customer does not exist");
	    }

	Node newNode = new Node (c);
	
	if (length() == 0)
	    {
		first = newNode;
		last = newNode;
		newNode.next = null;
	    }

	else 
	    {
		last.next = newNode;
		last = newNode;
		newNode.next = null;	    
	    }

	length++;
    }

    /** 
     * removes the first Customer in the queue. 
     * 
     * @return
     * the removed Customer or null if the queue is empty.
     */    
    public Customer dequeue()
    {

	if (length() == 0)
	    {
		System.out.println("The queue is empty");
		return null;
	    }

	else
	    {
		Customer doneCustomer = first.element;
		first = first.next;
		
		length--;
		return doneCustomer;
	    }
    }
    

    public Customer first()
    {
	if(length() == 0)
	    {
		return null;
	    }
	else
	    {
		return first.element;
	    }
    }
    
}
