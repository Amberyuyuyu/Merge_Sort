/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019. All rights reserved.
 * Description: 上机编程认证
 */

#include <ios>
#include <iostream>
#include <tuple>
#include <utility>
#include <type_traits>

#include <string>

using namespace std;

class Solution {
public:
    string GetMaxOccuredSubstring(const string& inputStr)
    {
        return "";
    }
};

// 以下为考题输入输出框架，此部分代码不建议改动；提交代码时请勿包含下面代码
namespace IoContext {

class Reader {
public:
    explicit Reader(istream& in) : is(in) {}

    template<typename T, typename... U>
    bool ReadManyEach(T& value, U&... others)
    {
        if (!Read(value)) { return false; }
        if constexpr (sizeof...(others) == 0) {
            return true;
        } else {
            return ReadManyEach(others...);
        }
    }

    template<typename... T> bool ReadMany(T&... values)
    {
        if constexpr (sizeof...(values) == 0) {
            return true;
        } else {
            return ReadManyEach(values...);
        }
    }

    bool PickChar(char c)
    {
        char x;
        is >> x;
        return !is.fail() && x == c;
    }

    bool Read(string& value)
    {
        if (!PickChar('\"')) { return false; }
        char c = static_cast<char>(is.get());
        while (c != '\"') {
            value.push_back(c);
            c = static_cast<char>(is.get());
            if (is.fail()) { return false; }
        }
        return true;
    }

private:
    istream& is;
};

class Writer {
public:
    explicit Writer(ostream& out) : os(out) {}

    void Print(const string& value)
    {
        os << '\"' << value << '\"';
    }

private:
    ostream& os;
};

class Invoker {
public:
    Invoker(istream& is, ostream& os) : reader(is), writer(os) {}

    template<typename R, typename... Args, typename T, size_t... I>
    bool ExpandArgs(R (Solution::*func)(Args...), Solution& obj, T& args, index_sequence<I...>)
    {
        if (!reader.ReadMany(get<I>(args)...)) { return false; }
        if constexpr (is_void_v<R>) {
            (obj.*func)(get<I>(args)...);
        } else {
            writer.Print((obj.*func)(get<I>(args)...));
        }
        return true;
    }

    template<typename R, typename... Args>
    bool Invoke(R (Solution::*func)(Args...), Solution& obj)
    {
        tuple<remove_cv_t<remove_reference_t<Args>>...> args;
        return ExpandArgs(func, obj, args, make_index_sequence<sizeof...(Args)>());
    }

private:
    Reader reader;
    Writer writer;
};

template<typename Ret, typename... P>
class VerifyTypes {
public:
    template<typename R, typename T, typename... Args>
    static void Match(R (T::*func)(Args...))
    {
        static_assert(is_same_v<R, Ret> && (... && is_same_v<P, Args>),
            "Interface's return type or parameter type has been changed!");
    }
};

}

int main()
{
    IoContext::VerifyTypes<string, const string&>::Match(&Solution::GetMaxOccuredSubstring);
    IoContext::Invoker invoker(cin, cout);
    Solution solution;
    if (!invoker.Invoke(&Solution::GetMaxOccuredSubstring, solution)) {
        cout << "Error: Input format incorrect!" << endl;
    }
    return 0;
}