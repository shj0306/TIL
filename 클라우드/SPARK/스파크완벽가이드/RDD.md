# RDD

비즈니스나 기술적 문제를 고수준 API를 사용해 모두 처리할 수 있는 것은 아닙니다. 이런 경우의 스파크의 저수준 API를 사용해야 할 수도 있습니다.

스파크의 저수준 API는 RDD, SparkContext 그리고 accumulator와 브로드캐스트 변수같은 분산형 공유 변수 등을 의미합니다.

## 저수준 API란

스파크에는 두 종류의 저수준 API가 있습니다. 하나는 분산 데이터 처리를 위한 RDD이며, 다른 하나는 브로드캐스트 변수와 accumulator처럼 분산형 공유 변수를 배포하고 다루기 위한 API입니다.

### 저수준 API는 언제 사용할까

- 고수준 API에서 제공하지 않는 기능이 필요한 경우, 예를 들어 클러스터의 물리적 데이터의 배치를 아주 세밀하게 제어해야 하는 상황
- RDD를 사용해 개발된 기존 코드를 유지해야 하는 경우
- 사용자가 정의한 공유 변수를 다뤄야 하는 경우

위와 같은 상황에서만 저수준 API 기능을 사용해야 합니다. 

DataFrame 트랜스포메이션을 호출하면 실제로 다수의 RDD 트랜스포메이션으로 변환됩니다.

스파크는 구조적 API 위주로 사용하는 것이 좋습니다. 그러나 필요한 요건을 맞추기 위해 저수준 API를 사용해야 하는 경우가 발생할 수 있습니다.

저수준 API는 세밀한 제어 방법을 제공하여 개발자가 치명적인 실수를 하지 않도록 도와주기도 합니다.

### 저수준 API는 어떻게 사용할까

- SparkContext는 저수준 API 기능을 사용하기 위한 진입 지점입니다. 스파크 클러스터에서 연산을 수행하는 데 필요한 도구인 SparkSession을 이용해 SparkContext에 접근할 수 있습니다.

- SparkContext에 접근

  ```scala
  spark.sparkContext
  ```



## RDD 개요

- 사용자가 실행한 모든 데이터프레임이나 데이터셋 코드는 RDD로 컴파일됩니다. 

- RDD는 불변성을 가지며 병렬로 처리할 수 있는 파티셔닝된 레코드의 모음입니다. 
- RDD의 레코드는 자바나 파이썬의 객체이므로 완벽하게 제어할 수 있습니다. 이러한 객체에는 사용자가 원하는 포맷을 사용해 원하는 모든 데이터를 저장할 수 있습니다.
- 모든 값을 다루거나 값 사이의 상호작용 과정을 반드시 수동으로 정의해야 합니다. 또한 구조적 API와는 다르게 레코드의 내부 구조를 스파크에서 파악할 수 없으므로 최적화를 하려면 더 많은 수작업이 필요합니다.
- RDD API는 데이터셋과 유사하지만 RDD는 구조화된 데이터 엔진을 사용해 데이터를 저장하거나 다루지 않습니다. 하지만 RDD와 데이터셋 사이의 전환은 매우 쉽기 때문에 두 API를 모두 사용해 각 API의 장점을 동시에 활용할 수 있습니다.

### RDD 유형

- 사용자는 두 가지 타입의 RDD를 만들 수 있는 데, 하나는 제네릭 RDD 타입이고, 다른 하나는 키 기반의 집계가 가능한 키-값 RDD입니다. 목적에 맞게 두 RDD 중 하나를 선택할 수 있습니다. 
- RDD 다섯 가지 주요 속성
  1. 파티션의 목록
  2. 각 조각을 연산하는 함수
  3. 다른 RDD와의 의존성 목록
  4. 부가적으로 키-값 RDD를 위한 파티셔너
  5. 부가적으로 각 조각을 연산하기 위한 기본 위치 목록
- 각 RDD 유형은 위에 나열한 각 속성에 대한 구현체를 가지고 있습니다. 사용자는 각 속성을 구현하여 새로운 데이터소스를 정의할 수 있습니다.
- RDD 역시 분산 환경에서 데이터를 다루는 데 필요한 지연 처리 방식의 **트랜스포메이션**과 즉시 실행 방식의 **액션**을 제공합니다. 데이터프레임과 데이터셋의 동작과 동일하지만 RDD에는 로우라는 개념이 없습니다. 개별 레코드는 자바, 스칼라, 파이썬 객체일 뿐이며 구조적 API에서 제공하는 여러 함수를 사용하지 못하기 때문에 수동으로 처리해야 합니다.
- 파이썬을 사용해 RDD를 다룰 때는 상당한 성능 저하가 발생할 수 있습니다. 
  - 파이썬으로 RDD를 실행하는 것은 파이썬으로 만들어진 사용자 정의 함수를 각 로우마다 적용하는 것과 동일합니다.

### RDD는 언제 사용할까

- RDD는 정말 필요한 경우가 아니면 수동으로 생성하면 안됩니다.
- 물리적으로 분산된 데이터에 세부적인 제어가 필요할 때 RDD를 사용하는 것이 가장 적합합니다.

### 데이터셋과 RDD의 케이스 클래스

1. 데이터셋과 케이스 클래스를 사용해서 만들어진 RDD의 차이점은 무엇일까?

- 데이터셋은 구조적 API가 제공하는 풍부한 기능과 최적화 기법을 제공한다는 것이 가장 큰 차이점입니다. 

2. 데이터셋을 사용하면 JVM 데이터 타입과 스파크 데이터 타입 중 어떤 것을 쓸지 고민하지 않아도 됩니다.

## RDD 생성하기

### 1. DataFrame, Dataset으로 RDD 생성하기

- RDD를 얻을 수 있는 가장 쉬운 방법은 기존에 사용하던 데이터프레임과 데이터셋을 이용하는 겁니다. rdd 메서드만 호출하면 쉽게 RDD로 변환할 수 있습니다.

  ```scala
  spark.range(100).rdd
  ```

- RDD를 사용해 데이터프레임이나 데이터셋을 생성할 때도 동일한 방법을 사용합니다.

  ```scala
  spark.range(100).rdd.toDF()
  ```

  rdd 메서드는 row 타입을 가진 RDD를 생성합니다. row 타입은 스파크가 구조적 API에서 데이터를 표현하는 데 사용하는 내부 카탈리스트 포맷입니다. 이 기능을 사용하면 상황에 따라 구조적 API와 저수준 API 사이를 오고가게 만들 수 있습니다.

### 2. 로컬 컬렉션으로 RDD 생성하기

- 컬렉션 객체를 RDD로 만들려면 sparkContext의 parallelize 메서드를 호출해야 합니다.

- 이 메서드는 단일 노드에 있는 컬렉션을 병렬 컬렉션으로 전환합니다. 또 파티션 수를 명시적으로 지정할 수 있습니다.

- 예제) 두 개의 파티션을 가진 병렬 컬렉션 객체를 만든다.

  ```scala
  val myCollection = "Spark the definitive Guide : Big Data Processing Made Siimple".split(" ")
  val words = spark.sparkContext.parallelize(myCollection, 2)
  ```

### 3. 데이터소스로 RDD 생성하기

- 데이터소스나 텍스트 파일로 직접 생성할 수 있지만, DataSource API를 사용하는 것이 더 바람직합니다. 

- RDD는 주로 RDD 간의 의존성 구조와 파티션 목록을 정의합니다. 

- sparkContext를 사용해 데이터를 RDD로 읽을 수 있습니다.

- 예제) 줄 단위로 텍스트 파일을 읽는 예제

  ```scala
  spark.sparkContext.textFile("/FileStore/tables/TextFiles")
  ```

- 여러 텍스트 파일의 각 줄을 레코드로 가진 RDD를 생성합니다. 

   ```scala
   spark.sparkContext.wholeTextFiles("/FileStore/tables/TextFiles")
   ```
   
- 생성된 RDD에서 파일명은 첫 번째 객체인 RDD의 키가 되고, 텍스트 파일의 값은 두번째 문자열 객체인 RDD의 값이 됩니다.

## RDD 다루기

- RDD는 스파크 데이터 타입 대신 자바나 스칼라 객체를 다룬다는 점이 데이터프레임과 가장 큰 차이점입니다.
- 연산을 단순화하는 헬퍼 메서드나 함수도 데이터프레임에 비해 많이 부족하기 때문에 대부분의 함수를 사용자가 직접 정의해야 합니다.

## 트랜스포메이션

### 1. distinct

- RDD의 distinct 메서드를 호출하면 RDD에서 중복된 데이터를 제거합니다.

  ```scala
  words.distinct().count()
  ```

### 2. filter

- 필터링은 SQL의 where 조건절을 생성하는 것과 비슷합니다. RDD의 레코드를 모두 확인하고 조건 함수를 만족하는 레코드만 반환합니다.

- 모든 로우는 어떤 경우라도 입력값을 가지고 있어야 합니다.

- 예제) 문자 'S'로 시작하는 단어만 남도록 RDD를 필터링

  ```scala
  def startsWithS(individual : String) : Boolean = {
    individual.startsWith("S")
  }
  ```

  ```python
  def startsWithS(individual):
      return individual.startswith("S")
  ```

### 3. map

- 주어진 입력을 원하는 값으로 반환하는 함수를 명시하고 레코드별로 적용합니다.

- 예제) 현재 단어를 '단어', '단어의 시작 문자', '첫 문자가 S인지 아닌지' 순서로 매핑합니다.

  ```scala
  val words2 = words.map(word => (word, word(0), word.startsWith("S")))
  
  //words2: org.apache.spark.rdd.RDD[(String, Char, Boolean)] 
  ```

- 새로 만든 함수의 세번째 반환값인 불리언 값으로 필터링할 수 있습니다.

  ```scala
  words2.filter(record => record._3).take(5)
  
  // Array((Spark,S,true), (Simple,S,true))
  ```

### flatMap

- map 함수의 확장 버전입니다. 때론 단일 로우를 여러 개의 로우로 변환해야 하는 경우가 있습니다. 예를 들어 flatMap 메서드를 사용해 단어를 문자 집합으로 변환할 수 있습니다. 

  ```scala
  words.flatMap(word => word.toSeq).take(5)
  
  //Array(S, p, a, r, k)
  ```

### 4. sortBy

- RDD를 정렬하려면 sortBy 메서드를 사용합니다. 

- 다른 RDD 작업과 마찬가지로 함수를 지정해 RDD의 데이터 객체에서 값을 추출한 다음 값을 기준으로 정렬합니다.

  ```scala
  // 단어의 길이를 기준으로 내림차순 정렬
  words.sortBy(word => word.length() * -1).take(2)
  ```

### 5. randomSplit

- RDD를 임의로 분할해 RDD 배열을 만들 때 사용하며, 가중치와 난수 시드로 구성된 배열 파라미터로 사용됩니다.

  ```scala
  val fiftyFiftySplit = words.randomSplit(Array[Double](0.5,0.5))
  ```

## 액션

- 액션은 데이터를 드라이버로 모으거나 외부 데이터소스로 내보낼 수 있습니다.

### 1. reduce

- RDD의 모든 값을 하나의 값으로 만들려면 reduce 메서드를 사용합니다. 예를 들어 정수형 집합이 주어졌다면 두 개의 입력값을 하나로 줄이는 함수를 사용해 합계를 구할 수 있습니다.

  ```scala
  spark.sparkContext.parallelize(1 to 20).reduce(_ + _)
  ```

  ```python
  spark.sparkContext.parallelize(range(1,21)).reduce(lambda x, y : x + y)
  ```

- 예제) 단어 집합에서 가장 긴 단어를 찾는 예제

  ```scala
  def wordLengthReducer(leftWord:String, rightWord:String) : String = {
    if (leftWord.length > rightWord.length) return leftWord
    else return rightWord
  }
  
  words.reduce(wordLengthReducer)
  ```

  wordLengthReducer 함수는 두 개의 입력값을 하나의 결과로 만들기 때문에 reduce 메서드를 설명하는 데 적합합니다.

### 2. count

- RDD의 전체 로우수를 알 수 있습니다.

###     countApprox

- count 함수의 근사치를 제한 시간 내에 계산합니다. 제한 시간을 넘기면 불완전한 결과를 반환할 수 있습니다.

- 신뢰도는 실제로 연산한 결과와의 오차율을 의미합니다.

  ```scala
  val confidence = 0.95
  val timeoutMS = 400
  words.countApprox(timeoutMS, confidence)
  
  org.apache.spark.partial.PartialResult[org.apache.spark.partial.BoundedDouble] = (final: [10.000, 10.000])
  ```

### 3. firtst

- 데이터셋의 첫 번째 값을 반환합니다.

### 4. max, min

- max와 min은 각 최댓값, 최솟값을 반환합니다.

### 5. take

- take와 파생 메서드는 RDD에서 가져올 값의 개수를 파라미터로 사용합니다.

- 이 메서드는 먼저 하나의 파티션을 스캔합니다. 그 다음 해당 파티션의 결과 수를 이용해 파라미터로 지정된 값을 만족하는데 필요한 추가 파티션 수를 예측합니다.

- RDD에서 고정 크기의 임의 표본 데이터를 얻기 위해 takeSample 함수를 사용할 수 있습니다. takeSample 함수는 withReplacement, 임의 표본 수, 난수 시드값을 파라미터로 사용합니다.

- top 함수는 암시적 순서에 따라 최상윗값을 선택합니다.

  ```scala
  words.take(5)
  //Array(Spark, the, definitive, Guide, :)
  words.takeOrdered(5)
  // Array(:, Big, Data, Guide, Made)
  words.top(5)
  // Array(the, definitive, Spark, Simple, Processing)
  
  val withReplacement = true
  val numberToTake = 6
  val randomSeed = 100L
  words.takeSample(withReplacement, numberToTake, randomSeed)
  // Array[String] = Array(Guide, Spark, :, Simple, Simple, Spark)
  ```

## 파일 저장하기

- RDD를 사용하면 일반적인 의미의 데이터소스에는 저장할 수 없습니다.
- 각 파티션의 내용을 저장하려면 전체 파티션을 순회하면서 외부 데이터소스에 저장해야 합니다.

### 1. saveAsTextFile

```scala
words.saveAsTextFile("file://tmp/bookTitle")
```

압축 코덱을 설정하려면 하둡에서 사용 가능한 코덱을 임포트해야 합니다. org.apache.hadoop.io.compress 라이브러리에서 지원하는 코덱을 찾을 수 있습니다.

```scala
import org.apache.hadoop.io.compress.BZip2Codec

words.saveAsTextFile("file://tmp/bookTitle", classOf[Bzip2Codec])
```

### 2. 시퀀스 파일

- 스파크는 하둡 시스템을 기반으로 성장했기 때문에 하둡 기능과 잘 호환됩니다.
- 스파크는 saveAsObjectFile 메서드나 명시적인 키-값 쌍 데이터 저장 방식을 이용해 시퀀스 파일을 작성할 수 있습니다.

### 3. 하둡 파일

- 하둡 파일 포맷을 사용하면 클래스, 출력 포맷, 하둡 설정 그리고 압축 방식을 지정할 수 있습니다.

## 캐싱

RDD 캐싱에도 데이터프레임이나 데이터셋의 캐싱과 동일한 원칙이 적용됩니다.





  