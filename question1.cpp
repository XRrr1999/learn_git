#include <iostream>
#include <stack>
#include <algorithm>


int divide(std::vector<int>& arr, int left, int right) {
    int num = arr[left];    
    while (left < right){
        while (left < right && arr[right] > num){
            right--;
        }
        if (left < right){
            arr[left++]=arr[right];
        }
        while(left < right && arr[left] < num) {
            left++;
        }
        if(left < right) {
            arr[right--] = arr[left];
        }
    }
    arr[left] = num;
    return left; 
}

void quickSort(std::vector<int> & arr) {
    int left = 0;
    int right = arr.size()-1;
    std::stack<int> Sta;
  
    Sta.push(left);
    Sta.push(right);
  
    while (!Sta.empty()) {
        right = Sta.top(); 
        Sta.pop();
        left = Sta.top(); 
        Sta.pop();
  
        int position = divide(arr, left, right);
  
        if (position-1 > left) {
            Sta.push(left); 
            Sta.push(position - 1);
        }
  
        if (position+1 < right) {
            Sta.push(position + 1); 
            Sta.push(right);
        } 
    }
}


int main(void){
    std::vector<int> arr = {3,4,2,5,1,6};
    quickSort(arr);
    for (auto i:arr){
        std::cout<<i<<"  ";
    }
    return 0;
}