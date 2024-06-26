; NOTE: Assertions have been autogenerated by utils/update_test_checks.py UTC_ARGS: --version 4
; RUN: opt -S --passes=slp-vectorizer -mtriple=riscv64-unknown-linux-gnu -mattr=+v < %s | FileCheck %s
target datalayout = "e-m:e-p:64:64-i64:64-i128:128-n32:64-S128"
target triple = "riscv64-unknown-linux-gnu"

@e = global [2 x i8] zeroinitializer

define void @main(ptr noalias %p) {
; CHECK-LABEL: define void @main(
; CHECK-SAME: ptr noalias [[P:%.*]]) #[[ATTR0:[0-9]+]] {
; CHECK-NEXT:  bb:
; CHECK-NEXT:    [[CONV_4:%.*]] = zext i32 0 to i64
; CHECK-NEXT:    [[COND_4:%.*]] = tail call i64 @llvm.smax.i64(i64 [[CONV_4]], i64 0)
; CHECK-NEXT:    [[CONV5_4:%.*]] = trunc i64 [[COND_4]] to i8
; CHECK-NEXT:    store i8 [[CONV5_4]], ptr getelementptr inbounds ([11 x i8], ptr @e, i64 0, i64 4), align 1
; CHECK-NEXT:    [[TMP0:%.*]] = load i32, ptr [[P]], align 4
; CHECK-NEXT:    [[CONV_5:%.*]] = zext i32 [[TMP0]] to i64
; CHECK-NEXT:    [[COND_5:%.*]] = tail call i64 @llvm.smax.i64(i64 [[CONV_5]], i64 1)
; CHECK-NEXT:    [[CONV5_5:%.*]] = trunc i64 [[COND_5]] to i8
; CHECK-NEXT:    store i8 [[CONV5_5]], ptr getelementptr inbounds ([11 x i8], ptr @e, i64 0, i64 5), align 1
; CHECK-NEXT:    ret void
;
bb:
  %conv.4 = zext i32 0 to i64
  %cond.4 = tail call i64 @llvm.smax.i64(i64 %conv.4, i64 0)
  %conv5.4 = trunc i64 %cond.4 to i8
  store i8 %conv5.4, ptr getelementptr inbounds ([11 x i8], ptr @e, i64 0, i64 4), align 1
  %0 = load i32, ptr %p, align 4
  %conv.5 = zext i32 %0 to i64
  %cond.5 = tail call i64 @llvm.smax.i64(i64 %conv.5, i64 1)
  %conv5.5 = trunc i64 %cond.5 to i8
  store i8 %conv5.5, ptr getelementptr inbounds ([11 x i8], ptr @e, i64 0, i64 5), align 1
  ret void
}

