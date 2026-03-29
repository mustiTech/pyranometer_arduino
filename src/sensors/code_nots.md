# 🌞 Pyranometer Measurement – Technical Notes

---

## 🇬🇧 Technical Notes (Hardware / Signal Perspective)

### ADS1115 (ADC)
- 16-bit delta-sigma analog-to-digital converter.
- Converts analog voltage into a digital value.
- High resolution enables accurate measurement of low-level signals.

### Measurement Type (Single-Ended)
- Measures voltage at input A0 relative to GND.
- Suitable for sensors with output referenced to ground.
- Input range depends on programmable gain (PGA).

### Digital Output (Raw Value)
- Output is a signed 16-bit integer (−32768 to +32767).
- Represents the scaled analog input signal.
- Value depends on selected full-scale range.

### LSB Resolution
- 0.1875 mV per bit (at ±6.144 V range).
- Defines the smallest detectable voltage change.
- Higher resolution improves sensitivity for small signals.

### Voltage Conversion Principle
- Voltage = Digital Value × LSB size
- LSB is in millivolts → divide by 1000 to convert to volts.
- Final output is an analog-equivalent voltage.

### Pyranometer Signal Characteristics
- Produces very small voltage (µV to mV range).
- Output is proportional to solar irradiance (W/m²).
- Often requires amplification before ADC.

### Noise and Accuracy
- Low-level signals are sensitive to electrical noise.
- Proper grounding and shielding are important.
- Averaging multiple readings improves stability.

### Gain (PGA)
- Determines measurable voltage range.
- Lower range → higher resolution and sensitivity.
- Must be selected according to sensor output.

---

## 🇹🇷 Teknik Notlar (Donanım / Sinyal Perspektifi)

### ADS1115 (ADC)
- 16-bit delta-sigma analog-dijital çevirici.
- Analog gerilimi dijital değere dönüştürür.
- Yüksek çözünürlük sayesinde küçük sinyaller ölçülebilir.

### Ölçüm Tipi (Single-Ended)
- A0 girişini GND’ye göre ölçer.
- Toprağa referanslı sensörler için uygundur.
- Giriş aralığı PGA ayarına bağlıdır.

### Dijital Çıkış (Ham Değer)
- Çıkış 16-bit signed integer’dır (−32768 ile +32767 arası).
- Analog girişin ölçeklenmiş halidir.
- Seçilen gerilim aralığına bağlıdır.

### LSB Çözünürlüğü
- 0.1875 mV/bit (±6.144 V aralığında).
- Ölçülebilecek en küçük gerilim değişimini belirler.
- Yüksek çözünürlük → daha hassas ölçüm.

### Gerilim Hesaplama Prensibi
- Gerilim = Dijital değer × LSB değeri
- mV → V dönüşümü için 1000’e bölünür.
- Sonuç analog gerilimi temsil eder.

### Pyranometre Sinyali
- Çok düşük seviyede gerilim üretir (µV–mV).
- Çıkış güneş ışınımı (W/m²) ile orantılıdır.
- Genellikle yükseltici (amplifier) gerektirir.

### Gürültü ve Doğruluk
- Küçük sinyaller gürültüye hassastır.
- Doğru topraklama ve ekranlama önemlidir.
- Ortalama alma (averaging) stabiliteyi artırır.

### Kazanç (PGA)
- Ölçüm aralığını belirler.
- Düşük aralık → yüksek hassasiyet.
- Sensör çıkışına uygun seçilmelidir.

---