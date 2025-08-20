//
// Created by amir on 8/20/25.
//
#include <tonb/system/log.hxx>

// Optional: show Task + RunGuard + progress if your header exists
#if __has_include("tonb/system/task.hxx")
#include <tonb/system/task.hxx>
#include <tonb/system/run_context.hxx>
#define TONB_DEMO_HAS_TASKS 1
#endif

#include <thread>
#include <chrono>
#include <cstring>
#include <cstdlib>

using namespace tonb::system;
using namespace std::chrono_literals;

// --- Optional: spdlog sink (only if you enabled TONB_WITH_SPDLOG and vcpkg provides spdlog)
#ifdef TONB_WITH_SPDLOG
#include <spdlog/spdlog.h>
#endif

int main() {
    // 1) Build a root logger with Console + JSON + Buffered sinks
    auto root = std::make_shared<Logger>(LogLevel::debug, "Demo");
    root->clear_sinks();

    // console: human-friendly (colours + timestamps)
    root->add_sink(std::make_shared<ConsoleSink>(true, true));

    // NDJSON file: machine-friendly
    root->add_sink(std::make_shared<JsonFileSink>("logs.ndjson"));

    // BufferedText: reproduces the "old logger" behaviour (flush/rewind/etc.)
    auto buffered = std::make_shared<BufferedTextSink>([](const std::string& s) {std::fwrite(s.data(), 1, s.size(), stdout);});
    buffered->set_max_buffer_size(256*1024);
    buffered->set_auto_flush_on_overflow(true);
    root->add_sink(buffered);

    // Optional: spdlog sink
#ifdef TONB_WITH_SPDLOG
    if (auto sp = spdlog::stdout_color_mt("spd-demo")) {
        root->add_sink(std::make_shared<SpdlogSink>(sp));
    }
#endif

    // 2) Contexts: child loggers tag all records with component + (optional) task_id
    auto app = root->with_context("App");
    auto ser = root->with_context("Serialization");
    auto net = root->with_context("Network");

    // 3) Basic logs + structured fields (source location captured automatically)
    app->info("application start", {{"version", "1.0,0"}, {"mode", "demo"}});
    ser->debug("preparing buffers", {{"bytes", "16384"}});
    net->warn("slow DNS response", {{"ms", "1200"}});

    // 4) Scope timing: auto "started/finished ... duration_ms=..."
    {
        Logger::Scope phase(app, LogLevel::info, "initialisation");
        std::this_thread::sleep_for(50ms);
        app->debug("init step", {{"step", "load-config"}});
        std::this_thread::sleep_for(30ms);
    } // <- logs finish + duration

    // 5) Rate limiting: keep repeated warnings from spamming
    RateLimiter lim(750); // 750 ms per key
    for (int i = 0; i < 5; ++i) {
        if (lim.allow("noisy-warning"))
            app->warn("intermittent sensor glitch", {{"count", std::to_string(i)}});
        std::this_thread::sleep_for(250ms);
    }

    // 6) BufferedTextSink controls: build some lines, then rewind & flush
    app->info("buffered line A");
    app->info("buffered line B");
    // Oops, second line was premature - roll back to the last flushed snapshot:
    root->rewind_to_last(); // Buffered sink restores last flushed content
    // Now add a corrected line and flush everything out:
    app->info("buffered line B (corrected)");
    root->flush();

#if TONB_DEMO_HAS_TASKS
    // 7) Task integration: RunGuard logs start/finish; progress & cancellation
    class DemoTask : public Task {
    public:
        using Task::Task; // inherit ctor (name, logger)

        void run(const RunContext&) override {
            RunGuard guard(*this); // sets Running, logs "started", times run
            try {
                constexpr int steps = 40;
                for (int i = 0; i < steps; ++i) {
                    if (is_cancellation_requested()) {
                        set_status(TaskStatus::cancelled);
                        log(LogLevel::warn, "cancellation observed");
                        return;
                    }
                    // pretend work
                    std::this_thread::sleep_for(20ms);
                    // log occasionally with structured context
                    if ((i % 10) == 0) {
                        log(LogLevel::info, "milestone", {{"i", std::to_string(i)}, {"steps", std::to_string(steps)}});
                    }
                    report_progress(static_cast<double>(i + 1) / steps);
                }
                set_status(TaskStatus::succeeded);
            } catch (...) {
                set_status(TaskStatus::failed);
                log(LogLevel::error, "exception escaped from run()");
                throw;
            }
        }
    };

    auto tlog = root->with_context("Task");
    DemoTask t("DemoTask", tlog);
    t.set_progress_callback([&](double p) {
        app->debug("progress update", {{"p", std::to_string(p)}});
    });

    // run in a worker thread; cancel part-way to demo Cancelled + guard footer
    std::thread worker([&]{t.run({});});
    std::this_thread::sleep_for(250ms);
    t.request_cancel();
    worker.join();
    app->info("task final status", {{"status", (t.status() == TaskStatus::succeeded ? "Succeeded":
        t.status() == TaskStatus::cancelled ? "Cancelled" :
        t.status() == TaskStatus::failed? "Failed" : "Other")}});
#else
    app->warn("Task demo skipped (tonb/system/task.hss not found)");
#endif

    app->info("application shutdown");
    // final explicit flush (Buffered/Json/console where applicable)
    root->flush();
    return EXIT_SUCCESS;
}