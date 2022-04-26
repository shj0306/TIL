## Ensemble

### 1. Voting

- 서로 다른 알고리즘을 가진 분류기를 결합해 투표를 통해 최종 예측 결과를 결정하는 방식
- #### Hard Voting
  - Majority Voting이라고도 하며, 각각의 모델들이 결과를 예측하면 단순히 가장 많은 표를 얻은 결과를 선택하는 방식입니다.

![img](https://user-images.githubusercontent.com/40904001/165271716-ae592d7f-9ee1-417d-b8e9-935e5d60c533.png)

- #### Soft Voting
  - 다른 말로 Probaility Voting이라고 불립니다. 각 class 별로 모델들이 예측한 확률을 합산해서 가장 높은 class를 선택하는 방식입니다.


![soft_voting](https://user-images.githubusercontent.com/40904001/165271837-d7a168f5-3fc8-4840-8b7d-3bfb46c39727.png)



### 2. Bagging(Bootstrap Aggregation)

- Bagging은 샘플을 여러 번 뽑아(Bootstrap) 각 모델을 학습 시켜 결과물을 집계(Aggregation)하는 방식입니다.

- 랜덤 포레스트(Random Forest)
  - 랜덤 포레스트는 여러 개의 결정 트리 분류기가 전체 데이터에서 배깅 방식으로 각자의 데이터를 샘플링해 개별적으로 학습을 수행한 뒤 최종적으로 모든 분류기가 voting을 통해 예측 결정을 합니다.  
  
   ![rf](https://user-images.githubusercontent.com/40904001/165272135-69208d5a-d37b-4ecb-a66b-31b2891dcec9.jpg)

  
- 랜덤 포레스트 하이퍼 파라미터
  - n_estimators: 결정 트리의 개수 지정. 디폴트는 100
  - max_features: 결정 트리에서 사용하는 max_features. 디폴트는 'auto'
  - max_depth, min_samples_leaf 등 결정 트리에서 사용하는 파라미터


### 3. Boosting

- 여러 개의 약한 학습기를 순차적으로 학습-예측하면서 데이터에 가중치 부여를 통해 오류를 개선해 나가면서 학습하는 방식

  ![boosting](https://user-images.githubusercontent.com/40904001/165272054-d5fb2e7c-ad91-4898-be04-e477b3a49feb.jpg)

  
- XgBoost
  - GBM의 단점인 느린 수행 시간과 과적합 규제 부재 등의 문제를 해결해 각광받고 있는 패키지다.
  - XGBoost 하이퍼 파라미터
    - booster : gbtree(트리 베이스 모델), gblinear(선형 모델), default = gbtree
    - silent: 출력 메시지를 나타내고 싶지 않을 때 1로 설정, default = 0
    - nthread: CPU의 실행 스레드 개수를 조정
  - 주요 부스터 파라미터: 트리 최적화, 부스팅, regularization 등과 관련 파라미터 등을 지칭한다.
    - eta[default=0.3, alias: learning_rate]: GBM의 학습률(learning_rate) 와 같은 파라미터로 0-1 사이의 값을 지정하고 부스팅 스텝을 반복적으로 수행할 때 업데이트되는 학습률 값.
    - num_boost_rounds: GBM의 n_estimators 와 같은 파라미터
    min_child_weight[default=1]: 트리에서 추가적으로 가지를 나눌지를 결정하기 위해 필요한 데이터의 weight 총합, 값이 클수록 분할을 자제하며 과적합을 조절하기 위해 사용
    - gamma[default=0, alias: min_split_loss]: 트리의 리프 노드를 추가로 나눌지를 결정할 최소 손실 감소 값, 해당 값보다 큰 손실이 감소된 경우 리프를 분리하며, 값이 클수록 과적합 감소 효과가 있다.
    - max_depth[default=6]: 트리 기반 알고리즘의 max_depth 와 같다. 0을 지정하면 깊이에 제한이 없고, max_depth 가 높으면 특정 피처 조건에 특화되어 과적합 가능성이 높아지므로 3~10 사이의 값을 적용한다.
    - sub_sample[default=1]: GBM의 subsample 과 동일하다. 트리가 커져서 과적합되는 것을 제어하기위해 데이터를 샘플링하는 비율을 지정한다. 0에서 1사이의 값이 가능하나 일반적으로 0.5에서 1사이의 값을 사용한다.
    - colsample_bytree[default=1]: GBM의 max_features 와 유사하다. 트리 생성에 필요한 피처를 임의로 샘플링 하는데 사용되며, 매우 많은 피처가 있을때 과적합을 조정하는데 적용한다.
    - lambda[default=1, alias: reg_lambda]: L2 Regularizaion 적용 값으로, 피처 개수가 많을 경우 적용을 검토하고, 값이 클수록 과적합 감소 효과가 있다.
    - alpha[default=0, alias: reg_alpha]: L1 Regularizaion 적용 값으로, 위 lambda 와 동일하다.
    - scale_pos_weight[default=1]: 특정 값으로 치우친 비대칭한 클래스로 구성된 데이터 세트의 균형을 유지하기 위한 파라미터이다.

  - 학습 태스크 파라미터: 학습 수행시의 객체 함수, 평가를 위한 지표 등을 설정하는 파라미터
    - objective: 최솟값을 가져야할 손실 함수를 정의, 이진 분류인지 다중 분류인지에 따라 달라짐.
    - binary:logistic: 이진 분류일 때 적용
    - multi:softmax: 다중 분류일 때 적용, 손실 함수가 multi:sotfmax면 레이블 클래스의 개수인 num_class 파라미터를 지정해야 한다.
    - multi:softprob: multi:softmax와 유사하나 개별 레이블 클래스의 해당하는 예측 확률을 반환한다.
    - eval_metric: 검증에 사용되는 함수를 정의, 기본값은 회귀인 경우 rmse, 분류는 error이다.



- LGBM(Light Gradient Boosting Machine)

  - Gradient Boosting 프레임워크로 Tree 기반 학습 알고리즘입니다. 기존의 다른 Tree 기반 알고리즘과 다른점은 Tree구조가 수평적으로 확장하는 다른 Tree기반 알고리즘에 비해 수직적으로 확장을 하는 것에 있습니다.
  
    ![다운로드](https://user-images.githubusercontent.com/40904001/165272257-c756ae85-72dd-4424-8082-94029fb71fe8.png)
    
  - Light GBM의 단점?
    - Light GBM은 leaf-wise growth로 과적합의 우려가 다른 Tree 알고리즘에 비해 높은 편입니다. 그러므로 데이터의 양이 적을 경우 과적합에 취약한 면이 있어 데이터 양이 적을 경우 사용하지 않는 것이 좋습니다.
  
  - 하이퍼 파라미터 튜닝 방안
    - num_levels의 개수를 중심으로 min_child_samples(min_data_in_leaf), max_depth를 함께 조정하면서 모델의 복잡도를 줄이는 것이 기본 튜닝 방안입니다.
  
      - num_levels는 개별 트리가 가질 수 있는 최대 리프의 개수이고 LightGBM 모델의 복잡도를 제어하는 주요 파라미터입니다. 일반적으로 num_leaves의 개수를 높이면 정확도가 높아지지만, 반대로 트리의 깊이가 깊어지고 모델이 복잡도가 커져 과적합 영향도가 커집니다.
      - min_data_in_leaf는 사이킷런 래퍼 클래스에서는 min_child_samples로 이름이 바뀝니다. 과적합을 개선하기 위한 중요한 파라미터입니다. num_leaves와 학습 데이터의 크기에 따라 달라지지만, 보통 큰 값으로 설정하면 트리가 깊어지는 것을 방지합니다.
      - max_depth는 명시적으로 깊이의 크기를 제한합니다. num_leaves, min_data_in_leaf와 결합해 과적합을 개선하는 데 사용합니다.
