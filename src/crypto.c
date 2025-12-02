#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <string.h>
#include "crypto.h"

static unsigned char KEY[32] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
                                 17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32 };

static unsigned char IV[16]  = { 9,8,7,6,5,4,3,2,1,0,1,2,3,4,5,6 };

int encrypt_message(const unsigned char *plaintext, size_t len,
                    unsigned char *out, size_t *out_len)
{
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    int l, total = 0;
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, KEY, IV);
    EVP_EncryptUpdate(ctx, out, &l, plaintext, len);
    total += l;
    EVP_EncryptFinal_ex(ctx, out + total, &l);
    total += l;

    // append HMAC
    unsigned int hmac_len = 0;
    unsigned char *hmac = HMAC(EVP_sha256(), KEY, 32,
                               out, total, out + total, &hmac_len);

    *out_len = total + hmac_len;

    EVP_CIPHER_CTX_free(ctx);
    return 1;
}

int decrypt_message(const unsigned char *cipher, size_t len,
                    unsigned char *out, size_t *out_len)
{
    // last 32 bytes = HMAC
    if (len < 32) return 0;

    size_t cipher_len = len - 32;
    unsigned char expected_hmac[32];

    unsigned int hmac_len = 0;
    HMAC(EVP_sha256(), KEY, 32,
         cipher, cipher_len,
         expected_hmac, &hmac_len);

    if (memcmp(expected_hmac, cipher + cipher_len, 32) != 0)
        return 0;

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int l, total = 0;

    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, KEY, IV);
    EVP_DecryptUpdate(ctx, out, &l, cipher, cipher_len);
    total += l;
    EVP_DecryptFinal_ex(ctx, out + total, &l);
    total += l;

    *out_len = total;
    EVP_CIPHER_CTX_free(ctx);

    return 1;
}
