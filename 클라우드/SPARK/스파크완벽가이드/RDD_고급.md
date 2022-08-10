# RDD 고급 개념

- 집계와 키-값 형태의 RDD
- 사용자 정의 파티셔닝
- RDD 조인

## 키-값 형태의 RDD

RDD에는 데이터를 키-값 형태로 다룰 수 있는 다양한 메서드가 있습니다. 

이러한 메서드는 **<연산명>ByKey** 형태의 이름을 가집니다. 메서드 이름에 ByKey가 있다면 PairRDD 타입만 사용할 수 있습니다. PairRDD 타입을 만드는 가장 쉬운 방법은 RDD에 맵 연산을 수행해 키-값 구조로 만드는 겁니다. 즉 RDD 레코드에 두 개의 값이 존재합니다.

```scala
words.map(word => (word.toLowerCase, 1))

// org.apache.spark.rdd.RDD[(String, Int)] 
```

### 1. keyBy

- 현재 값으로부터 키를 생성하는 keyBy 함수를 사용해 동일한 결과를 얻을 수 있습니다.

- 예제) 단어의 첫 번째 문자를 킬로 만들어 RDD를 생성합니다.

  ```scala
  val keyword = words.keyBy(word => word.toLowerCase.toSeq(0).toString)
  //org.apache.spark.rdd.RDD[(String, String)]
  ```

  ```python
  keyword = words.keyBy(lambda word : word.lower()[0])
  ```

  이 때 스파크는 원본 단어를 생성된 RDD의 값으로 유지합니다.

### 2. 값 매핑하기

mapValues 메서드를 사용하면 값 수정 시 발생할 수 있는 오류를 미리 방지 할 수 있습니다.

```scala
keyword.mapValues(word => word.toUpperCase).collect()
```

flatMap 함수를 사용해 반환되는 결과의 각 로우가 문자를 나타내도록 확장할 수 있습니다.

- 예제) 단어의 첫 글자를 키로, 단어의 각 문자를 값으로 하는 배열 생성

  ```scala
  keyword.flatMapValues(word => word.toUpperCase).collect()
  /*
   Array[(String, Char)] = Array((s,S), (s,P), (s,A), (s,R), (s,K), (t,T), (t,H), (t,E), (d,D), (d,E), (d,F), (d,I), (d,N), (d,I), (d,T), (d,I), (d,V), (d,E), (g,G), (g,U), (g,I), (g,D), (g,E), (:,:), (b,B), (b,I), (b,G), (d,D), (d,A), (d,T), (d,A), (p,P), (p,R), (p,O), (p,C), (p,E), (p,S), (p,S), (p,I), (p,N), (p,G), (m,M), (m,A), (m,D), (m,E), (s,S), (s,I), (s,M), (s,P), (s,L), (s,E))
  */
  ```

### 3. 키와 값 추출하기

```scala
keyword.keys.collect()
keyword.values.collect()
```

### 4. lookup

- 특정 키에 관한 결과를 찾을 때 사용합니다.

- 예제) s로 시작하는 단어 조회

  ```scala
  keyword.lookup("s")
  //WrappedArray(Spark, Simple)
  ```

### 5. sampleByKey

- 근사치나 정확도를 이용해 키를 기반으로 RDD 샘플을 생성할 수 있습니다.

- 두 작업 모두 특정 키를 부분 샘플링할 수 있으며 선택에 따라 비복원 추출을 사용할 수도 있습니다.

  ```scala
  val distinctChars = words.flatMap(word => word.toLowerCase.toSeq).distinct.collect()
  
  import scala.util.Random
  val sampleMap = distinctChars.map(c => (c, new Random().nextDouble())).toMap
  words.map(word => (word.toLowerCase.toSeq(0), word)).sampleByKey(true, sampleMap, 6L).collect()
  ```

  sampleByKey 메서드는 RDD를 한번만 처리하면서 간단한 무작위 샘플링을 사용하기 때문에 모든 키값에 대한 math.ceil(numItems * samplingRate) 값의 총합과 거의 동일한 크기의 샘플을 생성합니다.

## 집계

```scala
val chars = words.flatMap(word => word.toLowerCase.toSeq)
val KVcharacters = chars.map(letter => (letter, 1))

def maxFunc(left:Int, right:Int) = math.max(left, right)
def addFUnc(left:Int, right:Int) = left + right

val nums = sc.parallelize(1 to 30, 5)
```

### 1. countByKey

- countByKey 메서드는 각 키의 아이템 수를 구하고 로컬 맵으로 결과를 수집합니다.

  ```scala
  KVcharacters.countByKey()
  /*
  res10: scala.collection.Map[Char,Long] = Map(e -> 7, s -> 4, n -> 2, t -> 3, u -> 1, f -> 1, a -> 4, m -> 2, i -> 7, v -> 1, b -> 1, g -> 3, l -> 1, p -> 3, c -> 1, h -> 1, r -> 2, : -> 1, k -> 1, o -> 1, d -> 4)
  */
  ```

  

- 스칼라나 자바를 사용한다면 countByKey 메서드에 제한 시간과 신뢰도를 인수로 지정해 근사치를 구할 수 있습니다.

  ```scala
  KVcharacters.countByKeyApprox(timeout, confidence)
  /*
  Map(e -> [7.000, 7.000], s -> [4.000, 4.000], n -> [2.000, 2.000], t -> [3.000, 3.000], u -> [1.000, 1.000], f -> [1.000, 1.000], a -> [4.000, 4.000], m -> [2.000, 2.000], i -> [7.000, 7.000], v -> [1.000, 1.000], b -> [1.000, 1.000], g -> [3.000, 3.000], l -> [1.000, 1.000], p -> [3.000, 3.000], c -> [1.000, 1.000], h -> [1.000, 1.000], r -> [2.000, 2.000], : -> [1.000, 1.000], k -> [1.000, 1.000], o -> [1.000, 1.000], d -> [4.000, 4.000]))
  */
  ```

### 2. 집계 연산 구현 방식 이해하기

### 2-1. groupByKey

- 각 키의 총 레코드 수를 구하는 경우, groupByKey의 결과로 만들어진 그룹에 map 연산을 수행하는 방식이 가장 좋습니다.

  ```python
  from functools import reduce
  
  KVcharacters.groupByKey().map(lambda row: (row[0], reduce(addFunc, row[1]))).collect()
  
  #success
  ```

  ```scala
  KVcharacters.groupByKey().map(row => (row._1, row._2.reduce(addFunc))).collect()
  
  //null pointer exception
  ```

  여기서 가장 큰 문제는 모든 익스큐터에 함수를 적용하기 전에 해당 키와 관련된 모든 값을 메모리로 읽어 들여야 한다는 겁니다. 그 이유는 심각하게 치우쳐진 키가 있다면 일부 파티션이 엄청난 양의 값을 가질 수 있으므로 OutofMemoryError가 발생할 수 있습니다. 

  대규모 분산환경에서는 심각한 문제로 이어질 수 있기 때문에 주의해야 합니다. 그러므로 각 키에 대한 값의 크기가 일정하고 익스큐터에 할당된 메모리에서 처리 가능할 정도의 크기라면 groupByKey 메서드를 사용합니다.

### 2-2. reduceByKey

- 각 파티션에서 리듀스 작업을 수행하기 때문에 훨씬 안정적이며 모든 값을 메모리에 유지하지 않아도 됩니다. 또한 최종 리듀스 과정을 제외한 모든 작업은 개별 워커에서 처리하기 때문에 연산 중에 셔플이 발생하지 않습니다.

  ```scala
  KVcharacters.reduceByKey(addFunc).collect()
  /*
  Array[(Char, Int)] = Array((d,4), (p,3), (t,3), (b,1), (h,1), (n,2), (f,1), (v,1), (:,1), (r,2), (l,1), (s,4), (e,7), (a,4), (i,7), (k,1), (u,1), (o,1), (g,3), (m,2), (c,1))
  */
  ```

  키별 그룹 RDD를 반환합니다. 그러나 RDD의 개별 요소들은 정렬되어 있지 않기 때문에 결과의 순서가 중요한 경우에는 적합하지 않습니다.

### 2-3. 기타 집계 메서드

#### 2-3-1. aggregate

null 값이나 집계 시작값이 필요하며 두 가지 함수를 파라미터로 사용합니다.

첫 번째 함수는 파티션 내에 수행되고, 두 번째 함수는 모든 파티션에 걸쳐 수행됩니다. 두 함수 모두 시작값을 사용합니다.

```scala
nums.aggregate(0)(maxFunc, addFunc)
```

aggregate 함수 같은 경우 드라이버에서 최종 집계를 수행하기 때문에 익스큐터의 결과가 너무 크면 OutOfMemoryError가 발생해 드라이버가 비정상적으로 종료될 수 있습니다.

aggregate 함수와 동일한 작업을 수행하지만 다른 처리 과정을 거치는 treeAggregate 함수도 있습니다. 이 함수는 기본적으로 드라이버에서 최종 집계를 수행하기 전에 익스큐터끼리 트리를 형성해 집계 처리의 일부 하위 과정을 **푸시 다운** 방식으로 먼저 수행합니다.

집계 처리를 여러 단계로 구성하는 것은 드라이버의 메모리를 모두 소비하는 현상을 막는 데 도움이 됩니다. 이러한 트리 기반의 구현 방식은 작업의 안정성을 높일 수 있습니다.

```scala
val depth = 3
nums.treeAggregate(0)(maxFunc, addFunc, depth)
```

#### 2-3-2. aggregateByKey

aggregateByKey는  aggregate 함수와 동일하지만 파티션 대신 키를 기준으로 연산을 수행합니다.

```scala
KVcharacters.aggregateByKey(0)(addFunc, maxFunc).collect()
```

#### 2-3-3. combineByKey

combineByKey 함수는 집계 함수 대신 컴바이너를 사용합니다. 이 컴바이너는 키를 기준으로 연산을 수행하며 파라미터로 사용된 함수에 따라 값을 병합합니다. 그 다음 여러 컴바이너의 결괏값을 병합해 결과를 반환합니다. 사용자 정의 파티셔너를 사용해 출력 파티션 수를 지정할 수도 있습니다.

사용자는 세가지 함수를 제공해야 한다.

1. createCombiner : Value값을 하나의 리스트로 만들어 준다.
2. mergeValue : value값을 리스트에 추가한다.
3. mergeCombiners : 2 개의 리스트를 하나로 병합한다.

```scala
val valToCombiner = (value:Int) => List(value)
val mergeValuesFunc = (vals:List[Int], valToAppend:Int) => valToAppend :: vals
val mergeCombinerFunc = (vals1:List[Int], vals2:List[Int]) => vals1 ::: vals2

val outputPartitions = 6

KVcharacters
.combineByKey(
  valToCombiner,
  mergeValuesFunc,
  mergeCombinerFunc,
  outputPartitions
).collect()

/*
 Array[(Char, List[Int])] = Array((f,List(1)), (r,List(1, 1)), (l,List(1)), (s,List(1, 1, 1, 1)), (a,List(1, 1, 1, 1)), (g,List(1, 1, 1)), (m,List(1, 1)), (t,List(1, 1, 1)), (b,List(1)), (h,List(1)), (n,List(1, 1)), (i,List(1, 1, 1, 1, 1, 1, 1)), (u,List(1)), (o,List(1)), (c,List(1)), (d,List(1, 1, 1, 1)), (p,List(1, 1, 1)), (v,List(1)), (:,List(1)), (e,List(1, 1, 1, 1, 1, 1, 1)), (k,List(1)))
*/
```

#### 2-3-4. foldByKey

- 결합 함수와 항등원인 '제로값'을 이용해 각 키의 값을 병합합니다.

  ```scala
  KVcharacters.foldByKey(0)(addFunc).collect()
  /*
   Array[(Char, Int)] = Array((d,4), (p,3), (t,3), (b,1), (h,1), (n,2), (f,1), (v,1), (:,1), (r,2), (l,1), (s,4), (e,7), (a,4), (i,7), (k,1), (u,1), (o,1), (g,3), (m,2), (c,1))
  */
  ```

## cogroup

스칼라를 사용하는 경우 최대 3개, 파이썬을 사용하는 경우 최대 2개의 키-값 형태의 RDD를 그룹화할 수 있으며, 각 키를 기준으로 값을 결합합니다. 즉 RDD에 대한 그룹 기반의 조인을 수행합니다.

cogroup 함수는 출력 파티션 수나 클러스터에 데이터 분산 방식을 정확하게 제어하기 위해 사용자 정의 파티션 함수를 파라미터로 사용할 수 있습니다.

```scala
import scala.util.Random

val distinctChars = words.flatMap(word => word.toLowerCase.toSeq).distinct
val charRDD = distinctChars.map(C => (C, new Random().nextDouble()))
val charRDD2 = distinctChars.map(C => (C, new Random().nextDouble()))
val charRDD3 = distinctChars.map(C => (C, new Random().nextDouble()))

charRDD.cogroup(charRDD2, charRDD3).take(5)

/*
 Array((d,(CompactBuffer(0.1231185888399442),CompactBuffer(0.8259508070859128),CompactBuffer(0.8949670068917723))), (p,(CompactBuffer(0.10544706826133576),CompactBuffer(0.39319377910225506),CompactBuffer(0.5385153673207894))), (t,(CompactBuffer(0.6017792499218054),CompactBuffer(0.03971271769193907),CompactBuffer(0.540674860765947))), (b,(CompactBuffer(0.409403530884179),CompactBuffer(0.477590030829773),CompactBuffer(0.6383650295475158))), (h,(CompactBuffer(0.9153838186265776),CompactBuffer(0.26729627733427685),CompactBuffer(0.11813396946970545))))
*/
```

### 1. 조인

RDD는 구조적 API의 조인 방식과 거의 동일하지만, RDD를 사용하면 사용자가 많은 부분에 관여해야 합니다. 기본적으로 두 개의 RDD가 필요하고, 때에 따라 **출력 파티션 수**나 **사용자 정의 파티션 함수**를 파라미터로 사용합니다.

#### 1-1. 내부 조인

```scala
val keyedChars = distinctChars.map(c => (c, new Random().nextDouble()))
val outputPartitions = 10

KVcharacters.join(keyedChars).count() //51
KVcharacters.join(keyedChars, outputPartitions).count() //51
```

- fullOuterJoin : 외부 조인
- leftOuterJoin : 왼쪽 외부 조인
- rightOuterJoin : 오른쪽 외부 조인
- cartesian : 교차 조인

#### 1-2. zip

zip 함수를 사용해 동일한 길이의 두 개의 RDD를 지퍼를 잠그듯 연결할 수 있으며, PairRDD를 생성합니다. 두 개의 RDD는 동일한 수의 요소와 동일한 수의 파티션으르 가져야 합니다.

```scala
val numRange = sc.parallelize(0 to 9, 2)
words.zip(numRange).collect()
// Array((Spark,0), (The,1), (Definitive,2), (Guide,3), (:,4), (Big,5), (Data,6), (Processing,7), (Made,8), (Simple,9))
```

## 파티션 제어하기

구조적 API와 RDD의 가장 큰 차이는 파티션 함수를 파라미터로 사용할 수 있다는 사실입니다.

### 1. coalesce

파티션을 재분배할 때 발생하는 데이터 셔플을 방지하기 위해 동일한 워커에 존재하는 파티션을 합치는 메서드입니다.

```scala
words.coalesce(1).getNumPartitions //1
```

예제의 words RDD는 현재 두 개의 파티션으로 구성되어 있습니다. coalesce 메서드를 사용해 데이터 셔플 없이 하나의 파티션으로 합칠 수 있습니다.

### 2. repartition

파티션 수를 늘리거나 줄일 수 있지만, 처리 시 노드 간의 셔플이 발생할 수 있습니다. 파티션 수를 늘리게 되면 맵 타입이나 필터 타입의 연산을 수행할 때 병렬 처리 수준을 높일 수 있습니다.

```scala
words.repartition(10) // 10개의 파티션이 생성됩니다.
```

### 3. repartitionAndSortWithinPartitions

파티션을 재분배할 수 있고, 재분배된 결과 파티션의 정렬 방식을 지정할 수 있습니다.

파티셔닝과 키 비교 모두 사용자가 지정할 수 있습니다.

### 4. 사용자 정의 파티셔닝

사용자 정의 파티셔닝은 RDD를 사용하는 가장 큰 이유입니다. 논리적인 대응책이 없기 때문에 구조적 API에서는 사용자 정의 파티셔닝을 파라미터로 사용할 수 없습니다. 사용자 정의 파티셔너는 저수준 API의 세부적인 구현 방식입니다.

사용자 정의 파티셔닝의 대표적인 예제는 페이지랭크입니다. 페이지랭크는 사용자 정의 파티셔닝을 이용해 클러스터의 데이터 배치 구조를 제어하고 셔플을 회피합니다.

사용자 정의 파티셔닝의 목표는 클러스터 전체에 걸쳐 데이터를 균등하게 분배하는 겁니다.

사용자 정의 파티셔닝을 사용하려면 구조적 API로 RDD를 얻고 사용자 정의 파티셔너를 적용한 다음 다시 데이터프레임이나 데이터셋으로 변환해야 합니다. 이 방법은 필요할 때만 사용자 정의 파티셔닝을 사용할 수 있기 때문에 구조적 API의 장점 또한 활용할 수 있습니다.

사용자 정의 파티셔닝을 사용하려면 Partitioner를 확장한 클래스를 구현해야 합니다. 문제에 대한 업무 지식을 충분히 가지고 있는 경우에만 사용해야 합니다. 단일 값이나 다수 값을 파티셔닝해야 한다면 데이터프레임을 사용하는 것이 좋습니다.

```scala
val df = spark.read.option("header", "true").option("inferSchema", "true").csv("/FileStore/tables/all/")
val rdd = df.coalesce(10).rdd
```

HashPartitioner(파티션 수)와 RangePartitioner는 RDD에서 사용할 수 있는 내장형 파티셔너입니다.

각각 이산형과 연속형 값을 다룰 때 사용합니다. 두 파티셔너는 구조적 API와 RDD 모두 사용할 수 있습니다.

```scala
import org.apache.spark.HashPartitioner

rdd.map(r => r(6)).take(5).foreach(println)
val keyedRDD = rdd.keyBy(row => row(6).asInstanceOf[Int].toDouble)

keyedRDD.partitionBy(new HashPartitioner(10)).take(10)
```

HashPartitioner와 RangePartitioner는 유용하지만 매우 기초적인 기능을 제공하기 때문에 매우 큰 데이터나 심각하게 치우친 키를 다뤄야 할땐 고급 파티셔닝 기능을 사용해야 합니다.

키가 특정 형태를 띠는 경우 키를 분할 해야 합니다.

```scala
import org.apache.spark.Partitioner

class DomainPartitioner extends Partitioner {
  def numPartitions = 3
  def getPartition(key : Any):Int = {
    val customerId = key.asInstanceOf[Double].toInt
    if (customerId == 17850.0 || customerId == 12583.0) {
      return 0
    }else {
      return new java.util.Random().nextInt(2) + 1
    }
  }
}

keyedRDD.partitionBy(new DomainPartitioner).map(_._1).glom().map(_.toSet.toSeq.length).take(5)

// Array(2, 4299, 4292)
```

위 코드를 실행하면 각 파티션 수를 확인할 수 있습니다.

## 사용자 정의 직렬화

**Kryo 직렬화** 관련 내용입니다. 병렬화 대상인 모든 객체나 함수는 직렬화 할 수 있어야 합니다.

```scala
class SomeClass extends Serializable {
  var someValue = 0
  def setSomeValue(i:Int) = {
    someValue = i
    this
  }
}

sc.parallelize(1 to 10).map(num => new SomeClass().setSomeValue(num))
```

스파크는 Kryo 라이브러리를 사용해 더 빠르게 객체를 직렬화 할 수 있습니다. Kryo는 자바 직렬화보다 약 10배 이상 성능이 좋으며 더 간결합니다. 하지만 모든 직렬화 유형을 지원하지는 않습니다. 그리고 최상의 성능을 얻으려면 프로그램에서 사용할 클래스를 사전에 등록해야 합니다.

SparkConf를 사용해 잡을 초기화하는 시점에서 spark.serializer 속성값을 org.apache.spark.serializer.KryoSerializer로 설정해 Kryo를 사용할 수 있습니다.

spark.serializer 설정으로 워커 노드 간 데이터 셔플링과 RDD를 직렬화해 디스크에 저장하는 용도로 사용할 시리얼라이저를 지정할 수 있습니다. 

Kryo가 기본값이 아닌 이유는 사용자가 직접 클래스를 등록해야 해서입니다. Kryo는 네트워크에서 민감한 애플리케이션에서 사용할 것을 권장합니다. 

Kryo에 사용자 정의 클래스를 등록하려면 registerKryoClasses 메서드를 사용합니다.

```scala
val conf = new SparkConf().setMaster(...).setAppName(...)
conf.registerKryoClasses(Array(classOf[MyClass1], classO[Myclass2]))
val sc = new SparkContext(conf)
```

