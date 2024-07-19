from os import link
import requests
from bs4 import BeautifulSoup
import re

crtsh = "https://crt.sh/?q="

domain_name = "schoolworkspro.com"

crtsh = crtsh+domain_name

response = requests.get(crtsh)

output = response.text



soup = BeautifulSoup(output,"html.parser")

# soup = soup.find_all('td')

for soups in soup.find_all('td'):

    soupe = soups.text

    outer = re.match(r'^schoolworkspro.com$',soupe)
    
    if(outer == None):
        continue
    
    else:
        print(outer)
    
    








