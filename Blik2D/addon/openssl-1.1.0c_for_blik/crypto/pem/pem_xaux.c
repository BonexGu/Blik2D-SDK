/*
 * Copyright 2001-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdio.h>
#include BLIK_OPENSSL_U_internal__cryptlib_h //original-code:"internal/cryptlib.h"
#include BLIK_OPENSSL_V_openssl__bio_h //original-code:<openssl/bio.h>
#include BLIK_OPENSSL_V_openssl__evp_h //original-code:<openssl/evp.h>
#include BLIK_OPENSSL_V_openssl__x509_h //original-code:<openssl/x509.h>
#include BLIK_OPENSSL_V_openssl__pkcs7_h //original-code:<openssl/pkcs7.h>
#include BLIK_OPENSSL_V_openssl__pem_h //original-code:<openssl/pem.h>

IMPLEMENT_PEM_rw(X509_AUX, X509, PEM_STRING_X509_TRUSTED, X509_AUX)
