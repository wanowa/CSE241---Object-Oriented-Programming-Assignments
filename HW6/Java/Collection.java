/**<h3><p>Collection interface is a generic interface that set, list, queue interfaces extend</p></h3>
 * 
 * @author YeTeA
 *
 * 
 */
public interface Collection<E> {
	/**
	 * <p>iterator() method returns the Collection's iterator.</p>
	 * @return iterator of type Itr<E>
	 */
	Itr<E> iterator();
	
	/**
	 * <p>add(E e) method adds new element to the end of set/list/queue</p>
	 * @param e
	 * @return True;if element added successfully, False;otherwise.
	 */
	boolean add(E e);
	/**
	 * <p>addAll method adds object c's elements one by one to the end of set/list/queue</p>
	 * @param e
	 * @return True;if elements added successfully, False;otherwise
	 */
	boolean addAll(Collection<E> c);
	/**
	 * <p>clear method clears whole elements of a set/list/queue</p>
	 * @return void
	 */
	void clear();
	/**
	 * <p>Checks if array contains element e</p>
	 * @param e
	 * @return True;if array contains element e, False;otherwise
	 */
	boolean contains(E e);
	/**
	 * <p>Checks if array contains whole elements in Collection c</p>
	 * @param c
	 * @return True; if this collection contains all of the elements in thespecified collection, False;otherwise
	 */
	boolean containsAll(Collection<E> c);
	/**
	 * <p>Checks whether array empty or not</p>
	 * @return True;is array empty,False;otherwise
	 */
	boolean isEmpty();
	/**
	 * <p>Removes element e from this array, if exist.</p>
	 * @param e
	 * @return True;if element removed successfully, False;otherwise
	 */
	boolean remove(E e);
	/**
	 * <p>Removes whole elements in Collection c from this array, if exist.</p>
	 * @param c
	 * @return True;if elements removed successfully, False;otherwise
	 */
	boolean removeAll(Collection<E> c);
	/**
	 * <p>Retains only the elements in this collection that are contained in the specified collection</p>
	 * @param c
	 * @return True; if uncommon elements removed successfully, False;otherwise.
	 */
	boolean retainAll(Collection<E> c);
	/**
	 * 
	 * @return size of this array.
	 */
	int size();
	/**
	 * 
	 * @return number of used elements of this array.
	 */
	int used();
}