/**
 * @file log_context.cxx
 * @brief Implementation of thread-local logging context and RAII scopes.
 */
#include <tonb/foundation/logger/log_context.hxx>
#include <tonb/foundation/logger/logger.hxx>

#include <atomic>
#include <iomanip>
#include <sstream>

namespace tonb::foundation::log {
    namespace {
        std::atomic<std::uint64_t> g_task_counter{0};
        thread_local Context g_context{};
        thread_local std::shared_ptr<Logger> g_active_logger{};
    }

    Context& current_context() noexcept {
        return g_context;
    }

    std::string current_command_path() {
        const auto& context = current_context();
        if (context.command_stack.empty()) {
            return {};
        }

        std::string out;
        for (std::size_t i = 0; i < context.command_stack.size(); ++i) {
            if (i != 0) {
                out += " > ";
            }
            out += context.command_stack[i];
        }
        return out;
    }

    std::string new_task_id() {
        const auto value = g_task_counter.fetch_add(1, std::memory_order_relaxed) + 1;
        std::ostringstream oss;
        oss << "job-" << std::setw(6) << std::setfill('0') << value;
        return oss.str();
    }

    Logger& active_logger() noexcept {
        if (g_active_logger) {
            return *g_active_logger;
        }
        return Logger::global();
    }

    TaskScope::TaskScope(std::string task_id) {
        auto& context = current_context();
        previous_ = context.task_id;
        context.task_id = std::move(task_id);
    }

    TaskScope::~TaskScope() {
        auto& context = current_context();
        context.task_id = std::move(previous_);
    }

    CommandScope::CommandScope(std::string command_segment) {
        auto& context = current_context();
        previous_depth_ = context.command_stack.size();
        context.command_stack.push_back(std::move(command_segment));
    }

    CommandScope::~CommandScope() {
        auto& context = current_context();
        while (context.command_stack.size() > previous_depth_) {
            context.command_stack.pop_back();
        }
    }

    LevelScope::LevelScope(const Level threshold) {
        auto& context = current_context();
        previous_ = context.level_override;
        context.level_override = threshold;
    }

    LevelScope::~LevelScope() {
        auto& context = current_context();
        context.level_override = previous_;
    }

    LoggerScope::LoggerScope(std::shared_ptr<Logger> logger)
        : current_(std::move(logger)), previous_(g_active_logger) {
        if (current_) {
            g_active_logger = current_;
        }
    }

    LoggerScope::~LoggerScope() {
        g_active_logger = std::move(previous_);
    }

} // namespace tonb::foundation::log
