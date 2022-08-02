#include "s21_decimal.h"

s21_overflow_decimal overflow_mul(s21_overflow_decimal dec_a, s21_overflow_decimal dec_b, int* res_scale) {
    s21_overflow_decimal res = { 0, 0, 0, 0, 0, 0, 0 };
    s21_overflow_decimal buf = { 0, 0, 0, 0, 0, 0, 0 };
    s21_decimal zero = { 0, 0, 0 , 0 };
    int div = 0;
    if (res.value_type == s21_NORMAL_VALUE) {
        for (int i = 0; i < 96; i++) {
            buf = shift_left_overflow(dec_a, i);
            if (get_bit(dec_b.bits[i / 32], i % 32)) {
                res = overflow_add(res, buf);
            }
        }
        while (res.bits[3]) {
            if (!*res_scale && res.bits[3]) {
                res = init_overflow(zero);
                res.value_type = s21_INFINITY_OVF;
                break;
            }
            div = dec_div_10_overflow(&res);
            (*res_scale)--;
        }
        if (res.value_type == s21_NORMAL_VALUE_OVF) {
            int parity = 0;
            while (*res_scale > 28) {
                div = dec_div_10_overflow(&res);
                (*res_scale)--;
            }
            parity = get_bit(res.bits[0], 0);
            if ((div >= 5 && parity && *res_scale) || (div > 5 && !parity && *res_scale)
                || (!*res_scale && div >= 5))
                res.bits[0] = res.bits[0] + 1;
        }
    }
    return res;
}


s21_overflow_decimal simple_overflow_mul(s21_overflow_decimal dec_a, s21_overflow_decimal dec_b) {
    s21_overflow_decimal res = { 0, 0, 0, 0, 0, 0, 0 };
    s21_overflow_decimal buf = { 0, 0, 0, 0, 0, 0, 0 };
    s21_decimal zero = { 0, 0, 0 , 0 };
    int div = 0;
    if (res.value_type == s21_NORMAL_VALUE) {
        for (int i = 0; i < 192; i++) {
            buf = shift_left_overflow(dec_a, i);
            if (get_bit(dec_b.bits[i / 32], i % 32)) {
                res = overflow_add(res, buf);
            }
        }
    }
    return res;
}

s21_overflow_decimal shift_left_overflow(s21_overflow_decimal d, int offset) {
    s21_overflow_decimal res = { 0, 0, 0, 0, 0, 0, 0 };
    int i = 0;
    for (; i < 192; i++) {
        if (get_bit(d.bits[i / 32], i)) {
            if (i + offset >= 0) {
                set_bit(&res.bits[(i + offset) / 32], (i + offset) % 32, 1);
            }
        }
    }
    return res;
}


s21_overflow_decimal overflow_add(s21_overflow_decimal par_a, s21_overflow_decimal par_b) {
    s21_overflow_decimal res = { 0, 0, 0, 0, 0, 0, 0 };
    int tmp = 0;
    for (int i = 0; i < 192; i++) {
        char bit_a = get_bit_dec_ovf(par_a, i);
        char bit_b = get_bit_dec_ovf(par_b, i);
        if (bit_a && bit_b && tmp) {
            set_bit_dec_ovf(&res, i, 1);
            tmp = 1;
        } else if (bit_a && bit_b && !tmp) {
            tmp = 1;
        } else if ((bit_a ^ bit_b) && tmp) {
            tmp = 1;
        } else if ((bit_a ^ bit_b) && !tmp) {
            set_bit_dec_ovf(&res, i, 1);
        } else if (!bit_a && !bit_b && tmp) {
            set_bit_dec_ovf(&res, i, 1);
            tmp = 0;
        }
        if (i == 223 && tmp && par_a.value_type != s21_ADDCODE_OVF &&
            par_b.value_type != s21_ADDCODE_OVF) {
            res.value_type = s21_INFINITY_OVF;
        } else {
            res.value_type = s21_NORMAL_VALUE_OVF;
        }
        if (dec_inf_ovf(&par_a, &par_b) != 0) {
            res.value_type = s21_INFINITY_OVF;
        }
    }
    return res;
}


s21_overflow_decimal overflow_div(s21_overflow_decimal dec_a, s21_overflow_decimal dec_b, int* res_scale) {
    s21_overflow_decimal res = { 0, 0, 0, 0, 0, 0, 0 };
    int res_sign = 0, parity = 0;
    s21_overflow_decimal zero = { 0, 0, 0, 0, 0, 0, 0 };
    s21_overflow_decimal remainder = { 0, 0, 0, 0, 0, 0, 0 };
    s21_overflow_decimal tmp = { 0, 0, 0, 0, 0, 0, 0 };
    s21_overflow_decimal ten = { {10, 0, 0, 0}, s21_NORMAL_VALUE_OVF };
    tmp = div_simple_ovf(dec_a, dec_b);
    remainder = mod_ovf(dec_a, dec_b);
    int tmp_scale = 0, div = 0;
    for (s21_overflow_decimal tmpDec = {10, 0, 0, 0, 0, 0, 0};
        !overflow_is_equal(tmp, tmpDec) || !overflow_is_greater(tmp, tmpDec);
                        tmpDec = simple_overflow_mul(tmpDec, ten), tmp_scale++) {
    }
    for (; *res_scale + tmp_scale < 29 && overflow_is_equal(remainder, zero) == FALSE; (*res_scale)++) {
        remainder = simple_overflow_mul(remainder, ten);
        tmp = simple_overflow_mul(tmp, ten);
        tmp = overflow_add(tmp, div_simple_ovf(remainder, dec_b));
        remainder = mod_ovf(remainder, dec_b);
    }
    while (*res_scale + tmp_scale > 28) {
        if (!(*res_scale) && (tmp.bits[3] || tmp.bits[4] || tmp.bits[5])) {
            tmp = zero;
            tmp.value_type = s21_INFINITY_OVF;
            break;
        }
        div = dec_div_10_overflow(&tmp);
        (*res_scale)--;
    }
    while (*res_scale > 28) {
        div = dec_div_10_overflow(&tmp);
        (*res_scale)--;
    }
    parity = get_bit(tmp.bits[0], 0);
    if ((div >= 5 && parity && *res_scale) || (div > 5 && !parity && *res_scale)
        || (!*res_scale && div >= 5))
        tmp.bits[0] += 1;
    return tmp;
}


void norm_scale_ovf(s21_overflow_decimal*dec1_s, s21_overflow_decimal*dec2_s,
                                                int dec1_scale, int dec2_scale) {
    int diffScale = dec1_scale - dec2_scale;
    if (diffScale < 0) {
        diffScale *= -1;
        *dec1_s = overflow_decimal_increase_scale(diffScale, dec1_scale, *dec1_s);
    } else if (diffScale > 0) {
        *dec2_s = overflow_decimal_increase_scale(diffScale, dec2_scale,  *dec2_s);
    }
}


s21_overflow_decimal overflow_decimal_increase_scale(int diffScale, int src_scale,
                                                    s21_overflow_decimal src_s) {
    s21_overflow_decimal dec_s = src_s;
    s21_overflow_decimal dec_10 = {10, 0, 0, 0, 0, 0, 0};
    for (int i = diffScale; i > 0 && dec_s.value_type == s21_NORMAL_VALUE; i--) {
        dec_s = simple_overflow_mul(dec_s, dec_10);
        src_scale++;
    }
    return dec_s;
}

s21_overflow_decimal div_simple_ovf(s21_overflow_decimal dec1, s21_overflow_decimal dec2) {
    s21_overflow_decimal res = { 0, 0, 0, 0, 0, 0, 0 };
    for (int scale = shift_left_for_div_ovf(dec1, &dec2); scale >= 0; scale--) {
        set_bit_dec_ovf(&res, 0, !overflow_is_greater(dec1, dec2) || !overflow_is_equal(dec1, dec2));
        if (get_bit_dec_ovf(res, 0)) {
            dec1 = overflow_sub(dec1, dec2);
        }
        dec2 = shift_right_overflow(dec2, 1);
        res = shift_left_overflow(res, 1);
    }
    res = shift_right_overflow(res, 1);
    return res;
}


int shift_left_for_div_ovf(s21_overflow_decimal dec1, s21_overflow_decimal* dec2) {
    int shift = 0;
    for (; !get_bit_dec_ovf(dec1, 224 - shift); shift++) {
    }
    for (int j = 0; !get_bit_dec_ovf(*dec2, 224 - j); j++, shift--) {
    }
    if (shift < 0) *dec2 = shift_left_overflow(*dec2, -shift);
    return -shift;
}


s21_overflow_decimal shift_right_overflow(s21_overflow_decimal src, int shift) {
    s21_overflow_decimal res = { 0, 0, 0, 0, 0, 0, 0 };
    for (int i = 0; i < 224; set_bit_dec_ovf(&res, i, get_bit_dec_ovf(src, shift + i)), i++) {
    }
    return res;
}

s21_overflow_decimal mod_ovf(s21_overflow_decimal dec1, s21_overflow_decimal dec2) {
    int scale = shift_left_for_div_ovf(dec1, &dec2);
    for (; scale >= 0; scale--) {
        if (!overflow_is_greater(dec1, dec2) || !overflow_is_equal(dec1, dec2)) {
            dec1 = overflow_sub(dec1, dec2);
        }
        dec2 = shift_right_overflow(dec2, 1);
    }
    return dec1;
}


unsigned get_bit_dec_ovf(s21_overflow_decimal dst, unsigned bit) {
    int res = 0;
    if (bit / 32 < 7) {
        unsigned int mask = 1u << (bit % 32);
        res = dst.bits[bit / 32] & mask;
    }
    return !!res;
}

void set_bit_dec_ovf(s21_overflow_decimal* dst, unsigned num_bit, unsigned set) {
    if (set == 1)
        dst->bits[num_bit / 32] |= (1U << num_bit);
    else
        dst->bits[num_bit / 32] &= ~(1U << num_bit);
}


int overflow_is_less(s21_overflow_decimal dec_a, s21_overflow_decimal dec_b) {
    int res = overflow_is_greater(dec_b, dec_a);
    return res;
}


int overflow_is_greater(s21_overflow_decimal dec_a, s21_overflow_decimal dec_b) {
    int res = -1;
    int prov_inf = dec_inf_ovf(&dec_a, &dec_b);
    int prov_neg_inf = dec_neg_inf_ovf(&dec_a, &dec_b);
    if ((dec_nan_ovf(&dec_a, &dec_b) == TRUE) ||
        (!is_zero_dec_ovf(dec_a, dec_b) && !dec_inf_ovf(&dec_a, &dec_b) &&
            !dec_neg_inf_ovf(&dec_a, &dec_b))) {
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
    }
    if (compare_func_ovf(dec_a, dec_b) == 0 && res == -1) {
        res = TRUE;
    }
    if (res != TRUE) {
        res = FALSE;
    }
    return res;
}

int is_zero_dec_ovf(s21_overflow_decimal dec_a, s21_overflow_decimal dec_b) {
    int res = FALSE;
    s21_overflow_decimal* tmp_a = &dec_a;
    s21_overflow_decimal* tmp_b = &dec_b;

    if (tmp_a && tmp_b) {
        if (!dec_a.bits[0] && !dec_b.bits[0] && !dec_a.bits[1] &&
            !dec_b.bits[1] && !dec_a.bits[2] && !dec_b.bits[2] &&
            !dec_b.bits[3] && !dec_b.bits[4] && !dec_b.bits[5] &&
            !dec_a.bits[3] && !dec_a.bits[4] && !dec_a.bits[5])
            res = TRUE;
    }
    return res;
}

int compare_func_ovf(s21_overflow_decimal dec_a, s21_overflow_decimal dec_b) {
    int res = -1;
    int sign_a = 0, sign_b = 0;
    for (int i = 243; i >= 0; i--) {
        if (!get_bit_dec_ovf(dec_a, i) && get_bit_dec_ovf(dec_b, i)) {
            res = 1;
            break;
        }
        if (get_bit_dec_ovf(dec_a, i) && !get_bit_dec_ovf(dec_b, i)) {
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


int dec_nan_ovf(s21_overflow_decimal* dec_a, s21_overflow_decimal* dec_b) {
    int type_a = dec_a->value_type;
    int type_b = dec_b->value_type;

    return (type_a == s21_NAN || type_b == s21_NAN) ? TRUE : FALSE;
}

int dec_inf_ovf(s21_overflow_decimal* dec_a, s21_overflow_decimal* dec_b) {
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

int dec_neg_inf_ovf(s21_overflow_decimal* dec_a, s21_overflow_decimal* dec_b) {
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

unsigned dec_div_10_overflow(s21_overflow_decimal* src) {
    unsigned out = 0, i = get_last_bit_ovf(*src);
    s21_overflow_decimal ten, buff, divided;
    s21_decimal ten_dec = { 10, 0, 0, 0 };
    s21_decimal zero = { 0, 0, 0, 0 };
    buff = init_overflow(zero);
    ten = init_overflow(ten_dec);
    divided = init_overflow(zero);
    for (; i >= 3; i--) {
        buff = shift_left_overflow(ten, i - 3);
        divided = shift_left_overflow(divided, 1);
        if (overflow_is_less(*src, buff)) {
            *src = overflow_sub(*src, buff);
            set_bit(&divided.bits[0], 0, 1);
        }
    }
    out = (*src).bits[0];
    *src = divided;
    return out;
}

unsigned get_last_bit_ovf(s21_overflow_decimal src) {
    unsigned i;
    for (i = 223; i > 0; i--) {
        if (get_bit(src.bits[i / 32], i % 32)) break;
    }
    return i;
}


s21_overflow_decimal overflow_sub(s21_overflow_decimal dec_a, s21_overflow_decimal dec_b) {
    s21_overflow_decimal res;
    s21_overflow_decimal min, max;
    s21_decimal zero = { 0, 0, 0, 0 };
    min = init_overflow(zero);
    max = init_overflow(zero);
    res = init_overflow(zero);
    int sign_a = 0;
    int sign_b = 0;
    int fin_scale = 0;
    int fin_sign = 0;
    if (overflow_is_equal(dec_a, dec_b) == FALSE) {
        if (overflow_is_less(dec_a, dec_b) == FALSE) {
            min = dec_b;
            max = dec_a;
            fin_sign = sign_a;
        } else {
            min = dec_a;
            max = dec_b;
            fin_sign = !sign_b;
        }
        overflow_to_addcode(&min);
        res = overflow_add(min, max);
    } else {
        res = init_overflow(zero);
    }
    return res;
}

int overflow_is_equal(s21_overflow_decimal dec_a, s21_overflow_decimal dec_b) {
    int res = FALSE;
    int prov_inf = dec_inf_ovf(&dec_a, &dec_b);
    int prov_neg_inf = dec_neg_inf_ovf(&dec_a, &dec_b);
    if (dec_nan_ovf(&dec_a, &dec_b) == TRUE) {
        res = FALSE;
    } else {
        int comp = compare_func_ovf(dec_a, dec_b);
        if (comp != 2) {
            res = FALSE;
        } else {
            res = TRUE;
        }
        if (is_zero_dec_ovf(dec_a, dec_b) == TRUE) {
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


void overflow_to_addcode(s21_overflow_decimal* dec) {
    s21_overflow_decimal add;
    s21_overflow_decimal one;
    s21_decimal one_dec = { 1, 0, 0, 0 };
    one = init_overflow(one_dec);
    dec->bits[0] = ~dec->bits[0];
    dec->bits[1] = ~dec->bits[1];
    dec->bits[2] = ~dec->bits[2];
    dec->bits[3] = ~dec->bits[3];
    dec->bits[4] = ~dec->bits[4];
    dec->bits[5] = ~dec->bits[5];
    dec->bits[6] = ~dec->bits[6];
    add = overflow_add(*dec, one);
    dec->bits[0] = add.bits[0];
    dec->bits[1] = add.bits[1];
    dec->bits[2] = add.bits[2];
    dec->bits[3] = add.bits[3];
    dec->bits[4] = add.bits[4];
    dec->bits[5] = add.bits[5];
    dec->bits[6] = add.bits[6];
    dec->value_type = s21_ADDCODE_OVF;
}
