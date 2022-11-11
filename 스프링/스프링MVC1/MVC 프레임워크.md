# 프론트 컨트롤러

## FrontController 패턴 특징

- 프론트 컨트롤러 서블릿 하나로 클라이언트 요청을 받는다.
- 프론트 컨트롤러가 요청에 맞는 컨트롤러를 찾아서 호출
- 나머지 컨트롤러는 서블릿을 사용하지 않아도 된다.

### 1. 프론트 컨트롤러 기본 구조

![image](https://user-images.githubusercontent.com/40904001/201349334-86a80160-b119-4634-acee-a3a906b5cd8d.png)

공통 인터페이스인 ControllerV1을 상속받은 컨트롤러들을 URI 매핑 정보에서 조회해서 호출하면 컨트롤러에서는 JSP를 forward해 화면을 표시해준다.



### 2. View 분리 (중복 코드 제거)

![image](https://user-images.githubusercontent.com/40904001/201349067-85712c22-3e67-46bd-bf04-eec25f522cba.png)

1에서 문제였던 뷰로 이동하는 부분에 중복을 제거해주기 위해 MyView라는 객체를 만들어준다. 

MyView라는 객체에 뷰 이름만 넣고 반환하면 해당 객체가 render()를 통해서 JSP를 실행시킨다.



