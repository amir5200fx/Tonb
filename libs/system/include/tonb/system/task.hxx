//
// Created by amir on 8/19/25.
//
#pragma once
#ifndef TONB_SYSTEM_TASK_HXX
#define TONB_SYSTEM_TASK_HXX

#include <tonb/system/module.hxx>
#include <tonb/system/run_context.hxx>
#include <tonb/system/log.hxx>

#include <atomic>
#include <chrono>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <utility>

namespace tonb::system {

/**
 * @enum TaskStatus
 * @brief Execution state of a Task.
 *
 * pending   -> created but not started
 * Running   -> run() is executing
 * Succeeded -> finished without error
 * Failed    -> finished with an error
 * Cancelled -> cooperative stop by request
 */
enum class TaskStatus : unsigned char {
    pending,
    running,
    succeeded,
    failed,
    cancelled
};

/**
 * @class Task
 * @brief Base class for executable work with status, cancellation, progress, and logging.
 *
 * Usage pattern for derived classes:
 * @code
 * class MyTask : public Task {
 * public:
 *   using Task::Task; // inherit ctor to pass name and logger
 *
 *   void run(const RunContext& ctx) override {
 *     RunGuard guard(*this);           // sets Running, logs "started", times execution
 *     try {
 *       // ... your work, use ctx as needed ...
 *       if (is_cancellation_requested()) {
 *         set_status(TaskStatus::Cancelled);
 *         return;
 *       }
 *       report_progress(1.0);
 *       set_status(TaskStatus::Succeeded);
 *     } catch (...) {
 *       set_status(TaskStatus::Failed);
 *       log(LogLevel::Error, "exception thrown");
 *       throw; // or swallow depending on policy
 *     }
 *   }
 * };
 * @endcode
 */
class Task {
public:
    using Clock = std::chrono::steady_clock;
    using ProgressCallback = std::function<void(double)>;  // range [0.0, 1.0]

    /// Construct with a human-friendly name and optional shared logger.
    explicit Task(std::string name = "Task",
                  std::shared_ptr<Logger> logger = default_logger())
        : name_(std::move(name))
        , id_(next_id())
        , logger_(std::move(logger))
    {}

    virtual ~Task() = default;

    /**
     * @brief Execute the task. Implement this in derived classes.
     * @note Respect cancellation by polling is_cancellation_requested().
     * @note Prefer using RunGuard at the top of the implementation.
     */
    virtual void run(const RunContext& ctx) = 0;

    // -------- Status --------
    TNB_NODISCARD TaskStatus status() const noexcept { return status_.load(std::memory_order_acquire); }

    TNB_NODISCARD bool is_done() const noexcept {
        const auto s = status_.load(std::memory_order_acquire);
        return s == TaskStatus::succeeded || s == TaskStatus::failed || s == TaskStatus::cancelled;
    }

    // -------- Cancellation (cooperative) --------
    void request_cancel() noexcept { cancel_requested_.store(true, std::memory_order_release); }

    TNB_NODISCARD bool is_cancellation_requested() const noexcept {
        return cancel_requested_.load(std::memory_order_acquire);
    }

    // -------- Progress --------
    TNB_NODISCARD double progress() const noexcept { return progress_.load(std::memory_order_acquire); }

    /**
     * @brief Register a callback that is invoked whenever progress changes.
     * @warning The callback is invoked on the thread that calls report_progress().
     *          Marshal to your UI thread if needed.
     */
    void set_progress_callback(ProgressCallback cb) {
        std::lock_guard<std::mutex> lock(cb_mutex_);
        progress_cb_ = std::move(cb);
    }

    // -------- Identity / Logger --------
    TNB_NODISCARD std::string_view name() const noexcept { return name_; }
    TNB_NODISCARD std::string id() const { return id_; }

    void set_logger(std::shared_ptr<Logger> lg) { logger_ = std::move(lg); }
    TNB_NODISCARD std::shared_ptr<Logger> logger() const { return logger_; }

protected:
    // -------- Helpers for derived classes --------
    void set_status(const TaskStatus s) noexcept {
        const auto prev = status_.exchange(s, std::memory_order_acq_rel);
        if (logger_ && prev != s) {
            logger_->log(LogLevel::debug,
                         std::string("status -> ") + status_to_string(s),
                         /*fields*/{});
        }
    }

    /**
     * @brief Report progress in [0,1]. Clamped. Avoids duplicate callbacks.
     */
    void report_progress(double p) {
        if (p < 0.0) p = 0.0;
        if (p > 1.0) p = 1.0;

        const double old = progress_.exchange(p, std::memory_order_acq_rel);
        if (old == p) return;

        ProgressCallback cb_copy;
        {
            std::lock_guard<std::mutex> lock(cb_mutex_);
            cb_copy = progress_cb_;
        }
        if (cb_copy) cb_copy(p);
    }

    /// Convenience to increment progress by dp.
    void advance_progress(const double dp) { report_progress(progress() + dp); }

    /// Log with the task’s logger, enriched with name and id.
    void log(const LogLevel lvl, const std::string_view msg) {
        if (logger_) {
            // Use a child logger with fixed context if available.
            auto child = logger_->with_context(std::string(name_), id_);
            child->log(lvl, msg);
        }
    }

public:
    /**
     * @brief RAII guard to mark a run as started and log finish with duration.
     *
     * Creates a child logger with component=name() and task_id=id().
     * Sets status to Running and progress to 0.0 on construction.
     * On destruction, logs the end and duration, choosing level by final status.
     */
    class RunGuard {
    public:
        explicit RunGuard(Task& t)
            : task_(t)
            , start_(Clock::now())
        {
            task_.set_status(TaskStatus::running);
            task_.report_progress(0.0);

            if (task_.logger_) {
                logger_ = task_.logger_->with_context(std::string(task_.name_), task_.id_);
                logger_->info("started");
            }
        }

        ~RunGuard() {
            using std::chrono::duration_cast;
            using std::chrono::milliseconds;

            const auto ms = duration_cast<milliseconds>(Clock::now() - start_).count();
            if (!logger_) return;

            const auto msg = std::string("finished in ") + std::to_string(ms) + " ms";
            switch (task_.status()) {
                case TaskStatus::succeeded: logger_->info(msg); break;
                case TaskStatus::cancelled: logger_->warn(msg); break;
                case TaskStatus::failed:    logger_->error(msg); break;
                default:                    logger_->warn(msg); break;
            }
        }

    private:
        Task& task_;
        Clock::time_point start_;
        std::shared_ptr<Logger> logger_;
    };

private:
    // -------- Internals --------
    static std::shared_ptr<Logger> default_logger() {
        static std::shared_ptr<Logger> lg = std::make_shared<Logger>(LogLevel::info, "Task");
        return lg;
    }

    static std::string next_id() {
        static std::atomic<unsigned long long> c{0};
        return std::to_string(++c);
    }

    static const char* status_to_string(const TaskStatus s) {
        switch (s) {
            case TaskStatus::pending:   return "pending";
            case TaskStatus::running:   return "Running";
            case TaskStatus::succeeded: return "Succeeded";
            case TaskStatus::failed:    return "Failed";
            case TaskStatus::cancelled: return "Cancelled";
        }
        return "Unknown";
    }

private:
    // Identity and logging
    std::string name_;
    std::string id_;
    std::shared_ptr<Logger> logger_;

    // State
    std::atomic<TaskStatus> status_{TaskStatus::pending};
    std::atomic<bool>       cancel_requested_{false};
    std::atomic<double>     progress_{0.0};

    // Progress callback
    std::mutex        cb_mutex_;
    ProgressCallback  progress_cb_;
};

} // namespace tonb::system
#endif // TONB_SYSTEM_TASK_HXX
