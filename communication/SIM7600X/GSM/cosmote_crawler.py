import urllib.request as urll 
import re

link = 'http://myinternet.cosmote.gr/main'
link = 'file:///home/pi/Desktop/cosmote.html'
f = urll.urlopen(link)
myfile = f.read()
myfile = str(myfile, 'latin-1')

string = '<span class="customClassTotalDataBalance"></span>'

matches = re.findall(string, myfile);
first = re.search(string, myfile).start()
last = first+len(string)
newstring = ''
for i in range(20):
	newstring+=myfile[last+i]

print(newstring.split('<')[0])


