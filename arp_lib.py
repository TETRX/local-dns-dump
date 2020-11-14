import scapy.all as sp

'''
Send ARP request with IP address filled in.
'''

ip = "10.0.2.2"  # fill in
ans, unans = sp.srp(sp.Ether(dst="ff:ff:ff:ff:ff:ff") / sp.ARP(pdst="10.0.2.0/24"), timeout=2, verbose=0)
print(ans)
if len(ans) == 0:
  print("error")
print(ans[0][1].src)
