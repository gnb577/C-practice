#define R 20
#define BOUNCE 1
#define W 20
#define H 200

R = 20 공용
W = 20 스틱용
H = 200 스틱용

/*

x, y = 초기 좌표
xv, yv = x,y의 속도
sX,sY = 스틱의 초기값 그러나 안씀
sXv,sYv = 스틱의 속도 그러나 안씀




/*

x = 250;
y = 200;
xv *= -(BOUNCE);
flag = 0;
누를 때마다 방향을 반대로




wsprintf(str, TEXT("%d, %d, %d, %d"), x, y, xv, yv);
아까 띄어져 있던 숫자 표현


void moveBall()
{
	if (y <= R || y >= crt.bottom - R) {
		yv *= -(BOUNCE);
		if (y <= R) y = R;
		if (y >= crt.bottom - R) y = crt.bottom - R;
	}
	x += (int)xv;
	y += (int)yv;
}

상단을 넘어가거나, 하단을 넘어간 경우, 역 재생하겠다.


void collision()
{
	if (flag == 0) {
		if (x < W + R && y > sY[0] - R && y < sY[0] + H + R)
		{
			x += R / 2;
			xv *= (-BOUNCE);
		}
		if (x >= crt.right - R - W && y > sY[1] - R && y < sY[1] + H + R)
		{
			x -= R / 2;
			xv *= (-BOUNCE);
		}
	}
	if (x < crt.left - R || x > crt.right + R) //벗어난 경우
	{
		flag = 1;
	}
}
안씀 moveball에 이전됨

그리고 결국 x, y, xv, yv가 공유되면 되는 부분인 거임