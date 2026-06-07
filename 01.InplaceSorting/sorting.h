#ifndef SORTING_H
#define SORTING_H

#include <iterator>
#include <algorithm>

// BUBBLE SORT O(n²) 
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end) {
    if (begin == end) return;
    
    int n = std::distance(begin, end);
    
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        
        for (Iterator j = begin; j != begin + (n - i - 1); ++j) {
            Iterator next = j;
            ++next;
            
            if (*next < *j) {
                std::swap(*j, *next);
                swapped = true;
            }
        }
        
        if (!swapped) break;
    }
}

// QUICK SORT O(n log n) 
template <typename Iterator>
Iterator partition(Iterator begin, Iterator end) {
    Iterator pivot = end;
    --pivot;
    
    Iterator i = begin;
    
    for (Iterator j = begin; j != pivot; ++j) {
        if (*j < *pivot) {
            std::swap(*j, *i);
            ++i;
        }
    }
    
    std::swap(*i, *pivot);
    return i;
}

template <typename Iterator>
void quick_sort(Iterator begin, Iterator end) {
    if (begin == end) return;
    
    Iterator next = begin;
    ++next;
    if (next == end) return;
    
    Iterator pivot_pos = partition(begin, end);
    quick_sort(begin, pivot_pos);
    
    Iterator after_pivot = pivot_pos;
    ++after_pivot;
    quick_sort(after_pivot, end);
}

#endif // SORTING_H