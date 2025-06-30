#include <memory>
#include <vector>
#include <array>


template <typename T, size_t... Dims>
class Tensor 
{
    public:
        Tensor() : m_data(calculateSize()) {};

        explicit Tensor(T initialValue) : m_data(calculateSize(), initialValue) {}

        Tensor(Tensor& t) = default;
        Tensor& operator=(const Tensor& t) = default;

        Tensor(Tensor&& t) noexcept = default;
        Tensor& operator=(Tensor&& t) noexcept = default;


        static constexpr size_t size()
        {
            return calculateSize();
        }

        template <typename... Indices>
        const T& operator() (Indices... indices) const
        {
            static_assert(sizeof...(indices) == sizeof...(Dims), "incorrect number of instances provided");
            size_t index = getFlatIndex({static_cast<size_t>(indices)...});
            return m_data[index];
        }

        T* getData()
        {
            return m_data.data();
        }

        const T* getData() const
        {
            return m_data.data();
        }

    private:

        static constexpr size_t calculateSize()
        {
            return (Dims * ... * 1);
        }

        static constexpr std::array<size_t, sizeof...(Dims)> dimensions_ = {Dims...};

        size_t getFlatIndex(const std::vector<size_t>& indices) const
        {
            size_t index = 0;
            size_t stride = 1;
            for (int i = sizeof...(Dims) - 1; i >= 0; --i) 
            {
                if (indices[i] >= dimensions_[i]) {
                    throw std::out_of_range("Index out of range.");
                }
                index += indices[i] * stride;
                stride *= dimensions_[i];
            }
            return index;
        }

        std::vector<T> m_data;
};