#Base Python client for MEng in IoT Assignment
#consumes data from IoT Gateway
#import urllib2

#response = urllib2.urlopen('http://localhost:8080/')
#resp = response.read()

#print resp

import urllib3
import xml.etree.cElementTree as ET
import re

http = urllib3.PoolManager()

url = 'http://localhost:8080/'

response = http.request('GET', url)

xml_string = '<temp_readings>'
xml_string += response.data.decode('ascii')
xml_string += '</temp_readings>'

root = ET.fromstring(xml_string)

print(root.tag)

for reading in root:
    print('Time: ' + reading.find('time').text)
    print('Temp: ' + reading.find('temperature').text)
    
#print(tree)