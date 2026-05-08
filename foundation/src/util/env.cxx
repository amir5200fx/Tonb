/**
* @file env.cxx
 * @brief Implementation of small environment-variable helpers.
 */
#include <tonb/foundation/util/env.hxx>

#include <cstdlib>

namespace tonb::foundation::util {

    std::optional<std::string> env_string(const std::string& name) {
        if (name.empty()) {
            return std::nullopt;
        }
        const char* value = std::getenv(name.c_str());
        if (value == nullptr || *value == '\0') {
            return std::nullopt;
        }
        return std::string(value);
    }

    std::optional<std::filesystem::path> env_path(const std::string& name) {
        if (const auto v = env_string(name)) {
            return std::filesystem::path(*v);
        }
        return std::nullopt;
    }

} // namespace tonb::foundation::util
