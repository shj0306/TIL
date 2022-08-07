# 스파크 SQL

## SQL이란 ?

- 데이터에 대한 관계형 연산을 표현하기 위한 도메인 특화 언어입니다. 모든 관계형 데이터베이스에서 사용되며, 많은 NoSQL에서도 쉽게 사용할 수 있는 변형된 자체 SQL을 제공합니다.

## 빅데이터와 SQL : 아파치 하이브

- 스파크가 등장하기 전에는 하이브가 빅데이터 SQL 접근 계층에서 사실상의 표준이었습니다. 
- 분석가들이 하이브로 SQL 쿼리를 실행할 수 있게 되면서 하둡을 다양한 산업군으로 진출시키는 데 도움을 주었습니다.

## 빅데이터와 SQL : 아파치 스파크

- 스파크 SQL은 데이터프레임과의 뛰어난 호환성 덕분에 다양한 기업에서 강력한 기능으로 자리매김할 겁니다.
- SQL 분석가들은 thrift Server나 SQL 인터페이스에 접속해 스파크의 연산 능력을 활용 할 수 있고, 데이터 엔지니어와 사이언티스트는 전체 데이터 처리 파이프라인에 스파크 SQL을 사용할 수 있습니다.
- 이러한 통합형 API는 SQL로 데이터를 조회하고, 데이터프레임으로 변환하고 스파크의 MLlib이 제공하는 대규모 머신러닝 알고리즘 중 하나를 사용해 수행한 결과를 다른 데이터소스에 저장하는 전체 과정을 가능하게 합니다.
- 스파크 SQL은 OLTP 데이터베이스가 아닌 OLAP 데이터베이스로 동작하기 때문에 매우 낮은 지연 시간이 필요한 쿼리를 수행할 수 없습니다.

## 스파크와 하이브의 관계

- 스파크 SQL은 하이브 메타스토어를 사용하므로 하이브와 잘 연동할 수 있습니다.

- 스파크 SQL은 하이브 메타스토어에 접속한 뒤 조회할 파일 수를 최소화하기 위해 메타데이터를 참조합니다.

  **하이브 메타스토어**에 접속하기 위해 필요한 속성들

  1. 하이브 메타 스토어에 적합한 버전을 spark.sql.hive.metastore.version에 설정해야 합니다.
  2. HiveMetastoreClient가 초기화되는 방식을 변경하려면 spark.sql.hive.metastore.jars를 설정해야 합니다.
  3. 하이브 메타스토어가 저장된 다른 데이터베이스에 접속하려면 적합한 클래스 접두사를 정의해야 합니다.
  4. 스파크와 하이브에서 공유할 수 있도록 클래스 접두사를 spark.sql.hive.metastore.sharedPrefixes 속성에 설정합니다.

## 스파크 SQL 쿼리 실행 방법

### 스파크 SQL CLI

- 로컬 환경의 cmd에서 기본 스파크 sql 쿼리를 실행할 수 있는 편리한 도구입니다.  스파크 SQL CLI는 thrift JDBC 서버와 통신할 수 없습니다. 스파크 SQL CLI를 사용하려면 스파크 디렉토리에서 다음 명령을 실행합니다.

  ```shell
  $./bin/spark-sql
  ```

  스파크가 설치된 경로의 conf 디렉토리에 hive-site.xml, core-site.xml, hdfs-site.xml 파일을 배치해 하이브를 사용할 수 있는 환경을 구성할 수 있습니다.

### 스파크의 프로그래밍 SQL 인터페이스

- 스파크에서 지원하는 언어 API로 비정형 SQL을 실행할 수 있습니다

- SparkSession 객체의 sql 메서드를 사용합니다.

  ```scala
  spark.sql("""
      select dest_country_name, sum(count)
      from some_sql_view group by dest_country_name
  """).where("dest_country_name like 'S%'")
      .where("`sum(count)` > 10")
      .count()
  
  // 12
  ```

## 스파크 SQL thrift JDBC/ODBC 서버

- 스파크는 JDBC 인터페이스를 제공합니다. 사용자나 원격 프로그램은 스파크 SQL을 실행하기 위해 이 인터페이스로 스파크 드라이버에 접속합니다.

  비즈니스 분석가가 태블로(Tableau) 같은 비즈니스 인텔리전스 소프트웨어를 이용해 스파크에 접속하는 형태가 가장 대표적인 활용 사례입니다.

- JDBC/ODBC 서버를 시작하려면 스파크 디렉토리에서 다음 명령을 실행합니다.

  ```shell
  ./sbin/start-thriftserver.sh
  ```

  이 스크립트는 bin/spark-submit 스크립트에서 사용할 수 있는 모든 명령행 옵션을 지원합니다. thrift 서버는 기본적으로 localhost:10000 주소를 사용합니다.

  환경 변수나 시스템 속성을 지정해 thrift 서버의 주소를 변경할 수 있습니다.

  1. 환경 변수 설정 방법

     ```shell
     export HIVE_SERVER2_THRIFT_PORT=<listening-port>
     export HIVE_SERVER2_THRIFT_BIND_HOST=<listening-host>
     ./sbin/start-thriftserver.sh \
     --master <master-url> \
     ```
  
  2. 시스템 속성 설정 방법
  
     ```shell
     ./sbin/start-thriftserver.sh \
     --hiveconf hive.server2.thrift.port=<listening-port> \
     --hiveconf hive.server2.thrift.bind.host=<listening-host> \
     --master <master-url>
     ...
     ```
  
  서버가 시작되면 다음 명령을 사용해 접속 테스트
  
  ```shell
  ./bin/beeline
  beeline> !connect jdbc:hive2//localhost:10000
  ```

## 카탈로그 서버

- 스파크 SQL에서 가장 높은 추상화 단계는 카탈로그입니다. 카탈로그는 테이블에 저장된 데이터에 대한 메타데이터뿐만 아니라 데이터베이스, 테이블, 함수 그리고 뷰에 대한 정보를 추상화합니다.
- 카탈로그는 org.apache.spark.sql.catalog.Catalog 패키지로 사용할 수 있습니다. 카탈로그는 테이블, 데이터베이스 그리고 함수를 조회하는 등 여러 가지 유용한 함수를 제공합니다.

## 테이블

- 스파크 SQL을 사용해 유용한 작업을 수행하려면 먼저 테이블을 정의해야 합니다.
- 데이터프레임은 프로그래밍 언어로 정의하지만 테이블은 데이터베이스에서 정의합니다.

### 스파크 관리형 테이블

- 테이블은 두 가지 중요한 정보를 저장합니다. 테이블의 데이터와 메타 데이터입니다. 스파크는 데이터뿐만 아니라 파일에 대한 메타데이터를 관리할 수 있습니다. 디스크에 저장된 파일을 이용해 테이블을 정의하면 외부 테이블을 정의하는 겁니다. 
- 데이터프레임의 saveAsTable 메서드는 스파크가 관련된 모든 정보를 추적할 수 있는 관리형 테이블을 만들 수 있습니다. saveAsTable 메서드는 테이블을 읽고 데이터를 스파크 포맷으로 변환한 후 새로운 경로에 저장합니다.
- 데이터 저장 경로를 변경하려면 SparkSession을 생성할 때 spark.sql.warehouse.dir 속성에 원하는 디렉토리 경로를 설정합니다. 기본 저장 경로는 /user/hive/warehouse입니다.

### 테이블 생성하기

- 다양한 데이터소스를 활용해서 테이블을 생성할 수 있습니다.

- 스파크는 실행 즉시 테이블을 생성 할 수 있습니다.

  ```sql
  create table flights (
    dest_country_name string, origin_country_name string, count long
  ) using json options (path '/FileStore/tables/2015_summary.json')
  
  create table flights_from_select using parquet as select * from flights
  
  create table partitioned_flights using parquet partitioned by (dest_country_name)
  as select dest_country_name, origin_country_name, count from flights limit 5
  ```

  위에 나온 using 구문은 매우 중요합니다. 포맷을 지정하지 않으면 스파크는 기본적으로 하이브 SerDe 설정을 사용합니다. 하이브 SerDe는 스파크의 자체 직렬화보다 느리기 때문에 성능에 영향을 미칩니다. 하이브 사용자는 stored as 구문으로 하이브 테입르을 생성할 수 있습니다.

### 외부 테이블 생성하기

- 스파크 SQL은 하이브 SQL과 완벽하게 호환되기 때문에 대부분의 하이브 쿼리문을 스파크 SQL에 바로 사용할 수 있습니다. 

- 스파크는 외부 테이블의 메타 데이터를 관리하지만 데이터 파일은 관리하지 않습니다. CREATE EXTERNAL TABLE 구문을 사용해 외부 테이블을 생성할 수 있습니다.

  ```sql
  create external table hive_flights (
    dest_country_name string, origin_country_name string, count long
  ) row format delimited fields terminated by ',' location 'FileStore/tables/flight-data-hive/'
  ```

### 테이블에 데이터 삽입하기

```sql
insert into flights_from_select
select dest_country_name, origin_country_name, count from flights limit 20
```

### 테이블 메타 데이터 확인하기

```sql
describe table flights

-- output
col_name data_type
dest_country_name string
origin_country_name string
count bigint
```

```sql
show paritions partitioned_flights

-- output
partition
dest_country_name=__HIVE_DEFAULT_PARTITION__
```

### 테이블 메타데이터 갱신하기

- 테이블 메타데이터를 유지하는 것은 가장 최신의 데이터셋을 읽고 있다는 것을 보장할 수 있는 중요한 작업입니다.

- 테이블 메타데이터를 갱신할 수 있는 2가지 명령이 있습니다.

  ```sql
  refresh table partitioned_flights
  ```
  
  - 테이블과 관련된 모든 캐싱된 항목을 갱신합니다.
  
  - 테이블이 이미 캐싱되어 있다면 다음번 스캔이 동작하는 시점에 다시 캐싱합니다.
  
  ```sql
  msck repair table partitioned_flights
  ```
  
  - 카탈로그에서 관리하는 테이블의 파티션 정보를 새로 고치는 명령어입니다.
  - 새로운 파티션 정보를 수집하는 데 초점을 맞춥니다.

### 테이블 제거하기

- 테이블은 삭제(delete)할 수 없고 제거(drop)만 가능합니다. drop 키워드를 사용해 테이블을 제거 할 수 있습니다.
- 존재하지 않는 테이블을 제거하려고 하면 오류가 발생합니다. 테이블이 존재하는 경우만 제거하려면 DROP TABLE IF EXISTS 구문을 사용해야 합니다.

### 테이블 캐싱하기

- 데이터프레임에서처럼 테이블을 캐시하거나 캐시에서 제거할 수 있습니다.

  ```sql
  (UN)CACHE TABLE flights
  ```



## 뷰

### 뷰 생성하기

- 신규 경로에 모든 데이터를 다시 저장하는 대신 단순하게 쿼리 시점에 데이터 소스에 트랜스포메이션을 수행합니다. filter, select, Group By, Rollup

- 테이블처럼 데이터베이스에 등록하지 않고 현재 세션에만 사용할 수 있는 임시 뷰도 생성할 수 있다.

- 데이터베이스 상관없이 사용할 수 있는 전역적 임시 뷰도 만들 수 있습니다. 세션이 종료되면 사라집니다.

  ```sql
  create (global) (temp) view just_usa_view as
  select * from flights where dest_country_name = 'United States'
  ```

- 스파크 데이터프레임과 스파크 SQL로 생성된 쿼리 실행 계획을 비교할 수 있습니다.

  ```scala
  val just_usa_df = flights.where("dest_country_name = 'United States'")
  just_usa_df.selectExpr("*").explain
  ```

  ```sql
  explain select * from just_usa_view
  ```



### 뷰 제거하기

- 테이블을 제거하는 것과 동일한 방식으로 제거할 수 있습니다.
- 뷰와 테이블 제거의 핵심 차이점은 뷰는 어떤 데이터도 제거되지 않으며 뷰 정의만 제거됩니다.



## 데이터베이스

- 전체 데이터베이스 목록 확인

  ```sql
  show databases
  ```

- 데이터베이스 생성하기

  ```sql
  create database some_db
  ```

- 데이터베이스 설정하기

  ```sql
  use some_db
  ```

- 현재 사용 중인 데이터베이스 확인

  ```sql
  select current_database()
  ```

- 데이터 베이스 제거하기

  ```sql
  drop database if exists some_db
  ```

### SELECT 구문

#### case...when...then 구문

- SQL 쿼리 값을 조건에 맞게 변경해야 할 수도 있습니다. 이 때 사용하는 구문이고, 이 구문은 프로그래밍의 if 구문과 동일한 처리를 합니다.

  ```sql
  select
  case when dest_country_name = 'UNITED STATES' then 1
  	 when dest_country_name = 'Egypt' then 0
       else -1 end
  from partitioned_flights
  ```

### SQL 쿼리

### 1. 복합 데이터 타입

- 복합 데이터 타입은 표준 SQL과는 거리가 있고 표준 SQL에 존재하지 않는 강력한 기능입니다.

- 스파크 SQL에는 구조체, 리스트, 맵 세가지 핵심 복합 데이터 타입이 존재합니다.

  ### 구조체

  - 구조체는 맵에 더 가까우며 스파크에서 중첩 데이터를 생성하거나 쿼리하는 방법을 제공합니다. 구조체는 여러 컬럼이나 표현식을 괄호로 묶기만 하면 됩니다.

    ```sql
    create view if not exists nested_data as
    select (dest_country_name, origin_country_name) as country, count from flights
    ```

  - 구조체 데이터 조회

    ```sql
    select * from nested_data
    ```

  - 구조체 개별 컬럼 조회

    ```sql
    select country.dest_country_name, count from nested_data
    ```

  ### 리스트

  - 값의 리스트를 만드는 collect_list 함수나 중복 값이 없는 배열을 만드는 collect_set 함수를 사용할 수 있습니다. 두 함수 모두 집계 함수기 때문에 집계 연산 시에만 사용할 수 있습니다.

  - 파이썬 방식과 유사한 배열 쿼리 구문을 사용해 리스트의 특정 위치의 데이터를 쿼리할 수 있습니다.

    ```sql
    select dest_country_name as new_name, collect_list(count)([idx]) as flight_counts, collect_set(origin_country_name) as origin_set from flights group by dest_country_name
    ```

  - explode 함수를 사용해 배열을 다시 여러 개의 로우로 변환할 수 있습니다.

    ```sql
    select explode(collected_counts), dest_country_name from flights_agg
    ```

### 2. 함수

- 스파크 SQL은 다양한 고급 함수를 제공합니다. 전체 함수 목록을 확인하려면 show functions 구문을 사용합니다.

- 스파크에 내장된 시스템 함수나 사용자 함수 중 어떤 유형의 함수 목록을 보고 싶은 지 지정할 수 있습니다.

  ```sql
  SHOW SYSTEM(USER) FUCTIONS
  ```

- 개별 함수 설명과 사용법을 보고 싶으면 describe 키워드를 사용합니다.

  ```sql
  describe function function_name
  ```

- 사용자 정의 함수를 정의하고, 분산 환경에서 사용할 수 있는 기능을 제공합니다.

  ```scala
  def power3(number:Double):Double = number * number * number
  spark.udf.register("power3", power3(_:Double):Double)
  
  //sql 구문
  select count, power3(count) from flights
  ```

### 3. 서브 쿼리

- 서브 쿼리를 사용하면 쿼리 안에 쿼리를 지정할 수 있습니다.
- 스파크에는 두 가지 기본 서브쿼리가 있습니다.
  - 상호 연관 서브 쿼리 : 서브쿼리의 정보를 보완하기 위해 쿼리의 외부 범위에 있는 일부 정보를 사용할 수 있습니다.
  - 비상호 연관 서브 쿼리 : 외부 범위에 있는 정보를 사용하지 않습니다.
- 스파크는 값에 따라 필터링할 수 있는 조건절 서브 쿼리도 지원합니다.

### 비상호연관 조건절 서브 쿼리

- 예제) 데이터 중 상위 5개의 목적지 국가 정보를 조회합니다.

  ```sql
  select dest_country_name from flights
  group by dest_country_name order by sum(count) desc limit 5
  ```

- 이전 예제의 결과에 출발지 국가 정보가 존재하는 지 확인할 수 있습니다.

  ```sql
  select * from flights
  where origin_country_name in (select dest_country_name from flights group by dest_country_name order by sum(count) desc limit 5)
  ```

### 상호연관 조건절 서브 쿼리

- 내부 쿼리에서 외부 범위에 있는 정보를 사용할 수 있습니다.

- 예제) 목적지 국가에서 되돌아 올 수 있는 항공편이 있는 지

  ```sql
  select * from flights f1
  where exists (select 1 from flights f2
               where f1.dest_country_name = f2.origin_country_name)
  and exists (select 1 from flights f2
             where f2.dest_country_name = f1.origin_country_name)
  ```

  EXISTS 키워드는 서브쿼리에 값이 존재하면 true를 반환합니다. 앞에 NOT 연산자를 붙여 결과를 뒤집을 수 있습니다.



