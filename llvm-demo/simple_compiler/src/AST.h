#pragma once

#ifndef AST_H
#define AST_H

#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"

class AST;
class Expr;
class Factor;
class BinaryOp;
class WithDeclaration;

class ASTVisitor
{
public:

    virtual void Visit(AST&)
    {
    }

    virtual void Visit(Expr&)
    {
    }

    virtual void Visit(Factor&) {};
    virtual void Visit(BinaryOp&) {};
    virtual void Visit(WithDeclaration&) {};
};

class AST
{
public:

    virtual ~AST()
    {
    }

    virtual void Accept(ASTVisitor& visitor) = 0;
};

class Expr : public AST
{
public:

    Expr()
    {
    }
};

class Factor : public Expr
{
public:

    enum ValueType
    {
        kIdent,
        kNumber
    };

private:

    ValueType type;
    llvm::StringRef value;

public:

    Factor(ValueType inType, llvm::StringRef inVal) :
        type(inType),
        value(inVal)
    {
    }

    ValueType GetType()
    {
        return type;
    }

    llvm::StringRef GetVal()
    {
        return value;
    }

    virtual void Accept(ASTVisitor& visitor) override
    {
        visitor.Visit(*this);
    }
};

class BinaryOp : public Expr
{
public:

    enum Operator
    {
        kPlus,
        kMinus,
        kMultiple,
        kDivide
    };

private:

    Expr* left;
    Expr* right;
    Operator op;

public:

    BinaryOp(Operator inOp, Expr* inLeftExpr, Expr* inRightExpr) :
        op(inOp),
        left(inLeftExpr),
        right(inRightExpr)
    {
    }

    Expr* GetLeft()
    {
        return left;
    }

    Expr* GetRight()
    {
        return right;
    }

    Operator GetOperator()
    {
        return op;
    }

    virtual void Accept(ASTVisitor& visitor) override
    {
        visitor.Visit(*this);
    }

    std::string GetDisplayText() const
    {
        switch (op)
        {
        case kPlus:
            return "+";

        case kMinus:
            return "-";

        case kMultiple:
            return "*";

        case kDivide:
            return "/";

        default:
            break;
        }

        return "";
    }
};

class WithDeclaration : public AST
{
    using VariableVector = llvm::SmallVector<llvm::StringRef, 8>;

public:

    WithDeclaration(llvm::SmallVector<llvm::StringRef, 8> inVars, Expr* inExpr) :
        variables(inVars),
        expr(inExpr)
    {
    }

    VariableVector::const_iterator begin()
    {
        return variables.begin();
    }

    VariableVector::const_iterator end()
    {
        return variables.end();
    }

    Expr* GetExpr()
    {
        return expr;
    }

    virtual void Accept(ASTVisitor& visitor) override
    {
        visitor.Visit(*this);
    }

private:

    VariableVector variables;
    Expr* expr;
};


#endif /* AST_H */
