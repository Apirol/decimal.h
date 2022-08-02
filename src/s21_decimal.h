#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "overflow_decimal.h"

#define TRUE 0
#define FALSE 1
#define EPSILON 1e-7
#define SIGN 0x80000000

typedef enum {
    s21_NORMAL_VALUE = 0,
    s21_INFINITY = 1,
    s21_NEGATIVE_INFINITY = 2,
    s21_NAN = 3,
    s21_ADDCODE = 4,
} value_type_t;

typedef struct {
    unsigned bits[4];
    value_type_t value_type;
} s21_decimal;

typedef union {
    float f;
    struct {
        unsigned man : 23;
        unsigned exp : 8;
        unsigned sign : 1;
    } raw;
} float_union;


typedef union {
    int ui;
    float fl;
} floatbits;



// ==Convertors and parsers== //

int s21_from_int_to_decimal(int src, s21_decimal* dst);
int s21_from_float_to_decimal(float src, s21_decimal* dst);
int s21_from_decimal_to_int(s21_decimal src, int* dst);
int s21_from_decimal_to_float(s21_decimal src, float* dst);

// ==Arithmetic Operators== //

s21_decimal s21_add(s21_decimal dec_a, s21_decimal dec_b);  // Сложение
s21_decimal s21_sub(s21_decimal dec_a, s21_decimal dec_b);  // Вычитание
s21_decimal s21_mul(s21_decimal dec_a, s21_decimal dec_b);  // Умножение
s21_decimal s21_div(s21_decimal dec_a, s21_decimal dec_b);  // Деление
s21_decimal basic_div(s21_decimal a, s21_decimal b);
s21_decimal s21_mod(s21_decimal, s21_decimal);  // Взятие по модулю

// ==Comparison Operators== //

int s21_is_less(s21_decimal dec_a, s21_decimal dec_b);  // dec_a < dec_b
int s21_is_less_or_equal(s21_decimal dec_a,
    s21_decimal dec_b);               // dec_a <= dec_b
int s21_is_greater(s21_decimal dec_a, s21_decimal dec_b);  // dec_a > dec_b
int s21_is_greater_or_equal(s21_decimal dec_a,
    s21_decimal dec_b);              // dec_a >= dec_b
int s21_is_equal(s21_decimal dec_a, s21_decimal dec_b);      // dec_a == dec_b
int s21_is_not_equal(s21_decimal dec_a, s21_decimal dec_b);  // dec_a != dec_b

// ==Another functions== //

s21_decimal s21_floor(s21_decimal src);
s21_decimal s21_round(s21_decimal src);
s21_decimal s21_truncate(s21_decimal src);
s21_decimal s21_negate(s21_decimal src);

// ==Dop functions== //

void init_dec_bits(s21_decimal* dst);
void set_bit(unsigned int* dst, unsigned bit, unsigned set);
unsigned get_bit(int src, unsigned bit);
void set_bit_dec(s21_decimal* dst, unsigned bit, unsigned set);
unsigned get_bit_dec(s21_decimal dst, unsigned bit);
void shift(s21_decimal* src, int offset);
unsigned get_scale(s21_decimal src);
void set_scale(s21_decimal* src, unsigned scale);
void set_dec_scale(s21_decimal* dst, int scale);
s21_decimal summ(s21_decimal par_a, s21_decimal par_b);
unsigned dec_div_10(s21_decimal* src);
int compar_func(s21_decimal dec_a, s21_decimal dec_b);
int norm_scale(s21_decimal* dec_a, s21_decimal* dec_b);
int dec_nan(s21_decimal* dec_a, s21_decimal* dec_b);
int dec_inf(s21_decimal* dec_a, s21_decimal* dec_b);
int dec_neg_inf(s21_decimal* dec_a, s21_decimal* dec_b);
int is_zero_dec(s21_decimal dec_a, s21_decimal dec_b);
void only_bits_equals(s21_decimal src, s21_decimal* dst);
int last_bit(s21_decimal dec);
void dec_to_addcode(s21_decimal* dec);
void clear_dec(s21_decimal* dec);
s21_decimal str_to_dec(char binary_number[], s21_decimal* dec, int point_place);
int getFloatSign(float* src);
int getFloatExp(float* src);
unsigned get_last_bit(s21_decimal src);
s21_decimal validate_mul(s21_decimal dec_1, s21_decimal dec_2);
s21_decimal validate_div(s21_decimal dec_a, s21_decimal dec_b);
s21_decimal div_only_bit(s21_decimal dec_a, s21_decimal dec_b,
    s21_decimal* remainder);
unsigned dec_div_10_round(s21_decimal* src);

s21_decimal shift_left(s21_decimal d, int offset);
s21_decimal shift_right(s21_decimal src, unsigned offset);
int get_parity(s21_decimal src, int scale);
value_type_t convert_type(s21_overflow_decimal dec);
// ==Overflow convertors==
s21_overflow_decimal init_overflow(s21_decimal src);
#endif  // SRC_S21_DECIMAL_H_
