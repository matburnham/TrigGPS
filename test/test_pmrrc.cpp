#include <gtest/gtest.h>

#include "pmrrc.h"
#include "string.h"

// TODO: add additional tests from the other document

TEST(PMRRC, ChecksumMeetsSpec1)
{
  // Spec indicates the following
  // $PMRRC041SLE<space>99<cr>
  // i.e. data: "041SLE<space>"
  //  checksum: "99"
  char calc[3] = {0};
  char data[] = "041SLE ";

  checksum(data, strlen(data), calc);  
  ASSERT_STREQ("99", calc);
}

TEST(PMRRC, ChecksumMeetsSpec2)
{
  // Spec indicates the following
  // $PMRRC0511IT64
  // i.e. data: "0511IT"
  //  checksum: "64"  

  char calc[3] = {0};
  char data[] = "0511IT";
  
  checksum(data, strlen(data), calc);
  ASSERT_STREQ("64", calc);
}

TEST(PMRRC, StrCatC)
{
  char str[] = "abcd";
  char c = '1';
  
  strcat_c(str, c);
  ASSERT_STREQ("abcd1", str);
}

TEST(PMRRC, remoteIdentMessageMeetSpec)
{
  // Spec indicates the following to set "SLE " as ICAO code:
  // $PMRRC041SLE<space>99<cr>

  char msg[20] = {0};
  remoteIdentInput(1, "SLE ", msg);
  ASSERT_STREQ("$PMRRC041SLE 99\r\n", msg);
}

TEST(PMRRC, pmrrc_setRemoteFreqListMeetsSpec)
{
  char msg[20] = {0};
  setRemoteFreqList(1, '1', 'I', 'T', msg);
  ASSERT_STREQ("$PMRRC0511IT64\r\n", msg);
}
