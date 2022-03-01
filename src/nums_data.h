/* nums_data.h
 *
 * Copyright (C) 2022 Christopher Schick seeschickrun@gmail.com
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#pragma once

enum nums_data_op {
	NUMS_OP_NONE,
	NUMS_OP_ADD,
	NUMS_OP_SUBTRACT,
	NUMS_OP_MULTIPLY,
	NUMS_OP_DIVIDE,
	NUMS_OP_ERROR,
};

struct nums_data;

struct nums_data*
nums_data_new(void);

void
nums_data_free(struct nums_data* data);

void
nums_data_clear(struct nums_data* data);

void
nums_data_eval(struct nums_data* data);

void
nums_data_prepare_op(struct nums_data* data, enum nums_data_op op);

const char*
nums_data_get_buffer(const struct nums_data* data);

void
nums_data_append_digit(struct nums_data* data, char digit);

void
nums_data_append_decimal(struct nums_data* data);

void
nums_data_change_sign(struct nums_data* data);

