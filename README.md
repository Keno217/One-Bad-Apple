# CIS 452 Operating Systems

## Project One: One Bad Apple

**Authors:** Kenan Velagic & Joshua Johnson

---

## Project Overview

The goal of this project is to design a circular communication system in which `k` processes form a ring. Each process (node), is connected to its direct neighbor, creating a loop where messages can circulate in one direction.

The project uses **process management** and **inter-process communication (IPC)** system calls (`fork`, `pipe`, `read`, `write`, `signal`) to implement the system.

---

## System Architecture

### 1. Ring Structure

- Parent process (node 0) spawns `k` child processes.
- Each node has a read pipe from the previous node and a write pipe to the next node.
- The last node wraps around to the parent, forming a circular ring.

---

### 2. Pipes

- A total of `k` pipes are created: `pipes[0]` to `pipes[k-1]`.
- Each pipe is used to send messages from one node to the next.
- Unused pipe ends are closed in each child to prevent unintended reads/writes and to ensure proper blocking behavior.

---

### 3. Process Flow

1. **Parent process**:

   - Prompts the user for the number of nodes `k`.
   - Creates `k` pipes.
   - Forks `k` child processes.
   - Gets user messages via `fgets` and sends them to the first node in the ring.

2. **Child process (Node i)**:

   - Closes all unused pipe ends.
   - Reads messages from the previous node via its pipe (blocking).
   - Checks if the message is intended for it:
     - If yes: processes and optionally prints it.
     - If no: forwards the message to the next node.
   - Sends the message to the next node via its write pipe.

3. **Message format**:

   - Contains a destination node ID and the message text, e.g., `"3:Hello World"`.

4. **Ring synchronization**:
   - Only the node that holds the “apple” can pass the message forward.
   - Pipes naturally enforce order, as `read()` is blocking until data arrives.

---

### 4. Graceful Shutdown

- The system handles **Control-C (SIGINT)** to allow the parent process to:
  - Signal all child processes to terminate.
  - Close all pipes.
  - Exit cleanly without leaving orphan processes.

---

### 5. Implementation Notes

- **Message handling**: Can support multiple-word messages.
- **No busy waiting**: `sleep` or no-op loops are avoided; pipes handle blocking.

---

### 6. Key System Calls

- `fork()` → create child processes.
- `pipe()` → create communication channels between processes.
- `read()` / `write()` → pass messages between nodes.
- `close()` → close unused pipe ends.
- `wait()` → parent waits for children to finish.
- `signal()` → handle graceful shutdown on Ctrl-C.

---

### 7. Example Flow

1. Parent asks for `k = 3` nodes.
2. Parent creates 3 pipes and forks 3 children.
3. Parent inputs message `"Hello"` to node 2: `"2:Hello"`.
4. Node 1 reads message → not for it → forwards to node 2.
5. Node 2 reads message → destination matches → prints it.
6. Node 2 forwards message to node 3 (or back to parent if last node).

---
