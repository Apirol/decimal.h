#include <check.h>

#include "s21_decimal.h"

#define INT_TEST_0 100
#define INT_TEST_1 -100
#define INT_TEST_2 0
#define INT_TEST_3 -999

#define FLT_TEST_0 100.900
#define FLT_TEST_1 -100.900
#define FLT_TEST_2 0.900
#define FLT_TEST_3 -0.900

START_TEST(s21_from_int_to_decimal_1) {
    s21_decimal val;

    s21_from_int_to_decimal(0, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);

    s21_from_int_to_decimal(-128, &val);
    ck_assert_int_eq(val.bits[0], 128);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 2147483648);

    s21_from_int_to_decimal(127, &val);
    ck_assert_int_eq(val.bits[0], 127);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);

    s21_from_int_to_decimal(-2147483648, &val);
    ck_assert_int_eq(val.bits[0], 2147483648);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 2147483648);

    s21_from_int_to_decimal(2147483647, &val);
    ck_assert_int_eq(val.bits[0], 2147483647);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_1) {
    s21_decimal val;

    s21_from_float_to_decimal(0.03, &val);
    ck_assert_int_eq(val.bits[0], 3);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 131072);

    s21_from_float_to_decimal(127.1234, &val);
    ck_assert_int_eq(val.bits[0], 1271234);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 262144);
}
END_TEST
START_TEST(s21_from_float_to_decimal_2) {
    s21_decimal val;
    s21_from_float_to_decimal(-128.023, &val);
    ck_assert_int_eq(val.bits[0], 12802299);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    // ck_assert_int_eq(val.bits[3], -2147155968);
}
START_TEST(s21_from_float_to_decimal_3) {
    s21_decimal val;
    s21_from_float_to_decimal(-2.1474836E+09, &val);
    ck_assert_int_eq(val.bits[0], 2147483648);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 2147483648);
}
END_TEST
START_TEST(s21_from_float_to_decimal_4) {
    s21_decimal val;
    s21_from_float_to_decimal(22.14836E+03, &val);
    ck_assert_int_eq(val.bits[0], 2214836);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 131072);
}
END_TEST
START_TEST(s21_from_float_to_decimal_5) {
    s21_decimal val;
    s21_from_float_to_decimal(1.02E+09, &val);
    ck_assert_int_eq(val.bits[0], 1020000000);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}
END_TEST
START_TEST(s21_from_float_to_decimal_6) {
    s21_decimal val;
    s21_from_float_to_decimal(-333.2222, &val);
    ck_assert_int_eq(val.bits[0], 3332222);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    // ck_assert_int_eq(val.bits[3], -2147221504);
}
END_TEST
START_TEST(s21_from_float_to_decimal_7) {
    s21_decimal val;
    float a = 1.0 / 0.0;
    s21_from_float_to_decimal(a, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}
END_TEST
START_TEST(s21_from_float_to_decimal_8) {
    s21_decimal val;
    float a = -1.0 / 0.0;
    s21_from_float_to_decimal(a, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}
END_TEST
START_TEST(s21_from_float_to_decimal_9) {
    s21_decimal val;
    float a = 0.0 / 0.0;
    s21_from_float_to_decimal(a, &val);
    ck_assert_int_eq(val.bits[0], 0);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_1) {
    s21_decimal src;
    int result = 0, number = 0;
    src.value_type = 0;
    src.bits[0] = INT_MAX;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 0;
    result = s21_from_decimal_to_int(src, &number);
    ck_assert_float_eq(number, 2147483647);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_int_2) {
    s21_decimal src;
    int result = 0, number = 0;
    src.value_type = 0;
    src.bits[0] = 133141;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 0;
    result = s21_from_decimal_to_int(src, &number);
    ck_assert_int_eq(number, 133141);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_int_3) {
    s21_decimal src;
    int result = 0, number = 0;
    src.value_type = 0;
    src.bits[0] = 2147483647;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 0;
    set_bit_dec(&src, 127, 1);
    result = s21_from_decimal_to_int(src, &number);
    ck_assert_int_eq(number, -2147483647);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_int_4) {
    s21_decimal src;
    int result = 0, number = 0;
    src.value_type = 0;
    src.bits[0] = 123451234;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 2147483648;
    result = s21_from_decimal_to_int(src, &number);
    ck_assert_int_eq(number, -123451234);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_int_5) {
    s21_decimal src;
    int result = 0, number = 0;
    src.value_type = 0;
    src.bits[0] = 18;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 2147483648;
    result = s21_from_decimal_to_int(src, &number);
    ck_assert_int_eq(number, -18);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_int_6) {
    s21_decimal src;
    int result = 0, number = 0;
    src.value_type = 0;
    src.bits[0] = 4294967295;
    src.bits[1] = 4294967295;
    src.bits[2] = 0;
    src.bits[3] = 0;
    result = s21_from_decimal_to_int(src, &number);
    ck_assert_int_eq(number, 0xFFFFFFFFFFFFFFFF);
    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_1) {
    s21_decimal src;
    int result = 0;
    float number = 0.0;
    src.value_type = 0;
    src.bits[0] = 18122;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 2147680256;
    result = s21_from_decimal_to_float(src, &number);
    ck_assert_float_eq(number, -18.122);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_float_2) {
    s21_decimal src;
    int result = 0;
    float number = 0.0;
    src.value_type = 0;
    src.bits[0] = 1812;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 2147483648;
    result = s21_from_decimal_to_float(src, &number);
    ck_assert_float_eq(number, -1812);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_float_3) {
    s21_decimal src;
    int result = 0;
    float number = 0.0;
    src.value_type = 0;
    src.bits[0] = 0XFFFFFF;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 0;
    result = s21_from_decimal_to_float(src, &number);
    ck_assert_float_eq(number, 16777215);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_float_4) {
    s21_decimal src;
    int result = 0;
    float number = 0.0;
    src.value_type = 0;
    src.bits[0] = 23450987;
    src.bits[1] = 0;
    src.bits[2] = 0;
    src.bits[3] = 2147745792;
    result = s21_from_decimal_to_float(src, &number);
    ck_assert_float_eq(number, -2345.0987);
    ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_float_5) {
    s21_decimal src;
    int result = 0;
    float number = 0.0;
    src.value_type = 0;
    src.bits[0] = 4294967295;
    src.bits[1] = 4294967295;
    src.bits[2] = 0;
    src.bits[3] = 0;
    result = s21_from_decimal_to_float(src, &number);
    ck_assert_float_eq(number, 0xFFFFFFFFFFFFFFFF);
    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_int_to_dec) {
    s21_decimal res_dec, correct_result;
    init_dec_bits(&res_dec), init_dec_bits(&correct_result);
    int signed_integer = 0, res_of_conv = 0;

    // check NULL
    res_of_conv = s21_from_int_to_decimal(signed_integer, NULL);
    ck_assert_int_eq(res_of_conv, 1);

    // check 0
    res_of_conv = s21_from_int_to_decimal(signed_integer, &res_dec);
    str_to_dec("0", &correct_result, 0);
    ck_assert_int_eq(res_of_conv, 0);
    ck_assert_int_eq(s21_is_equal(correct_result, res_dec), 0);

    // check 123456789
    signed_integer = 123456789;
    res_of_conv = s21_from_int_to_decimal(signed_integer, &res_dec);
    str_to_dec("111010110111100110100010101", &correct_result, 0);
    ck_assert_int_eq(res_of_conv, 0);
    ck_assert_int_eq(s21_is_equal(correct_result, res_dec), 0);

    // check -123456789
    signed_integer = -123456789;
    res_of_conv = s21_from_int_to_decimal(signed_integer, &res_dec);
    str_to_dec("-111010110111100110100010101", &correct_result, 0);
    ck_assert_int_eq(res_of_conv, 0);
    ck_assert_int_eq(s21_is_equal(correct_result, res_dec), 0);
}
END_TEST

START_TEST(from_float_to_dec) {
    s21_decimal res, correct_result;
    init_dec_bits(&res), init_dec_bits(&correct_result);
    int res_of_conv = 0;
    float fl_val = 0;

    // check NULL
    res_of_conv = s21_from_float_to_decimal(fl_val, NULL);
    ck_assert_int_eq(res_of_conv, 1);

    // check NaN
    fl_val = NAN;
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 1);
    ck_assert_int_eq(res.value_type, s21_NAN);

    // check INF
    fl_val = INFINITY;
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 1);
    ck_assert_int_eq(res.value_type, s21_INFINITY);

    // check -INF
    fl_val = -INFINITY;
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 1);
    ck_assert_int_eq(res.value_type, s21_NEGATIVE_INFINITY);

    // check 0
    fl_val = 0;
    res_of_conv = s21_from_int_to_decimal(fl_val, &res);
    str_to_dec("0", &correct_result, 0);
    ck_assert_int_eq(res_of_conv, 0);
    ck_assert_int_eq(s21_is_equal(correct_result, res), 0);

    // new tests
    // printf("%.30f\n%.30f\n%.30f\n", fl_val, back_conv, (fl_val - back_conv));
    fl_val = 123.123456;
    float eps = 1e-5;
    // fl_bits fl = {.fl = fl_val};
    float back_conv = 0;
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 0);
    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    ck_assert_float_lt((fl_val - back_conv), eps);

    fl_val = pow(2, 95);
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 0);
    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    // ck_assert_float_lt((fl_val - back_conv), eps);
    fl_val = pow(2, 68), back_conv = 0, init_dec_bits(&res);
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 0);
    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    // ck_assert_float_lt((fl_val - back_conv), eps);
    fl_val = pow(2, 27), back_conv = 0, init_dec_bits(&res);
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 0);
    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    ck_assert_float_lt((fl_val - back_conv), eps);

    fl_val = 123.777, back_conv = 0, init_dec_bits(&res);
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 0);
    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    ck_assert_float_lt((fl_val - back_conv), eps);

    fl_val = -123.777, back_conv = 0, init_dec_bits(&res);
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 0);
    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    ck_assert_float_lt((fl_val - back_conv), eps);

    fl_val = pow(2, 72), back_conv = 0, init_dec_bits(&res);
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 0);
    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    // ck_assert_float_lt((fl_val - back_conv), eps);

    fl_val = 10000000, back_conv = 0, init_dec_bits(&res);
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 0);
    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    ck_assert_float_lt((fl_val - back_conv), eps);

    fl_val = 123.456897, back_conv = 0, init_dec_bits(&res);
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 0);
    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    ck_assert_float_lt((fl_val - back_conv), eps);

    // new new test
    fl_val = 0.0, back_conv = 0.0, init_dec_bits(&res);
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 1);
    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    ck_assert_float_lt((fl_val - back_conv), eps);

    fl_val = 0.6, back_conv = 0.0, init_dec_bits(&res);
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 0);
    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    ck_assert_float_lt((fl_val - back_conv), eps);

    fl_val = 0.06, back_conv = 0.0, init_dec_bits(&res);
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 0);

    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    ck_assert_float_lt((fl_val - back_conv), eps);

    fl_val = 0.223648, back_conv = 0.0, init_dec_bits(&res);
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 0);
    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    ck_assert_float_lt((fl_val - back_conv), eps);

    fl_val = 0.000000000000001, back_conv = 0.0, init_dec_bits(&res);
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 0);
    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    ck_assert_float_lt((fl_val - back_conv), eps);

    fl_val = 10e-28, back_conv = 0.0, init_dec_bits(&res);

    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 0);
    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    ck_assert_float_lt((fl_val - back_conv), eps);

    fl_val = 10e-29, back_conv = 0.0, init_dec_bits(&res);
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 1);
    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    // ck_assert_float_lt((fl_val - back_conv), eps);

    fl_val = 128935798234578236870459., back_conv = 0.0, init_dec_bits(&res);
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 0);
    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    // ck_assert_float_lt((fl_val - back_conv), eps);

    fl_val = -7283946982385609.12904580, back_conv = 0.0, init_dec_bits(&res);
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 0);
    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    ck_assert_float_lt((fl_val - back_conv), eps);

    fl_val = -0.234634573467456868, back_conv = 0.0, init_dec_bits(&res);
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 0);
    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    // ck_assert_float_lt((fl_val - back_conv), eps);

    fl_val = -0.344375236702030878974356, back_conv = 0.0, init_dec_bits(&res);
    res_of_conv = s21_from_float_to_decimal(fl_val, &res);
    ck_assert_int_eq(res_of_conv, 0);
    res_of_conv = s21_from_decimal_to_float(res, &back_conv);
    ck_assert_int_eq(res_of_conv, 0);
    // ck_assert_float_lt((fl_val - back_conv), eps);
}
END_TEST

START_TEST(from_dec_to_int) {
    s21_decimal dec;
    init_dec_bits(&dec);
    int res_of_conv = 0, converted_int = 0;

    // check NULL
    res_of_conv = s21_from_decimal_to_int(dec, NULL);
    ck_assert_int_eq(res_of_conv, 1);

    // check INF
    dec.value_type = s21_INFINITY;
    res_of_conv = s21_from_decimal_to_int(dec, &converted_int);
    ck_assert_int_eq(res_of_conv, 1);

    // check NEG_INF
    dec.value_type = s21_NEGATIVE_INFINITY;
    res_of_conv = s21_from_decimal_to_int(dec, &converted_int);
    ck_assert_int_eq(res_of_conv, 1);

    // check NaN
    dec.value_type = s21_NAN;
    res_of_conv = s21_from_decimal_to_int(dec, &converted_int);
    ck_assert_int_eq(res_of_conv, 1);
    init_dec_bits(&dec);

    // check overflow INT_MAX + 1 = 2147483648
    str_to_dec("10000000000000000000000000000000", &dec, 0);
    res_of_conv = s21_from_decimal_to_int(dec, &converted_int);
    ck_assert_int_eq(res_of_conv, 0);
    init_dec_bits(&dec);

    // // check max
    str_to_dec("1111111111111111111111111111111", &dec, 0);
    res_of_conv = s21_from_decimal_to_int(dec, &converted_int);
    ck_assert_int_eq(converted_int, INT_MAX);
    ck_assert_int_eq(res_of_conv, 0);
    init_dec_bits(&dec);

    // // check min
    str_to_dec("-10000000000000000000000000000000", &dec, 0);
    res_of_conv = s21_from_decimal_to_int(dec, &converted_int);
    ck_assert_int_eq(converted_int, INT_MIN);
    ck_assert_int_eq(res_of_conv, 0);
    init_dec_bits(&dec);

    // // check float 999999.875
    str_to_dec("111011100110101100100110000011", &dec, 3);
    res_of_conv = s21_from_decimal_to_int(dec, &converted_int);
    ck_assert_int_eq(converted_int, 999999);
    ck_assert_int_eq(res_of_conv, 0);
    init_dec_bits(&dec);
}
END_TEST

START_TEST(from_dec_to_float) {
    s21_decimal dec;
    init_dec_bits(&dec);
    int res_of_conv = 0;
    float converted_fl = 0, correct_result = 0;

    // check NULL
    res_of_conv = s21_from_decimal_to_float(dec, NULL);
    ck_assert_int_eq(res_of_conv, 1);

    // check INF
    dec.value_type = s21_INFINITY;
    res_of_conv = s21_from_decimal_to_float(dec, &converted_fl);
    ck_assert_int_eq(res_of_conv, 1);
    // ck_assert_int_eq(1, isinf(converted_fl));

    // check NEG_INF
    dec.value_type = s21_NEGATIVE_INFINITY;
    res_of_conv = s21_from_decimal_to_float(dec, &converted_fl);
    ck_assert_int_eq(res_of_conv, 1);
    // ck_assert_int_eq(1, isinf(-converted_fl));

    // check NaN
    dec.value_type = s21_NAN;
    res_of_conv = s21_from_decimal_to_float(dec, &converted_fl);
    ck_assert_int_eq(res_of_conv, 1);
    // ck_assert_int_eq(1, isnan(converted_fl));

    init_dec_bits(&dec);
    // check max 79228162514264337593543950335
    correct_result = 79228162514264337593543950335.;
    str_to_dec(
        "1111111111111111111111111111111111111111111111111111111111111111111111"
        "11111111111111111111111111",
        &dec, 0);
    res_of_conv = s21_from_decimal_to_float(dec, &converted_fl);
    // ck_assert_float_eq(converted_fl, correct_result);
    ck_assert_int_eq(res_of_conv, 0);
    init_dec_bits(&dec);

    // check min 1e-28
    correct_result = 1e-28;
    str_to_dec("1", &dec, 28);
    res_of_conv = s21_from_decimal_to_float(dec, &converted_fl);
    ck_assert_float_eq(converted_fl, correct_result);
    ck_assert_int_eq(res_of_conv, 0);
    init_dec_bits(&dec);

    // check precise 1.234567
    correct_result = 1.234567;
    str_to_dec("100101101011010000111", &dec, 6);
    res_of_conv = s21_from_decimal_to_float(dec, &converted_fl);
    ck_assert_float_eq(converted_fl, correct_result);
    ck_assert_int_eq(res_of_conv, 0);
    init_dec_bits(&dec);
}
END_TEST

START_TEST(compare_less) {
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_less(dst1, dst2), FALSE);  // 1.2345 < 1.2
    ck_assert_int_eq(s21_is_less(dst2, dst1), TRUE);   // 1.2 < 1.2345

    dst1 = s21_negate(dst1);
    dst2 = s21_negate(dst2);
    ck_assert_int_eq(s21_is_less(dst1, dst2), TRUE);   // -1.2345 < -1.2
    ck_assert_int_eq(s21_is_less(dst2, dst1), FALSE);  // -1.2 < -1.2345

    dst1 = s21_negate(dst1);
    ck_assert_int_eq(s21_is_less(dst1, dst2),
                     FALSE);                          //  1.2345 < -1.2 fail
    ck_assert_int_eq(s21_is_less(dst2, dst1), TRUE);  //  -1.2 < 1.2345 fail

    s21_from_float_to_decimal(0.0, &dst1);
    s21_from_float_to_decimal(0.0, &dst2);
    ck_assert_int_eq(s21_is_less(dst1, dst2), FALSE);  // 0 < 0

    dst1.value_type = s21_INFINITY;
    dst2.value_type = s21_NORMAL_VALUE;
    ck_assert_int_eq(s21_is_less(dst1, dst2), FALSE);  // +INFINITY < 0
    ck_assert_int_eq(s21_is_less(dst2, dst1), TRUE);   // 0 < +INFINITY

    dst1.value_type = s21_NEGATIVE_INFINITY;
    dst2.value_type = s21_NORMAL_VALUE;
    ck_assert_int_eq(s21_is_less(dst1, dst2), TRUE);   // -INFINITY < 0
    ck_assert_int_eq(s21_is_less(dst2, dst1), FALSE);  // 0 < -INFINITY
}
END_TEST

START_TEST(compare_greater) {
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_greater(dst1, dst2), TRUE);   // 1.2345 > 1.2
    ck_assert_int_eq(s21_is_greater(dst2, dst1), FALSE);  // 1.2 > 1.2345

    dst1 = s21_negate(dst1);
    dst2 = s21_negate(dst2);
    ck_assert_int_eq(s21_is_greater(dst1, dst2), FALSE);  // -1.2345 > -1.2
    ck_assert_int_eq(s21_is_greater(dst2, dst1), TRUE);   // -1.2 > 1.2345

    dst1 = s21_negate(dst1);
    ck_assert_int_eq(s21_is_greater(dst1, dst2), TRUE);   //  1.2345 > -1.2
    ck_assert_int_eq(s21_is_greater(dst2, dst1), FALSE);  //  -1.2 > 1.2345

    s21_from_float_to_decimal(0.0, &dst1);
    s21_from_float_to_decimal(0.0, &dst2);
    ck_assert_int_eq(s21_is_greater(dst1, dst2), FALSE);  // 0 > 0

    dst1.value_type = s21_INFINITY;
    dst2.value_type = s21_NORMAL_VALUE;
    ck_assert_int_eq(s21_is_greater(dst1, dst2), TRUE);   // +INFINITY > 0
    ck_assert_int_eq(s21_is_greater(dst2, dst1), FALSE);  // 0 > +INFINITY

    dst1.value_type = s21_NEGATIVE_INFINITY;
    dst2.value_type = s21_NORMAL_VALUE;
    ck_assert_int_eq(s21_is_greater(dst1, dst2), FALSE);  // -INFINITY > 0
    ck_assert_int_eq(s21_is_greater(dst2, dst1), TRUE);   // 0 > -INFINITY
}
END_TEST

START_TEST(compare_less_or_equal) {
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2),
                     FALSE);  // 1.2345 <= 1.2
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1),
                     TRUE);  // 1.2 <= 1.2345

    dst1 = s21_negate(dst1);
    dst2 = s21_negate(dst2);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2),
                     TRUE);  // -1.2345 <= -1.2
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1),
                     FALSE);  // -1.2 <= 1.2345

    dst1 = s21_negate(dst1);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2),
                     FALSE);  //  1.2345 <= -1.2 // fail
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1),
                     TRUE);  //  -1.2 <= 1.2345

    s21_from_float_to_decimal(0.0, &dst1);
    s21_from_float_to_decimal(0.0, &dst2);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2), TRUE);  // 0 <= 0

    dst1.value_type = s21_INFINITY;
    dst2.value_type = s21_NORMAL_VALUE;
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2),
                     FALSE);  // +INFINITY <= 0
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1),
                     TRUE);  // 0 <= +INFINITY

    dst1.value_type = s21_INFINITY;
    dst2.value_type = s21_INFINITY;
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1),
                     TRUE);  // +INFINITY <= +INFINITY

    dst1.value_type = s21_NEGATIVE_INFINITY;
    dst2.value_type = s21_NORMAL_VALUE;
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2),
                     TRUE);  // -INFINITY <= 0
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1),
                     FALSE);  // 0 <= -INFINITY

    s21_from_float_to_decimal(1726.73, &dst1);
    s21_from_float_to_decimal(1726.73, &dst2);
    ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2),
                     TRUE);  // 1726.73 <= 1726.73
}
END_TEST

START_TEST(compare_greater_or_equal) {
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2),
                     TRUE);  // 1.2345 >= 1.2
    ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1),
                     FALSE);  // 1.2 >= 1.2345

    dst1 = s21_negate(dst1);
    dst2 = s21_negate(dst2);
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2),
                     FALSE);  // -1.2345 >= -1.2
    ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1),
                     TRUE);  // -1.2 >= 1.2345

    dst1 = s21_negate(dst1);
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2),
                     TRUE);  //  1.2345 >= -1.2 // fail
    ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1),
                     FALSE);  //  -1.2 >= 1.2345

    s21_from_float_to_decimal(0.0, &dst1);
    s21_from_float_to_decimal(0.0, &dst2);
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2), TRUE);  // 0 >= 0

    dst1.value_type = s21_INFINITY;
    dst2.value_type = s21_NORMAL_VALUE;
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2),
                     TRUE);  // +INFINITY >= 0
    ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1),
                     FALSE);  // 0 >= +INFINITY

    dst1.value_type = s21_NEGATIVE_INFINITY;
    dst2.value_type = s21_NORMAL_VALUE;
    ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2),
                     FALSE);  // -INFINITY >= 0
    ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1),
                     TRUE);  // 0 >= -INFINITY
}
END_TEST

START_TEST(compare_equal) {
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_equal(dst1, dst2), FALSE);  // 1.2345 = 1.2

    s21_from_float_to_decimal(1.2, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    dst1.value_type = s21_NEGATIVE_INFINITY;
    dst2.value_type = s21_NEGATIVE_INFINITY;
    ck_assert_int_eq(s21_is_equal(dst1, dst2), TRUE);  // 1.2 = 1.2

    s21_from_float_to_decimal(-234.17, &dst1);
    s21_from_float_to_decimal(234.17, &dst2);
    ck_assert_int_eq(s21_is_equal(dst1, dst2), FALSE);

    s21_from_float_to_decimal(234.17, &dst1);
    s21_from_float_to_decimal(234.17, &dst2);
    ck_assert_int_eq(s21_is_equal(dst1, dst2), TRUE);

    dst1.value_type = s21_INFINITY;
    dst2.value_type = s21_INFINITY;
    ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1),
                     TRUE);  // +INFINITY = +INFINITY
}
END_TEST

START_TEST(compare_equal_null) {
    s21_decimal dst1, dst2;
    s21_from_int_to_decimal(0, &dst1);  // -0 == 0
    s21_from_int_to_decimal(0, &dst2);
    dst1.bits[3] = SIGN;
    ck_assert_int_eq(s21_is_equal(dst1, dst2), TRUE);
    s21_from_int_to_decimal(0, &dst1);  // NAN == NAN
    s21_from_int_to_decimal(0, &dst2);
    dst1.value_type = s21_NAN;
    dst2.value_type = s21_NAN;
    ck_assert_int_eq(s21_is_equal(dst1, dst2), FALSE);
}
END_TEST

START_TEST(compare_not_equal) {
    s21_decimal dst1, dst2;

    s21_from_float_to_decimal(1.2345, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_not_equal(dst1, dst2), TRUE);  // 1.2345 = 1.2

    s21_from_float_to_decimal(1.2, &dst1);
    s21_from_float_to_decimal(1.2, &dst2);
    ck_assert_int_eq(s21_is_not_equal(dst1, dst2), FALSE);  // 1.2 = 1.2

    s21_from_float_to_decimal(-234.17, &dst1);
    s21_from_float_to_decimal(234.17, &dst2);
    dst1.value_type = s21_NEGATIVE_INFINITY;
    dst2.value_type = s21_NEGATIVE_INFINITY;
    ck_assert_int_eq(s21_is_not_equal(dst1, dst2), FALSE);

    s21_from_float_to_decimal(234.17, &dst1);
    s21_from_float_to_decimal(234.17, &dst2);
    ck_assert_int_eq(s21_is_not_equal(dst1, dst2), FALSE);
}
END_TEST

START_TEST(eq_funcs_test) {
    s21_decimal dec1, dec2;
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);
    dec1.bits[0] = 1325411;
    dec2.bits[0] = 1325411;
    dec1.bits[1] = 121;
    dec2.bits[1] = 121;
    dec1.bits[2] = 213;
    dec2.bits[2] = 213;

    ck_assert_int_eq(s21_is_equal(dec1, dec2), 0);

    ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 1);
    set_bit_dec(&dec2, 127, 1);
    ck_assert_int_eq(s21_is_equal(dec1, dec2), 1);
    ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 0);

    set_bit_dec(&dec1, 127, 1);

    ck_assert_int_eq(s21_is_equal(dec1, dec2), 0);
    ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 1);

    dec2.bits[0] = 132541;

    ck_assert_int_eq(s21_is_equal(dec1, dec2), 1);
    ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 0);

    dec1.bits[0] = 2147483647;
    dec2.bits[0] = 2147483647;
    dec1.bits[1] = 0;
    dec2.bits[1] = 2147483647;
    dec1.bits[2] = 2147483647;
    dec2.bits[2] = 2147483647;

    ck_assert_int_eq(s21_is_equal(dec1, dec2), 1);
    ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 0);

    str_to_dec("-1010011110", &dec1, 1);
    str_to_dec("-1000011", &dec2, 0);
    ck_assert_int_eq(s21_is_equal(dec1, dec2), TRUE);
    ck_assert_int_eq(s21_is_not_equal(dec1, dec2), FALSE);

    // new_test
    str_to_dec(
        "1001111110010000011011001100101110000011110001011000110110100100000011"
        "110101000001000100100011",
        &dec1, 12);
    str_to_dec(
        "1001111110010000011011001100101110000011110001011000110110100100000011"
        "110101000001000100100011",
        &dec2, 12);
    ck_assert_int_eq(s21_is_not_equal(dec1, dec2), FALSE);

    dec2.value_type = s21_INFINITY;
    ck_assert_int_eq(s21_is_not_equal(dec1, dec2), TRUE);

    dec1.value_type = s21_INFINITY;
    ck_assert_int_eq(s21_is_not_equal(dec1, dec2), FALSE);
}
END_TEST

START_TEST(greater_funcs_test) {
    s21_decimal dec1, dec2;
    init_dec_bits(&dec1);
    dec1.value_type = s21_NORMAL_VALUE;
    init_dec_bits(&dec2);
    dec2.value_type = s21_NORMAL_VALUE;
    dec1.bits[0] = 1325411;
    dec2.bits[0] = 1325411;
    dec1.bits[1] = 121;
    dec2.bits[1] = 121;
    dec1.bits[2] = 213;
    dec2.bits[2] = 213;

    // dec1 == dec2
    ck_assert_int_eq(s21_is_greater(dec1, dec2), 1);
    ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2), 0);

    dec2.bits[0] = 15;
    // dec1 > dec2
    ck_assert_int_eq(s21_is_greater(dec1, dec2), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2), 0);

    set_bit_dec(&dec1, 127, 1);
    // dec1 < dec2
    ck_assert_int_eq(s21_is_greater(dec1, dec2), 1);
    ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2), 1);

    set_bit_dec(&dec2, 127, 1);
    // dec1 < dec2
    ck_assert_int_eq(s21_is_greater(dec1, dec2), 1);
    ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2), 1);

    dec1.bits[3] = 0;
    // dec1 > dec2
    ck_assert_int_eq(s21_is_greater(dec1, dec2), 0);
    ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2), 0);

    str_to_dec("10000000000000000000000000000000", &dec1, 0);

    str_to_dec("100000000000000000000000000000000", &dec2, 0);
    ck_assert_int_eq(s21_is_greater(dec1, dec2), FALSE);
    ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2), FALSE);

    // new test
    str_to_dec(
        "1001111110010000011011001100101110000011110001011000110110100100000011"
        "110101000001000100100011",
        &dec1, 12);
    str_to_dec(
        "1001111110010000011011001100101110000011110001011000110110100100000011"
        "110101000001000100100011",
        &dec2, 12);

    ck_assert_int_eq(s21_is_greater(dec1, dec2), FALSE);

    str_to_dec(
        "1001111110010000011011001100101110000011110001011000110110100100000011"
        "110101000001000100100011",
        &dec2, 11);
    ck_assert_int_eq(s21_is_greater(dec1, dec2), FALSE);

    str_to_dec(
        "1001111110010000011011001100101110000011110001011000110110100100000011"
        "110101000001000100100011",
        &dec2, 13);
    ck_assert_int_eq(s21_is_greater(dec1, dec2), TRUE);

    dec1.value_type == s21_INFINITY;
    ck_assert_int_eq(s21_is_greater(dec1, dec2), TRUE);

    dec2.value_type == s21_NEGATIVE_INFINITY;
    ck_assert_int_eq(s21_is_greater(dec1, dec2), TRUE);

    dec2.value_type == s21_NORMAL_VALUE;
    ck_assert_int_eq(s21_is_greater(dec1, dec2), TRUE);
    dec2.value_type == s21_INFINITY;
    dec1.value_type == s21_NORMAL_VALUE;
    ck_assert_int_eq(s21_is_greater(dec1, dec2), TRUE);
}
END_TEST

START_TEST(lesser_funcs_test) {
    s21_decimal dec1, dec2;
    init_dec_bits(&dec1);
    dec1.value_type = s21_NORMAL_VALUE;
    init_dec_bits(&dec2);
    dec2.value_type = s21_NORMAL_VALUE;
    dec1.bits[0] = 1325411;
    dec2.bits[0] = 1325411;
    dec1.bits[1] = 121;
    dec2.bits[1] = 121;
    dec1.bits[2] = 213;
    dec2.bits[2] = 213;

    // dec1 == dec2
    ck_assert_int_eq(s21_is_less(dec1, dec2), 1);
    ck_assert_int_eq(s21_is_less_or_equal(dec1, dec2), 0);

    dec2.bits[0] = 15;
    // dec1 > dec2
    ck_assert_int_eq(s21_is_less(dec1, dec2), 1);
    ck_assert_int_eq(s21_is_less_or_equal(dec1, dec2), 1);

    set_bit_dec(&dec1, 127, 1);
    // dec1 < dec2
    ck_assert_int_eq(s21_is_less(dec1, dec2), 0);
    ck_assert_int_eq(s21_is_less_or_equal(dec1, dec2), 0);

    set_bit_dec(&dec2, 127, 1);
    // dec1 < dec2
    ck_assert_int_eq(s21_is_less(dec1, dec2), 0);
    ck_assert_int_eq(s21_is_less_or_equal(dec1, dec2), 0);

    dec1.bits[3] = 0;
    // dec1 > dec2
    ck_assert_int_eq(s21_is_less(dec1, dec2), 1);
    ck_assert_int_eq(s21_is_less_or_equal(dec1, dec2), 1);
}
END_TEST

START_TEST(eq_funcs_test_float_point) {
    s21_decimal dec1, dec2;
    // 5.201
    str_to_dec("1010001010001", &dec1, 3);
    // 5.201
    str_to_dec("1010001010001", &dec2, 3);
    ck_assert_int_eq(s21_is_equal(dec1, dec2), 0);
    ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 1);
    // 5.201
    str_to_dec("1010001010001", &dec1, 3);
    // 52.01
    str_to_dec("1010001010001", &dec2, 2);
    ck_assert_int_eq(s21_is_equal(dec1, dec2), 1);
    ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 0);

    // 174536166.053
    str_to_dec("10100010100011001010101000101010100101", &dec1, 3);
    // 174536.166053
    str_to_dec("10100010100011001010101000101010100101", &dec2, 6);
    ck_assert_int_eq(s21_is_equal(dec1, dec2), 1);
    ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 0);

    // 174536.166053
    str_to_dec("10100010100011001010101000101010100101", &dec1, 6);
    // 174536.166053
    str_to_dec("10100010100011001010101000101010100101", &dec2, 6);
    ck_assert_int_eq(s21_is_equal(dec1, dec2), 0);
    ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 1);

    // 0.00
    init_dec_bits(&dec1);
    str_to_dec("", &dec1, 2);
    // 0
    init_dec_bits(&dec2);
    str_to_dec("", &dec2, 0);
    ck_assert_int_eq(s21_is_equal(dec1, dec2), 0);
    ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 1);
}
END_TEST

START_TEST(greater_test_float_point) {
    s21_decimal dec1, dec2;
    // 5.201
    str_to_dec("1010001010001", &dec1, 3);
    // 5.201
    str_to_dec("1010001010001", &dec2, 3);
    ck_assert_int_eq(s21_is_greater(dec1, dec2), 1);
    ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2), 0);
    // 5.201
    str_to_dec("1010001010001", &dec1, 3);
    // 52.01
    str_to_dec("1010001010001", &dec2, 2);
    ck_assert_int_eq(s21_is_greater(dec1, dec2), FALSE);
    ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2), FALSE);

    // 52.01
    str_to_dec("1010001010001", &dec1, 2);
    // 5.201
    str_to_dec("1010001010001", &dec2, 3);
    ck_assert_int_eq(s21_is_greater(dec1, dec2), TRUE);
    ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2), TRUE);

    // 174536166.053
    str_to_dec("10100010100011001010101000101010100101", &dec1, 3);
    // 174536.166053
    str_to_dec("10100010100011001010101000101010100101", &dec2, 6);
    ck_assert_int_eq(s21_is_greater(dec1, dec2), TRUE);
    ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2), TRUE);

    // 174536.166053
    str_to_dec("10100010100011001010101000101010100101", &dec1, 6);
    // 174536.166053
    str_to_dec("10100010100011001010101000101010100101", &dec2, 6);
    ck_assert_int_eq(s21_is_greater(dec1, dec2), FALSE);
    ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2), TRUE);

    // 563715.1
    str_to_dec("10101100000010000011111", &dec1, 1);
    // 174536.166053
    str_to_dec("1010", &dec2, 0);
    ck_assert_int_eq(s21_is_greater(dec1, dec2), TRUE);
    ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2), TRUE);

    str_to_dec("1111", &dec1, 1);
    // 174536.166053
    str_to_dec("1", &dec2, 0);
    ck_assert_int_eq(s21_is_greater(dec1, dec2), TRUE);
    ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2), TRUE);
}
END_TEST

START_TEST(s21_int_to_dec_vv_test) {
    s21_decimal dec0;
    int int0;
    float flt0;
    s21_from_int_to_decimal(INT_TEST_0, &dec0);
    s21_from_decimal_to_int(dec0, &int0);
    ck_assert_int_eq(int0, INT_TEST_0);
    s21_from_int_to_decimal(INT_TEST_1, &dec0);
    s21_from_decimal_to_int(dec0, &int0);
    ck_assert_int_eq(int0, INT_TEST_1);
    s21_from_int_to_decimal(INT_TEST_2, &dec0);
    s21_from_decimal_to_int(dec0, &int0);
    ck_assert_int_eq(int0, INT_TEST_2);
    s21_from_int_to_decimal(INT_TEST_3, &dec0);
    s21_from_decimal_to_int(dec0, &int0);
    ck_assert_int_eq(int0, INT_TEST_3);

    // float to int
    s21_from_int_to_decimal(INT_TEST_0, &dec0);
    s21_from_decimal_to_float(dec0, &flt0);
    ck_assert_float_eq(flt0, (float)INT_TEST_0);
}
END_TEST

START_TEST(s21_flt_to_dec_vv_test) {
    s21_decimal dec0;
    int int0;
    float flt0;
    s21_from_float_to_decimal(FLT_TEST_0, &dec0);
    s21_from_decimal_to_float(dec0, &flt0);
    ck_assert_float_eq(flt0, FLT_TEST_0);
    s21_from_float_to_decimal(FLT_TEST_1, &dec0);
    s21_from_decimal_to_float(dec0, &flt0);
    ck_assert_float_eq(flt0, FLT_TEST_1);
    s21_from_float_to_decimal(FLT_TEST_2, &dec0);
    s21_from_decimal_to_float(dec0, &flt0);
    ck_assert_float_eq(flt0, FLT_TEST_2);
    s21_from_float_to_decimal(FLT_TEST_3, &dec0);
    s21_from_decimal_to_float(dec0, &flt0);
    ck_assert_float_eq(flt0, FLT_TEST_3);

    // int to float
    s21_from_float_to_decimal(FLT_TEST_0, &dec0);
    s21_from_decimal_to_int(dec0, &int0);
    ck_assert_int_eq(int0, (int)FLT_TEST_0);
}
END_TEST

START_TEST(s21_round_test) {
    s21_decimal dec0;
    int int0;
    float flt0;
    s21_from_float_to_decimal(FLT_TEST_0, &dec0);
    dec0 = s21_round(dec0);
    s21_from_decimal_to_float(dec0, &flt0);
    ck_assert_float_eq(flt0, roundf(FLT_TEST_0));
    s21_from_float_to_decimal(FLT_TEST_1, &dec0);
    dec0 = s21_round(dec0);
    s21_from_decimal_to_float(dec0, &flt0);
    ck_assert_float_eq(flt0, roundf(FLT_TEST_1));
    s21_from_float_to_decimal(FLT_TEST_2, &dec0);
    dec0 = s21_round(dec0);
    s21_from_decimal_to_float(dec0, &flt0);
    ck_assert_float_eq(flt0, roundf(FLT_TEST_2));
    s21_from_float_to_decimal(FLT_TEST_3, &dec0);
    dec0 = s21_round(dec0);
    s21_from_decimal_to_float(dec0, &flt0);
    ck_assert_float_eq(flt0, roundf(FLT_TEST_3));

    // try round int
}
END_TEST

START_TEST(s21_truncate_test) {
    s21_decimal dec0;
    int int0;
    float flt0;
    s21_from_float_to_decimal(FLT_TEST_0, &dec0);
    dec0 = s21_truncate(dec0);
    s21_from_decimal_to_float(dec0, &flt0);
    ck_assert_float_eq(flt0, truncf(FLT_TEST_0));
    s21_from_float_to_decimal(FLT_TEST_1, &dec0);
    dec0 = s21_truncate(dec0);
    s21_from_decimal_to_float(dec0, &flt0);
    ck_assert_float_eq(flt0, truncf(FLT_TEST_1));
    s21_from_float_to_decimal(FLT_TEST_2, &dec0);
    dec0 = s21_truncate(dec0);
    s21_from_decimal_to_float(dec0, &flt0);
    ck_assert_float_eq(flt0, truncf(FLT_TEST_2));
    s21_from_float_to_decimal(FLT_TEST_3, &dec0);
    dec0 = s21_truncate(dec0);
    s21_from_decimal_to_float(dec0, &flt0);
    ck_assert_float_eq(flt0, truncf(FLT_TEST_3));

    // try truncate int
}
END_TEST

START_TEST(truncate_common_values) {
    s21_decimal dec, result, correct_result;
    init_dec_bits(&result);
    // 677
    str_to_dec("1010100101", &dec, 0);
    str_to_dec("1010100101", &correct_result, 0);
    result = s21_truncate(dec);
    ck_assert_int_eq(s21_is_equal(result, correct_result), TRUE);

    // 67.7
    str_to_dec("1010100101", &dec, 1);
    //   s21_from_float_to_decimal(67.7, &dec);
    // 67
    str_to_dec("1000011", &correct_result, 0);
    result = s21_truncate(dec);
    ck_assert_int_eq(s21_is_equal(result, correct_result), TRUE);

    // -67.7
    str_to_dec("-1010100101", &dec, 1);
    // -67
    str_to_dec("-1000011", &correct_result, 0);
    result = s21_truncate(dec);
    ck_assert_int_eq(s21_is_equal(result, correct_result), TRUE);

    // 710579.877
    str_to_dec("101010010110101001011010100101", &dec, 3);
    // 710579
    str_to_dec("10101101011110110011", &correct_result, 0);
    result = s21_truncate(dec);
    ck_assert_int_eq(s21_is_equal(result, correct_result), TRUE);

    // 76297933.3938255525
    str_to_dec("101010010110101001011010100101101010010110101001011010100101",
               &dec, 10);
    // 76297933
    str_to_dec("100100011000011011011001101", &correct_result, 0);
    result = s21_truncate(dec);
    ck_assert_int_eq(s21_is_equal(result, correct_result), TRUE);

    // 819242.821697167591502157477
    str_to_dec(
        "101010010110101001011010100101101010010110101001011010100101101010"
        "0101"
        "10"
        "101001011010100101",
        &dec, 21);
    // 819242
    str_to_dec("11001000000000101010", &correct_result, 0);
    result = s21_truncate(dec);
    ck_assert_int_eq(s21_is_equal(result, correct_result), TRUE);

    // 819242821697167591502157477
    str_to_dec(
        "101010010110101001011010100101101010010110101001011010100101101010"
        "0101"
        "10"
        "101001011010100101",
        &dec, 0);
    // 819242821697167591502157477
    str_to_dec(
        "101010010110101001011010100101101010010110101001011010100101101010"
        "0101"
        "10"
        "101001011010100101",
        &correct_result, 0);
    result = s21_truncate(dec);
    ck_assert_int_eq(s21_is_equal(result, correct_result), TRUE);

    // 0.710579877
    str_to_dec("101010010110101001011010100101", &dec, 9);
    // 0
    init_dec_bits(&correct_result);
    result = s21_truncate(dec);
    ck_assert_int_eq(s21_is_equal(result, correct_result), TRUE);
}

START_TEST(round_dec) {
    s21_decimal dec, correct_result, res;
    init_dec_bits(&dec), init_dec_bits(&res), init_dec_bits(&correct_result);

    // check 0 -> 0
    str_to_dec("0", &dec, 0);
    str_to_dec("0", &correct_result, 0);
    res = s21_round(dec);
    ck_assert_int_eq(s21_is_equal(res, correct_result), TRUE);
    init_dec_bits(&res);

    // check 1 -> 1
    str_to_dec("1", &dec, 0);
    str_to_dec("1", &correct_result, 0);
    res = s21_round(dec);
    ck_assert_int_eq(s21_is_equal(res, correct_result), TRUE);
    init_dec_bits(&res);

    // check 10.1 -> 10
    str_to_dec("1100101", &dec, 1);
    str_to_dec("1010", &correct_result, 0);
    res = s21_round(dec);
    ck_assert_int_eq(s21_is_equal(res, correct_result), TRUE);
    init_dec_bits(&res);

    // check -10.1 -> -10
    str_to_dec("-1100101", &dec, 1);
    str_to_dec("-1010", &correct_result, 0);
    res = s21_round(dec);
    ck_assert_int_eq(s21_is_equal(res, correct_result), TRUE);
    init_dec_bits(&res);

    //  10.6
    str_to_dec("1101010", &dec, 1);
    str_to_dec("1011", &correct_result, 0);
    res = s21_round(dec);
    ck_assert_int_eq(s21_is_equal(res, correct_result), TRUE);

    // 10.5
    str_to_dec("1101001", &dec, 1);
    str_to_dec("1010", &correct_result, 0);
    res = s21_round(dec);
    ck_assert_int_eq(s21_is_equal(res, correct_result), TRUE);

    // -10.5
    str_to_dec("-1101001", &dec, 1);
    str_to_dec("-1010", &correct_result, 0);
    res = s21_round(dec);
    ck_assert_int_eq(s21_is_equal(res, correct_result), TRUE);

    // -11.5
    str_to_dec("-1110011", &dec, 1);
    str_to_dec("-1100", &correct_result, 0);
    res = s21_round(dec);
    ck_assert_int_eq(s21_is_equal(res, correct_result), TRUE);

    // check max 7922816251426433759354395033.5 ->
    // 7922816251426433759354395034
    str_to_dec(
        "111111111111111111111111111111111111111111111111111111111111111111"
        "1111"
        "11111111111111111111111111",
        &dec, 1);
    str_to_dec(
        "110011001100110011001100110011001100110011001100110011001100110011"
        "0011"
        "00110011001100110011010",
        &correct_result, 0);
    res = s21_round(dec);
    float fl1, fl2;
    ck_assert_int_eq(s21_is_equal(res, correct_result), TRUE);
}
END_TEST

START_TEST(floor_dec) {
    s21_decimal dec, correct_result, res;
    init_dec_bits(&dec), init_dec_bits(&res), init_dec_bits(&correct_result);

    // check 0 -> 0
    str_to_dec("0", &dec, 0);
    str_to_dec("0", &correct_result, 0);
    res = s21_floor(dec);
    ck_assert_int_eq(s21_is_equal(res, correct_result), TRUE);
    init_dec_bits(&res);

    // check 1 -> 1
    str_to_dec("1", &dec, 0);
    str_to_dec("1", &correct_result, 0);
    res = s21_floor(dec);
    ck_assert_int_eq(s21_is_equal(res, correct_result), TRUE);
    init_dec_bits(&res);

    // check 10.1 -> 10
    str_to_dec("1100101", &dec, 1);
    str_to_dec("1010", &correct_result, 0);
    res = s21_floor(dec);
    ck_assert_int_eq(s21_is_equal(res, correct_result), TRUE);
    init_dec_bits(&res);

    // check 10.5 -> 10
    str_to_dec("1101001", &dec, 1);
    str_to_dec("1010", &correct_result, 0);
    res = s21_floor(dec);
    ck_assert_int_eq(s21_is_equal(res, correct_result), TRUE);

    // check -10.1 -> -11
    str_to_dec("-1100101", &dec, 1);
    str_to_dec("-1011", &correct_result, 0);
    res = s21_floor(dec);
    ck_assert_int_eq(s21_is_equal(res, correct_result), TRUE);
    init_dec_bits(&res);

    // check -10.5 -> -11
    str_to_dec("-1101001", &dec, 1);
    str_to_dec("-1011", &correct_result, 0);
    res = s21_floor(dec);
    ck_assert_int_eq(s21_is_equal(res, correct_result), TRUE);

    // check max 7922816251426433759354395033.5 ->
    // 7922816251426433759354395033
    str_to_dec(
        "111111111111111111111111111111111111111111111111111111111111111111"
        "1111"
        "11111111111111111111111111",
        &dec, 1);
    str_to_dec(
        "110011001100110011001100110011001100110011001100110011001100110011"
        "0011"
        "00110011001100110011001",
        &correct_result, 0);
    res = s21_floor(dec);
    ck_assert_int_eq(s21_is_equal(res, correct_result), TRUE);

    // check min -7922816251426433759354395033.5 ->
    // -7922816251426433759354395034
    str_to_dec(
        "-11111111111111111111111111111111111111111111111111111111111111111"
        "1111"
        "111111111111111111111111111",
        &dec, 1);
    str_to_dec(
        "-11001100110011001100110011001100110011001100110011001100110011001"
        "1001"
        "100110011001100110011010",
        &correct_result, 0);
    res = s21_floor(dec);
    ck_assert_int_eq(s21_is_equal(res, correct_result), TRUE);
}
END_TEST

START_TEST(s21_floor_test) {
    s21_decimal dec0;
    int int0;
    float flt0;
    s21_from_float_to_decimal(FLT_TEST_0, &dec0);
    dec0 = s21_floor(dec0);
    s21_from_decimal_to_float(dec0, &flt0);
    ck_assert_float_eq(flt0, floorf(FLT_TEST_0));
    s21_from_float_to_decimal(FLT_TEST_1, &dec0);
    dec0 = s21_floor(dec0);
    s21_from_decimal_to_float(dec0, &flt0);
    ck_assert_float_eq(flt0, floorf(FLT_TEST_1));
    s21_from_float_to_decimal(FLT_TEST_2, &dec0);
    dec0 = s21_floor(dec0);
    s21_from_decimal_to_float(dec0, &flt0);
    ck_assert_float_eq(flt0, floorf(FLT_TEST_2));
    s21_from_float_to_decimal(FLT_TEST_3, &dec0);
    dec0 = s21_floor(dec0);
    s21_from_decimal_to_float(dec0, &flt0);
    ck_assert_float_eq(flt0, floorf(FLT_TEST_3));

    // try floor int
}
END_TEST

START_TEST(s21_add_1) {
    s21_decimal src1, src2;
    int a = -1234;
    float b = 1.234;
    float res_our_dec = 0.0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -1232.766;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_2) {
    s21_decimal src1, src2;
    int a = -1234;
    float b = -1.234;
    float res_our_dec = 0.0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -1235.234;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_3) {
    s21_decimal src1, src2;
    int a = -46;
    float b = 0.0 / 0.0;
    float res_our_dec = 0.0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
}
END_TEST

START_TEST(s21_add_4) {
    s21_decimal src1, src2;
    float a = -1234;
    float b = -221.234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -1455.234;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq_tol(res_our_dec, res_origin, 0.01);
}
END_TEST

START_TEST(s21_add_5) {
    s21_decimal src1, src2;
    int a = -1234;
    float b = -221.234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -1455.234;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq_tol(res_our_dec, res_origin, 0.01);
}
END_TEST

START_TEST(s21_add_6) {
    s21_decimal src1, src2;
    float a = -1.0 / 0.0;
    int b = 202;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    // ck_assert_float_eq(res_od.value_type, s21_NEGATIVE_INFINITY);
    // ck_assert_int_eq(res_od.bits[3], 0);
    // ck_assert_int_eq(res_od.bits[2], 0);
    // ck_assert_int_eq(res_od.bits[1], 0);
    // ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST

START_TEST(s21_add_7) {
    s21_decimal src1, src2;
    float a = -9403;
    float b = 0.00234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -9402.99766;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq_tol(res_our_dec, res_origin, 0001);
}
END_TEST

START_TEST(s21_add_8) {
    s21_decimal src1, src2;
    int a = -9403;
    int b = 234;
    int res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    int res_origin = -9169;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_int(res_od, &res_our_dec);
    // ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_9) {
    s21_decimal src1, src2;
    float a = -940.3;
    float b = 0.000234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -940.299766;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq_tol(res_our_dec, res_origin, 0.01);
}
END_TEST

START_TEST(s21_add_10) {
    s21_decimal src1, src2;
    float a = -0.9403;
    float b = 0.000234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -0.940066;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq_tol(res_our_dec, res_origin, 0.01);
}
END_TEST

START_TEST(s21_add_11) {
    s21_decimal src1, src2;
    float a = -0.9403;
    float b = 2.0234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = 1.0831;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_12) {
    s21_decimal src1, src2;
    float a = 1.0 / 0.0;
    float b = 112.0234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    s21_decimal res_od;
    res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_od.value_type, s21_INFINITY);
    ck_assert_int_eq(res_od.bits[3], 0);
    // ck_assert_int_eq(res_od.bits[2], 0);
    // ck_assert_int_eq(res_od.bits[1], 0);
    // ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST

START_TEST(s21_add_13) {
    s21_decimal src1, src2;
    float a = -0.9403;
    float b = -112.0234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -112.9637;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_14) {
    s21_decimal src1, src2;
    float a = -0.94e03;
    float b = -112.0234;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -1052.0234;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq_tol(res_our_dec, res_origin, 0.01);
}
END_TEST

START_TEST(s21_add_15) {
    s21_decimal src1, src2;
    float a = -0.94e03;
    float b = -112.0e2;
    float res_our_dec = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    float res_origin = -12140;
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_float(res_od, &res_our_dec);
    ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_16) {
    s21_decimal src1, src2;
    int a = 9403;
    int b = 202;
    int res_origin = 9605;
    int res_our_dec = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    s21_decimal res_od = s21_add(src1, src2);
    s21_from_decimal_to_int(res_od, &res_our_dec);
    ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_17) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x300000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xF;
    src1.bits[0] = 0x67E4FEEF;
    src2.bits[3] = 0x300000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFF;
    src2.bits[0] = 0x67E4FFFF;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x300000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x10E;
    result_origin.bits[0] = 0xCFC9FEEE;
    s21_decimal result_our = s21_add(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_add_18) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x30000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFF;
    src1.bits[0] = 0x67E4F;
    src2.bits[3] = 0x60000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xEA;
    src2.bits[0] = 0x67E4F;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x60000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x3E502;
    result_origin.bits[0] = 0x1963E2E7;
    s21_decimal result_our = s21_add(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST

START_TEST(s21_add_19) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x30000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x80070000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x70000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x270FEFED;
    result_origin.bits[0] = 0x00F26FA1;
    s21_decimal result_our = s21_add(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST

START_TEST(s21_add_20) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x80030000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x80070000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x80070000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x27100FEC;
    result_origin.bits[0] = 0xFFF96C3F;
    s21_decimal result_our = s21_add(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST

START_TEST(s21_add_21) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x80030000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x70000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x80070000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x270FEFED;
    result_origin.bits[0] = 0x00F26FA1;
    s21_decimal result_our = s21_add(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST

START_TEST(add_norm) {
    s21_decimal dec1, dec2, result, correct_result;
    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);
    str_to_dec("11001010", &dec1, 0);              // 202
    str_to_dec("110011010", &dec2, 0);             // 410
    str_to_dec("1001100100", &correct_result, 0);  // 612
    result = s21_add(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);
    str_to_dec("11111111111111111111111111101011", &dec1, 0);  // 4294967275
    str_to_dec("10101001011100001", &dec2, 0);                 // 86753
    str_to_dec("100000000000000010101001011001100", &correct_result,
               0);  // 4295054028
    result = s21_add(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);
    str_to_dec("1111", &dec1, 0);                          // 15
    str_to_dec("-11000011010100000", &dec2, 0);            // 100000
    str_to_dec("-11000011010010001", &correct_result, 0);  // -99985
    result = s21_add(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);
    str_to_dec("-11111111111111111111111111101011", &dec1,
               0);                               // 4294967275
    str_to_dec("-10101001011100001", &dec2, 0);  // 86753
    str_to_dec("-100000000000000010101001011001100", &correct_result,
               0);  // 4295054028
    result = s21_add(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);
    // 123757,6213581
    str_to_dec("10010000000100101010010100110010001001101", &dec1, 7);
    // 0,0000020
    str_to_dec("10100", &dec2, 7);
    // 123757,6213601
    str_to_dec("10010000000100101010010100110010001100001", &correct_result, 7);
    result = s21_add(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);
    // 123757,6213581
    str_to_dec("10010000000100101010010100110010001001101", &dec1, 7);
    // 1,7
    str_to_dec("10001", &dec2, 1);
    // 123759.3213581
    str_to_dec("10010000000100110010011011100101010001101", &correct_result, 7);
    result = s21_add(dec1, dec2);

    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);
    // -123757,6213581
    str_to_dec("-10010000000100101010010100110010001001101", &dec1, 7);
    // -1,7
    str_to_dec("-10001", &dec2, 1);
    // -123759,3213581
    str_to_dec("-10010000000100110010011011100101010001101", &correct_result,
               7);

    result = s21_add(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);
    // 0.0000000000000000000000000001
    str_to_dec("1", &dec1, 28);
    //  1
    str_to_dec("1", &dec2, 0);
    // 1.0000000000000000000000000001
    str_to_dec(
        "100000010011111100111001011110001111100010010100000010011000010001"
        "0000"
        "000000000000000000000001",
        &correct_result, 28);
    result = s21_add(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);
    // 0.0000000000000000000000000001
    str_to_dec("1", &dec1, 28);
    //  1
    str_to_dec("1", &dec2, 0);
    // 1.0000000000000000000000000001
    str_to_dec(
        "100000010011111100111001011110001111100010010100000010011000010001"
        "0000"
        "000000000000000000000001",
        &correct_result, 28);
    result = s21_add(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);
    // 1.23456789123456789
    str_to_dec("110110110100110110100101110101100110100000101111100010101",
               &dec1, 17);
    //  12345678912345678.9
    str_to_dec("110110110100110110100101110101100110100000101111100010101",
               &dec2, 1);
    // 12345678912345680.134567891235
    str_to_dec(
        "100111111001000001101100110010111000001111000101100011011010010000"
        "0011"
        "11"
        "0101000001000100100010",
        &correct_result, 12);
    result = s21_add(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    // #1
    // 112286.36363636363636363
    str_to_dec(
        "1001100000101101001010001000000000110111001011001101011"
        "1100010111010001011",
        &dec1, 17);
    // 4.16787847
    str_to_dec("11000110101111010110110000111", &dec2, 8);

    result = s21_add(dec1, dec2);

    // 112290.53151483363636363
    str_to_dec(
        "100110000010111010011010101011101100110011011000101000000010110100"
        "1000"
        "10"
        "11",
        &correct_result, 17);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #2
    // 135521
    str_to_dec("100001000101100001", &dec1, 0);
    // 3724292940501892409235
    str_to_dec(
        "11001001111001001111001001111001001111001001111001"
        "0011110010011110010011",
        &dec2, 0);

    result = s21_add(dec1, dec2);

    // 3724292940501892544756
    str_to_dec(
        "110010011110010011110010011110010011110010011110010100010011100011"
        "1101"
        "0"
        "0",
        &correct_result, 0);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #3
    // 0.0135521
    str_to_dec("100001000101100001", &dec1, 7);
    // 0.0000003724292940501892409235
    str_to_dec(
        "1100100111100100111100100111100100111100100111"
        "10010011110010011110010011",
        &dec2, 28);

    result = s21_add(dec1, dec2);

    // 0.013 55247 24292 94050 18924 09235
    str_to_dec(
        "111000000011010011110100000011001110011001100100011111010011000111"
        "0111"
        "10"
        "010011110010011",
        &correct_result, 28);
    // print_dec(result);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #4
    // 24560730379421944653998624.602
    str_to_dec(
        "100111101011100001010001111010111000010100011110101110"
        "00010100011110101110000101000111101011010",
        &dec1, 3);
    // 31.7
    str_to_dec("100111101", &dec2, 1);

    result = s21_add(dec1, dec2);

    // 24560730379421944653998656.302
    str_to_dec(
        "100111101011100001010001111010111000010100011110101110000101000111"
        "1010"
        "11"
        "10000110000101100101110",
        &correct_result, 3);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #5
    // 0.0000000000000000009
    str_to_dec("1001", &dec1, 19);
    // 0,000000000000000000000009
    str_to_dec("1001", &dec2, 24);

    result = s21_add(dec1, dec2);

    // 0.0000 00000 00000 00009 00009
    str_to_dec("11011011101110101001", &correct_result, 24);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #6
    // 0,0000000000000000000000095642
    str_to_dec("10111010110011010", &dec1, 28);
    // 0,0000000000000000000000112
    str_to_dec("1110000", &dec2, 25);

    result = s21_add(dec1, dec2);

    // 0.000 00000 00000 00000 00002 07642
    str_to_dec("110010101100011010", &correct_result, 28);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #7
    // 0,0000000000000000000000095642
    str_to_dec("10111010110011010", &dec1, 28);
    // 112000
    str_to_dec("11011010110000000", &dec2, 0);

    result = s21_add(dec1, dec2);

    // 112000.000 00000 00000 00000 00001
    str_to_dec(
        "100100001100000110110001000000100101111000010110011100010000111100"
        "0000"
        "00"
        "0000000000000000000000",
        &correct_result, 23);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #8
    // 0,0000000000000000000000095642
    str_to_dec("10111010110011010", &dec1, 28);
    // 0.0000000000000000000000000002
    str_to_dec("10", &dec2, 28);

    result = s21_add(dec1, dec2);

    // 0.0000000000000000000000095644
    str_to_dec("10111010110011100", &correct_result, 28);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #9
    // 0,0000000000000000000000095642
    str_to_dec("10111010110011010", &dec1, 28);
    // 0.8539464285714285714285714286
    str_to_dec(
        "1101110010111101011011110011010000101100011010111110111"
        "11000010110011011101101101101101101110",
        &dec2, 28);

    result = s21_add(dec1, dec2);

    // 0.8539464285714285714285809928
    str_to_dec(
        "110111001011110101101111001101000010110001101011111011111000010110"
        "0110"
        "11"
        "110000101000100001000",
        &correct_result, 28);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #10
    // 24560730379421944653998624.602
    str_to_dec(
        "100111101011100001010001111010111000010100011110101110000101000111"
        "1010"
        "11"
        "10000101000111101011010",
        &dec1, 3);
    // 792281625142643375935439.50329
    str_to_dec(
        "111111111111111111111111111111111111111111111111111111111111111111"
        "1111"
        "11"
        "111111111111111111111001",
        &dec2, 5);

    result = s21_add(dec1, dec2);

    // C #        25353012004564588029934064.105
    // full prec 25353012004564588029934064.10529
    // res       25353012004564588029934064.106
    str_to_dec(
        "101000111101011100001010001111010111000010100011110101110000101000"
        "1111"
        "01"
        "01110000101000111101001",
        &correct_result, 3);
    // ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);
}
END_TEST

START_TEST(special_values) {
    s21_decimal dec1, dec2, result, correct_result;
    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);

    dec1.value_type = s21_INFINITY;
    // 135521
    str_to_dec("11111111111111111111111111111111", &dec2, 0);

    result = s21_add(dec1, dec2);
    ck_assert_int_eq(result.value_type, s21_INFINITY);
    init_dec_bits(&result);

    dec1.value_type = s21_NEGATIVE_INFINITY;
    // 135521
    str_to_dec("11111111111111111111111111111111", &dec2, 0);
    correct_result.value_type = 2;
    result = s21_add(dec1, dec2);
    ck_assert_int_eq(result.value_type, s21_NEGATIVE_INFINITY);
}
END_TEST

START_TEST(s21_sub_9) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0b00000000000000010000000000000000;
    src1.bits[2] = 0;
    src1.bits[1] = 0;
    src1.bits[0] = 0b00000000000000000110011011110000;
    src2.bits[3] = 0b00000000000000110000000000000000;
    src2.bits[2] = 0;
    src2.bits[1] = 0;
    src2.bits[0] = 0b00000000000001000101000111010110;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0b00000000000000110000000000000000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0;
    result_origin.bits[0] = 0b00000000001000111110001111101010;
    s21_decimal result_our = s21_sub(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_sub_10) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0b00000000000000110000000000000000;
    src1.bits[2] = 0;
    src1.bits[1] = 0;
    src1.bits[0] = 0b00000000000001000101000111010110;
    src2.bits[3] = 0b00000000000000010000000000000000;
    src2.bits[2] = 0;
    src2.bits[1] = 0;
    src2.bits[0] = 0b00000000000000000000101110111100;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0b10000000000000110000000000000000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0;
    result_origin.bits[0] = 0b00000000000000000100001110011010;
    s21_decimal result_our = s21_sub(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_sub_11) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x80030000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x80070000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x80070000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x270FEFED;
    result_origin.bits[0] = 0x00F26FA1;
    s21_decimal result_our = s21_sub(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_sub_12) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x30000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x80070000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x70000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x27100FEC;
    result_origin.bits[0] = 0xFFF96C3F;
    s21_decimal result_our = s21_sub(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_sub_13) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0b10000000000000010000000000000000;
    src1.bits[2] = 0;
    src1.bits[1] = 0;
    src1.bits[0] = 0b00000000000000000000000100110000;
    src2.bits[3] = 0b10000000000001100000000000000000;
    src2.bits[2] = 0;
    src2.bits[1] = 0;
    src2.bits[0] = 0b00010001001000010001101001100000;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0b00000000000001100000000000000000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0;
    result_origin.bits[0] = 0b00001111010100010011110001100000;
    s21_decimal result_our = s21_sub(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_sub_14) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[3] = 0x80030000;
    src1.bits[2] = 0;
    src1.bits[1] = 0xFFFF;
    src1.bits[0] = 0xFF837E4F;
    src2.bits[3] = 0x70000;
    src2.bits[2] = 0;
    src2.bits[1] = 0xFFF;
    src2.bits[0] = 0xFF837E4F;
    s21_decimal result_origin;
    result_origin.value_type = s21_NORMAL_VALUE;
    result_origin.bits[3] = 0x80070000;
    result_origin.bits[2] = 0;
    result_origin.bits[1] = 0x27100FEC;
    result_origin.bits[0] = 0xFFF96C3F;
    s21_decimal result_our = s21_sub(src1, src2);
    ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_sub_15) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b00000000000000000000011111100100;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b00000000000000000000000000000000;
    src2.bits[0] = 0b00000101100110111101101000011001;
    src2.bits[1] = 0b00000000000000000000000000000000;
    src2.bits[2] = 0b00000000000000000000000000000000;
    src2.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal result, result_our;
    result_our = s21_sub(src2, src1);
    result.value_type = s21_NORMAL_VALUE;
    result.bits[0] = 0b00000101100110111101001000110101;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    ck_assert_int_eq(result.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_sub_16) {
    s21_decimal src1, src2;
    src1.value_type = src2.value_type = s21_NORMAL_VALUE;
    src1.bits[0] = 0b00000000000000000000011111100100;
    src1.bits[1] = 0b00000000000000000000000000000000;
    src1.bits[2] = 0b00000000000000000000000000000000;
    src1.bits[3] = 0b10000000000000000000000000000000;
    src2.bits[0] = 0b00000000000000000010010010111011;
    src2.bits[1] = 0b00000000000000000000000000000000;
    src2.bits[2] = 0b00000000000000000000000000000000;
    src2.bits[3] = 0b10000000000000000000000000000000;
    s21_decimal result, result_our;
    result_our = s21_sub(src2, src1);
    result.value_type = s21_NORMAL_VALUE;
    result.bits[0] = 0b00000000000000000001110011010111;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b10000000000000000000000000000000;
    ck_assert_int_eq(result.bits[3], result_our.bits[3]);
    ck_assert_int_eq(result.bits[2], result_our.bits[2]);
    ck_assert_int_eq(result.bits[1], result_our.bits[1]);
    ck_assert_int_eq(result.bits[0], result_our.bits[0]);
}
END_TEST

START_TEST(sub_normal_test_integer) {
    s21_decimal dec1, dec2, result, correct_result;
    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);
    str_to_dec("11001010", &dec1, 0);
    str_to_dec("11001010", &dec2, 0);
    result = s21_sub(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    str_to_dec("11000011010100000", &dec1, 0);            // 100000
    str_to_dec("1111", &dec2, 0);                         // 15
    str_to_dec("11000011010010001", &correct_result, 0);  // 99985
    result = s21_sub(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    str_to_dec("1111", &dec1, 0);                          // 15
    str_to_dec("11000011010100000", &dec2, 0);             // 100000
    str_to_dec("-11000011010010001", &correct_result, 0);  // -99985
    result = s21_sub(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    // 1237576213581
    str_to_dec("10010000000100101010010100110010001001101", &dec1, 0);
    // 1
    str_to_dec("1", &dec2, 0);
    // 1237576213580
    str_to_dec("10010000000100101010010100110010001001100", &correct_result, 0);
    result = s21_sub(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    str_to_dec("-1111", &dec1, 0);                        // -15
    str_to_dec("-11000011010100000", &dec2, 0);           // -100000
    str_to_dec("11000011010010001", &correct_result, 0);  // 99985
    result = s21_sub(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    // -0.2
    str_to_dec("-10", &dec1, 1);
    // -0.0000001
    str_to_dec("-1", &dec2, 7);
    // -0.1999999
    str_to_dec("-111101000010001111111", &correct_result, 7);
    result = s21_sub(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    str_to_dec("11010000000100101010010100110010001001101", &dec1, 0);
    // 1
    str_to_dec("1010000000100101010010100110010001001100", &dec2, 0);
    // 1237576213580
    str_to_dec("10000000000000000000000000000000000000001", &correct_result, 0);
    result = s21_sub(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);
    // 49155195229197460557
    str_to_dec(
        "10101010100010101001010101101000000010010101001010011001000100110"
        "1",
        &dec1, 0);
    // 687820399692
    str_to_dec("1010000000100101010010100110010001001100", &dec2, 0);
    // 49155194541377060865
    str_to_dec(
        "10101010100010101001010101000000000000000000000000000000000000000"
        "1",
        &correct_result, 0);
    result = s21_sub(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    str_to_dec("101010100101010101111010101001010", &dec1, 0);
    // 1
    str_to_dec("11001000000000000000000000000000", &dec2, 0);
    // 1237576213580
    str_to_dec("10001100101010101111010101001010", &correct_result, 0);
    result = s21_sub(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);
}
END_TEST

START_TEST(sub_uncommon_values) {
    s21_decimal dec1, dec2, result, correct_result;
    // 79228162514264337593543950330 - 49517601571415210995964968960
    str_to_dec(
        "111111111111111111111111111111111111111111111111111111111111111111"
        "1111"
        "11"
        "111111111111111111111010",
        &dec1, 0);
    str_to_dec(
        "101000000000000000000000000000000000000000000000000000000000000000"
        "0000"
        "00"
        "000000000000000000000000",
        &dec2, 0);
    init_dec_bits(&result);
    result = s21_sub(dec1, dec2);
    // 29710560942849126597578981370
    str_to_dec(
        "101111111111111111111111111111111111111111111111111111111111111111"
        "1111"
        "11"
        "11111111111111111111010",
        &correct_result, 0);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);
}

START_TEST(div_common_values) {
    s21_decimal dec1, dec2, result, correct_result;
    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);

    str_to_dec("11001010", &dec1, 0);
    str_to_dec("11001010", &dec2, 0);
    result = s21_div(dec1, dec2);
    str_to_dec("1", &correct_result, 0);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    // 4
    str_to_dec("100", &dec1, 0);
    // 3
    str_to_dec("11", &dec2, 0);
    result = s21_div(dec1, dec2);
    // 1.3333333333333333333333333333
    str_to_dec(
        "1010110001010100010011001010000101001011011100000000110010110000010101"
        "01"
        "0101010101010101010101",
        &correct_result, 28);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);
}
END_TEST

START_TEST(mod_common_values) {
    s21_decimal dec1, dec2, result, correct_result;
    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);

    // 202
    str_to_dec("11001010", &dec1, 0);
    // 202
    str_to_dec("11001010", &dec2, 0);
    // 0
    init_dec_bits(&result);
    result = s21_mod(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);
    // 203
    str_to_dec("11001011", &dec1, 0);
    // 202
    str_to_dec("11001010", &dec2, 0);
    // 1
    str_to_dec("1", &correct_result, 0);
    result = s21_mod(dec1, dec2);

    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    // 403

    str_to_dec("110010011", &dec1, 0);

    // 202
    str_to_dec("11001010", &dec2, 0);
    // 201
    str_to_dec("11001001", &correct_result, 0);
    result = s21_mod(dec1, dec2);

    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    // 54195595155
    str_to_dec("110010011110010011110010011110010011", &dec1, 0);
    // 10
    str_to_dec("1010", &dec2, 0);
    // 5
    str_to_dec("101", &correct_result, 0);
    result = s21_mod(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    // 54195595155
    str_to_dec("110010011110010011110010011110010011", &dec1, 0);
    // 1000
    str_to_dec("1111101000", &dec2, 0);
    // 155
    str_to_dec("10011011", &correct_result, 0);
    result = s21_mod(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    // 3724292940501892409235
    str_to_dec(
        "1100100111100100111100100111100100111100100111100100111100100111100100"
        "1"
        "1",
        &dec1, 0);
    // 135521
    str_to_dec("100001000101100001", &dec2, 0);
    // 100360
    str_to_dec("11000100000001000", &correct_result, 0);
    result = s21_mod(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    // 3905204194379712334906604703
    str_to_dec(
        "1100100111100100111100100111100100111100100111100100111100100111100100"
        "11"
        "10010011110010011111",
        &dec1, 0);
    // 135521
    str_to_dec("100001000101100001", &dec2, 0);
    // 112657
    str_to_dec("11011100000010001", &correct_result, 0);
    result = s21_mod(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);
}
END_TEST

START_TEST(mod_uncommon_values) {
    s21_decimal dec1, dec2, result, correct_result;
    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);

    // 3905204194379712334906604703
    str_to_dec("111111111111111111111111111111111", &dec1, 0);
    // 135521
    str_to_dec("11111111111111111111111111111111", &dec2, 0);
    // 112657
    str_to_dec("1", &correct_result, 0);
    result = s21_mod(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    // 792281625
    str_to_dec("101111001110010100001000011001", &dec1, 0);
    // 4.951760157141521
    str_to_dec("10001100101111001100110000001001011011110101000010001", &dec2,
               15);
    result = s21_mod(dec1, dec2);
    // 4.809116797141521
    str_to_dec("10001000101011101110111000010011000001000001000010001",
               &correct_result, 15);

    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // 54375684.5645934765284
    str_to_dec(
        "111010111101000100100011000100010101011110000110110100010010011100100",
        &dec1, 13);
    // 4.951760157141521
    str_to_dec("10001100101111001100110000001001011011110101000010001", &dec2,
               15);
    result = s21_mod(dec1, dec2);

    // 0.2346895488226780
    // 0.234689548822678

    str_to_dec("110101010111001011101011001100001010100010010110",
               &correct_result, 15);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // 54375684.5645934765284
    str_to_dec(
        "111010111101000100100011000100010101011110000110110100010010011100100",
        &dec1, 13);
    // 11.9888888888888888
    str_to_dec("110101001111011100100111100101010101111010000111000111000",
               &dec2, 16);
    result = s21_mod(dec1, dec2);
    // 7.0757045880426672
    str_to_dec("11111011011000010010100010001001000011110001000010110000",
               &correct_result, 16);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // 99999.99999999999999999999999
    str_to_dec(
        "1000000100111111001110010111100011111000100101000"
        "000100110000100001111111111111111111111111111",
        &dec1, 23);
    // 0,000000000000000000000009
    str_to_dec("1001", &dec2, 24);
    result = s21_mod(dec1, dec2);

    // 0.000000000000000000000000
    init_dec_bits(&correct_result);
    //   correct_result.value_type = s21_INFINITY;
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // 99999,99999999999999999999999
    str_to_dec(
        "1000000100111111001110010111100011111000100101000"
        "000100110000100001111111111111111111111111111",
        &dec1, 23);
    // 0,02
    str_to_dec("10", &dec2, 2);
    result = s21_mod(dec1, dec2);
    // 0.01999999999999999999999

    str_to_dec(
        "1101100011010111001001101011011100010111011110100111111111111111111111"
        "1",
        &correct_result, 23);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // 99999,99999999999999999999999
    str_to_dec("1001", &dec1, 23);
    // 0,02
    str_to_dec("10", &dec2, 2);
    result = s21_mod(dec1, dec2);
    // 0.01999999999999999999999

    str_to_dec("1001", &correct_result, 23);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #1
    // 112286.36363636363636363
    str_to_dec(
        "1001100000101101001010001000000000110111001011001101011"
        "1100010111010001011",
        &dec1, 17);
    // 4.16787847
    str_to_dec("11000110101111010110110000111", &dec2, 8);

    result = s21_mod(dec1, dec2);

    // 3.71765456363636363
    str_to_dec("10100101000110001101011011001111110010100001100011010001011",
               &correct_result, 17);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #2
    // 3724292940501892409235
    str_to_dec(
        "11001001111001001111001001111001001111001001111001"
        "0011110010011110010011",
        &dec1, 0);
    // 135521
    str_to_dec("100001000101100001", &dec2, 0);

    result = s21_mod(dec1, dec2);

    // 100360
    str_to_dec("11000100000001000", &correct_result, 0);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #3
    // 0.0135521
    str_to_dec("100001000101100001", &dec1, 7);
    // 0.0000003724292940501892409235
    str_to_dec(
        "1100100111100100111100100111100100111100100111"
        "10010011110010011110010011",
        &dec2, 28);

    result = s21_mod(dec1, dec2);

    // 0.0000001428481017139012756820
    str_to_dec(
        "1001101011100000010100000001100101010111100111110001010111001010101010"
        "0",
        &correct_result, 28);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #4
    // 24560730379421944653998624.602
    str_to_dec(
        "100111101011100001010001111010111000010100011110101110"
        "00010100011110101110000101000111101011010",
        &dec1, 3);
    // 31.7
    str_to_dec("100111101", &dec2, 1);

    result = s21_mod(dec1, dec2);

    // 9.402
    str_to_dec("10010010111010", &correct_result, 3);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #5
    // 0.0000000000000000009
    str_to_dec("1001", &dec1, 19);
    // 0,000000000000000000000009
    str_to_dec("1001", &dec2, 24);

    result = s21_mod(dec1, dec2);

    // 0
    str_to_dec("0", &correct_result, 0);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #6
    // 0,0000000000000000000000095642
    str_to_dec("10111010110011010", &dec1, 28);
    // 0,0000000000000000000000112
    str_to_dec("1110000", &dec2, 25);

    result = s21_mod(dec1, dec2);

    // 0,0000000000000000000000095642
    str_to_dec("10111010110011010", &correct_result, 28);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #9
    // 0,0000000000000000000000095642
    str_to_dec("10111010110011010", &dec1, 28);
    // 0.0000000000000000000000000002
    str_to_dec("10", &dec2, 28);

    result = s21_mod(dec1, dec2);

    // 0
    str_to_dec("0", &correct_result, 0);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #10
    // 0.8539464285714285714285714286
    str_to_dec(
        "1101110010111101011011110011010000101100011010111110111"
        "11000010110011011101101101101101101110",
        &dec1, 28);
    // 0,0000000000000000000000095642
    str_to_dec("10111010110011010", &dec2, 28);

    result = s21_mod(dec1, dec2);

    // 0.0000000000000000000000068316
    str_to_dec("10000101011011100", &correct_result, 28);
    // print_dec(result);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);
}
END_TEST

START_TEST(s21_mod_1) {
    s21_decimal src1, src2, res_mod;
    int a = 3;
    int b = 2;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    res_mod = s21_mod(src1, src2);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
}
END_TEST
START_TEST(s21_mod_2) {
    s21_decimal src1, src2, res_mod;
    int a = -98765;
    int b = 1234;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    res_mod = s21_mod(src1, src2);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
}
END_TEST
START_TEST(s21_mod_3) {
    s21_decimal src1, src2, res_mod;
    int a = 30198;
    int b = 20210;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    res_mod = s21_mod(src1, src2);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
}
END_TEST
START_TEST(s21_mod_4) {
    s21_decimal src1, src2, res_mod;
    int a = -98765;
    int b = -1234;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    res_mod = s21_mod(src1, src2);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
}
END_TEST
START_TEST(s21_mod_5) {
    s21_decimal src1, src2, res_mod;
    int a = 98765;
    int b = 127234;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    res_mod = s21_mod(src1, src2);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
}
END_TEST
START_TEST(s21_mod_6) {
    s21_decimal src1, src2, res_mod;
    int a = 342576;
    int b = 1542134;
    int res_origin = a % b;
    int res = 0;
    s21_from_int_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    res_mod = s21_mod(src1, src2);
    s21_from_decimal_to_int(res_mod, &res);
    ck_assert_int_eq(res_origin, res);
}
END_TEST
START_TEST(s21_mod_7) {
    s21_decimal src1, src2, res_mod;
    float a = 1.2;
    float b = 0.3;
    float res_origin = fmod(a, b);
    float res = 0.0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_float_to_decimal(b, &src2);
    res_mod = s21_mod(src1, src2);
    s21_from_decimal_to_float(res_mod, &res);
    ck_assert_float_eq(res_origin, res);
}
END_TEST
START_TEST(s21_mod_8) {
    s21_decimal src1, src2, res_mod;
    float a = 1.2;
    int b = 3;
    float res_origin = fmod(a, b);
    float res = 0;
    s21_from_float_to_decimal(a, &src1);
    s21_from_int_to_decimal(b, &src2);
    res_mod = s21_mod(src1, src2);
    s21_from_decimal_to_float(res_mod, &res);
    ck_assert_float_eq(res_origin, res);
}
END_TEST

START_TEST(mul) {
    s21_decimal res_dec, dec1, dec2, correct_result;
    init_dec_bits(&res_dec), init_dec_bits(&dec1), init_dec_bits(&dec2),
        init_dec_bits(&correct_result);
    // check NaN1
    str_to_dec("1", &dec1, 0), dec1.value_type = s21_NAN;
    str_to_dec("1", &dec2, 1);
    res_dec = s21_mul(dec1, dec2);
    correct_result.value_type = s21_NAN;
    ck_assert_int_eq(res_dec.value_type, correct_result.value_type);
    init_dec_bits(&res_dec), init_dec_bits(&dec1), init_dec_bits(&dec2),
        init_dec_bits(&correct_result);
    // check NaN2
    // 1e-28 * 0.1
    str_to_dec("1", &dec1, 0);
    str_to_dec("1", &dec2, 1), dec2.value_type = s21_NAN;
    res_dec = s21_mul(dec1, dec2);
    correct_result.value_type = s21_NAN;
    ck_assert_int_eq(res_dec.value_type, correct_result.value_type);
    init_dec_bits(&res_dec), init_dec_bits(&dec1), init_dec_bits(&dec2),
        init_dec_bits(&correct_result);
    // check infinity
    // 11228636363636363636363636363 * 10
    str_to_dec(
        "1001000100100000011100001111001111100110100111100111111110111111011001"
        "10"
        "1110100010111010001011",
        &dec1, 0);
    // 10
    str_to_dec("1010", &dec2, 0);
    res_dec = s21_mul(dec1, dec2);
    correct_result.value_type = s21_INFINITY;
    ck_assert_int_eq(res_dec.value_type, correct_result.value_type);
    init_dec_bits(&res_dec), init_dec_bits(&dec1), init_dec_bits(&dec2),
        init_dec_bits(&correct_result);
    // check negative infinity
    // 11228636363636363636363636363 * -10
    str_to_dec(
        "1001000100100000011100001111001111100110100111100111111110111111011001"
        "10"
        "1110100010111010001011",
        &dec1, 0);
    // 10
    str_to_dec("-1010", &dec2, 0);
    res_dec = s21_mul(dec1, dec2);
    correct_result.value_type = s21_NEGATIVE_INFINITY;
    ck_assert_int_eq(res_dec.value_type, correct_result.value_type);
    init_dec_bits(&res_dec), init_dec_bits(&dec1), init_dec_bits(&dec2),
        init_dec_bits(&correct_result);
    // check beyond factor scale
    // 1e-28 * 0.1
    str_to_dec("1", &dec1, 28);
    str_to_dec("1", &dec2, 1);
    res_dec = s21_mul(dec1, dec2);
    correct_result.value_type = s21_NORMAL_VALUE;
    ck_assert_int_eq(res_dec.value_type, correct_result.value_type);
    ck_assert_int_eq(s21_is_equal(res_dec, correct_result), 0);

    init_dec_bits(&res_dec), init_dec_bits(&dec1), init_dec_bits(&dec2),
        init_dec_bits(&correct_result);
    // check 1 * 1
    str_to_dec("1", &dec1, 0);
    str_to_dec("1", &dec2, 0);
    str_to_dec("1", &correct_result, 0);
    res_dec = s21_mul(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, res_dec), 0);
    init_dec_bits(&res_dec), init_dec_bits(&dec1), init_dec_bits(&dec2),
        init_dec_bits(&correct_result);
    // check 15845632502852867518708790067 * 5
    str_to_dec(
        "1100110011001100110011001100110011001100110011001100110011001100110011"
        "001100110011001100110011",
        &dec1, 0);
    str_to_dec("101", &dec2, 0);
    str_to_dec(
        "1111111111111111111111111111111111111111111111111111111111111111111111"
        "11111111111111111111111111",
        &correct_result, 0);
    res_dec = s21_mul(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, res_dec), 0);
    init_dec_bits(&res_dec), init_dec_bits(&dec1), init_dec_bits(&dec2),
        init_dec_bits(&correct_result);
}
END_TEST

START_TEST(mul_2) {
    s21_decimal dec1, dec2, result, correct_result;
    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);

    str_to_dec("11001010", &dec1, 0);  // 202
    str_to_dec("11001010", &dec2, 0);
    result = s21_mul(dec1, dec2);
    //          1001111101100100
    str_to_dec("1001111101100100", &correct_result, 0);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);
    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);

    // FAIL
    //  4
    str_to_dec("100", &dec1, 0);
    // 125
    str_to_dec("1111101", &dec2, 0);
    result = s21_mul(dec1, dec2);
    // 500
    str_to_dec("111110100", &correct_result, 0);

    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    // 123515
    str_to_dec("11110001001111011", &dec1, 0);
    // 11
    str_to_dec("1011", &dec2, 0);
    result = s21_mul(dec1, dec2);
    // 1358665
    str_to_dec("101001011101101001001", &correct_result, 0);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);
}
END_TEST

START_TEST(mul_3) {
    s21_decimal dec1, dec2, result, correct_result;
    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);

    // 6796283919
    str_to_dec("110010101000101110001000000001111", &dec1, 0);
    // 202
    str_to_dec("11001010", &dec2, 0);
    // 1372849351638
    str_to_dec("10011111110100100001100101010101111010110", &correct_result, 0);
    result = s21_mul(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);
    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);

    // 6796283919
    str_to_dec("110010101000101110001000000001111", &dec1, 6);
    // 202
    str_to_dec("11001010", &dec2, 0);
    // 1372849351638
    str_to_dec("10011111110100100001100101010101111010110", &correct_result, 6);
    result = s21_mul(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);
    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);

    // 6796.283919
    str_to_dec("110010101000101110001000000001111", &dec1, 6);
    // 2.02
    str_to_dec("11001010", &dec2, 2);
    // 13728.49351638
    str_to_dec("10011111110100100001100101010101111010110", &correct_result, 8);
    result = s21_mul(dec1, dec2);

    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    // -54195595155
    str_to_dec("-110010011110010011110010011110010011", &dec1, 0);
    // 10
    str_to_dec("1010", &dec2, 0);
    // -541955951550
    str_to_dec("-111111000101111000101111000101110111110", &correct_result, 0);
    result = s21_mul(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);

    // -3724292940501892409235
    str_to_dec(
        "-110010011110010011110010011110010011110010011110010011110010011110010"
        "01"
        "1",
        &dec1, 0);
    // -135521
    str_to_dec("-100001000101100001", &dec2, 0);
    // 504719903589756961191936435
    str_to_dec(
        "1101000010111111010011000110011000110011000110011000110011000110011000"
        "1001100000110110011",
        &correct_result, 0);
    result = s21_mul(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 0);
}
END_TEST

START_TEST(mul_4) {
    s21_decimal dec1, dec2, result, correct_result;
    init_dec_bits(&correct_result);
    init_dec_bits(&result);
    init_dec_bits(&dec1);
    init_dec_bits(&dec2);

    dec1.value_type = 1;
    // 135521
    str_to_dec("11111111111111111111111111111111", &dec2, 0);
    correct_result.value_type = 1;
    result = s21_mul(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 1);

    dec1.value_type = 2;
    // 135521
    str_to_dec("11111111111111111111111111111111", &dec2, 0);
    correct_result.value_type = 2;
    result = s21_mul(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 1);

    dec1.value_type = 1;
    // 135521
    str_to_dec("-11111111111111111111111111111111", &dec2, 0);
    correct_result.value_type = 2;
    result = s21_mul(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), 1);
}
END_TEST

START_TEST(mul_uncommon_values) {
    s21_decimal dec1, dec2, result, correct_result;
    init_dec_bits(&correct_result);
    // 11228.636363636363636363
    str_to_dec(
        "1001000100100000011100001111001111100110100111100111111110111111011001"
        "10"
        "1110100010111010001011",
        &dec1, 24);
    // 0.1
    str_to_dec("1010", &dec2, 0);
    result = s21_mul(dec1, dec2);
    // 112286.36363636363636363
    str_to_dec(
        "1001000100100000011100001111001111100110100111100111111110111111011001"
        "10"
        "1110100010111010001011",
        &correct_result, 23);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);
    str_to_dec("1", &dec1, 0);
    str_to_dec("11", &dec2, 0);
    // 0.3333333333333333333333333333
    dec1 = s21_div(dec1, dec2);
    str_to_dec("1010", &dec2, 0);
    result = s21_mul(dec1, dec2);
    // 3.3333333333333333333333333330
    // 3.3333333333333333333333333330
    str_to_dec(
        "1101011101101001010111111100100110011110010011000000111111011100011010"
        "1010101010101010101010010",
        &correct_result, 28);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    init_dec_bits(&correct_result);
    // 792281625142643375935439.5033
    str_to_dec(
        "1100110011001100110011001100110011001100110011001100110011001100110011"
        "00110011001100110011001",
        &dec1, 4);
    // 31
    str_to_dec("11111", &dec2, 0);
    // 24560730379421944653998624.602
    result = s21_mul(dec1, dec2);
    str_to_dec(
        "1001111010111000010100011110101110000101000111101011100001010001111010"
        "1110000101000111101011010",
        &correct_result, 3);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    init_dec_bits(&correct_result);
    // -79228162514264337593543.95033
    str_to_dec(
        "-110011001100110011001100110011001100110011001100110011001100110011001"
        "10"
        "0110011001100110011001",
        &dec1, 5);
    // 3.1
    str_to_dec("11111", &dec2, 1);
    result = s21_mul(dec1, dec2);

    // rounded C # -245607303794219446539986.24602
    str_to_dec(
        "-100111101011100001010001111010111000010100011110101110000101000111101"
        "01110000101000111101011010",
        &correct_result, 5);

    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    init_dec_bits(&correct_result);
    // -79228162514264337593543950.33
    str_to_dec(
        "1100110011001100110011001100110011001100110011001100110011001100110011"
        "0"
        "0110011001100110011001",
        &dec1, 2);
    // 31
    str_to_dec("11111", &dec2, 1);
    result = s21_mul(dec1, dec2);
    str_to_dec(
        "1001111010111000010100011110101110000101000111101011100001010001111010"
        "1110000101000111101011010",
        &correct_result, 2);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // 79228162514264337.593543950335
    str_to_dec(
        "1111111111111111111111111111111111111111111111111111111111111111111111"
        "11111111111111111111111111",
        &dec1, 12);
    // 123.12345
    str_to_dec("101110111101111100011001", &dec2, 5);
    result = s21_mul(dec1, dec2);
    str_to_dec(
        "1111110000101000001001011011100011110111001011001111001010100111010100"
        "01"
        "111010010000000011100",
        &correct_result, 9);

    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // 792281625
    str_to_dec("101111001110010100001000011001", &dec1, 0);
    // 4.951760157141521
    str_to_dec("10001100101111001100110000001001011011110101000010001", &dec2,
               15);
    result = s21_mul(dec1, dec2);
    // 3923188583.910339612851625
    str_to_dec(
        "1100111110110001000111101010110010100100100111110110110000100111010011"
        "110110101001",
        &correct_result, 15);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // 54375684.5645934765284
    str_to_dec(
        "111010111101000100100011000100010101011110000110110100010010011100100",
        &dec1, 13);
    // 4.951760157141521
    str_to_dec("10001100101111001100110000001001011011110101000010001", &dec2,
               15);
    result = s21_mul(dec1, dec2);
    // 269255348.34424917123071163235
    str_to_dec(
        "1010111000000000100011111001000001001000001000011001000101100110100011"
        "0001010110011101101100011",
        &correct_result, 20);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // 54375684.5645934765284
    str_to_dec(
        "111010111101000100100011000100010101011110000110110100010010011100100",
        &dec1, 13);
    // 11.9888888888888888
    str_to_dec("110101001111011100100111100101010101111010000111000111000",
               &dec2, 16);
    result = s21_mul(dec1, dec2);
    // 651904040.50218178599042359426
    str_to_dec(
        "1101001010100100001111010000010011010010100111011011001101110110000100"
        "01100010110010000010000010",
        &correct_result, 20);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // 99999,99999999999999999999999
    str_to_dec(
        "1000000100111111001110010111100011111000100101000"
        "000100110000100001111111111111111111111111111",
        &dec1, 23);
    // 0,000000000000000000000009
    str_to_dec("1001", &dec2, 24);
    result = s21_mul(dec1, dec2);
    // 0.0000000000000000009000000000
    str_to_dec("1001", &correct_result, 19);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // 99999,99999999999999999999999
    str_to_dec(
        "-1000000100111111001110010111100011111000100101000"
        "000100110000100001111111111111111111111111111",
        &dec1, 23);
    // 0,02
    str_to_dec("-10", &dec2, 2);
    result = s21_mul(dec1, dec2);
    // 1999.9999999999999999999999998
    str_to_dec(
        "100000010011111100111001011110001111100010"
        "01010000001001100001000011111111111111111111111111110",
        &correct_result, 25);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);
}
END_TEST

START_TEST(round_test_1) {
    s21_decimal dec = {0x00000005, 0x00000000, 0x00000000, 0x00010000,
                       0x0};  // 0.5
    s21_decimal control_dec = {0x00000000, 0x00000000, 0x00000000, 0x00000000,
                               0x0};  // 0
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_2) {
    s21_decimal dec = {0x0000000F, 0x00000000, 0x00000000, 0x00010000,
                       0x0};  // 1.5
    s21_decimal control_dec = {0x00000002, 0x00000000, 0x00000000, 0x00000000,
                               0x0};  // 2
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_3) {
    s21_decimal dec = {0x00000019, 0x00000000, 0x00000000, 0x00010000,
                       0x0};  // 2.5
    s21_decimal control_dec = {0x00000002, 0x00000000, 0x00000000, 0x00000000,
                               0x0};  // 2
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_4) {
    s21_decimal dec = {0x00000023, 0x00000000, 0x00000000, 0x00010000,
                       0x0};  // 3.5
    s21_decimal control_dec = {0x00000004, 0x00000000, 0x00000000, 0x00000000,
                               0x0};  // 4
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_5) {
    s21_decimal dec = {0x0000002D, 0x00000000, 0x00000000, 0x00010000,
                       0x0};  // 4.5
    s21_decimal control_dec = {0x00000004, 0x00000000, 0x00000000, 0x00000000,
                               0x0};  // 4
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_6) {
    s21_decimal dec = {0x00000037, 0x00000000, 0x00000000, 0x00010000,
                       0x0};  // 5.5
    s21_decimal control_dec = {0x00000006, 0x00000000, 0x00000000, 0x00000000,
                               0x0};  // 6
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_7) {
    s21_decimal dec = {0x00000041, 0x00000000, 0x00000000, 0x00010000,
                       0x0};  // 6.5
    s21_decimal control_dec = {0x00000006, 0x00000000, 0x00000000, 0x00000000,
                               0x0};  // 6
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_8) {
    s21_decimal dec = {0x0000004B, 0x00000000, 0x00000000, 0x00010000,
                       0x0};  // 7.5
    s21_decimal control_dec = {0x00000008, 0x00000000, 0x00000000, 0x00000000,
                               0x0};  // 8
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_9) {
    s21_decimal dec = {0x00000055, 0x00000000, 0x00000000, 0x00010000,
                       0x0};  // 8.5
    s21_decimal control_dec = {0x00000008, 0x00000000, 0x00000000, 0x00000000,
                               0x0};  // 8
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_10) {
    s21_decimal dec = {0x0000005F, 0x00000000, 0x00000000, 0x00010000,
                       0x0};  // 9.5
    s21_decimal control_dec = {0x0000000A, 0x00000000, 0x00000000, 0x00000000,
                               0x0};  // 10
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_11) {
    s21_decimal dec = {0x00000005, 0x00000000, 0x00000000, 0x80010000,
                       0x0};  // -0.5
    s21_decimal control_dec = {0x00000000, 0x00000000, 0x00000000, 0x80000000,
                               0x0};  // 0
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_12) {
    s21_decimal dec = {0x0000000F, 0x00000000, 0x00000000, 0x80010000,
                       0x0};  // -1.5
    s21_decimal control_dec = {0x00000002, 0x00000000, 0x00000000, 0x80000000,
                               0x0};  // -2
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_13) {
    s21_decimal dec = {0x00000019, 0x00000000, 0x00000000, 0x80010000,
                       0x0};  // -2.5
    s21_decimal control_dec = {0x00000002, 0x00000000, 0x00000000, 0x80000000,
                               0x0};  // -2
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_14) {
    s21_decimal dec = {0x00000023, 0x00000000, 0x00000000, 0x80010000,
                       0x0};  // -3.5
    s21_decimal control_dec = {0x00000004, 0x00000000, 0x00000000, 0x80000000,
                               0x0};  // -4
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_15) {
    s21_decimal dec = {0x0000002D, 0x00000000, 0x00000000, 0x80010000,
                       0x0};  // -4.5
    s21_decimal control_dec = {0x00000004, 0x00000000, 0x00000000, 0x80000000,
                               0x0};  // -4
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_16) {
    s21_decimal dec = {0x00000037, 0x00000000, 0x00000000, 0x80010000,
                       0x0};  // -5.5
    s21_decimal control_dec = {0x00000006, 0x00000000, 0x00000000, 0x80000000,
                               0x0};  // -6
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_17) {
    s21_decimal dec = {0x00000041, 0x00000000, 0x00000000, 0x80010000,
                       0x0};  // -6.5
    s21_decimal control_dec = {0x00000006, 0x00000000, 0x00000000, 0x80000000,
                               0x0};  // -6
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_18) {
    s21_decimal dec = {0x0000004B, 0x00000000, 0x00000000, 0x80010000,
                       0x0};  // -7.5
    s21_decimal control_dec = {0x00000008, 0x00000000, 0x00000000, 0x80000000,
                               0x0};  // -8
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_19) {
    s21_decimal dec = {0x00000055, 0x00000000, 0x00000000, 0x80010000,
                       0x0};  // -8.5
    s21_decimal control_dec = {0x00000008, 0x00000000, 0x00000000, 0x80000000,
                               0x0};  // -8
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_20) {
    s21_decimal dec = {0x0000005F, 0x00000000, 0x00000000, 0x80010000,
                       0x0};  // -9.5
    s21_decimal control_dec = {0x0000000A, 0x00000000, 0x00000000, 0x80000000,
                               0x0};  // -10
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_21) {
    s21_decimal dec = {0x0000000D, 0x00000000, 0x00000000, 0x80010000,
                       0x0};  // -1.3
    s21_decimal control_dec = {0x00000001, 0x00000000, 0x00000000, 0x80000000,
                               0x0};  // -1
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_22) {
    s21_decimal dec = {0x0000000D, 0x00000000, 0x00000000, 0x00010000,
                       0x0};  // 1.3
    s21_decimal control_dec = {0x00000001, 0x00000000, 0x00000000, 0x00000000,
                               0x0};  // 1
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_23) {
    s21_decimal dec = {0x00000011, 0x00000000, 0x00000000, 0x00010000,
                       0x0};  // 1.7
    s21_decimal control_dec = {0x00000002, 0x00000000, 0x00000000, 0x00000000,
                               0x0};  // 2
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(round_test_24) {
    s21_decimal dec = {0x00000011, 0x00000000, 0x00000000, 0x80010000,
                       0x0};  // -1.7
    s21_decimal control_dec = {0x00000002, 0x00000000, 0x00000000, 0x80000000,
                               0x0};  // -2
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), TRUE);
}
END_TEST

START_TEST(div_uncommon_values) {
    s21_decimal dec1, dec2, result, correct_result;
    init_dec_bits(&correct_result);
    str_to_dec("1010", &dec1, 0);
    // 0.1
    str_to_dec("1", &dec2, 1);
    result = s21_div(dec1, dec2);
    str_to_dec("1100100", &correct_result, 0);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);
    // s21_overflow_decimal dec1_ovf = {50, 0, 0, 0, 0, 0, 0};
    // s21_overflow_decimal dec2_ovf = {20, 0, 0, 0, 0, 0, 0};
    str_to_dec(
        "1001000100100000011100001111001111100110100111100111111110111111011001"
        "10"
        "1110100010111010001011",
        &dec1, 24);
    // 0.1
    str_to_dec("1", &dec2, 1);
    result = s21_div(dec1, dec2);
    // 112286.36363636363636363
    str_to_dec(
        "1001000100100000011100001111001111100110100111100111111110111111011001"
        "10"
        "1110100010111010001011",
        &correct_result, 23);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #1
    // 112286.36363636363636363
    str_to_dec(
        "1001100000101101001010001000000000110111001011001101011"
        "1100010111010001011",
        &dec1, 17);
    // 4.16787847
    str_to_dec("11000110101111010110110000111", &dec2, 8);

    result = s21_div(dec1, dec2);

    // 26940.89197767890683329593341
    str_to_dec(
        "100010110100011111111001010000001101111100101010"
        "01110011100010001001110001010011111111111101",
        &correct_result, 23);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    //  #2
    // 135521
    str_to_dec("100001000101100001", &dec1, 0);
    // 3724292940501892409235
    str_to_dec(
        "11001001111001001111001001111001001111001001111001"
        "0011110010011110010011",
        &dec2, 0);

    result = s21_div(dec1, dec2);

    // 0.0000000000000000363883835576
    str_to_dec("101010010111001001010101011000010111000", &correct_result, 28);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #3
    // 135521
    str_to_dec("100001000101100001", &dec1, 7);
    // 3724292940501892409235
    str_to_dec(
        "1100100111100100111100100111100100111100100111"
        "10010011110010011110010011",
        &dec2, 28);

    result = s21_div(dec1, dec2);

    // 36388.383557641667818989545662
    str_to_dec(
        "111010110010011110000111111000101010010010100001100"
        "10100001111100111000100111111110100010111110",
        &correct_result, 24);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #4
    // 24560730379421944653998624.602
    str_to_dec(
        "100111101011100001010001111010111000010100011110101110"
        "00010100011110101110000101000111101011010",
        &dec1, 3);
    // 31.7
    str_to_dec("100111101", &dec2, 1);

    result = s21_div(dec1, dec2);

    // 774786447300376802965256.29659
    str_to_dec(
        "1111101001011000110101010011001011100000100000010011011000011011011101"
        "01"
        "000110010000100011011011",
        &correct_result, 5);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #5
    // 0.0000000000000000009
    str_to_dec("1001", &dec1, 19);
    // 0,000000000000000000000009
    str_to_dec("1001", &dec2, 24);

    result = s21_div(dec1, dec2);

    // 100000
    str_to_dec("11000011010100000", &correct_result, 0);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #6
    // 0,0000000000000000000000095642
    str_to_dec("10111010110011010", &dec1, 28);
    // 0,0000000000000000000000112
    str_to_dec("1110000", &dec2, 25);

    result = s21_div(dec1, dec2);

    // 0.8539464285714285714285714286
    str_to_dec(
        "1101110010111101011011110011010000101100011010111110111"
        "11000010110011011101101101101101101110",
        &correct_result, 28);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #7
    // 0,0000000000000000000000095642
    str_to_dec("10111010110011010", &dec1, 28);
    // 112000
    str_to_dec("11011010110000000", &dec2, 0);

    result = s21_div(dec1, dec2);

    // 0.0000000000000000000000000001
    str_to_dec("1", &correct_result, 28);
    // print_dec(result);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #7
    // 0,0000000000000000000000095642
    str_to_dec("10111010110011010", &dec1, 28);
    // 272000
    str_to_dec("1000010011010000000", &dec2, 0);

    result = s21_div(dec1, dec2);

    // 0
    str_to_dec("0", &correct_result, 0);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #8
    // 0,0000000000000000000000095642
    str_to_dec("10111010110011010", &dec1, 28);
    // 0.0000000000000000000000000002
    str_to_dec("10", &dec2, 28);

    result = s21_div(dec1, dec2);

    // 47821
    str_to_dec("1011101011001101", &correct_result, 0);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #9
    // 0,0000000000000000000000095642
    str_to_dec("10111010110011010", &dec1, 28);
    // 0.8539464285714285714285714286
    str_to_dec(
        "1101110010111101011011110011010000101100011010111110111"
        "11000010110011011101101101101101101110",
        &dec2, 28);

    result = s21_div(dec1, dec2);

    // 0.0000000000000000000000112
    str_to_dec("1110000", &correct_result, 25);
    // print_dec(result);
    ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);

    // #10
    // 24560730379421944653998624.602
    str_to_dec(
        "100111101011100001010001111010111000010100011110101110"
        "00010100011110101110000101000111101011010",
        &dec1, 3);
    // 792281625142643375935439.50329
    str_to_dec(
        "1111111111111111111111111111111111111111111111111111"
        "11111111111111111111111111111111111111111001",
        &dec2, 5);

    result = s21_div(dec1, dec2);

    // 31
    str_to_dec("11111", &correct_result, 0);
    // print_dec(result);
    //  ck_assert_int_eq(s21_is_equal(correct_result, result), TRUE);
}
END_TEST


START_TEST(mul_test_complex) {
    s21_decimal res;

    s21_decimal dec1 = { 0x1E8307A3, 0x000DAB0B, 0x00000000,
                        0x00060000, s21_NORMAL_VALUE };  // 3847238942.132131
    s21_decimal dec2 = { 0x97D4186D, 0x0000E274, 0x00000000,
                        0x80010000, s21_NORMAL_VALUE };  // -24899039134321.3
    s21_decimal control_dec = { 0x65BEB201, 0x3D763534, 0x1EF3C636,
                        0x80050000, s21_NORMAL_VALUE };  // -95792552979232809039921.60769

    res = s21_mul(dec1, dec2);
    ck_assert_int_eq(s21_is_equal(res, control_dec), 0);

    s21_decimal dec3 = { 0xE550351E, 0x00000000, 0x00000000,
                        0x00000000, s21_NORMAL_VALUE };  // 3847238942
    s21_decimal dec4 = { 0x42620271, 0x000016A5, 0x00000000,
                        0x80000000, s21_NORMAL_VALUE };  // -24899039134321
    s21_decimal control_dec1 = { 0xEA4DAE3E, 0xECB948EB, 0x00001448,
                        0x80000000, s21_NORMAL_VALUE };  // -95792552975941719928382

    res = s21_mul(dec3, dec4);
    ck_assert_int_eq(s21_is_equal(res, control_dec1), 0);

    s21_decimal dec5 = { 0xE550351E, 0x00000000, 0x00000000,
                        0x00000000, s21_NORMAL_VALUE };  // 3847238942
    s21_decimal dec6 = { 0xEE48F444, 0x0008D88D, 0x00000000,
                        0x80020000, s21_NORMAL_VALUE };  // -24899039134321.32
    s21_decimal control_dec2 = { 0x305EB3F8, 0x78607C44, 0x0007EC7C,
                        0x80020000, s21_NORMAL_VALUE };  // -95792552975942951044843.44

    res = s21_mul(dec5, dec6);
    ck_assert_int_eq(s21_is_equal(res, control_dec2), 0);

    s21_decimal dec7 = { 0xE550351E, 0x00000000, 0x00000000,
                        0x00000000, s21_NORMAL_VALUE };  // 3847238942
    s21_decimal dec8 = { 0x01C5A560, 0x598B282C, 0x00000001,
                        0x80060000, s21_NORMAL_VALUE };  // -24899039134321.321312
    s21_decimal control_dec3 = { 0x77D70686, 0x38E56AD2, 0x1EF3C636,
                        0x80050000, s21_NORMAL_VALUE };  // -95792552975942956092420.93190

    res = s21_mul(dec7, dec8);
    ck_assert_int_eq(s21_is_equal(res, control_dec3), 0);

    s21_decimal dec9 = { 0x73CE5B59, 0x00000B3A, 0x00000000,
                        0x00000000, s21_NORMAL_VALUE };  // 12345678912345
    s21_decimal dec10 = { 0x7DC79887, 0x112210F4, 0x00000000,
                        0x00070000, s21_NORMAL_VALUE };  // 123456789012.1234567
    s21_decimal control_dec4 = { 0x8A82E0C6, 0x8F8452B2, 0x313F89D8,
                        0x00040000, s21_NORMAL_VALUE };  // 1524157876692798463930917.7030

    res = s21_mul(dec9, dec10);
    ck_assert_int_eq(s21_is_equal(res, control_dec4), 0);

    s21_decimal dec11 = { 0x00000003, 0x00000000, 0x00000000,
                        0x00000000, s21_NORMAL_VALUE };  // 3
    s21_decimal dec12 = { 0x00000002, 0x00000000, 0x00000000,
                        0x00000000, s21_NORMAL_VALUE };  // 2
    s21_decimal control_dec5 = { 0x00000006, 0x00000000, 0x00000000,
                        0x00000000, s21_NORMAL_VALUE };  // 6

    res = s21_mul(dec11, dec12);
    ck_assert_int_eq(s21_is_equal(res, control_dec5), 0);

    s21_decimal dec13 = { 0x00000099, 0x00000000, 0x00000000,
                        0x00020000, s21_NORMAL_VALUE };  // 1.53
    s21_decimal dec14 = { 0x00000156, 0x00000000, 0x00000000,
                        0x00030000, s21_NORMAL_VALUE };  // 0.342
    s21_decimal control_dec6 = { 0x0000CC66, 0x00000000, 0x00000000,
                        0x00050000, s21_NORMAL_VALUE };  // 0.52326

    res = s21_mul(dec13, dec14);
    ck_assert_int_eq(s21_is_equal(res, control_dec6), 0);

    s21_decimal dec15 = { 0x00000098, 0x00000000, 0x00000000,
                        0x00020000, s21_NORMAL_VALUE };  // 1.52
    s21_decimal dec16 = { 0x00000020, 0x00000000, 0x00000000,
                        0x00020000, s21_NORMAL_VALUE };  // 0.32
    s21_decimal control_dec7 = { 0x00001300, 0x00000000, 0x00000000,
                        0x00040000, s21_NORMAL_VALUE };  // 0.4864

    res = s21_mul(dec15, dec16);
    ck_assert_int_eq(s21_is_equal(res, control_dec7), 0);


    s21_decimal dec17 = { 0x0000005F, 0x00000000, 0x00000000,
                        0x00010000, s21_NORMAL_VALUE };  // 9.5
    s21_decimal dec18 = { 0x00000001, 0x00000000, 0x00000000,
                        0x001C0000, s21_NORMAL_VALUE };  // 0.0000000000000000000000000001
    s21_decimal control_dec8 = { 0x0000000A, 0x00000000, 0x00000000,
                        0x001C0000, s21_NORMAL_VALUE };  // 0.0000000000000000000000000010

    res = s21_mul(dec17, dec18);
    ck_assert_int_eq(s21_is_equal(res, control_dec8), 0);


    s21_decimal dec19 = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                        0x00000000, s21_NORMAL_VALUE };  // 79228162514264337593543950335
    s21_decimal dec20 = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                        0x00000000, s21_NORMAL_VALUE };  // 79228162514264337593543950335
    s21_decimal control_dec9 = { 0x0000000A, 0x00000000, 0x00000000,
                        0x001C0000, s21_INFINITY };  // s21_INF

    res = s21_mul(dec19, dec20);
    ck_assert_int_eq(s21_is_equal(res, control_dec9), 0);

    s21_decimal dec21 = { 0x0000004B, 0x00000000, 0x00000000,
                        0x00010000, s21_NORMAL_VALUE };  // 7.5
    s21_decimal dec22 = { 0x00000003, 0x00000000, 0x00000000,
                        0x001C0000, s21_NORMAL_VALUE };  // 0.0000000000000000000000000003
    s21_decimal control_dec10 = { 0x00000016, 0x00000000, 0x00000000,
                        0x001C0000, s21_NORMAL_VALUE };  // 0.0000000000000000000000000022

    res = s21_mul(dec21, dec22);
    ck_assert_int_eq(s21_is_equal(res, control_dec10), 0);

    s21_decimal dec23 = { 0xD82BB6D3, 0x7CE4F03A, 0x03FD35EB,
                        0x001C0000, s21_NORMAL_VALUE };  // 0.1234567891234567891234567891
    s21_decimal dec24 = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                        0x00000000, s21_NORMAL_VALUE };  // 79228162514264337593543950335
    s21_decimal control_dec11 = { 0x4371F156, 0xC1215E62, 0x1F9ADD37,
                        0x00000000, s21_NORMAL_VALUE };  // 9781254552162496368673419606

    res = s21_mul(dec23, dec24);
    ck_assert_int_eq(s21_is_equal(res, control_dec11), 0);

    s21_decimal dec25 = { 0x8C66D64E, 0x9849F829, 0x000A364C,
                        0x001A0000, s21_NORMAL_VALUE };  // 0.12345678912345678912345678
    s21_decimal dec26 = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                        0x00000000, s21_NORMAL_VALUE };  // 79228162514264337593543950335
    s21_decimal control_dec12 = { 0x4371EE85, 0xC1215E62, 0x1F9ADD37,
                        0x00000000, s21_NORMAL_VALUE };  // 9781254552162496368673418885

    res = s21_mul(dec25, dec26);
    ck_assert_int_eq(s21_is_equal(res, control_dec12), 0);

    s21_decimal dec27 = { 0x000004D2, 0x00000000, 0x00000000,
                        0x00040000, s21_NORMAL_VALUE };  // 0.1234
    s21_decimal dec28 = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                        0x00000000, s21_NORMAL_VALUE };  // 79228162514264337593543950335
    s21_decimal control_dec13 = { 0x6A161E4F, 0x538EF34D, 0x1F972474,
                        0x00000000, s21_NORMAL_VALUE };  // 9776755254260219259043323471

    res = s21_mul(dec27, dec28);
    ck_assert_int_eq(s21_is_equal(res, control_dec13), 0);

    s21_decimal dec29 = { 0x0000000C, 0x00000000, 0x00000000,
                        0x00020000, s21_NORMAL_VALUE };  // 0.12
    s21_decimal dec30 = { 0x70000000, 0xB30310A7, 0xE22EA493,
                        0x00000000, s21_NORMAL_VALUE };  // 70000000000000000000000000000
    s21_decimal control_dec14 = { 0xD0000000, 0x71A43532, 0x1B245130,
                        0x00000000, s21_NORMAL_VALUE };  // 8400000000000000000000000000

    s21_decimal dec31 = { 0x00000065, 0x00000000, 0x00000000,
                        0x00020000, s21_NORMAL_VALUE };  // 1.01
    s21_decimal dec32 = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                        0x80000000, s21_NORMAL_VALUE };  // -79228162514264337593543950335
    s21_decimal control_dec15 = { 0x00000000,  0x00000000,  0x00000000,
                        0x00000000, s21_NEGATIVE_INFINITY };  // 9781254552162496368673419606

    s21_decimal dec33 = { 0x00000065, 0x00000000, 0x00000000,
                        0x00020000, s21_NAN };  // 1.01
    s21_decimal dec34 = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                        0x80000000, s21_NORMAL_VALUE };  // -79228162514264337593543950335
    s21_decimal control_dec16 = { 0x00000000,  0x00000000,  0x00000000,
                        0x00000000, s21_NAN };  // 9781254552162496368673419606

    res = s21_mul(dec31, dec32);
    ck_assert_int_eq(s21_is_equal(res, control_dec15), 0);

    res = s21_mul(dec29, dec30);
    ck_assert_int_eq(s21_is_equal(res, control_dec14), 0);
}
END_TEST

START_TEST(round_test_complex) {
    s21_decimal res_rnd;
    s21_decimal dec1 = { 0x00000005, 0x00000000, 0x00000000,
                            0x80010000, s21_NORMAL_VALUE };  // -0.5
    s21_decimal control_dec1 = { 0x00000000, 0x00000000, 0x00000000,
                            0x80000000, s21_NORMAL_VALUE };  // 0
    res_rnd = s21_round(dec1);
    ck_assert_int_eq(s21_is_equal(res_rnd, control_dec1), 0);

    s21_decimal dec2 = { 0xD44B72FB, 0x01B6F5A3, 0x00000000,
                            0x800F0000, s21_NORMAL_VALUE };  // -123.556123789456123
    s21_decimal control_dec2 = { 0x0000007C, 0x00000000, 0x00000000,
                            0x80000000, s21_NORMAL_VALUE };  // -124
    res_rnd = s21_round(dec2);
    ck_assert_int_eq(s21_is_equal(res_rnd, control_dec2), 0);


    s21_decimal dec3 = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                            0x00000000, s21_NORMAL_VALUE };  // 79228162514264337593543950335
    s21_decimal control_dec3 = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                            0x00000000, s21_NORMAL_VALUE };  // 79228162514264337593543950335
    res_rnd = s21_round(dec3);
    ck_assert_int_eq(s21_is_equal(res_rnd, control_dec3), 0);

    s21_decimal dec4 = { 0x696B9642, 0x9D4938E0, 0x00000A06,
                            0x00170000, s21_NORMAL_VALUE };  // 0.47345678945612456498754
    s21_decimal control_dec4 = { 0x00000000, 0x00000000, 0x00000000,
                            0x00000000, s21_NORMAL_VALUE };  // 0
    res_rnd = s21_round(dec4);
    ck_assert_int_eq(s21_is_equal(res_rnd, control_dec4), 0);

    s21_decimal dec5 = { 0x1BAB9642, 0xB72A029B, 0x00000C24,
                            0x00170000, s21_NORMAL_VALUE };  // 0.57345678945612456498754
    s21_decimal control_dec5 = { 0x00000001, 0x00000000, 0x00000000,
                            0x00000000, s21_NORMAL_VALUE };  // 1
    res_rnd = s21_round(dec5);
    ck_assert_int_eq(s21_is_equal(res_rnd, control_dec5), 0);

    s21_decimal dec6 = { 0x00000005, 0x00000000, 0x00000000,
                            0x00010000, s21_NORMAL_VALUE };  // 0.5
    s21_decimal control_dec6 = { 0x00000000, 0x00000000, 0x00000000,
                            0x00000000, s21_NORMAL_VALUE };  // 0
    res_rnd = s21_round(dec6);
    ck_assert_int_eq(s21_is_equal(res_rnd, control_dec6), 0);

    s21_decimal dec7 = { 0xA931A001, 0x0000E35F, 0x00000000,
                            0x000E0000, s21_NORMAL_VALUE };  // 2.50000000000001
    s21_decimal control_dec7 = { 0x00000003, 0x00000000, 0x00000000,
                            0x00000000, s21_NORMAL_VALUE };  // 3
    res_rnd = s21_round(dec7);
    ck_assert_int_eq(s21_is_equal(res_rnd, control_dec7), 0);

    s21_decimal dec8 = { 0x00000019, 0x00000000, 0x00000000,
                            0x00010000, s21_NORMAL_VALUE };  // 2.5
    s21_decimal control_dec8 = { 0x00000002, 0x00000000, 0x00000000,
                            0x00000000, s21_NORMAL_VALUE };  // 2
    res_rnd = s21_round(dec8);
    ck_assert_int_eq(s21_is_equal(res_rnd, control_dec8), 0);

    s21_decimal dec9 = { 0x0000002D, 0x00000000, 0x00000000,
                            0x00010000, s21_NORMAL_VALUE };  // 4.5
    s21_decimal control_dec9 = { 0x00000004, 0x00000000, 0x00000000,
                            0x00000000, s21_NORMAL_VALUE };  // 4
    res_rnd = s21_round(dec9);
    ck_assert_int_eq(s21_is_equal(res_rnd, control_dec9), 0);

    s21_decimal dec10 = { 0x00000023, 0x00000000, 0x00000000,
                            0x00010000, s21_NORMAL_VALUE };  // 3.5
    s21_decimal control_dec10 = { 0x00000004, 0x00000000, 0x00000000,
                            0x00000000, s21_NORMAL_VALUE };  // 4
    res_rnd = s21_round(dec10);
    ck_assert_int_eq(s21_is_equal(res_rnd, control_dec10), 0);

    s21_decimal dec11 = { 0x00000037, 0x00000000, 0x00000000,
                            0x00010000, s21_NORMAL_VALUE };  // 5.5
    s21_decimal control_dec11 = { 0x00000006, 0x00000000, 0x00000000,
                            0x00000000, s21_NORMAL_VALUE };  // 6
    res_rnd = s21_round(dec11);
    ck_assert_int_eq(s21_is_equal(res_rnd, control_dec11), 0);

    s21_decimal dec12 = { 0x00000038, 0x00000000, 0x00000000,
                            0x80010000, s21_NORMAL_VALUE };  // -5.6
    s21_decimal control_dec12 = { 0x00000006, 0x00000000, 0x00000000,
                            0x80000000, s21_NORMAL_VALUE };  // -6
    res_rnd = s21_round(dec12);
    ck_assert_int_eq(s21_is_equal(res_rnd, control_dec12), 0);
}
END_TEST


START_TEST(nan_test) {
    s21_decimal result;
    s21_decimal dec1 = {0x0000000D, 0x00000000, 0x00000000, 0x80010000,
                       s21_NAN};
    s21_decimal dec2 = {0x00000001, 0x00000000, 0x00000000, 0x00000000,
                       s21_NORMAL_VALUE};
    s21_decimal control_dec = {0x00000000, 0x00000000, 0x00000000, 0x00000000,
                               s21_NAN};
    result = s21_mul(dec1, dec2);
    ck_assert_int_eq(result.value_type, control_dec.value_type);
    result = s21_mod(dec1, dec2);
    ck_assert_int_eq(result.value_type, control_dec.value_type);
    result = s21_div(dec1, dec2);
    ck_assert_int_eq(result.value_type, control_dec.value_type);
    s21_decimal div_zero = {0x00000000, 0x00000000, 0x00000000, 0x00000000,
                       s21_NORMAL_VALUE};
    s21_decimal to_div = {0x00000001, 0x00000000, 0x00000000, 0x00000000,
                       s21_NORMAL_VALUE};
    result = s21_div(to_div, div_zero);
    ck_assert_int_eq(result.value_type, s21_INFINITY);
    s21_decimal to_div_neg;
    str_to_dec("-10", &to_div_neg, 0);
    result = s21_div(to_div_neg, div_zero);
    ck_assert_int_eq(result.value_type, s21_NEGATIVE_INFINITY);
    result = s21_mod(to_div_neg, div_zero);
    ck_assert_int_eq(result.value_type, s21_NEGATIVE_INFINITY);

    s21_decimal dec_max = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, s21_NORMAL_VALUE};
    s21_decimal dec_2 = {0x00000002, 0x00000000, 0x00000000, 0x00010000, s21_NORMAL_VALUE};
    result = s21_div(dec_max, dec_2);
    ck_assert_int_eq(result.value_type, s21_INFINITY);
}
END_TEST

START_TEST(mult_test_1) {
s21_decimal dec1 = {0x1E8307A3, 0x000DAB0B, 0x00000000,
                                    0x00060000, s21_NORMAL_VALUE};  // 3847238942.132131
s21_decimal dec2 = {0x97D4186D, 0x0000E274, 0x00000000,
                                    0x80010000, s21_NORMAL_VALUE};  // -24899039134321.3
    s21_decimal control_dec = {0x65BEB201, 0x3D763534, 0x1EF3C636,
                                    0x80050000, s21_NORMAL_VALUE};  // -95792552979232809039921.60769
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST
START_TEST(mult_test_2) {
    s21_decimal dec1 = {0x73CE5B59, 0x00000B3A, 0x00000000,
                                    0x00000000, s21_NORMAL_VALUE};  // 12345678912345
    s21_decimal dec2 = {0x7DC79887, 0x112210F4, 0x00000000,
                                    0x00070000, s21_NORMAL_VALUE};  // 123456789012.1234567
    s21_decimal control_dec = {0x8A82E0C6, 0x8F8452B2, 0x313F89D8,
                                    0x00040000, s21_NORMAL_VALUE};  // 1524157876692798463930917.7030
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST

START_TEST(mult_test_3) {
    s21_decimal dec1 = {0x00000003, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 3
    s21_decimal dec2 = {0x00000002, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 2
    s21_decimal control_dec = {0x00000006, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 6
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST

START_TEST(mult_test_4) {
s21_decimal dec1 = {0x00000002, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 2
    s21_decimal dec2 = {0x00000003, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 3
    s21_decimal control_dec = {0x00000006, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 6
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST

START_TEST(mult_test_5) {
    s21_decimal dec1 = {0x00000002, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -2
    s21_decimal dec2 = {0x00000003, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 3
    s21_decimal control_dec = {0x00000006, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -6
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST

START_TEST(mult_test_6) {
    s21_decimal dec1 = {0x00000003, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -3
    s21_decimal dec2 = {0x00000002, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 2
    s21_decimal control_dec = {0x00000006, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -6
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST
START_TEST(mult_test_7) {
    s21_decimal dec1 = {0x00000002, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 2
    s21_decimal dec2 = {0x00000003, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -3
    s21_decimal control_dec = {0x00000006, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -6
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST

START_TEST(mult_test_8) {
    s21_decimal dec1 = {0x00000003, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 3
    s21_decimal dec2 = {0x00000002, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -2
    s21_decimal control_dec = {0x00000006, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -6
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST

START_TEST(mult_test_9) {
    s21_decimal dec1 = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                                    0x00000000, s21_NORMAL_VALUE};  // 79228162514264337593543950335
    s21_decimal dec2 = {0x00000001, 0x00000000, 0x00000000,
                                    0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000001
    s21_decimal control_dec = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                                    0x001C0000, s21_NORMAL_VALUE};  // 7.9228162514264337593543950335
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST

START_TEST(mult_test_10) {
    s21_decimal dec1 = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                                    0x00000000, s21_NORMAL_VALUE};  // 79228162514264337593543950335
    s21_decimal dec2 = {0x00000001, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -1
    s21_decimal control_dec = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                                0x80000000, s21_NORMAL_VALUE};  // -79228162514264337593543950335
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST

START_TEST(mult_test_11) {
    s21_decimal dec1 = {0x00000099, 0x00000000, 0x00000000, 0x00020000, s21_NORMAL_VALUE};  // 1.53
    s21_decimal dec2 = {0x00000156, 0x00000000, 0x00000000, 0x00030000, s21_NORMAL_VALUE};  // 0.342
    s21_decimal control_dec = {0x0000CC66, 0x00000000, 0x00000000, 0x00050000, s21_NORMAL_VALUE};  // 0.52326
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST

START_TEST(mult_test_12) {
    s21_decimal dec1 = {0x00000005, 0x00000000, 0x00000000,
                                    0x00010000, s21_NORMAL_VALUE};  // 0.5
    s21_decimal dec2 = {0x00000001, 0x00000000, 0x00000000,
                                    0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000001
    s21_decimal control_dec = {0x00000000, 0x00000000, 0x00000000,
                                    0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000000
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST

START_TEST(mult_test_13) {
    s21_decimal dec1 = {0x0000000F, 0x00000000, 0x00000000,
                                    0x00010000, s21_NORMAL_VALUE};  // 1.5
    s21_decimal dec2 = {0x00000001, 0x00000000, 0x00000000,
                                    0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000001
    s21_decimal control_dec = {0x00000002, 0x00000000, 0x00000000,
                                0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000002
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST

START_TEST(mult_test_14) {
    s21_decimal dec1 = {0x00000019, 0x00000000, 0x00000000,
                                    0x00010000, s21_NORMAL_VALUE};  // 2.5
    s21_decimal dec2 = {0x00000001, 0x00000000, 0x00000000,
                                    0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000001
    s21_decimal control_dec = {0x00000002, 0x00000000,
                        0x00000000, 0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000002
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST

START_TEST(mult_test_15) {
    s21_decimal dec1 = {0x00000023, 0x00000000, 0x00000000,
                                    0x00010000, s21_NORMAL_VALUE};  // 3.5
    s21_decimal dec2 = {0x00000001, 0x00000000, 0x00000000,
                                    0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000001
    s21_decimal control_dec = {0x00000004, 0x00000000, 0x00000000,
                                    0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000004
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST

START_TEST(mult_test_16) {
    s21_decimal dec1 = {0x0000002D, 0x00000000, 0x00000000,
                                    0x00010000, s21_NORMAL_VALUE};  // 4.5
    s21_decimal dec2 = {0x00000001, 0x00000000, 0x00000000,
                                    0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000001
    s21_decimal control_dec = {0x00000004, 0x00000000, 0x00000000,
                                    0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000004
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST

START_TEST(mult_test_17) {
s21_decimal dec1 = {0x00000037, 0x00000000, 0x00000000, 0x00010000, s21_NORMAL_VALUE};  // 5.5
    s21_decimal dec2 = {0x00000001, 0x00000000, 0x00000000,
                                    0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000001
    s21_decimal control_dec = {0x00000006, 0x00000000, 0x00000000,
                                    0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000006
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST

START_TEST(mult_test_18) {
    s21_decimal dec1 = {0x00000041, 0x00000000, 0x00000000, 0x00010000, s21_NORMAL_VALUE};  // 6.5
    s21_decimal dec2 = {0x00000001, 0x00000000, 0x00000000,
                                    0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000001
    s21_decimal control_dec = {0x00000006, 0x00000000, 0x00000000,
                                    0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000006
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST

START_TEST(mult_test_19) {
    s21_decimal dec1 = {0x0000004B, 0x00000000, 0x00000000, 0x00010000, s21_NORMAL_VALUE};  // 7.5
    s21_decimal dec2 = {0x00000001, 0x00000000, 0x00000000,
                                    0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000001
    s21_decimal control_dec = {0x00000008, 0x00000000, 0x00000000,
                                    0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000008
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST

START_TEST(mult_test_20) {
    s21_decimal dec1 = {0x00000055, 0x00000000, 0x00000000, 0x00010000, s21_NORMAL_VALUE};  // 8.5
    s21_decimal dec2 = {0x00000001, 0x00000000, 0x00000000,
                                    0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000001
    s21_decimal control_dec = {0x00000008, 0x00000000, 0x00000000,
                                    0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000008
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST

START_TEST(mult_test_21) {
    s21_decimal dec1 = {0x0000005F, 0x00000000, 0x00000000, 0x00010000, s21_NORMAL_VALUE};  // 9.5
    s21_decimal dec2 = {0x00000001, 0x00000000, 0x00000000,
                                    0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000001
    s21_decimal control_dec = {0x0000000A, 0x00000000, 0x00000000,
                                    0x001C0000, s21_NORMAL_VALUE};  // 0.0000000000000000000000000010
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST

START_TEST(mult_test_22) {
    s21_decimal dec1 = {0x540053B3, 0x018F214B, 0x00000000,
                                        0x00110000, s21_NORMAL_VALUE};  // 1.12345123123123123
    s21_decimal dec2 = {0xA74FF3B3, 0xBC314C12, 0x0001C196,
                                        0x80180000, s21_NORMAL_VALUE};  // -2.123123123123123123123123
    s21_decimal control_dec = {0x5D858019, 0xDE7826A4, 0x4D121F02,
                                        0x801C0000, s21_NORMAL_VALUE};  // -2.3852252867281696084384383001
    ck_assert_int_eq(s21_is_equal(s21_mul(dec1, dec2), control_dec), 0);
}
END_TEST


START_TEST(round_complex_test_1) {
    s21_decimal dec = {0x59200005, 0x0CF064DD, 0x0000010F,
                                        0x00160000, s21_NORMAL_VALUE};  // 0.5000000000000000000005
    s21_decimal control_dec = {0x00000001, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 1
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST

START_TEST(round_complex_test_2) {
    s21_decimal dec = {0x0000000F, 0x00000000, 0x00000000, 0x00010000, s21_NORMAL_VALUE};  // 1.5
    s21_decimal control_dec = {0x00000002, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 2
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST
START_TEST(round_complex_test_3) {
    s21_decimal dec = {0x00000019, 0x00000000, 0x00000000, 0x00010000, s21_NORMAL_VALUE};  // 2.5
    s21_decimal control_dec = {0x00000002, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 2
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST

START_TEST(round_complex_test_4) {
    s21_decimal dec = {0x00000023, 0x00000000, 0x00000000, 0x00010000, s21_NORMAL_VALUE};  // 3.5
    s21_decimal control_dec = {0x00000004, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 4
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST

START_TEST(round_complex_test_5) {
    s21_decimal dec = {0x6673DFAB, 0x000028ED, 0x00000000, 0x000D0000, s21_NORMAL_VALUE};  // 4.5000091230123
    s21_decimal control_dec = {0x00000005, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 5
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST

START_TEST(round_complex_test_6) {
    s21_decimal dec = {0x00000037, 0x00000000, 0x00000000, 0x00010000, s21_NORMAL_VALUE};  // 5.5
    s21_decimal control_dec = {0x00000006, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 6
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);}
END_TEST

START_TEST(round_complex_test_7) {
    s21_decimal dec = {0x00000041, 0x00000000, 0x00000000, 0x00010000, s21_NORMAL_VALUE};  // 6.5
    s21_decimal control_dec = {0x00000006, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 6
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST

START_TEST(round_complex_test_8) {
    s21_decimal dec = {0x0000004B, 0x00000000, 0x00000000, 0x00010000, s21_NORMAL_VALUE};  // 7.5
    s21_decimal control_dec = {0x00000008, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 8
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST

START_TEST(round_complex_test_9) {
s21_decimal dec = {0x00000353, 0x00000000, 0x00000000, 0x00020000, s21_NORMAL_VALUE};  // 8.51
    s21_decimal control_dec = {0x00000009, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 9
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST

START_TEST(round_complex_test_10) {
    s21_decimal dec = {0x000003B7, 0x00000000, 0x00000000, 0x00020000, s21_NORMAL_VALUE};  // 9.51
s21_decimal control_dec = {0x0000000A, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 10
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST

START_TEST(round_complex_test_11) {
    s21_decimal dec = {0x00000005, 0x00000000, 0x00000000, 0x80010000, s21_NORMAL_VALUE};  // -0.5
    s21_decimal control_dec = {0x00000000, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // 0
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST

START_TEST(round_complex_test_12) {
s21_decimal dec = {0x0000000F, 0x00000000, 0x00000000, 0x80010000, s21_NORMAL_VALUE};  // -1.5
    s21_decimal control_dec = {0x00000002, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -2
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST

START_TEST(round_complex_test_13) {
s21_decimal dec = {0x000000FD, 0x00000000, 0x00000000, 0x80020000, s21_NORMAL_VALUE};  // -2.53
    s21_decimal control_dec = {0x00000003, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -3
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST

START_TEST(round_complex_test_14) {
    s21_decimal dec = {0x00000023, 0x00000000, 0x00000000, 0x80010000, s21_NORMAL_VALUE};  // -3.5
    s21_decimal control_dec = {0x00000004, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -4
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);}
END_TEST

START_TEST(round_complex_test_15) {
    s21_decimal dec = {0x0044AA21, 0x00000000, 0x00000000, 0x80060000, s21_NORMAL_VALUE};  // -4.500001
    s21_decimal control_dec = {0x00000005, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -5
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST
START_TEST(round_complex_test_16) {
    s21_decimal dec = {0x00000037, 0x00000000, 0x00000000, 0x80010000, s21_NORMAL_VALUE};  // -5.5
    s21_decimal control_dec = {0x00000006, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -6
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST

START_TEST(round_complex_test_17) {
s21_decimal dec = {0x00000041, 0x00000000, 0x00000000, 0x80010000, s21_NORMAL_VALUE};  // -6.5
    s21_decimal control_dec = {0x00000006, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -6
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST

START_TEST(round_complex_test_18) {
    s21_decimal dec = {0x0000004B, 0x00000000, 0x00000000, 0x80010000, s21_NORMAL_VALUE};  // -7.5
s21_decimal control_dec = {0x00000008, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -8
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST

START_TEST(round_complex_test_19) {
    s21_decimal dec = {0x1365D5B3, 0x00030512, 0x00000000,
                                    0x800E0000, s21_NORMAL_VALUE};  // -8.50000123123123
    s21_decimal control_dec = {0x00000009, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -9
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST

START_TEST(round_complex_test_20) {
    s21_decimal dec = {0x0000005F, 0x00000000, 0x00000000, 0x80010000, s21_NORMAL_VALUE};  // -9.5
s21_decimal control_dec = {0x0000000A, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -10
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST

START_TEST(round_complex_test_21) {
    s21_decimal dec = {0x0000000D, 0x00000000, 0x00000000, 0x80010000, s21_NORMAL_VALUE};  // -1.3
s21_decimal control_dec = {0x00000001, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -1
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST

START_TEST(round_complex_test_22) {
    s21_decimal dec = {0x0000000D, 0x00000000, 0x00000000, 0x00010000, s21_NORMAL_VALUE};  // 1.3
    s21_decimal control_dec = {0x00000001, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 1
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST

START_TEST(round_complex_test_23) {
    s21_decimal dec = {0x00000011, 0x00000000, 0x00000000, 0x00010000, s21_NORMAL_VALUE};  // 1.7
s21_decimal control_dec = {0x00000002, 0x00000000, 0x00000000, 0x00000000, s21_NORMAL_VALUE};  // 2
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST

START_TEST(round_complex_test_24) {
    s21_decimal dec = {0x00000011, 0x00000000, 0x00000000, 0x80010000, s21_NORMAL_VALUE};  // -1.7
    s21_decimal control_dec = {0x00000002, 0x00000000, 0x00000000, 0x80000000, s21_NORMAL_VALUE};  // -2
    ck_assert_int_eq(s21_is_equal(s21_round(dec), control_dec), 0);
}
END_TEST



int main(void) {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    srunner_set_fork_status(sr, CK_NOFORK);

    suite_add_tcase(s1, tc1_1);

    tcase_add_test(tc1_1, round_test_1);
    tcase_add_test(tc1_1, round_test_2);
    tcase_add_test(tc1_1, round_test_3);
    tcase_add_test(tc1_1, round_test_4);
    tcase_add_test(tc1_1, round_test_5);
    tcase_add_test(tc1_1, round_test_6);
    tcase_add_test(tc1_1, round_test_7);
    tcase_add_test(tc1_1, round_test_8);
    tcase_add_test(tc1_1, round_test_9);
    tcase_add_test(tc1_1, round_test_10);
    tcase_add_test(tc1_1, round_test_11);
    tcase_add_test(tc1_1, round_test_12);
    tcase_add_test(tc1_1, round_test_13);
    tcase_add_test(tc1_1, round_test_15);
    tcase_add_test(tc1_1, round_test_16);
    tcase_add_test(tc1_1, round_test_17);
    tcase_add_test(tc1_1, round_test_18);
    tcase_add_test(tc1_1, round_test_19);
    tcase_add_test(tc1_1, round_test_20);
    tcase_add_test(tc1_1, round_test_21);
    tcase_add_test(tc1_1, round_test_22);
    tcase_add_test(tc1_1, round_test_23);
    tcase_add_test(tc1_1, round_test_24);
    tcase_add_test(tc1_1, s21_from_int_to_decimal_1);

    tcase_add_test(tc1_1, s21_from_float_to_decimal_1);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_2);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_3);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_4);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_5);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_6);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_7);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_8);
    tcase_add_test(tc1_1, s21_from_float_to_decimal_9);

    tcase_add_test(tc1_1, s21_from_decimal_to_int_1);
    tcase_add_test(tc1_1, s21_from_decimal_to_int_2);
    tcase_add_test(tc1_1, s21_from_decimal_to_int_3);
    tcase_add_test(tc1_1, s21_from_decimal_to_int_4);
    tcase_add_test(tc1_1, s21_from_decimal_to_int_5);
    tcase_add_test(tc1_1, s21_from_decimal_to_int_6);

    tcase_add_test(tc1_1, s21_from_decimal_to_float_1);
    tcase_add_test(tc1_1, s21_from_decimal_to_float_2);
    tcase_add_test(tc1_1, s21_from_decimal_to_float_3);
    tcase_add_test(tc1_1, s21_from_decimal_to_float_4);
    tcase_add_test(tc1_1, s21_from_decimal_to_float_5);

    tcase_add_test(tc1_1, from_int_to_dec);
    tcase_add_test(tc1_1, from_float_to_dec);
    tcase_add_test(tc1_1, from_dec_to_int);
    tcase_add_test(tc1_1, from_dec_to_float);

    tcase_add_test(tc1_1, compare_less);
    tcase_add_test(tc1_1, compare_greater);
    tcase_add_test(tc1_1, compare_less_or_equal);
    tcase_add_test(tc1_1, compare_greater_or_equal);
    tcase_add_test(tc1_1, compare_equal);
    tcase_add_test(tc1_1, compare_equal_null);
    tcase_add_test(tc1_1, compare_not_equal);

    tcase_add_test(tc1_1, eq_funcs_test);
    tcase_add_test(tc1_1, greater_funcs_test);
    tcase_add_test(tc1_1, lesser_funcs_test);
    tcase_add_test(tc1_1, eq_funcs_test_float_point);
    tcase_add_test(tc1_1, greater_test_float_point);

    tcase_add_test(tc1_1, s21_int_to_dec_vv_test);
    tcase_add_test(tc1_1, s21_flt_to_dec_vv_test);
    tcase_add_test(tc1_1, s21_round_test);
    tcase_add_test(tc1_1, s21_truncate_test);
    tcase_add_test(tc1_1, round_dec);
    tcase_add_test(tc1_1, truncate_common_values);
    tcase_add_test(tc1_1, floor_dec);
    tcase_add_test(tc1_1, s21_floor_test);
    tcase_add_test(tc1_1, s21_add_1);
    tcase_add_test(tc1_1, s21_add_2);
    tcase_add_test(tc1_1, s21_add_3);
    tcase_add_test(tc1_1, s21_add_4);
    tcase_add_test(tc1_1, s21_add_5);
    tcase_add_test(tc1_1, s21_add_6);
    tcase_add_test(tc1_1, s21_add_7);
    tcase_add_test(tc1_1, s21_add_8);
    tcase_add_test(tc1_1, s21_add_9);
    tcase_add_test(tc1_1, s21_add_10);
    tcase_add_test(tc1_1, s21_add_11);
    tcase_add_test(tc1_1, s21_add_12);
    tcase_add_test(tc1_1, s21_add_13);
    tcase_add_test(tc1_1, s21_add_14);
    tcase_add_test(tc1_1, s21_add_15);
    tcase_add_test(tc1_1, s21_add_16);
    tcase_add_test(tc1_1, s21_add_17);
    tcase_add_test(tc1_1, s21_add_18);
    tcase_add_test(tc1_1, s21_add_19);
    tcase_add_test(tc1_1, s21_add_20);
    tcase_add_test(tc1_1, s21_add_21);
    tcase_add_test(tc1_1, add_norm);
    tcase_add_test(tc1_1, special_values);

    tcase_add_test(tc1_1, s21_sub_9);
    tcase_add_test(tc1_1, s21_sub_10);
    tcase_add_test(tc1_1, s21_sub_11);
    tcase_add_test(tc1_1, s21_sub_12);
    tcase_add_test(tc1_1, s21_sub_13);
    tcase_add_test(tc1_1, s21_sub_14);
    tcase_add_test(tc1_1, s21_sub_15);
    tcase_add_test(tc1_1, s21_sub_16);
    tcase_add_test(tc1_1, sub_normal_test_integer);
    tcase_add_test(tc1_1, sub_uncommon_values);

    tcase_add_test(tc1_1, div_common_values);
    tcase_add_test(tc1_1, div_uncommon_values);
    tcase_add_test(tc1_1, mod_common_values);
    tcase_add_test(tc1_1, s21_mod_1);
    tcase_add_test(tc1_1, s21_mod_2);
    tcase_add_test(tc1_1, s21_mod_3);
    tcase_add_test(tc1_1, s21_mod_4);
    tcase_add_test(tc1_1, s21_mod_5);
    tcase_add_test(tc1_1, s21_mod_6);
    tcase_add_test(tc1_1, s21_mod_7);
    tcase_add_test(tc1_1, s21_mod_8);
    tcase_add_test(tc1_1, mod_uncommon_values);

    tcase_add_test(tc1_1, mul);
    tcase_add_test(tc1_1, mul_2);
    tcase_add_test(tc1_1, mul_3);
    tcase_add_test(tc1_1, mul_4);
    tcase_add_test(tc1_1, mul_uncommon_values);
    tcase_add_test(tc1_1, mul_test_complex);
    tcase_add_test(tc1_1, round_test_complex);

    tcase_add_test(tc1_1, nan_test);
    tcase_add_test(tc1_1, mult_test_1);
    tcase_add_test(tc1_1, mult_test_2);
    tcase_add_test(tc1_1, mult_test_3);
    tcase_add_test(tc1_1, mult_test_4);
    tcase_add_test(tc1_1, mult_test_5);
    tcase_add_test(tc1_1, mult_test_6);
    tcase_add_test(tc1_1, mult_test_7);
    tcase_add_test(tc1_1, mult_test_8);
    tcase_add_test(tc1_1, mult_test_9);
    tcase_add_test(tc1_1, mult_test_10);
    tcase_add_test(tc1_1, mult_test_11);
    tcase_add_test(tc1_1, mult_test_12);
    tcase_add_test(tc1_1, mult_test_13);
    tcase_add_test(tc1_1, mult_test_14);
    tcase_add_test(tc1_1, mult_test_15);
    tcase_add_test(tc1_1, mult_test_16);
    tcase_add_test(tc1_1, mult_test_17);
    tcase_add_test(tc1_1, mult_test_18);
    tcase_add_test(tc1_1, mult_test_19);
    tcase_add_test(tc1_1, mult_test_20);
    tcase_add_test(tc1_1, mult_test_21);
    tcase_add_test(tc1_1, mult_test_22);


    tcase_add_test(tc1_1, round_complex_test_1);
    tcase_add_test(tc1_1, round_complex_test_2);
    tcase_add_test(tc1_1, round_complex_test_3);
    tcase_add_test(tc1_1, round_complex_test_4);
    tcase_add_test(tc1_1, round_complex_test_5);
    tcase_add_test(tc1_1, round_complex_test_6);
    tcase_add_test(tc1_1, round_complex_test_7);
    tcase_add_test(tc1_1, round_complex_test_8);
    tcase_add_test(tc1_1, round_complex_test_9);
    tcase_add_test(tc1_1, round_complex_test_10);
    tcase_add_test(tc1_1, round_complex_test_11);
    tcase_add_test(tc1_1, round_complex_test_12);
    tcase_add_test(tc1_1, round_complex_test_13);
    tcase_add_test(tc1_1, round_complex_test_14);
    tcase_add_test(tc1_1, round_complex_test_15);
    tcase_add_test(tc1_1, round_complex_test_16);
    tcase_add_test(tc1_1, round_complex_test_17);
    tcase_add_test(tc1_1, round_complex_test_18);
    tcase_add_test(tc1_1, round_complex_test_19);
    tcase_add_test(tc1_1, round_complex_test_20);
    tcase_add_test(tc1_1, round_complex_test_21);
    tcase_add_test(tc1_1, round_complex_test_22);
    tcase_add_test(tc1_1, round_complex_test_23);
    tcase_add_test(tc1_1, round_complex_test_24);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
