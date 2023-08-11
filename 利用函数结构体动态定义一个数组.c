/*
Ŀ�ģ����ú����ṹ�嶯̬����һ�����飬���������һЩ����
*/
# include<stdio.h>
# include<malloc.h>
# include <stdlib.h>


//�����ݽṹ��������һ����������,���������͵����ֽ���sturuct Arr,���������ͺ���������Ա
struct Arr {
	int *pBase;//�洢���������һ��Ԫ�صĵ�ַ
	int len;//�����������ɵ����Ԫ�صĸ���
	int cnt;//��ǰ������ЧԪ�صĸ���
	//int increment;//�Զ��������ӣ�������λ��Ϊԭλ����һ��
};


/*�Ժ���������*/
void init_arr(struct Arr *inarr, int ien);//��ʼ���ķ���
bool append_arr(struct Arr *aparr, int an); //ĩβ׷��
bool insert_arr(struct Arr *inarr, int pos, int an); //�м����  pos��ֵ��1��ʼ���±�Ϊ���Ԫ���ǵ�һ��
bool delete_arr(struct Arr *dearr, int pos, int *su);//ɾ��  suΪsubtractive ����д
void get(struct Arr *gearr, int loc); //��ȡ�±�ΪX��ĳһ��ֵ
bool is_empty(struct Arr *isarr); //�Ƿ�Ϊ��
bool is_full(struct Arr *isarr); //�Ƿ���
void sort_arr(struct Arr *soarr); //����
void show_arr(struct Arr *sharr); //��ʾ���
void inversion_arr(struct Arr *inarr); //����


/*�����������к������á�*/
int main(void) {
	int len = 5;
	int su;
	struct Arr arr;//����һ���ṹ�������ϵͳ�Ѿ��������ڴ�

	init_arr(&arr, len);	//����init����ʹ������ʼ��

	append_arr(&arr, 1);	//���ú���append�ж��Ƿ����������ЧԪ��
	append_arr(&arr, 2);
	append_arr(&arr, 3);
	append_arr(&arr, 4);
	insert_arr(&arr, 2, 999);
	if (delete_arr(&arr, 1, &su)) {
		printf("ɾ���ɹ�,ɾ����Ԫ��Ϊ��%d\n", su);
	} else {
		printf("ɾ��ʧ��");
	}
	if (append_arr(&arr, 5)) {
		printf("׷�ӳɹ�\n")	;
	} else {
		printf("׷��ʧ��\n");
	}
	get(&arr, 2);
	show_arr(&arr);		//���ú���show�������
	inversion_arr(&arr);	//���ú���inversion��������Ԫ��
	printf("\n \n���鵹�ú�Ϊ��\n");
	show_arr(&arr);
	sort_arr(&arr);		//���ú���sort�������������
	printf("\n \n���������Ϊ��\n");
	show_arr(&arr);
	return 0;
}


/*�˺������г�ʼ��*/
void init_arr(struct Arr *inarr, int len) {
	//��������ϵͳ����һ���ڴ�ռ�
	inarr->pBase = (int *)malloc(sizeof(struct Arr) * len);

	//ͨ��if����ж�ϵͳ�Ƿ�ɹ��������ڴ�
	if (NULL == inarr->pBase) { //�ж�pBase�Ƿ�Ϊ��
		printf("��̬�ڴ����ʧ�ܣ�\n");
		exit(-1);//��ֹ����������Ҫ�ڿ�ͷ���stdlibͷ�ļ�
	} else {
		inarr->len = len;	//��ִ�к�����鳤�ȸ����ṹ���еĳ�Աlen
		inarr->cnt = 0;		//�������ЧԪ�ظ���
	}

	return;
}

/*�˺��������жϺ�����ЧԪ���Ƿ�Ϊ�գ��շ����棬�ǿշ��ؼ�*/
bool is_empty(struct Arr *isarr) {
	if (0 == isarr->cnt)	//�ṹ��ĳ�Աcnt������������ЧԪ�صĸ���
		return true;	//������
	else
		return false;	//���ؼ�

}

/*�˺��������ж�������ЧԪ���Ƿ������鳤����ȣ������ж������Ƿ���ֵ*/
bool is_full(struct Arr *isarr) {
	if (isarr->cnt == isarr->len)
		return true;
	else
		return false;
}

/*�˺���������������*/
void show_arr(struct Arr *sharr) {
	if (is_empty(sharr)) { //�����ͨ������is_empty���ж��Ƿ�Ϊ��Ч������
		printf("����Ϊ�գ�\n");
	} else {
		if (is_full(sharr))
			printf("��������\n");
		else
			printf("����δ��\n");
		printf("������Ч���ݣ�\n");
		for (int i = 0; i < sharr->len; i++) {
			printf("  %d", sharr->pBase[i]);
			if (i > sharr->cnt)
				printf("(��Ԫ��Ϊ��)");
		}
		printf("\n���������Чλ��Ϊ��%d", sharr->cnt);
	}

}

/*�˺������ж�������Ч��ֵ�Ƿ�������Ȼ������Ƿ�׷��*/
bool append_arr(struct Arr *aparr, int na) { //na��newly added����д���������¼ӵ�Ԫ��
	if (is_full(aparr)) {
		return false;//��ʱ����false
	} else { //����׷��
		aparr->pBase[aparr->cnt] = na;
		/*��Ϊǰһ����ЧԪ�ص�λ�����ö�Ӧ����һ��Ԫ�ص��±꣬
		���Կ��Խ�����Ԫ�ص��±�����Чֵ��ʾ*/
		(aparr->cnt)++;//׷��Ԫ�غ���ЧԪ�صĸ���Ҳ����
		return true;
	}
}

/*�˺�����һ������Ԫ���в���һ���µ�����*/
bool insert_arr(struct Arr *inarr, int pos, int an)

//pos������������Ԫ�ص�λ�ã����ڵ�posλԪ��ǰ����һ��an
{
	int i;
	if (pos < 1 || pos > inarr->cnt + 1) //�����жϴ������λ���Ƿ��������
		return false;
	else {
		for (i = inarr->cnt - 1; i >= pos - 1; i--) { //�����һλ��Чֵ��ʼ����ƶ�һλ
			inarr->pBase[i + 1] = inarr->pBase[i];
		}
		inarr->pBase[pos - 1] = an;//���������ֵ�����ճ���λ��Ԫ��
		(inarr->cnt)++;//���������ЧԪ������
		return true;
	}
}

/*�˺�������ɾ�������е�����һ��Ԫ��*/
bool delete_arr(struct Arr *dearr, int pos, int *su) {
	int i;

	if (is_empty(dearr))
		return false;
	if (pos < 1 || pos > dearr->cnt)
		return false;

	*su = dearr->pBase[pos - 1];//�ڽ�ֵɾ��ǰ��ֵ���棬�Ա����

	for (i = pos; i < dearr->cnt; i++) { //ֱ�ӽ�ɾ��Ԫ�صĺ�һλ��ֵ���Ǵ�ɾ����ֵ������������
		dearr->pBase[i - 1] = dearr->pBase[i];
	}

	(dearr->cnt)--;//��Ϊɾ����һλ�����Լ�ȥһ����Чֵ��
	return true;
}

/*�˺��������ָ���±�Ԫ�ص���ֵ*/
void get(struct Arr *gearr, int loc) { //loc��location����д
	if (loc < 1 || loc > gearr->cnt)
		printf("��λ������ֵ");
	else
		printf("��λ�õ���ֵΪ��%d\n", gearr->pBase[loc - 1]);

}

/*�˺����������ڵ�����Ԫ�ص���*/
void inversion_arr(struct Arr *inarr) {
	int i = 0, j;
	int t;
	j = inarr->cnt - 1;
	//ʹ��һ�������һ��Ԫ�ص�ֵ���������������ơ�����ʹi��j��ָ��һ������ֵ���ʹֹͣ
	while (i < j) {
		t = inarr->pBase[i];
		inarr->pBase[i] = inarr->pBase[j];
		inarr->pBase[j] = t;
		i++;
		--j;
	}
	return;
}

/*�˺���������Ԫ�ؽ�������*/
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
