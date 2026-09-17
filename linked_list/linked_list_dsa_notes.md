# Linked List — DSA Notes

## 1. Node Structure

```cpp
struct Node {
    int data;
    Node* next;
};
```

A `Node*` stores the **address of a Node**.

```cpp
Node* head = new Node();
```

`head` contains the address of the newly created node.

### `->`

```cpp
head->data
head->next
```

means: go to the Node pointed to by `head` and access its member.

---

## 2. Pointer Passed by Value vs Reference

If we have:

```cpp
void func(Node* head)
```

the pointer itself is passed **by value**.

The copied pointer still points to the same Node, so this works:

```cpp
head->data = 10;
```

But this does **not** change the caller's pointer:

```cpp
head = someOtherNode;
```

To modify the caller's pointer, use:

```cpp
Node*& head
```

Example:

```cpp
void changeHead(Node*& head) {
    head = head->next;
}
```

### Rule

- Modify the **Node** → `Node*` is enough.
- Modify the **pointer itself** → use `Node*&`.

---

# 3. Traversal

```cpp
Node* tmp = head;

while (tmp != NULL) {
    cout << tmp->data << endl;
    tmp = tmp->next;
}
```

Time: **O(n)**  
Extra space: **O(1)**

---

# 4. Insertion

## Insert Before

Basic pointer idea:

```text
prev → current
```

Create:

```cpp
Node* tmp = new Node();
tmp->data = data;
```

Then:

```cpp
tmp->next = current;
prev->next = tmp;
```

If inserting before `head`, `head` itself must change:

```cpp
tmp->next = head;
head = tmp;
```

Therefore the function generally needs:

```cpp
void insertBefore(Node*& head, Node* current, int data);
```

---

## Insert After

Given:

```text
current → next
```

Do:

```cpp
tmp->next = current->next;
current->next = tmp;
```

The important rule:

> Save the existing link before overwriting it.

---

# 5. Deletion

## Delete Head

```cpp
Node* tmp = head;
head = head->next;
delete tmp;
```

Order matters:

1. Save old head.
2. Move head.
3. Delete old head.

---

## Delete a Middle/Last Node

Given:

```text
prev → current → next
```

Do:

```cpp
prev->next = current->next;
delete current;
```

Think:

> **Bypass the node, then delete it.**

You need `prev` because you must modify the previous node's `next`.

---

## Delete by Value

Typical structure:

```cpp
void deleteValue(Node*& head, int value) {

    if (head == NULL)
        return;

    if (head->data == value) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
        return;
    }

    Node* prev = NULL;
    Node* current = head;

    while (current != NULL && current->data != value) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        cout << "element not found.";
        return;
    }

    prev->next = current->next;
    delete current;
}
```

Important edge cases:

- Empty list
- Target is head
- Target is in middle
- Target is last
- Target does not exist

---

# 6. Search

```cpp
Node* search(Node* head, int value) {

    Node* current = head;

    while (current != NULL) {
        if (current->data == value)
            return current;

        current = current->next;
    }

    return NULL;
}
```

Complexity:

- Best case: **O(1)**
- Average case: **O(n)**
- Worst case: **O(n)**
- Space: **O(1)**

A normal singly linked list does not support O(1) random access, so searching requires traversal.

---

# 7. Length

```cpp
int length(Node* head) {

    int count = 0;

    while (head != NULL) {
        count++;
        head = head->next;
    }

    return count;
}
```

Complexity:

- Time: **O(n)**
- Space: **O(1)**

If a linked-list class maintains a `size` variable and updates it on every insertion/deletion, retrieving the size can be **O(1)**.

---

# 8. Reverse Linked List ⭐

Given:

```text
1 → 2 → 3 → 4 → NULL
```

Want:

```text
4 → 3 → 2 → 1 → NULL
```

Use three pointers:

```cpp
void reverse(Node*& head) {

    Node* prev = NULL;
    Node* current = head;
    Node* next;

    while (current != NULL) {

        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev;
}
```

The four key operations are:

```cpp
next = current->next;  // save
current->next = prev;  // reverse
prev = current;        // move prev
current = next;        // move current
```

Finally:

```cpp
head = prev;
```

Complexity:

- Time: **O(n)**
- Space: **O(1)**

---

# 9. Find Middle — Fast & Slow Pointers ⭐

Use:

```cpp
Node* slow = head;
Node* fast = head;

while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
}

return slow;
```

`slow` moves 1 step.

`fast` moves 2 steps.

When `fast` reaches the end, `slow` is at the middle.

For an even-length list, this standard version returns the **second middle**.

Complexity:

- Time: **O(n)**
- Space: **O(1)**

---

# 10. Detect Cycle — Floyd's Algorithm ⭐

Example:

```text
1 → 2 → 3 → 4
        ↑     ↓
        └─────┘
```

Use:

```cpp
bool find_cycle(Node* head) {

    Node* slow = head;
    Node* fast = head;

    while (fast != NULL && fast->next != NULL) {

        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return true;
    }

    return false;
}
```

Why compare pointers?

```cpp
slow == fast
```

means both point to the **same Node object**.

Don't compare `data`, because different nodes can contain the same value.

Complexity:

- Time: **O(n)**
- Space: **O(1)**

---

# 11. Find Start of Cycle ⭐

Important distinction:

> The point where `slow` and `fast` meet is NOT necessarily the start of the cycle.

### Phase 1 — Detect cycle

Find the meeting point.

### Phase 2 — Find cycle entry

After they meet:

```cpp
slow = head;

while (slow != fast) {
    slow = slow->next;
    fast = fast->next;
}
```

Now:

```cpp
slow == fast
```

and this node is the **start of the cycle**.

Complete implementation:

```cpp
Node* start_of_cycle(Node* head) {

    Node* slow = head;
    Node* fast = head;

    // Phase 1: detect cycle
    while (fast != NULL && fast->next != NULL) {

        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            break;
    }

    // No cycle
    if (fast == NULL || fast->next == NULL)
        return NULL;

    // Phase 2: find cycle start
    slow = head;

    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}
```

Complexity:

- Time: **O(n)**
- Space: **O(1)**

---

# 12. Length of a Cycle

If only the cycle length is required, you do **not necessarily need to find the cycle start**.

After Floyd's algorithm finds a meeting point:

```cpp
int count = 1;
Node* curr = slow->next;

while (curr != slow) {
    count++;
    curr = curr->next;
}
```

The number of nodes visited before returning to `slow` is the cycle length.

Alternatively, if the problem requires the cycle start too:

1. Detect cycle.
2. Find cycle start.
3. Traverse from cycle start until returning to it.

Using `do-while`:

```cpp
Node* curr = cycleStart;
int length = 0;

do {
    curr = curr->next;
    length++;
} while (curr != cycleStart);
```

---

# 13. Delete Middle Node ⭐

Combine:

- Fast/slow pointers → find middle
- `prev` → delete it

```cpp
Node* deleteMiddle(Node* head) {

    if (head == NULL || head->next == NULL) {
        delete head;
        return NULL;
    }

    Node* prev = NULL;
    Node* slow = head;
    Node* fast = head;

    while (fast != NULL && fast->next != NULL) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    prev->next = slow->next;
    delete slow;

    return head;
}
```

For:

```text
1 → 2 → 3 → 4 → 5
```

`slow` ends at `3` and `prev` at `2`.

Then:

```cpp
prev->next = slow->next;
delete slow;
```

gives:

```text
1 → 2 → 4 → 5
```

---

# 14. Important Pointer Patterns So Far

### Pattern 1 — Delete a node

```cpp
prev->next = current->next;
delete current;
```

### Pattern 2 — Reverse

```cpp
next = current->next;
current->next = prev;
prev = current;
current = next;
```

### Pattern 3 — Fast/slow

```cpp
slow = slow->next;
fast = fast->next->next;
```

Used for:

- Middle
- Cycle detection
- Cycle start
- Other two-pointer problems

### Pattern 4 — Modify head

If a function needs to change the caller's head:

```cpp
Node*& head
```

---

# 15. Complexity Summary

| Operation | Time | Extra Space |
|---|---:|---:|
| Traverse | O(n) | O(1) |
| Search | O(n) | O(1) |
| Length | O(n) | O(1) |
| Insert at head | O(1) | O(1) |
| Insert after known node | O(1) | O(1) |
| Insert before known node* | O(n) | O(1) |
| Delete head | O(1) | O(1) |
| Delete known node* | O(n) | O(1) |
| Reverse | O(n) | O(1) |
| Find middle | O(n) | O(1) |
| Detect cycle | O(n) | O(1) |
| Find cycle start | O(n) | O(1) |

`*` assumes only `head` and the target node are given. If you already have the previous node, insertion/deletion can be O(1).

---

# 16. Next Problems

You are currently at:

## Remove N-th Node From End ⭐

Example:

```text
1 → 2 → 3 → 4 → 5 → NULL
```

`n = 2`

Result:

```text
1 → 2 → 3 → 5 → NULL
```

Requirement:

- One traversal
- O(n) time
- O(1) extra space

Hint:

Use two pointers:

```cpp
Node* fast = head;
Node* slow = head;
```

Maintain a gap of `n` nodes between them.

After this, continue with:

1. Merge Two Sorted Linked Lists
2. Palindrome Linked List
3. Intersection of Two Linked Lists
4. Reorder Linked List
5. Doubly Linked List
6. Circular Linked List
