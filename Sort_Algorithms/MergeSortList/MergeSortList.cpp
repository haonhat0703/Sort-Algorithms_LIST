//****MERGESORT_LIST*****************

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
void listMergeSort(LIST& l);//Ham merge Sort voi danh sach lien ket
void mergeList(LIST& l, LIST& l1, LIST& l2);//gop l1, l2 thanh danh sach l
void DistributeList(LIST& l, LIST& l1, LIST& l2);// ham chia danh sach l thanh hai danh sach con l1, l2 voi l1 chua nua ds dau cua l 
// l2 chua nua ds sau cua l
void output(LIST l);// xuat gia tri cua danh sach
reff getMid(LIST l);// ham tim phan tu chinh giua cua mot list
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
	listMergeSort(l);// sort lai list
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
	cout << endl;
}

reff getMid(LIST l) 
// ham tim phan tu chinh giua cua mot list
{
	if (l.pHead==l.pTail) return l.pHead;// khi danh sach rong hoac co 1 node
	reff p = l.pHead, q = l.pHead;
	while (q->next && q->next->next) {
		p = p->next;
		q = q->next->next;
	}
	return p;
}

void DistributeList(LIST& l, LIST& l1, LIST& l2)
// ham chia danh sach l thanh hai danh sach con l1, l2 voi l1 chua nua ds dau cua l 
// l2 chua nua ds sau cua l
{
	reff mid = getMid(l);// tim node tro den phan tu giua cua danh sach l
	
	// chia danh sach thanh 2 nua l1 va l2
	l1.pHead = l.pHead;
	l1.pTail = mid;

	l2.pHead = mid->next;
	l2.pTail = l.pTail;
	mid->next = NULL;
	init(l);// khi nay danh sach l se tro thanh rong
}

void mergeList(LIST& l, LIST& l1, LIST& l2) 
// gop l1, l2 thanh l 
{
	reff p = NULL;
		
	while ( (l1.pHead) && (l2.pHead) )// dieu kien lap khi l1 va l2 deu con de so sanh, dung khi l1 hoac l2 tro NULL
	{
		if (l1.pHead->key <= l2.pHead->key) {// so sanh hay key roi update cho p
			p = l1.pHead;
			l1.pHead = p->next;
		}
		else
		{
			p = l2.pHead;
			l2.pHead = p->next;
		}
		p->next = NULL;// 1 node p
		addTail(l, p->key);// them gia tri cua p vao cuoi list l
	}
	
	if (l1.pHead) {// khi l1 con => l2 tro NULL => noi l1 vao cuoi danh sach l
		if (l.pHead == NULL) {// xu li khi l chua co phan tu nao khi do l chinh la l1
			l.pHead = l1.pHead;
			l.pTail = l1.pTail;
		}
		else {// khi l da co thi noi l1 vao cuoi va cap nhat pTail thanh pTail cua l1
			l.pTail->next = l1.pHead;
			l.pTail = l1.pTail;
		}
	} else if (l2.pHead) {// tuong tu voi truong hop nguoc lai
		if (l.pHead == NULL) {
			l.pHead = l2.pHead;
			l.pTail = l2.pTail;
		}
		else {
			l.pTail->next = l2.pHead;
			l.pTail = l2.pTail;
		}
	}
}

void listMergeSort(LIST& l)
//Ham merge Sort voi danh sach lien ket
{
	if (l.pHead == l.pTail) return;// co 1 phan tu hoac dang rong => da duoc sap xep => stop
	LIST l1, l2;
	init(l1), init(l2);// khoi tao 

	DistributeList(l, l1, l2);// chia nho thanh hai phan l1 va l2 
	
	listMergeSort(l1);// sort l1
	listMergeSort(l2);// sort l2
			
	mergeList(l, l1, l2);// ghep l1 l2 thanh l
	
}