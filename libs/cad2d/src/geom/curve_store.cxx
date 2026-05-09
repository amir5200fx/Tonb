//
// Created by amir on 1/25/26.
//
#include <tonb/cad2d/geom/curve_store.hxx>

namespace tonb::cad2d::geom {
    topo::Id CurveStore::add(const Curve &c) {
        if (!c.is_valid()) {
            throw std::invalid_argument("CurveStore::add: curve is invalid");
        }
        const std::uint64_t id = next_id_++;
        curves_.emplace(id, c);
        return static_cast<topo::Id>(id);
    }

    const Curve & CurveStore::get(const topo::Id id) const {
        validate_id_(id, "CurveStore::get");

        const auto it = curves_.find(static_cast<std::uint64_t>(id));
        if (it == curves_.end()) {
            throw std::out_of_range("CurveStore::get: id not found (id = " + std::to_string(id) + ")");
        }
        return it->second;
    }

    bool CurveStore::contains(const topo::Id id) const {
        validate_id_(id, "CurveStore::contains");
        return curves_.contains(static_cast<std::uint64_t>(id));
    }

    bool CurveStore::remove(const topo::Id id) {
        validate_id_(id, "CurveStore::remove");
        return curves_.erase(static_cast<std::uint64_t>(id)) != 0;
    }

    void CurveStore::clear() noexcept {
        curves_.clear();
        next_id_ = 1;
    }

    void CurveStore::validate_id_(const topo::Id id, const char *where) {
        if (id == 0) {
            throw std::invalid_argument(std::string(where) + ": invalid curve id (0)");
        }
    }


}
