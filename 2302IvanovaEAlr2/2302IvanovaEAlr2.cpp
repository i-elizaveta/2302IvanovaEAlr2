#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;

void selectionSort(int arr[], int n) 
{
	
		for (int i = 0; i < n - 1; i++) 
		{
			int minIndex = i;
			for (int j = i + 1; j < n; j++) 
			{
				if (arr[j] < arr[minIndex]) 
					minIndex = j;
				
			}
			swap(arr[i], arr[minIndex]);
		}
	
}

void insertionSort(int arr[], int n) 
{
	
		for (int i = 1; i < n; i++) {
			int key = arr[i];
			int j = i - 1;
			while (j >= 0 && arr[j] > key) {
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = key;
		}
	
}

void bubbleSort(int arr[], int n) 
{
	
		for (int i = 0; i < n - 1; i++) 
		{
			for (int j = 0; j < n - i - 1; j++) 
			{
				if (arr[j] > arr[j + 1]) 
					swap(arr[j], arr[j + 1]);
			}
	
		}
}

void merge(int arr[], int l, int m, int r) 
{
	int n1 = m - l + 1;
	int n2 = r - m;

	int L[1000], R[1000];

	for (int i = 0; i < n1; i++) 
	{
		L[i] = arr[l + i];
	}
	for (int j = 0; j < n2; j++) 
	{
		R[j] = arr[m + 1 + j];
	}

	int i = 0, j = 0, k = l;

	while (i < n1 && j < n2) 
	{
		if (L[i] <= R[j]) 
		{
			arr[k] = L[i];
			i++;
		}
		else 
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) 
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) 
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(int arr[], int l, int r) 
{
	if (l >= r) 
	{
		return;
	}
	int m = l + (r - l) / 2;
	mergeSort(arr, l, m);
	mergeSort(arr, m + 1, r);
	merge(arr, l, m, r);
}



int partition(int arr[], int low, int high) 
{
	int pivot = arr[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) 
	{
		if (arr[j] < pivot) 
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return i + 1;
}

void quickSort(int arr[], int low, int high) 
{
	if (low < high) 
	{
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}


	

void shellSort(int arr[], int n) 
{
	for (int gap = n / 2; gap > 0; gap /= 2) 
	{
		for (int i = gap; i < n; i++) 
		{
			int temp = arr[i];
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) 
				arr[j] = arr[j - gap];
			
			arr[j] = temp;
		}
	}
}


void heapify(int arr[], int n, int i) 
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && arr[l] > arr[largest]) 
		largest = l;
	

	if (r < n && arr[r] > arr[largest]) 
		largest = r;
	

	if (largest != i) 
	{
		swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}

void heapSort(int arr[], int n) 
{
	for (int i = n / 2 - 1; i >= 0; i--) 
	{
		heapify(arr, n, i);
	}

	for (int i = n - 1; i >= 0; i--) {
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}


//void timSort(int arr[], int n) 
const int RUN = 32;

void insertionSort(int arr[], int left, int right) 
{
	for (int i = left + 1; i <= right; i++) 
	{
		int temp = arr[i];
		int j = i - 1;
		while (j >= left && arr[j] > temp) 
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = temp;
	}
}

void timSort(int arr[], int n) 
{
	for (int i = 0; i < n; i += RUN) 
		insertionSort(arr, i, min((i + RUN - 1), (n - 1)));
	
	for (int size = RUN; size < n; size = 2 * size) 
	{
		for (int left = 0; left < n; left += 2 * size) 
		{
			int mid = left + size - 1;
			int right = min((left + 2 * size - 1), (n - 1));
			merge(arr, left, mid, right);
		}
	}
}

	

void introSort(int arr[], int n) 
{
	if (n <= 1) 
		return;
	
	if (n < 16) 
	{
		insertionSort(arr, n);
		return;
	}
	if (n < 2 * log2(n)) 
	{
		heapSort(arr, n);
		return;
	}
	int pivot = arr[n / 2];
	int i = -1, j = n;
	while (true) 
	{
		do 
		{
			i++;
		} 
		while (arr[i] < pivot);
		do
		{
			j--;
		} 
		while (arr[j] > pivot);
		if (i >= j) 
			break;
		swap(arr[i], arr[j]);
	}
	introSort(arr, i);
	introSort(arr + i, n - i);
}


int main() 
{
	setlocale(LC_ALL, "Russian");
	const int k = 1000;
	int n;

	cout << "Введите размер массива: ";
	cin >> n;
	
	int arr[k];
	cout << "Введите элементы массива: ";
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	auto start = chrono::high_resolution_clock::now();
	selectionSort(arr, n);
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
	cout << "Selection sort time: " << duration.count() << " nanoseconds" << endl;

	
	start = chrono::high_resolution_clock::now();
	void insertionSort(int arr[], int n);
	end = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
	cout << "Insertion sort time: " << duration.count() << " nanoseconds" << endl;

	start = chrono::high_resolution_clock::now();
	void bubbleSort(int arr[], int n);
	end = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
	cout << "Bubble sort time: " << duration.count() << " nanoseconds" << endl;

	
	start = chrono::high_resolution_clock::now();
	void mergeSort(int arr[], int l, int r);
	end = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
	cout << "Merge sort time: " << duration.count() << " nanoseconds" << endl;
	
	start = chrono::high_resolution_clock::now();
	void quickSort(int arr[], int low, int high);
	end = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
	cout << "Quick sort time: " << duration.count() << " nanoseconds" << endl;

	start = chrono::high_resolution_clock::now();
	void shellSort(int arr[], int n);
	end = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
	cout << "Shell sort time: " << duration.count() << " nanoseconds" << endl;

	
	start = chrono::high_resolution_clock::now();
	heapSort(arr, n);
	end = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
	cout << "Heap sort time: " << duration.count() << " nanoseconds" << endl;


	start = chrono::high_resolution_clock::now();
	timSort(arr, n);
	end = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
	cout << "Tim sort time: " << duration.count() << " nanoseconds" << endl;

	
	start = chrono::high_resolution_clock::now();
	void introSort(int arr[], int n);
	end = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
	cout << "Intro sort time: " << duration.count() << " nanoseconds" << endl;
	int choice;
	do {
		cout << "\n\n Меню:\n";
		cout << "1. Selection Sort\n";
		cout << "2. Insertion Sort\n";
		cout << "3. Bubble Sort\n";
		cout << "4. Merge Sort\n";
		cout << "5. Quick Sort\n";
		cout << "6. Shell Sort\n";
		cout << "7. Heap Sort\n";
		cout << "8. Timsort\n";
		cout << "9. Introsort\n";
		cout << "10. Выход\n";
		cout << "\nВыберите одну из сортировок или нажмите 10 для выхода: ";
		cin >> choice;
		switch (choice) {
		case 1:
			selectionSort(arr, n);
			
			break;
		case 2:
			insertionSort(arr, n);
			break;
		case 3:
			bubbleSort(arr, n);
			break;
		case 4:
			mergeSort(arr, 0, n - 1);
			break;
		case 5:
			quickSort(arr, 0, n - 1);
			break;
		case 6:
			shellSort(arr, n);
			break;
		case 7:
			heapSort(arr, n);
			break;
		case 8:
			timSort(arr, n);
			break;
		case 9:
			introSort(arr, n);
			break;
		case 10:
			cout << "Вы завершили работу\n";
			break;
		default:
			cout << "Неверный выбор, повторите попытку.\n";
		}
		if (choice != 10) {
			cout << "Отсортированный массив: ";
			for (int i = 0; i < n; i++) {
				cout << arr[i] << " ";
			}
			cout << endl;
		}
	} 
	while (choice != 10);
	// Sort and time selection sort
	
	return 0;
}
