import json
import time
from subprocess import Popen, PIPE, TimeoutExpired
from threading import Lock
from python_hosts import Hosts, HostsEntry

class LocalDnsResolver():
    lock=Lock()

    def __init__(self,timeout=0):
        self.timeout = timeout
    
    def get_ip_from_dns(self, qname):
        # Synchronize so the getter is called only once at the time
        with self.lock:
            # TODO: change it. Start the c++ ip getter
            process = Popen(["./get_ip.x", qname], stdout=PIPE, stderr=PIPE)
            try:
                exit_code = process.wait(self.timeout)
                (output, err) = process.communicate()
                print(exit_code)
                print(err.decode("utf-8"))
                if exit_code:
                    return ""
                else:
                    return output.decode("utf-8")
            except TimeoutExpired:
                return ""

def remove_lines(blacklist,file):
    lines=[]
    with open(file,"r") as old:
        for line in old:
            if not any(word in line for word in blacklist):
                lines.append(line)
    with open(file, "w") as new:
        for line in lines:
            new.write(line)
while True:
    resolver=LocalDnsResolver(timeout=5)

    file="/etc/local_dns/DnsMapUser.config"

    str=""
    for line in open(file,"r"):
        if not line.strip().startswith("//"):
            str+=line

    loaded=json.loads(str)

    answers={}

    for address in loaded.keys():
        answer=resolver.get_ip_from_dns(address)
        answer=answer.split('\n')[-2]
        if len(answer)>0:
            answers[address]=answer

    hosts_file="/etc/hosts"
    remove_lines([".localdns."],hosts_file)
    hosts=Hosts(hosts_file)

    entries=[]
    for address, answer in answers.items():
        new_entry=HostsEntry(entry_type='ipv4',address=answer,names=[address])
        entries.append(new_entry)

    hosts.add(entries)
    hosts.write()
    
    time.sleep(10)