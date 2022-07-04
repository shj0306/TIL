# 스파크 머신러닝 완벽 가이드

## Spark ML 알고리즘 학습 및 예측 수행

- iris 데이터프레임을 randomSplit()을 이용하여 train,test 데이터프레임으로 분할한다.

  ```python
  train_sdf, test_sdf = iris_df.randomSplit([0.8,0.2], seed='랜덤값')
  train_sdf.cache()
  ```

- VectorAssembler를 이용하여 모든 feature들을 하나의 feature vector로 변환한다.

  ```python
  from pyspark.ml.feature import VectorAssembler
  
  vec_assembler = VectorAssembler(inputCols=iris_columns, outputCol='features')
  train_df = vec_assembler.transform(iris_train_df)
  ```

- Estimator 객체를 생성하고, fit() 메소드를 호출하여 ML model을 반환한다.

  ```python
  from pyspark.ml.classification import DecisionTreeClassifier
  
  dt = DecisionTreeClassifier(featuresCol='feature_vectorization한 컬럼', labelCol='target', maxDepth=5)
  
  # 모델 학습 (인자로 데이터프레임이 들어간다)
  dt_model = dt.fit(train_df)
  ```

- ML model을 이용하여 테스트 데이터프레임에 예측을 수행한다.

  ```python
  test_df = vec_assembler.transform(test_sdf)
  pred = dt_model.transform(test_df)
  ```

- 모델이 얼마나 정확한지 테스트 데이터와 비교한다.

  ```python
  from pyspark.ml.evaluation import MulticlassClassificationEvaluator
  
  eval_acc = MulticlassClassificationEvaluator(labelCol='target', predictionCol='prediction', metricName='accuracy')
  accuracy = eval_acc.evaluate(pred)
  ```



## PipeLine 적용하기

- 여러 개의 Transformer 변환 작업, Estimator의 학습 작업을 일련의 **Stage 연결**을 통해 간단한 API로 구현이 가능하다.
- 각 작업을 Stage로 정의해 Pipeline에 등록한 뒤 Pipeline의 fit() 메소드를 호출하여 연결된 Stage 작업을 수행하여 학습을 진행한다.



## Spark ML 교차 검증과 하이퍼 파라미터 튜닝

- Spark ML 은 CrossValidator 클래스를 통해서 교차 검증을 지원한다.

- CrossValidator는 교차검증뿐만 아니라 하이퍼 파라미터 튜닝까지 같이 실행한다(GridSearchCV와 유사)

- ParamGridBuilder로 하이퍼파라미터 튜닝을 위한 그리드 서치용 Param Grid를 생성한다.

  ```python
  from pyspark.ml.tuning import CrossValidator, ParamGridBuilder
  
  param_grid = ParamGridBuilder().addGrid('튜닝할 파라미터1')
  							   .addGrid('튜닝할 파라미터2')
                                 .build()
  ```

- 교차 검증 시 성능을 평가할 Evaluator를 생성한다.

  ```python
  eval_acc = MulticlassClassificationEvaluator(labelCol='타겟컬럼명', predictionCol='예측컬럼명', metricName='측정지표')
  ```

- CrossValidator 객체 생성시 Estimator객체, 그리드 서치용 Param Grid, 성능 평가용 Evaluator 객체, Fold 수를 인자로 입력함.

  ```python
  cv = CrossValidator(estimator='Estimator 객체', estimatorParamMaps=param_grid, evaluator='Evaluator 객체', numFolds='반복 횟수')
  ```

- CrossValidator 객체의 fit(입력DataFrame) 메소드를 호출하여 교차 검증과 하이퍼파라미터 튜닝 수행. fit() 수행 후 CrossValidatorModel 반환.

  

- 반환된 CrossValidatorModel의 avgMetrics 속성에 교차 검증별 평균 성능 평가점수, bestModel에 최적 하이퍼파라미터로 refit된 EstimatorModel 객체를 가짐.



## Pipeline과 결합하여 사용하기

```python
from pyspark.ml import Pipeline

pipeline = Pipeline(stages=[stage_1, stage_2])
# 하이퍼파라미터 튜닝을 위한 그리드 서치(Grid Search)용 ParamGrid 생성. stage_2.maxDepth로 지정해야함
param_grid = ParamGridBuilder().addGrid(stage_2.maxDepth, [5, 7, 8, 10])
                               .addGrid(stage_2.minInstancesPerNode, [3, 5, 6])
                               .build()
        
#CrossValidator 객체 생성 시 estimator 인자로 Estimator 객체가 아닌 Pipeline 객체 입력
cv = CrossValidator(estimator=pipeline, estimatorParamMaps=param_grid, evaluator=eval_acc, numFolds='반복 횟수')


# cv_model의 tranform()호출 시 test_sdf는 feature vectorization되지 않아야 함
pred = cv_model.transform(test_sdf)
```



## TrainValidationSplit

- input dataset을 랜덤하게 train set과 validation set으로 나눈 다음 하이퍼 파라미터 튜닝을 진행한다.
- CrossValidator의 경우 Fold 수 * 하이퍼파라미터 조합 수 만큼 튜닝이 진행되는 반면, TrainValidationSplit은 하이퍼파라미터 조합 수만큼만 튜닝이 진행된다.

```python
from pyspark.ml.tuning import TrainValidationSplit, ParamGridBuilder

dt_estimator = DecisionTreeClassifier(featuresCol='', labelCol='', maxDepth=10)
tvs_param_grid = ParamGridBuilder().addGrid().addGrid().build()

eval_acc = MulticlassClassificationEvaluator(labelCol='', predictionCol='', metricName='')

# TrainValidationSplit 객체 생성
tvs = TrainValidationSplit(estimator='estimator object', estimatorParamMaps='param_grid', evaluator=eval_acc, seed='random_val')
```

