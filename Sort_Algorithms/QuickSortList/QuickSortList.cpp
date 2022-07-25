//****QUICKSORT_LIST*****************

#include <iostream>

using namespace std;

typedef struct node* reff;
struct node {
	int key;// gia tri cua node hien tai
	reff next;// node ke tiep
};

struct LIST {// quan li dau, cuoi cua list
	reff pHead;
	reff pTail;
};

LIST l;// list chua cac gia rti can sort


// cac ham chinh trong chuong trinh
void listQuickSort(LIST& l);//Ham quick Sort voi danh sach lien ket
void output(LIST l);// xuat gia tri cua danh sach
void init(LIST& l);// khoi tao list rong
reff getNode(int data);// tao mot node moi chuan bi them vao list
void addTail(LIST& l, int data);//them node moi vao cuoi danh sach



//_____________________//
int main()
{
	init(l);// khoi tao danh sach rong
	int x = 1;// tao cho x khac 0 de lap
	while (x) {
		cout << "Them phan tu vao list (0 de ket thuc): ";
		cin >> x;
		if (!x) break;
		addTail(l, x);// them x vao cuoi list
	}
	listQuickSort(l);// sort lai list
	output(l);// xuat list sau khi sort
	init(l);// lam rong list
	return 0;
}
//--------------------//



void init(LIST& l)// khoi tao list rong
{
	l.pHead = l.pTail = NULL;
}

reff getNode(int data) {// tao mot node moi chuan bi them vao list
	reff p = new node;
	if (p == NULL) {// khong the tao moi node -> bao loi va thoat chuong trinh
		cout << "khong du bo nho\n";
		exit(1);
	}
	p->key = data;// gan gia tri cho node moi bang data
	p->next = NULL;// node nay duy nhat nen khong co node ke tiep
	return p;// tra ve node moi tao voi gia tri cua node la data
}

void addTail(LIST& l, int data) {//them node moi vao cuoi danh sach
	reff p = getNode(data);// tao node moi voi du lieu la bien data
	if (l.pHead == NULL) {// neu danh sach hien dang rong
		l.pHead = l.pTail = p;// cap nhat node dau tien cung hien la node cuoi cung dua list voi gia tri la node p moi
	}
	else {// da co it nhat mot node trong danh sach
		l.pTail->next = p;// them vao cuoi danh sach
		l.pTail = p;// cap nhat lai pTail
	}
}

void output(LIST l) {// xuat gia tri cua danh sach
	for (reff p = l.pHead; p/*gia tri p con ton tai*/; p = p->next/*truy cap den node ke cua node hien tai*/)
		cout << p->key << " ";
}

void listQuickSort(LIST& l)
//Ham quick Sort voi danh sach lien ket
{
	if (l.pHead == l.pTail) return;// chi co mot phan tu trong list => list da co thu tu => dk dung cua dq

	reff p = NULL, x = NULL;
	LIST l1, l2;
	init(l1), init(l2); // khoi tao 2 list moi voi l1 chua cac node co gia tri nho hon phan tu cam canh
	//l2 chua cac phan tu lon hon gia tri cam canh
	x = l.pHead;//x chi den phan tu cam canh (chon phan tu dau danh sach la phan tu cam canh)
	l.pHead = x->next;// bo x di khoi list ban dau

	while (l.pHead)// tach l thanh l1 va l2 nhu da noi o tren
	{
		// lay phan tu dau ra khoi danh sach va gan no cho p
		p = l.pHead;
		l.pHead = p->next;// cap nhat danh sach
		p->next = NULL;

		if (p->key <= x->key)
			addTail(l1, p->key);
		else addTail(l2, p->key);
	}
	listQuickSort(l1);// goi de quy sort l1
	listQuickSort(l2);// goi de quy sort l2

	//Noi (l1 - x - l2) thanh l da sap xep
	if (l1.pHead) {// neu l1 khac rong
		l.pHead = l1.pHead;// l nhan l1 lam dau danh sach
		l1.pTail->next = x;// sau do them x vao cuoi danh sach l hien tai
	}
	else l.pHead = x;// neu l1 rong -> x se la phan tu dau danh sach l 

	x->next = l2.pHead;// noi l2 vao cuoi danh sach l

	if (l2.pHead) {// neu l2 khac rong -> cap nhat pTail cho l
		l.pTail = l2.pTail;
	}
	else l.pTail = x;// nguoc lai x la phan tu pTail
}