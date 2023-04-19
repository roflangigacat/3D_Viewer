#include <stdio.h>

#include "MyString.h"
#include "check.h"
#include "parce.h"
#include "stack.h"

double FLAG_V[] = {1.0000,    2.0000,    3.0000,    -123.321,  -35.454,
                   -4.0000,   1.94,      3.897,     1.1,       3.374600,
                   30.095299, 7.841400,  3.553400,  29.251499, 7.841400,
                   3.374600,  29.251499, 7.841400,  3.553400,  29.123299,
                   7.841400,  3.374600,  29.123299, 7.841400};
int FLAG_F[] = {73,     54,     54,     72,     72,     73,     54,
                52,     52,     72,     72,     54,     196843, 196844,
                196844, 196838, 196838, 196839, 196839, 196843};

START_TEST(vflags_test) {
  Stack_t *number = NULL;
  Stack_t *fnumber = NULL;
  Vvalue Vflags = VvalueConstruct();
  char fileWay[512] = "./objects/testingfile.txt";
  int len = 0;
  parsingFile(fileWay, &number, &fnumber, &Vflags);
  Data *arr = getAllValue(&number, &len);
  for (int i = 0; i < len; ++i) {
    printf("FLAGV %lf, parse %lf\n", arr[i].DValue, FLAG_V[i]);
    ck_assert_double_eq(arr[i].DValue, FLAG_V[i]);
  }
  free(arr);
  StackDelete(&number);
  StackDelete(&fnumber);
}
END_TEST

START_TEST(fflags_test) {
  Stack_t *number = NULL;
  Stack_t *fnumber = NULL;
  Vvalue Vflags = VvalueConstruct();
  char fileWay[512] = "./objects/testingfile.txt";
  int len = 0;
  parsingFile(fileWay, &number, &fnumber, &Vflags);
  Data *arr = getAllValue(&fnumber, &len);
  for (int i = 0; i < len; ++i) {
    printf("FLAGF %lf, parse %lf\n", arr[i].DValue, FLAG_F[i]);
    ck_assert_int_eq(arr[i].IValue, FLAG_F[i]);
  }
  free(arr);
  StackDelete(&number);
  StackDelete(&fnumber);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  //  ENTER CONTAINER
  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, vflags_test);
  tcase_add_test(tc1_1, fflags_test);
  //
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
