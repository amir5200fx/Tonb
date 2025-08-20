//
// Created by amir on 8/19/25.
//
#pragma once
#ifndef TONB_SYSTEM_SERIALIZATION_WIRE_HXX
#define TONB_SYSTEM_SERIALIZATION_WIRE_HXX

/*------------------------------------------------------------------------------
  File: wire.hxx
  Purpose:
    Defines the on-disk/wire header used by TNB binary files. The header makes
    files self-describing and versioned, so readers can validate inputs before
    parsing payloads.

  Design:
    - Fixed-size fields with explicit widths (no plain int).
    - Little-endian encoding for all multi-byte fields.
    - Magic "TNB1" guards against wrong-file types.
    - Version enables backward-compatible evolution.
    - Flags reserve room for feature bits (compression, etc.).
    - index_bits records the index width used in the payload (32 or 64).

  Portability notes:
    - Do not assume struct layout for I/O; compilers may add padding.
      Prefer explicit read/write helpers that serialize each field in order,
      converting endianness as needed.
    - If you *do* ever write the struct as a blob, ensure it is standard-layout
      and tightly packed on all targets, and bump the header version if that
      representation changes. Safer: write fields one by one.

  Validation:
    - Always verify magic, known version, and that index_bits is {32,64}
      before consuming the payload.

  Forward-compat:
    - Keep unused flag bits for future features.
    - Consider adding a header_size field if you plan to extend the header.

  Endianness:
    - Files are little-endian. Convert on big-endian hosts (rare today but
      trivial to support). See the helpers below.

------------------------------------------------------------------------------*/


#include <tonb/system/module.hxx>
#include <tonb/system/log.hxx>

#include <array>
#include <cstdint>
#include <istream>
#include <ostream>
#include <type_traits>

namespace tonb::system::serialization {
    // File magic as a constant for easy comparison and construction.
    inline constexpr std::array<char,4> k_magic{'T','N','B','1'};

    // Bit flags (reserve future bits)
    // bit0: compressed, bit1: encrypted, etc.
    enum : std::uint8_t {
        k_flag_compressed = 1u << 0,
        // k_flag_encrypted = 1u << 1,
      };

    struct wire_header {
        std::array<char,4> magic{k_magic}; // "TNB1"
        std::uint16_t      version{1};     // header/payload schema version
        std::uint8_t       flags{0};       // feature bits
        std::uint8_t       index_bits{32}; // {32, 64} for payload index width
        // If you extend the header, prefer adding a header_size field and bump version.
    };

    // Sanity: standard layout/copyable (good for simple POD handling).
    static_assert(std::is_standard_layout_v<wire_header>);
    static_assert(std::is_trivially_copyable_v<wire_header>);

    // --- Endianness helpers (files are little-endian) ----------------------------

#if __cpp_lib_endian >= 201907L
#include <bit>
    inline constexpr bool host_is_little_endian = (std::endian::native == std::endian::little);
#else
    // Fallback: assume little on mainstream platforms; change if you support big.
    inline constexpr bool host_is_little_endian = true;
#endif

    template<class T>
    inline T to_le(T v) noexcept {
        static_assert(std::is_integral_v<T> || std::is_enum_v<T>);
        if constexpr (host_is_little_endian) return v;
        if constexpr (sizeof(T) == 2) return static_cast<T>((v >> 8) | (v << 8));
        if constexpr (sizeof(T) == 4) return static_cast<T>(((v & 0x000000FFu) << 24) |
                                                            ((v & 0x0000FF00u) << 8 ) |
                                                            ((v & 0x00FF0000u) >> 8 ) |
                                                            ((v & 0xFF000000u) >> 24));
        if constexpr (sizeof(T) == 8) {
            auto x = static_cast<std::uint64_t>(v);
            x = (x << 56) |
                ((x & 0x000000000000FF00ull) << 40) |
                ((x & 0x0000000000FF0000ull) << 24) |
                ((x & 0x00000000FF000000ull) << 8 ) |
                ((x & 0x000000FF00000000ull) >> 8 ) |
                ((x & 0x0000FF0000000000ull) >> 24) |
                ((x & 0x00FF000000000000ull) >> 40) |
                (x >> 56);
            return static_cast<T>(x);
        }
        return v;
    }

    // --- Validation --------------------------------------------------------------

    inline bool is_valid_magic(const wire_header& h) noexcept { return h.magic == k_magic; }
    inline bool is_supported_version(const wire_header& h) noexcept { return h.version >= 1; }
    inline bool is_valid_index_bits(const wire_header& h) noexcept {
        return h.index_bits == 32 || h.index_bits == 64;
    }

    // --- I/O (write/read fields explicitly; avoid writing the raw struct) --------
    TNB_NODISCARD
    inline bool write_wire_header(std::ostream& os, const wire_header& h) noexcept {
        os.write(h.magic.data(), h.magic.size());
        const auto v_le = to_le<std::uint16_t>(h.version);
        os.write(reinterpret_cast<const char*>(&v_le), sizeof v_le);
        os.write(reinterpret_cast<const char*>(&h.flags),      sizeof h.flags);
        os.write(reinterpret_cast<const char*>(&h.index_bits), sizeof h.index_bits);
        return static_cast<bool>(os);
    }

    TNB_NODISCARD
    inline bool read_wire_header(std::istream& is, wire_header& h) noexcept {
        is.read(h.magic.data(), h.magic.size());
        std::uint16_t v_le{}; std::uint8_t fl{}, ib{};
        is.read(reinterpret_cast<char*>(&v_le), sizeof v_le);
        is.read(reinterpret_cast<char*>(&fl),   sizeof fl);
        is.read(reinterpret_cast<char*>(&ib),   sizeof ib);
        if (!is) return false;
        h.version    = to_le<std::uint16_t>(v_le);
        h.flags      = fl;
        h.index_bits = ib;
        return is_valid_magic(h) && is_supported_version(h) && is_valid_index_bits(h);
    }

    // --- Logging adapters (new overloads) ---------------------------------------
    TNB_NODISCARD
    inline bool write_wire_header(std::ostream& os, const wire_header& h,
                                const std::shared_ptr<Logger>& logger) noexcept {
        const bool ok = write_wire_header(os, h);
        if (logger) {
            const auto lg = logger->with_context("Serialization", "", {{"op","write-header"}});
            if (ok) {
                lg->debug("header written", {{"version", std::to_string(h.version)},
                                             {"flags", std::to_string(h.flags)},
                                             {"index_bits", std::to_string(h.index_bits)}});
            } else {
                lg->error("failed to write header");
            }
        }
        return ok;
    }

    TNB_NODISCARD
    inline bool read_wire_header(std::istream& is, wire_header& h,
                               const std::shared_ptr<Logger>& logger) noexcept {
        const bool ok = read_wire_header(is, h);
        if (logger) {
            const auto lg = logger->with_context("Serialization", "", {{"op","read-header"}});
            if (ok) {
                lg->debug("header read", {{"version", std::to_string(h.version)},
                                          {"flags", std::to_string(h.flags)},
                                          {"index_bits", std::to_string(h.index_bits)}});
            } else {
                lg->error("header invalid", {{"reason", "bad magic/version/index_bits"}});
            }
        }
        return ok;
    }



}
#endif  // TONB_SYSTEM_SERIALIZATION_WIRE_HXX
