# ☀️ Irradiance & Sun Status
### What the irradiance value tells us
*Pyranometer Project — Arduino + ADS1115*

---

## Can We Know the Sun's Status from Irradiance?

Yes — indirectly.

The irradiance value does not tell us the sun's position in degrees or direction,
but it tells us the **current state of sunlight**, which is exactly what we need.

---

## Irradiance Ranges & Meanings

| Irradiance (W/m²) | Sun Status | Fan |
|---|---|---|
| 0 – 10 | Night / No Sun | OFF |
| 10 – 200 | Sunrise or Sunset | OFF |
| 200 – 600 | Sun Present — Cloudy Sky | ON |
| 600 – 1000+ | Full Sun — Clear Sky | ON |

---

## What Irradiance CAN Tell Us

- ✅ Whether the sun is **up or down**
- ✅ Whether the sky is **clear or cloudy**
- ✅ Whether it is **day or night**

## What Irradiance CANNOT Tell Us

- ❌ The sun's angle in degrees
- ❌ The sun's direction (East / West)

---

## The getSunStatus() Function

The function reads the irradiance value and returns a text description
of the current sun condition. It uses simple threshold comparisons:

```
irradiance < 10       →  "Night / No Sun"
irradiance < 200      →  "Sunrise or Sunset"
irradiance < 600      →  "Sun Present - Cloudy"
irradiance >= 600     →  "Full Sun - Clear Sky"
```

> **Note:** These threshold values are based on typical solar irradiance ranges.
> They may need adjustment depending on your location and sensor sensitivity.

---

*Pyranometer Project — Arduino + ADS1115 — Sun Status Notes*
