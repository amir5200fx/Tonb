//
// Created by amir on 8/23/25.
//

#ifndef TONB_BASE_TRAITS_HXX
#define TONB_BASE_TRAITS_HXX

/**
 * @file traits.hxx
 * @brief Lightweight compile-time type traits for Tonb.
 *
 * This header provides a minimal set of templates to reason about types at compile-time
 * without depending on heavy meta-programming frameworks. Utilities include small
 * dimensionality predicates and special-purpose transformations like stripping pointer,
 * smart-pointer, and reference qualifiers.
 *
 * ### Design notes
 * - Zero-overhead: all utilities are simple aliases or `std::true_type`/`std::false_type`
 *   based meta-constants evaluated entirely at compile time.
 * - Header-only and constexpr-friendly.
 * - Complements `<type_traits>` rather than replacing it.
 *
 * ### Example
 * @code{.cpp}
 * using tonb::base::traits::remove_pointer;
 * using tonb::base::traits::remove_reference;
 *
 * static_assert( tonb::base::traits::is_two_dimension<2>::value );
 * static_assert(!tonb::base::traits::is_two_dimension<3>::value );
 *
 * using P1 = int*;
 * using P2 = std::shared_ptr<double>;
 * static_assert(std::is_same_v<typename remove_pointer<P1>::type, int>);
 * static_assert(std::is_same_v<typename remove_pointer<P2>::type, double>);
 *
 * using R1 = const float&;
 * static_assert(std::is_same_v<typename remove_reference<R1>::type, float>);
 * @endcode
 */

#include <type_traits>
#include <memory>

namespace tonb::base::traits {

    /**
     * @brief Meta-boolean that is `true` only when @p Dim equals 2.
     * @tparam Dim Dimensionality to test.
     * @note Primary template defaults to `false_type`. A specialization is provided for `2`.
     */
    template<int Dim> struct is_two_dimension : std::false_type {};
    /// @copydoc is_two_dimension
    template<> struct is_two_dimension<2> : std::true_type {};

    template<int Dim> struct is_three_dimension : std::false_type {};
    template<> struct is_three_dimension<3> : std::true_type {};

    /**
     * @brief Remove raw-pointer or `std::shared_ptr` qualifiers from a type.
     *
     * Provides `type` member alias equal to the pointee for:
     * - `T*`, `T* const`, `T* volatile`, `T* const volatile`
     * - `std::shared_ptr<T>`
     * For non-pointer types, `type` is the original `T`.
     *
     * @tparam T Input type to transform.
     */
    template<typename T> struct remove_pointer {using type = T;};
    /// @copydoc remove_pointer
    template<typename T> struct remove_pointer<T*> {using type = T;};
    /// @copydoc remove_pointer
    template<typename T> struct remove_pointer<T* const> {using type = T;};
    /// @copydoc remove_pointer
    template<typename T> struct remove_pointer<T* volatile> {using type = T;};
    /// @copydoc remove_pointer
    template<typename T> struct remove_pointer<T* const volatile> {using type = T;};
    /// @copydoc remove_pointer
    template<typename T> struct remove_pointer<std::shared_ptr<T>> {using type = T;};

    /**
     * @brief Remove lvalue-reference qualifiers and top-level `const` from a reference.
     *
     * Behaves similarly to `std::remove_reference_t`, but also maps `const T&` to `T`.
     * For non-reference types, `type` is the original `T`.
     *
     * @tparam T Input type to transform.
     */
    template<typename T> struct remove_reference {using type = T;};
    /// @copydoc remove_reference
    template<typename T> struct remove_reference<T&> {using type = T;};
    /// @copydoc remove_reference
    template<typename T> struct remove_reference<const T&> {using type = T;};

}
#endif //TONB_BASE_TRAITS_HXX