# Module needed: openblas
# => module load openblas
# You need to uncomment the header for openblas
dgesv_gcc: dgesv_updated.c
	gcc  -g3   dgesv_updated.c  -lopenblas -o dgesv_gcc

# Modules needed: intel imkl
# => module load intel imkl
# You need to uncomment the header for mkl
dgesv_icc: dgesv_updated.c
	icc  -g3   dgesv_updated.c  -mkl -o dgesv_icc
