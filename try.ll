; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

@0 = private unnamed_addr constant [3 x i8] c"%d\00"
@1 = private unnamed_addr constant [3 x i8] c"%c\00"

define i64 @main() {
entry:
  %n = alloca i64
  store i64 5, i64* %n
  %i = alloca i64
  store i64 0, i64* %i
  br label %loop_header

loop_body:                                        ; preds = %loop_header
  %j = alloca i64
  store i64 0, i64* %j
  br label %loop_header6

after_loop:                                       ; preds = %loop_header
  ret i64 0

loop_header:                                      ; preds = %after_loop5, %entry
  %tmp = load i64, i64* %n
  %0 = call i64 @pow(i64 2, i64 %tmp)
  %tmp1 = load i64, i64* %i
  %tmp2 = icmp slt i64 %tmp1, %0
  %zext = zext i1 %tmp2 to i64
  %tmp3 = icmp ne i64 %zext, 0
  br i1 %tmp3, label %loop_body, label %after_loop

loop_body4:                                       ; preds = %loop_header6
  %k = alloca i64
  store i64 0, i64* %k
  %tmp12 = load i64, i64* %j
  %1 = call i64 @pow(i64 2, i64 %tmp12)
  %tmp13 = load i64, i64* %i
  %tmp14 = sdiv i64 %tmp13, %1
  store i64 %tmp14, i64* %k
  %tmp15 = load i64, i64* %k
  %tmp16 = srem i64 %tmp15, 2
  %tmp17 = icmp eq i64 %tmp16, 1
  %zext18 = zext i1 %tmp17 to i64
  %tmp19 = icmp ne i64 %zext18, 0
  br i1 %tmp19, label %then, label %else

after_loop5:                                      ; preds = %loop_header6
  %printf23 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0), i8 10)
  %load24 = load i64, i64* %i
  %tmp25 = add i64 %load24, 1
  store i64 %tmp25, i64* %i
  br label %loop_header

loop_header6:                                     ; preds = %after, %loop_body
  %tmp7 = load i64, i64* %n
  %tmp8 = load i64, i64* %j
  %tmp9 = icmp slt i64 %tmp8, %tmp7
  %zext10 = zext i1 %tmp9 to i64
  %tmp11 = icmp ne i64 %zext10, 0
  br i1 %tmp11, label %loop_body4, label %after_loop5

then:                                             ; preds = %loop_body4
  %tmp20 = load i64, i64* %j
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i64 %tmp20)
  %printf21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0), i8 32)
  br label %after

else:                                             ; preds = %loop_body4
  br label %after

after:                                            ; preds = %else, %then
  %load = load i64, i64* %j
  %tmp22 = add i64 %load, 1
  store i64 %tmp22, i64* %j
  br label %loop_header6
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
