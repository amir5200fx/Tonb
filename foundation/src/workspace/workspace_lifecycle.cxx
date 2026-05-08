/**
 * @file workspace_lifecycle.cxx
 * @brief Implementation of session-level workspace lifecycle management.
 */
#include <tonb/foundation/workspace/workspace_lifecycle.hxx>

#include <tonb/foundation/workspace/workspace_persist.hxx>

#include <stdexcept>
#include <utility>

namespace tonb::foundation::workspace {

WorkspaceLifecycle::WorkspaceLifecycle(tonb::foundation::config::AppIdentity app)
    : app_(std::move(app)) {
}

const Workspace& WorkspaceLifecycle::workspace() const {
    if (!ws_) {
        throw std::logic_error("workspace: no active workspace");
    }
    return *ws_;
}

const std::string& WorkspaceLifecycle::canonical_root_string() const {
    if (!ws_) {
        throw std::logic_error("workspace: no active workspace");
    }
    return canonical_root_;
}

void WorkspaceLifecycle::init(const std::filesystem::path& root) {
    Workspace candidate(root);

    {
        std::error_code ec;
        std::filesystem::create_directories(candidate.root(), ec);
        if (ec) {
            throw std::runtime_error(
                "workspace init: failed to create workspace root directory: '" +
                candidate.root().string() + "': " + ec.message());
        }
    }

    create_required_dirs(candidate);
    const std::string can = compute_canonical_root_string(candidate.root());

    if (ws_) {
        if (canonical_root_ == can) {
            return;
        }
        throw std::logic_error(
            "workspace init: workspace already set to a different root; reset first");
    }

    save_workspace_root(app_, candidate.root());
    ws_ = std::move(candidate);
    canonical_root_ = can;
}

bool WorkspaceLifecycle::init_from_saved_or_environment() {
    const auto root = resolve_workspace_root_if_any(app_);
    if (root.empty()) {
        return false;
    }
    init(root);
    return true;
}

void WorkspaceLifecycle::reset() noexcept {
    clear_workspace_root(app_);
    ws_.reset();
    canonical_root_.clear();
}

void WorkspaceLifecycle::create_required_dirs(const Workspace& ws) {
    for (const auto& dir : {ws.export_dir(), ws.dump_dir(), ws.logs_dir(), ws.session_dir()}) {
        std::error_code ec;
        std::filesystem::create_directories(dir, ec);
        if (ec) {
            throw std::runtime_error(
                "workspace init: failed to create required directory: '" +
                dir.string() + "': " + ec.message());
        }
    }
}

std::string WorkspaceLifecycle::compute_canonical_root_string(const std::filesystem::path& root) {
    std::error_code ec;
    const auto can = std::filesystem::canonical(root, ec);
    if (!ec) {
        return can.lexically_normal().string();
    }
    ec.clear();
    const auto wcan = std::filesystem::weakly_canonical(root, ec);
    if (!ec) {
        return wcan.lexically_normal().string();
    }
    return root.lexically_normal().string();
}

} // namespace tonb::foundation::workspace
