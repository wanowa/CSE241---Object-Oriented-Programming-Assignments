/**
 * 
 * @author YeTeA
 *<p>It's my LinkedList class. It implements Set<E> and Queue<E> interfaces. Implements required methods and initializes some needed fields.</p>
 *<p>What the method's do is explained in the Collection and Queue javadoc files.
 * @param <E> LinkedList has generic type <E>
 */


public class LinkedList<E> implements List<E>,Queue<E>{
	
	
    private static final int SIZE = 100;
    private E[] buckets;
    private int size;
    private int used=0;
    
    public LinkedList() {	//Arrayimi default size ile initialize ediyorum.
    	this(SIZE);
    }
    
    @SuppressWarnings("unchecked")
	public LinkedList(int var) {		//Degiskenlerimi initialize ediyorum
    	this.buckets = (E[])new Object[var];
    	this.size = var;
    }
    
    ////// 	QUEUE 
	@SuppressWarnings("unchecked")
	public boolean add(E e) {	//LinkedList'imin sonuna e elemanini ekliyorum.
		int i;
		if(used == size) {
    		E[] tempBucket = buckets;		
    		this.buckets = (E[])new Object[size*2];	
    		for(i=0;i<used;i++) {
    			buckets[i] = tempBucket[i];
    		}
    		size = size*2;
		}
		buckets[used] = e;
		used++;
		return true;
	}
	
	@SuppressWarnings("unchecked")
	public boolean offer(E e) {	//LinkedList'imin sonuna e elemanini ekliyorum.
		int i;
		if(used == size) {
    		E[] tempBucket = buckets;		
    		this.buckets = (E[])new Object[size*2];	
    		for(i=0;i<used;i++) {
    			buckets[i] = tempBucket[i];
    		}
    		size = size*2;
		}
		buckets[used] = e;
		used++;
		return true;
	}
	
	public E element() {	//LinkedList'in head'ini donduruyorum.
		return buckets[0];
	}
	
	public E poll() {
		E temp = buckets[0];
		for(int i=1;i<used;i++) {
			buckets[i-1] = buckets[i];
		}
		used--;
		return temp;
	}
	//////
	
    
    public String toString() {	//toString method'umda StringBuilder kullanarak array'in tum elemanlarindan olusan bir 
    	int i;					//string olusturuyorum, ardindan return ediyorum.
    	StringBuilder sb = new StringBuilder();
    	sb.append("(");
    	for(i=0;i<used;i++) {
    		if(i==0) {
    			sb.append(buckets[i].toString() + ",");
    		}
    		else if(i == used-1) {
    			sb.append(buckets[i].toString());
    		}
    		else {
    			sb.append(buckets[i].toString() + ",");
    		}
    	}
    	sb.append(")");
    	return sb.toString();
    }
    
    public boolean retainAll(Collection<E> c){	//Eger arrayimdeki eleman c'nin arrayinde yoksa bu elemani this.buckets'dan cikariyorum.
    	int i;
    	for(i=0;i<used;i++) {
    		if(!c.contains(buckets[i])) {
    			this.remove(buckets[i]);
    			i--;
    		}
    	}
    	return true;
    }
    
    public boolean containsAll(Collection<E> c) {	//Eger arrayim, c arrayindeki tum elemanlari iceriyorsa true donduruyorum, aksi takdirde false donduruyorum.
    	Itr<E> iter = c.iterator();
    	E temp = null;
    	while(iter.hasNext()) {
    		temp = iter.next();
    		if(!this.contains(temp)) {
    			return false;
    		}
    	}
    	return true;
    }
    
    
    public boolean contains(E e) {	// e elemani array'imde bulunuyorsa true,bulunmuyorsa false donduruyorum.
    	for(int i=0;i<this.used;i++) {
    		if(buckets[i] == e) { 
    			return true;
    		}
    	}
    	return false;
    }

    public boolean removeAll(Collection<E> c) {	//Array'imden, c'de bulunan tum elemanlari cikariyorum.
    	int i;
    	for(i=0;i<used;i++) {
    		if(c.contains(buckets[i])) {
    			this.remove(buckets[i]);
    			i--;
    		}
    	}
    	return true;
    }
    
    public boolean remove(E e) {	//Array'imde e elamani varsa cikariyorum.
    	int i,j;
    	if(this.contains(e)) {
    		for(i=0;i<used;i++) {
    			if(buckets[i] == e) {
    				for(j=i+1;j<used;j++) {
    					buckets[j-1] = buckets[j];
    				}
    				buckets[used-1] = null;
    				used--;
    				return true;
    			}
    		}
    	}
    	return false;
    }

    public Itr<E> iterator() {	//Iterator donduruyorum.
    	return new Itr<E>(buckets,this);
    }
    
    public int size() {	//Array'imin size'ini donduruyor
        return size;
    }
    
    public int used() {		//Array'imdeki eleman sayisini donduruyor.
    	return used;
    }
	
    public boolean isEmpty() {	//Arrayimde hic eleman yoksa true, aksi takdirde false donduruyor.
    	return used==0;
    }
    
    
    @SuppressWarnings("unchecked")
	public void clear() {	//Array'imdeki tum elemanlari siliyorum.
        this.buckets = (E[])new Object[size];
        used=0;	
    }
    
    @SuppressWarnings("unchecked")
	public boolean addAll(Collection<E> c) {	//Array'ime c arrayindeki tum elemanlari ekliyorum
    	int i;
    	E temp = null;
    	Itr<E> iter = c.iterator();
    	if(used+c.size() >= size) {
    		E[] tempBucket = buckets;	
    		this.buckets = (E[])new Object[(used+c.size())*2];
    		for(i=0;i<used;i++) {
    			buckets[i] = tempBucket[i];
    		}
    		size = (used+c.size())*2;
    	}
    	while(iter.hasNext()) {
    		temp = iter.next();
    		buckets[used] = temp;
    		used++;
    	}
    	return true;
    } 
}
