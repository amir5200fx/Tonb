//
// Created by amir on 02/09/2025.
//
#pragma once
#ifndef TONB_GEOMETRY_SPATIAL_AD_TREE_HXX
#define TONB_GEOMETRY_SPATIAL_AD_TREE_HXX

#include <tonb/geometry/meta/box.hxx>
#include <tonb/geometry/tools.hxx>
#include <tonb/base/precision.hxx>
#include <tonb/base/range.hxx>

#include <functional>

namespace tonb::geometry::spatial {
    template<class T, class Point>
    class AdTreeNode {
    public:
        using node_type = AdTreeNode;
    private:
        /*Private Data*/

        T data_;
        meta::Box<Point> region_;

        int level_ = 0;

        node_type* left_ = nullptr;
        node_type* right_ = nullptr;
    public:

        AdTreeNode() : left_(nullptr), right_(nullptr) {}
        AdTreeNode(T item, meta::Box<Point> region, const int level)
            : data_(std::move(item)), region_(std::move(region)), level_(level) {}

        // Public functions and operators

        TNB_NODISCARD const auto& data() const { return data_; }
        TNB_NODISCARD const auto& region() const { return region_; }

        TNB_NODISCARD int level() const { return level_; }
        int& level() { return level_; }

        TNB_NODISCARD auto left() const { return left_; }
        TNB_NODISCARD auto right() const { return right_; }
        node_type*& left() {return left_;}
        node_type*& right() {return right_;}

    };

    template<class T>
    class AdTree {
    public:
        using point_type = std::remove_pointer_t<T>::ptType;
        using node_type = AdTreeNode<T, point_type>;

        using box_type = meta::Box<point_type>;

    private:
        /*Private Data*/

        node_type* root_ = nullptr;
        int item_count_ = 0;
        box_type world_;

        std::function<const point_type& (const T&)> coordinate_of;

        // Private functions and operators

        TNB_NODISCARD int dim_level(const int level) const noexcept {return level % point_type::nb_cmpts;}

        void find_leaf(node_type* t, node_type*& leaf) {
            if (!t) leaf = nullptr;
            else if (t->left() == nullptr && t->right() == nullptr)  leaf = t;
            else if (t->left()) find_leaf(t->left(), leaf);
            else find_leaf(t->right(), leaf);
        }

        void retrieve_to(node_type* t, std::vector<T>& items) {
            if (t) {
                retrieve_to(t->left(), items); items.emplace_back(t->data()); retrieve_to(t->right(), items);
            }
        }

        void insert(T item, box_type region, const int level, node_type*& t) {
            if (!t) {
                t = new node_type{std::move(item), std::move(region), level};
                ++item_count_;
                return;
            }
            auto dim = dim_level(level);
            const real x = coordinate_of(item)[dim];
            const typename box_type::Range r = region.range(static_cast<Direction>(dim));

            const bool left = (x >= r.lower() && x <= r.mid());
            insert(std::move(item), region.half(static_cast<Direction>(dim), left ? 0 : 1), t->level() + 1,
                   left ? t->left() : t->right());
        }

        void remove(const T& item, node_type*& t) {
            if (!t) {
                throw std::invalid_argument("tree is empty");
            }
            if (item == t->data()) {
                if (t->right()) {
                    node_type* leaf = nullptr;
                    find_leaf(t->right(), leaf);

                    t->data() = leaf->data();
                    remove(t->data(), t->right());
                } else if (t->left()) {
                    node_type* leaf = nullptr;
                    find_leaf(t->left(), leaf);

                    t->data() = leaf->data();
                    remove(t->data(), t->left());
                } else {
                    node_type* old = t;
                    t = t->left() ? t->left() : t->right();
                    delete old;
                    --item_count_;
                }
            } else {
                const auto& coord = coordinate_of(item);
                const auto dim = dim_level(t->level());
                const real x = coord[dim];
                if (const typename box_type::Range r = t->region().range(static_cast<Direction>(dim)); x >= r.lower() && x < r.mid()) remove(
                    item, t->left());
                else remove(item, t->right());
            }
        }

        void search(const box_type& region, node_type* t, std::vector<T>& items) const {
            if (!t) return;
            const int dim = dim_level(t->level());
            if (region.contains(coordinate_of(t->data()))) {
                items.emplace_back(t->data());
            }
            const typename box_type::Range r0 = t->region().range(static_cast<Direction>(dim));
            const auto xm = r0.mid();

            const typename box_type::Range r1 = region.range(static_cast<Direction>(dim));

            if (Tools::have_intersection(r1.lower(), r1.upper(), r0.lower(), xm))
                search(region, t->left(), items);
            if (Tools::have_intersection(r1.lower(), r1.upper(), xm, r0.upper()))
                search(region, t->right(), items);
        }

        void clear(node_type*& t) {
            if (t) {
                clear(t->left());
                clear(t->right());
                --item_count_;
                delete t;
                t = nullptr;
            }
        }

    public:

        // default constructor
        AdTree() : root_(nullptr) {}

        ~AdTree() {
            if (root_) clear(root_);
        }

        // Public functions and operators

        TNB_NODISCARD int size() const { return item_count_; }
        TNB_NODISCARD bool empty() const { return item_count_ == 0; }
        TNB_NODISCARD std::vector<T> retrieve() const {
            std::vector<T> items; items.reserve(item_count_);
            retrieve_to(items);
            return items;
        }
        void set_world(box_type region) {world_ = std::move(region);}
        void set_function(std::function<const point_type& (const T&)> f) {coordinate_of = std::move(f);}
        void insert(T item) { insert(std::move(item), world_, 0, root_); }
        void insert(const std::vector<T>& items) { for (const T& item : items) insert(item); }
        void remove(const T& item) { remove(item, root_); }
        void search(const box_type& region, std::vector<T>& items) const { search(region, root_, items); }
        void search_in_radius(const real radius, const point_type &center, std::vector<T> &items) const {
            search(box_type::from_radius_and_center(radius, center), root_, items);
        }
        void retrieve_to(std::vector<T>& items) { retrieve_to(root_, items); }
        void clear() { clear(root_); }
    };
}
#endif //TONB_GEOMETRY_SPATIAL_AD_TREE_HXX