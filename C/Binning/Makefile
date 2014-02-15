all: auxillary binning

auxillary: auxillary.c
	$(CC) -o $@ $^

binning: binning.c
	$(CC) -o $@ $^ -lrt


.PHONY : clean
clean: 
	rm auxillary binning
