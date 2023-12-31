#include "IRGenerator.h"

#include "llvm/ADT/StringMap.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;
namespace {
    class IRGeneratorImplementation: public ASTVisitor {
        Module* module;
        IRBuilder<> builder;
        Type* voidType;
        Type* int32Type;
        Type* int8PtrType;
        Type* int8PtrPtrType;
        Constant* int32Zero;

        Value* value;
        StringMap<Value*> nameMap;
    public:
        IRGeneratorImplementation(Module* inModule): module(inModule), builder(inModule->getContext()) {
            voidType = Type::getVoidTy(module->getContext());
            int32Type = Type::getInt32Ty(module->getContext());
            int8PtrType = Type::getInt8PtrTy(module->getContext());
            int8PtrPtrType = int8PtrType->getPointerTo();
            int32Zero = ConstantInt::get(int32Type, 0, true);
        }

        void Generate(AST* tree) {
            FunctionType* mainFunctionType = FunctionType::get(int32Type, {int32Type, int8PtrPtrType}, false);
            Function* mainFunction = Function::Create(mainFunctionType, GlobalValue::ExternalLinkage, "main", module);
            BasicBlock* basicBlock = BasicBlock::Create(module->getContext(), "entry", mainFunction);
            builder.SetInsertPoint(basicBlock);

            tree->Accept(*this);

            FunctionType* calculatorWriteFunctionType = FunctionType::get(voidType, {int32Type}, false);
            Function* calculatorWriteFunction =
                Function::Create(calculatorWriteFunctionType, GlobalValue::ExternalLinkage, "calc_write", module);
            builder.CreateCall(calculatorWriteFunctionType, calculatorWriteFunction, {value});

            builder.CreateRet(int32Zero);
        }

        void Visit(Factor& node) override {
            if(node.GetType() == Factor::kIdent) {
                value = nameMap[node.GetVal()];
            } else {
                int intValue;
                node.GetVal().getAsInteger(10, intValue);
                value = ConstantInt::get(int32Type, intValue, true);
            }
        };

        void Visit(BinaryOp& node) override {
            node.GetLeft()->Accept(*this);
            Value* left = value;

                        node.GetRight()->Accept(*this);
            Value* right = value;

            switch (node.GetOperator())
            {
            case BinaryOp::kPlus:
                value = builder.CreateNSWAdd(left, right);
                break;

            case BinaryOp::kMinus:
                value = builder.CreateNSWSub(left, right);
                break;

            case BinaryOp::kMultiple:
                value = builder.CreateNSWMul(left, right);
                break;

            case BinaryOp::kDivide:
                value = builder.CreateSDiv(left, right);
                break;
            }

        };
    
        void Visit(WithDeclaration& node) override
        {
            FunctionType* calculatorReadFunctionType = FunctionType::get(int32Type, {int8PtrType}, false);
            Function* calculatorReadFunction =
                Function::Create(calculatorReadFunctionType, GlobalValue::ExternalLinkage, "calc_read", module);
            for (const auto& variable : node)
            {
                // Create call to calc_read function
                // GlobalVariable(Module &M, Type *Ty, bool isConstant, LinkageTypes Linkage,
                //     Constant *Initializer, const Twine &Name = "",
                //     GlobalVariable *InsertBefore = nullptr,
                //     ThreadLocalMode = NotThreadLocal,
                //     std::optional<unsigned> AddressSpace = std::nullopt,
                //     bool isExternallyInitialized = false);

                Constant* strText = ConstantDataArray::getString(module->getContext(), variable);
                GlobalVariable* str = new GlobalVariable(*module,
                                                         strText->getType(),
                                                         /*isConstant=*/true,
                                                         GlobalValue::PrivateLinkage,
                                                         strText,
                                                         Twine(variable).concat(".str"));
                // const allocation = builder.createAlloca(
                //     llvm.ArrayType.get(llvm.Type.getInt32Ty(module->getContext()), 5),
                //     llvm.ConstantInt.get(module->getContext(), 5)
                // );
                // Value* ptr = builder.CreateInBoundsGEP(str, {int32Zero, int32Zero}, "ptr");
                // Value *CreateInBoundsGEP(Type *Ty, Value *Ptr, ArrayRef<Value *> IdxList,
                //            const Twine &Name = "") {
                Value* ptr = builder.CreateInBoundsGEP(strText->getType(), strText, {int32Zero, int32Zero}, "ptr");
                CallInst* call = builder.CreateCall(calculatorReadFunctionType, calculatorReadFunction, {ptr});

                nameMap[variable] = call;
            }

            node.GetExpr()->Accept(*this);
        };
    };
}

void IRGenerator::Generate(AST* ast) {
    LLVMContext context;
    Module* module = new Module("calc.expr", context);
    IRGeneratorImplementation generator(module);
    generator.Generate(tree);
    module->print(outs(), nullptr);
}