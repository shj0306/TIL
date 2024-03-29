# MVC 패턴

하나의 서블릿이나, JSP로 처리하던 것을 컨트롤러와 뷰라는 영역으로 역할을 나눈 것

**컨트롤러**

- HTTP 요청을 받아서 파라미터를 검증하고, 비즈니스 로직을 실행한다.
- 뷰에 전달할 결과 데이터를 모델에 담아서 전달한다.

**모델**

- 뷰에 출력할 데이터를 담아둔다.
- 모델 객체 덕분에 뷰는 화면을 렌더링하는 일에만 집중할 수 있다.

**뷰**

- 모델에 담겨 있는 데이터를 사용해서 화면을 표시한다.

![image](https://user-images.githubusercontent.com/40904001/201333412-b9a27a3c-92c9-4039-8aa9-4891574788e7.png)



## MVC 패턴 - 한계

- 컨트롤러 쪽 코드가 중복되는 부분이 생긴다.
- 사용하지 않는 코드가 생긴다. (HttpServletRequest req, HttpServletResponse resp)
- 이런 경우 테스트 케이스를 작성하기도 힘들다.
- 공통 처리가 어렵다.



**이 문제를 해결하기 위해서**



## 프론트 컨트롤러 (Front Controller)
