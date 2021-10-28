/* Provide SSL/TLS functions to ESP32 with Arduino IDE
 * by Evandro Copercini - 2017 - Apache 2.0 License
 */

#ifndef SSL_PPPOS_SSL_H
#define SSL_PPPOS_SSL_H
#include "mbedtls/platform.h"
#include "mbedtls/net.h"
#include "mbedtls/debug.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/error.h"

typedef struct sslclient_context_t {
    int socket;
    mbedtls_ssl_context ssl_ctx;
    mbedtls_ssl_config ssl_conf;

    mbedtls_ctr_drbg_context drbg_ctx;
    mbedtls_entropy_context entropy_ctx;

    mbedtls_x509_crt ca_cert;
    mbedtls_x509_crt client_cert;
    mbedtls_pk_context client_key;

    unsigned long handshake_timeout;
} sslclient_context_t;


void _ssl_init(sslclient_context_t *ssl_client);
int _start_ssl_client(sslclient_context_t *ssl_client, const char *host, uint32_t port, int timeout, const char *rootCABuff, const char *cli_cert, const char *cli_key, const char *pskIdent, const char *psKey, bool insecure);
void _stop_ssl_socket(sslclient_context_t *ssl_client, const char *rootCABuff, const char *cli_cert, const char *cli_key);
int _data_to_read(sslclient_context_t *ssl_client);
int _send_ssl_data(sslclient_context_t *ssl_client, const uint8_t *data, size_t len);
int _get_ssl_receive(sslclient_context_t *ssl_client, uint8_t *data, int length);
bool _verify_ssl_fingerprint(sslclient_context_t *ssl_client, const char* fp, const char* domain_name);
bool _verify_ssl_dn(sslclient_context_t *ssl_client, const char* domain_name);

#endif
