/**
 * @brief KONSTANTA UNTUK FLOWMETER
 * Ini adalah konstanta yang spesifik untuk perhitungan flowmeter,
 * yang mungkin akan digunakan di masa depan untuk modularitas atau
 * jika ada beberapa flowmeter dengan konfigurasi berbeda.
 * Saat ini, nilai-nilai ini duplikat dari konstanta yang digunakan
 * di bagian atas file untuk perhitungan aliran.
 */
#define FLOW_R_SHUNT 150.0 // Resistansi Shunt (Ω) untuk flowmeter
#define FLOW_I_MIN 4.0     // Arus minimum sinyal (4 mA) untuk flowmeter
#define FLOW_I_MAX 20.0    // Arus maksimum sinyal (20 mA) untuk flowmeter
#define FLOW_Q_MIN 0.0     // Laju Aliran Minimum (L/M) untuk flowmeter
#define FLOW_Q_MAX 500.0   // Laju Aliran Maksimum (L/M) untuk flowmeter

/**
 * @brief FUNGSI PEMBACAAN FLOWMETER
 * Membaca data dari sensor flowmeter yang terhubung ke ADS1115.
 * Fungsi ini melakukan konversi dari nilai ADC mentah menjadi tegangan,
 * kemudian ke arus (mA), dan akhirnya ke laju aliran (L/M).
 */
void readFlowMeter()
{
  /** 1. Baca nilai mentah & Konversi ke Tegangan (Volt) */
  flowMeterData.raw = ads.readADC_SingleEnded(FLOW_CHANNEL);
  // V = (Raw / MAX_ADC_VALUE) * FSR
  flowMeterData.voltage = (float)flowMeterData.raw / MAX_ADC_VALUE * FSR;

  /** 2. Konversi Tegangan (Volt) ke Arus (mA) */
  // I = (V / R_SHUNT) * 1000
  // Batasi (constrain) nilai mA di rentang 4-20mA.
  // Ini agar perhitungan aliran tidak menggunakan nilai di luar rentang kalibrasi.
  flowMeterData.current_mA = constrain((flowMeterData.voltage / FLOW_R_SHUNT) * 1000.0, FLOW_I_MIN, FLOW_I_MAX);

  /** 3. Konversi Arus (mA) ke Laju Aliran (L/M) */
  // Menggunakan pemetaan linier: 4mA -> Q_MIN, 20mA -> Q_MAX.
  flowMeterData.flow_rate_LM = map_float(flowMeterData.current_mA, FLOW_I_MIN, FLOW_I_MAX, FLOW_Q_MIN, FLOW_Q_MAX);
}