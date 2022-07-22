# 스파크 머신러닝 완벽 가이드

## 회귀 (Regression)

### 선형 회귀 (linear regression)

- 종속 변수 y와 한 개 이상의 독립 변수 X와의 선형 관계를 모델링하는 회귀분석 기법

### Regularized 선형 회귀

- 실제값과 예측값의 오차를 줄이는 데만 집중하기 때문에 오버피팅이 발생 하기 쉽다. 이를 제어하기 위해 규제(Regularization)를 적용
- 규제는 L2, L1 규제가 있다. L2 규제는 W의 제곱에 대해 페널티를 부여하는 방식, L2 규제를 적용한 회귀를 릿지 회귀라고 한다.
- 라쏘(Lasso) 회귀는 L1 규제를 적용한 회귀이다. L1 규제는 W의 절대값에 대해 페널티를 부여한다. L1 규제를 적용하게 되면 영향력 없는 회귀 계수 값은 0으로 변환된다.
- 엘라스틱 넷(Elastic Net) : L1, L2 규제를 함께 결합한 모델. 주로 feature가 많은 데이터에 적용되며, L1 규제로 feature의 개수를 줄이면서 L2 규제로 계수 값의 크기를 조정한다.



## Scikit-learn Elastic Net Regression

- 사이킷런은 엘라스틱넷 클래스를 통해서 엘라스틱넷 회귀를 구현한다.

- 주요 파라미터 : alpha, l1_ratio
  $$
  ElasticNet_{reg} = a \times L1_{reg} + b \times L2_{reg}\\(a = L1\;규제의\;alpha,\; b = L2\;규제의\;alpha)
  $$



## LinearRegression 학습, 예측, 평가 수행.

- regParam = 0, elasticNetParam = 0 => 무규제 선형회귀
- regParam > 0, elasticNetParam = 0 => Ridge(L2 규제)
- regParam > 0, elasticNetParam = 1 => Lasso(L1 규제)
- regParam > 0, elasticNetParam = (0 ~ 1) => ElasticNet
- LinearRegression은 데이터를 학습전에 Standard Scaling을 적용할 수 있음. standardization=True가 기본임.