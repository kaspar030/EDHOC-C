#ifndef EDHOC_FORMATTING_H
#define EDHOC_FORMATTING_H

#include <stdint.h>
#include <stddef.h>

#if !defined(EDHOC_CONFIG_FILE)

#include "edhoc/config.h"

#else
#include EDHOC_CONFIG_FILE
#endif

#include "edhoc/edhoc.h"

/**
 * @brief Message encoding routine for EDHOC message_1
 *
 * @param[in] corr          EDHOC correlation value
 * @param[in] method        EDHOC authentication method
 * @param[in] cipher_suite  EDHOC selected cipher suite
 * @param[in] key           Pointer to ephemeral COSE key (message includes only the public part)
 * @param[in] cidi          Pointer to connection identifier (Initiator)
 * @param[in] cidi_len      Length of @p cidi
 * @param[in] ad1           Pointer to additional data
 * @param[in] ad1_len       Length of @p ad1
 * @param[out] out          Output buffer for the CBOR encoded EDHOC message_1
 * @param[in] olen          Maximum capacity of @p out
 *
 * @return On success the size of the EDHOC message_1
 * @return On failure a negative value (EDHOC_ERR_CBOR_ENCODING)
 */
ssize_t edhoc_msg1_encode(corr_t corr,
                          uint8_t method,
                          uint8_t cipher_suite,
                          cose_key_t *key,
                          const uint8_t *cidi,
                          size_t cidi_len,
                          ad_cb_t ad1,
                          uint8_t *out,
                          size_t olen);

/**
 * @brief Message decoding routine for EDHOC message_1
 *
 * @param[in,out] ctx   EDHOC context structure
 * @param[in] msg1      Buffer containing the EDHOC message_1
 * @param[in] msg1_len  Length of @p msg1
 *
 * @return On success, EDHOC_SUCCESS
 * @return On failure a negative return code (EDHOC_ERR_CBOR_DECODING, EDHOC_ERR_BUFFER_OVERFLOW,
 * EDHOC_ERR_ILLEGAL_CIPHERSUITE, ..)
 */
int edhoc_msg1_decode(edhoc_ctx_t *ctx, const uint8_t *msg1, size_t msg1_len);

/**
 * @brief Message encoding routine for EDHOC message_2
 *
 * @param[in] data2         Buffer containing the CBOR encoded EDHOC data_2 structure
 * @param[in] data2_len     Length of @p data2
 * @param[in] ct2           Buffer containing EDHOC ciphertext_2
 * @param[in] ct2_len       Length of @p ct2
 * @param[out] out          Output buffer for the CBOR encoded EDHOC message_2
 * @param[in] olen          Maximum capacity of @p out
 *
 * @return On success returns the size of the EDHOC message_2
 * @return On failure returns a negative value (EDHOC_ERR_CBOR_ENCODING)
 */
ssize_t edhoc_msg2_encode(const uint8_t* data2,
                          size_t data2_len,
                          const uint8_t* ct2,
                          size_t ct2_len,
                          uint8_t* out,
                          size_t olen);

/**
 * @brief Decoding routine for EDHOC message_2
 *
 * @param[in,out] ctx   EDHOC context structure
 * @param[in] msg2      Buffer containing the EDHOC message_2
 * @param[in] msg2_len  Length of @p msg2
 *
 * @return On success returns EDHOC_SUCCESS
 * @return On failure a negative return code (EDHOC_ERR_CBOR_DECODING, EDHOC_ERR_BUFFER_OVERFLOW,
 * EDHOC_ERR_ILLEGAL_CIPHERSUITE, ..)
 */
int edhoc_msg2_decode(edhoc_ctx_t *ctx, const uint8_t *msg2, size_t msg2_len);

/**
 * @brief Message encoding routine for EDHOC message_3
 *
 * @param[in] data3         Buffer containing the CBOR encoded EDHOC data_3 structure
 * @param[in] data3_len     Length of @p data3
 * @param[in] ct3           Buffer containing EDHOC ciphertext_3
 * @param[in] ct3_len       Length of @p ct3
 * @param[out] out          Output buffer for the CBOR encoded EDHOC message_3
 * @param[in] olen          Maximum capacity of @p out
 *
 * @return On success returns the size of the EDHOC message_3
 * @return On failure returns a negative value (EDHOC_ERR_CBOR_ENCODING)
 */
ssize_t edhoc_msg3_encode(const uint8_t* data3,
                          size_t data3_len,
                          const uint8_t* ct3,
                          size_t ct3_len,
                          uint8_t* out,
                          size_t olen);

/**
 * @brief Decoding routine for EDHOC message 3
 *
 * @param[in,out] ctx   Pointer to the EDHOC context structure
 * @param[in] msg3      Buffer containing the EDHOC message 3
 * @param[in] msg3_len  Length of @p msg3
 *
 * @return On success returns EDHOC_SUCCESS
 * @return On failure a negative return code (EDHOC_ERR_CBOR_ENCODING)
 */
int edhoc_msg3_decode(edhoc_ctx_t *ctx, const uint8_t *msg3, size_t msg3_len);

/**
 * @brief Encoding routine for the EDHOC data_2 structure
 *
 * @param[in] corr      EDHOC correlation value.
 * @param[in] cidi      Pointer to the Initiator's connection identifier.
 * @param[in] cidi_len  Length of @p cidi
 * @param[in] cidr      Pointer to the Responder's connection identifier.
 * @param[in] cidr_len  Length of @p cidr
 * @param[in] eph_key   Pointer to Responder's ephemeral key
 * @param[out] out      Output buffer
 * @param[in] olen      Maximum length of @p out
 *
 * @return On success the size of data_2 message part
 * @return On failure a negative value (EDHOC_ERR_CBOR_ENCODING, ..)
 */
ssize_t edhoc_data2_encode(corr_t corr,
                           const uint8_t *cidi,
                           size_t cidi_len,
                           const uint8_t *cidr,
                           size_t cidr_len,
                           const cose_key_t *eph_key,
                           uint8_t *out,
                           size_t olen);

/**
 * @brief Encoding routine for the EDHOC data_3 structure
 *
 * @param[in] corr         EDHOC correlation value
 * @param[in] cidr         Connection identifier of the responder
 * @param[in] cidr_len     Length @p cidr
 * @param[out] out         Output buffer for the CBOR encoded EDHOC message_3
 * @param[in] olen         Maximum capacity if @p out
 *
 * @return On success returns the size of the EDHOC message_3
 * @return On failure returns a negative value (e.g. EDHOC_CBOR_ERR_ENCODING)
 */
ssize_t edhoc_data3_encode(corr_t corr, const uint8_t *cidr, size_t cidr_len, uint8_t *out, size_t olen);

/**
 * @brief Encoding routine for the EDHOC-KDF info structure
 *
 * @param[in] id        COSE algorithm identifier
 * @param[in] th        Transcript hash
 * @param[in] label     String label
 * @param[in] len       The length of the KDF output
 * @param[out] out      Output buffer
 * @param[in] olen     The maximum capacity of @p out
 *
 * @returns  On success, length of the final CBOR encode info byte string
 * @returns  On failure, EDHOC_ERR_CBOR_ENCODING or another negative value
 **/
ssize_t edhoc_info_encode(cose_algo_t id, const uint8_t *th, const char *label, size_t len, uint8_t *out, size_t olen);

/**
 * @brief Creates the external additional data for a COSE message.
 *
 * @param[in] th        Transcript hash
 * @param[in] cred      Public credentials (CBOR certificate or public key)
 * @param[in] cred_len  Length of @p cred
 * @param[out] out      Output buffer
 * @param[in] olen      Maximum length of @p out
 *
 * @return On success the size of the external data
 * @return On failure a negative error code (EDHOC_ERR_CBOR_ENCODING, ..)
 */
ssize_t edhoc_cose_external_aad_encode(const uint8_t *th,
                                       const uint8_t *cred,
                                       size_t cred_len,
                                       ad_cb_t ad2,
                                       uint8_t *out,
                                       size_t olen);

/**
 * @brief Create the Enc structure for the COSE Encrypt0 message
 *
 * @param[in] cred_id           Pointer to the credential identifier
 * @param[in] cred_id_len       Length of @p cred_id
 * @param[in] external_aad      Pointer to the external additional data for the COSE Encrypt0 message
 * @param[in] external_aad_len  Length of @p external_aad
 * @param[out] out              Buffer to store the CBOR encoded Enc structure
 * @param[in] olen              Maximum length of @p out
 *
 * @return On success the size of the CBOR encoded Enc structure
 * @return On failure a negative value (EDHOC_ERR_CBOR_ENCODING, ...)
 */
ssize_t edhoc_cose_enc_struct_encode(const uint8_t *cred_id,
                                     size_t cred_id_len,
                                     const uint8_t *external_aad,
                                     size_t external_aad_len,
                                     uint8_t *out,
                                     size_t olen);


/**
 * @brief Decodes P_2e and verifies the included signature
 *
 * @param[in] p2e       Plaintext included in EDHOC message 2
 * @param[in] p2e_len   Length of @p p2e
 *
 * @return On success returns EDHOC_SUCCESS
 * @return On failure a negative value (i.e., EDHOC_ERR_CRYPTO, EDHOC_ERR_CBOR_DECODING, ...)
 */
int edhoc_p2e_decode(uint8_t *p2e, size_t p2e_len);

/**
 * @brief Decodes P_3ae and verifies the included signature
 *
 * @param[in] p3ae       Plaintext included in EDHOC message 3
 * @param[in] p3ae_len   Length of @p p3ae
 *
 * @return On success returns EDHOC_SUCCESS
 * @return On failure a negative value (i.e., EDHOC_ERR_CRYPTO, EDHOC_ERR_CBOR_DECODING, ...)
 */
int edhoc_p3ae_decode(uint8_t *p3ae, size_t p3ae_len);


/**
 * @brief Encoding routine for the associated data structure (A_3ae) in the outer COSE_Encrypt0 structure in
 * EDHOC message_3
 *
 * @param[in] th3       Transcript hash 3
 * @param[out] out      Output buffer for the result
 * @param[in] olen      Maximum capacity of @p out
 *
 * @return On success returns the size of A_3ae
 * @return On failure a negative value (i.e., EDHOC_ERR_CBOR_ENCODING, ...)
 */
ssize_t edhoc_a3ae_encode(const uint8_t *th3, uint8_t *out, size_t olen);

/**
 * @brief Encoding routine for the plaintext structures (P_2e and P_3ae) in EDHOC message_2 and message_3
 *
 * @param[in] ctx       Pointer to an EDHOC context structure
 * @param[out] out      Pointer to output buffer to store the P_2e CBOR sequence
 * @param[in] olen      Maximum length of @p out
 *
 * @return On success returns the size of P_2e or P_3ae
 * @return On failure a negative value (i.e., EDHOC_ERR_CBOR_ENCODING, ...)
 */
ssize_t edhoc_p2e_or_p3ae_encode(edhoc_ctx_t *ctx, uint8_t *signature_23, uint8_t *out, size_t olen);


#endif /* EDHOC_FORMATTING_H */
