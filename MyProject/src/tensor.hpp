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

    private:

        static constexpr size_t calculateSize()
        {
            return (Dims * ... * 1);
        }

        std::vector<T> m_data;
};