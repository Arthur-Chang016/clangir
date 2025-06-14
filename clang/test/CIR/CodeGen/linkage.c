// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -fclangir -emit-cir %s -o %t-O0.cir
// RUN: FileCheck --input-file=%t-O0.cir %s -check-prefixes=CIR,CIR-O0
// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -fclangir -emit-cir %s -O1 -o %t-O1.cir
// RUN: FileCheck --input-file=%t-O1.cir %s -check-prefixes=CIR,CIR-O1
// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -fclangir -emit-llvm %s -o %t.ll
// RUN: FileCheck --input-file=%t.ll %s -check-prefix=LLVM


static int bar(int i) {
  return i;
}

int foo(void) {
  return bar(5);
}

// CIR:   cir.func internal private dso_local @bar(
// CIR:   cir.func dso_local @foo(

// LLVM: define internal i32 @bar(
// LLVM: define dso_local i32 @foo(

static int var = 0;
// CIR: cir.global "private" internal dso_local @var = #cir.int<0> : !s32i
int get_var(void) {
  return var;
}

// Should generate available_externally linkage when optimizing.
inline int availableExternallyMethod(void) { return 0; }
void callAvailableExternallyMethod(void) { availableExternallyMethod(); }
// CIR-O0-NOT: cir.func available_externally @availableExternallyMethod
// CIR-O1:     cir.func available_externally @availableExternallyMethod
