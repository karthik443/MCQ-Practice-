# 01 — Network Basics & Reference Models

## 1. What is a Computer Network?
Two or more devices connected to **share resources and communicate**. Components: nodes (hosts), links (wired/wireless), protocols, and intermediary devices.

### Types by size ⭐
| Type | Area | Example |
|------|------|---------|
| **PAN** | Personal (~1–10 m) | Bluetooth |
| **LAN** | Building / campus | Office Ethernet, Wi-Fi |
| **MAN** | City | Cable TV network |
| **WAN** | Country / global | **The Internet**, leased lines |

### Transmission modes
- **Simplex:** one direction only (keyboard, TV broadcast).
- **Half-duplex:** both directions, **not simultaneously** (walkie-talkie, hub-based Ethernet).
- **Full-duplex:** both simultaneously (telephone, switched Ethernet).

### Cast types
**Unicast** (1→1), **Multicast** (1→group), **Broadcast** (1→all in a network), **Anycast** (1→nearest of a group; IPv6/CDN).

### Client–Server vs Peer-to-Peer
- **Client–server:** dedicated server provides services (web). **P2P:** every node is both client and server (BitTorrent).

## 2. Topologies ⭐
| Topology | Description | Pros | Cons |
|----------|-------------|------|------|
| **Bus** | Single shared cable | Cheap | One cable failure kills all, collisions |
| **Star** | All nodes to a central hub/switch | Easy to manage; one node failure doesn't matter | **Central device = single point of failure** |
| **Ring** | Nodes form a closed loop | Orderly access | One break can break the ring |
| **Mesh** | Every node linked to every other | Very reliable | Costly. **Links in full mesh = n(n−1)/2; ports per node = n−1** |
| **Tree** | Hierarchy of stars | Scalable | Root dependent |
| **Hybrid** | Combination | Flexible | Complex |

**Example:** 6 nodes full mesh → 6×5/2 = **15 links**.
**Star is the most common LAN topology today.**

## 3. Network Devices ⭐⭐ (by layer)
| Device | OSI Layer | Function |
|--------|:--:|----------|
| **Repeater** | 1 | Regenerates/amplifies signals |
| **Hub** | 1 | Multi-port repeater; **broadcasts to all ports**. **One collision domain + one broadcast domain** |
| **Bridge** | 2 | Connects LAN segments; filters by MAC |
| **Switch** | 2 | Multi-port bridge. Forwards frames **by MAC address** to the right port. **Each port = its own collision domain**; all ports share one broadcast domain (unless VLANs) |
| **Router** | 3 | Forwards packets by **IP**; connects different networks. **Each port = separate broadcast domain** |
| **Layer-3 switch** | 2+3 | Switching + routing |
| **Gateway** | up to 7 | Connects different protocols/architectures (protocol translation) |
| **Access Point** | 1–2 | Wi-Fi to wired |
| **Modem** | 1 | Modulates/demodulates signals |
| **Firewall** | 3–7 | Filters traffic by rules |

- **Collision domain:** set of devices whose frames can collide. **Broadcast domain:** set of devices that receive a broadcast.
- Switch: N ports → N collision domains, 1 broadcast domain. Router: each interface = 1 broadcast domain.

## 4. OSI Model ⭐⭐⭐ (7 layers)
Mnemonic (top→bottom): **A**ll **P**eople **S**eem **T**o **N**eed **D**ata **P**rocessing.
| # | Layer | Function | PDU | Protocols / devices |
|---|-------|----------|-----|--------------------|
| 7 | **Application** | User services / APIs | Data | HTTP, FTP, SMTP, DNS, SSH, Telnet |
| 6 | **Presentation** | **Translation, encryption, compression** (format, e.g. ASCII, JPEG, SSL) | Data | SSL/TLS (conceptually), JPEG, MPEG |
| 5 | **Session** | Establish, manage, terminate sessions; **synchronization/checkpoints** | Data | NetBIOS, RPC |
| 4 | **Transport** | **End-to-end** delivery, **segmentation, flow + error control, port addressing** | **Segment** (TCP) / **Datagram** (UDP) | TCP, UDP |
| 3 | **Network** | **Logical (IP) addressing, routing**, path selection | **Packet** | IP, ICMP, ARP*, OSPF; **Router** |
| 2 | **Data Link** | Node-to-node delivery, **framing, MAC addressing, error detection, flow control, access control** | **Frame** | Ethernet, PPP, HDLC; **Switch, bridge** |
| 1 | **Physical** | **Bits** over medium: voltage, cables, rates | **Bit** | Cables, hub, repeater |

- **Data flows down with headers added (encapsulation) on the sender; up with headers stripped (decapsulation) on the receiver.**
- **Hop-to-hop:** layers 1–3 (physical, data link, network). **End-to-end:** layers 4–7.
- **Addresses:** data link = **MAC** (physical), network = **IP** (logical), transport = **port**, application = URL/email.
- **Layers in a router: 1–3. In a switch: 1–2. In a hub: 1.**
- *ARP sits between layers 2 and 3.

## 5. TCP/IP Model ⭐⭐
| TCP/IP layer | OSI layers | Examples |
|--------------|------------|----------|
| **Application** | 5, 6, 7 | HTTP, FTP, SMTP, DNS |
| **Transport** | 4 | TCP, UDP |
| **Internet** | 3 | IP, ICMP, ARP |
| **Network Access (Link)** | 1, 2 | Ethernet, Wi-Fi |

| OSI | TCP/IP |
|-----|--------|
| 7 layers | 4 layers (some texts: 5) |
| Theoretical reference | **Practical, actually used** |
| Protocol-independent | Protocol-specific |
| Clear service/interface/protocol separation | Less strict |

## 6. Switching Techniques ⭐
| | **Circuit switching** | **Packet switching** | **Message switching** |
|--|----------------------|----------------------|------|
| Path | Dedicated path reserved before transfer | Packets take independent routes (datagram) or a virtual circuit | Whole message stored and forwarded |
| Delay | Setup delay, then constant | Variable | High |
| Bandwidth use | Wasteful (idle while silent) | **Efficient** | |
| Example | Old telephone network | **Internet** | Email (store-and-forward) |

- **Datagram** packet switching: no setup, each packet routed independently (may reorder; IP). **Virtual circuit:** setup route first, packets carry a VC id (ATM, MPLS).

## 7. Delay & Performance ⭐ (numericals)
- **Transmission delay** = L / R (packet length / bandwidth). Time to push bits onto the link.
- **Propagation delay** = d / s (distance / signal speed, ~2×10⁸ m/s in cable).
- **Queuing delay**, **Processing delay.**
- **Total (nodal) delay** = processing + queuing + transmission + propagation.
- **RTT** = 2 × propagation delay (+ others).
- **Bandwidth** = capacity (bps). **Throughput** = actual rate achieved. **Latency** = delay. **Jitter** = variation in delay.
- **Bandwidth-delay product** = bandwidth × RTT (or one-way delay) = bits "in flight" on the link.

**Example:** 1000-byte packet on a 1 Mbps link: Tt = 8000 / 10⁶ = **8 ms**. Distance 2000 km at 2×10⁸ m/s: Tp = 2×10⁶ / 2×10⁸ = **10 ms**.

**Units:** 1 byte = 8 bits. Network speeds use **K = 10³**, storage often 2¹⁰.

## 8. Transmission Media
- **Guided:** twisted pair (UTP/STP; Cat5/6), **coaxial**, **fiber optic** (highest bandwidth, immune to EMI, long distance; single-mode vs multi-mode).
- **Unguided:** radio, microwave, satellite, infrared.
- **Attenuation** (signal weakening), **noise**, **distortion**.
- **Nyquist (noiseless):** max bit rate = **2·B·log₂(L)** (B = bandwidth Hz, L = signal levels). **Shannon (noisy):** capacity = **B·log₂(1 + SNR)**.
  - Example: B = 3 kHz, 4 levels → 2×3000×2 = **12 kbps**. SNR = 1023, B = 1 kHz → 1000×log₂(1024) = **10 kbps**.
  - **SNR(dB) = 10·log₁₀(SNR).** 30 dB → SNR = 1000.
- **Encoding:** NRZ, Manchester (self-clocking; used in classic Ethernet), etc.

## 9. Common Interview Questions
1. What are the layers of the OSI model? What does each do?
2. OSI vs TCP/IP?
3. Hub vs switch vs router?
4. What are a collision domain and a broadcast domain?
5. Topologies with pros/cons?
6. Circuit vs packet switching?
7. What is encapsulation? What are PDUs at each layer?
8. LAN vs WAN? What is the Internet?
9. Bandwidth vs throughput vs latency?
10. Unicast vs multicast vs broadcast?

## MCQ Traps
- **Router = Layer 3; switch = Layer 2; hub = Layer 1.**
- **Switch: each port is a separate collision domain, but one broadcast domain.**
- **Hub: one collision domain, one broadcast domain.**
- **PDUs: Data → Segment → Packet → Frame → Bits.**
- **Transport = end-to-end; Data link = hop-to-hop.**
- **Encryption/compression belong to the Presentation layer (OSI).**
- **TCP/IP is the practical model; OSI is the reference model.**
- **Full mesh links = n(n−1)/2.**
- **Internet uses packet switching.**

## Practice MCQs
1. Which layer does routing? → **Network**
2. PDU of the Data Link layer → **Frame**
3. A 10-port switch has how many collision domains? → **10**
4. Full mesh of 8 nodes → **28 links**
5. SNR 1000, B = 2 kHz. Shannon capacity ≈ → 2000 × log₂(1001) ≈ **20 kbps**
