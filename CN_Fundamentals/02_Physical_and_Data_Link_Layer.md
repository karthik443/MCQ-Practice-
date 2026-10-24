# 02 — Data Link Layer (with a bit of Physical)

**Job of the Data Link Layer:** reliable **node-to-node** delivery over a link. Functions: **framing, physical (MAC) addressing, error detection/correction, flow control, access control.**

## 1. Framing
Splits the bit stream into **frames**.
- **Character/byte count**, **flag bytes with byte stuffing**, **flag bits with bit stuffing**.
- **Bit stuffing** (flag = `01111110`): after **five consecutive 1s**, the sender inserts a **0**. The receiver removes it.
  - Example: `011111110` → `0111110110` (a 0 is inserted after the first five 1s). This stops data from looking like the flag `01111110`.

## 2. Error Detection & Correction ⭐⭐
### Parity
- **Single parity bit** (even/odd). Detects **odd number of bit errors**; **fails for even number of errors**. Can't correct.
- **2D parity:** row + column parity; detects more and can **correct single-bit** errors.

### Checksum
Sum of data words, then complemented (1's complement). Used in **IP, TCP, UDP headers**. Receiver sums all, including the checksum → result all 1s = OK.

### CRC (Cyclic Redundancy Check) ⭐⭐⭐
Sender and receiver agree on a **generator polynomial G** of degree r (r+1 bits).
1. Append **r zeros** to the data.
2. **Divide** (modulo-2, i.e. XOR) by G. The **remainder** (r bits) is the CRC.
3. Transmit data + CRC. The receiver divides the whole frame by G: **remainder 0 → no error detected.**

**Example:** data = `1101011011`, G = `10011` (x⁴+x+1, r = 4).
Append 4 zeros: `11010110110000`. Dividing by 10011 (XOR steps) gives the remainder **`1110`** → transmit `11010110111110`.
- CRC detects **all single-bit errors, all burst errors ≤ r bits, all odd numbers of errors** (if G has factor x+1). Used in **Ethernet (CRC-32)**.
- Polynomial → bits: x³ + x + 1 → `1011`. Number of CRC bits = degree of G.

### Hamming Code ⭐⭐ (error correction)
- **Parity bits at positions that are powers of 2** (1, 2, 4, 8, …); data at the other positions.
- **Number of parity bits r for m data bits:** **2ʳ ≥ m + r + 1.** m = 4 → r = 3 (Hamming(7,4)). m = 8 → r = 4. m = 11 → r = 4.
- Each parity bit covers positions whose binary index has that bit set. On receipt, the **syndrome** (error position in binary) points to the bad bit, then flip it.
- **Hamming distance** = number of differing bit positions between two codewords. To **detect d errors: min distance ≥ d + 1**. To **correct t errors: min distance ≥ 2t + 1**.
  - Min distance 3 → detect 2 / correct 1.
  - Example: d(1011, 0110) = 3.

## 3. Flow Control & ARQ ⭐⭐⭐
**Flow control:** stop a fast sender from swamping a slow receiver.

### Stop-and-Wait
Send 1 frame, wait for ACK. Simple, **inefficient** on long links.
- **Efficiency (utilization) η = Tt / (Tt + 2Tp) = 1 / (1 + 2a)**, where **a = Tp/Tt**.
- **Throughput = η × bandwidth.**

### Sliding Window ⭐
Send multiple frames before needing ACKs. Window size = number of unacknowledged frames allowed.
- **Efficiency η = N / (1 + 2a)** (capped at 1), N = window size. **Max useful window: N = 1 + 2a.**
- **Sequence numbers:** with **m bits**, there are 2ᵐ sequence numbers.
  - **Go-Back-N:** sender window ≤ **2ᵐ − 1**, receiver window = **1**.
  - **Selective Repeat:** sender window = receiver window ≤ **2ᵐ⁻¹** (= 2ᵐ/2).
  - **Stop-and-Wait:** 1-bit sequence numbers (window 1).
- Min bits for sequence numbers: GBN: N ≤ 2ᵐ − 1 → m = ⌈log₂(N+1)⌉; SR: m = ⌈log₂(2N)⌉.

| | Go-Back-N | Selective Repeat |
|--|-----------|------------------|
| On error | **Retransmit the erroneous frame and all after it** | **Retransmit only the erroneous frame** |
| Receiver | Discards out-of-order frames, window = 1 | **Buffers** out-of-order frames |
| ACK | **Cumulative** | Individual |
| Complexity / buffer | Simple, small | Complex, larger |
| Bandwidth use | Wasteful on errors | Efficient |

**Numerical:** Tt = 1 ms, Tp = 49.5 ms → a = 49.5, 1 + 2a = 100. Stop-and-wait η = 1/100 = **1%**. Window 100 needed for **100%**.

### Piggybacking: attach the ACK to outgoing data frames.

## 4. Medium Access Control (MAC) ⭐⭐
For **shared** channels. Types: **channel partitioning** (TDMA, FDMA, CDMA), **random access** (ALOHA, CSMA), **taking turns** (polling, token passing).

### ALOHA
| | **Pure ALOHA** | **Slotted ALOHA** |
|--|---------------|-------------------|
| Transmit | Anytime | At slot boundaries |
| Vulnerable time | **2 × Tf** | **Tf** |
| Max efficiency | **1/(2e) ≈ 18.4%** (at G = 0.5) | **1/e ≈ 36.8%** (at G = 1) |
| Throughput S | G·e^(−2G) | G·e^(−G) |

### CSMA family ⭐
- **CSMA:** listen before transmitting (carrier sense).
- **CSMA/CD (Collision Detection)** — **wired Ethernet (half-duplex)**. Transmit, keep listening; on a collision send a **jam signal**, abort, and use **binary exponential backoff** (wait random 0 … 2ⁿ−1 slots).
  - **Condition to detect collisions: Tt ≥ 2·Tp** → **minimum frame size = 2 × Tp × bandwidth.** Min Ethernet frame = **64 bytes** (for 10 Mbps, 2.5 km).
- **CSMA/CA (Collision Avoidance)** — **Wi-Fi (802.11)**. Collisions can't be reliably detected in wireless. Uses **backoff + ACKs + optional RTS/CTS** (solves the **hidden terminal problem**).
- Persistence: 1-persistent, non-persistent, p-persistent.
- **Token ring:** a token circulates; only the holder transmits (no collisions).

**Numerical:** 10 Mbps, Tp = 25.6 µs → min frame = 2×25.6µs×10⁷ = **512 bits = 64 bytes.**

## 5. MAC Addresses & Ethernet ⭐
- **MAC address:** 48 bits (6 bytes), written in hex `00:1A:2B:3C:4D:5E`. First 3 bytes = **OUI (manufacturer)**; last 3 = device id. **Burned into the NIC, unique globally, flat (non-hierarchical)**. Broadcast MAC = `FF:FF:FF:FF:FF:FF`.
- **Ethernet frame (IEEE 802.3):** Preamble (7 B) + SFD (1 B) + **Dest MAC (6)** + **Src MAC (6)** + **EtherType/Length (2)** + **Payload (46–1500 B)** + **FCS/CRC (4)**.
  - **Min frame 64 B, max 1518 B** (excluding preamble). **MTU = 1500 B.** Payload < 46 gets padding.
- **Ethernet speeds:** 10BASE-T (10 Mbps), Fast Ethernet 100 Mbps, Gigabit 1 Gbps, 10 GbE.
- **Wi-Fi (802.11):** a/b/g/n/ac/ax. CSMA/CA. 2.4 GHz vs 5 GHz.

### Switch operation ⭐
- **Learning:** records (source MAC → port) in the **MAC address table (CAM)**.
- **Forwarding:** known destination → that port only. **Unknown unicast or broadcast → flood** to all ports except the incoming one. **Filtering:** same port → drop.
- **Spanning Tree Protocol (STP):** prevents **switching loops** in redundant topologies.
- **VLAN:** logically splits one switch into multiple broadcast domains. **802.1Q tagging.** Inter-VLAN traffic needs a router/L3 switch.
does CRC work? Why is it better than parity?

## 6. Other Data-Link Protocols
- **PPP:** point-to-point links (dial-up, DSL). **HDLC.** **ARP** (maps IP → MAC) lives between layers 2–3 (file 04).

## 7. Common Interview Questions
1. Functions of the data link layer?
2. How does CRC work? Why is it better than parity?
3. What is Hamming code? Hamming distance?
4. Stop-and-wait vs Go-Back-N vs Selective Repeat?
5. Explain CSMA/CD. Why is there a minimum frame size?
6. CSMA/CD vs CSMA/CA? Hidden terminal problem?
7. What is a MAC address? How does a switch learn addresses?
8. Pure vs slotted ALOHA efficiency?
9. What is bit stuffing?
10. What is VLAN? What is STP?
11. What is MTU?

## MCQ Traps
- **CRC:** remainder zero at the receiver = no error detected. Append **r zeros** (r = degree of G).
- **Parity can't detect an even number of bit errors.**
- **GBN receiver window = 1; SR window ≤ 2ᵐ⁻¹; GBN sender window ≤ 2ᵐ − 1.**
- **Slotted ALOHA efficiency = 36.8% (double pure ALOHA's 18.4%).**
- **Ethernet uses CSMA/CD (wired); Wi-Fi uses CSMA/CA.**
- **Collision detection requires Tt ≥ 2Tp.**
- **Ethernet min frame 64 B, max 1518 B, MTU 1500 B.**
- **Hamming: 2ʳ ≥ m + r + 1.**
- **Stop-and-wait efficiency = 1 / (1 + 2a).**

## Practice MCQs
1. Data 4 bits, Hamming code needs how many parity bits? → **3**
2. Min Hamming distance to correct 2 errors → **5**
3. Sequence number 3 bits; max GBN sender window → **7**; SR → **4**
4. Stop-and-wait: Tt = 1 ms, Tp = 4.5 ms → η = 1/(1+9) = **10%**
5. Slotted ALOHA max throughput → **36.8%**
