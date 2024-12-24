#include <stdexcept>
#include <vector>

template <typename T>
class CircularBuffer {
public:
    // Constructor initializes buffer with given size
    CircularBuffer(const size_t size) : start(0), end(0), is_full(false), buffer(size)  {

    }

    // Adds an element to the end of the buffer
    void push_back(const T& item) {
        buffer[end] = item;
        end = (end + 1) % buffer.size();

        if (is_full) {
            // Move the start if buffer is full (overwriting)
            start = (start + 1) % buffer.size();
        } else if (end == start) {
            is_full = true;
        }
    }

    // Get first member of buffer
    T& front() {
        if(isEmpty()){
            throw std::out_of_range("Buffer is empty");
        }
        return buffer[start];
    }
    const T& front() const{
        if(isEmpty()){
            throw std::out_of_range("Buffer is empty");
        }
        return buffer[start];
    }
    // Get last member of buffer
    T& back() {
        if(isEmpty()){
            throw std::out_of_range("Buffer is empty");
        }
        size_t last_index = (end == 0) ? buffer.size() - 1 : end - 1;
        return buffer[last_index];
    }
    const T& back() const{
        if(isEmpty()){
            throw std::out_of_range("Buffer is empty");
        }
        size_t last_index = (end == 0) ? buffer.size() - 1 : end - 1;
        return buffer[last_index];
    }
    // Overload [] operator for element access by index
    T& operator[](size_t index) {
        if (index >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return buffer[(start + index) % buffer.size()];
    }
    const T& operator[](size_t index) const{
        if (index >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return buffer[(start + index) % buffer.size()];
    }

    // Get current number of elements in the buffer
    size_t size() const {
        if (is_full) {
            return buffer.size();
        }
        if (end >= start) {
            return end - start;
        }
        return buffer.size() - (start - end);
    }

    // Check if buffer is empty
    bool isEmpty() const {
        return (!is_full && (start == end));
    }
    // Check if buffer is full
    bool isFull() const{
        return is_full;
    }


private:
    std::vector<T> buffer;
    size_t start;
    size_t end;
    bool is_full;
};