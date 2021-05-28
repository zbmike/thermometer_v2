from RPLCD.i2c import CharLCD
import subprocess

result = subprocess.run(['hostname', '-I'], stdout=subprocess.PIPE)
ip = result.stdout.decode('utf-8')

# i2c
lcd = CharLCD(i2c_expander='PCF8574', address=0x27, port=1,
              cols=16, rows=2)

lcd.clear()
lcd.cursor_pos = (0, 0)
lcd.write_string('Local IP Addr:')
lcd.cursor_pos = (1, 0)
lcd.write_string(ip)
lcd.close()