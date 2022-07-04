# 스파크 머신러닝 완벽 가이드

## Spark ML의 주요 특징과 구성 요소

- Spark DataFrame 데이터를 학습/검증/테스트 기반으로 ML 알고리즘 구동
- 여러 개의 컬럼들을 한 컬럼의 feature vectorization 한 뒤 이를 이용해 학습/예측을 수행한다.
- Estimator가 fit을 호출하여 Model 객체를 반환하며 이 모델에서 예측을 수행한다.
- 파이프라인 사용 권장

### 구성 요소

1. Estimator
   - Classification
   - Regression
   - Clustering
   - Collaborative
   - filtering
2. Transformar
   - OneHotEncoder
   - VectorAssembler
   - StandardScaler
   - Toknizer

1. Model Selection(and Tuning)
   - randomSplit
   - TrainValidaionSplit
   - CrossValidator
   - ParamGridBuilder
2. Pipeline
3. Evaluator
   - RegressionEvaluator
   - BinaryClassificationEv
   - MultiClassificationEv
4. Extractor, Feature Selection
   - TF-IDF
   - Word2Vec



## Spark ML의 주요 구성 요소 상세 및 특징

1. DataFrame
   - 데이터 처리를 위한 기반 object
2. Transformer
   - 보통 레이블/원-핫 인코딩을 하는 인코더, 스케일링 변환을 하는 스케일러, Feature Vectorization 등의 작업을 수행한다.
   - 모델이 예측하려면 transform() 메소드를 호출하는 데 여기에 입력 인자로 DataFrame이 필요하며, 반환된 DataFrame에 예측 결과를 가지고 있음.
3. Estimator
   - 머신 러닝 알고리즘 객체, Estimator는 fit() 메소드로 학습을 수행한다. 하지만 fit() 메소드는 Estimator Model 객체를 반환하며, 해당 객체에서 transform()을 호출하여 예측을 수행한다.
4. Pipeline
   - 개별 처리 로직을 묶어서 한꺼번에 처리할 수 있도록 도와준다.

