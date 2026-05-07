//
// Created by amir on 8/19/25.
//
#include <gtest/gtest.h>
#include <atomic>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <tonb/system/run_context.hxx>
#include <tonb/system/task.hxx>

using namespace tonb::system;

// Simple task used for tests
class SleepyTask final : public Task {
public:
    explicit SleepyTask(int steps = 50, int ms_per_step = 2)
        : steps_(steps), ms_(ms_per_step) {}

    void run(const RunContext& ctx = RunContext{}) override {
        set_status(TaskStatus::running);
        report_progress(0.0);

        try {
            const bool fail = ctx.get_or<bool>("fail", false);
            const int  fail_at = ctx.get_or<int>("fail_at", steps_ / 3);

            for (int i = 0; i < steps_; ++i) {
                if (is_cancellation_requested()) {
                    set_status(TaskStatus::cancelled);
                    return;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(ms_));
                if (fail && i == fail_at) throw std::runtime_error("Injected failure");
                report_progress(static_cast<double>(i + 1) / steps_);
            }

            set_status(TaskStatus::succeeded);
        } catch (...) {
            set_status(TaskStatus::failed);
            throw;
        }
    }

private:
    int steps_;
    int ms_;
};

TEST(TaskTests, CompletesSuccessfully) {
    SleepyTask task(30, 1);
    std::atomic<int> ticks{0};
    double last = 0.0;

    // Run in the same thread, so callback is also on this thread
    task.set_progress_callback([&](double p){
        EXPECT_GE(p, last); // monotonic non-decreasing
        last = p;
        ++ticks;
    });

    RunContext ctx; // no failure flags
    task.run(ctx);

    EXPECT_TRUE(task.is_done());
    EXPECT_EQ(task.status(), TaskStatus::succeeded);
    EXPECT_GE(task.progress(), 0.999);
    EXPECT_GT(ticks.load(), 0);
}

TEST(TaskTests, CancelsCooperatively) {
    using namespace std::chrono_literals;
    SleepyTask task(200, 1);

    std::thread th([&]{ task.run(); });

    // Wait until some progress is made to avoid timing flakiness
    for (int i = 0; i < 200; ++i) {
        if (task.progress() >= 0.15) break;
        std::this_thread::sleep_for(1ms);
    }
    task.request_cancel();
    th.join();

    EXPECT_TRUE(task.is_done());
    EXPECT_EQ(task.status(), TaskStatus::cancelled);
    EXPECT_LT(task.progress(), 1.0);
}

TEST(TaskTests, FailsWithExceptionAndSetsStatus) {
    SleepyTask task(40, 1);

    RunContext ctx;
    ctx.set("fail", true);
    ctx.set("fail_at", 10);

    EXPECT_THROW(task.run(ctx), std::runtime_error);

    EXPECT_TRUE(task.is_done());
    EXPECT_EQ(task.status(), TaskStatus::failed);
    EXPECT_LT(task.progress(), 1.0);
}

TEST(TaskTests, ProgressCallbackCollectsSamples) {
    SleepyTask task(25, 1);

    std::vector<double> samples;
    samples.reserve(25);
    std::mutex m;

    task.set_progress_callback([&](double p){
        std::lock_guard<std::mutex> lock(m);
        samples.push_back(p);
    });

    task.run();

    // Check monotonicity after the run
    std::lock_guard<std::mutex> lock(m);
    ASSERT_FALSE(samples.empty());
    for (size_t i = 1; i < samples.size(); ++i) {
        EXPECT_LE(samples[i-1], samples[i]);
    }
    EXPECT_NEAR(samples.back(), 1.0, 1e-6);
}