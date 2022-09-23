# OSIV (OpenSession In View)

## OSIV : ON

![image](https://user-images.githubusercontent.com/40904001/191947850-54c1e2f7-c7d5-4f40-ab98-a1dc5ec507e2.png)

특징

- 기본값 : true
- 트랜잭션 시작처럼 최초 데이터베이스 커넥션 시작 시점부터 api 응답이 끝날 때까지 영속성 컨텍스트와 데이터베이스 커넥션을 유지한다.
- view template이나 api controller에서 지연로딩이 가능해 유지보수성이 좋다.
- 지연로딩은 영속성 컨텍스트가 살아있어야 가능하다.

단점

- 너무 오랜 시간동안 데이터베이스 커넥셜 리소스를 사용하기 때문에 실시간 트래픽이 중요한 애플리케이션에서 장애가 발생할 수 있다.

## OSIV : OFF

![image](https://user-images.githubusercontent.com/40904001/191947874-902a2baa-ae2e-4664-9612-a95c9eee6cab.png)

- 모든 지연로딩을 트랜잭션 안에서 처리해야 한다.

- view template에서 지연로딩이 불가능하다.