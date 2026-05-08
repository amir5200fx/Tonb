/**
 * @file workspace.cxx
 * @brief Implementation of deterministic workspace path modelling.
 */
#include <tonb/foundation/workspace/workspace.hxx>

#include <stdexcept>

namespace tonb::foundation::workspace {

namespace {

std::filesystem::path normalise_absolute_lexical(const std::filesystem::path& p) {
    if (p.empty()) {
        throw std::invalid_argument("Workspace: root path is empty");
    }
    std::filesystem::path abs = std::filesystem::absolute(p);
    return abs.lexically_normal();
}

bool is_within_base_lexical(const std::filesystem::path& base, const std::filesystem::path& child) {
    if (!base.is_absolute()) {
        throw std::invalid_argument("Workspace: base must be absolute");
    }
    if (!child.is_absolute()) {
        throw std::invalid_argument("Workspace: child must be absolute");
    }
    if (child == base) {
        return true;
    }
    const std::filesystem::path rel = child.lexically_relative(base);
    if (rel.empty()) {
        return false;
    }
    if (rel.has_root_path() || rel.has_root_name() || rel.is_absolute()) {
        return false;
    }
    const auto it = rel.begin();
    if (it != rel.end() && (*it) == "..") {
        return false;
    }
    return true;
}

const char* area_dir_name(const Area a) {
    switch (a) {
        case Area::export_: return "export";
        case Area::dump_: return "dump";
        case Area::logs_: return "logs";
        case Area::session_: return "session";
        default: throw std::out_of_range("Workspace: invalid Area");
    }
}

} // namespace

Workspace::Workspace(const std::filesystem::path& root)
    : root_(normalise_absolute_lexical(root)) {
    validate();
}

std::filesystem::path Workspace::dir(const Area a) const {
    return (root_ / area_dir_name(a)).lexically_normal();
}

std::filesystem::path Workspace::failure_bundles_dir() const {
    return (dump_dir() / "failure_bundles").lexically_normal();
}

std::filesystem::path Workspace::resolve_under(const Area a, const std::filesystem::path& p) const {
    return resolve_under(dir(a), p);
}

std::filesystem::path Workspace::resolve_under(const std::filesystem::path& base, const std::filesystem::path& p) const {
    if (p.empty()) {
        throw std::invalid_argument("Workspace: resolve_under: path is empty");
    }
    if (!base.is_absolute()) {
        throw std::invalid_argument("Workspace: resolve_under: base must be absolute");
    }
    const std::filesystem::path base_norm = base.lexically_normal();
    if (p.is_absolute()) {
        return p.lexically_normal();
    }
    std::filesystem::path out = (base_norm / p).lexically_normal();
    if (!out.is_absolute()) {
        throw std::logic_error("Workspace: resolved path is not absolute");
    }
    if (!is_within_base_lexical(base_norm, out)) {
        throw std::logic_error("Workspace: path escapes base directory");
    }
    return out;
}

void Workspace::validate() const {
    if (root_.empty()) {
        throw std::invalid_argument("Workspace: root empty after normalisation");
    }
    if (!root_.is_absolute()) {
        throw std::invalid_argument("Workspace: root must be absolute");
    }
}

} // namespace tonb::foundation::workspace
