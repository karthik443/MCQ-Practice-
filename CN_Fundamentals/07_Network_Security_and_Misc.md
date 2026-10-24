# 07 — Network Security & Miscellaneous

## 1. Security Goals (CIA + more) ⭐
- **Confidentiality:** only authorized parties read the data (encryption).
- **Integrity:** data isn't altered (hashes, MACs, signatures).
- **Availability:** services remain accessible (DDoS protection).
- **Authentication:** who are you? **Authorization:** what can you do? **Non-repudiation:** can't deny an action (digital signature).

## 2. Cryptography Basics ⭐⭐
| | **Symmetric** | **Asymmetric (public-key)** |
|--|---------------|-----------------------------|
| Keys | **One shared secret key** | **Key pair: public + private** |
| Speed | **Fast** | Slow |
| Key distribution | Hard (how to share the key securely?) | Easy (public key is public) |
| Use | **Bulk data encryption** | Key exchange, signatures, certificates |
| Algorithms | **AES** (current standard), DES (weak, 56-bit), 3DES, ChaCha20 | **RSA**, ECC, Diffie-Hellman (key exchange), DSA |

- **Encrypt with the recipient's public key → only their private key decrypts** (confidentiality).
- **Sign with your private key → anyone verifies with your public key** (authenticity + non-repudiation).
- **Hash function:** fixed-size digest, **one-way**, collision-resistant, avalanche effect. **SHA-256** (secure), **MD5/SHA-1** (broken for security). Used for integrity and password storage (**salted**, use bcrypt/Argon2).
- **Digital signature** = hash of the message encrypted with the sender's private key.
- **Digital certificate (X.509):** binds an identity to a public key, signed by a **Certificate Authority (CA)**. **PKI** = CA + certificates + trust chain.
- **HMAC:** hash + secret key for message integrity/authentication.
- **Block vs stream ciphers**; **modes** (ECB is insecure: same plaintext → same ciphertext; CBC, GCM).
- **Hybrid approach (real world):** use asymmetric crypto to exchange a **session key**, then **symmetric** for data (TLS).
- **Diffie–Hellman:** two parties derive a shared secret over an insecure channel (vulnerable to MITM without authentication).
- **RSA:** based on the difficulty of factoring large primes. n = p·q; public (e, n); private d. Encryption C = Mᵉ mod n, decryption M = Cᵈ mod n.
  - **Tiny example:** p = 3, q = 11 → n = 33, φ = 20, e = 3, d = 7 (3×7 = 21 ≡ 1 mod 20). M = 4 → C = 4³ mod 33 = 64 mod 33 = **31**. Decrypt: 31⁷ mod 33 = **4**.

## 3. SSL/TLS & HTTPS ⭐⭐
**TLS (Transport Layer Security)** (successor of SSL) secures communication above TCP. **HTTPS = HTTP + TLS (port 443).**
- Provides **confidentiality (encryption), integrity (MAC), server authentication (certificate)**.

**Simplified TLS handshake:**
1. **ClientHello** — supported versions, cipher suites, random.
2. **ServerHello** + **server certificate** (contains its public key, signed by a CA).
3. Client **verifies the certificate** (CA chain, domain, expiry, revocation).
4. **Key exchange** (ECDHE / RSA) → both derive a shared **session key**.
5. **Finished** messages → the rest of the traffic is encrypted with **symmetric** encryption (AES).
- **TLS 1.3**: 1-RTT handshake, removes weak ciphers, forward secrecy mandatory.
- **Forward secrecy:** compromise of long-term keys doesn't reveal past sessions.
- **Certificate errors:** expired, untrusted CA, hostname mismatch.

## 4. Firewalls, VPN, Proxies, IDS ⭐
| | Description |
|--|-------------|
| **Firewall** | Filters traffic by rules. **Packet filter** (L3/L4: IP, port, protocol), **stateful** (tracks connections), **application-layer / proxy / WAF** (L7: inspects HTTP), **NGFW** (deep inspection). **DMZ:** a zone for public-facing servers |
| **VPN** | **Encrypted tunnel** over a public network (IPSec, OpenVPN, WireGuard, SSL VPN) → privacy and remote access |
| **Proxy** | **Forward proxy:** represents **clients** (filtering, anonymity, caching). **Reverse proxy:** represents **servers** (load balancing, TLS termination, caching, protection) — Nginx, HAProxy |
| **IDS** | Detects suspicious activity (alerts). **IPS** blocks it |
| **IPSec** | Network-layer security (AH, ESP; transport/tunnel modes) |
| **SSH** | Encrypted remote access, tunnelling |
| **WPA2/WPA3** | Wi-Fi security (WEP is broken) |

## 5. Common Attacks & Defences ⭐⭐
| Attack | What | Defence |
|--------|------|---------|
| **Phishing** | Fake messages steal credentials | Awareness, MFA, email filters |
| **Man-in-the-Middle (MITM)** | Attacker intercepts/alters traffic | TLS, certificate validation, HSTS |
| **DoS / DDoS** | Flood a service to make it unavailable | Rate limiting, CDN/scrubbing, anycast, SYN cookies |
| **SYN flood** | Half-open TCP connections | SYN cookies |
| **ARP spoofing** | Fake ARP replies | Dynamic ARP inspection, static ARP |
| **DNS spoofing / cache poisoning** | Fake DNS answers | DNSSEC, DoH/DoT |
| **IP spoofing** | Forged source IP | Ingress filtering |
| **Sniffing** | Capture packets (Wireshark) | Encryption |
| **SQL injection** | Inject SQL via input | Prepared statements, validation |
| **XSS (Cross-Site Scripting)** | Inject script into pages seen by others | Output encoding, CSP, HttpOnly cookies |
| **CSRF** | Trick a logged-in user's browser into sending a request | CSRF tokens, SameSite cookies |
| **Brute force / credential stuffing** | Guess passwords | Rate limits, lockout, MFA, strong hashing |
| **Replay attack** | Re-send captured valid messages | Nonces, timestamps |
| **Ransomware / malware / worm / trojan** | Malicious software | AV, patching, backups |
| **Zero-day** | Exploit of an unknown flaw | Defence in depth, patching |
| **Port scanning** | Discover open ports (nmap) | Firewall, IDS |

- **Authentication factors:** something you **know** (password), **have** (OTP/token), **are** (biometric). **MFA** = 2+ factors.
- **OAuth 2.0:** delegated **authorization** (access tokens). **OpenID Connect:** authentication on top. **SSO**, **JWT**. **Principle of least privilege.** **Defence in depth.**
- **Same-Origin Policy and CORS:** browsers restrict cross-origin requests; the server opts in via `Access-Control-Allow-Origin`.

## 6. Web Infrastructure ⭐
- **Load balancer:** distributes requests across servers (**round robin, least connections, IP hash, weighted**). **L4** (TCP/UDP) vs **L7** (HTTP-aware). Gives **scalability, availability, health checks**. **Sticky sessions.**
- **CDN (Content Delivery Network):** geographically distributed **edge caches** near users → lower latency, less origin load, DDoS absorption (Cloudflare, Akamai, CloudFront).
- **Caching layers:** browser → CDN → reverse proxy → app cache (Redis) → DB.
- **Forward vs reverse proxy** (above). **API gateway:** single entry point for microservices (auth, rate limiting, routing).
- **Latency vs throughput**; **horizontal vs vertical scaling.**
- **WebSocket, SSE, long polling** for real-time.

## 7. Wireless & Emerging
- **Wi-Fi 802.11** (CSMA/CA; 2.4/5/6 GHz). **Bluetooth** (PAN). **Cellular:** 4G LTE, 5G (low latency, high bandwidth, network slicing). **Zigbee / LoRa** (IoT).
- **IoT protocols:** **MQTT** (lightweight publish/subscribe over TCP), CoAP (UDP).
- **SDN:** separates control plane from data plane; centralized controller (OpenFlow). **NFV.**
- **Cloud networking:** VPC, subnets, security groups, NAT gateways.
- **Network utilities:** `ping` (ICMP), `traceroute/tracert`, `nslookup/dig`, `netstat/ss`, `ipconfig/ifconfig`, `curl`, `nmap`, `tcpdump/Wireshark`, `arp -a`.

## 8. Common Interview Questions
1. Symmetric vs asymmetric encryption? How does HTTPS use both?
2. How does a digital signature work? What is a certificate / CA?
3. Explain the TLS handshake.
4. What is a firewall? Types? What is a DMZ?
5. VPN: what and why?
6. Forward proxy vs reverse proxy?
7. DoS vs DDoS? How do you mitigate?
8. What is MITM? ARP spoofing? DNS spoofing?
9. SQL injection, XSS, CSRF: difference and defences?
10. Hashing vs encryption?
11. What is a CDN? Load balancer algorithms?
12. What is CORS? Same-origin policy?
13. Authentication vs authorization? MFA? OAuth?
14. How are passwords stored securely? (Salted hash with bcrypt/Argon2, not encryption.)

## MCQ Traps
- **Symmetric = 1 key (AES, fast); asymmetric = key pair (RSA, slow).**
- **Encrypt with the public key to send confidentially; sign with the private key to prove identity.**
- **Hashing is one-way; encryption is reversible.**
- **HTTPS uses asymmetric crypto for key exchange and symmetric for data.**
- **DES is obsolete (56-bit); AES is the standard.**
- **MD5/SHA-1 are broken; use SHA-256.**
- **Reverse proxy protects servers; forward proxy protects/represents clients.**
- **CSRF abuses the user's logged-in session; XSS injects scripts into pages.**
- **SYN flood → SYN cookies. ARP spoofing → dynamic ARP inspection.**
- **IPS blocks; IDS only detects.**

## Practice MCQs
1. Which algorithm is asymmetric? **(a) AES (b) DES (c) RSA (d) ChaCha20** → **c**
2. To sign a message, you use → **Your private key**
3. A reverse proxy commonly provides → **Load balancing / TLS termination**
4. TLS uses which type of encryption for bulk data? → **Symmetric**
5. Attack that makes a service unavailable by overwhelming it → **DoS / DDoS**
