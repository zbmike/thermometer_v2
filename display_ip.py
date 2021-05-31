#! /usr/bin/env python3
from RPLCD.i2c import CharLCD
import subprocess

result = subprocess.run(['hostname', '-I'], stdout=subprocess.PIPE)
ip = result.stdout.decode('utf-8')

# i2c
lcd = CharLCD(i2c_expander='PCF8574', address=0x27, port=1,
              cols=16, rows=2)

# GPIO
# lcd = CharLCD(cols=16, rows=2, pin_rs=20, pin_e=16, pins_data=[26, 19, 13, 6],
#               numbering_mode=GPIO.BCM, compat_mode=True)

lcd.clear()
lcd.cursor_pos = (0, 0)
lcd.write_string('Local IP Addr:')
lcd.cursor_pos = (1, 0)
lcd.write_string(ip)
lcd.close()