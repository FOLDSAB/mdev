import requests
import socket


s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)


domain = input("please enter the domain name: ")

try:
    ip = socket.gethostbyname(domain)
    print("[+] Domain ip: ",ip)

except:
    print("\n\n---------------------------------------------------\n")
    print("[-] please enter the valid domain name")
    print("\n\n---------------------------------------------------\n")

    exit()




for port in range (441,444):

    if(port%5 ==0):
        print("[!] checking....")
    
    result = s.connect_ex((ip,port))


    if(result==0):
        print("[+] found open port: ",port)
        

