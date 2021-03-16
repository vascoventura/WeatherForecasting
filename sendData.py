import http.client
import serial
import array as arr

ser = serial.Serial(
    port='COM8',
    baudrate=9600
)

while True:
    ch = ser.readline()

    sensor = str(ch.decode())

    result = sensor.split(' ')

    
    
    temperatura = result[0]
    humidade =  result[1]

    print ("Temperatura: " + temperatura +  " " + "Humidade: " + humidade)

    conn = http.client.HTTPConnection('184.106.153.149')
    conn.request("GET","/update?api_key=GI627UOI6O5TDE6H&field1=" + temperatura + "&field2=" + humidade)
    conn.close()

    temperatura = ''
    humidade = ''
    
    ch = ''

