CXX := nvcc
CXXFLAGS := 
LDFLAGS := -lrt
INCLUDE := -I../include_45/ -I../

all: list_sort search vector_ops vector_sort

clean:
	rm -f search list_sort

search:
	${CXX} ${INCLUDE} ${CXXFLAGS} ${LDFLAGS} -o search search.cu

list_sort:
	${CXX} ${INCLUDE} ${CXXFLAGS} ${LDFLAGS} -o list_sort list_sort.cu

vector_ops:
	${CXX} ${INCLUDE} ${CXXFLAGS} ${LDFLAGS} -o vector_ops vector_ops.cu

.PHONY vector_sort:
	${CXX} ${INCLUDE} ${CXXFLAGS} ${LDFLAGS} -o vector_sort vector_sort.cu
