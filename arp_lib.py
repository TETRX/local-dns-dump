import scapy.all as sp

'''
Send ARP request with IP address filled in.
'''

ip = "10.0.2.2"  # fill in
and, unans = sp.srp(sp.Ether(dst="ff:ff:ff:ff:ff:ff") / sp.ARP(pdst=ip), timeout=2, verbose=0)
if len(ans) == 0:
  print("error")
print(ans[0][1].src)
