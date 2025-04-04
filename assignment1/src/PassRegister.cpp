#include <llvm/Passes/PassPlugin.h>
#include <llvm/Passes/PassBuilder.h>
#include "assignment1.hpp"

using namespace llvm;
//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------
llvm::PassPluginLibraryInfo getAssignmentPassPluginInfo()
{
  return {LLVM_PLUGIN_API_VERSION, "Assignment", LLVM_VERSION_STRING,
          [](PassBuilder &PB)
          {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>)
                {
                  if (Name == "algebraic-identity")
                  {
                    FPM.addPass(assignment1::AlgebraicIdentity());
                    return true;
                  }
                  if (Name == "strength-reduction")
                  {
                    FPM.addPass(assignment1::StrengthReduction());
                    return true;
                  }
                  if (Name == "multi-instruction-optimization")
                  {
                    FPM.addPass(assignment1::MultiInstructionOptimization());
                    return true;
                  }
                  return false;
                });
          }};
}

// This is the core interface for pass plugins. It guarantees that 'opt' will
// be able to recognize TestPass when added to the pass pipeline on the
// command line, i.e. via '-passes=test-pass'
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo()
{
  return getAssignmentPassPluginInfo();
}