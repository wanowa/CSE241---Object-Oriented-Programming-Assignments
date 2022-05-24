/**
 * 
 * @author YeTeA
 *<p>It's my HashSet class. It implements Set<E> interface. Implements required methods and initializes some needed fields.</p>
 *<p>What the method's do is explained in the Collection javadoc file.
 * @param <E> HashSet has generic type <E>
 */

public class HashSet<E> implements Set<E> {

    private static final int SIZE = 100;
   /**
    * This is my uninitialized array 'buckets'. It will be initialized in constructor.
    */
    private E[] buckets;
    /**
     * size is 'Size of My array 'buckets''
     */
    private int size;
    /**
     * used shows how many elements are in the array
     */
    private int used=0;
    
    
	
    public HashSet() {
    	this(SIZE);
    }
    
    @SuppressWarnings("unchecked")
	public HashSet(int var) {
    	this.buckets = (E[])new Object[var];	//Degiskenlerimi initialize ediyorum
    	this.size = var;
    }
    
    public String toString() {		//toString method'umda StringBuilder kullanarak array'in tum elemanlarindan olusan bir 
    	int i;						//string olusturuyorum, ardindan return ediyorum.
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
    
    
    public boolean contains(E e) {		// e elemani array'imde bulunuyorsa true,bulunmuyorsa false donduruyorum.
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
    
    public boolean remove(E e) {		//Array'imde e elamani varsa cikariyorum.
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

    public Itr<E> iterator() {		//Iterator donduruyorum.
    	return new Itr<E>(buckets,this);
    }
    
    public int size() {		//Array'imin size'ini donduruyor
        return size;
    }
    
    public int used() {	//Array'imdeki eleman sayisini donduruyor.
    	return used;
    }
	
    public boolean isEmpty() {	//Arrayimde hic eleman yoksa true, aksi takdirde false donduruyor.
    	return used==0;
    }
    
    
    @SuppressWarnings("unchecked")
	public void clear() {		//Array'imdeki tum elemanlari siliyorum.
        this.buckets = (E[])new Object[size];		
        used=0;		
    }
    
    @SuppressWarnings("unchecked")
	public boolean add(E e) {		//Array'ime (eger yoksa) e elemanini ekliyorum.
    	int i;
    	if(contains(e))
    		return false;
    	if(used==size) {
    		E[] tempBucket = buckets;		
    		this.buckets = (E[])new Object[size*2];	
    		for(i=0;i<used;i++) {
    			buckets[i] = tempBucket[i];
    		}
    		size = size*2;
    	}
    	buckets[used]=e;	
    	used++;
    	return true;
    }
    
    @SuppressWarnings("unchecked")
	public boolean addAll(Collection<E> c) {	//c arrayinde bulunan, this.buckets'da bulunmayan tum elemanlari this.buckets arrayime ekliyorum.
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
    		if(!this.contains(temp)) {
    			buckets[used] = temp;
    			used++;
    		}
    	}
    	return true;
    } 
}
