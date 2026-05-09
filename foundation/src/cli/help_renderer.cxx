/**
 * @file help_renderer.cxx
 * @brief Plain-text rendering for the foundation CLI metadata model.
 */
#include <tonb/foundation/cli/help_renderer.hxx>
#include <tonb/foundation/cli/text_table.hxx>

#include <algorithm>
#include <sstream>

namespace tonb::foundation::cli {

    namespace {
        std::string indent(const int n) {
            return std::string(static_cast<std::size_t>(std::max(0, n)), ' ');
        }

        std::string ansi_wrap(const ColourMode mode, const std::string_view code, const std::string& text) {
            if (mode != ColourMode::ansi) {
                return text;
            }
            return std::string("\033[") + std::string(code) + "m" + text + "\033[0m";
        }

        std::string bold(const ColourMode mode, const std::string& text) {
            return ansi_wrap(mode, "1", text);
        }

        std::string dim(const ColourMode mode, const std::string& text) {
            return ansi_wrap(mode, "2", text);
        }

        std::vector<std::string> wrap_words(const std::string& text, const int width) {
            if (width <= 0 || static_cast<int>(text.size()) <= width) {
                return {text};
            }

            std::vector<std::string> lines;
            std::istringstream iss(text);
            std::string word;
            std::string current;

            while (iss >> word) {
                if (current.empty()) {
                    current = word;
                } else if (static_cast<int>(current.size() + 1 + word.size()) <= width) {
                    current += ' ';
                    current += word;
                } else {
                    lines.push_back(current);
                    current = word;
                }
            }

            if (!current.empty()) {
                lines.push_back(current);
            }
            if (lines.empty()) {
                lines.push_back({});
            }
            return lines;
        }

        void append_paragraph(std::ostringstream& oss, const std::string& text, const int first_indent, const int continuation_indent, const int width) {
            const int first_width = width <= 0 ? width : std::max(0, width - first_indent);
            const int cont_width = width <= 0 ? width : std::max(0, width - continuation_indent);
            const auto lines = wrap_words(text, first_width);
            if (lines.empty()) {
                oss << indent(first_indent) << '\n';
                return;
            }
            oss << indent(first_indent) << lines.front() << '\n';
            for (std::size_t i = 1; i < lines.size(); ++i) {
                const auto parts = wrap_words(lines[i], cont_width);
                for (const auto& part : parts) {
                    oss << indent(continuation_indent) << part << '\n';
                }
            }
        }

        std::string stability_label(const CommandStability stability) {
            switch (stability) {
                case CommandStability::stable: return "stable";
                case CommandStability::experimental: return "experimental";
                case CommandStability::deprecated: return "deprecated";
            }
            return "unknown";
        }

        std::string visibility_label(const CommandVisibility visibility) {
            switch (visibility) {
                case CommandVisibility::public_command: return "public";
                case CommandVisibility::hidden_command: return "hidden";
                case CommandVisibility::internal_command: return "internal";
            }
            return "unknown";
        }
    }

    std::string render_command(const CommandSpec& spec, const RenderOptions& options) {
        std::ostringstream oss;

        oss << bold(options.colour, spec.canonical_path.to_string()) << '\n';
        oss << indent(2) << spec.summary << '\n';

        for (const auto& paragraph : spec.description) {
            if (!paragraph.empty()) {
                oss << '\n';
                append_paragraph(oss, paragraph, 2, 2, options.width);
            }
        }

        if (options.show_aliases && !spec.aliases.empty()) {
            oss << '\n' << bold(options.colour, "Aliases") << '\n';
            for (const auto& alias : spec.aliases) {
                oss << indent(options.section_indent) << alias.to_string() << '\n';
            }
        }

        if (!spec.usage.empty()) {
            oss << '\n' << bold(options.colour, "Usage") << '\n';
            for (const auto& line : spec.usage) {
                oss << indent(options.section_indent) << line << '\n';
            }
        }

        if (options.show_capabilities) {
            std::vector<std::string> capability_parts;
            capability_parts.push_back("visibility=" + visibility_label(spec.visibility));
            capability_parts.push_back("stability=" + stability_label(spec.stability));
            if (spec.capabilities.requires_workspace) capability_parts.push_back("requires-workspace");
            if (spec.capabilities.mutates_state) capability_parts.push_back("mutates-state");
            if (spec.capabilities.destructive) capability_parts.push_back("destructive");
            if (spec.capabilities.long_running) capability_parts.push_back("long-running");
            if (spec.capabilities.interactive) capability_parts.push_back("interactive");
            if (spec.capabilities.script_friendly) capability_parts.push_back("script-friendly");

            oss << '\n' << bold(options.colour, "Metadata") << '\n';
            oss << indent(options.section_indent);
            for (std::size_t i = 0; i < capability_parts.size(); ++i) {
                if (i > 0) oss << ", ";
                oss << capability_parts[i];
            }
            oss << '\n';
        }

        if (options.show_tags && !spec.tags.empty()) {
            oss << '\n' << bold(options.colour, "Tags") << '\n';
            oss << indent(options.section_indent);
            for (std::size_t i = 0; i < spec.tags.size(); ++i) {
                if (i > 0) oss << ", ";
                oss << spec.tags[i];
            }
            oss << '\n';
        }

        if (!spec.options.empty()) {
            oss << '\n' << bold(options.colour, "Options") << '\n';
            for (const auto& option : spec.options) {
                std::string label = option.label;
                if (options.show_defaults && !option.default_value.empty()) {
                    label += " " + dim(options.colour, "(default: " + option.default_value + ")");
                }
                oss << indent(options.section_indent) << label << '\n';
                append_paragraph(oss, option.description, options.continuation_indent, options.continuation_indent, options.width);
            }
        }

        if (!spec.examples.empty()) {
            oss << '\n' << bold(options.colour, "Examples") << '\n';
            for (const auto& example : spec.examples) {
                oss << indent(options.section_indent) << example << '\n';
            }
        }

        if (!spec.notes.empty()) {
            oss << '\n' << bold(options.colour, "Notes") << '\n';
            for (const auto& note : spec.notes) {
                append_paragraph(oss, note, options.section_indent, options.continuation_indent, options.width);
            }
        }

        if (options.show_deprecation && spec.deprecation.has_value()) {
            oss << '\n' << bold(options.colour, "Deprecation") << '\n';
            if (!spec.deprecation->replacement.empty()) {
                oss << indent(options.section_indent) << "Use: " << spec.deprecation->replacement << '\n';
            }
            if (!spec.deprecation->message.empty()) {
                append_paragraph(oss, spec.deprecation->message, options.section_indent, options.continuation_indent, options.width);
            }
        }

        return oss.str();
    }

    std::string render_listing(const std::vector<ListingEntry>& entries, const RenderOptions& options) {
        TextTable table({
            Column{.header = "Name", .min_width = static_cast<std::size_t>(std::max(0, options.listing_name_width)), .max_width = 0, .align = Align::left},
            Column{.header = "Kind", .min_width = 10, .max_width = 0, .align = Align::left},
            Column{.header = "Summary", .min_width = 0, .max_width = 0, .align = Align::left}
        });

        for (const auto& entry : entries) {
            std::string kind = entry.is_namespace ? "namespace" : "command";
            if (entry.alias_entry) {
                kind = "alias";
            }
            std::string summary = entry.summary;
            if (entry.alias_entry && !entry.alias_target.empty()) {
                summary += " -> " + entry.alias_target;
            }
            table.add_row({entry.path.to_string(), kind, summary});
        }

        std::ostringstream oss;
        for (const auto& line : table.render_lines()) {
            oss << line << '\n';
        }
        return oss.str();
    }

    std::string render_namespace(const CommandRegistry& registry, const CommandPath& prefix, const RenderOptions& options) {
        std::ostringstream oss;
        oss << bold(options.colour, prefix.empty() ? std::string("root") : prefix.to_string()) << '\n';

        if (const auto* ns = registry.find_namespace(prefix); ns != nullptr && !ns->summary.empty()) {
            oss << indent(2) << ns->summary << '\n';
        }

        const auto entries = registry.list_direct_children(prefix, options.show_hidden, options.show_aliases);
        if (!entries.empty()) {
            oss << '\n' << bold(options.colour, "Children") << '\n';
            oss << render_listing(entries, options);
        }

        return oss.str();
    }

} // namespace tonb::foundation::cli
