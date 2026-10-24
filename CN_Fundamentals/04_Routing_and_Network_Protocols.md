# 04 — Routing & Network-Layer Protocols

## 1. Routing Basics ⭐
- **Router** keeps a **routing table**: destination network/prefix → next hop + interface + metric.
- **Longest prefix match:** if several entries match, use the one with the **longest (most specific) mask**. Example: 192.168.1.0/24 beats 192.168.0.0/16 for 192.168.1.5. **Default route 0.0.0.0/0** is used when nothing else matches.
- **Static routing:** manually configured (simple, no overhead, doesn't adapt). **Dynamic routing:** protocols learn routes automatically and adapt to failures.
- **Autonomous System (AS):** a network under one administrative control. **IGP** (inside an AS): RIP, OSPF, EIGRP. **EGP** (between ASes): **BGP**.

## 2. Routing Algorithms ⭐⭐
| | **Distance Vector** | **Link State** |
|--|--------------------|----------------|
| Algorithm | **Bellman-Ford** | **Dijkstra** |
| Knowledge | Only **neighbours' distance tables** ("routing by rumour") | **Complete topology map** |
| Information shared | **Whole routing table** with **neighbours only** | **Own link states** flooded to **all routers** |
| Updates | Periodic | Triggered on change |
| Convergence | Slow; **count-to-infinity problem** | Fast |
| Overhead | Low CPU/memory | High CPU/memory |
| Protocols | **RIP**, IGRP | **OSPF**, IS-IS |

### Distance Vector numerical
Dist(X→Y) = min over neighbours Z of [cost(X,Z) + Dist(Z→Y)]. Repeat until stable.

### Count-to-infinity & fixes ⭐
- **Problem:** when a link fails, routers keep increasing their distance to an unreachable destination (bad news travels slowly).
- **Fixes:** **Split horizon** (don't advertise a route back to the neighbour it came from), **Poison reverse** (advertise it with infinite metric), **hold-down timers**, **max hop count (RIP: 15; 16 = infinity)**.

### Dijkstra (link state)
Start at the source, repeatedly pick the unvisited node with the smallest tentative distance, and relax its neighbours. **O(V²)** (simple) or O(E log V) with a heap. Needs **non-negative weights.**

## 3. Routing Protocols ⭐⭐
| Protocol | Type | Metric | Notes |
|----------|------|--------|-------|
| **RIP** | Distance vector (IGP) | **Hop count**, max 15 | Updates every 30 s, UDP **port 520**. Simple, small networks |
| **OSPF** | Link state (IGP) | **Cost (bandwidth-based)** | Runs directly over IP (protocol 89), **areas** (hierarchical; Area 0 = backbone), fast convergence, uses **multicast** hellos, **Dijkstra** |
| **EIGRP** | Advanced distance vector (Cisco) | Composite (bandwidth, delay) | |
| **BGP** | **Path vector** (EGP) | **Path attributes / policies** (AS-PATH) | **TCP port 179.** Routes **between ASes**: the routing protocol of the Internet. Policy-based, not just shortest path |

**eBGP** (between ASes) vs **iBGP** (inside one AS).

## 4. ARP, RARP ⭐
- **ARP (Address Resolution Protocol):** maps **IP → MAC** on the same LAN.
  1. Host broadcasts an **ARP request** ("Who has 192.168.1.5? Tell 192.168.1.10").
  2. The owner replies with a **unicast ARP reply** containing its MAC.
  3. The result is cached in the **ARP table**.
  - **Only works within a LAN.** For a remote destination, the host ARPs for the **default gateway's MAC**, and the destination IP stays the same across hops while MAC addresses change hop-to-hop.
  - **ARP spoofing/poisoning:** attacker sends fake ARP replies → man-in-the-middle.
- **RARP:** MAC → IP (obsolete, replaced by BOOTP/DHCP). **Proxy ARP**: a router answers ARP on behalf of another host. **Gratuitous ARP:** announces own IP-MAC (duplicate IP detection).

**Key concept ⭐:** as a packet crosses routers, **source/destination IP stay the same** (unless NAT) and **source/destination MAC change at every hop.**

## 5. ICMP ⭐
**Internet Control Message Protocol**: error reporting and diagnostics for IP. Carried inside IP (protocol 1); **no ports**, not a transport protocol.
- **Echo request/reply → `ping`** (connectivity and RTT).
- **Time Exceeded → `traceroute`** (sends packets with TTL = 1, 2, 3… and reads each router's ICMP reply).
- **Destination Unreachable**, **Redirect**, **Source Quench** (deprecated), **Fragmentation Needed**.
- ICMP doesn't correct errors; it **only reports** them.

## 6. DHCP ⭐⭐
**Dynamic Host Configuration Protocol:** auto-assigns IP address, subnet mask, **default gateway**, **DNS server**, and a **lease time**. Runs over **UDP: server port 67, client port 68.**

**DORA process:**
1. **D**iscover (client broadcast)
2. **O**ffer (server proposes an IP)
3. **R**equest (client accepts/requests)
4. **A**cknowledge (server confirms and leases)
- Uses broadcast because the client has no IP yet (source 0.0.0.0, destination 255.255.255.255).
- **DHCP relay agent** forwards across subnets. **Lease renewal** at 50% (T1) of the lease time.
- If DHCP fails → **APIPA** 169.254.x.x.

## 7. NAT & PAT ⭐⭐
**Network Address Translation:** maps **private IPs ↔ public IP(s)** at the router, because of IPv4 shortage.
- **Static NAT:** 1 private ↔ 1 public. **Dynamic NAT:** pool of public IPs. **PAT / NAT overload:** **many private IPs share one public IP**, distinguished by **port numbers** (most common; home routers).
- **NAT table** maps (private IP:port) ↔ (public IP:port).
- **Pros:** conserves IPv4 addresses, hides internal structure (basic security). **Cons:** breaks end-to-end connectivity, complicates P2P/VoIP, adds processing delay, inbound connections need **port forwarding**.

## 8. Other Network-Layer Concepts
- **IGMP:** manages multicast group membership.
- **Congestion control at the network layer:** traffic shaping (**leaky bucket**: constant output rate; **token bucket**: allows bursts), load shedding, choke packets.
- **QoS:** prioritize traffic (VoIP).
- **MPLS:** label-based forwarding (between L2 and L3).
- **IP multicast**, **tunneling (GRE, IPsec)**, **SDN** (separates control plane and data plane).
- **Default gateway:** the router interface a host sends to for off-subnet destinations.

## 9. Common Interview Questions
1. Distance vector vs link state?
2. What is the count-to-infinity problem and how is it solved?
3. RIP vs OSPF vs BGP?
4. What is ARP? How does it work?
5. What is ICMP? How do ping and traceroute work?
6. Explain DHCP and DORA.
7. What is NAT / PAT? Pros/cons?
8. What is longest prefix match?
9. What changes and what stays the same in a packet as it crosses routers? (MAC changes; IP stays.)
10. What is an Autonomous System? IGP vs EGP?
11. What is a default route / default gateway?
12. Leaky bucket vs token bucket?

## MCQ Traps
- **RIP = distance vector, hop count, max 15; OSPF = link state, Dijkstra; BGP = path vector, TCP 179.**
- **DHCP uses UDP 67/68 and DORA.**
- **ARP works within a LAN, IP → MAC, uses broadcast request.**
- **ICMP has no port numbers; used by ping/traceroute.**
- **Split horizon / poison reverse fix count-to-infinity.**
- **IP addresses stay end-to-end; MAC changes per hop.**
- **PAT uses port numbers to let many hosts share one public IP.**
- **Longest prefix wins.**
- **Bellman-Ford → DV; Dijkstra → LS.**

## Practice MCQs
1. Protocol used to find the MAC for a known IP → **ARP**
2. Which protocol routes between autonomous systems? → **BGP**
3. RIP's maximum hop count → **15**
4. Third step of DHCP → **Request**
5. Router has 10.0.0.0/8 and 10.1.0.0/16; packet to 10.1.5.5 goes via → **10.1.0.0/16** (longest prefix)
