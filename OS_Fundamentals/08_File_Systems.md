# 08 — File Systems

## 1. File Concept
A **file** is a named collection of related information stored on secondary storage. It is the smallest unit of logical storage from the user's point of view.

**File attributes:** name, identifier (inode number), type, location, size, protection, timestamps (created, modified, accessed), owner.

**File operations:** create, open, read, write, seek (reposition), delete, truncate, close.

**Open-file table:** the OS keeps a **system-wide table** (file position, open count, disk location) plus a **per-process table** (file descriptors). In Linux, `0 = stdin`, `1 = stdout`, `2 = stderr`.

## 2. Access Methods
| Method | Description | Example |
|--------|-------------|---------|
| **Sequential** | Read in order, one record after another | Tape, log files, compilers |
| **Direct / Random** | Jump to any block directly | Databases |
| **Indexed** | An index points to blocks. Search the index, then access | ISAM, database indexes |

## 3. Directory Structures
| Structure | Description | Pros / Cons |
|-----------|-------------|-------------|
| **Single-level** | All files in one directory | Simple. Name collisions, no grouping |
| **Two-level** | A separate directory for each user (MFD → UFD) | Isolates users. No sharing or grouping |
| **Tree-structured** | Hierarchy of directories, with absolute/relative paths | Efficient grouping. Sharing is hard |
| **Acyclic graph** | Shared subdirectories/files via **links** | Sharing. Deletion is complicated (dangling pointers) |
| **General graph** | Cycles allowed | Needs garbage collection and cycle detection |

### Hard link vs Soft (symbolic) link ⭐
| Hard link | Soft link (symlink) |
|-----------|---------------------|
| Another directory entry pointing to the **same inode** | A separate file that stores the **path** of the target |
| Same inode number | Different inode |
| Deleting the original → data **still accessible** | Deleting the original → **dangling** link |
| Can't span file systems. Can't link directories | Can cross file systems and link directories |
| `ln file hlink` | `ln -s file slink` |

## 4. File System Structure (Layered)
```
Application programs
   ↓
Logical file system      (metadata, directories, FCB/inode, protection)
   ↓
File-organization module (logical → physical block, free-space manager)
   ↓
Basic file system        (generic block read/write, buffers, cache)
   ↓
I/O control              (device drivers, interrupt handlers)
   ↓
Devices
```
**On-disk structures:** boot control block (boot block), volume control block (**superblock** in Unix: number of blocks, block size, free counts), directory structure, and a per-file **FCB (File Control Block) = inode** in Unix.

## 5. Allocation Methods ⭐
How disk blocks are assigned to files.

### 5.1 Contiguous Allocation
- A file occupies consecutive blocks. The directory stores (start, length).
- ✅ Simple, **fast sequential and direct access**, minimal seeks.
- ❌ **External fragmentation**, and the file is hard to grow.
- Used by CD-ROMs.

### 5.2 Linked Allocation
- Each block contains a **pointer to the next block**. The directory stores the start and end.
- ✅ No external fragmentation, files grow easily.
- ❌ **Direct access is slow** (you must follow the chain), pointer overhead, and a broken pointer loses the rest of the file (poor reliability).
- **FAT (File Allocation Table):** a variant that keeps all the pointers in a table at the start of the disk (MS-DOS, USB drives). The table can be cached, which speeds up random access.

### 5.3 Indexed Allocation
- Each file has an **index block** containing pointers to all its data blocks.
- ✅ **Direct access** and no external fragmentation.
- ❌ Index block overhead (wasteful for small files), and the index block size limits the file size.
- For large files: linked index blocks, **multilevel index**, or a **combined scheme (Unix inode)**.

### Unix inode (combined scheme) ⭐
An inode contains the file metadata (**not the file name**; the name lives in the directory entry) plus:
- **12 direct pointers**
- **1 single indirect** → a block of pointers
- **1 double indirect** → pointers to pointer blocks
- **1 triple indirect**

**Max file size example:** block = 1 KB, pointer = 4 B → 256 pointers per block
= (12 + 256 + 256² + 256³) × 1 KB = (12 + 256 + 65,536 + 16,777,216) KB ≈ **16 GB**

| Method | Sequential access | Random access | External frag. | Grow file |
|--------|-------------------|---------------|----------------|-----------|
| Contiguous | ✅ Best | ✅ | ❌ Yes | ❌ Hard |
| Linked | ✅ | ❌ Slow | ✅ None | ✅ Easy |
| Indexed | ✅ | ✅ | ✅ None | ✅ Easy |

## 6. Free-Space Management
| Method | Idea | Note |
|--------|------|------|
| **Bit vector / bitmap** | 1 bit per block (in the usual convention 1 = free, 0 = allocated) | Easy to find contiguous free blocks. Must be kept in memory. Bitmap size = number of blocks / 8 bytes |
| **Linked list** | Free blocks linked together | No wasted space. Traversal is slow |
| **Grouping** | The first free block stores the addresses of n free blocks | Finds many free blocks quickly |
| **Counting** | Store (first free block, count of contiguous free blocks) | Good when free space is contiguous |

## 7. Directory Implementation
- **Linear list:** simple, but searching is O(n).
- **Hash table:** fast lookup. Must handle collisions.
- Modern systems use B-trees (NTFS, ext4 with htree, XFS, Btrfs).

## 8. Reliability & Performance
- **Buffer cache / page cache:** keeps disk blocks in memory.
- **Unified buffer cache:** a single cache for both file I/O and memory-mapped pages.
- **Consistency checking:** `fsck` (Unix), `chkdsk` (Windows).
- **Journaling (log-structured) file systems:** changes are written to a **journal** first as transactions, then applied. After a crash, the journal is replayed, so recovery is fast. Examples: **ext3/ext4, NTFS, XFS**.
- **Backup & restore:** full and incremental.

## 9. Common File Systems
| FS | OS | Notes |
|----|----|-------|
| FAT32 | Windows, USB | 4 GB max file size, simple |
| exFAT | USB drives, SD cards | Large files, no journaling |
| NTFS | Windows | Journaling, ACLs, compression, encryption |
| ext4 | Linux | Journaling, extents, up to 16 TB files |
| APFS | macOS, iOS | Copy-on-write, snapshots |
| XFS, Btrfs, ZFS | Linux/Unix | High performance, snapshots (Btrfs/ZFS are COW) |

## 10. Protection
- **Access types:** read, write, execute, append, delete, list.
- **Access Control List (ACL):** a per-file list of users and their permissions.
- **Unix permissions:** owner / group / others × r w x. `chmod 755 file` → rwxr-xr-x (7 = 4+2+1 = rwx, 5 = r-x).
- **Mounting:** attaching a file system at a **mount point** in the directory tree.

## 11. Common Interview Questions
1. What is an inode, and what does it contain? (Everything except the **file name**.)
2. Hard link vs soft link?
3. Contiguous vs linked vs indexed allocation, with pros and cons?
4. What is FAT?
5. How is free space managed? (Bitmap, linked list, and so on.)
6. What is journaling?
7. What does `chmod 644` mean? (rw-r--r--)
8. What happens when you delete a file that has a hard link? (The link count goes down. The data is freed only when the count reaches 0.)
9. Max file size calculation with inode pointers.

## MCQ Traps
- An inode **doesn't** store the file name.
- A hard link **can't** cross file systems or point to directories.
- Linked allocation → **no random access**.
- Contiguous allocation → **external fragmentation**.
- Bitmap size for a 1 TB disk with 4 KB blocks = 2⁴⁰/2¹² = 2²⁸ bits = **32 MB**.
