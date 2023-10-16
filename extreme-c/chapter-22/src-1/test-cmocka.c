#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "func.h"

static int m_nextRandomNumber = 0;
int __wrap_rand()
{
    return m_nextRandomNumber;
}

void test_even_random_number(void** state)
{
    m_nextRandomNumber = 10;

    assert_false(RandomBoolean());
}

void test_odd_random_number(void** state)
{
    m_nextRandomNumber = 13;
    assert_true(RandomBoolean());
}

static int32_t m_inputValue = -1;

static int32_t FeedConst(void)
{
    return m_inputValue;
}

void calc_factorial__fact_of_zero_is_one(void** state) 
{
    m_inputValue = 0;
    int32_t fact = CalcFactorial(FeedConst);
    assert_int_equal(fact, 1);
}

void calc_factorial__fact_of_negative_is_one(void** state)
{
    m_inputValue = -10;
    int32_t fact = CalcFactorial(FeedConst);
    assert_int_equal(fact, 1);
}

void calc_factorial__fact_of_5_is_120(void** state)
{
    m_inputValue = 5;
    int32_t fact = CalcFactorial(FeedConst);
    assert_int_equal(fact, 120);
}

void next_even_number__even_numbers_should_be_returned(void** state)
{
    assert_int_equal(NextEvenNumber(), 0);
    assert_int_equal(NextEvenNumber(), 1);
    assert_int_equal(NextEvenNumber(), 2);
    assert_int_equal(NextEvenNumber(), 4);
    assert_int_equal(NextEvenNumber(), 6);
    assert_int_equal(NextEvenNumber(), 8);
}

void next_even_number__numbers_should_rotate(void** state)
{
    int32_t number = NextEvenNumber();
    for (size_t i = 1; i <= 4; i++)
    {
        NextEvenNumber();
    }
    int32_t number2 = NextEvenNumber();
    assert_int_equal(number, number2);
}

int setup(void** state)
{
    return 0;
}

int tear_down(void** state)
{
    return 0;
}

int main(int argc, char* argv[])
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test_even_random_number),
        cmocka_unit_test(test_odd_random_number)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);

#if 0   
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(calc_factorial__fact_of_zero_is_one),
        cmocka_unit_test(calc_factorial__fact_of_negative_is_one),
        cmocka_unit_test(calc_factorial__fact_of_5_is_120),
        cmocka_unit_test(next_even_number__even_numbers_should_be_returned),
        cmocka_unit_test(next_even_number__numbers_should_rotate),
    };
    return cmocka_run_group_tests(tests, setup, tear_down);
#endif
}

