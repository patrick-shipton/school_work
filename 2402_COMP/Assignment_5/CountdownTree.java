package comp2402a5;

import java.util.Random;
import java.util.SortedSet;
import java.util.TreeSet;
import java.util.HashMap;

/**
* An unfinished implementation of an Countdown tree (for exercises)
* @author morin
*
* @param <T>
*/
public class CountdownTree<T> extends
BinarySearchTree<CountdownTree.Node<T>, T> implements SSet<T> {

	// countdown delay factor
	double d;

	public static class Node<T> extends BSTNode<Node<T>,T> {
		int timer;  // the height of the node
	}

	public CountdownTree(double d) {
		this.d = d;
		sampleNode = new Node<T>();
		c = new DefaultComparator<T>();
	}

	public boolean add(T x) {
		Node<T> u = new Node<T>();
		u.timer = (int)Math.ceil(d);
		u.x = x;
		if (super.add(u)) {
			while(u.parent != nil){
				u = u.parent;
				u.timer--;
				if(u.timer == 0){
					explode(u);
				}
			}
			return true;
		}
		return false;
	}

	public void splice(Node<T> u) {
		Node<T> w = u.parent;
		super.splice(u);
		while(u.parent != nil){
			u = u.parent;
			u.timer--;
			if(u.timer == 0){
				explode(u);
			}
		}
	}
	
	public void traverse6(Node<T> u, Integer s, String position) {
		if (u == nil) return;
		if(position == ""){
			System.out.println(s + " root: " + u.x + "\ttimer: " + u.timer);
		} else {
			System.out.println(s + position +  ": " + u.x + "\ttimer: " + u.timer);
		}
		traverse6(u.left, s+1, position + " left");
		traverse6(u.right,s+1, position + " right");
	}


	public void explode(Node<T> v) {
		// Write this code to explode u
		// Make sure to update u.parent and/or r (the tree root) as appropriate
		
		// The entire subtree rooted at u is rebuilt into a perfectly balanced binary search tree (note that u is probably not the root of this new subtree.) 
		// Every node v in the rebuilt subtree has it's timer reset to Math.ceil(d*size(v)) where size(v) denotes the number of nodes in the subtree rooted at v
		
		// size vs height?
		// Can I balance from the base?
		HashMap<Node<T>,Integer> sizeMap = new HashMap<Node<T>,Integer>();
		System.out.println("\n\nExplode " + v.x);
		
		//traverse6(r,0,"");
		
		Node<T> u = v, prev = v.parent, next;
		int size, sizeTemp, sizeL, sizeR, sizeLR, sizeRL, sizeRR, sizeLL;
		boolean visit = false;
		while (u != nil && u != v.parent) {
			visit = false;
			if (prev == u.parent) {
				if (u.left != nil && u != v.parent){
					next = u.left;
				}
				else if (u.right != nil) {
					next = u.right;
				}
				else {
					next = u.parent;
					//visit(u)
					visit = true;
				}
			} else if (prev == u.left) {
				if (u.right != nil && u != v.parent){
					next = u.right;
				}
				else{
					next = u.parent;
					//visit(u);
					visit = true;
				}
			} else {
				next = u.parent;
				//visit(u);
				visit = true;
			}
			prev = u;
			if(visit){
				size = 1;
				sizeL = 0; // for calculations
				sizeR = 0; // for calculations
				//System.out.println("Special: " + u.x + " prev: " + prev.x);
				if(u.left != nil){
					sizeL = sizeMap.get(u.left);
					size += sizeL;
				} 
				if(u.right != nil){
					sizeR = sizeMap.get(u.right);
					size += sizeR;
				}
				//System.out.println("sizes L" + sizeL + " S" + size + " R" + sizeR);
				if(2*size <= (3*sizeL) ){
					System.out.println("rotateRight " + 2*size + " < " + 3*sizeL);
					size = 1 + sizeR;
					if(u.left != nil){
						if(u.left.right != nil){
							size += sizeMap.get(u.left.right);
						}
						sizeTemp = sizeMap.get(u.left) + 1 + sizeL;
						sizeMap.put(u.left, sizeTemp);
						u.left.timer = (int)Math.ceil(d * sizeTemp);
					}
					rotateRight(u);
					traverse6(r,0,"");
					prev = u;
					next = u.parent;
					
					
				} else if(2*size <= (3*sizeR)){
					System.out.println("rotateLeft " + 2*size + " < " + 3*sizeR);
					size = 1 + sizeL;
					if(u.right != nil){
						if(u.right.left != nil){
							size += sizeMap.get(u.right.left);
						}
						sizeTemp = sizeMap.get(u.right) + 1 + sizeR;
						sizeMap.put(u.right, sizeTemp);
						u.right.timer = (int)Math.ceil(d * sizeTemp);
					}
					rotateLeft(u);
					traverse6(r,0,"");
					prev = u.parent.left;
					next = u.parent;
				}
				sizeMap.put(u, size);
				u.timer = (int)Math.ceil(d * size);
				//System.out.println("u.x: " + u.x + "[" + size + "]");
				//traverse6(r,0,"");
				//System.out.println("");
			}
			u = next;
		}
		
		//postorder to countdown
		
		//preorder to rebuild
		System.out.println("End of Explode " + v.x);
		traverse6(r,0,"");
	}

	// Here is some test code you can use
	public static void main(String[] args) {
		
		Testum.sortedSetSanityTests(new SortedSSet<Integer>(new CountdownTree<Integer>(1)), 1000);
		Testum.sortedSetSanityTests(new SortedSSet<Integer>(new CountdownTree<Integer>(2.5)), 1000);
		Testum.sortedSetSanityTests(new SortedSSet<Integer>(new CountdownTree<Integer>(0.5)), 1000);
		
		java.util.List<SortedSet<Integer>> ell = new java.util.ArrayList<SortedSet<Integer>>();
		ell.add(new java.util.TreeSet<Integer>());
		ell.add(new SortedSSet<Integer>(new CountdownTree<Integer>(1)));
		ell.add(new SortedSSet<Integer>(new CountdownTree<Integer>(2.5)));
		ell.add(new SortedSSet<Integer>(new CountdownTree<Integer>(0.5)));
		Testum.sortedSetSpeedTests(ell, 1000000);
		//*/
		
		CountdownTree<Integer> t = new CountdownTree<Integer>(2);
		t.add(1);
		t.add(2);
		t.add(3);
		t.add(4);
		t.add(5);
		t.add(6);
		t.add(7);
		t.add(8);
		System.out.println(t);
		t.traverse6(t.r,0,"");
		System.out.println("\nBreak");
		t.explode(t.r);
	}
}
