/*
 * Copyright (C) 2011-2012 Free Software Foundation, Inc.
 *
 * Author: Nikos Mavrogiannopoulos
 *
 * This file is part of GnuTLS.
 *
 * The GnuTLS is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 */

/*
 * The following code is an implementation of the AES-128-GCM cipher
 */

#include <gnutls_errors.h>
#include <gnutls_int.h>

#ifdef HAVE_LIBNETTLE

#include <gnutls/crypto.h>
#include <gnutls_errors.h>
#include <aes-x86.h>
#include <x86.h>
#include <byteswap.h>
#include <nettle/gcm.h>
#include <aes-x86.h>

/* GCM mode 
 * It is used when the CPU doesn't include the PCLMUL instructions.
 */
struct gcm_x86_aes_ctx GCM_CTX(AES_KEY);

static void x86_aes_encrypt(void *_ctx,
				unsigned length, uint8_t * dst,
				const uint8_t * src)
{
	AES_KEY *ctx = _ctx;

	vpaes_encrypt(src, dst, ctx);
}

static void x86_aes_set_encrypt_key(void *_ctx,
					unsigned length,
					const uint8_t * key)
{
	AES_KEY *ctx = _ctx;

	vpaes_set_encrypt_key(key, length*8, ctx);
}

static int
aes_gcm_cipher_init(gnutls_cipher_algorithm_t algorithm, void **_ctx,
		    int enc)
{
	/* we use key size to distinguish */
	if (algorithm != GNUTLS_CIPHER_AES_128_GCM &&
	    algorithm != GNUTLS_CIPHER_AES_256_GCM)
		return GNUTLS_E_INVALID_REQUEST;

	*_ctx = gnutls_calloc(1, sizeof(struct gcm_x86_aes_ctx));
	if (*_ctx == NULL) {
		gnutls_assert();
		return GNUTLS_E_MEMORY_ERROR;
	}

	return 0;
}

static int
aes_gcm_cipher_setkey(void *_ctx, const void *userkey, size_t keysize)
{
	struct gcm_x86_aes_ctx *ctx = _ctx;

	GCM_SET_KEY(ctx, x86_aes_set_encrypt_key, x86_aes_encrypt,
		    keysize, userkey);

	return 0;
}

static int aes_gcm_setiv(void *_ctx, const void *iv, size_t iv_size)
{
	struct gcm_x86_aes_ctx *ctx = _ctx;

	if (iv_size != GCM_BLOCK_SIZE - 4)
		return gnutls_assert_val(GNUTLS_E_INVALID_REQUEST);

	GCM_SET_IV(ctx, iv_size, iv);

	return 0;
}

static int
aes_gcm_encrypt(void *_ctx, const void *src, size_t src_size,
		void *dst, size_t length)
{
	struct gcm_x86_aes_ctx *ctx = _ctx;

	GCM_ENCRYPT(ctx, x86_aes_encrypt, src_size, dst, src);

	return 0;
}

static int
aes_gcm_decrypt(void *_ctx, const void *src, size_t src_size,
		void *dst, size_t dst_size)
{
	struct gcm_x86_aes_ctx *ctx = _ctx;

	GCM_DECRYPT(ctx, x86_aes_encrypt, src_size, dst, src);
	return 0;
}

static int aes_gcm_auth(void *_ctx, const void *src, size_t src_size)
{
	struct gcm_x86_aes_ctx *ctx = _ctx;

	GCM_UPDATE(ctx, src_size, src);

	return 0;
}

static void aes_gcm_tag(void *_ctx, void *tag, size_t tagsize)
{
	struct gcm_x86_aes_ctx *ctx = _ctx;

	GCM_DIGEST(ctx, x86_aes_encrypt, tagsize, tag);
}

static void aes_gcm_deinit(void *ctx)
{
	gnutls_free(ctx);
}

const gnutls_crypto_cipher_st aes_gcm_x86_ssse3 = {
	.init = aes_gcm_cipher_init,
	.setkey = aes_gcm_cipher_setkey,
	.setiv = aes_gcm_setiv,
	.encrypt = aes_gcm_encrypt,
	.decrypt = aes_gcm_decrypt,
	.deinit = aes_gcm_deinit,
	.tag = aes_gcm_tag,
	.auth = aes_gcm_auth,
};

#endif
