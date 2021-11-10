#ifndef rsa_h
#define rsa_h

__declspec(dllexport) unsigned rsa_genkey(unsigned *e, unsigned *d);
__declspec(dllexport) unsigned rsa_encrypt(unsigned m, unsigned e, unsigned n, unsigned *crypt);
__declspec(dllexport) unsigned rsa_decrypt(unsigned crypt, unsigned d, unsigned n, unsigned *decrypt);

#endif

