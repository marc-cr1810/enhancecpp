#pragma once

#include <cmath>
#include <cstdint>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>

#define INDEX_FROM_BIT(bit)     floor((float)((bit) / UINT8_WIDTH))

namespace enhance
{
    template<typename Block = uint8_t>
    class bitset
    {
    public:
        bitset()
            : m_block_size(sizeof(Block) * UINT8_WIDTH), m_size(0)
        {}

        bitset(Block value)
            : bitset()
        {
            char data[sizeof(Block)];
            std::memcpy(data, &value, sizeof(Block));
            m_size = sizeof(Block) * UINT8_WIDTH;
            for (int i = 0; i < sizeof(Block); i++)
            {
                m_bytes.push_back(data[i]);
            }
        }

        bitset(const std::string& binary_string)
        {
            auto length = binary_string.size();
            int bit = 0;
            for (int i = 0; i < length; i++)
            {
                char c = binary_string[(length - 1) - i];
                if (c == '_')
                    continue;

                if (c == '1')
                    set(bit, 1);
                else if (c == '0')
                    set(bit, 0);
                else
                    throw std::runtime_error("Invalid char value, bit strings can only have '0' or '1' char values");
                bit++;
            }
        }

        auto set() -> void
        {
            for (int i = 0; i < m_size; i++)
                set(i, 1);
        }

        auto set(size_t bit, uint8_t value = 0b1) -> void
        {
            size_t idx = INDEX_FROM_BIT(bit);
            if (idx >= m_bytes.size())
                resize(bit + 1);
            if (bit >= m_size)
                m_size = bit + 1;
            uint8_t byte_bit = bit - (idx * UINT8_WIDTH);
            m_bytes[idx] = (m_bytes[idx] & ~(0b1 << byte_bit) | ((value & 0b1) << byte_bit));
        }

        auto get(size_t bit) -> uint8_t
        {
            if (bit >= m_size)
                throw std::runtime_error("Index out of bounds");
            
            size_t idx = INDEX_FROM_BIT(bit);
            uint8_t byte_bit = bit - (idx * UINT8_WIDTH);
            return (m_bytes[idx] >> byte_bit) & 0b1;
        }

        auto flip() -> void
        {
            for (size_t i = 0; i < m_size; i++)
                flip(i);
        }

        auto flip(size_t bit) -> void
        {
            set(bit, !get(bit));
        }

        auto resize(size_t num_bits, uint8_t value = 0b0)
        {
            if (num_bits == 0)
            {
                m_bytes.clear();
                m_size = 0;
                return;
            }

            int64_t alloc = (INDEX_FROM_BIT(num_bits - 1) + 1) - m_bytes.size();
            uint8_t byte_value = value == 0b0 ? 0x0 : 0xFF;
            
            for (size_t i = 0; i < abs(alloc); i++)
            {
                if (alloc > 0)
                    m_bytes.push_back(byte_value);
                else
                    m_bytes.pop_back();
            }

            m_size = num_bits;
        }

        auto reset() -> void
        {
            for (int i = 0; i < m_size; i++)
                set(i, 0);
        }

        auto reset(size_t bit)
        {
            if (bit < m_size)
                set(bit, 0);
        }

        auto test(size_t bit) -> bool
        {
            return get(bit);
        }

        auto all() -> bool
        {
            for (int i = 0; i < m_size; i++)
            {
                if (!get(i))
                    return false;
            }
            return true;
        }

        auto none() -> bool
        {
            return !all();
        }

        auto to_string() -> std::string
        {
            std::string out;
            out.resize(m_size);
            for (int i = 0; i < m_size; i++)
                out[(m_size - 1) - i] = get(i) ? '1' : '0';
            return out;
        }

        auto operator[](size_t bit) -> uint8_t
        {
            return get(bit);
        }
    private:
        std::vector<uint8_t> m_bytes;
        size_t m_block_size;
        size_t m_size;
    };
}

#undef INDEX_FROM_BIT