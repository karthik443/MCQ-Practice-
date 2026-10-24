# 05 — Transport Layer: TCP & UDP

**Job:** **end-to-end (process-to-process)** communication. Uses **port numbers**, **segmentation & reassembly**, **multiplexing/demultiplexing**, and (TCP) **reliability, flow control, congestion control.**

## 1. Ports & Sockets ⭐
- **Port:** 16-bit number (0–65535) identifying a process. **IP identifies the host; port identifies the application.**
- **Well-known: 0–1023** (system), **registered: 1024–49151**, **dynamic/ephemeral: 49152–65535**.
- **Socket = IP address + port.** A connection is identified by the **4-tuple/5-tuple**: (src IP, src port, dst IP, dst port [, protocol]).
- **Multiplexing:** many apps share the network through ports. **Demultiplexing:** deliver to the right socket.

## 2. TCP vs UDP ⭐⭐⭐
| | **TCP** | **UDP** |
|--|---------|---------|
| Connection | **Connection-oriented** (handshake) | **Connectionless** |
| Reliability | **Reliable** (ACKs, retransmission, ordering) | Unreliable (best effort) |
| Ordering | In-order delivery | No guarantee |
| Flow / congestion control | **Yes** | **No** |
| Speed / overhead | Slower; header **20–60 B** | Faster; header **8 B** |
| Data unit | Byte stream (segments) | Datagrams with message boundaries |
| Broadcast / multicast | No (point-to-point only) | **Yes** |
| Use cases | **HTTP/HTTPS, FTP, SMTP, SSH, email, file transfer** | **DNS, DHCP, VoIP, video streaming, online games, TFTP, SNMP** |

### UDP header (8 bytes) ⭐
Source port (2) + Dest port (2) + Length (2) + Checksum (2). **Checksum optional in IPv4.**

### TCP header (20–60 bytes) ⭐
Source port, Dest port, **Sequence number (32 b)**, **Acknowledgement number (32 b)**, **Header length (4 b, units of 4 bytes)**, **Flags: URG, ACK, PSH, RST, SYN, FIN**, **Window size (16 b)**, Checksum, Urgent pointer, Options.
- **Sequence number** = byte number of the first data byte in the segment. **ACK number** = next byte the receiver **expects**.
- **Header length field:** 5 to 15 (×4) → 20–60 B. **Max window = 65,535 B** (more with window scaling).
- **Checksum** covers a pseudo-header + TCP header + data.

## 3. TCP Connection Establishment — 3-Way Handshake ⭐⭐⭐
1. **Client → Server: SYN** (seq = x)
2. **Server → Client: SYN + ACK** (seq = y, ack = x + 1)
3. **Client → Server: ACK** (ack = y + 1) → **ESTABLISHED**

- **Why 3-way?** Both sides must confirm they can **send and receive**, and **synchronize initial sequence numbers (ISNs)**. It also protects against old duplicate connection requests.
- **SYN consumes one sequence number.** Pure ACKs don't.
- **SYN flood attack:** attacker sends many SYNs and never completes the handshake → exhausts the server's half-open connection queue. Mitigation: **SYN cookies**, rate limiting.

## 4. TCP Connection Termination — 4-Way ⭐⭐
1. Client → **FIN**
2. Server → **ACK** (server may still send data: **half-close**)
3. Server → **FIN**
4. Client → **ACK** → client waits in **TIME_WAIT (2 × MSL)** then closes.
- **TIME_WAIT:** ensures the last ACK arrived and that delayed old segments die out.
- **RST** flag: abruptly resets/aborts a connection.

### TCP states (recall the main ones)
CLOSED → LISTEN → SYN_SENT / SYN_RCVD → **ESTABLISHED** → FIN_WAIT_1 → FIN_WAIT_2 → TIME_WAIT → CLOSED; CLOSE_WAIT, LAST_ACK on the passive side.

## 5. Reliability in TCP ⭐
- **Sequence numbers + cumulative ACKs** (ACK n = "received everything up to n−1, send n next").
- **Retransmission** on **timeout (RTO)**, computed from estimated **RTT**; or on **3 duplicate ACKs → fast retransmit** (without waiting for the timeout).
- **Checksum** for errors. **Out-of-order segments** buffered and reordered.
- TCP uses **Go-Back-N-like cumulative ACKs plus selective ACK (SACK)** option → selective-repeat-like behaviour.

## 6. Flow Control ⭐⭐
Prevents the **sender from overwhelming the receiver.** Uses the **sliding window** with the **receiver window (rwnd)** advertised in every ACK.
- Sender's unacknowledged data ≤ **rwnd**. If rwnd = 0 → sender stops and sends **zero-window probes**.
- **Effective window = min(rwnd, cwnd).**
- **Silly window syndrome:** tiny window updates cause tiny segments → fix with **Nagle's algorithm** (sender) and **Clark's** solution (receiver).

**Throughput bound:** throughput ≤ window size / RTT. **Efficiency = W / (1 + 2a)** for window W (in packets).

## 7. Congestion Control ⭐⭐⭐
Prevents the **network** from being overloaded. The sender maintains **cwnd (congestion window)**.

**Phases (TCP Reno/Tahoe):**
1. **Slow Start:** cwnd starts at **1 MSS**, **doubles every RTT** (+1 MSS per ACK) → **exponential growth**, until cwnd reaches **ssthresh**.
2. **Congestion Avoidance:** cwnd increases by **1 MSS per RTT** → **linear (AIMD: additive increase)**.
3. **On loss:**
   - **Timeout (severe):** ssthresh = cwnd/2, **cwnd = 1 MSS**, restart slow start (**Tahoe** does this for all losses).
   - **3 duplicate ACKs (mild), Reno:** ssthresh = cwnd/2, **cwnd = ssthresh**, **fast recovery**, then linear growth.
- **AIMD:** Additive Increase, Multiplicative Decrease (halve on loss).

**Numerical:** ssthresh = 16, cwnd: 1 → 2 → 4 → 8 → 16 (slow start, doubling) → 17 → 18 … (linear). Timeout at cwnd = 20 → **ssthresh = 10, cwnd = 1**.
Initial ssthresh is often 64 KB. (Some texts start ssthresh at the receiver window.)

- **Modern variants:** CUBIC (Linux default), BBR (Google; model-based), Vegas. **ECN** (explicit congestion notification). **QUIC** (runs on UDP, used by HTTP/3; faster setup, avoids head-of-line blocking).
- **Flow control = receiver-driven (end-to-end); congestion control = network-driven (sender infers).**

## 8. Other TCP Concepts
- **MSS** (Maximum Segment Size) negotiated in SYN = MTU − 40 (IP + TCP headers) = **1460 B** for Ethernet.
- **Nagle's algorithm:** buffers small packets to reduce overhead (disable with TCP_NODELAY for latency-sensitive apps).
- **Keep-alive**, **window scaling**, **timestamps**, **TCP Fast Open**.
- **Sequence number wrap-around:** 32 bits = 4 GB; time to wrap depends on the rate.
- **Head-of-line blocking:** one lost segment delays later data.
- **Max bytes before wrap** = 2³².
- **Socket programming:** server: `socket() → bind() → listen() → accept() → recv()/send() → close()`. Client: `socket() → connect() → send()/recv() → close()`. UDP: `socket() → bind() → recvfrom()/sendto()` (no listen/accept/connect needed).
- **Reliable data transfer over UDP:** build at the application layer (e.g. QUIC).

## 9. TCP vs UDP — when to choose
- **TCP:** correctness matters (web pages, file transfer, email, banking).
- **UDP:** speed/low latency matters and loss is tolerable (live video, VoIP, gaming), or small request-response (DNS), or broadcast/multicast.

## 10. Common Interview Questions
1. TCP vs UDP? Examples of each?
2. Explain the 3-way handshake. Why three steps, not two?
3. Explain connection termination. What is TIME_WAIT?
4. Flow control vs congestion control?
5. Explain slow start, congestion avoidance, fast retransmit, fast recovery.
6. What happens on a timeout vs 3 duplicate ACKs?
7. How does TCP ensure reliability?
8. What is a socket? What's the difference between a port and a socket?
9. What is a SYN flood?
10. Why does DNS use UDP? (Small, single request/response; low overhead.)
11. What is QUIC/HTTP3?
12. TCP header fields; sequence and ACK numbers?
13. Is UDP really "unreliable"? (No delivery guarantee; apps add their own logic.)

## MCQ Traps
- **TCP: reliable, ordered, connection-oriented, 20 B min header. UDP: 8 B header, connectionless.**
- **3-way handshake: SYN → SYN+ACK → ACK.** ACK number = seq + 1 for SYN.
- **DNS, DHCP, VoIP, streaming → UDP. HTTP, FTP, SMTP, SSH → TCP.**
- **Flow control → receiver window (rwnd); congestion control → cwnd.**
- **Slow start is exponential; congestion avoidance is linear.**
- **Timeout → cwnd = 1; 3 dup-ACKs (Reno) → cwnd = ssthresh (halved).**
- **Sending window = min(rwnd, cwnd).**
- **ACK number = next expected byte.**
- **Well-known ports: 0–1023.**
- **Port identifies a process; socket = IP + port.**
- **TCP doesn't support broadcast/multicast.**
- **TIME_WAIT = 2 × MSL.**

## Practice MCQs
1. Which protocol uses a 3-way handshake? → **TCP**
2. UDP header size → **8 bytes**
3. cwnd = 8 MSS in slow start → after one RTT → **16 MSS**
4. Loss by timeout at cwnd = 32: new ssthresh and cwnd → **16 and 1**
5. Server sends SYN+ACK with seq = 500; client ACK number is → **501**
