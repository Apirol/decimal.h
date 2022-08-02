#include "s21_decimal.h"

// ==Convertors and parsers== //

int s21_from_int_to_decimal(int src, s21_decimal* dst) {
    int res = TRUE;
    if (dst) {
        init_dec_bits(dst);
        if (src < 0) {
            src *= -1;
            set_bit_dec(dst, 127, 1);
        }
        dst->bits[0] = src;
        dst->value_type = s21_NORMAL_VALUE;
    } else {
        res = FALSE;
    }
    return res;
}

int s21_from_decimal_to_int(s21_decimal src, int* dst) {
    int res = 1;
    if (&src != NULL && dst != NULL && src.value_type == s21_NORMAL_VALUE) {
        *dst = src.bits[0];
        *dst *= get_bit_dec(src, 127) ? -1 : 1;
        *dst /= (int)pow(10, get_scale(src));
        res = 0;
    }
    return res;
}

int s21_from_float_to_decimal(float src, s21_decimal* dst) {
    int result = FALSE;
    if (&src && dst) {
        dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
        dst->value_type = s21_NORMAL_VALUE;
        int sign = getFloatSign(&src), exp = getFloatExp(&src);

        if (isinf(src) && !sign)
            dst->value_type = s21_INFINITY;
        else if (isinf(src) && sign)
            dst->value_type = s21_NEGATIVE_INFINITY;
        else if (isnan(src))
            dst->value_type = s21_NAN;

        if (dst && dst->value_type == s21_NORMAL_VALUE && src != 0) {
            double temp = (double)fabs(src);
            int off = 0;
            for (; off < 28 && (int)temp / (int)pow(2, 21) == 0;
                temp *= 10, off++) {
            }
            temp = round(temp);
            if (off <= 28 && (exp > -94 && exp < 96)) {
                floatbits mant;
                temp = (float)temp;
                for (; fmod(temp, 10) == 0 && off > 0; off--, temp /= 10) {
                }
                mant.fl = temp;
                exp = getFloatExp(&mant.fl);
                dst->bits[exp / 32] |= 1 << exp % 32;
                for (int i = exp - 1, j = 22; j >= 0; i--, j--)
                    if ((mant.ui & (1 << j)) != 0)
                        dst->bits[i / 32] |= 1 << i % 32;
                dst->bits[3] = (sign << 31) | (off << 16);
                result = TRUE;
            }
        }
    }
    return result;
}

int s21_from_decimal_to_float(s21_decimal src, float* dst) {
    int result = FALSE;
    if (&src != NULL && dst && src.value_type == s21_NORMAL_VALUE) {
        double temp = 0;
        int off = 0;
        for (int i = 0; i < 96; i++)
            if ((src.bits[i / 32] & (1 << i % 32)) != 0) temp += pow(2, i);
        if ((off = (src.bits[3] & ~SIGN) >> 16) > 0) {
            for (int i = off; i > 0; i--) temp /= 10.0;
        }
        *dst = (float)temp;
        *dst *= src.bits[3] >> 31 ? -1 : 1;
        result = TRUE;
    }
    return result;
}

// ==Arithmetic Operators== //

s21_decimal s21_add(s21_decimal dec_a, s21_decimal dec_b) {
    s21_decimal res;
    int sign_a = get_bit_dec(dec_a, 127), sign_b = get_bit_dec(dec_b, 127);
    init_dec_bits(&res);
    if (dec_a.value_type > dec_b.value_type) {
        res.value_type = dec_a.value_type;
    } else if (!dec_a.value_type && !dec_b.value_type &&
        dec_a.value_type != dec_b.value_type) {
        res.value_type = s21_NAN;
    } else {
        res.value_type = dec_b.value_type;
    }
    if (res.value_type == s21_NORMAL_VALUE || res.value_type == s21_ADDCODE) {
        if (!sign_a && !sign_b) {
            if (get_scale(dec_a) != get_scale(dec_b)) {
                norm_scale(&dec_a, &dec_b);
            }
            res = summ(dec_a, dec_b);
            res.bits[3] = dec_a.bits[3];
        } else if (sign_a && !sign_b) {
            set_bit_dec(&dec_a, 127, 0);
            res = s21_sub(dec_b, dec_a);
        } else if (!sign_a && sign_b) {
            set_bit_dec(&dec_b, 127, 0);
            res = s21_sub(dec_a, dec_b);
        } else if (sign_a && sign_b) {
            set_bit_dec(&dec_a, 127, 0);
            set_bit_dec(&dec_b, 127, 0);
            res = s21_add(dec_a, dec_b);
            set_bit_dec(&res, 127, 1);
            if (res.value_type == s21_INFINITY) {
                res.value_type == s21_NEGATIVE_INFINITY;
                init_dec_bits(&res);
            }
        }
    }
    if (res.value_type == s21_ADDCODE) {
        res.value_type = s21_NORMAL_VALUE;
    }

    return res;
}

s21_decimal s21_sub(s21_decimal dec_a, s21_decimal dec_b) {
    s21_decimal res;
    s21_decimal min, max;
    init_dec_bits(&min);
    init_dec_bits(&max);
    init_dec_bits(&res);
    int sign_a = 0;
    int sign_b = 0;
    int fin_scale = 0;
    int fin_sign = 0;
    init_dec_bits(&res);
    if (dec_a.value_type != s21_NORMAL_VALUE) {
        res.value_type = dec_a.value_type;
    } else {
        res.value_type = dec_b.value_type;
    }
    if (res.value_type == s21_NORMAL_VALUE) {
        if (get_scale(dec_a) != get_scale(dec_b)) {
            fin_scale = norm_scale(&dec_a, &dec_b);
            set_dec_scale(&res, fin_scale);
        }
    }
    if (get_bit_dec(dec_a, 127) != get_bit_dec(dec_b, 127)) {
        fin_sign = get_bit_dec(dec_a, 127);
        set_bit_dec(&dec_a, 127, 0);
        set_bit_dec(&dec_b, 127, 0);
        res = s21_add(dec_a, dec_b);
        set_bit_dec(&res, 127, fin_sign);
    } else {
        if (s21_is_equal(dec_a, dec_b) == FALSE) {
            sign_a = get_bit_dec(dec_a, 127);
            sign_b = get_bit_dec(dec_b, 127);
            set_bit_dec(&dec_a, 127, 0);
            set_bit_dec(&dec_b, 127, 0);
            if (s21_is_less(dec_a, dec_b) == FALSE) {
                min = dec_b;
                max = dec_a;
                fin_sign = sign_a;
            } else {
                min = dec_a;
                max = dec_b;
                fin_sign = !sign_b;
            }
            dec_to_addcode(&min);
            res = s21_add(min, max);
            set_bit_dec(&res, 127, fin_sign);
        } else {
            init_dec_bits(&res);
        }
    }
    return res;
}


s21_decimal s21_mul(s21_decimal dec_a, s21_decimal dec_b) {
    s21_decimal res, buf;
    int bit;
    int sign_a = get_bit_dec(dec_a, 127), sign_b = get_bit_dec(dec_b, 127);
    init_dec_bits(&res);
    init_dec_bits(&buf);
    res = validate_mul(dec_a, dec_b);
    int scale = get_scale(dec_a) + get_scale(dec_b);
    if (res.value_type == s21_NORMAL_VALUE) {
        s21_decimal zero = {0, 0, 0, 0, 0};
        s21_overflow_decimal overflow = init_overflow(zero);
        overflow = overflow_mul(init_overflow(dec_a), init_overflow(dec_b), &scale);
        s21_decimal temp = { overflow.bits[0], overflow.bits[1],
                                    overflow.bits[2], 0, convert_type(overflow)};
        res = temp;
        if ((sign_a && sign_b) || (!sign_a && !sign_b)) {
            set_bit_dec(&res, 127, 0);
        } else {
            set_bit_dec(&res, 127, 1);
        }
        set_dec_scale(&res, scale);
    }
    if (res.value_type == s21_INFINITY && get_bit_dec(res, 127)) {
        res.value_type = s21_NEGATIVE_INFINITY;
    }
    return res;
}

value_type_t convert_type(s21_overflow_decimal dec) {
    value_type_t res;
    if (dec.value_type == s21_INFINITY_OVF)
        res = s21_INFINITY;
    else if (dec.value_type == s21_NEGATIVE_INFINITY_OVF)
        res = s21_NEGATIVE_INFINITY;
    else if (dec.value_type == s21_NEGATIVE_INFINITY_OVF)
        res = s21_NORMAL_VALUE;
    else if (dec.value_type == s21_NAN_OVF)
        res = s21_NAN;
    else if (dec.value_type == s21_NORMAL_VALUE_OVF)
        res = s21_NORMAL_VALUE;
    return res;
}

s21_decimal validate_mul(s21_decimal dec_1, s21_decimal dec_2) {
    s21_decimal res;
    s21_decimal zero;
    init_dec_bits(&res);
    init_dec_bits(&zero);
    int it_nan = dec_nan(&dec_1, &dec_2) == TRUE ? 1 : 0;
    int it_inf = dec_inf(&dec_1, &dec_2) != TRUE ? 1 : 0;
    int it_neg_inf = dec_neg_inf(&dec_1, &dec_2) != TRUE ? 1 : 0;
    int it_zero =
        s21_is_equal(dec_1, zero) == TRUE || s21_is_equal(dec_2, zero) ? 1 : 0;
    int norm = (s21_is_greater(dec_1, zero) == TRUE &&
        dec_1.value_type == s21_NORMAL_VALUE ||
        s21_is_greater(dec_2, zero) == TRUE &&
        dec_2.value_type == s21_NORMAL_VALUE)
        ? 1
        : 0;
    int norm_minus = (s21_is_less(dec_1, zero) == TRUE &&
        dec_1.value_type == s21_NORMAL_VALUE ||
        s21_is_less(dec_2, zero) == TRUE &&
        dec_2.value_type == s21_NORMAL_VALUE)
        ? 1
        : 0;
    res.value_type = dec_1.value_type ? dec_1.value_type : dec_2.value_type;
    if (it_nan || (it_zero && it_inf) || (it_zero && it_neg_inf)) {
        res.value_type = s21_NAN;
    } else if ((norm && it_inf) || (norm_minus && it_neg_inf) ||
        (dec_1.value_type == s21_INFINITY &&
            dec_2.value_type == s21_INFINITY) ||
        (dec_1.value_type == s21_NEGATIVE_INFINITY &&
            dec_2.value_type == s21_NEGATIVE_INFINITY)) {
        res.value_type = s21_INFINITY;
    } else if ((norm_minus && it_inf) || (it_inf && it_neg_inf) ||
        (norm && it_neg_inf)) {
        res.value_type = s21_NEGATIVE_INFINITY;
    }
    return res;
}

s21_decimal s21_div(s21_decimal dec_a, s21_decimal dec_b) {
    s21_decimal res;
    s21_overflow_decimal overflow;
    int res_scale = 0;
    int res_sign = 0;
    res = validate_div(dec_a, dec_b);
    if (dec_a.value_type == s21_NORMAL_VALUE &&
        (dec_b.value_type == s21_INFINITY ||
            dec_b.value_type == s21_NEGATIVE_INFINITY)) {
        init_dec_bits(&res);
    } else {
        if (res.value_type == s21_NORMAL_VALUE) {
            s21_decimal zero;
            s21_decimal victim;
            s21_decimal remainder;
            s21_decimal tmp;
            s21_decimal ten = { {10, 0, 0, 0}, s21_NORMAL_VALUE };
            s21_decimal border_value = { {-1, -1, -1, 0}, s21_NORMAL_VALUE };
            set_dec_scale(&border_value, 1);
            init_dec_bits(&remainder);
            init_dec_bits(&tmp);
            init_dec_bits(&zero);
            init_dec_bits(&victim);
            int beg_scale = get_scale(dec_a) - get_scale(dec_b);
            int temp_scale = beg_scale;
            s21_overflow_decimal a_ovf = init_overflow(dec_a);
            s21_overflow_decimal b_ovf = init_overflow(dec_b);
            norm_scale_ovf(&a_ovf, &b_ovf, get_scale(dec_a), get_scale(dec_b));
            overflow = overflow_div(a_ovf, b_ovf, &res_scale);
            s21_decimal temp = { overflow.bits[0], overflow.bits[1],
                                    overflow.bits[2], 0, convert_type(overflow)};
            res = temp;
            int tmp_scale = 0;
            if (get_bit_dec(dec_a, 127) || get_bit_dec(dec_b, 127)) {
                res_sign = 1;
            }
        }
        set_dec_scale(&res, res_scale);
        set_bit_dec(&res, 127, res_sign);
    }
    return res;
}


// ==Comparison Operators== //

int s21_is_less(s21_decimal dec_a, s21_decimal dec_b) {
    int res = s21_is_greater(dec_b, dec_a);
    return res;
}

int s21_is_less_or_equal(s21_decimal dec_a, s21_decimal dec_b) {
    int res = FALSE;
    if (s21_is_less(dec_a, dec_b) == TRUE ||
        s21_is_equal(dec_a, dec_b) == TRUE || dec_inf(&dec_a, &dec_b) == 2 ||
        dec_neg_inf(&dec_a, &dec_b) == 2) {
        res = TRUE;
    }
    return res;
}

int s21_is_greater(s21_decimal dec_a, s21_decimal dec_b) {
    int res = -1;
    int prov_inf = dec_inf(&dec_a, &dec_b);
    int prov_neg_inf = dec_neg_inf(&dec_a, &dec_b);
    if ((dec_nan(&dec_a, &dec_b) == TRUE) ||
        (!is_zero_dec(dec_a, dec_b) && !dec_inf(&dec_a, &dec_b) &&
            !dec_neg_inf(&dec_a, &dec_b))) {
        res = FALSE;
    }
    if (res == -1) {
        if (prov_inf == 1) {
            res = TRUE;
        } else if (prov_inf == 2 || prov_inf == -1) {
            res = FALSE;
        }
        if (prov_neg_inf == -1) {
            res = TRUE;
        } else if (prov_neg_inf == 1 || prov_neg_inf == 2) {
            res = FALSE;
        }
        if (res == -1 && (get_scale(dec_a) != get_scale(dec_b))) {
            norm_scale(&dec_a, &dec_b);
        }
    }
    if (compar_func(dec_a, dec_b) == 0 && res == -1) {
        res = TRUE;
    }
    if (res != TRUE) {
        res = FALSE;
    }
    return res;
}

int s21_is_greater_or_equal(s21_decimal dec_a, s21_decimal dec_b) {
    int res = FALSE;
    if (s21_is_greater(dec_a, dec_b) == TRUE ||
        s21_is_equal(dec_a, dec_b) == TRUE) {
        res = TRUE;
    }
    return res;
}

int s21_is_equal(s21_decimal dec_a, s21_decimal dec_b) {
    int res = FALSE;
    int prov_inf = dec_inf(&dec_a, &dec_b);
    int prov_neg_inf = dec_neg_inf(&dec_a, &dec_b);
    if (dec_nan(&dec_a, &dec_b) == TRUE) {
        res = FALSE;
    } else {
        if (((get_scale(dec_a) != get_scale(dec_b)))) {
            norm_scale(&dec_a, &dec_b);
        }
        int comp = compar_func(dec_a, dec_b);
        if (comp != 2) {
            res = FALSE;
        } else {
            res = TRUE;
        }
        if (is_zero_dec(dec_a, dec_b) == TRUE) {
            res = TRUE;
        }
        if (prov_inf == 2) {
            res = TRUE;
        } else if (prov_inf == 1 || prov_inf == -1) {
            res = FALSE;
        }
        if (prov_neg_inf == 2) {
            res = TRUE;
        } else if (prov_neg_inf == 1 || prov_neg_inf == -1) {
            res = FALSE;
        }
        if (res == -1) {
            res = FALSE;
        }
    }
    return res;
}

int s21_is_not_equal(s21_decimal dec_a, s21_decimal dec_b) {
    int res = FALSE;
    if (s21_is_equal(dec_a, dec_b) == FALSE) {
        res = TRUE;
    }
    return res;
}

// ==Another functions== //

s21_decimal s21_floor(s21_decimal src) {
    unsigned f = 0;
    if (!src.value_type) {
        s21_decimal one, tmp;
        s21_from_int_to_decimal(1, &one);
        init_dec_bits(&tmp);
        unsigned scale = get_scale(src), sign = get_bit(src.bits[3], 31);
        for (int i = 0; i < scale; i++) {
            if (dec_div_10_round(&src)) f++;
        }
        if (sign && f) {
            tmp = s21_add(src, one);
            if (tmp.value_type) {
                src.value_type = s21_NEGATIVE_INFINITY;
            } else {
                set_bit(&(tmp.bits[3]), 31, 1);
                src = tmp;
            }
        }
    }
    return src;
}


s21_decimal s21_truncate(s21_decimal src) {
    if (!src.value_type) {
        unsigned scale = get_scale(src);
        for (int i = 0; i < scale; i++) dec_div_10(&src);
    }
    return src;
}

s21_decimal s21_negate(s21_decimal src) {
    if (get_bit_dec(src, 127)) {
        set_bit(&src.bits[3], 31, 0);
    } else {
        set_bit(&src.bits[3], 31, 1);
    }
    return src;
}

// ==Dop functions== //

void init_dec_bits(s21_decimal* dst) {
    for (int i = 0; i <= 3; i++) {
        dst->bits[i] = 0;
    }
    dst->value_type = s21_NORMAL_VALUE;
}

void set_bit(unsigned int* dst, unsigned bit, unsigned set) {
    if (set == 1)
        *dst |= (1 << bit);
    else
        *dst &= ~(1 << bit);
}

unsigned get_bit(int src, unsigned bit) { return src & (1 << bit) ? 1 : 0; }

unsigned get_bit_dec(s21_decimal dst, unsigned bit) {
    int res = 0;
    if (bit / 32 < 4) {
        unsigned int mask = 1u << (bit % 32);
        res = dst.bits[bit / 32] & mask;
    }
    return !!res;
}

void set_bit_dec(s21_decimal* dst, unsigned num_bit, unsigned set) {
    if (set == 1)
        dst->bits[num_bit / 32] |= (1U << num_bit);
    else
        dst->bits[num_bit / 32] &= ~(1U << num_bit);
}

void shift(s21_decimal* src, int offset) {
    unsigned int mask_32;
    unsigned int mask_63;
    int last = last_bit(*src);
    if (last + offset > 95) {
        src->value_type = s21_INFINITY;
        return;
    }
    for (int i = 0; i < abs(offset); i++) {
        if (offset > 0) {
            mask_32 = get_bit((*src).bits[0], 31);
            mask_63 = get_bit((*src).bits[1], 31);
            src->bits[2] <<= 1;
            src->bits[1] <<= 1;
            src->bits[0] <<= 1;
            if (mask_32) {
                set_bit(&(*src).bits[1], 0, 1);
            }
            if (mask_63) {
                set_bit(&(*src).bits[2], 0, 1);
            }
        } else {
            mask_32 = get_bit((*src).bits[1], 0);
            mask_63 = get_bit((*src).bits[2], 0);
            src->bits[2] >>= 1;
            src->bits[1] >>= 1;
            src->bits[0] >>= 1;
            if (mask_32) {
                set_bit(&(*src).bits[0], 31, 1);
            }
            if (mask_63) {
                set_bit(&(*src).bits[1], 31, 1);
            }
        }
    }
}

unsigned get_scale(s21_decimal src) {
    unsigned scale;
    scale = ((src.bits[3] << 1) >> 17);
    return scale;
}

void set_scale(s21_decimal* dst, unsigned scale) {
    (*dst).bits[3] &= 0x80000000;
    (*dst).bits[3] |= scale;
}

void set_dec_scale(s21_decimal* dst, int scale) {
    char sign = 0;
    if (get_bit(dst->bits[3], 31)) {
        sign = 1;
    }
    dst->bits[3] = 0;
    dst->bits[3] |= (scale << 16);
    if (sign) {
        set_bit_dec(dst, 127, 1);
    }
}

s21_decimal summ(s21_decimal par_a, s21_decimal par_b) {
    s21_decimal res;
    int tmp = 0;
    init_dec_bits(&res);
    for (int i = 0; i < 96; i++) {
        char bit_a = get_bit_dec(par_a, i);
        char bit_b = get_bit_dec(par_b, i);
        if (bit_a && bit_b && tmp) {
            set_bit_dec(&res, i, 1);
            tmp = 1;
        } else if (bit_a && bit_b && !tmp) {
            tmp = 1;
        } else if ((bit_a ^ bit_b) && tmp) {
            tmp = 1;
        } else if ((bit_a ^ bit_b) && !tmp) {
            set_bit_dec(&res, i, 1);
        } else if (!bit_a && !bit_b && tmp) {
            set_bit_dec(&res, i, 1);
            tmp = 0;
        }
        if (i == 95 && tmp && par_a.value_type != s21_ADDCODE &&
            par_b.value_type != s21_ADDCODE) {
            res.value_type = s21_INFINITY;
        } else {
            res.value_type = s21_NORMAL_VALUE;
        }
        if (dec_inf(&par_a, &par_b) != 0) {
            res.value_type = s21_INFINITY;
        }
    }
    return res;
}


unsigned dec_div_10(s21_decimal* src) {
    unsigned out = 0, i = 95;
    for (; !get_bit((*src).bits[i / 32], i) && i; i--) {
    }
    s21_decimal ten, buff, divided;
    s21_from_int_to_decimal(10, &ten);
    init_dec_bits(&buff);
    init_dec_bits(&divided);
    set_dec_scale(&divided, get_scale(*src) - 1);
    if (get_bit((*src).bits[3], 31)) set_bit(&divided.bits[3], 31, 1);
    (*src).bits[3] = 0;
    for (; i >= 3; i--) {
        s21_decimal tmp = ten;
        shift(&tmp, i - 3);
        buff = tmp;
        shift(&divided, 1);
        if (s21_is_less(*src, buff)) {
            *src = s21_sub(*src, buff);
            set_bit(&divided.bits[0], 0, 1);
        }
    }
    out = (*src).bits[0];
    *src = divided;
    return out;
}

int compar_func(s21_decimal dec_a, s21_decimal dec_b) {
    int res = -1;
    int sign_a = get_bit_dec(dec_a, 127), sign_b = get_bit_dec(dec_b, 127);
    for (int i = 95; i >= 0; i--) {
        if (!get_bit_dec(dec_a, i) && get_bit_dec(dec_b, i)) {
            res = 1;
            break;
        }
        if (get_bit_dec(dec_a, i) && !get_bit_dec(dec_b, i)) {
            res = 0;
            break;
        }
    }
    if (!sign_a && sign_b) {
        res = 0;
    } else if (sign_a && !sign_b) {
        res = 1;
    }
    if (res == -1 && (sign_a == sign_b)) {
        res = 2;
    }
    if (sign_a && sign_b && res == 0) {
        res = 1;
    } else if (sign_a && sign_b && res == 1) {
        res = 0;
    }
    return res;
}

int norm_scale(s21_decimal* dec_a, s21_decimal* dec_b) {
    s21_decimal tmp, tmp_1, tmp_2, * min = NULL, * max = NULL;
    init_dec_bits(&tmp);
    init_dec_bits(&tmp_1);
    init_dec_bits(&tmp_2);
    int scale_a = get_scale(*dec_a);
    int scale_b = get_scale(*dec_b);
    int fin_scale = 0;
    if (scale_a > scale_b) {
        max = dec_a;
        min = dec_b;
    } else {
        max = dec_b;
        min = dec_a;
    }
    while (get_scale(*dec_a) != get_scale(*dec_b)) {
        int scale_a1 = get_scale(*dec_a);
        int scale_b1 = get_scale(*dec_b);
        if (tmp.value_type == s21_NORMAL_VALUE && !get_bit_dec(*min, 93) &&
            !get_bit_dec(*min, 94) && !get_bit_dec(*min, 95)) {
            tmp_1 = tmp_2 = *min;
            shift(&tmp_1, 1);
            shift(&tmp_2, 3);
            tmp = summ(tmp_1, tmp_2);
            int min_scale = get_scale(*min);
            if (tmp.value_type == s21_NORMAL_VALUE) {
                only_bits_equals(tmp, min);
                set_dec_scale(min, min_scale + 1);
            }

        } else {
            dec_div_10(max);
        }
    }
    fin_scale = get_scale(*dec_a);
    return fin_scale;
}

int dec_nan(s21_decimal* dec_a, s21_decimal* dec_b) {
    int type_a = dec_a->value_type;
    int type_b = dec_b->value_type;

    return (type_a == s21_NAN || type_b == s21_NAN) ? TRUE : FALSE;
}

int dec_inf(s21_decimal* dec_a, s21_decimal* dec_b) {
    int res = 0;
    int type_a = dec_a->value_type;
    int type_b = dec_b->value_type;

    if (type_a == s21_INFINITY && type_b != s21_INFINITY) {
        res = 1;
    } else if (type_a != s21_INFINITY && type_b == s21_INFINITY) {
        res = -1;
    } else if (type_a == s21_INFINITY && type_b == s21_INFINITY) {
        res = 2;
    }
    return res;
}

int dec_neg_inf(s21_decimal* dec_a, s21_decimal* dec_b) {
    int res = 0;
    int type_a = dec_a->value_type;
    int type_b = dec_b->value_type;

    if (type_a == s21_NEGATIVE_INFINITY && type_b != s21_NEGATIVE_INFINITY) {
        res = 1;
    }
    if (type_a != s21_NEGATIVE_INFINITY && type_b == s21_NEGATIVE_INFINITY) {
        res = -1;
    }
    if (type_a == s21_NEGATIVE_INFINITY && type_b == s21_NEGATIVE_INFINITY) {
        res = 2;
    }

    return res;
}

int is_zero_dec(s21_decimal dec_a, s21_decimal dec_b) {
    int res = FALSE;
    s21_decimal* tmp_a = &dec_a;
    s21_decimal* tmp_b = &dec_b;

    if (tmp_a && tmp_b) {
        if (!dec_a.bits[0] && !dec_b.bits[0] && !dec_a.bits[1] &&
            !dec_b.bits[1] && !dec_a.bits[2] && !dec_b.bits[2])
            res = TRUE;
    }
    return res;
}

void only_bits_equals(s21_decimal src, s21_decimal* dst) {
    dst->bits[0] = src.bits[0];
    dst->bits[1] = src.bits[1];
    dst->bits[2] = src.bits[2];
}

int last_bit(s21_decimal dec) {
    int last = 0;
    int i = 95;
    for (i = 95; i >= 0; i--) {
        if (get_bit_dec(dec, i)) {
            last = i;
            break;
        }
    }
    return i;
}

void dec_to_addcode(s21_decimal* dec) {
    s21_decimal add;
    s21_decimal one;
    init_dec_bits(&one);
    s21_from_int_to_decimal(1, &one);
    dec->bits[0] = ~dec->bits[0];
    dec->bits[1] = ~dec->bits[1];
    dec->bits[2] = ~dec->bits[2];
    add = summ(*dec, one);
    dec->bits[0] = add.bits[0];
    dec->bits[1] = add.bits[1];
    dec->bits[2] = add.bits[2];
    dec->value_type = s21_ADDCODE;
}

s21_decimal str_to_dec(char binary_number[], s21_decimal* dec,
    int point_place) {
    if (dec == NULL) {
        s21_decimal res;
        dec = &res;
    }
    init_dec_bits(dec);
    char copy[100];
    int shift = 0;
    if (binary_number[0] == '-') {
        set_bit_dec(dec, 127, 1);
        strncpy(copy, binary_number + 1, 97);
    } else {
        strncpy(copy, binary_number, 98);
    }
    dec->bits[3] += point_place << 16;
    int len_number = strlen(copy);
    for (int i = shift; i < len_number; i++) {
        int bit_place = (i - shift) % 32;
        int int_place = (i - shift) / 32;
        int bit = copy[len_number - 1 - i + shift] - '0';
        dec->bits[int_place] += bit << bit_place;
    }

    return *dec;
}

int getFloatSign(float* src) { return *(int*)src >> 31; }

int getFloatExp(float* src) { return ((*(int*)src & ~SIGN) >> 23) - 127; }

unsigned get_last_bit(s21_decimal src) {
    unsigned i;
    for (i = 95; i > 0; i--) {
        if (get_bit(src.bits[i / 32], i % 32)) break;
    }
    return i;
}

s21_decimal validate_div(s21_decimal dec_a, s21_decimal dec_b) {
    s21_decimal res;
    s21_decimal zero;
    init_dec_bits(&zero);
    init_dec_bits(&res);
    int dec_b_norm = s21_is_greater(dec_b, zero) == TRUE &&
        dec_b.value_type == s21_NORMAL_VALUE
        ? 1
        : 0;
    int dec_b_norm_minus =
        s21_is_less(dec_b, zero) == TRUE && dec_b.value_type == s21_NORMAL_VALUE
        ? 1
        : 0;
    if (dec_nan(&dec_a, &zero) == TRUE) {
        res.value_type = s21_NAN;
    } else if (s21_is_equal(dec_b, zero) == TRUE &&
        s21_is_less(dec_a, zero) == TRUE) {
        res.value_type = s21_NEGATIVE_INFINITY;
    } else if (s21_is_equal(dec_b, zero) == TRUE &&
        s21_is_greater(dec_a, zero) == TRUE) {
        res.value_type = s21_INFINITY;
    } else if (s21_is_equal(dec_b, zero) == TRUE &&
        s21_is_equal(dec_a, zero) == TRUE) {
        res.value_type = s21_NAN;
    } else if ((dec_a.value_type == s21_INFINITY ||
        dec_a.value_type == s21_NEGATIVE_INFINITY) &&
        (dec_b.value_type == s21_INFINITY ||
            dec_b.value_type == s21_NEGATIVE_INFINITY)) {
        res.value_type = s21_NAN;
    } else if ((dec_a.value_type == s21_INFINITY && dec_b_norm) ||
        (dec_a.value_type == s21_NEGATIVE_INFINITY &&
            dec_b_norm_minus)) {
        res.value_type = s21_INFINITY;
    } else if ((dec_a.value_type == s21_INFINITY && dec_b_norm_minus) ||
        (dec_a.value_type == s21_NEGATIVE_INFINITY && dec_b_norm)) {
        res.value_type = s21_NEGATIVE_INFINITY;
    }
    return res;
}

s21_decimal shift_left(s21_decimal d, int offset) {
    s21_decimal res;
    init_dec_bits(&res);
    for (int i = 0; i < 96; i++) {
        if (get_bit(d.bits[i / 32], i)) {
            if (i + offset >= 0) {
                set_bit(&res.bits[(i + offset) / 32], (i + offset) % 32, 1);
            }
        }
    }
    return res;
}

unsigned dec_div_10_round(s21_decimal* src) {
    unsigned out = 0, i = get_last_bit(*src);
    s21_decimal ten, buff, divided;
    s21_from_int_to_decimal(10, &ten);
    init_dec_bits(&buff);
    init_dec_bits(&divided);
    set_scale(&divided, get_scale(*src) - 1);
    set_bit(&divided.bits[3], 31, get_bit((*src).bits[3], 31));
    (*src).bits[3] = 0;
    for (; i >= 3; i--) {
        buff = shift_left(ten, i - 3);
        divided = shift_left(divided, 1);
        if (s21_is_less(*src, buff)) {
            *src = s21_sub(*src, buff);
            set_bit(&divided.bits[0], 0, 1);
        }
    }
    out = (*src).bits[0];
    *src = divided;
    return out;
}

s21_decimal s21_mod(s21_decimal a, s21_decimal b) {
    s21_decimal res;
    s21_decimal remainder;
    s21_overflow_decimal zero = { 0, 0, 0, 0, 0, 0, 0 };
    int sign = 0, res_scale = get_scale(a) >= get_scale(b) ? get_scale(a) : get_scale(b);
    int div = 0, ovf_flag = 0;
    init_dec_bits(&res);
    res = validate_div(a, b);
    if (res.value_type == s21_NORMAL_VALUE) {
        if (get_bit(a.bits[3], 31) == get_bit(b.bits[3], 31)) {
            sign = get_bit(a.bits[3], 31);
            set_bit(&a.bits[3], 31, 0);
            set_bit(&b.bits[3], 31, 0);
        } else {
            sign = 1;
        }
        set_bit(&a.bits[3], 31, 0);
        set_bit(&b.bits[3], 31, 0);
        if (abs(abs((int)get_scale(a)) - abs((int)get_scale(b))) <= 1 &&
            abs(abs((int)get_scale(a)) - abs((int)get_scale(b)) != 0)) {
            init_dec_bits(&res);
        } else {
        if (!s21_is_greater_or_equal(a, b)) {
                s21_overflow_decimal dec1_S = init_overflow(a);
                s21_overflow_decimal dec2_S = init_overflow(b);
                norm_scale_ovf(&dec1_S, &dec2_S, get_scale(a), get_scale(b));
                int scale = shift_left_for_div_ovf(dec1_S, &dec2_S);
                for (; scale >= 0; scale--) {
                    if (!overflow_is_greater(dec1_S, dec2_S) || !overflow_is_equal(dec1_S, dec2_S))
                        dec1_S = overflow_sub(dec1_S, dec2_S);
                    dec2_S = shift_right_overflow(dec2_S, 1);
                }
                while (dec1_S.bits[3] || dec1_S.bits[4] || dec1_S.bits[5]) {
                    if (!res_scale && (dec1_S.bits[3] || dec1_S.bits[4] || dec1_S.bits[5])) {
                        dec1_S = zero;
                        dec1_S.value_type = s21_INFINITY_OVF;
                        break;
                    }
                    ovf_flag = 1;
                    div = dec_div_10_overflow(&dec1_S);
                    res_scale--;
                }
                if (dec1_S.value_type == s21_NORMAL_VALUE_OVF && ovf_flag) {
                    int parity = 0;
                    while (res_scale > 28) {
                        div = dec_div_10_overflow(&dec1_S);
                        res_scale--;
                    }
                    parity = get_bit(res.bits[0], 0);
                    if ((div >= 5 && parity && res_scale) || (div > 5 && !parity && res_scale)
                        || (!res_scale && div >= 5))
                        dec1_S.bits[0] = dec1_S.bits[0] + 1;
                }
                s21_decimal temp = { dec1_S.bits[0], dec1_S.bits[1],
                                        dec1_S.bits[2], 0, convert_type(dec1_S)};
                res = temp;
            } else {
                res_scale = get_scale(a);
            }
            set_dec_scale(&res, res_scale);
        }
        if (!s21_is_less(a, b) && get_bit(a.bits[3], 31) == get_bit(b.bits[3], 31))
            res = a;
        set_bit(&res.bits[3], 31, sign);
    }
    return res;
}

s21_decimal s21_round(s21_decimal src) {
    s21_decimal half = { {0x2FAF080, 0, 0, 0x80000}, s21_NORMAL_VALUE };  // 0.5f
    s21_decimal one, out;
    init_dec_bits(&out);
    if (!src.value_type) {
        s21_from_int_to_decimal(1, &one);
        unsigned scale = get_scale(src), dif = 0,
            sign = get_bit(src.bits[3], 31);
        set_bit(&src.bits[3], 31, 0);
        if (scale) {
            s21_decimal temp = s21_sub(src, s21_truncate(src));
            set_bit(&temp.bits[3], 31, 0);
            int parity = get_parity(src, scale);
            if ((!s21_is_greater_or_equal(temp, half) && parity) ||
                            (!s21_is_greater(temp, half) && !parity)) {
                out = s21_add(s21_truncate(src), one);
            } else {
                out = s21_truncate(src);
            }
            if (sign) set_bit(&out.bits[3], 31, 1);
        } else {
            out = src;
        }
    } else {
        out.value_type = src.value_type;
    }
    return out;
}

int get_parity(s21_decimal src, int scale) {
    int res = 0;
    for (int i = 0; i < scale; i++) {
        dec_div_10_round(&src);
        res = get_bit(src.bits[0], 0);
    }
    return res;
}

s21_overflow_decimal init_overflow(s21_decimal src) {
    s21_overflow_decimal res = { src.bits[0], src.bits[1], src.bits[2], 0, 0, 0, 0};
    return res;
}
