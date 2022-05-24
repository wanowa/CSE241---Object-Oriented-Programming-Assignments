/*
import ArrayList;
import HashSet;
import LinkedList;
*/
/**
 * This class is our main class. We'll test Hashset, ArrayList, LinkedList classes in here.
 * 
 * 
 * @author Yusuf Talha Altun
 * 
 * 
*/
public class Main {

	/**
	 * This is our main method to test our Classes/Interfaces.
	 * 
	 * @param HS1 HashSet variable of Integer Type
	 * @param HS2 HashSet variable of Integer Type
	 * @param HS3 HashSet variable of String Type
	 * @param HS4 HashSet variable of String Type
	 * @param AL1 ArrayList variable of Integer Type
	 * @param AL2 ArrayList variable of Integer Type
	 * @param AL3 ArrayList variable of String Type
	 * @param AL4 ArrayList variable of String Type
	 * @param LL1 LinkedList variable of Integer Type
	 * @param LL2 LinkedList variable of Integer Type
	 * @param LL3 LinkedList variable of String Type
	 * @param LL4 LinkedList variable of String Type
	 *@return no return value 
	 *
	 */

	public static void main(String[] args) {	

		/////////////////////	HASHSET
		HashSet<Integer> HS1 = new HashSet<Integer>(20);
		
		System.out.printf("\n\nHS1.isEmpty() applied\n");
		if(HS1.isEmpty()) {
			System.out.printf("Yes, HS1 is empty now.\n\n");
		}
		else {
			System.out.printf("No, HS1 is not empty.\n\n");
		}
		
		HS1.add(98);
		HS1.add(42);
		HS1.add(55);
		HS1.add(34);
		HS1.add(42);
		HS1.add(55);
		HS1.add(41);
		HS1.add(20);
		HS1.add(6);
		System.out.printf("HS1 = %s\n",HS1);
		
		System.out.printf("HS1.contains(41) applied\n");		
		if(HS1.contains(41)) {
			System.out.printf("Yes, HS1 contains 41.\n\n");
		}
		else {
			System.out.printf("No, HS1 doesn't contains 41.\n\n");
		}
		HS1.remove(41);
		System.out.printf("HS1.remove(41) applied.\n\n",HS1);
		
		System.out.printf("HS1.contains(41) applied\n");
		if(HS1.contains(41)) {
			System.out.printf("Yes, HS1 contains 41.\n");
		}
		else {
			System.out.printf("No, HS1 doesn't contains 41.\n\n");
		}
		
		HashSet<Integer> HS2 = new HashSet<Integer>(20);
		HS2.add(98);
		HS2.add(65);
		HS2.add(55);
		HS2.add(73);
		HS2.add(34);
		HS2.add(42);
		HS2.add(96);
		HS2.add(27);
		HS2.add(6);
		System.out.printf("HS2 = %s\n\n",HS2);
		
		HS1.retainAll(HS2);
		System.out.printf("HS1.retainAll(HS2) applied.\n");
		System.out.printf("HS1 = %s\n\n",HS1);
		
		HS1.removeAll(HS2);
		System.out.printf("HS1.removeAll(HS2) applied.\n");
		System.out.printf("HS1 = %s\n\n",HS1);
		
		HS2.clear();
		System.out.printf("HS2.clear() applied.\n\n");
		System.out.printf("HS2 = %s\n",HS2);
		
		HashSet<String> HS3 = new HashSet<String>(5);
		HS3.add("Yusuf");
		HS3.add("Talha");
		HS3.add("Altun");
		HS3.add("CSE241");
		HS3.add("HW6");
		HS3.add("Java");
		HS3.add("Hierarchy");
		HS3.add("HashSet");
		HS3.add("Example");
		System.out.printf("HS3 = %s\n\n",HS3);
		
		
		HashSet<String> HS4 = new HashSet<String>(20);
		HS4.add("Yusuf");
		HS4.add("Talha");
		HS4.add("Altun");
		HS4.add("CSE241");
		System.out.printf("HS4 = %s\n\n",HS4);
		
		if(HS3.containsAll(HS4)) {
			System.out.printf("Yes,HS3 contains all of the elements in the HS4.\n\n");
		}
		else {
			System.out.printf("No, HS3 doesn't contains all of the elements in the HS4.\n\n");
		}
		
		HS3.remove("Talha");
		System.out.printf("HS3.remove('Talha') applied.\n");
		System.out.printf("HS3 = %s\n\n",HS3);
		
		System.out.printf("Some elements inserted to HS4.\n");
		HS4.add("HW7");
		HS4.add("Java");
		HS4.add("GUI");
		HS4.add("HexGame");
		HS4.add("Button");
		System.out.printf("HS4 = %s.\n\n",HS4);
		
		HS3.addAll(HS4);
		System.out.printf("HS3.addAll(HS4) applied.\n");
		System.out.printf("HS3 = %s.\n\n",HS3);
		
		HS3.retainAll(HS4);
		System.out.printf("HS3.retainAll(HS4) applied.\n");
		System.out.printf("HS3 = %s.\n\n",HS3);
		
		HS3.removeAll(HS4);
		System.out.printf("HS3.removeAll(HS4) applied.\n");
		System.out.printf("HS3 = %s.\n\n",HS3);
		
		HS4.clear();
		System.out.printf("HS4.clear() applied.\n");
		System.out.printf("HS4 = %s.\n\n",HS4);
		
	
		
		////////////////////	ARRAYLIST		
		ArrayList<Integer> AL1 = new ArrayList<Integer>(20);
		if(AL1.isEmpty()) {
			System.out.printf("Yes, AL1 is empty now.\n\n");
		}
		else {
			System.out.printf("No, AL1 is not empty.\n\n");
		}
		
		AL1.add(98);
		AL1.add(42);
		AL1.add(42);
		AL1.add(55);
		AL1.add(55);
		AL1.add(34);
		AL1.add(41);
		AL1.add(20);
		AL1.add(6);
		System.out.printf("AL1 = %s\n",AL1);
		
		System.out.printf("AL1.contains(41) applied.\n");
		if(AL1.contains(41)) {
			System.out.printf("Yes, AL1 contains 41.\n\n");
		}
		else {
			System.out.printf("No, AL1 doesn't contains 41.\n\n");
		}
		AL1.remove(41);
		System.out.printf("AL1.remove(41) applied.\n",AL1);
		if(AL1.contains(41)) {
			System.out.printf("Yes, AL1 contains 41.\n");
		}
		else {
			System.out.printf("No, AL1 doesn't contains 41.\n\n");
		}
		
		ArrayList<Integer> AL2 = new ArrayList<Integer>(20);
		AL2.add(98);
		AL2.add(65);
		AL2.add(55);
		AL2.add(73);
		AL2.add(73);
		AL2.add(34);
		AL2.add(42);
		AL2.add(96);
		AL2.add(27);
		AL2.add(27);
		AL2.add(6);
		System.out.printf("AL2 = %s\n\n",AL2);
		
		AL1.retainAll(AL2);
		System.out.printf("AL1.retainAll(AL2) applied.\n");
		System.out.printf("AL1 = %s\n\n",AL1);
		
		AL1.removeAll(AL2);
		System.out.printf("AL1.removeAll(AL2) applied.\n");
		System.out.printf("AL1 = %s\n\n",AL1);
		
		AL2.clear();
		System.out.printf("AL2.clear() applied.\n");
		System.out.printf("AL2 = %s\n\n",AL2);
		
		ArrayList<String> AL3 = new ArrayList<String>(5);
		AL3.add("Yusuf");
		AL3.add("Yusuf");
		AL3.add("Talha");
		AL3.add("Altun");
		AL3.add("CSE241");
		AL3.add("HW6");
		AL3.add("HW6");
		AL3.add("Java");
		AL3.add("Hierarchy");
		AL3.add("ArrayList");
		AL3.add("Example");
		System.out.printf("AL3 = %s\n\n",AL3);
		
		
		ArrayList<String> AL4 = new ArrayList<String>(20);
		AL4.add("Yusuf");
		AL4.add("Talha");
		AL4.add("Talha");
		AL4.add("Altun");
		AL4.add("CSE241");
		System.out.printf("AL4 = %s\n\n",AL4);
		
		System.out.printf("AL3.containsAll(AL4) applied.\n");
		if(AL3.containsAll(AL4)) {
			System.out.printf("Yes,AL3 contains all of the elements in the AL4.\n\n");
		}
		else {
			System.out.printf("No, AL3 doesn't contains all of the elements in the AL4.\n\n");
		}
		
		AL3.remove("Talha");
		System.out.printf("AL3.remove('Talha') applied.\n");
		System.out.printf("AL3 = %s\n\n",AL3);
		
		System.out.printf("Some elements inserted to AL4.\n");
		AL4.add("HW7");
		AL4.add("Java");
		AL4.add("GUI");
		AL4.add("HexGame");
		AL4.add("Button");
		System.out.printf("AL4 = %s\n\n",AL4);
		
		
		AL3.addAll(AL4);
		System.out.printf("AL3.addAll(AL4) applied.\n");
		System.out.printf("AL3 = %s.\n\n",AL3);
		
		AL3.retainAll(AL4);
		System.out.printf("AL3.retainAll(AL4) applied.\n");
		System.out.printf("AL3 = %s.\n\n",AL3);
		
		AL3.removeAll(AL4);
		System.out.printf("AL3.removeAll(AL4) applied.\n");
		System.out.printf("AL3 = %s.\n\n",AL3);
		
		AL4.clear();
		System.out.printf("AL4.clear() applied.\n");
		System.out.printf("AL4 = %s.\n\n",AL4);
		
		
		
		///////////////////////	LINKED LIST
		Integer tempI = null;
		
		LinkedList<Integer> LL1 = new LinkedList<Integer>(20);
		if(LL1.isEmpty()) {
			System.out.printf("Yes, LL1 is empty now.\n\n");
		}
		else {
			System.out.printf("No, LL1 is not empty.\n\n");
		}
		
		LL1.add(98);
		LL1.add(42);
		LL1.add(42);
		LL1.add(55);
		LL1.add(55);
		LL1.add(34);
		LL1.add(41);
		LL1.add(20);
		LL1.add(6);
		System.out.printf("LL1 = %s\n",LL1);
		
		System.out.printf("LL1.contains(41) applied.\n");
		if(LL1.contains(41)) {
			System.out.printf("Yes, LL1 contains 41.\n\n");
		}
		else {
			System.out.printf("No, LL1 doesn't contains 41.\n\n");
		}
		LL1.remove(41);
		System.out.printf("LL1.remove(41) applied.\n",LL1);
		if(LL1.contains(41)) {
			System.out.printf("Yes, LL1 contains 41.\n");
		}
		else {
			System.out.printf("No, LL1 doesn't contains 41.\n\n");
		}
		
		LinkedList<Integer> LL2 = new LinkedList<Integer>(20);
		LL2.add(98);
		LL2.add(65);
		LL2.add(55);
		LL2.add(73);
		LL2.add(73);
		LL2.offer(27);
		LL2.offer(6);
		System.out.printf("LL2 = %s\n\n",LL2);
		
		LL1.addAll(LL2);
		System.out.printf("LL1.addAll(LL2) applied.\n");
		System.out.printf("LL1 = %s\n\n",LL1);
		
		tempI = LL1.poll();
		System.out.printf("LL1.poll() applied.\n");
		System.out.printf("Retrieved element is = %d.\n",tempI);
		System.out.printf("LL1 = %s\n\n",LL1);
		
		tempI = LL1.poll();
		System.out.printf("LL1.poll() applied.\n");
		System.out.printf("Retrieved element is = %d.\n",tempI);
		System.out.printf("LL1 = %s\n\n",LL1);
		
		tempI = LL1.element();
		System.out.printf("LL1.element() applied.\n");
		System.out.printf("Retrieved element is = %d.\n",tempI);
		System.out.printf("LL1 = %s\n\n",LL1);
		
		LL1.retainAll(LL2);
		System.out.printf("LL1.retainAll(LL2) applied.\n");
		System.out.printf("LL1 = %s\n\n",LL1);
		
		LL1.removeAll(LL2);
		System.out.printf("LL1.removeAll(LL2) applied.\n");
		System.out.printf("LL1 = %s\n\n",LL1);
		
		LL2.clear();
		System.out.printf("LL2.clear() applied.\n");
		System.out.printf("LL2 = %s\n\n",LL2);
		
		
		String tempS = null;
		LinkedList<String> LL3 = new LinkedList<String>(5);
		LL3.add("Yusuf");
		LL3.add("Yusuf");
		LL3.add("Talha");
		LL3.add("Altun");
		LL3.add("CSE241");
		LL3.add("HW6");
		LL3.add("HW6");
		LL3.add("Java");
		LL3.add("Hierarchy");
		LL3.add("LinkedList");
		LL3.add("Example");
		System.out.printf("LL3 = %s\n\n",LL3);
		
		
		LinkedList<String> LL4 = new LinkedList<String>(20);
		LL4.add("Yusuf");
		LL4.add("Talha");
		LL4.add("Talha");
		LL4.add("Altun");
		LL4.add("CSE241");
		System.out.printf("LL4 = %s\n\n",LL4);
		
		System.out.printf("LL3.containsAll(LL4) applied.\n");
		if(LL3.containsAll(LL4)) {
			System.out.printf("Yes,LL3 contains all of the elements in the LL4.\n\n");
		}
		else {
			System.out.printf("No, LL3 doesn't contains all of the elements in the LL4.\n\n");
		}
		
		LL3.remove("Talha");
		System.out.printf("LL3.remove('Talha') applied.\n");
		System.out.printf("LL3 = %s\n\n",LL3);
		
		System.out.printf("Some elements inserted to LL4.\n");
		LL4.offer("HW7");
		LL4.offer("Java");
		LL4.offer("GUI");
		LL4.offer("HexGame");
		LL4.offer("Button");
		System.out.printf("LL4 = %s\n\n",LL4);
		
		
		LL3.addAll(LL4);
		System.out.printf("LL3.addAll(LL4) applied.\n");
		System.out.printf("LL3 = %s.\n\n",LL3);
		
		LL3.retainAll(LL4);
		System.out.printf("LL3.retainAll(LL4) applied.\n");
		System.out.printf("LL3 = %s.\n\n",LL3);
		
		tempS = LL3.poll();
		System.out.printf("LL3.poll() applied.\n");
		System.out.printf("Retrieved element is '%s'.\n",tempS);
		System.out.printf("LL3 = %s.\n\n",LL3);
		
		tempS = LL3.poll();
		System.out.printf("LL3.poll() applied.\n");
		System.out.printf("Retrieved element is '%s'.\n",tempS);
		System.out.printf("LL3 = %s.\n\n",LL3);
		
		tempS = LL3.element();
		System.out.printf("LL3.element() applied.\n");
		System.out.printf("Retrieved element is '%s'.\n",tempS);
		System.out.printf("LL3 = %s.\n\n",LL3);
		
		LL3.removeAll(LL4);
		System.out.printf("LL3.removeAll(LL4) applied.\n");
		System.out.printf("LL3 = %s.\n\n",LL3);
		
		LL4.clear();
		System.out.printf("LL4.clear() applied.\n");
		System.out.printf("LL4 = %s.\n\n",LL4);
		
		
	}
}
