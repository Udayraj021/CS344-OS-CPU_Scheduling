# CS344 Operating Systems Project

This project extends the **xv6 operating system** with custom CPU scheduling policies and memory-management features.

## Features

### 1. Lottery Scheduling

Implemented a Lottery Scheduler in xv6 where each runnable process is assigned a configurable number of tickets.

- Added a `tickets` field to the process structure.
- Added a `settickets()` system call.
- Modified the scheduler to select runnable processes probabilistically based on ticket count.
- Added runtime accounting to observe CPU usage.
- Added a user-level test program to verify proportional scheduling behavior.

**Location:**

```text
scheduling/lottery/
```

---

### 2. Shortest Job First Scheduling

Implemented **Shortest Job First (SJF)** scheduling using a configurable burst-time value for each process.

- Added a `burst_time` field to the process structure.
- Added a `setburst()` system call.
- Modified the scheduler to select the runnable process with the smallest burst time.
- Added a user-level test program to verify scheduling order.

**Location:**

```text
scheduling/sjf/
```

---

### 3. Lazy Memory Allocation

Implemented demand-based lazy memory allocation using page faults.

- Process virtual memory size is increased without immediately allocating physical pages.
- Physical memory is allocated only when the process first accesses the requested page.
- Page faults are handled through the xv6 trap and virtual-memory subsystem.
- Added per-process page-fault accounting.
- Added a test program that requests multiple pages and verifies that faults occur only for pages that are actually accessed.

**Location:**

```text
memory_management/lazy_allocation/
```

---

### 4. Copy-on-Write Fork

Implemented **Copy-on-Write (COW) fork** to avoid immediately copying all user memory when a process calls `fork()`.

- Parent and child initially share the same physical pages.
- Writable pages are marked read-only and tagged as Copy-on-Write.
- Added physical-page reference counting in the kernel memory allocator.
- A write to a shared COW page generates a page fault.
- The fault handler allocates a private page, copies the original contents, and remaps it as writable.
- Updated `copyout()` so kernel-to-user writes also correctly handle COW pages.
- Physical pages are freed only when their reference count becomes zero.
- Added a user-level test program to verify that child writes do not modify the parent's memory.
- Verified the implementation using the xv6 `usertests` suite.

**Location:**

```text
memory_management/copy_on_write/
```

---

## Additional System Calls and Process Metadata

The project adds support for retrieving and configuring process information, including:

- Process ID
- Process state
- Lottery ticket count
- Burst time
- CPU runtime
- Process creation time
- Page-fault count
- Process memory size
- Number of virtual pages

The following custom system calls are used:

```text
settickets()
setburst()
getprocinfo()
```

---

## Project Structure

```text
CS344-OS-project/
│
├── scheduling/
│   ├── lottery/
│   │   ├── kernel/
│   │   ├── user/
│   │   └── Makefile
│   │
│   └── sjf/
│       ├── kernel/
│       ├── user/
│       └── Makefile
│
└── memory_management/
    ├── lazy_allocation/
    │   ├── kernel/
    │   ├── user/
    │   └── Makefile
    │
    └── copy_on_write/
        ├── kernel/
        ├── user/
        └── Makefile
```

Each directory contains the files modified for that particular implementation.

---

## Implementation Overview

### Lottery Scheduler

For every scheduling decision:

```text
Find all RUNNABLE processes
        ↓
Calculate total number of tickets
        ↓
Generate a random winning ticket
        ↓
Find the process owning that ticket
        ↓
Run the selected process
```

### SJF Scheduler

For every scheduling decision:

```text
Find all RUNNABLE processes
        ↓
Compare their burst times
        ↓
Select minimum burst time
        ↓
Run selected process
```

### Lazy Allocation

```text
Process requests memory
        ↓
Increase virtual address-space size
        ↓
No physical page allocated yet
        ↓
Process accesses the page
        ↓
Page fault
        ↓
Allocate physical page
        ↓
Map page into process address space
        ↓
Resume execution
```

### Copy-on-Write Fork

```text
Process calls fork()
        ↓
Parent and child share physical pages
        ↓
Writable pages are marked COW and read-only
        ↓
Child or parent attempts to write
        ↓
Store page fault
        ↓
Allocate a new physical page
        ↓
Copy original page contents
        ↓
Remap faulting process to private writable page
        ↓
Decrease old page reference count
        ↓
Resume execution
```

---

## Testing

The following user programs were added for testing:

```text
procinfo
lotterytest
sjftest
lazytest
cowtest
```

### Lottery Scheduling

Lottery scheduling is best tested using a single CPU:

```bash
make CPUS=1 qemu
```

Inside xv6:

```text
lotterytest
```

### SJF Scheduling

SJF can similarly be tested using:

```text
sjftest
```

### Lazy Allocation

Lazy allocation and page-fault accounting can be tested using:

```text
lazytest
```

A successful lazy-allocation test demonstrates that requesting several pages does not immediately generate page faults, while accessing individual pages causes page faults only for those pages.

### Copy-on-Write

Copy-on-Write behavior can be tested using:

```text
cowtest
```

A successful COW test demonstrates that the child initially sees the parent's memory contents, but modifying the shared memory creates a private copy and leaves the parent's value unchanged.

The Copy-on-Write implementation was also tested using:

```text
usertests
```

with the full xv6 test suite passing successfully.

---

## Base System

The project is based on **MIT xv6 for RISC-V** and modifies its process scheduling, system-call, trap-handling, physical-memory allocation, and virtual-memory components for educational purposes.