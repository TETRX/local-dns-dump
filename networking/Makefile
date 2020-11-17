test: test_ip_getter_multithreading.o ip_getter.o arping_requester.o
	#g++ -pthread test_ip_getter_multithreading.cpp ip_getter.cpp -o test_ip_getter_multithreading.x
	g++ -o test_ip_getter_multithreading.x test_ip_getter_multithreading.o ip_getter.o arping_requester.o -pthread -L. -l:arping.a -lcap -lnet -lnsl -lrt -lpcap -lm
	rm test_ip_getter_multithreading.o ip_getter.o

%.o : %.cpp
	g++ -c $^ -o $@

arping:
	cd ../local_dns/src; ./makelib.sh; cd ../../networking
	mv ../local_dns/src/arping.a .

clean:
	rm -f *.x
	rm -f *.o
	rm arping.a
