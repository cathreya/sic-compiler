; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

@0 = private unnamed_addr constant [3 x i8] c"%d\00"
@1 = private unnamed_addr constant [3 x i8] c"%c\00"

define i64 @main() {
entry:
  %N = alloca i64
  store i64 5, i64* %N
  %k = alloca i64
  store i64 2, i64* %k
  %ans = alloca i64
  %tmp = load i64, i64* %N
  %tmp1 = load i64, i64* %k
  %0 = call i64 @g(i64 %tmp, i64 %tmp1)
  store i64 %0, i64* %ans
  %tmp2 = load i64, i64* %ans
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i64 %tmp2)
  ret i64 0
}

declare i32 @printf(i8*, ...)

define internal i64 @pow(i64 %base, i64 %expo) {
body:
  %base1 = alloca i64
  store i64 %base, i64* %base1
  %expo2 = alloca i64
  store i64 %expo, i64* %expo2
  %prod = alloca i64
  store i64 0, i64* %prod
  store i64 1, i64* %prod
  %i = alloca i64
  store i64 0, i64* %i
  br label %loop_header

loop_body:                                        ; preds = %loop_header
  %tmp6 = load i64, i64* %base1
  %tmp7 = load i64, i64* %prod
  %tmp8 = mul i64 %tmp7, %tmp6
  store i64 %tmp8, i64* %prod
  %load = load i64, i64* %i
  %tmp9 = add i64 %load, 1
  store i64 %tmp9, i64* %i
  br label %loop_header

after_loop:                                       ; preds = %loop_header
  %tmp10 = load i64, i64* %prod
  ret i64 %tmp10

loop_header:                                      ; preds = %loop_body, %body
  %tmp = load i64, i64* %expo2
  %tmp3 = load i64, i64* %i
  %tmp4 = icmp slt i64 %tmp3, %tmp
  %zext = zext i1 %tmp4 to i64
  %tmp5 = icmp ne i64 %zext, 0
  br i1 %tmp5, label %loop_body, label %after_loop
}

define internal i64 @g(i64 %n, i64 %k) {
body:
  %n1 = alloca i64
  store i64 %n, i64* %n1
  %k2 = alloca i64
  store i64 %k, i64* %k2
  %sum = alloca i64
  store i64 0, i64* %sum
  store i64 0, i64* %sum
  %i = alloca i64
  store i64 0, i64* %i
  br label %loop_header

loop_body:                                        ; preds = %loop_header
  %tmp6 = load i64, i64* %i
  %tmp7 = load i64, i64* %k2
  %0 = call i64 @pow(i64 %tmp6, i64 %tmp7)
  %load = load i64, i64* %sum
  %tmp8 = add i64 %load, %0
  store i64 %tmp8, i64* %sum
  %load9 = load i64, i64* %i
  %tmp10 = add i64 %load9, 1
  store i64 %tmp10, i64* %i
  br label %loop_header

after_loop:                                       ; preds = %loop_header
  %tmp11 = load i64, i64* %sum
  ret i64 %tmp11

loop_header:                                      ; preds = %loop_body, %body
  %tmp = load i64, i64* %n1
  %tmp3 = load i64, i64* %i
  %tmp4 = icmp slt i64 %tmp3, %tmp
  %zext = zext i1 %tmp4 to i64
  %tmp5 = icmp ne i64 %zext, 0
  br i1 %tmp5, label %loop_body, label %after_loop
}
