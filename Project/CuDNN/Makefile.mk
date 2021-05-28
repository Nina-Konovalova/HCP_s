CUDA_PATH=/usr/local/cuda
CUDNN_PATH=$(CUDA_PATH)/cudnn

CC=nvcc
CFLAGS=-I. -I$(CUDA_PATH)/include -I$(CUDNN_PATH)
LIBS=-lcudart -lcublas -lcudnn  -lm -lstdc++
LFLAGS=-L$(CUDA_PATH)/lib64 -L$(CUDNN_PATH)

OBJ = lenet.o readubyte.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.cu $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lenet: $(OBJ)
	gcc -o $@ $^ $(LFLAGS) $(LIBS)

clean:
	rm *.o 