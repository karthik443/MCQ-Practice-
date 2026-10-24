# 06 — Application Layer

## 1. Overview & Architectures
- Protocols users' programs use directly: **HTTP, FTP, SMTP, POP3, IMAP, DNS, DHCP, SSH, Telnet, SNMP.**
- **Client–server** vs **peer-to-peer.** The application layer defines message types, syntax, semantics, and rules.

## 2. Port Numbers ⭐ (memorize)
| Protocol | Port | Transport |
|----------|:--:|:--:|
| **HTTP** | 80 | TCP |
| **HTTPS** | 443 | TCP (HTTP/3: UDP/QUIC) |
| **FTP** | **20 (data), 21 (control)** | TCP |
| **SSH / SFTP** | 22 | TCP |
| **Telnet** | 23 | TCP |
| **SMTP** | 25 (587 submission, 465 SMTPS) | TCP |
| **DNS** | 53 | **UDP** (TCP for zone transfers / large responses) |
| **DHCP** | 67 (server), 68 (client) | UDP |
| **TFTP** | 69 | UDP |
| **POP3** | 110 (995 secure) | TCP |
| **IMAP** | 143 (993 secure) | TCP |
| **SNMP** | 161/162 | UDP |
| **NTP** | 123 | UDP |
| **LDAP** | 389 | TCP |
| **RDP** | 3389 | TCP |
| MySQL / PostgreSQL / MongoDB | 3306 / 5432 / 27017 | TCP |

## 3. HTTP ⭐⭐⭐
**HyperText Transfer Protocol:** **stateless**, **request–response**, text-based, runs over **TCP**, port 80.

### Request / Response
```
GET /index.html HTTP/1.1          <- request line: method, path, version
Host: example.com                 <- headers
User-Agent: Chrome
                                  <- blank line, then optional body

HTTP/1.1 200 OK                   <- status line
Content-Type: text/html
Content-Length: 1234
<html>...</html>
```

### Methods ⭐
| Method | Purpose | Idempotent | Safe | Body |
|--------|---------|:--:|:--:|:--:|
| **GET** | Retrieve a resource | ✔ | ✔ | No |
| **POST** | Create / submit data | ✘ | ✘ | Yes |
| **PUT** | Replace / create a resource entirely | ✔ | ✘ | Yes |
| **PATCH** | Partial update | Not guaranteed | ✘ | Yes |
| **DELETE** | Remove | ✔ | ✘ | Usually no |
| **HEAD** | Headers only (no body) | ✔ | ✔ | No |
| **OPTIONS** | Supported methods (CORS preflight) | ✔ | ✔ | |

- **Idempotent:** repeating gives the same server state. **Safe:** doesn't modify state.
- **GET vs POST:** GET puts params in the **URL** (visible, cached, bookmarkable, length-limited, not for sensitive data); POST puts data in the **body** (not cached, larger, used for forms/creation).
- **PUT vs POST:** PUT is idempotent, targets a specific URL; POST creates a new subordinate resource each time.

### Status codes ⭐⭐
| Class | Meaning | Common |
|-------|---------|--------|
| **1xx** | Informational | 100 Continue, 101 Switching Protocols |
| **2xx** | Success | **200 OK**, **201 Created**, 204 No Content |
| **3xx** | Redirection | **301 Moved Permanently**, **302 Found (temporary)**, **304 Not Modified** (cache) |
| **4xx** | Client error | **400 Bad Request**, **401 Unauthorized** (not authenticated), **403 Forbidden** (authenticated but not allowed), **404 Not Found**, 405 Method Not Allowed, 409 Conflict, **429 Too Many Requests** |
| **5xx** | Server error | **500 Internal Server Error**, 502 Bad Gateway, **503 Service Unavailable**, 504 Gateway Timeout |

### Headers (common)
`Host`, `User-Agent`, `Accept`, `Content-Type`, `Content-Length`, `Authorization`, `Cookie` / `Set-Cookie`, `Cache-Control`, `ETag`, `Location` (redirect), `Origin`, `Access-Control-Allow-Origin` (CORS).

### HTTP versions ⭐
| Version | Key features |
|---------|--------------|
| **HTTP/1.0** | **Non-persistent**: new TCP connection per request |
| **HTTP/1.1** | **Persistent connections (default)**, pipelining, `Host` header (virtual hosting), chunked transfer |
| **HTTP/2** | **Binary framing, multiplexing** many requests on one connection, header compression (HPACK), server push. Still TCP → TCP head-of-line blocking |
| **HTTP/3** | Over **QUIC (UDP)**, no TCP HoL blocking, faster handshake, built-in TLS 1.3 |

**Response time for a non-persistent page with n objects:** each object costs **2 RTT** (1 RTT TCP handshake + 1 RTT request/response) + transmission. **Persistent:** handshake once.

### Stateless & Cookies / Sessions ⭐
- HTTP is **stateless**: the server doesn't remember previous requests. State is added by:
  - **Cookies:** small data stored in the browser and sent with every request (`Set-Cookie`). Flags: **Secure, HttpOnly (no JS access, mitigates XSS theft), SameSite (mitigates CSRF)**, Expires/Max-Age.
  - **Sessions:** server stores data; the browser holds a **session ID** cookie.
  - **Tokens (JWT):** stateless authentication (signed token). Local/session storage.
- **Caching:** `Cache-Control`, `ETag`/`If-None-Match` → **304**. **Proxy / reverse proxy** / CDN.

### REST API basics ⭐
**REST** = architectural style over HTTP: resources identified by URLs (`/users/5`), standard methods (GET/POST/PUT/DELETE), **stateless**, usually **JSON**. Status codes signal results. **REST vs GraphQL** (client specifies fields; one endpoint) vs **gRPC** (HTTP/2 + protobuf).

### HTTPS
**HTTP over TLS** (port 443): **encryption, integrity, authentication** of the server (certificates). (See file 07.)

## 4. DNS ⭐⭐⭐
**Domain Name System:** a distributed, hierarchical database that maps **domain names → IP addresses.** Uses **UDP 53** (TCP for large responses/zone transfers).

### Hierarchy
**Root (.) → TLD (.com, .org, .in) → Authoritative (example.com) → subdomains (www.example.com).**

### Name servers
- **Recursive resolver (local DNS / ISP / 8.8.8.8):** does the lookup work for the client and caches results.
- **Root servers:** 13 logical root server addresses (A–M); point to TLD servers.
- **TLD servers:** point to the authoritative servers.
- **Authoritative servers:** hold the actual records for the domain.

### Resolution process ⭐
Client → **browser/OS cache** → **hosts file** → **recursive resolver** (cache?) → **root** ("ask .com") → **TLD** ("ask ns1.example.com") → **authoritative** ("IP = x.x.x.x") → answer returned and **cached** for the **TTL**.
- **Recursive query:** "give me the final answer" (client → resolver). **Iterative query:** "give me the best referral" (resolver → root/TLD/authoritative).

### Record types ⭐
| Record | Purpose |
|--------|---------|
| **A** | Domain → **IPv4** |
| **AAAA** | Domain → **IPv6** |
| **CNAME** | **Alias** → another domain name |
| **MX** | **Mail** exchange servers (with priority) |
| **NS** | **Name servers** of a domain |
| **TXT** | Text (SPF, DKIM, verification) |
| **PTR** | **Reverse** lookup: IP → domain |
| **SOA** | Start of authority (zone info) |

- **DNS caching + TTL** reduce load. **DNS load balancing** (round robin), **CDN** uses DNS/anycast.
- **Attacks:** **DNS spoofing/cache poisoning**, DDoS/amplification. **DNSSEC** signs records. **DoH/DoT** encrypt DNS.
- Tools: `nslookup`, `dig`.

## 5. Email Protocols ⭐
| Protocol | Role | Direction |
|----------|------|-----------|
| **SMTP** (25/587) | **Sending/relaying** mail (**push protocol**) | Client → server, server → server |
| **POP3** (110) | **Retrieve** mail; **downloads and usually deletes** from the server; one device | Server → client (pull) |
| **IMAP** (143) | Retrieve mail; **mail stays on the server**, synced across devices; folders | Server → client (pull) |
- Flow: sender's mail client →(SMTP) sender's server →(SMTP) recipient's server ←(POP3/IMAP) recipient's client.
- **MIME** extends email for attachments and non-ASCII.
- **SPF, DKIM, DMARC** fight spoofing.

## 6. FTP, SSH, Telnet & Others
- **FTP:** two connections — **control (21)** and **data (20)**; "out-of-band" control. **Active vs passive mode.** Credentials in **plain text**. **SFTP** (over SSH) / **FTPS** are secure.
- **Telnet:** remote terminal, **unencrypted**. **SSH:** **encrypted** remote login (replaced Telnet); key-based authentication.
- **TFTP:** simple, UDP, no authentication.
- **SNMP:** network device monitoring. **NTP:** time synchronization. **DHCP** (file 04).
- **WebSocket:** full-duplex, persistent connection over a single TCP (chat, live feeds). **Long polling / SSE** alternatives. **HTTP is half-duplex request–response.**

## 7. What Happens When You Type a URL (e.g. https://www.google.com)? ⭐⭐⭐
1. **Browser parses** the URL (scheme, host, path). Checks the **browser/HSTS/cache**.
2. **DNS resolution:** browser cache → OS cache/hosts → resolver → root → TLD → authoritative → **IP**.
3. **ARP / routing:** the host determines whether the IP is on the local subnet; if not, it sends to the **default gateway** (**ARP** to get the gateway's MAC). Packets are **routed** hop by hop (IP stays, MAC changes). **NAT** at the home router.
4. **TCP 3-way handshake** (SYN, SYN-ACK, ACK) to port **443**.
5. **TLS handshake:** certificate validation, key exchange → encrypted channel.
6. **HTTP request** (GET /) is sent over the secure channel.
7. The **server** (possibly behind a **load balancer / CDN / reverse proxy**) processes it (app, DB, cache) and returns an **HTTP response** (200 + HTML).
8. **Browser renders** HTML → fetches CSS/JS/images (more requests, parallel, HTTP/2 multiplexing) → builds DOM/CSSOM → paints.
9. Connection kept alive or closed (FIN).

## 8. Common Interview Questions
1. What happens when you type a URL in the browser?
2. HTTP vs HTTPS? HTTP/1.1 vs HTTP/2 vs HTTP/3?
3. GET vs POST? PUT vs POST vs PATCH? What is idempotency?
4. Explain common status codes (200, 301, 304, 401 vs 403, 404, 500, 503).
5. HTTP is stateless. How do cookies and sessions work?
6. How does DNS work? Record types? Why UDP?
7. Recursive vs iterative DNS query?
8. SMTP vs POP3 vs IMAP?
9. FTP: why two connections?
10. What is REST? Characteristics?
11. Cookie vs session vs JWT?
12. What is CORS?
13. Telnet vs SSH?
14. What is a CDN / reverse proxy?
15. WebSocket vs HTTP?

## MCQ Traps
- **DNS → UDP 53 (TCP for zone transfer).** **HTTP 80, HTTPS 443, SSH 22, FTP 20/21, SMTP 25, POP3 110, IMAP 143.**
- **HTTP is stateless.** Cookies/sessions add state.
- **401 = not authenticated; 403 = authenticated but forbidden.**
- **301 permanent, 302 temporary redirect; 304 = use cache.**
- **PUT is idempotent; POST isn't.**
- **SMTP = send; POP3/IMAP = receive.** **IMAP keeps mail on the server.**
- **A → IPv4; AAAA → IPv6; CNAME → alias; MX → mail; NS → name server; PTR → reverse.**
- **FTP uses separate control and data connections; sends passwords in plaintext.**
- **HTTP/1.1 = persistent by default; HTTP/2 = multiplexing; HTTP/3 = QUIC/UDP.**
- **Non-persistent HTTP: 2 RTT per object.**

## Practice MCQs
1. Default port of HTTPS → **443**
2. Record mapping a domain to an IPv6 address → **AAAA**
3. Which protocol downloads mail and leaves a copy on the server, synced across devices? → **IMAP**
4. Status for "resource not found" → **404**
5. Which is an idempotent method? **(a) POST (b) PUT (c) both (d) none** → **b**
