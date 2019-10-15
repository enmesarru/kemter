#ifndef KEMTER_HASH_NODE_H
#define KEMTER_HASH_NODE_H

namespace kemter
{
    template <typename Key, typename Value>
    class kemter_hnode
    {
        private:
            Key m_key;
            Value m_value;
            kemter_hnode* m_next;
        public:
            kemter_hnode();
            kemter_hnode(const Key& key, const Value& value);
            Key getKey() const;
            Value getValue() const;
            void setValue(const Value& value);
    };

    template <typename Key, typename Value>
    kemter::kemter_hnode<Key, Value>::kemter_hnode()
    {

    }
    
    template<typename Key, typename Value>
    kemter_hnode<Key, Value>::kemter_hnode(const Key& key, const Value& value)
        : m_key(key), m_value(value), m_next(nullptr) { }

    template<typename Key, typename Value>
    Key kemter_hnode<Key, Value>::getKey() const {
        return m_key;
    }

    template<typename Key, typename Value>
    void kemter_hnode<Key, Value>::setValue(const Value& value) {
        m_value = value;
    }

    template<typename Key, typename Value>
    Value kemter_hnode<Key, Value>::getValue() const {
        return m_value;
    }
}

#endif