#pragma once

#include <iterator>
#include <string.h>
#include <cassert>

namespace tribl
{
    enum class CMP { LESS=-1, EQ=0, GRTR=1 };

    // IMU: these two simple funcions are main perforance heaters
    // couple of considerations:
    // 1. It would have been ideally of cause had microprocessor manufactures
    //    had supported atomic operation on hardware level, reducing
    //    comparision of two numbers to tri-boolean value
    //    that would be just fantastic, but fantastic doesn't mean realistic :-)
    // 2. We can use bit's operations here, but that would be only for signed numbers
    // 
    // this is for a signed data (string in our case)
    template <typename T>
    inline CMP sign(T x1) { return (x1 > 0) ? CMP::GRTR : ((x1 < 0) ? CMP::LESS : CMP::EQ); }
    // unsigned
    //        yes, having two simial functions looks odd, just for testing purposes
    template <typename T>
    inline CMP sign(T x1, T x2) { return (x1 > x2) ? CMP::GRTR : ((x1 < x2) ? CMP::LESS : CMP::EQ); }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
    template <class T>
    inline CMP cmp(T const& i1, T const& i2) { assert(0); }
#pragma GCC diagnostic pop

    template<>
    inline CMP cmp<int>(int const& i1, int const& i2)
        { return tribl::sign(i1, i2); }
    template<>
    inline CMP cmp<std::string>(std::string const& s1, std::string const& s2)
    {
        return static_cast<CMP>(tribl::sign(::strcmp(s1.c_str(), s2.c_str())));
    }

    template<typename _ForwardIterator, typename _Tp, typename _Compare>
    inline _ForwardIterator
    __lower_bound(_ForwardIterator __first, _ForwardIterator __last,
        const _Tp & __val, _Compare __comp) {
        typedef typename std::iterator_traits < _ForwardIterator > ::difference_type
        _DistanceType;

        _DistanceType __len = std::distance(__first, __last);

        while (__len > 0)
        {
            _DistanceType __half = __len >> 1;
            _ForwardIterator __middle = __first;
            std::advance(__middle, __half);
            // GS:
            //      dereferencing iterator here
            switch(__comp(*__middle, __val))
            {
                case CMP::LESS:
                    __first = __middle;
                    ++__first;
                    __len = __len - __half - 1;
                    break;
                case CMP::GRTR:
                    __len = __half;
                    break;
                case CMP::EQ:
                    // Hamlet Act 5, scene 2, 280–283
                    // Osric:
                    //          A hit, a very palpable hit.
                    return __middle;
            }
        }
        return __first;
    }
    template < typename _ForwardIterator, typename _Tp >
        inline _ForwardIterator
    lower_bound(_ForwardIterator __first, _ForwardIterator __last,
        const _Tp & __val) {
        // concept requirements
        __glibcxx_function_requires(_ForwardIteratorConcept < _ForwardIterator > )
        __glibcxx_function_requires(_LessThanOpConcept <
            typename iterator_traits < _ForwardIterator > ::value_type, _Tp > )
        __glibcxx_requires_partitioned_lower(__first, __last, __val);

        return tribl::__lower_bound(__first, __last, __val, tribl::cmp<_Tp>);
    }
}
