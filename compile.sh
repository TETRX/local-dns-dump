cd local_dns/src; ./makelib.sh; cd ../../
mv local_dns/src/arping.a .
g++ -c ip_from_mac.cpp -o ip_from_mac.o
g++ -o ip_from_mac ip_from_mac.o -L. -l:arping.a -lcap -lnet -lnsl -lrt -lpcap -lm
rm ip_from_mac.o
