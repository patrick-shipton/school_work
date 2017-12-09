package comp2402a5;

import java.util.Random;
import java.util.SortedSet;
import java.util.TreeSet;
import java.util.HashMap;
import java.util.Map.Entry;
import java.util.AbstractMap.SimpleEntry;

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
	
	public void left(Node<T> u, HashMap<Node<T>,Entry<Integer,Integer>> sizeMap, int heightL, int heightR){
		int heightRL = 0;
		int sizeL = 0;
		if(u.left != nil){
			sizeL = sizeMap.get(u.left).getKey();
		}
		int size = 1 + sizeL;
		if(u.right != nil){
			if(u.right.left != nil){
				size += sizeMap.get(u.right.left).getKey();
				heightRL = sizeMap.get(u.right.left).getValue();
			}
			int sizeTemp = sizeMap.get(u.right).getKey() + 1 + sizeL;
			int heightTemp = 1 + ((heightRL > heightL) ? heightRL : heightL); //??
			sizeMap.put(u.right, new SimpleEntry<>(sizeTemp, heightTemp));
			u.right.timer = (int)Math.ceil(d * sizeTemp);
		}
		rotateLeft(u);
		
		sizeMap.put(u, new SimpleEntry<>(size, 1 + ((heightRL > heightL) ? heightRL : heightL))); //??
		u.timer = (int)Math.ceil(d * size);
	}
	
	public void right(Node<T> u, HashMap<Node<T>, Entry<Integer,Integer>> sizeMap, int heightL, int heightR){
		int heightLR = 0;
		int sizeR = 0;
		if(u.right != nil){
			sizeR = sizeMap.get(u.right).getKey();
		}
		int size = 1 + sizeR;
		if(u.left != nil){
			if(u.left.right != nil){
				size += sizeMap.get(u.left.right).getKey();
				heightLR = sizeMap.get(u.left.right).getValue();
			}
			int sizeTemp = sizeMap.get(u.left).getKey() + 1 + sizeR;
			int heightTemp = 1 + ((heightLR > heightR) ? heightLR : heightR); //??
			sizeMap.put(u.right, new SimpleEntry<>(sizeTemp, heightTemp));
			u.left.timer = (int)Math.ceil(d * sizeTemp);
		}
		rotateRight(u);
		
		sizeMap.put(u, new SimpleEntry<>(size, 1 + ((heightLR > heightR) ? heightLR : heightR))); //??
		u.timer = (int)Math.ceil(d * size);
	}
	
	public void explode(Node<T> v) {
		// Write this code to explode u
		// Make sure to update u.parent and/or r (the tree root) as appropriate
		
		// The entire subtree rooted at u is rebuilt into a perfectly balanced binary search tree (note that u is probably not the root of this new subtree.) 
		// Every node v in the rebuilt subtree has it's timer reset to Math.ceil(d*size(v)) where size(v) denotes the number of nodes in the subtree rooted at v
		
		// size vs height?
		// Can I balance from the base?
		HashMap<Node<T>,Entry<Integer,Integer>> sizeMap = new HashMap<Node<T>,Entry<Integer,Integer>>();
		//HashMap<Node<T>,Integer> heightMap = new HashMap<Node<T>,Integer>();
		//new SimpleEntry<>(size,height)
		// getKey = size getValue = height
		
		Node<T> u = v, prev = v.parent, next;
		int size;
		int heightR, heightL, heightLR, heightRL, heightRR, heightLL;
		boolean visit = false;
		while (u != nil && u != v.parent) {
			visit = false;
			if (prev == u.parent) {
				if (u.left != nil && u != v.parent){next = u.left;}
				else if (u.right != nil) {next = u.right;}
				else {next = u.parent;visit = true;}
				
			} else if (prev == u.left) {
				if (u.right != nil && u != v.parent){next = u.right;}
				else{next = u.parent;visit = true;}
				
			} else {next = u.parent;visit = true;}
			
			prev = u;
			if(visit){
				heightL = 0; heightR = 0;
				if(u.left != nil){heightL = sizeMap.get(u.left).getValue();} 
				if(u.right != nil){heightR = sizeMap.get(u.right).getValue();}
				
				//left case
				if(heightR + 1 < heightL){
					heightLR = 0;
					heightLL = 0;
					if(u.left != nil){
						if(u.left.right != nil){
							heightLR = sizeMap.get(u.left.right).getValue();
						}
						if(u.left.left != nil){
							heightLL = sizeMap.get(u.left.left).getValue();
						}
					}
					if(heightLL < heightLR){
						//left right case
						left(u.left, sizeMap, heightL, heightR);
					}
					// else
						// left left
					right(u, sizeMap, heightL, heightR);
					prev = nil;
					if(u.parent != nil){next = u.parent;
					} else {next = nil;}
				}
				// right case
				else if(heightL + 1 < heightR){
					heightRR = 0;
					heightRL = 0;
					if(u.right != nil){
						if(u.right.right != nil){
							heightRR = sizeMap.get(u.right.right).getValue();
						}
						if(u.right.left != nil){
							heightRL = sizeMap.get(u.right.left).getValue();
						}
					}
					if(heightRR < heightRL){
						//left right case
						right(u.right, sizeMap, heightL, heightR);
					} 
					//else
						//right right case
					left(u, sizeMap, heightL, heightR);
					prev = nil;
					if(u.parent != nil){next = u.parent;
					} else {next = nil;}
				} else {
					// default
					size = 1;
					if(u.left != nil){size += sizeMap.get(u.left).getKey();} 
					if(u.right != nil){size += sizeMap.get(u.right).getKey();}
					sizeMap.put(u, new SimpleEntry<>(size,1 + ((heightL > heightR) ? heightL : heightR)));
					u.timer = (int)Math.ceil(d * size);
				}
			}
			u = next;
		}
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
		
		/*
		CountdownTree<Integer> t = new CountdownTree<Integer>(2);
		t.add(1);
		t.add(2);
		t.add(3);
		t.add(4);
		t.add(5);
		t.add(6);
		t.add(7);
		t.add(8);
		t.add(9);
		System.out.println(t);
		t.traverse6(t.r,0,"");
		System.out.println("\nBreak");
		t.explode(t.r);
		//*/
	}
}
