
//MQTT broker
//#define MQTT_SERVER "broker.hivemq.com"//"192.168.2.233"
#define MQTT_SERVER "192.168.2.233"
#define MQTT_USER "mqtt-user"
#define MQTT_PASSWD  "kokos123"

//WIFI
#define WIFI_SSID "Kanal69"
#define WIFI_PASSWD "00420603435309"

//setup LED
#define LED_SETUP 2

//updates every Nth minute
#define UPDATE_INTERVAL 1

//switch between pareing and operational mode
#define MODE_PIN 5  

//dhtsensor
#define DHTPIN 14
#define DHTTYPE DHT11

//switches on watersensors
#define SENSOR_SWITCH_PIN 22

#define MQ2_SENSOR 35
#define MQ135_SENSOR 32
#define MQ135_R0 20

//lightsensor
#define LIGHT_SENSOR_PIN 34
#define LIGHT_SENSOR_MAX_VALUE 3900
#define LIGHT_SENSOR_MIN_VALUE 150

//waterlevel sensor
#define WATER_LEVEL_SENSOR_PIN 33
#define WATER_LEVEL_SENSOR_MAX_VALUE 1600 //500
#define WATER_LEVEL_SENSOR_MIN_VALUE 0 //200

//soil moisture sensor
#define MOISTURE_SENSOR_PIN 32
#define MOISTURE_SENSOR_MAX_VALUE 2760
#define MOISTURE_SENSOR_MIN_VALUE 1500

//water pump
#define WATER_PUMP_PIN 13
#define WATER_PUMP_TIME 3000

//rgb led - waterlevel
#define WATER_LED_R_PIN 4
#define WATER_LED_G_PIN 5
#define WATER_LED_B_PIN 15

//rgb led - err 
#define ERR_LED_R_PIN 21
#define ERR_LED_G_PIN 19
#define ERR_LED_B_PIN 18