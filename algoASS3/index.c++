#include <iostream>
#include <vector>
#include <random>

int selectionSort(std::vector<int>& arr) {
    int comparisons = 0;
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            comparisons++;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }

    return comparisons;
}

int insertionSort(std::vector<int>& arr) {
    int comparisons = 0;
    int n = arr.size();

    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            comparisons++;
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }

    return comparisons;
}

int partition(std::vector<int>& arr, int low, int high, int& comparisons) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        comparisons++;
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

int quicksort(std::vector<int>& arr, int low, int high, int& comparisons) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high, comparisons);
        quicksort(arr, low, pivotIndex - 1, comparisons);
        quicksort(arr, pivotIndex + 1, high, comparisons);
    }

    return comparisons;
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 10000);

    std::vector<std::vector<int>> sets(10, std::vector<int>(1000));
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 1000; ++j) {
            sets[i][j] = dis(gen);
        }
    }

    for (int i = 0; i < 10; ++i) {
        std::vector<int> set = sets[i];

        int comparisons_selection = selectionSort(set);
        int comparisons_insertion = insertionSort(set);
        int comparisons_quicksort = 0;
        quicksort(set, 0, set.size() - 1, comparisons_quicksort);

        std::cout << "Set " << i + 1 << ":\n";
        std::cout << "Selection Sort Comparisons: " << comparisons_selection << "\n";
        std::cout << "Insertion Sort Comparisons: " << comparisons_insertion << "\n";
        std::cout << "Quicksort Comparisons: " << comparisons_quicksort << "\n\n";
    }

    return 0;
}
