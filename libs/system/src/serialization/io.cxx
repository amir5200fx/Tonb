//
// Created by amir on 8/20/25.
//
#include <tonb/system/serialization/io.hxx>

std::error_code tonb::system::serialization::peak_file_type(const fs::path &path, type_tag &out,
    const std::shared_ptr<Logger> &logger) noexcept {
    const auto lg = make_serialize_logger(logger, "peek-type", path);
    std::ifstream is(path, std::ios::binary);
    if (!is) {
        if (lg) {
            lg->error("open failed");
            return std::make_error_code(std::errc::io_error);
        }
    }

    if (wire_header hdr{}; !read_wire_header(is, hdr, lg)) {
        if (lg) lg->error("bad header");
        return std::make_error_code(std::errc::illegal_byte_sequence);
    }
    if (!read_type_tag(is, out, lg)) {
        if (lg) lg->error("bad tag");
        return std::make_error_code(std::errc::illegal_byte_sequence);
    }
    if (lg) lg->info("peek type");
    return {};
}
