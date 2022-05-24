
/**
 * 
 * @author YeTeA
 *
 * @param <E> Iterator has a Generic parameter. Could be Integer or String.
 */
public class Itr<E> implements Iterator<E> {

	private int cursor=0;
	private Collection<E> var;
	private E[] arr;
	
	/**
	 * 
	 * @param tempArr to initialize Array.
	 * @param temp to initialize Collection type.
	 */
	public Itr(E[] tempArr, Collection<E> temp) {
		this.arr = tempArr;
		var = temp;
	}
	/**
	 * This method returns next element of a Array
	 * @return Returns next element of Array of type <E>.
	 */
	public E next() {
		return arr[cursor++];
	}
	/**
	 * Checks whether Array has a next element or not.
	 * @return True;if Array has next element, False;otherwise.
	 */
	public boolean hasNext() {
		return cursor<var.used();
	}
	/**
	 * Removes the last element of Array.
	 * @return No return value.
	 */
	public void remove() {
		var.remove(arr[cursor]);
	}
	
}
