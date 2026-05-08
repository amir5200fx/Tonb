/**
* @file workspace_default.cxx
 * @brief Implementation of platform-conventional default workspace root resolution.
 */
#include <tonb/foundation/workspace/workspace_default.hxx>
#include <tonb/foundation/config/app_config.hxx>

namespace tonb::foundation::workspace {

    std::filesystem::path default_workspace_root(const tonb::foundation::config::AppIdentity& app) {
        return tonb::foundation::config::data_root_dir(app) / "workspace";
    }

} // namespace tonb::foundation::workspace
