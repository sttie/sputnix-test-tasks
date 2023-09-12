#include <vector>
#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* mergeKLists(const std::vector<ListNode*>& lists) {
    static const auto comparator = [](ListNode* a, ListNode* b) {
        return a->val > b->val;
    };

    std::vector<ListNode*> heap;
    heap.reserve(lists.size());
    for (auto list : lists){
        if (list) {
            heap.push_back(list);
        }
    }
    std::make_heap(heap.begin(), heap.end(), comparator);

    ListNode fake_node;
    ListNode* current = &fake_node;
    while (heap.size() > 0){
        current->next = heap.front();
        std::pop_heap(heap.begin(), heap.end(), comparator); 
        heap.pop_back(); 

        current = current->next;
        if (current->next) {
            heap.push_back(current->next); 
            std::push_heap(heap.begin(), heap.end(), comparator);
        }
    }

    return fake_node.next;
}

ListNode* CreateListFromVector(const std::vector<int>& values) {
    ListNode fake_node;
    ListNode* current = &fake_node;

    for (int value : values) {
        current->next = new ListNode{value};
        current = current->next;
    }

    return fake_node.next;
}

bool AreListsEqual(ListNode* list1, ListNode* list2) {
    auto current1 = list1, current2 = list2;
    while (current1 != nullptr && current2 != nullptr) {
        if (current1->val != current2->val) {
            return false;
        }

        current1 = current1->next;
        current2 = current2->next;
    }

    return (current1 == nullptr && current2 == nullptr) ? true : false;
}

void PrintTestResult(int test_number, bool success) {
    std::cout << "Test #" << test_number << ": ";
    if (success)
        std::cout << "successed!";
    else
        std::cout << "failed!";
    std::cout << std::endl;
}

void Test1() {
    auto list1 = CreateListFromVector(std::vector<int>{-11, -10, 1, 4, 5});
    auto list2 = CreateListFromVector(std::vector<int>{-10, 1, 3, 4});
    auto list3 = CreateListFromVector(std::vector<int>{-20});
    auto expected = CreateListFromVector(std::vector<int>{-20, -11, -10, -10, 1, 1, 3, 4, 4, 5});

    bool equal = AreListsEqual(mergeKLists(std::vector<ListNode*>{list1, list2, list3}), expected);
    PrintTestResult(1, equal);
}

void Test2() {
    auto list1 = CreateListFromVector(std::vector<int>{});
    auto list2 = CreateListFromVector(std::vector<int>{});
    auto list3 = CreateListFromVector(std::vector<int>{});
    auto expected = CreateListFromVector(std::vector<int>{});

    bool equal = AreListsEqual(mergeKLists(std::vector<ListNode*>{list1, list2, list3}), expected);
    PrintTestResult(2, equal);
}

void Test3() {
    auto list1 = CreateListFromVector(std::vector<int>{});
    auto list2 = CreateListFromVector(std::vector<int>{2});
    auto list3 = CreateListFromVector(std::vector<int>{});
    auto expected = CreateListFromVector(std::vector<int>{2});

    bool equal = AreListsEqual(mergeKLists(std::vector<ListNode*>{list1, list2, list3}), expected);
    PrintTestResult(3, equal);
}

int main() {
    Test1();
    Test2();
    Test3();

    return 0;
}
