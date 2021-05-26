import time
import board
import adafruit_dht
from RPLCD.i2c import CharLCD

dhtDevice = adafruit_dht.DHT22(board.D4)
lcd = CharLCD(i2c_expander='PCF8574', address=0x27, port=1,
              cols=16, rows=2)

while True:
    try:
        # Print the values to the serial port
        temperature_c = dhtDevice.temperature
        temperature_f = temperature_c * (9 / 5) + 32
        humidity = dhtDevice.humidity
        print(
            "Temp: {:.1f} F / {:.1f} C    Humidity: {}% ".format(
                temperature_f, temperature_c, humidity
            )
        )
        lcd.cursor_pos = (0, 0)
        lcd.write_string("{:.1f} F / {:.1f} C".format(temperature_f, temperature_c))
        lcd.cursor_pos = (1, 0)
        lcd.write_string("Humidity: %d %%" % humidity)

    except RuntimeError as error:
        # Errors happen fairly often, DHT's are hard to read, just keep going
        print(error.args[0])
        time.sleep(2.0)
        continue
    except Exception as error:
        dhtDevice.exit()
        raise error
    # except KeyboardInterrupt:
        # lcd.close(clear = True)

    time.sleep(2.0)