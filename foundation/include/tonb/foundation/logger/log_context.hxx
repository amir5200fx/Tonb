/**
 * @file log_context.hxx
 * @brief Thread-local execution context automatically attached to log records.
 *
 * @details
 * This header defines a small thread-local context model and several RAII
 * scopes used to populate it:
 *
 * - TaskScope   : installs a task/job correlation id
 * - CommandScope: pushes a command path component
 * - LevelScope  : installs a per-thread threshold override
 * - LoggerScope : installs a thread-local logger override
 *
 * Compared with other implementations, this version stores only a
 * command stack and derives the flattened command path on demand. This removes
 * the earlier split-brain `cmd` versus `cmd_stack` state.
 */
#pragma once
#ifndef TONB_FOUNDATION_LOG_CONTEXT_HXX
#define TONB_FOUNDATION_LOG_CONTEXT_HXX

#include <tonb/foundation/logger/log_level.hxx>
#include <tonb/foundation/module.hxx>

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace tonb::foundation::log {

    class Logger;

    /**
     * @brief Per-thread logging context.
     */
    struct Context {
        /** @brief Correlation id for a background task or job, if any. */
        std::string task_id;

        /** @brief Nested command path components, outermost first. */
        std::vector<std::string> command_stack;

        /** @brief Optional per-thread level override. */
        std::optional<Level> level_override;
    };

    /** @brief Return the current thread-local context. */
    TNBFOUND_ND_EXPORT Context& current_context() noexcept;

    /** @brief Return the current command path flattened with " > ". */
    TNBFOUND_ND_EXPORT std::string current_command_path();

    /** @brief Generate a deterministic task id such as "job-000001". */
    TNBFOUND_ND_EXPORT std::string new_task_id();

    /**
     * @brief Return the active logger for the current thread.
     *
     * If no thread-local override exists, the process-global logger is returned.
     */
    TNBFOUND_ND_EXPORT Logger& active_logger() noexcept;

    /**
     * @brief RAII scope that sets the current thread's task id.
     */
    class TaskScope {
    public:
        explicit TNBFOUND_EXPORT TaskScope(std::string task_id);
        TNBFOUND_EXPORT ~TaskScope();
        TaskScope(const TaskScope&) = delete;
        TaskScope& operator=(const TaskScope&) = delete;
    private:
        std::string previous_;
    };

    /**
     * @brief RAII scope that appends one command path segment.
     */
    class CommandScope {
    public:
        explicit TNBFOUND_EXPORT CommandScope(std::string command_segment);
        TNBFOUND_EXPORT ~CommandScope();
        CommandScope(const CommandScope&) = delete;
        CommandScope& operator=(const CommandScope&) = delete;
    private:
        std::size_t previous_depth_ = 0;
    };

    /**
     * @brief RAII scope that overrides the log level threshold for the current thread.
     */
    class LevelScope {
    public:
        explicit TNBFOUND_EXPORT LevelScope(Level threshold);
        TNBFOUND_EXPORT ~LevelScope();
        LevelScope(const LevelScope&) = delete;
        LevelScope& operator=(const LevelScope&) = delete;
    private:
        std::optional<Level> previous_;
    };

    /**
     * @brief RAII scope that installs a thread-local logger override.
     */
    class LoggerScope {
    public:
        explicit TNBFOUND_EXPORT LoggerScope(std::shared_ptr<Logger> logger);
        TNBFOUND_EXPORT ~LoggerScope();
        LoggerScope(const LoggerScope&) = delete;
        LoggerScope& operator=(const LoggerScope&) = delete;
    private:
        std::shared_ptr<Logger> current_;
        std::shared_ptr<Logger> previous_;
    };

} // namespace tonb::foundation::log

#endif // TONB_FOUNDATION_LOG_CONTEXT_HXX
