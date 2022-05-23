## 1. 퍼셉트론이란?

퍼셉트론은 다수의 신호를 입력으로 받아 하나의 신호를 출력한다. 퍼셉트론은 1(신호가 흐른다), 0(신호가 흐르지 않는다) 신호를 출력하여 앞으로 전달한다.

![img](https://blog.kakaocdn.net/dn/m8k58/btqIasGxlM3/QuFyNZi1KsII7bKJrDm57k/img.png)

- x2와 x1는 입력 신호,
- y는 출력 신호, w1와 w2는 가중치
- 원을 뉴런 혹은 노드라고 부른다



퍼셉트론의 동작원리

1. 입력 신호가 뉴런에 보내질 때는 각각 고유한 가중치가 곱해진다.
2. 뉴런에서 보내온 신호의 총합이 정해진 한계(임계값)를 넘어설 때만 1을 출력한다.

![img](https://blog.kakaocdn.net/dn/cjwhN3/btqHYJqgdNn/h66Q2xtjaCzgbcM0qdyIb0/img.png)

퍼셉트론은 복수의 입력 신호 각각에 고유한 가중치를 부여한다. 가중치는 각 신호가 결과에 중요한 영향력을 조절하는 요소로 작용한다. 즉 가중치가 클수록 해당 신호가 그만큼 중요함을 의미한다.



## 2. 단순한 논리 회로

### 			2.1 AND 게이트

![img](https://blog.kakaocdn.net/dn/CHvny/btqH2cyae1X/SK7XyA4Ef8zM5YkqbjBiNK/img.png)

### 			2.2 NAND 게이트와 OR 게이트

​				NAND는 Not AND를 의미하며, 그 동작은 AND 게이트 출력을 뒤집은 것이 된다.

![img](https://blog.kakaocdn.net/dn/dc06sB/btqH2dRuj1T/4QHARCnLnetDPJ2vKiwaF1/img.png)

​																	NAND 게이트의 진리표

​				OR 게이트는 입력 신호 중 하나 이상이 1이면 출력이 1이 되는 논리 회로입니다.

![img](https://blog.kakaocdn.net/dn/cwaFDo/btqHVozH8TG/bBsdUkbs6kN1gvP9KywEh1/img.png)

​																		OR 게이트의 진리표

## 4. 퍼셉트론의 한계

### 			4.1 XOR 게이트를 구현할 수 없다.

​			XOR 게이트는 베타적 논리합이라는 논리 회로다. x1과 x2 중 한쪽이 1일 때만 1을 출력한다.

​			단층 퍼셉트론으로는 XOR 게이트를 구현 할 수 없다.

![img](https://blog.kakaocdn.net/dn/IzHto/btqH891yxK7/K3f0pFeGHPwXAJx9tNO7lk/img.png)

​																	   XOR 게이트의 진리표

​			하나의 직선으로 XOR을 나눌 수 없기 때문에 단층 퍼셉트론으론 비선형 영역을 분리할 수 없다.



### 5. XOR 게이트 구현하기

### 	5.1 기존 게이트 조합하기

​			AND, NAND, OR게이트를 조합하여 XOR게이트를 만들 수 있다.

![img](https://blog.kakaocdn.net/dn/bphbAH/btqH0qwMDlP/KXcblVOGJqs7ORdGmWJKb0/img.png)



![img](https://blog.kakaocdn.net/dn/bTta66/btqH0WpbfW5/lirWjg4gdSHAbKl6oKA6bk/img.png)

![img](https://blog.kakaocdn.net/dn/dV0N3K/btqHZjEH5I4/pT6xXI9hBVG7a38O1nVwn0/img.png)

x1과 x2는 NAND와 OR게이트의 입력이 되고, NAND의 출력을 s1, OR의 출력을 s2로 해서 AND 게이트의 입력으로 넣어주면 된다.

```python
def XOR(x1, x2):
    s1 = NAND(x1, x2)
    s2 = OR(x1, x2)
    y = AND(s1, s2)
    return y
```

![img](https://blog.kakaocdn.net/dn/7029T/btqH4t0y6Iw/ibOdzTolVR2onSHT29T4lK/img.png)

이처럼 층이 여러 개인 퍼셉트론을 다층 퍼셉트론이라고 한다.



## 6. 정리

- 퍼셉트론은 입출력을 갖춘 알고리즘이다. 입력을 주면 정해진 규칙에 따른 값을 출력한다.
- 퍼셉트론은 '가중치'와 '편향'을 매개변수로 설정한다.
- 퍼셉트론은 AND, OR 게이트 등의 논리 회로를 표현할 수 있다.
- XOR 게이트는 단층 퍼셉트론으론 표현할 수 없다
- 다층 퍼셉트론을 이용하면 XOR게이트를 표현할 수 있다.
