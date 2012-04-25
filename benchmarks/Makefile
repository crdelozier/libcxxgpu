CXX := nvcc
CXXFLAGS := 
LDFLAGS := -lrt -DSTL_ENABLE_GPU -O3 -DGT9600
INCLUDE := -I../include_45/ -I../

.PHONY all: list_sort search vector_ops vector_sort function set reductions

clean:
	rm -f list_sort search vector_ops vector_sort function set reductions test

function:
	${CXX} ${INCLUDE} ${CXXFLAGS} ${LDFLAGS} -o function function.cu

search:
	${CXX} ${INCLUDE} ${CXXFLAGS} ${LDFLAGS} -o search search.cu

set:
	${CXX} ${INCLUDE} ${CXXFLAGS} ${LDFLAGS} -o set set.cu

list_sort:
	${CXX} ${INCLUDE} ${CXXFLAGS} ${LDFLAGS} -o list_sort list_sort.cu

reductions:
	${CXX} ${INCLUDE} ${CXXFLAGS} ${LDFLAGS} -o reductions reductions.cu

vector_ops:
	${CXX} ${INCLUDE} ${CXXFLAGS} ${LDFLAGS} -o vector_ops vector_ops.cu

vector_sort:
	${CXX} ${INCLUDE} ${CXXFLAGS} ${LDFLAGS} -o vector_sort vector_sort.cu
