#include <algorithm>
#include <optional>
#include <sstream>
#include <stdexcept>

#include <tonb/cad2d/shell/command/command_registry.hxx>

namespace tonb::cad2d::shell::command {

    void CommandRegistry::add_command(CommandPath path, CommandHandler handler) {
        if (!handler) {
            throw std::invalid_argument("cannot register command without handler");
        }
        if (commands_.contains(path)) {
            throw std::invalid_argument("command already registered: '" + path.to_string() + "'");
        }
        if (aliases_.contains(path)) {
            throw std::invalid_argument("cannot register command path already used by alias: '" + path.to_string() + "'");
        }
        commands_.emplace(std::move(path), RegisteredCommand{std::move(handler)});
    }

    void CommandRegistry::add_alias(CommandPath alias, const CommandPath& target) {
        if (!commands_.contains(target)) {
            throw std::invalid_argument("cannot register alias for missing command: '" + target.to_string() + "'");
        }
        if (commands_.contains(alias)) {
            throw std::invalid_argument("cannot register alias path already used by command: '" + alias.to_string() + "'");
        }
        if (aliases_.contains(alias)) {
            throw std::invalid_argument("alias already registered: '" + alias.to_string() + "'");
        }
        aliases_.emplace(std::move(alias), target);
    }

    std::vector<CommandNode> CommandRegistry::nodes() const {
        std::vector<CommandNode> result;
        result.reserve(commands_.size());

        for (const auto& [path, _] : commands_) {
            result.push_back(CommandNode{path, aliases_for(path)});
        }
        return result;
    }

    std::vector<CommandPath> CommandRegistry::command_paths() const {
        std::vector<CommandPath> result;
        result.reserve(commands_.size());
        for (const auto& [path, _] : commands_) {
            result.push_back(path);
        }
        return result;
    }

    std::vector<CommandPath> CommandRegistry::aliases_for(const CommandPath& canonical) const {
        std::vector<CommandPath> result;
        for (const auto& [alias, target] : aliases_) {
            if (target == canonical) {
                result.push_back(alias);
            }
        }
        std::sort(result.begin(), result.end());
        return result;
    }

    std::optional<CommandLookup> CommandRegistry::resolve(const std::vector<std::string>& tokens) const {
        std::optional<CommandLookup> best;

        for (const auto& [path, _] : commands_) {
            if (starts_with(tokens, path)) {
                const CommandLookup candidate{path, path, false, path.size()};
                if (!best.has_value() || candidate.consumed_tokens > best->consumed_tokens) {
                    best = candidate;
                }
            }
        }

        for (const auto& [alias, target] : aliases_) {
            if (starts_with(tokens, alias)) {
                const CommandLookup candidate{alias, target, true, alias.size()};
                if (!best.has_value() || candidate.consumed_tokens > best->consumed_tokens) {
                    best = candidate;
                }
            }
        }

        return best;
    }

    CommandResult CommandRegistry::dispatch(const std::vector<std::string>& tokens,
                                            const CommandContext& context) const {
        const auto lookup = resolve(tokens);
        if (!lookup.has_value()) {
            return CommandResult::failure("unknown command");
        }

        const auto it = commands_.find(lookup->canonical_path);
        if (it == commands_.end()) {
            return CommandResult::failure("resolved command has no handler: '" + lookup->canonical_path.to_string() + "'");
        }

        std::vector<std::string> remainder;
        remainder.reserve(tokens.size() >= lookup->consumed_tokens ? tokens.size() - lookup->consumed_tokens : 0);
        for (std::size_t i = lookup->consumed_tokens; i < tokens.size(); ++i) {
            remainder.push_back(tokens[i]);
        }

        return it->second.handler(context, CommandArgs{std::move(remainder)});
    }

    std::string CommandRegistry::key_from(const CommandPath& path) {
        return path.to_string();
    }

    bool CommandRegistry::starts_with(const std::vector<std::string>& tokens, const CommandPath& path) {
        if (tokens.size() < path.size()) {
            return false;
        }
        for (std::size_t i = 0; i < path.size(); ++i) {
            if (tokens[i] != path.segments()[i]) {
                return false;
            }
        }
        return true;
    }

} // namespace tonb::cad2d::shell::command
