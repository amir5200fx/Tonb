//
// Created by amir on 8/19/25.
//

#ifndef TONB_SYSTEM_SERIALIZATION_IO_HXX
#define TONB_SYSTEM_SERIALIZATION_IO_HXX
/*------------------------------------------------------------------------------
  File: tonb/global/serialization/io.hpp
  Purpose:
    High-level read/write helpers for TNB binary files. These wrap an
    archive backend (Boost or cereal) selected by default_archive.hpp and
    always prepend/verify a versioned wire header (see wire.hpp).

  Design:
    - No-throw API: returns std::error_code (TNBGLOBAL_NODISCARD).
    - Optional throwing wrappers for convenience.
    - Uses std::filesystem::path for clarity and portability.
    - Backend-agnostic: your model defines `serialize(Archive& ar)` once.

  Error mapping (no-throw):
    - I/O open/write/read failures → std::errc::io_error
    - Bad or unsupported header     → std::errc::illegal_byte_sequence
    - Exceptions from archive/model → std::errc::invalid_argument (conservative)

  Notes:
    - Keep the backend choice consistent across all TUs (make the
      TNB_WITH_CEREAL compile definition PUBLIC on your global target).
    - For very large arrays, prefer bulk (contiguous) serialization in your
      model code to avoid per-element overhead.
------------------------------------------------------------------------------*/

#include <tonb/system/serialization/wire.hxx>
#include <tonb/system/serialization/default_archive.hxx>
#include <tonb/system/verbosity.hxx>
#include <tonb/system/module.hxx>
#include <tonb/system/log.hxx>

#include <filesystem>
#include <fstream>
#include <system_error>
#include <type_traits>
#include <exception>

namespace tonb::system::serialization {
    namespace fs = std::filesystem;

    // -----------------------------------------------------------------------------
    // Concept-like check (works in C++17 and up):
    // Ensures T provides:  void T::serialize(Archive&)
    // -----------------------------------------------------------------------------
    namespace detail {
        template<class, class, class = void> struct is_serializable_with : std::false_type {};
        template<class T, class Archive>
        struct is_serializable_with<T, Archive,
          std::void_t<decltype(std::declval<T&>().serialize(std::declval<Archive&>()))>
        > : std::true_type {};

        template<class, class, class = void> struct is_const_serializable_with : std::false_type {};
        template<class T, class Archive>
        struct is_const_serializable_with<T, Archive,
          std::void_t<decltype(std::declval<const T&>().serialize(std::declval<Archive&>()))>
        > : std::true_type {};
    }

    // Helper: scope a child logger for this operation
    TNB_NODISCARD inline std::shared_ptr<Logger> make_serialize_logger(const std::shared_ptr<Logger> &base,
                                                                       std::string_view op, const fs::path &p,
                                                                       std::initializer_list<std::pair<std::string,
                                                                           std::string> > extra = {}) {
        if (!base) {return nullptr;}
        auto log = base->with_context("Serialization", "", {{"op", std::string(op)}, {"path", p.string()}});
        // Optional context breadcrumb
        for (auto& kv : extra) log->log(LogLevel::debug, "ctx", {kv});
        return log;
    }

    // -----------------------------------------------------------------------------
    // write_file (no-throw): writes wire header + payload
    // -----------------------------------------------------------------------------

    template<class T>
    TNB_NODISCARD inline std::error_code write_file(const fs::path &path, const T &obj,
                                                    const std::uint8_t index_bits = 32,
                                                    Verbosity /*v*/  = Verbosity::quiet) noexcept {
        return write_file(path, obj, index_bits, nullptr);
    }

    // Overloaded with logger
    template<class T>
    TNB_NODISCARD inline std::error_code write_file(const fs::path &path, const T &obj, const std::uint8_t index_bits,
                                                    const std::shared_ptr<Logger> &logger) noexcept {
        static_assert(
            detail::is_serializable_with<T, oarchive>::value || detail::is_const_serializable_with<T, oarchive>::value,
            "T must provide: void serialize(Archive&) [const or non-const].");

        auto lg = make_serialize_logger(logger, "write", path, {{"index_bits", std::to_string(index_bits)}});
        if (lg) lg->info("open for write");

        std::ofstream os(path, std::ios::binary);
        if (!os) {
            if (lg) lg->error("failed to open for write");
            return std::make_error_code(std::errc::io_error);
        }

        wire_header hdr;
        hdr.index_bits = index_bits;
        if (!write_wire_header(os, hdr, lg)) {
            if (lg) lg->error("failed to write header");
            return std::make_error_code(std::errc::io_error);
        }

        try {
            oarchive ar(os);
            if constexpr (detail::is_serializable_with<T, oarchive>::value) {
                obj.serialize(ar);
            } else {
                const_cast<T&>(obj).serialize(ar);
            }
        } catch (const std::exception &e) {
            if (lg) lg->error(std::string("archive/model throw") + e.what());
            return std::make_error_code(std::errc::invalid_argument);
        } catch (...) {
            if (lg) lg->error("archive/model threw: unknown exception");
            return std::make_error_code(std::errc::invalid_argument);
        }

        if (!os.good()) {
            if (lg) lg->error("stream error after write");
            return std::make_error_code(std::errc::io_error);
        }

        if (lg) lg->info("write ok");
        return {};
    }


    // -----------------------------------------------------------------------------
    // read_file (no-throw): reads and validates header, then payload
    // -----------------------------------------------------------------------------

    template<class T>
    TNB_NODISCARD inline std::error_code read_file(const fs::path &path, T &obj,
                                                   Verbosity /*v*/  = Verbosity::quiet) noexcept {
        return read_file(path, obj, nullptr);
    }

    // Overload with logger
    template<class T>
    TNB_NODISCARD inline std::error_code read_file(const fs::path &path, T &obj,
                                                   const std::shared_ptr<Logger> &logger) noexcept {
        static_assert(detail::is_serializable_with<T, iarchive>::value, "T must provide: void serialize(Archive&).");

        auto lg = make_serialize_logger(logger, "read", path);
        if (lg) lg->info("open for read");

        std::ifstream is(path, std::ios::binary);
        if (!is) {
            if (lg) lg->error("failed to open for read");
            return std::make_error_code(std::errc::io_error);
        }

        wire_header hdr{};
        if (!read_wire_header(is, hdr, lg)) {
            if (lg) lg->error("header invalid", {{"reason", "bad magic/version/index_bits"}});
            return std::make_error_code(std::errc::illegal_byte_sequence);
        }

        try {
            iarchive ar(is);
            obj.serialize(ar);
        } catch (const std::exception &e) {
            if (lg) lg->error(std::string("archive/model threw") + e.what());
            return std::make_error_code(std::errc::invalid_argument);
        } catch (...) {
            if (lg) lg->error("archive/model threw: unknown exception");
            return std::make_error_code(std::errc::invalid_argument);
        }

        if (lg) lg->info("read ok");
        return {};
    }

    // -----------------------------------------------------------------------------
    // Throwing convenience wrappers (map error_code → std::system_error)
    // -----------------------------------------------------------------------------

    template<class T>
    inline void write_file_or_throw(const fs::path &path, const T &obj, std::uint8_t index_bits = 32) {
        if (auto ec = write_file(path, obj, index_bits, nullptr)) {
            throw std::system_error(ec, "write_file failed: "+path.string());
        }
    }

    template<class T>
    inline void write_file_or_throw(const fs::path& p, const T& obj, std::uint8_t index_bits, const std::shared_ptr<Logger>& logger) {
        if (auto ec = write_file(p, obj, index_bits, logger)) {
            throw std::system_error(ec, "write_file failed: "+p.string());
        }
    }

    template<class T>
    inline void read_file_or_throw(const fs::path& path, T& obj) {
        if (auto ec = read_file(path, obj)) {
            throw std::system_error(ec, "read_file failed: "+path.string());
        }
    }

    template<class T>
    inline void read_file_or_throw(const fs::path& p, T& obj, const std::shared_ptr<Logger>& logger) {
        if (auto ec = read_file(p, obj, nullptr, logger)) {
            throw std::system_error(ec, "read_file failed: "+p.string());
        }
    }
}
#endif //TONB_SYSTEM_SERIALIZATION_IO_HXX