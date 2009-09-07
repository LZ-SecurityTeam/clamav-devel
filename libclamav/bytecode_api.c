/*
 *  ClamAV bytecode internal API
 *
 *  Copyright (C) 2009 Sourcefire, Inc.
 *
 *  Authors: Török Edvin
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 */

#include <stdlib.h>
#include "cltypes.h"
#include "clambc.h"
#include "bytecode_priv.h"
#include "type_desc.h"
#include "bytecode_api.h"
#include "bytecode_api_impl.h"

uint32_t cli_bcapi_test0(struct cli_bc_ctx *ctx, struct foo* s, uint32_t u)
{
    return (s && s->nxt == s && u == 0xdeadbeef) ? 0x12345678 : 0x55;
}

uint32_t cli_bcapi_test1(struct cli_bc_ctx *ctx, uint32_t a, uint32_t b)
{
    return (a==0xf00dbeef && b==0xbeeff00d) ? 0x12345678 : 0x55;
}

int32_t cli_bcapi_read(struct cli_bc_ctx* ctx, uint8_t *data, int32_t size)
{
    if (ctx->fd == -1)
	return -1;
    return pread(ctx->fd, data, size, ctx->off);
}

int32_t cli_bcapi_seek(struct cli_bc_ctx* ctx, int32_t pos, uint32_t whence)
{
    off_t off;
    switch (whence) {
	case 0:
	    off = pos;
	    break;
	case 1:
	    off = ctx->off + pos;
	    break;
	case 2:
	    off = ctx->file_size + pos;
	    break;
    }
    if (off < 0 || off > ctx->file_size)
	return -1;
    ctx->off = off;
    return off;
}