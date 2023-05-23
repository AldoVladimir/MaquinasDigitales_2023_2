#include "mbedtls/aes.h"

void encrypt(char * plainText, char * key, unsigned char * outputBuffer){

  mbedtls_aes_context aes;

  mbedtls_aes_init(&aes);
  mbedtls_aes_setkey_enc(&aes, (const unsigned char *) key, strlen(key)*8);
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, (const unsigned char *) plainText, outputBuffer);
  mbedtls_aes_free(&aes);
}

void decrypt(unsigned char * cipherText, char * key, unsigned char * outputBuffer){

  mbedtls_aes_context aes;

  mbedtls_aes_init(&aes);
  mbedtls_aes_setkey_enc(&aes, (const unsigned char *) key, strlen(key)*8);
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, (const unsigned char *) cipherText, outputBuffer);
  mbedtls_aes_free(&aes);
}

void setup() {
  
  Serial.begin(115200);

  char * key = "abcdefghijklmnop";    // Un char equivale a un Btye. 1 Byte = 8 bits (a - 97DEC - 0110 0001b). 16 chars = 128 bits => AES128
  char * plainText = "Maquinas Digitales";

  unsigned char cipherTextOutput[18];
  unsigned char decipheredTextOutput[18];

  encrypt(plainText, key, cipherTextOutput);
  decrypt(cipherTextOutput, key, decipheredTextOutput);

  Serial.println("Texto original: ");
  Serial.println(plainText);

  Serial.println("Texto cifrado: ");
  for(int i=0; i<18; i++){
    Serial.print((char)cipherTextOutput[i]);
  }

  Serial.println("Texto desencriptado: ");
  for(int i=0; i<18; i++){
    Serial.print((char)decipheredTextOutput[i]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
