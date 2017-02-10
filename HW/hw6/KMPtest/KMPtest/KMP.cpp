//ddd

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <string.h>

P=set{P1,P2,...,PK}
Native-String-Matcher(T, P)
{
N=T.length
for i=0 to K-1
	M[i]=Pi.length
	for s=0 to N-M[i]
		if P[1..M[i]]==T[s+1..s+M[i]]
			print "Pattern " i+1 "occurs with shift " s
}


P=set{P1,P2,...,PK}
Compute-Prefix-Function(P)
{
for i=0 to K-1
	M[i]=Pi.length
	let 𝜋[i][1..𝑚] be a new array
	𝜋[i][1]=0
	j=0
	for q=2 to M[i]
		while k>0 and Pi[j+1]!=Pi[q]
			j=𝜋[i][j]
		if Pi[j+1]==Pi[q]
			j=j+1
		𝜋[i][𝑞]=j
return 𝜋
}

KMP-Matcher(T,P)
{
N=T.length
𝜋=Compute-Prefix-Function(P)
for i=0 to K-1
	M[i]=Pi.length
	q=0
	for n=1 to N
		while q>0 && Pi[q+1]!=T[i]
			q=𝜋[i][q]
		if Pi[q+1]==T[i]
			q=q+1
		if q==m
			print "Pattern " i+1 "occurs with shift " n-M[i]
		q=𝜋[i][q]
}