#ifndef SRC_OVERFLOW_DECIMAL_H_
#define SRC_OVERFLOW_DECIMAL_H_

#include <math.h>

typedef enum {
    s21_NORMAL_VALUE_OVF = 0,
    s21_INFINITY_OVF = 1,
    s21_NEGATIVE_INFINITY_OVF = 2,
    s21_NAN_OVF = 3,
    s21_ADDCODE_OVF = 4
} value_type_t_overflow;


typedef struct {
    unsigned bits[7];
    value_type_t_overflow value_type;
} s21_overflow_decimal;


s21_overflow_decimal overflow_add(s21_overflow_decimal par_a, s21_overflow_decimal par_b);
s21_overflow_decimal overflow_mul(s21_overflow_decimal dec_a, s21_overflow_decimal dec_b, int* res_scale);
s21_overflow_decimal overflow_div(s21_overflow_decimal dec_a, s21_overflow_decimal dec_b, int* res_scale);
s21_overflow_decimal shift_left_overflow(s21_overflow_decimal d, int offset);
s21_overflow_decimal simple_overflow_mul(s21_overflow_decimal dec_a, s21_overflow_decimal dec_bs);
s21_overflow_decimal div_simple_ovf(s21_overflow_decimal dec1, s21_overflow_decimal dec2);
s21_overflow_decimal shift_right_overflow(s21_overflow_decimal src, int shift);
s21_overflow_decimal mod_ovf(s21_overflow_decimal dec1, s21_overflow_decimal dec2);
s21_overflow_decimal  overflow_sub(s21_overflow_decimal dec_a, s21_overflow_decimal dec_b);
s21_overflow_decimal overflow_decimal_increase_scale(int diffScale, int src_scale,
                                                        s21_overflow_decimal src_s);
void norm_scale_ovf(s21_overflow_decimal*dec1_s, s21_overflow_decimal*dec2_s, int dec1_scale, int dec2_scale);
int shift_left_for_div_ovf(s21_overflow_decimal dec1, s21_overflow_decimal* dec2);
unsigned get_bit_dec_ovf(s21_overflow_decimal dst, unsigned bit);
void set_bit_dec_ovf(s21_overflow_decimal* dst, unsigned num_bit, unsigned set);
int overflow_is_less(s21_overflow_decimal dec_a, s21_overflow_decimal dec_b);
int overflow_is_greater(s21_overflow_decimal dec_a, s21_overflow_decimal dec_b);
int is_zero_dec_ovf(s21_overflow_decimal dec_a, s21_overflow_decimal dec_b);
int compare_func_ovf(s21_overflow_decimal dec_a, s21_overflow_decimal dec_b);
int dec_nan_ovf(s21_overflow_decimal* dec_a, s21_overflow_decimal* dec_b);
int dec_inf_ovf(s21_overflow_decimal* dec_a, s21_overflow_decimal* dec_b);
int dec_neg_inf_ovf(s21_overflow_decimal* dec_a, s21_overflow_decimal* dec_b);
unsigned get_last_bit_ovf(s21_overflow_decimal src);
int overflow_is_equal(s21_overflow_decimal dec_a, s21_overflow_decimal dec_b);
void overflow_to_addcode(s21_overflow_decimal* dec);
unsigned dec_div_10_overflow(s21_overflow_decimal* src);
#endif  // SRC_OVERFLOW_DECIMAL_H_
