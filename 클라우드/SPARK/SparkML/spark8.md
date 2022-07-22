# 스파크 머신러닝 완벽 가이드

## Spark ML 분류 평가

- BinaryClassificationEvaluator, MulticlassClassificationEvaluator 두개의 클래스를 이용한다.
- Binary class는 roc-auc 지표만 제공한다.
- accuracy, precision, recall, f1-score를 얻기위해서는 MulticlassClassificationEvaluator 클래스를 사용해야 한다.
- MulticlassClassificationEvaluator로 얻어지는 precison, recall은 positive 예측 데이터 건수를 반영한 weighted precision, weighted recall 값이다.



## XGboost의 이해 및 주요 하이퍼 파라미터

### 스파크에서 구동 가능한 XGboost

1. XGBoost4j-spark
   - 스칼라 기반 xgboost
   - github에서 다운로드 하여 빌드 후 사용 가능
2. SPARKDL
   - python 기반 xgboost
   - databricks에서만 사용이 가능하다



- XGBoost4J의 하이퍼 파라미터는 Native Xgboost의 하이퍼 파라미터와 같다.
- SPARKDL의 하이퍼 파라미터는 Scikit-learn Wrapper XGBoost의 하이퍼 파라미터와 같다.

### XGBoost4J의 하이퍼 파라미터

1. eta : GBM의 learning_rate와 동일함
2. num_boost_rounds : 사이킷 런에 n_estimators와 동일함.
3. min_child_weight : 결정트리의 min_samples_leaf와 유사함. 과적합 조절용
4. max_depth : 트리의 최대 깊이
5. sub_sample : GBM의 subsample과 동일함.
6. lambda : L2 규제 적용 값
7. alpha : L1 규제 적용 값
8. colsample_bytree : GBM의 max_features와 유사함.
9. scale_pos_weight : 특정 값으로 치우쳐 있는 데이터 세의 균형을 유지하기 위한 파라미터
10. gamma : 트리의 리프 노드를 추가적으로 나눌지를 결정할 최소 손실 감소 값입니다.



## Spark XGBoost Early Stopping

- xgboost는 특정 반복 횟수만큼 더 이상 비용함수가 감소되지 않으면 반복 횟수를 완료하지 않고 종료할 수 있다.
- 학습 시간이 단축된다.
- 너무 반복 횟수를 단축하게 되면 예측 성능 최적화가 안된 상태에서 학습이 종료 될 수 있음.
- 조기 중단 설정을 위한 주요 파라미터
  - early_stopping_rounds : 더 이상 비용 평가 지표가 감소하지 않는 최대 반복 횟수
  - eval_metric : 반복 수행 시 사용하는 비용 평가 지표
  - validationIndicatorCol : 평가를 수행하는 별도의 검증 데이터 셋 여부를 학습 데이터 프레임에서 컬럼으로 가진다. 이를 이용하여 검증용 데이터 셋을 구분한다. (사이킷 런 xgboost의 eval_set과 유사함.)
- early stopping을 사용할 땐 검증 데이터 셋을 너무 크게 잡지 않도록 한다.



## mmlspark LightGBM 하이퍼 파라미터

- baggingFraction : 트리가 커져서 과적합되는 것을 제어하기 위해 데이터를 샘플링하는 비율 지정
- featureFraction : 트리 생성에 필요한 컬럼을 임의로 샘플링하는 데 사용된다. 
- minDetainLeaf : 리프 노드가 될 수 있는 최소 데이터 건 수
- lambdaL2 : L2 규제 적용 값
- labmdaL1 : L1 규제 적용 값
