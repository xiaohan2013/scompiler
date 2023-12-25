// mypass.cpp

#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/raw_ostream.h"

#include <iostream>

using namespace llvm;

namespace name
{
    class MyPass : public PassInfoMixin<MyPass>
    {
    public:
        PreservedAnalyses run(Function& function, FunctionAnalysisManager& analysisManager)
        {
            std::out << "MyPass in function: " << function.getName().str() << std::endl;
            // here goes what you want to do with a pass
            // Assuming we did not change anything of the IR code
            return PreservedAnalyses::all();
        }
    };
} // namespace name


extern "C" PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK llvmGetPassPluginInfo()
{
    return 
    {
        LLVM_PLUGIN_API_VERSION,
        "MyPass",
        "v0.1",
        [](PassBuilder &passBuilder) {
            passBuilder.registerPipelineParsingCallback(
                [](StringRef name, FunctionPassManager &passManager, ArrayRef<PassBuilder::PipelineElement>) {
                    if(name == "my-pass") {
                        passManager.addPass(MyPass());
                        return true;
                    }

                    return false;
                }
            );
        }
    };
}