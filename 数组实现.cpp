#include <stdio.h>
#define MaxSize 8
void king(int m,int n) { //m���ӵ�������n�ǳ��е�����
	int mon[MaxSize];
	int i=0,j=0,t=-1;
	while(i<m) {

		mon[i]=1;
		i++;
	}
	i=0;
	while(i<m) {
		while(j<n) {
			t=(t+1)%m;  //��ֹn>m���
			if(mon[t]==1)  //����0ʱ����˴������Ѿ���ȥ
				j++;
		}
		mon[t]=0;  //�����Ѿ���ȥ�ĺ���
		printf("%d ",t+1);
		i++;
		j=0;
	}
}

int main() {
	int m,n;
	printf("��������ӵĸ��������е���š�");
	scanf("%d %d", &m, &n);
	king(m,n);
	return 0;
}

