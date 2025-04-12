#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <chrono>
#include <random>
#include <string>
#include <fstream>

using namespace std;

vector<vector<int>> threeSumBruteForce(vector<int>& nums) {
    vector<vector<int>> result;
    int n = nums.size();
    
    unordered_set<string> seen;
    
    sort(nums.begin(), nums.end());
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (nums[i] + nums[j] + nums[k] == 0) {
                    vector<int> triplet = {nums[i], nums[j], nums[k]};
                    
                    string triplet_key = to_string(nums[i]) + "," + 
                                       to_string(nums[j]) + "," + 
                                       to_string(nums[k]);
                    
                    if (seen.find(triplet_key) == seen.end()) {
                        result.push_back(triplet);
                        seen.insert(triplet_key);
                    }
                }
            }
        }
    }
    
    return result;
}

vector<vector<int>> threeSumOptimized(vector<int>& nums) {
    vector<vector<int>> result;
    int n = nums.size();
    
    sort(nums.begin(), nums.end());
    
    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        
        int left = i + 1;
        int right = n - 1;
        
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            
            if (sum < 0) {
                left++;
            } else if (sum > 0) {
                right--;
            } else {
                result.push_back({nums[i], nums[left], nums[right]});
                
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                
                left++;
                right--;
            }
        }
    }
    
    return result;
}

vector<int> generateArray(int size) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(-100, 100);
    
    for (int i = 0; i < size; i++) {
        arr[i] = dist(gen);
    }
    
    if (size >= 3) {
        arr[0] = 5;
        arr[1] = 10;
        arr[2] = -15;  
    }
    
    return arr;
}

int main() {
    vector<int> sizes = {100, 200, 400, 800, 1600, 3200};
    
    ofstream dataFile("runtime_data.csv");
    dataFile << "size,brute_force_ms,optimized_ms\n";
    
    for (int size : sizes) {
        vector<int> nums = generateArray(size);
        
        auto start_bf = chrono::high_resolution_clock::now();
        vector<vector<int>> result_bf = threeSumBruteForce(nums);
        auto end_bf = chrono::high_resolution_clock::now();
        double time_bf_ms = chrono::duration_cast<chrono::microseconds>(end_bf - start_bf).count() / 1000.0;
        
        auto start_opt = chrono::high_resolution_clock::now();
        vector<vector<int>> result_opt = threeSumOptimized(nums);
        auto end_opt = chrono::high_resolution_clock::now();
        double time_opt_ms = chrono::duration_cast<chrono::microseconds>(end_opt - start_opt).count() / 1000.0;
        
        cout << "Size: " << size << endl;
        cout << "Brute Force Time: " << time_bf_ms << " ms" << endl;
        cout << "Optimized Time: " << time_opt_ms << " ms" << endl;
        cout << "Brute Force Triplets: " << result_bf.size() << endl;
        cout << "Optimized Triplets: " << result_opt.size() << endl;
        cout << "----------------------------" << endl;
        
        dataFile << size << "," << time_bf_ms << "," << time_opt_ms << endl;
    }
    
    dataFile.close();
    cout << "Runtime data saved to runtime_data.csv" << endl;
    
    return 0;
}

