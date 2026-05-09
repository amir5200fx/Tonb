/**
 * @file command_path.hxx
 * @brief Deterministic command-path value object for the Tonb foundation CLI module.
 *
 * @details
 * This header defines @ref tonb::foundation::cli::CommandPath, a small utility
 * type used throughout the CLI foundation layer to represent canonical command
 * names such as:
 *
 * - `help`
 * - `workspace init`
 * - `geom hull build`
 *
 * The type is intentionally shell-agnostic. It does not know anything about
 * command execution, sessions, handlers, or application state. Its sole purpose
 * is to provide a reusable, validated representation for command and namespace
 * paths.
 *
 * Design goals:
 * - deterministic ordering and comparison
 * - validation of empty segments
 * - cheap conversion to and from token vectors
 * - stable textual rendering using single-space separation
 */
#pragma once
#ifndef TONB_FOUNDATION_CLI_COMMAND_PATH_HXX
#define TONB_FOUNDATION_CLI_COMMAND_PATH_HXX

#include <tonb/foundation/module.hxx>

#include <compare>
#include <string>
#include <string_view>
#include <vector>

namespace tonb::foundation::cli {

    /**
     * @brief Value type representing a shell-style command path.
     *
     * @details
     * A command path is an ordered list of non-empty segments. Examples:
     *
     * - `{ "help" }`
     * - `{ "workspace", "status" }`
     * - `{ "geom", "propeller", "build" }`
     *
     * The path compares lexicographically using its segment vector, making it
     * suitable for use as a deterministic map key.
     */
    class CommandPath final {
    public:
        /**
         * @brief Construct an empty path.
         */
        CommandPath() = default;

        /**
         * @brief Construct from an explicit list of segments.
         *
         * @param segments Ordered path segments.
         *
         * @throws std::invalid_argument If any segment is empty.
         */
        explicit CommandPath(std::vector<std::string> segments);

        /**
         * @brief Construct from an initializer-list of segments.
         *
         * @param segments Ordered path segments.
         *
         * @throws std::invalid_argument If any segment is empty.
         */
        CommandPath(std::initializer_list<std::string> segments);

        /**
         * @brief Build a path from a token vector.
         *
         * @param segments Ordered path segments.
         * @return Constructed command path.
         */
        TNBFOUND_ND_EXPORT static CommandPath from_segments(const std::vector<std::string>& segments);

        /**
         * @brief Parse a space-separated command string into a path.
         *
         * @param text Input command string.
         * @return Parsed command path.
         *
         * @throws std::invalid_argument If the text is empty or contains empty segments.
         */
        TNBFOUND_ND_EXPORT static CommandPath parse(std::string_view text);

        /**
         * @brief Return true if the path contains no segments.
         */
        TNB_NODISCARD bool empty() const noexcept { return segments_.empty(); }

        /**
         * @brief Return the number of segments in the path.
         */
        TNB_NODISCARD std::size_t size() const noexcept { return segments_.size(); }

        /**
         * @brief Access the underlying path segments.
         */
        TNB_NODISCARD const std::vector<std::string>& segments() const noexcept { return segments_; }

        /**
         * @brief Access a single segment by index.
         *
         * @param index Segment index.
         * @return Segment text.
         *
         * @throws std::out_of_range If @p index is out of range.
         */
        TNB_NODISCARD const std::string& at(std::size_t index) const;

        /**
         * @brief Return the last segment in the path.
         *
         * @throws std::logic_error If the path is empty.
         */
        TNB_NODISCARD const std::string& leaf() const;

        /**
         * @brief Return a parent prefix of the path.
         *
         * @return Parent path.
         *
         * @throws std::logic_error If the path is empty.
         */
        TNBFOUND_ND_EXPORT CommandPath parent() const;

        /**
         * @brief Return a new path formed by appending a segment.
         *
         * @param segment Segment to append.
         * @return Extended path.
         *
         * @throws std::invalid_argument If @p segment is empty.
         */
        TNBFOUND_ND_EXPORT CommandPath child(std::string segment) const;

        /**
         * @brief Return true if this path starts with @p prefix.
         *
         * @param prefix Prefix path.
         * @return True when the prefix matches exactly.
         */
        TNB_NODISCARD bool starts_with(const CommandPath& prefix) const noexcept;

        /**
         * @brief Render the path as a single space-separated command string.
         */
        TNBFOUND_ND_EXPORT std::string to_string() const;

        /**
         * @brief Lexicographic three-way comparison.
         */
        auto operator<=>(const CommandPath&) const = default;

        /**
         * @brief Equality comparison.
         */
        bool operator==(const CommandPath&) const = default;

    private:
        /**
         * @brief Validate all segments are non-empty.
         *
         * @throws std::invalid_argument If any segment is empty.
         */
        static void validate(const std::vector<std::string>& segments);

        /**
         * @brief Ordered path segments.
         */
        std::vector<std::string> segments_;
    };

} // namespace tonb::foundation::cli

#endif // TONB_FOUNDATION_CLI_COMMAND_PATH_HXX
