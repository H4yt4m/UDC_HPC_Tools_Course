# Module needed: openblas
# => module load openblas
# You need to uncomment the header for openblas
dgesv_gcc_o0: dgesv.c
	gcc  -g3   dgesv.c  -lopenblas -o dgesv_gcc -O0 -march=native

dgesv_gcc_o1: dgesv.c
	gcc  -g3   dgesv.c  -lopenblas -o dgesv_gcc -O1 -march=native

dgesv_gcc_o2: dgesv.c
	gcc  -g3   dgesv.c  -lopenblas -o dgesv_gcc -O2 -march=native

dgesv_gcc_o3: dgesv.c
	gcc  -g3   dgesv.c  -lopenblas -o dgesv_gcc -O3 -march=native

dgesv_gcc_ofast: dgesv.c
	gcc  -g3   dgesv.c  -lopenblas -o dgesv_gcc -Ofast -march=native

dgesv_gcc_o0_pfprof_gen: dgesv.c
	gcc  -g3   dgesv.c  -lopenblas -o dgesv_gcc -O0 -march=native -fprofile-generate

dgesv_gcc_o0_pfprof_use: dgesv.c
	gcc  -g3   dgesv.c  -lopenblas -o dgesv_gcc -O0 -march=native -fprofile-use

dgesv_gcc_o0_parallel_first: dgesv.c
	gcc  -g3   dgesv.c  -lopenblas -o dgesv_gcc -O0 -march=native -floop-parallelize-all

dgesv_gcc_o0_parallel_second: dgesv.c
	gcc  -g3   dgesv.c  -lopenblas -o dgesv_gcc -O0 -march=native -ftree-parallelize-loops=8

dgesv_gcc_o3_pfprof_gen: dgesv.c
	gcc  -g3   dgesv.c  -lopenblas -o dgesv_gcc -O3 -march=native -fprofile-generate

dgesv_gcc_o3_pfprof_use: dgesv.c
	gcc  -g3   dgesv.c  -lopenblas -o dgesv_gcc -O3 -march=native -fprofile-use

dgesv_gcc_ofast_pfprof_gen: dgesv.c
	gcc  -g3   dgesv.c  -lopenblas -o dgesv_gcc -Ofast -march=native -fprofile-generate

dgesv_gcc_ofast_pfprof_use: dgesv.c
	gcc  -g3   dgesv.c  -lopenblas -o dgesv_gcc -Ofast -march=native -fprofile-use

# Modules needed: intel imkl
# => module load intel imkl
# You need to uncomment the header for mkl
dgesv_icc_o0: dgesv.c
	icc  -g3   dgesv.c  -mkl -o dgesv_icc -O0 -xHost

dgesv_icc_o1: dgesv.c
	icc  -g3   dgesv.c  -mkl -o dgesv_icc -O1 -xHost

dgesv_icc_o2: dgesv.c
	icc  -g3   dgesv.c  -mkl -o dgesv_icc -O2 -xHost

dgesv_icc_o3: dgesv.c
	icc  -g3   dgesv.c  -mkl -o dgesv_icc -O3 -xHost

dgesv_icc_ofast: dgesv.c
	icc  -g3   dgesv.c  -mkl -o dgesv_icc -Ofast -xHost

dgesv_icc_o0_prof_gen: dgesv.c
	icc  -g3   dgesv.c  -mkl -o dgesv_icc -O0 -xHost -prof-gen

dgesv_icc_o0_prof_use: dgesv.c
	icc  -g3   dgesv.c  -mkl -o dgesv_icc -O0 -xHost -prof-use

dgesv_icc_o0_parallel: dgesv.c
	icc  -g3   dgesv.c  -mkl -o dgesv_icc -O0 -xHost -parallel

dgesv_icc_o3_prof_gen: dgesv.c
	icc  -g3   dgesv.c  -mkl -o dgesv_icc -O3 -xHost -prof-gen

dgesv_icc_o3_prof_use: dgesv.c
	icc  -g3   dgesv.c  -mkl -o dgesv_icc -O3 -xHost -prof-use

dgesv_icc_ofast_prof_gen: dgesv.c
	icc  -g3   dgesv.c  -mkl -o dgesv_icc -Ofast -xHost -prof-gen

dgesv_icc_ofast_prof_use: dgesv.c
	icc  -g3   dgesv.c  -mkl -o dgesv_icc -Ofast -xHost -prof-use
