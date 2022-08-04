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
- 테이블 메타데이터