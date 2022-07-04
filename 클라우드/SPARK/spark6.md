# 스파크 머신러닝 완벽가이드

## Spark ML Encoding

- Label Encoding은 StringIndexer 클래스를 이용, one-hot encoding은 OneHotEncoder 클래스를 이용
- StringIndexer, OneHotEncoder 모두 Transformer에 속한다.



### Label Encoding

```python
from pyspark.ml.feature import StringIndexer

indexer = StringIndexer(inputCol='col_name', outputCol='le_col')
# 여러 개의 컬럼을 적용시키고자 할 때
indexer = StringIndexer(inputCols=['col_name1', 'col_name2'], outputCols=['le_col1', 'le_col2'])

# StringIndexe는 fit() 수행시 데이터프레임을 입력으로 받고, StringIndexerModel 객체를 반환한다.
indexer_model = indexer.fit(df)
```

#### IndexToString 클래스를 이용하여 Label Encoding된 값을 원본 값으로 변환

```python
from pyspark.ml.feature import IndexToString

converter = IndexToString(inputCol='레이블인코딩된 컬럼명', outputCol='새로운 컬럼명')
converted = converter.transform(df)
```



### One-hot Encoding

- OnehotEncoder 클래스를 이용하여 변환한다.

- One-hot Encoding할 컬럼들은 반드시 숫자형이어야 한다. 그렇기 때문에 문자형 컬럼을 바꾸기 위해선 우선 Label-Encoding으로 숫자로 변환해준 다음 One-hot Encoding을 해줘야 한다.

  ```python
  # dropLast는 마지막 인자를 제외할지를 나타냄 default는 True. 
  # 5개의 카테고리(0, 1, 2, 3, 4)가 있을 경우 2는 [0.0, 0.0, 1.0, 0.0] 로 매핑. 4는 [0.0, 0.0, 0.0, 0.0]로 매핑. 
  encoder = OneHotEncoder(dropLast='T/F', inputCols=["col_name1", "col_name2"], outputCols=["oe1", "oe2"])
  
  ```

- 파이프라인을 활용하면 효율적으로 One-hot Encoding을 할 수 있다.



## Standard Scaling / MinMax Scaling

### Standard Scaling

- Standard 스케일링은 StandardScaler 클래스로, Min Max 스케일링은 MinMaxClass를 이용하여 적용한다.

- 주의할 점 : 사용한 Scaling은 일반 컬럼형(숫자형)이 아니라 vector형에만 적용이 가능함. 이는 Spark ML이 통계 전용의 기능을 제공하기 보다는 ML에 주로 특화 되었기 때문이다.

- 단일 컬럼에 Scaling을 적용할 때도 반드시 VectorAssembler로 변환 후에 적용해야 함

  ```python
  from pyspark.ml.feature import VectorAssembler
  from pyspark.ml.feature import StandardScaler
  
  vec_assembler = VectorAssembler(inputCols=['input_col'], outputCols='output_vector')
  
  # 변환된 spark dataframe
  vectorized_sdf = vec_assembler.transform(sdf)
  ```

- 전체 컬럼에 Standard Scaler 적용

  ```python
  vec_assembler = VectorAssembler(inputCols='전체 컬럼 리스트', outputCol='output_col')
  # withMean, withStd : True로 설정하지 않으면 평균값을 0, 표준편차 값을 1로 잡아 주지 않는다.
  standard_scaler = StandardScaler(inputCol='output_col', outputCol='standard_scaled_features', withMean=True, withStd=True)
  
  standard_scaled_df = standard_scaler.fit(vectorized_sdf).transform(vectorized_sdf)
  ```

 

### MinMax Scaling

```python
from pyspark.ml.feature import MinMaxScaler

# 전체 feature 컬럼에 minmax scaler 적용
vec_assembler = VectorAssembler(inputCols='전체 컬럼 리스트', outputCol='output_col')
vectorized_sdf = vec_assembler.transform(sdf)

minmax_scaler = MinMaxScaler(inputCol='output_col', outputCol='minmax_scaled_features')
minmax_scaled_df = minmax_scaler.fit(vectorized_sdf).transform(vectorized_sdf)
```

