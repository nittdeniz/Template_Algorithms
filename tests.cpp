/******************************************************************************************\
 * MIT License                                                                            *
 *                                                                                        *
 * Copyright (c) 2021 Deniz A. Nitt                                                       *
 *                                                                                        *
 * Permission is hereby granted, free of charge, to any person obtaining a copy           *
 *         of this software and associated documentation files (the "Software"), to deal  *
 * in the Software without restriction, including without limitation the rights           *
 *         to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      *
 *         copies of the Software, and to permit persons to whom the Software is          *
 * furnished to do so, subject to the following conditions:                               *
 *                                                                                        *
 * The above copyright notice and this permission notice shall be included in all         *
 *         copies or substantial portions of the Software.                                *
 *                                                                                        *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR             *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,               *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE            *
 *         AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,          *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE          *
 * SOFTWARE.                                                                              *
\******************************************************************************************/

#include <iostream>

#include "simple_test/simple_test.hpp"

#define $CLASSNAME Base
#include "template_algorithms.hpp"

template<std::size_t... n>
struct Base
{
    constexpr static std::array<std::size_t, std::index_sequence<n...>().size()> array = {n...};
    using type = Base<n...>;
};

template<std::size_t... n>
bool operator==(Base<n...>& b1, Base<n...>& b2)
{
    return true;
}

template<std::size_t... m, std::size_t... n>
bool operator==(Base<m...>& b1, Base<n...>& b2)
{
    return false;
}

template<typename... Args>
void print(Args...);

template<std::size_t... i>
void print(Base<i...> b)
{
    for( auto const& elem : b.array )
    {
        std::cout  << elem << ", ";
    }
    std::cout << "\n";
}

int main()
{
    using namespace Template_Algorithm;
    Simple_Test::Test_Manager T;
    // CONCAT
    T.add_test("concat<><>", [](){
        concat<Base<>, Base<>> test;
        Base<> result;
        return test == result;
    });

    T.add_test("concat<> <1>", [](){
       concat<Base<>, Base<1>> test;
       Base<1> result;
       return test == result;
    });

    T.add_test("concat<1> <>", [](){
        concat<Base<1>, Base<>> test;
        Base<1> result;
        return test == result;
    });

    T.add_test("concat<1,2,3> <4,5,6>", [](){
        concat<Base<1,2,3>, Base<4,5,6>> test;
        Base<1,2,3,4,5,6> result;
        return test == result;
    });

    // get

    T.add_test("get<Pos<3>, <1,2,3,4,5,6>", [](){
        get<Pos<3>, Base<1,2,3,4,5,6>> test;
        Base<4> result;
        return test == result;
    });

    T.add_test("get<First<3>, <1,2,3,4,5,6>", [](){
        get<First<3>, Base<1,2,3,4,5,6>> test;
        Base<1,2,3> result;
        return test == result;
    });

    T.add_test("get<First<3>, <1,2>", [](){
        get<First<3>, Base<1,2>> test;
        Base<1,2> result;
        return test == result;
    });

    T.add_test("get<First<3>, <>", [](){
        get<First<3>, Base<>> test;
        Base<> result;
        return test == result;
    });

    T.add_test("get<Last<3>, <1,2,3,4,5,6>", [](){
        get<Last<3>, Base<1,2,3,4,5,6>> test;
        Base<4,5,6> result;
        return test == result;
    });

    T.add_test("get<Last<3>, <>", [](){
        get<First<3>, Base<>> test;
        Base<> result;
        return test == result;
    });

    // del

    T.add_test("del<Pos<3>, <1,2,3,4,5,6>", [](){
        del<Pos<3>, Base<1,2,3,4,5,6>> test;
        Base<1,2,3,5,6> result;
        return test == result;
    });

    T.add_test("del<First<3>, <1,2,3,4,5,6>", [](){
        del<First<3>, Base<1,2,3,4,5,6>> test;
        Base<4,5,6> result;
        return test == result;
    });

    T.add_test("del<Last<3>, <1,2,3,4,5,6>", [](){
       del<Last<3>, Base<1,2,3,4,5,6>> test;
       Base<1,2,3> result;
       return test == result;
    });

    T.add_test("del<Last<3>, <>", [](){
        del<Last<3>, Base<>> test;
        Base<> result;
        return test == result;
    });

    // islice

    T.add_test("islice<Pos<2>, Pos<5>, <1,2,3,4,5,6,7,8>", [](){
       islice<Pos<2>, Pos<5>, Base<1,2,3,4,5,6,7,8>> test;
       Base<3,4,5,6> result;
       return test == result;
    });

    // xslice

    T.add_test("xslice<Pos<2>, Pos<5>, <1,2,3,4,5,6,7,8>", [](){
        xslice<Pos<2>, Pos<5>, Base<1,2,3,4,5,6,7,8>> test;
        Base<4,5> result;
        return test == result;
    });

    // swap

    T.add_test("swap<Pos<2>, Pos<5>, <1,2,3,4,5,6,7,8>", [](){
        swap<Pos<2>, Pos<5>, Base<1,2,3,4,5,6,7,8>> test;
        Base<1,2,6,4,5,3,7,8> result;
        return test == result;
    });

    T.run();

    /*
    concat<Base<>, Base<>>  concat1;
    std::cout << "concat <> <>\n";
    print(concat1);
    concat<Base<>, Base<1>> concat2;
    std::cout << "concat <> <1>\n";
    print(concat2);
    concat<Base<1>, Base<>> concat3;
    std::cout << "concat <1> <>\n";
    print(concat3);
    concat<Base<1>, Base<2>> concat4;
    std::cout << "concat <> <>\n";
    print(concat1);
    concat<Base<1,2,3>, Base<4,5,6>> concat5;
    std::cout << "concat <1,2,3> <4,5,6>\n";
    print(concat5);
     */
    return EXIT_SUCCESS;
}
