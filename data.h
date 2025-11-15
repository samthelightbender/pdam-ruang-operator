#include <inttypes.h>

/**
 * FLOW METER
 */
struct FlowMeterData
{
  int16_t raw;
  float voltage;
  float current_mA;
  float flow_rate_LM;
};

/**
 * PH
 */
struct PHData
{
  int16_t raw;
  float voltage;
  float ph_value;
};

/**
 * NTU
 */
struct NTUData
{
  int16_t raw;
  float voltage;
  float ntu_value;
};

/**
 * PRESSURE
 */
struct PressureData
{
  int16_t raw;
  float voltage;
  float current_mA;
  float pressure_bar;
};