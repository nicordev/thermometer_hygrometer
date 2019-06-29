/**
 * A thermometer and a hygrometer with a LCD screen
 */
#include <LiquidCrystal.h>
#include <dht_nonblocking.h>

// initialize the screen library with the numbers of the interface pins
LiquidCrystal screen(7, 8, 9, 10, 11, 12);

// Thermometer and hygrometer
#define DHT_SENSOR_TYPE DHT_TYPE_11

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment(float *temperature, float *humidity)
{
    static unsigned long measurement_timestamp = millis();

    /* Measure once every four seconds. */
    if (millis() - measurement_timestamp > 3000ul)
    {
        if (dht_sensor.measure(temperature, humidity) == true)
        {
            measurement_timestamp = millis();
            return (true);
        }
    }

    return (false);
}

void setup() {
    // set up the LCD's number of columns and rows:
    screen.begin(16, 2);
    screen.print("Hello world!");
}

void loop() {
    float temperature;
    float humidity;

    /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
    if (measure_environment(&temperature, &humidity) == true)
    {
        screen.setCursor(0, 0);
        screen.print("T = ");
        screen.print(temperature, 1);

        screen.setCursor(0, 1);
        screen.print(" *C, H = ");
        screen.print(humidity, 0);
        screen.print(" %");
    }
}
