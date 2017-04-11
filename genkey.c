#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <Blum.h>

int main(int argc, char *argv[]){
  if (argc != 4) {
    fprintf(stderr, "Usage : %s <filename of the public key> <filename of the private key> <size of the key>\n\n", argv[0]);
    exit(EXIT_FAILURE);
  }

	mpz_t public_key;
	mpz_t private_key;

	/* Faire:
	 * BBS_step dans Blum.c
	 * genkey.c
	 * encrypt.c
	 * decrypt.c */

	//read_pub_key(argv[1], public_key);
	/* read_key(argv[2], private_key ... */
	//privkeyfn = argv[2]
	//keysize = argv[3];
	
	/* char *reead_plaintext -> (char *){1, 0, 0, 1, 0, ..., 1} */
  // A completer avant 13 avril
	/* BBS_Step returns z_i */
	//read_plaintext();

	/* Génération de clés */
	// Bob choisit s elem R [1, n-1]

	//x0 = s*s mod n;
	//mpz_mul(s_squared, s, s);

	/* res = s_squared mod n */
	//mpz_mod(x_0, s_squared, n);

	/* Génération de la suite chiffrante */

	/* Construction et envoi du chifré */
	
  exit(EXIT_SUCCESS);
}
