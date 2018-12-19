#Base Python client for MEng in IoT Assignment
#consumes data from IoT Gateway
#import urllib2

#response = urllib2.urlopen('http://localhost:8080/')
#resp = response.read()

#print resp

import urllib3
import xml.etree.cElementTree as et
import re
import matplotlib.pyplot as plt

http = urllib3.PoolManager()

url = 'http://localhost:8080/'

response = http.request('GET', url)

xml_string = '<temp_readings>'
xml_string += response.data.decode('ascii')
xml_string += '</temp_readings>'

root = et.fromstring(xml_string)

timestamps = []
temperatures = []

for reading in root:
    print('Time: ' + reading.find('time').text + ', Temp: ' + reading.find('temperature').text)
    timestamps.append(reading.find('time').text)
    temperatures.append(float(reading.find('temperature').text))

plt.plot(timestamps, temperatures)
plt.ylabel('Temperature')
plt.xticks(timestamps, timestamps, rotation='vertical')
plt.show()