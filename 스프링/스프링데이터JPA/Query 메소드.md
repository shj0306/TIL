# JPA NamedQuery(실무에선 잘 안씀)

## NameQuery 정의

![image](https://user-images.githubusercontent.com/40904001/190847621-ae65dd3a-5856-42f5-810f-c57b63ece0ca.png)



## JPA를 직접 사용해서 NamedQuery 사용

![image](https://user-images.githubusercontent.com/40904001/190847673-5c284c30-c3a3-4899-b168-e8c7042a8726.png)



## 스프링 데이터 JPA로 NamedQuery 사용

 ![image](https://user-images.githubusercontent.com/40904001/190847849-5f38e271-8460-46d9-92aa-44fc7aae9cf7.png)

- @Query를 생략해도 우선적으로 Member.findByUsername이란 이름의 Named 쿼리를 찾아서 실행시켜준다. 없다면 메소드명으로 쿼리를 실행해준다.



## NamedQuery의 장점

- NamedQuery는 애플리케이션 로딩 시점에서 오류를 잡아준다.

  ![image](https://user-images.githubusercontent.com/40904001/190847996-9079da27-edad-4aa2-9630-9c44583208d7.png)



## 리포지토리 메소드에 쿼리 정의하기

![image](https://user-images.githubusercontent.com/40904001/190848268-947e6575-da34-4cae-87e0-fab95a6038be.png)

- 실무에서 가장 많이 씀 (개인적)
- NamedQuery와 마찬가지로 애플리케이션 로딩 시점에 오류를 잡아준다.



## 파라미터 바인딩

```java
select m from Member m where m.username = ?0 // 위치 기반
select m from Member m where m.username = :name // 이름 기반
```

**컬렉션 파라미터 바인딩**

![image-20220917180109709](Query 메소드.assets/image-20220917180109709.png)

[실행 결과]

![image](https://user-images.githubusercontent.com/40904001/190849098-7c0ce64c-e722-444e-8662-f4356f46d3f2.png)





# 스프링 데이터 JPA 페이징과 정렬

![image](https://user-images.githubusercontent.com/40904001/190850699-d0539c02-ce43-4c63-8f28-98e11e9bf336.png)

**테스트 코드**

![image](https://user-images.githubusercontent.com/40904001/190850735-582af440-0b2d-4e58-a2aa-3ad6f544b96b.png)

**[실행 결과]**

![image](https://user-images.githubusercontent.com/40904001/190850781-12ae6b29-8125-4936-98fe-ac250ddb8256.png)

![image](https://user-images.githubusercontent.com/40904001/190850789-f70126e3-712a-4080-a17f-0afb13981268.png)

![image](https://user-images.githubusercontent.com/40904001/190850864-24178767-568d-46e1-8976-a361ac9299f9.png)



- 이 때 Slice로 할 경우 count 쿼리는 나가지 않는다.

- 위 코드는 limit을 3으로 설정했는 데 slice의 경우는 3+1인 4로 쿼리가 나간다.

  - Page로 쿼리를 날릴 때

  ![image](https://user-images.githubusercontent.com/40904001/190851219-8361d5d1-d7bd-46c9-af37-b2a21508b07c.png)

  - Slice로 쿼리를 날릴 때

  ![image](https://user-images.githubusercontent.com/40904001/190851161-e284d80b-6ba6-4088-9f44-56974a8894bb.png)



**count 쿼리를 분리할 수 있다.**

![image](https://user-images.githubusercontent.com/40904001/190851442-bce37cc4-ee00-4c4c-826e-4166b205fd2b.png)



## 실무 꿀팁

- api에 엔티티를 직접 반환하지 않고 DTO로 변환한 후 반환해야 한다.

![image](https://user-images.githubusercontent.com/40904001/190851604-f3e481a8-7b84-4223-bebc-8d0285d9fd8d.png)





# 벌크성 수정 쿼리

![image-20220917192611331](Query 메소드.assets/image-20220917192611331.png)

**주의할 점**

- 벌크 연산은 영속성 컨텍스트를 무시하고 DB에 바로 쿼리를 날리기 때문에 DB와 영속성 컨텍스트의 값이 다를 수 있다.
- 그렇기 때문에 벌크 연산을 수행한 후에는 em.clear()로 영속성 컨텍스트를 날려서 DB에서 가져오게 한다.
- 혹은 @Modifying에 clearAutomatically = true로 설정해주면 된다.



# Entity Graph

- 지연로딩에서 발생하는 N+1 문제를 해결해주는 기능
- 페치 조인과 기능이 동일함

1. @NamedEntityGraph

   ![image](https://user-images.githubusercontent.com/40904001/190853548-4ce4e781-d910-4dfc-bcad-4e8f0727a60c.png)

   ![image](https://user-images.githubusercontent.com/40904001/190853541-501b62b8-37d6-4b90-9ced-0116face872c.png)

2. @EntityGraph

   ![image](https://user-images.githubusercontent.com/40904001/190853534-52e1d461-8f12-409a-ac71-efa5945f89b0.png)

[실행 결과]

![image](https://user-images.githubusercontent.com/40904001/190853530-09bfdbb0-dd3d-4684-9991-4e91893e0ae4.png)





# JPA Hint & Lock

