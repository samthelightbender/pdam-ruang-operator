#include <Wire.h>
#include <Adafruit_ADS1X15.h>

/**
 * @brief KONSTANTA ADS1115
 * Ini adalah konstanta utama yang digunakan untuk konfigurasi dan perhitungan dengan sensor ADC ADS1115.
 */
#define FSR 4.096             // FSR (Full Scale Range) adalah rentang tegangan input maksimum yang dapat diukur oleh ADS1115. Untuk GAIN_ONE, FSR adalah ±4.096V.
#define MAX_ADC_VALUE 32767.0 // MAX_ADC_VALUE adalah nilai ADC maksimum yang dapat dihasilkan oleh ADS1115 (16-bit). Untuk mode single-ended, ini adalah 2^15 - 1 = 32767.
#define PH_CHANNEL 0          // Channel untuk sensor pH
#define NTU_CHANNEL 1         // Channel untuk sensor NTU (kekeruhan)
#define FLOW_CHANNEL 2        // Channel untuk sensor flowmeter
#define PRESSURE_CHANNEL 3    // Channel untuk sensor tekanan

struct FlowMeterData
{
  int16_t raw;
  float voltage;
  float current_mA;
  float flow_rate_LM;
};

struct PHData
{
  int16_t raw;
  float voltage;
  float ph_value;
};

struct NTUData
{
  int16_t raw;
  float voltage;
  float ntu_value;
};

struct PressureData
{
  int16_t raw;
  float voltage;
  float current_mA;
  float pressure_bar;
};

Adafruit_ADS1115 ads;
FlowMeterData flowMeterData;
PHData phData;
NTUData ntuData;
PressureData pressureData;

void readFlowMeter();
void printSensorsData();
void readPH();
// void readNTU();
// void readPressure();
float map_float(float x, float in_min, float in_max, float out_min, float out_max);

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  /** Inisialisasi ADS1115 */
  if (!ads.begin())
  {
    Serial.println("ADS1115 Tidak Terdeteksi!");
    while (1)
      ;
  }
  ads.setGain(GAIN_ONE); // Set Gain ke ±4.096V (FSR)

  Serial.println("ADS1115 Ready");
}

void loop()
{
  readFlowMeter();
  readPH();
  // readNTU();
  // readPressure();
  printSensorsData();
  delay(500);
}

/**
 * @brief Fungsi untuk memetakan nilai float secara linier
 * Fungsi ini sama dengan map() built-in Arduino, namun mendukung tipe data float,
 * yang penting untuk konversi presisi tinggi (mA ke L/M).
 */
float map_float(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * @brief FUNGSI MENAMPILKAN DATA SENSOR
 * Fungsi ini berfungsi untuk menampilkan data sensor ke
 * Serial Monitor
 */
void printSensorsData()
{
  Serial.print("Flowmeter Raw: ");
  Serial.print(flowMeterData.raw);
  Serial.print(", Voltage: ");
  Serial.print(flowMeterData.voltage, 4); // 4 desimal
  Serial.print("V, Current: ");
  Serial.print(flowMeterData.current_mA, 2); // 2 desimal
  Serial.print("mA, Flow Rate: ");
  Serial.print(flowMeterData.flow_rate_LM, 2); // 2 desimal
  Serial.println(" L/min");
  Serial.print("pH Raw: ");
  Serial.print(phData.raw);
  Serial.print(", Voltage: ");
  Serial.print(phData.voltage, 4); // 4 desimal
  Serial.print("V, pH Value: ");
  Serial.print(phData.ph_value, 2); // 2 desimal
  Serial.println("");
}