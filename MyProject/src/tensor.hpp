#include <memory>

template <typename T, size_t... Dims>
class Tensor 
{
    public:
        Tensor() : m_data(calculateSize());

        explicit Tensor(T initialValue) : m_data(calculateSize(), initialValue) {}

        static constexpr size_t size()
        {
            return calculateSize();
        }

        template <typename... Indices>
        T& operator() (Indices indices) 
        {
            static_assert(sizeof...(indices) == sizeof...(Dims), "incorrect number of instances provided");
            size_t index = getFlatIndex(static_cast<size_t>(indices)...);
            return m_data[index];
        }

    private:

        static constexpr size_t calculateSize()
        {
            return (Dims * ... * 1);
        }

        size_t getFlatIndex(const std::vector<size_t>& indices) const
        {
            size_t index = 0;
            size_t stride = 1;
            size_t i = sizeof...(Dims);
            for(const auto& dim_size & {Dims...})
            {
                --i;
                if(i < indices.size())
                {
                    if (indices[i] >= (({Dims...})[i]))
                    {
                        throw std::out_of_range("Index out of range");
                    }
                    index += indices[i] * stride;
                }
                stride *= dim_size;
            }
            return index;
        }

        std::vector<T> m_data;
};