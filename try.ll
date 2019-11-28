; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00"

declare i32 @printf(i8*, ...)

define i64 @main() {
entry:
  %i = alloca i64
  store i64 0, i64* %i
  store i64 0, i64* %i
  br label %loop_header

loop_body:                                        ; preds = %loop_header
  %tmp3 = load i64, i64* %i
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0), i64 %tmp3)
  %load = load i64, i64* %i
  %tmp4 = add i64 %load, 1
  store i64 %tmp4, i64* %i
  br label %loop_header

after_loop:                                       ; preds = %loop_header
  ret i64 0

loop_header:                                      ; preds = %loop_body, %entry
  %tmp = load i64, i64* %i
  %tmp1 = icmp slt i64 %tmp, 10
  %zext = zext i1 %tmp1 to i64
  %tmp2 = icmp ne i64 %zext, 0
  br i1 %tmp2, label %loop_body, label %after_loop
}
