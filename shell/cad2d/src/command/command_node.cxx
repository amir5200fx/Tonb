#include <sstream>
#include <stdexcept>

#include <tonb/cad2d/shell/command/command_node.hxx>

namespace tonb::cad2d::shell::command {

    namespace {
        std::vector<std::string> validate_segments(std::vector<std::string> segments) {
            if (segments.empty()) {
                throw std::invalid_argument("command path must contain at least one segment");
            }
            for (const auto& segment : segments) {
                if (segment.empty()) {
                    throw std::invalid_argument("command path segments must not be empty");
                }
            }
            return segments;
        }
    }

    CommandPath::CommandPath(std::vector<std::string> segments)
        : segments_(validate_segments(std::move(segments))) {
    }

    CommandPath::CommandPath(std::initializer_list<std::string> segments)
        : segments_(validate_segments(std::vector<std::string>(segments))) {
    }

    std::string CommandPath::to_string() const {
        std::ostringstream stream;
        for (std::size_t i = 0; i < segments_.size(); ++i) {
            if (i != 0) {
                stream << ' ';
            }
            stream << segments_[i];
        }
        return stream.str();
    }

} // namespace tonb::cad2d::shell::command
