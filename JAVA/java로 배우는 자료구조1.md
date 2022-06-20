# java로 배우는 자료구조

## 변수, 배열, 반복문

String 변수 생성시 주소 할당

1. 리터럴을 이용한 방식
2. new 연산자를 이용한 방식

> 리터럴을 사용하게 되면 string constant pool이라는 영역에 존재하게 되고, new를 통해 String을 생성하면 힙 영역에 존재하게 됩니다. 

> String을 리터럴로 선언할 경우 내부적으로 String의 intern() 메서드가 호출되게 되고, intern() 메서드는 주어진 문자열이 string constant pool에 존재하는 지 검색하고 있다면 그 주소값을 반환하고 없다면 string constant pool에 넣고 새로운 주소값을 반환합니다.

```java
String str1 = "apple"; //리터럴을 이용한 방식
String str2 = new String("apple"); //new 연산자를 이용한 방식
```

<img src="https://blog.kakaocdn.net/dn/cAbQYM/btrm3PpaEN2/AuIXpphooR5Q2KuPDYf5JK/img.png" alt="String 주소할당" style="zoom:80%;" />

### 정렬

1. bubble sort

   인접한 두 원소의 크기를 비교하면서 정렬해가는 알고리즘

   ```java
   private static int[] bubble_sort(int n, int[] arr) {
           for (int i = n-1; i > 0; i--) {
               for (int j = 0; j < i; j++) {
                   if (arr[j] > arr[j+1]) {
                       int tmp = arr[j];
                       arr[j] = arr[j+1];
                       arr[j+1] = tmp;
                   }
               }
           }
           return arr;
   }
   ```

2. insertion sort

   자료 배열의 모든 요소를 앞에서부터 차례대로 이미 정렬된 배열 부분과 비교하여, 자신의 위치를 찾아 삽입해 정렬해나가는 알고리즘

   ```java
   private static int[] insertion_sort(int n, int[] arr) {
           for (int i = 1; i < n; i++) {
               for (int j = i-1; j >= 0 && arr[j+1] < arr[j]; j--) {
                   int tmp = arr[j+1];
                   arr[j+1] = arr[j];
                   arr[j] = tmp;
               }
           }
           return arr;
   }
   ```

3. selection sort

   해당 인덱스에 들어갈 원소를 결정해서 넣어주는 알고리즘

   ```java
   private static int[] selection_sort(int n, int[] arr) {
           for (int i = 0; i < n-1; i++) {
               int val = arr[i];
               int min_id = i;
               for (int j = i; j < n; j++) {
                   if (val > arr[j]) {
                       val = arr[j];
                       min_id = j;
                   }
               }
   
               arr[min_id] = arr[i];
               arr[i] = val;
           }
           return arr;
   }
   ```

