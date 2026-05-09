#include <tonb/cad2d/shell/shell_session.hxx>

#include <stdexcept>
#include <tuple>
#include <utility>

namespace tonb::cad2d::shell {

    namespace {

        auto require_non_empty_name(const std::string& name, const char* where) -> const std::string& {
            if (name.empty()) {
                throw std::invalid_argument(std::string(where) + ": name must not be empty");
            }
            return name;
        }

    } // namespace

    namespace session {

        bool CurveDomain::has(const std::string& name) const noexcept {
            return stores_.find(name) != stores_.end();
        }

        std::size_t CurveDomain::size() const noexcept {
            return stores_.size();
        }

        std::vector<std::string> CurveDomain::names() const {
            std::vector<std::string> out;
            out.reserve(stores_.size());
            for (const auto& [name, _] : stores_) {
                out.push_back(name);
            }
            return out;
        }

        void CurveDomain::create(const std::string& name) {
            require_non_empty_name(name, "CurveDomain::create");
            if (has(name)) {
                throw std::invalid_argument("CurveDomain::create: curve store '" + name + "' already exists");
            }

            auto [it, inserted] = stores_.emplace(
                    std::piecewise_construct,
                    std::forward_as_tuple(name),
                    std::forward_as_tuple(CurveStoreEntry{name, geom::CurveStore{}}));
            (void)it;
            if (!inserted) {
                throw std::runtime_error("CurveDomain::create: failed to insert curve store '" + name + "'");
            }
        }

        bool CurveDomain::erase(const std::string& name) {
            require_non_empty_name(name, "CurveDomain::erase");
            const auto erased = stores_.erase(name);
            if (active_ && *active_ == name) {
                active_.reset();
            }
            return erased > 0;
        }

        void CurveDomain::clear() noexcept {
            stores_.clear();
            active_.reset();
        }

        void CurveDomain::set_active(const std::string& name) {
            require(name);
            active_ = name;
        }

        void CurveDomain::clear_active() noexcept {
            active_.reset();
        }

        const std::optional<std::string>& CurveDomain::active_name() const noexcept {
            return active_;
        }

        geom::CurveStore& CurveDomain::require(const std::string& name) {
            require_non_empty_name(name, "CurveDomain::require");
            const auto it = stores_.find(name);
            if (it == stores_.end()) {
                throw std::out_of_range("CurveDomain::require: unknown curve store '" + name + "'");
            }
            return it->second.store;
        }

        const geom::CurveStore& CurveDomain::require(const std::string& name) const {
            require_non_empty_name(name, "CurveDomain::require");
            const auto it = stores_.find(name);
            if (it == stores_.end()) {
                throw std::out_of_range("CurveDomain::require: unknown curve store '" + name + "'");
            }
            return it->second.store;
        }

        bool ShapeDomain::has(const std::string& name) const noexcept {
            return shapes_.find(name) != shapes_.end();
        }

        std::size_t ShapeDomain::size() const noexcept {
            return shapes_.size();
        }

        std::vector<std::string> ShapeDomain::names() const {
            std::vector<std::string> out;
            out.reserve(shapes_.size());
            for (const auto& [name, _] : shapes_) {
                out.push_back(name);
            }
            return out;
        }

        void ShapeDomain::create(const std::string& name) {
            require_non_empty_name(name, "ShapeDomain::create");
            if (has(name)) {
                throw std::invalid_argument("ShapeDomain::create: shape '" + name + "' already exists");
            }

            auto [it, inserted] = shapes_.emplace(
                    std::piecewise_construct,
                    std::forward_as_tuple(name),
                    std::forward_as_tuple(ShapeEntry{name, std::make_shared<topo::Shape>(), std::nullopt}));
            (void)it;
            if (!inserted) {
                throw std::runtime_error("ShapeDomain::create: failed to insert shape '" + name + "'");
            }
        }

        bool ShapeDomain::erase(const std::string& name) {
            require_non_empty_name(name, "ShapeDomain::erase");
            const auto erased = shapes_.erase(name);
            if (active_ && *active_ == name) {
                active_.reset();
            }
            return erased > 0;
        }

        void ShapeDomain::clear() noexcept {
            shapes_.clear();
            active_.reset();
        }

        void ShapeDomain::set_active(const std::string& name) {
            (void)require(name);
            active_ = name;
        }

        void ShapeDomain::clear_active() noexcept {
            active_.reset();
        }

        const std::optional<std::string>& ShapeDomain::active_name() const noexcept {
            return active_;
        }

        ShapeEntry& ShapeDomain::require_entry(const std::string& name) {
            require_non_empty_name(name, "ShapeDomain::require_entry");
            const auto it = shapes_.find(name);
            if (it == shapes_.end()) {
                throw std::out_of_range("ShapeDomain::require_entry: unknown shape '" + name + "'");
            }
            return it->second;
        }

        const ShapeEntry& ShapeDomain::require_entry(const std::string& name) const {
            require_non_empty_name(name, "ShapeDomain::require_entry");
            const auto it = shapes_.find(name);
            if (it == shapes_.end()) {
                throw std::out_of_range("ShapeDomain::require_entry: unknown shape '" + name + "'");
            }
            return it->second;
        }

        std::shared_ptr<topo::Shape> ShapeDomain::require(const std::string& name) const {
            const auto& entry = require_entry(name);
            return entry.shape;
        }

        void ShapeDomain::bind_curve_store(const std::string& shape_name, const std::string& curve_store_name) {
            auto& entry = require_entry(shape_name);
            require_non_empty_name(curve_store_name, "ShapeDomain::bind_curve_store");
            entry.curve_store_name = curve_store_name;
        }

        void SelectionDomain::clear() noexcept {
            primary_.reset();
        }

        void SelectionDomain::set_primary(EntityRef ref) {
            if (ref.shape_name.empty()) {
                throw std::invalid_argument("SelectionDomain::set_primary: shape_name must not be empty");
            }
            if (ref.id == 0) {
                throw std::invalid_argument("SelectionDomain::set_primary: entity id must be non-zero");
            }
            primary_ = std::move(ref);
        }

        const std::optional<EntityRef>& SelectionDomain::primary() const noexcept {
            return primary_;
        }

    } // namespace session

    session::CurveDomain& ShellSession::curves() noexcept {
        return curves_;
    }

    const session::CurveDomain& ShellSession::curves() const noexcept {
        return curves_;
    }

    session::ShapeDomain& ShellSession::shapes() noexcept {
        return shapes_;
    }

    const session::ShapeDomain& ShellSession::shapes() const noexcept {
        return shapes_;
    }

    session::SelectionDomain& ShellSession::selection() noexcept {
        return selection_;
    }

    const session::SelectionDomain& ShellSession::selection() const noexcept {
        return selection_;
    }

    session::RuntimeFlags& ShellSession::runtime() noexcept {
        return runtime_;
    }

    const session::RuntimeFlags& ShellSession::runtime() const noexcept {
        return runtime_;
    }

    void ShellSession::reset() noexcept {
        curves_.clear();
        shapes_.clear();
        selection_.clear();
        runtime_ = session::RuntimeFlags{};
    }

    session::SessionStatus ShellSession::status() const {
        session::SessionStatus out{};
        out.curve_store_count = curves_.size();
        out.active_curve_store = curves_.active_name();

        out.shape_count = shapes_.size();
        out.active_shape = shapes_.active_name();
        if (out.active_shape) {
            const auto& active_entry = shapes_.require_entry(*out.active_shape);
            out.active_shape_curve_store = active_entry.curve_store_name;
        }

        out.primary_selection = selection_.primary();
        out.runtime = runtime_;
        return out;
    }

} // namespace tonb::cad2d::shell
