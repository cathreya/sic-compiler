./codegen Programs/$1.sic > $1.ll &&
llc $1.ll  &&
clang-9 $1.s -o $1 &&
./$1