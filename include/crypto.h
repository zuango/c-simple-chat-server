#ifndef CRYPTO_H
#define CRYPTO_H

int encrypt_message(const unsigned char *text, size_t len, unsigned char *out, size_t *out_len);

int decrypt_message(const unsigned char *cipher, size_t len, unsigned char *out, size_t *out_len);

#endif
