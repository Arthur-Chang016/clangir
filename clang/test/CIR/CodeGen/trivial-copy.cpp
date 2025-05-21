// RUN:   %clang_cc1 -triple x86_64-unknown-linux-gnu -fclangir -emit-cir %s -o - \
// RUN:   | FileCheck %s

struct Trivial {
  int i;
};

void f(Trivial &a) { Trivial b(a); }

// CHECK:         cir.copy
// CHECK-NOT:     call
// CHECK-NOT:     cir.call{{.*}}_ZN7TrivialC2ERKS_
// CHECK-NOT:     cir.func{{.*}}_ZN7TrivialC2ERKS_
