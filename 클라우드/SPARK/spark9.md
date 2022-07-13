# 스파크 머신러닝 완벽가이드

## Grid 기반 튜닝의 문제점

### Grid Search / Random Search

- 개별 하이퍼 파라미터들을 grid 형태로 지정하는 것은 한계가 존재한다.
- 하이퍼 파라미터 수가 늘어날수록 비례하여 시간이 증가한다.
- 최적의 해를 찾는다는 보장이 없다.

## Bayesian Optimization

- 미지의 함수가 반환하는 값의 최대/최소값을 매우 짧은 주기를 통해서 찾아내는 방식
- 함수의 사후 분포를 생성하고 이를 기반으로 최적화하려는 함수를 재구성한다.

### 베이지안 최적화를 구현한 패키지

1. HyperOpt

   - 분산 framework에서 동작 가능

     ```python
     def objective_func(search_space):
         x = search_space['x']
         y = search_space['y']
         return {'loss':x**2+y*20, 'status':STATUS_OK}
     
     search_space = {'x':hp.quniform('x',5,15,1), 
                     'y': hp.uniform('y',0.01,0.1)}
     
     best = fmin(fn=objective_func, space=search_space, algo=algo, max_evals=5, trials=trials)
     ```

2. Bayesian optimization

   - 

3. Optuna

   - 