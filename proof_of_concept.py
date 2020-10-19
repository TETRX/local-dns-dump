from subprocess import Popen,PIPE
import re

'''
1. Get IPs in the local network by broadcast pinging
2. Get a MAC address for each of those IPs
3. return a mapping from Macs to IPs
'''

BROADCAST_IP="" #fill out
NETWORK=""

def get_broadcast_ip():
    return BROADCAST_IP

def get_network_type():
    return NETWORK

IP_PATTERN=re.compile(r'(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})')
MAC_PATTERN=  re.compile(r'(?:[0-9a-fA-F]:?){12}')


def get_command_output(command):
    pid = Popen(command, stdout=PIPE)
    s = pid.communicate()[0]
    return s

def get_command_error(command):
    pid = Popen(command, stderr=PIPE)
    s = pid.communicate()[1]
    return s


def find_pattern(line, pattern):
    return pattern.findall(line)

def find_patterns_in_lines(lines,pattern):
    ips = set()
    for line in lines:
        try:
            line_ips=find_pattern(line,pattern)
        except:
            continue
        for ip in line_ips:
            if not ip==None:
                ips.add(ip)
    return list(ips)

def get_ips(timeout):
    broadcast_ip=get_broadcast_ip()
    raw=get_command_output(["timeout", str(timeout), "ping", "-b", broadcast_ip])
    pings=raw.decode("utf-8").split('\n')[1::]
    return find_patterns_in_lines(pings,IP_PATTERN)

def from_ip_get_mac(ip):
    line=get_command_error(["arpsend", "-D", "-e", ip, get_network_type()]).decode("utf-8")
    mac=find_pattern(line, MAC_PATTERN)[0]
    return mac

def get_mac_to_ip(ips):
    mac_to_ip={}
    for ip in ips:
        mac_to_ip[from_ip_get_mac(ip)]=ip

    return mac_to_ip
    

ips=get_ips(0.5)
print(get_mac_to_ip(ips))