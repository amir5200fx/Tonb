/**
 * @file command_registry.cxx
 * @brief Implementation of the deterministic foundation CLI registry.
 */
#include <tonb/foundation/cli/command_registry.hxx>

#include <algorithm>
#include <stdexcept>

namespace tonb::foundation::cli {

    namespace {
        bool is_visible(const CommandVisibility visibility, const bool include_hidden) {
            return include_hidden || visibility == CommandVisibility::public_command;
        }
    }

    void CommandRegistry::add_namespace(NamespaceSpec spec) {
        if (spec.path.empty()) {
            throw std::invalid_argument("CommandRegistry::add_namespace: namespace path must not be empty");
        }

        namespaces_.insert_or_assign(spec.path, std::move(spec));
    }

    void CommandRegistry::add_command(CommandSpec spec) {
        validate_command_spec(spec);

        const CommandPath canonical = spec.canonical_path;

        if (commands_.contains(canonical) || aliases_.contains(canonical)) {
            throw std::logic_error("CommandRegistry::add_command: canonical path already registered: " + canonical.to_string());
        }

        for (const auto& alias : spec.aliases) {
            if (commands_.contains(alias)) {
                throw std::logic_error("CommandRegistry::add_command: alias conflicts with canonical command: " + alias.to_string());
            }
            const auto it = aliases_.find(alias);
            if (it != aliases_.end() && it->second != canonical) {
                throw std::logic_error("CommandRegistry::add_command: alias conflict: " + alias.to_string());
            }
        }

        commands_.emplace(canonical, spec);
        for (const auto& alias : spec.aliases) {
            aliases_.insert_or_assign(alias, canonical);
        }
    }

    const CommandSpec* CommandRegistry::find_command(const CommandPath& path) const noexcept {
        const auto it = commands_.find(path);
        return it == commands_.end() ? nullptr : &it->second;
    }

    const NamespaceSpec* CommandRegistry::find_namespace(const CommandPath& path) const noexcept {
        const auto it = namespaces_.find(path);
        return it == namespaces_.end() ? nullptr : &it->second;
    }

    const CommandSpec* CommandRegistry::resolve_exact(const CommandPath& path) const noexcept {
        if (const auto* spec = find_command(path)) {
            return spec;
        }
        const auto it_alias = aliases_.find(path);
        if (it_alias == aliases_.end()) {
            return nullptr;
        }
        return find_command(it_alias->second);
    }

    ResolveResult CommandRegistry::resolve_longest_prefix(const std::vector<std::string>& tokens) const {
        ResolveResult result{};

        for (std::size_t depth = 1; depth <= tokens.size(); ++depth) {
            std::vector<std::string> candidate_segments(tokens.begin(), tokens.begin() + static_cast<std::ptrdiff_t>(depth));
            const CommandPath candidate(candidate_segments);

            if (const auto* spec = find_command(candidate)) {
                result.spec = spec;
                result.invoked_path = candidate;
                result.canonical_path = candidate;
                result.used_alias = false;
                result.matched_depth = depth;
            } else if (const auto it_alias = aliases_.find(candidate); it_alias != aliases_.end()) {
                result.spec = find_command(it_alias->second);
                result.invoked_path = candidate;
                result.canonical_path = it_alias->second;
                result.used_alias = true;
                result.matched_depth = depth;
            }
        }

        if (result.spec != nullptr) {
            result.remaining_args.assign(tokens.begin() + static_cast<std::ptrdiff_t>(result.matched_depth), tokens.end());
        }

        return result;
    }

    std::vector<const CommandSpec*> CommandRegistry::list_commands(const bool include_hidden) const {
        std::vector<const CommandSpec*> out;
        out.reserve(commands_.size());
        for (const auto& [path, spec] : commands_) {
            (void)path;
            if (is_visible(spec.visibility, include_hidden)) {
                out.push_back(&spec);
            }
        }
        return out;
    }

    std::vector<const NamespaceSpec*> CommandRegistry::list_namespaces(const bool include_hidden) const {
        std::vector<const NamespaceSpec*> out;
        out.reserve(namespaces_.size());
        for (const auto& [path, spec] : namespaces_) {
            (void)path;
            if (is_visible(spec.visibility, include_hidden)) {
                out.push_back(&spec);
            }
        }
        return out;
    }

    std::vector<ListingEntry> CommandRegistry::list_direct_children(
        const CommandPath& prefix,
        const bool include_hidden,
        const bool include_aliases) const {

        std::vector<ListingEntry> out;

        for (const auto& [path, ns] : namespaces_) {
            if (!is_visible(ns.visibility, include_hidden)) {
                continue;
            }
            if (!path.starts_with(prefix) || path.size() != prefix.size() + 1) {
                continue;
            }
            out.push_back(ListingEntry{
                .path = path,
                .summary = ns.summary,
                .is_namespace = true,
                .visibility = ns.visibility,
                .stability = ns.experimental ? CommandStability::experimental : CommandStability::stable,
                .alias_entry = false,
                .alias_target = {}
            });
        }

        for (const auto& [path, spec] : commands_) {
            if (!is_visible(spec.visibility, include_hidden)) {
                continue;
            }
            if (!path.starts_with(prefix) || path.size() != prefix.size() + 1) {
                continue;
            }
            out.push_back(ListingEntry{
                .path = path,
                .summary = spec.summary,
                .is_namespace = false,
                .visibility = spec.visibility,
                .stability = spec.stability,
                .alias_entry = false,
                .alias_target = {}
            });
        }

        if (include_aliases) {
            for (const auto& [alias, canonical] : aliases_) {
                if (!alias.starts_with(prefix) || alias.size() != prefix.size() + 1) {
                    continue;
                }
                const auto* spec = find_command(canonical);
                if (spec == nullptr || !is_visible(spec->visibility, include_hidden)) {
                    continue;
                }
                out.push_back(ListingEntry{
                    .path = alias,
                    .summary = spec->summary,
                    .is_namespace = false,
                    .visibility = spec->visibility,
                    .stability = spec->stability,
                    .alias_entry = true,
                    .alias_target = canonical.to_string()
                });
            }
        }

        std::sort(out.begin(), out.end(), [](const ListingEntry& a, const ListingEntry& b) {
            if (a.is_namespace != b.is_namespace) {
                return a.is_namespace && !b.is_namespace;
            }
            return a.path < b.path;
        });

        return out;
    }

    std::string CommandRegistry::alias_target(const CommandPath& alias) const noexcept {
        const auto it = aliases_.find(alias);
        return it == aliases_.end() ? std::string{} : it->second.to_string();
    }

} // namespace tonb::foundation::cli
