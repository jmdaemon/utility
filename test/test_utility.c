#include "utility.h"
#include "unity.h"

#define PDT (+5)

void setUp(void) {
    /* set stuff up here */
}

void tearDown(void) {
    /* clean stuff up here */
}

void ltimestamp_should_return_correct_time() {
    // Set the local time zone
    /*tzset();*/
    // Get the current time
    /*struct tm date;*/
    /*date.tm_isdst = 0;*/

    /*time_t utc = mktime(&date);*/
    /*time_t local = utc - timezone + (daylight?3600:0);*/
    /*date = *localtime(&local);*/

    /*time_t rawtime = get_time();*/
    /*struct tm * ptm;*/
    /*ptm = gmtime (&rawtime);*/

    /*const char* result = ltimestamp(rawtime);*/
    /*char* expect = (char*)malloc(6 * sizeof(char));*/

    /*sprintf (expect, "%2d:%02d", (ptm->tm_hour+PDT)%24, ptm->tm_min);*/
    /*sprintf(expect, "%2d:%02d", (ptm->tm_hour)%24, ptm->tm_min);*/
    /*sprintf(expect, "%2d:%02d", date.tm_hour%24, date.tm_min);*/
    /*sprintf(expect, "%2d:%02d", (to24hour(ptm))%24, ptm->tm_min);*/
    /*printf("Timestamp Expect: %s\n", expect);*/
    /*printf("Timestamp Actual: %s\n", result);*/

      time_t t = time(NULL);
      struct tm lt = {0};

      localtime_r(&t, &lt);

      char* expect = (char*)malloc(5 * sizeof(char));
      sprintf(expect, "%2d:%02d", lt.tm_hour, lt.tm_min);

      printf("Offset to GMT is %lds.\n", lt.tm_gmtoff);
      printf("The time zone is '%s'.\n", lt.tm_zone);
      printf("Time: %2d:%02d.\n", lt.tm_hour, lt.tm_min);

      time_t rawtime = get_time();
      const char* result = ltimestamp(rawtime);

      TEST_ASSERT_EQUAL_STRING(expect, result);

  /*const std::time_t epoch_plus_11h = 60 * 60 * 11;*/
  /*const int local_time = localtime(&epoch_plus_11h)->tm_hour;*/
  /*const int gm_time = gmtime(&epoch_plus_11h)->tm_hour;*/
  /*const int tz_diff = local_time - gm_time;*/

    /*TEST_ASSERT_EQUAL_STRING(expect, result);*/
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(ltimestamp_should_return_correct_time);
    return UNITY_END();
}
