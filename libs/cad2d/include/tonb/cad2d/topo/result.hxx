//
// Created by amir on 11/9/25.
//
/**
 * @file result.hxx
 * @brief Provides a lightweight result type for non-throwing error handling
 *        across the cad2d library.
 *
 * The Result<T> class template represents the outcome of an operation that
 * can either succeed (holding a value of type T) or fail (holding an error
 * description). It is a simplified stand-in for std::expected<T, E> intended
 * for use in internal topology, builder, and validator modules.
 *
 * Design goals:
 * - Avoid exceptions in core algorithms.
 * - Carry both value and descriptive error.
 * - Header-only, minimal overhead.
 */
#pragma once
#ifndef TONB_CAD2D_TOPO_RESULT_HXX
#define TONB_CAD2D_TOPO_RESULT_HXX
#include <tonb/system/module.hxx>
#include <string>
#include <optional>
#include <utility>
#include <cstdint>

namespace tonb::cad2d::topo {

    /**
     * @enum ErrorCode
     * @brief Classifies categories of recoverable or validation errors.
     */
    enum class ErrorCode : std::uint8_t {
        none = 0,           ///< Success, no error.
        invalid_input,      ///< Invalid arguments or missing data.
        topology_error,     ///< Broken connectivity or inconsistent links.
        geometry_error,     ///< Invalid curve, point, or parametric range.
        degenerate,         ///< zero-length or degenerate configuration.
        validation_failed,  ///< Check failed (non-manifold, overlap, etc.).
        internal            ///< Unexpected internal condition.
    };

    /**
     * @struct ResultError
     * @brief Represents a descriptive failure message and error code.
     */
    struct ResultError {
        std::string message;
        ErrorCode code {ErrorCode::none};

        ResultError() = default;
        explicit ResultError(std::string msg, const ErrorCode c = ErrorCode::none)
            : message(std::move(msg)), code(c) {}
    };

    /**
     * @class Result
     * @brief Represents either a success (value) or failure (error) outcome.
     */
    template<class T>
    class Result {
    public:
        /// @name Construction
        /// @{

        explicit Result(const T& value) : value_(value), has_value_(true) {}
        explicit Result(T&& value) noexcept : value_(std::move(value)), has_value_(true) {}
        explicit Result(ResultError err) : error_(std::move(err)), has_value_(false) {}

        /// @}

        /// @name Queries
        /// @{

        TNB_NODISCARD bool has_value() const noexcept {return has_value_;}
        TNB_NODISCARD explicit operator bool() const noexcept {return has_value_;}

        TNB_NODISCARD const T& value() const {return *value_;}
        TNB_NODISCARD T& value() {return *value_;}

        TNB_NODISCARD const ResultError& error() const noexcept {return *error_;}

        /// @}

    private:
        std::optional<T> value_;
        std::optional<ResultError> error_;
        bool has_value_ {false};
    };

    /// @brief Partial specialisation for Result<void>.
    template<>
    class Result<void> {
    public:
        Result() = default;
        explicit Result(ResultError err) : error_(std::move(err)), has_error_(true) {}

        TNB_NODISCARD bool has_value() const noexcept {return !has_error_;}
        TNB_NODISCARD explicit operator bool() const noexcept {return !has_error_;}

        TNB_NODISCARD const ResultError& error() const noexcept {return *error_;}

    private:
        std::optional<ResultError> error_;
        bool has_error_{false};
    };

    /**
     * @brief Helper to create a successful Result<T>.
     */
    template<class T>
    TNB_NODISCARD inline Result<T> ok(T&& value) {
        return Result<T>(std::forward<T>(value));
    }

    /**
     * @brief Helper to create a failed Result<T>
     */
    template<class T>
    TNB_NODISCARD inline Result<T> fail(std::string msg, const ErrorCode code = ErrorCode::internal) {
        return Result<T>(ResultError{std::move(msg), code});
    }
}
#endif //TONB_CAD2D_TOPO_RESULT_HXX