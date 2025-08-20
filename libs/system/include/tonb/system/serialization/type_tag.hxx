//
// Created by amir on 8/20/25.
//
#pragma once
#ifndef TONB_SYSTEM_SERIALIZATION_TYPE_TAG_HXX
#define TONB_SYSTEM_SERIALIZATION_TYPE_TAG_HXX

#include <tonb/system/log.hxx-backup>
#include <tonb/system/module.hxx>

#include <cstdint>
#include <string>
#include <string_view>
#include <ostream>
#include <istream>
#include <utility>


namespace tonb::system::serialization {

    struct type_tag {
        std::string name;           // e.g. "tonb.Mesh" or "tonb.ErosionConfig"
        std::uint32_t schema = 1;   // your per-type schema version
    };

    // --- little-endian helpers ---
    inline void write_u32_le(std::ostream& os, std::uint32_t v) {
        unsigned char b[4] = {
            static_cast<unsigned char>(v & 0xFF),
            static_cast<unsigned char >((v >> 8) & 0xFF),
            static_cast<unsigned char >((v >> 16) & 0xFF),
            static_cast<unsigned char >((v >> 24) & 0xFF)
        };
        os.write(reinterpret_cast<const char*>(b), sizeof(b));
    }

    TNB_NODISCARD inline bool read_u32_le(std::istream& is, std::uint32_t& v) {
        unsigned char b[4];
        is.read(reinterpret_cast<char*>(b), sizeof(b));
        if (!is) return false;
        v = (static_cast<std::uint32_t>(b[0]) << 0) | (static_cast<std::uint32_t>(b[1]) << 8) | (
                static_cast<std::uint32_t>(b[2]) << 16) | (static_cast<std::uint32_t>(b[3]) << 24);
        return true;
    }

    // --- string (length-prefixed) ---
    inline void write_string(std::ostream& os, std::string_view s) {
        write_u32_le(os, static_cast<std::uint32_t>(s.size()));
        os.write(s.data(), static_cast<std::streamsize>(s.size()));
    }

    TNB_NODISCARD inline bool read_string(std::istream& is, std::string& out) {
        std::uint32_t n = 0;
        if (!read_u32_le(is, n)) return false;
        out.reserve(n);
        is.read(out.data(), static_cast<std::streamsize>(n));
        return static_cast<bool>(is);
    }

    // --- tagged IO with optional logger ---
    TNB_NODISCARD inline bool write_type_tag(std::ostream& os, const type_tag& t, const std::shared_ptr<Logger>& logger = nullptr) {
        write_string(os, t.name);
        write_u32_le(os, t.schema);
        const bool ok = static_cast<bool>(os);
        if (logger) {
            auto lg = logger->with_context("Serialization", "", {{"op", "write-type-tag"}});
            if (!ok) lg->log(LogLevel::debug, "tag written", {{"name", t.name}, {"schema", std::to_string(t.schema)}});
            else lg->error("failed to write type tag");
        }
        return ok;
    }

    TNB_NODISCARD inline bool read_type_tag(std::istream& is, type_tag& t, const std::shared_ptr<Logger>& logger = nullptr) {
        const bool ok = read_string(is, t.name) && read_u32_le(is, t.schema);
        if (logger) {
            auto lg = logger->with_context("Serialization", "", {{"op", "read-type-tag"}});
            if (ok) lg->log(LogLevel::debug, "tag read", {{"name", t.name}, {"schema", std::to_string(t.schema)}});
            else lg->error("failed to read type tag");
        }
        return ok;
    }
}

#endif //TONB_SYSTEM_SERIALIZATION_TYPE_TAG_HXX