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
#include <tonb/system/serialization/type_tag.hxx>
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

    // Write: header + type_tag + payload
    template<class T>
    TNB_NODISCARD inline std::error_code write_tagged_file(const fs::path &path, const T &obj, const type_tag &tag,
                                                           std::uint8_t index_bits = 32,
                                                           const std::shared_ptr<Logger> &logger = nullptr) {
        auto lg = make_serialize_logger(logger, "write_tagged", path, {
                                            {"type", tag.name}, {"schema", std::to_string(tag.schema)}
                                        });
        if (lg) lg->info("open for write");

        std::ofstream os(path, std::ios::binary);
        if (!os) {
            if (lg) lg->error("failed to open for write");
            return std::make_error_code(std::errc::io_error);
        }

        wire_header hdr{};
        hdr.index_bits = index_bits;
        if (!write_wire_header(os, hdr, lg)) {
            if (lg) lg->error("header write failed");
            return std::make_error_code(std::errc::io_error);
        }
        if (!write_type_tag(os, tag, lg)) {
            if (lg) lg->error("tag write failed");
            return std::make_error_code(std::errc::io_error);
        }

        try {
            oarchive ar(os);
            if constexpr (detail::is_const_serializable_with<T, oarchive>::value)
                obj.serialize(ar);
            else
                const_cast<T&>(obj).serialize(ar);
        } catch (const std::exception &e) {
            if (lg) lg->error(std::string("archive/model threw: ") + e.what());
            return std::make_error_code(std::errc::invalid_argument);
        } catch (...) {
            if (lg) lg->error("archive/model threw: unknown exception");
            return std::make_error_code(std::errc::invalid_argument);
        }

        if (lg) lg->info("write ok");
        return {};
    }

    // Peak: header + type_tag only (no payload)
    TNBSYSTEM_ND_EXPORT
    std::error_code peak_file_type(const fs::path &path, type_tag &out, const std::shared_ptr<Logger>& logger) noexcept;

    // a tiny registry for dynamic dispatch
    template<class Base>
    class TypeRegistry {
    public:
        // Loader constructs and deserializes a concrete object into Base*
        using Loader = std::function<std::unique_ptr<Base>(iarchive&)>;
    private:
        /*Private Data*/

        std::unordered_map<std::string, Loader> table_;

        static std::string key(const std::string& name, const std::uint32_t schema) {
            return name + '@' + std::to_string(schema);
        }
    public:

        // Public functions and operators

        void add(const std::string& type_name, const std::uint32_t schema, Loader loader) {
            table_[key(type_name, schema)] = std::move(loader);
        }
        Loader* find(const std::string& type_name, const std::uint32_t schema) {
            auto it = table_.find(key(type_name, schema));
            if (it == table_.end()) return nullptr;
            return &it->second;
        }
    };

    // Dynamic read: read header + tag, then dispatch to registered loader
    template<class Base>
    TNB_NODISCARD inline std::error_code read_tagged_file_any(const fs::path &path, type_tag &out, TypeRegistry<Base>& registry, const std::shared_ptr<Logger>& logger) {
        auto lg = make_serialize_logger(logger, "read_tagged", path);
        if (lg) lg->info("open for read");

        std::ifstream is(path, std::ios::binary);
        if (!is) {
            if (lg) lg->error("failed to open for read");
            return std::make_error_code(std::errc::io_error);
        }

        if (wire_header hdr{}; !read_wire_header(is, hdr, lg)) {
            if (lg) lg->error("bad header");
            return std::make_error_code(std::errc::illegal_byte_sequence);
        }

        type_tag tag{};
        if (!read_type_tag(is, tag, lg)) {
            if (lg) lg->error("bad tag");
            return std::make_error_code(std::errc::illegal_byte_sequence);
        }

        auto loader = registry.find(tag.name, tag.schema);
        if (!loader) {
            if (lg) lg->warn("no loader registered", {{"name", tag.name}, {"schema", std::to_string(tag.schema)}});
            return std::make_error_code(std::errc::protocol_error);
        }

        try {
            iarchive ar(is);
            out  = (*loader)(ar);
        } catch (const std::exception &e) {
            if (lg) lg->error(std::string("failed to load type: ") + e.what());
            return std::make_error_code(std::errc::invalid_argument);
        } catch (...) {
            if (lg) lg->error("unknown exception");
            return std::make_error_code(std::errc::invalid_argument);
        }

        if (lg) lg->info("read ok", {{"name", tag.name}, {"schema", std::to_string(tag.schema)}});
        return {};
    }
}
#endif //TONB_SYSTEM_SERIALIZATION_IO_HXX