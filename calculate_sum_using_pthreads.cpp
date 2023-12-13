#include <iostream>
#include <pthread.h>

using namespace std;

pthread_mutex_t mutex;
int sum1 = 0, sum2 = 0;

void* sumThread1(void* arg) {
  int* arr1 = (int*)arg;
  int n = sizeof(arr1) / sizeof(int);
  for (int i = 0; i < n; i++) {
    sum1 += arr1[i];
  }
  pthread_mutex_lock(&mutex);
  cout << "Sum of first half: " << sum1 << endl;
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
}

void* sumThread2(void* arg) {
  int* arr2 = (int*)arg;
  int n = sizeof(arr2) / sizeof(int);
  for (int i = 0; i < n; i++) {
    sum2 += arr2[i];
  }
  pthread_mutex_lock(&mutex);
  cout << "Sum of second half: " << sum2 << endl;
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
}

int main() {
  int n;
  cout << "Enter the number of elements: ";
  cin >> n;

  int arr[n];
  cout << "Enter the elements: ";
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  pthread_t thread1, thread2;

  int half = n / 2;
  int* arr1 = arr;
  int* arr2 = arr + half;

  pthread_mutex_init(&mutex, NULL);
  pthread_create(&thread1, NULL, sumThread1, (void*)arr1);
  pthread_create(&thread2, NULL, sumThread2, (void*)arr2);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  int totalSum = sum1 + sum2;
  cout << "Total sum: " << totalSum << endl;

  pthread_mutex_destroy(&mutex);

  return 0;
}

