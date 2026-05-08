/**
* @file env.hxx
 * @brief Small environment-variable helpers used by foundation modules.
 *
 * @details
 * The foundation layer needs a narrow, deterministic way to read a few
 * platform environment variables such as HOME, APPDATA, XDG_CONFIG_HOME, and
 * XDG_DATA_HOME. This module keeps that concern isolated so higher-level
 * modules do not directly depend on std::getenv throughout the codebase.
 */
#pragma once
#ifndef TONB_FOUNDATION_UTIL_ENV_HXX
#define TONB_FOUNDATION_UTIL_ENV_HXX

#include <tonb/foundation/module.hxx>

#include <filesystem>
#include <optional>
#include <string>

namespace tonb::foundation::util {

    /**
     * @brief Return the raw string value of an environment variable, if set.
     *
     * @param name Environment variable name.
     * @return Variable value when present and non-empty; std::nullopt otherwise.
     */
    TNBFOUND_ND_EXPORT std::optional<std::string> env_string(const std::string& name);

    /**
     * @brief Return the filesystem path value of an environment variable, if set.
     *
     * @param name Environment variable name.
     * @return Parsed path when present and non-empty; std::nullopt otherwise.
     */
    TNBFOUND_ND_EXPORT std::optional<std::filesystem::path> env_path(const std::string& name);

} // namespace tonb::foundation::util

#endif // TONB_FOUNDATION_UTIL_ENV_HXX
