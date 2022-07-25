//****RADIXSORT_LIST*****************

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
int getDigit(int n, int k);// tra ve chu so nam o vi tri k+1 theo thu tu tu cuoi len vd (1534, 2) -> 5
void listRadixSort(LIST& l);//Ham radix Sort voi danh sach lien ket
void appendList(LIST& l, LIST& l1);// noi l1 vao duoi list l
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
	listRadixSort(l);// sort lai list
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

int getDigit(int n, int k)
// ham tra ve chu so o vi tri k+1 tinh tu duoi len
{
	int div10 = 1;
	for (int i = 1; i <= k; i++) div10 *= 10;
	return (n / div10) % 10;
}

void appendList(LIST& l, LIST& l1)
// noi l1 vao duoi list l
{
	if (!l1.pHead) return;// neu l1 rong thi khong thuc hien tiep

	if (l.pHead) // khi l da chua it nhat mot node thi ta chi can them l1 vao duoi l
		// roi cap nhap pTail
	{
		l.pTail->next = l1.pHead;
		l.pTail = l1.pTail;
	}
	else l = l1;// khi l chua co node nao -> l luc nay se chua toan bo l1 

	init(l1);// da them vao l thi xoa l1 rong de cho cac thao tac tiep theo  
}

void listRadixSort(LIST& l)
//Ham radix Sort voi danh sach lien ket
{
	LIST b[10];// list chua cac chu so 0..9
	reff p = NULL;
	if (l.pHead == l.pTail) return;// da sap xep thi thoat
	
	for (int i = 0; i < 10; i++) init(b[i]);// khoi tao buckets rong 
	
	for (int k = 0; k < 10; k++)// lan luot lay ra cac chu so o thu tu k tu duoi len
		// dung voi key toi da 9 chu so (kieu int)
		// co the tim max cac key roi chay theo so luong chu so cua so max nay 
	{
		while (l.pHead) // lay lan luot tung node roi phan phoi vao cac bucket (0->9)
		{
			p = l.pHead;
			l.pHead = p->next;
			p->next = NULL;
			int num = getDigit(p->key, k);// lay digit thu k theo thu tu tu duoi len (tinh thu 0)
			addTail(b[num], p->key);// them gia tri nay vao bucket chua tuong ung
		}
		l.pTail = l.pHead = NULL;// nay cho chac la l rong khong can cung duoc <(*_*)>

		for (int i = 0; i < 10; i++)
			appendList(l, b[i]);// cap nhat lai list l khi sap xep theo digit thu k
	}
}