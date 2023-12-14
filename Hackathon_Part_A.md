# **Locking The Tree of Space**

You have a world map represented as an M-Ary tree (sample tree below)  

<aside>

<img src="./images/asterisk_green.svg" alt="asterisk_green.svg" width="15px" /> In graph theory, an m-ary tree (for nonnegative integers m) (also known as n-ary, k-ary or k-way tree) is an arborescence (or an ordered tree) in which each node has no more than m children. A binary tree is the special case where m = 2, and a ternary tree is another case with m = 3 that limits its children to three.

<img src="./images/asterisk_green.svg" alt="asterisk_green.svg" width="15px" /> In graph theory, an arborescence is a directed graph in which, for a vertex u (called the root) and any other vertex v, there is exactly one directed path from u to v. A graph is a collection of vertices (also known as nodes) and edges that connect these vertices. A tree is a special type of graph that is connected and acyclic, meaning that there are no cycles in the graph. In a tree, there is a unique path between any two vertices, and there is a single vertex called the root that is used as the starting point for traversing the tree. 

</aside>

![Sample Tree](./images/Sample%20Tree.png)

You need to define three operations on it:

```cpp
1. lock(X, uid)
2. unlock(X, uid)
3. upgradeLock(X, uid)
```

where `X` the name of a node in the tree (that would be unique) and `uid` is the user who is performing the operation.  
**Input format**: x is country name (string) and uid is user number (number).

**Here are the definitions for the operations:**

>**`lock(x, uid)`**  
Lock takes an exclusive access on the subtree rooted at `X`. It is formally defined like this: Once `lock(x, uid)` succeeds, then:  
    <li>`lock(A, anyUserid)` should fail (returns false), where `A` is a descendent of `X`,</li>
    <li>`lock(B, anyUserld)` should fail (returns false), where `X` is a descendent of `B`,</li>
    <li>Lock operation cannot be performed on a node which is already locked i.e. `lock(x, anyUserld)` should fail (returns false).</li>  
    <aside>
    <img src="./images/asterisk_green.svg" alt="asterisk_green.svg" width="15px" /> Exclusive access means that only one user can lock a node and its descendants at a time, and no other user can lock any node that is related to the locked node by ancestry or descent. This ensures that there is no conflict or interference between different users who want to perform operations on the tree.
    </aside> 

>**`unlock(X, uid)`**  
Unlock reverts what was done by the lock operation. It can only be called on same node on which user `uid` had called a Lock on before. Returns true if it is successful.

>**`upgradeLock(x, uid)`**  
It helps the user `uid` upgrade their lock to an ancestor node. It is only possible if the node `X` already has locked descendants and all of them are only locked by the same user `uid`. Upgrade should fail if there is any node which is descendant of X that is locked by a different user. Successful Upgrade will 'lock' the node. `upgradeLock` call shouldn't violate the consistency model that Lock/Unlock function requires.

**Notes**

1. The number of nodes in the tree `N` is very large. So, optimize the time complexity for the above algorithms.
2. The below section contains the input format.
    - The first line contains the **number** of Nodes in the tree (`N`).
    - The second line contains **number** of children per node (value `m` in m-ary Tree).
    - The third line contains **number** of queries (`Q`).
    - Next **`N`** lines contains the **`NodeName`** (string) in the m-Ary Tree.
    - Next **`Q`** lines contains queries which are in format: 
    **`Operation Type` `NodeName` `Userld`**
    - **Operation Type**
        
        `1` for lock  
        `2` for unlock  
        `3` for upgradeLock
        
    - **`NodeName`** - Name of any node (unique) in m-Ary Tree.
    - **`Userld`** - Integer value representing a unique user.

**Example input**

```cpp
7
2
3
World
Asia
Africa
China
India
South Africa
Egypt
1 China 9
2 India 9
3 Asia 9
```

With the above input you represent a 2-ary tree with 7 nodes as follows:

```
                 World
            /             \
        Asia               Africa
      /      \          /         \
China    India    South Africa   Egypt
```

**Additional Notes**

1. Here `1 China 3` indicates the following '`Operation Type` `NodeName` `Userld`'.
2. The tree is always fully balanced.
3. Constraints on the inputs are as follows:  
1 < **N** < 5 * 10^5  
1 < **m** < 30  
1 < **Q** <5 * 10^5  
1 < length of **NodeName** < 20
4. Optimize the time complexity:
    - Lock - O(logmN)
    - Unlock - O(logmN)
    - UpgradeLock - O(numberOfLockedNodes * logmN)
5. Lock operation on already locked node should fail.
6. Once Upgrade lock(X, uid) succeeds on X. It is equivalent to X being locked by uid. So, Lock(A/B, anyuser) should fail as per the definition of Lock and Unlock(X, uid) should also work.
7. Upgrade lock operation on a node having no locked descendants should fail and upgrade lock on already locked node should also fail.

**Example input**

```cpp
7
2
5
World
Asia
Africa
China
India
SouthAfrica
Egypt
1 China 9
1 India 9
3 Asia 9
2 India 9
2 Asia 9
```

**Example input**

```cpp
true
true
true
false
true
```

Query 1: `1 China 9` ⇒ This operation is success as initially China is unlocked. 

Query 2: `1 India 9` ⇒ This should be success as none of ancestors and descendants of India are locked.

Query 3: `3 Asia 9` ⇒ This also should be success as upgrade operation is done by same user who has locked descendants.

Query 4: `2 India 9` ⇒ This should fail as the India is now not locked 

Query 5: `2 Asia 9` ⇒ This should be success as Asia was earlier (refer Query 3) locked by user 9.
