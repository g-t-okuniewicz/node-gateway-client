#Base Python client for MEng in IoT Assignment
#consumes data from IoT Gateway
#import urllib2

#response = urllib2.urlopen('http://localhost:8080/')
#resp = response.read()

#print resp

import urllib3

http = urllib3.PoolManager()

url = 'http://localhost:8080/'

response = http.request('GET', url)

print(response.data)