//===-- Unittests for feclearexcept with exceptions enabled ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "src/fenv/feclearexcept.h"

#include "src/__support/FPUtil/FEnvImpl.h"
#include "test/UnitTest/Test.h"

#include "hdr/fenv_macros.h"
#include <stdint.h>

TEST(LlvmLibcFEnvTest, ClearTest) {
  uint16_t excepts[] = {FE_DIVBYZERO, FE_INVALID, FE_INEXACT, FE_OVERFLOW,
                        FE_UNDERFLOW};
  LIBC_NAMESPACE::fputil::disable_except(FE_ALL_EXCEPT);
  LIBC_NAMESPACE::fputil::clear_except(FE_ALL_EXCEPT);

  for (uint16_t e : excepts)
    ASSERT_EQ(LIBC_NAMESPACE::fputil::test_except(e), 0);

  LIBC_NAMESPACE::fputil::raise_except(FE_ALL_EXCEPT);

  for (uint16_t e1 : excepts) {
    for (uint16_t e2 : excepts) {
      for (uint16_t e3 : excepts) {
        for (uint16_t e4 : excepts) {
          for (uint16_t e5 : excepts) {
            // We clear one exception and test to verify that it was cleared.
            LIBC_NAMESPACE::feclearexcept(e1 | e2 | e3 | e4 | e5);
            ASSERT_EQ(
                LIBC_NAMESPACE::fputil::test_except(e1 | e2 | e3 | e4 | e5), 0);
            // After clearing, we raise the exception again.
            LIBC_NAMESPACE::fputil::raise_except(e1 | e2 | e3 | e4 | e5);
          }
        }
      }
    }
  }
}
