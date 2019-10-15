#ifndef KEMTER_HASH_MAP_H
#define KEMTER_HASH_MAP_H
#include <cstddef>
#include <vector>
#include <memory>
#include <type_traits>
#include <experimental/vector>
#include "kemter_hnode.h"

namespace kemter
{
    template<typename Key, typename Value, typename Hash = std::hash<Key> >
    class kemter_hmap
    {
        using Node = kemter_hnode<Key, Value>;
        using NodePtr = std::shared_ptr<Node>;
        using Nodes = std::vector<NodePtr>;
        
        public:
            kemter_hmap(): m_nodes(64) { }
            std::size_t capacity () const;
            std::size_t size () const;
            void add(const Key& key, const Value& value);
            void remove(const Key& key);
        private:
            Nodes m_nodes;
            std::size_t hash(const Key& key);
    };

    template <typename Key, typename Value, typename Hash>
    void kemter::kemter_hmap<Key, Value, Hash>::add(const Key& key, const Value& value)
    {
        auto index = this->hash(key);
        if( index > (this->capacity() + 1) ) {
            this->m_nodes.resize(this->capacity() * index);
        }
        auto node = std::make_shared<Node>(key, value);
        this->m_nodes[index] = node;
    }

    template <typename Key, typename Value, typename Hash>
    std::size_t kemter::kemter_hmap<Key, Value, Hash>::capacity () const {
        return this->m_nodes.capacity();
    }

    template <typename Key, typename Value, typename Hash>
    std::size_t kemter::kemter_hmap<Key, Value, Hash>::size () const {
        return this->m_nodes.size();
    }

    template <typename Key, typename Value, typename Hash>
    void kemter::kemter_hmap<Key, Value, Hash>::remove(const Key& key)
    {
        std::size_t index = hash(key);
        std::experimental::erase_if(this->m_nodes, [](Node& node) {
        });
    }

    template <typename Key, typename Value, typename Hash>
    std::size_t kemter::kemter_hmap<Key, Value, Hash>::hash(const Key& key)
    {
        auto hash = Hash()(key);
        return hash % this->capacity();
    }
};
#endif