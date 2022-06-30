# 스파크 머신러닝 완벽 가이드

## withColumn() 메소드

- pandas DataFrame은 [] 을 이용하여 기존 컬럼값을 update, 또는 신규 컬럼 추가, 묵시적으로 컬럼 타입을 변경할 수 있음. 컬럼명 변경시는 rename()을 사용. 명시적인 컬럼 타입 변경은 astype()적용

- spark DataFrame은 withColumn() 메소드를 이용하여 기존 컬럼값을 update, 컬럼 타입 변경, 신규 컬럼값을 추가할 수 있음.

- withColumn('신규 또는 Update되는 컬럼명', '신규 또는 update되는 값')을 인자로 가짐.

- 신규 또는 update되는 값을 생성 시에 기존 컬럼을 기반으로 한다면 신규 컬럼은 문자열로, 기존 컬럼은 반드시 컬럼형(col('컬럼명'))을 이용하여 적용.

- 신규 컬럼값을 추가하는 것은 select() 메소드로도 가능

- 컬럼명을 변경하는 것은 withColumnRename() 메소드로 수행.

- update할 값은 컬럼형이어야 하고, 상수값으로 update하려면 lit()을 사용해야 한다.

- split()을 이용하여 문자열을 특정 문자로 분리하여 새로운 컬럼들을 생성할 수 있다.

  

## withColumnRenamed() 메소드

```python
withColumnRenamed('기존 컬럼명', '변경 컬럼명')
```

- 변경하려는 컬럼명이 없어도 오류를 발생 시키지 않는다. (유의)



## Spark DataFrame의 컬럼과 로우 삭제

- Spark DataFrame drop() 메소드는 컬럼 삭제만 가능. 단일/여러개의 컬럼을 삭제 할 수 있음. 단 여러개의 컬럼 삭제 시 list로 입력 할 수 없으며 개별 컬럼명들이 입력되어야 함.
- Spark DataFrame은 기본적으로는 특정 조건에 따른 로우 삭제가 어려움. 로우 삭제 대신 filter() 메소드를 이용하여 삭제하지 않은 데이터만 추출해낸다.
- Pandas의 None 값을 Null을 의미하여 Spark에서는 null로 변환됨.
- 값이 있는 record는 dropna() 메소드 또는 DataFrame.na.drop()을 이용하여 삭제 할 수 있음. 또는 filter() 조건에서 Not null조건으로 다시 만들어 냄.
- drop할 컬럼이 존재하지 않아도 오류가 발생하지 않음 (유의)
- 여러 개의 컬럼을 삭제할 때 list가 아니라 단일 컬럼명들을 각각 인자로 넣어야 한다.
- 여러 개의 컬럼들을 삭제할 때 컬럼형 인자는 안된다.



## Spark DataFrame의 Null인 레코드 삭제

- 특정 컬럼에 Null이 있는 경우에만 삭제할 경우

  ```python
  sdf.na.drop(subset=['삭제할 컬럼명1','삭제할 컬럼명2'])
  ```



## Pandas와 Spark에서의 None, Null, NaN 의 구분 - 1

- Python은 None이라는 값이 없는 내장 상수가 있음. None 객체라고도 부리면 이는 NoneType 클래스임.
- numpy는 python None은 처리하기 위해 object 형으로 None을 할당할수 있고, float 형으로 NaN을 할당 할 수 있음.
- 특정 컬럼에 데이터가 없을 때 문자열인 경우 None, 숫자형 컬럼인 경우 NaN으로 할당된다.
- Spark는 csv와 같은 파일에서 로드 시 모든 컬럼을 다 Null로 변환. 기본적으로 None은 Null에 할당. 이는 SQL사상과 동일.
- 하지만 Spark는 pandas DataFrame의 NaN 처리와 어느정도 호환성을 유지하기 위해 NaN도 함께 지원.
- 과거 버전 Spark(Spark 3.0 이하)는 pandas DataFrame을 spark로 변환 시에 NaN 값을 동일하게 NaN으로 변환하였으나 현재(Spark 3.2)는 null로 변환함. 하지만 NaN 값을 명확하게 지정하여 spark DataFrame을 만들 수 있음.
- 결론적으로 NaN은 고려하지 않고 Null만 고려할 수 있도록 Spark DataFrame을 만드는 것이 중요. isnan()은 사용하지 않고, isNull()만 사용할 수 있도록 유도.



## Pandas와 Spark에서의 Null과 NaN 찾기

- pandas DataFrame의 isnull()과 isna()는 서로 동일한 메소드임. isnull(), isna() 모두 None과 NaN을 모두 찾음.
- spark DataFrame isNull()은 null만 찾아줌, isnan()은 NaN만 찾음. 또한 isNull()은 컬럼 조건에 붙어서 filter()메소드와 함께 사용되며, isnan()은 pyspark.sql.functions의 함수로 정의됨.
- spark DataFrame의 dropna() 메소드는 NaN과 Null 모두를 찾아서 삭제해줌.
- Not Null 조건으로 찾을 때는 isNotNull() 적용.



## when을 적용하여 조건별로 데이터 처리하기

### When

- pyspark의 dataframe에서 if문처럼 사용할 수 있는 sql인 case-when과 비슷한 when(+otherwise)을 사용할 수 있다.

  ```python
  from pyspark.sql.functions import when
  
  df = df.withColumn('new_gender', when(df.gender == 'M', 'Male')
                    .when(df.gender == 'F', 'Female')
                    .when(df.gender.isNull(), "")
                    .otherwise(df.gender))
  ```

- select 문에도 사용할 수 있다.

  ```python
  df = df.select(col('*'), when(df.gender=='M','Male')
                .when(df.gender == 'F', 'Female')
                .when(df.gender.isNull(), '')
                .otherwise(df.gender).alias('new_gender'))
  ```



## 결손 데이터 처리하기

- DataFrame의 fillna() 메소드, 또는 DataFrameNaFunctions 객체인 DataFrame.na의 fill() 메소드를 이용
- DataFrame.fillna(value=값, subset=['컬럼1', 컬럼2])로 형태로 사용. value는 결측값에 입력될 값, subset은 대상 컬럼. subset을 지정하지 않으면 전체 컬럼에 적용.
- subset을 지정하지 않고 value에 숫자값을 입력하면 숫자형 컬럼만 결손값을 처리함. 비슷하게 value에 문자값을 입력하면 문자형 컬럼만 결손값을 처리함.
- value는 반드시 단일 값이 들어가야함. 단일 값을 가지는 DataFrame은 안됨.

- **first()** 메소드
  - head()와 동일하게 동작하지만 first는 맨 처음 Row만 가져온다.



## UDF 적용하기

- UDF를 Spark DataFrame에 적용하려면 먼저 일반 함수를 만든 후에 이를 spark의 udf() 함수를 이용하여 DataFrame에서 사용할 수 있도록 변환해야 함.
- Spark DataFrame의 fillna()에 인자로 Dict를 입력하여 여러개의 컬럼들에 대해서 결측치 값을 입력할 수 있다.





