# 08 — Quick Revision (Read this right before the interview)

## A. One-line definitions
| Term | One-liner |
|------|-----------|
| OSI model | 7-layer reference model: Physical, Data Link, Network, Transport, Session, Presentation, Application |
| TCP/IP | 4-layer practical model: Link, Internet, Transport, Application |
| Hub / Switch / Router | L1 broadcast repeater / L2 MAC-based forwarder / L3 IP-based router |
| Collision domain | Devices whose frames can collide (each switch port is one) |
| Broadcast domain | Devices that receive a broadcast (each router port is one) |
| MAC address | 48-bit hardware address, hop-to-hop |
| IP address | Logical address, end-to-end (IPv4 = 32-bit, IPv6 = 128-bit) |
| Port | 16-bit process identifier; socket = IP + port |
| Subnetting | Dividing a network into smaller subnets |
| CIDR | Classless addressing `a.b.c.d/n` |
| NAT / PAT | Translate private ↔ public IPs (PAT uses ports) |
| ARP | IP → MAC (LAN) |
| DHCP | Auto-assigns IP config (DORA; UDP 67/68) |
| DNS | Name → IP (UDP 53) |
| ICMP | Error/diagnostic messages (ping, traceroute) |
| TCP | Reliable, ordered, connection-oriented byte stream |
| UDP | Fast, connectionless, unreliable datagrams |
| 3-way handshake | SYN → SYN+ACK → ACK |
| Flow control | Receiver protects itself (rwnd) |
| Congestion control | Sender protects the network (cwnd) |
| HTTP | Stateless request–response app protocol |
| HTTPS | HTTP over TLS (443) |
| TLS | Encrypts, authenticates, protects integrity |
| CRC | Polynomial-division error-detection code |
| Hamming code | Single-bit error correction (parity at powers of 2) |
| CSMA/CD | Ethernet collision detection (wired) |
| CSMA/CA | Wi-Fi collision avoidance |
| RIP / OSPF / BGP | DV hop count / link state / path vector between ASes |
| VPN | Encrypted tunnel over a public network |
| CDN | Edge caches close to users |
| Load balancer | Spreads requests across servers |

## B. Formulas cheat sheet
| What | Formula |
|------|---------|
| Transmission delay | Tt = L / R |
| Propagation delay | Tp = d / speed |
| RTT | ≈ 2 × Tp |
| Bandwidth-delay product | Bandwidth × RTT |
| a | Tp / Tt |
| Stop-and-wait efficiency | 1 / (1 + 2a) |
| Sliding window efficiency | min(1, N / (1 + 2a)) |
| Optimal window | 1 + 2a |
| GBN sender window | ≤ 2ᵐ − 1 (receiver 1) |
| SR window | ≤ 2ᵐ⁻¹ each |
| Min frame size (CSMA/CD) | 2 × Tp × bandwidth |
| Pure / slotted ALOHA max | 18.4% / 36.8% |
| Nyquist | 2 · B · log₂ L |
| Shannon | B · log₂(1 + SNR) |
| SNR (dB) | 10 log₁₀ SNR |
| Hamming parity bits | 2ʳ ≥ m + r + 1 |
| Detect d / correct t errors | dmin ≥ d + 1 / dmin ≥ 2t + 1 |
| Full mesh links | n(n − 1)/2 |
| Usable hosts | 2^h − 2 |
| Subnets | 2^(borrowed bits) |
| Network address | IP AND mask |
| IPv4 header | 20–60 B |
| Fragment offset | In units of 8 bytes |
| TCP effective window | min(rwnd, cwnd) |
| Slow start | cwnd doubles per RTT |
| Ethernet frame | 64–1518 B; MTU 1500 |
| MSS | MTU − 40 = 1460 |

## C. "Which one…?" quick answers
- Device connecting different networks → **Router**
- Device forwarding by MAC → **Switch**
- Reliable delivery → **TCP**; low latency streaming / DNS → **UDP**
- IP → MAC → **ARP**; name → IP → **DNS**; auto IP → **DHCP**
- ping / traceroute → **ICMP**
- Routing between ASes → **BGP**; shortest path link state → **OSPF**; hop count → **RIP**
- Wired Ethernet access → **CSMA/CD**; Wi-Fi → **CSMA/CA**
- Error correction (1 bit) → **Hamming**; detection in frames → **CRC**
- Retransmit only the bad frame → **Selective Repeat**
- Fix count-to-infinity → **Split horizon / poison reverse**
- Share one public IP → **PAT/NAT**
- Secure web → **HTTPS/TLS**; secure remote login → **SSH**
- Send mail → **SMTP**; fetch mail (synced) → **IMAP**; fetch & delete → **POP3**
- Alias record → **CNAME**; mail record → **MX**; reverse lookup → **PTR**
- Stateless HTTP state → **Cookies / sessions / JWT**
- Private key used to → **Sign / decrypt**; public key used to → **Verify / encrypt**
- Protects servers, balances load → **Reverse proxy / load balancer**
- Cached static content near users → **CDN**

## D. Ports & status codes (must memorize)
**Ports:** HTTP 80 · HTTPS 443 · FTP 20/21 · SSH 22 · Telnet 23 · SMTP 25 · DNS 53 · DHCP 67/68 · TFTP 69 · POP3 110 · IMAP 143 · SNMP 161 · RDP 3389 · MySQL 3306
**HTTP:** 200 OK · 201 Created · 301 Moved · 302 Found · 304 Not Modified · 400 Bad Request · 401 Unauthorized · 403 Forbidden · 404 Not Found · 500 Server Error · 502 Bad Gateway · 503 Unavailable

## E. Top 50 interview questions (answer out loud)
**Models & devices**
1. OSI layers and what each does?
2. OSI vs TCP/IP?
3. Hub vs switch vs router? Collision vs broadcast domain?
4. PDUs and encapsulation?
5. Circuit vs packet switching?
6. Network topologies?

**Data link**
7. Functions of the data link layer?
8. CRC, parity, checksum, Hamming?
9. Stop-and-wait vs GBN vs SR?
10. CSMA/CD vs CSMA/CA; ALOHA?
11. MAC address; how a switch learns?
12. VLAN / STP?

**Network layer**
13. IPv4 classes; private ranges?
14. Subnetting a network (numerical)?
15. CIDR, VLSM, supernetting?
16. IPv4 vs IPv6?
17. Fragmentation; TTL; MTU?
18. Distance vector vs link state?
19. Count-to-infinity and fixes?
20. RIP vs OSPF vs BGP?
21. ARP; DHCP (DORA); ICMP (ping/traceroute)?
22. NAT/PAT, pros & cons?
23. What changes at each hop: IP or MAC?

**Transport**
24. TCP vs UDP?
25. 3-way handshake and 4-way close; TIME_WAIT?
26. Flow vs congestion control?
27. Slow start, congestion avoidance, fast retransmit/recovery?
28. How does TCP ensure reliability?
29. Port vs socket?
30. SYN flood?
31. Why does DNS use UDP?

**Application**
32. What happens when you type a URL?
33. HTTP vs HTTPS; HTTP/1.1 vs 2 vs 3?
34. GET vs POST vs PUT; idempotency?
35. Status codes (401 vs 403, 301 vs 302)?
36. Cookies vs sessions vs JWT?
37. DNS hierarchy, resolution, record types?
38. SMTP vs POP3 vs IMAP?
39. FTP control/data connections?
40. REST principles?
41. WebSocket vs HTTP?

**Security & infra**
42. Symmetric vs asymmetric; how HTTPS uses both?
43. TLS handshake; digital certificate; CA?
44. Hashing vs encryption; password storage?
45. Firewall, VPN, proxy (forward vs reverse)?
46. DoS/DDoS, MITM, ARP/DNS spoofing?
47. SQL injection, XSS, CSRF?
48. Load balancer algorithms; CDN?
49. CORS / same-origin policy?
50. A request from a browser to a server behind a load balancer. Trace it end to end.

## F. Last-minute traps checklist
- [ ] Router L3, switch L2, hub L1; **switch port = collision domain; router port = broadcast domain**
- [ ] PDUs: data → segment → packet → frame → bits
- [ ] Hosts = 2^h − 2; class A 1–126; private 172.16–172.31
- [ ] Network = IP AND mask; /30 = 2 hosts
- [ ] IP stays, MAC changes per hop
- [ ] TCP 20 B header; UDP 8 B; both use ports; ICMP has none
- [ ] ACK number = next byte expected
- [ ] Timeout → cwnd = 1; 3 dup ACKs → cwnd = ssthresh
- [ ] DNS/DHCP/VoIP on UDP; HTTP/FTP/SMTP on TCP
- [ ] GBN window ≤ 2ᵐ − 1; SR ≤ 2ᵐ⁻¹
- [ ] Ethernet = CD, Wi-Fi = CA; min frame 64 B
- [ ] 401 ≠ 403; PUT idempotent, POST not
- [ ] DES obsolete, AES standard; hash ≠ encryption
- [ ] BGP on TCP 179; RIP max 15 hops
