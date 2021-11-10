#include "pch.h"
#include "rsa.h"
#include <cstdlib>

unsigned rsa_simple();
unsigned rsa_gcd(unsigned a, unsigned b);

unsigned rsa_simple()
{
	unsigned r = (rand() % 256 + 2) | 1;

	while (1)
		unsigned i;
		for (i = 3; i * i <= r; i += 2)
		{
			if (r % i == 0)
				break;
		}

		if (i * i > r)
			return r;
		else
			r += 2;
	}
}

unsigned rsa_gcd(unsigned a, unsigned b)
{
	while (b != 0)
	{
		unsigned r = a % b;
		a = b; 
		b = r;
	}
	return a;
}

unsigned rsa_genkey(unsigned *e, unsigned *d) 
{
	unsigned p = rsa_simple();
	unsigned q;

	do
	{
		q = rsa_simple();
	} while (p == q);

	unsigned n = p * q;
	unsigned f = (p - 1) * (q - 1); 

	
	unsigned temp1 = 3;
	while (rsa_gcd(temp1, f) != 1)
		temp1 += 2;
		
	unsigned temp2 = 2;
	while (temp2 * temp1 % f != 1)
		temp2 += 1;

	*e = temp1;
	*d = temp2;
	
	return n;
}

unsigned rsa_encrypt(unsigned m, unsigned e, unsigned n, unsigned *crypt)
{
	if (m >= n)
		return 1;

	unsigned res = 1;
	for (unsigned i = 0; i < e; i++)
		res = res * m % n;
	*crypt = res;

	return 0;
}

unsigned rsa_decrypt(unsigned crypt, unsigned d, unsigned n, unsigned *decrypt)
{
	return rsa_encrypt(crypt, d, n, decrypt);
}

