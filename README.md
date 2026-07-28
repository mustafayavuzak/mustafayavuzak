<img src="https://mustafayavuzak.com/static/img/github-banner.jpg" alt="Mustafa Yavuz Ak, Founder of Başarı Miladı" width="100%">

<p align="center">
  <a href="https://basarimiladi.com"><img src="https://img.shields.io/endpoint?url=https%3A%2F%2Fmustafayavuzak.com%2Fstatus%2Fbasarimiladi%2Fbadge.json&cacheSeconds=300" alt="basarimiladi.com live status"></a>
  <a href="https://astromansion.com"><img src="https://img.shields.io/endpoint?url=https%3A%2F%2Fmustafayavuzak.com%2Fstatus%2Fastromansion%2Fbadge.json&cacheSeconds=300" alt="astromansion.com live status"></a>
  <a href="https://saturnempire.com"><img src="https://img.shields.io/endpoint?url=https%3A%2F%2Fmustafayavuzak.com%2Fstatus%2Fsaturnempire%2Fbadge.json&cacheSeconds=300" alt="saturnempire.com live status"></a>
</p>

<p align="center">
  <a href="https://mustafayavuzak.com"><img src="https://img.shields.io/badge/mustafayavuzak.com-ff0051?style=flat-square&logo=safari&logoColor=white" alt="Website"></a>
  <a href="mailto:founder@mustafayavuzak.com"><img src="https://img.shields.io/badge/founder@mustafayavuzak.com-0b0b0d?style=flat-square&logo=maildotru&logoColor=white" alt="Email"></a>
  <a href="https://x.com/mustafayavuzak"><img src="https://img.shields.io/badge/X-0b0b0d?style=flat-square&logo=x&logoColor=white" alt="X"></a>
  <a href="https://www.linkedin.com/in/mustafayavuzak"><img src="https://img.shields.io/badge/LinkedIn-0b0b0d?style=flat-square&logo=linkedin&logoColor=white" alt="LinkedIn"></a>
</p>

**I build the whole platform, from schema to server.** Database design, application code, deployment and monitoring are all mine. Every figure on this page is a measured result. The method sits next to it.

The three badges above are live. A monitor on my own server probes each upstream every two minutes and answers on a public endpoint. When a service goes down the badge turns grey while I am still asleep.

<img src="https://mustafayavuzak.com/static/img/gh/basarimiladi.jpg" alt="Başarı Miladı, social platform" width="100%">

A social platform built on a point economy. Members earn, spend and transfer points. Clubs, leaderboards and live rooms run on that ledger. Every balance change is an append-only entry, so a balance is never silently overwritten.

| Database tables | Endpoints | Subdomains | Status |
|---|---|---|---|
| 60 | 402 | 6 | Opening January 2027 |

[basarimiladi.com](https://basarimiladi.com)

<img src="https://mustafayavuzak.com/static/img/gh/astromansion.jpg" alt="AstroMansion, astronomy engine" width="100%">

An astrology calculation engine that runs on its own core. I wrote the C kernel that reads NASA JPL's 623 MB DE422 ephemeris file. There is no third party ephemeris library in the stack, no AGPL exposure, and birth data stays on the server.

| Lines of C | Celestial bodies | RMS vs NASA JPL | Full natal chart |
|---|---|---|---|
| ~18,900 | 11,000+ | 0.11″ to 0.19″ | 0.12 ms |

<details>
<summary><b>Accuracy: audited against NASA JPL Horizons, 1900 to 2100</b></summary>

<br>

Ecliptic longitude measured against JPL Horizons apparent values at quarterly steps across two centuries. The query definition and the raw CSV are published.

| Body | RMS | 95th pct | Max |
|---|---|---|---|
| Sun | 0.11″ | 0.20″ | 0.24″ |
| Moon | 0.11″ | 0.20″ | 0.24″ |
| Mercury | 0.11″ | 0.20″ | 0.25″ |
| Venus | 0.11″ | 0.20″ | 0.24″ |
| Mars | 0.11″ | 0.20″ | 0.24″ |
| Jupiter | 0.19″ | 0.21″ | 3.52″ |
| Saturn | 0.11″ | 0.21″ | 0.28″ |
| Uranus | 0.12″ | 0.22″ | 0.26″ |
| Neptune | 0.12″ | 0.22″ | 0.24″ |
| Pluto | 0.19″ | 0.38″ | 0.44″ |

Jupiter carries one isolated 3.5″ deviation near 1949. Neighbouring dates are clean and the raw data parses correctly. I did not identify its source in this audit, so it stays in the table.

ΔT uses the standard IERS and Stephenson-Morrison-Hohenkerk model. Output agrees with Skyfield to within 0.0003″ on the same DE kernel. That figure confirms the engine applies IAU 2000A/2006 conventions correctly, and it is an internal consistency check.

[Full accuracy report](https://astromansion.com/en/accuracy) · [Raw audit data (CSV)](https://astromansion.com/en/accuracy/audit.csv)

</details>

<details>
<summary><b>Speed: measured under a cold moment discipline</b></summary>

<br>

| Measurement | Result |
|---|---|
| Single body, cold moment | 51 µs |
| Per body inside a chart | 5.5 µs |
| Throughput inside chart computation | ~180,000 bodies/s |
| Full natal chart (ephemeris + houses) | 0.12 ms |

Every call uses a different instant, scattered across 1960 to 2020. A repeated moment returns from cache at 0.7 µs, so those calls are excluded. Single body over 30,000+ calls. Charts over 4,000 people, median of three runs, warmup dropped. Reference server, single core.

</details>

<details>
<summary><b>Two findings from the audit work</b></summary>

<br>

**The Moon under Lilith.** Interpolated Lilith marks the direction of the Moon's orbital apogee, so it is only as sound as the Moon beneath it. This engine takes the Moon from the numerically integrated DE422. Most astrology software still leans on an analytic lunar series from 1991. Measured against JPL Horizons across 1955 to 2024, lunar longitude here departs by 0.11″ and that analytic series by 0.57″. Five times closer to NASA. Lilith inherits the advantage, and the few arcsecond gap against other tools is deliberate.

**A comet in the wrong sign.** Validating hyperbolic and long period orbits against Horizons surfaced a ~30° error in a widely used reference implementation's Hale-Bopp position. A full zodiac sign off.

</details>

[astromansion.com](https://astromansion.com) · [API docs](https://astromansion.com/en/docs) · [Swagger](https://api.astromansion.com/docs)

<img src="https://mustafayavuzak.com/static/img/gh/saturnempire.jpg" alt="Saturn Empire, software company" width="100%">

My company. We build AI-integrated web software for businesses, and we operate what we ship. The engineering below is what a client gets, pointed at their problem.

[saturnempire.com](https://saturnempire.com)

<img src="https://mustafayavuzak.com/static/img/gh/engineering.jpg" alt="Engineering" width="100%">

**Systems under load.** Atomic database operations, row locks, append-only ledgers, idempotency keys. Running the same job twice has no additional effect.

**Real-time infrastructure.** WebSocket connections and a mediasoup SFU. Each worker holds its own RTC port range, and resources are released when a room empties.

**Numerical computation.** A C library that reads JPL ephemeris files, with its own Kepler solver for elliptic and hyperbolic orbits. Output verified against NASA JPL Horizons.

**Infrastructure.** Nginx, systemd, Cloudflare, PostgreSQL, Redis, Celery, Prometheus. I install them and I operate them.

| Layer | Tools |
|:---|:---|
| **Languages** | <img src="https://img.shields.io/badge/Python-0b0b0d?style=flat-square&logo=python&logoColor=white" alt="Python"> <img src="https://img.shields.io/badge/C-0b0b0d?style=flat-square&logo=c&logoColor=white" alt="C"> <img src="https://img.shields.io/badge/JavaScript-0b0b0d?style=flat-square&logo=javascript&logoColor=white" alt="JavaScript"> <img src="https://img.shields.io/badge/SQL-0b0b0d?style=flat-square" alt="SQL"> |
| **Backend** | <img src="https://img.shields.io/badge/FastAPI-0b0b0d?style=flat-square&logo=fastapi&logoColor=white" alt="FastAPI"> <img src="https://img.shields.io/badge/PostgreSQL-0b0b0d?style=flat-square&logo=postgresql&logoColor=white" alt="PostgreSQL"> <img src="https://img.shields.io/badge/Redis-0b0b0d?style=flat-square&logo=redis&logoColor=white" alt="Redis"> <img src="https://img.shields.io/badge/Celery-0b0b0d?style=flat-square&logo=celery&logoColor=white" alt="Celery"> |
| **Real-time** | <img src="https://img.shields.io/badge/WebRTC-0b0b0d?style=flat-square&logo=webrtc&logoColor=white" alt="WebRTC"> <img src="https://img.shields.io/badge/mediasoup-0b0b0d?style=flat-square" alt="mediasoup"> <img src="https://img.shields.io/badge/WebSocket-0b0b0d?style=flat-square" alt="WebSocket"> |
| **Frontend** | <img src="https://img.shields.io/badge/HTML-0b0b0d?style=flat-square&logo=html5&logoColor=white" alt="HTML"> <img src="https://img.shields.io/badge/CSS-0b0b0d?style=flat-square&logo=css&logoColor=white" alt="CSS"> <img src="https://img.shields.io/badge/SVG-0b0b0d?style=flat-square&logo=svg&logoColor=white" alt="SVG"> |
| **Ops** | <img src="https://img.shields.io/badge/Linux-0b0b0d?style=flat-square&logo=linux&logoColor=white" alt="Linux"> <img src="https://img.shields.io/badge/Nginx-0b0b0d?style=flat-square&logo=nginx&logoColor=white" alt="Nginx"> <img src="https://img.shields.io/badge/Docker-0b0b0d?style=flat-square&logo=docker&logoColor=white" alt="Docker"> <img src="https://img.shields.io/badge/Cloudflare-0b0b0d?style=flat-square&logo=cloudflare&logoColor=white" alt="Cloudflare"> <img src="https://img.shields.io/badge/Prometheus-0b0b0d?style=flat-square&logo=prometheus&logoColor=white" alt="Prometheus"> <img src="https://img.shields.io/badge/systemd-0b0b0d?style=flat-square" alt="systemd"> |

<details>
<summary><b>The monitor behind those badges</b></summary>

<br>

```
GET https://mustafayavuzak.com/status/projects.json
GET https://mustafayavuzak.com/status/{project}/badge.json
```

Both read from memory and never block on the network. The probe runs as its own asyncio task and hits each upstream directly, skipping the CDN round trip. A gateway error counts as offline. The task is cancelled cleanly on shutdown.

The badge answers in the shields.io endpoint schema, and the styling is decided on my server.

```json
{"schemaVersion": 1, "label": "basarimiladi.com", "message": "live", "color": "ff0051"}
```

</details>

> I handle the design, the development and the system administration myself.
>
> The performance and accuracy figures I publish are measured results, and the method sits beside them.
>
> I also operate the systems I deliver.

<img src="https://mustafayavuzak.com/static/img/gh/contact.jpg" alt="Contact" width="100%">

Slow site, unstable server, messy data, or no idea where to start. Tell me what the system needs to do and I will tell you what it takes.

[founder@mustafayavuzak.com](mailto:founder@mustafayavuzak.com) · [mustafayavuzak.com](https://mustafayavuzak.com) · [x](https://x.com/mustafayavuzak) · [linkedin](https://www.linkedin.com/in/mustafayavuzak)

<sub>I am Unbound.</sub>
