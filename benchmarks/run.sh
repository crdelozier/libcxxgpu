nvcc -I../include_45/ -I../ -lrt -o test vector_sort.cu -DSTL_ENABLE_GPU -O3 -DDATA_TYPE=int -DGT9600
./test 32000
./test 32000
./test 64000
./test 128000
./test 256000
./test 500000
./test 1000000
./test 2000000
./test 4000000
./test 8000000
./test 16000000
./test 32000000

nvcc -I../include_45/ -I../ -lrt -o test vector_sort.cu -O3 -DDATA_TYPE=int
./test 32000
./test 64000
./test 128000
./test 256000
./test 500000
./test 1000000
./test 2000000
./test 4000000
./test 8000000
./test 16000000
./test 32000000

nvcc -I../include_45/ -I../ -lrt -o test vector_sort.cu -DSTL_ENABLE_GPU -O3 -DDATA_TYPE=float -DGT9600
./test 32000
./test 32000
./test 64000
./test 128000
./test 256000
./test 500000
./test 1000000
./test 2000000
./test 4000000
./test 8000000
./test 16000000
./test 32000000

nvcc -I../include_45/ -I../ -lrt -o test vector_sort.cu -O3 -DDATA_TYPE=float
./test 32000
./test 64000
./test 128000
./test 256000
./test 500000
./test 1000000
./test 2000000
./test 4000000
./test 8000000
./test 16000000
./test 32000000
