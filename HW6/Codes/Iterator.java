
/**
 * 
 * @author YeTeA
 *
 * @param <E> Iterator has a Generic parameter. Could be Integer or String.
 */
public interface Iterator<E> {
	/**
	 * This method returns next element of a Array
	 * @return Returns next element of Array of type <E>.
	 */
	public E next();
	/**
	 * Checks whether Array has a next element or not.
	 * @return True;if Array has next element, False;otherwise.
	 */
	public boolean hasNext();
	/**
	 * Removes the last element of Array.
	 * @return No return value.
	 */
	public void remove();
}
