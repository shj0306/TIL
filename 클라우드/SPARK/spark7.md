# 스파크 머신러닝 완벽 가이드

## Spark Machine Learning library의 장단점

- 분산 서버에서 머신 러닝 알고리즘이 구동될 수 있도록 구현됨
- 라이브러리 기능의 다양성 측면에서는 사이킷 런보다 미흡하다



## Decision Tree 알고리즘

### 주요 하이퍼 파라미터

- maxDepth : Decision Tree의 최대 깊이

- maxBins : 연속형 feature 값을 이산 값으로 변환 시 최대 bin 수

- minInfoGain : split시 최소 information gain

- impurity : information gain 또는 gini 계수를 기반으로 할지 설정

- maxMemoryInMB : histogram 총합 최대 메모리

- minInstancePerNode : 분할 후에 자식 노드가 가지는 최소 sample 개수,  이 값보다 작아야 더 이상 분할하지 않는다.

- minWeightFractionPerNode : 분할 후에 자식 노드가 가지는 최소 sample 수값에 적용하 weight값(0~0.5)

  

## RandomForest 알고리즘

- 배깅의 대표적인 알고리즘

### 주요 하이퍼 파라미터

- numTrees : 학습에 사용될 tree 개수
- subsamplingRate : 학습에 사용될 데이터의 비율
- featureSubsetStrategy : 학습에 사용될 feature의 선택 전략(all, sqrt, log2, N)



## Gradient Boosting 알고리즘

### 주요 하이퍼 파라미터

- maxIter : Gradient Update 최대 반복 적용 횟수