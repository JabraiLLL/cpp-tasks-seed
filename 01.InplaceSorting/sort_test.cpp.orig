#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "sorting.h"

// BUBBLE SORT TESTS 

TEST(BubbleSortTest, EmptyArray) {
    std::vector<int> arr;
    bubble_sort(arr.begin(), arr.end());
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

TEST(BubbleSortTest, SingleElement) {
    std::vector<int> arr = {42};
    bubble_sort(arr.begin(), arr.end());
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

TEST(BubbleSortTest, AlreadySorted) {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    bubble_sort(arr.begin(), arr.end());
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

TEST(BubbleSortTest, ReversedOrder) {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    bubble_sort(arr.begin(), arr.end());
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

TEST(BubbleSortTest, WithDuplicates) {
    std::vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    bubble_sort(arr.begin(), arr.end());
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

TEST(BubbleSortTest, NegativeNumbers) {
    std::vector<int> arr = {-5, -2, -8, 0, -1, 3, -10};
    bubble_sort(arr.begin(), arr.end());
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

//  QUICK SORT TESTS 

TEST(QuickSortTest, EmptyArray) {
    std::vector<int> arr;
    quick_sort(arr.begin(), arr.end());
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

TEST(QuickSortTest, SingleElement) {
    std::vector<int> arr = {42};
    quick_sort(arr.begin(), arr.end());
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

TEST(QuickSortTest, AlreadySorted) {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    quick_sort(arr.begin(), arr.end());
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

TEST(QuickSortTest, ReversedOrder) {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    quick_sort(arr.begin(), arr.end());
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

TEST(QuickSortTest, WithDuplicates) {
    std::vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    quick_sort(arr.begin(), arr.end());
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

TEST(QuickSortTest, NegativeNumbers) {
    std::vector<int> arr = {-5, -2, -8, 0, -1, 3, -10};
    quick_sort(arr.begin(), arr.end());
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

// INTEGRATION TESTS 

TEST(IntegrationTest, BubbleAndQuickProduceSameResult) {
    std::vector<int> original = {9, 2, 7, 4, 1, 8, 3, 6, 5, 0};
    
    std::vector<int> bubble_copy = original;
    std::vector<int> quick_copy = original;
    
    bubble_sort(bubble_copy.begin(), bubble_copy.end());
    quick_sort(quick_copy.begin(), quick_copy.end());
    
    EXPECT_EQ(bubble_copy, quick_copy);
}

TEST(IntegrationTest, DifferentSizes) {
    std::vector<int> sizes = {0, 1, 10, 100, 1000};
    
    for (int size : sizes) {
        std::vector<int> original(size);
        for (int i = 0; i < size; ++i) {
            original[i] = size - i;
        }
        
        std::vector<int> bubble_copy = original;
        std::vector<int> quick_copy = original;
        
        bubble_sort(bubble_copy.begin(), bubble_copy.end());
        quick_sort(quick_copy.begin(), quick_copy.end());
        
        EXPECT_EQ(bubble_copy, quick_copy) << "Failed for size " << size;
        EXPECT_TRUE(std::is_sorted(bubble_copy.begin(), bubble_copy.end())) 
            << "Not sorted for size " << size;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}