#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <time.h>
const char russianAlphabet[] = "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
const char delimiters[] = " ;,][{}/|)(-_+=*?^%$#@!&:<>\\/\"";

struct node
{
	int sym;
	node* pNext;
};

int get_key()
{
	int key = _getch();
	if ((key == 0) || (key == 224)) key = _getch();
	return key;
}

void message(const char* msg)
{
	system("cls");
	printf("%s", msg); Sleep(500);
	for (int i = 0; i < 3; i++)
	{
		printf(".");
		Sleep(500);
	}
}

bool russianAlphaCheck(int sym)
{
	return strchr(russianAlphabet, sym);
}

bool delimitersCheck(int sym)
{
	return strchr(delimiters, sym);
}

int setSymbol()
{
	while (true)
	{
		system("cls");
		printf("   Введите символ. Для отмены ввода нажмите Enter.\n   ");
		int temp = get_key();
		if (temp == 13)
		{
			message("   Отмена ввода");
			return 0;
		}
		else
		{
			if (russianAlphaCheck(temp) || delimitersCheck(temp))
			{
				printf("%c", temp);
				Sleep(500);
				return temp;
			}
			else
				message("   Введён недопустимый символ");
		}
	}
}

int randomSymOfSequence(node* list, unsigned sequenceLength)
{
	srand((unsigned)time(NULL));
	unsigned randomSymOfSequence = 1 + rand() % sequenceLength;
	while (--randomSymOfSequence)
		list = list->pNext;
	return list->sym;
}

void clearList(node** head) 
{ 
	node* temp; 
	while (*head) 
	{ 
		temp = *head; 
		*head = (*head)->pNext; 
		free(temp); 
	} 
}

void deleteSequence(node** first, node** last)
{
	node* temp;
	while (*first != *last)
	{
		temp = *first;
		*first = (*first)->pNext;
		free(temp);
	}
}

unsigned processList(node* list)
{
	node* firstSymOfSequencePointer = NULL;
	node* lastSymOfSequencePointer	= NULL;
	unsigned count = 0;
	while (list)
	{
		unsigned sequenceLength = 1;
		if (delimitersCheck(list->sym))
		{
			firstSymOfSequencePointer = list;
			while (list->pNext && delimitersCheck((list->pNext)->sym))
			{
				sequenceLength++;
				list = list->pNext;
			}
			lastSymOfSequencePointer = list;
			if (sequenceLength > 1)
			{
				node* tmp = lastSymOfSequencePointer->pNext;
				firstSymOfSequencePointer->sym = randomSymOfSequence(firstSymOfSequencePointer, sequenceLength);
				deleteSequence(&firstSymOfSequencePointer->pNext, &lastSymOfSequencePointer);
				firstSymOfSequencePointer->pNext = tmp;
				count++;
			}
		}
		list = list->pNext;
	}
	return count;
}

node* deleteNode(node** head, node** current)
{
	if (head && current)
	{
		node* tempPointer = (*current)->pNext;
		node* tempHead = *head;
		if (*head != *current)
		{
			while (tempHead->pNext != *current)
				tempHead = tempHead->pNext;
			tempHead->pNext = tempPointer;
			free(*current);
		}
		else
		{
			free(*head);
			*head = tempPointer;
		}
		return tempPointer;
	}
	else
		return NULL;
}

node* insertHead(node* head, int sym)
{
	node* newHead = (node*)malloc(sizeof(node));
	if (newHead)
	{
		newHead->sym = sym;
		newHead->pNext = head;
		return newHead;
	}
	return head;
}

node* insertNode(node* current, int sym)
{
	if (current)
	{
		node* newNode = NULL;
		newNode = (node*)malloc(sizeof(node));
		if (newNode)
		{
			newNode->pNext = current->pNext;
			current->pNext = newNode;
			newNode->sym = sym;
		}
		return newNode;
	}
	else
		return insertHead(current, sym);
}

void printList(node* list, node* current)
{
	if (list)
	{
		printf("   Список:\n   ");
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		while (list)
		{
			if (list == current)
				SetConsoleTextAttribute(handle, (WORD)((15 << 4) | 0));
			printf("%c", list->sym);
			SetConsoleTextAttribute(handle, (WORD)((0 << 4) | 15));
			list = list->pNext;
		}
		printf("\n\n");
	}
	else
		printf("   Список пуст.\n\n\n");
}

int listViewMenu(int m, node* head, node** current)
{
	while (true)
	{
		system("cls");
		printList(head, *current);
		switch (m)
		{
		case 0:
			printf(" > Вставить новый корень списка\t\t <\n   Вставить новый элемент после текущего\n   Удалить выбранный элемент\n   Заменить выбранный элемент\n   Вернуться в главное меню\n");
			break;
		case 1:
			printf("   Вставить новый корень списка\n > Вставить новый элемент после текущего <\n   Удалить выбранный элемент\n"
				"   Заменить выбранный элемент\n   Вернуться в главное меню\n");
			break;
		case 2:
			printf("   Вставить новый корень списка\n   Вставить новый элемент после текущего\n > Удалить выбранный элемент\t\t <\n"
				"   Заменить выбранный элемент\n   Вернуться в главное меню\n");
			break;
		case 3:
			printf("   Вставить новый корень списка\n   Вставить новый элемент после текущего\n   Удалить выбранный элемент\n"
				" > Заменить выбранный элемент\t\t <\n   Вернуться в главное меню\n");
			break;
		case 4:
			printf("   Вставить новый корень списка\n   Вставить новый элемент после текущего\n   Удалить выбранный элемент\n"
				"   Заменить выбранный элемент\n > Вернуться в главное меню\t\t <\n");
			break;
		}
		printf("\n\n\n   Навигация по списку:\n   Стрелка влево - к началу списка\n   Стрелка вправо - к следующему элементу");
		int key = get_key();
		switch (key)
		{
		case 72:
			if (m > 0) m--;
			else m = 4;
			break;
		case 80:
			if (m < 4) m++;
			else m = 0;
			break;
		case 77:
			if (head)
			{
				if ((*current)->pNext == NULL)
					*current = head;
				else
					*current = (*current)->pNext;
			}
			break;
		case 75:
			if (head)
				*current = head;
			break;
		case 13:
			return m;
		}
	}
}

int listView(node** head)
{
	int m = 0;
	node* current = *head;
	while (true)
	{
		switch (m = listViewMenu(m, *head, &current))
		{
		case 0:
			if (int sym = setSymbol())
				current = *head = insertHead(*head, sym);
			break;
		case 1:
			if (int sym = setSymbol())
			{
				current = insertNode(current, sym);
				if (*head == NULL)
				{
					message("   Список был пуст. Элемент назначен корнем списка");
					*head = current;
				}
			}
			break;
		case 2:
			if (*head)
			{
				current = deleteNode(head, &current);
				if (current == NULL)
					current = *head;
				if (*head == NULL)
					*head = current;
			}
			else
				message("   Список пуст, удаление невозможно");
			break;
		case 3:
			if (*head)
			{
				if (int newSym = setSymbol())
					current->sym = newSym;
			}
			else
				message("   Список пуст, невозможно заменить символ");
			break;
		case 4:
			return 0;
		}
	}
}

int main_menu(node* head, int k)
{
	while (true)
	{
		system("cls");
		printList(head, NULL);
		switch (k)
		{
		case 0:
			printf(" > Редактировать список\t<\n   Обработать список\n   Завершить работу\n");
			break;
		case 1:
			printf("   Редактировать список\n > Обработать список\t<\n   Завершить работу\n");
			break;
		case 2:
			printf("   Редактировать список\n   Обработать список\n > Завершить работу\t<\n");
			break;
		}
		switch (get_key())
		{
		case 72:
			if (k > 0) k--;
			else k = 2;
			break;
		case 80:
			if (k < 2) k++;
			else k = 0;
			break;
		case 13:
			return k;
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	node* head = NULL;
	int k = 0;
	while (true)
	{
		switch (k = main_menu(head, k))
		{
		case 0:
			listView(&head);
			break;
		case 1:
			message("   Обработка списка");
			if (processList(head))
				message("   Результат обработки списка: список был измёнен");
			else
				message("   Результат обработки списка: список не был измёнен");
			break;
		case 2:
			clearList(&head);
			system("cls");
			return 0;
		}
	}
}