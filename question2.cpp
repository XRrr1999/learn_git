#include <iostream>
#include <optional>
#include <array>
template <typename T, std::size_t N> 
class RingBuffQueue{
public:
    constexpr RingBuffQueue(): head(0), tail(0){}
  
    // 如果满了返回false, 成功返回true
    bool enqueue(T val) {
        std::size_t newtail = (tail + 1) % N;
        if (newtail == head){
            return false;
        }
        else{
            buff[tail] = val;
            tail = newtail;
            return true;
        }
    }

    // 如果空返回nullopt, 成功返回队首元素
    std::optional<T> dequeue() {
        if (head == tail) {
            return std::nullopt;
        }
        else{
            T ret = buff[head];
            head = (head + 1) % N;
            return ret;
        }
    }
  
private:
    std::array<T, N> buff;
    size_t head;
    size_t tail;
};

int main(void){
    RingBuffQueue<int, 5> ringqueue;

    for (int i = 1; i <= 5; i++){
        if(ringqueue.enqueue(i)){
            std::cout << "Yes" << i << std::endl;
        } else {
            std::cout << "No" << i << std::endl;
        }
    }
    
    
    for (int i = 1; i <= 5; i++){ 
        auto result = ringqueue.dequeue();
        if(result.has_value()){
            std::cout << "Yes" << result.value() << std::endl;
        } else {
            std::cout << "No" << std::endl;
        }
    }

    return 0;
}