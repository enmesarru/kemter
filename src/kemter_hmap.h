#ifndef KEMTER_HASH_MAP_H
#define KEMTER_HASH_MAP_H
#include <cstddef>
#include <vector>
#include <memory>
#include <type_traits>
#include <variant>
#include <iostream>
#include <experimental/vector>
#include "kemter_hnode.h"
#include "kemter_types.h"

namespace kemter
{
    template<typename Key, typename Value, typename Hash = std::hash<Key> >
    class kemter_hmap
    {
        using Node = kemter_hnode<Key, Value>;
        using NodePtr = std::shared_ptr<Node>;
        using Nodes = std::vector<NodePtr>;

        public:
            kemter_hmap(): m_nodes(64, nullptr), m_node_count(0) { }
            std::size_t capacity () const;
            std::size_t size () const;
            Value get(const Key& key);
            void add(const Key& key, const Value& value);
            void remove(const Key& key);
            void put(const Key& key, const Value& value);
        private:
            std::size_t m_node_count;
            Nodes m_nodes;
            std::size_t hash(const Key& key);
    };

    template <typename Key, typename Value, typename Hash>
    Value kemter_hmap<Key, Value, Hash>::get(const Key& key) {

        auto index = this->hash(key);
        auto item = this->m_nodes.at(index);
        if(!item) {
            return kemter::type::Status::NodeNotExist;
        }
        auto value = item.get()->getValue();
        return value;
    };

    template <typename Key, typename Value, typename Hash>
    void kemter_hmap<Key, Value, Hash>::add(const Key& key, const Value& value)
    {
        auto index = this->hash(key);
        if(this->m_nodes.at(index) != nullptr) {
            /* ToDo: if the node exists, 
            add the new node into the child node */
        }

        if( index > (this->capacity() + 1) ) {
            this->m_nodes.resize(this->capacity() * index);
        }

        auto node = std::make_shared<Node>(key, value);
        this->m_nodes.at(index) = node;
        this->m_node_count++;
    }

    template <typename Key, typename Value, typename Hash>
    void kemter_hmap<Key, Value, Hash>::put(const Key& key, const Value& value)
    {
        auto index = this->hash(key);
        if(this->m_nodes.at(index) == nullptr) {
            return;
        }
        this->m_nodes.at(index) = std::make_shared<Node>(key, value);
    }

    template <typename Key, typename Value, typename Hash>
    std::size_t kemter_hmap<Key, Value, Hash>::capacity () const {
        return this->m_nodes.capacity();
    }

    template <typename Key, typename Value, typename Hash>
    std::size_t kemter_hmap<Key, Value, Hash>::size () const {
        return this->m_node_count;
    }

    template <typename Key, typename Value, typename Hash>
    void kemter_hmap<Key, Value, Hash>::remove(const Key& key)
    {
        std::size_t index = this->hash(key);
        if(this->m_nodes.at(index) == nullptr) {
            return;
        }
        this->m_nodes.at(index) = nullptr;
        this->m_node_count--;
    }

    template <typename Key, typename Value, typename Hash>
    std::size_t kemter_hmap<Key, Value, Hash>::hash(const Key& key)
    {
        auto hash = Hash()(key);
        return hash % this->capacity();
    }
};
#endif