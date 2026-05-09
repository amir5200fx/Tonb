/**
 * @file command_path.cxx
 * @brief Implementation of the command-path value object used by foundation CLI.
 */
#include <tonb/foundation/cli/command_path.hxx>

#include <cctype>
#include <sstream>
#include <stdexcept>

namespace tonb::foundation::cli {

    void CommandPath::validate(const std::vector<std::string>& segments) {
        for (const auto& segment : segments) {
            if (segment.empty()) {
                throw std::invalid_argument("CommandPath: empty path segment is not allowed");
            }
        }
    }

    CommandPath::CommandPath(std::vector<std::string> segments)
        : segments_(std::move(segments)) {
        validate(segments_);
    }

    CommandPath::CommandPath(std::initializer_list<std::string> segments)
        : segments_(segments) {
        validate(segments_);
    }

    CommandPath CommandPath::from_segments(const std::vector<std::string>& segments) {
        return CommandPath(segments);
    }

    CommandPath CommandPath::parse(std::string_view text) {
        std::vector<std::string> segments;
        std::string current;

        bool seen_non_space = false;
        for (const char ch : text) {
            if (std::isspace(static_cast<unsigned char>(ch)) != 0) {
                if (!current.empty()) {
                    segments.push_back(current);
                    current.clear();
                }
            } else {
                seen_non_space = true;
                current.push_back(ch);
            }
        }

        if (!current.empty()) {
            segments.push_back(current);
        }

        if (!seen_non_space || segments.empty()) {
            throw std::invalid_argument("CommandPath::parse: empty command text");
        }

        return CommandPath(std::move(segments));
    }

    const std::string& CommandPath::at(const std::size_t index) const {
        return segments_.at(index);
    }

    const std::string& CommandPath::leaf() const {
        if (segments_.empty()) {
            throw std::logic_error("CommandPath::leaf: path is empty");
        }
        return segments_.back();
    }

    CommandPath CommandPath::parent() const {
        if (segments_.empty()) {
            throw std::logic_error("CommandPath::parent: path is empty");
        }
        std::vector<std::string> prefix = segments_;
        prefix.pop_back();
        return CommandPath(std::move(prefix));
    }

    CommandPath CommandPath::child(std::string segment) const {
        if (segment.empty()) {
            throw std::invalid_argument("CommandPath::child: segment must not be empty");
        }
        std::vector<std::string> extended = segments_;
        extended.push_back(std::move(segment));
        return CommandPath(std::move(extended));
    }

    bool CommandPath::starts_with(const CommandPath& prefix) const noexcept {
        if (prefix.size() > size()) {
            return false;
        }
        for (std::size_t i = 0; i < prefix.size(); ++i) {
            if (segments_[i] != prefix.segments_[i]) {
                return false;
            }
        }
        return true;
    }

    std::string CommandPath::to_string() const {
        std::ostringstream oss;
        for (std::size_t i = 0; i < segments_.size(); ++i) {
            if (i > 0) {
                oss << ' ';
            }
            oss << segments_[i];
        }
        return oss.str();
    }

} // namespace tonb::foundation::cli
