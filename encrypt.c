#include <Blum.h>

void encrypt_BG(char *file_plain, char *file_cipher, mpz_t n) {
  // A completer
  size_t i;
  char *plaintext, *c;
  unsigned long size;

  gmp_randstate_t state;
  mpz_t x, nminusone;

  mpz_inits(x, nminusone, NULL);
  mpz_sub_ui(nminusone, n, 1);

  read_plaintext(file_plain, &plaintext, &size);

  gmp_randinit_default(state);
  mpz_urandomm(x, state, nminusone);
  /* x elem [0, n-2] */
  mpz_add_ui(x, x, 1);
  /* x elem [1, n-1] */

  /* x0 = s^2 mod n where s elem [1, n-1] */
  BBS_step(&x, n);
  
  c = malloc(size * sizeof(*c));  

  for (i = 0; i < size; ++i) {
    char z = BBS_step(&x, n);
    c[i] = z ^ plaintext[i];
  }

  BBS_step(&x, n);
  write_ciphertext(file_cipher, c, size, x);

  mpz_clears(x, nminusone, NULL);

  free(c);
  free(plaintext);
}

int main(int argc, char *argv[]){
  if (argc != 4) {
    fprintf(stderr, "Usage : %s <filename of the public key> <filename of the plaintext> <filename of the ciphertext>\n\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  // A completer
  mpz_t n;
  mpz_init(n);

  read_pub_key(argv[1], &n);
  encrypt_BG(argv[2], argv[3], n);

  mpz_clear(n);

  exit(EXIT_SUCCESS);
}
