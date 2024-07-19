import requests
import socket

File_object = open(r"wordlist.txt", "r")

domain_name = input("Please enter the domain name: ")
directory = File_object.readlines()

try:
    ipaddr = socket.gethostbyname(domain_name)
except:
    print("please enter valid domain")
    exit()


for name in directory:
    
    r = requests.get("https://"+domain_name+"/"+name)

    if(r.status_code == 200):
        print("[+] found: ",name+"     Statuscode: 200")

    if(r.status_code == 300):
        print("[!] found: ",name+"Statuscode: 300")
    else:
        print("not found") 
 
    print(r.status_code)





