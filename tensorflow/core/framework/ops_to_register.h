#ifndef OPS_TO_REGISTER
#define OPS_TO_REGISTER
constexpr inline bool ShouldRegisterOp(const char op[]) {
  return false
     || (strcmp(op, "Add") == 0)
     || (strcmp(op, "ConcatV2") == 0)
     || (strcmp(op, "Const") == 0)
     || (strcmp(op, "Identity") == 0)
     || (strcmp(op, "MatMul") == 0)
     || (strcmp(op, "Mul") == 0)
     || (strcmp(op, "NoOp") == 0)
     || (strcmp(op, "Placeholder") == 0)
     || (strcmp(op, "Pow") == 0)
     || (strcmp(op, "RandomUniform") == 0)
     || (strcmp(op, "Range") == 0)
     || (strcmp(op, "Rank") == 0)
     || (strcmp(op, "RealDiv") == 0)
     || (strcmp(op, "Reshape") == 0)
     || (strcmp(op, "Split") == 0)
     || (strcmp(op, "Sqrt") == 0)
     || (strcmp(op, "Square") == 0)
     || (strcmp(op, "Sub") == 0)
     || (strcmp(op, "Sum") == 0)
     || (strcmp(op, "Transpose") == 0)
     || (strcmp(op, "_Recv") == 0)
     || (strcmp(op, "_Send") == 0)
  ;
}
#define SHOULD_REGISTER_OP(op) ShouldRegisterOp(op)


    namespace {
      constexpr const char* skip(const char* x) {
        return (*x) ? (*x == ' ' ? skip(x + 1) : x) : x;
      }

      constexpr bool isequal(const char* x, const char* y) {
        return (*skip(x) && *skip(y))
                   ? (*skip(x) == *skip(y) && isequal(skip(x) + 1, skip(y) + 1))
                   : (!*skip(x) && !*skip(y));
      }

      template<int N>
      struct find_in {
        static constexpr bool f(const char* x, const char* const y[N]) {
          return isequal(x, y[0]) || find_in<N - 1>::f(x, y + 1);
        }
      };

      template<>
      struct find_in<0> {
        static constexpr bool f(const char* x, const char* const y[]) {
          return false;
        }
      };
    }  // end namespace
    constexpr const char* kNecessaryOpKernelClasses[] = {
"BinaryOp< CPUDevice, functor::add<float>>",
"ConcatV2Op<CPUDevice, float>",
"ConstantOp",
"IdentityOp",
"MatMulOp<CPUDevice, float, false >",
"BinaryOp< CPUDevice, functor::mul<float>>",
"NoOp",
"PlaceholderOp",
"BinaryOp< CPUDevice, functor::pow<float>>",
"PhiloxRandomOp<CPUDevice, random::UniformDistribution< random::PhiloxRandom, float> >",
"RangeOp<::tensorflow::int32>",
"RankOp",
"BinaryOp< CPUDevice, functor::div<float>>",
"ReshapeOp",
"SplitOpCPU<float>",
"UnaryOp< CPUDevice, functor::sqrt<float>>",
"UnaryOp< CPUDevice, functor::square<float>>",
"BinaryOp< CPUDevice, functor::sub<float>>",
"BinaryOp< CPUDevice, functor::sub<int32>>",
"ReductionOp<CPUDevice, float, Eigen::internal::SumReducer<float>>",
"TransposeCpuOp",
"RecvOp",
"SendOp",
};
#define SHOULD_REGISTER_OP_KERNEL(clz) (find_in<sizeof(kNecessaryOpKernelClasses) / sizeof(*kNecessaryOpKernelClasses)>::f(clz, kNecessaryOpKernelClasses))

#define SHOULD_REGISTER_OP_GRADIENT false
#endif
