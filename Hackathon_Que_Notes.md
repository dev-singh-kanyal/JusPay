# Question Review

>The problem “Locking the Tree of Space” involves designing and implementing three operations on an M-Ary tree:

- **`lock(x, uid)`:** Grants exclusive access to the subtree rooted at `x` for user `uid`. Succeeds only if no ancestors or descendants of `x` are locked by any user.
- **`unlock(x, uid)`:** Reverts the lock on `x` by user `uid`. Succeeds only if `x` was previously locked by `uid`.
- **`upgradeLock(x, uid)`:** Upgrades a lock from a descendant of `x` to `x` itself for user `uid`. Succeeds only if:
    - `x` is not currently locked.
    - All locked descendants of `x` are locked by `uid`.
    - `x` has at least one locked descendant (if none, return `false`).

>**Assumptions:**

1. **Unique User IDs:** Each user has a unique identifier (`uid`) for distinction. And all user IDs in queries are valid.
2. **Valid Node Names:** All node names in queries are valid and exist in the tree.
3. **Synchronization:** The system handles concurrent operations to prevent race conditions.
4. **Error Handling:** The system handles operation failures; the system does not crash and instead returns a meaningful error message.
5. **Memory:** No memory limitations exist for storing the tree.
6. **Upgrade Restrictions:** Descendants are unlocked when their ancestor is upgraded. Upgrade fails if `x` has any locked ancestors.

>**Points to Remember:**

- Tree is fully balanced (each node has 0 or `m` children).
- Queries are formatted as `Operation_Type NodeName Userld` 
(1 for lock, 2 for unlock, 3 for upgrade).
- Expected time complexities:
    - lock/unlock: `O(logm(N))`
    - upgradeLock: `O(numberOfLockedNodes * logm(N))`
- Output: `true` for successful operations, `false` otherwise.

>**Use Cases:**

The problem “Locking The Tree of Space” can be applied in several real-world scenarios for JusPay, especially considering its role as a fintech company that deals with online payments. Here are some potential applications:

1. **Transaction Processing:** Ensure smooth concurrent processing of multiple transactions by locking relevant nodes (representing transaction stages) in the tree. This prevents data inconsistencies and accidental modifications.
2. **User Session Management:** Manage active user sessions and prevent resource conflicts by locking corresponding nodes in the tree. This ensures exclusive access to services and resources until the session ends.
3. **Resource Allocation:** Optimize resource allocation in cloud environments by locking nodes representing resources (CPU, memory, storage) when assigned to tasks. This prevents overbooking and ensures task completion without resource conflicts.
4. **Database Operations:** Maintain data integrity during concurrent database operations (updates, deletes) by locking relevant table nodes (Users, Orders, Items) in the tree. This serializes operations and prevents data corruption.
5. **Payment Gateway Integration:** Facilitate smooth payment processing through JusPay's integrated gateways by locking the chosen gateway node in the tree. This prevents concurrent access and ensures successful transaction completion on the chosen platform.
    
    >**a. Selection and Locking:**    
    >- When Customer A reaches the payment gateway selection step, the corresponding node in the tree (representing all available gateways) is locked.
    >- This prevents other customers from choosing any gateway until A makes their selection.
    >- Once A selects Visa, the specific Visa node within the tree is locked, granting A exclusive access to its processing resources.
    
    >**b. Concurrent Access Prevention:**    
    >- While A's transaction progresses through Visa's processing steps (e.g., authorization, settlement), the Visa node remains locked.
    >- This prevents other customers from choosing Visa during this period, ensuring A's transaction receives undivided attention from the gateway.
    
    >**c. Controlled Resource Allocation:**  
    >- Locking the Visa node also allocates necessary resources like processing power and network bandwidth specifically for A's transaction.
    >- This prevents resource overload from concurrent transactions on the same gateway, ensuring smooth and efficient processing for A.
    
    >**d. Unlock and Release:**
    >- Upon successful completion of A's transaction, both the general gateway node and the Visa node are unlocked.
    >- This releases the allocated resources and makes them available for other customers seeking to use Visa or any other gateway.
    
    >**Additional Benefits:**
    >- This locking mechanism minimizes the risk of conflicts or errors that might arise from concurrent transactions on the same gateway.
    >- It also improves overall system performance by preventing resource overload and ensuring efficient utilization of gateway resources.