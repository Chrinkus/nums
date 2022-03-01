/* nums_data.c
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
#include "nums_data.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>	/* snprintf */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 

/**
 * str_append
 *
 * Add a character to the end of a string. Caller is responsible for
 * ensuring there is enough room.
 */
static void
str_append(char* s, char ch)
{
	while (*s)
		++s;
	*s++ = ch;
	*s = '\0';
}

/**
 * str_prepend
 *
 * Add a character to the front of a string. Caller is responsible for
 * ensuring there is enough room.
 */
static void
str_prepend(char* s, char ch)
{
	for (char tmp = *s; ch; *s++ = ch, ch = tmp)
		if (tmp)
			tmp = *s;
	*s = '\0';
}

/**
 * str_shift
 *
 * Shift all characters towards the front of the string, removing first
 * character.
 */
static void
str_shift(char* s)
{
	for (char* p = s+1; *s; ++s, ++p)
		*s = *p;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 

enum nums_data_buffer_size { NUMS_DATA_MAXBUFF = 16 };

enum nums_data_string_indexes {
	ND_ZERO,
	ND_ERROR,
	ND_NUM_STRINGS
};
const char* const nums_data_strings[ND_NUM_STRINGS] = {
	[ND_ZERO]	= "0",
	[ND_ERROR]	= "Error",
};

struct nums_data {
	char buffer[NUMS_DATA_MAXBUFF];
	double store;
	enum nums_data_op op;
};

struct nums_data*
nums_data_new(void)
{
	struct nums_data* data = malloc(sizeof(struct nums_data));
	strcpy(data->buffer, nums_data_strings[ND_ZERO]);
	data->store = 0.0;
	return data;
}

void
nums_data_free(struct nums_data* data)
{
	free(data);
}

const char*
nums_data_get_buffer(const struct nums_data* data)
{
	return data->buffer;
}

void
nums_data_clear(struct nums_data* data)
{
	strcpy(data->buffer, nums_data_strings[ND_ZERO]);
}

void
nums_data_eval(struct nums_data* data)
{
	double tmp = strtod(data->buffer, NULL);

	switch (data->op) {
	case NUMS_OP_ADD:	data->store += tmp;	break;
	case NUMS_OP_SUBTRACT:	data->store -= tmp;	break;
	case NUMS_OP_MULTIPLY:	data->store *= tmp;	break;
	case NUMS_OP_DIVIDE:
		if (tmp == 0.0) {
			strcpy(data->buffer, nums_data_strings[ND_ERROR]);
			data->op = NUMS_OP_ERROR;
		} else {
			data->store /= tmp;
		}
		break;
	case NUMS_OP_NONE:	/* fallthrough */
	default:		/* fallthrough */
	}

	if (data->op != NUMS_OP_ERROR) {
		snprintf(data->buffer, NUMS_DATA_MAXBUFF, "%f", data->store);
		data->op = NUMS_OP_NONE;
		data->store = 0.0;
	}
}

void
nums_data_prepare_op(struct nums_data* data, enum nums_data_op op)
{
	if (data->op == NUMS_OP_NONE)
		data->store = strtod(data->buffer, NULL);
	else
		nums_data_eval(data);

	data->op = op;
}

void
nums_data_append_digit(struct nums_data* data, char digit)
{
	if (strcmp(data->buffer, "0") == 0)
		data->buffer[0] = digit;
	else if (strlen(data->buffer) < NUMS_DATA_MAXBUFF - 1)
		str_append(data->buffer, digit);
}

void
nums_data_append_decimal(struct nums_data* data)
{
	if (!strchr(data->buffer, '.') &&
			strlen(data->buffer) < NUMS_DATA_MAXBUFF - 1)
		str_append(data->buffer, '.');
}

void
nums_data_change_sign(struct nums_data* data)
{
	if (data->buffer[0] == '-')
		str_shift(data->buffer);
	else if (strlen(data->buffer) < NUMS_DATA_MAXBUFF - 1)
		str_prepend(data->buffer, '-');
}

