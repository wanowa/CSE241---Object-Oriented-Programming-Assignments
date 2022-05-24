
/**
 * 
 * @author YeTeA
 *
 * @param <E> Queue interface has generic type <E>. It extends Collection interface.
 */
public interface Queue<E> extends Collection<E>{
	/**
	 * Inserts the specified element into this queue
	 * @param e is variable to add
	 * @return True;if element added successfully, False;otherwise.
	 */
	boolean add(E e);
	/**
	 * Retrieves, but does not remove, the head of this queue.
	 * @return Head of this queue
	 */
	E element();
	/**
	 * Inserts the specified element into this queue
	 * @param e is variable to add
	 * @return True;if element added successfully, False;otherwise.
	 */
	boolean offer(E e);
	/**
	 * Retrieves and removes the head of this queue, or throws if this queue is empty.
	 * @return Head of this queue.
	 */
	E poll();
}