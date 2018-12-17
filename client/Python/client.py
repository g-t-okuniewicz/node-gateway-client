#Base Python client for MEng in IoT Assignment
#consumes data from IoT Gateway
import urllib2

response = urllib2.urlopen('http://localhost:8080/')
resp = response.read()

print resp