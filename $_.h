/*
	2406 Assignement 5
	Patrick Shipton 
	101046328
	06/12/2017
*/
HashMap<Node<T>,Integer> sizeMap = new HashMap<Node<T>,Integer>();
		HashMap<Node<T>,Integer> heightMap = new HashMap<Node<T>,Integer>();
		//System.out.println("\n\nExplode " + v.x);
		
		//traverse6(r,0,"");
		
		Node<T> u = v, prev = v.parent, next;
		int size, sizeTemp, sizeL, sizeR;
		int height, heightTemp, heightR, heightL, heightLR, heightRL, heightRR, heightLL;
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
				//System.out.println("Special: " + u.x + " prev: " + prev.x);
				if(u.left != nil){
					heightL = heightMap.get(u.left);
				} 
				if(u.right != nil){
					heightR = heightMap.get(u.right);
				}
				
				//System.out.println("sizes L" + sizeL + " S" + size + " R" + sizeR);
				//System.out.println("heights L" + heightL + " R" + heightR);
				//System.out.println("height: " + height + " [" + size + "]");
				
				//left case
				if(heightR + 1 < heightL){
					//System.out.println("rotateRight " + (heightR+1) + " < " + heightL);
					heightLR = 0;
					heightLL = 0;
					if(u.left != nil){
						if(u.left.right != nil){
							heightLR = heightMap.get(u.left.right);
						}
						if(u.left.left != nil){
							heightLL = heightMap.get(u.left.left);
						}
					}
					if(heightLL < heightLR){
						//left right case
						//System.out.println("left right case " + (heightLL) + " < " + heightLR);
						left(u.left, sizeMap, heightMap, heightL, heightR);
					}
					// else
						// left left
						//System.out.println("left left case " + (heightLL) + " < " + heightLR);
					right(u, sizeMap, heightMap, heightL, heightR);
					prev = nil;
					if(u.parent != nil){
						next = u.parent;
					} else {
						next = nil;
					}
				}
				// right case
				else if(heightL + 1 < heightR){
					//System.out.println("rotateLeft " + (heightL+1) + " < " + heightR);
					heightRR = 0;
					heightRL = 0;
					if(u.right != nil){
						if(u.right.right != nil){
							heightRR = heightMap.get(u.right.right);
						}
						if(u.right.left != nil){
							heightRL = heightMap.get(u.right.left);
						}
					}
					if(heightRR < heightRL){
						//left right case
						//System.out.println("right left case " + (heightRR) + " < " + heightRL);
						right(u.right, sizeMap, heightMap, heightL, heightR);
					} 
					//else
						//right right case
						//System.out.println("right right case " + (heightRR) + " < " + heightRL);
					left(u, sizeMap, heightMap, heightL, heightR);
					prev = nil;
					if(u.parent != nil){
						next = u.parent;
					} else {
						next = nil;
					}
				} else {
					size = 1;
					if(u.left != nil){size += sizeMap.get(u.left);} 
					if(u.right != nil){size += sizeMap.get(u.right);}
					height = 1 + Math.max(heightL,heightR);
					sizeMap.put(u, size);
					heightMap.put(u, height);
					u.timer = (int)Math.ceil(d * size);
				}
				//System.out.println("u.x: " + u.x + "[" + size + "] next " + next.x);
				//System.out.println("u.x: " + u.x + "[" + sizeMap.get(u) + "] height " + heightMap.get(u));
				//traverse6(r,0,"");
				//System.out.println("");
			}
			//System.out.println("u.x: " + u.x + " next " + next.x);
			u = next;
		}









Lheight = 1;
				Lsize = 1 + sizeL;
				if(u.left.right != nil){
					if(u.left.right.left != nil){
						Lsize += sizeMap.get(u.left.right.left);
					}
					LsizeTemp = sizeMap.get(u.left.right) + 1 + sizeMap.get(u.left.left);
					sizeMap.put(u.left.right, sizeTemp);
					u.left.right.timer = (int)Math.ceil(d * sizeTemp);
				}
				Lheight += Math.max(heightLL, heightMap.get(u.left.right.left));
				rotateLeft(u.left);
				sizeMap.put(u.left, size);
				heightMap.put(u.left, height);
				u.left.timer = (int)Math.ceil(d * size);
				traverse6(r,0,"");


System.out.println("rotateLeft " + (heightL+1) + " < " + heightR);
					size = 1 + sizeL;
					height = 1;
					heightRL = 0;
					heightRR = 0;
					if(u.right != nil){
						if(u.right.left != nil){
							size += sizeMap.get(u.right.left);
							heightRL = heightMap.get(u.right.left);
						}
						if(u.right.right != nil){
							heightRR = heightMap.get(u.right.right);
						}
						if(heightRR < heightRL){
							//left right case
							System.out.println("right left case " + (heightRR+1) + " < " + heightRL);
							rotateRight(u.right);
						} else {
							//right right case
							System.out.println("right right case " + (heightRR+1) + " < " + heightRL);
						}
						sizeTemp = sizeMap.get(u.right) + 1 + sizeL;
						heightTemp = 1 + Math.max(heightRL, heightL);
						sizeMap.put(u.right, sizeTemp);
						heightMap.put(u.right, heightTemp);
						u.right.timer = (int)Math.ceil(d * sizeTemp);
					}
					height += Math.max(heightL, heightRL);
					rotateLeft(u);
					traverse6(r,0,"");
					prev = nil;
					if(u.parent != nil){
						next = u.parent;
					} else {
						next = nil;
					}





	
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
	
	
	
	
	
	
	
	
	if(v.parent != nil){
			System.out.println("v.parent = " + v.parent.x);
			
		}
		
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
				if(2*size < (3*sizeL) + 1){
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
					
					
				} else if(2*size < (3*sizeR) + 1){
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
				System.out.println("sizes L" + sizeL + " S" + size + " R" + sizeR);
				if(2*size <= 3*sizeL){
					System.out.println("rotateRight " + 2*size + " < " + 3*sizeL);
					sizeTemp = 1 + sizeR;
					if(u.left != nil){
						if(u.left.right != nil){
							sizeTemp += sizeMap.get(u.left.right);
						}
					}
					sizeMap.put(u, sizeTemp);
					u.timer = (int)Math.ceil(d * sizeTemp);
					size = sizeMap.get(u.left) + 1 + sizeL;
					rotateRight(u);
					traverse6(r,0,"");
					prev = u;
					next = u.parent;
					
					
				} else if(2*size <= 3*sizeR){
					System.out.println("rotateLeft " + 2*size + " < " + 3*sizeR);
					sizeTemp = 1 + sizeL;
					if(u.right != nil){
						if(u.right.left != nil){
							sizeTemp += sizeMap.get(u.right.left);
						}
					}
					sizeMap.put(u, sizeTemp);
					u.timer = (int)Math.ceil(d * sizeTemp);
					size = sizeMap.get(u.right) + 1 + sizeL;
					rotateLeft(u);
					traverse6(r,0,"");
					prev = u.parent.left;
					next = u.parent;
				}
				sizeMap.put(u, size);
				u.timer = (int)Math.ceil(d * size);
				System.out.println("u.x: " + u.x + "[" + size + "]");
				//traverse6(r,0,"");
				System.out.println("");
			}