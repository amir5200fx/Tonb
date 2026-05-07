//
// Created by amir on 8/30/25.
//
#pragma once
#ifndef TONB_GEOMETRY_SPATIAL_ADAPTIVE_TREE_HXX
#define TONB_GEOMETRY_SPATIAL_ADAPTIVE_TREE_HXX
#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>
#include <tonb/base/index_types.hxx>
#include <memory>
#include <vector>
#include <tonb/geometry/meta/box.hxx>

namespace tonb::geometry::spatial {


    template<class T>
    struct traits; // Provide a specialisation for your T.

    template<class T>
    class AdaptiveTree {
    public:

        // ----------------- Recommended defaults / knobs --------------------
        struct default_build_params {
            // Maximum items stored in a leaf before splitting
            std::size_t leaf_capacity = 8;

            // Force a maximum depth to prevent pathological cases
            index_t max_depth = 64;

            // Choose axis by largest extend; set true to cycle axes instead
            bool cycle_axes = false;
        };

        // Forward Declarations
        template<class Box>
        class Node;

        using value_type = T;

        // Deduce Box type from traits<T>::aabb(T)
        using box_type = std::decay_t<decltype(traits<value_type>::aabb(std::declval<const value_type&>()))>;

        using node_type = Node<box_type>;
        using node_ptr = std::unique_ptr<node_type>;
        using bucket_type = std::vector<node_ptr>;

        template<class Box>
        class Node {
        public:
            // Types

            using box_type = Box;


        private:

            // Topology
            node_ptr left_{};
            node_ptr right_{};

            // Geometry
            box_type region_{};
            std::array<box_type, 2> child_boxes_{};  // cached AABBs for children

            // Metadata
            index_t level_ = 0;
            index_t split_axis_ = 0;
            real split_value_ = 0.0;
            std::size_t size_ = 0;
            bool is_leaf_ = true;

            // Payload (leaf only)
            bucket_type bucket_{};

        public:

            // Construction (leaf by default)
            explicit Node(const box_type& box, const index_t level = 0, const index_t split_axis = 0) noexcept
            : region_(box), level_(level), split_axis_(split_axis), size_(0), is_leaf_(true)
            {}

            Node(const Node&) = delete;
            Node& operator=(const Node&) = delete;
            Node(Node&&) noexcept = delete;
            Node& operator=(Node&&) = delete;
            ~Node() noexcept = default;

            // --------------------------- Observers ----------------------------------

            TNB_NODISCARD const box_type& region() const noexcept { return region_; }
            TNB_NODISCARD const node_type& left() const noexcept { return left_; }
            TNB_NODISCARD const node_type& right() const noexcept { return right_; }
            TNB_NODISCARD const box_type& left_box() const noexcept { return child_boxes_[0]; }
            TNB_NODISCARD const box_type& right_box() const noexcept { return child_boxes_[1]; }
            TNB_NODISCARD const auto& bucket() const noexcept { return bucket_; }
            TNB_NODISCARD index_t level() const noexcept { return level_; }
            TNB_NODISCARD index_t split_axis() const noexcept { return split_axis_; }
            TNB_NODISCARD index_t size() const noexcept { return size_; }
            TNB_NODISCARD bool is_leaf() const noexcept { return is_leaf_; }

            // The split coordinate used to partition this node (valid when !is_leaf())
            TNB_NODISCARD real split_value() const noexcept { return split_value_; }

            // -------------------------- Mutators ---------------------------------------

            // Append an item to the leaf bucket; caller updates size() via bump_size().
            // Precondition: is_leaf() = true.
            void push_into_bucket(const value_type& v) {
                bucket_.push_back(v);
                ++size_;
            }

            // Reserve bucket capacity (helps during build builds).
            void reserve_bucket(std::size_t n) {bucket_.reserve(n);}

            // Make this not an internal node by setting its split and attaching children.
            // This clears the bucket and flips is_leaf_ to false.
            // The child boxes are cached to avoid recomputation during traversal.
            void make_internal(index_t axis, real split_val, node_ptr left_child, node_ptr right_child,
                               const box_type &left_box, const box_type &right_box) noexcept {
                split_axis_ = axis;
                split_value_ = split_val;
                is_leaf_ = false;
                bucket_.clear();
                left_ = std::move(left_child);
                right_ = std::move(right_child);
                child_boxes_[0] = left_box;
                child_boxes_[1] = right_box;

                // Recompute size as sum of children (defensive if caller forgot)
                size_ (left_ ? left_->size_ : 0) + (right_ ? right_->size_ : 0);
            }

            // Update cached size after mutation below this node.
            void recompute_size_from_children() noexcept {
                size_ = (left_ ? left_->size_ : 0) + (right_ ? right_->size_ : 0);
            }

            // Bump size when caller inserts beneath this node (fast path).
            void bump_size(std::size_t delta = 1) noexcept {size_ += delta;}

            // Helper: returns the child index (0=left, 1=right) for a point coordiante.
            template<class PointLike>
            TNB_NODISCARD index_t child_index_for_point(const PointLike& p) const noexcept {
                const real c = coord_of(p, split_axis_);
                return (c < split_axis_) ? 0 : 1;
            }

            // ------------------- Utilities --------------------------------------

            // Decide next split axis: by largest extent (recommended) or just cycle.
            // Pss cycle=true to use simple round-robin axis selection
            static int next_axis(const box_type& b, index_t current_axis, bool cycle = false) noexcept {
                constexpr index_t D = traits<value_type>::dimensions;
                if (cycle) return (current_axis + 1)%D;

                // Largets-extent heuristic
                index_t best = 0;
                real best_extent = b.extent(0);
                for (index_t i = 1; i < D; ++i) {
                    const real e = b.extent(i);
                    if (e > best_extent) {
                        best_extent = e; best = i;
                    }
                }
                // Fallback if all zero extents (degenerate box)
                return best_extent > 0 ? best : (current_axis + 1) % D;
            }

            // Compute median split value from a small leaf bucket on the chosen axis.
            // For small buckets this simple nth_element-free approach is fine; replace
            // with nth_element if you expect large buckets.
            TNB_NODISCARD real median_from_bucket(index_t axis) const {
                std::vector<real> coords;
                coords.reserve(bucket_.size());
                for (const auto& v: bucket_) {
                    coords.push_back(coord_of(traits<value_type>::point(v), axis));
                }
                if (coords.empty()) return 0.5*(region_.min(axis) + region_.max(axis));
                std::sort(coords.begin(), coords.end());
                const auto mid = coords.size() / 2;
                if (coords.size() % 2 == 1) return coords[mid];
                return 0.5*(coords[mid -1] + coords[mid]);
            }

        private:

            // Minimal point coordinate accessor to decouple from concrete pont type
            template<class PointLike>
            static real coord_of(const PointLike& p, index_t axis) noexcept {
                // Expect a method coord(int) or Coord(int); try both at compile-time.
                if constexpr (requires{p.coord(axis);}) {
                    return p.coord(axis);
                } else if constexpr (requires{p.Coord(axis + 1);}) {
                    return p.Coord(axis + 1);
                } else if constexpr (requires{p[static_cast<std::size_t>(axis)];}) {
                    return static_cast<real>(p[static_cast<std::size_t>(axis)]);
                } else {
                    static_assert(sizeof(PointLike) == 0, "PointLike must provide coord(i), Coord(i+1), or operator[]");
                    return 0.0;
                }
            }
        };

    private:

        /*Private Data*/

        node_ptr root_{};
        box_type world_{};
        default_build_params params_{};

        void insert_impl(node_ptr* node, const value_type& v, index_t depth) {
            // Safety: cap depth to avoid pathological cases
            if (depth >= params_.max_depth) {
                // Forced leaf: just store in this bucket
                node->push_into_bucket(v);
                return;
            }

            if (node->is_leaf()) {
                // Place in bucket
                node->push_into_bucket(v);

                // Split if over capacity
                if (node->bucket().size() > params_.leaf_capacity) {
                    // Choose axis: by largets extent (default) or cycle
                    const index_t axis = node_type::next_axis(node->region(), node->split_axis(), params_.cycle_axes);

                    // Choose split position : median of bucket along axis (fall back to mid of region)
                    real split_val = node->median_from_bucket(axis);
                    const real lo = node->region().min(axis);
                    const real hi = node->region().max(axis);
                    if (!(split_val > lo && split_val < hi)) {
                        // Fallback to mid if median collapses (degenerate region)
                        split_val = static_cast<real>(0.5)* (lo + hi);
                        // If still degenerate, give up splitting
                        if (!(split_val > lo && split_val < hi)) return;
                    }

                    // Split region and allocate children
                    auto [left_box , right_box] = node->region().split(axis, split_val);
                    auto left_child = std::make_unique<node_ptr>(left_box, node->level() + 1, axis);
                    auto right_child = std::make_unique<node_ptr>(right_box, node->level() + 1, axis);

                    // Re-distribute existing bucket items into children
                    for (const auto& item: node->bucket()) {
                        const auto& p = traits<value_type>::point(item);
                        const real c = [&] {
                            if constexpr (requires{p.coord(axis);}) return static_cast<real>(p.coord(axis));
                            else if constexpr (requires{p.Coord(axis + 1);}) return static_cast<real>(p.Coord(axis+1));
                            else return static_cast<real>(p[static_cast<std::size_t>(axis)]);
                        }();
                        ((c < split_val) ? left_child : right_child)->push_into_bucke(item);
                    }

                    // Promote to internal node (clears bucket inside)
                    node->make_internal(axis, split_val, std::move(left_child), std::move(right_child), left_box, right_box);
                }
                return;
            }

            // Internal node: descend
            const index_t axis = node->split_axis();
            const real split_val = node->split_value();

            const auto& p = traits<value_type>::point(v);
            const real c = [&] {
                if constexpr (requires{p.coord(axis);}) return static_cast<real>(p.coord(axis));
                else if constexpr (requires{p.Coord(axis + 1);}) return static_cast<real>(p.Coord(axis+1));
                else return static_cast<real>(p[static_cast<std::size_t>(axis)]);
            }();

            node_type* child = nullptr;
            if (c < split_val) {
                if (!node->left()) {
                    auto [lb, rb] = node->region().split(axis, split_val);

                }
            }
        }

    };
}
#endif