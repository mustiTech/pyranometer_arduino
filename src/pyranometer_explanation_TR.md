# ☀️ Pyranometre Sensoru
### Degerler ve Olcumler Hakkinda Aciklama
*Arduino + ADS1115 Projesi*

---

## 1. Pyranometre Nedir?

Pyranometre, gunes isiniminini (solar irradiance) olcen bilimsel bir sensordur. Bir yuzey uzerine dusen gunes enerjisi miktarini oelcer ve radyometre adli cihaz kategorisine girer. Hava istasyonlarinda, gunes enerjisi sistemlerinde ve tarimsal izleme uygulamalarinda yaygin olarak kullanilir.

Sensor, isik enerjisini kucuk bir elektrik gerilimine (voltaj) donusturur. Gunes isigi ne kadar parlaksa, urettigi voltaj da o kadar yuksek olur. Karanlıkta — ornegin geceleyin — cikis voltaji neredeyse sifira duser.

---

## 2. Sensor Ne Uretir?

Pyranometre, analog bir voltaj sinyali uretir. Bu voltaj son derece kucuktur — kullanilan sensore ve hassasiyet degerine gore genellikle **0 milivolt** (gunes yok) ile yaklasik **40 milivolt** (tam gunes isigi) arasinda degisir.

Bu kucuk sinyal bizim temel olcumumuzdur. Projemizde her sey — deger okumaktan fanonun ne zaman acilip kapanacagina kadar — bu voltajin dogru sekilde yorumlanmasina dayanir.

---

## 3. Arduino Neden Dogrudan Okuyamaz?

Arduino'nun dahili Analog-Dijital Ceviricisi (ADC) **10-bit cozunurluğe** sahiptir. Bu, giris araligini (0–5V) **1.024 adime** boldugu anlamina gelir. Her adim yaklasik **4.88 milivolta** esittir — bu deger bile zaman zaman pyranometreden gelen sinyalden buyuktur.

Bu nedenle Arduino'nun dahili ADC'si bu uygulama icin cok yetersiz kalir. Sensorden gelen kucuk voltaj degisikliklerini algilayabilmek icin cok daha ince bir cozunurluğe ihtiyacimiz var.

---

## 4. ADS1115 — Cozumumuz

ADS1115, harici bir **16-bit** Analog-Dijital Ceviricidir. Sadece iki veri kablosu (SDA ve SCL) kullanarak I2C iletisim protokolu uzerinden Arduino'ya baglanir. Bu sayede kablolama sade ve temiz kalir.

### 16-bit neden onemli?

16-bit cozunurlukle ADS1115, olcum araligini **32.768 adime** boler. Arduino'nun 1.024 adımiyla karsilastirildiginda ADS1115, **32 kat daha hassastir**. Bu hassasiyet, pyranometreden gelen kucuk voltajlari dogru okumak icin zorunludur.

---

## 5. rawValue Nedir?

ADS1115 sensoru okuduğunda, ham bir dijital sayi doner — buna **rawValue** deriz. Bu sayi, giris pinindeki mevcut voltaj seviyesini temsil eden **0 ile 32.767** arasinda bir degerdir.

Tek basina bu sayinin fiziksel bir birimi yoktur. Ancak sensorun cozunurluk katsayisi kullanilarak gercek volta donusturuldugunde anlamli hale gelir.

> **Onemli:** rawValue = 0 voltaj yok demektir (gunes yok). rawValue = 32.767 maksimum voltaj demektir (cok parlak gunes). Aradaki her deger orantisal bir olcumdur.

---

## 6. 0.1875 Sayisi Nereden Geliyor?

ADS1115'in varsayilan kazanc ayarinda tam olcum araligi ±6.144 Volt'tur. Her bir adimin kac milivolt oldugunu bulmak icin tam araligi adim sayisina boleriz:

| | Deger | Aciklama |
|---|---|---|
| **Tam Aralik** | 6.144 mV | Varsayilan kazanctaki toplam olcum araligi |
| **Toplam Adim** | 32.768 | 2'nin 15. kuvveti, 16-bit'in pozitif yarisi |
| **Her Adim** | **0.1875 mV** | 6.144 / 32.768 = cozunurluk katsayimiz |

---

## 7. Voltaj Formulu

rawValue degerini gercek Volt cinsinden voltaja donusturmek icin basit iki adimli bir hesaplama uygulariz:

```
voltaj (V) = rawValue × 0.1875 / 1000
```

- `rawValue × 0.1875` → **milivolt (mV)** cinsinden voltaj
- `/ 1000` → milivolttan **Volt (V)**'a donusum

---

## 8. Pratik Ornekler

| Senaryo | Hesaplama | Sonuc ve Anlami |
|---|---|---|
| Gunes yok (gece) | 5 × 0.1875 / 1000 | 0.0009 V — Fan KAPALI olmali |
| Cok zayif isik | 200 × 0.1875 / 1000 | 0.0375 V — Fan KAPALI olmali |
| Orta gunes | 1000 × 0.1875 / 1000 | 0.1875 V — Fan ACILABILIR |
| Guclu direkt gunes | 5000 × 0.1875 / 1000 | 0.9375 V — Fan kesinlikle ACIK |

---

## 9. Bunu Projemizde Nasil Kullaniyoruz?

Projemiz voltaj okumalarini basit bir karar vermek icin kullanir: gunes dogduysa fani ac; gunes battiysas fani kapat. Mantik su sekilde isler:

- Pyranometre, mevcut gunes isigina gore surekli voltaj uretir
- ADS1115 bu voltaji rawValue sayisina donusturur
- Kodumuz rawValue degerini gercek volta cevirir
- Voltaji bir **esik deger** ile karsilastiririz (gercek testlerden sonra belirlenir)
- Voltaj esik degerinin **uzerindeyse** → fan **ACILIR**
- Voltaj esik degerinin **altindaysa** → fan **KAPANIR**

---

## 10. Onemli Notlar

> **Esik Deger:** Kesin esik voltaji, gunes dogusundaki gercek okumalara bakilarak belirlenir. Her kurulum biraz farklidir.

> **Hassasiyet:** Farkli pyranometre modellerinin farkli hassasiyet degerleri vardir (mV / W/m²). Her zaman sensorunuzun veri sayfasini kontrol edin.

> **Kablolama:** ADS1115, I2C kullanir — SDA'yi Arduino A4'e, SCL'yi Arduino A5'e baglayin. Sensor cikisi ADS1115'in A0 pinine baglanir.

> **Kutuphane:** Herhangi bir kod yuklemeden once Arduino IDE'ye **Adafruit ADS1X15** kutuphanesinin kurulu olmasi gerekir.

---


