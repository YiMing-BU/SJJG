/*
目的：利用函数结构体动态定义一个数组，并对其进行一些操作
*/
# include<stdio.h>
# include<malloc.h>
# include <stdlib.h>


//“数据结构”定义了一个数据类型,该数据类型的名字叫做sturuct Arr,该数据类型含有三个成员
struct Arr {
	int *pBase;//存储的是数组第一个元素的地址
	int len;//数组所能容纳的最大元素的个数
	int cnt;//当前数组有效元素的个数
	//int increment;//自动增长因子，增长的位数为原位数的一倍
};


/*对函数的声明*/
void init_arr(struct Arr *inarr, int ien);//初始化的方法
bool append_arr(struct Arr *aparr, int an); //末尾追加
bool insert_arr(struct Arr *inarr, int pos, int an); //中间插入  pos的值从1开始，下标为零的元素是第一个
bool delete_arr(struct Arr *dearr, int pos, int *su);//删除  su为subtractive 的缩写
void get(struct Arr *gearr, int loc); //获取下标为X的某一个值
bool is_empty(struct Arr *isarr); //是否为空
bool is_full(struct Arr *isarr); //是否满
void sort_arr(struct Arr *soarr); //排序
void show_arr(struct Arr *sharr); //显示输出
void inversion_arr(struct Arr *inarr); //倒置


/*主函数“进行函数调用”*/
int main(void) {
	int len = 5;
	int su;
	struct Arr arr;//定义一个结构体变量，系统已经分配了内存

	init_arr(&arr, len);	//调用init函数使函数初始化

	append_arr(&arr, 1);	//调用函数append判断是否可以增加有效元素
	append_arr(&arr, 2);
	append_arr(&arr, 3);
	append_arr(&arr, 4);
	insert_arr(&arr, 2, 999);
	if (delete_arr(&arr, 1, &su)) {
		printf("删除成功,删除的元素为：%d\n", su);
	} else {
		printf("删除失败");
	}
	if (append_arr(&arr, 5)) {
		printf("追加成功\n")	;
	} else {
		printf("追加失败\n");
	}
	get(&arr, 2);
	show_arr(&arr);		//调用函数show输出数组
	inversion_arr(&arr);	//调用函数inversion倒置数组元素
	printf("\n \n数组倒置后为：\n");
	show_arr(&arr);
	sort_arr(&arr);		//调用函数sort将数组进行排序
	printf("\n \n数组排序后为：\n");
	show_arr(&arr);
	return 0;
}


/*此函数进行初始化*/
void init_arr(struct Arr *inarr, int len) {
	//首先请求系统分配一定内存空间
	inarr->pBase = (int *)malloc(sizeof(struct Arr) * len);

	//通过if语句判断系统是否成功分配了内存
	if (NULL == inarr->pBase) { //判断pBase是否为空
		printf("动态内存分配失败！\n");
		exit(-1);//终止整个程序，需要在开头添加stdlib头文件
	} else {
		inarr->len = len;	//将执行后的数组长度赋给结构体中的成员len
		inarr->cnt = 0;		//数组的有效元素个数
	}

	return;
}

/*此函数用于判断函数有效元素是否为空，空返回真，非空返回假*/
bool is_empty(struct Arr *isarr) {
	if (0 == isarr->cnt)	//结构体的成员cnt代表了数组有效元素的个数
		return true;	//返回真
	else
		return false;	//返回假

}

/*此函数用于判断数组有效元素是否与数组长度相等，用于判断数组是否满值*/
bool is_full(struct Arr *isarr) {
	if (isarr->cnt == isarr->len)
		return true;
	else
		return false;
}

/*此函数用于数组的输出*/
void show_arr(struct Arr *sharr) {
	if (is_empty(sharr)) { //此语句通过函数is_empty来判断是否为无效空数组
		printf("数组为空！\n");
	} else {
		if (is_full(sharr))
			printf("数组已满\n");
		else
			printf("数组未满\n");
		printf("数组有效内容：\n");
		for (int i = 0; i < sharr->len; i++) {
			printf("  %d", sharr->pBase[i]);
			if (i > sharr->cnt)
				printf("(此元素为空)");
		}
		printf("\n此数组的有效位数为：%d", sharr->cnt);
	}

}

/*此函数先判断数组有效数值是否已满，然后决定是否追加*/
bool append_arr(struct Arr *aparr, int na) { //na是newly added的缩写，代表了新加的元素
	if (is_full(aparr)) {
		return false;//满时返回false
	} else { //否则追加
		aparr->pBase[aparr->cnt] = na;
		/*因为前一个有效元素的位数正好对应着下一个元素的下标，
		所以可以将增加元素的下标用有效值表示*/
		(aparr->cnt)++;//追加元素后有效元素的个数也增加
		return true;
	}
}

/*此函数在一有数组元素中插入一个新的数组*/
bool insert_arr(struct Arr *inarr, int pos, int an)

//pos代表了数组中元素的位置，及在第pos位元素前插入一个an
{
	int i;
	if (pos < 1 || pos > inarr->cnt + 1) //首先判断待插入的位置是否允许插入
		return false;
	else {
		for (i = inarr->cnt - 1; i >= pos - 1; i--) { //从最后一位有效值开始向后移动一位
			inarr->pBase[i + 1] = inarr->pBase[i];
		}
		inarr->pBase[pos - 1] = an;//将待插入的值赋给空出的位的元素
		(inarr->cnt)++;//将数组的有效元素增加
		return true;
	}
}

/*此函数可以删除数组中的任意一个元素*/
bool delete_arr(struct Arr *dearr, int pos, int *su) {
	int i;

	if (is_empty(dearr))
		return false;
	if (pos < 1 || pos > dearr->cnt)
		return false;

	*su = dearr->pBase[pos - 1];//在将值删除前将值保存，以备输出

	for (i = pos; i < dearr->cnt; i++) { //直接将删除元素的后一位的值覆盖待删除的值，并依次类推
		dearr->pBase[i - 1] = dearr->pBase[i];
	}

	(dearr->cnt)--;//因为删除了一位，所以减去一个有效值。
	return true;
}

/*此函数将输出指定下标元素的数值*/
void get(struct Arr *gearr, int loc) { //loc是location的缩写
	if (loc < 1 || loc > gearr->cnt)
		printf("此位置无数值");
	else
		printf("此位置的数值为：%d\n", gearr->pBase[loc - 1]);

}

/*此函数将数组内的所有元素倒置*/
void inversion_arr(struct Arr *inarr) {
	int i = 0, j;
	int t;
	j = inarr->cnt - 1;
	//使第一个和最后一个元素的值互换，且依次类推。最终使i和j都指向一个或者值相等使停止
	while (i < j) {
		t = inarr->pBase[i];
		inarr->pBase[i] = inarr->pBase[j];
		inarr->pBase[j] = t;
		i++;
		--j;
	}
	return;
}

/*此函数将数组元素进行排序*/
void sort_arr(struct Arr *soarr) {
	int i, j, t;
	for (i = 0; i < soarr->cnt; ++i) {
		for (j = i + 1; j < soarr->cnt; j++)
			if (soarr->pBase[i] > soarr->pBase[j]) {
				t = soarr->pBase[i];
				soarr->pBase[i] = soarr->pBase[j];
				soarr->pBase[j] = t;
			}
	}
}
