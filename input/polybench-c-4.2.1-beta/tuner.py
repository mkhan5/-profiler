import subprocess

l1=[gemm,gesummv,bicg,mvt,syr2k,atax,cholesky,gramschmidt,lu,gemver]

l2=[gemm1,gesummv1,bicg1,mvt1,syr2k1,atax1,cholesky1,gramschmidt1,lu1,gemver1]

for l in l1:
	for i in range(0,5):
		subprocess.Popen("time ./"+l,
