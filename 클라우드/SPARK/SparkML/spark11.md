# 스파크 머신러닝 완벽 가이드

## feature engineering

- 알고리즘이 보다 효율적으로 예측할 수 있도록 데이터 가공
  - Scaling (StandardScaler, MinMaxScaler)
  - 변환 (Transformation)
    - 로그 변환
    - Polynomial 피처 변환
    - PCA 변환
  - 인코딩
    - Label Encoding
    - One-Hot Encoding
  - 결측치(Null 값) / 이상치(Outlier) 치환
  - Skew 데이터 셋 보정
    - Over/Under Sampling
- 주요 feature들을 결합/재가공하여 새로운 feature들을 도출

- 아직 데이터로 표출되지 않은 주요 feature들을 feature engineering을 통해 도출
- 비슷한 feature들을 너무 많이 도출하는 것은 과적합을 가져 올 수 있다.