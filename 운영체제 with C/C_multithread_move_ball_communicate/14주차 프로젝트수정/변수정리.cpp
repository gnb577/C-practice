#define R 20
#define BOUNCE 1
#define W 20
#define H 200

R = 20 ����
W = 20 ��ƽ��
H = 200 ��ƽ��

/*

x, y = �ʱ� ��ǥ
xv, yv = x,y�� �ӵ�
sX,sY = ��ƽ�� �ʱⰪ �׷��� �Ⱦ�
sXv,sYv = ��ƽ�� �ӵ� �׷��� �Ⱦ�




/*

x = 250;
y = 200;
xv *= -(BOUNCE);
flag = 0;
���� ������ ������ �ݴ��




wsprintf(str, TEXT("%d, %d, %d, %d"), x, y, xv, yv);
�Ʊ� ����� �ִ� ���� ǥ��


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

����� �Ѿ�ų�, �ϴ��� �Ѿ ���, �� ����ϰڴ�.


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
	if (x < crt.left - R || x > crt.right + R) //��� ���
	{
		flag = 1;
	}
}
�Ⱦ� moveball�� ������

�׸��� �ᱹ x, y, xv, yv�� �����Ǹ� �Ǵ� �κ��� ����