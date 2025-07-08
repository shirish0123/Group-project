#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace std::chrono;

void printVector(const vector<int>& v) {
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
        if ((i + 1) % 10 == 0) cout << endl;
    }
    cout << endl;
}

int binarySearch(const vector<int>& arr, int key) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int exponentialSearch(const vector<int>& arr, int key) {
    if (arr[0] == key) return 0;
    int i = 1;
    while (i < arr.size() && arr[i] <= key) i *= 2;
    int low = i / 2, high = min(i, (int)arr.size() - 1);
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);
    int i = 0, j = 0, k = left;
    while (i < L.size() && j < R.size()) {
        arr[k++] = (L[i] < R[j]) ? L[i++] : R[j++];
    }
    while (i < L.size()) arr[k++] = L[i++];
    while (j < R.size()) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    srand(time(0));
    const int N = 6;
    vector<int> numbers;

    for (int i = 0; i < N; ++i) {
        numbers.push_back( rand() % 100);
    }

    cout << "Unsorted List:\n";
    printVector(numbers);

    vector<int> quickSorted = numbers;
    auto start = high_resolution_clock::now();
    quickSort(quickSorted, 0, quickSorted.size() - 1);
    auto end = high_resolution_clock::now();
    cout << "Sorted List (Quick Sort):\n";
    printVector(quickSorted);
    cout << "Quick Sort Time: " 
         << duration_cast<microseconds>(end - start).count()
         << " µs\n";

    vector<int> mergeSorted = numbers;
    start = high_resolution_clock::now();
    mergeSort(mergeSorted, 0, mergeSorted.size() - 1);
    end = high_resolution_clock::now();
    cout << "Sorted List (Merge Sort):\n";
    printVector(mergeSorted);
    cout << "Merge Sort Time: " 
         << duration_cast<microseconds>(end - start).count()
         << " µs\n";

    int key;
    cout << "Enter number to search: ";
    cin >> key;

    int indexB = binarySearch(mergeSorted, key);
    if (indexB != -1)
        cout << "Binary Search: Found at index " << indexB << endl;
    else
        cout << "Binary Search: Not Found\n";

    int indexE = exponentialSearch(mergeSorted, key);
    if (indexE != -1)
        cout << "Exponential Search: Found at index " << indexE << endl;
    else
        cout << "Exponential Search: Not Found\n";

    return 0;
}
