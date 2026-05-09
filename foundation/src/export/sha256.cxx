//
// Created by amir on 05/03/2026.
//
#include <tonb/foundation/export/sha256.hxx>

#include <array>
#include <cstring>
#include <fstream>
#include <stdexcept>

namespace tonb::foundation::exporting {
    namespace {

        /**
         * @brief SHA-256 context (internal).
         */
        struct Sha256Ctx {
            std::array<std::uint32_t, 8> h{};
            std::uint64_t total_len = 0;
            std::array<std::uint8_t, 64> buffer{};
            std::size_t buffer_len = 0;
        };

        /**
         * @brief SHA-256 round constants.
         */
        constexpr std::array<std::uint32_t, 64> k = {
            0x428a2f98u,0x71374491u,0xb5c0fbcfu,0xe9b5dba5u,0x3956c25bu,0x59f111f1u,0x923f82a4u,0xab1c5ed5u,
            0xd807aa98u,0x12835b01u,0x243185beu,0x550c7dc3u,0x72be5d74u,0x80deb1feu,0x9bdc06a7u,0xc19bf174u,
            0xe49b69c1u,0xefbe4786u,0x0fc19dc6u,0x240ca1ccu,0x2de92c6fu,0x4a7484aau,0x5cb0a9dcu,0x76f988dau,
            0x983e5152u,0xa831c66du,0xb00327c8u,0xbf597fc7u,0xc6e00bf3u,0xd5a79147u,0x06ca6351u,0x14292967u,
            0x27b70a85u,0x2e1b2138u,0x4d2c6dfcu,0x53380d13u,0x650a7354u,0x766a0abbu,0x81c2c92eu,0x92722c85u,
            0xa2bfe8a1u,0xa81a664bu,0xc24b8b70u,0xc76c51a3u,0xd192e819u,0xd6990624u,0xf40e3585u,0x106aa070u,
            0x19a4c116u,0x1e376c08u,0x2748774cu,0x34b0bcb5u,0x391c0cb3u,0x4ed8aa4au,0x5b9cca4fu,0x682e6ff3u,
            0x748f82eeu,0x78a5636fu,0x84c87814u,0x8cc70208u,0x90befffau,0xa4506cebu,0xbef9a3f7u,0xc67178f2u
        };

        inline std::uint32_t rotr(std::uint32_t x, std::uint32_t n) { return (x >> n) | (x << (32 - n)); }
        inline std::uint32_t ch(std::uint32_t x, std::uint32_t y, std::uint32_t z) { return (x & y) ^ (~x & z); }
        inline std::uint32_t maj(std::uint32_t x, std::uint32_t y, std::uint32_t z) { return (x & y) ^ (x & z) ^ (y & z); }
        inline std::uint32_t bsig0(std::uint32_t x) { return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22); }
        inline std::uint32_t bsig1(std::uint32_t x) { return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25); }
        inline std::uint32_t ssig0(std::uint32_t x) { return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3); }
        inline std::uint32_t ssig1(std::uint32_t x) { return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10); }

        inline std::uint32_t read_be32(const std::uint8_t* p) {
            return (static_cast<std::uint32_t>(p[0]) << 24) | (static_cast<std::uint32_t>(p[1]) << 16) | (static_cast<std::uint32_t>(p[2]) << 8) | static_cast<std::uint32_t>(p[3]);
        }

        inline void write_be32(std::uint8_t* p, std::uint32_t v) {
            p[0] = static_cast<std::uint8_t>((v >> 24) & 0xff);
            p[1] = static_cast<std::uint8_t>((v >> 16) & 0xff);
            p[2] = static_cast<std::uint8_t>((v >> 8) & 0xff);
            p[3] = static_cast<std::uint8_t>(v & 0xff);
        }

        void sha256_init(Sha256Ctx& ctx) {
            ctx.h = { 0x6a09e667u,0xbb67ae85u,0x3c6ef372u,0xa54ff53au,0x510e527fu,0x9b05688cu,0x1f83d9abu,0x5be0cd19u };
            ctx.total_len = 0;
            ctx.buffer_len = 0;
        }

        void sha256_compress(Sha256Ctx& ctx, const std::uint8_t block[64]) {
            std::array<std::uint32_t, 64> w{};
            for (int i = 0; i < 16; ++i) {
                w[i] = read_be32(block + 4 * i);
            }
            for (int i = 16; i < 64; ++i) {
                w[i] = ssig1(w[i - 2]) + w[i - 7] + ssig0(w[i - 15]) + w[i - 16];
            }

            std::uint32_t a = ctx.h[0], b = ctx.h[1], c = ctx.h[2], d = ctx.h[3];
            std::uint32_t e = ctx.h[4], f = ctx.h[5], g = ctx.h[6], h = ctx.h[7];

            for (int i = 0; i < 64; ++i) {
                const std::uint32_t t1 = h + bsig1(e) + ch(e, f, g) + k[i] + w[i];
                const std::uint32_t t2 = bsig0(a) + maj(a, b, c);
                h = g;
                g = f;
                f = e;
                e = d + t1;
                d = c;
                c = b;
                b = a;
                a = t1 + t2;
            }

            ctx.h[0] += a; ctx.h[1] += b; ctx.h[2] += c; ctx.h[3] += d;
            ctx.h[4] += e; ctx.h[5] += f; ctx.h[6] += g; ctx.h[7] += h;
        }

        void sha256_update(Sha256Ctx& ctx, const std::uint8_t* data, std::size_t len) {
            if (len == 0)
                return;

            ctx.total_len += len;

            std::size_t off = 0;
            if (ctx.buffer_len > 0) {
                const std::size_t need = 64 - ctx.buffer_len;
                const std::size_t take = (len < need) ? len : need;
                std::memcpy(ctx.buffer.data() + ctx.buffer_len, data, take);
                ctx.buffer_len += take;
                off += take;

                if (ctx.buffer_len == 64) {
                    sha256_compress(ctx, ctx.buffer.data());
                    ctx.buffer_len = 0;
                }
            }

            while (off + 64 <= len) {
                sha256_compress(ctx, data + off);
                off += 64;
            }

            if (off < len) {
                const std::size_t rem = len - off;
                std::memcpy(ctx.buffer.data(), data + off, rem);
                ctx.buffer_len = rem;
            }
        }

        std::array<std::uint8_t, 32> sha256_final(Sha256Ctx& ctx) {
            // message length in bits
            const std::uint64_t bit_len = ctx.total_len * 8;

            // append 0x80
            std::uint8_t pad[64] = {0x80};
            std::size_t pad_len = (ctx.buffer_len < 56) ? (56 - ctx.buffer_len) : (56 + 64 - ctx.buffer_len);
            sha256_update(ctx, pad, pad_len);

            // append length in bits as big-endian 64-bit
            std::uint8_t len_buf[8];
            for (int i = 0; i < 8; ++i) {
                len_buf[7 - i] = static_cast<std::uint8_t>((bit_len >> (8 * i)) & 0xff);
            }
            sha256_update(ctx, len_buf, 8);

            std::array<std::uint8_t, 32> out{};
            for (int i = 0; i < 8; ++i) {
                write_be32(out.data() + 4 * i, ctx.h[i]);
            }
            return out;
        }

        std::string to_hex(const std::uint8_t* p, std::size_t n) {
            static const char* hex = "0123456789abcdef";
            std::string s;
            s.resize(n * 2);
            for (std::size_t i = 0; i < n; ++i) {
                s[2 * i] = hex[(p[i] >> 4) & 0x0f];
                s[2 * i + 1] = hex[p[i] & 0x0f];
            }
            return s;
        }
    }

    std::string sha256_hex(const std::vector<std::uint8_t> &data) {
        return sha256_hex(data.data(), data.size());
    }

    std::string sha256_hex(const std::uint8_t *data, std::size_t size) {
        if (size > 0 && data == nullptr)
            throw std::invalid_argument("sha256_hex: data is null with non-zero size");

        Sha256Ctx ctx;
        sha256_init(ctx);
        sha256_update(ctx, data, size);
        const auto d = sha256_final(ctx);
        return to_hex(d.data(), d.size());
    }

    std::string sha256_hex_file(const std::filesystem::path &path) {
        std::ifstream ifs(path, std::ios::binary);
        if (!ifs)
            throw std::runtime_error("sha256_hex_file: failed to open file");

        Sha256Ctx ctx;
        sha256_init(ctx);

        std::array<std::uint8_t, 64 * 1024> buf{};
        while (ifs) {
            ifs.read(reinterpret_cast<char*>(buf.data()), static_cast<std::streamsize>(buf.size()));
            const std::streamsize got = ifs.gcount();
            if (got > 0) {
                sha256_update(ctx, buf.data(), static_cast<std::size_t>(got));
            }
        }

        if (!ifs.eof() && ifs.fail())
            throw std::runtime_error("sha256_hex_file: failed during read");

        const auto d = sha256_final(ctx);
        return to_hex(d.data(), d.size());
    }
}