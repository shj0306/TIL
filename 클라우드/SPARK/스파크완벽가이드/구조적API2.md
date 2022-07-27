# 구조적 API

## 데이터 프레임 기본 연산

### 스키마(Schema)

- 스키마는 DataFrame의 컬럼명과 데이터 타입을 정의합니다. 데이터 소스에서 스키마를 어더나 직접 정의할 수 있습니다.

- 스키마는 여러 개의 structField 타입 필드로 구성된 StructType 객체입니다.

- 스파크는 런타임에서 데이터 타입이 스키마의 데이터 타입과 일치하지 않으면 에러를 발생시킵니다.

  그렇기 때문에 스키마를 직접 만들고 적용할 수 있어야 합니다.

  ```scala
  import org.apache.spark.sql.types.{StructField, StructType, StringType, LongType}
  import org.apache.spark.sql.types.Metadata
  
  val myManualSchema = StructType(Array(
    StructField("DEST_COUNTRY_NAME", StringType, true),
    StructField("ORIGIN_COUNTRY_NAME", StringType, true),
    StructField("count", LongType, false, Metadata.fromJson("{\"hello\":\"world\"}"))
  ))
  
  val df = spark.read.format("json").schema(myManualSchema).load("/FileStore/tables/2015_summary.json")
  ```

### 컬럼(Column)

  - col 함수나 column 함수를 통해서 컬럼을 생성하거나 참조할 수 있습니다.

    ```scala
    import org.apache.spark.sql.functions.{col, column}
    
    col("someColumn")
    column("someColumn")
    
    //스칼라는 아래와 같은 방법도 가능합니다.
    $"myColumn"
    'myColumn
    ```

  - col 함수는 조인 할 때 유용합니다. 데이터프레임의 어떤 컬럼을 다른 데이터프레임의 조인 대상 컬럼에서 참조하기 위해 col 함수를 사용할 수 있습니다.

### 레코드(record)와 로우(row)

  - 스파크는 레코드를 Row 객체로 표현합니다.

  - 로우 생성하기

    ```scala
    import org.apache.spark.sql.Row
    
    val myRow = Row("Hello", null, 1, false)
    ```

  - 스칼라나 자바에서는 헬퍼 메서드를 사용하거나 명시적으로 데이터 타입을 지정해야 하지만, 파이썬이나 R에서는 올바른 데이터 타입으로 자동 변환됩니다.

### DataFrame의 트랜스포메이션

- 데이터프레임 생성하기

  ```scala
  // Row 객체를 가진 Seq 타입을 직접 변환해 데이터프레임을 생성할 수 있다
  
  import org.apache.spark.sql.Row
  import org.apache.spark.sql.types.{StructField, StructType, StringType, LongType}
  
  val myManualSchema = new StructType(Array(
    new StructField("some", StringType, true),
    new StructField("col", StringType, true),
    new StructField("names", LongType, false)
  ))
  
  val myRows = Seq(Row("hello", null, 1L))
  val myRDD = spark.sparkContext.parallelize(myRows)
  val myDf = spark.createDataFrame(myRDD, myManualSchema)
  ```

- select, selectExpr

  - 데이터 테이블에 sql을 실행하는 것처럼 데이터프레임에서도 sql을 사용할 수 있습니다.

    ```scala
    df.select("columnName").show(2)
    
    //sql
    select columnName from dfTable limit 2;
    
    //두 코드의 실행결과가 같다.
    ```

  - 같은 형태의 쿼리로 여러 컬럼을 선택할 수 있습니다.

    ```scala
    df.select("columnName1", "columnName2").show(2)
    
    //sql
    select columnName1, columnName2 from dfTable limit 2;
    ```

  - Column 객체와 문자열을 함께 섞어 쓰게 되면 컴파일 오류가 발생합니다.

    ```scala
    // 다음 코드는 오류 발생
    df.select(col("columnName"), "columnName")
    ```

  - expr함수는 단순 컬럼 참조나 문자열을 이용해 컬럼을 참조할 수 있습니다.

    ```scala
    df.select(expr("columnName as cn")).show(2)
    
    //sql
    select columnName as cn from dfTable limit 2;
    ```
    
  - select 표현식에는 데이터프레임의 컬럼에 대한 집계함수를 지정할 수 있습니다.
  
    ```scala
    df.selectExpr("avg(col1)", "count(distinct(col2))").show(2)
    
    // sql
    select avg(col1), count(distinct(col2)) from dfTable limit 2
    ```
  
  - 명시적인 값을 전달해야 할 때는 lit을 사용합니다.
  
    ```scala
    import org.apache.spark.sql.functions.lit
    
    df.select(expr("*"), lit(1).as("One")).show(2)
    
    //sql
    select *, 1 as One from dfTable limit 2;
    ```
  
- 컬럼 추가하기

  - 데이터 프레임에 신규 컬럼을 추가할 때는 withColumn 메서드를 사용합니다.
  - withColumn 메서드는 2 개의 인수를 사용합니다. 하나는 컬럼명이고, 다른 하나는 값을 생성할 표현식입니다.

- 컬럼명 변경하기

  - withColumnRenamed 메서드로 컬럼명을 변경할 수 있습니다. 첫번째 인수로 전달된 컬럼명, 두번째 인수로 변경할 새로운 컬럼명이 들어갑니다.

- 예약 문자와 키워드

  - 공백이나 하이픈(-)같은 예약 문자는 컬럼명에 사용할 수 없습니다. 사용하려면 백틱(`) 문자를 이용해 이스케이핑해야 합니다.

  - withColumn 메서드의 첫 번째 인수로 문자열을 지정했기 때문에 이스케이프 문자가 필요없습니다.

    ```scala
    import org.apache.spark.sql.functions.expr
    
    val dfWithLongColName = df.withColumn(
    	"This Long Column-Name",
        expr("origin_country_name")
    )
    ```

  - 표현식 대신에 문자열을 사용해 명시적으로 컬럼을 참조하면 리터럴로 해석되기 때문에 예약 문자가 포함된 컬럼을 참조할 수 있습니다.

    ```scala
    dfWithLongColName.selectExpr(
      "`This long col-name`",
      "`This long col-name` as `new col`"
    ).show(2)
    ```

  - 예약 문자나 키워드를 사용한 표현식에만 이스케이프 처리가 필요합니다.

    ```scala
    dfWithLongColName.select(col("This long col-name")).columns
    ```

    ```python
    dfWithLongColName.select(expr("`This long col-ame`")).columns
    ```

- 컬럼 제거하기

  - select로도 컬럼을 제거할 수 있지만, drop 메소드를 사용해서 컬럼을 제거합니다.

    ```scala
    //1개의 컬럼을 제거
    df.drop("columnName").columns
    //2개 이상 컬럼을 제거
    df.drop("columnName1", "columnName2")
    ```

- 컬럼의 데이터 타입 변경하기

  - cast 메소드를 이용해서 데이터 타입을 변환할 수 있습니다.

    ```scala
    df.withColumn("count2", col("count").cast("string"))
    ```

- 로우 필터링

  - 데이터프레임의 where 메소드나 filter 메소드로 필터링할 수 있습니다. 

    ```scala
    df.filter(col("columnName") < 2).show(2)
    df.where("columnName < 2").show(2)
    
    //sql
    select * from dfTable where columnName < 2 limit 2;
    ```

  - 같은 표현식에 여러 필터를 적용해야 할 때도 있지만 스파크는 필터 순서 상관없이 자동으로 모든 필터링 작업을 수행하기 때문에 항상 유용하진 않습니다.

- 무작위 샘플 만들기

  - 데이터프레임에서 무작위 샘플 데이터를 얻으려면 데이터프레임의 sample 메소드를 사용합니다.

    ```scala
    val seed = 5
    val withReplacement = false
    val frac = 0.5
    df.sample(withReplacement, frac, seed).count() //책은 126이라고 하는데 저는 138이 나오네요
    ```

- 임의 분할하기

  - 머신러닝 알고리즘에서 사용할 학습셋, 검증셋, 테스트셋을 만들 때 주로 사용합니다.

    ```scala
    val dataFrames = df.randomSplit(Array(0.25, 0.75), seed=2022)
    dataFrames(0).count() > dataFrames(1).count() // False
    ```

- 로우 합치기와 추가하기

  - 데이터프레임은 불변성을 가지기 때문에 레코드를 추가하는 작업이 불가능합니다. 데이터프레임에 레코드를 추가하려면 원본 데이터프레임과 새로운 데이터프레임을 통합해야 합니다. 통합하려는 두 개의 데이터프레임은 반드시 동일한 스키마와 컬럼 수를 가져야 합니다.

    ```scala
    import org.apache.spark.sql.Row
    
    val schema = df.schema
    
    val newRows = Seq(
    	Row("New Country", "Other Country", 5L),
        Row("New Country2", "Other Country", 1L)
    )
    
    val parallelizedRows = spark.sparkContext.parallelize(newRows)
    val newDF = spark.createDataFrame(parallelizedRows, schema)
    
    df.union(newDF).where("count = num").where($"columnName" =!= "val")
    ```

- 로우 정렬하기

  - sort와 orderBy 메소드를 사용해서 데이터프레임을 정렬할 수 있습니다.

  - 두 메소드 모두 컬럼 표현식과 문자열을 사용할 수 있고, 다수의 컬럼을 지정할 수 있습니다.

  - 기본 동작 방식은 오름차순 정렬입니다.

    ```scala
    df.sort("columnName") //해당 컬럼을 기준으로 오름차순 정렬
    df.orderBy("columnName1", "columnName2") //2개의 컬럼을 기준으로 오름차순 정렬
    df.orderBy(col("columnName1"), col("columnName2"))
    ```

  - 정렬 기준을 지정하려면 asc나 desc 함수를 사용합니다.

    ```scala
    import org.apache.spark.sql.functions.{desc, asc}
    
    df.orderBy(expr("columnName1 desc")) // 해당 컬럼 기준으로 내림차순 정렬
    df.orderBy(desc("columnName1"), asc("columnName2")) // columnName1을 기준으로 내림차순 정렬, columnName2을 기준으로 오름차순 정렬
    df.orderBy(col("columnName1").desc(), col("columnName2").asc())
    ```

  - asc_nulls_first, desc_nulls_first, asc_nulls_last, desc_nulls_last 메소드를 사용해 정렬된 데이터프레임에서 null 값이 표시되는 기준을 지정할 수 있습니다.

  - 트랜스포메이션을 처리하기 전에 성능을 최적화하기 위해 파티션별 정렬을 수행하기도 합니다. 파티션별 정렬은 sortWithinPartitions 메소드를 사용합니다.

- repartition과 coalesce

  - reparition 메소드를 호출하면 무조건 전체 데이터를 셔플합니다. 향후에 사용할 파티션 수가 현재 파티션 수보다 많거나 컬럼을 기준으로 파티션을 만드는 경우에만 사용해야 합니다.

    ```scala
    df.rdd.getNumPartitions // 1
    df.repartition(5)
    
    // 자주 필터링되는 컬럼을 기준으로 파티션을 재분배 할 수 있습니다.
    df.repartition(col("columnName"))
    
    // 선택적으로 파티션 수를 지정할 수 있습니다
    df.repartition(5, col("columnName"))
    ```

  - coalesce 메소드는 전체 데이터를 셔플하지 않고, 파티션을 병합하는 경우에 사용합니다.

    ```scala
    // 목적지를 기준으로 셔플을 수행해 5개의 파티션으로 나누고, 전체 데이터를 셔플 없이 병합하는 코드
    
    df.repartition(5, col("목적지")).coalesce(2)
    ```

- 드라이버로 로우 데이터 수집하기

  - 스파크는 드라이버에서 클러스터 상태 정보를 유지합니다. 로컬 환경에서 데이터를 다루려면 드라이버로 데이터를 수집해야 합니다.

    ```scala
    val collectDF = df.limit(10)
    collectDF.take(5) // Array(row1,row2,...)형태로 출력된다.
    collectDF.show() //오른쪽 정렬된 채로 표시된다
    collectDF.show(5, false) //왼쪽 정렬된 채로 표시된다.
    collectDF.collect() // Array(row1, row2,....)형태로 출력된다.
    ```

  - 드라이버로 모든 데이터 컬렉션을 수집하는 작업은 비용이 매우 큰 작업입니다. 그렇기 때문에 collect 메소드를 수행하면 드라이버가 비정상적으로 종료될 수 있습니다. 

