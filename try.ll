; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

@0 = private unnamed_addr constant [3 x i8] c"%d\00"
@1 = private unnamed_addr constant [3 x i8] c"%c\00"
@a = common global [1000 x i64] zeroinitializer

define i64 @main() {
entry:
  %n = alloca i64
  store i64 5, i64* %n
  %tmp = load [1000 x i64], [1000 x i64]* @a
  %tmp1 = load i64, i64* %n
  call void @insertionSort([1000 x i64] %tmp, i64 %tmp1)
  %i = alloca i64
  store i64 0, i64* %i
  br label %loop_header

loop_body:                                        ; preds = %loop_header
  %tmp6 = load i64, i64* %i
  %0 = extractelement [1000 x i64]* @a, i64 %tmp6
  %load = load i64, [1000 x i64] %0
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i64 %load)
  %printf7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0), i8 32)
  %load8 = load i64, i64* %i
  %tmp9 = add i64 %load8, 1
  store i64 %tmp9, i64* %i
  br label %loop_header

after_loop:                                       ; preds = %loop_header
  %printf10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0), i8 10)
  ret i64 0

loop_header:                                      ; preds = %loop_body, %entry
  %tmp2 = load i64, i64* %n
  %tmp3 = load i64, i64* %i
  %tmp4 = icmp slt i64 %tmp3, %tmp2
  %zext = zext i1 %tmp4 to i64
  %tmp5 = icmp ne i64 %zext, 0
  br i1 %tmp5, label %loop_body, label %after_loop
}

declare i32 @printf(i8*, ...)

define internal void @insertionSort([1000 x i64] %arr, i64 %n) {
body:
  %n1 = alloca i64
  store i64 %n, i64* %n1
  %i = alloca i64
  store i64 0, i64* %i
  %key = alloca i64
  store i64 0, i64* %key
  %j = alloca i64
  store i64 0, i64* %j
  ret void
}
