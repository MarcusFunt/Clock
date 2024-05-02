//Pins
#define SENSOR_PIN 33//the pin you have connected to the analog light sensor

#define DISPLAY_PIN 32//the pin you have connected to the nanoleaf matrix


//WIFI
#define WIFI_SSID "33bGuest"//Your ssid

#define WIFI_PASSWORD "Holmsteen"//Your password


//TIME

#define GMT_OFFSET 3600//Offset from GMT(time zone)(number is in seconds(3600=1h))

#define DAYLIGHT_OFFSET 3600//Daylight saving(number is in seconds(3600=1h))

#define NTP_SERVER "pool.ntp.org"//Don't change this unless you know what youre doing


//LIGHT

#define LIGHT_HISTORY_SIZE 10

#define EMACALIBRATIONMIN 0.01

#define EMACALIBRATIONMAX 0.3

#define NUMBEROFREADINGSPERREADING 5

#define MAXACTUALLIGHT 2100

//DISPLAY

#define BRIGHTNESS 55


//MISC

#define UPDATESPEED 200

#define FALLBACKTIMEUPDATE 3600000

