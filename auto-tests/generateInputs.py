''' _______________________________________________________________________________
 * »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
 *
 * generateInputs.py
 *
 * -------------------------------------------------------------------------------
 *
 * Made by: Vasco Faria
 *
 * «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««
'''
from random import randint

def contains(l, u, v):
	for el in lst:
		if (el == (u, v) and el == (v, u)):
			return False

N=60000

print(str(N))
print(str(N))

lst = []
lst += [(randint(1, N), randint(1, N))]

i=0

while i < N:
	u = randint(1, N)
	v = randint(1, N)
	if not contains(lst, u, v):
		lst += [(u, v)]
		i += 1
		print(str(u) + " " + str(v))


'''______________________________________________________________________________
 * »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
 *
 * End of generateInputs.py
 *
 * «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««
'''
