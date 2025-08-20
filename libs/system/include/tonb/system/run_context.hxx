//
// Created by amir on 8/19/25.
//
#pragma once
#ifndef TONB_SYSTEM_RUN_CONTEXT_HXX
#define TONB_SYSTEM_RUN_CONTEXT_HXX

#include <any>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <stdexcept>

namespace tonb::system {

    /**
     * @file run_context.hpp
     * @brief Heterogeneous key–value store for passing arguments into Task::run().
     *
     * @details
     * RunContext is a lightweight container that maps string keys to values of
     * arbitrary types via std::any. It provides typed getters, optional accessors,
     * and convenience helpers for moving values out or chaining inserts.
     *
     * Design notes:
     *  - Lookups are O(1) average via std::unordered_map.
     *  - Type safety is enforced at retrieval time with clear error messages.
     *  - No synchronisation is provided. Treat instances as thread-confined or
     *    publish immutable const references across threads.
     */

    class RunContext {
        /*Private Data*/
        std::unordered_map<std::string, std::any> data_;

    public:
        // default constructor
        RunContext() = default;

        // Public functions and operators

        /**
         * @brief Insert or replace a value for @p key.
         */
        template<class T>
        void set(std::string key, T value) {
            data_[std::move(key)] = std::any(std::move(value));
        }

        /**
         * @brief In-place construct a value for @p key.
         */
        template<class T, class... Args>
        T& emplace(const std::string& key, Args&&... args) {
            auto& slot = data_[key]; // creates or finds
            slot.reset();
            slot.emplace<T>(std::forward<Args>(args)...);
            return *std::any_cast<T>(&slot);
        }

        /**
         * @brief Returns a pointer to T if present and of the right type, else nullptr.
         */
        template<class T>
        T* try_get(const std::string_view key) {
            const auto it = data_.find(std::string(key));
            if (it == data_.end()) return nullptr;
            return std::any_cast<T>(&it->second);
        }
        template<class T>
        const T* try_get(const std::string_view key) const {
            const auto it = data_.find(std::string(key));
            if (it == data_.end()) return nullptr;
            return std::any_cast<const T>(&it->second);
        }

        /**
         * @brief Get a reference to T or throw with a helpful message.
         * @throws std::out_of_range if missing; std::bad_any_cast if wrong type.
         */
        template<class T>
        T& get(const std::string_view key) {
            const auto it = data_.find(std::string(key));
            if (it == data_.end())
                throw std::out_of_range("RunContext: missing key '" + std::string(key) + "'");
            return std::any_cast<T&>(it->second); // may throw bad_any_cast
        }
        template<class T>
        const T& get(const std::string_view key) const {
            const auto it = data_.find(std::string(key));
            if (it == data_.end())
                throw std::out_of_range("RunContext: missing key '" + std::string(key) + "'");
            return std::any_cast<const T&>(it->second);
        }

        /**
         * @brief Return a copy of T if present and type matches, else @p fallback.
         */
        template<class T>
        T get_or(const std::string_view key, T fallback) const {
            if (auto p = try_get<T>(key)) return *p;
            return fallback;
        }

        /**
         * @brief Move a stored value of type T out of the context and erase the key.
         * @throws std::out_of_range or std::bad_any_cast on error.
         */
        template<class T>
        T take(const std::string_view key) {
            const auto it = data_.find(std::string(key));
            if (it == data_.end())
                throw std::out_of_range("RunContext: missing key '" + std::string(key) + "'");
            T out = std::any_cast<T>(std::move(it->second)); // move if possible
            data_.erase(it);
            return out;
        }

        /**
         * @brief Fluent helper for chaining inserts.
         */
        template<class T>
        RunContext& with(std::string key, T value) {
            set(std::move(key), std::move(value));
            return *this;
        }

        /**
         * @brief Merge entries from @p other. Existing keys are kept unless @p overwrite is true.
         */
        void merge(const RunContext& other, const bool overwrite = false) {
            for (const auto& [k, v] : other.data_) {
                if (overwrite || !data_.contains(k)) data_[k] = v;
            }
        }

        /// Book-keeping helpers
        bool contains(const std::string_view key) const { return data_.contains(std::string(key)); }
        bool erase(const std::string_view key) { return data_.erase(std::string(key)) > 0; }
        void clear() { data_.clear(); }
        std::size_t size() const { return data_.size(); }
        bool empty() const { return data_.empty(); }
    };

    /**
     * @brief Optional typed-key helper to avoid stringly-typed mistakes.
     *
     * Usage:
     *   struct Mesh {};
     *   inline constexpr Key<Mesh> kMesh{"mesh"};
     *   ctx.set(kMesh, Mesh{});
     *   auto& m = ctx.get(kMesh);
     */
    template<class T>
    struct Key { std::string_view name; };

    template<class T>
    inline void set(RunContext& ctx, Key<T> key, T value) { ctx.set(std::string(key.name), std::move(value)); }

    template<class T>
    inline T& get(RunContext& ctx, Key<T> key) { return ctx.get<T>(key.name); }

    template<class T>
    inline const T& get(const RunContext& ctx, Key<T> key) { return ctx.get<T>(key.name); }

    template<class T>
    inline T* try_get(RunContext& ctx, Key<T> key) { return ctx.try_get<T>(key.name); }

    template<class T>
    inline const T* try_get(const RunContext& ctx, Key<T> key) { return ctx.try_get<T>(key.name); }
}
#endif //TONB_SYSTEM_RUN_CONTEXT_HXX