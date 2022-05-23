class TwoLayerNet:

    # 초기화 수행 메서드
    # params는 신경망의 매개변수를 보관하는 딕셔너리 변수(인스턴스 변수)
    def __init__(self, input_size, hidden_size, output_size, weight_init_std=0.01):
        self.params = {}             # 가중치 초기화
        self.params['W1'] = weight_init_std * \
                           np.random.randn(input_size, hidden_size) # (입력 X 은닉층) 행렬의 가중치 생성
        self.params['b1'] = np.zeros(hidden_size)                   # 은닉층 노드수만큼 편향 생성, 0으로 설정
        self.params['W2'] = weight_init_std * \
                           np.random.randn(input_size, hidden_size) 
        self.params['b2'] = np.zeros(hidden_size)
        
    
    # 예측(추론) 수행 메서드, x : 이미지 데이터
    def predic(self, x):
        W1, W2 = self.params['W1'], self.params['W2']
        b1, b2 = self.params['b1'], self.parmas['b2']
        
        a1 = np.dot(x, W1) + b1      # 활성화 함수 입력 데이터
        z1 = sigmoid(a1)             # 활성화 함수 출력 ( 시그모이드 사용)
        a2 = np.dot(z1, W2) + b2
        y = softmax(a2)              # 소프트맥스 함수는 확률로 해석가능 (총합이 1)
        
        return y
        
        
    # 손실 함수 값을 구하는 매서드 x : 입력 데이터, t : 정답 레이블
    def loss(self, x, t):
        y = self.predict(x)
        
        return cross_entropy_error(y, t)
        
        
    # 정확도 측정하는 메서드
    def accuracy(self, x, t):
        y = self.predict(x)
        y = np.argmax(y, axis=1)     # y행렬의 1차원 요소 최대값 추출
        y = np.argmax(t, axis=1)
        
        accuracy = np.sum(y == t) / float(x.shape[0])
        return accuracy
        
        
    # 가중치 매개변수의 기울기를 구하는 메서드
    # grads는 기울기 보관하는 딕셔너리 변수(numerical_gradient의 반환값)
    def numerical_gradient(self, x, t)
        loss_W = lambda W: self.loss(x, t)
        
        grads = {}
        grads['W1'] = numerical_gradient(loss_W, self.params['W1'])
        grads['b1'] = numerical_gradient(loss_W, self.params['b1']) # 편향도 갱신해줘야 한다.
        grads['W2'] = numerical_gradient(loss_W, self.params['W2'])
        grads['b2'] = numerical_gradient(loss_W, self.params['b2'])
        
        return grads
        
    # 오차역전파법을 사용하여 기울기를 효율적이고 빠르고 계산할 수 있습니다.
    # def gradient(self, x, t) 오차역전파법은 다음 포스팅에서 공부하도록 하겠습니다.