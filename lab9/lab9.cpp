#include <iostream>
#include <vector>
#include <thread>
#include <locale>
#include <Windows.h>

// Класс для сортировки слиянием
class MergeSort {
public:
    // Основной метод сортировки
    void Sort(std::vector<int>& arr) {
        if (arr.size() <= 1) return;
        std::vector<int> left(arr.begin(), arr.begin() + arr.size() / 2);
        std::vector<int> right(arr.begin() + arr.size() / 2, arr.end());

        // Сортировка в параллельных потоках
        std::thread leftThread(&MergeSort::Sort, this, std::ref(left));
        std::thread rightThread(&MergeSort::Sort, this, std::ref(right));

        // Ожидание завершения сортировки в потоках
        leftThread.join();
        rightThread.join();

        // Слияние отсортированных массивов
        Merge(arr, left, right);
    }

private:
    // Метод для слияния двух отсортированных массивов
    void Merge(std::vector<int>& arr, const std::vector<int>& left, const std::vector<int>& right) {
        size_t i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] < right[j]) {
                arr[k++] = left[i++];
            }
            else {
                arr[k++] = right[j++];
            }
        }
        while (i < left.size()) {
            arr[k++] = left[i++];
        }
        while (j < right.size()) {
            arr[k++] = right[j++];
        }
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::vector<int> arr(10);

    std::cout << "Введите 10 чисел для сортировки: ";
    for (int& num : arr) {
        std::cin >> num;
    }

    MergeSort sorter;
    // Анонимная функция для сортировки
    auto sortFunction = [&sorter](std::vector<int>& arr) {
        sorter.Sort(arr);
        };

    // Создание и запуск потока для сортировки
    std::thread mergeSortThread(sortFunction, std::ref(arr));
    mergeSortThread.join();  // Ожидание завершения сортировки

    // Вывод отсортированного массива
    std::cout << "Отсортированный массив: ";
    for (const int& num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}