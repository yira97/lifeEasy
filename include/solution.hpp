

#include <array>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

namespace ns_addTwoNumbers {
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};
} // namespace ns_addTwoNumbers

class Solution {
  void test_twoSum() {
    vector<int> twoSum_param1 = {2, 7, 11, 15};
    vector<int> twoSum_res_1 = {0, 1};
    vector<int> twoSum_res_2 = {1, 0};

    auto twoSum_res = this->twoSum(twoSum_param1, 9);
    bool pass;
    if (twoSum_res[0] == twoSum_res_1[0] && twoSum_res[1] == twoSum_res_1[1] &&
        twoSum_res.size() == twoSum_res_1.size()) {
      pass = true;
    } else if (twoSum_res[0] == twoSum_res_2[0] &&
               twoSum_res[1] == twoSum_res_2[1] &&
               twoSum_res.size() == twoSum_res_2.size()) {
      pass = true;
    }
    if (!pass) {
      throw logic_error("test_twoSum failed");
    }
  }

  void test_addTwoNumbers() {
    using namespace ns_addTwoNumbers;
    // 输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
    // 输出：7 -> 0 -> 8
    // 原因：342 + 465 = 807
    auto param1 = ListNode(2);
    auto param1_2 = ListNode(4);
    auto param1_3 = ListNode(3);
    param1.next = &param1_2;
    param1_2.next = &param1_3;

    auto param2 = ListNode(5);
    auto param2_2 = ListNode(6);
    auto param2_3 = ListNode(4);
    param2.next = &param2_2;
    param2_2.next = &param2_3;

    auto res = this->addTwoNumbers(&param1, &param2);
    if (res == nullptr) {
      throw logic_error("test_addTwoNumbers failed: 1");
    }
    if (res->val != 7 || res->next == nullptr) {
      throw logic_error("test_addTwoNumbers failed: 2");
    }
    res = res->next;
    if (res->val != 0 || res->next == nullptr) {
      throw logic_error("test_addTwoNumbers failed: 3");
    }
    res = res->next;
    if (res->val != 8 || res->next != nullptr) {
      throw logic_error("test_addTwoNumbers failed: 4");
    }
  }

  void test_lengthOfLongestSubstring() {
    int res_1 = lengthOfLongestSubstring("abcabcbb");
    if (res_1 != 3) {
      throw logic_error("test_lengthOfLongestSubstring failed: 1");
    }

    int res_2 = lengthOfLongestSubstring("bbbbb");
    if (res_2 != 1) {
      throw logic_error("test_lengthOfLongestSubstring failed: 2");
    }

    int res_3 = lengthOfLongestSubstring("pwwkew");
    if (res_3 != 3) {
      throw logic_error("test_lengthOfLongestSubstring failed: 3");
    }
  }

public:
  void Test() {
    test_twoSum();
    test_addTwoNumbers();
    test_lengthOfLongestSubstring();
  }

  // 给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那
  // 两个 整数，并返回他们的数组下标。
  // 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。
  //
  // 示例:
  // 给定 nums = [2, 7, 11, 15], target = 9
  // 因为 nums[0] + nums[1] = 2 + 7 = 9
  // 所以返回 [0, 1]
  vector<int> twoSum(vector<int> &nums, int target) {
    map<int, int> rec_dict{};
    for (int i = 0, i_limit = nums.size(); i < i_limit; i++) {
      const auto &n = nums[i];
      auto ans = rec_dict.find(target - n);
      if (ans != rec_dict.end()) {
        return {ans->second, i};
      }
      rec_dict[n] = i;
    }
    return {-1, -1};
  }

  // 给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序
  // 的方式存储的，并且它们的每个节点只能存储 一位 数字。
  // 如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。
  // 您可以假设除了数字 0 之外，这两个数都不会以 0 开头。
  //
  // 示例：
  // 输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
  // 输出：7 -> 0 -> 8
  // 原因：342 + 465 = 807
  ns_addTwoNumbers::ListNode *addTwoNumbers(ns_addTwoNumbers::ListNode *l1,
                                            ns_addTwoNumbers::ListNode *l2) {
    using namespace ns_addTwoNumbers;
    int sum = l1->val + l2->val;
    bool carry = sum >= 10;
    auto res_head = new ListNode(sum % 10);
    auto res = res_head;

    while (l1->next != nullptr || l2->next != nullptr || carry) {
      sum = carry ? 1 : 0;
      if (l1->next != nullptr) {
        l1 = l1->next;
        sum += l1->val;
      }
      if (l2->next != nullptr) {
        l2 = l2->next;
        sum += l2->val;
      }
      // assert(sum > 0)
      res->next = new ListNode(sum % 10);
      res = res->next;
      carry = sum >= 10;
    }

    return res_head;
  }

  // 给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
  //
  // 示例 1:
  // 输入: "abcabcbb"
  // 输出: 3
  // 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
  //
  // 示例 2:
  // 输入: "bbbbb"
  // 输出: 1
  // 解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
  //
  // 示例 3:
  // 输入: "pwwkew"
  // 输出: 3
  // 解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
  //      请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
  int lengthOfLongestSubstring(string s) {
    if (s.size() <= 1) {
      return s.size();
    }
    int max_l = 0, max_r = 0, l = 0, r = 0;
    set<char> char_set{};
    auto update_max = [&max_l, &max_r](int l, int r) {
      if (r - 1 - l > max_r - max_l) {
        max_l = l;
        max_r = r - 1;
      }
    };
    while (r < s.size()) {
      // 没见过，直接插入
      if (char_set.find(s[r]) == char_set.end()) {
        char_set.insert(s[r]);
      } else {
        // 见过了，必须中断。
        // 检查本次是否更新了最大结果。
        update_max(l, r);
        // 把左界移到正确的位置
        while (s[l] != s[r]) {
          char_set.erase(s[l]);
          ++l;
        }
        ++l;
      }
      ++r;
    }
    update_max(l, r);
    return max_r - max_l + 1;
  }

  // 给定两个大小为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。
  // 请你找出这两个正序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
  // 你可以假设 nums1 和 nums2 不会同时为空。

  // 示例 1:
  // nums1 = [1, 3]
  // nums2 = [2]
  // 则中位数是 2.0

  // 示例 2:
  // nums1 = [1, 2]
  // nums2 = [3, 4]
  // 则中位数是 (2 + 3)/2 = 2.5
  double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
    // TODO
  }

  // 给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。

  // 示例 1：
  // 输入: "babad"
  // 输出: "bab"
  // 注意: "aba" 也是一个有效答案。

  // 示例 2：
  // 输入: "cbbd"
  // 输出: "bb"
  string longestPalindrome(string s) {
    int s_size = s.size();

    auto odd_palindrome = [&s, &s_size](int c) -> array<int, 2> {
      int r = 1;
      while (c - r >= 0 && c + r < s_size && s[c - r] == s[c + r]) {
        ++r;
      }
      --r;
      return {c - r, c + r};
    };

    auto even_palindrome = [&s, &s_size](int c1) -> int {
      int c2 = c1 + 1;
      int r = 1;
      while (c1 - r >= 0 && c2 + r < s_size && s[c1 - r] == s[c2 + r]) {
        ++r;
      }
      --r;
      return {c1 - }
    };
    auto is_palindrome = [&s](int l, int r) -> bool {
      if (s.size() <= 1) {
        return true;
      }
      while (l < r) {
        if (s[l] != s[r]) {
          return false;
        }
        ++l;
        --r;
      }
      return true;
    };

    auto max_palindrome = [&s](int l, int r) -> array<int, 2> { int center = }

    while (r - l >) {
      if (l)
    }
  };