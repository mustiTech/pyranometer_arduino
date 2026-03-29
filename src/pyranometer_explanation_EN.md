# ☀️ Pyranometer Sensor
### Understanding Values & Measurements
*Arduino + ADS1115 Project*

---

## 1. What is a Pyranometer?

A pyranometer is a scientific sensor designed to measure solar irradiance — the amount of solar energy that reaches a surface per unit area. It belongs to a category of instruments called radiometers, and it is widely used in weather stations, solar energy systems, and agricultural monitoring.

The sensor works by converting light energy into a small electrical voltage. The brighter the sunlight, the higher the voltage it produces. In complete darkness — such as at night — the output voltage drops to near zero.

---

## 2. What Does the Sensor Output?

The pyranometer outputs an analog voltage signal. This voltage is extremely small — typically ranging from **0 millivolts** (no sun) up to around **40 millivolts** (full direct sunlight), depending on the specific sensor model and its sensitivity rating.

This tiny signal is the key measurement. Everything in our project — from reading the value to deciding when to turn the fan on or off — is based on interpreting this voltage correctly.

---

## 3. Why Can't Arduino Read It Directly?

Arduino has a built-in Analog-to-Digital Converter (ADC) with **10-bit resolution**. This means it divides its input range (0–5V) into **1,024 steps**. Each step is approximately **4.88 millivolts** — which is already larger than some of the signals our pyranometer produces.

This makes Arduino's built-in ADC far too imprecise for our use case. We need a much finer resolution to detect the small voltage changes coming from the sensor.

---

## 4. The ADS1115 — Our Solution

The ADS1115 is an external **16-bit** Analog-to-Digital Converter. It connects to the Arduino via the I2C communication protocol using just two data wires (SDA and SCL), making wiring simple and clean.

### Why 16-bit matters

With 16-bit resolution, the ADS1115 divides its measurement range into **32,768 steps**. Compare this to Arduino's 1,024 steps — the ADS1115 is **32 times more precise**. This precision is essential for accurately reading the small voltages from our pyranometer.

---

## 5. What is the rawValue?

When the ADS1115 reads the sensor, it returns a raw digital number — we call this **rawValue**. It is simply a number between **0 and 32,767** that represents the current voltage level at the input pin.

By itself, this number has no physical unit. It only becomes meaningful when we convert it into actual volts using the sensor's resolution factor.

> **Key Point:** rawValue = 0 means no voltage (no sunlight). rawValue = 32,767 means maximum voltage (very bright sun). Everything in between is a proportional measurement.

---

## 6. Where Does 0.1875 Come From?

The ADS1115 has a default gain setting that sets its full measurement range to ±6.144 Volts. To find out how much voltage each individual step represents, we divide the full range by the number of steps:

| | Value | Description |
|---|---|---|
| **Full Range** | 6,144 mV | Total measurement range at default gain |
| **Total Steps** | 32,768 | 2 to the power of 15 (positive half of 16-bit) |
| **Each Step** | **0.1875 mV** | 6,144 ÷ 32,768 = our resolution factor |

---

## 7. The Voltage Formula

To convert rawValue into actual voltage in Volts, we apply a simple two-step calculation:

```
voltage (V) = rawValue × 0.1875 / 1000
```

- `rawValue × 0.1875` → voltage in **millivolts (mV)**
- `/ 1000` → convert millivolts to **Volts (V)**

---

## 8. Practical Examples

| Scenario | Calculation | Result & Meaning |
|---|---|---|
| No sunlight (night) | 5 × 0.1875 / 1000 | 0.0009 V — Fan should be OFF |
| Very dim light | 200 × 0.1875 / 1000 | 0.0375 V — Fan should be OFF |
| Moderate sunlight | 1000 × 0.1875 / 1000 | 0.1875 V — Fan may turn ON |
| Strong direct sunlight | 5000 × 0.1875 / 1000 | 0.9375 V — Fan definitely ON |

---

## 9. How We Use This in Our Project

Our project uses the voltage reading to make a simple decision: if the sun is up, turn the fan on; if the sun is down, turn the fan off. The logic works like this:

- The pyranometer continuously produces a voltage based on current sunlight
- The ADS1115 converts this voltage into a rawValue number
- Our code converts rawValue into actual volts
- We compare the voltage to a **threshold value** (determined after real testing)
- If voltage is **above** the threshold → fan turns **ON**
- If voltage is **below** the threshold → fan turns **OFF**

---

## 10. Important Notes

> **Threshold:** The exact threshold voltage must be determined by observing real readings at sunrise. Every installation is slightly different.

> **Sensitivity:** Different pyranometer models have different sensitivity ratings (mV per W/m²). Always check your sensor's datasheet.

> **Wiring:** The ADS1115 uses I2C — connect SDA to Arduino A4, SCL to Arduino A5. The sensor output connects to ADS1115 pin A0.

> **Library:** You need the **Adafruit ADS1X15** library installed in Arduino IDE before uploading any code.

---

*Pyranometer Project — Arduino + ADS1115 — English Reference*
