# 03 — Network Layer: IP Addressing & Subnetting

## 1. Network Layer Functions
**Logical addressing (IP), routing, forwarding, fragmentation, congestion control.** Unit = **packet/datagram.** Delivers **host-to-host** across networks.
- **Forwarding** = moving a packet from an input port to the right output port (data plane, per router). **Routing** = deciding the path (control plane).
- IP is **connectionless, best-effort, unreliable** (no guarantee of delivery/order).

## 2. IPv4 Address ⭐⭐
**32 bits**, written as four octets in dotted decimal (`192.168.1.10`), each 0–255. Total = 2³² ≈ 4.29 billion addresses. **Hierarchical:** Network ID + Host ID.z

### Classful addressing ⭐⭐⭐
| Class | First octet range | Leading bits | Default mask | Network / Host bits | Hosts per net |
|-------|-------------------|:--:|--------------|:--:|--------------|
| **A** | 1 – 126 | 0 | 255.0.0.0 (/8) | 8 / 24 | 2²⁴ − 2 = 16,777,214 |
| **B** | 128 – 191 | 10 | 255.255.0.0 (/16) | 16 / 16 | 2¹⁶ − 2 = 65,534 |
| **C** | 192 – 223 | 110 | 255.255.255.0 (/24) | 24 / 8 | 2⁸ − 2 = 254 |
| **D** | 224 – 239 | 1110 | — | — | **Multicast** |
| **E** | 240 – 255 | 1111 | — | — | Reserved / experimental |

- **127.x.x.x = loopback** (127.0.0.1 = localhost). Excluded from Class A usable networks (so A: 1–126).
- **Number of networks:** A = 2⁷ − 2 = 126, B = 2¹⁴ = 16,384, C = 2²¹ = 2,097,152.
- **Hosts = 2^h − 2** (subtract **network address** (all host bits 0) and **broadcast address** (all host bits 1)).

### Special addresses ⭐
| Address | Meaning |
|---------|---------|
| Host bits all 0 | **Network address** |
| Host bits all 1 | **Directed broadcast** |
| **255.255.255.255** | **Limited broadcast** (local network) |
| **0.0.0.0** | "This host" / default route |
| **127.0.0.0/8** | Loopback |
| **169.254.0.0/16** | **APIPA** (link-local, when DHCP fails) |

### Private address ranges ⭐ (not routable on the Internet; need NAT)
- **10.0.0.0/8** (Class A), **172.16.0.0 – 172.31.255.255 (172.16.0.0/12)**, **192.168.0.0/16**.

## 3. Subnet Mask & CIDR ⭐⭐⭐
- **Subnet mask:** 1s for network+subnet bits, 0s for host bits. `255.255.255.0` = /24.
- **Network address = IP AND mask.** **Broadcast = network address with all host bits set to 1.** Usable hosts = **2^h − 2**; first host = network + 1; last host = broadcast − 1.
- **CIDR (Classless Inter-Domain Routing):** `a.b.c.d/n` (n = prefix length). Removes class boundaries; allows **variable-length subnet masks (VLSM)** and **route aggregation (supernetting)**.

### Mask ↔ prefix cheat table
| Prefix | Mask (last octet) | Block size (addresses) | Usable hosts |
|:--:|------|:--:|:--:|
| /24 | .0 | 256 | 254 |
| /25 | .128 | 128 | 126 |
| /26 | .192 | 64 | 62 |
| /27 | .224 | 32 | 30 |
| /28 | .240 | 16 | 14 |
| /29 | .248 | 8 | 6 |
| /30 | .252 | 4 | **2** (point-to-point links) |
| /31 | .254 | 2 | 2 (RFC 3021) |
| /32 | .255 | 1 | single host |

Octet values of mask bits: 128, 192, 224, 240, 248, 252, 254, 255.

### Worked Numericals ⭐⭐⭐
**1. Find network, broadcast, hosts of 192.168.10.77/26.**
- Block size = 64 (256 − 192). 77 lies in 64–127.
- **Network = 192.168.10.64**, **Broadcast = 192.168.10.127**, hosts **.65 – .126** → 62 usable.

**2. Subnet a Class C network 200.1.1.0/24 into 4 subnets.**
- Need 2 subnet bits → /26, mask 255.255.255.192, 62 hosts each.
- Subnets: 200.1.1.0, .64, .128, .192.
- **Subnets = 2^(borrowed bits)**; **hosts = 2^(host bits) − 2**.

**3. A company needs 500 hosts. What's the minimum prefix?** 2^h − 2 ≥ 500 → h = 9 (510) → **/23** (32 − 9).

**4. How many subnets/hosts: 172.16.0.0/20?** Class B, subnet bits = 20 − 16 = 4 → 16 subnets. Host bits = 12 → 4094 hosts each.

**5. Same network?** 192.168.1.130/25 and 192.168.1.200/25: block 128, .130 and .200 are both in 128–255 → **same network**.

**6. VLSM allocation:** Given 192.168.1.0/24 with needs 100, 50, 20 hosts → allocate largest first: 100 → /25 (126), 50 → /26 (62), 20 → /27 (30). Start addresses: .0/25, .128/26, .192/27.

**7. Supernetting (route aggregation):** 192.168.0.0/24 + 192.168.1.0/24 → **192.168.0.0/23**. Networks must be **contiguous** and the block must start on a proper boundary (size power of 2).

**8. Mask given by a count:** a /21 mask = 255.255.248.0.

## 4. IPv4 Datagram Header ⭐
Fields: **Version (4 b), IHL (4 b), ToS/DSCP, Total Length (16 b), Identification, Flags (DF, MF), Fragment Offset (13 b), TTL (8 b), Protocol (8 b: 6 = TCP, 17 = UDP, 1 = ICMP), Header Checksum, Source IP, Dest IP, Options.**
- **Header length:** min **20 bytes**, max **60 bytes** (IHL × 4; IHL 5–15). **Max packet size = 65,535 bytes.**
- **TTL:** decremented at each router; at 0 the packet is discarded and ICMP "Time Exceeded" is sent → **prevents infinite loops** (used by `traceroute`).
- **Header checksum** recomputed at each hop (because TTL changes).

### Fragmentation ⭐
- If packet > link **MTU**, the router splits it into **fragments** (reassembled **only at the destination**).
- Fragment offset is in units of **8 bytes.** **MF = 1** for all but the last fragment. **DF = 1** forbids fragmentation (Path MTU discovery).
- Each fragment has its own IP header (20 B). **Payload per fragment must be a multiple of 8 (except the last).**
- **Example:** 4000 B packet (20 B header + 3980 data), MTU 1500 → max data per fragment = 1480 (multiple of 8 ✔).
  - Frag 1: 1480 B data, offset 0, MF = 1
  - Frag 2: 1480 B data, offset 185 (1480/8), MF = 1
  - Frag 3: 1020 B data, offset 370, MF = 0
  (1480 + 1480 + 1020 = 3980 ✔)

## 5. IPv6 ⭐
- **128-bit** addresses (2¹²⁸), written in **8 groups of 4 hex digits** separated by colons: `2001:0db8:0000:0000:0000:ff00:0042:8329` → compressed `2001:db8::ff00:42:8329` (`::` only **once**; leading zeros dropped).
- **Fixed 40-byte header**, **no header checksum**, **no fragmentation by routers** (only the source), **no broadcast** (uses multicast/anycast), **built-in IPSec** support, **auto-configuration (SLAAC)**, no need for NAT.
- **Loopback:** `::1`. **Link-local:** `fe80::/10`.
- **Transition:** dual stack, tunneling (6in4), translation (NAT64).

| IPv4 | IPv6 |
|------|------|
| 32-bit | 128-bit |
| Variable header (20–60 B) | Fixed 40 B |
| Checksum in header | None |
| Fragmentation at routers | Only at the source |
| ARP | NDP (Neighbor Discovery) |
| Broadcast | No broadcast |

## 6. Common Interview Questions
1. IPv4 address classes and ranges?
2. What is subnetting? Why do we do it?
3. What is CIDR? VLSM? Supernetting?
4. Find the network, broadcast, and host range for a given IP/mask.
5. Private vs public IP? Which ranges?
6. IPv4 vs IPv6?
7. What is TTL and why is it needed?
8. What is fragmentation? Who reassembles?
9. Why 2^h − 2 hosts?
10. What is the loopback address? What is APIPA?
11. Forwarding vs routing?
12. What is the default gateway?

## MCQ Traps
- **Usable hosts = 2^h − 2; subnets = 2^(borrowed bits).**
- **Class A first octet: 1–126 (127 = loopback). B: 128–191. C: 192–223. D (multicast): 224–239.**
- **Private ranges:** 10/8, 172.16/12 (**172.16–172.31**), 192.168/16.
- **Network address = IP AND mask.**
- **Fragment offset is in 8-byte units; reassembly at destination only.**
- **IPv4 header min 20 B (IHL = 5), max 60 B.**
- **Protocol field: 6 = TCP, 17 = UDP, 1 = ICMP.**
- **IPv6 has no broadcast, no header checksum, routers don't fragment.**
- **/30 gives 2 usable hosts.**
- **Default mask: A /8, B /16, C /24.**

## Practice MCQs
1. 10.5.6.7 belongs to Class → **A**
2. Usable hosts in a /27 → **30**
3. Network address of 172.16.35.100/20 → third octet: 35 AND 240 = 32 → **172.16.32.0**
4. Number of subnets if a /24 is split with mask /27 → **8**
5. Which field prevents infinite looping? → **TTL**
