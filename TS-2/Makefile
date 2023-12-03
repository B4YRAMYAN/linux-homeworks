demo-aplication: demo-aplication.o parallel_scheduler.o
	g++ demo-aplication.o parallel_scheduler.o demo-aplication
demp-aplication.o: demo-aplication.cpp
	g++ -c demp-aplication.cpp -o demo-aplication.o
parallel_scheduler.o: parallel_scheduler.cpp
	g++ -c parallel_scheduler.cpp -o parallel_schenduler.o
clean: rm demp-aplication *.o

