#include <iostream>
#include <chrono>

using namespace std;

double* doubleDataGenerator(int size) { // Генератор входных данных (double) 
	double* arrayWithRandomData = new double[size];

	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		arrayWithRandomData[i] = (double)rand() / (double)RAND_MAX * 100; // от 0 до 100
	}

	return arrayWithRandomData;
};


float* floatDataGenerator(int size) { // Генератор входных данных (float)
	float* arrayWithRandomData = new float[size];

	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		arrayWithRandomData[i] = (float)rand() / (float)RAND_MAX * 100; // от 0 до 100
	}

	return arrayWithRandomData;
};


template <class T>
T* simpleMovingAverage(int window, T* inputData, int size) { // Алгоритм простого скользящего среднего 

	if (window % 2 == 0) { // Если размер окна четный, тогда увеличиваем на единицу, для одинакового расстояния захвата значений относительно центрального значения 
		window++;
	}

	int range = (window - 1) / 2; // Расстояние, по левую и правую сторону, от центрального значения
	T* result = new T[size];
	int firstIndex, lastIndex; // Границы окна
	T temp = 0;

	for (int i = range; i < size - range; i++) { // Пропускаем крайние входные данные, которые короче длины range
		firstIndex = i - range;
		lastIndex = i + range;

		for (int j = firstIndex; j <= lastIndex; j++) {
			temp += inputData[j];
			result[i] = temp / window;
		}
		temp = 0;
	}

	return result;
};


int main() {

	const int count = 200000000; // Количество отсчётов  
	const int window = 4; // Длина окна | 4 8 16 32 64 128

	double* inputDataDouble = doubleDataGenerator(count); // Генерация входных данных (тип: double)
	float* inputDataFloat = floatDataGenerator(count); // Генерация входных данных (тип: float)

	auto start = chrono::high_resolution_clock::now(); // Запуск таймера для измерения выполнения функции

	auto result = simpleMovingAverage(window, inputDataDouble, count);

	auto end = chrono::high_resolution_clock::now(); // Остановка таймера
	chrono::duration<float> time = end - start;
	cout << "Function execution time : " << time.count() << " s." << endl;

	delete[] inputDataDouble;
	delete[] inputDataFloat;
	delete[] result;
	return 0;
}