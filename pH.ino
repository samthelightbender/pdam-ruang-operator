/**
 * KONSTANTA UNTUK PH
 *
 * Konstanta ini mendefinisikan nilai offset kalibrasi untuk sensor pH.
 * Nilai ini akan ditambahkan ke hasil perhitungan pH untuk menyesuaikan pembacaan sensor agar lebih akurat.
 */
#define PH_CALIBRATION_VALUE 0.0 // Offset kalibrasi untuk pH 7.

/**
 * FUNGSI PEMBACAAN PH
 *
 * Fungsi ini membaca nilai ADC mentah dari sensor pH yang terhubung ke ADS1115,
 * kemudian mengkonversinya menjadi tegangan, dan akhirnya menghitung nilai pH.
 * Offset kalibrasi juga diterapkan pada hasil akhir.
 */
void readPH()
{
  /** 1. Baca nilai mentah & Konversi ke Tegangan (Volt) */
  // Baca nilai ADC mentah dari channel PH_CHANNEL ADS1115
  phData.raw = ads.readADC_SingleEnded(PH_CHANNEL);

  // Konversi nilai ADC mentah ke tegangan (Volt)
  // Menggunakan referensi tegangan 4.096V (sesuai GAIN_ONE pada ADS1115)
  // dan resolusi 15-bit (32767 untuk nilai maksimum ADC)
  phData.voltage = (float)phData.raw * FSR / MAX_ADC_VALUE;

  /** 2. Hitung nilai pH berdasarkan tegangan */
  // Rumus ini didasarkan pada karakteristik probe pH di mana pH 7 biasanya pada 2.5V
  // dan setiap perubahan 0.05916V setara dengan perubahan 1 unit pH.
  phData.ph_value = 7 + ((2.5 - phData.voltage) / 0.05916);

  /** 3. Terapkan offset kalibrasi yang telah ditentukan */
  phData.ph_value += PH_CALIBRATION_VALUE;
}