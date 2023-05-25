#include <stdio.h>
#include <stdlib.h>

typedef struct node {//node 구조체 선언
	int key;//int형 변수 key 선언
	struct node *left;//node 구조체 포인터 left 선언
	struct node *right;//node 구조체 포인터 right 선언
} Node;//구조체 별칭 Node

int initializeBST(Node** h);//headNode에 메모리를 할당하여 초기화하는 함수 선언 
                            //Node형 이중포인터를 매개변수로 하는 int형 함수
                            

void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */




int main()
{
	char command;//char형 변수 command 선언
	int key;//int형 변수 key 선언
	Node* head = NULL;//Node형 포인터 head를 NULL로 초기화
	Node* ptr = NULL;//Node형 포인터 ptr를 NULL로 초기화

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//입력받은 값 command에 할당

		switch(command) {
		case 'z': case 'Z'://z 대소문자 입력받을 경우
			initializeBST(&head);//Node의 포인터 head의 주소를 매개인자로 받아 initializeBST 함수 호출
			break;
		case 'q': case 'Q'://q 대소문자 입력받을 경우
			freeBST(head);//Node의 포인터 head 매개인자로 받아 freeBST함수 호출
			break;
		case 'n': case 'N'://n 대소문자 입력받을 경우
			printf("Your Key = ");
			scanf("%d", &key);//입력 받은 값 key에 할당
			insert(head, key);//포인터 head와 변수 key를 매개인자로 받아 insert 함수 호출
			break;
		case 'd': case 'D'://d 대소문자 입력받을 경우
			printf("Your Key = ");
			scanf("%d", &key);//입력받은 값 key에 할당
			deleteLeafNode(head, key);//포인터 head와 변수 key를 매개인자로 받아 deleteLeafNode함수 호출
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);//입력받은 값 key에 할당
			ptr = searchIterative(head, key);//Node의 포인터 ptr에 Node포인터 head와 key를 매개인자로 받아 실행된 searchIterative함수의 리턴 값을 할당
			if(ptr != NULL)//(ptr이 NULL이 아니라면)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);//탐색된 값과 노드 출력
			else
				printf("\n Cannot find the node [%d]\n", key);//노드를 찾지 못했다고 출력
			break;
		case 's': case 'S'://s 대소문자 입력 받았을 때
			printf("Your Key = ");
			scanf("%d", &key);//입력받은 값 key에 할당
			ptr = searchRecursive(head->left, key);//ptr에 Node포인터 head의 left, key를 매개인자로 받아 실행된 searchRecursive함수의 리턴 값을 할당
			if(ptr != NULL)//ptr이 NULL이 아니라면
				printf("\n node [%d] found at %p\n", ptr->key, ptr);//탐색된 값과 노드 출력
			else
				printf("\n Cannot find the node [%d]\n", key);//노드를 찾지 못했다고 출력
			break;

		case 'i': case 'I'://i 대소문자 입력 받았을 때
			inorderTraversal(head->left);//Node포인터 head의 left를 매개인자로 받는 inorderTraversal 함수 호출
			break;
		case 'p': case 'P'://p 대소문자 입력 받았을 때
			preorderTraversal(head->left);//Node포인터 head의 left를 매개인자로 받는 preorderTraversal 함수 호출
			break;
		case 't': case 'T'://t 대소문자 입력 받았을 때
			postorderTraversal(head->left);//Node포인터 head의 left를 매개인자로 받는 postorderTraversal 함수 호출
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');//q가 입력되지 않을 동안 반복

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)//포인터 h가 가르키는 NULL이 아니라면
		freeBST(*h);//할당된 메모리 해제        

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));//포인터 h에 Node의 크기 만큼 동적메모리 할당
	(*h)->left = NULL;	//Node포인터 h의 left 선언 후 NULL로 초기화
	(*h)->right = *h; //Node포인터 h의 right에 포인터 h 값 할당
	(*h)->key = -9999;//Node 포인터 h의 key -9999로 초기화
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if(ptr) {//ptr이 NULL이 아닐 경우
		inorderTraversal(ptr->left);//ptr의 left를 매개인자로 받는 inorderTraversal 함수 호출하여 왼쪽 노드로 재귀
		printf(" [%d] ", ptr->key);//ptr의 key (root) 값 출력
		inorderTraversal(ptr->right);//ptr의 right를 매개인자로 받아 inorderTraversal 함수 호출하여 오른쪽 노드로 재귀
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr) {//ptr이 NULL이 아닐 경우
		printf(" [%d] ", ptr->key);//ptr의 key값(root) 출력
		preorderTraversal(ptr->left);//ptr의 left를 매개인자로 받는 preorderTraversal 함수 호출하여 왼쪽노드로 재귀
		preorderTraversal(ptr->right);//ptr의 right를 매개인자로 받는 preorderTraversal 함수 호출하여 오른쪽노드로 재귀
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr) {//ptr이 NULL이 아닐 경우
		postorderTraversal(ptr->left);//ptr의 left를 매개인자로 받는 postorderTraversal함수 호출하여 왼쪽노드로 재귀
		postorderTraversal(ptr->right);//ptr의 right를 매개인자로 받는 postorderTraversal함수 호출하여 오른쪽노드로 재귀
		printf(" [%d] ", ptr->key);//ptr의 key값(root) 출력
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));//Node의 포인터 newNode를 Node의 크기만큼 동적메모리 할당
	newNode->key = key;//newNode의 key 값에 key값 할당
	newNode->left = NULL;//newNode의 left를 NULL로 초기화
	newNode->right = NULL;//newNode의 right를 NULL로 초기화

	if (head->left == NULL) {//head의 left가 NULL이라면
		head->left = newNode;//head의 left에 newNode 저장
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;//Node의 ptr에 head의 left 저장(head의 left가 root)

	Node* parentNode = NULL;//Node의 parentNode NULL로 초기화
	while(ptr != NULL) {//ptr이 NULL이 아닐동안 반복

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;//ptr의 key가 key값 과 같다면 1 리턴

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;//parentNode에 ptr값 할당

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)//ptr의 key가 key보다 작다면
			ptr = ptr->right;//ptr에 ptr의 right값 할당
		else
			ptr = ptr->left;//ptr에 ptr의 left값 할당
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)//parentNode의 key가 key값 보다 크다면
		parentNode->left = newNode;//parentNode의 left에 newNode 저장
	else
		parentNode->right = newNode;//parentNode의 right에 newNode 저장
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {//head가 NULL이라면(트리가 존재하지 않을 때)
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {//head의 left가 NULL이라면
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left;//Node의 ptr포인터에 head의 left 저장


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;//Node의 포인터 parentNode에 head 저장

	while(ptr != NULL) {//ptr이 NULL이 아닐동안 반복

		if(ptr->key == key) {//ptr의 key가 key값과 같다면
			if(ptr->left == NULL && ptr->right == NULL) {//ptr의 left가 NULL and ptr의 right도 NULL일때

				/* root node case */
				if(parentNode == head)//parentNode가 head와 같다면
					head->left = NULL;//head의 left를 NULL로 초기화

				/* left node case or right case*/
				if(parentNode->left == ptr)//parentNode의 left가 ptr과 같다면
					parentNode->left = NULL;//parentNode의 left를 NULL로 초기화
				else
					parentNode->right = NULL;//parentNode의 right를 NULL로 초기화

				free(ptr);//ptr에 할당된 메모리 해제
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);//노드가 leaf가 아니라고 출력
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr;//parentNode에 ptr 저장

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)//ptr의 key값이 key보다 작다면
			ptr = ptr->right;//ptr에 ptr의 right값 저장
		else
			ptr = ptr->left;//ptr에 ptr의 leght 저장


	}

	printf("Cannot find the node for key [%d]\n ", key);//key값에 해당하는 node를 찾지못했다고 출력

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL)//ptr이 NULL이라면(트리가 존재하지 않는다면)
		return NULL;//NULL 리턴

	if(ptr->key < key)//ptr의 key가 key보다 작다면
		ptr = searchRecursive(ptr->right, key);//prt에 오른쪽 서브트리를 탐색한 결과를 할당	
	else if(ptr->key > key)//ptr의 key가 key보다 크다면
		ptr = searchRecursive(ptr->left, key);//ptr에 왼쪽 서브트리를 탐색한 결과를 할당

	/* if ptr->key == key */
	return ptr;//ptr 리턴

}
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;//Node의 포인터 ptr에 head의 left 저장

	while(ptr != NULL)//ptr이 NULL이 아닐동안 반복(트리가 존재할 동안)
	{
		if(ptr->key == key)//ptr의 key가 key와 같다면 
			return ptr;//ptr 리턴

		if(ptr->key < key) ptr = ptr->right;//ptr의 key가 key보다 작다면 ptr에 ptr의 right저장
		else
			ptr = ptr->left;//ptr에 ptr의 left저장
	}

	return NULL;
}

void freeNode(Node* ptr)//노드의 메모리 할당 해제
{
	if(ptr) {//ptr이 NULL이 아니라면
		freeNode(ptr->left);//ptr의 left에 할당된 메모리 해제
		freeNode(ptr->right);//ptr의 right에 할당된 메모리 해제
		free(ptr);//ptr 메모리 해제
	}
}

int freeBST(Node* head)//트리의 모든 메모리 할당 해제
{

	if(head->left == head)//head의 left가 head와 같다면
	{
		free(head);//head에 할당된 메모리 해제
		return 1;
	}

	Node* p = head->left;//Node의 포인터 p에 head의 left 저장

	freeNode(p);//p의 노드 메모리에 할당된 메모리 해제

	free(head);//head에 할당된 메모리 해제
	return 1;
}




