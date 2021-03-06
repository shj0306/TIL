# java로 배우는 자료구조

## 리스트

ArrayList

- List 자료형 중 가장 간단한 형태의 자료형

```java
ArrayList<Integer> arrayList = new ArrayList<Integer>();
arrayList.add(1); //맨 뒤에 1 추가
arrayList.add(2);
arrayList.add(3);

arrayList.add(0, 4); //첫번째 위치에 4 추가
```

1. get(int idx) : idx 위치에 값을 출력할 수 있다.

```java
arrayList.get(1); //2번째 값을 출력
```

2. size() : ArrayList의 갯수를 리턴합니다.

```java
System.out.println(arrayList.size());
```

3. contains() : 리스트 안에 해당 항목이 있는 지 판별해 boolean으로 리턴합니다.

```java
System.out.println(arrayList.contains(1)); //true 
```
4. join(구분자, 리스트객체) : 특정 문자로 문자열을 합쳐서 리턴합니다.

```java
ArrayList<String> arrayList = new ArrayList<>(Arrays.asList("123", "456", "789"));
String result = String.join(",", arrayList);
System.out.println(result); //123,456,789
```

**String.join 메소드는 java 8버전부터 사용할 수 있다. **

```java
ArrayList<String> pitches = new ArrayList<String>(Arrays.asList("138", "129", "142"));
arrayList.sort(Comparator.naturalOrder()); // 오름차순 정렬
```



## Map

- key와 value 쌍으로 이루어진 자료구조

1. HashMap

   자바의 맵 중 가장 간단한 hashmap에 대해서 알아보자.

   put : 데이터 추가할 때 사용할 수 있다.

   ```java
   HashMap<String, String> map = new HashMap<>();
   map.put("people", "사람");
   map.put("baseball", "야구");
   ```

   get (object key) : key값에 해당되는 value값을 리턴합니다.

   ```java
   System.out.println(map.get("people")); //사람
   ```

   containsKey : 맵(Map)에 해당 키가 있는 지를 조사하여 그 결과값을 리턴합니다.

   ```java
   System.out.println(map.containsKey("people")); //true
   ```

   remove : 맵의 항목을 삭제하는 메소드로 key값에 해당되는 아이템(key,value)을 삭제한 후 그 값을 리턴합니다.

   ```java
   System.out.println(map.remove("people")); //item이 삭제된 후 사람 출력
   ```

   KeySet : 맵의 모든 key를 리턴합니다.

   ```java
    System.out.println(map.keySet());  // [baseball, people] 출력
   ```

   keySet 메소드는 Map의 모든 key를 모아서 Set 자료형으로 리턴합니다.

LinkedHashMap과 TreeMap

Map의 가장 큰 트징은 순서에 의존하지 않고, key로 value를 가져오는 데 있습니다. 하지만 가끔 Map에 입력된 순서대로 데이터를 가져오고 싶은 경우도 있고, 때론 입력된 key에 의해 정렬된 데이터를 가져오고 싶을 수도 있습니다. 이런 경우엔 LinkedHashMap, TreeMap을 사용하는 것이 유리합니다.
