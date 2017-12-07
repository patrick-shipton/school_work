//package comp2402a5;

import java.util.Random;
import java.util.SortedSet;
import java.util.TreeSet;

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
					//explode(u);
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
				//explode(u);
			}
		}
	}

	public void explode(Node<T> v) {
		// Write this code to explode u
		// Make sure to update u.parent and/or r (the tree root) as appropriate
		
		// The entire subtree rooted at u is rebuilt into a perfectly balanced binary search tree (note that u is probably not the root of this new subtree.) 
		// Every node v in the rebuilt subtree has it's timer reset to Math.ceil(d*size(v)) where size(v) denotes the number of nodes in the subtree rooted at v
		
		Node<T> u = v, prev = v.parent, next;
		while (u != nil && u != v.parent) {
			if (prev == u.parent) {
				if (u.left != nil && u != v.parent) next = u.left;
				else if (u.right != nil) next = u.right;
				else next = u.parent;
			} else if (prev == u.left) {
				if (u.right != nil && u != v.parent) next = u.right;
				else next = u.parent;
			} else {
				next = u.parent;
			}
			prev = u;
			System.out.println("u.x: " + u.x);
			u = next;
		}
		
		//postorder to countdown
		
		//preorder to rebuild
	}

	// Here is some test code you can use
	public static void main(String[] args) {
		/*
		Testum.sortedSetSanityTests(new SortedSSet<Integer>(new CountdownTree<Integer>(1)), 1000);
		Testum.sortedSetSanityTests(new SortedSSet<Integer>(new CountdownTree<Integer>(2.5)), 1000);
		Testum.sortedSetSanityTests(new SortedSSet<Integer>(new CountdownTree<Integer>(0.5)), 1000);
		
		java.util.List<SortedSet<Integer>> ell = new java.util.ArrayList<SortedSet<Integer>>();
		ell.add(new java.util.TreeSet<Integer>());
		ell.add(new SortedSSet<Integer>(new CountdownTree<Integer>(1)));
		ell.add(new SortedSSet<Integer>(new CountdownTree<Integer>(2.5)));
		ell.add(new SortedSSet<Integer>(new CountdownTree<Integer>(0.5)));
		Testum.sortedSetSpeedTests(ell, 1000000);
		*/
		
		CountdownTree<Integer> t = new CountdownTree<Integer>(2);
		t.add(1);
		t.add(2);
		t.add(3);
		t.add(4);
		t.add(5);
		System.out.println(t);
		t.explode(t.r);
	}
}
