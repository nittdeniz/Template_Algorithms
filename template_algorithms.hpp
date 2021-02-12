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

#ifndef TEMPLATE_ALGORITHMS_HPP
#define TEMPLATE_ALGORITHMS_HPP

#include <array>
#include <iostream>
#include <utility>

template<std::size_t...>
struct $CLASSNAME;

namespace Template_Algorithm
{
    /*******************\
    |** CONCATENATION **|
    \*******************/

    template<typename...>
    struct concat_struct;

    template<std::size_t... m, std::size_t... n>
    struct concat_struct<$CLASSNAME<m...>, $CLASSNAME<n...>>
    {
        using type = $CLASSNAME<m..., n...>;
    };

    template<typename a, typename b>
    using concat = typename concat_struct<a, b>::type;

    /***************\
    |** POSITIONS **|
    \***************/
    template<std::size_t n>
    struct First
    {};

    template<std::size_t n>
    struct Last
    {};

    template<std::size_t i>
    struct Pos
    {};

    /******************\
    |** GET & DELETE **|
    \******************/

    template<typename...>
    struct delete_struct;

    template<std::size_t n>
    struct delete_struct<First<n>, $CLASSNAME<>>
    {
        using type = $CLASSNAME<>;
    };

    template<std::size_t i, std::size_t... j>
    struct delete_struct<First<0>, $CLASSNAME<i, j...>>
    {
        using type = $CLASSNAME<i, j...>;
    };

    template<std::size_t i>
    struct delete_struct<Last<i>, $CLASSNAME<>>
    {
        using type = $CLASSNAME<>;
    };

    template<std::size_t n, std::size_t i, std::size_t... j>
    struct delete_struct<First<n>, $CLASSNAME<i, j...>>
    {
        using type = typename delete_struct<First<n - 1>, $CLASSNAME<j...>>::type;
    };

    template<typename a, typename b>
    using del = typename delete_struct<a, b>::type;

    template<typename...>
    struct get_struct;

    template<std::size_t i, std::size_t... j>
    struct get_struct<First<i>, $CLASSNAME<j...>>
    {
        using type = $CLASSNAME<>;
    };

    template<std::size_t i, std::size_t... j>
    struct get_struct<First<0>, $CLASSNAME<i, j...>>
    {
        using type = $CLASSNAME<>;
    };

    template<std::size_t n, std::size_t i, std::size_t... j>
    struct get_struct<First<n>, $CLASSNAME<i, j...>>
    {
        using type = typename concat<$CLASSNAME<i>, typename get_struct<First<n - 1>, $CLASSNAME<j...>>::type>::type;
    };

    template<std::size_t n, std::size_t i, std::size_t... j>
    struct get_struct<Last<n>, $CLASSNAME<i, j...>>
    {
        using type = typename del<First<sizeof...(j) + 1 - n>, $CLASSNAME<i, j...>>::type;
    };

    template<typename a, typename b>
    using get = typename get_struct<a, b>::type;

    template<std::size_t n, std::size_t i, std::size_t... j>
    struct delete_struct<Last<n>, $CLASSNAME<i, j...>>
    {
        using type = typename get<First<sizeof...(j) + 1 - n>, $CLASSNAME<i, j...>>::type;
    };

    template<std::size_t n, std::size_t i, std::size_t... j>
    struct delete_struct<Pos<n>, $CLASSNAME<i, j...>>
    {
        using type = concat<
                get<
                        First<n>,
                        $CLASSNAME<i,j...>
                >,
                get<
                        Last<sizeof...(j)-n>,
                        $CLASSNAME<i,j...>
                >
        >;
    };

    template<std::size_t n, std::size_t i, std::size_t... j>
    struct get_struct<Pos<n>, $CLASSNAME<i, j...>>
    {
        using type = typename del<First<n>, typename del<Last<sizeof...(j) - n>, $CLASSNAME<i, j...>>::type>::type;
    };

    /*********************\
    |** XSLICE & ISLICE **|
    \*********************/

    template<typename...>
    struct islice_struct;

    template<std::size_t a, std::size_t b, std::size_t... i>
    struct islice_struct<Pos<a>, Pos<b>, $CLASSNAME<i...>>
    {
        using type = typename del<First<a>, typename del<Last<sizeof...(i) - b - 1>, $CLASSNAME<i...>>::type>::type;
    };

    template<typename a, typename b, typename c>
    using islice = typename islice_struct<a, b, c>::type;

    template<typename...>
    struct xslice_struct;

    template<std::size_t a, std::size_t b, std::size_t... i>
    struct xslice_struct<Pos<a>, Pos<b>, $CLASSNAME<i...>>
    {
        using type = typename del<First<a+1>, typename del<Last<sizeof...(i) - b>, $CLASSNAME<i...>>::type>::type;
    };

    template<typename a, typename b, typename c>
    using xslice = typename xslice_struct<a, b, c>::type;

    /**********\
    |** SWAP **|
    \**********/

    template<typename...>
    struct swap_struct;

    template<std::size_t a, std::size_t b, std::size_t... i>
    struct swap_struct<Pos<a>, Pos<b>, $CLASSNAME<i...>>
    {
        using type = typename
        concat<
                get<First<a>, $CLASSNAME<i...>>,
                concat<
                        get<Pos<b>, $CLASSNAME<i...>>,
                        concat<
                                xslice<Pos<a>, Pos<b>, $CLASSNAME<i...>>
                                ,
                                concat<
                                        get<Pos<a>, $CLASSNAME<i...>>,
                                        get<Last<sizeof...(i) - b - 1>, $CLASSNAME<i...>>
                                >
                        >
                >
        >::type;
    };

    template<typename a, typename b, typename c>
    using swap = typename swap_struct<a, b, c>::type;
}


#endif // TEMPLATE_ALGORITHMS_HPP