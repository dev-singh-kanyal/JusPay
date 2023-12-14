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