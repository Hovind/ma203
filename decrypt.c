#include <Blum.h>


void decrypt_BG(char *file_cipher, char *file_plain, mpz_t p, mpz_t q) {
  // A completer
  size_t i;
  unsigned long size;
  char *c, *m;
  mpz_t x, n, d1, d2, a, b, u, v, pminusone, qminusone, tplusone;

  read_ciphertext(file_cipher, &c, &size, &x);

  mpz_inits(x, n, d1, d2, a, b, u, v, pminusone, qminusone, tplusone, NULL);
  mpz_set_ui(tplusone, size+1);
  mpz_sub_ui(pminusone, p, 1);
  mpz_sub_ui(qminusone, p, 1);

  /*d1 = ((p+1)/4)^(t+1) mod (p-1)*/
  mpz_add_ui(d1, p, 1);
  mpz_cdiv_q_ui(d1, d1, 4);
  mpz_powm(d1, d1, tplusone, pminusone);

  /*d2 = ((q+1)/4)^(t+1) mod (q-1)*/
  mpz_add_ui(d2, q, 1);
  mpz_cdiv_q_ui(d2, d2, 4);
  mpz_powm(d2, d2, tplusone, qminusone);

  /*u = x^d1 mod p*/
  mpz_powm(u, x, d1, p);

  /*v = x^d2 mod q*/
  mpz_powm(v, x, d2, q);

  /*a = p^-1 mod q*/
  mpz_invert(a, p, q);

  /*b = q^-1 mod p*/
  mpz_invert(b, q, p);

  /*v = v*a*p*/
  mpz_mul(v, v, a);
  mpz_mul(v, v, p);

  /*u = u*b*q*/
  mpz_mul(u, u, b);
  mpz_mul(u, u, q);

  /*x = v + u*/
  mpz_add(x, v, u);

  /*x = x mod n*/
  mpz_mul(n, p, q);
  mpz_mod(x, x, n);

  mpz_clears(n, d1, d2, a, b, u, v, pminusone, qminusone, tplusone, NULL);

  m = malloc(size * sizeof(*m));
  for (i = 0; i < size; ++i) {
    char z = BBS_step(&x, n);
    m[i] = z ^ c[i];
  }
  write_plaintext(file_plain, m, size);

  mpz_clear(x);

  free(c);
  free(m);
}

int main(int argc, char *argv[]){
  if (argc != 4) {
    fprintf(stderr, "Usage : %s <filename of the private key> <filename of the ciphertext> <filename of the plaintext>\n\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // A completer
  mpz_t p, q;
  mpz_inits(p, q, NULL);
  printf("0\n");

  read_key(argv[1], &p, &q);
  decrypt_BG(argv[2], argv[3], p, q);

  mpz_clears(p, q, NULL);

  exit(EXIT_SUCCESS);
}
