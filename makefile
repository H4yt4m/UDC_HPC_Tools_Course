# Module needed: openblas
# => module load openblas
# You need to uncomment the header for openblas
dgesv_gcc: dgesv.c
	gcc  -g3   dgesv.c  -lopenblas -o dgesv_gcc

# Modules needed: intel imkl
# => module load intel imkl
# You need to uncomment the header for mkl
dgesv_icc: dgesv.c
	icc  -g3   dgesv.c  -mkl -o dgesv_icc
