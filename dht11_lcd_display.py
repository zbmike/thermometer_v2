
import time
import board
import adafruit_dht
from RPLCD.gpio import CharLCD
from RPi import GPIO

dhtDevice = adafruit_dht.DHT11(board.D4)
lcd = CharLCD(cols=16, rows=2, pin_rs=22, pin_e=23, pins_data=[9, 25, 11, 8],
              numbering_mode=GPIO.BCM, compat_mode=True)

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
        time.sleep(5.0)
        continue
    except Exception as error:
        dhtDevice.exit()
        lcd.close(clear = True)
        raise error

    time.sleep(5.0)