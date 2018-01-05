#include <stdio.h>
#define MaxSize 8
void king(int m,int n) { //m猴子的数量，n是出列的数。
	int mon[MaxSize];
	int i=0,j=0,t=-1;
	while(i<m) {

		mon[i]=1;
		i++;
	}
	i=0;
	while(i<m) {
		while(j<n) {
			t=(t+1)%m;  //防止n>m情况
			if(mon[t]==1)  //等于0时代表此处猴子已经出去
				j++;
		}
		mon[t]=0;  //代表已经出去的猴子
		printf("%d ",t+1);
		i++;
		j=0;
	}
}

int main() {
	int m,n;
	printf("请输入猴子的个数及出列的序号。");
	scanf("%d %d", &m, &n);
	king(m,n);
	return 0;
}

