#pragma once
#ifndef TONB_CAD2D_SHELL_SHELL_SESSION_HXX
#define TONB_CAD2D_SHELL_SHELL_SESSION_HXX

#include <tonb/cad2d/geom/curve_store.hxx>
#include <tonb/cad2d/topo/shape.hxx>
#include <tonb/cad2d/topo/id.hxx>
#include <tonb/cad2d/shell/module.hxx>

#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace tonb::cad2d::shell {

    namespace session {

        /**
         * @brief Identify a topology entity stored inside a named shell shape.
         *
         * The session uses entity references for shell-facing selection state. The
         * structure is intentionally small and explicit so it can later be extended
         * with symbolic aliases, journaling metadata, or more advanced CAD-style
         * selection workflows without changing the high-level session ownership
         * model introduced in Issue 2.
         */
        struct EntityRef {
            enum class Kind : std::uint8_t {
                vertex,
                edge,
                halfedge,
                wire,
                face
            };

            std::string shape_name;
            Kind kind = Kind::vertex;
            topo::Id id{};
        };

        /**
         * @brief Runtime flags owned by the shell session.
         *
         * These flags intentionally remain lightweight in the initial session
         * milestone. They provide a home for shell process state that should not be
         * mixed into geometry or topology domains, while leaving room for future
         * interactive command state and journaling controls.
         */
        struct RuntimeFlags {
            bool exit_requested = false;
            bool verbose = false;
            bool echo_commands = false;
        };

        /**
         * @brief User-facing named entry for a curve store.
         */
        struct CurveStoreEntry {
            std::string name;
            geom::CurveStore store;
        };

        /**
         * @brief User-facing named entry for a topology shape.
         *
         * The optional bound curve-store name gives the shell a practical active
         * geometry context without changing the clean separation between topology
         * and geometry inside the cad2d library itself.
         */
        struct ShapeEntry {
            std::string name;
            std::shared_ptr<topo::Shape> shape;
            std::optional<std::string> curve_store_name;
        };

        /**
         * @brief Snapshot summary of current shell session state.
         */
        struct SessionStatus {
            std::size_t curve_store_count = 0;
            std::optional<std::string> active_curve_store;

            std::size_t shape_count = 0;
            std::optional<std::string> active_shape;
            std::optional<std::string> active_shape_curve_store;

            std::optional<EntityRef> primary_selection;

            RuntimeFlags runtime{};
        };

        /**
         * @brief Named curve-store domain owned by ShellSession.
         */
        class CurveDomain {
        public:
            CurveDomain() = default;

            TNBCAD2DSHELL_ND_EXPORT bool has(const std::string& name) const noexcept;
            TNBCAD2DSHELL_ND_EXPORT std::size_t size() const noexcept;
            TNBCAD2DSHELL_ND_EXPORT std::vector<std::string> names() const;

            TNBCAD2DSHELL_EXPORT void create(const std::string& name);
            TNBCAD2DSHELL_EXPORT bool erase(const std::string& name);
            TNBCAD2DSHELL_EXPORT void clear() noexcept;

            TNBCAD2DSHELL_EXPORT void set_active(const std::string& name);
            TNBCAD2DSHELL_EXPORT void clear_active() noexcept;
            TNBCAD2DSHELL_ND_EXPORT const std::optional<std::string>& active_name() const noexcept;

            TNBCAD2DSHELL_EXPORT geom::CurveStore& require(const std::string& name);
            TNBCAD2DSHELL_ND_EXPORT const geom::CurveStore& require(const std::string& name) const;

        private:
            std::map<std::string, CurveStoreEntry, std::less<>> stores_;
            std::optional<std::string> active_;
        };

        /**
         * @brief Named topology-root domain owned by ShellSession.
         */
        class ShapeDomain {
        public:
            ShapeDomain() = default;

            TNBCAD2DSHELL_ND_EXPORT bool has(const std::string& name) const noexcept;
            TNBCAD2DSHELL_ND_EXPORT std::size_t size() const noexcept;
            TNBCAD2DSHELL_ND_EXPORT std::vector<std::string> names() const;

            TNBCAD2DSHELL_EXPORT void create(const std::string& name);
            TNBCAD2DSHELL_EXPORT bool erase(const std::string& name);
            TNBCAD2DSHELL_EXPORT void clear() noexcept;

            TNBCAD2DSHELL_EXPORT void set_active(const std::string& name);
            TNBCAD2DSHELL_EXPORT void clear_active() noexcept;
            TNBCAD2DSHELL_ND_EXPORT const std::optional<std::string>& active_name() const noexcept;

            TNBCAD2DSHELL_EXPORT ShapeEntry& require_entry(const std::string& name);
            TNBCAD2DSHELL_ND_EXPORT const ShapeEntry& require_entry(const std::string& name) const;

            TNBCAD2DSHELL_ND_EXPORT std::shared_ptr<topo::Shape> require(const std::string& name) const;

            TNBCAD2DSHELL_EXPORT void bind_curve_store(
                    const std::string& shape_name,
                    const std::string& curve_store_name);

        private:
            std::map<std::string, ShapeEntry, std::less<>> shapes_;
            std::optional<std::string> active_;
        };

        /**
         * @brief Primary selection state owned by ShellSession.
         */
        class SelectionDomain {
        public:
            SelectionDomain() = default;

            TNBCAD2DSHELL_EXPORT void clear() noexcept;
            TNBCAD2DSHELL_EXPORT void set_primary(EntityRef ref);
            TNBCAD2DSHELL_ND_EXPORT const std::optional<EntityRef>& primary() const noexcept;

        private:
            std::optional<EntityRef> primary_;
        };

    } // namespace session

    /**
     * @brief Central state container for the cad2d shell.
     *
     * ShellSession is the orchestration root for user-facing shell state. It owns
     * named curve stores, named topology roots, active-context tracking, primary
     * selection state, and lightweight runtime flags. The class intentionally does
     * not implement CAD algorithms; it provides the persistent state on top of
     * which later command, help, journaling, and AutoCAD-like workflows will be
     * built.
     */
    class ShellSession {
    public:
        ShellSession() = default;

        TNBCAD2DSHELL_EXPORT session::CurveDomain& curves() noexcept;
        TNBCAD2DSHELL_ND_EXPORT const session::CurveDomain& curves() const noexcept;

        TNBCAD2DSHELL_EXPORT session::ShapeDomain& shapes() noexcept;
        TNBCAD2DSHELL_ND_EXPORT const session::ShapeDomain& shapes() const noexcept;

        TNBCAD2DSHELL_EXPORT session::SelectionDomain& selection() noexcept;
        TNBCAD2DSHELL_ND_EXPORT const session::SelectionDomain& selection() const noexcept;

        TNBCAD2DSHELL_EXPORT session::RuntimeFlags& runtime() noexcept;
        TNBCAD2DSHELL_ND_EXPORT const session::RuntimeFlags& runtime() const noexcept;

        /**
         * @brief Reset the session to its default empty state.
         */
        TNBCAD2DSHELL_EXPORT void reset() noexcept;

        /**
         * @brief Return a deterministic snapshot summary of current session state.
         */
        TNBCAD2DSHELL_ND_EXPORT session::SessionStatus status() const;

    private:
        session::CurveDomain curves_;
        session::ShapeDomain shapes_;
        session::SelectionDomain selection_;
        session::RuntimeFlags runtime_{};
    };

} // namespace tonb::cad2d::shell

#endif // TONB_CAD2D_SHELL_SHELL_SESSION_HXX
